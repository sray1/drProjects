	Subroutine Get_Loads_Pal_D(LocF,ValF,nLod,nQd1,nQd2,iCont,iOut)			! TODO
!	Strip shell (Curved Arch) Palazotto
!	Quintic in xy and linear in xz (Poisson's = 0)				nLod = 2
	Real*8			ValF      
	Dimension		ValF(nLod)
	integer			LocF
	Dimension		LocF(nLod)
	integer			AddC05      
	Dimension		AddC05(2)	
	integer			AddC06      
!	Dimension		AddC06(4)	! Palazzoto		For CUBIC
	Dimension		AddC06(2)	! Palazzoto		For LINEAR
!---------------------------
	DATA AddC05 / 29,30/! Load Condition for Quartic (nQd = 5) tipForce freeend dis3
!---------------------------
!	DATA AddC06 / 69,70,71,72/! Load Condition for Quintic (nQd = 6) tipForce freeend dis3  FOR CUBIC
	DATA AddC06 / 35,36/! Load Condition for Quintic (nQd = 6) tipForce freeend dis3		FOR LINEAR
!------------------------------------
	Fact = -1.D0
	if (nQd1 == 5) Then	! Quartic 
		do 10 i = 1,nLod
   		LocF(i) = AddC05(i)
   		ValF(i) = 0.5D0*Fact
!   		ValF(i) = tupi
   10		continue
	elseif (nQd1 == 6) Then	! Quintic 
		do 40 i = 1,nLod
   		LocF(i) = AddC06(i)
   		ValF(i) = 0.50D0*Fact		!For LINEAR
!   		ValF(i) = 0.25D0*Fact		!For CUBIC
   40		continue
	endif
!	-----------   	
	return
	end
