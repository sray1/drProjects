	Subroutine DeformOut_MatLab_Bat(XLF,THETAL,Qd,nQd,nQc,nDof,
     &            	Rad,Conv,sign,iter,nPts,nStep,nPStep,iOut,iOutS,
     &				EndwSav,Qc,Nel)
	Implicit Real(kind=8) (a-h,o-z)
	logical SaveStep
!
	Real(kind=8)	Qc       ,Axes     ,geom       
	Dimension		Qc(3,nQc),Axes(3,3),geom(3)
	Real(kind=8)	Dof8,      Qd     ,Br    
	Dimension		Dof8(nDof),Qd(nQd),Br(nQc),EndwSav(4,*)
	character*1		sign
	character*20    Problem
	Data			zero/0.D0/,one/1.D0/,two/2.D0/
!------------------------------
	piby2	= two*datan(1.D0)
!-------------------------------------------- need to save?
	if(mod(nStep,nPStep).eq.0) Then
		SaveStep = .true.	
		nSav	 = nPts
	else		
		SaveStep = .false.	
		nSav	 = 1
	endif
	SaveStep = .true.	! Temporarily everyStep	
!-------------------------------------------- need to save?
	if (SaveStep) Then
!		write(iOutS,1030) nStep,xLF	! LoadFactor
!		--------------------------------------------		 
		CU		= one/Rad
!---------------------------------------- Temporary Check
!		CU		= 0.D0		! Straight Beam
!
		nQ0 = 0
		nQ1 = nQ0+nQc
		nQ2 = nQ1+nQc
		nQ3 = nQ2+nQc
		nQ4 = nQ3+nQc
		nQ5 = nQ4+nQc
!
		delri	= 1.D0/(dble(nPts-1))
		ri		= -delri
!		-----------------------------
		do 50 i = 1,nPts
		ri = ri + delri
!		-------------------------------------------- Basis Functions		 
		call Bernstein(Br,nQc,ri,iOut)
!		--------------
		Dof8 = zero	
		geom = zero	
!
		do 20 l= 1,nDof
		k = (l-1)*nQc
		do 20 j= 1,nQc
		Dof8(l) = Dof8(l) + Br(j)*Qd(k+j) 
   20		continue
		u	= Real(Dof8(1))
		w	= Real(Dof8(2))
		v	= Real(Dof8(3))
!--------------------------------------------------- Curvilinear-->Cartesian
	call QQ_TMB_CuLn(Qc,nQc,nQc,ri,Det,Curvature,Torsion,Axes,
     &							dxbardr,Nel,Iout,0)
!
	sumTX = Axes(1,1)*u+Axes(2,1)*w+Axes(3,1)*v
	sumTY = Axes(1,2)*u+Axes(2,2)*w+Axes(3,2)*v
	sumTZ = Axes(1,3)*u+Axes(2,3)*w+Axes(3,3)*v
!
!	sumRX = Axes(1,1)*sum1+Axes(2,1)*sum2+Axes(3,1)*sum3
!	sumRY = Axes(1,2)*sum1+Axes(2,2)*sum2+Axes(3,2)*sum3
!	sumRZ = Axes(1,3)*sum1+Axes(2,3)*sum2+Axes(3,3)*sum3
!
!
		do 40 l= 1,3
		do 40 j= 1,nQc
		geom(l) = geom(l) + Br(j)*Qc(l,j) 
   40		continue

		u = geom(1) + sumTX 
		v = geom(2) + sumTY 
		w = geom(3) + sumTZ
!--------------------------------------------
		write(iOutS,1020) u,v,w
!--------------------------------------------
!--------------------------------------------------- Curvilinear-->Cartesian:END
!		ri = ri + delri
   50		continue
!
		uEnd = u 
		vEnd = v
		wEnd = w
!		----------------------------------------- save for Plot
		EndwSav(1,nStep+1) = XLF
		EndwSav(2,nStep+1) = uEnd
		EndwSav(3,nStep+1) = vEnd
		EndwSav(4,nStep+1) = wEnd
		EndwSav(2,nStep+1) = sumTX
		EndwSav(3,nStep+1) = sumTY
		EndwSav(4,nStep+1) = sumTZ
!-------------------------------------------------- 
	endif
! 
!	done
!
!
	iPrt = 1
	if(iPrt == 1) Then
		write(iOut,1010) nStep,XLF,uEnd,vEnd,wEnd,iter,Conv,sign
	endif
!
	return
!
 1010 format(i3,1x,4(3x,e12.5),i5,e12.4,2x,a1)
 1020 format(F15.2,",",F15.2,",",F15.2)
 1030 format(i3,e15.5)
	end
