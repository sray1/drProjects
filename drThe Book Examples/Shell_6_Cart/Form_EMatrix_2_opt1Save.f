!	Subroutine FormEMatrix(AMat,C0,nC,E,nE,W,R,AA,CK,nG,Iout)
	Subroutine FormEMatrix_2(EMat,nE,nG,nC,iDir,Iout)
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
	include 'LogParams.h'
	include 'Material.h'
	include 'LoadStepIter.h'
	include 'CurParams.h'
	include 'ThetaConstants.h'
	include 'BeamParams.h'
	include 'ShellParams.h'
!==============================================
	Real(kind=8)	EMat                             
	Dimension		EMat(nE,nG)
	Real(kind=8)	E11       ,E12                          
	Dimension		E11(nC,nC),E12(nC,nC)
	Real(kind=8)	E13       ,E22       ,E23       ,E24                   
	Dimension		E13(nC,nC),E22(nC,nC),E23(nC,nC),E24(nC,nC)
	Real(kind=8)	CoA     ,CoB                            
	Dimension		CoA(3,3),CoB(3,3)
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/,onem/-1.0D0/ 
!----------------------------------------------------------------------- Get EBlocks for dir 2
	E11 = zero
	E12 = zero
	E13 = zero
	E22 = zero
	E24 = zero
!	---------------
!	C0		= C02
!	CK		= CK2
!	WMat	= WMat2
!	RMat	= RMat2
!	AA		= AA2
!	===============================================
	call FormEBlocks(nC,E11,E12,E13,E22,E24,2,Iout)
!	=============================================== correction to 1,2,3 from 2,1,-3 dofs
!	--------------------------- Corrector for dir 2 based on Engineering or Virtual For/Mom
	CoA = zero
	CoB = zero
	if(bEng == .TRUE.) then			! engineering
		CoA(1,2) = one
		CoA(2,1) = one
		CoA(3,3) = onem
!
		CoB(1,2) = one
		CoB(2,1) = one
		CoB(3,3) = onem
	else							! virtual
		CoA(1,2) = one
		CoA(2,1) = one
		CoA(3,3) = onem
!
		CoB(1,3) = one
		CoB(2,1) = one
		CoB(3,2) = onem
	endif
!	--------------------------- 
	E11 = MATMUL(MATMUL(CoB,E11),CoA)
	E12 = MATMUL(MATMUL(CoB,E12),CoA)
	E13 = MATMUL(MATMUL(CoB,E13),CoA)
!	--------------------------------- bending
	if(bEng == .TRUE.) then			! engineering
!		CoA as before
		CoB = zero
		CoB(1,1) = one
		CoB(2,2) = onem				!
		CoB(3,3) = onem
	else							! virtual
!		CoA as before
!		CoB as before
	endif
!	--------------------------- 
	E22 = MATMUL(MATMUL(CoB,E22),CoA)
	E24 = MATMUL(MATMUL(CoB,E24),CoA)
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
			call DumpStringVar("Direction 2",iPrt,iOut)
		write(Iout,1020) "E11", (i,(E11(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "E12", (i,(E12(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "E13", (i,(E13(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "E22", (i,(E22(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "E24", (i,(E24(i,j),j = 1,nC),i=1,nC)
	endif
!----------------------------------------------------------------------- Form EMatrix
	do 40 i = 1,3
	do 40 j = 1,3
	EMat(i+6 ,j   )	= E11(i,j)
	EMat(i+6 ,j+3 )	= E12(i,j)
	EMat(i+6 ,j+12)	= E13(i,j)
	EMat(i+9 ,j+3 )	= E22(i,j)
	EMat(i+9 ,j+15)	= E24(i,j)
   40 continue
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
 1030 format(2X, "E Matrix(12,18)"/(I3,18(f7.2,1X)))
	end
