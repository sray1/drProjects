	Subroutine Expand_BezierDispControls_C1(T,nStifS,nStifC,Xc,Xf
     &														,iOut)
!
	Real(kind=8)	T
	Dimension		T(nStifS,nStifC)
!
!	Xc(nXc)		= Solved Bezier Displacement Controls (Input)
!	Xf(nFf)		= Full Bezier Displacement Controls (Output)	
!
	real(kind = 8)	Xf     ,Xc     ,tipdis
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
!	Tip displacement at r=1;s=1/2
	tipdis = 0.25*(Xf(nStifS) + Xf(nStifS-6))+0.5*Xf(nStifS-3)
	write(iOut,1030) tipdis
!	
!   		 
	return
 1000 Format(/2x,"Just before Leaving: Expand_BezierDispControls_C1"/)
 1010 Format(/2x,"C1 DisplacementControls: 1x",I3/
     &										14(4(2x,F16.4)/) )
 1020 Format(/2x,"FULL DisplacementControls: 1x",I3/
     &										14(4(2x,F16.4)/) )
 1030 Format(/2x,"Tip. Displacement(r=1;s=1/2)   =",F10.4/)
	end 
