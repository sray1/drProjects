	Subroutine PutGetRefPropsatGaussPt(iRefPro1,Nel,iTyp)
	Implicit Real(kind=8) (a-h,o-z)
!	====================
	include 'CurParams.h'
	include 'files.h'
!	====================
	iPrt = 0
	call DumpStringVar("Beg:PutGetRefPropsatGaussPt",iPrt,iOut)
	call DumpStringVar("just in.PutGetRefPropsatGaussPt",iPrt,iOut)
	call DumpRealArray(xNor,3,"xNor",iPrt,iOut)
	call DumpRealArray(C01,3,"C01",iPrt,iOut)
	call DumpRealArray(C02,3,"C02",iPrt,iOut)
	call DumpRealVar(RutAhat,"RutAhat",iPrt,iOut)
	call DumpStringVar("End:PutGetRefPropsatGaussPt",iPrt,iOut)
	iPrt = 0
!-------------------------------------------- 
	SELECT CASE (iTyp)
		CASE (1)					! write						
			write(iRefPro1,REC=Nel) 
     &			(C01(i),i=1,3),(C02(i),i=1,3),RutAhat,
     &			((Ao12N(i,j),i=1,3),j=1,3)
		CASE (2)					! read						
			read (iRefPro1,REC=Nel)  
     &			(C01(i),i=1,3),(C02(i),i=1,3),RutAhat,
     &			((Ao12N(i,j),i=1,3),j=1,3)
	Ao1(1) = Ao12N(1,1) 
	Ao1(2) = Ao12N(2,1) 
	Ao1(3) = Ao12N(3,1)
!	 
	Ao2(1) = Ao12N(1,2) 
	Ao2(2) = Ao12N(2,2) 
	Ao2(3) = Ao12N(3,2)
!	 
	xNor(1) = Ao12N(1,3) 
	xNor(2) = Ao12N(2,3) 
	xNor(3) = Ao12N(3,3)
		CASE DEFAULT
			return
	END SELECT
!======================================================================= save:End
	return
	end
