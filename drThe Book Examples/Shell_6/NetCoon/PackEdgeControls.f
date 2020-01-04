	Subroutine PackEdgeControls(Q1,Q2,Q3,Q4,Qe,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!	====================================================
	Real(kind=8)	Q1(3),Q2(3),Q3(3),Q4(3)   
	Real(kind=8)	Qe(3,4)    
	
	Data			zero/0.D0/,one/1.D0/,two/2.D0/,three/3.D0/
	Data			nDim/3/
!	------------------------------------------------------------- Compute Bezier End Controls
	do k = 1,nDim
		Qe(k,1) = Q1(k)
		Qe(k,2) = Q2(k)
		Qe(k,3) = Q3(k)
		Qe(k,4) = Q4(k)
	end do
!
!	done
!
	return
	end
