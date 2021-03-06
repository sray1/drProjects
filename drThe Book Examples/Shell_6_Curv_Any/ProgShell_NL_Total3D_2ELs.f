	Program NonLinearSHELL_Total3D_Snap_RIKS
!------------------------- Modules
	USE linear_operators
	USE DFLIB
	USE DFPORT
	USE DeformationPlot
!	USE SCIGRAPH
!-------------------------
	include 'Implicit.h'
!========================================================================
	include 'Blank.h'
	include 'Examples.h'
	include 'Output.h'
	include 'LoadStepIter.h'
	include 'general.h'
	include 'Wpointers.h'
	include 'Addpoints.h'
	include 'SizeVar.h'
	include 'material.h'
	include 'geometry.h'
	include 'files.h'
	include 'solve.h'
	include 'LogParams.h'
	include 'Drill.h'

	LOGICAL	bArcLen,bNewton
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!========================================================================
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
!	Real(kind=8)	E,G,PR,RADIUS,DEPTH,WIDTH,Trace
	integer			Nel,NelType,Iout,nStif,nStifEL
	integer			n1a,n1b,n2
	real(kind = 8)	Disp   ,wc,uc,tc
	dimension		Disp(3)
	Logical			DontSkip
	character*1		sign,pos,neg
	LOGICAL			IsUpdateNeeded,TRUEE,FALSE
     &			 	ThetaNeedUpdate_STR,bReset
!
	data			pos/'+'/,neg/'-'/
!=================================================================================== Phase 0: BEG
	TRUEE			= .TRUE.
	FALSE			= .FALSE.
!	=========================
	bNewton			= TRUEE
	bNewton			= FALSE
!	=========================
	bPrint			= TRUEE
	bPlot			= TRUEE
!	=========================
	bDrill			= TRUEE
	bDrill			= FALSE
!	Output Variables & Arrays	
!
	nSzInt			= 4 !bytes
	nSzDbl			= 8 !bytes
!
	IsUpdateNeeded	= .FALSE.
	bReset			= .FALSE.
	Imaginary       = .FALSE.		
!	=========================
	iDebug		= 0
	nPStep		= 10	! Ex 2
	nPStep		= 1		! Ex 3
!	nPStep		= 1
	nPStep		= 2		! Ex 1
	nPStep		= 2		! Ex 11
	nPStep		= 1		! Ex 10
	iPlotCountDef  = 0	! MatLab
	iPlotCountEnd  = 0	! MatLab
!	nStrRec = 0		! Stress Recovery from Strain-Displacement
	nStrRec		= 1		! Stress Recovery from Equilibrium
!------------------------------------------------------------------- Files
	call Set_Files()
!------------------------------------------------------------------- Today's Date/Time		
	call Set_TimeDate(iOut)
!------------------------------------------------------------------- Heading
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
	write(iOut,*)
     &	'   S H E L L   T O T A L   G E N 3 D  w i t h  D R I L L:',
     &	'   S H E L L_ 6'
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
!=================================================================================== Phase I: BEG
	call PhaseI_Shell
!=================================================================================== Phase I: END
!=================================================================================== Phase II: BEG
	if(bNewton) then
		call PhaseII_Shell_NEWTON
	else
		call PhaseII_Shell
	endif
!=================================================================================== Phase II: END
!=================================================================================== PhaseIII: BEG
!	------------------------------------------------------------- MatLab Plot
!	--------------------------------------------- Endw Plot
	MaxStepsp1 = MaxSteps + 1
	call PlotDataEndw(A(nEndwSav),iPlotCountEnd,IoutEnd)
!
	write(IoutDef,1040) float(iPlotCountDef),float(nPtsDef)
	write(IoutEnd,1050) float(2),float(iPlotCountEnd),float(0),
     &													float(0)
!	------------------------------------------------------------- MatLab Plot End
	iPlot = 1
	if(iPlot == 1) Then
		iPltType = 2
		if(iPltType == 1) Then
!???			CALL SciGraphXYPlot(IoutDef,nDis,iPlotCount,iPltType)
		elseif(iPltType == 2) Then
!???			CALL SciGraphXYPlot(IoutEnd,iPlotCount,1,iPltType)
		else
			go to 999
		endif			 
	endif	
!
  999 Stop 'Program completed OK'
 1030	format(/" Step",8x,"Load",8x,"u(L)",12x,"w(L)",9x,"  v(L)  ",3x,
     &        " iter",2x,"convergence"/)
 1040 format(F15.2,",",F15.2,",")
 1050 format(F15.2,",",F15.2,",",F15.2,",",F15.2)
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
