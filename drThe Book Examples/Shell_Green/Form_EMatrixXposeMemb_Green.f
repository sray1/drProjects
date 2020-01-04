	Subroutine Form_EMatrixXposeMemb_Green(EMat,nG,nE,nC,Iout)
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
	Real(kind=8)	EMat       !,TAMAT     ,TWMAT                      
	Dimension		EMat(nG,nE)!,TAMAT(3,3),TWMAT(3,3)
	Real(kind=8)	TE11_1     ,TE11_2     ,TE12_1                      
	Dimension		TE11_1(3,3),TE11_2(3,3),TE12_1(3,3)
	Real(kind=8)	TE12_2     ,TE13_1     ,TE13_2                      
	Dimension		TE12_2(3,3),TE13_1(3,3),TE13_2(3,3)
	Real(kind=8)	xAA1     ,xAA2                         
	Dimension		xAA1(3,1),xAA2(3,1)
	Real(kind=8)	E11_1AA1     ,E11_2AA2                           
	Dimension		E11_1AA1(3,1),E11_2AA2(3,1)
	Real(kind=8)	E12_1AA1     ,E12_2AA2                           
	Dimension		E12_1AA1(3,1),E12_2AA2(3,1)
	Real(kind=8)	E13_1AA1     ,E13_2AA2                           
	Dimension		E13_1AA1(3,1),E13_2AA2(3,1)

	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/,onem/-1.0D0/ 
!	============================================================================ betaStrain terms
	TE11_1 = TRANSPOSE(E11_1)   
	TE11_2 = TRANSPOSE(E11_2)    
	TE12_1 = TRANSPOSE(E12_1)   
	TE12_2 = TRANSPOSE(E12_2)    
	TE13_1 = TRANSPOSE(E13_1)   
	TE13_2 = TRANSPOSE(E13_2)    
!
	do 5 i = 1,3
	xAA1(i,1) = AA1(i)
	xAA2(i,1) = AA2(i)
    5 continue
!	--------------------------------------------- trans(betaE11_1) {aa1} or trans(betaE11_2) {aa2}
	E11_1AA1 = MATMUL(TE11_1,xAA1)
	E11_2AA2 = MATMUL(TE11_2,xAA2)
!	--------------------------------------------- trans(betaE12_1) {aa1} or trans(betaE12_2) {aa2}    
	E12_1AA1 = MATMUL(TE12_1,xAA1)
	E12_2AA2 = MATMUL(TE12_2,xAA2)
!	--------------------------------------------- trans(betaE13_1) {aa1} or trans(betaE13_2) {aa2}    
	E13_1AA1 = MATMUL(TE13_1,xAA1)
	E13_2AA2 = MATMUL(TE13_2,xAA2)
!	============================================================================ FORM EMatrix:MEMMBRANE 
!	                                                                                1,2,3
	do 10 j = 1,3

	EMAT(j   ,1  )  = EMAT(j   ,1  ) + Two * E11_1AA1(j,1)				! dbar term
	EMat(j   ,2  )	= EMAT(j   ,2  ) + Two * E11_2AA2(j,1)
	EMat(j   ,3  )	= EMAT(j   ,3  ) + E11_1AA1(j,1) + E11_2AA2(j,1)
!			
	EMAT(j+ 3,1  )  = EMAT(j+ 3,1  ) + Two * E12_1AA1(j,1)				! Thetabar term
	EMat(j+ 3,2  )	= EMat(j+ 3,2  ) + Two * E12_2AA2(j,1)
	EMat(j+ 3,3  )	= EMat(j+ 3,3  ) + E12_1AA1(j,1) + E12_2AA2(j,1)
!			
	EMAT(j+ 6,1  )  = EMAT(j+ 6,1  ) + Two * E13_1AA1(j,1)				! dbar,1 term
	EMat(j+12,2  )	= EMat(j+12,2  ) + Two * E13_2AA2(j,1)				! dbar,2 term
	EMat(j+ 6,3  )	= EMat(j+ 6,3  ) + E13_1AA1(j,1)					! dbar,1 term
	EMat(j+12,3  )	= EMat(j+12,3  ) + E13_2AA2(j,1)					! dbar,2 term
!			
   10 continue
!	============================================================================ END EMatrix:MEMBRANE
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
 1030 format(2X, "E Matrix(8,18)"/(I3,18(f5.0,1X)))
	end
