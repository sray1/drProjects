!
	Subroutine Set_ExtLoad(Qf,nDim,iOut)
	
	real(kind = 8)	Qf
	Dimension		Qf(nDim)
!	
	Qf		= 0.		! All Zero
	Qf(2)	= 1.0D0
!
	return
	end

	Subroutine Quad_QC_LV(Qf,F,nF,xLenY,iOut)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element:LOAD VECTOR
!
!
!	Inputs
!		Qf(4)		= Load Ceffs at Bez. Pts at r = 1 Side
!		xLenY		= Length of side at r = 1
!		 	
!	Outputs 
!		F(32)	1= Desired Load Vector
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays: Specifically for Shear Load At r = 1 Surface
!
	Real(kind=8)	Qf
	Dimension		Qf(3)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	F
	Dimension		F(42)
	
	Real(kind=8)	T2i,T2j,T4iPj,fmult,dum
	Real(kind=8)	tem	    ,temF
	Dimension		tem(3,3),temF(3)
	integer			i,j
!
	
	do 10 i= 1,3
	do 10 j= 1,3
	ii = i-1
	jj = j-1
	T2i		= Factorial(2)/Factorial(ii)/Factorial(2-ii) 
	T2j		= Factorial(2)/Factorial(jj)/Factorial(2-jj) 
	T4iPj	= Factorial(4)/Factorial(ii+jj)/Factorial(4-(ii+jj))
!
	tem(i,j)= (1./5.)*T2i*T2j/T4iPj
   10 continue
!
!	--------------
	fmult = 3.0D0
!	--------------
	do 30 i= 1,3
	dum = 0.
	do 20 j= 1,3
	dum = dum + tem(i,j)*Qf(j)
   20	continue
	temF(i) = fmult*dum
   30 continue
!-------------------------------------------------------- Shear load   
!	Now fill up Load Vector for Y values at r = 1 side
!
	F = 0.		! zero All
	F(36) = temF(1)    
	F(39) = temF(2)    
	F(42) = temF(3)    
!-------------------------------------------------------- Shear load   
!-------------------------------------------------------- Axial load   
!	Now fill up Load Vector for Y values at r = 1 side
!
!	F = 0.		! zero All
!	F(27) = 1.0D0    
!	F(30) = 1.0D0    
!	F(33) = 1.0D0    
!-------------------------------------------------------- Axial load   
!	Done
!
	write(iOut,1000)
	write(iOut,1010) (F(i),i = 1,nF)
!   		 
	return
 1000 Format(/2x,"Just before Leaving: Quad_CC_LVY"/)
 1010 Format(/2x,"Load Vector"/
     &        7(2x,8F10.7/) )
	end 
	
	real(kind=8) function Factorial(num)
	integer num
	
	Factorial = 1.D0
	do 40 i = num,1,-1
	Factorial = Factorial*i
   40	continue
!
	end 
!
	Subroutine Extract_ContractedLoadVector(Ff,nFf,Fc,nFc,iCont,iOut)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM
!	EQUATIONS 1,13,17 Rows NEED TO GO
!
!	Ff(nFf)		= Full Load Vector (INPUT)	
!	Fc(nFc)		= Contracted Load Vector (OUTPUT)
!
	real(kind = 8)	Ff     ,Fc
	Dimension		Ff(nFf),Fc(nFc)
!
!
	integer i,ii
!
	integer			Drop   ,DropC0   ,DropC1   ,DropC2
	Dimension		Drop(4),DropC0(4),DropC1(4),DropC2(4)	
	DATA DropC0 / 1,5,9,13/
	DATA DropC1 / 1,4,7,10/
	DATA DropC2 / 1,4,7,10/
	DATA nDrop0/4/
	DATA nDrop1/4/
	DATA nDrop2/4/
!
!------------------------------ Initialize
	if( iCont == 0) Then
		nDrop = nDrop0
		do 5 k = 1,nDrop
		Drop(k) = DropC0(k)
    5		continue
	else if( iCont == 1) Then 
		nDrop = nDrop1
		do 6 k = 1,nDrop
		Drop(k) = DropC1(k)
    6		continue
	else if( iCont == 2) Then 
		nDrop = nDrop2
		do 7 k = 1,nDrop
		Drop(k) = DropC2(k)
    7		continue
	end if
!------------------------------
!
	ii = 0
!			
	do 20 i = 1,nFf
	do 10 k = 1,nDrop
	if(i == Drop(k)) then
		go to 20
	end if
   10	continue
	ii = ii + 1
!
	Fc(ii) = Ff(i)
   20 continue
!
	return
	end
!
		  		