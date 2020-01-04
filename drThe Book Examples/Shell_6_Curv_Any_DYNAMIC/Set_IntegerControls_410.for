	Subroutine Set_IntegerControls_410(iDebug,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!								====================================
!								HARDCODED for EX.10 with 4 ELEMENTS
!								====================================
	include 'Drill.h'
	include 'ElementType.h'
	include 'Examples.h'
	include 'SizeVar.h'
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/ 
!	=======================================================
	nCInt	= nDim*Nint			! # of total gauss pts * nDim Coord direction
!-------------------------------------------------
!	-------------------------------------------------------------
	nDof		=  6	! d1,d2,d3,theta1,theta2,theta3
	nDof2		= 18	! d,theta,(d,1),(theta,1),(d,2),(theta,2)
	nQd			= nQd1*nQd2*nDof
	nStifEL		= nQd 
	nCMat		= 12	! Full Constitutive
!	--------------------------------------------
!	********************************************
!	HARDCODED: Assuming one row of quadrilateral	To run the example problems
!				element like beams in direction 1
!	********************************************
	nStifS	=  726	! HARDCODED
!	---------------------------------------------
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
!---------------------------------------------------------------- Drilling DOFs etc.
	nStifR  = nStifN - nStif3		! 
!----------------------------------------------------------------- DATA
	NelType	= 14				! 
!	------------------------------------------------------------ HARDCODED
	write(iOut,1000) 
     &	ElDeg(nQc1-1),ElDeg(nQc2-1),ElDeg(nQd1-1),ElDeg(nQd2-1),
     n	nDof,nDof2,nElem,nStifEL
!-----------------------------------------------------------------
	write(iOut,1010) nCMat,nDof,nDof2,nStifEL,nStifS,iGeom,iCont,
     &					nC,nStifC,nSup,nStifR,nStif3,nStifN,
     &					ElType(Neltype)
!	-------------
	return
!
 1000 Format(/
     &	2x,"Element Geometry Degree in dir.1     = ",A10/
     &	2x,"Element Geometry Degree in dir.2     = ",A10/
     &	2x,"Element displacement Degree in dir.1 = ",A10/
     &	2x,"Element displacement Degree in dir.2 = ",A10/
     &	2x,"Nodal DOFs                           = ",I5/,
     &	2x,"Nodal Extended DOFs                  = ",I5/,
     &	2x,"No. of Elements                      = ",I5/,
     &	2x,"Element DOFs                         = ",I5/)
 1010 Format(/ 5x,"Integer Controls"/
     &	2x,"Size of ConstitutiveMatrix           = ",I10,1X, "nCMat"/
     &	2x,"No. of Nodal DOFs                    = ",I10,1X, "nDOF"/
     &	2x,"No. of Analysis Nodal DOFs           = ",I10,1X, "nDOF2"/
     &	2x,"Element Stiffness Size               = ",I10,1X,"nStifEL"/
     &	2x,"Singular Assembly Stiffness Size     = ",I10,1X,"nStifS"/
     &	2x,"Inter-ElementControl Cn, n			 = ",I5,2x,"Geometry"/
     &	2x,"Inter-ElementControl Cn, n			 = ",I5,2x,"Displac."/
     &	2x,"Inter-ElementControl Dofs			 = ",I5/
     &	2x,"Constrained Stiffness Size			 = ",I5/
     &	2x,"No. of Supported Dofs				 = ",I5/
     &	2x,"No. of UnSupported NonDrilling Dofs	 = ",I5/
     &	2x,"No. of UnSupported Drilling Dofs	 = ",I5/
     &	2x,"NonSingular Assembly Stiffness Size	 = ",I10,1X,"nStifN"/
     &	2x,"Element Type:						 = ",A20/
     &	)		
!	--------     		
	end
