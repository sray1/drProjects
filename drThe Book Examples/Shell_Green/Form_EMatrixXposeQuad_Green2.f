	Subroutine Form_EMatrixXposeQuad_Green2(EMat,nG,nE,nC,Iout)
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
	Real(kind=8)	EMat       ,TWMAT                      
	Dimension		EMat(nG,nE),TWMAT(3,3)
	Real(kind=8)	TRMA1     ,TRMA2     ,T1   ,T2                     
	Dimension		TRMA1(3,3),TRMA2(3,3),T1(3),T2(3)
	Real(kind=8)	CKN1   ,CKN2   ,xNor1   ,xNor2                          
	Dimension		CKN1(3),CKN2(3),xNor1(3),xNor2(3)
	Real(kind=8)	X11   ,X22   ,X12   ,X21                             
	Dimension		X11(3),X22(3),X12(3),X21(3)

	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/,onem/-1.0D0/ 
!	----------------------------------------------------------------------- 
	TWMAT = TRANSPOSE(WMAT) 
	TRMA1 = TRANSPOSE(RMAT1) 
	TRMA2 = TRANSPOSE(RMAT2) 
!	============================================================================ common terms
	call DotProduct(xNor,CK1,dot,nC,Iout)
	call ScaleVector(xNor,xNor1,dot*-1.D0,nC,Iout)
	call VectorAdd(CK1,xNor1,CKN1,nC,Iout)

	call DotProduct(xNor,CK2,dot,nC,Iout)
	call ScaleVector(xNor,xNor2,dot*-1.D0,nC,Iout)
	call VectorAdd(CK2,xNor2,CKN2,nC,Iout)
!	============================================================================ thetabar term
	X11 = MATMUL(TRMA1,CKN1)
	X22 = MATMUL(TRMA2,CKN2)
	X12 = MATMUL(TRMA1,CKN2)
	X21 = MATMUL(TRMA2,CKN1)
	call VectorAdd(X12,X21,X12,nC,Iout)
!	============================================================================ thetabar,alfa term
	T1 = MATMUL(TWMAT,CKN1)
	T2 = MATMUL(TWMAT,CKN2)
!	============================================================================ FORM EMatrix:QUADRAT
!																					 9,10,11
	do 10 j = 1,3
!			
	EMAT(j+ 3, 9)   = EMAT(j+ 3, 9) + Two * X11(j)									! Thetabar term
	EMat(j+ 3,10)	= EMat(j+ 3,10) + Two * X22(j)
	EMat(j+ 3,11)	= EMat(j+ 3,11) + X12(j)
!			
!
	EMAT(j+ 9, 9)   = EMAT(j+ 9, 9) + Two * T1(j)									! thetabar,1 
	EMat(j+15,10)	= EMat(j+15,10) + Two * T2(j)									! thetabar,2 
	EMat(j+ 9,11)	= EMat(j+ 9,11) + T2(j)											! thetabar,1
	EMat(j+15,11)	= EMat(j+15,11) + T1(j)											! thetabar,2
!			
   10 continue
!	============================================================================ END EMatrix:QUADRAT
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
