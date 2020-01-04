	Subroutine Quad_QQ_STIF(Qd,Qc,UQc,nQc,Nel,NelType,Nint,D,
     &		THETAL,Radius,Stif,BFors,StifK,nStif,Iout,Trace)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!	Notes:	Nint should be atleast 2
!
!	Inputs
!		Qd(nStif)	= Latest displacement solution: state vector
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
!		 	
!	Outputs 
!		Stif(nStif,nStif)	= Desired Stiffness Matrix
!		bFors(nStif)		= Desired Body force Vector Integrals
!		StifK(nStif)		= Desired kLamda Stiffness last column Vector Integrals
!		Trace		= trace of the matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
	Real(kind=8)	Qc       
	Dimension		Qc(2,nQc)
	Real(kind=8)	Qd       ,UQc       ,D   ,Radius,Depth,Width
	Dimension		Qd(nStif),UQc(2,nQc),D(3)
	integer			Nel,NelType,Iout,nStif
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	BFors       ,StifK       ,Stif			   ,Trace
	Dimension		BFors(nStif),StifK(nStif),Stif(nStif,nStif)
	Real(kind=8)	EDG     ,B         ,DB   ,Add    
	Dimension		EDG(6,6),B(6,nStif),DB(6),Add(nStif)
	Real(kind=8)	BVEC       ,SKLM    
	Dimension		BVEC(nStif),SKLM(nStif)
	Real(kind=8) AM,BM,CM,TH,Ri,Si,Wt,sum
!----------------------------------------------------------
!	Stiffness Matrix Calculation
!
	BFors	= 0.D0	!all
	StifK	= 0.D0	!all
    	Stif	= 0.D0	! all elements = 0.
!
	iPrt = 0
	If (iPrt == 1) Then
		write(Iout,1000) Nel,(i,(Qc(i,j),j=1,nQc),i=1,2)
	endif

!	Loop over Gauss Locations
	do 60 lr = 1,Nint
	Ri = GaussPtVal(lr,Nint,1) 
!
!------------------------------------------------------------- Get  B(6,3*nQc)
	Call QQ_StrainDispMat(Qc,nQc,Ri,Radius,THETAL,B,nStif,Det,
     &									Nel,NelType,Iout)
!------------------------------------------------------------- Get  EDG(6,6)
	call QQ_EtranDEplusGMatrix(UQc,nQc,Qd,nStif,Ri,Radius,D,Det,
     &				THETAL,BVEC,SKLM,EDG,Nel,NelType,Iout)
!------------------------------------------------------------- Form: Btran_EDG_B 
!	Add to stiffness matrix
!
	Wt = GaussPtVal(lr,Nint,2)*Det
!
	do 50 j = 1,nStif
	do 20 k = 1,6		! 
	DB(k) = 0.0
	do 20 l = 1,6		! 
	DB(k) = DB(k) + EDG(k,l)*B(l,j)
   20 continue
	do 40 i = j,nStif
	sum = 0.0
	do 30 l = 1,6		! 
	sum = sum + B(l,i)*DB(l)
   30	continue
	Stif(i,j) = Stif(i,j) + sum*Wt
   40	continue
   50 continue
!------------------------------------------------------------- Load Vector: Residual & Body force part 
	do 53 i = 1,nStif
	BFors(i) = BFors(i) + Wt*BVec(i)
   53 continue		
!------------------------------------------------------------- Form: Last Column of
!                                                              stiffness: KLamda Body Force part
 
	do 55 i = 1,nStif
	StifK(i) = StifK(i) + Wt*SKLM(i)
   55 continue		
   60 continue
!
!	symmetry: Upper Triangle 
!
	do 70 j = 1,nStif
	do 70 i = j,nStif
  	Stif(j,i) = Stif(i,j)
   70 continue
!
!	Get Trace
!
	Trace = 0.D0
	do 80 i = 1,nStif
	Trace = Trace + Stif(i,i)
   80 continue			
!
!	Check each col. vector for Null
!
	Add = 0.D0
	do 100 j = 1,nStif
	sum = 0.0 
	do 90 i = 1,nStif	
	sum = sum + Stif(i,j)
   90 continue
	Add(j) = sum
  100 continue			
!
!	done
!
	iPrt = 0
	if(iPrt == 1) Then
		write(Iout,1010) nStif,nStif
		do 110 i = 1,nStif
		write(Iout,1020) i,(Stif(i,j),j = 1,nStif)
  110	continue
	endif 
!
	return
!
 1000 format("QC(2,5): Elem# =",I4/
     &        2(I5,5X,5(f10.6,1X)/) )
 1010 format("Full Stiffness Matrix:Stif(",I2,",",I2,")"/)
 1020 format(I5/(3(5(f16.6,1X)/)/))
	end   		
	   		