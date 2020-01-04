	Subroutine Get_ReferenceInfo(Qc,nDim,nQc,RoCOld,CuCOld,nCInt,
     &                    Ri,jInt,R0,C0,CK,nC,T,B,
     &                    nDof,nDof2,nStif,Det,Iout,Nel,Nint)
!	----------------------------------------------------------------------------- 
!	Inputs
!		Qc(nDim,nQc)	= Geometry Controls
!		nDim			= 3
!		nQc				= order of Bezier
!		RoCOld(nCInt)	= rot Controls:Old for all Gauss point
!		CuCOld(nCInt)	= Curvature:Old
!		nCInt				= no. of Gauss Integration points * nDim (=3)
!								= nDim*nInt
!		Ri				= Current Gauss location Pt.
!		jInt			= Current Gauss Index
!		nDof			= 6
!		nDof2			= 12
!		nStif			= 6*nQc
! 	
!	Outputs 
!		R0(nDim)		= rot Controls:Old for the current Gauss Pt.
!		C0(nDim)		= Ref Curvature:for the current Gauss Pt.
!		T(nDof,nStif)	= Dof Transformmation Control matrix
!		B(nDof,nStif)	= Dof2 Transformmation Control matrix
!		Det				= Determinant (Jacobian)
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
	Real(kind=8)	Qc                    
	Dimension		Qc(nDim,nQc)
	Real(kind=8)	RoCOld       ,CuCOld
	Dimension		RoCOld(nCInt),CuCOld(nCInt)
!
!	Working Variables & Arrays
!
	Real(kind=8)	Br     ,H1D     ,Axes        
	Dimension		Br(nQc),H1D(nQc),Axes(3,3)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	B          ,T     
	Dimension		B(12,nStif),T(6,nStif)
	Real(kind=8)	R0      ,C0      ,CK
	Dimension		R0(nDim),C0(nDim),CK(nDim)
	character*3		readstat
!==========================================================
	LOGICAL bReset
	common/LoadStepIter/iStep,iNut,bReset
      common/files/iFileStiff,Ioutt,IoutDef,IoutEnd,iRotCur
!==========================================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	------------------------------------------------------------ 
	call TMB_CuLn(Qc,nQc,nOrderR,Ri,Br,H1D,Det,Cur,Tor,
     &					Axes,dxbardr,Nel,Iout,iPrt)
!
	C0(1)	= Tor
	C0(2)	= zero
	C0(3)	= Cur
!
	AJI		= one/det
!	---------------------
	kr = (jInt-1)*nDim+1
	if((iStep == 1).AND.(iNut == 2).AND.(Nel == 2)) Then
			abc = 0
	endif
!==========================================================================
!	inquire(iRotCur,NEXTREC = nRec)
!	if(nRec.GT.1) then
!		nRec = (Nel-1)*Nint + jInt
!		call PutGetRotCur(iRotCur,RoCOld,CuCold,nCInt,nRec,2)
!	endif			
!==========================================================================
!	call Extract_Vector(RoCOld,nCInt,R0,nC,kr,Iout)!rotationControlOld
!	call Extract_Vector(CuCOld,nCInt,CK,nDIm,kr,Iout)!CurvatureControlOld
!	------------------- initialize with geometric curvature
!	if(iNut == 0) Then
		CK = C0
!	endif
!------------------------------------------------------------- Get  T(nDof,nDof*nQc),B(nDof2,nDof*nQc)
	call Form_B_and_Tmatrices(Br,H1D,T,nDof,B,nDof2,nStif,AJI,
     &						nQc,Iout)
!		-------------------------------------------------------- Debug 
		iPrt = 0
		if((iStep == 1).AND.(iNut == 2)) Then
			iPrt = 0
			call DumpStringVar("Beg:Get_ReferenceInfo",iPrt,iOut)
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
		write(Iout,1000) nDim,nQc,(i,(Qc(i,j),j=1,nQc),i=1,nDim)
	endif
!----------------------------------------------------------
	return
!
 1000 format("QC(",I1,",",I1,"): "/
     &        3(I5,5X,6(f10.6,1X)/) )
	end
