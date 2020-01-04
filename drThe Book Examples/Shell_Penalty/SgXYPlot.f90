!**********************************************************************
!
! SciGraph -- Scientific Graphs for Compaq Visual Fortran
!
!

!
!   sgdemo.for - Demo of the SciGraph graphing library
!
!   DESCRIPTION
!       This program draws an example of each type of
!       graph available with SciGraph.
!

MODULE DeformationPlot

USE DFLIB
USE SCIGRAPH

CONTAINS
	
SUBROUTINE SciGraphXYPlot(iOutP,nPts,MaxPlot,iPltType)

      integer i

      open(9,file='user',title='xyGraph')
      call doDeformationPlot(iOutP,nPts,MaxPlot,iPltType)

      i = setexitqq(QWIN$EXITPERSIST)
END SUBROUTINE


!
! XYDemo -- Draws a simple XY Graph
!
SUBROUTINE doDeformationPlot(iOutP,nPts,MaxPlot,iPltType)

      RECORD /GraphSettings/ xyGraph
      RECORD /DataSettings/ xyDataSets(MaxPlot)    ! MaxPlot data sets (ranges)
      RECORD /AxisSettings/ xyAxes(4)			   ! 4 axes: 2 y, 2 x

      REAL*4      xyData(2,nPts,MaxPlot)           ! MaxPlot data sets each with nPts (x,y)
      CHARACTER*20 xyDataLegends(MaxPlot),dLeg     ! MaxPlot data range legends

      INTEGER     retcode
      INTEGER     setLegends
      RECORD /windowconfig/ wc
!-------------------------------------------------------------------------
		  REWIND iOutP
!		  READ (iOutP)
!		  READ (iOutP)
	
		  DO i =1,MaxPlot
		  if(iPltType == 1) Then
			Read(iOutP,1030) nStep,XLF	! LoadFactor
          endif
		  Read(iOutP,1020) (xyData(1,j,i),xyData(2,j,i),j=1,nPts)
		  write(dLeg,'(a4,i3)') 'Load',i
		  xyDataLegends(i) = dLeg 
		  END DO
!-------------------------------------------------------------------------
          if( .not. GetWindowConfig(wc) ) stop 'Window Not Open'

          retcode=GetGraphDefaults($GTXY,xyGraph)
          xyGraph.setGraphMode=.FALSE.
          xyGraph.x2=wc.numxpixels-1
          xyGraph.y2=wc.numypixels-1
          xyGraph.title='Deformed Shapes for LoadSTeps'

          retcode=GetMultiDataDefaults(xyGraph,nPts,xyData,MaxPlot,xyDataSets)
          DO setLegends=1,MaxPlot
              xyDataSets(setLegends).title=xyDataLegends(setLegends)
          END DO

          retcode=GetAxisMultiDefaults(xyGraph,MaxPlot,xyDataSets,  &
                 $ATX,$AFLINEAR,xyAxes(1))
          xyAxes(1).title='Beam direction'

          retcode=GetAxisMultiDefaults(xyGraph,MaxPlot,xyDataSets,  &
                 $ATY,$AFLINEAR,xyAxes(2))
          xyAxes(2).title='Deformation'
          xyAxes(2).gridStyle=$GSBOTH
          xyAxes(2).gridLineType=$LTDOT
          xyAxes(2).gridColor=$CILIGHTBLUE

          retcode=GetAxisMultiDefaults(xyGraph,MaxPlot,xyDataSets,  &
                 $ATX,$AFLINEAR,xyAxes(3))
          xyAxes(3).title='Beam direction'
!          xyAxes(3).lowVal=xyAxes(3).lowVal/2.54
!          xyAxes(3).highVal=xyAxes(3).highVal/2.54
!          xyAxes(3).increment=xyAxes(3).increment/2.54
          xyAxes(3).tickColor=$CIWHITE
          xyAxes(3).minorTickColor=$CIGRAY
          xyAxes(3).titleColor=$CIWHITE

          retcode=GetAxisMultiDefaults(xyGraph,MaxPlot,xyDataSets,  &
                 $ATY,$AFLINEAR,xyAxes(4))
          xyAxes(4).title='Deformation'
!          xyAxes(4).lowVal=xyAxes(4).lowVal/2.54
!          xyAxes(4).highVal=xyAxes(4).highVal/2.54
!          xyAxes(4).increment=xyAxes(4).increment/2.54
          xyAxes(4).tickColor=$CIWHITE
          xyAxes(4).minorTickColor=$CIGRAY
          xyAxes(4).titleColor=$CIWHITE


          retcode=PlotGraph(xyGraph,4,xyAxes,MaxPlot)

          retcode=PlotMultiData(xyGraph,xyData,MaxPlot,xyDataSets,xyAxes(1),xyAxes(2))
 
!
 1020 format(2e15.5)
 1030 format(i3,e15.5)


      END SUBROUTINE


END MODULE

