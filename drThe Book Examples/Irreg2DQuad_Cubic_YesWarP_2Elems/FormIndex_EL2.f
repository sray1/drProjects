	Subroutine FormIndexEL_2(Indx,nStifEL,iOut)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!
!	Outputs 
!		Indx(nStifEl)	= Indx of assembly for Element 2
!
	Implicit Real(kind=8) (a-h,o-z)
	integer Indx(nStifEL)
!
!	Indices of location in global stiffness
!
	Indx( 1) = 4
	Indx( 2) = 25
	Indx( 3) = 26
	Indx( 4) = 27
	Indx( 5) = 8
	Indx( 6) = 28
	Indx( 7) = 29
	Indx( 8) = 30
	Indx( 9) = 12
	Indx(10) = 31
	Indx(11) = 32
	Indx(12) = 33
	Indx(13) = 16
	Indx(14) = 34
	Indx(15) = 35
	Indx(16) = 36
	Indx(17) = 20
	Indx(18) = 37
	Indx(19) = 38
	Indx(20) = 39
	Indx(21) = 24
	Indx(22) = 40
	Indx(23) = 41
	Indx(24) = 42
!
	write(iOut,1000)
	write(iOut,1010) nStifEL,(Indx(i),i = 1,nStifEL)
!   		 
	return
 1000 Format(/2x,"Just before Leaving: FormIndexEL_2"/)
 1010 Format(/2x,"Indices for Element#2 for Global Assembly: 1x"I3/
     &										7(8(2x,I5)/) )
	end   		