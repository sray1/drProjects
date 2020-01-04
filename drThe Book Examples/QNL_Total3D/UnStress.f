c---------------------------------------------------------------------+
c                                                                     |
c......      UnStress    - -  A Finite Element Analysis Program for   |
c                                     Personal Computers              |
c                                                                     |
c                                                                     |
c.... A (PC)  Finite Element Analysis Program for solution of general |
c.... problem classes using the finite element method.   Problem size |
c.... is controlled by the dimension of blank common and value of max |
c.... set below.                                                      |
c                                                                     |
c.... Programmed by:                                                  |
c                Debabrata Ray                                        |
c                Institute for Dynamic Response,Inc                   |
c                Oakland, California 94618                            |
c                                                                     |
c         Uses: Fortran 90 Compiler System                            |
c                                                                     |
c                Use Frontal Solution system in file: pfsolv.for      |
c                  or                                                 |
c                Use Skyline Solution system in file: pasolv.for      |
c                                                                     |
c         Uses: Compaq (R) Fortran Version 6.6                        |
c               Graphics interfaced using file: pcfor5.for            |
c                                                                     |
c.... (C) Copyright -  iDRiDrRay  -  1990 to 2002  -                  |
c                                                                     |
c---------------------------------------------------------------------+
      program         UnStress

      implicit        none

      integer         numnp,numel,nummat,nen,neq
      common /cdata/  numnp,numel,nummat,nen,neq

      integer         iodr,iodw,ipd,ipr,ipi
      common /iofild/ iodr,iodw,ipd,ipr,ipi

      integer         maxm,ne
      common /psize/  maxm,ne

      character       tfile*12
      common /temfl1/ tfile(6)

      character      versn*12
      common /vdata/ versn(3)

c     Parameters control program capacity:
c                    mmax  = mesh size
c                    maxa  = equation size (in several routines)

      integer        mmax
      parameter     (mmax = 64000)

      integer        m
      common         m(mmax)

c     Set version data

      versn(1) = '   pcUnStress '
      versn(2) = '   -- 1.00 -- '
      versn(3) = '  01/23/02    '

c     Reserve memory size; set default input/output units
c         N.B. maxm is defined in number of INTEGER words.

      maxm = mmax
      ne   = 1
      iodr = 15
      iodw = 16

c     Set precision values: ipd = double; ipr = real; ipi = integer
c         N.B. Precisions are set as multiples of the integer value.
c
c           a. For short integers (integer*2) the values are:
c                  ipd = 4, ipr = 2, ipi = 1
c
c           b. For normal integer (integer*4) the values are:
c                  ipd = 2, ipr = 1, ipi = 1
c
c     integer*2

c     ipd  = 4
c     ipr  = 2

c     integer

      ipd  = 2
      ipr  = 1
      ipi  = 1

c     Start system if necessary

!      call pstart

c     Open files; erase scratch files if they exist; start execution

      call filnam
      call pdefil(tfile,1,4)
      call pcontr

c     Close input and output files; destroy temporary disk files

      close(iodr)
      close(iodw)

      call pdefil(tfile,1,4)

      call pstop

      end

      subroutine pdefil(tfile,n1,n2)

c     Purpose: Destroy temporary files used to solve problems

c     Inputs:
c       tfile(*)  - Filenames to delete
c       n1        - First number of array to delete
c       n2        - Last  number of array to delete

      implicit   none

      logical    lfil
      integer    n,n1,n2
      character  tfile(n2)*12

      do 100 n = n1,n2
        inquire(file=tfile(n),exist=lfil)
        if(lfil) then
          open (4,file=tfile(n),status='old')
          close(4,status='delete')
        endif
100   continue

c     Frontal files only

!????     call delfrt()

      end

      subroutine filnam()

c     Purpose:  Set filenames for execution

      implicit  none

      logical   linp,lout,lres,lsav
      integer   i,ix,iop,irs,isv,ifill
      character y*1,disknm*1,pdisknm*1,wd(2)*6
      character finp*12,fout*12,fres*12,fsav*12
      character pinp*12,pout*12,pres*12,psav*12,edate*12

      integer         jfill,jplot
      logical                     lfil
      common /instl2/ jfill,jplot,lfil

      integer         iodr,iodw,ipd,ipr,ipi
      common /iofild/ iodr,iodw,ipd,ipr,ipi

      character       tfile*12
      common /temfl1/ tfile(6)

      character      versn*12
      common /vdata/ versn(3)

      data wd/'new   ','exists'/

c     output version data to screen

      call pcdate(edate)
      write(*,2000) versn,edate

c     look to see if any problem has been run

      inquire(file='UnStress.NAM',exist=lfil)
      if(lfil) then
         open(3,file='UnStress.NAM',status='old')
         read(3,1000) pinp,pout,pres,psav,disknm,jfill
         finp = pinp
         fout = pout
         fres = pres
         fsav = psav
         go to 200
      else

c     default installation parameters

         pinp   = 'NONE'
         disknm = 'c'
         jfill  = 2

c     set scratch disk name

         write(*,2007) disknm
         read (*,1001) pdisknm
         if(pdisknm.ne.' ') disknm = pdisknm

c     set graphics monitor type

         write(*,2008) jfill
         read (*,1002) ifill
         if(ifill.ne.0) jfill = ifill
      endif

c     name file for input data

100   write(*,2000) versn,edate
      assign 1 to ix
1     write(*,2001) pinp
      read (*,1000,err=900) finp
      if(finp.eq.' ') finp = pinp

c     check if the input files exists

      inquire(file=finp,exist=linp)
      if(.not.linp) then
         write(*,3000)
         go to 1
      else
         pout = finp
         pres = finp
         psav = finp
         call pdisk('O',pout)
         call pdisk('R',pres)
         call pdisk('S',psav)
      endif
      pinp = finp

c     name file for output data

      assign 2 to ix
2     write(*,2002) pout
      read (*,1000,err=900) fout
      if(fout.eq.' ') fout = pout
      pout = fout

c     name file for restart read data

      assign 3 to ix
3     write(*,2003) pres
      read (*,1000,err=900) fres
      if(fres.eq.' ') fres = pres
      pres = fres

c     name file for restart save data

      assign 4 to ix
4     write(*,2004) psav
      read (*,1000,err=900) fsav
      if(fsav.eq.' ') fsav = psav
      psav = fsav

c     check file status and input if necessary

200   inquire(file=finp,exist=linp)
      if(.not.linp) go to 100
      inquire(file=fout,exist=lout)
      iop = 1
      if(lout) iop = 2
      inquire(file=fres,exist=lres)
      irs = 1
      if(lres) irs = 2
      inquire(file=fsav,exist=lsav)
      isv = 1
      if(lsav) isv = 2
      write(*,2005) finp,wd(2),fout,wd(iop),fres,wd(irs),fsav,wd(isv)
      read(*,1001) y
      if(y.eq.'s' .or.  y.eq.'S') call pstop
      if(y.ne.'y' .and. y.ne.'Y') go to 100

c     save a copy of the current filenames

      if(.not.lfil) open(3,file='UnStress.NAM',status='new')
      rewind 3
      write(3,1000) finp,fout,fres,fsav,disknm,jfill
      close(3)

c     Erase the output file if it exists

      if(lout) then
        open(3,file=fout,status='old')
        close(3,status='delete')
      endif
      write(*,2006)

c     Open the files for input and output

      open(unit=iodr,file=finp,status='old')
      open(unit=iodw,file=fout,status='new')

c     Set the scratch disk names and locations

      tfile(1) = ' :FRNT.TEM'
      tfile(2) = ' :HIST.TEM'
      tfile(3) = ' :MESH.TEM'
      tfile(4) = ' :STRE.TEM'
      tfile(5) = fres
      tfile(6) = fsav
      do 300 i = 1,4
        call pdisk(disknm,tfile(i))
300   continue 
      return

c     Error trap 

900   write(*,3001)
      go to ix

c     Format statements

1000  format(4a12,a1,i2)
1001  format(a1)
1002  format(i1)
2000  format(////6x,
     &' F I N I T E   E L E M E N T   A N A L Y S I S   P R O G R A M'//
     & 13x,'VERSION: ',3a12/34x,a12)
2001  format(/13x,'I n p u t    F i l e n a m e s'//
     &       15x,'Input data   (default: ',a12,') :',$)
2002  format(15x,'Output data  (default: ',a12,') :',$)
2003  format(15x,'Restart read (default: ',a12,') :',$)
2004  format(15x,'Restart save (default: ',a12,') :',$)
2005  format( /13x,'Files are set as follows :'//
     &  32x,'Filename',9x,'Status'/
     &  15x,'Input    (read ) : ',a12,5x,a6/
     &  15x,'Output   (write) : ',a12,5x,a6/
     &  15x,'Restart  (read ) : ',a12,5x,a6/
     &  15x,'Restart  (write) : ',a12,5x,a6//
     &  13x,'Caution, existing write files will be overwritten.'//
     &  13x,'Are filenames correct? ( y or n, s=stop) : ',$)
2006  format(/12x,'R U N N I N G   UnStress   P R O B L E M   N O W')
2007  format(/13x,'I N S T A L L A T I O N   P A R A M E T E R S'//
     &       15x,'Disk Name For Scratch Files:'/
     &       17x,'             (default = ',a1,9x,') :',$)
2008  format(15x,'Set: Graphics Terminal Type:'/
     &       17x,'1=CGA; 2=EGA (default = ',i2,8x,') :',$)
3000  format(' *** ERROR - - Specified input file does not exist')
3001  format(' *** ERROR on read *** reinput')

      end

      subroutine pcontr()

c     Control program for feap

      implicit  none
      logical   prt,tfl,pcomp
      integer   i,iii, n14,nad
      character titl(20)*4,yyy*80

      character      head*4
      common /bdata/ head(20)

      integer        numnp,numel,nummat,nen,neq
      common /cdata/ numnp,numel,nummat,nen,neq

      integer         ior,iow
      common /iofile/ ior,iow

      integer         iodr,iodw,ipd,ipr,ipi
      common /iofild/ iodr,iodw,ipd,ipr,ipi

      integer        nn,n0,n1,n2,n3,n4,n5,n6,n7,n8,n9,n10,n11,n12,n13
      common /mdata/ nn,n0,n1,n2,n3,n4,n5,n6,n7,n8,n9,n10,n11,n12,n13

      integer        n11a,n11b,n11c,ia
      common /mdat2/ n11a,n11b,n11c,ia(2,11)

      integer        ndf,ndm,nen1,nst
      common /sdata/ ndf,ndm,nen1,nst

      character      versn*12
      common /vdata/ versn(3)

      real*8 d
      real        r
      integer          m
      common d(1),r(1),m(1000)

c     Set parameters for rotation dof

      do 4 i = 1,4
        ia(1,i) = 1
        ia(2,i) = 2
4     continue

c     Set files back to default values

1     ior = iodr
      iow = iodw

c     Read a card and compare first 4 columns with macro list

      read(ior,1000,err=600,end=700) (titl(i),i=1,20)
      if(pcomp(titl(1),'unst')) go to 100
      if(pcomp(titl(1),'inte')) go to 200
      if(pcomp(titl(1),'macr')) go to 300
      if(pcomp(titl(1),'stop')) return
      go to 1

c     Read and print control information

100   do 101 i = 1,20
101   head(i) = titl(i)
      call pintio(yyy,10)
      read(yyy,1001,err=600) numnp,numel,nummat,ndm,ndf,nen,nad
      write(iow,2000) head,versn,numnp,numel,nummat,ndm,ndf,nen,nad

c     Set pointers for allocation of data arrays

      nen1 = nen + 4
      nst  = nen*ndf + nad
      call psetm(nn, numnp*max(ndm,ndf,2),'d',tfl)
      call psetm(nn, 5*nen*ndf,        'd',tfl)
      call psetm(n0, nen*ndm,          'd',tfl)
      call psetm(n1, nen,              'd',tfl)
      call psetm(n2, nst,              'i',tfl)
      call psetm(n3, nst,              'd',tfl)
      call psetm(n4, nst*nst,          'd',tfl)
      call psetm(n5, nummat*9,         'i',tfl)
      call psetm(n6, nummat*18,        'd',tfl)
      call psetm(n7, ndf*numnp,        'i',tfl)
      call psetm(n8, ndm*numnp,        'd',tfl)
      call psetm(n9, nen1*numel,       'i',tfl)
      call psetm(n10,numnp*ndf,        'd',tfl)
      call psetm(n11,numnp,            'd',tfl)
      call psetm(n11a,nen,             'd',tfl)
      call psetm(n11b,numnp,           'd',tfl)
      call psetm(n11c,max(numel,nst),  'i',tfl)
      call psetm(n12,ndf*numnp,        'i',tfl)

c     Call mesh input subroutine to read and print all mesh data

      iii = 0
      prt = .true.
!????      call pmesh(m(n2),m(n5),d(n6),m(n7),d(n8),m(n9),d(n10),d(n11),ndf,
!????     &   ndm,nen1,iii,prt)
      go to 1

c     Set files for interactive macro execution

200   ior = -iodr

c     Compute profile

300   continue
!???? call profil(m(n12),m(n11c),m(n7),m(n9),ndf,nen1)
      
      call psetm(n13,numnp*ndf,   'd',tfl)
      call psetm(n14,3*numnp*ndf, 'd',tfl)

c     Set up stress history addresses

!????      call sethis(m(n5),m(n9),m(n11c),ipd,nen,nen1,numel)

c     Zero the initial force and solution vectors

      call pconsd(d(n13),  ndf*numnp,0.0d0)
      call pconsd(d(n14),3*ndf*numnp,0.0d0)

c     Macro module for establishing solution algorithm

!????      call pmacr(m(n2),d(n4),m(n5),d(n6),m(n7),d(n8),m(n9),d(n10),
!????     &           d(n11),m(n12),d(n13),d(n14),d(1),ndf,ndm,nen1,nst,prt)
      go to 1

600   call perror('PCONTR',yyy)
      return

700   call pend('pcontr')

c     Input/output formats

1000  format(20a4)
1001  format(8i10)
2000  format(1x,20a4//5x,'VERSION :',3a12//
     &  5x,'Number of nodal points       =',i6/
     &  5x,'Number of elements           =',i6/
     &  5x,'Number of material sets      =',i6/
     &  5x,'Dimension of coordinate space=',i6/
     &  5x,'Degree of freedoms/node      =',i6/
     &  5x,'Nodes per element (maximum)  =',i6/
     &  5x,'Extra d.o.f. to element      =',i6)

      end

      subroutine pltstr(dt,st,numnp)

c     Stress projections computed by dividing by 'lumped' weightings

      implicit none
      integer  ii,j,numnp
      real*8   dt(numnp),st(numnp,*)
      real*8   sig(6)

      real*8         eerror,elproj,ecproj,efem,enerr,ebar
      common /errind/eerror,elproj,ecproj,efem,enerr,ebar

      elproj = 0.0
      do 100 ii = 1,numnp
        if(dt(ii).ne.0.0) then
          do 200 j = 1,4
            sig(j)   = st(ii,j)/dt(ii)
            elproj   = elproj + sig(j)*st(ii,j)
            st(ii,j) = sig(j)
200       continue

c         Compute the principal stress values

!????          call pstres(sig,sig(4),sig(5),sig(6))
          if(st(ii,5).ne.0.0) then
            dt(ii) = st(ii,5)/dt(ii)
          else
            dt(ii) = sig(6)
          endif
          st(ii,5) = sig(4)
          st(ii,6) = sig(5)
          st(ii,7) = (sig(4)-sig(5))/2.0
        endif
100   continue

      end

      subroutine prthed(iow)

c     Purpose: Output a header to printed outputs

c     Inputs:
c        iow      - Logical unit number for outputs

      implicit      none

      integer       iow

      character     head*4
      common/bdata/ head(20)

      write(iow,2000) head

2000  format(/1x,20a4//1x)

      end
