	Subroutine FormTransformationMatrix_C0_Lin(T,nStifS,nStifC,iOut)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!------------------------------------------------------------
!	C1- Contraints:
!	 old Row         new Cols	
!		i4  = (1/2){ i3  + i19)
!		i8  = (1/2){ i6  + i22)
!		i12 = (1/2){ i9  + i25)
!		i16 = (1/2){ i12 + i28)
!		i20 = (1/2){ i15 + i31)
!		i24 = (1/2){ i18 + i34)
!-----------------------------------
!
!	Inputs
!		nStifS					= Row or Col size of SinStiffness matrix 
!		nStifC					= Row or Col size of ConStiffness matrix
!		 	
!	Outputs 
!		T(nStifS,nStifC)		= C0 Transformation Matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	Half,TwThd,Third,Sixth   
	Dimension		T(nStifS,nStifC)
!------------------------------------------
!	write(iOut,1020) (Alfa(j),j = 1,4)
!	write(iOut,1030) (Beta(j),j = 1,4)
!	//////////////////////
!	Transformation Matrix 
!
	TwThd	= 2.0D0/3.0D0
	Third	= 1.0D0/3.0D0
	Sixth	= 1.0D0/6.0D0
	half	= 0.5D0
!	-----------------------------------
	T		= 0.0D0	! everything zeroed
	T( 1, 1) = 1.0D0 
	T( 4, 2) = 1.0D0 
	T( 9, 3) = 1.0D0 
	T(12, 4) = 1.0D0 
	T(13, 5) = 1.0D0 
	T(16, 6) = 1.0D0 
	T(21, 7) = 1.0D0 
	T(24, 8) = 1.0D0 
	T(27, 9) = 1.0D0 
	T(33,10) = 1.0D0 
	T(36,11) = 1.0D0 
	T(42,12) = 1.0D0 
!	-----------------------------------
	T( 2, 1) = TwThd 
	T( 2, 2) = Third 
	T(14, 5) = TwThd
	T(14, 6) = Third
	T( 3, 1) = Third 
	T( 3, 2) = TwThd 
	T(15, 5) = Third
	T(15, 6) = TwThd
	T( 5, 1) = Half 
	T( 5, 3) = Half 
	T(17, 5) = Half 
	T(17, 7) = Half 
	T( 6, 1) = Third 
	T( 6, 2) = Sixth 
	T( 6, 3) = Third 
	T( 6, 4) = Sixth 
	T(18, 5) = Third 
	T(18, 6) = Sixth 
	T(18, 7) = Third 
	T(18, 8) = Sixth 
	T( 7, 1) = Sixth 
	T( 7, 2) = Third 
	T( 7, 3) = Sixth 
	T( 7, 4) = Third 
	T(19, 5) = Sixth 
	T(19, 6) = Third
	T(19, 7) = Sixth 
	T(19, 8) = Third
	T( 8, 2) = Half 
	T( 8, 4) = Half 
	T(20, 6) = Half
	T(20, 8) = Half
	T(10, 3) = TwThd
	T(10, 4) = Third
	T(22, 7) = Half
	T(22, 8) = Half
	T(11, 3) = Third
	T(11, 4) = TwThd
	T(23, 7) = Third 
	T(23, 8) = TwThd 
!
	T(25, 2) = TwThd
	T(25, 9) = Third
	T(34, 6) = TwThd 
	T(34,11) = Third 
	T(26, 2) = Third
	T(26, 9) = TwThd
	T(35, 6) = Third 
	T(35,11) = TwThd 
	T(28, 2) = Third 
	T(28, 4) = Third 
	T(28, 9) = Sixth 
	T(28,10) = Sixth 
	T(37, 6) = Third 
	T(37, 8) = Third 
	T(37,11) = Sixth 
	T(37,12) = Sixth 
	T(29, 2) = Sixth 
	T(29, 4) = Sixth
	T(29, 9) = Third 
	T(29,10) = Third 
	T(38, 6) = Sixth 
	T(38, 8) = Sixth
	T(38,11) = Third 
	T(38,12) = Third 
	T(31, 5) = TwThd 
	T(30, 9) = Half 
	T(30,10) = Half 
	T(39,11) = Half
	T(39,12) = Half
	T(31, 4) = TwThd
	T(31,10) = Third
	T(40, 8) = TwThd 
	T(40,12) = Third 
	T(32, 4) = Third
	T(32,10) = TwThd
	T(41, 8) = Third 
	T(41,12) = TwThd 
!	----------------
!
!	OPEN (unit = 17, FILE = 'Tran_C1.prt', STATUS = 'NEW')
!	do 110 i = 1,nStifS
!	write(17,1010) nStifS,nStifC,i,(T(i,j),j = 1,nStifC)
!  110	continue
  120 continue
!   		 
	return
 1010 format("C0_Linear Transformation Matrix:T(",I3,",",I3,")"/
     &        I5/(5(9(f5.2,1X)/)))
	end   	
