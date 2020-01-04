	Program Try_Quad_CC_WARP_YES
!
!	Try Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!--------------------------------------------------------------------------------
!	Used:		Two Elements/ Plane strain
!	Reference:	paper by Ibrahimbegovic
!	ExactSol.	Tip v = (PL^^3/3EI) + {(4+5*Nu)PL/2Eh} Timoshenko/Goodier,1951
!	Data		E=30000 Nu=.25 P=40 L=48 h=12
!	Exact		Tip v = .3553
!	Our Sol		Tip v =	.xxxx (xx%)
!-------------------------------------------------------------------------------- 		
!
!	Notes:	Nint should be atleast 2
!			nStif MUST be 64
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
	integer			Nel,NelType,Iout,nStif,nStifEL
	integer			n1,n2
	real(kind = 8)	Disp
	dimension		Disp(2)
!		
!	
!	Output Variables & Arrays	
!
!	nStifActual = 64 - 8 (tie dofs between 2 Elements) = 56
	nStifEL	= 32
	nStif	= 64
	nStifA	= 56
	nSup	= 3
	nStifN  = nStifA - nSup	! size NonSingular: 53 = 56 - 3( 2 supX + 1 SupY)
!------------------------------------------------------------------- Continuity
	nCont	= 1					! 1 = C1/ 2 = C2
	if (nCont == 1) then
		nC		= 8 
		nStifC  = nStifN - nC	! size Constrained:45 =53-8(interface dofs)
								! C1-continuity constraint at interface for 
								! interface Bez dofs (8 of them)
								! Working on the Nonsingular stage
	else if (nCont == 2) then
!	------------------------------------------------------------------------
		nC		= 16 
		nStifC  = nStifN - nC	! size Constrained:37 = 53-16(interface dofs)
								! C2-continuity constraint at interface for 
								! interface Bez dofs (16 of them)
								! Working on the Nonsingular stage
	end if
!-----------------------------------------------------------------------------

	Nint	= 4		! Gauss Order
!	Nint	= 6		! Gauss Order
	IoDW	= 15	! I/O Default Write
!
!	Stress-Strain Law
!
!----------------------------------------------------------------- DATA
	NelType	= 1			! Plain Strain ( to compare w/ Ibrahim)
	E		= 1.D0	 	
	PR		= 0.25D0	! Poisson's Ratio
	Thk		= 1.D0		! thickness
	xLx		= 24.D0		!Aspect Ratio for each element		
	xLy		= 12.D0
!-----------------------------------------------------------------
!
!	Array sizes
!
	nSzInt	= 4 !bytes
	nSzDbl	= 8 !bytes
	n1		= 1								! Qc(2,16)
	n2		= n1  + 2*16*nSzDbl				! S(64,64) Singular / 2ELs(n2)
	n2b		= n2  + nStif*nStif*nSzDbl		! S(32,32) Singular / 1ELs(n2b)
	n3		= n2b + nStifEL*nStifEL*nSzDbl	! S(53,53) Non-Singular (n3)
	n4		= n3  + nStifN*nStifN*nSzDbl	! F(64) Singular(n4)
	n5		= n4  + nStif*nSzDbl			! Qd(4)
	nEnd	= n5  + 4*nSzDbl				
!
!	Set Bezier Coordinates 
!

	call BZ_Coords(A(n1),2,16,xLx,xLy)
!
!	Get Stiffness Matrix: Ist Elem 
!
	Nel = 1
	call Quad_CC_STIF(A(n1),Nel,NelType,Nint,E,PR,Thk,A(n2b),nStifEL,
     &					Iout,Trace)
!
!-----------------------------------------------------------------------
!	C0_Condition
!-----------------------------------------------------------------------
!	Assemble Ist Elem
!
	n2c		= nEnd
	nEnd	= n2c + nStifEL*nSzInt
	call Assemble_Stif(A(n2c),A(n2b),nStifEL,A(n2),nStif,Nel,
     & 													Iout,Trace)
!
!	Get Stiffness Matrix: 2nd Elem : same as first element, so skip
!
	Nel = 2
!	call Quad_CC_STIF(A(n1),Nel,NelType,Nint,E,PR,Thk,A(n2b),nStifEL,
!     &					Iout,Trace)
!
!	Assemble 2nd Elem
!
	call FormIndexEl_2(A(n2c),nStifEL)
	call Assemble_Stif(A(n2c),A(n2b),nStifEL,A(n2),nStif,Nel,
     & 													Iout,Trace)
!
!	Get Load Vector for Shear Load at End 
!
	call Set_ExtLoad(A(n5),4)
	call Quad_CC_LV(A(n5),A(n4),nStif,xLy)
!
!--------------------------------------------------------------------
!	IMPOSE C0 Condition by transformation 
!	no consideration given to Transformation matrix being sparse
!--------------------------------------------------------------------
	n8		= nEnd
	n3		= n8 + nStif*nStifA*nSzDbl
	n9		= n3 + nStifA*nStifA*nSzDbl
	nEnd	= n9 + nStifA*nSzDbl
	call FormTransformationMatrix_C0(A(n8),nStif,nStifA)
	call Impose_Continuity(A(n2),A(n4),nStif,A(n8),A(n3),A(n9)
     &														,nStifA)
!	displacement Controls:Qd
!
!
!	PROBLEM SPECIFIC
!	Make NonSingular by dropping Row/Cols corresponding to Bndry Conds
!	Five fixity: Eqn. #s : 1,13,17
!
!	Solve 
! EITHER
!--------------------------------------------------------------------
!	IMPOSE SUPPORT Conditions & make stiffnes Non-singular
!--------------------------------------------------------------------
	n6		= nEnd
	n7		= n6 + nStifN*nStifN*nSzDbl
	nEnd	= n7 + nStifN*nSzDbl
!
	call Extract_NonSingularStif(A(n3),nStifA,nStifA,A(n6),nStifN)
	call Extract_ContractedLoadVector(A(n9),nStifA,A(n7),nStifN)
!--------------------------------------------------------------------
!	SOLVE for 2 Elements in C0 Condition
!--------------------------------------------------------------------
!	call Factor_Determinant(A(n3),A(n4),A(n6),A(n7),29,29,29)
	call Factor_ConditionNumber(A(n6),A(n2),A(n4),nStifN,
     &										nStifN,nStifN)
	call Solve_AxEqB(A(n6),A(n7),A(n4),nStifN,nStifN)
	call Compute_StrainEnergy(A(n6),A(n4),nStifN,SEnergy)
!--------------------------------------------------------------------
!	IMPOSE C1 Condition by transformation 
!	no consideration given to Transformation matrix being sparse
!--------------------------------------------------------------------
	if (nCont == 1) then
		n8		= nEnd
		n9		= n8 + nStifN*nStifC*nSzDbl
		nEnd	= n9 + nStifN*nSzDbl
		call FormTransformationMatrix_C1(A(n8),nStifN,nStifC)
		call Impose_Continuity(A(n6),A(n7),nStifN,A(n8),A(n2),A(n3)
     &														,nStifC)
!     ---------------------------------------------------------------
!		SOLVE for 2 Elements in C1 Condition
!     ---------------------------------------------------------------
!		call Factor_Determinant(A(n3),A(n4),A(n6),A(n7),29,29,29)
		call Factor_ConditionNumber(A(n2),A(n6),A(n4),nStifC,
     &										nStifC,nStifC)
		call Solve_AxEqB(A(n2),A(n3),A(n4),nStifC,nStifC)
		call Compute_StrainEnergy(A(n2),A(n4),nStifC,SEnergy)
	end if
!--------------------------------------------------------------------
!	IMPOSE C2 Condition by transformation 
!	no consideration given to Transformation matrix being sparse
!--------------------------------------------------------------------
	if (nCont == 2) then
		n8		= nEnd
		n9		= n8 + nStifN*nStifC*nSzDbl
		nEnd	= n9 + nStifN*nSzDbl
		call FormTransformationMatrix_C2(A(n8),nStifN,nStifC)
		call Impose_Continuity(A(n6),A(n7),nStifN,A(n8),A(n2),A(n3)
     &														,nStifC)
!     ---------------------------------------------------------------
!		SOLVE for 2 Elements in C2 Condition
!     ---------------------------------------------------------------
!		call Factor_Determinant(A(n3),A(n4),A(n6),A(n7),29,29,29)
		call Factor_ConditionNumber(A(n2),A(n6),A(n4),nStifC,
     &										nStifC,nStifC)
		call Solve_AxEqB(A(n2),A(n3),A(n4),nStifC,nStifC)
		call Compute_StrainEnergy(A(n2),A(n4),nStifC,SEnergy)
	end if
!------------------------------------------------------------------------
! OR
!	call AddSupport_Stif(A(n2),32,32,Trace)
!	call MultSupport_Load(A(n4),32,Trace)
!	call Solve_AxEqB(A(n2),A(n4),A(n6),32,32)
	call Expand_BezierDispControls(A(n6),nStifN,A(n4),64)
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
  100 continue
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
!	EQUATIONS 1,13,17 diagonals add Joint Stif
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
	Subroutine Extract_NonSingularStif(Ss,nSs,nStif,Sn,nSn)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM
!	EQUATIONS 1,13,17 ROWS & COLS NEED TO GO
!
!	At connection of 2 Elements 8 Dofs gone, so actual size = 64 - 8 = 56
!	for Loop: nStif	
!	nSsI,nSsJ are dimensions
!	Ss(nSs,nSs)		= Stiffness-Singular Matrix (INPUT)	
!	Sn(nSn,nSn)		= Stiffness-NonSingular Matrix (OUTPUT)
!
	real(kind = 8)	Sn           ,Ss
	Dimension		Sn(nSn,nSn),Ss(nSs,nSs)
	real(kind = 8)	sum,Add(nSn)
!
!
	integer i,j,ii,jj
!
	integer			Drop
	Dimension		Drop(3)	
	DATA Drop / 1,13,17/
!
!	ii = 0
	jj = 0	
	do 40 j = 1,nStif
	do 10 k = 1,3
	if(j == Drop(k)) then
		go to 40
	end if
   10	continue
	jj = jj+1
!
	ii = 0
	do 30 i = 1,nStif
!
	do 20 k = 1,3
	if(i == Drop(k)) then
		go to 30
	end if
   20	continue
!
	ii = ii+1
	Sn(ii,jj) = Ss(i,j)
   30 continue
!	ii = mod(ii,nSn)		! reset row
   40 continue
!
!	Check each col. vector for NOT Null
!
	Add = 0.D0
	do 70 j = 1,nSn
	sum = 0.0 
	do 60 i = 1,nSn	
	sum = sum + Sn(i,j)
   60 continue
	Add(j) = sum
   70 continue			
!
	OPEN (unit = 15, FILE = 'Stiffness.prt', STATUS = 'NEW')
	do 110 i = 1,nSn
	write(15,1010) nSn,nSn,i,(Sn(i,j),j = 1,nSn)
  110	continue
!
!
 1010 format("Reduced Stiffness Matrix:Stif(",I3,",",I3,")"/
     &        I5/(6(8(f10.6,1X)/)/))
	return
	end

	Subroutine Extract_ContractedLoadVector(Ff,nFf,Fc,nFc)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM
!	EQUATIONS 1,13,17 Rows NEED TO GO
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
	Dimension		Drop(3)	
	DATA Drop / 1,13,17/
!
	ii = 0
!			
	do 20 i = 1,nFf
	do 10 k = 1,3
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
	Dimension		Drop(3)	
	DATA Drop / 1,13,17/
!
	Xf = 0.0	! initialize
	ii = 0
!			
	do 20 i = 1,nXf
	do 10 k = 1,3
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