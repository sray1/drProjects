	Subroutine AddGBlocks_Con_J2(nF,nC,G12,G22,G23,iCurDir,Iout)
!	----------------------------------------------------------------------------- 
!	Inputs
!		FM(nC)			= {forcei,momenti} for dir iCurDir 
!		nF				= 6
!		C0(nC)			= initial Curvature vector for dir iCurDir
!		nC				= 3
! 	
!	Outputs 
!		G22(nC,nC)		= GThetaBarDelThetaBlock
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	include 'ThetaConstants.h'
	include 'BeamParams.h'
	include 'EBlocks.h'
!	===============================
	Real(kind=8)	G12       ,G22       ,G23                         
	Dimension		G12(nC,nC),G22(nC,nC),G23(nC,nC)
	Real(kind=8)	W       ,SHat            
	Dimension		W(nC,nC),SHat(nC,nC)
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	------------------------------------------------------------------- 
	G12 = zero
	G22 = zero
	G23 = zero
!	========
	W = WMat
	call FormSkew(Hat,nC,SHat,Iout)		!skew[M]
!	========
	if(iCurDir == 1) then
		G12 = MATMUL(MATMUL(TRANSPOSE(E11),SHat),W)
		G22 = MATMUL(MATMUL(TRANSPOSE(E12),SHat),W)	
		G23 = MATMUL(MATMUL(TRANSPOSE(E13),SHat),W)	
	elseif (iCurDir == 2) then 
		G12 = MATMUL(MATMUL(TRANSPOSE(E31),SHat),W)
		G22 = MATMUL(MATMUL(TRANSPOSE(E32),SHat),W)	
		G23 = MATMUL(MATMUL(TRANSPOSE(E35),SHat),W)	
	endif
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
!		write(Iout,1010) (G(j),j = 1,nS)
		write(Iout,1005) iCurDir
		write(Iout,1020) "G12", (i,(G12(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "G22", (i,(G22(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "G23", (i,(G23(i,j),j = 1,nC),i=1,nC)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1005 format(1X,"Current direction for GC_Matrix_J2 ="I2/)
 1010 format(1X,"Current vector..."/2X,3(f10.7,1X))
 1020 format(2X,A3," Matrix(3,3)"/( (I5,3(f20.7,1X))  ))
	end
