	Subroutine Get_ElementCoords(iOut)
	Implicit Real(kind=8) (a-h,o-z)
!-------------------------------------------- 
	common A(1000000)
!
	common/Wpointers/  nSx,nRoCOld,nCuCOld,nRoKSav,nCKKSav,n1a,n1b,
     &				   n2,n2a,n2b,n3a,n3b,n3,n4,n4b,n5,nxo,nx,nBfors,
     &                   nStifK,nBo,nB,nPLoad,nGuLam,nUm,nUmO,nxmR,
     &				   nxm,nxmO,ndeltaUi,ndeltaUi1,ndeltaUi2,ndelUi,
     &				   ndelUiO,ndelUip11,ndelUip12,n7,n6,n6R,n2c
	common/SizeVar/	  iGeom,iCont,nDim,nQc,nSup,nDof,nQd,nElem,
     &                  nStifEL,Nint,nCInt,nStifS,nStifC,
     &				  nStifN,nLoadLoc,NelType
	common/Geometry/THETAP,THETAL,RADIUS,XLENGTH,DEPTH,WIDTH
	common/Examples/cEx(10),nEx
	character (30)	cEx
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/ 
!-------------------------------------------------------------- Element Data:Bezier Coordinates
	iDebug = 0
!-------------------------------------------- for Check with Quintic
	SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			Nel = 1
			if(iDebug == 1) write(iOut,2004)
			call BZ_Coords_EL1_Pal(A(n1a),nDim,nQc,RADIUS,iOut)
			if(nElem == 2) Then
			Nel = 2
			if(iDebug == 1) write(iOut,2005)
				call BZ_Coords_EL2(A(n1b),nDim,nQc,RADIUS,iOut)
			endif
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
			Nel = 1
			if(iDebug == 1) write(iOut,2004)
			call BZ_Coords_EL1_Pal(A(n1a),nDim,nQc,RADIUS,iOut)
			if(nElem == 2) Then
			Nel = 2
			if(iDebug == 1) write(iOut,2005)
				call BZ_Coords_EL2(A(n1b),nDim,nQc,RADIUS,iOut)
			endif
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
			Nel = 1
			if(iDebug == 1) write(iOut,2004)
			call BZ_Coords_EL1_Str(A(n1a),nDim,nQc,RADIUS,iOut)
			if(nElem == 2) Then
			Nel = 2
			if(iDebug == 1) write(iOut,2005)
				call BZ_Coords_EL2(A(n1b),nDim,nQc,RADIUS,iOut)
			endif
		CASE (4)							! 3D Curved Cantilev.LINMOD:Ex_4
			Nel = 1
			if(iDebug == 1) write(iOut,2004)
			call BZ_Coords_EL1_LIN(A(n1a),nDim,nQc,RADIUS,nElem,iOut)		!to change
	call DumpIntegerVar(Nel,"Element Number",1,iOut)
	call DumpRealMatrix(A(n1a),nDim,nQc,"Geometry Coords",1,iOut)
			if(nElem == 2) Then
				Nel = 2
				if(iDebug == 1) write(iOut,2005)
				call BZ_Coords_EL2_LIN(A(n1b),nDim,nQc,RADIUS,iOut)				!to change
			endif
		CASE (5)							! 3D Curved Cantilever-Bathe:Ex_5
			Nel = 1
			if(iDebug == 1) write(iOut,2004)
			call BZ_Coords_EL1_Bat(A(n1a),nDim,nQc,RADIUS,nElem,iOut)
	call DumpIntegerVar(Nel,"Element Number",1,iOut)
	call DumpRealMatrix(A(n1a),nDim,nQc,"Geometry Coords",1,iOut)
			if(nElem == 2) Then
				Nel = 2
				if(iDebug == 1) write(iOut,2005)
				call BZ_Coords_EL2_Bat(A(n1b),nDim,nQc,RADIUS,iOut)
			endif
		CASE (6:10)    ! FALL THRO'           Other: Ex_5... 
		CASE DEFAULT
			return
	END SELECT
!	=======================================================
	return
!
 2004 Format(/2x,"Entering: BZ_Coords_EL1"/)
 2005 Format(/2x,"Entering: BZ_Coords_EL2"/)
!	--------     		
	end
