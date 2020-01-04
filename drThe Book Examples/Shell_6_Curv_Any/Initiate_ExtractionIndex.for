	Subroutine Initiate_ExtractionIndex(EL1,EL2,nStifEL,iOut)
	
	integer EL1(nStifEL),EL2(nStifEL)
!---------------------------
	integer EL15(60),EL25(30)
	integer EL16(72),EL26(72)
!	integer EL16(144),EL26(72)
	DATA EL15/ 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,
     &          13,14,15,16,17,18,19,20,21,22,23,24,
     &		  25,26,27,28,29,30,31,32,33,34,35,36,
     &		  27,38,39,40,41,42,43,44,45,46,47,48,
     &		  49,50,51,52,53,54,55,56,57,58,59,60/
	DATA EL16/ 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,
     &          13,14,15,16,17,18,19,20,21,22,23,24,
     &		  25,26,27,28,29,30,31,32,33,34,35,36,
     &		  37,38,39,40,41,42,43,44,45,46,47,48,
     &		  49,50,51,52,53,54,55,56,57,58,59,60,
     &		  61,62,63,64,65,66,67,68,69,70,71,72/

!	                             ****************** WILL CHANGE LATER *********************
	DATA EL25/ 5,31,32,33,34,10,35,36,37,38,15,39,
     &          40,41,42,20,43,44,45,46,25,47,48,49,
     &		  50,30,51,52,53,54/
	DATA EL26/ 11,12,73,74,75,76,77,78,79,80,81,82,
     &           23,24,83,84,85,86,87,88,89,90,91,92 ,
     &		   35,36,93,94,95,96,97,98,99,100,101,102,
     &		   47,48,103,104,105,106,107,108,109,110,111,112,
     &		   59,60,113,114,115,116,117,118,119,120,121,122,
     &		   71,72,123,124,125,126,127,128,119,130,131,132/

!	****************** WILL CHANGE LATER ********************* END
!------------------------------------
	if (nStifEL == 60) Then		! Quartic 
		do 10 i = 1,nStifEL
     		EL1(i) = EL15(i)
!   		EL2(i) = EL25(i)	************************** TOCHANGE  EL25 first, then**************
   10     continue
	elseif (nStifEL == 72) Then	! Linear/Quintic : 2 Elements
		do 20 i = 1,nStifEL
     		EL1(i) = EL16(i)
   		EL2(i) = EL26(i)	
   20     continue
	elseif (nStifEL == 144) Then	! Cubic/Quintic  One Element Shallow Shell/ tipTwist
		do 30 i = 1,nStifEL
     		EL1(i) = i
   30     continue
	elseif (nStifEL == 216) Then	! Quintic/Quintic  One Element  Shell
		do 40 i = 1,nStifEL
     		EL1(i) = i
   40     continue
	elseif (nStifEL == 384) Then	! Septic/Septic  One Element  Shell
		do 50 i = 1,nStifEL
     		EL1(i) = i
   50     continue
	elseif (nStifEL == 486) Then	! Octic/Octic  One Element  Shell
		do 60 i = 1,nStifEL
     		EL1(i) = i
   60     continue
	endif
!-----------   	
	return
	end
