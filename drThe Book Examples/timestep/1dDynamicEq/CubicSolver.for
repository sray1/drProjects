	Subroutine CubicSolver(sol,a,b,c,d,iOut)
	Implicit Real(kind=8) (a-h,o-z)
c ----------------------------------------------------------------------
c Solve a cubic equation where a, b, c, and d are real.
c   a*x**3 + b*x**2 + c*x + d = 0
c
c Variables used:
c   a, b, c, d  ... coefficients (input)
c   y1, y2, y3  ... three transformed solutions
c   y2r, y2i    ... real and imaginary parts of a pair of complex roots
c   x(i)        ... three (generally) complex solutions (output)
c   nroot       ... number of roots
c
c Formula used are given in Tuma, "Engineering Mathematics Handbook", p7
c   (McGraw Hill, 1978).
c   Step 0: If a is 0. use the quadratic formula to avoid dividing by 0.
c   Step 1: Calculate p and q
c           p = ( 3*c/a - (b/a)**2 ) / 3
c           q = ( 2*(b/a)**3 - 9*b*c/a/a + 27*d/a ) / 27
c   Step 2: Calculate discriminant D
c           D = (p/3)**3 + (q/2)**2
c   Step 3: Depending on the sign of D, we follow different strategy.
c           If D<0, three distinct real roots.
c           If D=0, three real roots of which at least two are equal.
c           If D>0, one real and two complex roots.
c   Step 3a: For D>0 and D=0,
c           Calculate u and v
c           u = cubic_root(-q/2 + sqrt(D))
c           v = cubic_root(-q/2 - sqrt(D))
c           Find the three transformed roots
c           y1 = u + v
c           y2 = -(u+v)/2 + i (u-v)*sqrt(3)/2
c           y3 = -(u+v)/2 - i (u-v)*sqrt(3)/2
c   Step 3b Alternately, for D<0, a trigonometric formulation is more convenient
c           y1 =  2 * sqrt(|p|/3) * cos(phi/3)
c           y2 = -2 * sqrt(|p|/3) * cos((phi+pi)/3)
c           y3 = -2 * sqrt(|p|/3) * cos((phi-pi)/3)
c           where phi = acos(-q/2/sqrt(|p|**3/27))
c                 pi  = 3.141592654...
c   Step 4  Finally, find the three roots
c           x = y - b/a/3
c
c ----------------------------------------------------------------------
c Instructor: Nam Sun Wang
c ----------------------------------------------------------------------

c Declare variables
      complex(8)	sol(3),x(3)
	real*8		rat
      data pi/3.141592654/

c Print the program header ---------------------------------------------
!      write(iOut,*) '--------------------------------------------------'
!      write(iOut,*) 'Solve a cubic equation:'
!      write(iOut,*) '   a*x**3 + b*x**2 + c*x + d = 0'
!      write(iOut,*) 'where a, b, c, and d are real.'
!      write(iOut,*) '--------------------------------------------------'

c Input the coefficients -----------------------------------------------
c      write(*,*) 'Enter a: '
c      read(*,*) a
c      write(*,*) 'Enter b: '
c      read(*,*) b
c      write(*,*) 'Enter c: '
c      read(*,*) c
c      write(*,*) 'Enter d: '
c      read(*,*) d

c Step 0: If a is 0 use the quadratic formula. -------------------------
      IF(a .eq. 0.)THEN
      if(b .eq. 0.)then
        if(c. eq. 0.)then
c         We have a non-equation; therefore, we have no valid solution
          nroot = 0
        else
c         We have a linear equation with 1 root.
          nroot = 1
          x(1) = cmplx(-d/c, 0.)
        endif
      else
c     We have a true quadratic equation.  Apply the quadratic formula to find two roots.
      nroot = 2
        DD = c*c-4.*b*d
        if(DD .ge. 0.)then
          x(1) = cmplx((-c+sqrt(DD))/2./b, 0.)
          x(2) = cmplx((-c-sqrt(DD))/2./b, 0.)
        else
          x(1) = cmplx(-c/2./b, +sqrt(-DD)/2./b)
          x(2) = cmplx(-c/2./b, -sqrt(-DD)/2./b)
        endif
      endif

      ELSE

c Cubic equation with 3 roots
      nroot = 3

c Step 1: Calculate p and q --------------------------------------------
      p  = c/a - b*b/a/a/3.
      q  = (2.*b*b*b/a/a/a - 9.*b*c/a/a + 27.*d/a) / 27.

c Step 2: Calculate DD (discriminant) ----------------------------------
      DD = p*p*p/27. + q*q/4.

c Step 3: Branch to different algorithms based on DD -------------------
      if(DD .lt. 0.)then
c       Step 3b:
c       3 real unequal roots -- use the trigonometric formulation
        phi = acos(-q/2./sqrt(abs(p*p*p)/27.))
        temp1=2.*sqrt(abs(p)/3.)
        y1 =  temp1*cos(phi/3.)
        y2 = -temp1*cos((phi+pi)/3.)
        y3 = -temp1*cos((phi-pi)/3.)
      else
c       Step 3a:
c       1 real root & 2 conjugate complex roots OR 3 real roots (some are equal)
        temp1 = -q/2. + sqrt(DD)
        temp2 = -q/2. - sqrt(DD)
        u = abs(temp1)**(1./3.)
        v = abs(temp2)**(1./3.)
        if(temp1 .lt. 0.) u=-u
        if(temp2 .lt. 0.) v=-v
        y1  = u + v
        y2r = -(u+v)/2.
        y2i =  (u-v)*sqrt(3.)/2.
      endif

c Step 4: Final transformation -----------------------------------------
      temp1 = b/a/3.
      y1 = y1-temp1
      y2 = y2-temp1
      y3 = y3-temp1
      y2r=y2r-temp1

c Assign answers -------------------------------------------------------
      if(DD .lt. 0.)then
        x(1) = cmplx( y1,  0.)
        x(2) = cmplx( y2,  0.)
        x(3) = cmplx( y3,  0.)
      elseif(DD .eq. 0.)then
        x(1) = cmplx( y1,  0.)
        x(2) = cmplx(y2r,  0.)
        x(3) = cmplx(y2r,  0.)
      else
        x(1) = cmplx( y1,  0.)
        x(2) = cmplx(y2r, y2i)
        x(3) = cmplx(y2r,-y2i)
      endif

      ENDIF

c Output the results. --------------------------------------------------
      write(iOut,1000) nroot
      do i=1, nroot
        write(iOut,*) x(i)
      enddo
!
	return
 1000 format(//
     & " There are", I2, " root(s)" )
 1010 format(5(f10.4,2x,f10.5))
 1020 format(//5x,"Computed roots",//
     &	   10x,"root 1                       = ", f10.3/
     &	   10x,"root 2                       = ", f10.3/
     &	   10x,"root 3                       = ", f10.3)
 1030 format(10x,"time period                     = ", f10.3/
     &	   10x,"no. of intervals per half cycle = ", I10//)
 2020 format(//5x,"Each Interval = ", f10.3//)
 2010 format(9(2x,f8.4))

      end

