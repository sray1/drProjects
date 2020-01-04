	Subroutine Set_IntegerControls(iDebug,iOut)
	Implicit Real(kind=8) (a-h,o-z)

	common/ElementType/ElType(10),ElDeg(5)
	character (20)	ElType
	character(10)   ElDeg
!
	common/SizeVar/	  iGeom,iCont,nDim,nQc,nSup,nDof,nQd,nElem,
     &                  nStifEL,Nint,nCInt,nStifS,nStifC,
     &				  nStifN,nLoadLoc,NelType
	common/Examples/cEx(10),nEx
	character (30)	cEx
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/ 
!-------------------------------------------- for Check with Quintic
	nElem	= 1							! DEFAULT no. of Elements
	SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			nSup	= 22		! Hinge/Slide Symmetric: 2D Beam
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
			nSup	= 22		! Hinge/Slide Symmetric: 2D Beam
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
			nSup	= 21				
		CASE (4)							! 3D Curved CantilevLINMOD: Ex_4
			nElem	=  2					! no. of Elements
			nSup	=  6				
		CASE (5)							! 3D Curved Cantilev.Bathe: Ex_5
			nElem	=  1					! no. of Elements
			nSup	=  6				
		CASE (6:10)    ! FALL THRO'           other: Ex_5.... 
		CASE DEFAULT
			return
	END SELECT
!	=======================================================
	iGeom	= 0 
	iCont	= 0					! 0 = C0/1 = C1/ 2 = C2
	nDim	= 3					! 2 = Planar Curve/3=true 3D Curve
	nQc		= 6					! 5 = Quartic/ 6 = Quintic
	nDof	= 6					! dof per node: Planar: u,w,v,th_t,th_m,th_b
	nQd		= nQc*nDof
	nStifEL	=  nDof*nQc 
	Nint	=  nQc-1			! Gauss Order (OPTIMAL)   
!	Nint	=  nQc-2			! Gauss Order (UNSTABLE)
!	Nint	=  nQc  			! Gauss Order (ERRONEOUS)
!	Nint	= 16				! Gauss Order (NO IMPROVEMENT from Nint=nQc)
	nCInt	= nDim*Nint
!-------------------------------------------------
	nStifS	=  nElem*nDof*(nQc-1) + nDof		! Singular: nElems
!
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
!----------------------------------------------------------------- DATA
	NelType	= 8			! 3D NonLinear Beam
!-----------------------------------------------------------------
	write(iOut,1010) nStifS,iGeom,iCont,nC,nStifC,nSup,
     &				nStifN,Nint,ElType(Neltype)
!	------------------------------
	if(nQc == 5) Then
		write(iOut,1000) ElDeg(4),nDof,nElem,nStifEL
!		write(IoutDef,1000) ElDeg(1),nDof,nElem,nStifEL
	else if(nQc == 6) Then
		write(iOut,1000) ElDeg(5),nDof,nElem,nStifEL
!		write(IoutDef,1000) ElDeg(2),nDof,nElem,nStifEL
	endif
!	-------------
	return
!
 1000 Format(/
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
     &	2x,"Element Type:              = ",A20/
     &	)		
!	--------     		
	end
