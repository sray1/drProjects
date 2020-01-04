	Program Try_Cubic_Beam_Beta_W
!
!	Try Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!	Notes:	Nint should be atleast 2
!			nStif MUST be 8
!
!	Inputs
!		Qc(4)		= Bezier X-Coordinates
!					=	(qc00x qc10x...qc33x)
!		Nel			= Element Number
!		NelType		= Element Type:
!		Nint		= Number of Gauss Points
!		E			= Elasticity Modulus
!		PR			= Poisson's ratio
!		Thk			= Thickness
!		nStif		= Row or Col size of Stiffness matrix ( MUST BE 8)
!		Iout		= Error Output file#
!		Stif(8,8)	= Desired Stiffness Matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!
	common A(1000000)
!
!	Input Variables & Arrays
!
	Real(kind=8)	E,PR,Thk,xLx,xLy,Trace
	integer			Nel,NelType,Iout,nStifS,nStifN,nDegR
	integer			n1,n2
	real(kind = 8)	Disp
	dimension		Disp(2)
!		
!	
!	Output Variables & Arrays	
!
	nStifS	= 8
	nStifN	= 6
	nDegR	= 4
	Nel		= 1
!	Nint	= 3		! Gauss Order
	Nint	= 6		! Gauss Order
	IoDW	= 15	! I/O Default Write
!
!	Stress-Strain Law
!
!	NelType	= 1		! Plain Strain
	NelType	= 0		! Plain Stress
	E		= 1.D0	 	
	PR		= 0.25D0	! Poisson's Ratio
	Thk		= 1.D0 ! thickness
!
!	Array sizes
!
	nSzInt	= 4 !bytes
	nSzDbl	= 8 !bytes
	n1		= 1								! Qc(4)
	n2		= n1 + nDegR*nSzDbl				! S(8,8) Singular
	n3		= n2 + nStifS*nStifS*nSzDbl		! S(6,6) Non-Singular
	n4		= n3 + nStifN*nStifN*nSzDbl		! F(8)
	nEnd	= n4 + nStifS*nSzDbl		
!
!	Set Bezier Coordinates 
!
	xLx = 100.0D0
	xLy = 1.0D0
!	xLx = 10.D0
!	xLy = 0.01D0
	call BZ_Coords(A(n1),nDegR,xLx)
!
!	Get Stiffness Matrix 
!
	call Quad_CC_STIF(A(n1),nDegR,Nel,NelType,Nint,E,PR,Thk,xLy,
     &					A(n2),nStifS,Iout,Trace)
!
!	Get Load Vector for Shear Load at End 
!
	
	call Set_ExtLoad(A(n4),nStifS)
!
!	displacement Controls:Qd
!
	n6		= nEnd
	n7		= n6 + nStifS*nStifS*nSzDbl
	nEnd	= n6 + nStifS*nSzDbl
!
!	Make NonSingular by dropping Row/Cols corresponding to Bndry Conds
!	Five fixity: Eqn. #s : 1,5
!	SO FINAL TOTAL EQUATION = 8-2=6
!
!	Solve 
! EITHER
!
	call Extract_NonSingularStif(A(n2),nStifS,nStifS,A(n3),nStifN,
     &														nStifN)
	call Extract_ContractedLoadVector(A(n4),nStifS,A(n4),nStifN)
!
	call Solve_AxEqB(A(n3),A(n4),A(n6),nStifN,nStifN)
!
	call Expand_BezierDispControls(A(n6),nStifN,A(n4),nStifS)
!
!	Compute Displacement
!
	call Compute_Displacement(A(n4),16,2,1.D0,0.5D0,D)
!
	Stop 'OK'
	end 
!
	Subroutine BZ_Coords(Qc,nC,xLx)
	
	real(kind = 8)	Qc
	Dimension		Qc(nC)
	real(kind = 8)	xLx
	integer			nC
!
	Qc			= 0.			! zero all
!
	Qc(2)		= xLx/3.D0
	Qc(3)		= 2.D0*xLx/3.D0
	Qc(4)		= xLx
!
	return
	end
	
	Subroutine Set_ExtLoad(Qf,nDim)
	
	real(kind = 8)	Qf
	Dimension		Qf(nDim)
!	
	Qf		= 0.		! All Zero
	Qf(4)	= 1.0
!
	return
	end
!	  			
	Subroutine Extract_NonSingularStif(Ss,nSsI,nSsJ,Sn,nSnI,nSnJ)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM
!	EQUATIONS 1,5 ROWS & COLS NEED TO GO: Cantilever beam
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
	DATA Drop / 1,5/
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
 1010 format("Reduced Stiffness Matrix:Stif(nSnI,nSnI)"/
     &        I5/(3(9(f10.6,1X)/)/))
	return
	end

	Subroutine Extract_ContractedLoadVector(Ff,nFf,Fc,nFc)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM
!	EQUATIONS 1,5 Rows NEED TO GO Cantilever Beam
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
	DATA Drop / 1,5/
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
	Dimension		Drop(2)	
	DATA Drop / 1,5/
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