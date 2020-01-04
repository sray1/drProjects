	Subroutine Initial_CurRot(Qc,nDim,nQc,RoCOld,CuCOld,DetRef,
     &										nCInt,Iout,Nel,Nint)
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
	Real(kind=8)	DetRef      ,RoCOld       ,CuCOld
	Dimension		DetRef(Nint),RoCOld(nCInt),CuCOld(nCInt)
!
!	Working Variables & Arrays
!
!
	Real(kind=8)	Axes        
	Dimension		Axes(3,3)
!	
	Real(kind=8)	C0      ,CK
	Dimension		C0(nDim),CK(nDim)
!==========================================================
	LOGICAL bReset
	common/LoadStepIter/iStep,iNut,bReset
      common/Scratch/	  iRotCur1,iRotCur2,iDetRef
!==========================================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!===================================================================== Geometry
	iPrt = 1
	if (iPrt == 1) Then
		write(Iout,1000) nDim,nQc,Nel,(i,(Qc(i,j),j=1,nQc),i=1,nDim)
	endif
!===================================================================== Rotation
	RoCOld = zero
!===================================================================== Curvature
!	Loop over Gauss Locations
	do 60 jInt = 1,Nint
	Ri = GaussPtVal(jInt,Nint,1) 
!	------------------------------------------------------------ 
	call QQ_TMB_CuLn(Qc,nQc,nOrderR,Ri,Det,Cur,Tor,
     &						Axes,dxbardr,Nel,Iout,iPrt)
!
	C0(1)	= Tor
	C0(2)	= zero
	C0(3)	= Cur
!
!	============================================================= save
	DetRef(jInt) = Det
	do 10 ii = 1,nDim
	ij = ii + (jInt -1)*nDim
	CuCold(ij) = C0(ii) 
   10	continue
!		-------------------------------------------------------- Debug 
		iPrt = 0
		if((iStep == 1).AND.(iNut == 2)) Then
			iPrt = 0
			call DumpStringVar("Beg:Initial_CurRot",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
			call DumpIntegerVar(lr,"GaussIndex",iPrt,iOut)
			call DumpRealVar(Ri,"GaussPt.",iPrt,iOut)
			call DumpRealArray(DetRef,Nint,"DetRef",iPrt,iOut)
			call DumpIntegerVar(nCInt,"nCInt",iPrt,iOut)
			call DumpRealArray(RoCOld,nCInt,"RoCOld",iPrt,iOut)
			call DumpRealArray(CuCOld,nCInt,"CuCOld",iPrt,iOut)
			call DumpRealArray(C0,nC,"C0",iPrt,iOut)
			call DumpRealArray(CK,nC,"CK",iPrt,iOut)
			call DumpStringVar("End:Initial_CurRot",iPrt,iOut)
		endif
!		-------------------------------------------------------- Debug : End
   60 continue
!=============
	return
!
 1000 format("QC(",I1,",",I1,") for Element# = ",I3/
     &        3(I5,5X,6(f10.6,1X)/) )
	end
