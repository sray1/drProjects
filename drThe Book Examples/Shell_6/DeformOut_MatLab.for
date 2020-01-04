	Subroutine DeformOut_MatLab(Qc,Qd,Conv,sign,EndwSav,Nel)
	Implicit Real(kind=8) (a-h,o-z)
!==================================================================
	include 'Wpointers.h'
	include 'Output.h'
	include 'LogParams.h'
	include 'LoadStepIter.h'
	include 'SizeVar.h'
	include 'Material.h'
	include 'geometry.h'
	include 'files.h'
	include 'Solve.h'
	include 'Examples.h'
!==================================================================
	logical SaveStep
!
	Real(kind=4)	u,w    
	
	Real(kind=8)	Qc              
	Dimension		Qc(nDim,nQc1,nQc2)
	Real(kind=8)	Qd        ,EndwSav      
	Dimension		Qd(nStifS),EndwSav(4,*)
	character*1		sign
!
!-------------------------------------------- for Check with Quintic
	SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			call DeformOut_MatLab_Pal(SLamdam,Qd,Qc,Conv,sign,iter,
     &                                 	iOut,IoutDef,EndwSav)
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
			call DeformOut_MatLab_Pal(SLamdam,Qd,Qc,Conv,sign,iter,
     &                                 	iOut,IoutDef,EndwSav)
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
			call DeformOut_MatLab_Str(SLamdam,Qd,Qc,Conv,sign,iter,
     &                                 	iOut,IoutDef,EndwSav)
		CASE (4)							! 3D Curved Cantilev.LINMOD:Ex_4
!			call DeformOut_MatLab_LIN(SLamdam,THETAL,Qd,nStifS,
!     &				nQc,nDof,RADIUS,Conv,sign,inut,nPts,iStep,
!     &				nPStep,iOut,IoutDef,EndwSav,Qc,Nel)
		CASE (5)							! 3D Str. Cantilever-Bathe: Ex_5
!			call DeformOut_MatLab_Bat(SLamdam,THETAL,Qd,nStifS,
!     &				nQc,nDof,RADIUS,Conv,sign,inut,nPts,iStep,
!     &				nPStep,iOut,IoutDef,EndwSav,Qc,Nel)
		CASE (6)							! 2D Str. CantiFrameARGYRIS Ex_6
!			call DeformOut_MatLab_ARG(SLamdam,THETAL,Qd,nStifS,
!     &				nQc,nDof,RADIUS,Conv,sign,inut,nPts,iStep,
!     &				nPStep,iOut,IoutDef,EndwSav,Qc,Nel)
		CASE (7:9)    ! FALL THRO'           other: Ex_7-10... 
			return
		CASE (10)							! Hemisphere              :Ex_10
			if(bPrint) then
				call DeformOut_Print_Hem(SLamdam,Qd,Qc,Conv,sign,iter,
     &                                 	iOut,IoutDef,EndwSav)
			endif
			if(bPlot) then
				call DeformOut_MatLab_Hem(SLamdam,Qd,Qc,Conv,sign,iter,
     &                                 	iOut,IoutDef,EndwSav)
			endif
		CASE (11)							! Shallow Shell           :Ex_11
			if(bPrint) then
				call DeformOut_Print_Sco(SLamdam,Qd,Qc,Conv,sign,iter,
     &                                 	iOut,IoutDef,EndwSav)
			endif
			if(bPlot) then
				call DeformOut_MatLab_Sco(SLamdam,Qd,Qc,Conv,sign,iter,
     &                                 	iOut,IoutDef,EndwSav)
			endif
		CASE (12)						   ! 2D Str. Cantile-Tip Twist:Ex_12
			call DeformOut_MatLab_Str_TT(SLamdam,Qd,Qc,Conv,sign,iter,
     &                                 	iOut,IoutDef,EndwSav)
		CASE DEFAULT
			return
	END SELECT
!	=======================================================
!-----------   	
	return
	end
