	Subroutine DeformOut_MatLab_Coord(Qc,nDim,nQc1,nQc2,nPtsi,nPtsj,
     &								iOut,iOutS)
	Implicit Real(kind=8) (a-h,o-z)

!
	
	Real(kind=8)	Qc(nDim,nQc1,nQc2),Coord(nDim)    
	
	Real(kind=8)	DefSav   
	Dimension		DefSav(3,nPtsi*(nPtsj+1))
	Data			zero/0.D0/,one/1.D0/,two/2.D0/
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
!
	Coord = 0.D0
	call CalcCoords_at_a_Pt(Coord,Qc,nDim,nQc1,nQc2,ri,rj)
!
	xc = Coord(1)
	yc = Coord(2)
	zc = Coord(3)
!	--------------------------------------------
	if(j == 1) then
		DefSav(1,m) = xc
		DefSav(2,m) = yc
		DefSav(3,m) = zc
	else
		n = nPtsij-m+1
		DefSav(1,n) = xc
		DefSav(2,n) = yc
		DefSav(3,n) = zc
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
!
		Coord = 0.D0
		call CalcCoords_at_a_Pt(Coord,Qc,nDim,nQc1,nQc2,ri,rk)
!
		xc = Coord(1)
		yc = Coord(2)
		zc = Coord(3)
!	--------------------------------------------
		DefSav(1,m) = xc
		DefSav(2,m) = yc
		DefSav(3,m) = zc
   45		continue
	endif
!	====================================================================================
	ri		= -delri
   50	continue
!	----------------------------------------------------- Plot Save
	do 60 n = 1,nPtsi*(nPtsj + 1)
	write(iOutS,1020) DefSav(1,n),DefSav(2,n),DefSav(3,n)
   60	continue	 
!	----------------------------------------------------- starting Pt.. to close plot
	write(iOutS,1020) DefSav(1,1),DefSav(2,1),DefSav(3,1)
!	----------------------------------------------------- starting Pt.. to close plot END
!	====================================================================================
   70 continue
!
!	done
!
	return
!
 1020 format(F15.2,",",F15.2,",",F15.2,",")
	end
