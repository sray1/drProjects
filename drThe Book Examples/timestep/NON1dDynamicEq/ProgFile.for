	Program TimeStep_MDDynamic
!------------------------- Modules
	USE linear_operators
	USE DFLIB
	USE DFPORT
!	USE SCIGRAPH
!------------------------------------------------------------------- Files
	include 'files.h'
	include 'solveDYN.h'
	include 'SizeVar.h'
	include 'Blank.h'
!
	Real(kind=8)	ddel
	
	integer			nStep,nDof
	integer			nSzInt,nSzDbl
	integer			n1,n2,n3,n4,n5,n6,nend
!	
!	--------------------------------------------------------------------------- Prelim
	call Set_Files()
!------------------------------------------------------------------- Today's Date/Time		
	call Set_TimeDate(iOut)
!	----------------------------------------------- Newmark
	beta	= 0.25D0			! Average Acceleration
	gama	= 0.5D0 
!	-----------
	nSzInt			= 4 !bytes
	nSzDbl			= 8 !bytes
!	----------------------------------------------- Dim & Data :ChopraEx:15.1 p:614
	nStep	= 21
	nDof	= 5
!	-----------
	n1		= 1							!stif
	n2		= n1 + nDof*nDof*nSzDbl		!damp
	n3		= n2 + nDof*nDof*nSzDbl		!mass
	n4		= n3 + nDof*nDof*nSzDbl		!load
	n5		= n4 + nDof*nStep*nSzDbl	!d0
	n6		= n5 + nDof*nSzDbl			!v0
	nend	= n6 + nDof*nSzDbl			!end
!	-----------
	call getData5(A(n1),A(n2),A(n3),A(n4),A(n5),A(n6), 
     &				nDof,nStep,ddel,iOut) 
!	-------------------
	call MidPtRule(A(n1),A(n2),A(n3),A(n4),A(n5),A(n6),nDof,
     &                     nStep,ddel,iOut,2)
!	-------------------
	call AvgRule(A(n1),A(n2),A(n3),A(n4),A(n5),A(n6),nDof,
     &                     nStep,ddel,iOut,2)
!	-------------------
	call ChopraAvgRule(A(n1),A(n2),A(n3),A(n4),A(n5),A(n6),nDof,
     &                     nStep,ddel,iOut,2)
!	-------------------------------------------- CubicC2 End
  999 Stop	'Program: TimeStep_MDDynamic Ran OK'

	end 
!	 
	Subroutine MidPtRule(Stif,Damp,Mass,Load,d0,v0,nDof,
     &                     nStep,deltaT,iOut,nProb)
 			
!
!	No Need for additional matrix. Momentum Balance @ Mid. Pt. of Step 
! 			
	Real*8	Stif(nDof,nDof),Damp(nDof,nDof),Mass(nDof,nDof),time
	Real*8	eStif(nDof,nDof),eLoad(nDof),Load(nDof,nStep),deltaT
	Real*8	cLoad(nDof),dis(nDof,nStep),a0,a1,a2,a3,a4,sum,delu(nDof)

	Real(kind=8)	d(nDof),ddot(nDof),d2dot(nDof),temv
	
	integer			nStep,iOut,nProb
!
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!========================================================================
!	Method		Newmark MidPt. Rule : MultiDegreeOfFreedom
!------------------------------------------------------------------- Heading
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
	write(iOut,*)
     &	'             MD Dynamic Equation Time Stepping           ',
     &	'               (Average Accl: Mid. Pt. Rule)             ',
     &    '                         by',   
     &    '                         ',   
     &    '                    DEBABRATA RAY',   
     &    '                         ' 
	write(iOut,*)
     &'    No additional matrix. Momentum Balance @ Mid. Pt. of Step'
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
!-------------------------------------------------------------------------------- 		
	if(nProb == 1) then
		write(iOut,1000) deltaT
	else
		write(iOut,1001) deltaT
	endif 
!
	pi		= 4.D0*atan(1.)
	time	= 0.D0
!	-------------------------------- initial calc
	d		= d0
	ddot	= v0
!
	eStif	= Mass
	call Invert_A(eStif,nDof,nDof,iOut)
!
	do i=1,nDof
		cLoad(i)= Load(i,1)
	end do
!
	do ii = 1,ndof
		sum = 0.D0
		do jj = 1,ndof
			sum	= sum- 
     &			Damp(ii,jj)*ddot(jj)-Stif(ii,jj)*d(jj)
		end do
			eLoad(ii) = sum+Load(ii,1) 
	end do
	d2dot = MATMUL(eStif,eLoad) 
!
	a1      = 1.D0/deltaT
	a0      = 2.D0*a1/deltaT
	a2		= 2.D0*a1
	a3		= 4.D0*a1
	a4		= 2.D0*a0
!	-----------------------------------
	do ii = 1,ndof
		do jj = 1,ndof
		eStif(ii,jj) =
     &		 a0*Mass(ii,jj)+a1*Damp(ii,jj)+.5D0*Stif(ii,jj)
		end do
	end do
	call Invert_A(eStif,nDof,nDof,iOut)
!	--------------------------------------------------------------------------- Loop
	do is = 1,nStep-1
!
		do ii = 1,ndof
			sum = 0.D0
			do jj = 1,ndof
				sum	= sum+
     &				a2*Mass(ii,jj)*ddot(jj)-Stif(ii,jj)*d(jj)
			end do
			eLoad(ii) = sum+.5D0*(Load(ii,is+1)+Load(ii,is)) 
		end do
!
		delu	= MATMUL(eStif,eLoad)
		do ii = 1,ndof
			temv		= ddot(ii)
			d(ii)		= d(ii) + delu(ii)
			ddot(ii)	= a2*delu(ii) - temv 
			d2dot(ii)	= a4*delu(ii) - a3*temv - d2dot(ii) 
		end do  
!	--------------------------- save for print
		do ii = 1,ndof
			dis(ii,is) = d(ii)
		end do  
!	---------------------------
	end do
!	---------------------------
	if(nProb == 1) then
		write(iOut, 1010) (i, i = 1,nStep-1) 
		write(iOut, 1020) (i,(dis(i,j),j=1,nStep-1),i=1,nDof)	! Bathe
	else
		write(iOut, 1015) (i, i = 1,nDof) 
		write(iOut, 1030) (j,(dis(i,j),i=1,nDof),j=1,nStep-1)	! Chopra
	endif 
!	----------
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
!
  999 return 

 1000 format(//5x,"Bathe: Example 8.1:pp 314",//
     &	10x,"time-step = ", f10.3//)
 1001 format(//5x,"Chopra: Example 15.1:pp 614",//
     &	10x,"time-step = ", f10.3//)
 1010 format( 5x, 'nDelT' ,5x, 12(I4,5x) )
 1015 format( 5x, 'nDOF ' ,5x, 5(I4,5x) )
 1020 format((5x, 'dis(',I1,')', 12(f8.4,1x)))
 1030 format((5x, I8, 5(f8.4,1x)))

	end
!	 
!	 
	Subroutine AvgRule(Stif,Damp,Mass,Load,d0,v0,nDof,
     &                     nStep,deltaT,iOut,nProb)
 			
!
!	No Need for additional matrix. Difference of Momentum Balance
! 			
	Real*8	Stif(nDof,nDof),Damp(nDof,nDof),Mass(nDof,nDof),time
	Real*8	eStif(nDof,nDof),eLoad(nDof),Load(nDof,nStep),deltaT
	Real*8	cLoad(nDof),dis(nDof,nStep),a0,a1,a2,a3,a4,sum

	Real(kind=8)	u(nDof),v(nDof),a(nDof),temv,d0,v0,tema
	Real(kind=8)	du(nDof),dv(nDof),da(nDof)
	
	integer			nStep,iOut,nProb
!
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!========================================================================
!	Method		Newmark Avg. Rule : MultiDegreeOfFreedom
!------------------------------------------------------------------- Heading
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
	write(iOut,*)
     &	'             MD Dynamic Equation Time Stepping           ',
     &	'              (Average Accl: Difference Rule)            ',
     &    '                         by',   
     &    '                         ',   
     &    '                    DEBABRATA RAY',   
     &    '                         '   
	write(iOut,*)
     &'    No additional matrix. Difference of Momentum Balance      '
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
!-------------------------------------------------------------------------------- 		
	if(nProb == 1) then
		write(iOut,1000) deltaT
	else
		write(iOut,1001) deltaT
	endif 
!	---------------------------
	if(nProb == 2) then
		write(iOut, 1015) (i, i = 1,nDof) 
	endif 
!	-----------------
	time	= 0.D0
!	-------------------------------- initial calc
	u		= d0
	v		= v0
	u		= 0.D0
	v		= 0.D0
!
	eStif	= Mass
!	call Invert_A(eStif,nDof,nDof,iOut)
!
	do i=1,nDof
		cLoad(i)= Load(i,1)
	end do
!
	do ii = 1,ndof
		sum = 0.D0
		do jj = 1,ndof
			sum	= sum- 
     &			Damp(ii,jj)*v(jj)-Stif(ii,jj)*u(jj)
		end do
			eLoad(ii) = sum+Load(ii,1) 
	end do
!	a = MATMUL(eStif,eLoad) 
!
	call Solve_AxEqB(eStif,eLoad,a,nDof,nDof,iOut)
!
!
	a1      = 1.D0/deltaT
	a0      = 2.D0*a1/deltaT
	a2		= 2.D0*a1
	a3		= 4.D0*a1
	a4		= 2.D0*a0
!	----------------------------------- Effective Stiffness
	eStif	= 0.D0
	do ii = 1,ndof
		do jj = 1,ndof
		eStif(ii,jj) =
     &		 a4*Mass(ii,jj)+a2*Damp(ii,jj)+Stif(ii,jj)
		end do
	end do
!	call Invert_A(eStif,nDof,nDof,iOut)
!	--------------------------------------------------------------------------- Loop
	do is = 1,nStep-1
!
		do ii = 1,ndof
			sum = 0.D0
			do jj = 1,ndof
				sum	= sum+
     &				Mass(ii,jj)*(a3*v(jj)+2.D0*a(jj))
     &               +Damp(ii,jj)*(2.D0*v(jj))
			end do
			eLoad(ii) = sum+(Load(ii,is+1) - Load(ii,is))
		end do
!
!		du	= MATMUL(eStif,eLoad)
!
		call Solve_AxEqB(eStif,eLoad,du,nDof,nDof,iOut)
!
		do ii = 1,ndof
			dv(ii)		= a2*du(ii) - 2.D0*v(ii) 
			da(ii)		= a4*du(ii) - a3*v(ii) - 2.D0*a(ii) 
		end do  
!
		do ii = 1,ndof
			u(ii)	= u(ii)	+ du(ii)
			v(ii)	= v(ii)	+ dv(ii) 
			a(ii)	= a(ii)	+ da(ii)
		end do  
!
!============================================================ alternate
!		do ii = 1,ndof
!		sum = 0.D0
!			do jj = 1,ndof
!				sum	= sum- 
!     &			Damp(ii,jj)*v(jj)-Stif(ii,jj)*u(jj)
!			end do
!			eLoad(ii) = sum+Load(ii,is+1) 
!		end do
!
!		call Solve_AxEqB(Mass,eLoad,a,nDof,nDof,iOut)
!============================================================ alternate END
!
!
	time	= time + deltaT
!	---------------------------
	if(nProb == 2) then
		write(iOut, 1030) time,(u(i),i=1,nDof)	! Chopra
	endif 
!	-----------------
!	--------------------------- save for print
		do ii = 1,ndof
			dis(ii,is) = u(ii)
		end do  
!	--------------------------------------------------------------------------- Loop END
	end do
!	---------------------------
	if(nProb == 1) then
		write(iOut, 1010) (i, i = 1,nStep-1) 
		write(iOut, 1020) (i,(dis(i,j),j=1,nStep-1),i=1,nDof)	! Bathe
	endif 
!	-----------------
!	----------
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
!
  999 return 

 1000 format(//5x,"Bathe: Example 8.1:pp 314",//
     &	10x,"time-step = ", f10.3//)
 1001 format(//5x,"Chopra: Example 15.2:pp 620",//
     &	10x,"time-step = ", f10.3//)
 1010 format( 5x, 'nDelT' ,5x, 12(I4,5x) )
 1015 format( 3x, 'time/nDOF' ,5x, 5(I4,5x) )
 1020 format((5x, 'dis(',I1,')', 12(f8.4,1x)))
 1030 format((5x, f6.1,2x, 5(f8.4,1x)))

	end
!	 
	Subroutine getData5(Stif,Damp,Mass,Load,d0,v0,
     &					nDof,nStep,deltaT,iOut)
 			
!	chopra Ex15.1 p 614
!
	Real*8	Stif(nDof,nDof),Damp(nDof,nDof),Mass(nDof,nDof)
	Real*8	Load(nDof,nStep),d0(nDof),v0(nDof),deltaT
	Real*8	EI,h,xm,xp,xs

	integer	iPrt
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!
	deltaT		= 0.1D0
	write(iOut,1000) deltaT
!
!
	EI			= 5.469E10
	h			= 120.D0
	xm			= 208.6D0
	xp			= 1000.D0
!	============================================================== initial cond.
	d0			= 0.D0
	v0			= 0.D0
!=================================================================== Stiffness
	xs			= EI/h/h/h
	stif		= 0.D0
!
	stif(1,1)	= 18.83D0	
	stif(1,2)	= -11.90D0	
	stif(2,1)	= -11.90D0	
	stif(1,3)	= 4.773D0	
	stif(3,1)	= 4.773D0	
	stif(1,4)	= -1.193D0	
	stif(4,1)	= -1.193D0	
	stif(1,5)	= 0.1989D0
	stif(5,1)	= 0.1989D0
!	
	stif(2,2)	= 14.65D0	
	stif(2,3)	= -10.71D0	
	stif(3,2)	= -10.71D0	
	stif(2,4)	= 4.177D0	
	stif(4,2)	= 4.177D0	
	stif(2,5)	= -0.6961D0	
	stif(5,2)	= -0.6961D0	
!	
	stif(3,3)	= 14.06D0	
	stif(3,4)	= -9.514D0	
	stif(4,3)	= -9.514D0	
	stif(3,5)	= 2.586D0	
	stif(5,3)	= 2.586D0	
!	
	stif(4,4)	= 9.878D0	
	stif(4,5)	= -3.646D0
	stif(5,4)	= -3.646D0
!	
	stif(5,5)	= 1.608D0
!=================================================================== Damp
	dm			= 0.D0
	damp		= 0.D0
!=================================================================== mass
	mass		= 0.D0
!
	mass(1,1)	= 1.D0
	mass(2,2)	= 1.D0
	mass(3,3)	= 1.D0
	mass(4,4)	= 1.D0
	mass(5,5)	= .5D0
!=================================================================== load
	load		= 0.D0
!
	do is = 2,nStep
		load(5,is)	= 1.D0
	end do
!=================================================================== print
	iPrt = 1
	if(iPrt == 1) then 
		write(iOut, 1000) nDof
		write(iOut, 1010) ((stif(i,j),j=1,ndof),i=1,ndof)
		write(iOut, 1020) ((damp(i,j),j=1,ndof),i=1,ndof)
		write(iOut, 1030) ((mass(i,j),j=1,ndof),i=1,ndof)
		write(iOut, 1040) (j,(load(i,j),i=1,ndof),j=1,nStep)
	endif
!	-------------------------------------------------------------- with multipliers
	stif		= xs*stif	
	mass		= xm*mass	
!
	do is = 1,nStep
		load(5,is)	= xp*load(5,is)
	end do
!=================================================================== print again
	iPrt = 1
	if(iPrt == 1) then 
		write(iOut, 1050) 
		write(iOut, 1060) EI,h,xs,xm,xp 
		write(iOut, 1070) ((stif(i,j),j=1,ndof),i=1,ndof)
		write(iOut, 1020) ((damp(i,j),j=1,ndof),i=1,ndof)
		write(iOut, 1030) ((mass(i,j),j=1,ndof),i=1,ndof)
		write(iOut, 1040) (j,(load(i,j),i=1,ndof),j=1,nStep)
	endif
!
!
  999 return 

 1000 format(//5x,"Chopra: Example 15.1:pp 614 DATA",//
     &	10x,"time-step = ", f10.3//)
 1010 format(//" Stiffness matrix.........."//5(2x,f10.4) )
 1020 format(//" Damping matrix.........."//5(2x,f10.4) )
 1030 format(//" Mass matrix.........."//5(2x,f10.4) )
 1040 format(//" Load Vectors.........."//
     &        (5x, 'Step(',I2,')', 5(f10.4,3x)) )
 1050 format(//5x,"Final Matrices............."//)
 1060 format(//
     &" EI.......................... = ",2x,g10.4/
     &" h........................... = ",2x,f10.4/
     &" Stiffness Mult(EI/h**3)..... = ",2x,f10.4/
     &" Mass Mult................... = ",2x,f10.4/
     &" Load Mult................... = ",2x,f10.4 )
 1070 format(//" Stiffness matrix.........."//5(2x,f16.4) )
!	-----
	end
!	 
	Subroutine getData2(Stif,Damp,Mass,Load,d0,v0,
     &					nDof,nStep,deltaT,iOut)
 			
!	Bathe Ex8.1 p 314
!
	Real*8	Stif(nDof,nDof),Damp(nDof,nDof),Mass(nDof,nDof)
	Real*8	Load(nDof,nStep),d0(nDof),v0(nDof),deltaT
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!
	deltaT		=.28D0
!	============================================================== initial cond.
	d0			= 0.D0
	v0			= 0.D0
!=================================================================== Stiffness
	stif		= 0.D0
!
	stif(1,1)	= 6.D0	
	stif(1,2)	= -2.D0	
	stif(2,1)	= -2.D0	
	stif(2,2)	= 4.D0	
!=================================================================== Damp
	damp		= 0.D0
!=================================================================== mass
	mass		= 0.D0
!
	mass(1,1)	= 2.D0
	mass(2,2)	= 1.D0
!=================================================================== load
	load		= 0.D0
!
	do is = 1,nStep
		load(2,is)	= 10.D0
	end do
!=================================================================== print
	write(iOut, 1000) nDof
	write(iOut, 1010) ((stif(i,j),j=1,ndof),i=1,ndof)
	write(iOut, 1020) ((damp(i,j),j=1,ndof),i=1,ndof)
	write(iOut, 1030) ((mass(i,j),j=1,ndof),i=1,ndof)
	write(iOut, 1040) ((load(i,j),j=1,nStep),i=1,ndof)
!
!
  999 return 

 1000 format(//5x,"Bathe: Example 8.1:pp 314 DATA",//2x,
     &  "nDof = ",i5//)
 1010 format(//" Stiffness matrix.........."//2(2x,f10.4) )
 1020 format(//" Damping matrix.........."//2(2x,f10.4) )
 1030 format(//" Mass matrix.........."//2(2x,f10.4) )
 1040 format(//" Load Vectors.........."//13(2x,f5.2) )
!	-----
	end
!	 
	Subroutine ChopraAvgRule(Stif,Damp,Mass,Load,d0,v0,nDof,
     &                     nStep,deltaT,iOut,nProb)
!
!	Needs additional matrix aa & bb
! 			
	Real*8	aa(nDof,nDof),bb(nDof,nDof)
!
	Real*8	Stif(nDof,nDof),Damp(nDof,nDof),Mass(nDof,nDof),time
	Real*8	eStif(nDof,nDof),eLoad(nDof),Load(nDof,nStep),deltaT
	Real*8	dLoad,dis(nDof,nStep),a0,a1,a2,a3,a4,sum

	Real(kind=8)	u(nDof),v(nDof),a(nDof),temv,d0,v0,tema
	Real(kind=8)	du(nDof),dv(nDof),da(nDof)
	
	integer			nStep,iOut,nProb
!
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!========================================================================
!	Method		Newmark Avg. Rule : MultiDegreeOfFreedom
!------------------------------------------------------------------- Heading
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
	write(iOut,*)
     &	'             MD Dynamic Equation Time Stepping           ',
     &	'                (Chopra Average Accl Rule)               ',
     &    '                         by',   
     &    '                         ',   
     &    '                    DEBABRATA RAY',   
     &    '                         '   
	write(iOut,*)
     &'Needs addl. matrices:aa & bb.Difference of Momentum Balance  '
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
!-------------------------------------------------------------------------------- 		
	if(nProb == 1) then
		write(iOut,1000) deltaT
	else
		write(iOut,1001) deltaT
	endif 
!	---------------------------
	if(nProb == 2) then
		write(iOut, 1015) (i, i = 1,nDof) 
	endif 
!	-----------------
	time	= 0.D0
!	-------------------------------- initial calc
!	u		= d0
!	v		= v0
	u		= 0.D0
	v		= 0.D0
!
	eStif	= Mass
!	call Invert_A(eStif,nDof,nDof,iOut)
!
!
	do ii = 1,ndof
		sum = 0.D0
		do jj = 1,ndof
			sum	= sum- 
     &			Damp(ii,jj)*v(jj)-Stif(ii,jj)*u(jj)
		end do
			eLoad(ii) = sum+Load(ii,1) 
	end do
!	a = MATMUL(eStif,eLoad) 
!
	call Solve_AxEqB(eStif,eLoad,a,nDof,nDof,iOut)
!
	a2		= 2.D0/deltaT
	a3		= 4.D0/deltaT
	a4		= 4.D0/deltaT/deltaT
!
	aa		= 0.D0
	bb		= 0.D0
	do ii = 1,ndof
		do jj = 1,ndof
			aa(ii,jj) = a3*Mass(ii,jj)+2.D0*Damp(ii,jj)
			bb(ii,jj) = 2.D0*Mass(ii,jj)
		end do
	end do
!	----------------------------------- Effective Stiffness
	eStif	= 0.D0
	do ii = 1,ndof
		do jj = 1,ndof
			eStif(ii,jj) =
     &			a4*Mass(ii,jj)+a2*Damp(ii,jj)+Stif(ii,jj)
		end do
	end do
!	call Invert_A(eStif,nDof,nDof,iOut)
!	--------------------------------------------------------------------------- Loop
	do is = 1,nStep-1
!
		do ii = 1,ndof
			sum = 0.D0
			do jj = 1,ndof
				sum	= sum+
     &				aa(ii,jj)*v(jj)+bb(ii,jj)*a(jj)
			end do
			dLoad		= Load(ii,is+1) - Load(ii,is)
			eLoad(ii)	= sum+dLoad
		end do
!
!		du	= MATMUL(eStif,eLoad)
!
		call Solve_AxEqB(eStif,eLoad,du,nDof,nDof,iOut)
!
		do ii = 1,ndof
			dv(ii)		= a2*du(ii) - 2.D0*v(ii) 
			da(ii)		= a4*du(ii) - a3*v(ii) - 2.D0*a(ii) 
		end do  
!
		do ii = 1,ndof
			u(ii)	= u(ii)	+ du(ii)
			v(ii)	= v(ii)	+ dv(ii) 
			a(ii)	= a(ii)	+ da(ii)
		end do  
!
!============================================================ alternate
!		do ii = 1,ndof
!		sum = 0.D0
!			do jj = 1,ndof
!				sum	= sum- 
!     &			Damp(ii,jj)*v(jj)-Stif(ii,jj)*u(jj)
!			end do
!			eLoad(ii) = sum+Load(ii,is+1) 
!		end do
!
!		call Solve_AxEqB(Mass,eLoad,a,nDof,nDof,iOut)
!============================================================ alternate END
!
!
	time	= time + deltaT
!	---------------------------
	if(nProb == 2) then
		write(iOut, 1030) time,(u(i),i=1,nDof)	! Chopra
	endif 
!	-----------------
!	--------------------------- save for print for Bathe
		do ii = 1,ndof
			dis(ii,is) = u(ii)
		end do  
!	--------------------------------------------------------------------------- Loop END
	end do
!	---------------------------
	if(nProb == 1) then
		write(iOut, 1010) (i, i = 1,nStep-1) 
		write(iOut, 1020) (i,(dis(i,j),j=1,nStep-1),i=1,nDof)	! Bathe
	endif 
!	-----------------
!	----------
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
!
  999 return 

 1000 format(//5x,"Bathe: Example 8.1:pp 314",//
     &	10x,"time-step = ", f10.3//)
 1001 format(//5x,"Chopra: Example 15.2:pp 620",//
     &	10x,"time-step = ", f10.3//)
 1010 format( 5x, 'nDelT' ,5x, 12(I4,5x) )
 1015 format( 3x, 'time/nDOF' ,5x, 5(I4,5x) )
 1020 format((5x, 'dis(',I1,')', 12(f8.4,1x)))
 1030 format((5x, f6.1,2x, 5(f8.4,1x)))

	end
!	 
