!	Subroutine FormEMatrix(AMat,C0,nC,E,nE,W,R,AA,CK,nG,Iout)
	Subroutine FormEMatrix_1_Con(EMatb,EMatk,nE,nG,nC,iDir,Iout)
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
!		EMat(nE,nG)		= EMat Matrix (12,18)
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!============================================
	include 'Material.h'
	include 'LoadStepIter.h'
	include 'CurParams.h'
	include 'ThetaConstants.h'
	include 'BeamParams.h'
	include 'ShellParams.h'
	include 'EBlocks.h'
!==============================================
	Real(kind=8)	EMatb      ,EMatk                             
	Dimension		EMatb(1,nG),EMatk(1,nG)
	Real(kind=8)	E22       ,E24                   
	Dimension		E22(nC,nC),E24(nC,nC)
	Real(kind=8)	CoA     ,CoB                            
	Dimension		CoA(3,3),CoB(3,3)
!	-------------------------------------------
	Real(kind=8)	Ab12       ,Ak22          
	Dimension		Ab12(nC,nC),Ak22(nC,nC)
	Real(kind=8)	A2H     ,E1C     ,E2C     ,E3C                              
	Dimension		A2H(1,3),E1C(1,3),E2C(1,3),E3C(1,3)
	Real(kind=8)	E22C     ,E24C                                   
	Dimension		E22C(1,3),E24C(1,3)
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/,onem/-1.0D0/ 
	DATA A2H/0.D0,1.0D0,0.D0/
!----------------------------------------------------------------------- Get EBlocks for dir 1
!	===============================================
	call FormEBlocks(nC,E11,E12,E13,E22,E24,1,Iout)
	A12 = zero
	call FormAddEBlock_Con(nC,Ab12,Ak22,1,Iout)
	E12 = E12 - Ab12
	E22 = E22 - Ak22
!	----------------------------------------------------- E12
	E1C = MATMUL(A2H,E11)	
	E2C = MATMUL(A2H,E12)	
	E3C = MATMUL(A2H,E13)	
	E22C = MATMUL(A2H,E22)	
	E24C = MATMUL(A2H,E24)	
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
			call DumpStringVar("Direction 1",iPrt,iOut)
			call DumpRealArray(E1C,nC,"E1C",iPrt,iOut)
			call DumpRealArray(E2C,nC,"E2C",iPrt,iOut)
			call DumpRealArray(E3C,nC,"E3C",iPrt,iOut)
	endif
!----------------------------------------------------------------------- Form EMatrix
	EMatb = zero
	EMatk = zero
!	--------
	do 10 j = 1,3
	EMatb(1  ,j  )	= E1C(1,j)		! [C0]
	EMatb(1  ,j+3)	= E2C(1,j)		! [a1]W		
	EMatb(1  ,j+6)	= E3C(1,j)		! I
!
	EMatk(1  ,j+3)	= E22C(1,j)		! R+[Cn]W
	EMatk(1  ,j+9)	= E24C(1,j)		! W
   10 continue
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1030) (i,(EMatb(i,j),j = 1,nG),i=1,nE)
		write(Iout,1030) (i,(EMatk(i,j),j = 1,nG),i=1,nE)
	endif
	iPrt = 0
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Current vector..."/2X,3(f10.7,1X))
 1020 format(2X,A3," Matrix(3,3)"/( (I3,3(f10.2,1X))  ))
 1030 format(2X, "EC Matrix(12,18)"/(I3,18(f5.0,1X)))
	end
