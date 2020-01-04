!	Subroutine FormEMatrix(AMat,C0,nC,E,nE,W,R,AA,CK,nG,Iout)
	Subroutine FormEMatrix_2_Con(EMatb,EMatk,nE,nG,nC,iDir,Iout)
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
	Real(kind=8)	E42       ,E46                   
	Dimension		E42(nC,nC),E46(nC,nC)
	Real(kind=8)	CoA     ,CoB                            
	Dimension		CoA(3,3),CoB(3,3)
!	-------------------------------------------
	Real(kind=8)	Ab32       ,Ak42          
	Dimension		Ab32(nC,nC),Ak42(nC,nC)
	Real(kind=8)	A1H     ,E1C     ,E2C     ,E3C                              
	Dimension		A1H(1,3),E1C(1,3),E2C(1,3),E3C(1,3)
	Real(kind=8)	E42C     ,E46C                                   
	Dimension		E42C(1,3),E46C(1,3)
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/,onem/-1.0D0/ 
	DATA A1H/1.D0,0.0D0,0.D0/
!----------------------------------------------------------------------- Get EBlocks for dir 2
	E31 = zero
	E32 = zero
	E35 = zero
	E42 = zero
	E46 = zero
	A32 = zero
!	===============================================
	call FormEBlocks(nC,E31,E32,E35,E42,E46,2,Iout)
!	=============================================== 
	call FormAddEBlock_Con(nC,Ab32,Ak42,2,Iout)
	E32 = E32 - Ab32
	E42 = E42 - Ak42
!	----------------------------------------------------- E12
	E1C = MATMUL(A1H,E31)	
	E2C = MATMUL(A1H,E32)	
	E3C = MATMUL(A1H,E35)	
	E42C = MATMUL(A1H,E42)	
	E46C = MATMUL(A1H,E46)	
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
			call DumpStringVar("Direction 1",iPrt,iOut)
			call DumpRealArray(E1C,nC,"E1C",iPrt,iOut)
			call DumpRealArray(E2C,nC,"E2C",iPrt,iOut)
			call DumpRealArray(E3C,nC,"E3C",iPrt,iOut)
	endif
!----------------------------------------------------------------------- Form EMatrix
	do 40 j = 1,3
	EMatb(1 ,j   )	= EMatb(1 ,j   )	- E1C(1,j)
	EMatb(1 ,j+3 )	= EMatb(1 ,j+3 )	- E2C(1,j)
	EMatb(1 ,j+12)	= EMatb(1 ,j+12)	- E3C(1,j)
!
	EMatk(1 ,j+3 )	= EMatk(1 ,j+3 )	- E42C(1,j)
	EMatk(1 ,j+15)	= EMatk(1 ,j+15)	- E46C(1,j)
   40 continue
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
 1030 format(2X, "EC Matrix(12,18)"/(I3,18(f7.2,1X)))
	end
