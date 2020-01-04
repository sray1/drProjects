	Subroutine FormEMatrix(AMat,C0,nC,E,nE,W,R,AA,CK,nG,Iout)
!	----------------------------------------------------------------------------- 
!	Inputs
!		AMat(nC,nC)		= Rotation Matrix
!		nG				= 12
!		C0(nC)			= initial Curvature vector = {torsion,0,curvature} = k0
!		nC				= 3
!		nE				= 6
!		W(nC,nC)		= W Matrix
!		R(nC,nC)		= R Matrix
!		AA(nC)			= e + [k0]d
!		CK(nC)			= k0 + k = k0 + W(thetaPrimed)
! 	
!	Outputs 
!		E(nE,nG)		= E Matrix
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	C0    ,E       ,AMat                       
	Dimension		C0(nC),E(nE,nG),AMat(nC,nC)
	Real(kind=8)	E11       ,E12                          
	Dimension		E11(nC,nC),E12(nC,nC)
	Real(kind=8)	E13       ,E22       ,E23       ,E24                   
	Dimension		E13(nC,nC),E22(nC,nC),E23(nC,nC),E24(nC,nC)
	Real(kind=8)	CK    ,AA                                      
	Dimension		CK(nC),AA(nC)
	Real(kind=8)	W       ,R                   
	Dimension		W(nC,nC),R(nC,nC)
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!----------------------------------------------------------------------- Get EBlocks
	call FormEBlocks(C0,nC,W,R,AA,CK,AMat,E11,E12,E13,E22,E24,Iout)
!----------------------------------------------------------------------- Form EMatrix
	E = zero
!	--------
	do 40 i = 1,3
	do 40 j = 1,3
	E(i,j)		= E11(i,j)
	E(i,j+3)	= E12(i,j)
	E(i,j+6)	= E13(i,j)
	E(i+3,j+3)	= E22(i,j)
	E(i+3,j+9)	= E24(i,j)
   40 continue
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1020) "E11", (i,(E11(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "E12", (i,(E12(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "E13", (i,(E13(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "E22", (i,(E22(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "E24", (i,(E24(i,j),j = 1,nC),i=1,nC)
		write(Iout,1030) (i,(E(i,j),j = 1,nG),i=1,nE)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Current vector..."/2X,3(f10.7,1X))
 1020 format(2X,A3," Matrix(3,3)"/( (I5,3(f20.7,1X))  ))
 1030 format(2X, "E Matrix(12,12)"/(I5,3(4(f20.7,1X)/)))
	end
