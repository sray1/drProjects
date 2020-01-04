      subroutine         FileStuff()

      implicit        none

      character       tfile*12
      common /temfl1/ tfile(6)

      integer         iodr,iodw,ipd,ipr,ipi
      common /iofild/ iodr,iodw,ipd,ipr,ipi

      character       tfile*12
      common /temfl1/ tfile(6)

!
!     default input/output units
!     

      iodr = 15
      iodw = 16

c     Start system if necessary

      call pstart

c     Open files; erase scratch files if they exist; start execution

      call filnam
      call pdefil(tfile,1,4)

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

      inquire(file='FEAP.NAM',exist=lfil)
      if(lfil) then
         open(3,file='FEAP.NAM',status='old')
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

      if(.not.lfil) open(3,file='FEAP.NAM',status='new')
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
     &' QUAD CUBIC-CUBIC CASE '//
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
2006  format(/12x,'R U N N I N G   P R O B L E M   N O W')
2007  format(/13x,'I N S T A L L A T I O N   P A R A M E T E R S'//
     &       15x,'Disk Name For Scratch Files:'/
     &       17x,'             (default = ',a1,9x,') :',$)
2008  format(15x,'Set: Graphics Terminal Type:'/
     &       17x,'1=CGA; 2=EGA (default = ',i2,8x,') :',$)
3000  format(' *** ERROR - - Specified input file does not exist')
3001  format(' *** ERROR on read *** reinput')

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
