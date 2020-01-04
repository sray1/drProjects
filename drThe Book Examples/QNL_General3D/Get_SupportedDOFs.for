	Subroutine Get_SupportedDOFs(Sx,nSup,nQc,iCont,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!
	integer			Sx
	Dimension		Sx(nSup)
!
	common/Examples/cEx(10),nEx
	character (30)	cEx
!-------------------------------------------- for Check with Quintic
	SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			call Get_SupportedDOFs_Pal(Sx,nSup,nQc,iCont,iOut)
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
			call Get_SupportedDOFs_Pal(Sx,nSup,nQc,iCont,iOut)
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
			call Get_SupportedDOFs_Str(Sx,nSup,nQc,iCont,iOut)
		CASE (4)							! 3D Curved Cantilev.LINMOD:Ex_4
			call Get_SupportedDOFs_LIN(Sx,nSup,nQc,iCont,iOut)
		CASE (5)							! 3D Curved Cantilev. Bathe:Ex_5
			call Get_SupportedDOFs_Bat(Sx,nSup,nQc,iCont,iOut)
		CASE (6:10)    ! FALL THRO'           other: Ex_5 
		CASE DEFAULT
			return
	END SELECT
!	=======================================================
!-----------   	
	return
	end
