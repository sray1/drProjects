	Subroutine Form_EMatrixXposeBend_Green2(EMat,nG,nE,nC,Iout)
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
	Real(kind=8)	TRMA1     ,TRMA2     ,TWAxN1   ,TWAxN2                     
	Dimension		TRMA1(3,3),TRMA2(3,3),TWAxN1(3),TWAxN2(3)
	Real(kind=8)	C011N   ,C022N   ,C012N   ,C021N                          
	Dimension		C011N(3),C022N(3),C012N(3),C021N(3)
	Real(kind=8)	xNC1   ,xNC2   ,RAA1   ,RAA2                             
	Dimension		xNC1(3),xNC2(3),RAA1(3),RAA2(3)
	Real(kind=8)	RAAxN1   ,RAAxN2   ,TANC1   ,TANC2                             
	Dimension		RAAxN1(3),RAAxN2(3),TANC1(3),TANC2(3)
	Real(kind=8)	TWANC11   ,TWANC22   ,TWANC12   ,TWANC21   
	Dimension		TWANC11(3),TWANC22(3),TWANC12(3),TWANC21(3)
	Real(kind=8)	TXRAN11   ,TXRAN22   ,TXRAN12   ,TXRAN21   
	Dimension		TXRAN11(3),TXRAN22(3),TXRAN12(3),TXRAN21(3)

	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/,onem/-1.0D0/ 
!	----------------------------------------------------------------------- 
	TAMAT = TRANSPOSE(AMAT) 
	TWMAT = TRANSPOSE(WMAT) 
	TRMA1 = TRANSPOSE(RMAT1) 
	TRMA2 = TRANSPOSE(RMAT2) 
!	============================================================================ common terms
	call CrossProduct(xNor,CK1,xNC1,Iout)		! N cross CK1
	call CrossProduct(xNor,CK2,xNC2,Iout)		! N cross CK2		
	RAA1 = MATMUL(AMat,AA1)						! (R A1) 
	RAA2 = MATMUL(AMat,AA2)						! (R A2)
	call CrossProduct(RAA1,xNor,RAAxN1,Iout)	! (R A1) cross N
	call CrossProduct(RAA2,xNor,RAAxN2,Iout)	! (R A2) cross N
!	============================================================================ dbar term
	call CrossProduct(MATMUL(TAMat,xNC1),C01,C011N,Iout)
	call CrossProduct(MATMUL(TAMat,xNC2),C02,C022N,Iout)
	call CrossProduct(MATMUL(TAMat,xNC1),C02,C012N,Iout)
	call CrossProduct(MATMUL(TAMat,xNC2),C01,C021N,Iout)
	call VectorAdd(C012N,C021N,C012N,nC,Iout)
!	============================================================================ dbar,alfa terms
	TANC1 = MATMUL(TAMAT,xNC1)
	TANC2 = MATMUL(TAMAT,xNC2)
!	============================================================================ thetabar term
!	--------------------------------------------- Wtran(AMatAalf) cross (N cross CKbet)     
	call CrossProduct(MATMUL(TWMAT,RAA1),xNC1,TWANC11,Iout)
	call CrossProduct(MATMUL(TWMAT,RAA2),xNC2,TWANC22,Iout)
	call CrossProduct(MATMUL(TWMAT,RAA1),xNC2,TWANC12,Iout)
	call CrossProduct(MATMUL(TWMAT,RAA2),xNC1,TWANC21,Iout)
	call VectorAdd(TWANC12,TWANC21,TWANC12,nC,Iout)
!	---------------------------------------------  XalfTran(AmatAbet cross N)  
	TXRAN11 = MATMUL(TRMA1,RAAxN1)
	TXRAN22 = MATMUL(TRMA2,RAAxN2)
	TXRAN12 = MATMUL(TRMA1,RAAxN2)
	TXRAN21 = MATMUL(TRMA2,RAAxN1)
	call VectorAdd(TXRAN12,TXRAN21,TXRAN12,nC,Iout)
!	============================================================================ thetabar,alfa term
!	--------------------------------------------- Ttran((AmatAbet cross N))     
	TWAxN1 = MATMUL(TWMat,RAAxN1)				 
	TWAxN2 = MATMUL(TWMat,RAAxN2)				 
!	============================================================================ FORM EMatrix:BENDING 6,7,8
	do 10 j = 1,3
	EMAT(j   ,6  )  = EMAT(j   ,6  ) + Two * C011N(j)								! dbar term
	EMat(j   ,7  )	= EMAT(j   ,7  ) + Two * C022N(j)
	EMat(j   ,8  )	= EMAT(j   ,8  ) + C012N(j)
!			
	EMAT(j+ 6,6  )  = EMAT(j+ 6,6  ) + Two * TANC1(j)								! dbar,1 term
	EMat(j+12,7  )	= EMat(j+12,7  ) + Two * TANC2(j)								! dbar,2 term
	EMat(j+ 6,8  )	= EMat(j+ 6,8  ) + TANC1(j)										! dbar,1 term
	EMat(j+12,8  )	= EMat(j+12,8  ) + TANC2(j)										! dbar,2 term
!			
	EMAT(j+ 3,6  )  = EMAT(j+ 3,6  ) + Two * (TWANC11(j) + TXRAN11(j))				! Thetabar term
	EMat(j+ 3,7  )	= EMat(j+ 3,7  ) + Two * (TWANC22(j) + TXRAN22(j))
	EMat(j+ 3,8  )	= EMat(j+ 3,8  ) + (TWANC12(j) + TXRAN12(j))
!			
!
	EMAT(j+ 9,6  )  = EMAT(j+ 9,6  ) + Two * TWAxN1(j)								! thetabar,1 
	EMat(j+15,7  )	= EMat(j+15,7  ) + Two * TWAxN2(j)				                ! thetabar,2 
	EMat(j+ 9,8  )	= EMat(j+ 9,8  ) + TWAxN2(j)									! thetabar,1
	EMat(j+15,8  )	= EMat(j+15,8  ) + TWAxN1(j)									! thetabar,2
!			
   10 continue
!	============================================================================ END EMatrix:BENDING 6,7,8
!	---------------------------------------------------------- Write:
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
