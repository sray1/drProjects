	Program NonLinear_Circular_Snap_RIKS
!------------------------------------------------------------ NOTE: For Straight Beam
!	SET:
!		THETAL	= 1.D0				in NonLinear_Circular_Snap
!		CU		= 0.D0 				in QQ_EtranDEplusGMatrix
!------------------------------------------------------------ NOTE: For Compressibility Param, c
!	SET: for c = 0
!	E			= 10.0D6				in this NonLinear_Circular_Snap_RIKS	 
!	D(3)		= D(1)/12.D0	!EI		in Subroutine Constitutive
!	ArcLen		= 100.D0				in Subroutine Initiate_SolutionData		
!	MaxSteps	= 100					in Subroutine Initiate_SolutionData			
!	===================================	
!	SET: for c = 0
!	E			= 10.0D1				in this NonLinear_Circular_Snap_RIKS	 	
!	D(3)		= D(1)*256		!EI		in Subroutine Constitutive 
!	ArcLen		= 2.D0					in Subroutine Initiate_SolutionData								 
!	MaxSteps	= 18					in Subroutine Initiate_SolutionData			 
!------------------------- Modules
	USE linear_operators
	USE DFLIB
	USE DFPORT
	USE DeformationPlot
	USE SCIGRAPH
!-------------------------
	Implicit Real(kind=8) (a-h,o-z)
	CHARACTER(9) TODAY
	character (24) systime
!
!	Date
!--------------------------------------------------------------------------------
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
!		Qc(3,NN)	= Bezier Y-Coordinates
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
!
	common A(1000000)
!
!	Input Variables & Arrays
!
	Real(kind=8)	E,G,PR,RADIUS,DEPTH,WIDTH,Trace
	integer			Nel,NelType,Iout,nStif,nStifEL
	integer			n1a,n1b,n2
	real(kind = 8)	D   ,Disp   ,wc,uc,tc
	dimension		D(3),Disp(3)
	character(10)   ElDeg
	dimension		ElDeg(2)
	Logical			Imaginary,DontSkip
	character*1		sign,pos,neg
	data			pos/'+'/,neg/'-'/
	DATA			ElDeg		/"QUARTIC","QUINTIC"/ 
	DATA			zero/0.D0/,one/1.0D0/,two/2.D0/  
!---------------------------
!	Output Variables & Arrays	
!
	iDebug	= 0
	nDis	= 49	! for Print Loop
	nStr	= 49	! for Print Loop
!	nStrRec = 0		! Stress Recovery from Strain-Displacement
	nStrRec = 1		! Stress Recovery from Equilibrium
!----------------------------------------------------
	OPEN(UNIT=10,FILE='c:\The Book Examples\Gauss\det.dat')
	OPEN(UNIT=3,FILE='c:\The Book Examples\QNL_Circular\PlotDef.txt')
	OPEN(UNIT=4,FILE='c:\The Book Examples\QNL_Circular\PlotEnd.txt')
	Iout	= 10
	IoutDef	= 3
	IoutEnd	= 4
!------------------------------------------------------------------- Today's Date/Time		
	systime = CTIME (TIME( ))
	write(iOut,*) 'Run date and time is ',systime
!	write(IoutDef,*) 'Run date and time is ',systime

	!If today's date is October 6, 1995, the following
	!code prints "06-Oct-95"
!	CALL DATE(TODAY)
!	write(iOut,*) "                               Run Date = ",TODAY
	!The next line prints "10/06/95"
!	write(iOut,*) DATE( )
!------------------------------------------------------------------- Continuity
	iGeom	= 0 
	iCont	= 0					! 0 = C0/1 = C1/ 2 = C2
	nDim	= 2					! 2 = Planar Curve/3=true 3D Curve
	nQc		= 6					! 5 = Quartic/ 6 = Quintic
!	nSup	= 6					! Hinge/Slide Symmetric: 2D Beam
	nSup	= 4					! cantilevered: Planar Beam
	nDof	= 3					! dof per node: Planar: u, w, theta
	nQd		= nQc*nDof
	nElem	= 1					! no. of Elements
	nStifEL	=  nDof*nQc 
	Nint	=  nQc-1			! Gauss Order (OPTIMAL)   
!	Nint	=  nQc-2			! Gauss Order (UNSTABLE)
!	Nint	=  nQc  			! Gauss Order (ERRONEOUS)
!	Nint	= 16				! Gauss Order (NO IMPROVEMENT from Nint=nQc)
!	------------------------------
	if(nQc == 5) Then
		write(iOut,1000) ElDeg(1),nDof,nElem,nStifEL
!		write(IoutDef,1000) ElDeg(1),nDof,nElem,nStifEL
	else if(nQc == 6) Then
		write(iOut,1000) ElDeg(2),nDof,nElem,nStifEL
!		write(IoutDef,1000) ElDeg(2),nDof,nElem,nStifEL
	endif
!	------------------------
	if(iDebug == 1) write(iOut,2001)
	call Initiate_DegreeData(nStifS,nLoadLoc,nElem,nDof,
     &										nQc,iCont,iOut)
!	---------------------------------------------------------------------------------
	nSzInt	= 4 !bytes
	nSzDbl	= 8 !bytes
!	--------------------------------------------- Support
	nSx		= 1
	nEnd	= nSx + nSup*nSzInt
!
	if(iDebug == 1) write(iOut,2002)
	call Initiate_Support(A(nSx),nSup,nQc,iCont,iOut)
!-------------------------------------------------
	if (iCont == 0) then
		nC		= 0
		nStifC  = nStifS - nC	! BC at r=0
	else if (iCont == 1) then
		nC		= 1				! 1 (w    at junction)
!		nC		= 2				! 2 (w, u at junction)
!		nC		= 3				! 3 (w, u and theta at junction)
		nStifC  = nStifS - nC	! size Constrained:
								! Working on the Nonsingular stage
	else if (iCont == 2) then
!	------------------------------------------------------------------------
		nC		= 6 
		nStifC  = nStifS - nC	! size Constrained:
								! Working on the Nonsingular stage
	end if
!---------------------------------------------------------------- Support Cond
	nStifN  = nStifC - nSup		! size NonSingular: Sing - 4(2supU+2SupTheta)
!----------------------------------------------------
!
!	Stress-Strain Law
!
!----------------------------------------------------------------- DATA
!	NelType	= 1			! Plain Strain 
	NelType	= 0			! Plain Stress
	E		= 10.0D6	! c = 0	 	
!	E		= 10.0D1	! c = .01	 	
	G		= E/two
!/////////////////////////////////////
!	E		= 1.D0	 	
!/////////////////////////////////////
	PR		= (E/G/2.D0)-1.D0	! Poisson's Ratio
!-------------------------- Load
	P		= 1.D0							
!-------------------------- Geometry
	THETAP	= 53.13D0
	piby4		= datan(1.D0)
	THETAL	= THETAP*piby4/45.D0
!---------------------------------------- 
!	THETAL	= 1.D0
!	THETAL	= .0001D0						! **** Straight Beam ****
!	RADIUS	= 10000.0D0	! Radius
!---------------------------------------- 
	RADIUS	= 100.0D0	! Radius
	DEPTH	= 1.0D0		! Depth
	WIDTH	= 1.0D0		! Width
!-----------------------------------------------------------------
	write(iOut,1010) nStifS,iGeom,iCont,nC,nStifC,nSup,
     &				nStifN,Nint,Neltype
	write(iOut,1020) E,PR,THETAP,RADIUS,DEPTH,WIDTH,P
!----------------------------------------------------------------- Solution Params
	if(iDebug == 1) write(iOut,2003)
	call Initiate_SolutionData(Tol,ArcLen,MaxSteps,MaxIt,iCutMax,iOut)
!-------------------------------------------------------
!	Array sizes
!
	n1a		= nEnd							! Qc1(2,nQc)
	n1b		= n1a    + 2*nQc*nSzDbl			! Qc2(2,nQc)
	n1c		= n1b    + 2*nQc*nSzDbl			! UQc(2,nQc)
	n2		= n1c    + 2*nQc*nSzDbl			! S(21,21) Singular / 2ELs(n2)
	n2a		= n2     + nStifS*nStifS*nSzDbl	! S(32,32) Singular / 1ELs(n2b)
	n2b		= n2a    + nStifS*nStifS*nSzDbl	! S(32,32) Singular / 1ELs(n2b)
	n3a		= n2b    + nStifEL*nStifEL*nSzDbl	! T(56,54) Constraint(n3a)
	n3b		= n3a    + nStifS*nStifC*nSzDbl	! S(54,54) Singular (n3b) 
	n3		= n3b    + nStifC*nStifC*nSzDbl	! S(51,51) Non-Sing (n3)
	n4		= n3     + nStifN*nStifN*nSzDbl	! F(56) (Sing/NonSing)
	n4b		= n4     + nStifS*nSzDbl			! F(54) (Cons)
	n5		= n4b    + nStifS*nSzDbl			! Qd(nQc)
	nxo		= n5     + nQc*nSzDbl				
	nx		= nxo    + nStifS*nSzDbl				
	nBfors	= nx     + nStifS*nSzDbl
	nStifK	= nBfors + nStifS*nSzDbl				
	nBo		= nStifK + nStifS*nSzDbl
	nB		= nBo    + nStifS*nSzDbl
	nEnd	= nB     + nStifS*nSzDbl
	nPLoad		= nEnd			+ nStifS*nSzDbl 
	nGuLam		= nPLoad		+ nStifS*nSzDbl
	nUm			= nGuLam		+ nStifS*nSzDbl
	nUmO		= nUm   		+ nStifS*nSzDbl
	nxm 		= nUmO   		+ nStifS*nSzDbl
	nxmO		= nxm   		+ nStifS*nSzDbl
	ndeltaUi	= nxmO			+ nStifS*nSzDbl	! iterationSpecific
	ndeltaUi1	= ndeltaUi		+ nStifS*nSzDbl
	ndeltaUi2	= ndeltaUi1		+ nStifS*nSzDbl
	ndelUi		= ndeltaUi2		+ nStifS*nSzDbl ! stepSpecific
	ndelUiO		= ndelUi		+ nStifS*nSzDbl
	ndelUip11	= ndelUiO		+ nStifS*nSzDbl
	ndelUip12	= ndelUip11		+ nStifS*nSzDbl
	nEndw		= ndelUip12     + nStifS*nSzDbl
	nEnd		= nEndw			+ 2*(MaxSteps+1)*nSzDbl
!-------------------------------------------------------
!
!	Set Bezier Coordinates 
!                                     
!-------------------------------------------------------------- Element Data
	Nel = 1
	if(iDebug == 1) write(iOut,2004)
	call BZ_Coords_EL1(A(n1a),2,nQc,RADIUS,iOut)
	if(nElem == 2) Then
		Nel = 2
		if(iDebug == 1) write(iOut,2005)
		call BZ_Coords_EL2(A(n1b),2,nQc,RADIUS,iOut)
	endif
!	displacement Controls:Qd
!
!--------------------------------------------------------------------
	n7		= nEnd
	n6		= n7 + nStifC*nSzDbl
	nEnd	= n6 + nStifC*nStifC*nSzDbl
!
	
	nU		= n6
	nW		= nU	+ MaxSteps*nDis*nSzDbl
	nT		= nW	+ MaxSteps*nDis*nSzDbl
	nV		= nT	+ MaxSteps*nDis*nSzDbl
	nRx		= nV	+ nDis*nSzDbl
	nRy		= nRx	+ nDis*nSzDbl
	nRz		= nRy	+ nDis*nSzDbl
	nMDR	= nRz	+ (nDis+1)*nSzDbl
	nEnd	= nMDR	+ 6*(nDis+1)*nSzDbl
	nF1		= nEnd
	nF2		= nF1	+ 2*(nStr+1)*nSzDbl
	nF3		= nF2	+ 2*(nStr+1)*nSzDbl
	nM1		= nF3	+ 2*(nStr+1)*nSzDbl
	nM2		= nM1	+ 2*(nStr+1)*nSzDbl
	nM3		= nM2	+ 2*(nStr+1)*nSzDbl
	nMSA	= nM3	+ 2*(nStr+1)*nSzDbl
	nCT		= nMSA	+ 6*(nStr+1)*nSzDbl
	nEnd	= nCT	+ 2*(nStr+1)*nSzDbl
!--------------------------------------------------------------------
!	C0_Condition
!--------------------------------------------------------------------
	if (iCont == 0) then
!
		n2c		= nEnd
		nEnd	= n2c + nStifEL*nSzInt
!		-------------------------------------|------|----------------- Connectivity
		if(nElem == 2) Then
			if(iDebug == 1) write(iOut,2006)
			call FormIndexEl_2(A(n2c),nStifEL,iOut)
		endif
!		-------------------------------------|------|----------------- Constitutive
		if(iDebug == 1) write(iOut,2007)
		call Constitutive(D,E,PR,Width,Depth,iOut)
!		-------------------------------------|------|----------------- State Vector:Initialize
		if(iDebug == 1) write(iOut,2008)
		call Initialize_StateVector(A(nxo),A(nx),nStifS,iOut)	  
		call Initialize_StateVector(A(nxmO),A(nxm),nStifS,iOut)	  
		call LV_Initialize(A(n4),nStifS,Iout)	! state
		call LV_Initialize(A(nBo),nStifS,Iout)	! Old Load Vector for Convergence
!----------------------------------------------------------------------- For Printing End Results	
		write(iOut,1030) 
!		--------------------------------------------------------- Print Undeformed Shape
		SLamdam		= zero
		call LV_Initialize(A(nxmO),nStifS,Iout)		! state
		call LV_Initialize(A(nxm),nStifS,Iout)		! state
		call ResultsAtDesiredSteps(SLamdam,THETAL,A(nxm),
     &		nStifS,nQc,Radius,Conv,pos,inut,nDis,0,1,
     &		iOut,IoutDef,A(nEndw))
!===========================================================================================STEP 1 INITIALIZE
!		---------------------------------------------------------------------- Stiffness Matrix
		DelLamdaiO = ArcLen
!		-------------------------------------| Stiffness:Elem 1
!		Form Stiffness Matrix: Ist Elem 
!
		call Quad_QQ_STIF(A(nxmO),A(n1a),A(n1c),nQc,1,NelType,Nint,
     &			D,THETAL,Radius,A(n2a),A(nBfors),A(nStifK),
     &			nStifEL,Iout,Trace)
!
!		Assemble Ist Elem:nSTfK only has body force integral part
!
		call Assemble_Stif(A(n2c),A(n2a),
     &    		nStifEL,A(n2),nStifS,1,Iout,Trace)
!------------------------------------------------------------------------------- Residual & End Loads
!		----|------|----------------- Surface/End Load Vector
!		Get Load Vector 
		call Set_ExtLoad_Y(A(n5),3,Iout)
		call LV_EndLoad(A(n5),nQc,A(n7),nStifS,nLoadLoc,Iout)
!
!		Assemble Ist Elem:nBFors only has Residual & body force integral part
!
		call Assemble_Load(A(n2c),A(n7),
     &    		nStifEL,A(nB),nStifS,1,Iout)
!		-------------------------------------| Stiffness:Elem 2
		if(nElem == 2) Then
			call Quad_QQ_STIF(A(nxm),A(n1b),A(n1c),nQc,2,NelType,Nint,
     &			D,THETAL,Radius,A(n2b),A(nBfors),A(nStifK),
     &			nStifEL,Iout,Trace)
!
!		Assemble 2nd Elem:nSTfK only has body force integral part
!
			call Assemble_Stif(A(n2c),A(n2b),		
     &    		nStifEL,A(n2),nStifS,Nel,Iout,Trace)
!
!		Assemble 2nd Elem:nBFors only has Residual & body force integral part
!
			call Assemble_Load(A(n2c),A(nBFors),
     &    		nStifEL,A(nB),nStifS,2,Iout)
		endif
!------------------------------------------------------------------------------- Supported Stiff/Load/State
!		-----------|------|----------------- NonSingular Stiffness
!		Add Supports: rigid body Out
!
		call Extract_NonSingularStif(A(n2),nStifC,nStifC,A(n6),nStifN,
     &								A(nSx),nSup,iCont,iOut)
!		----------|------|----------------- Supported Load Vector & State Vector
!		Add Supports: rigid body Out
!
		call Extract_ContractedLoadVector(A(n7),nStifC,A(nPLoad),	!P-EndLoad
     &						nStifN,A(nSx),nSup,iCont,iOut)
!------------------------------------------------------------------------------- Solve:Current Iteration
!		call Factor_Determinant(A(n3),A(n4),A(n6),A(n7),29,29,29)
!		call Factor_ConditionNumber(A(n6),A(n2),A(n4),nStifN,
!     &										nStifN,nStifN,iOut)
!		call Solve_AxEqB(A(n6),A(nx),A(n4),nStifN,nStifN,iOut)
!		--------------------------------------------------------- Invert:Current Iteration
		call RealSym_Determinant(A(n6),A(n3),NStifN,NStifN,NStifN,
     &								detK)
		detKO = detK
		call Invert_A(A(n6),nStifN,nStifN,iOut)
!------------------------------------------------------------------ Initialize
!		! Step 2a: eqn 7
		call Calc_deltaUi2(A(n6),A(nPLoad),A(ndeltaUi2),
     &						nStifN,iOut)
!		! Step 2b: 
		call Calc_ArcLength_Step1(A(ndeltaUi2),nStifN,
     &					DelLamdaiO,DelLmO,iOut)
!		! Step 2b: eqn 10: At the beginning of each Loadstep Linear Solution
		call LV_Initialize(A(ndeltaUi1),nStifS,Iout)		! state
		call Calc_delUi(DelLamdaiO,A(ndeltaUi1),A(ndeltaUi2),
     &					A(ndelUiO),NStifN,iOut)
		DeltaLamdai = ArcLen
		DelLm		= DelLmO	
		call Expand_BezierDispControls_C0(A(ndelUiO),nStifN,A(nxo),
     &					nStifC,A(nSx),nSup,iCont,iOut)
!===========================================================================================
!		-------------------------------------|------|----------------- LOOP:Linearized Solution
		iTerRef		= 5
!		---------------
		iDetSChange = 0
		do 500 iStep = 1, MaxSteps
		DontSkip	= .TRUE.
		call LV_Initialize(A(ndelUi),nStifS,Iout)		! state
		call LV_Initialize(A(ndeltaUi),nStifS,Iout)		! state
		call LV_Initialize(A(ndeltaUi1),nStifS,Iout)	! state
!		-------------------------------------| Newton Iterations for each LoadStep
		do 300 inut = 1, MaxIt
!		===================
		if(inut.eq.1) Then
			go to 250
		endif
!		===================
		call LV_Initialize(A(nB),nStifS,Iout)	! Current Load Vector
!		---------------------------------------------------------------------- Stiffness Matrix
!		-------------------------------------| Stiffness:Elem 1
!		Form Stiffness Matrix: Ist Elem 
!
		call Quad_QQ_STIF(A(nxm),A(n1a),A(n1c),nQc,1,NelType,Nint,
     &			D,THETAL,Radius,A(n2a),A(nBfors),A(nStifK),
     &			nStifEL,Iout,Trace)
!
!		Assemble Ist Elem:nSTfK only has body force integral part
!
		call Assemble_Stif(A(n2c),A(n2a),
     &    		nStifEL,A(n2),nStifS,1,Iout,Trace)
!------------------------------------------------------------------------------- Residual & End Loads
!		----|------|----------------- Surface/End Load Vector
!		Get Load Vector 
!		call Set_ExtLoad_Y(A(n5),3,Iout)
!		call LV_EndLoad(A(n5),nQc,A(n7),nStifS,nLoadLoc,Iout)
!		----|------|----------------- Residual - lamda*P Load Vector
		call LV_minus_EndLoad(SLamdam+delLamdaiO,A(n7),A(nBfors),
     &							nStifS,iOut)
!
!		Assemble Ist Elem:nBFors only has Residual & body force integral part
!
		call Assemble_Load(A(n2c),A(nBFors),
     &    		nStifEL,A(nB),nStifS,1,Iout)
!		-------------------------------------| Stiffness:Elem 2
		if(nElem == 2) Then
			call Quad_QQ_STIF(A(nxm),A(n1b),A(n1c),nQc,2,NelType,Nint,
     &			D,THETAL,Radius,A(n2b),A(nBfors),A(nStifK),
     &			nStifEL,Iout,Trace)
!
!		Assemble 2nd Elem:nSTfK only has body force integral part
!
			call Assemble_Stif(A(n2c),A(n2b),		
     &    		nStifEL,A(n2),nStifS,Nel,Iout,Trace)
!
!		Assemble 2nd Elem:nBFors only has Residual & body force integral part
!
			call Assemble_Load(A(n2c),A(nBFors),
     &    		nStifEL,A(nB),nStifS,2,Iout)
		endif
!------------------------------------------------------------------------------- Supported Stiff/Load/State
!		-----------|------|----------------- NonSingular Stiffness
!		Add Supports: rigid body Out
!
		call Extract_NonSingularStif(A(n2),nStifC,nStifC,A(n6),nStifN,
     &								A(nSx),nSup,iCont,iOut)
!		----------|------|----------------- Supported Load Vector & State Vector
!		Add Supports: rigid body Out
!
!		call Extract_ContractedLoadVector(A(n7),nStifC,A(nPLoad),	!P-EndLoad
!     &						nStifN,A(nSx),nSup,iCont,iOut)
		call Extract_ContractedLoadVector(A(nB),nStifC,A(nGuLam),	!Residual
     &						nStifN,A(nSx),nSup,iCont,iOut)
		call Extract_ContractedLoadVector(A(nxO),nStifC,A(ndelUiO),	!State
     &						nStifN,A(nSx),nSup,iCont,iOut)
!------------------------------------------------------------------------------- Solve:Current Iteration
!		call Factor_Determinant(A(n3),A(n4),A(n6),A(n7),29,29,29)
!		call Factor_ConditionNumber(A(n6),A(n2),A(n4),nStifN,
!     &										nStifN,nStifN,iOut)
!		call Solve_AxEqB(A(n6),A(nx),A(n4),nStifN,nStifN,iOut)
!		--------------------------------------------------------- Invert:Current Iteration
!		detKO = detK
!		call RealSym_Determinant(A(n6),A(n3),NStifN,NStifN,NStifN,
!     &								detK)
		call Invert_A(A(n6),nStifN,nStifN,iOut)
!----------------------------------------------------------------------------------		
!		--------------------------------------------------------- for iteration>1
!		! Step 3bi: eqn7	
		call Calc_deltaUi2(A(n6),A(nPLoad),A(ndeltaUi2),nStifN,	
     &							iOut)
!		! Step 3bii: eqn6	
		call Calc_deltaUi1(A(n6),A(nGuLam),A(ndeltaUi1),nStifN,			
     &							iOut)
!------------------
  250		continue
!------------------
!		! Step 3biii	
		call LoadParamChange(A(ndeltaUi1),A(ndeltaUi2),A(ndelUiO),	
     &						nStifN,DelLm,Imaginary,
     &					DeltaLamdai1,DeltaLamdai2,aa,bb,cc,iOut)
		if(Imaginary) Then
			DelLm  = DelLm/2.D0
			DontSkip = .FALSE.
			Stop 'IIMAGINARY ROOTS'
		endif
!		! Step 3biv: eqn 8 part
!			call Calc_deltaUi(delLamdai,A(ndeltaUi1),A(ndeltaUi2),
!     &							A(ndeltaUi),NStifN,iOut)
!		! Step 3biv: eqn 8
		call Check_PossibleDisplacement(A(nDelUiO),
     &						A(ndeltaUi1),A(ndeltaUi2),		
     &						A(ndelUip11),A(ndelUip12),NStifN,
     &						DeltaLamdai1,DeltaLamdai2,iOut)
!		! Step 3bv: eqn 11
		call Calc_Angles(A(ndelUiO),A(ndelUip11),A(ndelUip12),NStifN,
     &						Th1,Th2,iOut)
		call UpdateIter_Displace_Lambda(Th1,Th2,A(ndelUip11),
     &						A(ndelUip12),	
     &						A(ndelUi),A(ndelUiO),NStifN,DeltaLamdai,
     1						DeltaLamdai1,DeltaLamdai2,cc,bb,iOut)
!-----------------
!  250		continue
!-----------------
!		! Step 3bvi: eqn 9
		call UpdateStep_Displace_Lambda(A(ndelUi),A(ndelUiO),A(nUm),
     &		A(nUmO),NStifN,DeltaLamdai,DelLamdaiO,DelLamdai,inut,iOut)
!		SLamdam		= SLamdam + delLamdaiO 		
!		--------------------------------------------------------- Expand State vector for Support
		call Expand_BezierDispControls_C0(A(nUmO),nStifN,A(nxmO),
     &					nStifC,A(nSx),nSup,iCont,iOut)
		call Expand_BezierDispControls_C0(A(nUm),nStifN,A(nxm),
     &					nStifC,A(nSx),nSup,iCont,iOut)
		call Expand_BezierDispControls_C0(A(ndelUiO),nStifN,A(nxo),
     &					nStifC,A(nSx),nSup,iCont,iOut)
		call Expand_BezierDispControls_C0(A(ndelUi),nStifN,A(nx),
     &					nStifC,A(nSx),nSup,iCont,iOut)
!------------------------------------------------------------------------------- Test Convergence
		call Convergence_Residual(A(nxmO),A(nxm),
     &							nStifS,Conv,inut,iOut)
		call Compute_uwthetaAtEnd(DelLm,SLamdam+DelLamdai,A(nxm),
     &							nStifC,nQc,inut,MaxIt,Conv,iOut)
!		-------------------------
		if(Conv.LE.tol) go to 400
  300		continue
!		--------------------------------------------------------- Iteration Limit Hit
!		------------------------------------ Try Cutting ArcLen
		write(iOut,4001) MaxIt
		stop 'ITERATION LIMIT HIT'
!		--------------------------------------------------------- Iteration SUCCESSFUL
  400		continue
!		--------------------------------------------------------- Print LoadStep Result
		SLamdam = SLamdam + delLamdaiO
!
		sign = pos
		if(detK.LT.zero) sign = neg
! 
		call ResultsAtDesiredSteps(SLamdam,THETAL,A(nxm),
     &		nStifS,nQc,Radius,Conv,sign,inut,nDis,iStep,1,
     &		iOut,IoutDef,A(nEndw))
!		--------------------------------------------------------- Update State for next LoadStep
!		DelLamdaiO	= zero
		DelLmO		= DelLm		
		iTermO		= inut
!===========================================================================================
!		---------------------------------------------------------------------- Stiffness Matrix
!		-------------------------------------| Stiffness:Elem 1
!		Form Stiffness Matrix: Ist Elem 
!
		call Quad_QQ_STIF(A(nxm),A(n1a),A(n1c),nQc,1,NelType,Nint,
     &			D,THETAL,Radius,A(n2a),A(nBfors),A(nStifK),
     &			nStifEL,Iout,Trace)
!
!		Assemble Ist Elem:nSTfK only has body force integral part
!
		call Assemble_Stif(A(n2c),A(n2a),
     &    		nStifEL,A(n2),nStifS,1,Iout,Trace)
!------------------------------------------------------------------------------- Residual & End Loads
!		----|------|----------------- Surface/End Load Vector
!		Get Load Vector 
!		call Set_ExtLoad_Y(A(n5),3,Iout)
!		call LV_EndLoad(A(n5),nQc,A(n7),nStifS,nLoadLoc,Iout)
!
!		Assemble Ist Elem:nBFors only has Residual & body force integral part
!
		call Assemble_Load(A(n2c),A(n7),
     &    		nStifEL,A(nB),nStifS,1,Iout)
!		-------------------------------------| Stiffness:Elem 2
		if(nElem == 2) Then
			call Quad_QQ_STIF(A(nxm),A(n1b),A(n1c),nQc,2,NelType,Nint,
     &			D,THETAL,Radius,A(n2b),A(nBfors),A(nStifK),
     &			nStifEL,Iout,Trace)
!
!		Assemble 2nd Elem:nSTfK only has body force integral part
!
			call Assemble_Stif(A(n2c),A(n2b),		
     &    		nStifEL,A(n2),nStifS,Nel,Iout,Trace)
!
!		Assemble 2nd Elem:nBFors only has Residual & body force integral part
!
			call Assemble_Load(A(n2c),A(nBFors),
     &    		nStifEL,A(nB),nStifS,2,Iout)
		endif
!------------------------------------------------------------------------------- Supported Stiff/Load/State
!		-----------|------|----------------- NonSingular Stiffness
!		Add Supports: rigid body Out
!
		call Extract_NonSingularStif(A(n2),nStifC,nStifC,A(n6),nStifN,
     &								A(nSx),nSup,iCont,iOut)
!		----------|------|----------------- Supported Load Vector & State Vector
!		Add Supports: rigid body Out
!
!		call Extract_ContractedLoadVector(A(n7),nStifC,A(nPLoad),	!P-EndLoad
!     &						nStifN,A(nSx),nSup,iCont,iOut)
!------------------------------------------------------------------------------- Solve:Current Iteration
!		call Factor_Determinant(A(n3),A(n4),A(n6),A(n7),29,29,29)
!		call Factor_ConditionNumber(A(n6),A(n2),A(n4),nStifN,
!     &										nStifN,nStifN,iOut)
!		call Solve_AxEqB(A(n6),A(nx),A(n4),nStifN,nStifN,iOut)
!		--------------------------------------------------------- Invert:Current Iteration
		detKO = detK
		call RealSym_Determinant(A(n6),A(n3),NStifN,NStifN,NStifN,
     &								detK)
		call Invert_A(A(n6),nStifN,nStifN,iOut)
!------------------------------------------------------------------ Initialize
!		! Step 3ai: eqn x
		call Calc_ArcLength_Stepm(delLmO,DelLm,
     &							iTermO,iTerRef,iStep,iOut)
!		! Step 3aii: eqn 7
		call Calc_deltaUi2(A(n6),A(nPLoad),A(ndeltaUi2),
     &						nStifN,iOut)
!		! Step 3aiii: eqn xx
		call Calc_Lamda1_Stepm(iStep,A(ndeltaUi2),nStifN,delLamdaiO,
     &						DelLm,DetK,DetKO,iOut)
!		! Step 2b: eqn 10: At the beginning of each Loadstep Linear Solution
		call LV_Initialize(A(ndeltaUi1),nStifS,Iout)		! state
		call Calc_delUi(DelLamdaiO,A(ndeltaUi1),A(ndeltaUi2),
     &					A(ndelUiO),NStifN,iOut)
		DeltaLamdai = delLamdaiO
		DelLm		= DelLmO	
		call Expand_BezierDispControls_C0(A(ndelUiO),nStifN,A(nxo),
     &					nStifC,A(nSx),nSup,iCont,iOut)
!===========================================================================================
  500		continue
	endif
  998 continue
!	--------------------------------------------- Endw Plot
	MaxStepsp1 = MaxSteps + 1
	call PlotDataEndw(A(nEndw),MaxStepsp1,IoutEnd)
	iPlot = 1
	if(iPlot == 1) Then
		iPltType = 2
		if(iPltType == 1) Then
			CALL SciGraphXYPlot(IoutDef,nDis,MaxSteps+1,iPltType)
		elseif(iPltType == 2) Then
			CALL SciGraphXYPlot(IoutEnd,MaxSteps+1,1,iPltType)
		else
			go to 999
		endif			 
	endif	
!
  999 Stop 'OK'
 1000 Format(/5x,
     & "FULLY NONLINEAR CURVED BEAM: ONE ELEMENT: Applied Tip Load"/
     &	2x,"Element Degree             = ",A10/
     &	2x,"Nodal DOFs                 = ",I5/,
     &	2x,"No. of Elements            = ",I5/,
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
     &	2x,"Elasticity Modulus          = ",G12.5/
     &	2x,"Poisson's Ratio             = ",F10.5/
     &	2x,"Total Elemental Angle       = ",F10.5,1X,"degree"/
     &	2x,"Radius                      = ",F10.5/
     &	2x,"Depth                       = ",F10.5/
     &	2x,"Width                       = ",F10.5/
     &	2x,"Vertical Load at End        = ",F10.5/
     &	)		
 1030	format(/" Step",8x,"Load",8x,"u(L)",12x,"w(L)",9x,"theta(L)",3x,
     &        " iter",2x,"convergence"/)
 2000 Format(/2x,"Entering: NonLinear_Circular_Snap"/)
 2001 Format(/2x,"Entering: Initiate_DegreeData"/)
 2002 Format(/2x,"Entering: Initiate_Support"/)
 2003 Format(/2x,"Entering: Initiate_SolutionData"/)
 2004 Format(/2x,"Entering: BZ_Coords_EL1"/)
 2005 Format(/2x,"Entering: BZ_Coords_EL2"/)
 2006 Format(/2x,"Entering: FormIndexEl_2"/)
 2007 Format(/2x,"Entering: Constitutive"/)
 2008 Format(/2x,"Entering: StateVector"/)
 4001 Format(/5x,"ITERATION LIMIT OF",I3," HIT: Back to Drawing Board!"
     &               /)
 4002 Format(/5x,"ARCLEN CUT OF",I3," HIT: Back to Drawing Board!"/)
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
