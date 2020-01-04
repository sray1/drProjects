	Subroutine SaveConvergedRotCur(Qc,
     &						RoCOld,CuCOld,DetRef,Qd,Nel,nQc,
     &						nQd,nC,nDof,nDof2,Nint,nCInt,Iout)
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
	Real(kind=8)	Axex     ,AxeP     ,Axes6     ,Axes12
	Dimension		Axes(3,3),AxeP(3,3),Axes6(6,6),Axes12(12,12)
	Real(kind=8)	Qc       
	Dimension		Qc(3,nQc)
	Real(kind=8)	Qd     ,DetRef              
	Dimension		Qd(nQd),DetRef(Nint)
	Real(kind=8)	RoCOld       ,CuCOld            
	Dimension		RoCOld(nCInt),CuCOld(nCInt)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	B           ,T     
	Dimension		B(nDof2,nQd),T(nDof,nQd)
	Real(kind=8)	HD       ,R0    ,C0                           
	Dimension		HD(nDof2),R0(nC),C0(nC)
	Real(kind=8)	WMat       ,AMatInc                   
	Dimension		WMat(nC,nC),AMatInc(nC,nC)
	Real(kind=8)	Ro    ,Rp    ,RK    ,CK                             
	Dimension		Ro(nC),Rp(nC),RK(nC),CK(nC)
!============================================
	common/LoadStepIter/iStep,iNut,bReset
      common/Scratch/	  iRotCur1,iRotCur2,iDetRef
	common/ThetaConstants/c1,c2,c1b,c2b
!============================================
	DATA zero/0.D0/,one/1.0D0/ 
!	============================================
	nRec = Nel
	call PutGetDetRef(iDetRef,DetRef,Nint,nRec,2)				!Read
!============================================ Loop over Gauss Locations
	do 60 jInt = 1,Nint
	kr	= (jInt-1)*nC + 1
	Ri	= GaussPtVal(jInt,Nint,1) 
	Det	= DetRef(jInt)
	AJI	= one/Det
!------------------------------------------------------------- Get Cur,Tor & Axes
!	call QQ_TMB_CuLn(Qc,nQc,nOrderR,Ri,Det,Cur,Tor,
!     &						Axes,dxbardr,Nel,Iout,iPrt)
!------------------------------------------------------------- Get  T(nDof,nDof*nQc),B(nDof2,nDof*nQc)
	call Form_B_and_Tmatrices(Br,H1D,T,nDof,B,nDof2,nQd,AJI,
     &						nQc,Iout)
!		-------------------------------------------------------- Debug 
		if(iStep == 1) Then
			iPrt = 0
			call DumpStringVar("Beg:SaveConvergedRotCur",iPrt,iOut)
			call DumpIntegerVar(Nel,"Element#",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
			call DumpStringVar("Beg:SaveConvergedRotCur",iPrt,iOut)
			call DumpRealMatrix(B,12,nQd,"B",iPrt,iOut)
			call DumpRealArray(Qd,nQd,"Qd",iPrt,iOut)
			iPrt = 0
			call DumpStringVar("End:SaveConvergedRotCur",iPrt,iOut)
		endif
!		-------------------------------------------------------- Debug : End
	HD = MATMUL(B,Qd)
!	------------------------------------------------------------------- H(dHat):Incremental
	call Extract_Vector(HD,nDof2,Ro,nC,4,Iout)		!rotation
	call Extract_Vector(HD,nDof2,Rp,nC,10,Iout)		!rotationPrimed
	call Extract_Vector(RoCOld,nCInt,R0,nC,kr,Iout)	!CurvatureControlOld
	call Extract_Vector(CuCOld,nCInt,C0,nC,kr,Iout)	!CurvatureControlOld
!	============================
	if((iStep == 2)) Then
		abc = 1
	endif
!	------------------------------------------------------------------- Theta Constants
	call FormThetaConstants(Ro,nC,c1,c2,c1b,c2b,Iout)
!	call FormRotationMatrix(Ro,AMatInc,nC,Iout)
	call Form_WMatrix(Ro,WMat,nC,Iout)
!	=============================================================
	RK = R0 + Ro
!	CK = MATMUL(TRANSPOSE(AMatInc),C0) + MATMUL(WMat,Rp)
!	CK = MATMUL(AMatInc,C0) + MATMUL(WMat,Rp)
	CK = C0 + MATMUL(WMat,Rp)
!	============================================================= save
	if((iStep == 2)) Then
		abc = 1
	endif
	do 10 ii = 1,nC
	ij = ii + (jInt -1)*nC
	RoCOld(ij) = RK(ii) 
	CuCold(ij) = CK(ii) 
   10	continue
!	===================
	if(iStep == 1) Then
		abc = 1
	endif
!	======================================================================
		if(iStep == 1) Then
			iPrt = 0
			call DumpStringVar("Beg:SaveConvergedRotCur",iPrt,iOut)
			call DumpIntegerVar(Nel,"Element#",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
			call DumpIntegerVar(lr,"GaussIndex",iPrt,iOut)
			call DumpIntegerVar(nCInt,"nCInt",iPrt,iOut)
			call DumpRealArray(R0,nC,"R0",iPrt,iOut)
			call DumpRealArray(C0,nC,"C0",iPrt,iOut)
			call DumpRealArray(Ro,3,"Ro",iPrt,iOut)
			call DumpRealArray(Rp,3,"Rp",iPrt,iOut)
			call DumpRealVar(c1,"c1",iPrt,iOut)
			call DumpRealVar(c2,"c2",iPrt,iOut)
			call DumpRealVar(c1b,"c1b",iPrt,iOut)
			call DumpRealVar(c2b,"c2b",iPrt,iOut)
			call DumpRealMatrix(AMatInc,3,3,"AMatInc",iPrt,iOut)
			call DumpRealMatrix(WMAT,3,3,"WMAT",iPrt,iOut)
			call DumpRealArray(RK,nC,"RK",iPrt,iOut)
			call DumpRealArray(CK,nC,"CK",iPrt,iOut)
		iPrt = 0
			call DumpRealMatrix(T,nDof,nQd,"T",iPrt,iOut)
			call DumpRealMatrix(B,nDof2,nQd,"B",iPrt,iOut)
			iPrt = 0
			call DumpStringVar("End:SaveConvergedRotCur",iPrt,iOut)
		endif
!		-------------------------------------------------------- Debug : End
   60 continue
!	===================================================================== Debug
		if(iStep == 1) Then
			iPrt = 0
			call DumpStringVar("Beg:SaveConvergedRotCur",iPrt,iOut)
			call DumpIntegerVar(Nel,"Element#",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
			call DumpIntegerVar(nCInt,"nCInt",iPrt,iOut)
			call DumpRealArray(RoCOld,nCInt,"RoCOld",iPrt,iOut)
			call DumpRealArray(CuCOld,nCInt,"CuCOld",iPrt,iOut)
			call DumpStringVar("End:SaveConvergedRotCur",iPrt,iOut)
		endif
!		-------------------------------------------------------- Debug : End
!	===================================================================== Save
!	nRec = Nel
!	call PutGetRotCur(iRotCur2,RoCOld,CuCold,nCInt,nRec,1)	!Write
!===================================================================== Save End
	return
!
	end   		
