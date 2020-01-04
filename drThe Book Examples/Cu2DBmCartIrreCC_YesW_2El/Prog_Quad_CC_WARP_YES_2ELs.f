	Program Try_Quad_CC_WARP_YES
!
!	Try Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!--------------------------------------------------------------------------------
!	Used:		Two Elements/ Plane strain
!	Reference:	paper by Ibrahimbegovic
!	ExactSol.	Tip v = (PL^^3/3EI) + {(4+5*Nu)PL/2Eh} Timoshenko/Goodier,1951
!	Data		E=30000 Nu=.25 P=40 L=48 h=12
!	Exact		Tip v = .3553
!	Our Sol		Tip v =	.xxxx (xx%)
!-------------------------------------------------------------------------------- 		
!
!	Notes:	Nint should be atleast 2
!			nStif MUST be 64
!
!	Inputs
!		Qc(1,16)	= Bezier X-Coordinates
!					=	(qc00x qc10x...qc33x)
!		Qc(2,16)	= Bezier Y-Coordinates
!					=	(qc00y qc10y...qc33y)
!		Nel			= Element Number
!		NelType		= Element Type:
!						0 = Plane Stress
!						1 = Plane Strain
!						2 = Axi-symmtric	(NOT DONE YET)
!		Nint		= Number of Gauss Points
!		E			= Elasticity Modulus
!		PR			= Poisson's ratio
!		Thk			= Thickness
!		nStif		= Row or Col size of Stiffness matrix ( MUST BE 32)
!		Iout		= Error Output file#
!		Stif(32,32)	= Desired Stiffness Matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!
	common A(1000000)
!
!	Input Variables & Arrays
!
	Real(kind=8)	E,PR,Thk,xLx,xUx,xLy,Trace
	integer			Nel,NelType,Iout,nStif,nStifEL
	integer			n1a,n1b,n2
	real(kind = 8)	Disp
	dimension		Disp(2)
!		
!	
!	Output Variables & Arrays	
!
!	nStifActual = 64 - 8 (tie dofs between 2 Elements) = 56
	nStifEL	= 32
	nStifS	= 56				! Singular
!------------------------------------------------------------------- Continuity
	iCont	= 0					! 0 = C0/1 = C1/ 2 = C2
!-------------------------------------------------
	if (iCont == 0) then
	!-----------------------------------
!		nConBC	= 2
!		nStifC  = nStifS - nConBC	! C0
	!-----------------------------------
		nC		= 0
		nStifC  = nStifS - nC	! C0
	else if (iCont == 1) then
		nC		= 8 
		nStifC  = nStifS - nC	! size Constrained:48 =56-8(interface dofs)
								! C1-continuity constraint at interface for 
								! interface Bez dofs (8 of them)
								! Working on the Nonsingular stage
	else if (iCont == 2) then
!	------------------------------------------------------------------------
		nC		= 16 
		nStifC  = nStifS - nC	! size Constrained:37 = 53-16(interface dofs)
								! C2-continuity constraint at interface for 
								! interface Bez dofs (16 of them)
								! Working on the Nonsingular stage
	end if
!---------------------------------------------------------------- Support Cond
	nSup	= 3
	nStifN  = nStifC - nSup	! size NonSingular: yy = xx - 3( 2 supX + 1 SupY)
!-----------------------------------------------------------------------------
	Nint	= 4		! Gauss Order
!	Nint	= 16		! Gauss Order
	IoDW	= 15	! I/O Default Write
!
!	Stress-Strain Law
!
!----------------------------------------------------------------- DATA
!	NelType	= 1			! Plain Strain ( to compare w/ Hughes)
	NelType	= 0			! Plain Stress
	E		= 1.D0	 	
	PR		= 0.25D0	! Poisson's Ratio
	Thk		= 1.D0		! thickness
!-------------------------- not needed, they're getting hardcoded
	xLx		= 0.D0		!		
	xUx		= 0.D0		!		
!-------------------------- not needed end
	xLy		= 1.0D0
!-----------------------------------------------------------------
!
!	Array sizes
!
	nSzInt	= 4 !bytes
	nSzDbl	= 8 !bytes
	n1a		= 1								! Qc1(2,16)
	n1b		= n1a + 2*16*nSzDbl				! Qc2(2,16)
	n2		= n1b + 2*16*nSzDbl				! S(56,56) Singular / 2ELs(n2)
	n2b		= n2  + nStifS*nStifS*nSzDbl	! S(32,32) Singular / 1ELs(n2b)
	n4		= n2b + nStifEL*nStifEL*nSzDbl	! F(56) Singular(n4)
	n5		= n4  + nStifS*nSzDbl			! Qd(4)
	nEnd	= n5  + 4*nSzDbl				
!-------------------------------------------------------
!	nSzInt	= 4 !bytes
!	nSzDbl	= 8 !bytes
!	n1a		= 1								! Qc1(2,16)
!	n1b		= n1a + 2*16*nSzDbl				! Qc2(2,16)
!	n2		= n1b + 2*16*nSzDbl				! S(56,56) Singular / 2ELs(n2)
!	n2b		= n2  + nStifS*nStifS*nSzDbl		! S(32,32) Singular / 1ELs(n2b)
!	n3a		= n2b + nStifEL*nStifEL*nSzDbl		! T(56,54) Constraint(n3a)
!	n3b		= n3a + nStifS*nStifC*nSzDbl	! S(54,54) Singular (n3b) 
!	n3		= n3b + nStifC*nStifC*nSzDbl	! S(51,51) Non-Sing (n3)
!	n4		= n3 + nStifN*nStifN*nSzDbl		! F(56) (Sing/NonSing)
!	n4b		= n4 + nStifS*nSzDbl			! F(54) (Cons)
!	n5		= n4b + nStifS*nSzDbl		! Qd(4)
!	nEnd	= n5 + 4*nSzDbl				
!-------------------------------------------------------
!
!	Set Bezier Coordinates 
!                                     
!-------------------------------------------------
	call BZ_Coords_EL1(A(n1a),2,16,20.0D0,50.0D0,xLy)
!                                     ^      ^
!-------------------------------------|------|--------
!	Get Stiffness Matrix: Ist Elem 
!
	Nel = 1
	call Quad_CC_STIF(A(n1a),Nel,NelType,Nint,E,PR,Thk,A(n2b),nStifEL,
     &					Iout,Trace)
!
!	Assemble Ist Elem
!
	n2c		= nEnd
	nEnd	= n2c + nStifEL*nSzInt
	call Assemble_Stif(A(n2c),A(n2b),nStifEL,A(n2),nStifS,Nel,
     & 													Iout,Trace)
!
!	Get Stiffness Matrix: 2nd Elem : 
!
	Nel = 2
!-------------------------------------------------
	call BZ_Coords_EL2(A(n1b),2,16,80.0D0,50.0D0,xLy)
!                                     ^     ^
!-------------------------------------|-----|--------
	call Quad_CC_STIF(A(n1b),Nel,NelType,Nint,E,PR,Thk,A(n2b),nStifEL,
     &					Iout,Trace)
!
!	Assemble 2nd Elem
!
	call FormIndexEl_2(A(n2c),nStifEL)
	call Assemble_Stif(A(n2c),A(n2b),nStifEL,A(n2),nStifS,Nel,
     & 													Iout,Trace)
!
!	Get Load Vector for Root side Extensional Load in X direction
!	Also initialize F = 0 all first
!
	call Set_ExtLoad_X(A(n5),4)
	call Quad_CC_LVX(A(n5),A(n4),nStifS,xLx,xLy)
!
!	Get Load Vector for Shear Load at Both Ends 
!
	call Set_ExtLoad_Y(A(n5),4)
	call Quad_CC_LVY(A(n5),A(n4),nStifS,xLy)
!---------------------------------------------------------------------
!	Form And Impose Constraints a for BC at r=0 section
!	call FormBC_r0_ConMatrix(A(n3a),nStifS,nStifC)
!	call Impose_BC_r0_Cons(A(n2),A(n4),nStifS,A(n3a),A(n3b),A(n4b),
!    &														nStifC)
!----------------------------------------------------------------------
!	displacement Controls:Qd
!
!--------------------------------------------------------------------
	n6		= nEnd
	n7		= n6 + nStifC*nStifC*nSzDbl
	nEnd	= n7 + nStifC*nSzDbl
!
!--------------------------------------------------------------------
!	C0_Condition
!--------------------------------------------------------------------
	if (iCont == 0) then
		call Extract_NonSingularStif(A(n2),nStifC,nStifC,A(n6),nStifN,
     &														iCont)
		call Extract_ContractedLoadVector(A(n4),nStifC,A(n7),nStifN,
     &														iCont)
!	call Factor_Determinant(A(n3),A(n4),A(n6),A(n7),29,29,29)
		call Factor_ConditionNumber(A(n6),A(n2),A(n4),nStifN,
     &										nStifN,nStifN)
		call Solve_AxEqB(A(n6),A(n7),A(n4),nStifN,nStifN)
		call Compute_StrainEnergy(A(n6),A(n7),A(n4),nStifN,SEnergy,
     &														PEnergy)
!-----------------------------------------------------------------------
!		call Extract_NonSingularStif(A(n3b),nStifC,nStifC,A(n3),nStifN,
!     &														iCont)
!		call Extract_ContractedLoadVector(A(n4b),nStifC,A(n4b),nStifN,
!     &														iCont)
!	call Factor_Determinant(A(n3),A(n4),A(n6),A(n7),29,29,29)
!		call Factor_ConditionNumber(A(n3),A(n6),A(n7),nStifN,
!     &										nStifN,nStifN)
!		call Solve_AxEqB(A(n3),A(n4b),A(n7),nStifN,nStifN)
!		call Compute_StrainEnergy(A(n3),A(n7),A(n4),nStifN,SEnergy,
!     &														PEnergy)
!------------------------------------------------------------------------
	end if
!--------------------------------------------------------------------
!	IMPOSE C1 Condition by transformation 
!	no consideration given to Transformation matrix being sparse
!--------------------------------------------------------------------
		n8		= nEnd
		n9		= n8 + nStif*nStifC*nSzDbl
		nEnd	= n9 + nStif*nSzDbl
!--------------------------------------------------------------------
	if (iCont == 1) then
		call FormTransformationMatrix_C1(A(n8),nStif,nStifC)
		call Impose_Continuity(A(n2),A(n4),nStif,A(n8),A(n6),A(n7)
     &														,nStifC)
!--------------------------------------------------------------------
!	IMPOSE C2 Condition by transformation 
!	no consideration given to Transformation matrix being sparse
!--------------------------------------------------------------------
	else if (iCont == 2) then
		stop ' need to change C2'
		call FormTransformationMatrix_C2(A(n8),nStif,nStifC)
		call Impose_Continuity(A(n2),A(n4),nStifN,A(n8),A(n6),A(n7)
     &														,nStifC)
	end if
!--------------------------------------------------------------------
!	IMPOSE SUPPORT Conditions & make stiffnes Non-singular
!	PROBLEM SPECIFIC
!	Make NonSingular by dropping Row/Cols corresponding to Bndry Conds
!	Five fixity: Eqn. #s : 1,10,13
!-----------------------------------
	if (iCont == 1.OR.iCont == 2) then
		call Extract_NonSingularStif(A(n6),nStifC,nStifC,A(n2),nStifN,
     &														iCont)
		call Extract_ContractedLoadVector(A(n7),nStifC,A(n4),nStifN,
     &														iCont)
		call Factor_ConditionNumber(A(n2),A(n6),A(n7),nStifN,
     &										nStifN,nStifN)
		call Solve_AxEqB(A(n2),A(n4),A(n7),nStifN,nStifN)
		call Compute_StrainEnergy(A(n2),A(n4),A(n7),nStifN,SEnergy,
     &														PEnergy)
	end if		
!------------------------------------------------------------------------
! OR
!	call AddSupport_Stif(A(n2),32,32,Trace)
!	call MultSupport_Load(A(n4),32,Trace)
!	call Solve_AxEqB(A(n2),A(n4),A(n6),32,32)
	call Expand_BezierDispControls(A(n4),nStifN,A(n7),nStifS)
!
!	Compute Displacement
!
	call Compute_Displacement(A(n4),16,2,1.D0,0.5D0,D)
!
	Stop 'OK'
	end 
!
	Subroutine BZ_Coords_EL1(Qc,nR,nC,xLx,xUx,xLy)
!	xLx=16/xUx=32	
	Implicit Real(kind=8) (a-h,o-z)
	real(kind = 8)	Qc
	Dimension		Qc(nR,nC)
	real(kind = 8)	xLx,xUx,xLy,xLy3,x2Ly3,aa
	integer			nR,nC
!
	Qc			= 0.			! zero all
!---------------------- C0
	Qc(1,1)		= 0.0
	Qc(1,2)		= xLx/3.
	Qc(1,3)		= 2.*xLx/3.
	Qc(1,4)		= xLx
!---------------------- C2
!	Qc(1,2)		= 4.0
!	Qc(1,3)		= 8.0
!----------------------- C1
!	Qc(1,2)		= 8.0D0/3.0D0
!	Qc(1,3)		= 8.0
!----------------------
!	Qc(1,4)		= xLx
!-----------------------------
!	redefine for equal tangent length
!------------------------------------------
!	Qc(1,3)		= 2.*16.D0/3.D0
!-----------------------------
!
	aa			= xLx + (xUx - xLx)/3.
!---------------------- C0
	Qc(1,5)		= 0.0
	Qc(1,6)		= aa/3.
	Qc(1,7)		= 2.*aa/3.
	Qc(1,8)		= aa
!----------------------- Zero Twist Override
!	Qc(1,6)		= 16.0D0/3.0D0
!	Qc(1,7)		= 16.0D0
!---------------------- C2
!	Qc(1,6)		= 6.0
!	Qc(1,7)		= aa - 8.0
!---------------------- C1
!	Qc(1,6)		= 56.0D0/9.0D0
!	Qc(1,7)		= aa - 8.0
!	Qc(1,8)		= aa
!-----------------------------
!	redefine for equal tangent length
!------------------------------------------
!	Qc(1,7)		= 2.*(16.D0+ 16.D0/3.D0)/3.D0
!-----------------------------
!
	aa			= xLx + 2.*(xUx - xLx)/3.
!------------------------------ C0
	Qc(1,9)		= 0.0
	Qc(1,10)	= aa/3.
	Qc(1,11)	= 2.*aa/3.
	Qc(1,12)	= aa
!----------------------- Zero Twist Override
!	Qc(1,10)	= 32.0D0/3.0D0
!	Qc(1,11)	= 16.0D0
!---------------------- C2
!	Qc(1,10)	= 8.0
!	Qc(1,11)	= aa - 8.0
!---------------------- C1
!	Qc(1,10)	= 88.0D0/9.0D0
!	Qc(1,11)	= aa - 8.0
!----------------------
!	Qc(1,12)	= aa
!-----------------------------
!	redefine for equal tangent length
!------------------------------------------
!	Qc(1,11)	= Qc(1,12) - (16.D0+ 16.D0/3.D0)/3.D0
!-----------------------------
!
!------------------------------ C0
	Qc(1,13)	= 0.0
	Qc(1,14)	= xUx/3.
	Qc(1,15)	= 2.*xUx/3.
	Qc(1,16)	= xUx
!---------------------- C2
!	Qc(1,14)	= 12.0
!	Qc(1,15)	= xUx - 8.0
!---------------------- C1
!	Qc(1,14)	= 40.0D0/3.0D0
!	Qc(1,15)	= xUx - 8.0
!----------------------
!	Qc(1,16)	= xUx
!-----------------------------
!	redefine for equal tangent length
!------------------------------------------
!	Qc(1,15)	= (32.D0- 16.D0/3.D0)
!-----------------------------
!
	xLy3		= xLy/3.
	x2Ly3		= 2.*xLy3
!
!	Qc(2,1)		= 0.
!	Qc(2,2)		= 0.
!	Qc(2,3)		= 0.
!	Qc(2,4)		= 0
!
	Qc(2,5)		= xLy3
	Qc(2,6)		= xLy3
	Qc(2,7)		= xLy3
	Qc(2,8)		= xLy3

!
	Qc(2,9)		= x2Ly3
	Qc(2,10)	= x2Ly3
	Qc(2,11)	= x2Ly3
	Qc(2,12)	= x2Ly3

!
	Qc(2,13)	= xLy
	Qc(2,14)	= xLy
	Qc(2,15)	= xLy
	Qc(2,16)	= xLy
  100 continue
!
	return
	end
	
!
	Subroutine BZ_Coords_EL2(Qc,nR,nC,xLx,xUx,xLy)
	
	Implicit Real(kind=8) (a-h,o-z)
	real(kind = 8)	Qc
	Dimension		Qc(nR,nC)
	real(kind = 8)	xLx,xUx,xLy,xLy3,x2Ly3,bb,aa
	integer			nR,nC
!
	Qc			= 0.			! zero all
!
!------------------------------ C0
	Qc(1,1)		= 0.0
	Qc(1,2)		= xLx/3.
	Qc(1,3)		= 2.*xLx/3.
	Qc(1,4)		= xLx
!---------------------- C2
!	Qc(1,2)		= 8.0
!	Qc(1,3)		= 20.0
!---------------------- C1
!	Qc(1,2)		= 8.0
!	Qc(1,3)		= 56.0D0/3.0D0
!----------------------
!	Qc(1,4)		= xLx
!-----------------------------
!	redefine for equal tangent length
!------------------------------------------
!	Qc(1,2)		= 16.D0/3.D0
!-----------------------------
!
!------------------------------ 
	bb			= (xLx - xUx)/3.
	aa			= xLx - bb 
!------------------------------ C0
	Qc(1,5)		= bb
	Qc(1,6)		= bb + aa/3.
	Qc(1,7)		= bb + 2.*aa/3.
	Qc(1,8)		= bb + aa
!----------------------- Zero Twist Override
!	Qc(1,6)		= 16.0D0
!	Qc(1,7)		= 32.0D0-(32.0D0/3.0D0)
!---------------------- C2
!	Qc(1,5)		= bb
!	Qc(1,6)		= bb + 8.0
!	Qc(1,7)		= 24.0
!---------------------- C1
!	Qc(1,5)		= bb
!	Qc(1,6)		= bb + 8.0
!	Qc(1,7)		= 200.0D0/9.0D0
!----------------------
!	Qc(1,8)		= xLx
!-----------------------------
!	redefine for equal tangent length
!------------------------------------------
!	Qc(1,6)		= Qc(1,5) + (16.D0+ 16.D0/3.D0)/3.D0
!-----------------------------
!
!------------------------------
	bb			= 2.*(xLx - xUx)/3.
	aa			= xLx - bb 
!------------------------------  C0
	Qc(1,9)		= bb
	Qc(1,10)	= bb + aa/3.
	Qc(1,11)	= bb + 2.*aa/3.
	Qc(1,12)	= bb + aa
!----------------------- Zero Twist Override
!	Qc(1,10)	= 16.0D0
!	Qc(1,11)	= 32.0D0-(16.0D0/3.0D0)
!---------------------- C2
!	Qc(1,9)		= bb
!	Qc(1,10)	= bb + 8.0
!	Qc(1,11)	= 26.0
!---------------------- C1
!	Qc(1,9)		= bb
!	Qc(1,10)	= bb + 8.0
!	Qc(1,11)	= 232.0D0/9.0D0
!----------------------
!	Qc(1,12)	= xLx
!-----------------------------
!	redefine for equal tangent length
!------------------------------------------
!	Qc(1,10)	= Qc(1,9) + (16.D0+ 16.D0/3.D0)/3.D0
!-----------------------------
	bb			= (xLx - xUx)
	aa			= xLx - bb 
!------------------------------ C0
	Qc(1,13)	= bb
	Qc(1,14)	= bb + xUx/3.
	Qc(1,15)	= bb + 2.*xUx/3.
	Qc(1,16)	= bb + xUx
!---------------------- C2
!	Qc(1,13)	= bb
!	Qc(1,14)	= bb + 8.0
!	Qc(1,15)	= xLx - 4.0
!---------------------- C1
!	Qc(1,13)	= bb
!	Qc(1,14)	= bb + 8.0
!	Qc(1,15)	= xLx - 8.0D0/3.0D0
!-----------------------
!	Qc(1,16)	= xLx
!-----------------------------
!	redefine for equal tangent length
!------------------------------------------
!	Qc(1,14)	= Qc(1,13) + 16.D0/3.D0
!-----------------------------

	xLy3		= xLy/3.
	x2Ly3		= 2.*xLy3
!
!	Qc(2,1)		= 0.
!	Qc(2,2)		= 0.
!	Qc(2,3)		= 0.
!	Qc(2,4)		= 0
!
	Qc(2,5)		= xLy3
	Qc(2,6)		= xLy3
	Qc(2,7)		= xLy3
	Qc(2,8)		= xLy3

!
	Qc(2,9)		= x2Ly3
	Qc(2,10)	= x2Ly3
	Qc(2,11)	= x2Ly3
	Qc(2,12)	= x2Ly3

!
	Qc(2,13)	= xLy
	Qc(2,14)	= xLy
	Qc(2,15)	= xLy
	Qc(2,16)	= xLy
  100 continue
!
	return
	end
	
	Subroutine Set_ExtLoad_X(Qf,nDim)
	
	real(kind = 8)	Qf
	Dimension		Qf(nDim)
!	
	Qf(1)	= +3.0
	Qf(2)	= +1.0
	Qf(3)	= -1.0
	Qf(4)	= -3.0
!
	return
	end
!	  			
	Subroutine Set_ExtLoad_Y(Qf,nDim)
	
	real(kind = 8)	Qf
	Dimension		Qf(nDim)
!	
	Qf		= 0.		! All Zero
	Qf(2)	= 1.0
	Qf(3)	= 1.0
!
	return
	end
!	  			
	Subroutine AddSupport_Stif(Ss,nSsI,nSsJ,Trace)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM
!	EQUATIONS 1,13,17 diagonals add Joint Stif
!
	real(kind = 8)	Ss           ,Trace,DiaStif
	Dimension		Ss(nSsI,nSsJ)
!
!	Add Joint Stiffness = 1000*Trace
!
	DiaStif = 1000000.* Trace
!
	Ss(1,1)		= Ss(1,1) + DiaStif 	
	Ss(13,13)	= Ss(13,13) + DiaStif 	
	Ss(17,17)	= Ss(17,17) + DiaStif 
!
	return
	end
!
!	  			
	Subroutine MultSupport_Load(F,nF,Trace)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM
!	EQUATIONS 1,13,17 diagonals add Joint Stif
!
	real(kind = 8)	F           ,Trace,FJoint
	Dimension		F(nF)
!
!	Multiply Joint Pseudo Load = 1000*Trace
!
	FJoint = 1000000.* Trace
!
	F(1)	= F(1)	* FJoint 	
	F(13)	= F(13) * FJoint 	
	F(17)	= F(17) * FJoint 
!
	return
	end
!
!			
	Subroutine Extract_NonSingularStif(Ss,nSs,nStif,Sn,nSn,iCont)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM
!
!	for Loop: nStif	
!	nSsI,nSsJ are dimensions
!	Ss(nSs,nSs)		= Stiffness-Singular Matrix (INPUT)	
!	Sn(nSn,nSn)		= Stiffness-NonSingular Matrix (OUTPUT)
!
	real(kind = 8)	Sn           ,Ss
	Dimension		Sn(nSn,nSn),Ss(nSs,nSs)
	real(kind = 8)	sum,Add(nSn)
!
!
	integer i,j,ii,jj
!
	integer			Drop   ,DropC0   ,DropC1   ,DropC2
!	Dimension		Drop(5),DropC0(5),DropC1(5),DropC2(5)	
	Dimension		Drop(3),DropC0(3),DropC1(3),DropC2(3)	
!	DATA DropC0 / 1,5,9,13,17/
!	DATA DropC1 / 1,4,7,10,13/
!---------------------------
!	DATA DropC0 / 1,12,16/ ! for r0BC constraints
!---------------------------
	DATA DropC0 / 1,13,17/
!	DATA DropC1 / 1,10,13/
!	DATA DropC2 / 1,4,7,10,13/
!	DATA nDrop/5/
	DATA nDrop/3/
!
!------------------------------ Initialize
	if( iCont == 0) Then
		do 5 k = 1,nDrop
		Drop(k) = DropC0(k)
    5		continue
	else if( iCont == 1) Then 
		do 6 k = 1,nDrop
		Drop(k) = DropC1(k)
    6		continue
	end if
!------------------------------
!	ii = 0
	jj = 0	
	do 40 j = 1,nStif
	do 10 k = 1,nDrop
	if(j == Drop(k)) then
		go to 40
	end if
   10	continue
	jj = jj+1
!
	ii = 0
	do 30 i = 1,nStif
!
	do 20 k = 1,nDrop
	if(i == Drop(k)) then
		go to 30
	end if
   20	continue
!
	ii = ii+1
	Sn(ii,jj) = Ss(i,j)
   30 continue
   40 continue
!
!	Check each col. vector for NOT Null
!
	Add = 0.D0
	do 70 j = 1,nSn
	sum = 0.0D0 
	do 60 i = 1,nSn	
	sum = sum + Sn(i,j)
   60 continue
	Add(j) = sum
   70 continue			
  100	continue
!--------------------------------------------------------------
!	OPEN (unit = 15, FILE = 'Stiffness.prt', STATUS = 'NEW')
!	do 110 i = 1,nSn
!	write(15,1010) nSn,nSn,i,(Sn(i,j),j = 1,nSn)
!  110	continue
!--------------------------------------------------------------
!
 1010 format("Reduced Stiffness Matrix:Stif(",I3,",",I3,")"/
     &        I5/(6(8(f10.6,1X)/)/))
	return
	end

	Subroutine Extract_ContractedLoadVector(Ff,nFf,Fc,nFc,iCont)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM
!	EQUATIONS 1,13,17 Rows NEED TO GO
!
!	Ff(nFf)		= Full Load Vector (INPUT)	
!	Fc(nFc)		= Contracted Load Vector (OUTPUT)
!
	real(kind = 8)	Ff     ,Fc
	Dimension		Ff(nFf),Fc(nFc)
!
!
	integer i,ii
!
	integer			Drop   ,DropC0   ,DropC1   ,DropC2
!	Dimension		Drop(5),DropC0(5),DropC1(5),DropC2(5)	
	Dimension		Drop(3),DropC0(3),DropC1(3),DropC2(3)	
!	DATA DropC0 / 1,5,9,13,17/
!	DATA DropC1 / 1,4,7,10,13/
!---------------------------
!	DATA DropC0 / 1,12,16/ ! for r0BC constraints
!---------------------------
	DATA DropC0 / 1,13,17/
!	DATA DropC1 / 1,10,13/
!	DATA DropC2 / 1,4,7,10,13/
	DATA nDrop/3/
!	DATA nDrop/5/
!
!------------------------------ Initialize
	if( iCont == 0) Then
		do 5 k = 1,nDrop
		Drop(k) = DropC0(k)
    5		continue
	else if( iCont == 1) Then 
		do 6 k = 1,nDrop
		Drop(k) = DropC1(k)
    6		continue
	end if
!------------------------------
!
	ii = 0
!			
	do 20 i = 1,nFf
	do 10 k = 1,nDrop
	if(i == Drop(k)) then
		go to 20
	end if
   10	continue
	ii = ii + 1
!
	Fc(ii) = Ff(i)
   20 continue
!
	return
	end
!
	Subroutine Expand_BezierDispControls(Xc,nXc,Xf,nXf)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM
!	EQUATIONS 1,13,17 Rows include = 0.0
!
!	Xc(nXc)		= Solved Bezier Displacement Controls (Input)
!	Xf(nFf)		= Full Bezier Displacement Controls (Output)	
!
	real(kind = 8)	Xf     ,Xc
	Dimension		Xf(nXf),Xc(nXc)
!
!
	integer i,ii
!
	integer			Drop
	Dimension		Drop(3)	
	DATA Drop / 1,13,17/
!
	Xf = 0.0	! initialize
	ii = 0
!			
	do 20 i = 1,nXf
	do 10 k = 1,3
	if(i == Drop(k)) then
		go to 20
	end if
   10	continue
	ii = ii + 1
!
	Xf(i) = Xc(ii)
   20 continue
!
	return
	end
!
	Subroutine Compute_Displacement(Xf,nRow,nCol,R,S,D)
!
!	Xf(nRow=32,nCol=2)		= Full Bezier Displacement Controls (Output)	
!
	real(kind = 8)	Xf			 ,D	    
	Dimension		Xf(nRow,nCol),D(2)
	real(kind = 8)	R,S,DX,DY
	integer			nRow,nCol     
!
	real(kind = 8)	sum
	integer			i,j,k     
!
	Real(kind=8)	Br   ,Bs
	Dimension		Br(4),Bs(4)
!	
!	Define Bernstein Interpolations
!
	Br(1) = (1.-r)*(1.-r)*(1.-r)
	Br(2) = 3.*(1.-r)*(1.-r)*r
	Br(3) = 3.*(1.-r)*r*r
	Br(4) = r*r*r
!	 
	Bs(1) = (1.-s)*(1.-s)*(1.-s)
	Bs(2) = 3.*(1.-s)*(1.-s)*s
	Bs(3) = 3.*(1.-s)*s*s
	Bs(4) = s*s*s
!	
	do 20 l = 1,2
	sum = 0.0
	do 10 k = 1,nRow
	i = modulo(k,4)
	if(i == 0) then
		i = 4
	endif
	j = (k-1)/4 + 1
!
	sum = sum + Br(i)*Bs(j)*Xf(k,l)
!
   10 continue
	D(l) = sum
   20 continue
!
	return
	end   			 			  			  			  		