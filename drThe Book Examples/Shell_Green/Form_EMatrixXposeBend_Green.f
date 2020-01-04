	Subroutine Form_EMatrixXposeBend_Green(EMat,nG,nE,nC,Iout)
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
	Real(kind=8)	C011N   ,C022N   ,C012N   ,C021N                          
	Dimension		C011N(3),C022N(3),C012N(3),C021N(3)
	Real(kind=8)	xNC1     ,xNC2     ,xNRC1     ,xNRC2                             
	Dimension		xNC1(3,1),xNC2(3,1),xNRC1(3,1),xNRC2(3,1)
	Real(kind=8)	AN1     ,AN2     ,TAAN1     ,TAAN2                             
	Dimension		AN1(3,1),AN2(3,1),TAAN1(3,1),TAAN2(3,1)
	Real(kind=8)	ANRC11   ,ANRC22   ,ANRC12   ,ANRC21                          
	Dimension		ANRC11(3),ANRC22(3),ANRC12(3),ANRC21(3)
	Real(kind=8)	TE11_1     ,TE11_2     ,TE12_1                      
	Dimension		TE11_1(3,3),TE11_2(3,3),TE12_1(3,3)
	Real(kind=8)	TE12_2     ,TE13_1     ,TE13_2                      
	Dimension		TE12_2(3,3),TE13_1(3,3),TE13_2(3,3)
	Real(kind=8)	TE31_1     ,TE31_2     ,TE32_1                      
	Dimension		TE31_1(3,3),TE31_2(3,3),TE32_1(3,3)
	Real(kind=8)	TE32_2     ,TE35_1     ,TE35_2                      
	Dimension		TE32_2(3,3),TE35_1(3,3),TE35_2(3,3)
	Real(kind=8)	E11_1NRC1     ,E11_2NRC2     ,E11_1NRC2                      
	Dimension		E11_1NRC1(3,1),E11_2NRC2(3,1),E11_1NRC2(3,1)
	Real(kind=8)	E11_2NRC1                           
	Dimension		E11_2NRC1(3,1)
	Real(kind=8)	E12_1NRC1     ,E12_2NRC2     ,E12_1NRC2                      
	Dimension		E12_1NRC1(3,1),E12_2NRC2(3,1),E12_1NRC2(3,1)
	Real(kind=8)	E12_2NRC1                           
	Dimension		E12_2NRC1(3,1)
	Real(kind=8)	E13_1NRC1     ,E13_2NRC2     ,E13_1NRC2                      
	Dimension		E13_1NRC1(3,1),E13_2NRC2(3,1),E13_1NRC2(3,1)
	Real(kind=8)	E13_2NRC1                           
	Dimension		E13_2NRC1(3,1)
!
	Real(kind=8)	E31_1AN1     ,E31_2AN2     ,E31_1AN2                      
	Dimension		E31_1AN1(3,1),E31_2AN2(3,1),E31_1AN2(3,1)
	Real(kind=8)	E31_2AN1                           
	Dimension		E31_2AN1(3,1)
	Real(kind=8)	E32_1TAAN1     ,E32_2TAAN2     ,E32_1TAAN2                      
	Dimension		E32_1TAAN1(3,1),E32_2TAAN2(3,1),E32_1TAAN2(3,1)
	Real(kind=8)	E32_2TAAN1                           
	Dimension		E32_2TAAN1(3,1)
	Real(kind=8)	E35_1TAAN1     ,E35_2TAAN2     ,E35_1TAAN2                      
	Dimension		E35_1TAAN1(3,1),E35_2TAAN2(3,1),E35_1TAAN2(3,1)
	Real(kind=8)	E35_2TAAN1                           
	Dimension		E35_2TAAN1(3,1)

	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/,onem/-1.0D0/ 
!	----------------------------------------------------------------------- 
	TAMAT = TRANSPOSE(AMAT) 
	TWMAT = TRANSPOSE(WMAT) 
!	============================================================================ dbar term
!	--------------------------------------------- (C01 cross C02 + C02 cross C01) N   
	call DotProduct(C01,xNor,dot1,nC,Iout)		! C01 dot Normal
	call DotProduct(C02,xNor,dot2,nC,Iout)		! C02 dot Normal
	call ScaleVector(C01,C011N,dot1,nC,Iout)
	call ScaleVector(C02,C022N,dot2,nC,Iout)
	call ScaleVector(C01,C012N,dot2,nC,Iout)
	call ScaleVector(C02,C021N,dot1,nC,Iout)
	call VectorAdd(C012N,C021N,C012N,nC,Iout)
!	============================================================================ dbar(,alfa or beta) term
!	--------------------------------------------- N cross C01 and N cross C02    
	call CrossProduct(xNor,C01,xNC1,Iout)
	call CrossProduct(xNor,C02,xNC2,Iout)
!	============================================================================ thetabar term
!	--------------------------------------------- (A1 or A2) cross {N cross [(tran(Rot) CK1 or CK2]}    
	call CrossProduct(xNor,MATMUL(TAMat,CK1),xNRC1,Iout)
	call CrossProduct(xNor,MATMUL(TAMat,CK2),xNRC2,Iout)
!
	call CrossProduct(AA1,xNRC1,ANRC11,Iout)
	call CrossProduct(AA2,xNRC2,ANRC22,Iout)
	call CrossProduct(AA1,xNRC2,ANRC12,Iout)
	call CrossProduct(AA2,xNRC1,ANRC21,Iout)
	call VectorAdd(ANRC12,ANRC21,ANRC12,nC,Iout)
!
	ANRC11 = MATMUL(TWMAT,ANRC11)
	ANRC22 = MATMUL(TWMAT,ANRC22)
	ANRC12 = MATMUL(TWMAT,ANRC12)
!	============================================================================ betaStrain terms
	TE11_1 = TRANSPOSE(E11_1)   
	TE11_2 = TRANSPOSE(E11_2)    
	TE12_1 = TRANSPOSE(E12_1)   
	TE12_2 = TRANSPOSE(E12_2)    
	TE13_1 = TRANSPOSE(E13_1)   
	TE13_2 = TRANSPOSE(E13_2)    
!	--------------------------------------------- trans(betaE11) {N cross [(tran(Rot) CK1 or CK2]}
	E11_1NRC1 = MATMUL(TE11_1,xNRC1)
	E11_2NRC2 = MATMUL(TE11_2,xNRC2)
	E11_1NRC2 = MATMUL(TE11_1,xNRC2)
	E11_2NRC1 = MATMUL(TE11_2,xNRC1)
	call VectorAdd(E11_1NRC2,E11_2NRC1,E11_1NRC2,nC,Iout)
!	--------------------------------------------- trans(betaE12) {N cross [(tran(Rot) CK1 or CK2]}    
	E12_1NRC1 = MATMUL(TE12_1,xNRC1)
	E12_2NRC2 = MATMUL(TE12_2,xNRC2)
	E12_1NRC2 = MATMUL(TE12_1,xNRC2)
	E12_2NRC1 = MATMUL(TE12_2,xNRC1)
	call VectorAdd(E12_1NRC2,E12_2NRC1,E12_1NRC2,nC,Iout)
!	--------------------------------------------- trans(betaE13) {N cross [(tran(Rot) CK1 or CK2]}    
	E13_1NRC1 = MATMUL(TE13_1,xNRC1)
	E13_2NRC2 = MATMUL(TE13_2,xNRC2)
	E13_1NRC2 = MATMUL(TE13_1,xNRC2)
	E13_2NRC1 = MATMUL(TE13_2,xNRC1)
!	============================================================================ kiStrain terms
	TE32_1 = TRANSPOSE(E32_1)   
	TE32_2 = TRANSPOSE(E32_2)    
	TE35_1 = TRANSPOSE(E35_1)   
	TE35_2 = TRANSPOSE(E35_2)    
!
	call CrossProduct(AA1,xNor,AN1,Iout)
	call CrossProduct(AA2,xNor,AN2,Iout)
	TAAN1 = MATMUL(TAMAT,AN1)
	TAAN2 = MATMUL(TAMAT,AN2)
!	--------------------------------------------- trans(kiE32) {(Aalfa or Abeta) cross N}    
	E32_1TAAN1 = MATMUL(TE32_1,TAAN1)
	E32_2TAAN2 = MATMUL(TE32_2,TAAN2)
	E32_1TAAN2 = MATMUL(TE32_1,TAAN2)
	E32_2TAAN1 = MATMUL(TE32_2,TAAN1)
	call VectorAdd(E32_1TAAN2,E32_2TAAN1,E32_1TAAN2,nC,Iout)
!	--------------------------------------------- trans(kiE35 or kiE46) {(Aalfa or Abeta) cross N}    
	E35_1TAAN1 = MATMUL(TE35_1,TAAN1)
	E35_2TAAN2 = MATMUL(TE35_2,TAAN2)
	E35_1TAAN2 = MATMUL(TE35_1,TAAN2)
	E35_2TAAN1 = MATMUL(TE35_2,TAAN1)
!	============================================================================ FORM EMatrix:BENDING 6,7,8
	do 10 j = 1,3
	EMAT(j   ,6  )  = EMAT(j   ,6  ) + Two * C011N(j)				! dbar term
	EMat(j   ,7  )	= EMAT(j   ,7  ) + Two * C022N(j)
	EMat(j   ,8  )	= EMAT(j   ,8  ) + C012N(j)
!			
	EMAT(j+ 6,6  )  = EMAT(j+ 6,6  ) + Two * xNC1(j,1)				! dbar,1 term
	EMat(j+12,7  )	= EMat(j+12,7  ) + Two * xNC2(j,1)				! dbar,2 term
	EMat(j+ 6,8  )	= EMat(j+ 6,8  ) + xNC1(j,1)					! dbar,1 term
	EMat(j+12,8  )	= EMat(j+12,8  ) + xNC2(j,1)					! dbar,2 term
!			
	EMAT(j+ 3,6  )  = EMAT(j+ 3,6  ) + Two * ANRC11(j)				! Thetabar term
	EMat(j+ 3,7  )	= EMat(j+ 3,7  ) + Two * ANRC22(j)
	EMat(j+ 3,8  )	= EMat(j+ 3,8  ) + ANRC12(j)
!			
	EMAT(j   ,6  )  = EMAT(j   ,6  ) + Two * E11_1NRC1(j,1)			! betaStrain terms: dbar
	EMat(j   ,7  )	= EMAT(j   ,7  ) + Two * E11_2NRC2(j,1)
	EMat(j   ,8  )	= EMAT(j   ,8  ) + E11_1NRC2(j,1)
!
	EMAT(j+ 3,6  )  = EMAT(j+ 3,6  ) + Two * E12_1NRC1(j,1)			!			      : thetabar 
	EMat(j+ 3,7  )	= EMat(j+ 3,7  ) + Two * E12_2NRC2(j,1)
	EMat(j+ 3,8  )	= EMat(j+ 3,8  ) + E12_1NRC2(j,1)
!
	EMAT(j+ 6,6  )  = EMAT(j+ 6,6  ) + Two * E13_1NRC1(j,1)			! betaStrain terms: dbar,1 
	EMat(j+12,7  )	= EMat(j+12,7  ) + Two * E13_2NRC2(j,1)			!                   dbar,2 
	EMat(j+ 6,8  )	= EMat(j+ 6,8  ) + E13_1NRC2(j,1)				!                   dbar,1
	EMat(j+12,8  )	= EMat(j+12,8  ) + E13_2NRC1(j,1)				!                   dbar,2
!			
	EMAT(j+ 3,6  )  = EMAT(j+ 3,6  ) + Two * E32_1TAAN1(j,1)		! kiStrain terms: thetabar 
	EMat(j+ 3,7  )	= EMat(j+ 3,7  ) + Two * E32_2TAAN2(j,1)
	EMat(j+ 3,8  )	= EMat(j+ 3,8  ) + E32_1TAAN2(j,1)
!
	EMAT(j+ 9,6  )  = EMAT(j+ 9,6  ) + Two * E35_1TAAN1(j,1)		! kiStrain terms: thetabar,1 
	EMat(j+15,7  )	= EMat(j+15,7  ) + Two * E35_2TAAN2(j,1)		                  thetabar,2 
	EMat(j+ 9,8  )	= EMat(j+ 9,8  ) + E35_1TAAN2(j,1)				!                 thetabar,1
	EMat(j+15,8  )	= EMat(j+15,8  ) + E35_2TAAN1(j,1)				!                 thetabar,2
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
