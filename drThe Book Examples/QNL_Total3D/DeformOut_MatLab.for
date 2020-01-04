	Subroutine DeformOut_MatLab(Qc,Qd,Conv,sign,nPts,nPStep,
     &							EndwSav,Nel)
	Implicit Real(kind=8) (a-h,o-z)

	common/LoadStepIter/iStep,iNut,bReset
	common/SizeVar/	  iGeom,iCont,nDim,nQc,nSup,nDof,nQd,nElem,
     &                  nStifEL,Nint,nCInt,nStifS,nStifC,
     &				  nStifN,nLoadLoc,NelType
	common/Material/E,G,PR
	common/Geometry/THETAP,THETAL,RADIUS,XLENGTH,DEPTH,WIDTH
       common/files/	  iFileStiff,Iout,IoutDef,IoutEnd
	common/SolVar/	  detKO,detK,delLmO,DelLm,iTermO,iTerRef,
     &				  delLamdaiO,SLamdam,SLamdamO,DeltaLamdai,ArcLen,
     &				  Tol,MaxSteps,MaxIt,iCutMax,Imaginary
	LOGICAL			  Imaginary		

	logical SaveStep
!
	Real(kind=4)	u,w    
	
	Real(kind=8)	Qc              
	Dimension		Qc(nDim,nQc)
	Real(kind=8)	Qd        ,EndwSav      
	Dimension		Qd(nStifS),EndwSav(2,*)
	character*1		sign
!
	common/Examples/cEx(10),nEx
	character (30)	cEx
!-------------------------------------------- for Check with Quintic
	SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			call DeformOut_MatLab_Pal(SLamdam,THETAL,Qd,nStifS,
     &				nQc,nDof,RADIUS,Conv,
     &            	sign,inut,nPts,iStep,nPStep,iOut,IoutDef,EndwSav)
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
			call DeformOut_MatLab_Pal(SLamdam,THETAL,Qd,nStifS,
     &				nQc,nDof,RADIUS,Conv,
     &            	sign,inut,nPts,iStep,nPStep,iOut,IoutDef,EndwSav)
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
			call DeformOut_MatLab_Str(SLamdam,THETAL,Qd,nStifS,
     &				nQc,RADIUS,Conv,
     &            	sign,inut,nPts,iStep,nPStep,iOut,IoutDef,EndwSav)
		CASE (4)							! 3D Curved Cantilev.LINMOD:Ex_4
			call DeformOut_MatLab_LIN(SLamdam,THETAL,Qd,nStifS,
     &				nQc,nDof,RADIUS,Conv,sign,inut,nPts,iStep,
     &				nPStep,iOut,IoutDef,EndwSav,Qc,Nel)
		CASE (5)							! 3D Str. Cantilever-Bathe: Ex_5
			call DeformOut_MatLab_Bat(SLamdam,THETAL,Qd,nStifS,
     &				nQc,nDof,RADIUS,Conv,sign,inut,nPts,iStep,
     &				nPStep,iOut,IoutDef,EndwSav,Qc,Nel)
		CASE (6:10)    ! FALL THRO'           other: Ex_5... 
		CASE DEFAULT
			return
	END SELECT
!	=======================================================
!-----------   	
	return
	end
