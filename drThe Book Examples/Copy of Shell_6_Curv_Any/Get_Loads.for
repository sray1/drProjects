	Subroutine Get_Loads(LocF,ValF,mLod,mQc1,mQc2,jCont,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!==========================================================================================
	include 'Drill.h'
	include 'Examples.h'
	include 'SizeVar.h'
!==========================================================================================
	Real*8			ValF      
	Dimension		ValF(mLod)
	integer			LocF
	Dimension		LocF(mLod)
!-------------------------------------------- for Check with Quintic
	SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			call Get_Loads_Pal(LocF,ValF,mLod,mQc1,mQc2,jCont,iOut)
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
		if(bDrill) then							! PALAZOTTO:c0=0.01:        Ex_2
			call Get_Loads_Pal_D(LocF,ValF,mLod,mQc1,mQc2,jCont,iOut)
		else
			call Get_Loads_Pal(LocF,ValF,mLod,mQc1,mQc2,jCont,iOut)
		endif
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
			call Get_Loads_Str(LocF,ValF,mLod,mQc1,mQc2,jCont,iOut)
		CASE (4)							! 3D Curved CantilevLINMOD: Ex_4
!			call Get_Loads_LIN(Qf,nQ,iOut)
		CASE (5)							! 3D Curved Cantilev.Bathe: Ex_5
!			call Get_Loads_Bat(Qf,nQ,iOut)
		CASE (6)							! 2D Frame Buckling_Argyris:Ex_6
!			call Get_Loads_ARG(Qf,nQ,iOut)
		CASE (7:9)    ! FALL THRO'           other: Ex_7-10... 
			return
		CASE (10)							! Hemisphere w/ hole       Ex_10
			if(nElem == 1) then
				call 
     &			Get_Loads_Hem(LocF,ValF,mLod,mQc1,mQc2,jCont,iOut)
			elseif(nElem == 4) then
				call 
     &			Get_Loads_Hem_4(LocF,ValF,mLod,mQc1,mQc2,jCont,iOut)
			endif
		CASE (11)							! Scordelis Low:           Ex_11
			call Get_Loads_Sco(LocF,ValF,mLod,mQc1,mQc2,jCont,iOut)
		CASE (12)							! 2D Str. Cantil-Tip Twist:Ex_12
		if(bDrill) then							
			call Get_Loads_Str_TT_D
     &							(LocF,ValF,mLod,mQc1,mQc2,jCont,iOut)
		else
			call Get_Loads_Str_TT(LocF,ValF,mLod,mQc1,mQc2,jCont,iOut)
		endif
		CASE DEFAULT
			return
	END SELECT
!	=======================================================
!-----------   	
	return
	end
