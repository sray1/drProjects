	Subroutine Set_WorkArrayPointers()
	Implicit Real(kind=8) (a-h,o-z)
!-------------------------------------------- 
	include 'Wpointers.h'
	include 'Addpoints.h'
	include 'SizeVar.h'
	include 'Output.h'
	include 'solve.h'
!-------------------------------------------- for Check with Quintic
	iDebug		= 1
!	nSx			= 1
!	n5			= nSx			+ nSup*nSzInt			!   Supported DOFs
!	n5V			= n5			+ nQc1*nSzDbl			!	Assumed load at the end along y			
	nRoCOld     = nEndW			! 	Start HERE			
	nCuCOld		= nRoCOld		+ nDim*Nint*nSzDbl
	nRoKSav		= nCuCOld		+ nDim*Nint*nSzDbl
	nCKKSav		= nRoKSav		+ nDim*Nint*nSzDbl
!
	n1c			= nCKKSav		+ nDim*Nint*nSzDbl
	n2			= n1c			+ nDim*nQc1*nQc2*nSzDbl		! S Singular / 2ELs(n2)
	n2a			= n2			+ nStifS*nStifS*nSzDbl		! S Singular / 1ELs(n2b)
	n2b			= n2a			+ nStifS*nStifS*nSzDbl		! S Singular / 1ELs(n2b)
	n3a			= n2b			+ nStifEL*nStifEL*nSzDbl	! T Constraint(n3a)
	n3b			= n3a			+ nStifS*nStifC*nSzDbl		! S Singular (n3b) 
	n3			= n3b			+ nStifC*nStifC*nSzDbl		! S Non-Sing (n3)
	n4			= n3			+ nStifN*nStifN*nSzDbl		! F (Sing/NonSing)
	n4b			= n4			+ nStifS*nSzDbl				! F (Cons)
	nxo			= n4b			+ nStifS*nSzDbl				! Qd(nQc)
	nx			= nxo			+ nStifS*nSzDbl				
	nBfors		= nx			+ nStifS*nSzDbl
	nStifK		= nBfors		+ nStifS*nSzDbl				
	nBo			= nStifK		+ nStifS*nSzDbl
	nB			= nBo			+ nStifS*nSzDbl
	nPLoad		= nB			+ nStifS*nSzDbl
	nGuLam		= nPLoad		+ nStifS*nSzDbl
	nUm			= nGuLam		+ nStifS*nSzDbl
	nUmO		= nUm   		+ nStifS*nSzDbl
	nxmR 		= nUmO   		+ nStifS*nSzDbl
	nxm 		= nxmR   		+ nStifS*nSzDbl
	nxmO		= nxm   		+ nStifS*nSzDbl
	ndeltaUi	= nxmO			+ nStifS*nSzDbl	! iterationSpecific
	ndeltaUi1	= ndeltaUi		+ nStifS*nSzDbl
	ndeltaUi2	= ndeltaUi1		+ nStifS*nSzDbl
	ndelUi		= ndeltaUi2		+ nStifS*nSzDbl ! stepSpecific
	ndelUiO		= ndelUi		+ nStifS*nSzDbl
	ndelUip11	= ndelUiO		+ nStifS*nSzDbl
	ndelUip12	= ndelUip11		+ nStifS*nSzDbl
	n7			= ndelUip12     + nStifS*nSzDbl
	n6			= n7			+ nStifS*nSzDbl
	n6R			= n6			+ nStifS*nStifS*nSzDbl
	n2c			= n6R			+ nStifS*nStifS*nSzDbl
	nEndwSav	= n2c			+ nStifEL*nSzInt
	ndelUiEL	= nEndwSav		+ 4*(MaxSteps+1)*nSzDbl
	nEndW		= ndelUiEL		+ nStifS*nSzDbl ! ElementSpecific			
!
!-------------------------------------------------------
	return
	end
