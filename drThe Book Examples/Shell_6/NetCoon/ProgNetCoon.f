	Program NonLinearSHELL_Total3D_Snap_RIKS
!------------------------- Modules
	USE linear_operators
	USE DFLIB
	USE DFPORT
!========================================================================
	Implicit Real(kind=8) (a-h,o-z)
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
!
	nSzInt			= 4 !bytes
	nSzDbl			= 8 !bytes
!
	nDim			= 3
!------------------------------------------------------------------- Files
	call Set_Files()
!------------------------------------------------------------------- Today's Date/Time		
	call Set_TimeDate(iOut)
!------------------------------------------------------------------- Heading
	write(iOut,*)
     &	'========================================================',
     &	'   N E T C O O N  F O R  S P H E R I C A L  P A T C H'
	write(iOut,*)
     &	'========================================================'
!
!	============================================================= Data
	Rad		= 10.D0
	pi		= dacos(-1.D0)
	THED	= 72.D0					! degree
	THER	= THED*pi/180.D0		! Radian
	PHID	= 90.D0					! degree
	PHIR	= PHID*pi/180.D0		! Radian
!
	write(iOut,1000) Rad,THED,PHID
!	============================================================= Form Curves
	nDefSav			= 1
	nPtsi			= 49
	nPtsDef			= 4*nPtsi
	nPtsCon			= 4*4
	nConSavI		= nDefSav	+ nPtsDef*nSzDbl
	nConSavO		= nConSavI	+ 3*nPtsCon*nSzDbl
!	============================================================= Edge Controls
	call FormSave_Beziers(Rad,THER,PHIR,A(nDefSav),nPtsDef,nPtsi,
     &					A(nConSavI),nPtsCon,iOutDef,iOutCon,iOut)
!	============================================================= Fill Coon Net Controls
	call NetCoon(A(nConSavI),A(nConSavO),3,4,4,iConFEA,iOut)
	mC = 0
	call PackAllControlsforPlot(A(nConSavO),3,4,4,mC,iOutCon)
!	------------------------------------------------------------- MatLab Plot Edges
	iPlotCountDef	= 1
!	--------------------------------------------- Net Plot
	write(IoutDef,1040) float(iPlotCountDef),float(nPtsDef)
!	------------------------------------------------------------- MatLab Plot Edge Controls
	iPlotCountCon	= 1
!	--------------------------------------------- Net Plot
	write(IoutCon,1040) float(iPlotCountCon),float(mC)
!	------------------------------------------------------------- MatLab Plot End
!
  999 Stop 'Program completed OK'
 1000 format(//2x,"Radius             = ",F10.4/
     &         2X,"Theta:Longitudinal = ",F10.4/
     &         2X,"Theta:Latitudinal  = ",F10.4/)
 1040 format(F15.2,",",F15.2,",")
	end 
!	  			
