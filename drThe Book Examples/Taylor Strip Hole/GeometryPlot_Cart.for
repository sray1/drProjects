	Subroutine GeometryPlot_Cart(Qc,nDim,nQc1,nQc2,R_IN,DEPTH,ANGLE,
     &			nPtsi,nPtsj,iElem,nElems,SaveC,nPts,iOut,iOutG)
	Implicit Real(kind=8) (a-h,o-z)

!
!	Real(kind=8)	uT,uR,xc,yc   
	
	Real(kind=8)	Qc(nDim,nQc1,nQc2),Coord(nDim),SaveC(nDim,nPts)    
	
	character*1		sign
	Data			zero/0.D0/,one/1.D0/,two/2.D0/
!	--------------------------------------------
	delri	= 1.D0/(dble(nPtsi-1))
	delrj	= 1.D0/(dble(nPtsj-1))
!
	m		= 0
!	==================================================================================== Outer Radius
	ri	= 0.D0
	rj	= -delrj
	do j = 1,nPtsj
		rj = rj + delrj
!		-------------------------------------------- Calc Coordinates		 
		Coord = 0.D0
		call Calc_Coords_at_a_Pt(Coord,Qc,nDim,nQc1,nQc2,ri,rj)
!		-------------------------------------------- Save
		m = m + 1
		SaveC(1,m) = Coord(1)
		SaveC(2,m) = Coord(2)
	end do !j
!	==================================================================================== radial at 90
	rj	= 1.D0
	ri	= -delri
	do i = 1,nPtsi
		ri = ri + delri
!		-------------------------------------------- Calc Coordinates		 
		Coord = 0.D0
		call Calc_Coords_at_a_Pt(Coord,Qc,nDim,nQc1,nQc2,ri,rj)
!		-------------------------------------------- Save
		m = m + 1
		SaveC(1,m) = Coord(1)
		SaveC(2,m) = Coord(2)
	end do !i
!	==================================================================================== Inner Radius backward
	ri	= 1.D0
	rj	= -delrj
	ms	= m
	do j = 1,nPtsj
		rj = rj + delrj
!		-------------------------------------------- Calc Coordinates		 
		Coord = 0.D0
		call Calc_Coords_at_a_Pt(Coord,Qc,nDim,nQc1,nQc2,ri,rj)
!		-------------------------------------------- Save
		mm = ms + nPtsj+1-j
		m = m + 1
		SaveC(1,mm) = Coord(1)
		SaveC(2,mm) = Coord(2)
	end do !i
!	==================================================================================== radial at 0 backward
	rj	= 0.D0
	ri	= -delri
	ms	= m
	do i = 1,nPtsi
		ri = ri + delri
!		-------------------------------------------- Calc Coordinates		 
		Coord = 0.D0
		call Calc_Coords_at_a_Pt(Coord,Qc,nDim,nQc1,nQc2,ri,rj)
!		-------------------------------------------- Save
		mm = ms + nPtsi+1-i
		m = m + 1
		SaveC(1,mm) = Coord(1)
		SaveC(2,mm) = Coord(2)
	end do !i
!	==================================================================================== Superpose ACTUAL
	R_Out	= R_IN + DEPTH
	piby2	= DATAN(1.D0)*2.D0
!	==================================================================================== ACTUAL:Outer Radius
	ri	= 0.D0
	rj	= -delrj
	do j = 1,nPtsj
		rj = rj + delrj
!		-------------------------------------------- Calc Coordinates		 
		Coord = 0.D0
!
		Coord(1) = R_OUT*(1.D0 - DCOS(rj*piby2)	)	
		Coord(2) = R_OUT*DSIN(rj*piby2)		
!		-------------------------------------------- Save
		m = m + 1
		SaveC(1,m) = Coord(1)
		SaveC(2,m) = Coord(2)
	end do !j
!	==================================================================================== radial at 90
	rj	= 1.D0
	ri	= -delri
	do i = 1,nPtsi
		ri = ri + delri
!		-------------------------------------------- Calc Coordinates		 
		Coord = 0.D0
!
		Coord(1) = R_OUT		
		Coord(2) = R_OUT - ri*DEPTH		
!		-------------------------------------------- Save
		m = m + 1
		SaveC(1,m) = Coord(1)
		SaveC(2,m) = Coord(2)
	end do !i
!	==================================================================================== Inner Radius backward
	ri	= 1.D0
	rj	= -delrj
	ms	= m
	do j = 1,nPtsj
		rj = rj + delrj
!		-------------------------------------------- Calc Coordinates		 
		Coord = 0.D0
!
		Coord(1) = R_OUT - R_IN*DCOS(rj*piby2)		
		Coord(2) = R_IN*DSIN(rj*piby2)		
!		-------------------------------------------- Save
		mm = ms + nPtsj+1-j
		m = m + 1
		SaveC(1,mm) = Coord(1)
		SaveC(2,mm) = Coord(2)
	end do !i
!	==================================================================================== radial at 0 backward
	rj	= 0.D0
	ri	= -delri
	ms	= m
	do i = 1,nPtsi
		ri = ri + delri
!		-------------------------------------------- Calc Coordinates		 
		Coord = 0.D0
!
		Coord(1) = ri*DEPTH		
		Coord(2) = 0.D0		
!		-------------------------------------------- Save
		mm = ms + nPtsi+1-i
		m = m + 1
		SaveC(1,mm) = Coord(1)
		SaveC(2,mm) = Coord(2)
	end do !i
!	==================================================================================== Add Control Polygon
	do j = 1,nQc2
		m = m+1
		SaveC(1,m) = Qc(1,1,j)
		SaveC(2,m) = Qc(2,1,j)
	end do !j
!
	do i = 1,nQc1
		m = m+1
		SaveC(1,m) = Qc(1,i,nQc2)
		SaveC(2,m) = Qc(2,i,nQc2)
	end do !j
!
	ms = m
	do j = 1,nQc2
		mm = ms + nQc2-j
		m = m + 1
		SaveC(1,mm) = Qc(1,nQc1,j)
		SaveC(2,mm) = Qc(2,nQc1,j)
	end do !j
!
	ms = m
	do i = 1,nQc1
		mm = ms + nQc1-i
		m = m + 1
		SaveC(1,mm) = Qc(1,i,1)
		SaveC(2,mm) = Qc(2,i,1)
	end do !j
!	==================================================================================== Plot Save
	do n = 1,m
		write(iOutG,1020) SaveC(1,n),SaveC(2,n)
   	end do !n	 
!
!	done
!
	return
!
 1010 format(i3,1x,4(3x,e12.5),i5,e12.4,2x,a1)
 1020 format(F15.2,",",F15.8)
 1030 format(F15.2,",",F15.8)
	end
