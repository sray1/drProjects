	Subroutine CalcRot_at_a_Pt(Rot,Qd,nQd,nDim,nQd1,nQd2,ri,rj)
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Rot    
	Dimension		Rot(nDim)
	Real(kind=8)	Qd     ,Bri      ,Brj    
	Dimension		Qd(nQd),Bri(nQd1),Brj(nQd2)
!	-------------------------------------------- Basis Functions		 
	call Bernstein(Bri,nQd1,ri,iOut)
	call Bernstein(Brj,nQd2,rj,iOut)
!	------------------------------
	nQd12	= nQd1*nQd2
	nRstart = nDim*nQd12
	Rot		= 0.D0
!		
	do 10 k= 1,nDim
	kStart	= nRstart + (k-1)*nQd12

	do 10 i= 1,nQd1
	do 10 j= 1,nQd2
!
	Brij = Bri(i)*Brj(j)
	loc		= kStart + (i-1)*nQd2 + j
	Rot(k)	= Rot(k) + Brij*Qd(loc) 
   10	continue
!
!	done
!
	return
	end
