	Subroutine Opt1_FormForMom(D,rE,nE,AMat1,AMat2,nC,nDof,FMt1,FMt2,
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
	include 'LoadStepIter.h'
	include 'Shell2BeamXforms.h'
	include 'LogParams.h'
!==============================================
	Real(kind=8)	rE    ,FMn    ,Fn    ,Xn                           
	Dimension		rE(nE),FMn(nE),Fn(nC),Xn(nC)
	Real(kind=8)	FMt1    ,FMt2                          
	Dimension		FMt1(nDof),FMt2(nDof)
	Real(kind=8)	Ft    ,Xt    ,FMns                           
	Dimension		Ft(nC),Xt(nC),FMns(nE)
	Real(kind=8)	AMat1       ,AMat2       ,D                           
	Dimension		AMat1(nC,nC),AMat2(nC,nC),D(nE,nE)
!
	Real(kind=8)	rEt    ,rn    ,rBet_t                              
	Dimension		rEt(nE),rn(nC),rBet_t(nC)
!============================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
	DATA half/0.5D0/,quart/0.25D0/
!	====================================== Debug
	if((iStep == 1).AND.(iNut == 2)) Then
		abc = 1
	endif
!------------------------------------------------------------------ FMn in N-Mn-Qn Coords
	FMn = MATMUL(D,rE) 		!	rE is original engineering strain
!------------------------------------------------------------------ FMt in t-m-b Coords
!																	for G Matrix
!-------------------------------------------------- symmetrized FMn in shell coords 
	FMns( 1) = FMn( 1)						!eF11
	FMns( 2) = quart*(FMn( 2) + FMn( 7))   !(eF12+eF21)/4
	FMns( 3) = FMn( 3)						!eF13
!
	FMns( 4) = FMn( 4)						!eM11
	FMns( 5) = quart*(FMn( 5) + FMn(10))	!(eM12+eM21)/4
	FMns( 6) = 0							!eM13
!
	FMns( 7) = FMns( 2)						!(eF12+eF21)/4					     
	FMns( 8) = FMn( 8)						!eF22
	FMns( 9) = FMn( 9)						!eF23
!
	FMns(10) = FMns( 5)						!(eM12+eM21)/4
	FMns(11) = FMn(11)						!eM22
	FMns(12) = 0							!eM23
!------------------------------------------ Direction 1 in beam coords for G matrix by beam formula
	Fn(1) = FMns(1)				
	Fn(2) = FMns(2)
	Fn(3) = FMns(3)
!	-------------------------- convert to beam coordinates
	Fn = MATMUL(D1b,Fn)
!	-------------------------- t-m-b coords
	Ft = MATMUL(AMat1,Fn)
!
	Xn(1) = FMns(4)
	Xn(2) = FMns(5)
	Xn(3) = FMns(6)
!	-------------------------- convert to beam coordinates
	Xn = MATMUL(D1k,Xn)
!	-------------------------- t-m-b coords
	Xt = MATMUL(AMat1,Xn)
!
	FMt1(1)		= Ft(1)
	FMt1(2)		= Ft(2)
	FMt1(3)		= Ft(3)
	FMt1(4)		= Xt(1)
	FMt1(5)		= Xt(2)
	FMt1(6)		= Xt(3)
!------------------------------------------ Direction 2 in beam coords for G matrix by beam formula
	Fn(1) = FMns(7)				
	Fn(2) = FMns(8)
	Fn(3) = FMns(9)
!	-------------------------- convert to beam coordinates
	Fn = MATMUL(D2b,Fn)
!	-------------------------- t-m-b coords
	Ft = MATMUL(AMat2,Fn)
!
	Xn(1) = FMns(10)
	Xn(2) = FMns(11)
	Xn(3) = FMns(12)
!	-------------------------- convert to beam coordinates
	Xn = MATMUL(D2k,Xn)
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
		if((iStep == 1).AND.(iNut == 2)) Then
			iPrt = 0
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
			call DumpRealArray(FMns,nE,"FMns",iPrt,iOut)
			call DumpRealArray(FMt1,nDof,"FMt1",iPrt,iOut)
			call DumpRealArray(FMt2,nDof,"FMt2",iPrt,iOut)
			call DumpStringVar("End:FormForMom",iPrt,iOut)
			iPrt = 0
		endif
!		-------------------------------------------------------- Debug : End
	if(bOpt1) then
	endif	
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Force-Moment in t-m-b Coords..."/2X,3(f20.7,1X))
	end
