	Subroutine FormForMom(D,rE,nE,AMat1,AMat2,nC,nDof,FMt1,FMt2,
     &											FMn,FMns,Iout)
!	-------------------------------------------------------------- Ft,Mt for G Matrix
!	Inputs
!		D(nE,nE)		= Constitutive Matrix 
!		rE(nE)			= Real Strain Vector in n-Mn-Qn Coords
!		nC				= 3
!		nE				= 12
!		AMat(nC,nC)		= Rotation Matrix
! 	
!	Outputs 
!		FMn(nE)			= Force-Moment in N-Mn-Qn Coordinates
!		FMt(nE)			= Force-Moment in t-m-b Coordinates
!						= AMat_(FM in N-Mn-Qn) Coords
!						= AMat_(D_(rE in N-Mn-Qn Coords))
!	------------------------------------------------------------
	Implicit Real(kind=8) (a-h,o-z)
	include 'LogParams.h'			! contains Xformation matrix for virtual or engineering
	include 'LoadStepIter.h'
!	include 'Shell2BeamXforms.h'
!==============================================
	Real(kind=8)	rE    ,FMn    ,Fn    ,Xn                           
	Dimension		rE(nE),FMn(nE),Fn(nC),Xn(nC)
	Real(kind=8)	FMt1      ,FMt2                          
	Dimension		FMt1(nDof),FMt2(nDof)
	Real(kind=8)	Ft    ,Xt    ,FMns                           
	Dimension		Ft(nC),Xt(nC),FMns(nE)
	Real(kind=8)	AMat1       ,AMat2       ,D                           
	Dimension		AMat1(nC,nC),AMat2(nC,nC),D(nE,nE)
!
	Real(kind=8)	rEt    ,rn    ,rBet_t    ,XeTXe                              
	Dimension		rEt(nE),rn(nC),rBet_t(nC),XeTXe(12,12)
!============================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
	DATA half/0.5D0/,quart/0.25D0/
!	====================================== Debug
	if((iStep == 1).AND.(iNut == 2)) Then
		abc = 1
	endif
!------------------------------------------------------------------ FMn in N-Mn-Qn Coords
	FMn = MATMUL(D,rE) 		!	rE is original 12x1 strain
!------------------------------------------------------------------ FMt in t-m-b Coords
!																	for G Matrix
!-------------------------------------------------- symmetrized FMn in shell coords 
!	XeTXe	= MATMUL(TRANSPOSE(XE),XE)
!	FMns	= MATMUL(XeTXe,FMn)
	FMns	= FMn
!-------------------------------------------------- Direction 1 for G matrix in t-m-b coords
	Fn(1) = FMns(1)				
	Fn(2) = FMns(2)
	Fn(3) = FMns(3)
!	-------------------------- t-m-b coords
	Ft = MATMUL(AMat1,Fn)
!
	Xn(1) = FMns(4)
	Xn(2) = FMns(5)
	Xn(3) = FMns(6)
!	-------------------------- t-m-b coords
	Xt = MATMUL(AMat1,Xn)
!
	FMt1(1)		= Ft(1)
	FMt1(2)		= Ft(2)
	FMt1(3)		= Ft(3)
	FMt1(4)		= Xt(1)
	FMt1(5)		= Xt(2)
	FMt1(6)		= Xt(3)
!-------------------------------------------------- Direction 2 for G matrix in t-m-b coords
	Fn(1) = FMns(7)				
	Fn(2) = FMns(8)
	Fn(3) = FMns(9)
!	-------------------------- t-m-b coords
	Ft = MATMUL(AMat2,Fn)
!
	Xn(1) = FMns(10)
	Xn(2) = FMns(11)
	Xn(3) = FMns(12)
!	-------------------------- t-m-b coords
	Xt = MATMUL(AMat2,Xn)
!
	FMt2(1)		= Ft(1)
	FMt2(2)		= Ft(2)
	FMt2(3)		= Ft(3)
	FMt2(4)		= Xt(1)
	FMt2(5)		= Xt(2)
	FMt2(6)		= Xt(3)
!		-------------------------------------------------------- Debug 
	iPrt = 0
		if((iStep == 1).AND.(iNut == 2)) Then
			iPrt = 0
		endif
	if (iPrt == 1) Then
!			call DumpVar(iOut)
			call DumpStringVar("Beg:FormForMom",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
			call DumpRealMatrix(D,nE,nE,"D",iPrt,iOut)
			call DumpRealMatrix(AMAT1,nC,nC,"AMAT1",iPrt,iOut)
			call DumpRealMatrix(AMAT2,nC,nC,"AMAT2",iPrt,iOut)
			call DumpRealArray(rE,nE,"rE",iPrt,iOut)
			call DumpRealArray(Fn,nC,"Fn",iPrt,iOut)
			call DumpRealArray(Ft,nC,"Ft",iPrt,iOut)
			call DumpRealArray(Xn,nC,"Xn",iPrt,iOut)
			call DumpRealArray(Xt,nC,"Xt",iPrt,iOut)
			call DumpRealArray(FMn,nE,"FMn",iPrt,iOut)
			call DumpRealArray(FMns,nE,"FMns",iPrt,iOut)
			call DumpRealArray(FMt1,nDof,"FMt1",iPrt,iOut)
			call DumpRealArray(FMt2,nDof,"FMt2",iPrt,iOut)
			call DumpStringVar("End:FormForMom",iPrt,iOut)
		endif
			iPrt = 0
!		-------------------------------------------------------- Debug : End
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Force-Moment in t-m-b Coords..."/2X,3(f20.7,1X))
	end
