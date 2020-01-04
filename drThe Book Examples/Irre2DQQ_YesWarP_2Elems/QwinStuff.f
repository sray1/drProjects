
c     Purpose:  Graphics routines to use with MS Compilers

      subroutine pstart()

      use DFLIB

      implicit  none

      interface
        logical(4)  function initialsettings
        end function
      end interface

      type(qwinfo)       winfo
      type(windowconfig) myscreen

      integer            status
      integer*2          nxpix,nypix,nrows,ncols,numfonts

c     Open Child Console Window

      open (unit = 0, file = 'CON' )

c     Get Current Input Data Window Size

      status = getwindowconfig(myscreen)
      nxpix = 82*myscreen.numxpixels/100
      nypix = 82*myscreen.numypixels/100
      ncols =    myscreen.numtextcols
      nrows =    myscreen.numtextrows

      myscreen.numxpixels  = nxpix
      myscreen.numypixels  = nypix
      myscreen.numtextcols = ncols
      myscreen.numtextrows = nrows
      myscreen.numcolors   = -1
      myscreen.fontsize    = #0007000E
      myscreen.title       =
     &  "C u b i c - C u b i c  C a s e"C
      myscreen.bitsperpixel = -1
      status = setwindowconfig(myscreen)
      if(status.eq.0) status = setwindowconfig(myscreen)

c     Maximize window

      winfo.type = QWIN$SET
      winfo.x   =  0
      winfo.y   =  0
      winfo.w   =  nxpix
      winfo.h   =  nypix
      status     = setwsizeqq(0,winfo)

c     Set font for Helvetica Bold outputs vector mode

      numfonts=initializefonts()
      if (numfonts.le.0) print *,"INITIALIZEFONTS error"
      if (grstatus().ne.$GROK) print *,'INITIALIZEFONTS GRSTATUS error.'

      call setviewport(int2(0),int2(0),nxpix,nypix)

c     Establish initial text window size and location

      status = settextcolorrgb(#00FFFF)
      call settextwindow(int2(1),int2(1),int2(nrows),int2(80))
      status = displaycursor($gcursoron)
      status = setfont( 't''Arial''h12b' )

      end

      logical(4) function initialsettings ( )

      use       msflib

      implicit  none

      type(qwinfo) winfo
      integer      status

      save

c     Maximize Frame

      winfo.type = qwin$max
      status     = setwsizeqq(qwin$framewindow,winfo)

      initialsettings = .true.

      end

      subroutine pstop

      use        DFLIB

      integer*2  status

      status = setexitqq(QWIN$EXITNOPERSIST)

	  stop

      end

      integer*2 function vopnwk()
      use      DFLIB
      implicit integer*2 (a-z)

      type(windowconfig) myscreen

      integer            jfill,jplot
      logical                        lfil
      common    /instl2/ jfill,jplot,lfil

      common    /vgraph/ idxl,idyl

      integer            status

      save

      status = getwindowconfig(myscreen)
      ixln   = myscreen.numxpixels - 1
      iyln   = myscreen.numypixels - 1
      idxl   = 32640.0/(ixln+1) + 0.5
      idyl   = 22480.0/(iyln+1) + 0.5
      if(myscreen.numcolors .le. 4) then
        jfill = 1
      else
        jfill = 2
      endif
      call     clearscreen( $GCLEARSCREEN )
      vopnwk = 0

      end

      integer*2 function vclrwk()
      use      MSFLIB
      implicit integer*2 (a-z)

c     Clear workstation

      call     clearscreen( $GCLEARSCREEN )
      vclrwk = 0

      end

      integer*2 function vclswk()

      use      DFLIB

      implicit integer*2 (a-z)

      type(rccoord) s
      type(windowconfig) myscreen

      integer*2  ncols,nrows

c     Home cursor - text mode

      call     settextposition( 1 , 1 , s )
      vclswk = settextcursor ( #0607 )
c     vclswk = setvideomode  ( $TEXTC80 )
      vclswk = getwindowconfig(myscreen)
      ncols = myscreen.numtextcols
      nrows = myscreen.numtextrows
      call settextwindow( int2(1), int2(1), nrows, ncols )
      vclswk = displaycursor ( $GCURSORON )

      end

      integer*2 function vrqstr(len,echoh,ixy,cstr)

c     Input a single character

      integer*2   ixy
      integer     len,echoh
      character*1 cstr
      read(*,'(a1)') cstr
      vrqstr = 0

      end

      integer*2 function vslcol(it)
      use      DFLIB
      implicit integer*2 (a-z)

      integer*2 ipal(7)
      integer         jfill,jplot
      logical                     lfil
      common /instl2/ jfill,jplot,lfil

c     Set line color

      data ipal/ 15, 4, 2, 1, 14, 3, 5/
      if(it.gt.0 .and. it.le.7 ) then
        icll = ipal(it)
        if(jfill.lt.2) icll = 1
      else
        icll = 0
      endif
      vslcol = setcolor( icll )

      end

      integer*2 function vpline(npt,ixy)
      use      DFLIB
      implicit integer*2 (a-z)

      integer*2 ixy(2,*), ir1,ir2,irc
      integer   npt

      type(xycoord) xy
      common /vgraph/ idxl,idyl

c     Draw line

      ir1 = idxl
      ir2 = idyl
      irc = 22200
      call moveto( int2(ixy(1,1)/ir1), int2((irc - ixy (2,1))/ir2), xy )
      do 100 n = 2,npt
        vpline = lineto( int2(ixy(1,n)/ir1),int2((irc - ixy(2,n))/ir2) )
100   continue

      end

      integer*2 function vencur()
      implicit integer*2 (a-z)

c     Display cursor

      vencur = 0

      end

      subroutine dplot(x,y,ipen)

c     Purpose: Plot line routine

c     Inputs:
c        x         - X-normalized coordinate to plot
c        y         - Y-normalized coordinate to plot
c        ipen      - Pen action: = 2 draw; = 3 move

c     Outputs:
c        none

      implicit   none

      integer*2  status,vpline
      integer    ipen
      real*8     x,y

      integer*2       ixy
      common /pdata2/ ixy(4)

c     Pen command motions  (ipen = 2, pendown)

      ixy(3) = 22000*x
      ixy(4) = 22000*y
      if(ipen.eq.2) then
        status = vpline(2,ixy)
      endif
      ixy(1) = ixy(3)
      ixy(2) = ixy(4)

      end
