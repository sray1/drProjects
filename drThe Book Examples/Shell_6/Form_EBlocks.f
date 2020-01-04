	Subroutine FormEBlocks(nC,E11,E12,E13,E22,E24,iCurDir,Iout)
!	----------------------------------------------------------------------------- 
!	Inputs
!		C0i(nC)			= initial Curvature vector  for dir iCurDir
!		nC				= 3
!		AMat			= Rotation Matrix
!		W				= matrix
!		R				= matrix
!		AA				= a Vector for dir iCurDir 
!		CK				= Kc Vector for dir iCurDir
! 	
!	Outputs 
!		E11(nC,nC)		= E11 block
!		E12(nC,nC)		= E12 block
!		E13(nC,nC)		= E13 block
!		E22(nC,nC)		= E22 block
!		E24(nC,nC)		= E24 block
!	------------------------------------------------------------
	Implicit Real(kind=8) (a-h,o-z)
!
!
	include 'ThetaConstants.h'
	include 'BeamParams.h'
!	===============================
	Real(kind=8)	E11       ,E12       ,E13       ,E22                   
	Dimension		E11(nC,nC),E12(nC,nC),E13(nC,nC),E22(nC,nC)
	Real(kind=8)	TAMat                           
	Dimension		TAMat(nC,nC)
	Real(kind=8)	W       ,R       ,E24       ,sAA       ,sKc            
	Dimension		W(nC,nC),R(nC,nC),E24(nC,nC),sAA(nC,nC),sKc(nC,nC)
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	------------------------------------------------------------------- 
	W = WMat
	R = RMat
!	========
!-----------------------------------------------------------------------------------------AAMatTran
	TAMat = TRANSPOSE(AMat)
!-----------------------------------------------------------------------------------------E11Block
	call FormSkew(C0,nC,E11,Iout)		!skew[k0]
	E11 = MATMUL(TAMat, E11)			!AMatTransposeE11
!-----------------------------------------------------------------------------------------E12Block
	call FormSkew(AA,nC,sAA,Iout)		!skew[a]
	E12 = MATMUL(sAA, W)				![a]W
	E12 = MATMUL(TAMat, E12)			!AMatTransposeE12
!-----------------------------------------------------------------------------------------E13Block
	E13 = TAMat							!AMatTransposeE13
!-----------------------------------------------------------------------------------------E22Block
	call FormSkew(CK,nC,sKc,Iout)		!skew[Kc]
	E22 = R + MATMUL(sKc,W)				!R + [Kc]W
	E22 = MATMUL(TAMat, E22)			!AMatTransposeE22
!-----------------------------------------------------------------------------------------E24Block
	E24 = W
	E24 = MATMUL(TAMat, E24)			!AMatTransposeE24
!------------------------------------
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
!		write(Iout,1010) (G(j),j = 1,nS)
		write(Iout,1005) iCurDir
		write(Iout,1020) "E11", (i,(E11(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "E12", (i,(E12(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "E13", (i,(E13(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "E22", (i,(E22(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "E24", (i,(E24(i,j),j = 1,nC),i=1,nC)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1005 format(1X,"Current direction for E_Matrix ="I2/)
 1010 format(1X,"Current vector..."/2X,3(f10.7,1X))
 1020 format(2X,A3," Matrix(3,3)"/
     &        (I5,3(f10.7,1X)/))
	end
