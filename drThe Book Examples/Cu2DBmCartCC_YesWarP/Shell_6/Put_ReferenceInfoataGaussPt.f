	Subroutine Put_ReferenceInfoataGaussPt
     &							(Qc,Ri,Rj,iInt,jInt,T,B,Nel,nRec)
!     &							(Qc,nDim,nQc1,nQc2,Ri,Rj,iInt,jInt,
!     &								T,B,nDof,nDof2,nStif,Nel,nRec)
!	----------------------------------------------------------------------------- 
!	Inputs
!		Qc(nDim,nQc1,nQc2)	= Geometry Controls
!		nDim				= 3
!		nQc1					= order of Bezier
!		nQc2					= order of Bezier
!		nCInt					= no. of Gauss Integration points * nDim (=3)
!								= nDim*nInt
!		Ri					= Current Gauss location Pt ith.
!		Rj					= Current Gauss location Pt jth.
!		nInt				= Total Gauss pts = iInt*jInt
!		iInt				= Current Gauss Index along 1
!		jInt				= Current Gauss Index along 2
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
!	======================
	include 'SizeVar.h'
	include 'Scratch.h'
	include 'CurParams.h'
	include 'LogParams.h'
	include 'files.h'
!	======================
!	common/LoadStepIter/iStep,iNut,bReset
!      common/files/iFileStiff,Ioutt,IoutDef,IoutEnd,iRotCur
!
!	Input Variables & Arrays
!
	Real(kind=8)	Qc                    
	Dimension		Qc(nDim,nQc1,nQc2)
!
!	Working Variables & Arrays
!
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	B          ,T     
	Dimension		B(nDof2,nStifEL),T(nDof,nStifEL)
	character*3		readstat
	LOGICAL bReset
!	==========================================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/,onm/-1.0D0/ 
!	-------------------------------------------------------------------- Curvatures/Det etc 
	inquire(iRefPro1,NEXTREC = nRecShould)
	if(nRec == nRecShould) then
		if(bOpt1) then
			call Opt1_Calc_ReferenceProps(Qc,ri,rj,nRec)
		else
			call Calc_ReferenceProps(Qc,ri,rj,nRec)
		endif
	endif
!	-------------------------------------------------------------------- T & B matrices 
	inquire(iRefPro2,NEXTREC = nRecShould)
	if(nRec == nRecShould) then
		call Form_B_and_Tmatrices(T,B,ri,rj,nRec)
!		call Form_B_and_Tmatrices(T,nDof,B,nDof2,nStif,
!     &						nDim,nQd1,nQd2,ri,rj,nRec)
	endif

!		-------------------------------------------------------- Debug 
		iPrt = 0
		call DumpStringVar
     &			("Beg:Put_ReferenceInfoataGaussPt",iPrt,iOut)
		call DumpIntegerVar(iInt,"GaussIndex dir_i",iPrt,iOut)
		call DumpIntegerVar(jInt,"GaussIndex dir_j",iPrt,iOut)
		call DumpRealVar(Ri,"GaussPt. dir_i",iPrt,iOut)
		call DumpRealVar(Rj,"GaussPt. dir_j",iPrt,iOut)
		call DumpIntegerVar(nCInt,"nCInt",iPrt,iOut)
!			call DumpRealArray(C0,nC,"C0",iPrt,iOut)
		call DumpStringVar
     &				("End:Put_ReferenceInfoataGaussPt",iPrt,iOut)
!		-------------------------------------------------------- Debug : End
!---------------------------------------------------------- Write:
!	iPrt = 0
!	if (iPrt == 1) Then
!		write(Iout,1000) nDim,nQc1,nQc2,
!     &		(i,j,(Qc(k,i,j),j=1,nQc),i=1,nDim)
!	endif
!----------------------------------------------------------
	return
!
 1000 format("QC(",I1,",",I1,"): "/
     &        3(I5,5X,6(f10.6,1X)/) )
	end
