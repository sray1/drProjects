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
	include 'files.h'
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
!
!	Input Variables & Arrays
!
!	Real(kind=8)	E,G,PR,RADIUS,DEPTH,WIDTH,Trace
	LOGICAL			IsUpdateNeeded,TRUEE,FALSE
     &			 	ThetaNeedUpdate_STR,bReset
!
	data			pos/'+'/,neg/'-'/
!=================================================================================== Phase 0: BEG
	TRUEE			= .TRUE.
	FALSE			= .FALSE.
!	=========================
!------------------------------------------------------------------- Files
	call Set_Files()
!------------------------------------------------------------------- Today's Date/Time		
	call Set_TimeDate(iOut)
!------------------------------------------------------------------- Heading
	write(iOut,*)
     &	'====================',
	write(iOut,*)
     &	'   N E T C O O N'
	write(iOut,*)
     &	'===================='
!	------------------------------------------------------------- MatLab Plot
!	--------------------------------------------- Net Plot
	write(IoutDef,1040) float(iPlotCountDef),float(nPtsDef)
	write(IoutEnd,1050) float(1),float(iPlotCountEnd),float(0),
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
