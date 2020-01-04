	Subroutine Form EdgeCubic(Q0,Q1,Q2,Q3,B1,B3,nDim,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!	====================================================
!	Uses Bilinear Coons Blending to Complete a Net
!
	
	Real(kind=8)	Q1(nDim),Q2(nDim),Q3(nDim),Q4(nDim)    
	Real(kind=8)	B1(nDim),B3(nDim)    
	
	Data			zero/0.D0/,Three/3.D0/,Thrbtu/1.5D0/
!	--------------------------------------------
	Q1 = Three*B1 - Thrbtu*B3
	Q2 = Three*B3 - Thrbtu*B1
!	-------------------------------------------- 
!	done
!
	return
!
	end
