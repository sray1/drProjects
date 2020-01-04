	Subroutine Form_Constitutive_Expanded(D,nCMat,iOut)
	
	Implicit Real(kind=8) (a-h,o-z)
!
	include 'Material.h'
	include 'LogParams.h'
!
	Real(kind=8)	D
	Dimension		D(nCMat,nCMat),T(8,nCMat) 
!	                          
	DATA zero/0.D0/,one/1.0D0/,onem/-1.0D0/,two/2.0D0/,three/3.0D0/ 
	DATA half/0.5D0/,halfm/-0.5D0/,quart/0.25D0/
!----------------------------------------------------------
	D		= 0.D0 !ALL
!============================== Transformation
	T = zero
!	============================================== engineering <- shell
	if(bEng == .TRUE.) then
		T( 1, 1) = one				!eb11 <- eb11
		T( 2, 8) = one				!eb22 <- eb22
		T( 3, 2) = half				!eb12 <- eb12
		T( 3, 7) = half				!eb12 <- eb21

		T( 4, 3) = one				!eb13 <- eb13
		T( 5, 9) = one				!eb23 <- eb23
!
!		T( 6, 5) = one				!ek11 <- ek12
!		T( 7,10) = onem				!ek22 <- ek21
!		T( 8, 4) = halfm			!ek12 <- ek11
!		T( 8,11) = half				!ek12 <- ek22
!
		T( 6, 4) = one				!ek11 <- ek11
		T( 7,11) = one				!ek22 <- ek22
		T( 8, 5) = half				!ek12 <- ek12
		T( 8,10) = half				!ek12 <- ek21
		write(iOut,1005) (i,(T(i,j),j=1,nCMat),i=1,8)
	else
!	============================================== virtual <- shell
		T( 1, 1) = one				!vb11 <- sb11
		T( 2, 8) = one				!vb22 <- sb22
		T( 3, 2) = half				!vb12 <- sb12
		T( 3, 7) = half				!vb12 <- sb21

		T( 4, 3) = one				!vb13 <- sb12
		T( 5, 9) = one				!vb23 <- sb23

		T( 6, 4) = one				!vk11 <- sk11
		T( 7,11) = one				!vk22 <- sk22
		T( 8, 5) = half				!vk12 <- sk12
		T( 8,10) = half				!vk21 <- sk21
		write(iOut,1010) (i,(T(i,j),j=1,nCMat),i=1,8)
	endif
!============================================================ expanded form
	D = MATMUL(TRANSPOSE(T),MATMUL(CD,T) )
!	=======================================================
	write(iOut,1020) (i,(D(i,j),j=1,nCMat),i=1,nCMat)
!	------
	return
 1005 Format(/ 5x,"Expansion Matrix		= ENGINEERING "/
     &	(2x,I2,12(2x,f5.2))  )		
 1010 Format(/ 5x,"Expansion Matrix		= VIRTUAL "/
     &	(2x,I2,12(2x,f5.2))  )		
 1020 Format(/ 5x,"Expanded Constitutive Matrix "/
     &	(2x,I2,12(2x,f9.2))  )		
	end
