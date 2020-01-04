	Subroutine CalcCoords_at_a_Pt(Coord,Qc,nDim,nQc1,nQc2,ri,rj)
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Coord    
	Dimension		Coord(nDim)
	Real(kind=8)	Qc                ,Bri      ,Brj    
	Dimension		Qc(nDim,nQc1,nQc2),Bri(nQc1),Brj(nQc2)
!	-------------------------------------------- Basis Functions		 
	call Bernstein(Bri,nQc1,ri,iOut)
	call Bernstein(Brj,nQc2,rj,iOut)
!------------------------------
	Coord = 0.D0	
	do 10 i= 1,nQc1
	do 10 j= 1,nQc2
!
	Brij = Bri(i)*Brj(j)
	do 10 k= 1,nDim
	Coord(k) = Coord(k) + Brij*Qc(k,i,j) 
   10	continue
!
!	done
!
	return
	end
