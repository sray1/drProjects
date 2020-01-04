	Program NonLinear_Genral3D_Snap_RIKS
!------------------------- Modules
	USE linear_operators
	USE DFLIB
	USE DFPORT
	USE DeformationPlot
	USE SCIGRAPH
!-------------------------
	Implicit Real(kind=8) (a-h,o-z)
!
!	Date
!--------------------------------------------------------------------------------
!-------------------------------------------------------------------------------- 		
!
!	Notes:	Nint should be atleast 2
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
!	Input Variables & Arrays
!
	Real(kind=8)	E,G,PR,RADIUS,DEPTH,WIDTH,Trace
	integer			Nel,NelType,Iout,nStif,nStifEL
	integer			n1a,n1b,n2
	real(kind = 8)	D     ,Disp   ,wc,uc,tc
	dimension		D(6,6),Disp(3)
	Logical			DontSkip
	character*1		sign,pos,neg
	LOGICAL			IsUpdateNeeded,TRUEE,
     &			 	ThetaNeedUpdate_STR,bReset
!
!========================================================================
	common A(1000000)
!
	common/Examples/cEx(10),nEx
	character (30)	cEx
	common/LoadStepIter/iStep,iNut,bReset
	common/general/	   Trace
	common/Wpointers/  nSx,nRoCOld,nCuCOld,nRoKSav,nCKKSav,n1a,n1b,
     &				   n2,n2a,n2b,n3a,n3b,n3,n4,n4b,n5,nxo,nx,nBfors,
     &                   nStifK,nBo,nB,nPLoad,nGuLam,nUm,nUmO,nxmR,
     &				   nxm,nxmO,ndeltaUi,ndeltaUi1,ndeltaUi2,ndelUi,
     &				   ndelUiO,ndelUip11,ndelUip12,n7,n6,n6R,n2c,
     &				   nEndwSav	
	common/Addpoints/  ndelUiEL,n1c
	common/SizeVar/	  iGeom,iCont,nDim,nQc,nSup,nDof,nQd,nElem,
     &                  nStifEL,Nint,nCInt,nStifS,nStifC,
     &				  nStifN,nLoadLoc,NelType
	common/Material/  E,G,PR
	common/Geometry/  THETAP,THETAL,RADIUS,XLENGTH,DEPTH,WIDTH
      common/files/	  iFileStiff,Iout,IoutDef,IoutEnd,iRotCur
      common/Scratch/	  iRotCur1,iRotCur2
	common/SolVar/	  detKO,detK,delLmO,DelLm,iTermO,iTerRef,
     &				  delLamdaiO,SLamdam,SLamdamO,DeltaLamdai,ArcLen,
     &				  Tol,MaxSteps,MaxIt,iCutMax,Imaginary
	LOGICAL			  Imaginary		
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!========================================================================
	data			pos/'+'/,neg/'-'/
	DATA			zero/0.D0/,one/1.0D0/,two/2.D0/  
!---------------------------
!	Output Variables & Arrays	
!
	TRUEE			= .TRUE.
	IsUpdateNeeded	= .FALSE.
	bReset			= .FALSE.
	Imaginary       = .FALSE.		
!
	iDebug	= 0
	iPlotCount  = 0	! MatLab
	nDis	= 49	! for Print Loop
	nStr	= 49	! for Print Loop
!	nStrRec = 0		! Stress Recovery from Strain-Displacement
	nStrRec = 1		! Stress Recovery from Equilibrium
!------------------------------------------------------------------- Files
	call Set_Files()
!------------------------------------------------------------------- Heading
	write(iOut,*)'====================================================='
	write(iOut,*)'        I N C R E M E N T A L   G E N 3 D '
	write(iOut,*)'====================================================='
!------------------------------------------------------------------- ElementTypes
	call Define_ElementTypes(iOut)
!------------------------------------------------------------------- Today's Date/Time		
	call Set_TimeDate(iOut)
!------------------------------------------------------------------- Example
	call Set_ExampleType(iOut)
!------------------------------------------------------------------- Continuity
	call Set_IntegerControls(iDebug,iOut)
!------------------------------------------------------------------- Scratch Files
	call Set_Files_Scratch(nCInt)
!---------------------------------------------------------------- Geometry & Material
	iPrt = 1
	call Get_Geometry(iPrt,iOut)
	call Get_Material(iPrt,iOut)
!---------------------------------------------------------------- Constitutive Matrix
	call Form_ConstitutiveMatrix(D,nDof,iOut)
!---------------------------------------------------------------- Solution Params
	if(iDebug == 1) write(iOut,2003)
	call Initiate_SolutionData(iOut)
!---------------------------------------------------------------- Array sizes
	nSzInt	= 4 !bytes
	nSzDbl	= 8 !bytes
	call Set_WorkArrayPointers(nSzInt,nSzDbl,nEndW)
!	----------------------------------------------------------- SupportDOFs
	if(iDebug == 1) write(iOut,2002)
	call Get_SupportedDOFs(A(nSx),nSup,nQc,iCont,iOut)
!	nEnd		= nEndw			+ 2*(MaxSteps+1)*nSzDbl
!---------------------------------------------------------------- Element Coords
	call Get_ElementCoords(iOut)
!------------------------------------------------------------------- Load
	if(iDebug == 1) write(iOut,2001)
	call Get_Loads(A(n5),3,iOut)
!--------------------------------------------------------------------
!	C0_Condition
!--------------------------------------------------------------------
	if (iCont == 0) then
!		-------------------------------------|------|----------------- Connectivity
		if(nElem == 2) Then
			if(iDebug == 1) write(iOut,2006)
			call FormIndexEl_2(A(n2c),nStifEL,iOut)
		endif
!		-------------------------------------|------|----------------- State Vector:Initialize
		if(iDebug == 1) write(iOut,2008)
		iStep = 0
		jStep = 0
		SLamdam		= zero
		SLamdamO	= zero
		call Initialize_StateVector(A(nRoCOld),A(nCuCOld),nCInt,iOut)	  
		call Initialize_StateVector(A(nRoKSav),A(nCKKSav),nCInt,iOut)	  
!==================================================================================== save
		do 4 Nel = 1,nElem
!		do 3 jInt = 1,Nint
!		nRec = (Nel-1)*Nint + jInt
		nRec = Nel
		call PutGetRotCur(iRotCur1,A(nRoCOld),A(nCuCOld),nCInt,nRec,1)	!Write
!    3		continue
    4		continue					
!==================================================================================== save:End
		call LV_Initialize(A(ndelUiEL),nStifEL,Iout)		! state
		call Initialize_StateVector(A(nxo),A(nx),nStifS,iOut)	  
		call Initialize_StateVector(A(nxmO),A(nxm),nStifS,iOut)	  
		call LV_Initialize(A(n4),nStifS,Iout)	! state
		call LV_Initialize(A(nBo),nStifS,Iout)	! Old Load Vector for Convergence
		call LV_Initialize(A(nxmO),nStifS,Iout)		! state
		call LV_Initialize(A(nxm),nStifS,Iout)		! state
!----------------------------------------------------------------------- For Printing End Results	
		if (jStep == 1) Then
			write(iOut,1030) 
		endif
!----------------------------------------------------------------------- For Plotting Results	
		iPlotCount  = iPlotCount + 1
!		--------------------------------------------------------- Print Undeformed Shape
!----------------------------------------------------------------------- For Plotting Results	
!------------------------------------------------------------------------- Elemental StepDisRot
		do 5 iEL = 1,nElem
			m1 =n1a
			if(iEL == 2) Then
				m1 =n1b
			elseif(iEL == 3) Then
				m1 =n1c
			endif
!			if(iEL.NE.nElem) then
!				goto 5
!			endif
!			--------------------------------------------------------- 
			call Extract_DispCon(A(nxm),nStifS,A(ndelUiEL),	!Extract DisRotCOntrols
     &			nStifEL,iEL,iOut)
			call DeformOut_MatLab(A(m1),A(ndelUiEL),Conv,pos,nDis,1,
     &							A(nEndwSav),iEL)
    5		continue
!--------------------------------------------------------------
!--------------------------------------------------------------
!		call DeformOut_MatLab(A(n1a),A(nxm),Conv,pos,nDis,1,
!     &							A(nEndwSav),nElem)
!============================================================================
  100		continue
		if(bReset == .FALSE.) Then
			jStep = iStep + 1
		else
			jStep = iStep
		endif
!===========================================================================================STEP 1 INITIALIZE
		iNut		= 0		!	Set for Curvature Initialization in
!								Get ReferenceInfo in QQ_Quad_Stif
!===========================================================================================STEP 1 INITIALIZE
		DelLamdaiO = ArcLen
		call LoadStep_1_iter_1(D)
!	-------------------------------------------------------- Check for theta update
!		bReset = .FALSE.
!	IsUpdateNeeded = ThetaNeedUpdate_STR(A(nxm),nStifEL,nQc,Iout)
!	if(IsUpdateNeeded.EQ. TRUEE ) Then
!			call Update_StepQc(A(nxm),nStifS,A(n1a),nQc,Iout)
!			call ResetReference(A(nxmO),A(nxm),nStifS,nQc,
!     &					A(nRoCOld),A(nCuCOld),
!     &					A(nRoKSav),A(nCKKSav),nCInt,Iout)
!		bReset = TRUEE
!	endif
!		-------------------------------------------------------- Check for theta update: End
!===========================================================================================
!		-------------------------------------|------|----------------- LOOP:Linearized Solution
		iTerRef		= 5
!		---------------
		iDetSChange = 0		! determinant sign change
		iPlotCount  = iPlotCount + 1
		do 500 iStep = jStep, MaxSteps
  150     continue	! for Imaginary roots	
!========================================================================================
!		-------------------------------------------------------- Check for theta update
!		bReset = .FALSE.
!		IsUpdateNeeded = ThetaNeedUpdate_STR(A(nxm),nStifEL,nQc,Iout)
!		if(IsUpdateNeeded.EQ. TRUEE ) Then
!			call ResetReference(A(nxmO),A(nxm),nStifS,nQc,
!     &					A(nRoCOld),A(nCuCOld),
!     &					A(nRoKSav),A(nCKKSav),nCInt,Iout)
!		bReset = TRUEE
!		go to 100
!		endif
!		-------------------------------------------------------- Check for theta update: End
!=============================================================================================
		DontSkip	= .TRUE.
		Imaginary	= .FALSE.
		call LV_Initialize(A(ndelUi),nStifS,Iout)		! state
		call LV_Initialize(A(ndeltaUi),nStifS,Iout)		! state
		call LV_Initialize(A(ndeltaUi1),nStifS,Iout)	! state
!		-------------------------------------| Newton Iterations for each LoadStep
		do 300 inut = 1, MaxIt
!		===================
		if(inut.eq.1) Then
!		---------------------------------------------------------------------- Stiffness Matrix
			if(iStep.GT.1) Then
				call LoadStep_n_iter_1(D)
			endif
!			--------------------------------- Save tangent stiffness needed to start over
!												for possible Imaginary root
!			--------------------------------- Save Inverted Tangent STiffness/Residue for the STEP
!			call InvertedTangentStiffness(A(n6),A(n6R),nStifN,1,iOut)	! 1 = Save
			call StateatStartofIter(A(nxm),A(nxmR),nStifS,1,iOut)			! 1 = Save
!			-----------------------------------------------			
			go to 250
		endif
!		===================
		call LV_Initialize(A(nB),nStifS,Iout)	! Current Load Vector
!		---------------------------------------------------------------------- Stiffness Matrix
!		-------------------------------------------------------- Debug 
		if((iStep == 2).AND.(iNut == 2)) Then
			abc = 1
		endif
!		-------------------------------------------------------- Debug : End
		call LoadStep_n_iter_m(D)
!	-------------------------------------------------------- Check for theta update
!		bReset = .FALSE.
!	IsUpdateNeeded = ThetaNeedUpdate_STR(A(nxm),nStifEL,nQc,Iout)
!	if(IsUpdateNeeded.EQ. TRUEE ) Then
!			call Update_StepQc(A(nxm),nStifS,A(n1a),nQc,Iout)
!			call ResetReference(A(nxmO),A(nxm),nStifS,nQc,
!     &					A(nRoCOld),A(nCuCOld),
!     &					A(nRoKSav),A(nCKKSav),nCInt,Iout)
!		bReset = TRUEE
!	endif
!		-------------------------------------------------------- Check for theta update: End
!------------------
  250		continue
!------------------
!		! Step 3biii	
!		call LoadParamChange(A(ndeltaUi1),A(ndeltaUi2),A(ndelUiO),	
!     &						nStifN,DelLm,Imaginary,
!     &					DeltaLamdai1,DeltaLamdai2,aa,bb,cc,iOut)
		call LoadParamChange(A(ndeltaUi1),A(ndeltaUi2),A(ndelUiO),	
     &						nStifN,DelLm,Imaginary,
!     &					DeltaLamdai1,DeltaLamdai2,aa,bb,cc,iOut)
     &					DeltaLamdai1,DeltaLamdai2,aa,bb,cc,iOut,
     &					A(nPLoad),DelLamdaiO)
!		-------------------------------------------------------- Debug 
		if((iStep == 1).AND.(iNut == 2)) Then
			iPrt = 0
!			call DumpVar(iOut)
			call DumpStringVar("Beg:aftLoadParamChange",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
			call DumpRealVar(DelLm,"DelLm",iPrt,iOut)
	call DumpRealVar(DeltaLamdai1,"DeltaLamdai1",iPrt,iOut)
	call DumpRealVar(DeltaLamdai2,"DeltaLamdai2",iPrt,iOut)
			call DumpRealVar(aa,"aa",iPrt,iOut)
			call DumpRealVar(bb,"bb",iPrt,iOut)
			call DumpRealVar(cc,"cc",iPrt,iOut)
	call DumpRealArray(A(nBFors),nStifEL,"A(nBFors)",iPrt,iOut)
	call DumpRealArray(A(nPLoad),nStifN,"A(nPLoad)",iPrt,iOut)
	call DumpRealArray(A(nGuLam),nStifN,"A(nGuLam)",iPrt,iOut)
	call DumpRealArray(A(ndeltaUi1),nStifN,"A(ndeltaUi1)",iPrt,iOut)
	call DumpRealArray(A(ndeltaUi2),nStifN,"A(ndeltaUi2)",iPrt,iOut)
	call DumpRealArray(A(ndelUiO),nStifN,"A(ndelUiO)",iPrt,iOut)
			call DumpStringVar("End:aftLoadParamChange",iPrt,iOut)
		endif
!		-------------------------------------------------------- Debug : End
		if(Imaginary) Then
!			DontSkip = .FALSE.
!			Stop 'IIMAGINARY ROOTS'
!			--------------------------------- Recover Inverted Tangent STiffness/Residue for the STEP
!			call InvertedTangentStiffness(A(n6),A(n6R),nStifN,2,iOut)		! 2 = Recall
			call StateatStartofIter(A(nxm),A(nxmR),nStifN,2,iOut)			! 2 = Recall
!			-----------------------------------------------			
			DelLm = 0.5D0*DelLm					
			go to 150
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
!		-------------------------------------------------------- Debug 
		if((iStep == 1).AND.(iNut == 3)) Then
			iPrt = 0
!			call DumpVar(iOut)
		call DumpStringVar("Beg:aftPossibleDisplacement",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
	call DumpRealVar(DeltaLamdai1,"DeltaLamdai1",iPrt,iOut)
	call DumpRealVar(DeltaLamdai2,"DeltaLamdai2",iPrt,iOut)
	call DumpRealArray(A(nDelUiO),nStifN,"A(nDelUiO)",iPrt,iOut)
	call DumpRealArray(A(ndeltaUi1),nStifN,"A(ndeltaUi1)",iPrt,iOut)
	call DumpRealArray(A(ndeltaUi2),nStifN,"A(ndeltaUi2)",iPrt,iOut)
	call DumpRealArray(A(ndelUip11),nStifN,"A(ndelUip11)",iPrt,iOut)
	call DumpRealArray(A(ndelUip12),nStifN,"A(ndelUip12)",iPrt,iOut)
	call DumpRealArray(A(ndelUiO),nStifN,"A(ndelUiO)",iPrt,iOut)
			call DumpStringVar("End:aftLoadParamChange",iPrt,iOut)
		endif
!		-------------------------------------------------------- Debug : End
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
!		--------------------------------------------------------- Extract END Element DisRotCOntrols
		call Extract_DispCon(A(nxm),nStifS,A(ndelUiEL),nStifEL,
     &							nElem,iOut)
		call Compute_uwthetaAtEnd(DelLm,SLamdam+DelLamdai,A(ndelUiEL),
     &							nStifEL,nQc,inut,MaxIt,Conv,iOut)
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
		SLamdam		= SLamdamO + delLamdaiO
		SLamdamO	= SLamdam
!
		sign = pos
		if(detK.LT.zero) sign = neg
!	-----------------------------------------------------------
		iPlotCount  = iPlotCount + 1
!------------------------------------------------------------------------- Elemental StepDisRot
		do 25 iEL = 1,nElem
			m1 =n1a
			if(iEL == 2) Then
				m1 =n1b
			elseif(iEL == 3) Then
				m1 =n1c
			endif
!			if(iEL.NE.nElem) then
!				goto 25
!			endif!			--------------------------------------------------------- 
			call Extract_DispCon(A(nxm),nStifS,A(ndelUiEL),	!Extract DisRotCOntrols
     &			nStifEL,iEL,iOut)
			call DeformOut_MatLab(A(m1),A(ndelUiEL),Conv,sign,nDis,1,
     &							A(nEndwSav),iEL)
   25		continue
!	--------------------------------------------------------------
!		----------------------------------------------
!		call DeformOut_MatLab(A(n1a),A(nxm),Conv,sign,nDis,1,
!     &							A(nEndwSav),nElem)
!		--------------------------------------------------------- Update State for next LoadStep
!		DelLamdaiO	= zero
		DelLmO		= DelLm		
		iTermO		= inut
!========================================================================================
!==================================================================================== save
		do 40 Nel = 1,nElem
!		do 30 jInt = 1,Nint
!		nRec = (Nel-1)*Nint + jInt
		nRec = Nel
		call PutGetRotCur(iRotCur2,A(nRoCOld),A(nCuCOld),nCInt,nRec,2)	!Read
		call PutGetRotCur(iRotCur1,A(nRoCOld),A(nCuCOld),nCInt,nRec,1)	!write
!   30		continue
   40		continue					
!==================================================================================== save:End
!===========================================================================================
!	-------------------------------------------------------- Check for theta update
!		bReset = .FALSE.
!	IsUpdateNeeded = ThetaNeedUpdate_STR(A(nxm),nStifEL,nQc,Iout)
!	if(IsUpdateNeeded.EQ. TRUEE ) Then
!			call Update_StepQc(A(nxm),nStifS,A(n1a),nQc,Iout)
!			call ResetReference(A(nxmO),A(nxm),nStifS,nQc,
!     &					A(nRoCOld),A(nCuCOld),
!     &					A(nRoKSav),A(nCKKSav),nCInt,Iout)
!		bReset = TRUEE
!	endif
!		-------------------------------------------------------- Check for theta update: End
!===========================================================================================
	if(Imaginary) Then								!added for 3DBat
		goto 150
	endif
!	------------------
  500		continue
	endif
  998 continue
!	------------------------------------------------------------- MatLab Plot
!	--------------------------------------------- Endw Plot
	MaxStepsp1 = MaxSteps + 1
	call PlotDataEndw(A(nEndwSav),iPlotCount,IoutEnd)
!
	write(IoutDef,1040) float(iPlotCount),float(nDis)
	write(IoutEnd,1040) float(1),float(iPlotCount)
!	------------------------------------------------------------- MatLab Plot End
	iPlot = 1
	if(iPlot == 1) Then
		iPltType = 2
		if(iPltType == 1) Then
			CALL SciGraphXYPlot(IoutDef,nDis,iPlotCount,iPltType)
		elseif(iPltType == 2) Then
			CALL SciGraphXYPlot(IoutEnd,iPlotCount,1,iPltType)
		else
			go to 999
		endif			 
	endif	
!
  999 Stop 'OK'
 1030	format(/" Step",8x,"Load",8x,"u(L)",12x,"w(L)",9x,"  v(L)  ",3x,
     &        " iter",2x,"convergence"/)
 1040 format(F15.2,",",F15.2,",")
 2000 Format(/2x,"Entering: NonLinear_Circular_Snap"/)
 2001 Format(/2x,"Entering: Initiate_DegreeData"/)
 2002 Format(/2x,"Entering: Initiate_Support"/)
 2003 Format(/2x,"Entering: Initiate_SolutionData"/)
 2006 Format(/2x,"Entering: FormIndexEl_2"/)
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
