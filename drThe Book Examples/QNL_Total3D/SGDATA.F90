!**********************************************************************
!
! SciGraph -- Scientific Graphs for Compaq Visual Fortran
!
!

!======================================================================
!
!   DESCRIPTION
!       Contains the type definitions and parameters (constants) used in the
!             SciGraph graphing library.
!

MODULE SGDATA

      IMPLICIT NONE

      STRUCTURE /GraphSettings/
          CHARACTER*40    title           ! title for graph
          INTEGER         titleFont       ! title font: $FTCOUR,$FTCOURSM,...
          INTEGER         titleColor      ! title color (0..numcolors)
          CHARACTER*40    title2          ! second title for graph
          INTEGER         title2Font      ! second title font: $FTCOUR,$FTCOURSM,...
          INTEGER         title2Color     ! second title color (0..numcolors)
          INTEGER         graphType       ! what kind of graph: $GTBAR,$GTLINE,...
          INTEGER         graphColor      ! what color for graph border
          INTEGER         graphBgColor    ! what color for graph background
          INTEGER         x1,y1,x2,y2     ! physical screen boundaries for graph
          LOGICAL         setGraphMode    ! if SciGraph should set the graphics mode
          INTEGER         sgprivate(8)    ! data PRIVATE to SciGraph: don't change
      END STRUCTURE

      STRUCTURE /PrivateGraphSettings/
          CHARACTER*40    title           ! title for graph
          INTEGER         titleFont       ! title font: $FTCOUR,$FTCOURSM,...
          INTEGER         titleColor      ! title color (0..numcolors)
          CHARACTER*40    title2          ! second title for graph
          INTEGER         title2Font      ! second title font: $FTCOUR,$FTCOURSM,...
          INTEGER         title2Color     ! second title color (0..numcolors)
          INTEGER         graphType       ! what kind of graph: $GTBAR,$GTLINE,...
          INTEGER         graphColor      ! what color for graph border
          INTEGER         graphBgColor    ! what color for graph background
          INTEGER         x1,y1,x2,y2     ! physical screen boundaries for graph
          LOGICAL         setGraphMode    ! if SciGraph should set the graphics mode
!   The following 3 will only get set if the user calls the Get*Default routines
          INTEGER         numSetsReq      ! number of data settings requested (for auto color)
          INTEGER         numXAxesReq     ! number of X axes requested
          INTEGER         numYAxesReq     ! number of Y axes requested
!   The following 4 will always get set by the PlotGraph and Plot*Data routines
          INTEGER         didPlotGraph    ! 1 if did plot graph successfully, else 0
          INTEGER         numSets         ! number of data sets to plot
          INTEGER         numSetsDone     ! number of data sets plotted so far
      END STRUCTURE

      REAL(8), PARAMETER :: $WXMIN           = 0.0D0
      REAL(8), PARAMETER :: $WXMAX           = 10240.0D0
      REAL(8), PARAMETER :: $WX              = $WXMAX-$WXMIN
      REAL(8), PARAMETER :: $WXC             = $WXMIN+$WX/2.0D0
      REAL(8), PARAMETER :: $WYMIN           = 0.0D0
      REAL(8), PARAMETER :: $WYMAX           = 7680.0D0
      REAL(8), PARAMETER :: $WY              = $WYMAX-$WYMIN
      REAL(8), PARAMETER :: $WYC             = $WYMIN+$WY/2.0D0
      REAL(8), PARAMETER :: $GXMIN           = 1300.0D0
      REAL(8), PARAMETER :: $GXMAX           = 8940.0D0
      REAL(8), PARAMETER :: $GX              = $GXMAX-$GXMIN
      REAL(8), PARAMETER :: $GXC             = $GXMIN+$GX/2.0D0
      REAL(8), PARAMETER :: $GYMIN           = 1248.0D0
      REAL(8), PARAMETER :: $GYMAX           = 6032.0D0
      REAL(8), PARAMETER :: $GY              = $GYMAX-$GYMIN
      REAL(8), PARAMETER :: $GYC             = $GYMIN+$GY/2.0D0
      REAL(8), PARAMETER :: $PGR             = 2560.0

      STRUCTURE /DataSettings/
          CHARACTER*20    title           ! title for data range (legend)
          INTEGER         titleFont       ! which font: $FTCOUR,$FTCOURSM,...
          INTEGER         titleColor      ! title color (0..numcolors)

          INTEGER         markerType      ! marker style: $MKNONE,$MKSQUARE,...
          INTEGER         markerColor     ! marker color (0..numcolors)
          INTEGER         lineType        ! line type: $LTNONE, $LTSOLID,...
          INTEGER         lineColor       ! line color
          INTEGER         barType         ! bar type: $BTNONE,$BTSOLID,..
          INTEGER         barColor        ! bar color
          INTEGER         errorbarType    ! error bar style: $EBNONE, $EBTHIN,...
          INTEGER         errorbarColor   ! error bar color

          INTEGER         dataType        ! #,# or text,# ?  $DTTEXT, $DTNUM
          LOGICAL         xFirst          ! x stored before y in a given row
          INTEGER         numPoints       ! number of data points or labels (bar/line)
          INTEGER         numElements     ! number of elements per data point (2/3)

          REAL*8          xLowVal         ! x values>= this value
          REAL*8          xHighVal        ! x values<= this value

          REAL*8          yLowVal         ! y values>= this value
          REAL*8          yHighVal        ! y values<= this value
      END STRUCTURE


      STRUCTURE /AxisSettings/
          CHARACTER*25    title           ! title for axis
          INTEGER         titleFont       ! which font: $FTCOUR,$FTCOURSM,...
          INTEGER         titleColor      ! title color (0..numcolors)

          INTEGER         axisFont        ! what font for the axis numbers/labels
          LOGICAL         axisFontRotated ! .TRUE. if axis numbers rotated (y only)
          INTEGER         axisPos         ! where to put axis: $APBOTTOM,$APTOP,...
          INTEGER         axisType        ! what kind of axis: $ATX, $ATY,...
          INTEGER         axisColor       ! what color the line of the axis is
          INTEGER         axisFunc        ! axis function: $AFNONE,$AFLOG10,...
          LOGICAL         axisCW          ! if polar axis is clockwise
          REAL*8          lowVal          ! axis starts at this value
          REAL*8          highVal         ! axis ends at this value
          REAL*8          increment       ! axis increment for major ticks
          INTEGER         numDigits       ! number of decimal digits to print

          INTEGER         tickType        ! tick type: $TTNONE,$TTINSIDE,...
          INTEGER         tickColor       ! color of the major (big) ticks
          INTEGER         minorTickColor  ! color of the minor (small) ticks
          INTEGER         tickRatio       ! number of minor ticks from one major
                                           !  tick to the next:
                                           !  1= all major ticks(||||),
                                           !  2=(|.|), 3=(|..|),4= |...|, etc
          INTEGER         gridStyle       ! grid style: $GSNONE,$GSMAJOR,...
          INTEGER         gridLineType    ! grid line type: $LTNONE, $LTSOLID,...
          INTEGER         gridColor       ! color of grid lines
      END STRUCTURE

!   Include the actual structure definitions which are stored in separate files
!   Logical   constants for Fortran type checking
!      LOGICAL   $TRUE2,$FALSE2
!      PARAMETER ($TRUE2           =.TRUE.)
!      PARAMETER ($FALSE2          =.FALSE.)

!   Numeric constants need in SciGraph
      REAL(8), PARAMETER :: $PI          = 3.141592653589793D0
      REAL(8), PARAMETER :: $EPREAL4     = 1.192092895507813D-07
      REAL(8), PARAMETER :: $EPREAL8     = 2.220446049250313D-016

!   Color indices for default 16 color palette
      INTEGER, PARAMETER :: $CIBLACK         = 0
      INTEGER, PARAMETER :: $CIBLUE          = 1
      INTEGER, PARAMETER :: $CIGREEN         = 2
      INTEGER, PARAMETER :: $CICYAN          = 3
      INTEGER, PARAMETER :: $CIRED           = 4
      INTEGER, PARAMETER :: $CIMAGENTA       = 5
      INTEGER, PARAMETER :: $CIBROWN         = 6
      INTEGER, PARAMETER :: $CIWHITE         = 7
      INTEGER, PARAMETER :: $CIGRAY          = 8
      INTEGER, PARAMETER :: $CILIGHTBLUE     = 9
      INTEGER, PARAMETER :: $CILIGHTGREEN    = 10
      INTEGER, PARAMETER :: $CILIGHTCYAN     = 11
      INTEGER, PARAMETER :: $CILIGHTRED      = 12
      INTEGER, PARAMETER :: $CILIGHTMAGENTA  = 13
      INTEGER, PARAMETER :: $CIYELLOW        = 14
      INTEGER, PARAMETER :: $CIBRIGHTWHITE   = 15

!   Graph types for use in graph settings structure
      INTEGER, PARAMETER :: $GTBAR           = 1     ! bar graph (x=text labels, y=num)
      INTEGER, PARAMETER :: $GTLINE          = 2     ! line graph (x=text labels, y=num)
      INTEGER, PARAMETER :: $GTLINEWERRBAR   = 3     ! line graph with error bars (same)
      INTEGER, PARAMETER :: $GTXY            = 4     ! xy graph (x=num, y=num)
      INTEGER, PARAMETER :: $GTXYWERRBAR     = 5     ! xy graph with error bars
      INTEGER, PARAMETER :: $GTPOLAR         = 6     ! polar coordinate graph
      INTEGER, PARAMETER :: $GTCOUNT         = 6     ! how many total GTs

!   Font types for use in settings structures
      INTEGER, PARAMETER :: $FTCOUR          = 1     ! courier font
      INTEGER, PARAMETER :: $FTCOURSM        = 2     ! small courier font
      INTEGER, PARAMETER :: $FTTROMAN        = 3     ! roman font
      INTEGER, PARAMETER :: $FTTROMANSM      = 4     ! small roman font
      INTEGER, PARAMETER :: $FTSANSSERIF     = 5     ! SANSSERIF font
      INTEGER, PARAMETER :: $FTSANSSERIFSM   = 6     ! small SANSSERIF font
      INTEGER, PARAMETER :: $FTCOUNT         = 6     ! how many total FTs

      INTEGER, PARAMETER :: $FTDEF           = 1000  ! default font

!   Font "values"
      CHARACTER*50, PARAMETER :: $FVCOUR      = "t'Courier New'h20w10b"
      CHARACTER*50, PARAMETER :: $FVCOURSM    = "t'Courier New'h20w9b"
      CHARACTER*50, PARAMETER :: $FVTROMAN    = "t'Times New Roman'h26w13b"
      CHARACTER*50, PARAMETER :: $FVTROMANSM  = "t'Times New Roman'h16w8b"
      CHARACTER*50, PARAMETER :: $FVSANSSERIF = "t'MS Sans Serif'h24w12b"
      CHARACTER*50, PARAMETER :: $FVSANSSERIFSM = "t'MS Sans Serif'h12w6b"
      CHARACTER*50, PARAMETER :: $FVDEF       = $FVCOUR


!   Data types for use in data settings structure
      INTEGER, PARAMETER :: $DTNUM           = 1     ! data is numeric,numeric
      INTEGER, PARAMETER :: $DTTEXT          = 2     ! data is text,numeric
      INTEGER, PARAMETER :: $DTCOUNT         = 2     ! how many total DTs


!   Marker types for use in data settings structure
      INTEGER, PARAMETER :: $MKNONE          = 0     ! no markers at points
      INTEGER, PARAMETER :: $MKSQUARE        = 1     ! draw squares at points
      INTEGER, PARAMETER :: $MKTRIANGLE      = 2     ! triangles
      INTEGER, PARAMETER :: $MKDIAMOND       = 3     ! diamonds
      INTEGER, PARAMETER :: $MKCIRCLE        = 4     ! circles
      INTEGER, PARAMETER :: $MKPLUS          = 5     ! plus signs
      INTEGER, PARAMETER :: $MKX             = 6     ! X marks
      INTEGER, PARAMETER :: $MKFISQUARE      = 7     ! filled in squares
      INTEGER, PARAMETER :: $MKFITRIANGLE    = 8     ! filled triangles
      INTEGER, PARAMETER :: $MKFIDIAMOND     = 9     ! filled diamonds
      INTEGER, PARAMETER :: $MKFICIRCLE      = 10    ! filled circles
      INTEGER, PARAMETER :: $MKCOUNT         = 10    ! how many total MKs

!   Line types for use in settings structures
      INTEGER, PARAMETER :: $LTNONE          = 0     ! no lines between points
      INTEGER, PARAMETER :: $LTSOLID         = 1     ! draw solid lines between points
      INTEGER, PARAMETER :: $LTDASH          = 2     ! dash
      INTEGER, PARAMETER :: $LTDASHDOT       = 3     ! dash-dot
      INTEGER, PARAMETER :: $LTDASHDOTDOT    = 4     ! dash-dot-dot
      INTEGER, PARAMETER :: $LTDOT           = 5     ! dot
      INTEGER, PARAMETER :: $LTTHICKSOLID    = 6     ! thick solid lines
      INTEGER, PARAMETER :: $LTTHICKDASH     = 7     ! thick dash
      INTEGER, PARAMETER :: $LTTHICKDASHDOT  = 8     ! thick dash-dot
      INTEGER, PARAMETER :: $LTTHICKDASHDOTDOT= 9    ! thick dash-dot-dot
      INTEGER, PARAMETER :: $LTTHICKDOT      = 10    ! thick dot
      INTEGER, PARAMETER :: $LTCOUNT         = 10    ! how many total LTs

      INTEGER, PARAMETER :: $LTDEF           = 1000  ! default line type

!   Line "values"
$IF DEFINED(WASDEBUG)         ! don't want to get flagged for range errors
$UNDEFINE WASDEBUG
$ENDIF
$IF DEFINED($DEBUG)
$DEFINE WASDEBUG
$ENDIF
!$NODEBUG
      INTEGER, PARAMETER :: $LVNONE          = 0     ! no lines between points
      INTEGER, PARAMETER :: $LVSOLID         = #FFFF ! draw solid lines between points
      INTEGER, PARAMETER :: $LVDASH          = #EEEE ! dash
      INTEGER, PARAMETER :: $LVDASHDOT       = #ECEC ! dash-dot
      INTEGER, PARAMETER :: $LVDASHDOTDOT    = #ECCC ! dash-dot-dot
      INTEGER, PARAMETER :: $LVDOT           = #AAAA ! dot
      INTEGER, PARAMETER :: $LVTHICKSOLID    = #FFFF ! thick solid lines
      INTEGER, PARAMETER :: $LVTHICKDASH     = #EEEE ! thick dash
      INTEGER, PARAMETER :: $LVTHICKDASHDOT  = #ECEC ! thick dash-dot
      INTEGER, PARAMETER :: $LVTHICKDASHDOTDOT= #ECCC! thick dash-dot-dot
      INTEGER, PARAMETER :: $LVTHICKDOT      = #AAAA ! thick dot

      INTEGER, PARAMETER :: $LVDEF           = $LVSOLID ! default line type
$IF DEFINED(WASDEBG)
$DEBUG
$ENDIF

!   Bar types for use in data settings structures.  $BV* are in SCIGRAPH.FOR
!     function SciDrawBar
      INTEGER, PARAMETER :: $BTNONE          = 0     ! don't draw bars
      INTEGER, PARAMETER :: $BTEMPTY         = 1     ! draw outline of bars
      INTEGER, PARAMETER :: $BTSOLID         = 2     ! draw bars filled in with solid color
      INTEGER, PARAMETER :: $BTHASHLEFT      = 3     ! left hashing  (/ /)
      INTEGER, PARAMETER :: $BTHASHRIGHT     = 4     ! right hashing  (\ \)
      INTEGER, PARAMETER :: $BTHEAVYHASHLEFT = 5     ! heavy left hashing  (// //)
      INTEGER, PARAMETER :: $BTHEAVYHASHRIGHT= 6     ! heavy right hashing  (\\ \\)
      INTEGER, PARAMETER :: $BTCOUNT         = 6     ! how many total BTs

!   Error bar types for use in data settings structures
      INTEGER, PARAMETER :: $EBNONE          = 0     ! no error bars
      INTEGER, PARAMETER :: $EBTHIN          = 1     ! thin y error bars
      INTEGER, PARAMETER :: $EBTHICK         = 2     ! thick y error bars

!   Axis Functions for use in axis settings
      INTEGER, PARAMETER :: $AFNONE          = 0     ! no transform function: leave data as is
      INTEGER, PARAMETER :: $AFLINEAR        = 0     ! no transform function: leave data as is
      INTEGER, PARAMETER :: $AFLOG10         = 1     ! take log base 10 of each data point
      INTEGER, PARAMETER :: $AFLOG           = 2     ! take log base e (natural log)
      INTEGER, PARAMETER :: $AFLOG2          = 3     ! take log base 2
      INTEGER, PARAMETER :: $AFCOUNT         = 3     ! how many total AFs

!   Axis Positions for use in axis setting structure
      INTEGER, PARAMETER :: $APNONE          = 0     ! don't display an axis
      INTEGER, PARAMETER :: $APBOTTOM        = 1     ! display axis at bottom
      INTEGER, PARAMETER :: $APTOP           = 2     ! top
      INTEGER, PARAMETER :: $APLEFT          = 3     ! left
      INTEGER, PARAMETER :: $APRIGHT         = 4     ! right
      INTEGER, PARAMETER :: $APCOUNT         = 4     ! how many total APs

!   Axis Types for use in axis settings structure
      INTEGER, PARAMETER :: $ATX             = 0     ! x-axis
      INTEGER, PARAMETER :: $ATY             = 1     ! y-axis
      INTEGER, PARAMETER :: $ATR             = 2     ! r-axis
      INTEGER, PARAMETER :: $ATTHETA         = 3     ! theta-axis
      INTEGER, PARAMETER :: $ATCOUNT         = 4     ! how many total ATs

!   Tick Types for use in axis settings structure
      INTEGER, PARAMETER :: $TTNONE          = 0     ! no ticks on axis
      INTEGER, PARAMETER :: $TTINSIDE        = 1     ! ticks "inside" axis
      INTEGER, PARAMETER :: $TTOUTSIDE       = 2     ! ticks "outside" axis
      INTEGER, PARAMETER :: $TTBOTH          = 3     ! ticks on both sides of axis
      INTEGER, PARAMETER :: $TTCOUNT         = 3     ! how many total TTs

!   Grid Style for use in axis settings structure
      INTEGER, PARAMETER :: $GSNONE          = 0     ! no grid
      INTEGER, PARAMETER :: $GSMAJOR         = 1     ! grid on major ticks
      INTEGER, PARAMETER :: $GSBOTH          = 2     ! grid on major and minor ticks
      INTEGER, PARAMETER :: $GSZERO          = 3     ! grid line on zero
      INTEGER, PARAMETER :: $GSZEROMAJOR     = 4     ! grid on zero and major ticks
      INTEGER, PARAMETER :: $GSZEROBOTH      = 5     ! grid on zero and major and minor ticks
      INTEGER, PARAMETER :: $GSCOUNT         = 5     ! how many total GSs

!   Error codes for return from all SciGraph functions
      INTEGER, PARAMETER :: $GEOK            = 0     ! no error
      INTEGER, PARAMETER :: $GEGRAPHMODE     = 1     ! couldn't enter graphics mode
      INTEGER, PARAMETER :: $GEFONT          = 2     ! couldn't set fonts
      INTEGER, PARAMETER :: $GEGRAPH         = 3     ! the graph info or type was bad
      INTEGER, PARAMETER :: $GEAXIS          = 4     ! the axis info, type, or func was bad
      INTEGER, PARAMETER :: $GEDATA          = 5     ! invalid data or data settings info
      INTEGER, PARAMETER :: $GEDIMS          = 6     ! one or more of the dimensions was bad
      INTEGER, PARAMETER :: $GEPARAMS        = 7     ! one or more of the params was bad
      INTEGER, PARAMETER :: $GENOPLOTGRAPH   = 8     ! didn't do plot graph before plot data

END MODULE SGDATA

