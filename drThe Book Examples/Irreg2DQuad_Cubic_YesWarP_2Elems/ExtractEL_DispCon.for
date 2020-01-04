	Subroutine Extract_DispCon(XS,nStifS,XE,nStifEL,Nel,iOut)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM
!	EQUATIONS 1,13,17 Rows include = 0.0
!
!	XS(nStifS)	= Solved Bezier Displacement Controls (Input)
!	XE(nStifEL)	= Element Bezier Displacement Controls (Output)	
!
	real(kind = 8)	XS        ,XE     
	Dimension		XS(nStifS),XE(nStifEL)
!
!
	integer i,ii,EL1(24),EL2(24)
	DATA EL1/ 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,
     &         13,14,15,16,17,18,19,20,21,22,23,24/
	DATA EL2/ 4,25,26,27, 8,28,29,30,12,31,32,33,
     &         16,34,35,36,20,37,38,39,24,40,41,42/
!
!
!------------------------------
	XE = 0.D0	! initialize
	ii = 0
!
	if (Nel == 1) Then			
		do 20 i = 1,nStifEL
		XE(i) = XS(EL1(i))
   20		continue
	elseif  (Nel == 2) Then
		do 30 i = 1,nStifEL
		XE(i) = XS(EL2(i))
   30		continue
	endif
  100 continue
!
	write(iOut,1000)
	write(iOut,1010) Nel,nStifEL,(XE(i),i = 1,nStifEL)
!	
!   		 
	return
 1000 Format(/2x,"Just before Leaving: Extract_DispCon"/)
 1010 Format(/2x,"Extracted DisControls for Element ",I2,": 1x",I3/
     &										4(8(2x,F10.4)/) )
	end
