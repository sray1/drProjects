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
!			nStifEL MUST be 24
!
!	Inputs
!		Qc(1,12)	= Bezier X-Coordinates
!					=	(qc00x qc10x...qc32x)
!		Qc(2,12)	= Bezier Y-Coordinates
!					=	(qc00y qc10y...qc32y)
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
!		Stif(24,24)	= Desired Stiffness Matrix
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
!	nStifActual = 48 - 6 (tie dofs between 2 Elements) = 56
	nQc		= 12
	nStifEL	= 24
	nStif	= 42				! Singular
!------------------------------------------------------------------- Continuity
	iCont	= 0					! 0 = C0/1 = C1/ 2 = C2
!-------------------------------------------------
	if (iCont == 0) then
		nC		= 0 
		nStifC  = nStif - nC	! C0
	else if (iCont == 1) then
		nC		= 6 
		nStifC  = nStif - nC	! size Constrained:36 =42-6(interface dofs)
								! C1-continuity constraint at interface for 
								! interface Bez dofs (6 of them)
								! Working on the Singular stage
	else if (iCont == 2) then
!	------------------------------------------------------------------------
		nC		= 12 
		nStifC  = nStif - nC	! size Constrained:30 = 42-12(interface dofs)
								! C2-continuity constraint at interface for 
								! interface Bez dofs (12 of them)
								! Working on the Singular stage
	end if
!---------------------------------------------------------------- Support Cond
	nSup	= 4
	nStifN  = nStifC - nSup	! size NonSingular: 32 = 36 - 4( 3 supX + 1 SupY)
	                       	! size NonSingular: 26 = 30 - 4( 3 supX + 1 SupY)
!-----------------------------------------------------------------------------
!	Nint	= 4		! Gauss Order
	Nint	= 6		! Gauss Order
	IoDW	= 15	! I/O Default Write
!
!	Stress-Strain Law
!
!----------------------------------------------------------------- DATA
	NelType	= 1			! Plain Strain ( to compare w/ Hughes)
	E		= 1.D0	 	
	PR		= 0.499D0	! Poisson's Ratio
	Thk		= 1.D0		! thickness
	xLx		= 24.D0		!Aspect Ratio for each element		
	xLy		= 12.D0
!-----------------------------------------------------------------
!
!	Array sizes
!
	nSzInt	= 4 !bytes
	nSzDbl	= 8 !bytes
	n1a		= 1								! Qc(2,12)
	n1b		= n1a + 2*nQc*nSzDbl			! Qc(2,12)
	n2		= n1b + 2*nQc*nSzDbl			! S(42,42) Singular / 2ELs(n2)
	n2b		= n2  + nStif*nStif*nSzDbl		! S(24,24) Singular / 1ELs(n2b)
	n4		= n2b + nStifEL*nStifEL*nSzDbl	! F(38) Singular(n4)
	n5		= n4  + nStif*nSzDbl			! Qd(3)
	nEnd	= n5  + 3*nSzDbl				
!
!	Set Bezier Coordinates: Element 1 
!
	Nel = 1
	call BZ_Coords(A(n1a),2,12,xLx,xLy)
!
!	Get Stiffness Matrix: Ist Elem 
!
	call Quad_QC_STIF(A(n1a),Nel,NelType,Nint,E,PR,Thk,A(n2b),nStifEL,
     &					Iout,Trace)
!
!	Assemble Ist Elem
!
	n2c		= nEnd
	nEnd	= n2c + nStifEL*nSzInt
	call Assemble_Stif(A(n2c),A(n2b),nStifEL,A(n2),nStif,Nel,
     & 													Iout,Trace)
!
!	Set Bezier Coordinates: Element 2 
!
	Nel = 2
	call BZ_Coords(A(n1b),2,12,xLx,xLy)
!
!	Get Stiffness Matrix: 2nd Elem : same as first element, so skip
!
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
	call Set_ExtLoad(A(n5),3)
	call Quad_QC_LV(A(n5),A(n4),xLy)
!
!	displacement Controls:Qd
!
!--------------------------------------------------------------------
	n6		= nEnd
	n7		= n6 + nStifC*nStifC*nSzDbl
	nEnd	= n7 + nStifC*nSzDbl
!
!--------------------------------------------------------------------
!	C0_Condition
!--------------------------------------------------------------------
	if (iCont == 0) then
		call Extract_NonSingularStif(A(n2),nStif,nStif,A(n6),nStifN,
     &														iCont)
		call Extract_ContractedLoadVector(A(n4),nStif,A(n7),nStifN,
     &														iCont)
!	call Factor_Determinant(A(n3),A(n4),A(n6),A(n7),29,29,29)
!	call Factor_ConditionNumber(A(n6),A(n2),A(n4),nStifN,
!     &										nStifN,nStifN)
		call Solve_AxEqB(A(n6),A(n7),A(n4),nStifN,nStifN)
		call Compute_StrainEnergy(A(n6),A(n7),A(n4),nStifN,SEnergy,
     &														PEnergy)
	end if
!--------------------------------------------------------------------
!	IMPOSE C1 Condition by transformation 
!	no consideration given to Transformation matrix being sparse
!--------------------------------------------------------------------
		n8		= nEnd
		n9		= n8 + nStif*nStifC*nSzDbl
		nEnd	= n9 + nStif*nSzDbl
!--------------------------------------------------------------------
	if (iCont == 1) then
!		call FormTransformationMatrix_C1(A(n1a),A(n1b),nQC,A(n8),
!     &														nStif)
		call FormTransformationMatrix_C1(A(n8),nStif,nstifC)
		call Impose_Continuity(A(n2),A(n4),nStif,A(n8),A(n6),A(n7)
     &														,nStifC)
!--------------------------------------------------------------------
!	IMPOSE C2 Condition by transformation 
!	no consideration given to Transformation matrix being sparse
!--------------------------------------------------------------------
	else if (iCont == 2) then
		call FormTransformationMatrix_C2(A(n8),nStif,nstifC)
		call Impose_Continuity(A(n2),A(n4),nStif,A(n8),A(n6),A(n7)
     &														,nStif)
	end if
!--------------------------------------------------------------------
!	IMPOSE SUPPORT Conditions & make stiffnes Non-singular
!	PROBLEM SPECIFIC
!	Make NonSingular by dropping Row/Cols corresponding to Bndry Conds
!	Five fixity: Eqn. #s : 1,10,13
!-----------------------------------
	if (iCont == 1.OR.iCont == 2) then
		call Extract_NonSingularStif(A(n6),nStifC,nStifC,A(n2),nStifN,
     &														iCont)
		call Extract_ContractedLoadVector(A(n7),nStifC,A(n4),nStifN,
     &														iCont)
		call Solve_AxEqB(A(n2),A(n4),A(n7),nStifN,nStifN)
		call Compute_StrainEnergy(A(n2),A(n4),A(n7),nStifN,SEnergy,
     &														PEnergy)
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
	xLy2		= xLy/2.
	x2Lx3		= 2.*xLx3
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
!	Qc(2,1)		= 0.
!	Qc(2,2)		= 0.
!	Qc(2,3)		= 0.
!	Qc(2,4)		= 0
!
	Qc(2,5)		= xLy2
	Qc(2,6)		= xLy2
	Qc(2,7)		= xLy2
	Qc(2,8)		= xLy2

!
	Qc(2,9)		= xLy
	Qc(2,10)	= xLy
	Qc(2,11)	= xLy
	Qc(2,12)	= xLy

!
	return
	end
	
	Subroutine Set_ExtLoad(Qf,nDim)
	
	real(kind = 8)	Qf
	Dimension		Qf(nDim)
!	
	Qf		= 0.		! All Zero
	Qf(2)	= 1.0
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
	Subroutine Extract_NonSingularStif(Ss,nSs,nStif,Sn,nSn,iCont)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM
!	EQUATIONS 1,13,17 ROWS & COLS NEED TO GO
!
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
	integer			Drop   ,DropC0   ,DropC1   ,DropC2
	Dimension		Drop(4),DropC0(4),DropC1(4),DropC2(4)	
	DATA DropC0 / 1,5,9,13/
	DATA DropC1 / 1,4,7,10/
	DATA DropC2 / 1,4,7,10/
	DATA nDrop/4/
!
!------------------------------ Initialize
	if( iCont == 0) Then
		do 5 k = 1,nDrop
		Drop(k) = DropC0(k)
    5		continue
	else if( iCont == 1) Then 
		do 6 k = 1,nDrop
		Drop(k) = DropC1(k)
    6		continue
	else if( iCont == 2) Then 
		do 7 k = 1,nDrop
		Drop(k) = DropC2(k)
    7		continue
	end if
!------------------------------
!	ii = 0
	jj = 0	
	do 40 j = 1,nStif
	do 10 k = 1,nDrop
	if(j == Drop(k)) then
		go to 40
	end if
   10	continue
	jj = jj+1
!
	ii = 0
	do 30 i = 1,nStif
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
   40 continue
!
!	Check each col. vector for NOT Null
!
	Add = 0.D0
	do 70 j = 1,nSn
	sum = 0.0D0 
	do 60 i = 1,nSn	
	sum = sum + Sn(i,j)
   60 continue
	Add(j) = sum
   70 continue			
  100	continue
!--------------------------------------------------------------
!	OPEN (unit = 15, FILE = 'Stiffness.prt', STATUS = 'NEW')
!	do 110 i = 1,nSn
!	write(15,1010) nSn,nSn,i,(Sn(i,j),j = 1,nSn)
!  110	continue
!--------------------------------------------------------------
!
 1010 format("Reduced Stiffness Matrix:Stif(",I3,",",I3,")"/
     &        I5/(6(8(f10.6,1X)/)/))
	return
	end

	Subroutine Extract_ContractedLoadVector(Ff,nFf,Fc,nFc,iCont)
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
	integer			Drop   ,DropC0   ,DropC1   ,DropC2
	Dimension		Drop(4),DropC0(4),DropC1(4),DropC2(4)	
	DATA DropC0 / 1,5,9,13/
	DATA DropC1 / 1,4,7,10/
	DATA DropC2 / 1,4,7,10/
	DATA nDrop/4/
!
!------------------------------ Initialize
	if( iCont == 0) Then
		do 5 k = 1,nDrop
		Drop(k) = DropC0(k)
    5		continue
	else if( iCont == 1) Then 
		do 6 k = 1,nDrop
		Drop(k) = DropC1(k)
    6		continue
	else if( iCont == 2) Then 
		do 7 k = 1,nDrop
		Drop(k) = DropC2(k)
    7		continue
	end if
!------------------------------
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