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
	nQc		= 16
	nStifEL	= 32
	nStifS	= 56				! Singular
!------------------------------------------------------------------- Continuity
	iGeom	= 0 
!	------------
	iCont	= 0					! 0 = C0/1 = C1/ 2 = C2
!-------------------------------------------------
	if (iCont == 0) then
	!-----------------------------------
		nC		= 2
		nStifC  = nStifS - nC	! BC at r=0
	else if (iCont == 1) then
		nC		= 10			! 2 (at r=0) + 8 (at junction)
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
!	Nint	= 4		! Gauss Order
	Nint	= 16		! Gauss Order
!----------------------------------------------------
	OPEN(UNIT=10,FILE='c:\The Book\Gauss\det.dat')
	Iout	= 10	
!	IoDW	= 15	! I/O Default Write
!----------------------------------------------------
!
!	Stress-Strain Law
!
!----------------------------------------------------------------- DATA
!	NelType	= 1			! Plain Strain ( to compare w/ Hughes)
	NelType	= 0			! Plain Stress
	E		= 1.D0	 	
	PR		= 0.25D0	! Poisson's Ratio
	Thk		= 1.D0		! thickness
!-------------------------- Geometry
	xLx		= 19.D0		!		
	xUx		= 29.D0		!		
!-------------------------- 
	xLy		= 12.0D0
!-----------------------------------------------------------------
	write(iOut,1010) nStifS,iGeom,iCont,nC,nStifC,nSup,nStifN,Nint,
     &				Neltype
	write(iOut,1020) E,PR,Thk,xLx,xUx,xUx,xLx,xLy
!
!	Array sizes
!-------------------------------------------------------
!	nSzInt	= 4 !bytes
!	nSzDbl	= 8 !bytes
!	n1a		= 1								! Qc1(2,16)
!	n1b		= n1a + 2*nQc*nSzDbl				! Qc2(2,16)
!	n2		= n1b + 2*nQc*nSzDbl				! S(56,56) Singular / 2ELs(n2)
!	n2b		= n2  + nStifS*nStifS*nSzDbl	! S(32,32) Singular / 1ELs(n2b)
!	n4		= n2b + nStifEL*nStifEL*nSzDbl	! F(56) Singular(n4)
!	n5		= n4  + nStifS*nSzDbl			! Qd(4)
!	nEnd	= n5  + 4*nSzDbl				
!-------------------------------------------------------
	nSzInt	= 4 !bytes
	nSzDbl	= 8 !bytes
	n1a		= 1								! Qc1(2,16)
	n1b		= n1a + 2*nQc*nSzDbl				! Qc2(2,16)
	n2		= n1b + 2*nQc*nSzDbl				! S(56,56) Singular / 2ELs(n2)
	n2b		= n2  + nStifS*nStifS*nSzDbl		! S(32,32) Singular / 1ELs(n2b)
	n3a		= n2b + nStifEL*nStifEL*nSzDbl		! T(56,54) Constraint(n3a)
	n3b		= n3a + nStifS*nStifC*nSzDbl	! S(54,54) Singular (n3b) 
	n3		= n3b + nStifC*nStifC*nSzDbl	! S(51,51) Non-Sing (n3)
	n4		= n3 + nStifN*nStifN*nSzDbl		! F(56) (Sing/NonSing)
	n4b		= n4 + nStifS*nSzDbl			! F(54) (Cons)
	n5		= n4b + nStifS*nSzDbl		! Qd(4)
	nEnd	= n5 + 4*nSzDbl				
!-------------------------------------------------------
!
!	Set Bezier Coordinates 
!                                     
!-------------------------------------------------
	call BZ_Coords_EL1(A(n1a),2,nQc,xLx,xUx,xLy,iGeom,iOut)
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
	call BZ_Coords_EL2(A(n1b),2,nQc,xUx,xLx,xLy,iGeom,iOut)
!                                     ^     ^
!-------------------------------------|-----|--------
	call Quad_CC_STIF(A(n1b),Nel,NelType,Nint,E,PR,Thk,A(n2b),nStifEL,
     &					Iout,Trace)
!
!	Assemble 2nd Elem
!
	call FormIndexEl_2(A(n2c),nStifEL,iOut)
	call Assemble_Stif(A(n2c),A(n2b),nStifEL,A(n2),nStifS,Nel,
     & 													Iout,Trace)
!
!	initialize F = 0 for all 
!	Get Load Vector for Root side Extensional Load in X direction
!
	call Set_ExtLoad_X(A(n5),4,Iout)
	call Quad_CC_LVX(A(n5),A(n4),nStifS,xLx,xLy,Iout)
!
!	Get Load Vector for Shear Load at Both Ends 
!
	call Set_ExtLoad_Y(A(n5),4,Iout)
	call Quad_CC_LVY(A(n5),A(n4),nStifS,xLy,Iout)
!----------------------------------------------------------------------
!	displacement Controls:Qd
!
!--------------------------------------------------------------------
	n6		= nEnd
	n7		= n6 + nStifC*nStifC*nSzDbl
	nEnd	= n7 + nStifC*nSzDbl
!--------------------------------------------------------------------
!	C0_Condition
!--------------------------------------------------------------------
	if (iCont == 0) then
!
!	Form And Impose Constraints a for BC at r=0 section
!
		call FormBC_r0_ConMatrix(A(n3a),nStifS,nStifC)
		call Impose_BC_r0_Cons(A(n2),A(n4),nStifS,A(n3a),A(n3b),A(n4b),
     &														nStifC)
!
!	Add Supports: rigid body Out
!
		call Extract_NonSingularStif(A(n3b),nStifC,nStifC,A(n6),nStifN,
     &													iCont,iOut)
		call Extract_ContractedLoadVector(A(n4b),nStifC,A(n7),nStifN,
     &													iCont,iOut)
!	call Factor_Determinant(A(n3),A(n4),A(n6),A(n7),29,29,29)
		call Factor_ConditionNumber(A(n6),A(n2),A(n4),nStifN,
     &										nStifN,nStifN,iOut)
		call Solve_AxEqB(A(n6),A(n7),A(n4),nStifN,nStifN,iOut)
		call Compute_StrainEnergy(A(n6),A(n7),A(n4),nStifN,SEnergy,
     &												PEnergy,iOut)
!
!	Expand for Support
!
		call Expand_BezierDispControls_C0(A(n4),nStifN,A(n7),
     &										nStifC,iCont,iOut)
!
!	Expand for BC at r=0
!
		call Expand_BezierDispControls_C0_BCr0(A(n3a),nStifS,nStifC,
     &											A(n7),A(n4),iOut)
!------------------------------------------------------------------------
	end if
!--------------------------------------------------------------------
!	IMPOSE C1 Condition by transformation 
!	no consideration given to Transformation matrix being sparse
!--------------------------------------------------------------------
!
!--------------------------------------------------------------------
	n8		= nEnd
	n9		= n8 + nStifS*nStifC*nSzDbl
	nEnd	= n9 + nStifS*nSzDbl
!
	if (iCont == 1) then
		call FormTransformationMatrix_C1(A(n1a),A(n1b),nQc,A(n8),
     &											nStifS,nStifC,iOut)
		call Impose_Continuity(A(n2),A(n4),nStifS,A(n8),A(n6),A(n7)
     &												,nStifC,iOut)
!--------------------------------------------------------------------
!	IMPOSE C2 Condition by transformation 
!	no consideration given to Transformation matrix being sparse
!--------------------------------------------------------------------
	else if (iCont == 2) then
		stop ' need to change C2'
		call FormTransformationMatrix_C2(A(n8),nStifS,nStifC)
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
!
!	Add Supports: rigid body Out
!
		call Extract_NonSingularStif(A(n6),nStifC,nStifC,A(n2),nStifN,
     &													iCont,iOut)
		call Extract_ContractedLoadVector(A(n7),nStifC,A(n4),nStifN,
     &													iCont,iOut)
		call Factor_ConditionNumber(A(n2),A(n6),A(n7),nStifN,
     &										nStifN,nStifN,iOut)
		call Solve_AxEqB(A(n2),A(n4),A(n7),nStifN,nStifN,iOut)
		call Compute_StrainEnergy(A(n2),A(n4),A(n7),nStifN,SEnergy,
     &												PEnergy,iOut)
!
!	Expand for Support
!
		call Expand_BezierDispControls_C0(A(n7),nStifN,A(n4),nStifC,
     &												iCont,iOut)
!
!	Expand for BC at r=0 + C1
!
		call Expand_BezierDispControls_C1(A(n8),nStifS,nStifC,
     &											A(n4),A(n7),iOut)
	end if		
!
!
!	Compute Displacement
!
!	call Compute_Displacement(A(n4),16,2,1.D0,0.5D0,D,iOut)
!
	Stop 'OK'
 1010 Format(/ 5x,"Integer Controls"/
     &	2x,"Singular Stiffness Size    = ",I5/
     &	2x,"Inter-ElementControl Cn, n = ",I5,2x,"Geometry"/
     &	2x,"Inter-ElementControl Cn, n = ",I5,2x,"Displacement"/
     &	2x,"Inter-ElementControl Dofs  = ",I5/
     &	2x,"Constrained Stiffness Size = ",I5/
     &	2x,"No. of Supported Dofs      = ",I5/
     &	2x,"NonSingular Stiffness Size = ",I5/
     &	2x,"No. of Gauss-Legendre Pts. = ",I5/
     &	2x,"Element Type:              = ",I5/
     &	2x,"   Plane Stress = 0"/
     &	2x,"   Plane Strain = 1"/
     &	2x,"   Axisymmetric = 2"/
     &	)		
 1020 Format(/ 5x,"Real Controls"/
     &	2x,"Elasticity Modulus         = ",F10.5/
     &	2x,"Poisson's Ratio            = ",F10.5/
     &	2x,"Thickness                  = ",F10.5/
     &	2x,"Element#1: Lower_X         = ",F10.5/
     &	2x,"Element#1: Upper_X         = ",F10.5/
     &	2x,"Element#2: Lower_X         = ",F10.5/
     &	2x,"Element#2: Upper_X         = ",F10.5/
     &	2x,"Depth_Y                    = ",F10.5/
     &	)		
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
