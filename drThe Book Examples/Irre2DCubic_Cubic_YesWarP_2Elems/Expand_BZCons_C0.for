!
	Subroutine Expand_BezierDispControls_C0(Xc,nXc,Xf,nXf,iCont,iOut)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM
!	EQUATIONS 1,13,17 Rows include = 0.0
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
	integer			Drop
	Dimension		Drop(3),DropC0(3),DropC1(3)	
	DATA DropC0 / 1,12,16/
	DATA DropC1 / 1,10,13/
!	DATA DropC2 / 1,4,7,10,13/
	DATA nDrop/3/
!	DATA nDrop/5/
!
!------------------------------ Initialize
	if( iCont == 0) Then
		do 5 k = 1,nDrop
		Drop(k) = DropC0(k)
    5		continue
	else if( iCont == 1) Then 
		do 6 k = 1,nDrop
		Drop(k) = DropC1(k)
    6		continue
	end if
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
	write(iOut,1000)
	write(iOut,1010) nXc,(XC(i),i = 1,nXc)
	write(iOut,1020) nXf,(XF(i),i = 1,nXf)
!
	return
!
 1000 Format(/2x,"Just before Leaving: Expand_BezierDispControls_C0"/)
 1010 Format(/2x,"Supported DisplacementControls: 1x"I3/
     &										14(4(2x,F16.4)/) )
 1020 Format(/2x,"Non-Support DisplacementControls: 1x"I3/
     &										14(4(2x,F16.4)/) )
	end 
!
