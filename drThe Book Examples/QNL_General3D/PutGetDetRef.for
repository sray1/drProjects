	Subroutine PutGetDetRef(iFile,DetRef,Nint,Nel,iTyp)
	Implicit Real(kind=8) (a-h,o-z)

	Real(kind=8)	DetRef
	Dimension		DetRef(Nint)
!-------------------------------------------- 
	SELECT CASE (iTyp)
		CASE (1)					! write						
			write(iFile,REC=Nel) (DetRef(i), i=1,Nint)
		CASE (2)					! read						
			read(iFile,REC=Nel)  (DetRef(i), i=1,Nint)
		CASE DEFAULT
			return
	END SELECT
!======================================================================= save:End
	return
	end
