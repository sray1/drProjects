	Subroutine NetCoon(QcI,QcO,nDim,nQc1,nQc2,iConFEA,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!	====================================================
!	Uses Bilinear Coons Blending to Complete a Net
!
	
	Real(kind=8)	QcI(nDim,nQc1,nQc2)    
	Real(kind=8)	QcO(nDim,nQc1,nQc2)    
	Real(kind=8)	u,v,u1,v1    
	
	Data			zero/0.D0/,one/1.D0/,two/2.D0/
!	--------------------------------------------------------------- Print QcI
	write (iOut,1010)
	do j = 1,nQc2
		do i = 1,nQc1
			write (iOut,1040) i,j,QcI(1,i,j),QcI(2,i,j),QcI(3,i,j)
		end do
	end do
!	--------------------------------------------------------------- Print end
!	--------------------------------------------
	QcO = QcI
!	---------
	do k = 1,nDim
		do i = 1,nQc1
		do j = 1,nQc2
!
			u = (dfloat(i-1))/(nQc1-1)
			u1 = one - u	
			v = (dfloat(j-1))/(nQc2-1)
			v1 = one - v	
!
			QcO(k,i,j) = u1*QcO(k,1,j) + u*QcO(k,nQc1,j) 
     &				   + v1*QcO(k,i,1) + v*QcO(k,i,nQc2)
     &			       - u1*v1*QcO(k,1,1)    - u1*v*QcO(k,1,nQc2)
     &			       - u *v1*QcO(k,nQc1,1) - u *v*QcO(k,nQc1,nQc2)
		end do 
		end do 
	end do 

!	--------------------------------------------------------------- Save for Finite Element Analysis
	write (iConFEA)
     &	 ((QcO(1,i,j),QcO(2,i,j),QcO(3,i,j),j = 1,nQc2),i = 1,nQc1)
!	--------------------------------------------------------------- Print
	write (iOut,1030)
	do j = 1,nQc2
		do i = 1,nQc1
			write (iOut,1040) i,j,QcO(1,i,j),QcO(2,i,j),QcO(3,i,j)
		end do
	end do
!	--------------------------------------------------------------- Print end
!
!	done
!
	return
!
 1010 format( 10x,"QcI(3,4,4) ...  "/ )
 1020 format(F15.2,",",F15.2,",",F15.2,",")
 1030 format( 10x,"QcO(3,4,4) ...  "/ )
 1040 format( 10x,4(5x,2i4,2x,4(2x,F10.4)/) )
 1050 format(3F16.10)
	end
