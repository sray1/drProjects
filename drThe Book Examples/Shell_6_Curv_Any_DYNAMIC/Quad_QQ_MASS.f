	Subroutine Quad_QQ_MASS(RoCOld,CuCOld,RoSav,CKSav,Qd,
     &						Nel,B,T,SMas,nStif,Iout,Trace)
!
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
!		nStif		= Row or Col size of Mass matrix 
!						= nDof*nQd1*nQd2
!		Iout		= Error Output file#
!		 	
!	Outputs 
!		Mass(nStif,nStif)	= Desired Mass Matrix
!		bFors(nStif)		= Desired Body force Vector Integrals
!		StifK(nStif)		= Desired kLamda Stiffness last column Vector Integrals
!		Trace		= trace of the matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!	===========================
	include 'Mass.h'
	include 'Material.h'
	include 'CurParams.h'
	include 'SizeVar.h'
	include 'LoadStepIter.h'
	include 'Scratch.h'
	include 'ShellParams.h'
	include 'LogParams.h'
	include 'GaussIndex.h'
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
!	
!	Working Variables & Arrays	
!
!	Real(kind=8)	DD   ,RR   ,DP1   ,Rp1   ,Dp2   ,Rp2                
!	Dimension		DD(3),RR(3),DP1(3),Rp1(3),Dp2(3),Rp2(3)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	B             ,T     
	Dimension		B(nDof2,nStif),T(nDof,nStif)
	Real(kind=8)	SMas			   ,Trace
	Dimension		SMas(nStif,nStif)
	Real(kind=8)	XM           ,DB        
	Dimension		XM(nDof,nDof),DB(nDof)
	Real(kind=8)	Add       ,HD       ,Rp   
	Dimension		Add(nStif),HD(nDof2),Rp(3)
	Real(kind=8)	R0   ,RK          
	Dimension		R0(3),RK(3)
	Real(kind=8) AM,BM,CM,TH,Ri,Rj,Si,Wt,sum
!	===============================
	LOGICAL bReset
	DATA zero/0.D0/,one/1.0D0/,onm/-1.0D0/ 
	DATA NC/3/
!================================================================================
!	Mass Matrix Calculation
!
    	SMas	= 0.D0	! all elements = 0.
!============================================================== 
	iPrt = 0
	if((iStep == 1).AND.(iNut == 2)) Then
		iPrt = 0
	endif
	if(iPrt == 1) then
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
		call DumpStringVar("Beg:From:Quad_QQ_MASS",iPrt,iOut)
		call DumpRealArray(Qd,nStif,"Qd array",1,iOut)
		call DumpStringVar("End:From:Quad_QQ_MASS",iPrt,iOut)
	endif
	iPrt = 0
!============================================================== .
!	Rewind CUrvatureInfo, B & T Scratch files
	if(Nel == 1) then
		nRec = 0
		rewind iRefPro1
		rewind iRefPro2
	endif
!	Loop over Gauss Locations
	do 60 iGau = 1,Nint1
	do 60 jGau = 1,Nint2
!	------------------------------ gauss positions
	ri = GaussPtVal(iGau,Nint1,1) 
	rj = GaussPtVal(jGau,Nint2,1) 
!------------------------------------------------------------- Get  Geometric Curvature Vector etc.
!	if(iNut == 1) Then
!	if((iStep == 1).AND.(iNut == 5)) Then
	if((iStep == 0).AND.(iNut == 0)) Then
		abc = 1
	endif
!
	nRec = nRec + 1
!	===============
	iPrt = 0
	if((iStep == 1).AND.(iNut == 2)) Then
		iPrt = 0
	endif
	if(iPrt == 1) then
		call DumpStringVar("Beg:Quad_QQ_MASS",iPrt,iOut)
		call DumpRealVar(ri,"ri",iPrt,iOut)
		call DumpRealVar(rj,"rj",iPrt,iOut)
		call DumpStringVar("End:Calc_ReferenceProps",iPrt,iOut)
	endif
	iPrt = 0
!	---------------------------------------------------
	T = zero
	B = zero
	call Get_ReferenceInfoataGaussPt
     &					(T,B,nDof,nDof2,nStif,Nel,nRec)
!	---------------------------------------------------
!	call Get_ReferenceInfo(Qc,nC,nQc,RoCOld,CuCOld,nCInt,
!     &                    Rjj,jGau,Rkk,kInt,R0,C0,CK,nC,T,B,
!     &                    nDof,nDof2,nStif,RutAhat,Iout,Nel,Nint)
!	endif
!		-------------------------------------------------------- Debug 
		iPrt = 0
		if((iStep == 1).AND.(iNut == 2)) Then
			iPrt = 0
		endif
	if(iPrt == 1) then
			call DumpStringVar("Beg:Quad_QQ_MASS_befXM",iPrt,iOut)
			call DumpIntegerVar(Nel,"Element#",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
			call DumpIntegerVar(iGau,"GIndex:iGau",iPrt,iOut)
	!		call DumpRealVar(Ri,"GaussPt.:Ri",iPrt,iOut)
			call DumpIntegerVar(jGau,"GIndex:jGau",iPrt,iOut)
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
			call DumpRealMatrix(T,nDof,nStif,"T",iPrt,iOut)
!			call DumpRealMatrix(B,nDof2,nStif,"B",iPrt,iOut)
			iPrt = 0
			call DumpStringVar("End:Quad_QQ_MASS_befXM",iPrt,iOut)
		endif
		iPrt = 0
!		-------------------------------------------------------- Debug : End
!--------------------------------------------------------------------- DisRots & Derivatives
!	if(bReset == .TRUE.) Then
	if(iStep == 6) Then
		abc = one
	endif
!	====================================== Debug
!	if((iStep == 1).AND.(iNut == 2)) Then
	if((iStep == 1).AND.(iNut == 2)) Then
		abc = 1
!		call DumpRealArray(Qd,nStif,"Qd",0,iOut)
	endif
!	====================================== Debug End
	call Split_Dis_Rot_Deriv(Qd,nStif,B,Iout)
!	---------------------------------------------------------------- Update Rotation
!	do 10 i = 1,nC				
!   10	RK(i) = R0(i) + RR(i)
!		-------------------------------------------------------- Debug 
	iPrt = 0
		if((iStep == 1).AND.(iNut == 2)) Then
			iPrt = 0
		endif
	if(iprt == 1) then
!			call DumpStringVar("Beg:Quad_QQ_NASS_aftXM",iPrt,iOut)
!			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
!			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
			call DumpIntegerVar(iGau,"iGau",iPrt,iOut)
			call DumpIntegerVar(jGau,"jGau",iPrt,iOut)
!			call DumpStringVar("End:Quad_QQ_MASS_aftXM",iPrt,iOut)
	endif
	iPrt = 0
!		-------------------------------------------------------- Debug : End
!	================================================================ XM(nDof,nDof)
	call Form_Mass_Matrix(W,XM,nS,nD,Iout)
	call Form_EtranDEplusGMatrix(DMat,T,B,BVEC,SKLM,EDG,Iout)
!		-------------------------------------------------------- Debug 
		iPrt = 0
		if((iStep == 1).AND.(iNut == 2)) Then
			iPrt = 0
		endif
		if(iprt == 1) then
			call DumpStringVar("Beg:Quad_QQ_MASS_aftXM",iPrt,iOut)
			if(iPrt == 1) Then
				write(Iout,1040) (i,(XM(i,j),j = 1,nDof),i=1,nDof)
			endif
!		----------------------------------------------------------
			call DumpStringVar("End:Quad_QQ_MASS_aftXM",iPrt,iOut)
		endif
!		-------------------------------------------------------- Debug : End
	if((iNut.LE.1).AND.(Nel == 2)) Then
			abc = 0
	endif
!============================================================= save
!	if(iNut.LE.1) Then
!		do 10 ii = 1,nC
!		ij = ii + (jGau -1)*nC
!		RoCOld(ij) = RK(ii) 
!		CuCold(ij) = CK(ii) 
!   10		continue
!		nRec = (Nel-1)*Nint + jGau
!		if(iRotCur == iRotCur1) Then
!			call PutGetRotCur(iRotCur2,RoCOld,CuCold,nCInt,nRec,1)
!		else
!			call PutGetRotCur(iRotCur1,RoCOld,CuCold,nCInt,nRec,1)
!		endif			
!	endif
!------------------------------------------------------------- Form: Ttran_XM_T 
!	Add to Mass matrix
!
	Wt = GaussPtVal(iGau,Nint1,2)*GaussPtVal(jGau,Nint2,2)*RutAhat
		iPrt = 0
		if((iStep == 1).AND.(iNut == 2)) Then
			iPrt = 0
		endif
		if(iprt == 1) then
			call DumpRealVar(RutAhat,"RutAhat",iPrt,iOut)
			call DumpRealVar
     &			(GaussPtVal(iGau,Nint1,2),"Gaussi",iPrt,iOut)
			call DumpRealVar
     &			(GaussPtVal(jGau,Nint1,2),"Gaussj",iPrt,iOut)
			call DumpRealVar(Wt,"Weight",iPrt,iOut)
		endif
		iPrt = 0
!
	do 50 j = 1,nStif
	do 20 k = 1,nDof		! 
	DT(k) = 0.0
	do 20 l = 1,nDof		! 
	DT(k) = DT(k) + XM(k,l)*T(l,j)
   20 continue
	do 40 i = j,nStif
	sum = 0.0
	do 30 l = 1,nDof		! 
	sum = sum + T(l,i)*DT(l)
   30	continue
	SMas(i,j) = SMas(i,j) + sum*Wt
   40	continue
   50 continue
!------------------------------------------------------------- Form
!
!	symmetry: Upper Triangle 
!
	do 70 j = 1,nStif
	do 70 i = j,nStif
  	SMas(j,i) = SMas(i,j)
   70 continue
!
!	Get Trace
!
	Trace = 0.D0
	do 80 i = 1,nStif
	Trace = Trace + SMas(i,i)
   80 continue			
!
!	done
!
	iPrt = 0
	if(iPrt == 1) Then
		write(Iout,1010) nStif,nStif
		do 110 i = 1,nStif
		write(Iout,1020) i,(SMas(i,j),j = 1,nStif)
  110	continue
	endif 
!============================================================== Check each col.
	iPrt = 0
	if(iPrt == 1) then
		Add = 0.D0
		do 999 j = 1,nStif
		sum = 0.0 
		do  99 i = 1,nStif	
		sum = sum + SMas(i,j)
   99		continue
		Add(j) = sum
  999		continue
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
		call DumpStringVar("Beg:From:Quad_QQ_MASS",iPrt,iOut)
		call DumpRealArray(Add,nStif,"Add_Col_Mass",1,iOut)
		call DumpStringVar("End:From:Quad_QQ_MASS",iPrt,iOut)
	endif
	iPrt = 0
!============================================================== Check each col.
!
	return
!
 1010 format("Full Mass Matrix:Stif(",I5,",",I5,")"/)
 1020 format(I5/(6(8(f12.1,1X)/)/))
 1040 format(2X, "XM Matrix(6,6)"/(I3,6(f5.0,1X)))
	end   		
	   		