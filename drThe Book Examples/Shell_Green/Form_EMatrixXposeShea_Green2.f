	Subroutine Form_EMatrixXposeShea_Green2(EMat,nG,nE,nC,Iout)
!	----------------------------------------------------------------------------- 
!	Inputs
!		AMat(nC,nC)		= Rotation Matrix
!		nG				= 18
!		C0i(nC)			= initial Curvature vector = k0i for iCurDir i
!		nC				= 3 (= nDim)
!		nE				= 8
!		W(nC,nC)		= W Matrix
!		R1(nC,nC)		= R1 Matrix
!		R2(nC,nC)		= R2 Matrix
!		AAi(nC)			= e + [k0i]d
!		CKi(nC)			= k0i + ki = k0i + W(thetaPrimed)
! 	
!	Outputs 
!		EMat(nG,nE)	= EMat Matrix (18,8)	! Transpose(EMat)
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!============================================
	include 'Material.h'
	include 'LoadStepIter.h'
	include 'CurParams.h'
!	include 'ThetaConstants.h'
	include 'BeamParams.h'
	include 'ShellParams.h'
	include 'EBlocks.h'
!==============================================
	Real(kind=8)	EMat       ,TAMAT     ,TWMAT                      
	Dimension		EMat(nG,nE),TAMAT(3,3),TWMAT(3,3)
	Real(kind=8)	TAxN   ,TANx1   ,TANx2   ,AMA1   ,AMA2                      
	Dimension		TAxN(3),TANx1(3),TANx2(3),AMA1(3),AMA2(3)
	Real(kind=8)	AMA1xN   ,AMA2xN   ,TWAMA1xN   ,TWAMA2xN                         
	Dimension		AMA1xN(3),AMA2xN(3),TWAMA1xN(3),TWAMA2xN(3)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/,onem/-1.0D0/ 
!	----------------------------------------------------------------------- 
	TAMAT = TRANSPOSE(AMAT) 
	TWMAT = TRANSPOSE(WMAT) 
!	============================================================================ dbar term
	TAxN = MATMUL(TAMAT,xNor)
	call CrossProduct(TAxN,C01,TANx1,Iout)
	call CrossProduct(TAxN,C02,TANx2,Iout)
!	============================================================================ dbar(,alfa or beta) term
!	TAxN
!	============================================================================ thetabar term
!	AMA1 = MATMUL(AMAT,AA1)
!	AMA2 = MATMUL(AMAT,AA2)
!	call CrossProduct(AMA1,xNor,AMA1xN,Iout)
!	call CrossProduct(AMA2,xNor,AMA2xN,Iout)
!
	call CrossProduct(AA1,TAxN,AMA1xN,Iout)
	call CrossProduct(AA2,TAxN,AMA2xN,Iout)
!
	TWAMA1xN = MATMUL(TWMat,AMA1xN)
	TWAMA2xN = MATMUL(TWMat,AMA2xN)
!	============================================================================ FORM EMatrix:SHEAR 
!	                                                                                4,5
	do 10 j = 1,3

	EMAT(j   ,4  )  = EMAT(j   ,4  ) + TANx1(j)					! dbar term
	EMat(j   ,5  )	= EMAT(j   ,5  ) + TANx2(j)
!			
	EMAT(j+ 3,4  )  = EMAT(j+ 3,4  ) + TWAMA1xN(j)				! Thetabar term
	EMat(j+ 3,5  )	= EMat(j+ 3,5  ) + TWAMA2xN(j)
!			
	EMAT(j+ 6,4  )  = EMAT(j+ 6,4  ) + TAxN(j)					! dbar,1 term
	EMat(j+12,5  )	= EMat(j+12,5  ) + TAxN(j)					! dbar,2 term
!			
   10 continue
!	============================================================================ END EMatrix:SHEAR
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1030) (i,(EMat(i,j),j = 1,nG),i=1,nE)
	endif
	iPrt = 0
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Current vector..."/2X,3(f10.7,1X))
 1020 format(2X,A3," Matrix(3,3)"/( (I3,3(f10.2,1X))  ))
 1030 format(2X, "E Matrix(12,18)"/(I3,18(f5.0,1X)))
	end
