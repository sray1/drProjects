	Subroutine PutGetRotCur(iRotCur,RoCOld,CuCold,nCInt,Nel,iTyp)
	Implicit Real(kind=8) (a-h,o-z)

	Real(kind=8)	RoCOld       ,CuCOld
	Dimension		RoCOld(nCInt),CuCOld(nCInt)
!-------------------------------------------- 
	SELECT CASE (iTyp)
		CASE (1)					! write						
			write(iRotCur,REC=Nel) (RoCOld(i),CuCold(i), i=1,nCInt)
		CASE (2)					! read						
			read(iRotCur,REC=Nel) (RoCOld(i),CuCold(i), i=1,nCInt)
		CASE DEFAULT
			return
	END SELECT
!======================================================================= save:End
	return
	end
