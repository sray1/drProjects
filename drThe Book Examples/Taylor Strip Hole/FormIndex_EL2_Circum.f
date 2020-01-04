	Subroutine FormIndex_EL2_Circum(cElemType,Indx,nStifEL,iOut)
!
!	Outputs 
!		Indx(nStifEl)	= Indx of assembly for Element 2
!
	Implicit Real(kind=8) (a-h,o-z)
	integer		Indx(nStifEL),nStifEL
	character*2	cElemtype	
!------------------------------------------------------ Indices of location in global stiffness
	if (cElemtype == "55") then
		do i = 1,6
			Indx( i   ) =  30+i
			Indx( i+ 6) =  72+i
			Indx( i+12) =  78+i
			Indx( i+18) =  84+i
			Indx( i+24) =  90+i
			Indx( i+30) =  96+i
!
			Indx( i+36) =  66+i
			Indx( i+42) = 102+i
			Indx( i+48) = 108+i
			Indx( i+54) = 114+i
			Indx( i+60) = 120+i
			Indx( i+66) = 126+i
		end do !i
!
	elseif (cElemtype == "44") then
		do i = 1,5
			Indx( i   ) =  20+i
			Indx( i+ 5) =  50+i
			Indx( i+10) =  55+i
			Indx( i+15) =  60+i
			Indx( i+20) =  65+i
!
			Indx( i+25) =  45+i
			Indx( i+30) =  70+i
			Indx( i+35) =  75+i
			Indx( i+40) =  80+i
			Indx( i+45) =  85+i
		end do !i
!
	elseif (cElemtype == "33") then
		do i = 1,4
			Indx( i   ) =  12+i
			Indx( i+ 4) =  32+i
			Indx( i+ 8) =  36+i
			Indx( i+12) =  40+i
!
			Indx( i+16) =  28+i
			Indx( i+20) =  44+i
			Indx( i+24) =  48+i
			Indx( i+28) =  52+i
		end do !i
!
		if(1 == 0) then
		Indx( 1) = 13
		Indx( 2) = 14
		Indx( 3) = 15
		Indx( 4) = 16

		Indx( 5) = 33
		Indx( 6) = 34
		Indx( 7) = 35
		Indx( 8) = 36

		Indx( 9) = 37
		Indx(10) = 38
		Indx(11) = 39
		Indx(12) = 40

		Indx(13) = 41
		Indx(14) = 42
		Indx(15) = 43
		Indx(16) = 44

		Indx(17) = 29
		Indx(18) = 30
		Indx(19) = 31
		Indx(20) = 32

		Indx(21) = 45
		Indx(22) = 46
		Indx(23) = 47
		Indx(24) = 48

		Indx(25) = 49
		Indx(26) = 50
		Indx(27) = 51
		Indx(28) = 52

		Indx(29) = 53
		Indx(30) = 54
		Indx(31) = 55
		Indx(32) = 56
		endif
	endif
!
	write(iOut,1000) (Indx(i),i=1,nStifEl)
!	------
	return
 1000 format(/
     & " Index for the 2nd Circumferentially connected element"/(4i4))
	end   		