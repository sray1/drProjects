	Subroutine FormIndex_EL2_Circum(cElemType,Indx,nStifEL,iOut)
!
!	Outputs 
!		Indx(nStifEl)	= Indx of assembly for Element 2
!
	Implicit Real(kind=8) (a-h,o-z)
	integer		Indx(nStifEL),nStifEL
	character*2	cElemtype	
!------------------------------------------------------ Indices of location in global stiffness
	if (cElemtype == "55") then     !*************WRONG: NOT USED*****************
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
	elseif (cElemtype == "44") then     !*************WRONG: NOT USED*****************
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
			Indx(1 + 4*(i-1)) =  4*i
			Indx(2 + 4*(i-1)) = 33+3*(i-1)
			Indx(3 + 4*(i-1)) = 34+3*(i-1)
			Indx(4 + 4*(i-1)) = 35+3*(i-1)
!
			Indx(17 + 4*(i-1)) = 16+4*i
			Indx(18 + 4*(i-1)) = 45+3*(i-1)
			Indx(19 + 4*(i-1)) = 46+3*(i-1)
			Indx(20 + 4*(i-1)) = 47+3*(i-1)
		end do !i
!
	endif
!
	write(iOut,1000) (Indx(i),i=1,nStifEl)
!	------
	return
 1000 format(/
     & " Index for the 2nd Circumferentially connected element"/(4i4))
	end   		