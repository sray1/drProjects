	Subroutine DeformOut_MatLab_Edges(Qc,nDim,nQc,DefSav,nDefSav,
     &									nPtsi,mCount,iOut,iOutS)
	Implicit Real(kind=8) (a-h,o-z)

!
	
	Real(kind=8)	Qc(nDim,nQc),Coord(nDim)    
	Real(kind=8)	DefSav   
	Dimension		DefSav(3,nDefSav)
	Data			zero/0.D0/,one/1.D0/,two/2.D0/
!	--------------------------------------------		 
	delri	= 1.D0/(dble(nPtsi-1))
	ri		= -delri
!	-----------------------------
	m = mCount
	do 40 i = 1,nPtsi
	m = m+1
	ri = ri + delri
!
	Coord = zero
	call CalcCoords_at_a_Pt_Edges(Coord,Qc,nDim,nQc,ri)
!
	DefSav(1,m) = Coord(1)
	DefSav(2,m) = Coord(2)
	DefSav(3,m) = Coord(3)
!	--------------------------------------------
   40	continue
	mCount = m
!
!	done
!
	return
!
 !	----------------------------------------------------- Plot Save
	end
