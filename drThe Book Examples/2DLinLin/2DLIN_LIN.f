	Program Try_Quad_LL
!
!	Try Coerced Isoparametric Quadrilateral_Linear_Linear Element
!
!	Notes:	Nint should be atleast 2
!			nStif MUST be 8
!
!	Inputs
!		Qc(1,4)		= Bezier X-Coordinates
!					=	(qc00x qc10x...qc11x)
!		Qc(2,4)		= Bezier Y-Coordinates
!					=	(qc00y qc10y...qc11y)
!		Nel			= Element Number
!		NelType		= Element Type:
!						0 = Plane Stress
!						1 = Plane Strain
!						2 = Axi-symmtric	(NOT DONE YET)
!		Nint		= Number of Gauss Points
!		E			= Elasticity Modulus
!		PR			= Poisson's ratio
!		Thk			= Thickness
!		nStif		= Row or Col size of Stiffness matrix ( MUST BE 8)
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
	integer			n1,n2,nRedu,nsize
!	
!	Output Variables & Arrays	
!
	nStif	= 8
	nRedu	= 5
	nSize 	= nStif/2
	nOrder	= 2		! for Linear
	Nel		= 1
	Nint	= 2		! Gauss Order
	IoDW	= 15	! I/O Default Write
!
!	Stress-Strain Law
!
	NelTyp	= 1		! Plain Strain
	E		= 1.D0	 	
	PR		= 0.25D0	! Poisson's Ratio
	Thk		= 1.0D0 ! thickness
!
!	Array sizes
!
	nSzInt	= 4 !bytes
	nSzDbl	= 8 !bytes
	n1		= 1								! Qc(2,nsize)
	n2		= n1 + 2*nsize*nSzDbl			! S(nStif,nStif) Singular
	n3		= n2 + nStif*nStif*nSzDbl		! S(nRedu,nRedu) Non-Singular
	n4		= n3 + nRedu*nRedu*nSzDbl		! F(nStif)
	n5		= n4 + nStif*nSzDbl				! Qd(nOrder)
											!	only on side (surface traction)
	nEnd	= n5 + nOrder*nSzDbl				
!
!	Set Bezier Coordinates 
!
	xLx = 1.
	xLy = 1.
	call BZ_Coords(A(n1),2,nSize,xLx,xLy)
!
!	Get Stiffness Matrix 
!
	call Quad_LL_STIF(A(n1),Nel,NelTyp,Nint,E,PR,Thk,A(n2),nStif,
     &						nOrder,nSize,Iout,Trace)
!
!	Get Load Vector for Shear Load at End 
!
	
	call Set_ExtLoad(A(n5),nOrder)
	call Quad_LL_LV(A(n5),A(n4),xLy,nOrder,nStif)
!
!	displacement Controls:Qd
!
	n6		= nEnd
	n7		= n6 + nStif*nStif*nSzDbl
	nEnd	= n6 + nStif*nSzDbl
!
!	PROBLEM SPECIFIC
!	Make NonSingular by dropping Row/Cols corresponding to Bndry Conds
!	Three fixity: Eqn. #s : 1,3,5
!	SO FINAL TOTAL EQUATION = 8-3=5
!
!	Solve 
! EITHER
!
	call Extract_NonSingularStif(A(n2),nStif,nStif,A(n3),nRedu,nRedu)
	call Extract_ContractedLoadVector(A(n4),nStif,A(n4),nRedu)
!	call Factor_Determinant(A(n3),A(n4),A(n6),A(n7),nRedu,nRedu,nRedu)
	call Solve_AxEqB(A(n3),A(n4),A(n6),nRedu,nRedu)
!
! OR
!	call AddSupport_Stif(A(n2),32,32,Trace)
!	call MultSupport_Load(A(n4),32,Trace)
!	call Solve_AxEqB(A(n2),A(n4),A(n6),32,32)
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
	Qc(1,2)		= xLx
!	Qc(1,3)		= 0.0
	Qc(1,4)		= xLx
!
!	Qc(2,1)		= 0.
!	Qc(2,2)		= 0.
	Qc(2,3)		= xLy
	Qc(2,4)		= xLy

!
	return
	end
	
	Subroutine Set_ExtLoad(Qf,nDim)
	
	real(kind = 8)	Qf
	Dimension		Qf(nDim)
!	
	Qf		= 0.		! All Zero
	Qf(1)	= 5.0*0.4/400.
								!1/.4 from stiffness side (Material factor)
								!1/400 material factor
	Qf(2)	= 5.0*0.4/400.
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
!	EQUATIONS 1,13,17 ROWS & COLS NEED TO GO
!
!	Ss(nSsI,nSsJ)		= Stiffness-Singular Matrix (INPUT)	
!	Sn(nSnI,nSnJ)		= Stiffness-NonSingular Matrix (OUTPUT)
!
	real(kind = 8)	Sn           ,Ss
	Dimension		Sn(nSnI,nSnJ),Ss(nSsI,nSsJ)
	real(kind = 8)	sum,Add(29)
!
!
	integer i,j,ii,jj
!
	integer			Drop
	Dimension		Drop(3)	
	DATA Drop / 1,3,5/
!
	ii = 0
	jj = 0
!			
	do 40 j = 1,nSsJ
	do 10 k = 1,3
	if(j == Drop(k)) then
		go to 40
	end if
   10	continue
	jj = jj+1
	do 30 i = 1,nSsI
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
	write(*,1000) nSnI,nSnI
	do 80 i = 1,nSnI
	write(*,1010)(Sn(i,j),j = 1,nSnI)
   80	continue
	Pause
	return
!
 1000 format("Reduced Stiffness Matrix:Stif(",I5,",",I5,")")
 1010 format((5(f10.6,1X)/))
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
	DATA Drop / 1,3,5/
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
	  			  		