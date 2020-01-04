	Subroutine Calc_Dis_at_a_Pt(Dis,nDim,Qd,nQd,nQd1,nQd2,
     &							ri,rj,iOut)
!***********************************************************
!	assumed: stored in nQc2 sets of nQc1 data, i.e.,
!			i=1,nQc1 data nQc2 times 
!***********************************************************
	Implicit Real(kind=8) (a-h,o-z)
!--------------------------------------
	Real(kind=8)	Dis      ,Qd     ,Bri      ,Brj    
	Dimension		Dis(nDim),Qd(nQd),Bri(nQd1),Brj(nQd2)
	real(kind = 8)	ri,rj,Brij
	integer			nDim,nQd,nQd1,nQd2,iOut
	integer			nQd12,k,kStart,loc
!	-------------------------------------------- Basis Functions		 
	call Bernstein(Bri,nQd1,ri,iOut)
	call Bernstein(Brj,nQd2,rj,iOut)
!	------------------------------
	nQd12	= nQd1*nQd2
	Dis		= 0.D0
!
	do k = 1,nDim		
		kStart	= (k-1)*nQd12

		do j= 1,nQd2
			do i= 1,nQd1
				Brij	= Bri(i)*Brj(j)
				loc		= kStart + (i-1)*nQd2 + j
				Dis(k)	= Dis(k) + Brij*Qd(loc) 
			end do !i
		end do !j
      end do !k
!
!	done
!
	return
	end
