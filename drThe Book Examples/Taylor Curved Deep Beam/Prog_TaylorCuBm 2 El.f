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
	LOGICAL			bLoadSpec,bCirCon,bGeometry

	character*30	cConnect(3)
	DATA			cConnect/"","Circumferentially Connected",
     &							"Radially Connected"/
!-------------------------------------------------------------- Number of Elements, controls, etc.
	bGeometry = .TRUE.
	bGeometry = .FALSE.
	nElems		= 1
	if(nElems.Gt.1) iCont	= 0
!	-----------
	bCirCon		= .TRUE.	! circumferentially Connected
	if(nElems == 1) then
		nConnect	= 1
	else
		if(bCirCon) then
			nConnect = 2	! circumferentially Connected
		else
			nConnect = 3	! radially Connected
		endif
	endif
	cElemTyp	= "33"
	bLoadSpec	= .FALSE.
	nDis		= 0
!
	if(cElemTyp == "33") then
		if(bCirCon.OR.nElems ==1) then	! Circumferentially >1 Elements or 1 Element
			nDis	= 4	! Specified Displacement DOFs
			nSup	= 5 ! Supported DOFs
!			nSup	= 8 ! Supported DOFs
		else
			nDis	= 7	! Specified Displacement DOFs
			nSup	= 8 ! Supported DOFs
		endif
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
	nQc1		= 2	! Circumferential Bezier Geometry
	nQc2		= 4	! Radial Bezier Geometry
!	----------------------------------------------------
	nEnd		= 1						! 
!-------------------------------------------------------------- Element & Load Type
	nmDof	= nEnd
	nDof	= nmDof		+ nDis*nSzInt
	nmSup	= nDof		+ nDis*nSzDbl
	nEnd	= nmSup		+ nSup*nSzInt
!
	if(bCirCon) then
		if(nElems == 1) then
!			call Elem_Data_1Elem(cElemTyp,
			call Elem_Data_1Cart(cElemTyp,
     &				A(nDof),A(nmDof),nDis,A(nmSup),nSup,
     &				Nint,nDim,nDegR,nDegS,nStifEl,iOut)
		elseif(nElems == 2) then
			call Elem_Data_2CircumElems(cElemTyp,nCommon,
     &				A(nDof),A(nmDof),nDis,A(nmSup),nSup,
     &				Nint,nDim,nDegR,nDegS,nStifEl,iOut)
		elseif(nElems == 3) then
			call Elem_Data_3CircumElems(cElemTyp,nCommon,
     &				A(nDof),A(nmDof),nDis,A(nmSup),nSup,
     &				Nint,nDim,nDegR,nDegS,nStifEl,iOut)
		elseif(nElems == 4) then
			call Elem_Data_4CircumElems(cElemTyp,nCommon,
     &				A(nDof),A(nmDof),nDis,A(nmSup),nSup,
     &				Nint,nDim,nDegR,nDegS,nStifEl,iOut)
		endif
	else
		if(nElems == 1) then
			call Elem_Data_1Elem(cElemTyp,
     &				A(nDof),A(nmDof),nDis,A(nmSup),nSup,
     &				Nint,nDim,nDegR,nDegS,nStifEl,iOut)
		elseif(nElems == 2) then
			call Elem_Data_2RadialElems(cElemTyp,nCommon,
     &				A(nDof),A(nmDof),nDis,A(nmSup),nSup,
     &				Nint,nDim,nDegR,nDegS,nStifEl,iOut)
		endif
	endif
!	************************************ HARDCODED for Elems butted CIrcumferentially
	nStifS	= nElems * nStifEl - nCommon
!	************************************ HARDCODED End
	inDrop	= nDis + nSup		
	nStifN	= nStifS - inDrop
!	------------------------------------------------------------ C1 or C2 Constraints .
	nCDofs	= 0	! 
	if(iCont==1) nCDofs	= 8		! C1 reduction
	if(iCont==2) nCDofs	= 16	! C2 reduction
	nStifNC	= nStifN - nCDofs
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
	R_IN	= 5.0D0
	R_OUT	=10.0D0
	DEPTH	= R_Out-R_In		! depth
	THK		= DEPTH
	ANGLE   = 90.D0
!	------------------------------------------------------------ Print/Plot Controls
	call Define_ElementTypes(iOut)
!
	write(iOut,1000) 
     &	ElDeg(nQc1-1),ElDeg(nQc2-1),ElDeg(nDegR-1),ElDeg(nDegS-1),
     n	2,nElems,cConnect(nConnect),nStifEL
	write(iOut,1010) nCMat,nStifEL,nStifS,nDis,nSup,nStifN,
     &                    iGeom,iCont,nCDofs,nStifNC,
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
		if(bCirCon) then
			THK		= DEPTH
			call BZ_Coords_CubicXY(A(n1),nDim,nQc1,nQc2,R_In,R_Out,
     &								Thk,nElems,iOut)
!		---------------------------------------------------------- Geometry Plot
	if(bGeometry) then
		nPlGi	= 2		! plot Geometry
		nPlGj	= 49
		nGTot	= 2.D0*(2.D0*(nPlGi+nPlGj)+nQc1+nQc2)
		nrGPlt		= nEnd
		nEnd		= nrGPlt	+ nDim*nGTot*nSzDbl
		call GeometryPlot_Cart
     &			(A(n1),nDim,nQc1,nQc2,R_IN,DEPTH,ANGLE,
     &			nPlGi,nPlGj,iE,nElems,A(nrGPlt),nGTot,iOut,iOutDef)
		write(IoutDef,1040) float(1),float(nGTot)
		Stop 'Geometry Plot Only'
	endif
!	---------------------------------------------------------- Geometry Plot End
!			call BZ_Coords_RadCircum
!     &		(A(n1),nDim,nQc1,nQc2,R_In,R_Out,Thk,iE,nElems,iOut)
		else
			THK		= DEPTH/nElems
			call BZ_Coords_RadialConnect
     &		(A(n1),nDim,nQc1,nQc2,R_In,R_Out,
     &								Thk,nElems,iOut)
		endif
!		-------------------------------------------------------------- Get Stiffness Matrix
!		if(iE == 1) then	! both element stiffnesses same, so don't compute 2nd time
			call Stif_Element(A(n1),nDim,nQc1,nQc2,Nel,NelType,Nint,
     &				E,PR,Thk,R_In,nDegR,nDegS,nElems,
     &				Thk,A(n2),nStifEl,Iout,Trace)
!		endif
!
		if(nElems == 2) then	! we need index for 2nd element
			if(iE == 2) then
				if(bCirCon) then
					call FormIndex_EL2_Circum
     &					(cElemTyp,A(niIndx),nStifEl,iOut)
				else
					call FormIndex_EL2_Radial
     &					(cElemTyp,A(niIndx),nStifEl,iOut)
				endif
			endif
		endif
!		-------------------------------------------------------------- Assemble Stiffness Matrix
		call Stif_Assemble(A(niIndx),A(n2),nStifEl,A(nStA),nStifS,
     &					iE,Iout,Trace)
	end do ! iE
!	------------------------------------------------------------------ Check rigid body modes
	nEig	= nEnd
	nEnd	= nEig + nStifS*nSzDbl
	call Get_EigenValues(A(nStA),nStifS,nStifS,A(nEig),iOut)
!-------------------------------------------------------------------------------------
	if(bLoadSpec) then
!	----------------------------------------- Get Load Vector from Shear Load at End 
!		call Set_ExtLoad(A(n5),4)
!		call Quad_CC_LV(A(n5),A(n4),Depth)

	else
!	----------------------------------------- Get Load Vector from displacement at End 
		call LoadfromDis(A(nStA),nStifS,nStifS,A(nDof),A(nmDof),
     &					nDis,A(nmSup),nSup,A(n4),iOut)

	endif
!-------------------------------------------------------------- NonSingular Stiffness Matrix
	call Extract_NonSingularStif(A(nStA),nStifS,nStifS,
     &			A(iDrop),inDrop,A(n3),nStifN,nStifN,iOut)
	call Extract_ContractedLoadVector(A(n4),nStifS,
     &			A(iDrop),inDrop,A(n4b),nStifN,iOut)
!-------------------------------------------------------------- C1 Stiffness Matrix & Loads
	nrStifNC	= n3
	nrLoadNC	= n4b
	if(nElems == 2.AND.iCont.GT.0) then
		nT		= nEnd
		nrStifNC	= nT		+ nStifN*nStifNC*nSzDbl
		nrLoadNC	= nrStifNC	+ nStifNC*nStifNC*nSzDbl
		nEnd		= nrLoadNC	+ nStifNC*nStifNC*nSzDbl
!
		if(iCont == 1) then
			call FormTransformationMatrix_C1(A(nT),
     &					nStifN,nStifNC,iOut)
		elseif(iCont == 2) then
			call FormTransformationMatrix_C2(A(nT),
     &					nStifN,nStifNC,iOut)
		endif
		call Impose_Continuity(A(n3),A(n4b),nStifN,A(nT),A(nrStifNC),
     &							A(nrLoadNC),nStifNC,iOut)
!
	endif

!--------------------------------------------------------------------------------------- Solve
!-------------------------------------------------------------- displacement Controls:Qd
	n6		= nEnd
	n7		= n6 + nStifNC*nStifNC*nSzDbl
	nEnd	= n7 + nStifNC*nSzDbl
!	call Factor_Determinant(A(n3),A(n4),A(n6),A(n7),29,29,29)
	call Factor_ConditionNumber(A(nrStifNC),A(n6),A(n7),
     &							nStifNC,nStifNC,
     &								nStifNC,iOut)
	call Solve_AxEqB(A(nrStifNC),A(nrLoadNC),A(n7),
     &							nStifNC,nStifNC,iOut)
	call Compute_StrainEnergy(A(nrStifNC),A(nrLoadNC),A(n7),nStifNC,
     &								SEnergy,PEnergy,iOut)
!-------------------------------------------------------------- Expand with C1 Transforms
	if(iCont.GT.0) then
		call ExpandFrom_C1or2Sol(A(n6),nStifN,A(nT),A(n7),
     &						nStifNC,iOut)
	else
		n6 = n7
	endif
!-------------------------------------------------------------- Expand Controls
	nXS		= nStifS
	iXS		= nEnd
	nEnd	= iXS + nXS*nSzDbl
	call Expand_BzDispCons(A(n6),nStifN,A(iDrop),inDrop,
     &		A(nDof),A(nmDof),nDis,A(iXS),nXS,iOut)
!-------------------------------------------------------------- Compute/Print/Plot Displacement
	if(nElems == 1) then
		nPtsi	=  2	! minimum = 2                print/ 1 Elem
		nPtsj	= 10	! minimum = 2
	else if(nElems == 2) then
		nPtsi	= 10	! minimum = 2                print/ 2 Elems
		nPtsj	=  2	! minimum = 2
	endif
	nPlsi	= 2/nElems		! plot
	nPlsj	= 49/nElems
!	--------------------------------------------------------- Initiate Extraction data
	niEDat		= nEnd
	nEnd		= niEDat	+ nStifEl*nSzDbl
!
	nXE		= nStifEl
	iXE		= nEnd
	nEnd	= iXE + nXE*nSzDbl
	niEjSav		= nEnd
	nEnd		= niEjSav + 2*nPlsi*nSzDbl
	do iE = 1, nElems
		write(iOut,1030) iE
!		--------------------------------------------------------- Extract Control Pts
		call Extract_DispCon(A(iXS),nXS,A(iXE),nXE,
!     &						A(niEDat),iE,iOut)
     &						A(niIndx),iE,iOut)
!		--------------------------------------------------------- Print
		call DeformOut_PrCar(A(iXE),nXE,nDegR,nDegS,A(n1),
     &		nDim,nQc1,nQc2,nPtsi,nPtsj,ANGLE,DEPTH,R_IN,
     &        iOut,IoutEnd)
!		--------------------------------------------------------- Plot
		call DeformOut_PLCar(A(iXE),nXE,nDegR,nDegS,A(n1),
     &		nDim,nQc1,nQc2,nPLsi,nPLsj,ANGLE,DEPTH,R_IN,
     &        iOut,IoutEnd)
!	------------------------------------------------------------- MatLab Plot
!		call DeformOut_MatLab(A(iXE),nXE,nDegR,nDegS,A(n1),
!		call DeformOut_MatCar(A(iXE),nXE,nDegR,nDegS,A(n1),
!     &		nDim,nQc1,nQc2,nPlsi,nPlsj,iE,nElems,
!     &		ANGLE/nElems,iOut,IoutDef,IoutEnd)
!	--------------------------------------------- Endw Plot
!
	end do !iE
	write(IoutDef,1040) float(nPlsi+nPlsj),float(nPlsi)
	write(IoutEnd,1040) float(1),float( (nPLsj-1)*nElems+1 )
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
     &	2x,"No. of Elements                      = ",I5,2x,A30/,
     &	2x,"Element DOFs                         = ",I5/)
 1010 Format(/ 5x,"Integer Controls"/
     &	2x,"Size of ConstitutiveMatrix           = ",I5,2X, "nCMat"/
     &	2x,"Element Stiffness Size               = ",I5,2X,"nStifEL"/
     &	2x,"Singular Assembly Stiffness Size     = ",I5,2X,"nStifS"/
     &	2x,"No. of Specified Displacement Dofs   = ",I5,2X,"nDis"/
     &	2x,"No. of Supported Dofs                = ",I5,2x,"nSup"/
     &	2x,"NonSingular Assembly Stiffness Size  = ",I5,2X,"nStifN"/
     &	2x,"Inter-ElementControl Cn, n           = ",I5,2x,"Geometry"/
     &	2x,"Inter-ElementControl Cn, n           = ",I5,2x,"Displace"/
     &	2x,"Inter-ElementControl Dofs            = ",I5,2x,"nCDofs"/
     &	2x,"No. of Final Stiffness Size for Soln = ",I5,2X,"nStifNC"/
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
	
	Subroutine Set_ExtLoad(Qf,nDim)
	
	real(kind = 8)	Qf
	Dimension		Qf(nDim)
!	
	Qf		= 0.		! All Zero
	Qf(2)	= 1.0
	Qf(3)	= 1.0
!
	return
	end
!	  			
