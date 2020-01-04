	Program Try_Quad_CC_WARP_NO
!
!	Try Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!	Notes:	Nint should be atleast 2
!			nStif MUST be 32
!
!	Inputs
!		Qc(1,16)	= Bezier X-Coordinates
!					=	(qc00x qc10x...qc33x)
!		Qc(2,16)	= Bezier Y-Coordinates
!					=	(qc00y qc10y...qc33y)
!		Nel			= Element Number
!		NelType		= Element Type:
!						0 = Plane Stress
!						1 = Plane Strain
!						2 = Axi-symmtric	(NOT DONE YET)
!		Nint		= Number of Gauss Points
!		E			= Elasticity Modulus
!		PR			= Poisson's ratio
!		Thk			= Thickness
!		nStif		= Row or Col size of Stiffness matrix ( MUST BE 32)
!		Iout		= Error Output file#
!		Stif(32,32)	= Desired Stiffness Matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!
	common A(1000000)
!
!	Input Variables & Arrays
!
	Real(kind=8)	E,PR,Thk,xLx,xLy,Trace
	integer			Nel,NelType,Iout,nStif
	integer			n1,n2
	real(kind = 8)	Disp
	dimension		Disp(2)
!		
!	
!	Output Variables & Arrays	
!
	nStif	= 32
	Nel		= 1
	Nint	= 3		! Gauss Order
	Nint	= 4		! Gauss Order
	IoDW	= 15	! I/O Default Write
!
!	Stress-Strain Law
!
!	NelType	= 1		! Plain Strain
	NelType	= 0		! Plain Stress
	E		= 3.D3/4.D0	 	
	E		= 1.D0	 	
	PR		= 0.25D0	! Poisson's Ratio
	Thk		= 1.D0 ! thickness
!
!	Array sizes
!
	nSzInt	= 4 !bytes
	nSzDbl	= 8 !bytes
	n1		= 1						! Qc(2,16)
	n2		= n1 + 2*16*nSzDbl		! S(32,32) Singular
	n3		= n2 + 32*32*nSzDbl		! S(24,24) Non-Singular
	n4		= n3 + 24*24*nSzDbl		! F(32)
	n5		= n4 + 32*nSzDbl		! Qd(4)
	nEnd	= n5 + 4*nSzDbl				
!
!	Set Bezier Coordinates 
!
	xLx = 1.D0
	xLy = 1.D0
!	xLx = 10.D0
!	xLy = 0.01D0
	call BZ_Coords(A(n1),2,16,xLx,xLy)
!
!	Get Stiffness Matrix 
!
	call Quad_CC_STIF(A(n1),Nel,NelType,Nint,E,PR,Thk,A(n2),nStif,Iout,
     &					Trace)
!
!	Get Load Vector for Shear Load at End 
!
	
	call Set_ExtLoad(A(n5),4)
	call Quad_CC_LV(A(n5),A(n4),xLy)
!
!	displacement Controls:Qd
!
	n6		= nEnd
	n7		= n6 + 32*32*nSzDbl
	nEnd	= n6 + 32*nSzDbl
!
!	PROBLEM SPECIFIC: NO WARP AT END
!	Make NonSingular by dropping Row/Cols corresponding to Bndry Conds
!	Five fixity: Eqn. #s : 1,5,9,13,17,21,25,29
!	SO FINAL TOTAL EQUATION = 32-8=24
!
!	Solve 
! EITHER
!
	call Extract_NonSingularStif(A(n2),32,32,A(n3),24,24)
	call Extract_ContractedLoadVector(A(n4),32,A(n4),24)
!	call Factor_Determinant(A(n3),A(n4),A(n6),A(n7),29,29,29)
	call Solve_AxEqB(A(n3),A(n4),A(n6),24,24)
!
! OR
!	call AddSupport_Stif(A(n2),32,32,Trace)
!	call MultSupport_Load(A(n4),32,Trace)
!	call Solve_AxEqB(A(n2),A(n4),A(n6),32,32)
	call Expand_BezierDispControls(A(n6),24,A(n4),32)
!
!	Compute Displacement
!
	call Compute_Displacement(A(n4),16,2,1.D0,0.5D0,D)
!
	Stop 'OK'
	end 
!
	Subroutine BZ_Coords(Qc,nR,nC,xLx,xLy)
	
	real(kind = 8)	Qc
	Dimension		Qc(nR,nC)
	real(kind = 8)	xLx,xLy,xLx3,x2Lx3,xLy3,x2Ly3
	integer			nR,nC
!
	Qc			= 0.			! zero all
!
	xLx3		= xLx/3.
	xLy3		= xLy/3.
	x2Lx3		= 2.*xLx3
	x2Ly3		= 2.*xLy3
!
!	Qc(1,1)		= 0.0
	Qc(1,2)		= xLx3
	Qc(1,3)		= x2Lx3
	Qc(1,4)		= xLx
!
!	Qc(1,5)		= 0.0
	Qc(1,6)		= xLx3
	Qc(1,7)		= x2Lx3
	Qc(1,8)		= xLx

!
!	Qc(1,9)		= 0.0
	Qc(1,10)	= xLx3
	Qc(1,11)	= x2Lx3
	Qc(1,12)	= xLx

!
!	Qc(1,13)	= 0.0
	Qc(1,14)	= xLx3
	Qc(1,15)	= x2Lx3
	Qc(1,16)	= xLx

!
!
!	Qc(2,1)		= 0.
!	Qc(2,2)		= 0.
!	Qc(2,3)		= 0.
!	Qc(2,4)		= 0
!
	Qc(2,5)		= xLy3
	Qc(2,6)		= xLy3
	Qc(2,7)		= xLy3
	Qc(2,8)		= xLy3

!
	Qc(2,9)		= x2Ly3
	Qc(2,10)	= x2Ly3
	Qc(2,11)	= x2Ly3
	Qc(2,12)	= x2Ly3

!
	Qc(2,13)	= xLy
	Qc(2,14)	= xLy
	Qc(2,15)	= xLy
	Qc(2,16)	= xLy

!
	return
	end
	
	Subroutine Set_ExtLoad(Qf,nDim)
	
	real(kind = 8)	Qf
	Dimension		Qf(nDim)
!	
	Qf		= 0.		! All Zero
	Qf(2)	= 1.0
	Qf(3)	= 1.0
!
	return
	end
!	  			
	Subroutine AddSupport_Stif(Ss,nSsI,nSsJ,Trace)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM
!	EQUATIONS 1,13,17 diagonals add Joint Stif
!
	real(kind = 8)	Ss           ,Trace,DiaStif
	Dimension		Ss(nSsI,nSsJ)
!
!	Add Joint Stiffness = 1000*Trace
!
	DiaStif = 1000000.* Trace
!
	Ss(1,1)		= Ss(1,1) + DiaStif 	
	Ss(13,13)	= Ss(13,13) + DiaStif 	
	Ss(17,17)	= Ss(17,17) + DiaStif 
!
	return
	end
!
!	  			
	Subroutine MultSupport_Load(F,nF,Trace)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM
!	EQUATIONS 1,5,9,13,17 diagonals add Joint Stif
!
	real(kind = 8)	F           ,Trace,FJoint
	Dimension		F(nF)
!
!	Multiply Joint Pseudo Load = 1000*Trace
!
	FJoint = 1000000.* Trace
!
	F(1)	= F(1)	* FJoint 	
	F(13)	= F(13) * FJoint 	
	F(17)	= F(17) * FJoint 
!
	return
	end
!
!			
	Subroutine Extract_NonSingularStif(Ss,nSsI,nSsJ,Sn,nSnI,nSnJ)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM
!	EQUATIONS 1,5,9,13,17,21,25,29 ROWS & COLS NEED TO GO
!
!	Ss(nSsI,nSsJ)		= Stiffness-Singular Matrix (INPUT)	
!	Sn(nSnI,nSnJ)		= Stiffness-NonSingular Matrix (OUTPUT)
!
	real(kind = 8)	Sn           ,Ss
	Dimension		Sn(nSnI,nSnJ),Ss(nSsI,nSsJ)
	real(kind = 8)	sum,Add(24)
!
!
	integer i,j,ii,jj
!
	integer			Drop
	Dimension		Drop(8)	
	DATA Drop / 1,5,9,13,17,21,25,29/
!
	ii = 0
	jj = 0
!			
	do 40 j = 1,nSsJ
	do 10 k = 1,8
	if(j == Drop(k)) then
		go to 40
	end if
   10	continue
	jj = jj+1
	do 30 i = 1,nSsI
!
	do 20 k = 1,8
	if(i == Drop(k)) then
		go to 30
	end if
   20	continue
!
	ii = ii+1
	Sn(ii,jj) = Ss(i,j)
   30 continue
	ii = mod(ii,nSnI)		! reset row
   40 continue
!
!	Check each col. vector for NOT Null
!
	Add = 0.D0
	do 70 j = 1,24
	sum = 0.0 
	do 60 i = 1,24	
	sum = sum + Sn(i,j)
   60 continue
	Add(j) = sum
   70 continue			
!
!	done
!
	do 80 i = 1,24
!	write(*,1010) i,(Sn(i,j),j = 1,24)
!	Pause
   80	continue
	return
!
 1010 format("Reduced Stiffness Matrix:Stif(24,24)"/
     &        I5/(3(9(f10.6,1X)/)/))
	return
	end

	Subroutine Extract_ContractedLoadVector(Ff,nFf,Fc,nFc)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM
!	EQUATIONS 1,5,9,13,17,21,25,29 Rows NEED TO GO
!
!	Ff(nFf)		= Full Load Vector (INPUT)	
!	Fc(nFc)		= Contracted Load Vector (OUTPUT)
!
	real(kind = 8)	Ff     ,Fc
	Dimension		Ff(nFf),Fc(nFc)
!
!
	integer i,ii
!
	integer			Drop
	Dimension		Drop(8)	
	DATA Drop / 1,5,9,13,17,21,25,29/
!
	ii = 0
!			
	do 20 i = 1,nFf
	do 10 k = 1,8
	if(i == Drop(k)) then
		go to 20
	end if
   10	continue
	ii = ii + 1
!
	Fc(ii) = Ff(i)
   20 continue
!
	return
	end
!
	Subroutine Expand_BezierDispControls(Xc,nXc,Xf,nXf)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM
!	EQUATIONS 1,13,17 Rows include = 0.0
!
!	Xc(nXc)		= Solved Bezier Displacement Controls (Input)
!	Xf(nFf)		= Full Bezier Displacement Controls (Output)	
!
	real(kind = 8)	Xf     ,Xc
	Dimension		Xf(nXf),Xc(nXc)
!
!
	integer i,ii
!
	integer			Drop
	Dimension		Drop(8)	
	DATA Drop / 1,5,9,13,17,21,25,29/
!
	Xf = 0.0	! initialize
	ii = 0
!			
	do 20 i = 1,nXf
	do 10 k = 1,8
	if(i == Drop(k)) then
		go to 20
	end if
   10	continue
	ii = ii + 1
!
	Xf(i) = Xc(ii)
   20 continue
!
	return
	end
!
	Subroutine Compute_Displacement(Xf,nRow,nCol,R,S,D)
!
!	Xf(nRow=32,nCol=2)		= Full Bezier Displacement Controls (Output)	
!
	real(kind = 8)	Xf			 ,D	    
	Dimension		Xf(nRow,nCol),D(2)
	real(kind = 8)	R,S,DX,DY
	integer			nRow,nCol     
!
	real(kind = 8)	sum
	integer			i,j,k     
!
	Real(kind=8)	Br   ,Bs
	Dimension		Br(4),Bs(4)
!	
!	Define Bernstein Interpolations
!
	Br(1) = (1.-r)*(1.-r)*(1.-r)
	Br(2) = 3.*(1.-r)*(1.-r)*r
	Br(3) = 3.*(1.-r)*r*r
	Br(4) = r*r*r
!	 
	Bs(1) = (1.-s)*(1.-s)*(1.-s)
	Bs(2) = 3.*(1.-s)*(1.-s)*s
	Bs(3) = 3.*(1.-s)*s*s
	Bs(4) = s*s*s
!	
	do 20 l = 1,2
	sum = 0.0
	do 10 k = 1,nRow
	i = modulo(k,4)
	if(i == 0) then
		i = 4
	endif
	j = (k-1)/4 + 1
!
	sum = sum + Br(i)*Bs(j)*Xf(k,l)
!
   10 continue
	D(l) = sum
   20 continue
!
	return
	end   			 			  			  			  		