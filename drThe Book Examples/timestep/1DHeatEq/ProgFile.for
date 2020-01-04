	Program TimeStep_1DHeat
!------------------------- Modules
	USE linear_operators
	USE DFLIB
	USE DFPORT
!	USE SCIGRAPH
!------------------------------------------------------------------- Files
	include 'files.h'
!	--------------------------------------------------------------------------- Prelim
	call Set_Files()
!------------------------------------------------------------------- Today's Date/Time		
	call Set_TimeDate(iOut)
!	-------------------------------------------- Quadratic
	call Quadratic(iOut)
!	-------------------------------------------- Quadratic End
!	-------------------------------------------- Cubic
	call Cubic(iOut)
!	-------------------------------------------- Cubic_ALTERNATE
	call Cubic_ALT(iOut)
!	-------------------------------------------- Cuic End
  999 Stop	'Program: TimeStep_1DHeat Ran OK'

	end 
!	 
	Subroutine Quadratic(iOut)
 			
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!========================================================================
!	Method		Quadratic B-Spline in Bezier Form
!--------------------------------------------------------------------------------
!               o	
!	equation: d(t) + d(t) = 0 with initial condition d(0)=1, te[0,10[
!	
!	solution: d(t) = exp(-t)
!-------------------------------------------------------------------------------- 		
!	Time stepping algorithm: C1 continuity, Quadratic B-spline Fit: 2-step
!-------------------------------------------------------------------------------- 		
	Real(kind=8)	eval(101),delt,ddel,x
	Real(kind=8)	b0,b1,b2,b3,b4,cval(101),del,delm2p2
	Real(kind=8)	err(101),tval(101)
	Real(kind=8)	arnst(20),ardel(20)

	
	integer			nsteps,iOut
!------------------------------------------------------------------- Heading
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
	write(iOut,*)
     &	'   1D Heat Equation Time Stepping with',
     &    '                QUADRATIC B-spline',
     &    '                         by',   
     &    '                         ',   
     &    '                    DEBABRATA RAY',   
     &    '                         '   
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
!	--------------------------------------------------------------------------- LOOP
	nlup = 5
!	---------------------------------------------------------
!	Following data chosen to match Zien & Taylor example
!	Chapter 18, vol. 1
!	---------------------------------------------------------
	arnst(1) = 101
	ardel(1) = .1
!
	arnst(2) = 6
	arnst(2) = 21
	ardel(2) = .5
!
	arnst(3) = 3
	arnst(3) = 12
	ardel(3) = .9
!
	arnst(4) = 3
	arnst(4) = 8
	ardel(4) = 1.5
!
	arnst(5) = 3
	arnst(5) = 5
	ardel(5) = 2.5
!

	do jl = 1,nlup
!	--------------------------------------------------------------------------- exact soln
		nsteps	= arnst(jl)
		ddel	= ardel(jl)
		delt	=-ddel
!
		write(iOut,1020) ddel
!
		do i = 1,nsteps
			x = delt+ddel
			eval(i)=EXP(-x)

			delt= x
			tval(i)=x
		end do
!	---------------------------
		write(iOut, 1000) 
		write(iOut, 1010) (tval(j),eval(j), j = 1,nsteps)
!	--------------------------------------------------------------------------- Computed soln
		del	= ddel
		write(iOut,2020) del
!	---------------------------------------- initial step
		b0		= 1.D0
		cval(1)	= b0
		delm2p2	=(2-del)/(2+del)
		b2		= delm2p2*b0
		cval(2)	= b2
!	---------------------------------------- Loop steps
		do i = 3,nsteps
			b4		= delm2p2*b2
!
			cval(i)	= b4
			b2		= b4
		end do
!	---------------------------
		write(iOut, 2000) 
		write(iOut, 2010) (tval(j),cval(j), j = 1,nsteps)
!
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
	end do
!
!
  999 return 

 1020 format(//5x,"time-step = ", f10.3//)
 1000 format(//
     & " Exact values.........."//5("    tval  ",2x,"    Eval  ") )
 1010 format(5(f10.4,2x,f10.5))
 2020 format(//5x,"Each Interval = ", f10.3//)
 2000 format(//
     & " Computed values.........."//5("    tval  ",2x,"    Cval  ") )
 2010 format(5(f10.4,2x,f10.5))

	end
!	 
	Subroutine Cubic(iOut)
 			
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!========================================================================
!	Method		Cubic B-Spline in Bezier Form
!--------------------------------------------------------------------------------
!               o	
!	equation: d(t) + d(t) = 0 with initial condition d(0)=1, te[0,10[
!	
!	solution: d(t) = exp(-t)
!-------------------------------------------------------------------------------- 		
!	Time stepping algorithm: C1 continuity, Quadratic B-spline Fit: 2-step
!-------------------------------------------------------------------------------- 		
	Real(kind=8)	eval(101),delt,ddel,x
	Real(kind=8)	b0,b1,b2,b3,b4,b5,b6,cval(101),del,amplify
	Real(kind=8)	err(101),tval(101)
	Real(kind=8)	arnst(20),ardel(20)

	
	integer			nsteps,iOut
!------------------------------------------------------------------- Heading
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
	write(iOut,*)
     &	'   1D Heat Equation Time Stepping with',
     &    '                    CUBIC B-spline',
     &    '                         by',   
     &    '                         ',   
     &    '                    DEBABRATA RAY',   
     &    '                         '   
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
!	--------------------------------------------------------------------------- LOOP
	nlup = 5
!	---------------------------------------------------------
!	Following data chosen to match Zien & Taylor example
!	Chapter 18, vol. 1
!	---------------------------------------------------------
	arnst(1) = 101
	ardel(1) = .1
!
	arnst(2) = 6
	arnst(2) = 21
	ardel(2) = .5
!
	arnst(3) = 3
	arnst(3) = 12
	ardel(3) = .9
!
	arnst(4) = 3
	arnst(4) = 8
	ardel(4) = 1.5
!
	arnst(5) = 3
	arnst(5) = 5
	ardel(5) = 2.5
!

	do jl = 1,nlup
!	--------------------------------------------------------------------------- exact soln
		nsteps	= arnst(jl)
		ddel	= ardel(jl)
		delt	=-ddel
!
		write(iOut,1020) ddel
!
		do i = 1,nsteps
			x = delt+ddel
			eval(i)=EXP(-x)

			delt= x
			tval(i)=x
		end do
!	---------------------------
		write(iOut, 1000) 
		write(iOut, 1010) (tval(j),eval(j), j = 1,nsteps)
!	--------------------------------------------------------------------------- Computed soln
		del	= ddel
		write(iOut,2020) del
!	---------------------------------------- initial step
		b0		= 1.D0
		cval(1)	= b0
		amplify	=(del*(del-6)+12)/(del*(del+6)+12)
		b3		= amplify*b0
		cval(2)	= b3
!	---------------------------------------- Loop steps
		do i = 3,nsteps
			b6		= amplify*b3
!
			cval(i)	= b6
			b3		= b6
		end do
!	---------------------------
		write(iOut, 2000) 
		write(iOut, 2010) (tval(j),cval(j), j = 1,nsteps)
!
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
	end do
!
!
  999 return 

 1020 format(//5x,"time-step = ", f10.3//)
 1000 format(//
     & " Exact values.........."//5("    tval  ",2x,"    Eval  ") )
 1010 format(5(f10.4,2x,f10.5))
 2020 format(//5x,"Each Interval = ", f10.3//)
 2000 format(//
     & " Computed values.........."//5("    tval  ",2x,"    Cval  ") )
 2010 format(5(f10.4,2x,f10.5))

	end
!	 
	Subroutine Cubic_ALT(iOut)
!	//////////////////////////
!			NO GOOD		
!	//////////////////////////
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!========================================================================
!	Method		Cubic B-Spline in Bezier Form
!--------------------------------------------------------------------------------
!               o	
!	equation: d(t) + d(t) = 0 with initial condition d(0)=1, te[0,10[
!	
!	solution: d(t) = exp(-t)
!-------------------------------------------------------------------------------- 		
!	Time stepping algorithm: C1 continuity, Quadratic B-spline Fit: 2-step
!-------------------------------------------------------------------------------- 		
	Real(kind=8)	eval(101),delt,ddel,x
	Real(kind=8)	b0,b1,b2,b3,b4,b5,b6,cval(101),del,amplify
	Real(kind=8)	alfa,beta,alfa2,beta2
	Real(kind=8)	err(101),tval(101)
	Real(kind=8)	arnst(20),ardel(20)

	
	integer			nsteps,iOut
!------------------------------------------------------------------- Heading
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
	write(iOut,*)
     &	'   1D Heat Equation Time Stepping with',
     &    '                    CUBIC_ALTERNATE B-spline',
     &    '                         by',   
     &    '                         ',   
     &    '                    DEBABRATA RAY',   
     &    '                         '   
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
!	--------------------------------------------------------------------------- LOOP
	nlup = 5
!	---------------------------------------------------------
!	Following data chosen to match Zien & Taylor example
!	Chapter 18, vol. 1
!	---------------------------------------------------------
	arnst(1) = 101
	ardel(1) = .1
!
	arnst(2) = 6
	arnst(2) = 21
	ardel(2) = .5
!
	arnst(3) = 3
	arnst(3) = 12
	ardel(3) = .9
!
	arnst(4) = 3
	arnst(4) = 8
	ardel(4) = 1.5
!
	arnst(5) = 3
	arnst(5) = 5
	ardel(5) = 2.5
!

	do jl = 1,nlup
!	--------------------------------------------------------------------------- exact soln
		nsteps	= arnst(jl)
		ddel	= ardel(jl)
		delt	=-ddel
!
		write(iOut,1020) ddel
!
		do i = 1,nsteps
			x = delt+ddel
			eval(i)=EXP(-x)

			delt= x
			tval(i)=x
		end do
!	---------------------------
		write(iOut, 1000) 
		write(iOut, 1010) (tval(j),eval(j), j = 1,nsteps)
!	--------------------------------------------------------------------------- Computed soln
		del	= ddel
		write(iOut,2020) del
		alfa	= 0.5		! assumed constant time-step
		beta	= 0.5		! assumed constant time-step
		alfa2	= alfa*alfa
		beta2	= beta*beta
!	---------------------------------------- initial step
		b0		= 1.D0
		cval(1)	= b0
		amplify	=(del*(del-6)+12)/(del*(del+6)+12)
		b3		= amplify*b0
		cval(2)	= b3
		b1		= (3-del)*b0/3
		b2		= (3+del)*b3/3
!	---------------------------------------- Loop steps
		do i = 3,nsteps
			b4		= (b3 - beta*b2)/alfa
			b5		= (beta2*b1 - beta*b2 + alfa*b4)/alfa2
			b6		= 3*b5/(3+del)
!
			cval(i)	= b6
			b1		= b4
			b2		= b5		
			b3		= b6
		end do
!	---------------------------
		write(iOut, 2000) 
		write(iOut, 2010) (tval(j),cval(j), j = 1,nsteps)
!
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
	end do
!
!
  999 return 

 1020 format(//5x,"time-step = ", f10.3//)
 1000 format(//
     & " Exact values.........."//5("    tval  ",2x,"    Eval  ") )
 1010 format(5(f10.4,2x,f10.5))
 2020 format(//5x,"Each Interval = ", f10.3//)
 2000 format(//
     & " Computed values.........."//5("    tval  ",2x,"    Cval  ") )
 2010 format(5(f10.4,2x,f10.5))

	end

