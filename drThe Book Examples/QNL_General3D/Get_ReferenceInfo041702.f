	Subroutine Get_ReferenceInfo(Axes,Cur,Tor,Axes6,Axes12,Axep,
     &					nQc,nDim,RoCOld,CuCOld,nCInt,
     &                    Ri,jInt,R0,C0,CK,T,B,
     &                    nDof,nDof2,nStif,Det,Iout,Nel,Nint)
!	----------------------------------------------------------------------------- 
!	Inputs
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
	Real(kind=8)	AxeP     ,Axes6     ,Axes12
	Dimension		AxeP(3,3),Axes6(6,6),Axes12(12,12)
	Real(kind=8)	B          ,T     
	Dimension		B(12,nStif),T(6,nStif)
	Real(kind=8)	R0      ,C0      ,CK
	Dimension		R0(nDim),C0(nDim),CK(nDim)
	character*3		readstat
!==========================================================
	LOGICAL bReset
	common/LoadStepIter/iStep,iNut,bReset
      common/Scratch/	  iRotCur1,iRotCur2,iDetRef
!==========================================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	------------------------------------------------------------ 
	AJI		= one/det
!	---------------------
	kr = (jInt-1)*nDim+1
	if((iStep == 1).AND.(iNut == 2).AND.(Nel == 2)) Then
			abc = 0
	endif
!
	call Extract_Vector(RoCOld,nCInt,R0,nDim,kr,Iout)!rotationControlOld
	call Extract_Vector(CuCOld,nCInt,C0,nDIm,kr,Iout)!CurvatureControlOld
!	------------------- initialize with geometric curvature
!	if(iStep == 0) Then
!		CK = C0
!	endif
!	--------------------------------------------------------- Get  T(nDof,nDof*nQc),B(nDof2,nDof*nQc)
	call Form_B_and_Tmatrices(Axes6,Axes12,Axep,Axes,
     &						Cur,Tor,Ri,T,nDof,B,nDof2,
     &							nStif,AJI,nQc,Iout)
!		-------------------------------------------------------- Debug 
		iPrt = 0
		if((iStep == 2).AND.(iNut == 1)) Then
			iPrt = 0
			call DumpStringVar("Beg:Get_ReferenceInfo",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
			call DumpIntegerVar(lr,"GaussIndex",iPrt,iOut)
			call DumpRealVar(Ri,"GaussPt.",iPrt,iOut)
			call DumpIntegerVar(nCInt,"nCInt",iPrt,iOut)
			call DumpRealArray(RoCOld,nCInt,"RoCOld",iPrt,iOut)
			call DumpRealArray(CuCOld,nCInt,"CuCOld",iPrt,iOut)
			call DumpRealArray(C0,nDim,"C0",iPrt,iOut)
!			call DumpRealArray(CK,nDim,"CK",iPrt,iOut)
			call DumpStringVar("End:Get_ReferenceInfo",iPrt,iOut)
		endif
!		-------------------------------------------------------- Debug : End
	return
!
 1000 format("QC(",I1,",",I1,"): "/
     &        3(I5,5X,6(f10.6,1X)/) )
	end
