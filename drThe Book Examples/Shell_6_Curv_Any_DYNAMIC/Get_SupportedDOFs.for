	Subroutine Get_SupportedDOFs(Sx,mSup,mQc1,mQc2,jCont,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!==========================================================================================
	include 'Drill.h'
	include 'Examples.h'
	include 'SizeVar.h'
!==========================================================================================
	integer			Sx
	Dimension		Sx(mSup)
!-------------------------------------------- for Check with Quintic
	SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			call Get_SupportedDOFs_Pal(Sx,mSup,mQc1,mQc2,jCont,iOut)
		CASE (2)
		if(bDrill) then							! PALAZOTTO:c0=0.01:        Ex_2
			call Get_SupportedDOFs_Pal_D(Sx,mSup,mQc1,mQc2,jCont,iOut)
		else
			call Get_SupportedDOFs_Pal(Sx,mSup,mQc1,mQc2,jCont,iOut)
		endif
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
			call Get_SupportedDOFs_Str(Sx,mSup,mQc1,mQc2,jCont,iOut)
		CASE (4)							! 3D Curved Cantilev.LINMOD:Ex_4
!			call Get_SupportedDOFs_LIN(Sx,mSup,nQc,jCont,iOut)
		CASE (5)							! 3D Curved Cantilev. Bathe:Ex_5
!			call Get_SupportedDOFs_Bat(Sx,mSup,nQc,jCont,iOut)
		CASE (6)							! 2D STr.Cantilev. ARGYRIS :Ex_6
!			call Get_SupportedDOFs_Bat(Sx,mSup,nQc,jCont,iOut)
		CASE (7:9)    ! FALL THRO'           other: Ex_7 
			return
		CASE (10)							! Hemisphere w/ hole       Ex_10
			if(nElem == 1) then
				call 
     &			Get_SupportedDOFs_Hem(Sx,mSup,mQc1,mQc2,jCont,iOut)
			elseif(nElem == 4) then
				call 
     &			Get_SupportedDOFs_Hem_4(Sx,mSup,mQc1,mQc2,jCont,iOut)
			endif
		CASE (11)							! Scodelis Low             Ex_11
			call Get_SupportedDOFs_Sco(Sx,mSup,mQc1,mQc2,jCont,iOut)
		CASE (12)							! 2D Str. Cantil-Tip Twist:Ex_12
		if(bDrill) then							
			call Get_SupportedDOFs_Str_TT_D
     &						(Sx,mSup,mQc1,mQc2,jCont,iOut)
		else
			call Get_SupportedDOFs_Str_TT
     &						(Sx,mSup,mQc1,mQc2,jCont,iOut)
		endif
		CASE DEFAULT
			return
	END SELECT
!	=======================================================
	return
	end
