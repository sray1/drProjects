	Subroutine Get_Loads(Qf,nQ,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!
	Dimension		Qf(nQ)
!
	common/Examples/cEx(10),nEx
	character (30)	cEx
!-------------------------------------------- for Check with Quintic
	SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			call Get_Loads_Pal(Qf,nQ,iOut)
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
			call Get_Loads_Pal(Qf,nQ,iOut)
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
			call Get_Loads_Str(Qf,nQ,iOut)
		CASE (4)							! 3D Curved CantilevLINMOD: Ex_4
			call Get_Loads_LIN(Qf,nQ,iOut)
		CASE (5)							! 3D Curved Cantilev.Bathe: Ex_5
			call Get_Loads_Bat(Qf,nQ,iOut)
		CASE (6:10)    ! FALL THRO'           other: Ex_5... 
		CASE DEFAULT
			return
	END SELECT
!	=======================================================
!-----------   	
	return
	end
