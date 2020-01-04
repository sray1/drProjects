	Subroutine PutGetRefPropsatGaussPt(iRefPro1,Nel,iTyp)
	Implicit Real(kind=8) (a-h,o-z)
!	====================
	include 'CurParams.h'
	include 'files.h'
!-------------------------------------------- 
	SELECT CASE (iTyp)
		CASE (1)					! write						
			write(iRefPro1,REC=Nel) 
     &			(C01(i),i=1,3),(C02(i),i=1,3),RutAhat
!	==================================================================
	iPrt = 0
	call DumpStringVar("************WRITE**************",iPrt,iOut)
	call DumpIntegerVar(iRefPro1,"iRefPro1",iPrt,iOut)
	call DumpIntegerVar(Nel,"jCInt",iPrt,iOut)
	call DumpStringVar("just in.PutGetRefPropsatGaussPt",iPrt,iOut)
!	call DumpRealArray(xNor,3,"xNor",iPrt,iOut)
	call DumpRealArray(C01,3,"C01",iPrt,iOut)
	call DumpRealArray(C02,3,"C02",iPrt,iOut)
	call DumpRealVar(RutAhat,"RutAhat",iPrt,iOut)
	call DumpStringVar("End:PutGetRefPropsatGaussPt",iPrt,iOut)
	iPrt = 0
!	==================================================================
		CASE (2)					! read						
			read (iRefPro1,REC=Nel)  
     &			(C01(i),i=1,3),(C02(i),i=1,3),RutAhat
!	==================================================================
	iPrt = 0
	call DumpStringVar("************READ**************",iPrt,iOut)
	call DumpIntegerVar(iRefPro1,"iRefPro1",iPrt,iOut)
	call DumpIntegerVar(Nel,"jCInt",iPrt,iOut)
	call DumpStringVar("just in.PutGetRefPropsatGaussPt",iPrt,iOut)
!	call DumpRealArray(xNor,3,"xNor",iPrt,iOut)
	call DumpRealArray(C01,3,"C01",iPrt,iOut)
	call DumpRealArray(C02,3,"C02",iPrt,iOut)
	call DumpRealVar(RutAhat,"RutAhat",iPrt,iOut)
	call DumpStringVar("End:PutGetRefPropsatGaussPt",iPrt,iOut)
	iPrt = 0
!	==================================================================
		CASE DEFAULT
			return
	END SELECT
!======================================================================= save:End
	return
	end
