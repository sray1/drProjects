	Subroutine Get_ReferenceInfoataGaussPt
     &					(T,B,nDof,nDof2,nStif,Nel,nRec)
!	----------------------------------------------------------------------------- 
!	Inputs
!		nDof				= 12
!		nDof2				= 18
!		nStif				= 6*nQd1*nQd2
! 	
!	Outputs 
!		C0(nDim)		= Ref Curvature:for the current Gauss Pt.
!		T(nDof,nStif)	= Dof Transformmation Control matrix
!		B(nDof2,nStif)	= Dof2 Transformmation Control matrix
!		RutAhat			= sq. root of Determinant of shell Jacobian
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!	==========================
!	include 'files.h'
	include 'files.h'
	include 'scratch.h'
	include 'CurParams.h'
	include 'LoadStepIter.h'
!	==========================
!	common/LoadStepIter/iStep,iNut,bReset
!      common/files/iFileStiff,Ioutt,IoutDef,IoutEnd,iRotCur
!
!	Input Variables & Arrays
!
!
!	Working Variables & Arrays
!
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	B          ,T     
	Dimension		B(nDof2,nStif),T(nDof,nStif)
	character*3		readstat
!	==========================================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/,onm/-1.0D0/ 
!	-------------------------------------------------------------------- Curvatures/Det etc 
	inquire(iRefPro1,NEXTREC = nRecShould)
	if(nRec == nRecShould) then
		call PutGetRefPropsatGaussPt(iRefPro1,nRec,2)
	endif
	CK1 = C01
	CK2 = C02
!	-------------------------------------------------------------------- T & B matrices 
	inquire(iRefPro2,NEXTREC = nRecShould)
	if(nRec == nRecShould) then
		call PutGetTBatGaussPt(T,nDof,B,nDof2,nStif,iRefPro2,nRec,2)
	endif
!		-------------------------------------------------------- Debug 
	iPrt = 0
	if((iStep == 1).AND.(iNut == 2)) Then
		iPrt = 0
		call DumpStringVar("Beg:Put_ReferenceInfo",iPrt,iOut)
		call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
		call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
		call DumpRealArray(C0,nC,"C0",iPrt,iOut)
		call DumpRealArray(CK,nC,"CK",iPrt,iOut)
		call DumpStringVar("End:Get_ReferenceInfo",iPrt,iOut)
	endif
!	-------------------------------------------------------- Debug : End
	return
	end
