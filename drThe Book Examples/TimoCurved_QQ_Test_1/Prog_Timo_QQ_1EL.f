	Program Timo_QQ_Test1_1EL
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
!		Qc(1,NN)	= Bezier X-Coordinates
!					=	(qc00x qc10x...qcNNx)
!		Qc(2,NN)	= Bezier Y-Coordinates
!					=	(qc00y qc10y...qcNNy)
!		Nel			= Element Number
!		NelType		= Element Type:
!						0 = Plane Stress
!						1 = Plane Strain
!						2 = Axi-symmtric	(NOT DONE YET)
!		Nint		= Number of Gauss Points
!		E			= Elasticity Modulus
!		PR			= Poisson's ratio
!		Thk			= Thickness
!		nStif		= Row or Col size of Stiffness matrix ( MUST BE NN)
!		Iout		= Error Output file#
!		Stif(NN,NN)	= Desired Stiffness Matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!
	common A(1000000)
!
!	Input Variables & Arrays
!
	Real(kind=8)	E,G,PR,RADIUS,DEPTH,WIDTH,Trace
	integer			Nel,NelType,Iout,nStif,nStifEL
	integer			n1a,n1b,n2
	real(kind = 8)	Disp   ,wc,uc,tc
	dimension		Disp(2)
!---------------------------
!		
!	
!	Output Variables & Arrays	
!
	nDis	= 49	! for Print Loop
	nStr	= 49	! for Print Loop
!----------------------------------------------------
	OPEN(UNIT=10,FILE='c:\The Book Examples\Gauss\det.dat')
	Iout	= 10	
!------------------------------------------------------------------- Continuity
	iGeom	= 0 
	iCont	= 0					! 0 = C0/1 = C1/ 2 = C2
	nQc		= 5					! 5 = Quartic/ 6 = Quintic
	nStifEL	=  3*nQc 
	Nint	=  nQc-1			! Gauss Order
!	Nint	=  nQc  			! Gauss Order
!	Nint	= 16				! Gauss Order
!	------------------------------
	write(iOut,1000) nStifEL
!	------------------------
	call Initiate_DegreeData(nStifS,nLoadLoc,iOut,nQc)
!-------------------------------------------------
	if (iCont == 0) then
		nC		= 0
		nStifC  = nStifS - nC	! BC at r=0
	else if (iCont == 1) then
		nC		= 2				! 2 (w & u at junction)
		nStifC  = nStifS - nC	! size Constrained:
								! Working on the Nonsingular stage
	else if (iCont == 2) then
!	------------------------------------------------------------------------
		nC		= 6 
		nStifC  = nStifS - nC	! size Constrained:
								! Working on the Nonsingular stage
	end if
!---------------------------------------------------------------- Support Cond
	nSup	= 3
	nStifN  = nStifC - nSup		! size NonSingular: Sing - 4(2supU+2SupTheta)
!----------------------------------------------------
!
!	Stress-Strain Law
!
!----------------------------------------------------------------- DATA
!	NelType	= 1			! Plain Strain 
	NelType	= 0			! Plain Stress
	E		= 10.5D6
	G		=  4.0D6
!/////////////////////////////////////
!	E		= 1.D0	 	
!/////////////////////////////////////
	PR		= (E/G/2.D0)-1.D0	! Poisson's Ratio
!-------------------------- Load
	P		= -100.D0		! Tip Radial at 90 degree							
!-------------------------- Geometry
	RADIUS	= 10.D0		! Radius
	DEPTH	= 1.0D0		! Depth
	WIDTH	= 1.D0		! Width
!-----------------------------------------------------------------
	write(iOut,1010) nStifS,iGeom,iCont,nC,nStifC,nSup,nStifN,Nint,
     &				Neltype
	write(iOut,1020) E,PR,RADIUS,DEPTH,WIDTH,P
!-------------------------------------------------------
!	Array sizes
!
	nSzInt	= 4 !bytes
	nSzDbl	= 8 !bytes
!	--------------------------------------------- Support
	nSx		= 1
	nEnd	= nSx + nSup*nSzInt
!
	call Initiate_Support(A(nSx),nSup,nQc,iCont,iOut)
!	---------------------------------------------
	n1a		= nEnd							! Qc1(2,4)
	n1b		= n1a + 2*nQc*nSzDbl			! Qc2(2,4)
	n2		= n1b + 2*nQc*nSzDbl			! S(21,21) Singular / 2ELs(n2)
	n2a		= n2  + nStifS*nStifS*nSzDbl	! S(32,32) Singular / 1ELs(n2b)
	n2b		= n2a + nStifS*nStifS*nSzDbl	! S(32,32) Singular / 1ELs(n2b)
	n3a		= n2b + nStifEL*nStifEL*nSzDbl	! T(56,54) Constraint(n3a)
	n3b		= n3a + nStifS*nStifC*nSzDbl	! S(54,54) Singular (n3b) 
	n3		= n3b + nStifC*nStifC*nSzDbl	! S(51,51) Non-Sing (n3)
	n4		= n3 + nStifN*nStifN*nSzDbl		! F(56) (Sing/NonSing)
	n4b		= n4 + nStifS*nSzDbl			! F(54) (Cons)
	n5		= n4b + nStifS*nSzDbl			! Qd(nQc)
	nEnd	= n5 + nQc*nSzDbl				
!-------------------------------------------------------
!
!	Set Bezier Coordinates 
!                                     
!-------------------------------------------------
	Nel = 1
	call BZ_Coords_EL1(A(n1a),2,nQc,RADIUS,iOut)
!-------------------------------------|------|--------
!	Get Stiffness Matrix: Ist Elem 
!
	call Quad_QQ_STIF(A(n1a),nQc,Nel,NelType,Nint,E,PR,
     &			Depth,Width,Radius,A(n2a),nStifEL,Iout,Trace)
!
!	Assemble Ist Elem
!
	n2c		= nEnd
	nEnd	= n2c + nStifEL*nSzInt
	call Assemble_Stif(A(n2c),A(n2a),nStifEL,A(n2),nStifS,Nel,
     & 													Iout,Trace)
!--------------------------------------------------------------------
!
!	Get Load Vector for Radial Load at Free End 
!
	call Set_ExtLoad_Y(A(n5),3,Iout)
	call Quad_QQ_LVY(A(n5),nQc,A(n4),nStifS,nLoadLoc,Iout)
!----------------------------------------------------------------------
!	displacement Controls:Qd
!
!--------------------------------------------------------------------
	n7		= nEnd
	n6		= n7 + nStifC*nSzDbl
	nEnd	= n6 + nStifC*nStifC*nSzDbl
!
	
	nW		= n6
	nU		= nW	+ nDis*nSzDbl
	nR		= nU	+ nDis*nSzDbl
	nEnd	= nR	+ (nDis+1)*nSzDbl
	nM		= nEnd
	nS		= nM	+ nStr*nSzDbl
	nA		= nS	+ nStr*nSzDbl
	nMSA	= nA	+ nStr*nSzDbl
	nEnd	= nMSA	+ (nStr+1)*nSzDbl
!--------------------------------------------------------------------
!	C0_Condition
!--------------------------------------------------------------------
	if (iCont == 0) then
!
!	Add Supports: rigid body Out
!
		call Extract_NonSingularStif(A(n2),nStifC,nStifC,A(n6),nStifN,
     &								A(nSx),nSup,iCont,iOut)
		call Extract_ContractedLoadVector(A(n4),nStifC,A(n7),nStifN,
     &								A(nSx),nSup,iCont,iOut)
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
     &					nStifC,A(nSx),nSup,iCont,iOut)
!----------------------------------------------------------------------------
!
!	Extract Element 1 Controls & Evaluate Disp./Strains/Stresses
!
	
		call Extract_DispCon(A(n7),nStifS,A(n4),nStifEL,1,iOut)
		call Compare_DisRot_1ELModel(nQc,A(n4),nStifEL,P,
     &					A(nW),A(nU),A(nR),nDis,nDis,1,iOut)
!	---------------------------------------------------------------
		call StressRecovery_2ELModel(A(n1a),nQc,A(n2a),nStifEL,
     &		E,PR,RADIUS,DEPTH,WIDTH,P,A(n4),nStifEL,
     &		A(nM),A(nS),A(nA),A(nMSA),nStr,nStr,nStr,1,iOut)
		call Compare_Castig_1ELModel(E,PR,RADIUS,DEPTH,WIDTH,
     &								A(n4),nStifEL,iOut)
!--------------------------------------------------------------------
	end if
!
!
	Stop 'OK'
 1000 Format(/ 5x,"TestCase I:"/
     &	2x,"Element Type               = Quartic/Quartic/Quartic"/
     &	2x,"Element DOFs               = ",I5/)
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
     &	2x,"Elasticity Modulus         = ",G12.5/
     &	2x,"Poisson's Ratio            = ",F10.5/
     &	2x,"Radius                     = ",F10.5/
     &	2x,"Depth                      = ",F10.5/
     &	2x,"Width                      = ",F10.5/
     &	2x,"Mid Moment in theta dir.   = ",F10.5/
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
