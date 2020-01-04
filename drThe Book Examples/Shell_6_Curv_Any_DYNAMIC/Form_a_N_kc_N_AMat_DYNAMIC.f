	Subroutine Form_a_N_kc_N_AMat_DYNAMIC(iDir,Iout)
!	----------------------------------------------------------------------------- 
!	Inputs
!		RoOld(nC)		= {rot} for Last Config
!		HD(nG)			= {dis,rot,disPrimed_1,rotPrimed_1,disPrimed_2,rotPrimed_2}: Incremental
!		nG				= 18
!		C0(nC)			= Reference Curvature vector = {torsion,0,curvature}
!		nC				= 3
!		WMat			= WMat(nC,nC)
!		WdotMat			= WdotMat(nC,nC)
!		W2dotMat		= W2dotMat(nC,nC)
! 	
!	Outputs 
!		AA(nC)			= a = [k0]d + e
!		CK(nC)			= kc = k0 + k = k0 + W*ThetaPrimed
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!============================================
	include 'LoadStepIter.h'
	include 'BeamParams.h'
	include 'DynParams.h'
	include 'ThetaConstants.h'
!==============================================
	Real(kind=8)	v1   ,v2                            
	Dimension		v1(3),v2(3)
!==========================================		
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
	DATA nC/3/
!===========================================================================================		
!	------------------------------------------------------------------- AA
	call CrossProduct(C0,Di,v1,Iout)		! [k01]d = k01 x d
	call VectorAdd(Hat,Dp,v2,nC,Iout)		!e-vector
	call VectorAdd(v1,v2,AA,nC,Iout)		!a-vector
!----------------------------------------------------------------------- Form AMat (Rodrigues)
	if((iStep == 9999).AND.(iNut == 2)) Then								!(Rotation Matrix)
		abc = 1
	endif
!	call FormRotationMatrix(RoOld,AMatOld,nC,Iout)
!	call FormRotationMatrix(Ro,AMatInc,nC,Iout)
!	------------------------------- Update
!	AMat = MATMUL(AMatOld,AMatInc)
!	----------------------------------------
	call FormRotationMatrix(Ro,AMat,nC,Iout)
!	------------------------------------------------------------------- Form WMatrix
	call Form_WMatrix(Ro,WMat,nC,Iout)
!	------------------------------------------------------------------- Form WdotMatrix
	call Form_WdotMatrix(Ro,WdotMat,nC,Iout)
!	------------------------------------------------------------------- Form W2dotMatrix
	call Form_W2dotMatrix(Ro,W2dotMat,nC,Iout)
!	------------------------------------------------------------------- CK
		CK = C0						! Reference Curvature vector
		CK = CK + MATMUL(WMat,Rp)	! kC1 = current Curvature
!									      =  + Reference Curvature + W thetaPrimed
!		-------------------------------------------------------- Debug 
		if((iStep == 9999).AND.(iNut == 2)) Then
!		if((iStep == 1).AND.(iNut == 2)) Then
			iPrt = 0
!			call DumpVar(iOut)
			call DumpStringVar("Beg:Form_a_N_kc_N_AMat",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
			call DumpIntegerVar(iDir,"iDir",iPrt,iOut)
			call DumpRealArray(Di,3,"Di             ",iPrt,iOut)
			call DumpRealArray(Ro,3,"Ro             ",iPrt,iOut)
			call DumpRealArray(Dp,3,"Dp           ",iPrt,iOut)
			call DumpRealArray(Rp,3,"Rp           ",iPrt,iOut)
			call DumpRealArray(C0 ,3,"C0           ",iPrt,iOut)
			call DumpRealArray(AA ,3,"AA           ",iPrt,iOut)
			call DumpRealVar(c1,"c1                 ",iPrt,iOut)
			call DumpRealVar(c2,"c2                 ",iPrt,iOut)
			call DumpRealVar(c1b,"c1b               ",iPrt,iOut)
			call DumpRealVar(c2b,"c2b               ",iPrt,iOut)
			call DumpRealMatrix(AMAT,3,3,"AMAT      ",iPrt,iOut)
			call DumpRealMatrix(WMAT,3,3,"WMAT      ",iPrt,iOut)
!			call DumpRealArray(RK,3,"RK             ",iPrt,iOut)
			call DumpRealArray(CK,3,"CK            ",iPrt,iOut)
			call DumpStringVar("End:Form_a_N_kc_N_AMat",iPrt,iOut)
			iPrt = 0
		endif
!		-------------------------------------------------------- Debug : End
!---------------------------------------------------------- Write:
	iPrt = 0
!	if (iPrt == 1) Then
!		write(Iout,1010) (AA(j),j = 1,nC)
!		write(Iout,1020) (CK(j),j = 1,nC)
!	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"a-vector..."/2X,3(f10.7,1X))
 1020 format(1X,"kc-vector..."/2X,3(f10.7,1X))
	end
