	Subroutine Put_ReferenceInfo(Qc,RoCOld,CuCOld,nCInt,
     &                    Ri,Rj,jInt,R0,C0,CK,nC,T,B,
     &                    nDof,nDof2,nStif,Det,Iout,Nel,Nint)
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
!		iInt				= Current Gauss Index along 1
!		jInt				= Current Gauss Index along 2
!		nDof				= 12
!		nDof2				= 18
!		nStif				= 6*nQd1*nQd2
! 	
!	Outputs 
!		R0(nDim)		= rot Controls:Old for the current Gauss Pt.
!		C0(nDim)		= Ref Curvature:for the current Gauss Pt.
!		T(nDof,nStif)	= Dof Transformmation Control matrix
!		B(nDof,nStif)	= Dof2 Transformmation Control matrix
!		Det				= Determinant (Jacobian)
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!	====================
!	include 'files.h'
	include 'CurParams.h'
!	====================
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
	Dimension		B(12,nStif),T(6,nStif)
	Real(kind=8)	R0      ,C0      ,CK
	Dimension		R0(nDim),C0(nDim),CK(nDim)
	character*3		readstat
!==========================================================
	common/LoadStepIter/iStep,iNut,bReset
      common/files/iFileStiff,Ioutt,IoutDef,IoutEnd,iRotCur
!	===========================
	common/Examples/cEx(10),nEx
	character (30)	cEx
!	include 'LoadStepIter.h'
!	include 'files.h'
!	include 'Examples.h'
	include 'LogParams.h'
!	===========================
!==========================================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/,onm/-1.0D0/ 
!	-------------------------------------------------------------------- Curvatures/Det etc 
	inquire(iRefPro1,NEXTREC = nRec)
	call Calc_ReferenceProps(Qc,nDim,nQc1,nQc2,ri,rj,nRec)
!	-------------------------------------------------------------------- T & B matrices 
!		 T(nDof,nDof*nQc1*nQc2),B(nDof2,nDof*nQc1*nQc2)
	call Form_B_and_Tmatrices(Br,H1D,T,nDof,B,nDof2,nStif,AJI,
     &						nQc,Iout)
!		-------------------------------------------------------- Debug 
		iPrt = 0
		if((iStep == 1).AND.(iNut == 2)) Then
			iPrt = 0
			call DumpStringVar("Beg:Put_ReferenceInfo",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
			call DumpIntegerVar(lr,"GaussIndex",iPrt,iOut)
			call DumpRealVar(Ri,"GaussPt.",iPrt,iOut)
			call DumpIntegerVar(nCInt,"nCInt",iPrt,iOut)
			call DumpRealArray(RoCOld,nCInt,"RoCOld",iPrt,iOut)
			call DumpRealArray(CuCOld,nCInt,"CuCOld",iPrt,iOut)
			call DumpRealArray(C0,nC,"C0",iPrt,iOut)
			call DumpRealArray(CK,nC,"CK",iPrt,iOut)
			call DumpStringVar("End:Get_ReferenceInfo",iPrt,iOut)
		endif
!		-------------------------------------------------------- Debug : End
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
!		write(Iout,1000) nDim,nQc,(i,(Qc(i,j),j=1,nQc),i=1,nDim)
	endif
!----------------------------------------------------------
	return
!
 1000 format("QC(",I1,",",I1,"): "/
     &        3(I5,5X,6(f10.6,1X)/) )
	end
