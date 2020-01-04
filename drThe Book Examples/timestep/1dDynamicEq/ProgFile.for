	Program TimeStep_1DDynamic
!------------------------- Modules
	USE linear_operators
	USE DFLIB
	USE DFPORT
!	USE SCIGRAPH
!------------------------------------------------------------------- Files
	include 'files.h'

	Real(kind=8)	timperiod,specrad
!	--------------------------------------------------------------------------- Prelim
	call Set_Files()
!------------------------------------------------------------------- Today's Date/Time		
	call Set_TimeDate(iOut)
!	-------------------------------------------- AvgAcclMidPtRule
!	call AvgAccl_MidPtRule(timperiod,iOut)
!	call SpectralRadius_AvgMid(srad,tp,iOut)
!	-------------------------------------------- CubicBSpline
!	call CubicBS(iOut)
!	call SpectralRadius_LinAccl(srad,tp,iOut)
!	-------------------------------------------- CubicMidPt
	call CubicBS_MidPtRule(timperiod,iOut)
!	call SpectralRadius(specrad,timperiod,iOut)
!	call SpectralRadiusAlt(specrad,timperiod,iOut)
!	-------------------------------------------- CubicBSplineExtended
!	call CubicBS_ExtendedTimeStep(iOut)
!	-------------------------------------------- End
  999 Stop	'Program: TimeStep_1DDynamic Ran OK'

	end 
!	 
	Subroutine AvgAccl_MidPtRule(tp,iOut)
 			
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!========================================================================
!	Method		
!--------------------------------------------------------------------------------
!               oo	                                         o
!	equation: d(t) + d(t) = 0 with initial condition d(0)=1, d(0)=1, te[0,10[
!	
!	solution: d(t) = exp(-t)
!-------------------------------------------------------------------------------- 		
!	Time stepping algorithm: C1 continuity, Quadratic B-spline Fit: 2-step
!-------------------------------------------------------------------------------- 		
	Real(kind=8)	om,om2,zi,omdel,zomdel,alf0,alf1,bet0,bet1,gama

	Real(kind=8)	xm,xc,xk,xp,xpm,d,ddot,d2dot,reci,pi,tp
	Real(kind=8)	eval(101),delt,ddel,ddel2,x
	Real(kind=8)	delu,xpO,delp,del,amplify
	Real(kind=8)	err,tval,cDis,cVel,cAcc
!	Real(kind=8)	err(101),tval(101)
	Real(kind=8)	ardel(20)
	integer			irnst(20),np_tp2

	
	integer			nsteps,iOut
!------------------------------------------------------------------- Heading
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
	write(iOut,*)
     &	'   1D Dynamic Equation Time Stepping with CUBIC B-spline:',
     &	'     (MidPt Average Acceleration Method: mid pt. rule)   ',
     &    '                         by',   
     &    '                         ',   
     &    '                    DEBABRATA RAY',   
     &    '                         '   
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
!
	pi	= 4.D0*atan(1.)
!	--------------------------------------------------------------------------- LOOP
	nlup = 1
!	---------------------------------------------------------
!	Following data chosen to match chopra example 5.1
!	Chapter 5 Section 5.2 page 169
!	---------------------------------------------------------
	irnst(1) = 9
	ardel(1) = .1D0
!	-------------------------------- initial data : Chopra p169
	xm		= 0.2533D0
	xc		= 0.1592D0
	xk		= 10.D0
	xp		= 0.
	xpm		= 0.
!	-------------------------------- omega & zi
	om2		= xk/xm
	om		= dsqrt(om2)
	zi		= xc/xm/2.D0/om
!	-------------------------------- system time period
	tp		= 2.D0*pi/om
	np_tp2  = tp/ardel(1)/2.D0 + 1
!	------------------	.
	do jl = 1,nlup
!	--------------------------------------------------------------------------- computed soln
		nsteps	= irnst(jl)
		ddel	= ardel(jl)
		delt	= ddel/tp
		ddel2	= ddel*ddel	
!	-------------------------------- omega & zi
		omdel	= om*ddel
		zomdel	= zi*omdel
		alfa	= 2.D0+4.D0*pi*zi*delt+2.D0*pi*pi*delt*delt
		gama	= 1.D0/alfa
!	-----------------------
		write(iOut,1020) ddel
		write(iOut,1030) tp,delt,np_tp2
	
		write(iOut, 2000) 
!	-------------------------------- initial step
	i		= 0
!
	d		= 0.
	ddot	= 0.
	d2dot	= (xp-2.D0*zi*om*ddot-om2*d)
!
	tval	= 0	
	cDis	= d
	cVel	= ddot
	cAcc	= d2dot
!	---------------------------
	write(iOut, 2010) tval,xpm,cDis,cVel,cAcc
!	----------
!	
		do i = 0,nsteps
			xpO		= xp
			tim		= (i+1)*ddel
			if(tim.le..6D0) then
				xp		= 10*sin(pi*tim/.6)/xm		
				xpm		= 10*sin(pi*(tim - 0.5D0*ddel)/.6)/xm	! mid pt.rule
			else
				xp		= 0.D0
				xpm		= 0.D0
			endif
!
			delu	= gama*(ddel2*(xpm-om2*d)+2.D0*ddel*ddot)
!
			d		= d+delu
			ddot	= -ddot+2*delu/ddel
			d2dot	= (xp-2.D0*zi*om*ddot-om2*d)
			tval	= tim	
			cDis	= d
			cVel	= ddot
			cAcc	= d2dot
!	---------------------------
			write(iOut, 2010) tval,xpm,cDis,cVel,cAcc
!	----------
		end do
!	---------------------------
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
	end do
!
!
  999 return 

 1000 format(//
     & " Exact values.........."//5("    tval  ",2x,"    Eval  ") )
 1010 format(5(f10.4,2x,f10.5))
 1020 format(//5x,"Chopra: Example 5.1:pp 169",//
     &	   10x,"time-step                       = ", f10.3)
 1030 format(10x,"time period                     = ", f10.3/
     &	   10x,"Ratio of timestep//time period  = ", f10.3/
     &	   10x,"no. of intervals per half cycle = ", I10//)
 2020 format(//5x,"Each Interval = ", f10.3//)
 2000 format(//
     & " Computed values.........."//
     & "     tval",2x,"       xp",2x,
     & "    CDis",2x,"    CVel",2x,"    CAcc" )
 2010 format(5(2x,f8.4))

	end
!	 
!	 
	Subroutine CubicBS(iOut)
 			
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!========================================================================
!	Method		Cubic B-Spline in Bezier Form
!--------------------------------------------------------------------------------
!               oo	                                         o
!	equation: d(t) + d(t) = 0 with initial condition d(0)=1, d(0)=1, te[0,10[
!	
!	solution: d(t) = exp(-t)
!-------------------------------------------------------------------------------- 		
!	Time stepping algorithm: C1 continuity, Quadratic B-spline Fit: 2-step
!-------------------------------------------------------------------------------- 		
	Real(kind=8)	xm,xc,xk,xp,d,ddot,d2dot,reci,pi,tp
	Real(kind=8)	eval(101),delt,ddel,ddel2,x
	Real(kind=8)	b0,b1,b2,b3,b4,b5,b6,del,amplify
	Real(kind=8)	err,tval,cDis,cVel,cAcc
!	Real(kind=8)	err(101),tval(101)
	Real(kind=8)	ardel(20)
	integer			irnst(20),np_tp2

	
	integer			nsteps,iOut
!------------------------------------------------------------------- Heading
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
	write(iOut,*)
     &	'   1D Dynamic Equation Time Stepping with CUBIC B-spline:',
     &	'  (same strength as Newmark_s Linear Acceleration Method)',
     &    '                         by',   
     &    '                         ',   
     &    '                    DEBABRATA RAY',   
     &    '                         '   
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
!
	pi	= 4.D0*atan(1.)
!	--------------------------------------------------------------------------- LOOP
	nlup = 1
!	---------------------------------------------------------
!	Following data chosen to match chopra example 5.1
!	Chapter 5 Section 5.2 page 169
!	---------------------------------------------------------
	irnst(1) = 9
	ardel(1) = .1D0
!	-------------------------------- initial data : Chopra p169
	xm		= 0.2533D0
	xc		= 0.1592D0
	xk		= 10.D0
	xp		= 0.
	d		= 0.
	ddot	= 0.
!	-------------------------------- system time period
	tp		= 2.D0*pi/dsqrt(xk/xm)
	np_tp2  = tp/ardel(1)/2.D0 + 1
!	------------------	.
	do jl = 1,nlup
!	--------------------------------------------------------------------------- computed soln
		nsteps	= irnst(jl)
		ddel	= ardel(jl)
		delt	=-ddel
		ddel2	= ddel*ddel	
!	-----------------------
		write(iOut,1020) ddel
		write(iOut,1030) tp,np_tp2
	
		write(iOut, 2000) 
!	-------------------------------- initial step
	i		= 0
	reci	= 1./(6*xm+3*xc*ddel+xk*ddel2)
!
	b0		= 0
	b1		= 0
	b2		= 0
	b3		= reci*(xp*ddel2+6*xm*(2*b2-b1)+3*xc*ddel*b2)
!
	d		= b3
	ddot	= 3*(b3-b2)/ddel
	d2dot	= (xp-xc*ddot-xk*d)/xm
!
	tval	= 0	
	cDis	= d
	cVel	= ddot
	cAcc	= d2dot
!	---------------------------
	write(iOut, 2010) tval,xp,b0,b1,b2,b3,cDis,cVel,cAcc
!	----------
!	
		do i = 0,nsteps
			tim		= (i+1)*ddel
			if(tim.le..6D0) then
				xp		= 10*sin(pi*tim/.6)
			else
				xp		= 0.D0
			endif
			tem		= b1
!
			b0		= b3
			b1		= 2*b3-b2
			b2		= 2*b1-2*b2+tem
			b3		= reci*(xp*ddel2+6*xm*(2*b2-b1)+3*xc*ddel*b2)
!
			d		= b3
			ddot	= 3.D0*(b3-b2)/ddel
			d2dot	= (xp-xc*ddot-xk*d)/xm
!
			tval	= tim	
			cDis	= d
			cVel	= ddot
			cAcc	= d2dot
!	---------------------------
			write(iOut, 2010) tval,xp,b0,b1,b2,b3,cDis,cVel,cAcc
!	----------
		end do
!	---------------------------
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
	end do
!
!
  999 return 

 1000 format(//
     & " Exact values.........."//5("    tval  ",2x,"    Eval  ") )
 1010 format(5(f10.4,2x,f10.5))
 1020 format(//5x,"Chopra: Example 5.1:pp 169",//
     &	   10x,"time-step                       = ", f10.3)
 1030 format(10x,"time period                     = ", f10.3/
     &	   10x,"no. of intervals per half cycle = ", I10//)
 2020 format(//5x,"Each Interval = ", f10.3//)
 2000 format(//
     & " Computed values.........."//
     & "     tval",2x,"       xp",2x,"      b0",2x,"      b1",2x,
     & "      b2",2x,
     & "      b3",2x,"    CDis",2x,"   CVel",2x,"     CAcc" )
 2010 format(9(2x,f8.4))

	end
!	 
	Subroutine CubicBS_MidPtRule(tp,iOut)
 			
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!========================================================================
!	Method		Cubic B-Spline in Bezier Form
!--------------------------------------------------------------------------------
!               oo	                                         o
!	equation: d(t) + d(t) = 0 with initial condition d(0)=1, d(0)=1, te[0,10[
!	
!	solution: d(t) = exp(-t)
!-------------------------------------------------------------------------------- 		
!	Time stepping algorithm: C1 continuity, Quadratic B-spline Fit: 2-step
!-------------------------------------------------------------------------------- 		
	Real(kind=8)	om,om2,zi,omdel,zomdel,alf0,alf1,bet0,bet1,gama

	Real(kind=8)	xm,xc,xk,xp,xpm,d,ddot,d2dot,reci,pi,tp
	Real(kind=8)	eval(101),delt,ddel,ddel2,x
	Real(kind=8)	b0,b1,b2,b3,b4,b5,b6,del,amplify
	Real(kind=8)	err,tval,cDis,cVel,cAcc
!	Real(kind=8)	err(101),tval(101)
	Real(kind=8)	ardel(20)
	integer			irnst(20),np_tp2

	
	integer			nsteps,iOut
!------------------------------------------------------------------- Heading
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
	write(iOut,*)
     &	'   1D Dynamic Equation Time Stepping with CUBIC B-spline:',
     &	'             (MidPt Cubic Method: mid pt. rule)          ',
     &    '                         by',   
     &    '                         ',   
     &    '                    DEBABRATA RAY',   
     &    '                         '   
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
!
	pi	= 4.D0*atan(1.)
!	--------------------------------------------------------------------------- LOOP
	nlup = 1
!	---------------------------------------------------------
!	Following data chosen to match chopra example 5.1
!	Chapter 5 Section 5.2 page 169
!	---------------------------------------------------------
	irnst(1) = 9
	ardel(1) = .1D0
!	-------------------------------- initial data : Chopra p169
	xm		= 0.2533D0
	xc		= 0.1592D0
	xk		= 10.D0
	xp		= 0.
	xpm		= 0.
!	-------------------------------- omega & zi
	om2		= xk/xm
	om		= dsqrt(om2)
	zi		= xc/xm/2.D0/om
!	-------------------------------- system time period
	tp		= 2.D0*pi/om
	np_tp2  = tp/ardel(1)/2.D0 + 1
!	------------------	.
	do jl = 1,nlup
!	--------------------------------------------------------------------------- computed soln
		nsteps	= irnst(jl)
		ddel	= ardel(jl)
		delt	= ddel/tp
		ddel2	= ddel*ddel	
!	-------------------------------- omega & zi
		omdel	= om*ddel
		zomdel	= zi*omdel
		alfa	= 2.D0+4.D0*pi*zi*delt+2.D0*pi*pi*delt*delt
		gama	= 1.D0/alfa
!	-----------------------
		write(iOut,1020) ddel
		write(iOut,1030) tp,np_tp2
	
		write(iOut, 2000) 
!	-------------------------------- initial step
	i		= 0
!
	d		= 0.
	ddot	= 0.
	d2dot	= (xp-2.D0*zi*om*ddot-om2*d)

	b0		= 0
	b1		= 0
	b2		= 0
	b3		= b0 + gama*(ddel2*(xpm-om2*b0)+2.D0*ddel*ddot)
!
	d		= b3
	ddot	= 3*(b3-b2)/ddel
	d2dot	= (xp-2.D0*zi*om*ddot-om2*d)



!
	tval	= 0	
	cDis	= d
	cVel	= ddot
	cAcc	= d2dot
!	---------------------------
	write(iOut, 2010) tval,xpm,b0,b1,b2,b3,cDis,cVel,cAcc
!	----------
!	
		do i = 0,nsteps
			tim		= (i+1)*ddel
			if(tim.le..6D0) then
				xp		= 10*sin(pi*tim/.6)/xm		
				xpm		= 10*sin(pi*(tim - 0.5D0*ddel)/.6)/xm	! mid pt.rule
			else
				xp		= 0.D0
				xpm		= 0.D0
			endif
			tem		= b1
!
			b0		= b3
			b3		= b0 + gama*(ddel2*xpm+2.D0*ddot*ddel
     &					-b0*4.D0*pi*pi*delt*delt)
!			b3		= b0 + gama*(ddel2*(xpm-om2*b0)+2.D0*ddel*ddot)
!
			d		= b3
			ddot	= -ddot+2.D0*(b3-b0)/ddel
			d2dot	= (xp-2.D0*zi*om*ddot-om2*d)
!			d2dot	= 6.D0*(b1-2.D0*b2+b3)/ddel/ddel
			tval	= tim	
			cDis	= d
			cVel	= ddot
			cAcc	= d2dot
!	---------------------------
			write(iOut, 2010) tval,xpm,b0,b1,b2,b3,cDis,cVel,cAcc
!	----------
		end do
!	---------------------------
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
	end do
!
!
  999 return 

 1000 format(//
     & " Exact values.........."//5("    tval  ",2x,"    Eval  ") )
 1010 format(5(f10.4,2x,f10.5))
 1020 format(//5x,"Chopra: Example 5.1:pp 169",//
     &	   10x,"time-step                       = ", f10.3)
 1030 format(10x,"time period                     = ", f10.3/
     &	   10x,"no. of intervals per half cycle = ", I10//)
 2020 format(//5x,"Each Interval = ", f10.3//)
 2000 format(//
     & " Computed values.........."//
     & "     tval",2x,"       xp",2x,"      b0",2x,"      b1",2x,
     & "      b2",2x,
     & "      b3",2x,"    CDis",2x,"   CVel",2x,"     CAcc" )
 2010 format(9(2x,f8.4))

	end
!	 
	Subroutine CubicBS_ExtendedTimeStep(iOut)
 			
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!========================================================================
!	Method		Cubic B-Spline in Bezier Form
!--------------------------------------------------------------------------------
!               oo	                                         o
!	equation: d(t) + d(t) = 0 with initial condition d(0)=1, d(0)=1, te[0,10[
!	
!	solution: d(t) = exp(-t)
!-------------------------------------------------------------------------------- 		
!	Time stepping algorithm: C1 continuity, Quadratic B-spline Fit: 2-step
!-------------------------------------------------------------------------------- 		
	Real(kind=8)	xm,xc,xk,xp,d,ddot,d2dot,reci,pi,theta,tp
	Real(kind=8)	eval(101),ddel,ddel2,x,alf,bet
	Real(kind=8)	deltaT,dt,dt2,dt3,tm2,tm12,tm13,vmul,amul
	Real(kind=8)	b0,b1,b2,b3,b4,b5,b6,del,amplify
	Real(kind=8)	err,tval,cDis,cVel,cAcc
!	Real(kind=8)	err(101),tval(101)
	Real(kind=8)	ardel(20)
	integer			irnst(20),np_tp2

	
	integer			nsteps,iOut
!------------------------------------------------------------------- Heading
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
	write(iOut,*)
     &	'   1D Dynamic Equation Time Stepping with CUBIC B-spline:',
     &	'              Time Step Extended by theta',
     &	'          (compare with Wilson_s Theta Method)           ',
     &    '                         by',   
     &    '                         ',   
     &    '                    DEBABRATA RAY',   
     &    '                         '   
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
!
	pi	= 4.D0*atan(1.)
!	--------------------------------------------------------------------------- LOOP
	nlup	= 1
!	---------------------------------------------------------
!	Following data chosen to match chopra example 5.1
!	Chapter 5 Section 5.2 page 169
!	---------------------------------------------------------
	irnst(1) = 9
	ardel(1) = .1D0
	theta	= 1.0D0
	theta	= 1.4D0
	theta	= 1.5D0
	theta	= 2.0D0
	theta	= 1.1D0
	theta	= 1.2D0
!	-------------------------------- initial data : Chopra p169
	xm		= 0.2533D0
	xc		= 0.1592D0
	xk		= 10.D0
	xp		= 0.
	d		= 0.
	ddot	= 0.
!	-------------------------------- system time period
	tp		= 2.D0*pi/dsqrt(xk/xm)
	np_tp2  = tp/ardel(1)/2.D0 + 1
!	------------------	.
	do jl = 1,nlup
!	--------------------------------------------------------------------------- computed soln
		nsteps	= irnst(jl)
		deltaT	= ardel(jl)
		ddel	= ardel(jl)*theta
		ddel2	= ddel*ddel	
!	-----------------------
		write(iOut,1020) deltaT,theta
		write(iOut,1030) tp,np_tp2
		write(iOut, 2000) 
!	-------------------------------- initial step
	i		= 0
	reci	= 1./(6*xm+3*xc*ddel+xk*ddel2)
!
	b0		= 0
	b1		= 0
	b2		= 0
	b3		= reci*(xp*ddel2+6*xm*(2*b2-b1)+3*xc*ddel*b2)
!
	d		= b3
	ddot	= 3*(b3-b2)/ddel
	d2dot	= (xp-xc*ddot-xk*d)/xm
!
	tval	= 0	
	cDis	= d
	cVel	= ddot
	cAcc	= d2dot
!	---------------------------
	write(iOut, 2010) tval,xp,b0,b1,b2,b3,cDis,cVel,cAcc
!	----------
!	
		do i = 0,nsteps
			tim		= i*deltaT+ddel
			if(tim.le..6D0) then
				xp		= 10*sin(pi*tim/.6)
			else
				xp		= 0.D0
			endif
			tem		= b1
!
			b0		= b3
			dtp		= deltaT+ddel
!
			alf		= deltaT/dtp
			bet		= ddel/dtp

			b1		= b3/alf-bet*b2/alf
			b2		= (alf*b1-bet*b2+bet*bet*tem)/alf/alf
			b3		= reci*(xp*ddel2+6*xm*(2*b2-b1)+3*xc*ddel*b2)
!			===================================================== COmpute & Update at deltaT
			dt		= deltaT/ddel
			dt2		= dt*dt
			dt3		= dt2*dt
			tm1		= 1-dt
			tm12	= tm1*tm1
			tm13	= tm12*tm1
			vmul	= 3.D0/ddel
			amul	= 6.D0/ddel/ddel
!
			d		= tm13*b0+3.D0*(tm12*dt*b1+tm1*dt2*b2) + dt3*b3
			ddot	= -3.D0*(tm12*b0 - (-2*tm1*dt+tm12)*b1 
     &					- (-dt2+2*dt*tm1)*b2 - dt2*b3)/ddel
			d2dot	= 6*(tm1*b0+(3*dt-2)*b1+(1-3*dt)*b2
     &					+dt*b3)/ddel/ddel
!			/////////////////////////////// update at deltaT
			b3		= d
			b2		= b3 - ddot*deltaT/3
!
			tval	= (i+1)*deltaT	
			cDis	= d
			cVel	= ddot
			cAcc	= d2dot
!	---------------------------
			write(iOut, 2010) tval,xp,b0,b1,b2,b3,cDis,cVel,cAcc
!	----------
		end do
!	---------------------------
	write(iOut,*)
     &	'=========================================================',
     &	'==============='
	end do
!
!
  999 return 

 1000 format(//
     & " Exact values.........."//5("    tval  ",2x,"    Eval  ") )
 1010 format(5(f10.4,2x,f10.5))
 1020 format(//5x,"Chopra: Example 5.1:pp 169",//
     &	   10x,"time-step                       = ", f10.3/
     &	   10x,"theta                           = ", f10.3)
 1030 format(10x,"time period                     = ", f10.3/
     &	   10x,"no. of intervals per half cycle = ", I10//)
 2020 format(//5x,"Each Interval = ", f10.3//)
 2000 format(//
     & " Computed values.........."//
     & "     tval",2x,"       xp",2x,"      b0",2x,"      b1",2x,
     & "      b2",2x,
     & "      b3",2x,"    CDis",2x,"   CVel",2x,"     CAcc" )
 2010 format(9(2x,f8.4))

	end

