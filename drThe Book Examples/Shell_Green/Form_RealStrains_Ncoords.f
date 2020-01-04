	Subroutine FormRealStrains_Ncoords(rE,nE,nC,iDir,Iout)
!	----------------------------------------------------------------------------- 
!	Inputs
!		C0(nC)			= initial Curvature vector = {torsion,0,curvature}
!		nC				= 3
!		nE				= 6
!		AMat			= Rotation Matrix
!		AA				= a Vector = [k0]d + e
!		CK				= Kc Vector = k0 + k = k0 + W(thetaPrimed)
!		iDir			= surface direction: 1 or 2
! 	
!	Outputs 
!		rE(nE)			= Real Strains in n-Mn-Qn Coordinates
!	------------------------------------------------------------
	Implicit Real(kind=8) (a-h,o-z)
!
!============================================
	include 'BeamParams.h'
	include 'LoadStepIter.h'
!	include 'Beam2ShellXforms.h'
!============================================
	Real(kind=8)	rE    ,Bet    ,xKi                    
	Dimension		rE(nE),Bet(nC),xKi(nC)
	Real(kind=8)	TAMat                           
	Dimension		TAMat(nC,nC)
!============================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	====================================== Debug
	if((iStep == 1).AND.(iNut == 2)) Then
	abc = 1
	endif
!------------------------------------------------------------------AMatTran
	TAMat = TRANSPOSE(AMat)
!------------------------------------------------------------------Beta_N
	Bet = MATMUL(TAMat,AA)				!AMatTransposeAA
	Bet = Bet - Hat					!AMatTransposeAA - Hat
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
		if((iStep == 9999).AND.(iNut == 2)) Then
			iPrt = 1
!			call DumpVar(iOut)
			call DumpStringVar("Beg:FormRealStrains_Ncoord",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
			call DumpIntegerVar(iDir,"iDir:Surface Direction",iPrt,iOut)
			call DumpRealArray(C0,nC,"C0",iPrt,iOut)
			call DumpRealArray(AA,nC,"AA",iPrt,iOut)
			call DumpRealArray(CK,nC,"CK",iPrt,iOut)
			call DumpRealArray(Bet,nC,"Bet",iPrt,iOut)
			call DumpRealArray(xKi,nC,"xKi",iPrt,iOut)
			call DumpRealArray(rE,nE,"rE:RealStrains_N",iPrt,iOut)
			call DumpRealMatrix(AMAT,3,3,"AMAT",iPrt,iOut)
			call DumpStringVar("End:FormRealStrains_Ncoord",iPrt,iOut)
			iPrt = 0
		endif
!		-------------------------------------------------------- Debug : End
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Real Strains..."/2X,3(f10.7,1X))
	end
