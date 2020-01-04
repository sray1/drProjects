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
	include 'Material.h'
	include 'LoadStepIter.h'
	include 'CurParams.h'
	include 'ThetaConstants.h'
	include 'BeamParams.h'
	include 'ShellParams.h'
!==============================================
	Real(kind=8)	EMat                             
	Dimension		EMat(nE,nG)
	Real(kind=8)	E31       ,E32                          
	Dimension		E31(nC,nC),E32(nC,nC)
	Real(kind=8)	E35       ,E42       ,E23       ,E46                   
	Dimension		E35(nC,nC),E42(nC,nC),E23(nC,nC),E46(nC,nC)
	Real(kind=8)	CoA     ,CoB                            
	Dimension		CoA(3,3),CoB(3,3)
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/,onem/-1.0D0/ 
!----------------------------------------------------------------------- Get EBlocks for dir 2
	E31 = zero
	E32 = zero
	E35 = zero
	E42 = zero
	E46 = zero
!	===============================================
	call FormEBlocks(nC,E31,E32,E35,E42,E46,2,Iout)
!	=============================================== 
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
			call DumpStringVar("Direction 2",iPrt,iOut)
		write(Iout,1020) "E31", (i,(E31(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "E32", (i,(E32(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "E35", (i,(E35(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "E42", (i,(E42(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "E46", (i,(E46(i,j),j = 1,nC),i=1,nC)
	endif
!----------------------------------------------------------------------- Form EMatrix
	do 40 i = 1,3
	do 40 j = 1,3
	EMat(i+6 ,j   )	= E31(i,j)
	EMat(i+6 ,j+3 )	= E32(i,j)
	EMat(i+6 ,j+12)	= E35(i,j)
	EMat(i+9 ,j+3 )	= E42(i,j)
	EMat(i+9 ,j+15)	= E46(i,j)
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
