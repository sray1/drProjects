	Subroutine Quad_QQ_STIF(RoCOld,CuCOld,RoSav,CKSav,nCInt,Qd,Qc,nQc,
     &						Nel,NelType,Nint,DMat,
     &						Stif,BFors,StifK,nStif,Iout,Trace)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!	Notes:	Nint should be atleast 2
!
!	Inputs
!		Qd(nStif)	= Latest displacement controls: state vector
!		Qc(1,16)	= Bezier X-Coordinates
!					=	(qc00x qc10x...qc33x)
!		Qc(2,16)	= Bezier Y-Coordinates
!					=	(qc00y qc10y...qc33y)
!		Qc(3,16)	= Bezier Z-Coordinates
!					=	(qc00z qc10z...qc33z)
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
	Real(kind=8)	Qc       ,Qd                   
	Dimension		Qc(3,nQc),Qd(nStif)
	Real(kind=8)	RoSav       ,CKSav            
	Dimension		RoSav(nCInt),CKSav(nCInt)
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
      common/files/iFileStiff,Ioutt,IoutDef,IoutEnd,iRotCur
      common/Scratch/iRotCur1,iRotCur2
!============================================
	DATA zero/0.D0/,one/1.0D0/ 
	DATA nC/3/,nDof/6/,nDof2/12/
!----------------------------------------------------------
!	Stiffness Matrix Calculation
!
	BFors	= 0.D0	!all
	StifK	= 0.D0	!all
    	Stif	= 0.D0	! all elements = 0.
!
	iPrt = 0
	If (iPrt == 1) Then
		write(Iout,1000) Nel,nC,nQc,(i,(Qc(i,j),j=1,nQc),i=1,nC)
	endif
!
!	Loop over Gauss Locations
	do 60 jInt = 1,Nint
	Ri = GaussPtVal(jInt,Nint,1) 
!------------------------------------------------------------- Get  Geometric Curvature Vector etc.
!	if(iNut == 1) Then
!	if((iStep == 9999).AND.(iNut == 0)) Then
	if((iStep == 2).AND.(iNut == 1)) Then
		abc = 1
	endif
	call Get_ReferenceInfo(Qc,nC,nQc,RoCOld,CuCOld,nCInt,
     &                    Ri,jInt,R0,C0,CK,nC,T,B,
     &                    nDof,nDof2,nStif,Det,Iout,Nel,Nint)
!	endif
!		-------------------------------------------------------- Debug 
		if((iStep == 9999).AND.(iNut == 2)) Then
			iPrt = 0
			call DumpStringVar("Beg:Quad_QQ_STIF_befEDG",iPrt,iOut)
			call DumpIntegerVar(Nel,"Element#",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
			call DumpIntegerVar(jInt,"GIndex:jInt",iPrt,iOut)
			call DumpRealVar(Ri,"GaussPt.:Ri",iPrt,iOut)
			call DumpIntegerVar(nCInt,"nCInt",iPrt,iOut)
			call DumpRealArray(Rocold,nCInt,"Rocold",iPrt,iOut)
			call DumpRealArray(Cucold,nCInt,"Cucold",iPrt,iOut)
			call DumpRealArray(Qd,nStif,"Qd",iPrt,iOut)
			call DumpRealMatrix(Qc,3,nQc,"Qc",iPrt,iOut)
			call DumpRealArray(R0,3,"R0",iPrt,iOut)
			call DumpRealArray(C0,3,"C0",iPrt,iOut)
			call DumpRealArray(CK,3,"CKBefEDG",iPrt,iOut)
			iPrt = 0
			call DumpRealMatrix(T, 6,nStif,"T",iPrt,iOut)
			call DumpRealMatrix(B,12,nStif,"B",iPrt,iOut)
			iPrt = 1
			call DumpStringVar("End:Quad_QQ_STIF_befEDG",iPrt,iOut)
		endif
!		-------------------------------------------------------- Debug : End
!--------------------------------------------------------------------- DisRots & Derivatives
!	if(bReset == .TRUE.) Then
	if(iStep == 6) Then
		abc = one
	endif
	HD		= MATMUL(B,Qd)
!------------------------------------------------------------- Get  EDG(nDof2,nDof2)
	call Form_EtranDEplusGMatrix(R0,HD,nStif,DMat,C0,RK,CK,
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
	if((iNut.LE.1).AND.(Nel == 2)) Then
			abc = 0
	endif
!============================================================= save
!	if(iNut.LE.1) Then
!		do 10 ii = 1,nC
!		ij = ii + (jInt -1)*nC
!		RoCOld(ij) = RK(ii) 
!		CuCold(ij) = CK(ii) 
!   10		continue
!		nRec = (Nel-1)*Nint + jInt
!		if(iRotCur == iRotCur1) Then
!			call PutGetRotCur(iRotCur2,RoCOld,CuCold,nCInt,nRec,1)
!		else
!			call PutGetRotCur(iRotCur1,RoCOld,CuCold,nCInt,nRec,1)
!		endif			
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
!
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
!
 1000 format("QC(",I1,",",I1,"): Elem# =",I4/
     &        2(I5,5X,5(f10.6,1X)/) )
 1010 format("Full Stiffness Matrix:Stif(",I2,",",I2,")"/)
 1020 format(I5/(3(5(f16.6,1X)/)/))
	end   		
	   		