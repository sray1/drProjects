	DOUBLE PRECISION Function Area(Q1,Q2,Q3,Nel,Iout)
!
!	Area comes out negative if input is clockwise
!	
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Q1   ,Q2   ,Q3       
	Dimension		Q1(2),Q2(2),Q3(2)
	integer			Nel,Iout
!------------------------------------ 
	Area	=	(
     &				(Q2(1)-Q1(1))*(Q3(2)-Q1(2)) -
     &				(Q2(2)-Q1(2))*(Q3(1)-Q1(1))
     &			)/2.D0
!	--------
	return
 1000	format(A,I5,A)
 1010 format(2X,"R = ",f10.5,2X,"S = ",f10.5,2X,"det = ",f10.5,
     &				" TP Av.Knot")
 1020 format(2X,"R = ",f10.5,2X,"S = ",f10.5,2X,"det = ",f10.5,
     &				" Normal")
!
	end
