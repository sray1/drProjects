	Subroutine DeformOut_PLCar(Qd,nQd,nQd1,nQd2,Qc,nDim,nQc1,nQc2,
     &				nPtsi,nPtsj,ANGLE,DEPTH,R_IN,iOut,iOutS)
	Implicit Real(kind=8) (a-h,o-z)

!
!	Real(kind=8)	uT,uR,xc,yc   
	
	Real(kind=8)	Qc(nDim,nQc1,nQc2),Coord(nDim),Dis(nDim)    
	
	Real(kind=8)	Qd     ,DefSav         ,EndSav   
	Dimension		Qd(nQd),DefSav(2,nPtsj),EndSav(2,nPtsj)
	character*1		sign
	Data			zero/0.D0/,one/1.D0/,two/2.D0/
!	--------------------------------------------
	RAD_OUT = R_IN + DEPTH
	piby2	= DATAN(1.D0)*2.D0
	radian_Ang = piby2
!		 
	DefSav = 0.D0
	nPtsij = nPtsi*nPtsj
	delri	= 1.D0/(dble(nPtsi-1))
	delrj	= 1.D0/(dble(nPtsj-1))
	ri		= -delri
	rj		= -delrj
!	-----------------------------
	do i = 1,nPtsi
		m		= 0
		ri		= ri + delri
!		*********************************
		cRad	= R_IN + DEPTH*(one - ri)
!		*********************************
		do j = 1,nPtsj
			m = m+1
			rj = rj + delrj
!			-------------------------------------------- Calc Displacements, uT and uR	
			if(j==nPtsj) then
				abc = 1
			endif	 
			Dis = 0.D0
			call Calc_Dis_at_a_Pt(Dis,nDim,Qd,nQd,nQd1,nQd2,
     &								ri,rj,iOut)
!			--------------
			uc	= Dis(1)
			vc	= Dis(2)
!		******************************************************

		call Calc_Coords_at_a_Pt(Coord,Qc,nDim,nQc1,nQc2,ri,rj)
	
		if(dabs(Rad_Out - Coord(1)).lt..00000000000001D0) then
			AnglR	= piby2
		else
			AnglR	= DATAN(Coord(2)/(RAD_OUT - Coord(1))  )
		endif
		cc			= DCOS(AnglR)
		ss			= DSIN(AnglR)
!		******************************************************
!			-------------------------------------------- Cartesian Disp: horizontal & vertical
			ang = radian_Ang*rj
			ci	= dcos(ang)
			si	= dsin(ang)
!
	ut			= uc*ss + vc*cc
	ur			= uc*cc - vc*ss
!
!			-------------------------------------------- Save for i = 2 for Plot
			if(i == 2) then
				EndSav(1,m) = rj*ANGLE
				EndSav(2,m) = uT
			endif
!		--------------------------------------------
   		end do !j
		rj		= -delrj
   	end do !i
!	====================================================================================
!	----------------------------------------------------- Plot Save
	do n = 1,nPtsj
		write(iOutS,1030) EndSav(1,n),EndSav(2,n)
   	end do !n	 
!	-------------
!
!	done
!
	return
!
 1010 format(/1x,"At Radius = ",f10.3//5x,
     &            "uCircumferential ..."/(8(2x,f10.7)) )
 1020 format(/5x,"uRadial ..."/(8(2x,f10.7)) )
 1030 format(F15.2,",",F15.8)
	end
