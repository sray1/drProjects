!
	Subroutine Expand_BezierDispControls_C0_BCr0(T,nStifS,nStifC,Xc,Xf
     &														,iOut)
!
	Real(kind=8)	T
	Dimension		T(nStifS,nStifC)
!
!	Xc(nXc)		= Solved Bezier Displacement Controls (Input)
!	Xf(nFf)		= Full Bezier Displacement Controls (Output)	
!
	real(kind = 8)	Xf     ,Xc
	Dimension		Xf(nStifS),Xc(nStifC)
!
!
!
	Xf = 0.0D0	! initialize
!
	do 50 i = 1,nStifS
	sum =0.0D0
	do 40 k = 1,nStifC
	sum = sum + T(i,k)*Xc(k)
   40	continue
   	Xf(i) = sum
   50 continue
  100 continue 
!   		 
	write(iOut,1000)
	write(iOut,1010) nStifC,(XC(i),i = 1,nStifC)
	write(iOut,1020) nStifS,(XF(i),i = 1,nStifS)
!   		 
	return
 1000 Format(/2x,"Just before Leaving:",
     &           " Expand_BezierDispControls_C0_BCr0"/)
 1010 Format(/2x,"C0 DisplacementControls: 1x",I3/
     &										7(8(2x,F10.4)/) )
 1020 Format(/2x,"FULL DisplacementControls: 1x",I3/
     &										7(8(2x,F10.4)/) )
	end 
