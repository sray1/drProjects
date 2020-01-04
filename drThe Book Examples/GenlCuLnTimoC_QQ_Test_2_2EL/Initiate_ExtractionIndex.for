	Subroutine Initiate_ExtractionIndex(EL1,EL2,nStifEL,iOut)
	
	integer EL1(nStifEL),EL2(nStifEL)
!---------------------------
	integer EL15(15),EL25(15)
	integer EL16(18),EL26(18)
	DATA EL15/ 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,
     &          13,14,15/
	DATA EL25/ 5,16,17,18,19,10,20,21,22,23,15,24,
     &          25,26,27/
	DATA EL16/ 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,
     &         13,14,15,16,17,18/
	DATA EL26/ 6,19,20,21,22,23,12,24,25,26,27,28,
     &          18,29,30,31,32,33/
!------------------------------------
	if (nStifEL == 15) Then	! Quartic 
		do 10 i = 1,nStifEL
     		EL1(i) = EL15(i)
   10		EL2(i) = EL25(i)
	elseif (nStifEL == 18) Then	! Quintic 
		do 20 i = 1,nStifEL
     		EL1(i) = EL16(i)
   20		EL2(i) = EL26(i)
	endif
!-----------   	
	return
	end
