	Program TaylorCuBm_2El
!
!		NelType		= Element Type:
!						10 = Plane Stress
!						11 = Plane Strain
!						2 = Axi-symmtric	(NOT DONE YET)
!		Nint		= Number of Gauss Points
!		E			= Elasticity Modulus
!		PR			= Poisson's ratio
!		Thk			= Thickness
!		nStif		= Row or Col size of Stiffness matrix 
!		Iout		= Output file#
!		Stif(xx,xx)	= Singular Stiffness Matrix
!		nSup		= Supported DOFs ( = x)
!		nSupD		= Prescribed Displacement DOFs ( = x)
!-------------------------------------------------------------------------------- Solution Data		
!
!	Notes:	Nint should be atleast 2
!			nStif is 50 (Quartic_Quartic)
!
!-------------------------------------------------------------------------------- 		
	Implicit Real(kind=8) (a-h,o-z)
!
	include	'files.h'
	include 'ElementType.h'
!
	common A(1000000)
!
!	Input Variables & Arrays
!
	Real(kind=8)	E,PR,Thk,Rad,Trace
	integer			Nel,NelType,Iout,nStifS,nStifC,nStifN
	integer			n1,n2,NCon,NSup
	real(kind = 8)	Disp
	dimension		Disp(2)
	character*2		cElemTyp
	LOGICAL			LoadSpec
!-------------------------------------------------------------- Number of Elements, controls, etc.
	nElems		= 1
	cElemTyp	= "33"
	LoadSpec	= .FALSE.
	nDis		= 0
!
	if(cElemTyp == "33") then
		nDis	= 4	! Specified Displacement DOFs
		nSup	= 5 ! Supported DOFs
	elseif (cElemTyp == "44") then
		nDis	= 5	! Specified Displacement DOFs
		nSup	= 6 ! Supported DOFs	
	elseif (cElemTyp == "55") then
		nDis	= 6	! Specified Displacement DOFs
		nSup	= 7 ! Supported DOFs	
	endif
!--------------------------------------------------------------
	call Set_Files()
	call Set_TimeDate(iOut)
!------------------------------------------------------------------- Heading
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
	write(iOut,1001) nElems
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
!----------------------------		
	nSzInt	= 4 !bytes
	nSzDbl	= 8 !
!-------------------------------------------------------------- Geometry
	nDim		= 2	! Coordinate dimension: 2 = Surface
	nQc1		= 4	! Circumferential Bezier Geometry
	nQc2		= 2	! Radial Bezier Geometry
!	----------------------------------------------------
	nEnd		= 1						! 
!-------------------------------------------------------------- Element & Load Type
	nmDof	= nEnd
	nDof	= nmDof		+ nDis*nSzInt
	nmSup	= nDof		+ nDis*nSzDbl
	nEnd	= nmSup		+ nSup*nSzInt
!
	if(nElems == 1) then
		call Elem_Data(cElemTyp,
     &				A(nDof),A(nmDof),nDis,A(nmSup),nSup,
     &				Nint,nDim,nDegR,nDegS,nStifEl,iOut)
	elseif(nElems == 2) then
		call Elem_Data_2El(cElemTyp,nCommon,
     &				A(nDof),A(nmDof),nDis,A(nmSup),nSup,
     &				Nint,nDim,nDegR,nDegS,nStifEl,iOut)
	endif
!------------------------------------------------------------------ .
	iCont	= 0
	nCon	= 0	! 
	nC		= 0
!	************************************ HARDCODED for 2Elems butted
	nStifS	= nElems * nStifEl - nCommon
!	************************************ HARDCODED End
	inDrop	= nDis + nSup		
	nStifC	= nStifS - nCon
	nStifN	= nStifC - inDrop
	nStifD	= nStifN
!----------------------------------------------------------------- DATA
	Nel		= nElems
	NelType	= 10			! Plain Stress ( to compare w/ short beam)
!	NelType	=  9			! Plain Strain ( to compare w/ Timo Curved beam)
	nCMat	=  3
	iGeom	=  0
!
!
	E		= 10000.0D0	 	
	PR		= 0.25D0	! Poisson's Ratio
	THK		= 1.0D0		! thickness
	R_IN	= 5.0D0
	R_OUT	=10.0D0
	DEPTH	= R_Out-R_In		! depth
	ANGLE   = 90.D0
!	------------------------------------------------------------ Print/Plot Controls
	call Define_ElementTypes(iOut)
!
	write(iOut,1000) 
     &	ElDeg(nQc1-1),ElDeg(nQc2-1),ElDeg(nDegR-1),ElDeg(nDegS-1),
     n	2,nElems,nStifEL
	write(iOut,1010) nCMat,nStifEL,nStifS,iGeom,iCont,
     &					nC,nStifC,nSup,nStifN,nDis,nStifD,
     &					ElType(Neltype)
	write(iOut,1020) R_In,R_Out,Depth,Thk,Angle,E,PR,Nint
!-------------------------------------------------------------- Create DOFs to be dropped 
	iDrop	= nEnd
	nEnd	= iDrop	+ inDrop*nSzInt	
	call Create_DropDOFs(A(nmDof),nDis,A(nmSup),nSup,
     &						A(iDrop),inDrop,iOut)
	call OutDisSup_Data(A(nDof),A(nmDof),nDis,A(nmSup),nSup,
     &					A(iDrop),inDrop,iOut)
!-------------------------------------------------------------- Array sizes
	n1		= nEnd								! Qc(nDim,nQc1,nQc2)
	n2		= n1	+ 2*nDim*nQc1*nQc2*nSzDbl	! S(nStifEl,nStifEl) Singular (n2)
	n3		= n2	+ nStifEl*nStifEl*nSzDbl	! S(nStifN,nStifN) Non-Sing (n3)
	n4		= n3	+ nStifN*nStifN*nSzDbl		! F(nStifS) (Sing/NonSing)
	n4b		= n4	+ nStifS*nSzDbl				! F(nStifS) (Cons)
	n5		= n4b	+ nStifS*nSzDbl				! Qd(4)
	nEnd	= n5	+ 4*nSzDbl
!
	niIndx		= nEnd
	nStA		= niIndx		+ nStifEl*nSzInt
	nEnd		= nStA			+ nStifS*nStifS*nSzDbl
	if(nElems == 1) then
		nStA = n2
	endif
!---------------------------------------------------------------------------------------- Loop:Element Stiffness
	do iE = 1, nElems
		!------------------------------------------------------------- Get Bezier Coordinates
		call BZ_Coords(A(n1),nDim,nQc1,nQc2,R_In,R_Out,Depth,iOut)
!		-------------------------------------------------------------- Get Stiffness Matrix
		if(iE == 1) then	! both element stiffnesses same, so don't compute 2nd time
			call Stif_Element(A(n1),nDim,nQc1,nQc2,Nel,NelType,Nint,
     &				E,PR,Thk,R_In,nDegR,nDegS,nElems,
     &				Depth,A(n2),nStifEl,Iout,Trace)
		endif
!
		if(nElems == 2) then	! we need index for 2nd element
			if(iE == 2) then
				call FormIndexEL_2(cElemTyp,A(niIndx),nStifEl)
			endif
		endif
!		-------------------------------------------------------------- Assemble Stiffness Matrix
		call Stif_Assemble(A(niIndx),A(n2),nStifEl,A(nStA),nStifS,
     &					iE,Iout,Trace)
	end do ! iE
!-------------------------------------------------------------------------------------
	if(LoadSpec) then
!	----------------------------------------- Get Load Vector from Shear Load at End 
!		call Set_ExtLoad(A(n5),4)
!		call Quad_CC_LV(A(n5),A(n4),Depth)

	else
!	----------------------------------------- Get Load Vector from displacement at End 
		call LoadfromDis(A(nStA),nStifS,nStifS,A(nDof),A(nmDof),
     &					nDis,A(nmSup),nSup,A(n4),nStifS-nDis,iOut)

	endif
!-------------------------------------------------------------- displacement Controls:Qd
	n6		= nEnd
	n7		= n6 + nStifS*nStifS*nSzDbl
	nEnd	= n6 + nStifS*nSzDbl
!-------------------------------------------------------------- Condense Stiffness Matrix
!	--------------------------------------------------------- YES warp
	call Extract_NonSingularStif(A(nStA),nStifC,nStifC,
     &			A(iDrop),inDrop,A(n3),nStifN,nStifN,iOut)
	call Extract_ContractedLoadVector(A(n4),nStifC,
     &			A(iDrop),inDrop,A(n4b),nStifN,iOut)
!-------------------------------------------------------------- Solve
!	call Factor_Determinant(A(n3),A(n4),A(n6),A(n7),29,29,29)
	call Factor_ConditionNumber(A(n3),A(n6),A(n7),nStifN,nStifN,
     &								nStifN,iOut)
	call Solve_AxEqB(A(n3),A(n4b),A(n6),nStifN,nStifN,iOut)
	call Compute_StrainEnergy(A(n3),A(n4b),A(n6),nStifN,
     &								SEnergy,PEnergy,iOut)
!-------------------------------------------------------------- Expand Controls
	nXS		= nStifS
	iXS		= nEnd
	nEnd	= iXS + nXS*nSzDbl
	call Expand_BzDispCons(A(n6),nStifN,A(iDrop),inDrop,
     &		A(nDof),A(nmDof),nDis,A(iXS),nXS,iOut)
!-------------------------------------------------------------- Compute/Print/Plot Displacement
	nPtsi	= 90	! print
	nPtsj	= 4

	nPlsi	= 49		! plot
	nPlsj	= 49
!	--------------------------------------------------------- Initiate Extraction data
	niEDat		= nEnd
	nEnd		= niEDat	+ nStifEl*nSzDbl
!
	nXE		= nStifEl
	iXE		= nEnd
	nEnd	= iXE + nXE*nSzDbl
	do iE = 1, nElems
		write(iOut,1030) iE
!		--------------------------------------------------------- Extract Control Pts
		call Extract_DispCon(A(iXS),nXS,A(iXE),nXE,
!     &						A(niEDat),iE,iOut)
     &						A(niIndx),iE,iOut)
!		--------------------------------------------------------- Print
		call DeformOut_Print(A(iXE),nXE,nDegR,nDegS,A(n1),
     &		nDim,nQc1,nQc2,nPtsi,nPtsj,ANGLE,DEPTH,R_IN,iOut,iOutS)
!	------------------------------------------------------------- MatLab Plot
	niEjSav		= nEnd
	nEnd		= niEjSav + 2*nPlsi*nSzDbl
		call DeformOut_MatLab(A(iXE),nXE,nDegR,nDegS,A(n1),
     &		nDim,nQc1,nQc2,nPlsi,nPlsj,ANGLE,iOut,IoutDef,IoutEnd)
!	--------------------------------------------- Endw Plot
!	call PlotDataEndw(A(nEndwSav),nPtsi,IoutEnd)	!ignore last one that closes figure
!
	write(IoutDef,1040) float(nPlsi+nPlsj),float(nPlsi)
	write(IoutEnd,1040) float(1),float(nPlsi)
!	write(IoutEnd,1040) float(1),float(nPtsi)
!
	end do !iE
!
	Stop 'OK'
 1001 Format(
     &	'   T A Y L O R  C U R V E D  B E A M:  Ch 2: with ',9x,i2,
     &   ' ELEMENT(s)')
 1000 Format(/
     &	2x,"Element Geometry Degree in dir.1     = ",A10/
     &	2x,"Element Geometry Degree in dir.2     = ",A10/
     &	2x,"Element displacement Degree in dir.1 = ",A10/
     &	2x,"Element displacement Degree in dir.2 = ",A10/
     &	2x,"Nodal DOFs                           = ",I5/,
     &	2x,"No. of Elements                      = ",I5/,
     &	2x,"Element DOFs                         = ",I5/)
 1010 Format(/ 5x,"Integer Controls"/
     &	2x,"Size of ConstitutiveMatrix           = ",I5,2X, "nCMat"/
     &	2x,"Element Stiffness Size               = ",I5,2X,"nStifEL"/
     &	2x,"Singular Assembly Stiffness Size     = ",I5,2X,"nStifS"/
     &	2x,"Inter-ElementControl Cn, n           = ",I5,2x,"Geometry"/
     &	2x,"Inter-ElementControl Cn, n           = ",I5,2x,"Displac."/
     &	2x,"Inter-ElementControl Dofs            = ",I5,2x,"nC"/
     &	2x,"Constrained Stiffness Size           = ",I5,2x,"nStifC"/
     &	2x,"No. of Supported Dofs                = ",I5,2x,"nSup"/
     &	2x,"NonSingular Assembly Stiffness Size  = ",I5,2X,"nStifN"/
     &	2x,"No. of Specified Displacement Dofs   = ",I5,2X,"nDis"/
     &	2x,"No. of Final Stiffness Size for Soln = ",I5,2X,"nStifD"/
     &	2x,"Element Type:                        = ",A20/
     &	)		
 1020 Format(/ 5x,"Problem & Solution Data"/
     &	2x,"Inside Radius                        = ",F10.3/
     &	2x,"Outside Radius                       = ",F10.3/
     &	2x,"Depth                                = ",F10.3/
     &	2x,"Thickness                            = ",F10.3/
     &	2x,"Angle                                = ",F10.3,2X,'degrees'//
     &	2x,"Modulus                              = ",F10.3/
     &	2x,"Poisson's Ratio                      = ",F10.3/
     &	2x,"Number of Gause Points               = ",i10/)
 1030 Format(//5x,"Displacements for Element ",i1//)
 1040 format(F15.2,",",F15.2)
	end 
!
