	Subroutine DeformOut_MatLab(Qd,nQd,nQd1,nQd2,Qc,nDim,nQc1,nQc2,
     &						nPtsi,nPtsj,ANGLE,iOut,iOutS)
	Implicit Real(kind=8) (a-h,o-z)

!
!	Real(kind=8)	uT,uR,xc,yc   
	
	Real(kind=8)	Qc(nDim,nQc1,nQc2),Coord(nDim),Dis(nDim)    
	
	Real(kind=8)	Qd     ,DefSav   
	Dimension		Qd(nQd),DefSav(2,nPtsi*(nPtsj+1))
	character*1		sign
	Data			zero/0.D0/,one/1.D0/,two/2.D0/
!	--------------------------------------------
	radian_Ang = DATAN(1.D0)*ANGLE/45.D0
!		 
	DefSav = 0.D0
	nPtsij = nPtsi*(nPtsj+1)
	delri	= 1.D0/(dble(nPtsi-1))
	delrj	= 1.D0/(dble(nPtsj-1))
	ri		= -delri
	rj		= -delrj
!	-----------------------------
	do j = 1,nPtsj
		m = 0
		rj = rj + delrj
		do i = 1,nPtsi
			m = m+1
			ri = ri + delri
!			-------------------------------------------- Calc Displacements, uT and uR		 
			Dis = 0.D0
			call Calc_Dis_at_a_Pt(Dis,nDim,Qd,nQd,nQd1,nQd2,ri,rj)
!			--------------
			uT	= Dis(1)
			uR	= Dis(2)
!			-------------------------------------------- Cartesian Disp: horizontal & vertical
			ang = radian_Ang*ri
			ci	= dcos(ang)
			si	= dsin(ang)
			uc	=  uT*ci + uR*si 
			vc	= -uT*si + uR*ci
!			-------------------------------------------- Calc Coordinates		 
			Coord = 0.D0
			call Calc_Coords_at_a_Pt(Coord,Qc,nDim,nQc1,nQc2,ri,rj)
!
			xc = Coord(1)
			yc = Coord(2)
!			-------------------------------------------- Save
			if(j == 1) then
				DefSav(1,m) = xc+uc
				DefSav(2,m) = yc+vc
			else
				n = nPtsij-m+1
				DefSav(1,n) = xc+uc
				DefSav(2,n) = yc+vc
			endif
!	--------------------------------------------
   		end do !i
!		====================================================================================
!		-------------------------------------------- plot at ri = 1 edge before rj = 1 edge
!														with nPtsi pts
		if( j == 1) then
			ri	= 1.D0
			rk	= -delri
			do i = 1,nPtsi
				m = m+1
				rk = rk + delri
!				-------------------------------------------- Calc Displacements		 
				Dis = 0.D0
				call Calc_Dis_at_a_Pt(Dis,nDim,Qd,nQd,nQd1,nQd2,ri,rk)
!				--------------
				uT	= Dis(1)
				uR	= Dis(2)
!				-------------------------------------------- Cartesian Disp: horizontal & vertical
				ang = radian_Ang*ri
				ci	= dcos(ang)
				si	= dsin(ang)
				uc	=  uT*ci + uR*si 
				vc	= -uT*si + uR*ci
!				-------------------------------------------- Calc Coordinates		 
				Coord = 0.D0
				call Calc_Coords_at_a_Pt(Coord,Qc,nDim,nQc1,nQc2,ri,rk)
!
				xc = Coord(1)
				yc = Coord(2)
!				--------------------------------------------
				DefSav(1,m) = xc+uc
				DefSav(2,m) = yc+vc
   			end do !i
		endif
!		====================================================================================
		ri		= -delri
   	end do !j
!	----------------------------------------------------- Plot Save
	do n = 1,nPtsi*(nPtsj + 1)
		write(iOutS,1020) DefSav(1,n),DefSav(2,n)
   	end do !n	 
!		----------------------------------------------------- starting Pt.. to close plot
	write(iOutS,1020) DefSav(1,1),DefSav(2,1)
!-------------------------------------------------- 
!
!	done
!
	return
!
 1010 format(i3,1x,4(3x,e12.5),i5,e12.4,2x,a1)
 1020 format(F15.2,",",F15.2,",")
 1030 format(i3,e15.5)
	end
