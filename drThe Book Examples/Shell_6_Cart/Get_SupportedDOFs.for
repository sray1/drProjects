	Subroutine Get_SupportedDOFs(Sx,nSup,nQc1,nQc2,iCont,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!==========================================================================================
	include 'Drill.h'
	include 'Examples.h'
!==========================================================================================
	integer			Sx
	Dimension		Sx(nSup)
!-------------------------------------------- for Check with Quintic
	SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			call Get_SupportedDOFs_Pal(Sx,nSup,nQc1,nQc2,iCont,iOut)
		CASE (2)
		if(bDrill) then							! PALAZOTTO:c0=0.01:        Ex_2
			call Get_SupportedDOFs_Pal_D(Sx,nSup,nQc1,nQc2,iCont,iOut)
		else
			call Get_SupportedDOFs_Pal(Sx,nSup,nQc1,nQc2,iCont,iOut)
		endif
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
			call Get_SupportedDOFs_Str(Sx,nSup,nQc1,nQc2,iCont,iOut)
		CASE (4)							! 3D Curved Cantilev.LINMOD:Ex_4
!			call Get_SupportedDOFs_LIN(Sx,nSup,nQc,iCont,iOut)
		CASE (5)							! 3D Curved Cantilev. Bathe:Ex_5
!			call Get_SupportedDOFs_Bat(Sx,nSup,nQc,iCont,iOut)
		CASE (6)							! 2D STr.Cantilev. ARGYRIS :Ex_6
!			call Get_SupportedDOFs_Bat(Sx,nSup,nQc,iCont,iOut)
		CASE (7:9)    ! FALL THRO'           other: Ex_7 
			return
		CASE (10)							! Hemisphere w/ hole       Ex_10
			call Get_SupportedDOFs_Hem(Sx,nSup,nQc1,nQc2,iCont,iOut)
		CASE (11)							! Scodelis Low             Ex_11
			call Get_SupportedDOFs_Sco(Sx,nSup,nQc1,nQc2,iCont,iOut)
		CASE (12)							! 2D Str. Cantil-Tip Twist:Ex_12
		if(bDrill) then							
			call Get_SupportedDOFs_Str_TT_D
     &						(Sx,nSup,nQc1,nQc2,iCont,iOut)
		else
			call Get_SupportedDOFs_Str_TT
     &						(Sx,nSup,nQc1,nQc2,iCont,iOut)
		endif
		CASE DEFAULT
			return
	END SELECT
!	=======================================================
	return
	end
