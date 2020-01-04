	Subroutine FormForMom(D,rE,nE,AMat,nC,FMt,FMn,Iout)
!	----------------------------------------------------------------------------- 
!	Inputs
!		D(nE,nE)		= Constitutive Matrix = diag{EA,GA,GA,GJ,MM,MB}
!		rE(nE)			= Real Strain Vector in n-Mn-Qn Coords
!		nC				= 3
!		nE				= 6
!		AMat(nC,nC)		= Rotation Matrix
! 	
!	Outputs 
!		FMn(nE)			= Force-Moment in N-Mn-Qn Coordinates
!		FMt(nE)			= Force-Moment in t-m-b Coordinates
!						= AMat_(FM in N-Mn-Qn) Coords
!						= AMat_(D_(rE in N-Mn-Qn Coords))
!	------------------------------------------------------------
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	rE    ,FMt    ,FMn    ,Fn    ,Xn                           
	Dimension		rE(nE),FMt(nE),FMn(nE),Fn(nC),Xn(nC)
	Real(kind=8)	Ft    ,Xt                           
	Dimension		Ft(nC),Xt(nC)
	Real(kind=8)	AMat       ,D                           
	Dimension		AMat(nC,nC),D(nE,nE)
!
	Real(kind=8)	rEt    ,rn    ,rBet_t                              
	Dimension		rEt(nE),rn(nC),rBet_t(nC)
!============================================
	common/LoadStepIter/iStep,iNut,bReset
!============================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!------------------------------------------------------------------ FMn in N-Mn-Qn Coords
	rn(1) = rE(1)
	rn(2) = rE(2)
	rn(3) = rE(3)
	rBet_t = MATMUL(AMat,rn)
!
	FMn = MATMUL(D,rE) 		!
!------------------------------------------------------------------ FMt in t-m-b Coords
	Fn(1) = FMn(1)
	Fn(2) = FMn(2)
	Fn(3) = FMn(3)
	Ft = MATMUL(AMat,Fn)
	Xn(1) = FMn(4)
	Xn(2) = FMn(5)
	Xn(3) = FMn(6)
	Xt = MATMUL(AMat,Xn)
!
	FMt(1) = Ft(1)
	FMt(2) = Ft(2)
	FMt(3) = Ft(3)
	FMt(4) = Xt(1)
	FMt(5) = Xt(2)
	FMt(6) = Xt(3)
!		-------------------------------------------------------- Debug 
		if((iStep == 9999).AND.(iNut == 2)) Then
			iPrt = 1
!			call DumpVar(iOut)
			call DumpStringVar("Beg:FormForMom",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
			call DumpRealMatrix(D,nE,nE,"D",iPrt,iOut)
			call DumpRealMatrix(AMAT,nC,nC,"AMAT",iPrt,iOut)
			call DumpRealArray(rE,nE,"rE",iPrt,iOut)
			call DumpRealArray(Fn,nC,"Fn",iPrt,iOut)
			call DumpRealArray(Ft,nC,"Ft",iPrt,iOut)
			call DumpRealArray(Xn,nC,"Xn",iPrt,iOut)
			call DumpRealArray(Xt,nC,"Xt",iPrt,iOut)
			call DumpRealArray(FMn,nE,"FMn",iPrt,iOut)
			call DumpRealArray(FMt,nE,"FMt",iPrt,iOut)
			call DumpStringVar("End:FormForMom",iPrt,iOut)
		endif
!		-------------------------------------------------------- Debug : End
!---------------------------------------------------------- Write:
	if((iStep == 9999).AND.(iNut == 2)) Then
		iPrt = 1
		if (iPrt == 1) Then
			write(Iout,1010) (FMt(j),j = 1,nE)
		endif
		iPrt = 0
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Force-Moment in t-m-b Coords..."/2X,3(f20.7,1X))
	end
