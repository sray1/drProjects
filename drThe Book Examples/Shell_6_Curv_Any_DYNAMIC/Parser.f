      subroutine acheck(x,y,n0,nl)

c     Purpose: Data parser

c     Inputs:
c        x        - Character input data
c        n0       - Field widths for parse
c        nl       - Number of characters to check

c     Outputs:
c        y        - Parsed array

      implicit none

      integer  n0,nl, i,ii,il, k

      character*1 x(nl),y(nl)

      do 100 ii = nl,1,-1
         if(x(ii).ne.' ') go to 110
100   continue

110   do 150 i = 1,nl
         y(i) = ' '
150   continue

      k = 0
      il= 0
      do 200 i = 1,ii
      if(x(i).eq.',') then
         k  = k + n0
         if(k.gt.nl-n0) go to 210
         il = k - i
      else
         y(i+il) = x(i)
      endif
200   continue
      k  = k + n0

210   call just(y,k,n0)
      do 220 i = n0,nl,n0
        if(y(i).eq.' ') y(i) = '0'
220   continue

      end
      subroutine addvec(a,b,nn)

c     Purpose: Add two vectors

c     Inputs:
c        a(*)     - Vector 1
c        b(*)     - Vector 2
c        nn       - Length of vectors

c     Outputs:
c        a(*)     - Sum of vector 1 and 2

      implicit none
      integer  n,nn
      real*8   a(*),b(*)

      do 100 n = 1,nn
        a(n) = a(n) + b(n)
100   continue

      end

      subroutine just(y,k,n0)

c     Purpose: Complete parser alignment of input data

c     Inputs:
c        y(*)        - Input string
c        k           - Length of input string
c        n0          - Field width for parsed data

c     Outputs:
c        y(*)        - Adjusted data to field widths of n0

      implicit    none
      integer     i,j,k,kl,l,n0,n1,n2
      character*1 y(k),yi,ze,ni,mi,pl,dt,sp

      data ze,ni,mi,pl,dt,sp/'0','9','-','+','.',' '/

      n1 = n0 - 1
      n2 = n1 - 1
      do 140 i = 1,k,n0
        do 100 j = i,i+n1
          if(y(j).ne.sp) go to 115
100     continue
        y(i+n1) = ze
115     if(y(i+n1).ne.sp) go to 140
        yi = y(i)
        if((yi.ge.ze.and.yi.le.ni).or.(yi.eq.mi).or.(yi.eq.pl)
     &                            .or.(yi.eq.dt)) then
          do 110 j = i+n2,i,-1
            if(y(j).ne.sp) go to 120
110       continue
120       kl = n1 + i - j
          do 130 l = j,i,-1
            y(l+kl) = y(l)
            y(l) = sp
130       continue
        endif
140   continue

      end

      subroutine elmlib(d,u,x,ix,t,s,p,i,j,k,iel,isw)

c     Purpose: Element library driver

c     Inputs:
c        d(*)      - Material set parameters
c        u(*)      - Element nodal solution parameters
c        x(*)      - Element nodal coordinates
c        ix(*)     - Element node numbers
c        t(*)      - Element nodal temperatures
c        i         - Number dof/node
c        j         - Spatial dimension of mesh
c        k         - Size of element arrays
c        iel       - Element type number
c        isw       - Switch for action to be taken by element routine

c     Outputs:
c        s(k,*)    - Element array
c        p(*)      - Element vector

      implicit  none

      integer   i, j, k, iel, isw
      real*8    d(*),p(*),s(*),u(*)
      real*8    x(*),t(*)
      integer   ix(*)

      integer         ior,iow
      common /iofile/ ior,iow

      if(isw.ge.3.and.isw.le.6) then
        call pconsd(p,k,0.0d0)
        call pconsd(s,k*k,0.0d0)
      endif
!      if(iel.eq.1) then
!        call elmt01(d,u,x,ix,t,s,p,i,j,k,isw)
!      elseif(iel.eq.2) then
!       call elmt02(d,u,x,ix,t,s,p,i,j,k,isw)
!      elseif(iel.eq.3) then
!        call elmt03(d,u,x,ix,t,s,p,i,j,k,isw)
!      elseif(iel.eq.4) then
!        call elmt04(d,u,x,ix,t,s,p,i,j,k,isw)
!      elseif(iel.eq.5) then
!        call elmt05(d,u,x,ix,t,s,p,i,j,k,isw)
!      elseif(iel.eq.6) then
!        call elmt06(d,u,x,ix,t,s,p,i,j,k,isw)

!      else
!        write(iow,4000) iel
!        if(ior.lt.0) write(*,4000) iel
!        stop
!      endif

4000  format('  **ERROR** Element type number',i3,' found.')

      end

      subroutine pconsd(v,nn,cc)

c     Purpose: Set real*8 array to constant value

c     Inputs:
c        nn        - Length of array
c        cc        - Value to assign

c     Outputs:
c        v(*)      - Array set to 'cc'

      implicit  none

      integer   n,nn
      real*8    v(nn),cc

      do 100 n = 1,nn
        v(n) = cc
100   continue

      end

      subroutine pconsi(iv,nn,ic)

c     Purpose: Set integer array to constant value

c     Inputs:
c        nn        - Length of array
c        ic        - Value to assign

c     Outputs:
c        iv(*)     - Array set to 'ic'

      implicit  none

      integer   n,nn,ic
      integer   iv(nn)

      do 100 n = 1,nn
        iv(n) = ic
100   continue

      end

      subroutine pconsr(v,nn,cr)

c     Purpose: Set real*4 array to constant value

c     Inputs:
c        nn        - Length of array
c        cr        - Value to assign

c     Outputs:
c        v(*)      - Array set to 'cr'

      implicit none

      integer  n,nn
      real     v(nn),cr
      do 100 n = 1,nn
        v(n) = cr
100   continue

      end

      subroutine pdisk(disk,files)

c     Purpose: Set disk name character string

c     Inputs:
c        disk        - Disk label for files (e.g., c for DOS hard)

c     Output:
c        files(*)    - File name with disk label added

      implicit    none

      integer     i
      character*1 disk,files(*)

      i = 1
      if((files(1).ne.' ') .and. (files(2).eq.':')) i = 3
      files(i) = disk

      end

      subroutine pend(subnam)

c     Purpose: End of file found

c     Inputs:
c        subnam    - Name of subroutine where EOF encountered

      implicit  none
      character subnam*6

      integer         ior,iow
      common /iofile/ ior,iow

      if(ior.gt.0) write(iow,4000) subnam
      if(ior.lt.0) write(  *,4000) subnam
      stop

4000  format(' ** ERROR in ',a6,' ** end of file encountered')

      end

      subroutine perror(subnam,yy)

c     Purpose: Read error encountered

c     Inputs:
c        subnam    - Name of subroutine where EOF encountered
c        yy        - String of data read

      implicit  none
      character subnam*6, yy*80

      integer         ior,iow
      common /iofile/ ior,iow

      if(ior.gt.0) then
        write(iow,4000) subnam,yy
        stop
      else
        write(*,4000) subnam
      endif

4000  format(' **ERROR in ',a6,'** Reinput last record:'/1x,a80)

      end

      subroutine pgauss(l,lint,r,z,w)

c     Purpose: Gauss points and weights for two dimensions

c     Inputs:
c        l         - Order of quadrature

c     Outputs:
c        lint      - Number of points
c        r(*),z(*) - Points
c        w(*)      - Weights

      implicit  none

      integer   i,l,lint
      integer   lr(9),lz(9),lw(9)
      real*8    r(*),z(*),w(*),g,h

      real*8          dm
      integer            n,ma,mct,iel,nel
      common /eldata/ dm,n,ma,mct,iel,nel

      data lr/-1,1,1,-1,0,1,0,-1,0/,lz/-1,-1,1,1,-1,0,1,0,0/
      data lw/4*25,4*40,64/

      lint = l*l

c     1x1 integration

      if(l.eq.1) then
        r(1) = 0.
        z(1) = 0.
        w(1) = 4.

c     2x2 integration

      elseif(l.eq.2) then
        g = 1.0/sqrt(3.d0)
        do 21 i = 1,4
          r(i) = g*lr(i)
          z(i) = g*lz(i)
          w(i) = 1.
21      continue

c     3x3 integration

      elseif(l.eq.3) then
        g = sqrt(0.60d0)
        h = 1.0/81.0d0
        do 31 i = 1,9
          r(i) = g*lr(i)
          z(i) = g*lz(i)
          w(i) = h*lw(i)
31      continue
      endif

      end

      subroutine phelp(wd,nwd,wrd,isw)

c     Purpose: Help file for macro command list

c     Inputs:
c        wd(*)     - List of FEAP command names
c        nwd       - Number of command names
c        wrd       - Request name for help
c        isw       - Switch: =1 for solution commands; otherwise mesh.

      implicit  none
      integer   nwd,isw
      character wd(nwd)*4,wrd*5

      integer         ior,iow
      common /iofile/ ior,iow

      if(ior.gt.0) return
      if(isw.eq.1) write(*,2000)
      if(isw.ne.1) write(*,2001) wrd
      write(*,2002) wd
      write(*,2003) wrd

2000  format(//' The following macro commands are available'//
     &         ' use of loop must terminate with a matching next'//
     &         ' multiple loop-next pairs may occur up to depth of 8')
2001  format(//' The following ',a5,'commands are available:')
2002  format(/8(3x,a4))
2003  format(/' Terminate ',a5,' execution with an "end" command.')

      end

      subroutine psetm(na,nl,typ,afl)

c     Purpose:  Allocate array storage pointer from blank common
c
c     Inputs:
c        nl        - length of array requested
c        typ       - type of array requested ('i', 'r', 'd')

c     Outputs:
c        na        - Pointer to first word in array
c        afl       - Flag, error if true

      implicit  none

      logical   afl
      integer   na,nl, np,ns
      real*8    amx
      character typ*1

      integer         iodr,iodw,ipd,ipr,ipi
      common /iofild/ iodr,iodw,ipd,ipr,ipi

      integer         ior,iow
      common /iofile/ ior,iow

      integer         maxm,ne
      common /psize/  maxm,ne

c     Set data management pointers for arrays

c     alignment for the blank common d(1),r(1),i(xx): xx = size
c     precisions: 'd' = ipd ; 'r' = ipr ; 'i' = ipi

c     N.B. ipd >= ipr >= ipi

      if( typ .eq. 'd' ) then
        np = ipd
        ns = 0
      elseif( typ .eq. 'r' ) then
        np = ipr
        ns = ipd/ipr
      elseif( typ .eq. 'i' ) then
        np = ipi
        ns = (ipd+ipr)/ipi
      endif
      na = ne
      ne = na + nl*np + mod(ipd - mod(nl*np,ipd),ipd)
      na   = (na + np - 1)/np - ns
      afl = .false.
      amx = maxm
      amx = ne/amx
      if(amx.gt.0.90) write(*,1001) ne,maxm,amx
      if(ne.le.maxm) return
      write(iow,1000) ne,maxm
      if(ior.lt.0) write(*,1000) ne,maxm
      stop

1000  format(2x,'**ERROR** Insufficient storage in blank common'/
     &      10x,'Required  =',i6/10x,'Available =',i6/)
1001  format('  **Memory warning** Used =',i6,' Avail =',i6,' % =',f6.3)

      end

      subroutine saxpb (a,b,x,n,c)

c     Purpose:  Scalar times vector plus vector

c     Inputs:
c        a(*)      - Vector to be multiplied by scalar
c        b(*)      - Vector to add
c        x         - Scalar value multiplying 'a'
c        n         - Length of vectors

c     Outputs:
c        c(*)      - Result of operation
      implicit none

      integer  k,n
      real*8   a(*),b(*),c(*),x

c    vector times scalar added to second vector 

      do 10 k=1,n
        c(k) = a(k)*x +b(k)
   10 continue

      end
      subroutine pctime(etime)

c     Purpose: Calls time routine for Micro Soft compilers
c              N.B. Replace "gettim" by appropriate timing routine 
c                   for each compiler

c     Outputs:
c        etime     - Character array with timing information

      implicit  none
      character etime*10
      integer   ihr,imin,isec,ihth

      call gettim (ihr,imin,isec,ihth)

      write(etime,2000) ihr,imin,isec
2000  format(i3,':',i2,':',i2)

      end

      subroutine pcdate(edate)

c     Purpose:  Put date on output file

c     Outputs:
c        edate     - character array with date information

      implicit  none
      character edate*12, mon(12)*3
      integer   iyr, imon, iday

      data mon/'Jan','Feb','Mar','Apr','May','Jun',
     &         'Jul','Aug','Sep','Oct','Nov','Dec'/

      edate = '    '
      call getdat( iyr, imon, iday)
      write(edate,2000) mon(imon),iday,iyr
 2000 format(a3,1x,i2,', ',i4)


      end

      logical function pcomp(a,b)

c     Purpose: Determine match between alphanumeric data:
c              N.B. inc = parameter for difference between 'a' and 'A'

c     Inputs:
c        a(*)      - 4-character array to test
c        b(*)      - 4-character comparison array

c     Outputs:
c        pcomp     - Flag, true if match made.  
c                    N.B.  converts all characters to lower case before
c                          test performed

      implicit  none
      integer   i,ia,ib,inc
      character a(4)*1,b(4)*1

      data inc /32/
      pcomp = .false.

      do 100 i = 1,4
         ia = ichar(a(i))
         ib = ichar(b(i))
         if(ia.ne.ib .and. ia+inc.ne.ib .and. ia.ne.ib+inc ) return
100   continue
      pcomp = .true.

      end

      subroutine pintio(y,n0)

c     Purpose:  Input control from current active unit - into a character
c               array for free format processing by 'acheck' into field
c               widths of 'n0'

c     Inputs:
c        n0       - Field width for formatting

c     Outputs:
c        y        - Character array formatted to field widths of 'n0'
c                   N.B. Internal I/O can be made to extract data

      implicit  none
      integer   n0
      character x*80,y*80

      integer         ior,iow
      common /iofile/ ior,iow

      if(ior.gt.0) read(ior,'(a)',err=100,end=100) x
      if(ior.lt.0) read(*,'(a)',err=100,end=100) x
      call acheck(x,y,n0,80)
      return

100   call perror('PINTIO',x)

      end

      subroutine pclear()

c     Purpose: Clear PC screen and home cursor on monitor

      implicit none

      write(*,2000) char(27)
2000  format(1x,a1,'[2J')

      end

