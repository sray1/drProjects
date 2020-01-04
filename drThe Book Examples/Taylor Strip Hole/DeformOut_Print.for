	Subroutine DeformOut_Print(Qd,nQd,nQd1,nQd2,Qc,nDim,nQc1,nQc2,
     &				nPtsi,nPtsj,ANGLE,DEPTH,R_IN,iOut,iOutS)
	Implicit Real(kind=8) (a-h,o-z)

!
!	Real(kind=8)	uT,uR,xc,yc   
	
	Real(kind=8)	Qc(nDim,nQc1,nQc2),Coord(nDim),Dis(nDim)    
	
	Real(kind=8)	Qd     ,DefSav   
	Dimension		Qd(nQd),DefSav(2,nPtsi)
	character*1		sign
	Data			zero/0.D0/,one/1.D0/,two/2.D0/
!	--------------------------------------------
	radian_Ang = DATAN(1.D0)*ANGLE/45.D0
!		 
	DefSav = 0.D0
	nPtsij = nPtsi*nPtsj
	delri	= 1.D0/(dble(nPtsi-1))
	delrj	= 1.D0/(dble(nPtsj-1))
	ri		= -delri
	rj		= -delrj
!	-----------------------------
	do j = 1,nPtsj
		m		= 0
		rj		= rj + delrj
		cRad	= rj * DEPTH + R_in	 
		do i = 1,nPtsi
			m = m+1
			ri = ri + delri
!			-------------------------------------------- Calc Displacements, uT and uR		 
			Dis = 0.D0
			call Calc_Dis_at_a_Pt(Dis,nDim,Qd,nQd,nQd1,nQd2,
     &								ri,rj,iOut)
!			-------------------------------------------- Save
			DefSav(1,m)	= Dis(1)
			DefSav(2,m)	= Dis(2)
!		--------------------------------------------
   		end do !i
!		====================================================================================
!		----------------------------------------------------- Print
		if(j == 1) then
			write(iOut,1010) cRad,(DefSav(1,mj),mj=1,m)
			write(iOut,1020) (DefSav(2,mj),mj=1,m)
		end if
		ri		= -delri
   	end do !j
!	-------------------------------------------------- 
!
!	done
!
	return
!
 1010 format(/1x,"At Radius = ",f10.3//5x,
     &            "uCircumferential ..."/(8(2x,f10.7)) )
 1020 format(/5x,"uRadial ..."/(8(2x,f10.7)) )
	end
