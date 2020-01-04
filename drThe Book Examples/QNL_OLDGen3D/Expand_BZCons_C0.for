!
	Subroutine Expand_BezierDispControls_C0(Xc,nXc,Xf,nXf,Sx,nSx,
     &												iCont,iOut)
!
!	Xc(nXc)		= Solved Bezier Displacement Controls (Input)
!	Xf(nFf)		= Full Bezier Displacement Controls (Output)	
!
	real(kind = 8)	Xf     ,Xc          
	Dimension		Xf(nXf),Xc(nXc)
!
!
	integer i,ii
!
	integer			Sx     ,Drop   
	Dimension		Sx(nSx),Drop(nSx)	
!------------------------------------ Initialize
	nDrop = nSx
	do 3 i = 1,nDrop
    3 Drop(i) = Sx(i)
!------------------------------
!
	Xf = 0.0D0	! initialize
	ii = 0
!			
	do 20 i = 1,nXf
	do 10 k = 1,nDrop
	if(i == Drop(k)) then
		go to 20
	end if
   10	continue
	ii = ii + 1
!
	Xf(i) = Xc(ii)
   20 continue
  100 continue
!
	iPrt = 0
	if(iPrt == 1) Then
		write(iOut,1000)
		write(iOut,1010) nXc,(XC(i),i = 1,nXc)
		write(iOut,1020) nXf,(XF(i),i = 1,nXf)
	endif
!
	return
!
 1000 Format(/2x,"Just before Leaving: Expand_BezierDispControls_C0"/)
 1010 Format(/2x,"Supported DisplacementControls: 1x"I3/
     &										3(4(2x,F16.8)/) )
 1020 Format(/2x,"Non-Support DisplacementControls: 1x"I3/
     &										3(5(2x,F16.8)/) )
	end 
!
