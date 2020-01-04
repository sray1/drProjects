	Program Try_CC_Beam_Cart
!
!	Try Curved Beam_Cubic Element described by Cartesian Coords
!	Cantilever with tip load of 90 deg Curve
!
!	Inputs
!		Qc(1,4)	= Bezier X-Coordinates
!					=	(qc0x qc1x...qc3x)
!		Qc(2,16)	= Bezier Y-Coordinates
!					=	(qc0y qc1y...qc3y)
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
	nStifS	= 4
	nSup	= 2	! Fxed End
	nStifN	= nStifS - nSup
	Nel		= 1
	Nint	= 3		! Gauss Order
	Nint	= 6		! Gauss Order
	IoDW	= 15	! I/O Default Write
!
!	Stress-Strain Law
!
!	NelType	= 1		! Plain Strain
	NelType	= 0		! Plain Stress
	E		= 1.0	 	
	PR		= 0.3125D0	! Poisson's Ratio
	Thk		= 1.D0 ! thickness
!
!	Array sizes
!
	nSzInt	= 4 !bytes
	nSzDbl	= 8 !bytes
	n1		= 1							! Qc(2,nStifS)
	n2		= n1 + 2*nStifS*nSzDbl		! S(nStifS,nStifS) Singular
	n3		= n2 + nStifS*nStifS*nSzDbl	! S(nStifN,nStifN) Non-Singular
	n4		= n3 + nStifN*nStifN*nSzDbl	! F(nStifS)
	n5		= n4 + nStifS*nSzDbl		! Qd(4)
	nEnd	= n5 + nStifS*nSzDbl				
!
!	Set Bezier Coordinates 
!
	xLx = 4.D0
	xLy = 1.D0
	call BZ_Coords(A(n1),2,nStifS,xLx,xLy)
!
!	Get Stiffness Matrix 
!
	call Quad_CC_STIF(A(n1),nStifS,Nel,NelType,Nint,E,PR,Thk,A(n2),
     &						nStifS,Iout,Trace)
!
!	Get Load Vector for Shear Load at End 
!
	
	call Set_ExtLoad(A(n5),4)
	call Quad_CC_LV(A(n5),nStifS,A(n4),nStifS,xLy)
!
!	displacement Controls:Qd
!
	n6		= nEnd
	n7		= n6 + nStifN*nStifN*nSzDbl
	nEnd	= n6 + nStifN*nSzDbl
!
!	PROBLEM SPECIFIC: NO WARP AT END
!	Make NonSingular by dropping Row/Cols corresponding to Bndry Conds
!	Five fixity: Eqn. #s : 1,2
!	SO FINAL TOTAL EQUATION = 32-8=24
!
!	Solve 
! EITHER
!
	call Extract_NonSingularStif(A(n2),nStifS,nStifS,A(n3),
     &										nStifN,nStifN)
	call Extract_ContractedLoadVector(A(n4),nStifS,A(n4),nStifN)
!	call Factor_Determinant(A(n3),A(n4),A(n6),A(n7),29,29,29)
	call Solve_AxEqB(A(n3),A(n4),A(n6),nStifN,nStifN)
!
! OR
!	call AddSupport_Stif(A(n2),32,32,Trace)
!	call MultSupport_Load(A(n4),32,Trace)
!	call Solve_AxEqB(A(n2),A(n4),A(n6),32,32)
	call Expand_BezierDispControls(A(n6),nStifN,A(n4),nStifS)
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
	real(kind = 8)	xLx,xLy,xLxy2,x2Ly3
	real(kind = 8)	R0,R1,R2,R3,h0,h1,h2,h3,xK
	integer			nR,nC
!
!	-----------------------------
	xK			= 4.0D0*(dsqrt(2.0D0)-1.0D0)/3.0D0
!
	Qc			= 0.0D0			! zero all
!--------------------------------------------------- x
	Qc(1,3)		= 1.0D0 - xK
	Qc(1,4)		= 1.0D0
!--------------------------------------------------- y
	Qc(2,2)		= xK
	Qc(2,3)		= 1.0D0
	Qc(2,4)		= 1.0D0
!-------------------------------------
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
	real(kind = 8)	sum,Add(nSnI)
!
!
	integer i,j,ii,jj
!
	integer			Drop
	Dimension		Drop(2)	
	DATA Drop / 1,2/
	DATA nDrop /2/
!
	ii = 0
	jj = 0
!			
	do 40 j = 1,nSsJ
	do 10 k = 1,nDrop
	if(j == Drop(k)) then
		go to 40
	end if
   10	continue
	jj = jj+1
	do 30 i = 1,nSsI
!
	do 20 k = 1,nDrop
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
	do 70 j = 1,nSnI
	sum = 0.0 
	do 60 i = 1,nSnI	
	sum = sum + Sn(i,j)
   60 continue
	Add(j) = sum
   70 continue			
!
!	done
!
	do 80 i = 1,nSnI
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
!	EQUATIONS 1,2 Rows NEED TO GO
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
	Dimension		Drop(2)	
	DATA Drop / 1,2/
	DATA nDrop /2/
!
	ii = 0
!			
	do 20 i = 1,nFf
	do 10 k = 1,nDrop
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
      USE NUMERICAL_LIBRARIES
!	HARD-CODED FOR A SPECIFIC PROBLEM
!	EQUATIONS 1,13,17 Rows include = 0.0
!
!	Xc(nXc)		= Solved Bezier Displacement Controls (Input)
!	Xf(nFf)		= Full Bezier Displacement Controls (Output)	
!
	real(kind = 8)	Xf     ,Xc     , uL_Extn,uL_thet,pi2
	Dimension		Xf(nXf),Xc(nXc)
!
!
	integer i,ii
!
	integer			Drop
	Dimension		Drop(2)	
	DATA Drop / 1,2/
	DATA nDrop /2/
!
	Xf = 0.0	! initialize
	ii = 0
!			
	do 20 i = 1,nXf
	do 10 k = 1,nDrop
	if(i == Drop(k)) then
		go to 20
	end if
   10	continue
	ii = ii + 1
!------------------------------ w (radial)
	Xf(i) = Xc(ii)
   20 continue
!------------------------------ u_r (extensional) at angle = pi/2
	pi2 = DATAN(1.D0)*2.0D0
	uL_Extn	 = -pi2*pi2*0.25*(Xf(3)+Xf(4))
!------------------------------ u_theta (rotational) at angle = pi/2
	uL_thet	 = 1.5D0*(Xf(4)-Xf(3))-0.5D0*uL_Extn
!-------------------------------------------
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