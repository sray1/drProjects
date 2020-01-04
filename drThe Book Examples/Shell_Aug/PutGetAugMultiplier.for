	Subroutine PutGetAugMultiplier(Penalt,AugMul,OldCon,
     &			Nint1,Nint2,iAugTape,Nel,iTyp,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Penalt                                                     
	Dimension		Penalt(Nint1,Nint2)
	Real(kind=8)	AugMul             ,OldCon                                           
	Dimension		AugMul(Nint1,Nint2),OldCon(Nint1,Nint2)
!-------------------------------------------- 
	SELECT CASE (iTyp)
		CASE (1)					! write						
			write(iAugTape,REC=Nel) 
     &			((Penalt(i,j),i=1,Nint1),j=1,Nint2),
     &			((AugMul(i,j),i=1,Nint1),j=1,Nint2),
     &			((OldCon(i,j),i=1,Nint1),j=1,Nint2)
		CASE (2)					! read						
			read(iAugTape,REC=Nel) 
     &			((Penalt(i,j),i=1,Nint1),j=1,Nint2),
     &			((AugMul(i,j),i=1,Nint1),j=1,Nint2),
     &			((OldCon(i,j),i=1,Nint1),j=1,Nint2)
		CASE DEFAULT
			return
	END SELECT
!	-------------------------------------------------------------- Debug	
	iPrt = 0
	if(iPrt == 1) Then
		call DumpStringVar("Beg:PutGetAugMultiplier",iPrt,iOut)
		call DumpIntegerVar(Nel,"Record Number",iPrt,iOut)
		call DumpIntegerVar(iTyp,"iTyp=1:Re/2:Wr",iPrt,iOut)
		write(Iout,1005) 
     &		Nint1,Nint2,(i,(Penalt(i,j),i=1,Nint1),j=1,Nint2)
		write(Iout,1000) 
     &		Nint1,Nint2,(i,(AugMul(i,j),i=1,Nint1),j=1,Nint2)
		write(Iout,1010) 
     &		Nint1,Nint2,(i,(OldCon(i,j),i=1,Nint1),j=1,Nint2)
		call DumpStringVar("End:PutGetAugMultiplier",iPrt,iOut)
	endif
	iPrt = 0
	return
!	
 1000 format("AugMul(",I2,",",I2,")"/(I2/,6(12(f7.4,1X)/)))
 1005 format("Penalt(",I2,",",I2,")"/(I2/,6(12(f7.4,1X)/)))
 1010 format("OldCon(",I2,",",I2,")"/(I2/,6(12(f7.4,1X)/)))
!======================================================================= save:End
	return
	end
