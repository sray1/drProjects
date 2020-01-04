	Subroutine DeformOut_MatLab_Hem4(XLF,Qd,Qc,Conv,sign,iter,
     &                                 	iOut,iOutS,EndwSav,Nel)
!	============================================================
!					HARDCODED FOR 2x2 SHELL MODEL
!					@ LoadStep = 11, the deformed
!					edges are shown.
!	============================================================
	Implicit Real(kind=8) (a-h,o-z)

	include 'LoadStepIter.h'
	include 'Examples.h'
	include 'Output.h'
	include 'geometry.h'
	include 'SizeVar.h'

	logical SaveStep
!
!	Real(kind=4)	u,v,w,t    
	
	Real(kind=8)	Qc(nDim,nQc1,nQc2),Coord(nDim)    
      Real(kind=8)	Ao12N                                
      Dimension		Ao12N(3,3)
	Real(kind=8)	Qd     ,EndwSav     ,DefSav   
	Dimension		Qd(nQd),EndwSav(4,*),DefSav(3,nPtsi*4)
	Real(kind=8)	Dis      ,Rot    
	Dimension		Dis(nDim),Rot(nDim)
	character*1		sign
	Data			zero/0.D0/,one/1.D0/,two/2.D0/
!-------------------------------------------- need to save?
!	if(Nel.GT.1) return
	piby2	= two*datan(1.D0)
!-------------------------------------------- need to save?
!	===============
	RefLoad = 1.D0
!	===============
!	if(mod(iStep,nPStep).eq.0) Then
!	if(iStep == 1) Then			! HARDCODED
	if(iStep == 0.OR.iStep == 13) Then			! HARDCODED
		SaveStep = .true.	
	else		
		go to 70	
	endif
!	--------------------------------------------		 
	DefSav = 0.D0
	nPtsi2 = 2*nPtsi
	nPtsi3 = 3*nPtsi
	nPts04 = 4*nPtsi
	delri	= 1.D0/(dble(nPtsi-1))
	delrj	= 1.D0/(dble(nPtsj-1))
	ri		= -delri
	rj		= -delrj
	m		= 0
!	-----------------------------
	do 50 j = 1,nPtsj
	rj = rj + delrj
	do 40 i = 1,nPtsi
	m = m+1
	ri = ri + delri
!	-------------------------------------------- Calc Coords		 
	Coord = 0.D0
	call CalcCoords_at_a_Pt_Hem4(Coord,Ao12N,ri,rj,Nel)
!
	xc = Coord(1)
	yc = Coord(2)
	zc = Coord(3)
!	-------------------------------------------- Calc Displacements		 
	Dis = 0.D0
	call CalcDis_at_a_Pt(Dis,Qd,nQd,nDim,nQd1,nQd2,ri,rj)
!	----------------------- Cartesian: x,y,z
	Dis = MATMUL(Ao12N,Dis)
!	------------
	u	= Dis(1)
	v	= Dis(2)
	w	= Dis(3)
!	--------------------------------------------
	if(j == 1) then
		DefSav(1,m) = xc+u
		DefSav(2,m) = yc+v
		DefSav(3,m) = zc+w
	else
		n = nPtsi3-m+nPtsi2+1
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


!	-------------------------------------------- Calc Coords		 
		Coord = 0.D0
		call CalcCoords_at_a_Pt_Hem4(Coord,Ao12N,ri,rk,Nel)
!
		xc = Coord(1)
		yc = Coord(2)
		zc = Coord(3)
!	-------------------------------------------- Calc Displacements		 
		Dis = 0.D0
		call CalcDis_at_a_Pt(Dis,Qd,nQd,nDim,nQd1,nQd2,ri,rk)
!	----------------------- Cartesian: x,y,z
		Dis = MATMUL(Ao12N,Dis)
!	------------
		u	= Dis(1)
		v	= Dis(2)
		w	= Dis(3)
!	--------------------------------------------
		DefSav(1,m) = xc+u
		DefSav(2,m) = yc+v
		DefSav(3,m) = zc+w
   45		continue
	else
		ri	= 0.D0
		rk	= -delri
		do 55 i = 1,nPtsi
		m = m+1
		rk = rk + delri


!	-------------------------------------------- Calc Coords		 
		Coord = 0.D0
		call CalcCoords_at_a_Pt_Hem4(Coord,Ao12N,ri,rk,Nel)
!
		xc = Coord(1)
		yc = Coord(2)
		zc = Coord(3)
!	-------------------------------------------- Calc Displacements		 
		Dis = 0.D0
		call CalcDis_at_a_Pt(Dis,Qd,nQd,nDim,nQd1,nQd2,ri,rk)
!	----------------------- Cartesian: x,y,z
		Dis = MATMUL(Ao12N,Dis)
!	------------
		u	= Dis(1)
		v	= Dis(2)
		w	= Dis(3)
!	--------------------------------------------
		n = nPts04-m+nPtsi3+1
		DefSav(1,n) = xc+u
		DefSav(2,n) = yc+v
		DefSav(3,n) = zc+w
   55		continue
	endif
!	====================================================================================
	ri		= -delri
   50	continue
!	----------------------------------------------------- Plot Save
!	if(mod(iStep,nPStep).eq.0) Then
!	if(iStep == 1) Then			! HARDCODED
	if(iStep == 0.OR.iStep == 13) Then			! HARDCODED
		iPlotCountDef  = iPlotCountDef + 1
		do 60 n = 1,nPts04
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
!	//////////////////////--------------------------------- Computed at control node 0,0
		if(Nel == 1) then
			call CalcDis_at_a_Pt(Dis,Qd,nQd,nDim,nQd1,nQd2,zero,zero)
			iPlotCountEnd  = iPlotCountEnd + 1
			EndwSav(2,iStep+1) = ABS(Dis(3))				! wEnd
		elseif(Nel == 2) then 
			call CalcDis_at_a_Pt(Dis,Qd,nQd,nDim,nQd1,nQd2,one,zero)
			EndwSav(3,iStep+1) = ABS(Dis(3))				! wEnd
			EndwSav(1,iStep+1) = XLF*RefLoad
		endif
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
