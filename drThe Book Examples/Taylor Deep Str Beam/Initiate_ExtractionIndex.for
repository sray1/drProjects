	Subroutine Initiate_ExtractionIndex(cElemTyp,
     &						ELDat,nStifEL,Nel,iOut)
	
	integer		ELDat(nStifEL)
	character*2	cElemTyp
!---------------------------
	integer EL1D5(72),EL2D5(72)
	integer EL1D4(50),EL2D4(50)
	integer EL1D3(32),EL2D3(32)
	
	DATA EL1D5/	 1, 2, 3, 4,  5, 6, 7, 8,  9,10,11,12,
     &			13,14,15,16, 17,18,19,20, 21,22,23,24,
     &			25,26,27,28, 29,30,31,32, 33,34,35,/
	DATA EL2D5	13,14,15,16, 33,34,35,36, 37,38,39,40,
     &			41,42,43,44, 29,30,31,32, 45,46,47,48,
     &			49,50,51,52, 53,54,55,56/
	DATA EL1D3/	 1, 2, 3, 4,  5, 6, 7, 8,  9,10,11,12,
     &			13,14,15,16, 17,18,19,20, 21,22,23,24,
     &			25,26,27,28, 29,30,31,32/
	DATA EL2D3	13,14,15,16, 33,34,35,36, 37,38,39,40,
     &			41,42,43,44, 29,30,31,32, 45,46,47,48,
     &			49,50,51,52, 53,54,55,56/
	DATA EL1D3/	 1, 2, 3, 4,  5, 6, 7, 8,  9,10,11,12,
     &			13,14,15,16, 17,18,19,20, 21,22,23,24,
     &			25,26,27,28, 29,30,31,32/
	DATA EL2D3	13,14,15,16, 33,34,35,36, 37,38,39,40,
     &			41,42,43,44, 29,30,31,32, 45,46,47,48,
     &			49,50,51,52, 53,54,55,56/
!------------------------------------------------------
	
	if(cElemTyp == "55") then
		if (Nel == 1) Then		! Quartic 
			do i = 1,50
				ELDat( i   ) =  i
			end do !i
		end do !i
!
		elseif (Nel == 2) Then	! Quintic 
			do i = 1,6
				ELDat( i   ) =  20+i
				ELDat( i+ 6) =  72+i
				ELDat( i+12) =  78+i
				ELDat( i+18) =  84+i
				ELDat( i+24) =  90+i
				ELDat( i+30) =  96+i
!
			ELDat( i+36) =  66+i
			ELDat( i+42) = 102+i
			ELDat( i+48) = 108+i
			ELDat( i+54) = 114+i
			ELDat( i+60) = 120+i
			ELDat( i+66) = 126+i
   			ELDat = EL2D5
	elseif(cElemTyp == "44") then
		if (Nel == 1) Then		! Quartic 
   			ELDat = EL1D4
		elseif (Nel == 2) Then	! Quintic 
   			ELDat = EL2D4
	elseif(cElemTyp == "33") then
		if (Nel == 1) Then		! Quartic 
   			ELDat = EL1D3
		elseif (Nel == 2) Then	! Quintic 
   			ELDat = EL2D3
	endif
!-----------   	
	return
	end
