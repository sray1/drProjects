	Subroutine DumpVar(iOut)

	Implicit Real(kind=8) (a-h,o-z)
	common/LoadStepIter/iStep,iNut,bReset
	common/SizeVar/	  iGeom,iCont,nDim,nQc,nSup,nDof,nQd,nElem,
     &                  nStifEL,Nint,nCInt,nStifS,nStifC,
     &				  nStifN,nLoadLoc,NelType
	common/SolVar/	  detKO,detK,delLmO,DelLm,iTermO,iTerRef,
     &				  delLamdaiO,SLamdam,SLamdamO,DeltaLamdai,ArcLen,
     &				  Tol,MaxSteps,MaxIt,iCutMax,Imaginary
	LOGICAL			  Imaginary		
	iPrt = 0
!-------------------------------------------- 
	write(iOut,1000) iStep,iNut
	write(iOut,1010) iGeom,iCont,nDim,nQc,nSup,nDof,nQd,nElem,
     &                  nStifEL,Nint,nCInt,nStifS,nStifC,
     &				  nStifN,nLoadLoc,NelType
	write(iOut,1020) detKO,detK,delLmO,DelLm,iTermO,iTerRef,
     &				  delLamdaiO,SLamdam,SLamdamO,DeltaLamdai,ArcLen,
     &				  Tol,MaxSteps,MaxIt,iCutMax 
!	-------------
	return
 1000 format(//2x,"iStep=",I5,2x,"iNut=",I5//)
 1010 format(/2x,"iGeom=",I5,2x,"iCont=",I5,2x,"nDim=",
     &        I5,2x,"nQc=",I5,2x,"nSup=",I5,2x,"nDof=",
     &		I5,2x,"nQd=",I5,2x,"nElem=",I5,2x,"nStifEL=",
     &		I5,2x,"Nint=",I5,2x/
     &		"nCInt=",I5,2x,"nStifS=",
     &		I5,2x,"nStifC=",I5,2x,"nStifN=",I5,2x,"nLoadLoc=",
     &		I5,2x,"NelType=",I5,2x/)
 1020 format(/2x,"detKO=",G10.5,2x,"detK=",G10.5,2x,"delLmO=",
     &        G10.5,2x,"DelLm=",G10.5,2x,"iTermO=",I10.5/2x,"iTerRef=",
     &		I10.5,2x,"delLamdaiO=",G10.5,2x,"SLamdam=",
     &		G10.5,2x,"SLamdamO=",G10.5,2x,"DeltaLamdai=",
     &		G12.5/2x,"ArcLen=",G10.5,2x,"Tol=",G10.5,2x,"MaxSteps=",
     &		I10.5,2x,"MaxIt=",I10.5,2x,"iCutMax=",I10.5/)
	end
