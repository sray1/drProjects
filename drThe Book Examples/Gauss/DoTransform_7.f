	Subroutine DoTransform_7(c,d)
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
!	Rk(15)		= Gauss-Legendre Nodes		Upto 16 Points
!	Ak(15,15)	= Gauss-Legendre Weights	Upto 16 Points
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
	Dimension    GLI(4,2) ,GLO(7,2)
	DATA ((GLI(i,j),j=1,2),i=1,4)/	
     &			0.94910791234275852453D0, 0.12948496616886969327D0,		
     &           	0.74153118559939443986D0, 0.27970539148927666790D0,			
     &            0.40584515137739716691D0, 0.38183005050511894495D0,	
     &            0.00000000000000000000D0, 0.41795918367346938776D0
     &		/
!     &            0.????????????????????D0, 0.????????????????????D0,	
!     &            0.????????????????????D0, 0.????????????????????D0,	
!     &            0.????????????????????D0, 0.????????????????????D0,	
!     &            0.????????????????????D0, 0.????????????????????D0	
!     &       /
!     		 
!
!
!	write(*,1000) ((GLI(i,j),j = 1,2),i=1,8)
!	Pause
!	
	rgam = (d-c)/2.0D0
	bet = -(d+c)
!
	do 10 i = 1,4
	j = 2*i-1
	GLO(j,1)	= rgam*( GLI(i,1) - bet)
	GLO(j,2)	= rgam*GLI(i,2)
	if (i == 4) Then
		goto 10
	end if
	GLO(j+1,1)	= rgam*(-GLI(i,1) - bet)
	GLO(j+1,2)	= GLO(j,2)
   10	continue
!
!	write(*,1010) ((GLO(i,j),j = 1,2),i=1,16)
  100	continue
!	Pause
!
!	save in a file:ASCII
!
	open(UNIT=10,FILE='c:\The Book\Gauss\Out_7.dat')
	write(10,1010) ((GLO(i,j),j = 1,2),i=1,7)
	write(10,1020)
	return
!
 1000 format(6X,"DATA ((GLI(i,j),j=1,2),i=1,4)/",/	
     &  (5X,"&",2X,(f20.16,',',2X,f20.16,',')) )
 1010 format(6X,"DATA ((GLO(i,j),j=1,2),i=1,7)/",/	
     &  (5X,"&",2X,(f20.16,',',2X,f20.16,',')) )
 1020 format(10X,'/')
	return
	end   		