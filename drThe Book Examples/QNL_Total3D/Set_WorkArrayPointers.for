	Subroutine Set_WorkArrayPointers(nSzInt,nSzDbl,nEndW)
	Implicit Real(kind=8) (a-h,o-z)
!-------------------------------------------- 
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
	common/SolVar/	  detKO,detK,delLmO,DelLm,iTermO,iTerRef,
     &				  delLamdaiO,SLamdam,SLamdamO,DeltaLamdai,ArcLen,
     &				  Tol,MaxSteps,MaxIt,iCutMax,Imaginary
	LOGICAL			  Imaginary		
!-------------------------------------------- for Check with Quintic
	nSx			= 1
	nRoCOld		= nSx			+ nSup*nSzInt
	nCuCOld		= nRoCOld		+ nDim*Nint*nSzDbl
	nRoKSav		= nCuCOld		+ nDim*Nint*nSzDbl
	nCKKSav		= nRoKSav		+ nDim*Nint*nSzDbl
	n1a			= nCKKSav		+ nDim*Nint*nSzDbl
	n1b			= n1a			+ nDim*nQc*nSzDbl		! Qc2(nDim,nQc)
	n1c			= n1b			+ nDim*nQc*nSzDbl		! Qc2(nDim,nQc)
	n2			= n1c			+ nDim*nQc*nSzDbl		! S(21,21) Singular / 2ELs(n2)
	n2a			= n2			+ nStifS*nStifS*nSzDbl	! S(32,32) Singular / 1ELs(n2b)
	n2b			= n2a			+ nStifS*nStifS*nSzDbl	! S(32,32) Singular / 1ELs(n2b)
	n3a			= n2b			+ nStifEL*nStifEL*nSzDbl	! T(56,54) Constraint(n3a)
	n3b			= n3a			+ nStifS*nStifC*nSzDbl	! S(54,54) Singular (n3b) 
	n3			= n3b			+ nStifC*nStifC*nSzDbl	! S(51,51) Non-Sing (n3)
	n4			= n3			+ nStifN*nStifN*nSzDbl	! F(56) (Sing/NonSing)
	n4b			= n4			+ nStifS*nSzDbl			! F(54) (Cons)
	n5			= n4b			+ nStifS*nSzDbl			! Qd(nQc)
	nxo			= n5			+ nQc*nSzDbl				
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
	ndelUiEL	= nEndwSav		+ 2*(MaxSteps+1)*nSzDbl
	nEnd		= ndelUiEL		+ nStifS*nSzDbl ! ElementSpecific
!
!-------------------------------------------------------
	return
	end
