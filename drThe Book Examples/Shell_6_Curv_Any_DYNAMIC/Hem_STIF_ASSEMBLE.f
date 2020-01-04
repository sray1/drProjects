	Subroutine Hem_Stif_Assemble(Indx,StifEL,nQ,nDof,
     &                        nStifEL,Stif,nStif,Nel,Iout,Trace)
!
!
!
!	Inputs
!		Indx(nStifEL)	= Index of location for Element 2
!		Nel				= Element Number
!		StifEL(32,32)	= Element Stiffness Matrix
!		nStifEL			= Row or Col size of Stiffness matrix ( MUST BE 32)
!		nStif			= Row or Col size of Stiffness matrix ( MUST BE 64)
!		Iout			= Error Output file#
!		 	
!	Outputs 
!		Stif(64,64)		= Desired Stiffness Matrix
!		Trace			= trace of the matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
	Real(kind=8)	StifEL			       ,Trace
	Dimension		StifEL(nStifEL,nStifEL)
	integer			Indx(nQ,nQ,nDof),Nel,Iout,nStifEL,nStif
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	Stif			 ,Add
	Dimension		Stif(nStif,nStif),Add(nStif)
!	--------------------------------------------
	iPrt = 0
	if(iPrt == 1) Then
		write(Iout,1030) nStifEL,nStifEL
		do 222 i = 1,nStifEL
		write(Iout,1040) i,(StifEL(i,j),j = 1,nStifEL)
  222	continue
	endif 
!	/////////
!
!	Stiffness Matrix Assembly
!
	if (Nel.EQ.1) Then
    		Stif = 0.D0	! all elements = 0.
	endif
!	=================================
	nQ2 = nQ*nQ
!
	do is = 1,nStifEL
		kDof	= is/nQ2
		nrem	= mod(is,nQ2)		
		if(nrem.gt.0) then
			kDof	= kDof+1
		else
			nrem	= nQ2
		endif
!
		i		= nrem/nQ
		j		= mod(nrem,nQ)
		if(j.gt.0) then
			i	= i+1
		else
			j	= nQ
		endif
!		////////////////////////
		iEqn	= indx(i,j,kDof)
!		////////////////////////
		do js = 1,nStifEL
			kDof	= js/nQ2
			nrem	= mod(js,nQ2)		
			if(nrem.gt.0) then
				kDof	= kDof+1
			else
				nrem	= nQ2
			endif
!
			i		= nrem/nQ
			j		= mod(nrem,nQ)
			if(j.gt.0) then
				i	= i+1
			else
				j	= nQ
			endif
!			////////////////////////
			jEqn	= indx(i,j,kDof)
!			////////////////////////
			if(iEqn.NE.0.and.jEqn.NE.0) then
   60				Stif(iEqn,jEqn) = Stif(iEqn,jEqn) + StifEL(is,js)
			endif
		end do !js
	end do !is
!
!	Get Trace
!
	Trace = 0.D0
	do 80 i = 1,nStif
	Trace = Trace + Stif(i,i)
   80 continue			
!
!	Check each col. vector for Null
!
	Add = 0.D0
	do 100 j = 1,nStif
	sum = 0.0 
	do  90 i = 1,nStif	
	sum = sum + Stif(i,j)
   90 continue
	Add(j) = sum
  100 continue			
!
!	done
!
	write(Iout,1000) Nel
	iPrt = 0
	if(iPrt == 1) Then
		write(Iout,1010) nStif,nStif
		do 110 i = 1,nStif
		write(Iout,1020) i,(Stif(i,j),j = 1,nStif)
  110	continue
	endif 
!	/////////
	return
!
 1000 format("Assembly after Element #",i2/)
 1010 format("Assembled Stiffness Matrix:Stif(",I5,",",I5,")"/)
 1020 format(I5/(6(8(f12.1,1X)/)/))
 1030 format("INPUT Stiffness Matrixfor Assembly:Stif(",I5,",",I5,")"/)
 1040 format(I5/(6(8(f12.1,1X)/)/))
	end   	
