	Subroutine Form_Constitutive_Expanded(D,nCMat,iOut)
!********************************************* nCMat MUST be 12 ********************	
	Implicit Real(kind=8) (a-h,o-z)
!
	include 'Material.h'
	include 'LogParams.h'
!
	Real(kind=8)	D
	Dimension		D(nCMat,nCMat) 
!	                          
	DATA zero/0.D0/,one/1.0D0/,onem/-1.0D0/,two/2.0D0/,three/3.0D0/ 
	DATA half/0.5D0/,halfm/-0.5D0/,quart/0.25D0/
!----------------------------------------------------------
	D		= 0.D0 !ALL
!============================== Transformation
	XE = zero
!	============================================== engineering <- shell
	if(bEng == .TRUE.) then
		XE( 1, 1) = one				!eb11 <- eb11
		XE( 2, 8) = one				!eb22 <- eb22
		XE( 3, 2) = half				!eb12 <- eb12
		XE( 3, 7) = half				!eb12 <- eb21

		XE( 4, 3) = one				!eb13 <- eb13
		XE( 5, 9) = one				!eb23 <- eb23
!
		XE( 6, 4) = one				!ek11 <- ek11
		XE( 7,11) = one				!ek22 <- ek22
		XE( 8, 5) = half				!ek12 <- ek12
		XE( 8,10) = half				!ek12 <- ek21
		write(iOut,1005) (i,(XE(i,j),j=1,nCMat),i=1,8)
	else
!	============================================== virtual sym <- virtual
		XE( 1, 1) = one				!sb11 <- sb11
		XE( 2, 8) = one				!sb22 <- sb22
		XE( 3, 2) = half				!sb12 <- sb12
		XE( 3, 7) = half				!sb12 <- sb21
!
		XE( 4, 3) = one				!vb13 <- sb13
		XE( 5, 9) = one				!vb23 <- sb23

		XE( 6, 5) = one				!sk11 <- sk12
		XE( 7,10) = one				!sk22 <- sk21
		XE( 8, 4) = half				!sk12 <- sk11
		XE( 8,11) = half				!sk12 <- sk22
		write(iOut,1010) (i,(XE(i,j),j=1,nCMat),i=1,8)
	endif
!============================================================ expanded form
!	D = MATMUL(TRANSPOSE(XE),MATMUL(CD,XE) )
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
