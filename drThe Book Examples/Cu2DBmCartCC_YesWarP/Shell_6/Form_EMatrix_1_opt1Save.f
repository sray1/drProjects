!	Subroutine FormEMatrix(AMat,C0,nC,E,nE,W,R,AA,CK,nG,Iout)
	Subroutine FormEMatrix_1(EMat,nE,nG,nC,iDir,Iout)
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
!----------------------------------------------------------------------- Get EBlocks for dir 1
!	C0		= C01
!	CK		= CK1
!	WMat	= WMat1
!	RMat	= RMat1
!	AA		= AA1
!	===============================================
	call FormEBlocks(nC,E11,E12,E13,E22,E24,1,Iout)
!	--------------------------- Corrector for dir 1 based on Engineering or Virtual For/Mom
	CoA = zero
	CoB = zero
	if(bEng == .TRUE.) then			! engineering
		CoA(1,1) = one
		CoA(2,2) = one
		CoA(3,3) = one
!
		CoB(1,1) = one
		CoB(2,2) = one
		CoB(3,3) = one
	else							! virtual
		CoA(1,1) = one
		CoA(2,2) = one
		CoA(3,3) = one
!
		CoB(1,1) = one
		CoB(2,2) = one
		CoB(3,3) = one
	endif
!	--------------------------- 
	E11 = MATMUL(MATMUL(CoB,E11),CoA)
	E12 = MATMUL(MATMUL(CoB,E12),CoA)
	E13 = MATMUL(MATMUL(CoB,E13),CoA)
!	--------------------------------- bending: 
	if(bEng == .TRUE.) then			! engineering
!	CoA as before
	CoB = zero
!		CoB(1,1) = one
!		CoB(2,2) = one				!one
!		CoB(3,3) = one
!
		CoB(1,2) = one
		CoB(2,1) = onem				!one
		CoB(3,3) = one

	else							! virtual
!	CoA as before
!	CoB as before
	endif
!	--------------------------- 
	E22 = MATMUL(MATMUL(CoB,E22),CoA)
	E24 = MATMUL(MATMUL(CoB,E24),CoA)
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
			call DumpStringVar("Direction 1",iPrt,iOut)
		write(Iout,1020) "E11", (i,(E11(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "E12", (i,(E12(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "E13", (i,(E13(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "E22", (i,(E22(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "E24", (i,(E24(i,j),j = 1,nC),i=1,nC)
	endif
!----------------------------------------------------------------------- Form EMatrix
	EMat = zero
!	--------
	do 10 i = 1,3
	do 10 j = 1,3
	EMat(i  ,j  )	= E11(i,j)		! [C0]
	EMat(i  ,j+3)	= E12(i,j)		! [a1]W		
	EMat(i  ,j+6)	= E13(i,j)		! I
	EMat(i+3,j+3)	= E22(i,j)		! R+[Cn]W
	EMat(i+3,j+9)	= E24(i,j)		! W
   10 continue
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
