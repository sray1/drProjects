	Subroutine Get_Loads(LocF,ValF,nLod,nQc1,nQc2,iCont,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!==========================================================================================
	include 'Drill.h'
	include 'Examples.h'
!==========================================================================================
	Real*8			ValF      
	Dimension		ValF(nLod)
	integer			LocF
	Dimension		LocF(nLod)
!-------------------------------------------- for Check with Quintic
	if(bDrill) then
		SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			call Get_Loads_Pal_D(LocF,ValF,nLod,nQc1,nQc2,iCont,iOut)
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
			call Get_Loads_Pal_D(LocF,ValF,nLod,nQc1,nQc2,iCont,iOut)
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
			call Get_Loads_Str_D(LocF,ValF,nLod,nQc1,nQc2,iCont,iOut)
		CASE (4)							! 3D Curved CantilevLINMOD: Ex_4
!			call Get_Loads_LIN_D(Qf,nQ,iOut)
		CASE (5)							! 3D Curved Cantilev.Bathe: Ex_5
!			call Get_Loads_Bat_D(Qf,nQ,iOut)
		CASE (6)							! 2D Frame Buckling_Argyris:Ex_6
!			call Get_Loads_ARG_D(Qf,nQ,iOut)
		CASE (7:10)    ! FALL THRO'           other: Ex_5... 
		CASE DEFAULT
			return
		END SELECT
	else
		SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			call Get_Loads_Pal(LocF,ValF,nLod,nQc1,nQc2,iCont,iOut)
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
			call Get_Loads_Pal(LocF,ValF,nLod,nQc1,nQc2,iCont,iOut)
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
			call Get_Loads_Str(LocF,ValF,nLod,nQc1,nQc2,iCont,iOut)
		CASE (4)							! 3D Curved CantilevLINMOD: Ex_4
!			call Get_Loads_LIN(Qf,nQ,iOut)
		CASE (5)							! 3D Curved Cantilev.Bathe: Ex_5
!			call Get_Loads_Bat(Qf,nQ,iOut)
		CASE (6)							! 2D Frame Buckling_Argyris:Ex_6
!			call Get_Loads_ARG(Qf,nQ,iOut)
		CASE (7:10)    ! FALL THRO'           other: Ex_5... 
		CASE DEFAULT
			return
		END SELECT
	endif
!	=======================================================
!-----------   	
	return
	end
