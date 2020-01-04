	Subroutine Assemble_Load(Indx,ELRBF,nStifEL,BLod,nStif,Nel,Iout)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!
!	Inputs
!		Indx(nStifEL)	= Index of location for Element 2
!		Nel				= Element Number
!		ELRBF			= Element Residual
!		nStifEL			= Row or Col size of Stiffness matrix ( MUST BE 32)
!		nStif			= Row or Col size of Stiffness matrix ( MUST BE 64)
!		Iout			= Error Output file#
!		 	
!	Outputs 
!		BLod			= Desired Assembled Load Vector
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
	Real(kind=8)	ELRBF         
	Dimension		ELRBF(nStifEL)
	integer			Indx(nStifEL),Nel,Iout,nStifEL,nStif
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	BLod	
	Dimension		BLod(nStif)
!	//////////////////////
!
!	Stiffness Matrix Assembly
!
	if (Nel.EQ.1) Then
    		BLod = 0.D0	! all elements = 0.
!
		do 10 i = 1,nStifEL
!		-------------------------------- Residual force part
   10		BLod(i) = ELRBF(i) 
	else if (Nel.EQ.2) Then
		do 60 i = 1,nStifEL
		ii = Indx(i) 
   60		BLod(ii) = BLod(ii)+ ELRBF(i)
	end if
!
!	done
!
	iPrt = 0
	if(iPrt == 1) Then
		write(iOut,1010) nStif,(BLod(i),i = 1,nStif)
	endif
!
	return
!
 1010 format("Full Load Vector :BLod(",I2,")"/
     &        (5(f16.7,1X))/)
	return
	end   	
