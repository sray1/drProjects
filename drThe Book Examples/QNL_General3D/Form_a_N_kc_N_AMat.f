	Subroutine Form_a_N_kc_N_AMat(HD,RoOld,nG,C0,AMat,WMat,nC,
     &								RK,AA,CK,Iout)
!	----------------------------------------------------------------------------- 
!	Inputs
!		RoOld(nC)		= {rot} for Last Config
!		HD(nG)			= {dis,rot,disPrimed,rotPrimed}: Incremental
!		nG				= 12
!		C0(nC)			= Reference Curvature vector = {torsion,0,curvature}
!		nC				= 3
!		WMat			= WMat(nC,nC)
! 	
!	Outputs 
!		AA(nC)			= a = [k0]d + e
!		CK(nC)			= kc = k0 + k = k0 + W9ThetaPrimed)
!	    FormThetaConstants = c1,c2,c1b,c2b
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	HD    ,RoOld    ,C0                       
	Dimension		HD(nG),RoOld(nC),C0(nC)
	Real(kind=8)	AMatOld       ,AMatInc                   
	Dimension		AMatOld(nC,nC),AMatInc(nC,nC)
	Real(kind=8)	AMat       ,WMat                   
	Dimension		AMat(nC,nC),WMat(nC,nC)
	Real(kind=8)	Di    ,Dp    ,Ro    ,RK    ,Rp                         
	Dimension		Di(nC),Dp(nC),Ro(nC),RK(nC),Rp(nC)
	Real(kind=8)	CK    ,AA    ,v1    ,v2    ,Hat1                        
	Dimension		CK(nC),AA(nC),v1(nC),v2(nC),Hat1(3)
!
	common/ThetaConstants/c1,c2,c1b,c2b
!==========================================		
	common/LoadStepIter/iStep,iNut,bReset
!==========================================		
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
	DATA Hat1/1.0D0,0.D0,0.D0/
!	------------------------------------------------------------------- H(dHat):Incremental
	call Extract_Vector(HD,nG,Di,nC,1,Iout)	!displacement
	call Extract_Vector(HD,nG,Ro,nC,4,Iout)	!rotation
	call Extract_Vector(HD,nG,Dp,nC,7,Iout)	!displacementPrimed
	call Extract_Vector(HD,nG,Rp,nC,10,Iout)!rotationPrimed
!============================
	if (iNut==1) Then
		Ro = 0
		Rp = 0
	endif
!	------------------------------------------------------------------- Theta Constants
	call FormThetaConstants(Ro,nC,c1,c2,c1b,c2b,Iout)
!	------------------------------------------------------------------- Translational
	call CrossProduct(C0,Di,v1,Iout)		! [k0]d = k0 x d
	call VectorAdd(Hat1,Dp,v2,nC,Iout)		!e-vector
	call VectorAdd(v1,v2,AA,nC,Iout)		!a-vector
!----------------------------------------------------------------------- Form AMat (Rodrigues)
!	if((iStep == 2).AND.(iNut == 1)) Then
	call FormRotationMatrix(RoOld,AMatOld,nC,Iout)
	call FormRotationMatrix(Ro,AMatInc,nC,Iout)
!	------------------------------- Update
	AMat = MATMUL(AMatOld,AMatInc)
!	-----------------
!	call FormRotationMatrix(Ro,AMat,nC,Iout)
!	------------------------------------------------------------------- Rotational
	call Form_WMatrix(Ro,WMat,nC,Iout)
!	-----------------
!	CK = C0						! Reference Curvature vector
	do 30 i = 1,nC				! kC = current Curvature
	RK(i) = RoOld(i) + Ro(i)
	sum = zero					!    =  + Reference Curvature + W thetaPrimed
	do 20 j = 1,nC
   20	sum = sum + WMat(i,j)*Rp(j)
	CK(i) = CK(i) + sum
   30 continue
	if((iStep == 3)) Then
		abc = 1
	endif
!		-------------------------------------------------------- Debug 
		if((iStep == 1).AND.(iNut == 2)) Then
			iPrt = 0
!			call DumpVar(iOut)
			call DumpStringVar("Beg:Form_a_N_kc_N_AMat",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
			call DumpRealArray(Di,3,"Di",iPrt,iOut)
			call DumpRealArray(Ro,3,"Ro",iPrt,iOut)
			call DumpRealArray(Dp,3,"Dp",iPrt,iOut)
			call DumpRealArray(Rp,3,"Rp",iPrt,iOut)
			call DumpRealArray(C0,3,"C0",iPrt,iOut)
			call DumpRealArray(AA,3,"AA",iPrt,iOut)
			call DumpRealMatrix(AMAT,3,3,"AMAT",iPrt,iOut)
			call DumpRealMatrix(WMAT,3,3,"WMAT",iPrt,iOut)
			call DumpRealArray(CK,3,"CK",iPrt,iOut)
			call DumpStringVar("End:Form_a_N_kc_N_AMat",iPrt,iOut)
		endif
!		-------------------------------------------------------- Debug : End
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1010) (AA(j),j = 1,nC)
		write(Iout,1020) (CK(j),j = 1,nC)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"a-vector..."/2X,3(f10.7,1X))
 1020 format(1X,"kc-vector..."/2X,3(f10.7,1X))
	end
