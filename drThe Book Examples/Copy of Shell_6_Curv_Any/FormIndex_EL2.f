	Subroutine FormIndexEL_2(Indx,nStifEL,iOut)
!															NEEDTOCHANGE
	Implicit Real(kind=8) (a-h,o-z)
!	==============================
!	Coerced Isoparametric Quartic Element
!
!
!	Outputs 
!		Indx(nStifEl)	= Indx of assembly for Element 2
!
	include 'Examples.h'
!	==============================
	integer Indx(nStifEL)
!
!	Indices of location in global stiffness
!
!-------------------------------------------- for Check with Quintic
	SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
!			call Get_Indx_Pal(LocF,ValF,nLod,nQc1,nQc2,iCont,iOut)
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
!			call Get_Indx_Pal_D(LocF,ValF,nLod,nQc1,nQc2,iCont,iOut)
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
!			call Get_Indx_Str(LocF,ValF,nLod,nQc1,nQc2,iCont,iOut)
		CASE (4)							! 3D Curved CantilevLINMOD: Ex_4
!			call Get_Loads_LIN(Qf,nQ,iOut)
		CASE (5)							! 3D Curved Cantilev.Bathe: Ex_5
!			call Get_Loads_Bat(Qf,nQ,iOut)
		CASE (6)							! 2D Frame Buckling_Argyris:Ex_6
!			call Get_Loads_ARG(Qf,nQ,iOut)
		CASE (7:10)    ! FALL THRO'           other: Ex_7-10... 
			return
		CASE (12)							! 2D Str. Cantil-Tip Twist:Ex_12
			call FormIndexEL_2Str_TT(Indx,nStifEL,iOut)
		CASE DEFAULT
			return
	END SELECT
!	=======================================================
	write(iOut,1000)
	write(iOut,1010) nStifEL,(Indx(i),i = 1,nStifEL)
!   		 
	return
 1000 Format(/2x,"Just before Leaving: FormIndexEL_2"/)
 1010 Format(/2x,"Indices for Element#2 for Global Assembly: 1x"I3/
     &										3(5(2x,I7)/) )
	end   		