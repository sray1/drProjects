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
!	===========================
	include 'Examples.h'
!	common/Examples/cEx(10),nEx
!	character (30)	cEx
!	===========================
!
!	Input Variables & Arrays
!
	Real(kind=8)	ELRBF         
	Dimension		ELRBF(nStifEL)
	integer			Indx(nStifEL),Nel,Iout,nStifEL,nStif
!	
!	Output Variables & Arrays	
!
!	=============================== ARGYRIS Frame
	Real(kind=8)	AA
	Dimension		AA(nStifEL,nStifEL)
!	=============================== ARGYRIS Frame End
	Real(kind=8)	BLod	
	Dimension		BLod(nStif)
!	===========================
	DATA zero/0.D0/,one/1.0D0/,onm/-1.0D0/ 
!	//////////////////////
!============================================================ ARGYRIS: Rotate 2nd Stiffness
	if((nEx == 6).AND.(Nel == 2)) Then
		do 97 i =1,nStifEL
		AA(i,i) = one
   97		continue
!		================ for 2nd Stiffness Rot Matrix from ist Curvilinear to 2nd
		AA( 1, 1)	= zero
		AA( 1, 7)	= one
!
		AA( 7, 7)	= zero
		AA( 7, 1)	= one
!
		AA(13,13)	= onm
!
		AA(19,19)	= zero
		AA(19,25)	= one
!
		AA(25,25)	= zero
		AA(25,19)	= one
!
		AA(31,31)	= onm
!		=================
		ELRBF	= MATMUL(AA,ELRBF)
	endif
!============================================================ ARGYRIS: Rotate 2nd Stiffness: END
!
!	Load Vector Assembly
!
	if (Nel.EQ.1) Then
    		BLod = 0.D0	! all elements = 0.
!
		do 10 i = 1,nStifEL
!		-------------------------------- Residual force part
   10		BLod(i) = ELRBF(i) 
	else
		do 60 i = 1,nStifEL
		ii = Indx(i) 
   60		BLod(ii) = BLod(ii)+ ELRBF(i)
	end if
!
!	done
!
	iPrt = 0
	if (Nel.EQ.4)iPrt = 0
	if(iPrt == 1) Then
		write(iOut,1010) nStif,(i,BLod(i),i = 1,nStif)
	endif
	iPrt = 0
!
	return
!
 1010 format("Full Load Vector :BLod(",I5,")"/
     &        (5(i3,2x,f16.7,1X))/)
	return
	end   	
