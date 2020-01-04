!	Subroutine FormGMatrix(HD,nG,FM,nF,C0,nC,G,W,R,AA,CK,Iout)
	Subroutine FormGMatrix(G,nG,nC,nDof,Iout)
!	----------------------------------------------------------------------------- 
!	Inputs
!		HD(nG)			= {dis,rot,disPrimed_1,rotPrimed_1,disPrimed_2,rotPrimed_2}
!		nG				= 18
!		FM(nC)			= {force1,moment1,force2,moment2}
!		nF				= 12
!		C01(nC)			= initial Curvature vector = k01
!		C02(nC)			= initial Curvature vector = k02
!		nC				= 3 (= nDim)
! 	
!	Outputs 
!		G22(nC,nC)		= GThetaBarDelThetaBlock
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
!============================================
	include 'LoadStepIter.h'
	include 'CurParams.h'
	include 'ThetaConstants.h'
	include 'BeamParams.h'
	include 'ShellParams.h'
!==============================================
	Real(kind=8)	G                       
	Dimension		G(nG,nG)
	Real(kind=8)	G12     ,G22     ,G23     ,G24                   
	Dimension		G12(3,3),G22(3,3),G23(3,3),G24(3,3)
!	============================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	===========
	G = zero
!----------------------------------------------------------------- Form GBLocks_Dir_1
	C0		= C01
	Ro		= RR
	Rp		= Rp1
	WMat	= WMat1
	RMat	= RMat1
	CK		= CK1
	AA		= AA1
	FMt		= FMt1
!	-------------------------------------------
	call FormGBlocks(nDof,nC,G12,G22,G23,G24,1,Iout)
!---------------------------------------------------------- Write:
	if((iStep == 9999).AND.(iNut == 2)) Then
		iPrt = 1
		if (iPrt == 1) Then
			write(Iout,1000) 
			write(Iout,1020) "G12", (i,(G12(i,j),j = 1,nC),i=1,nC)
			write(Iout,1020) "G22", (i,(G22(i,j),j = 1,nC),i=1,nC)
			write(Iout,1020) "G23", (i,(G23(i,j),j = 1,nC),i=1,nC)
			write(Iout,1020) "G24", (i,(G24(i,j),j = 1,nC),i=1,nC)
		endif
		iPrt = 0
	endif
!----------------------------------------------------------------- Fill GMatrix for Dir_1
!	---------------------------------- Upper Triangle with Diagonals
	do 10 i = 1,3
	do 10 j = 1,3
	G(i,j+3)	= G12(i,j)
	G(i+3,j+3)	= G22(i,j)
	G(i+3,j+6)	= G23(i,j)
	G(i+3,j+9)	= G24(i,j)
   10 continue
!----------------------------------------------------------------- Form GBLocks_Dir_2
	G12 = zero
	G22 = zero
	G23 = zero
	G24 = zero
!	---------------
	C0		= C02
	Ro		= RR
	Rp		= Rp2
	WMat	= WMat2
	RMat	= RMat2
	CK		= CK2
	AA		= AA2
	FMt		= FMt2
!	-------------------------------------------
	call FormGBlocks(nDof,nC,G12,G22,G23,G24,2,Iout)
!---------------------------------------------------------- Write:
	if((iStep == 2).AND.(iNut == 2)) Then
		iPrt = 0
		if (iPrt == 1) Then
			write(Iout,1005) 
			write(Iout,1020) "G12", (i,(G12(i,j),j = 1,nC),i=1,nC)
			write(Iout,1020) "G22", (i,(G22(i,j),j = 1,nC),i=1,nC)
			write(Iout,1020) "G23", (i,(G23(i,j),j = 1,nC),i=1,nC)
			write(Iout,1020) "G24", (i,(G24(i,j),j = 1,nC),i=1,nC)
		endif
		iPrt = 0
	endif
!----------------------------------------------------------------- Fill GMatrix for Dir_2
!	---------------------------------- Upper Triangle with Diagonals
	do 40 i = 1,3
	do 40 j = 1,3
	G(i  ,j+ 3)	= G(i  ,j+ 3)	+ G12(i,j)
	G(i+3,j+ 3)	= G(i+3,j+ 3)	+ G22(i,j)
	G(i+3,j+12)	= G(i+3,j+12)	+ G23(i,j)
	G(i+3,j+15)	= G(i+3,j+15)	+ G24(i,j)
   40 continue
!-------------------------------------------------- Symmetry:Lower Triangle
	do 50 i = 1,17
	do 50 j = i+1,18
	G(j,i) = G(i,j)
   50 continue	
!---------------------------------------------------------- Write:
	if((iStep == 9999).AND.(iNut == 2)) Then
		iPrt = 1
		if (iPrt == 1) Then
			write(Iout,1030) nG,nG
			do 110 i = 1,nG
			write(Iout,1040) i,(G(i,j),j = 1,nG)
  110			continue
		endif
		iPrt = 0
	endif
!----------------------------------------------------------
	return
!
 1000	format(2x," G Blocks for Direction 1"/)
 1005	format(2x," G Blocks for Direction 2"/)
 1010 format(1X,"Current vector..."/2X,3(f10.7,1X))
 1020 format(2X,A3," Matrix(3,3)"/( (I5,3(f20.7,1X))  ))
 1030 format("G Matrix:G(",I2,",",I2,")"/)
 1040 format(I5/(3(4(f16.6,1X)/)))
	end
