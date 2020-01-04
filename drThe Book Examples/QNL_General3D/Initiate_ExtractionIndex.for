	Subroutine Initiate_ExtractionIndex(EL1,EL2,nStifEL,iOut)
	
	integer EL1(nStifEL),EL2(nStifEL)
!---------------------------
	integer EL15(30),EL25(30)
	integer EL16(36),EL26(36)
	DATA EL15/ 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,
     &          13,14,15,16,17,18,19,20,21,22,23,24,
     &		  25,26,27,28,29,30/
	DATA EL25/ 5,31,32,33,34,10,35,36,37,38,15,39,
     &          40,41,42,20,43,44,45,46,25,47,48,49,
     &		  50,30,51,52,53,54/
	DATA EL16/ 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,
     &          13,14,15,16,17,18,19,20,21,22,23,24,
     &		  25,26,27,28,29,30,31,32,33,34,35,36/
	DATA EL26/ 6,37,38,39,40,41,12,42,43,44,45,46,
     &          18,47,48,49,50,51,24,52,53,54,55,56,
     &		  30,57,58,59,60,61,36,62,63,64,65,66/
!------------------------------------
	if (nStifEL == 30) Then		! Quartic 
		do 10 i = 1,nStifEL
     		EL1(i) = EL15(i)
   10		EL2(i) = EL25(i)
	elseif (nStifEL == 36) Then	! Quintic 
		do 20 i = 1,nStifEL
     		EL1(i) = EL16(i)
   20		EL2(i) = EL26(i)
	endif
!-----------   	
	return
	end
