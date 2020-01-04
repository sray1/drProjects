	Subroutine Get_SupportedDOFs(Sx,nSup,nQc1,nQc2,iCont,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!==========================================================================================
	include 'Drill.h'
	include 'Examples.h'
!==========================================================================================
	integer			Sx
	Dimension		Sx(nSup)
!-------------------------------------------- for Check with Quintic
	if(bDrill) then
		SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			call Get_SupportedDOFs_Pal_D(Sx,nSup,nQc1,nQc2,iCont,iOut)
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
			call Get_SupportedDOFs_Pal_D(Sx,nSup,nQc1,nQc2,iCont,iOut)
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
			call Get_SupportedDOFs_Str_D(Sx,nSup,nQc1,nQc2,iCont,iOut)
		CASE (4)							! 3D Curved Cantilev.LINMOD:Ex_4
!			call Get_SupportedDOFs_LIN_D(Sx,nSup,nQc,iCont,iOut)
		CASE (5)							! 3D Curved Cantilev. Bathe:Ex_5
!			call Get_SupportedDOFs_Bat_D(Sx,nSup,nQc,iCont,iOut)
		CASE (6)							! 2D STr.Cantilev. ARGYRIS :Ex_6
!			call Get_SupportedDOFs_Bat_D(Sx,nSup,nQc,iCont,iOut)
		CASE (7:10)    ! FALL THRO'           other: Ex_7 
		CASE DEFAULT
			return
		END SELECT
	else
		SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			call Get_SupportedDOFs_Pal(Sx,nSup,nQc1,nQc2,iCont,iOut)
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
			call Get_SupportedDOFs_Pal(Sx,nSup,nQc1,nQc2,iCont,iOut)
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
			call Get_SupportedDOFs_Str(Sx,nSup,nQc1,nQc2,iCont,iOut)
		CASE (4)							! 3D Curved Cantilev.LINMOD:Ex_4
!			call Get_SupportedDOFs_LIN(Sx,nSup,nQc,iCont,iOut)
		CASE (5)							! 3D Curved Cantilev. Bathe:Ex_5
!			call Get_SupportedDOFs_Bat(Sx,nSup,nQc,iCont,iOut)
		CASE (6)							! 2D STr.Cantilev. ARGYRIS :Ex_6
!			call Get_SupportedDOFs_Bat(Sx,nSup,nQc,iCont,iOut)
		CASE (7:10)    ! FALL THRO'           other: Ex_7 
		CASE DEFAULT
			return
		END SELECT
	endif
!	=======================================================
!-----------   	
	return
	end
