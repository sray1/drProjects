	Subroutine Quad_QQ_STIF(RoCOld,CuCOld,RoSav,CKSav,Qd,
     &						Nel,DMat,B,T,
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
!						= nDof*nQd1*nQd2
!		Iout		= Error Output file#
!		 	
!	Outputs 
!		Stif(nStif,nStif)	= Desired Stiffness Matrix
!		bFors(nStif)		= Desired Body force Vector Integrals
!		StifK(nStif)		= Desired kLamda Stiffness last column Vector Integrals
!		Trace		= trace of the matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!	===========================
	include 'Material.h'
	include 'CurParams.h'
	include 'SizeVar.h'
	include 'LoadStepIter.h'
	include 'Scratch.h'
	include 'ShellParams.h'
!============================================
!
!	Input Variables & Arrays
!
	Real(kind=8)	Qd                   
	Dimension		Qd(nStif)
	Real(kind=8)	RoSav       ,CKSav            
	Dimension		RoSav(nCInt),CKSav(nCInt)
	Real(kind=8)	RoCOld       ,CuCOld            
	Dimension		RoCOld(nCInt),CuCOld(nCInt)
	Real(kind=8)	DMat   
	Dimension		DMat(nCMat,nCMat)
!	
!	Working Variables & Arrays	
!
	Real(kind=8)	DD   ,RR   ,DP1   ,Rp1   ,Dp2   ,Rp2                
	Dimension		DD(3),RR(3),DP1(3),Rp1(3),Dp2(3),Rp2(3)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	B             ,T     
	Dimension		B(nDof2,nStif),T(nDof,nStif)
	Real(kind=8)	BFors       ,StifK       ,Stif			   ,Trace
	Dimension		BFors(nStif),StifK(nStif),Stif(nStif,nStif)
	Real(kind=8)	EDG             ,DB        
	Dimension		EDG(nDof2,nDof2),DB(nDof2)
	Real(kind=8)	Add       ,HD       ,Rp   
	Dimension		Add(nStif),HD(nDof2),Rp(3)
	Real(kind=8)	BVEC       ,SKLM       ,R0   ,RK          
	Dimension		BVEC(nStif),SKLM(nStif),R0(3),RK(3)
	Real(kind=8) AM,BM,CM,TH,Ri,Rj,Si,Wt,sum
!	=============================== ARGYRIS Frame
	Real(kind=8)	AA
	Dimension		AA(nStif,nStif)
!	=============================== ARGYRIS Frame End
!
	LOGICAL bReset
	DATA zero/0.D0/,one/1.0D0/,onm/-1.0D0/ 
!	//////////////////////
!================================================================================
!	Expanded Constitutive Matrix Calculation
!
	call Form_Constitutive_Expanded(DMat,nCMat,iOut)
!================================================================================
!	Stiffness Matrix Calculation
!
	BFors	= 0.D0	!all
	StifK	= 0.D0	!all
    	Stif	= 0.D0	! all elements = 0.
!============================================================== 
	iPrt = 0
	if(iPrt == 1) then
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
		call DumpStringVar("Beg:From:Quad_QQ_STIF",iPrt,iOut)
		call DumpRealArray(Qd,nStif,"Qd array",1,iOut)
		call DumpStringVar("End:From:Quad_QQ_STIF",iPrt,iOut)
	endif
	iPrt = 0
!============================================================== .
!	Rewind CUrvatureInfo, B & T Scratch files
	rewind iRefPro1
	rewind iRefPro2
!
	nRec = 0
!	Loop over Gauss Locations
	do 60 iInt = 1,Nint1
	do 60 jInt = 1,Nint2
!	------------------------------ gauss positions
!	Rjj = GaussPtVal(jInt,Nint1,1) 
!	Rkk = GaussPtVal(kInt,Nint2,1) 
!------------------------------------------------------------- Get  Geometric Curvature Vector etc.
!	if(iNut == 1) Then
!	if((iStep == 1).AND.(iNut == 5)) Then
	if((iStep == 0).AND.(iNut == 0)) Then
		abc = 1
	endif
!
	nRec = nRec + 1
!	---------------------------------------------------
	T = zero
	B = zero
	call Get_ReferenceInfoataGaussPt
     &					(T,B,nDof,nDof2,nStif,Nel,nRec)
!	---------------------------------------------------
!	call Get_ReferenceInfo(Qc,nC,nQc,RoCOld,CuCOld,nCInt,
!     &                    Rjj,jInt,Rkk,kInt,R0,C0,CK,nC,T,B,
!     &                    nDof,nDof2,nStif,RutAhat,Iout,Nel,Nint)
!	endif
!		-------------------------------------------------------- Debug 
		if((iStep == 0).AND.(iNut == 0)) Then
			iPrt = 0
			call DumpStringVar("Beg:Quad_QQ_STIF_befEDG",iPrt,iOut)
			call DumpIntegerVar(Nel,"Element#",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
			call DumpIntegerVar(iInt,"GIndex:iInt",iPrt,iOut)
	!		call DumpRealVar(Ri,"GaussPt.:Ri",iPrt,iOut)
			call DumpIntegerVar(jInt,"GIndex:jInt",iPrt,iOut)
	!		call DumpRealVar(Rj,"GaussPt.:Rj",iPrt,iOut)
			call DumpIntegerVar(nCInt,"nCInt",iPrt,iOut)
!			call DumpRealArray(Rocold,nCInt,"Rocold",iPrt,iOut)
!			call DumpRealArray(Cucold,nCInt,"Cucold",iPrt,iOut)
			call DumpRealArray(Qd,nStif,"Qd",iPrt,iOut)
			call DumpRealArray(R0,3,"R0",iPrt,iOut)
			call DumpRealArray(C01,3,"C01",iPrt,iOut)
			call DumpRealArray(CK1,3,"CK1BefEDG",iPrt,iOut)
			call DumpRealArray(C02,3,"C02",iPrt,iOut)
			call DumpRealArray(CK2,3,"CK2BefEDG",iPrt,iOut)
			iPrt = 0
!			call DumpRealMatrix(T,nDof,nStif,"T",iPrt,iOut)
			call DumpRealMatrix(B,nDof2,nStif,"B",iPrt,iOut)
			iPrt = 0
			call DumpStringVar("End:Quad_QQ_STIF_befEDG",iPrt,iOut)
		endif
!		-------------------------------------------------------- Debug : End
!--------------------------------------------------------------------- DisRots & Derivatives
!	if(bReset == .TRUE.) Then
	if(iStep == 6) Then
		abc = one
	endif
	HD		= MATMUL(B,Qd)
!============================================================== 
	iPrt = 0
	if(iPrt == 1) then
		call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
		call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
		call DumpStringVar("Beg:From:Quad_QQ_STIF",iPrt,iOut)
		call DumpRealArray(Hd,nDof2,"HD array",1,iOut)
		call DumpStringVar("End:From:Quad_QQ_STIF",iPrt,iOut)
	endif
	iPrt = 0
!============================================================== 
	nG =nDof2
!	------------------------------------------------------------------- H(dHat):Incremental
	call VectorExtract_Vector(HD,nG,DD,nC,1,Iout)		!displacement
	call VectorExtract_Vector(HD,nG,RR,nC,4,Iout)		!rotation
	call VectorExtract_Vector(HD,nG,Dp1,nC,7,Iout)	    !displacementPrimed
	call VectorExtract_Vector(HD,nG,Rp1,nC,10,Iout)	    !rotationPrimed
	call VectorExtract_Vector(HD,nG,Dp2,nC,13,Iout)	    !displacementPrimed
	call VectorExtract_Vector(HD,nG,Rp2,nC,16,Iout)	    !rotationPrimed
!	--------------------------------------------------------------------------------------- Update Rotation
	do 10 i = 1,nC				
   10	RK(i) = R0(i) + RR(i)
!	=============================================== Modify to use beam formulas .
!	---------------------------------- direction 1
	Di1		= DD
!	Ro1		= RR
	Ro1(1)	= RR(1)
	Ro1(2)	= RR(2)
	Ro1(3)	= RR(3)
	Dp11	= Dp1
!	Rp11	= Rp1
	Rp11(1)	= Rp1(1)
	Rp11(2)	= Rp1(2)
	Rp11(3)	= Rp1(3)
!	---------------------------------- direction 2
	Di2(1)	= DD(2)
	Di2(2)	= DD(1)
	Di2(3)	= -DD(3)
!
	Ro2(1)	= RR(2)
	Ro2(2)	= RR(1)
	Ro2(3)	= -RR(3)
!
	Dp21(1)	= Dp2(2)
	Dp21(2)	= Dp2(1)
	Dp21(3)	= -Dp2(3)
!
	Rp21(1)	= Rp2(2)
	Rp21(2)	= Rp2(1)
	Rp21(3)	= -Rp2(3)
!============================================================== .
!------------------------------------------------------------- Get  ED+G(nDof2,nDof2)
	call Form_EtranDEplusGMatrix(DMat,T,B,BVEC,SKLM,EDG,Iout)
!	call Form_EtranDEplusGMatrix(R0,HD,nStif,DMat,RK,
!     &				T,B,BVEC,SKLM,EDG,3,nDof,nDof2,Iout)
!------------------------------------------------------------- Save Curvature
!		-------------------------------------------------------- Debug 
		iPrt = 0
		if((iStep == 0).AND.(iNut == 0)) Then
			iPrt = 0
			call DumpStringVar("Beg:Quad_QQ_STIF_aftEDG",iPrt,iOut)
			call DumpRealArray(RK,3,"RK",iPrt,iOut)
			call DumpRealArray(C01,3,"C01_aftEDG",iPrt,iOut)
			call DumpRealArray(CK1,3,"CK1_aftEDG",iPrt,iOut)
			call DumpRealArray(C02,3,"C02_aftEDG",iPrt,iOut)
			call DumpRealArray(CK2,3,"CK2_aftEDG",iPrt,iOut)
			iPrt = 0
			call DumpRealArray(BFors,nStif,"BFors",iPrt,iOut)
			call DumpRealArray(BVEC,nStif,"BVEC",iPrt,iOut)
			call DumpRealArray(SKLM,nStif,"SKLM",iPrt,iOut)
			iPrt = 0
!		---------------------------------------------------------- Write:
			iPrt = 0
			if(iPrt == 1) Then
				write(Iout,1030) ((DMat(i,j),j = 1,nCMat),i=1,nCMat)
				write(Iout,1040) (i,(EDG(i,j),j = 1,nDof2),i=1,nDof2)
			endif
!		----------------------------------------------------------
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
!------------------------------------------------------------- Form: Btran_ED+G_B 
!	Add to stiffness matrix
!
	Wt = GaussPtVal(iInt,Nint1,2)*GaussPtVal(jInt,Nint2,2)*RutAhat
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
!	done
!
	iPrt = 0
	if(iPrt == 1) Then
		write(Iout,1010) nStif,nStif
		do 110 i = 1,nStif
		write(Iout,1020) i,(Stif(i,j),j = 1,nStif)
  110	continue
	endif 
!============================================================== Check each col.
	iPrt = 0
	if(iPrt == 1) then
		Add = 0.D0
		do 999 j = 1,nStif
		sum = 0.0 
		do  99 i = 1,nStif	
		sum = sum + Stif(i,j)
   99		continue
		Add(j) = sum
  999		continue
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
		call DumpStringVar("Beg:From:Quad_QQ_STIF",iPrt,iOut)
		call DumpRealArray(Add,nStif,"Add_Col_Stiffness",1,iOut)
		call DumpStringVar("End:From:Quad_QQ_STIF",iPrt,iOut)
	endif
	iPrt = 0
!============================================================== Check each col.
!
	return
!
 1010 format("Full Stiffness Matrix:Stif(",I2,",",I2,")"/)
 1020 format(I5/(6(12(f8.1,1X)/)/))
 1030 format("DMat(12,12)"/(12(f7.0,1X)))
 1040 format(2X, "EDG Matrix(18,18)"/(I3,18(f5.0,1X)))
	end   		
	   		