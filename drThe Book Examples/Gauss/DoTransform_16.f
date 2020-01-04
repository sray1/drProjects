	Subroutine DoTransform_16(c,d)
!
!	Transform Gauss-Legendre from [-1,1] -> [0,1]
!	Stroud,AH:Numerical Quadrature & Solution of ODE
!	(p:117)/Spinger-Verlag 1974
!	---------------------------
!	Formula:
!		Transform Gauss-Legendre from [a,b] -> [c,d]:
!		gam = (b-a)/(d-c)
!		bet = (ad-bc)/(d-c)
!		Node -> (1/gam)(Node - bet)
!		Value->	(1/gam)Value
!	---------------------------
!	Inputs:
!		c,d
!		Data	
!		Gauss-Legendre Points for [a,b] with a = -1 and b = 1
!	---------------------------	 	
!	Outputs 
!		Gauss-Legendre Points for [c,d]
!	/////////////////////////////////////////////
	Implicit Real(kind=8) (a-h,o-z)
!
!--------------------------------------------------
!	Rk(16)		= Gauss-Legendre Nodes		Upto 16 Points
!	Ak(16,16)	= Gauss-Legendre Weights	Upto 16 Points
!	
!	Recall: For our case 
!		Our integration,r = [0,1] 
!		Conventional	x = [-1,1]
!		ie., x = (2r-1)
!	->
!	gam = 2 and bet = a = -1 
!	So, following values modified as:
!		Node	= (1/2)(Nod+1)
!		Value	= (1/2)Value
!---------------------------------------------------
	Real(kind=8) c,d,rgam,bet     
	Real(kind=8) GLI      ,GLO     
	Dimension    GLI(8,2) ,GLO(16,2)
	DATA ((GLI(i,j),j=1,2),i=1,8)/	
     &			0.98940093499164993260D0, 0.027152459411754094852D0,		
     &           	0.94457502307323257608D0, 0.062253523938647892863D0,			
     &            0.86563120238783174388D0, 0.095158511682492784810D0,	
     &            0.75540440835500303390D0, 0.12462897125553387205D0,	
     &            0.61787624440264374845D0, 0.14959598881657673208D0,	
     &            0.45801677765722738634D0, 0.16915651939500253819D0,	
     &            0.28160355077925891323D0, 0.18260341504492358887D0,	
     &            0.095012509837637440185D0,0.18945061045506849629D0	
     &       /
!     		 
!
!
!	write(*,1000) ((GLI(i,j),j = 1,2),i=1,8)
!	Pause
!	
	rgam = (d-c)/2.0D0
	bet = -(d+c)
!
	do 10 i = 1,8
	j = 2*i-1
	GLO(j,1)	= rgam*( GLI(i,1) - bet)
	GLO(j+1,1)	= rgam*(-GLI(i,1) - bet)
	GLO(j,2)	= rgam*GLI(i,2)
	GLO(j+1,2)	= GLO(j,2)
   10	continue
!
!	write(*,1010) ((GLO(i,j),j = 1,2),i=1,16)
  100	continue
!	Pause
!
!	save in a file:ASCII
!
	open(UNIT=10,FILE='c:\The Book\Gauss\Out_16.dat')
	write(10,1010) ((GLO(i,j),j = 1,2),i=1,16)
	write(10,1020)
	return
!
 1000 format(6X,"DATA ((GLI(i,j),j=1,2),i=1,8)/",/	
     &  (5X,"&",2X,(f20.16,',',2X,f20.16,',')) )
 1010 format(6X,"DATA ((GLO(i,j),j=1,2),i=1,16)/",/	
     &  (5X,"&",2X,(f20.16,',',2X,f20.16,',')) )
 1020 format(10X,'/')
	return
	end   		