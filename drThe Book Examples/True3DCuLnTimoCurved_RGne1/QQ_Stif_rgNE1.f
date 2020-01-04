	Subroutine QQ_Stif_rgNE1(E,G,XP,Qc,nQc,R,V,Stif,nStif,Det,Axes,
     &												Nel,NelType,Iout)
!======================================================================
!	INTERPOLATION: U(m,b,s) = u(s) + .....
!=================================================	
!	Inputs
!		Qc(1,nQc)	= Bezier X-Coordinates
!					=	(qc00x qc10x...qc33x)
!		Qc(2,nQc)	= Bezier Y-Coordinates
!					=	(qc00y qc10y...qc33y)
!		R			= r-directional root domain value	
!		S			= r-directional root domain value
!		Nel			= Element Number
!		NelType		= Element Type:
!						0 = Plane Stress
!						1 = Plane Strain
!						2 = Axi-symmtric	(NOT DONE YET)
! 	
!	Outputs 
!		Stif(nStif,nStif)		= Stiffness matrix: 
!									at a point (R,S)
!		Det			= determinant of The Jacobian
!
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	XP   
	Dimension		XP(4)			! XP(1)=tm/XP(2)=A/XP(3)=XII/XP(4)=XIO
	Real(kind=8)	Qc       ,Stif
	Dimension		Qc(3,nQc),Stif(nStif,nStif)
	Real(kind=8)	Det,R,S
	integer			nDegR,nDegS,Nel,NelType,Iout
!
!		ndegR					= Bezier degree in r-dir = 4
!		ndegS					= Bezier degree in s-dir = 4
!
	Real(kind=8)	dum,xMult,dxbardr,Curvature,Torsion,Radius
	Real(kind=8)	Br   
	Dimension		Br(nQc)
	Real(kind=8)	H1D     ,Axes      	 
	Dimension		H1D(nQc),Axes(3,3)
	Real(kind=8)	AJ,     AJI 
	Real(kind=8)	CTDis   
	Dimension		CTDis(2,50)

!--------------	
	nDof	= 6
!-------------------------------------------------- Displacement/Bernstein
	call Bernstein(Br,nQc,R,iOut)
!------------------------------------------------------
!	Inverse & determinant of Jacobian
!	=====================
!	nPts = 50
!	delri = 1.D0/(nPts-1)

!	do 20 l = 1,nPts
!	xl = l
!	r = (xl-1.D0)*delri
!	=====================
!
	call QQ_TMB_CuLn(Qc,nQc,nQc,R,H1D,Det,CV,TS,Axes,
     &						dxbardr,Nel,Iout,iPrt)
!	=================================================
!	CTDis(1,l) = CV
!	CTDis(2,l) = TS
!   20 continue
!	=================================================
	CC					= CV*CV
	CT					= CV*TS	 
	TT					= TS*TS
!------------------------------------------------ Set For Checking: Rootg = 1
	iRootG	= 2	 
!	===========	 
     	if(iRootG == 1) Then			
		ALFM	= 1.D0
		BETM	= 0.D0
		GAMM	= 1.D0
		XK		= 5.D0/6.D0			! Shear Factor
     	elseif(iRootG.NE.1) Then			
		XAM		= CV * XP(1)
		ALFM	= DLOG((2.D0+XAM)/(2.D0-XAM))/XAM
		BETM	= (ALFM-1.D0)/CV
		GAMM	= 12.0D0*(ALFM-1.D0)/XAM/XAM
		XK		= 1.D0				! Shear Factor
	endif
!------------------------------------------------ End: Set
	XA		= XP(2)*ALFM
	XB		= XP(2)*BETM
	XI		= XP(3)*GAMM
	XO		= XP(4)*ALFM
	XJ		= XO + XI
!
	EA		= E*XP(2)
	EAM		= E*XA
	EAB		= E*XB
	EIM		= E*XI
	EOM		= E*XO
!
	XG		= XK*G	
!
	GAK		= XG*XP(2)
	GAM		= XG*XA
	GAB		= XG*XB
	GIM		= G*XI
	GOM		= G*XO
	GJM		= GIM+GOM
!	============================
!--------------------------------------------
!	Strain displacement Matrix for Quartic
!	u:		j= 1, 2, 3, 4, 5		| eps_X
!	v:		j= 6, 7, 8, 9,10		| gam_XY
!	w:		j=11,12,13,14,15		| gam_XZ
!	thetaX:	j=16,17,18,19,20		| tor_X
!	thetaY:	j=21,22,23,24,25		| ki_XZ
!	thetaZ:	j=26,27,28,29,30		| ki_XY
!----------------------------------
!	Axis(1,..)	= T	---> x
!	Axis(2,..)	= B	---> y
!	Axis(3,..)	= M	---> z
!----------------------------------
!	XZ - In-Plane		(Depth)
!	Y  - Out-of-Plane	(Width)
!----------------------------------
	AJI			= 1.D0/det
	AJI			= 1.D0/dxbardr
!
	Wt			=  V*Det
!
	do 70 i = 1,nQc								! Lower Triangle Blocks
	do 70 j = 1,nQc
	i0 = i+0*nQc 
	i1 = i+1*nQc 
	i2 = i+2*nQc 
	i3 = i+3*nQc 
	i4 = i+4*nQc 
	i5 = i+5*nQc 
!
	j0 = j+0*nQc 
	j1 = j+1*nQc 
	j2 = j+2*nQc 
	j3 = j+3*nQc 
	j4 = j+4*nQc 
	j5 = j+5*nQc 
!
	BI					= Br(i)
	BJ					= Br(j)
	BII					= BI*BI
	BJJ					= BJ*BJ
	BIJ					= BI*BJ
!
	HI					= H1D(i)*AJI	 
	HJ					= H1D(j)*AJI	 
	HII					= HI*HI
	HJJ					= HJ*HJ
	HIJ					= HI*HJ
!
	BIHI				= BI*HI
	BJHJ				= BJ*HJ
	BIHJ				= BI*HJ
	BJHI				= BJ*HI
!===========================================================================
!	EAB = 0.D0
!	GAB = 0.D0
	Stif(i0,j0)	=  Stif(i0,j0) + WT*(EAM*HIJ + GAM*CC*BIJ)				!u						
	Stif(i1,j0)	=  Stif(i1,j0) - WT*(GAM*CT*BIJ)		
	Stif(i2,j0)	=  Stif(i2,j0) + WT*((GAM*BJHI-EAM*BIHJ)*CV)		
	Stif(i4,j0)	=  Stif(i4,j0) - WT*(EAB*HIJ + GAM*CV*BIJ)		
!
	Stif(i1,j1)	=  Stif(i1,j1) + WT*(GAM*(HIJ+TT*BIJ))					!v
	Stif(i2,j1)	=  Stif(i2,j1) + WT*(GAM*TS*(BIHJ-BJHI))		
	Stif(i3,j1)	=  Stif(i3,j1) + WT*(GAB*HIJ)		
	Stif(i4,j1)	=  Stif(i4,j1) + WT*(GAM*TS*BIJ)		
!
	Stif(i2,j2)	=  Stif(i2,j2) + WT*(EAM*CC*BIJ + GAM*(TT*BIJ+HIJ))		!w	
	Stif(i3,j2)	=  Stif(i3,j2) + WT*(GAB*TS*BJHI) 		
	Stif(i4,j2)	=  Stif(i4,j2) + WT*(EAB*CV*BJHI - GAM*BIHJ)					               	
!
	Stif(i3,j3)	=  Stif(i3,j3) + WT*(EOM*CC*BIJ + GJM*HIJ)				!rotS 
	Stif(i4,j3)	=  Stif(i4,j3) - WT*(EOM*CT*BIJ)			
!
	Stif(i4,j4)	=  Stif(i4,j4) + WT*(EIM*HIJ + EOM*TT*BIJ + GAM*BIJ)	!rotB
!==============================================================================
     	if(iRootG == 1) Then				
		Stif(i5,j0)	=  Stif(i5,j0) - WT*(EAB*TS*BIHJ)		
		Stif(i5,j1)	=  Stif(i5,j1) + WT*(GAK*BIHJ)						!rotM							
		Stif(i5,j2)	=  Stif(i5,j2) + WT*((EAB*CT + GAK*TS)*BIJ)					               	
		Stif(i5,j3)	=  Stif(i5,j3) + WT*(CV*(EOM*BJHI - GJM*BIHJ) + 
     &									GAB*BIHJ)			
		Stif(i5,j4)	=  Stif(i5,j4) + WT*(TS*(EIM*BIHJ - EOM*BJHI))		
		Stif(i5,j5)	=  Stif(i5,j5) + WT*(TT*EIM*BIJ + EOM*HIJ +			 
     &									GAK*BIJ + CC*GJM*BIJ -
     &									2.D0*(GAB)*CV*BIJ)
     	else
		Stif(i5,j0)	=  Stif(i5,j0) - WT*(EAB*TS*BIHJ)		
		Stif(i5,j1)	=  Stif(i5,j1) + WT*(GAK*BIHJ)		
		Stif(i5,j2)	=  Stif(i5,j2) + WT*((EAB*CT + GAK*TS)*BIJ)					               	
		Stif(i5,j3)	=  Stif(i5,j3) + WT*(CV*(EOM*BJHI - GOM*BIHJ))			
		Stif(i5,j4)	=  Stif(i5,j4) + WT*(TS*(EIM*BIHJ - EOM*BJHI))		
		Stif(i5,j5)	=  Stif(i5,j5) + WT*(TT*EIM*BIJ + EOM*HIJ +			 
     &						         GAK*BIJ + CC*GOM*BIJ)
      endif
!=============================================================================					
   70 continue			
!--------------------------
  100	continue
!
	iPrtStrDis = 0
	if(iPrtStrDis == 1) Then
		write(Iout,1010) R,det,(i,(Stif(i,j),j = 1,nStif),i=1,6)
!		Pause
	endif
!
	return
!
 1000	format(A,I5,A)
 1010 format("Strain-Displacement Matrix B(6,15)"/
     &        "R = ",f20.16,2X,"det = ",f20.16/(I5/,6(5(f10.7,1X)/)))
	end
