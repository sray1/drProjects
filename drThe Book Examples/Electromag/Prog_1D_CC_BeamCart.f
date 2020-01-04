	Program Try_CC_Beam_Cart
!
!
!
	Implicit Real(kind=8) (a-h,o-z)
!
	common A(1000000)
!
!	Input Variables & Arrays
!
	integer			Nel,NelType,Iout,nStif
	integer			n1,n2
	real(kind = 8)	Disp
	dimension		Disp(2)
!		
!	
!	Output Variables & Arrays	
!
	nStifS	= 4
	nSup	= 1	! Fxed End
	nStifN	= nStifS - nSup
	Nel		= 1
	Nint	= 3		! Gauss Order
!	Nint	= 6		! Gauss Order
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
	call Quad_CC_STIF(Nel,NelType,Nint,A(n2),nStifS,Iout,Trace)
!
!	Get Load Vector for Shear Load at End 
!
	call Quad_CC_LV(Nint,A(n4),nStifS)
!
!	displacement Controls:Qd
!
	n6		= nEnd
	n7		= n6 + nStifN*nStifN*nSzDbl
	nEnd	= n6 + nStifN*nSzDbl
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
	call Compute_Displacement(A(n4),nStifS)
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
!	EQUATION 4th ROW & COL NEED TO GO
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
	integer			Drop(1)
	DATA Drop / 4/
	DATA nDrop /1/
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
!	EQUATIONS 4th Rows NEED TO GO
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
	Dimension		Drop(1)	
	DATA Drop / 4/
	DATA nDrop /1/
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
	Dimension		Drop(1)	
	DATA Drop / 4/
	DATA nDrop /1/
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
!-------------------------------------------
!
	return
	end
!
	Subroutine Compute_Displacement(Xf,nRow)
!
!	Xf(nRow=32,nCol=2)		= Full Bezier Displacement Controls (Output)	
!
	real(kind = 8)	Xf   
	Dimension		Xf(nRow)
!
	real(kind = 8)	sum
!
	Real(kind=8)	Br   ,Pot   
	Dimension		Br(4),Pot(2,50)

	nPts = 50
!	//////////////////////--------------------------------- Computed
	Ten4  = 1.E04
	delri = 1.D0/(nPts-1)

	do 20 l = 1,nPts
	xl = l
	r = (xl-1.D0)*delri
!	
!	Define Bernstein Interpolations
!
	Br(1) = (1.-r)*(1.-r)*(1.-r)
	Br(2) = 3.*(1.-r)*(1.-r)*r
	Br(3) = 3.*(1.-r)*r*r
	Br(4) = r*r*r
!	
	sum = 0.0
	do 10 k = 1,4
	sum = sum + Br(k)*Xf(k)
!
   10 continue
	Pot(1,l) = sum
!
!	Source charge density
!
	Pot(2,l) = -5.D0*(1.D0 - r) + Ten4*(r * (1.D0-r))**5
!
   20 continue
	OPEN(UNIT=3,FILE='c:\The Book Examples\Electromag\PlotDef.txt')
	IoutDef		= 3
		do 60 n = 1,nPts
	xl = n
	r = (xl-1.D0)*delri
		write(IoutDef,1020) r,Pot(1,n)
   60		continue	 
		do 70 n = 1,nPts
	xl = n
	r = (xl-1.D0)*delri
		write(IoutDef,1020) r,Pot(2,n)
   70		continue	 
	write(IoutDef,1020) 3.,50.
!
	return
 1020 format(F15.2,",",F15.2,",")
	end   			 			  			  			  		