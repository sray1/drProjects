	Subroutine Get_ElementCoords(iOut)
	Implicit Real(kind=8) (a-h,o-z)
!-------------------------------------------- 
	include 'Blank.h'
	include 'Wpointers.h'
	include 'SizeVar.h'
	include 'geometry.h'
	include 'Examples.h'
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/ 
!-------------------------------------------------------------- Element Data:Bezier Coordinates
	iDebug = 0
!-------------------------------------------- for Check with Quintic
	SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			Nel = 1
			if(iDebug == 1) write(iOut,2004)
			call BZ_Coords_EL1_Pal
     &				(A(n1a),nDim,nQc1,nQc2,RADIUS,iOut)
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
			Nel = 1
			if(iDebug == 1) write(iOut,2004)
			call BZ_Coords_EL1_Pal
     &				(A(n1a),nDim,nQc1,nQc2,RADIUS,iOut)
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
			Nel = 1
			if(iDebug == 1) write(iOut,2004)
			call BZ_Coords_EL1_Str
     &				(A(n1a),nDim,nQc1,nQc2,RADIUS,iOut)
	call DumpIntegerVar(Nel,"Element Number",1,iOut)
	call DumpRealMatrix3(A(n1a),nDim,nQc1,nQc2,"Geometry Coords",1,
     &				iOut)
		CASE (4)							! 3D Curved Cantilev.LINMOD:Ex_4
			Nel = 1
			if(iDebug == 1) write(iOut,2004)
!				call BZ_Coords_EL1_LIN
!     &				(A(n1a),nDim,nQc1,nQc2,RADIUS,nElem,iOut)		!to change
	call DumpIntegerVar(Nel,"Element Number",1,iOut)
	call DumpRealMatrix(A(n1a),nDim,nQc,"Geometry Coords",1,iOut)
			if(nElem == 2) Then
				Nel = 2
				if(iDebug == 1) write(iOut,2005)
!				call BZ_Coords_EL2_LIN
!     &				(A(n1b),nDim,nQc1,nQc2,RADIUS,iOut)				!to change
			endif
		CASE (5)							! 3D Curved Cantilever-Bathe:Ex_5
			Nel = 1
			if(iDebug == 1) write(iOut,2004)
!				call BZ_Coords_EL1_Bat
!     &				(A(n1a),nDim,nQc1,nQc2,RADIUS,nElem,iOut)
	call DumpIntegerVar(Nel,"Element Number",1,iOut)
	call DumpRealMatrix(A(n1a),nDim,nQc,"Geometry Coords",1,iOut)
			if(nElem == 2) Then
				Nel = 2
				if(iDebug == 1) write(iOut,2005)
!				call BZ_Coords_EL2_Bat
!     &				(A(n1b),nDim,nQc1,nQc2,RADIUS,iOut)
			endif
		CASE (6)							! 2D Frame Buckling-Argyris  Ex_6
			Nel = 1
			if(iDebug == 1) write(iOut,2004)
	!		call BZ_Coords_EL1_ARG
!				(A(n1a),nDim,nQc1,nQc2,RADIUS,nElem,iOut)
			if(nElem == 2) Then
				Nel = 2
				if(iDebug == 1) write(iOut,2005)
	!			call BZ_Coords_EL2_ARG
     &!				(A(n1b),nDim,nQc1,nQc2,RADIUS,iOut)
			endif
		CASE (7:10)    ! FALL THRO'           Other: Ex_5... 
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