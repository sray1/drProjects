	Subroutine PutGetIndxEL(iIndxEL,Indx,nIndx,Nel,iTyp,iOut)
	Implicit Real(kind=8) (a-h,o-z)

	integer	Indx,iPrt
	Dimension		Indx(nIndx)
!-------------------------------------------- 
	SELECT CASE (iTyp)
		CASE (1)					! write						
			write(iIndxEL,REC=Nel) (Indx(i), i=1,nIndx)
	!
			iPrt = 0
			if(iPrt == 1) then
				write(iOut,1030) (Indx(i), i=1,nIndx)
			endif
	!
		CASE (2)					! read						
			read(iIndxEL,REC=Nel) (Indx(i), i=1,nIndx)
	!
			iPrt = 0
			if(iPrt == 1) then
				write(iOut,1040) (Indx(i), i=1,nIndx)
			endif
	!
		CASE DEFAULT
			return
	END SELECT
!
!======================================================================= save:End
	return
!	=======
 1030 Format(/12x,"Index written as 1D array:Indx(i), i=1,nIndx"/(6I10))
 1040 Format(/12x,"Index read as 1D array:Indx(i), i=1,nIndx"/(6I10))

	end
