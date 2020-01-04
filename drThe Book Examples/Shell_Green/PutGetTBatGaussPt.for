	Subroutine PutGetTBatGaussPt(T,nT,B,nB,nD,iRefPro2,Nel,iTyp)
	Implicit Real(kind=8) (a-h,o-z)
!
	include 'files.h'
!
	Real(kind=8)	T       ,B
	Dimension		T(nT,nD),B(nB,nD)				! T(6,6n),B(18,6n)
!-------------------------------------------- 
	SELECT CASE (iTyp)
		CASE (1)					! write						
			write(iRefPro2,REC=Nel) 
     &			((T(i,j),i=1,nT),j=1,nD),((B(i,j),i=1,nB),j=1,nD)
		CASE (2)					! read						
			read (iRefPro2,REC=Nel)  
     &			((T(i,j),i=1,nT),j=1,nD),((B(i,j),i=1,nB),j=1,nD)
		CASE DEFAULT
			return
	END SELECT
!	-------------------------------------------------------------- Debug	
	iPrt = 0
	if(iPrt == 1) Then
		call DumpStringVar("Beg:PutGetTBatGaussPt",iPrt,iOut)
		call DumpIntegerVar(Nel,"Record Number",iPrt,iOut)
		call DumpIntegerVar(iTyp,"iTyp=1:Re/2:Wr",iPrt,iOut)
		write(Iout,1010) nT,nD,(i,(T(i,j),j = 1,nD),i=1,nT)
		write(Iout,1020) nB,nD,(i,(B(i,j),j = 1,nD),i=1,nB)
		call DumpStringVar("End:PutGetTBatGaussPt",iPrt,iOut)
	endif
	iPrt = 0
	return
!
 1010 format("T(",I2,",",I2,")"/(I2/,6(12(f7.4,1X)/)))
 1020 format("B(",I2,",",I2,")"/(I2/,6(12(f7.4,1X)/)))
!======================================================================= save:End
	return
	end
