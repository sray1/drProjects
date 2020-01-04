	Subroutine FormGMatrix(HD,nG,FM,nF,C0,nC,G,W,R,AA,CK,Iout)
!	----------------------------------------------------------------------------- 
!	Inputs
!		HD(nG)			= {dis,rot,disPrimed,rotPrimed}
!		nG				= 12
!		FM(nC)			= {force,moment}
!		nF				= 6
!		C0(nC)			= initial Curvature vector = {torsion,0,curvature}
!		nC				= 3
! 	
!	Outputs 
!		G22(nC,nC)		= GThetaBarDelThetaBlock
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	HD    ,FM    ,C0    ,G                       
	Dimension		HD(nG),FM(nF),C0(nC),G(nG,nG)
	Real(kind=8)	G12       ,G22       ,G23       ,G24                   
	Dimension		G12(nC,nC),G22(nC,nC),G23(nC,nC),G24(nC,nC)
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!----------------------------------------------------------------------- Get GBlocks
	call FormGBlocks(HD,nG,FM,nF,C0,nC,W,R,AA,CK,G12,G22,G23,G24,Iout)
!----------------------------------------------------------------------- Form GMatrix
	G = zero
!	---------------------------------- Upper Triangle with Diagonals
	do 10 i = 1,3
	do 10 j = 1,3
	G(i,j+3)	= G12(i,j)
	G(i+3,j+3)	= G22(i,j)
	G(i+3,j+6)	= G23(i,j)
	G(i+3,j+9)	= G24(i,j)
   10 continue
!-------------------------------------------------- Symmetry:Lower Triangle
	do 50 i = 1,11
	do 50 j = i+1,12
	G(j,i) = G(i,j)
   50 continue	
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1020) "G12", (i,(G12(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "G22", (i,(G22(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "G23", (i,(G23(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "G24", (i,(G24(i,j),j = 1,nC),i=1,nC)
	endif
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1030) nG,nG
		do 110 i = 1,nG
		write(Iout,1040) i,(G(i,j),j = 1,nG)
  110	continue
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Current vector..."/2X,3(f10.7,1X))
 1020 format(2X,A3," Matrix(3,3)"/( (I5,3(f20.7,1X))  ))
 1030 format("G Matrix:G(",I2,",",I2,")"/)
 1040 format(I5/(3(4(f16.6,1X)/)/))
	end
