	Subroutine Quad_QQ_STIF(Qc,
     &						RoCOld,CuCOld,DetRef,CKSav,nCInt,Qd,nQc,
     &						Nel,NelType,Nint,DMat,
     &						Stif,BFors,StifK,nStif,Iout,Trace)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!	Notes:	Nint should be atleast 2
!
!	Inputs
!		Qd(nStif)	= Latest displacement controls: state vector
!		Nel			= Element Number
!		NelType		= Element Type:
!						0 = Plane Stress
!						1 = Plane Strain
!						2 = Axi-symmtric	(NOT DONE YET)
!		Nint		= Number of Gauss Points
!		E			= Elasticity Modulus
!		PR			= Poisson's ratio
!		Thk			= Thickness
!		nStif		= Row or Col size of Stiffness matrix 
!						= nDof*nQc
!		Iout		= Error Output file#
!		 	
!	Outputs 
!		Stif(nStif,nStif)	= Desired Stiffness Matrix
!		bFors(nStif)		= Desired Body force Vector Integrals
!		StifK(nStif)		= Desired kLamda Stiffness last column Vector Integrals
!		Trace		= trace of the matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
	Real(kind=8)	SK     ,Axes     ,HC
	Dimension		SK(3,3),Axes(3,3),HC(12)
	Real(kind=8)	AxeP     ,Axes6     ,Axes12
	Dimension		AxeP(3,3),Axes6(6,6),Axes12(12,12)
	Real(kind=8)	Qc
	Dimension		Qc(3,nQc)
	Real(kind=8)	Qd                   
	Dimension		Qd(nStif)
	Real(kind=8)	DetRef       ,CKSav            
	Dimension		DetRef(Nint),CKSav(nCInt)
	Real(kind=8)	RoCOld       ,CuCOld            
	Dimension		RoCOld(nCInt),CuCOld(nCInt)
	Real(kind=8)	DMat   
	Dimension		DMat(6,6)
	integer			Nel,NelType,Iout,nStif
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	BFors       ,StifK       ,Stif			   ,Trace
	Dimension		BFors(nStif),StifK(nStif),Stif(nStif,nStif)
	Real(kind=8)	EDG       ,B          ,DB    ,T     
	Dimension		EDG(12,12),B(12,nStif),DB(12),T(6,nStif)
	Real(kind=8)	Add       ,HD    ,RoOld    ,Rp   
	Dimension		Add(nStif),HD(12),HDOld(12),Rp(3)
	Real(kind=8)	BVEC       ,SKLM       ,R0   ,RK   ,C0   ,CK       
	Dimension		BVEC(nStif),SKLM(nStif),R0(3),RK(3),C0(3),CK(3)
	Real(kind=8) AM,BM,CM,TH,Ri,Si,Wt,sum
!
	LOGICAL bReset
!============================================
	common/LoadStepIter/iStep,iNut,bReset
      common/Scratch/	  iRotCur1,iRotCur2,iDetRef
!============================================
	DATA zero/0.D0/,one/1.0D0/ 
	DATA nC/3/,nDof/6/,nDof2/12/
!----------------------------------------------------------
!	Stiffness Matrix Calculation
!
	BFors	= 0.D0	!all
	StifK	= 0.D0	!all
    	Stif	= 0.D0	! all elements = 0.
!===================================================================== Restore
	inquire(iRotCur1,NEXTREC = nRec)
	if(nRec.GT.1) then
		nRec = Nel
		call PutGetRotCur(iRotCur1,RoCOld,CuCold,nCInt,nRec,2)		!Read
		call PutGetDetRef(iDetRef,DetRef,Nint,nRec,2)				!Read
	endif			
	if(iNut.GT.0) Then
		abc = 1
	endif
!===================================================================== Restore End
!	Loop over Gauss Locations
	do 60 jInt = 1,Nint
	Ri	= GaussPtVal(jInt,Nint,1) 
	Det	= DetRef(jInt)
!------------------------------------------------------------- Get Cur,Tor & Axes
	call QQ_TMB_CuLn(Qc,nQc,nOrderR,Ri,Det,Cur,Tor,
     &						Axes,dxbardr,Nel,Iout,iPrt)
!---------------------------------------------- Check:Orthonomal:OK
	SK = MATMUL(Axes,TRANSPOSE(Axes))
!------------------------------------------------------------- Get  Geometric Curvature Vector etc.
	call Get_ReferenceInfo(Axes,Cur,Tor,Axes6,Axes12,Axep,
     &					nQc,nC,RoCOld,CuCOld,nCInt,
     &                    Ri,jInt,R0,C0,CK,T,B,
     &                    nDof,nDof2,nStif,Det,Iout,Nel,Nint)
!	endif
!		-------------------------------------------------------- Debug 
		if((iStep == 2).AND.(iNut == 1)) Then
			iPrt = 0
			call DumpStringVar("Beg:Quad_QQ_STIF_befEDG",iPrt,iOut)
			call DumpIntegerVar(Nel,"Element#",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
			call DumpIntegerVar(jInt,"GIndex:jInt",iPrt,iOut)
			call DumpRealVar(Ri,"GaussPt.:Ri",iPrt,iOut)
			call DumpIntegerVar(nCInt,"nCInt",iPrt,iOut)
			call DumpRealArray(DetRef,Nint,"DetRef",iPrt,iOut)
			call DumpRealArray(Rocold,nCInt,"Rocold",iPrt,iOut)
			call DumpRealArray(Cucold,nCInt,"Cucold",iPrt,iOut)
			call DumpRealArray(Qd,nStif,"Qd",iPrt,iOut)
			call DumpRealArray(R0,3,"R0",iPrt,iOut)
			call DumpRealArray(C0,3,"C0",iPrt,iOut)
			call DumpRealArray(CK,3,"CKBefEDG",iPrt,iOut)
			call DumpRealMatrix(T, 6,nStif,"T",iPrt,iOut)
			iPrt = 0
			call DumpRealMatrix(B,12,nStif,"B",iPrt,iOut)
			call DumpRealArray(Qd,nStif,"Qd",iPrt,iOut)
			iPrt = 0
			call DumpStringVar("End:Quad_QQ_STIF_befEDG",iPrt,iOut)
		endif
!		-------------------------------------------------------- Debug : End
!--------------------------------------------------------------------- DisRots & Derivatives
!	Qd represents cartesian deformations and derivatives
	HD = MATMUL(B,Qd)					! curvilinear
!------------------------------------------------------------- Get  EDG(nDof2,nDof2)
	call Form_EtranDEplusGMatrix(Axes6,
     &				R0,HD,nStif,DMat,C0,RK,CK,
     &				T,B,BVEC,SKLM,EDG,3,nDof,nDof2,Iout)
!------------------------------------------------------------- Save Curvature
!		-------------------------------------------------------- Debug 
		iPrt = 0
		if((iStep == 1).AND.(iNut == 2)) Then
			iPrt = 0
			call DumpStringVar("Beg:Quad_QQ_STIF_aftEDG",iPrt,iOut)
			call DumpRealArray(RK,3,"RK",iPrt,iOut)
			call DumpRealArray(C0,3,"C0_aftEDG",iPrt,iOut)
			call DumpRealArray(CK,3,"CK_aftEDG",iPrt,iOut)
			iPrt = 0
			call DumpRealArray(BFors,nStif,"BFors",iPrt,iOut)
			call DumpRealMatrix(DMat,6,6,"DMat",iPrt,iOut)
			call DumpRealArray(BVEC,nStif,"BVEC",iPrt,iOut)
			call DumpRealArray(SKLM,nStif,"SKLM",iPrt,iOut)
			call DumpRealMatrix(EDG,12,12,"EDG",iPrt,iOut)
			iPrt = 0
			call DumpStringVar("End:Quad_QQ_STIF_aftEDG",iPrt,iOut)
		endif
!		-------------------------------------------------------- Debug : End
!============================================================= save:Temporarily all iterations
!	if((iStep == 2)) Then
!		abc = 1
!	endif
!	do 10 ii = 1,nC
!	ij = ii + (jInt -1)*nC
!	RoCOld(ij) = RK(ii) 
!	CuCold(ij) = C0(ii) 
!   10	continue
!	if((iStep == 1).AND.(iNut == 5)) Then
!		abc = 1
!	endif
!------------------------------------------------------------- Form: Btran_EDG_B 
!	Add to stiffness matrix
!
	Wt = GaussPtVal(jInt,Nint,2)*Det
!
	do 50 j = 1,nStif
	do 20 k = 1,nDof2		! 
	DB(k) = 0.0
	do 20 l = 1,nDof2		! 
	DB(k) = DB(k) + EDG(k,l)*B(l,j)
   20 continue
	do 40 i = j,nStif
	sum = 0.0
	do 30 l = 1,nDof2		! 
	sum = sum + B(l,i)*DB(l)
   30	continue
	Stif(i,j) = Stif(i,j) + sum*Wt
   40	continue
   50 continue
!------------------------------------------------------------- Load Vector: Residual & Body force part 
	do 53 i = 1,nStif
	BFors(i) = BFors(i) + Wt*BVec(i)
   53 continue		
!------------------------------------------------------------- Form: Last Column of
!                                                              stiffness: KLamda Body Force part
 
	do 55 i = 1,nStif
	StifK(i) = StifK(i) + Wt*SKLM(i)
   55 continue		
   60 continue
!
!	symmetry: Upper Triangle 
!
	do 70 j = 1,nStif
	do 70 i = j,nStif
  	Stif(j,i) = Stif(i,j)
   70 continue
!===================================================================== Save
!	nRec = Nel
!	call PutGetRotCur(iRotCur2,RoCOld,CuCold,nCInt,nRec,1)	!Write
!===================================================================== Save End
!	Get Trace
!
	Trace = 0.D0
	do 80 i = 1,nStif
	Trace = Trace + Stif(i,i)
   80 continue			
!
!	Check each col. vector for Null
!
	Add = 0.D0
	do 100 j = 1,nStif
	sum = 0.0 
	do 90 i = 1,nStif	
	sum = sum + Stif(i,j)
   90 continue
	Add(j) = sum
  100 continue			
!
!	done
!
	iPrt = 0
	if(iPrt == 1) Then
		write(Iout,1010) nStif,nStif
		do 110 i = 1,nStif
		write(Iout,1020) i,(Stif(i,j),j = 1,nStif)
  110	continue
	endif 
!
	return
!===========
 1010 format("Full Stiffness Matrix:Stif(",I2,",",I2,")"/)
 1020 format(I5/(3(5(f16.6,1X)/)/))
	end   		
	   		