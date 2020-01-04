	Subroutine Direct_ResultsAtDesiredSteps(THETAL,Qd,nQd,
     &				nQc,Rad,Conv,
     &            	iter,nPts,nStep,nPStep,iOut,iOutS)
	Implicit Real(kind=8) (a-h,o-z)
	logical SaveStep
!
	Real(kind=4)	u,w,xLF    
	
	Real(kind=8)	Qd     ,Br    
	Dimension		Qd(nQd),Br(nQc)
	Data			zero/0.D0/,one/1.D0/,two/2.D0/
!-------------------------------------------- need to save?
	piby2	= two*datan(1.D0)
	if(mod(nStep,nPStep).eq.0) Then
		SaveStep = .true.	
		nSav	 = nPts
	else		
		SaveStep = .false.	
		nSav	 = 1
	endif
	SaveStep = .true.	! Temporarily everyStep	
!-------------------------------------------- need to save?
	XLF = zero
	if(nStep.GT.0) Then
		XLF = two*Qd(nQd)
	endif
	if (SaveStep) Then
		write(iOutS,1030) nStep,xLF	! LoadFactor
!		--------------------------------------------		 
		CU		= one/Rad
!---------------------------------------- Temporary Check
		CU		= 0.D0		! Straight Beam
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
		sumu = zero	
		sumw = zero	
		sumt = zero	
!
		do 10 j= 1,nQc
		sumu = sumu + Br(j)*Qd(j) 
		sumw = sumw + Br(j)*Qd(j+  nQc) 
		sumt = sumt + Br(j)*Qd(j+2*nQc) 
   10		continue
		u	= Real(sumu)
		w	= Real(sumw)
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
		write(iOutS,1020) xc + uc,yc - wc
!
!		ri = ri + delri
   50		continue
!
		uEnd = sumu 
		wEnd = sumw 
		tEnd = sumt 
!-------------------------------------------------- Prepare:Strains
	endif
! 
!	done
!
	iPrt = 1
	if(iPrt == 1) Then
		write(iOut,1010) nStep,XLF,uEnd,wEnd,tEnd,iter,Conv
  110		continue
	endif
!
	return
!
 1010 format(i3,1x,4(3x,e12.5),i5,e12.4)
 1020 format(2e15.5)
 1030 format(i3,e15.5)
	end
