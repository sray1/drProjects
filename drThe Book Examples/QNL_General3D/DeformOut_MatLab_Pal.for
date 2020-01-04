	Subroutine DeformOut_MatLab_Pal(XLF,THETAL,Qd,nQd,nQc,nDof,
     &            	Rad,Conv,
     &            	sign,iter,nPts,nStep,nPStep,iOut,iOutS,EndwSav)
	Implicit Real(kind=8) (a-h,o-z)
	logical SaveStep
!
	Real(kind=4)	Dof4(nDof)    
	
	Real(kind=8)	Dof8,      Qd     ,Br    
	Dimension		Dof8(nDof),Qd(nQd),Br(nQc),EndwSav(2,*)
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
!
		
		do 10 l= 1,nDof
		k = (l-1)*nQc
		do 10 j= 1,nQc
		Dof8(l) = Dof8(l) + Br(j)*Qd(k+j) 
   10		continue
		u	= Real(Dof8(1))
		w	= Real(Dof8(2))
!		----------------- Cartesian: horizontal & vertical
		ang = piby2 - THETAL*(one -ri)
		ci	= dcos(ang)
		si	= dsin(ang)
		uc	=  w*ci + u*si 
		wc	= -u*ci + w*si
!
		the = THETAL*ri
		cc	= dcos(the)
		ss	= dsin(the)
		xc	=  Rad*(one-cc)*ci + Rad*ss*si
		yc	=  Rad*(one-cc)*si + Rad*ss*ci
!--------------------------------------------
		write(iOutS,1020) xc + uc,yc - wc
!--------------------------------------------
!
!		ri = ri + delri
   50		continue
!
		uEnd = Dof8(1) 
		wEnd = Dof8(2) 
		tEnd = Dof8(6) 
!		----------------------------------------- save for Plot
		EndwSav(1,nStep+1) = wEnd
		EndwSav(2,nStep+1) = two*XLF
	endif
!-------------------------------------------------- 
!
!	done
!
	iPrt = 1
	if(iPrt == 1) Then
		write(iOut,1010) nStep,two*XLF,uEnd,wEnd,tEnd,iter,Conv,
     &			sign
  110		continue
	endif
!
	return
!
 1010 format(i3,1x,4(3x,e12.5),i5,e12.4,2x,a1)
 1020 format(F15.2,",",F15.2,",")
 1030 format(i3,e15.5)
	end
