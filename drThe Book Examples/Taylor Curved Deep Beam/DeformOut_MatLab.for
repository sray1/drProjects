	Subroutine DeformOut_MatLab(Qd,nQd,nQd1,nQd2,Qc,nDim,nQc1,nQc2,
     &			nPtsi,nPtsj,iElem,nElems,ANGLE,iOut,iOutS,iEjSav)
	Implicit Real(kind=8) (a-h,o-z)

!
!	Real(kind=8)	uT,uR,xc,yc   
	
	Real(kind=8)	Qc(nDim,nQc1,nQc2),Coord(nDim),Dis(nDim)    
	
	Real(kind=8)	Qd     ,DefSav   
	Dimension		Qd(nQd),DefSav(2,MAX(nPtsi,nPtsj)+1)
	Real(kind=8)	EndSav   
	Dimension		EndSav(2,nPtsi)
	character*1		sign
	Data			zero/0.D0/,one/1.D0/,two/2.D0/
!	--------------------------------------------
	radian_Ang = DATAN(1.D0)*ANGLE/45.D0
!		 
	DefSav = 0.D0
	delri	= 1.D0/(dble(nPtsi-1))
	delrj	= 1.D0/(dble(nPtsj-1))
!	==================================================================================== Circum direction
	ri		= -delri
	rj		= -delrj
	do j = 1,nPtsj
		rj	= rj + delrj
		ri	= -delri
		do i = 1,nPtsi
			ri = ri + delri
!			-------------------------------------------- Calc Displacements, uT and uR		 
			Dis = 0.D0
			call Calc_Dis_at_a_Pt(Dis,nDim,Qd,nQd,nQd1,nQd2,
     &								ri,rj,iOut)
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
			DefSav(1,i) = xc+uc
			DefSav(2,i) = yc+vc
!			-------------------------------------------- Save Edge rj =0. stored to mcompare Taylor plot
			if(j == 1) then
				if((iElem==1).OR.(iElem.GT.1.AND.i.GT.1) ) then
					kk = i
					if(iElem.GT.1) kk = i-1
					EndSav(1,kk) = (1.D0-ri)*ANGLE + 
     &								ANGLE*(nElems-iElem)
					EndSav(2,kk) = uT
				endif
			endif
!		--------------------------------------------
   		end do !i
!		----------------------------------------------------- Plot Save
		do n = 1,nPtsi
			write(iOutS,1020) DefSav(1,n),DefSav(2,n)
   		end do !n	 
!	-------------
	end do !j
!	==================================================================================== radial direction
	ri		= -delri
	rj		= -delrj
	do i = 1,nPtsi
		ri = ri + delri
		rj	= -delrj
		m	= 1				! save last one here for closing each polygon by MatLab
		do j = 1,nPtsj
			rj = rj + delrj
!			-------------------------------------------- Calc Displacements, uT and uR		 
			Dis = 0.D0
			call Calc_Dis_at_a_Pt(Dis,nDim,Qd,nQd,nQd1,nQd2,
     &								ri,rj,iOut)
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
			DefSav(1,j) = xc+uc
			DefSav(2,j) = yc+vc
!		--------------------------------------------
   		end do !j
!		----------------------------------------------------- Plot Save
		do n = 1,nPtsj
			write(iOutS,1020) DefSav(1,n),DefSav(2,n)
   		end do !n	 
!-------------------------------------------------- 
!	-------------
	end do !i
!====================================================================================
!	----------------------------------------------------- Plot Save Edge
	nPl = nPtsj
	if(iElem.GT.1) nPl = nPl - 1
	do n = 1,nPl
		write(iEjSav,1030) EndSav(1,n),EndSav(2,n)
   	end do !n	 
!
!	done
!
	return
!
 1010 format(i3,1x,4(3x,e12.5),i5,e12.4,2x,a1)
 1020 format(F15.2,",",F15.2)
 1030 format(F15.2,",",F15.8)
	end
