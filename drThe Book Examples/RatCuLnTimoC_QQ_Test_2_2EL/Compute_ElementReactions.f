	Subroutine Compute_ElementReactions(Stif,D,nStif,F,nF,Qc,nQc,P,
     &											RadOfCur,Nel,iOut)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!
!	Inputs
!		nStif					= Row or Col size of Stiffness Control matrix 
!		Stif(nStif,nStif)		= Non-Singular Element Stiffness Matrix
!		D(nStif)				= Element Displacement Control Vector
!		 	
!	Outputs 
!		F						= Element Nodal Reactions at r = 0 & r = 1
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
	Real(kind=8)	Stif		     ,D       ,P        
	Dimension		Stif(nStif,nStif),D(nStif)
	Real(kind=8)	Qc       ,Qx,     Qy     ,Wt
	Dimension		Qc(3,nQc),Qx(nQc),Qy(nQc),Wt(nQc)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	H1D     ,Axes      	 
	Dimension		H1D(nQc),Axes(3,3)
	Real(kind=8)	F    
	Dimension		F(nF)
	Integer			Indx(nF)
!	//////////////////////
	if(nF.NE.6) Then
		stop 'nF.NE.6'
	endif
!	////////////////////// 
!
!	Row Indices: for r = 0 & r = 1
!
	Indx(1)	= 1				! Pr		-- w:		Node I
	Indx(2)	= Indx(1) + nQc	! Pa		-- u:		Node I
	Indx(3)	= Indx(2) + nQc	! Moment	-- theta:	Node I
	Indx(4)	= nQc			! Pr		-- w:		Node J
	Indx(5)	= Indx(4) + nQc	! Pa		-- u:		Node J
	Indx(6)	= Indx(5) + nQc	! Moment	-- theta:	Node J
!	//////////////////////
!
!	Reactions: StifN*DN
!
	F = 0.0D0
!
	do 50 i = 1,nF
	irow = Indx(i)
	sum = 0.0D0
	do 20 j = 1,nStif
	sum = sum + Stif(irow,j)*D(j)
   20	continue
	F(i) = sum*P
   50 continue	
!	///////////////////////////////////////////////////
	write(iOut,1000) Nel
	write(iOut,1010) (F(i),i = 1,nF) 
!   		 
	return
 1000 Format(/2x,"Just before Leaving: Compute_ElementReactions"//
     &		"Element #",i2," Nodal Reactions:"/)
 1010 Format(/2x,"End I: Shear	= ",F12.7/
     &        2x,"       Axial	= ",F12.7/
     &        2x,"       Moment	= ",F12.7/
     &        2x,"End J: Shear	= ",F12.7/
     &        2x,"       Axial	= ",F12.7/
     &        2x,"       Moment	= ",F12.7)
	end   		