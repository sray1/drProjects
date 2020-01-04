	Program Try_Quad_CC_WARP_YES
!
!	Try Coerced Isoparametric Quadrilateral_Quadratic_Cubic Element
!
!--------------------------------------------------------------------------------
!	Used:		Two Irregular Elements/ Plane strain
!	Reference:	paper by Ibrahimbegovic/ Hughes:p255
!	ExactSol.	Tip v = (PL^^3/3EI) + {(4+5*Nu)PL/2Eh} Timoshenko/Goodier,1951
!	Data		E=30000 Nu=.25 P=40 L=48 h=12
!	Exact		Tip v = .3553
!	Our Sol		Tip v =	.xxxx (xx%)
!-------------------------------------------------------------------------------- 		
!
!	Notes:	Nint should be atleast 2
!			nStifEL MUST be 24
!
!	Inputs
!		Qc(1,12)	= Bezier X-Coordinates
!					=	(qc00x qc10x...qc32x)
!		Qc(2,12)	= Bezier Y-Coordinates
!					=	(qc00y qc10y...qc32y)
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
!		Stif(24,24)	= Desired Stiffness Matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!
	common A(1000000)
!
!	Input Variables & Arrays
!
	Real(kind=8)	E,PR,Thk,xLx,xUx,xLy,Trace,DetNorm
	Real(kind=8)	xKnot0,xknot1,xKnot2,xLxTot	! C1 data
	integer			Nel,NelType,Iout,nStif,nStifEL
	integer			n1,n2
	real(kind = 8)	Disp
	dimension		Disp(2)
!		
!	
!	Output Variables & Arrays	
!
!	nStifActual = 48 - 6 (tie dofs between 2 Elements) = 56
	nDis	= 11	! loop for Disp. Computation
	nStr	= 11	! loop for Strain Computation
	nQc		= 12
	nStifEL	= 24
	nStifS	= 42				! Singular
!------------------------------------------------------------------- Continuity
	iGeom	= 0					! 0 = C0/1 = C1/ 2 = C2
	iCont	= 1					! 0 = C0/1 = C1/ 2 = C2
!-------------------------------------------------
	if (iCont == 0) then
		nC		= 0 
		nStifC  = nStifS - nC	! C0
		nSup	= 4
	else if (iCont == 1) then
		nC		= 6 
		nStifC  = nStifS - nC	! size Constrained:36 =42-6(interface dofs)
								! C1-continuity constraint at interface for 
								! interface Bez dofs (6 of them)
								! Working on the Singular stage
		nSup	= 4
	else if (iCont == 2) then
!	------------------------------------------------------------------------
		nC		= 12 
		nStifC  = nStifS - nC	! size Constrained:30 = 42-12(interface dofs)
								! C2-continuity constraint at interface for 
								! interface Bez dofs (12 of them)
								! Working on the Singular stage
		nSup	= 4
	end if
!---------------------------------------------------------------- Support Cond
	nStifN  = nStifC - nSup	! size NonSingular: 32 = 36 - 4( 3 supX + 1 SupY)
!-----------------------------------------------------------------------------
	Nint	= 4		! Gauss Order
	Nint	= 6		! Gauss Order
!----------------------------------------------------
	OPEN(UNIT=10,FILE='c:\The Book\Gauss\det.dat')
	Iout	= 10	
!	IoDW	= 15	! I/O Default Write
!----------------------------------------------------
!
!	Stress-Strain Law
!
!----------------------------------------------------------------- DATA
!	NelType	= 1			! Plain Strain
	NelType	= 0			! Plain Stress
	E		= 3.D4/40.D0	 	
!	E		= 1.D0	 	
	PR		= 0.25D0	! Poisson's Ratio
	Thk		= 1.D0		! thickness
!-------------------------- Geometry
	xLx		= 24.D0		! ALAWAYS MAKE xLx <= XUx ( for Coding that follows)		
	xUx		= 24.D0		!
!	--------------------- C1 Geometry Info.
	xKnot0	= 0.0D0
	xknot1	= 24.0D0
	xKnot2	= 48.0D0
	xLxTot	= 48.0D0	
!-------------------------- 
	xLy		= 12.0D0
!-----------------------------------------------------------------
	write(iOut,1010) nStifS,iGeom,iCont,nC,nStifC,nSup,
     &				nStifN,Nint,Neltype
	write(iOut,1020) E,PR,Thk,xLx,xUx,xUx,xLx,xLy
!-----------------------------------------------------------------
!	Array sizes
!
	nSzInt	= 4 !bytes
	nSzDbl	= 8 !bytes
	n1a		= 1								! Qc(2,12)
	n1b		= n1a + 2*nQc*nSzDbl				! Qc(2,12)
	n2		= n1b + 2*nQc*nSzDbl				! S(42,42) Singular / 2ELs(n2)
	n2b		= n2  + nStifS*nStifS*nSzDbl		! S(24,24) Singular / 1ELs(n2b)
	n4		= n2b + nStifEL*nStifEL*nSzDbl	! F(38) Singular(n4)
	n5		= n4  + nStifS*nSzDbl			! Qd(3)
	nEnd	= n5  + 3*nSzDbl
!----------------------------------------------------
!
!	Set Bezier Coordinates 
!
	Nel = 1
	call BZ_Coords_EL1(A(n1a),2,nQc,xLx,xUx,xLy,
     &				xKnot0,xknot1,xKnot2,xLxTot,iGeom,iOut)
!                                     ^      ^
!-------------------------------------|------|--------
!	Get Stiffness Matrix: Ist Elem 
!
	call Quad_QC_STIF(A(n1a),Nel,NelType,Nint,E,PR,Thk,A(n2b),
     &					nStifEL,Iout,Trace)
!
!	Assemble Ist Elem
!
	n2c		= nEnd
	nEnd	= n2c + nStifEL*nSzInt
	call Assemble_Stif(A(n2c),A(n2b),nStifEL,A(n2),nStifS,Nel,
     & 									Iout,Trace)
!-------------------------------------------------
	Nel = 2
	call BZ_Coords_EL2(A(n1b),2,nQc,xUx,xLx,xLy,
     &				xKnot0,xknot1,xKnot2,xLxTot,iGeom,iOut)
!-------------------------------------|-----|--------
!	Get Stiffness Matrix: 2nd Elem : 
!
	call Quad_QC_STIF(A(n1b),Nel,NelType,Nint,E,PR,Thk,A(n2b),
     &					nStifEL,Iout,Trace)
!---------------------------------------------------------------
!	Assemble 2nd Elem
!
	call FormIndexEl_2(A(n2c),nStifEL,iOut)
	call Assemble_Stif(A(n2c),A(n2b),nStifEL,A(n2),nStifS,Nel,
     & 									Iout,Trace)
!
!	Get Load Vector for Shear Load at End 
!
	call Set_ExtLoad(A(n5),3,Iout)
	call Quad_QC_LV(A(n5),A(n4),nStifS,xLy,Iout)
!
!	displacement Controls:Qd
!
!--------------------------------------------------------------------
	n6		= nEnd
	n7		= n6 + nStifC*nStifC*nSzDbl
	nEnd	= n7 + nStifC*nSzDbl
	n8		= nEnd
	n9		= n8 + nStifS*nStifC*nSzDbl
	nEnd	= n9 + nStifS*nSzDbl
!
!--------------------------------------------------------------------
!	C0_Condition
!--------------------------------------------------------------------
	if (iCont == 0) then
!-----------------------------------------------------------------------
		call Extract_NonSingularStif(A(n2),nStifC,nStifC,A(n6),nStifN,
     &													iCont,iOut)
		call Extract_ContractedLoadVector(A(n4),nStifC,A(n7),nStifN,
     &													iCont,iOut)
		call Factor_Determinant(A(n6),A(n2),A(n4),A(n9),nStifN,nStifN,
     &							nStifN,iOut)
		call Factor_ConditionNumber(A(n6),A(n2),A(n4),nStifN,
     &										nStifN,nStifN,iOut)
!----------------------------------------------
!	Eigenvalues of the stiffness matrix
		call Stiffness_EigenValues(nStifN,A(n6),A(n2),nStifN,
     &								A(n4),iOut)
!--------------------------------------------------------
		call Solve_AxEqB(A(n6),A(n7),A(n4),nStifN,nStifN,iOut)
		call Compute_StrainEnergy(A(n6),A(n7),A(n4),nStifN,SEnergy,
     &												PEnergy,iOut)
!	Expand for Support
!
		call Expand_BezierDispControls(A(n4),nStifN,A(n7),
     &										nStifC,iCont,iOut)
!-----------------------------------------------------------------------
!-----------------------------------------------------------------------
	end if
!--------------------------------------------------------------------
!	IMPOSE C1 Condition by transformation 
!	no consideration given to Transformation matrix being sparse
!--------------------------------------------------------------------
!--------------------------------------------------------------------
	if (iCont == 1) then
		call FormTransformationMatrix_C1(A(n1a),A(n1b),nQc,
     &							A(n8),nStifS,nStifC,iOut)
!		call FormTransformationMatrix_C1(A(n8),nStif,nStifC)
		call Impose_Continuity(A(n2),A(n4),nStifS,A(n8),A(n6),A(n7)
     &												,nStifC,iOut)
!--------------------------------------------------------------------
!	IMPOSE C2 Condition by transformation 
!	no consideration given to Transformation matrix being sparse
!--------------------------------------------------------------------
	else if (iCont == 2) then
		call FormTransformationMatrix_C2(A(n1a),A(n1b),nQc,
     &							A(n8),nStifS,nStifC,iOut)
!		call FormTransformationMatrix_C2(A(n8),nStifS,nStifC)
		call Impose_Continuity(A(n2),A(n4),nStifS,A(n8),A(n6),A(n7)
     &												,nStifC,iOut)
	end if
!--------------------------------------------------------------------
!	IMPOSE SUPPORT Conditions & make stiffnes Non-singular
!	PROBLEM SPECIFIC
!	Make NonSingular by dropping Row/Cols corresponding to Bndry Conds
!	Five fixity: Eqn. #s : 1,10,13
!-----------------------------------
	if (iCont == 1.OR.iCont == 2) then
		call Extract_NonSingularStif(A(n6),nStifC,nStifC,A(n2),nStifN,
     &													iCont,iOut)
		call Extract_ContractedLoadVector(A(n7),nStifC,A(n4),nStifN,
     &													iCont,iOut)
		call Factor_ConditionNumber(A(n2),A(n6),A(n7),nStifN,
     &										nStifN,nStifN,iOut)
!----------------------------------------------
!	Eigenvalues of the stiffness matrix
		call Stiffness_EigenValues(nStifN,A(n2),A(n6),nStifN,
     &								A(n7),iOut)
!--------------------------------------------------------
		call Solve_AxEqB(A(n2),A(n4),A(n7),nStifN,nStifN,iOut)
		call Compute_StrainEnergy(A(n2),A(n4),A(n7),nStifN,SEnergy,
     &												PEnergy,iOut)
		call Expand_BezierDispControls(A(n7),nStifN,A(n4),nStifC,
     &												iCont,iOut)
		call Expand_BezierDispControls_C1(A(n8),nStifS,nStifC,
     &											A(n4),A(n7),iOut)
	end if	
!
!	Extract Element 1 Controls & Evaluate Disp./Strains/Stresses
!
	call Extract_DispCon(A(n7),nStifS,A(n4),nStifEL,1,iOut)
	call QC_Disps_EL(A(n4),nStifEL,nDis,1,NelType,Iout)
	call QC_Strains_EL
     &	(E,PR,Thk,A(n1a),nQc,A(n4),nStifEL,nStr,1,NelType,Iout)
!
!	Extract Element 2 Controls & Evaluate Disp./Strains/Stresses
!
	call Extract_DispCon(A(n7),nStifS,A(n4),nStifEL,2,iOut)
	call QC_Disps_EL(A(n4),nStifEL,nDis,2,NelType,Iout)
	call QC_Strains_EL
     &	(E,PR,Thk,A(n1b),nQc,A(n4),nStifEL,nStr,2,NelType,Iout)
!
!
	Stop 'OK'
 1010 Format(/ 5x,"Integer Controls"/
     &	2x,"Singular Stiffness Size    = ",I5/
     &	2x,"Inter-ElementGeom.   Cn, n = ",I5,2x,"Geometry"/
     &	2x,"Inter-ElementDisp    Cn, n = ",I5,2x,"Displacement"/
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
