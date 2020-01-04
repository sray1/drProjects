	Subroutine Calc_DispAtDOFs(Qd,nQd,nDim,nQd1,nQd2,D,
     &								iOut,iOutS)
	Implicit Real(kind=8) (a-h,o-z)

!
	Real(kind=8)	Qd(nQd),D(nQd),Dis(nDim)
	Data			zero/0.D0/,one/1.D0/,two/2.D0/
!	--------------------------------------------
	U = 0.D0
	V = 0.D0
	nQd12	= nQd1*nQd2
	delri	= 1.D0/(dble(nQd1-1))
	delrj	= 1.D0/(dble(nQd2-1))
	ri		= -delri
	rj		= -delrj
!	-----------------------------
	do i = 1,nQd1
		ri		= ri + delri
		do j = 1,nQd2
			k = j+(i-1)*nQd2
			rj = rj + delrj
!			-------------------------------------------- Calc Displacements, uT and uR		 
			Dis = 0.D0
			call Calc_Dis_at_a_Pt(Dis,nDim,Qd,nQd,nQd1,nQd2,
     &								ri,rj,iOut)
!			-------------------------------------------- Save
			D(k)		= Dis(1)
			D(k+nQd12)	= Dis(2)
!		--------------------------------------------
   		end do !j
		rj		= -delrj
   	end do !i
!	==================================================================================== Print
	write(iOut,1010) (D(mj),mj=1,nQd12)
	write(iOut,1020) (D(mj+nQd12),mj=1,nQd12)
!	-------------------------------------------------- 
!
!	done
!
	return
!
 1010 format(/5x,"Nodal DIsplacements..."
     &       /5x,"U ..."/(8(2x,f10.7)) )
 1020 format(/5x,"V ..."/(8(2x,f10.7)) )
	end
