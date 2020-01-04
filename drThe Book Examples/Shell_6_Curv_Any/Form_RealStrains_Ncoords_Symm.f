	Subroutine Form_RealStrains_Ncoords_Symm(rE,nE,iout)
!	----------------------------------------------------------------------------- 
!	Inputs
! 	
!	Outputs 
!		rE(nE)			= Real Strains in n-Mn-Qn Coordinates SYMMETRIC 12 = 21
!	------------------------------------------------------------
	Implicit Real(kind=8) (a-h,o-z)
!
!============================================
	include 'LoadStepIter.h'
!============================================
	Real(kind=8)	rE                        
	Dimension		rE(nE)
!============================================
	DATA zero/0.D0/,one/1.0D0/,half/0.5D0/,three/3.0D0/ 
!	====================================== Debug
	if((iStep == 7).AND.(iNut == 2)) Then
		abc = 1
	endif
!------------------------------------------------------------------------------ SYMMETRIC RealStrain
	rE(2)	= half*(rE(2) + rE(7))	! beta12
	rE(7)	= rE(2) 
	rE(4)	= half*(rE(4) + rE(10))	! ki12
	rE(10)	= rE(4)
!		-------------------------------------------------------- Debug 
		if((iStep == 9999).AND.(iNut == 2)) Then
			iPrt = 1
!			call DumpVar(iOut)
			call DumpStringVar("Beg:FormRealStrains_SYMM",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
			call DumpRealArray(rE,nE,"rE:RealStrains_N",iPrt,iOut)
			call DumpStringVar("End:FormRealStrains_SYMM",iPrt,iOut)
			iPrt = 0
		endif
!		-------------------------------------------------------- Debug : End
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Real Strains..."/2X,3(f10.7,1X))
	end
