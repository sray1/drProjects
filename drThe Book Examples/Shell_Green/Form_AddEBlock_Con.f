	Subroutine FormAddEBlock_Con(nC,E12,iCurDir,Iout)
!	----------------------------------------------------------------------------- 
!	Inputs
!		C0i(nC)			= initial Curvature vector  for dir iCurDir
!		nC				= 3
!		AMat			= Rotation Matrix
!		W				= matrix
!		Di				= displacement 
!		Dp				= displacement derivative for dir iCurDir
! 	
!	Outputs 
!		E12(nC,nC)		= E12 block = [ko x d + d,idir - AMat * Hatidir]W
!	------------------------------------------------------------
	Implicit Real(kind=8) (a-h,o-z)
!
!
	include 'ThetaConstants.h'
	include 'BeamParams.h'
!	===============================
	Real(kind=8)	v1   ,v2   ,AHat   ,pb                            
	Dimension		v1(3),v2(3),AHat(3),pb(3)
	Real(kind=8)	E12                 
	Dimension		E12(nC,nC)
	Real(kind=8)	sAA                  
	Dimension		sAA(nC,nC)
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	------------------------------------------------------------------- 
	AHat = MATMUL(AMat,Hat)
!	------------------------------------------------------------------- 
	call CrossProduct(C0,Di,v1,Iout)			! [k01]d = k01 x d
	call VectorAdd(v1,Dp,v2,nC,Iout)			! + Dp
	call VectorsSubtract(v2,AHat,pb,nC,Iout)	! - A*Hat
	!-----------------------------------------------------------------------------------------E12Block
	call FormSkew(pb,nC,sAA,Iout)		!skew[pb]
	E12 = MATMUL(sAA, WMat)				!skew[pb]W
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
!		write(Iout,1010) (G(j),j = 1,nS)
		write(Iout,1005) iCurDir
		write(Iout,1020) "Add12", (i,(E12(i,j),j = 1,nC),i=1,nC)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1005 format(1X,"Current direction for E_Matrix ="I2/)
 1010 format(1X,"Current vector..."/2X,3(f10.7,1X))
 1020 format(2X,A5," Matrix(3,3)"/
     &        (I5,3(f10.7,1X)/))
	end
