	Subroutine CalcCoords_at_a_Pt_Edges(Coord,Qc,nDim,nQc,ri)
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Coord    
	Dimension		Coord(nDim)
	Real(kind=8)	Qc          ,Bri        
	Dimension		Qc(nDim,nQc),Bri(nQc)
!	-------------------------------------------- Basis Functions		 
	call Bernstein(Bri,nQc,ri,iOut)
!------------------------------
	Coord = 0.D0	
	do 10 i= 1,nQc
!
	Brij = Bri(i)
	do 10 k= 1,nDim
	Coord(k) = Coord(k) + Brij*Qc(k,i) 
   10	continue
!
!	done
!
	return
	end
