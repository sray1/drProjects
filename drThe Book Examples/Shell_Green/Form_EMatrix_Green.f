	Subroutine FormEMatrix_Green(EMat,nE,nG,nC,Iout)
!	----------------------------------------------------------------------------- 
!	Inputs
!		AMat(nC,nC)		= Rotation Matrix
!		nG				= 18
!		C0i(nC)			= initial Curvature vector = k0i for iCurDir i
!		nC				= 3 (= nDim)
!		nE				= 12
!		W(nC,nC)		= W Matrix
!		R1(nC,nC)		= R1 Matrix
!		R2(nC,nC)		= R2 Matrix
!		AAi(nC)			= e + [k0i]d
!		CKi(nC)			= k0i + ki = k0i + W(thetaPrimed)
! 	
!	Outputs 
!		EMatT(nG,nE)	= EMatT Matrix (18,8)	! Transpose(EMat)
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!	============================================
	include 'LoadStepIter.h'
!	==============================================
	Real(kind=8)	EMat       ,TEMat 
	Dimension		EMat(nE,nG),TEMat(nG,nE)
	LOGICAL			bGreTyp                     
!	
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,half/0.5D0/,onem/-1.0D0/ 
!----------------------------------------------------------------------- Form EMatrix
	TEMat = zero
!
	bGreTyp = 2
	if(bGreTyp == 1) then			! thro'strain
		call Form_EMatrixXposeMemb_Green(TEMat,nG,nE,nC,Iout)
		call Form_EMatrixXposeShea_Green(TEMat,nG,nE,nC,Iout)
		call Form_EMatrixXposeBend_Green(TEMat,nG,nE,nC,Iout)
	else							! thro'disp/rot
		call Form_EMatrixXposeMemb_Green2(TEMat,nG,nE,nC,Iout)
		call Form_EMatrixXposeShea_Green2(TEMat,nG,nE,nC,Iout)
		call Form_EMatrixXposeBend_Green2(TEMat,nG,nE,nC,Iout)
		call Form_EMatrixXposeQuad_Green2(TEMat,nG,nE,nC,Iout)
	endif
!---------------------------------------------------------- Write:
	EMat = half*TRANSPOSE(TEMat)
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1030) (i,(TEMat(i,j),j = 1,nE),i=1,nG)
	endif
	iPrt = 0
!----------------------------------------------------------
	return
!
 1030 format(2X, "E-transpose Matrix(8,18)"/(I3,8(F9.0,1X)))
	end
