	Subroutine FormIndex_EL2_Radial(cElemType,Indx,nStifEL,iOut)
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
			Indx( 4*(i-1) + 1) =  4*i
			Indx( 4*(i-1) +17) =  4*i + 16
		end do !i

		do i = 1,3
			Indx( i+ 1) =  32+i
			Indx( i+17) =  44+i
!
			Indx( i+ 5) =  35+i
			Indx( i+21) =  47+i

			Indx( i+ 9) =  38+i
			Indx( i+25) =  50+i

			Indx( i+13) =  41+i
			Indx( i+29) =  53+i
		end do !i
	endif
!
	write(iOut,1000) (Indx(i),i = 1,nStifEL)
!
	return
 1000 format(//"Index for 2nd Radial Element..."//4(4(2x,I10)/))
	end   		