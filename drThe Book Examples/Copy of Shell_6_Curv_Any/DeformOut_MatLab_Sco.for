	Subroutine DeformOut_MatLab_Sco(XLF,Qd,Qc,Conv,sign,iter,
     &                                 	iOut,iOutS,EndwSav)
	Implicit Real(kind=8) (a-h,o-z)

	include 'LoadStepIter.h'
	include 'Output.h'
	include 'geometry.h'
	include 'SizeVar.h'

	logical SaveStep
!
!	Real(kind=4)	u,v,w,t    
	
	Real(kind=8)	Qc(nDim,nQc1,nQc2),Coord(nDim)    
	
	Real(kind=8)	Qd     ,EndwSav     ,DefSav   
	Dimension		Qd(nQd),EndwSav(4,*),DefSav(3,nPtsi*(nPtsj+1))
	Real(kind=8)	Dis      ,Rot    
	Dimension		Dis(nDim),Rot(nDim)
	character*1		sign
	Data			zero/0.D0/,one/1.D0/,two/2.D0/
!-------------------------------------------- need to save?
	piby2	= two*datan(1.D0)
!-------------------------------------------- need to save?
	if(mod(iStep,nPStep).eq.0) Then
		SaveStep = .true.	
	else		
		go to 70	
	endif
!	--------------------------------------------		 
	DefSav = 0.D0
	nPtsij = nPtsi*(nPtsj+1)
	delri	= 1.D0/(dble(nPtsi-1))
	delrj	= 1.D0/(dble(nPtsj-1))
	ri		= -delri
	rj		= -delrj
!	-----------------------------
	do 50 j = 1,nPtsj
	m = 0
	rj = rj + delrj
	do 40 i = 1,nPtsi
	m = m+1
	ri = ri + delri
!	-------------------------------------------- Calc Displacements		 
	Dis = 0.D0
	call CalcDis_at_a_Pt(Dis,Qd,nQd,nDim,nQd1,nQd2,ri,rj)
	Rot = 0.D0
	call CalcRot_at_a_Pt(Rot,Qd,nQd,nDim,nQd1,nQd2,ri,rj)
!	--------------
	u	= Dis(1)
	v	= Dis(2)
	w	= Dis(3)
	t	= Rot(2)
!		----------------- Cartesian: horizontal & vertical
!		ang = piby2 - THETAL*(one -ri)
!		ci	= dcos(ang)
!		si	= dsin(ang)
!		uc	=  w*ci + u*si 
!		vc	= -u*ci + v*si
!		----------------------------- Coordinates
!		the = THETAL*ri
!		cc	= dcos(the)
!		ss	= dsin(the)
!		xc	=  Rad*(one-cc)*ci + Rad*ss*si
!		yc	=  Rad*(one-cc)*si + Rad*ss*ci
!
	Coord = 0.D0
	call CalcCoords_at_a_Pt(Coord,Qc,nDim,nQc1,nQc2,ri,rj)
!
	xc = Coord(1)
	yc = Coord(2)
	zc = Coord(3)
!	--------------------------------------------
	if(j == 1) then
		DefSav(1,m) = xc+u
		DefSav(2,m) = yc+v
		DefSav(3,m) = zc+w
	else
		n = nPtsij-m+1
		DefSav(1,n) = xc+u
		DefSav(2,n) = yc+v
		DefSav(3,n) = zc+w
	endif
!	--------------------------------------------
   40	continue
!	====================================================================================
!	-------------------------------------------- plot at ri = 1 edge before rj = 1 edge
!													with nPtsi pts
	if( j == 1) then
		ri	= 1.D0
		rk	= -delri
		do 45 i = 1,nPtsi
		m = m+1
		rk = rk + delri
!		-------------------------------------------- Calc Displacements		 
		Dis = 0.D0
		call CalcDis_at_a_Pt(Dis,Qd,nQd,nDim,nQd1,nQd2,ri,rk)
		Rot = 0.D0
		call CalcRot_at_a_Pt(Rot,Qd,nQd,nDim,nQd1,nQd2,ri,rk)
!		--------------
		u	= Dis(1)
		v	= Dis(2)
		w	= Dis(3)
!
		Coord = 0.D0
		call CalcCoords_at_a_Pt(Coord,Qc,nDim,nQc1,nQc2,ri,rk)
!
		xc = Coord(1)
		yc = Coord(2)
		zc = Coord(3)
!	--------------------------------------------
		DefSav(1,m) = xc+u
		DefSav(2,m) = yc+v
		DefSav(3,m) = zc+w
   45		continue
	endif
!	====================================================================================
	ri		= -delri
   50	continue
!	----------------------------------------------------- Plot Save
	if(MOD(iStep,nPStep) == 0) then
		iPlotCountDef  = iPlotCountDef + 1
		do 60 n = 1,nPtsi*(nPtsj + 1)
		write(iOutS,1020) DefSav(1,n),DefSav(2,n),DefSav(3,n)
   60		continue	 
!	----------------------------------------------------- starting Pt.. to close plot
		write(iOutS,1020) DefSav(1,1),DefSav(2,1),DefSav(3,1)
	endif
!	----------------------------------------------------- starting Pt.. to close plot END
!	====================================================================================
   70 continue
!		----------------------------------------- save for Plot
	if(MOD(iStep,1) == 0) then
		call CalcDis_at_a_Pt(Dis,Qd,nQd,nDim,nQd1,nQd2,1.D0,1.D0)
		iPlotCountEnd  = iPlotCountEnd + 1
		EndwSav(1,iStep+1) = Dis(3)				! wEnd
		EndwSav(2,iStep+1) = 4.D0*XLF
	endif
!-------------------------------------------------- 
!
!	done
!
	return
!
 1010 format(i3,1x,4(3x,e12.5),i5,e12.4,2x,a1)
 1020 format(F15.2,",",F15.2,",",F15.2,",")
 1030 format(i3,e15.5)
	end
