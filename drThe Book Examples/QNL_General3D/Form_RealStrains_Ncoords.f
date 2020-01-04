	Subroutine FormRealStrains_Ncoords(C0,nC,AA,CK,AMat,rE,nE,Iout)
!	----------------------------------------------------------------------------- 
!	Inputs
!		C0(nC)			= initial Curvature vector = {torsion,0,curvature}
!		nC				= 3
!		nE				= 6
!		AMat			= Rotation Matrix
!		AA				= a Vector = [k0]d + e
!		CK				= Kc Vector = k0 + k = k0 + W(thetaPrimed)
! 	
!	Outputs 
!		rE(nE)			= Real Strains in n-Mn-Qn Coordinates
!	------------------------------------------------------------
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	C0                       
	Dimension		C0(nC)
	Real(kind=8)	rE    ,Bet    ,xKi    ,Hat1                   
	Dimension		rE(nE),Bet(nC),xKi(nC),Hat1(3)
	Real(kind=8)	CK    ,AA    ,AMat       ,TAMat                           
	Dimension		CK(nC),AA(nC),AMat(nC,nC),TAMat(nC,nC)
!============================================
	common/LoadStepIter/iStep,iNut,bReset
!============================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
	DATA Hat1/1.0D0,0.D0,0.D0/
!------------------------------------------------------------------AMatTran
	TAMat = TRANSPOSE(AMat)
!------------------------------------------------------------------Beta_N
	Bet = MATMUL(TAMat,AA)				!AMatTransposeAA
	Bet = Bet - Hat1					!AMatTransposeAA - Hat1
!------------------------------------------------------------------Ki_N
	xKi = MATMUL(TAMat,CK) - C0			!AMatTransposeCK - C0
!------------------------------------------------------------------------------ Form RealStrain
	rE(1) = Bet(1)
	rE(2) = Bet(2)
	rE(3) = Bet(3)
	rE(4) = xKi(1)
	rE(5) = xKi(2)
	rE(6) = xKi(3)
!		-------------------------------------------------------- Debug 
		if((iStep == 1).AND.(iNut == 2)) Then
			iPrt = 0
!			call DumpVar(iOut)
			call DumpStringVar("Beg:FormRealStrains_Ncoords",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
			call DumpRealArray(C0,nC,"C0",iPrt,iOut)
			call DumpRealArray(AA,nC,"AA",iPrt,iOut)
			call DumpRealArray(CK,nC,"CK",iPrt,iOut)
			call DumpRealArray(Bet,nC,"Bet",iPrt,iOut)
			call DumpRealArray(xKi,nC,"xKi",iPrt,iOut)
			call DumpRealArray(rE,nE,"rE",iPrt,iOut)
			call DumpRealMatrix(AMAT,3,3,"AMAT",iPrt,iOut)
			call DumpStringVar("End:FormRealStrains_Ncoords",iPrt,iOut)
		endif
!		-------------------------------------------------------- Debug : End
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1010) (rE(j),j = 1,nE)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Real Strains..."/2X,3(f10.7,1X))
	end
