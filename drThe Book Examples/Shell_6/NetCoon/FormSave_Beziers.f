	Subroutine FormSave_Beziers(Rad,THER,PHIR,DefSav,nPtsDef,nPtsi,
     &							ConSav,nPtsCon,iOutS,iOutC,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!	====================================================
	Real(kind=8)	Q1(3),Q2(3),Q3(3),Q4(3),B1(3),B3(3)    
	Real(kind=8)	Qe(3,4),DefSav(3,nPtsDef)    
	Real(kind=8)	ConSav(3,4,4)    
	Real(kind=8)	Rad,Ang    
	
	Data			zero/0.D0/,one/1.D0/,two/2.D0/,three/3.D0/
	Data			nDim/3/
!	-----------------------
	mCount = 0
	DefSave = zero
!	------------------------------------------------------------- Compute Bezier End Controls
	nCur = 1
	call FormmEndBezs(Rad,THER,PHIR,Q1,Q4,3,nCur,iOut)
	call Form B1_B3(Rad,THER,PHIR,Q1,Q4,B1,B3,3,nCur,iOut)
	write(iOut,1010) nCur,(Q1(i),i=1,3),(Q4(i),i=1,3),
     &                 	  (B1(i),i=1,3),(B3(i),i=1,3)
	call Form EdgeCubic(Q1,Q2,Q3,Q4,B1,B3,nDim,iOut)
	write(iOut,1020) (Q2(i),i=1,3),(Q3(i),i=1,3)
	call PackEdgeControls(Q4,Q3,Q2,Q1,Qe,iOut)
!	============================================== for edge controls plot check
	do n = 1,4
		write(iOutC,1040) Qe(1,n),Qe(2,n),Qe(3,n)
	end do
!	============================================== for edge controls plot check end
	write(iOut,1030) ((Qe(i,j),j=1,4),i=1,3)
	call DeformOut_MatLab_Edges(Qe,3,4,DefSav,nPtsDef,
     &							nPtsi,mCount,iOut,iOutS)
!	============================================== for NetCoon generation
	do k = 1,3
		ConSav(k,1,1) = Q1(k) 
		ConSav(k,2,1) = Q2(k) 
		ConSav(k,3,1) = Q3(k) 
		ConSav(k,4,1) = Q4(k) 
	end do
!	============================================== for NetCoon generation end
	nCur = 2
	call FormmEndBezs(Rad,THER,PHIR,Q1,Q4,3,nCur,iOut)
	call Form B1_B3(Rad,THER,PHIR,Q1,Q4,B1,B3,3,nCur,iOut)
	write(iOut,1010) nCur,(Q1(i),i=1,3),(Q4(i),i=1,3),
     &                 	  (B1(i),i=1,3),(B3(i),i=1,3)
	call Form EdgeCubic(Q1,Q2,Q3,Q4,B1,B3,nDim,iOut)
	write(iOut,1020) (Q2(i),i=1,3),(Q3(i),i=1,3)
	call PackEdgeControls(Q1,Q2,Q3,Q4,Qe,iOut)
!	============================================== for edge controls plot check
	do n = 1,4
		write(iOutC,1040) Qe(1,n),Qe(2,n),Qe(3,n)
	end do
!	============================================== for edge controls plot check end
	call DeformOut_MatLab_Edges(Qe,3,4,DefSav,nPtsDef,
     &							nPtsi,mCount,iOut,iOutS)
!	============================================== for NetCoon generation
	do k = 1,3
		ConSav(k,1,1) = Q1(k) 
		ConSav(k,1,2) = Q2(k) 
		ConSav(k,1,3) = Q3(k) 
		ConSav(k,1,4) = Q4(k) 
	end do
!	============================================== for NetCoon generation end
	nCur = 3
	call FormmEndBezs(Rad,THER,PHIR,Q1,Q4,3,nCur,iOut)
	call Form B1_B3(Rad,THER,PHIR,Q1,Q4,B1,B3,3,nCur,iOut)
	write(iOut,1010) nCur,(Q1(i),i=1,3),(Q4(i),i=1,3),
     &                 	  (B1(i),i=1,3),(B3(i),i=1,3)
	call Form EdgeCubic(Q1,Q2,Q3,Q4,B1,B3,nDim,iOut)
	write(iOut,1020) (Q2(i),i=1,3),(Q3(i),i=1,3)
!
	call PackEdgeControls(Q1,Q2,Q3,Q4,Qe,iOut)
!	============================================== for edge controls plot check
	do n = 1,4
		write(iOutC,1040) Qe(1,n),Qe(2,n),Qe(3,n)
	end do
!	============================================== for edge controls plot check end
	call DeformOut_MatLab_Edges(Qe,3,4,DefSav,nPtsDef,
     &							nPtsi,mCount,iOut,iOutS)
!	============================================== for NetCoon generation
	do k = 1,3
		ConSav(k,1,4) = Q1(k) 
		ConSav(k,2,4) = Q2(k) 
		ConSav(k,3,4) = Q3(k) 
		ConSav(k,4,4) = Q4(k) 
	end do
!	============================================== for NetCoon generation end
	nCur = 4
	call FormmEndBezs(Rad,THER,PHIR,Q1,Q4,3,nCur,iOut)
	call Form B1_B3(Rad,THER,PHIR,Q1,Q4,B1,B3,3,nCur,iOut)
	write(iOut,1010) nCur,(Q1(i),i=1,3),(Q4(i),i=1,3),
     &                 	  (B1(i),i=1,3),(B3(i),i=1,3)
	call Form EdgeCubic(Q1,Q2,Q3,Q4,B1,B3,nDim,iOut)
	write(iOut,1020) (Q2(i),i=1,3),(Q3(i),i=1,3)
	call PackEdgeControls(Q4,Q3,Q2,Q1,Qe,iOut)
!	============================================== for edge controls plot check
	do n = 1,4
		write(iOutC,1040) Qe(1,n),Qe(2,n),Qe(3,n)
	end do
!	============================================== for edge controls plot check end
	call DeformOut_MatLab_Edges(Qe,3,4,DefSav,nPtsDef,
     &							nPtsi,mCount,iOut,iOutS)
!	============================================== for NetCoon generation
	do k = 1,3
		ConSav(k,4,1) = Q1(k) 
		ConSav(k,4,2) = Q2(k) 
		ConSav(k,4,3) = Q3(k) 
		ConSav(k,4,4) = Q4(k) 
	end do
!	============================================== for NetCoon generation end
	do n = 1,mCount
		write(iOutS,1040) DefSav(1,n),DefSav(2,n),DefSav(3,n)
	end do
!
!	done
!
	return
 1010 format(  2x,"Edge Curve Nummber = "i10/
     &        10x,"Q1(1->3) = ",2x,3F10.4/
     &        10x,"Q4(1->3) = ",2x,3F10.4/
     &        10x,"B1(1->3) = ",2x,3F10.4/
     &        10x,"B3(1->3) = ",2x,3F10.4/)
 1020 format(
     &        10x,"Q2(1->3) = ",2x,3F10.4/
     &        10x,"Q3(1->3) = ",2x,3F10.4/)
 1030 format( 10x,"Qe(3,4)  "/3(15x,4(2x,F10.4)/) )
 1040 format(F15.2,",",F15.2,",",F15.2,",")
	end
