	Subroutine PackAllControlsforPlot(QO,nDim,nRow,nCol,mC,iOutC)
	Implicit Real(kind=8) (a-h,o-z)
!	====================================================
	Real(kind=8)	QO(nDim,nRow,nCol)    
!																	Nrow = nCol = 4	
	Data			zero/0.D0/,one/1.D0/,two/2.D0/,three/3.D0/
!	------------------------------------------------------------------------------- Edges
	iPlt = 0
	if(iPlt == 1) then
		mCount = mC
		do i = 1,nRow										!Edge 1 : left
			n =	nRow + 1 - i								
			mCount = mCount + 1
			write(iOutC,1040) QO(1,n,1),QO(2,n,1),QO(3,n,1)
		end do
		do j = 1,nCol										!Edge 2 : bottom
			n =	j								
			mCount = mCount + 1
			write(iOutC,1040) QO(1,1,n),QO(2,1,n),QO(3,1,n)
		end do
		do i = 1,nRow										!Edge 3 : right
			n =	nRow + 1 - i								
			mCount = mCount + 1
			write(iOutC,1040) QO(1,n,nCol),QO(2,n,nCol),QO(3,n,nCol)
		end do
		do j = 1,nCol										!Edge 4 : top
			n =	nCol + 1 - j								
			mCount = mCount + 1
			write(iOutC,1040) QO(1,nRow,n),QO(2,nRow,n),QO(3,nRow,n)
		end do
	endif
!	------------------------------------------------------------------------- Move to (nRow,2)
		mCount = mCount + 4
		write(iOutC,1040) QO(1,nRow,2),QO(2,nRow,2),QO(3,nRow,2)
		write(iOutC,1040) QO(1,nRow-1,2),QO(2,nRow-1,2),QO(3,nRow-1,2)
		write(iOutC,1040) QO(1,nRow-2,2),QO(2,nRow-2,2),QO(3,nRow-2,2)
		write(iOutC,1040) QO(1,nRow-3,2),QO(2,nRow-3,2),QO(3,nRow-3,2)
!	------------------------------------------------------------------------ Move to (nRow-3,3)
		mCount = mCount + 4
		write(iOutC,1040) QO(1,nRow-3,3),QO(2,nRow-3,3),QO(3,nRow-3,3)
		write(iOutC,1040) QO(1,nRow-2,3),QO(2,nRow-2,3),QO(3,nRow-2,3)
		write(iOutC,1040) QO(1,nRow-1,3),QO(2,nRow-1,3),QO(3,nRow-1,3)
		write(iOutC,1040) QO(1,nRow,3),QO(2,nRow,3),QO(3,nRow,3)
!	------------------------------------------------------------------------ Move to (nRow,nCol)
		mCount = mCount + 1
		write(iOutC,1040) QO(1,4,4),QO(2,4,4),QO(3,4,4)
!	------------------------------------------------------------------------ Move to (nRow-1,nCol)
		mCount = mCount + 4
		write(iOutC,1040) QO(1,3,4),QO(2,3,4),QO(3,3,4)
		write(iOutC,1040) QO(1,3,3),QO(2,3,3),QO(3,3,3)
		write(iOutC,1040) QO(1,3,2),QO(2,3,2),QO(3,3,2)
		write(iOutC,1040) QO(1,3,1),QO(2,3,1),QO(3,3,1)
!	------------------------------------------------------------------------ Move to (nRow-2,1)
		mCount = mCount + 4
		write(iOutC,1040) QO(1,2,1),QO(2,2,1),QO(3,2,1)
		write(iOutC,1040) QO(1,2,2),QO(2,2,2),QO(3,2,2)
		write(iOutC,1040) QO(1,2,3),QO(2,2,3),QO(3,2,3)
		write(iOutC,1040) QO(1,2,4),QO(2,2,4),QO(3,2,4)
!	===================================================
	mC = mCount
!
!	done
!
	return
 1040 format(F15.2,",",F15.2,",",F15.2,",")
	end
