!	http://sunsite2.berkeley.edu/patronupdate/
	subroutine PhaseI_Shell
!-------------------------
	include 'Implicit.h'
!========================================================================
	include 'Blank.h'
	include 'Debug.h'
	include 'Wpointers.h'
	include 'SizeVar.h'
	include 'material.h'
	include 'geometry.h'
	include 'files.h'
	include 'solve.h'
!	include 'Output.h'
!	include 'Examples.h'
!	include 'CurrentElem.h'
!	include 'LoadStepIter.h'
!	include 'general.h'
!	include 'Addpoints.h'
!========================================================================
!
!	Input Variables & Arrays
!
!=================================================================================== Phase I: BEG
!------------------------------------------------------------------- ElementTypes
	call Define_ElementTypes(iOut)
!------------------------------------------------------------------- Example
	call Set_ExampleType(iOut)
!------------------------------------------------------------------- Geometry & DOF controls
	iPrt = 1
	call Get_Geometry(iPrt,iOut)
!------------------------------------------------------------------- Element Coords
	nEndW		= 1
	n1a			= nEndW
	n1b			= n1a			+ nDim*nQc1*nQc2*nSzDbl	! Qc2(nDim,nQc1,nQc2) element 1
	nEndW		= n1b			+ nDim*nQc1*nQc2*nSzDbl	! Qc2(nDim,nQc1,nQc2) element 2
!
	call Get_ElementCoords(iOut)
!------------------------------------------------------------------- Material
	call Get_Material(iPrt,iOut)
!------------------------------------------------------------------- SupportDOFs
	nSx			= nEndW
	nEndW		= nSx			+ nSup*nSzInt			!   Supported DOFs
!
	if(iDebug == 1) write(iOut,2002)
	call Get_SupportedDOFs(A(nSx),nSup,nQd1,nQd2,iCont,iOut)
!
	call DumpIntegerArray(A(nSx),nSup,"A(nSx):Supported DOFs",1,iOut)
!------------------------------------------------------------------- Load
	n5			= nEndW			!   
	n5V			= n5			+ nLod*nSzInt	!	Location			
	nEndW       = n5V			+ nLod*nSzDbl	! 	Value			
	if(iDebug == 1) write(iOut,2001)
	call Get_Loads(A(n5),A(n5V),nLod,nQd1,nQd2,iCont,iOut)	! (n5)=LocF/(n5V)=ValF
!
	call DumpIntegerArray(A(n5),nLod,"A(n5):Load DOFs",1,iOut)
	call DumpRealArray(A(n5V),nLod,"A(n5V):Load Values",1,iOut)
!------------------------------------------------------------------- Solution Params
	if(iDebug == 1) write(iOut,2003)
	call Initiate_SolutionData(iOut)
!------------------------------------------------------------------- Continuity
	call Set_IntegerControls(iDebug,iOut)
!------------------------------------------------------------------- Reference Properties at Gauss
	nBMat		= nEndW
	nTMat		= nBMat 		+ nDim*nDof2*nStifEL*nSzDbl
	nEndW		= nTMat 		+ nDim*nDof *nStifEL*nSzDbl
!	--------------
	call Set_Files_Scratch()
	call Put_Reference_AllGauss(A(n1a),A(nTMat),A(nBMat),Nel)
!------------------------------------------------------------------- Constitutive Matrix
	nDMat		= nEndW
	nEndW		= nDMat 		+ nCMat*nCMat *nSzDbl
	call Form_Constitutive_Condensed(A(nDMat),nCMat,iOut)
!=================================================================================== Phase I: END
	return
!
 2001 Format(/2x,"Entering: Initiate_DegreeData"/)
 2002 Format(/2x,"Entering: Initiate_Support"/)
 2003 Format(/2x,"Entering: Initiate_SolutionData"/)
	end 
!	  			
