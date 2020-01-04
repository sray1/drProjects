	Subroutine Opt1_FormXforms(Iout)
!	----------------------------------------------------------------------------- 
	Implicit Real(kind=8) (a-h,o-z)
!============================================
	include 'LogParams.h'
	include 'Beam2ShellXforms.h'
	include 'Shell2BeamXforms.h'
!==============================================
!
	DATA zero/0.D0/,one/1.0D0/,onem/-1.0D0/ 
!	--------------------------- Corrector for dir 1 based on Engineering or Virtual For/Mom
	A1b = zero
	B1b = zero
	B1k = zero
!	=====================================================================
	if(bEng == .TRUE.) then									! engineering
!	------------------- translational: 
		A1b(1,1) = one
		A1b(2,2) = one
		A1b(3,3) = one
!
		B1b(1,1) = one
		B1b(2,2) = one
		B1b(3,3) = one
!
		C1b = A1b					!C1b = inv A1b
		D1b = B1b					!D1b = inv B1b
!
!	------------------- bending: 
		A1k = A1b
!
		B1k(1,2) = one
		B1k(2,1) = onem				!
		B1k(3,3) = one
!
		C1k = A1k					!C1k = inv A1k
!
		D1k(1,2) = onem
		D1k(2,1) = one				!D1k = inv B1k
		D1k(3,3) = one
!	=================================================================
	else													! virtual 
!	------------------- translational: 
		A1b(1,1) = one
		A1b(2,2) = one
		A1b(3,3) = one
!
		B1b(1,1) = one
		B1b(2,2) = one
		B1b(3,3) = one
!
		C1b = A1b					!C1b = inv A1b
		D1b = B1b					!D1b = inv B1b
!
!	------------------- bending: 
		A1k = A1b
		B1k = B1b
!
		C1k = A1k					!C1k = inv A1k
		D1k = B1k					!D1k = inv B1k
!
	endif
!	--------------------------- Corrector for dir 2 based on Engineering or Virtual For/Mom
	A2b = zero
	B2b = zero
	B2k = zero
	CoA = zero
	CoB = zero
!	=====================================================================
	if(bEng == .TRUE.) then									! engineering
		A2b(1,2) = one
		A2b(2,1) = one			
		A2b(3,3) = onem
!
		B2b(1,2) = one
		B2b(2,1) = one
		B2b(3,3) = onem
!
		C2b = A2b			!C2b = inv A2b
		D2b = B2b			!D2b = inv B2b
!	------------------- bending: 
		A2k = A2b
!
		B2k(1,1) = one
		B2k(2,2) = onem				!one
		B2k(3,3) = onem
!
		C2k = A2k			!C2k = inv A2k
		D2k = B2k			!D2k = inv B2k
!	=================================================================
	else													! virtual 
		A2b(1,2) = one
		A2b(2,1) = one
		A2b(3,3) = onem
!
		B2b(1,2) = one
		B2b(2,1) = one
		B2b(3,3) = onem
!
		C2b = A2b			!C2b = inv A2b
		D2b = B2b			!D2b = inv B2b
!	------------------- bending: 
		A2k = A2b
		B2k = B2b
!
		C2k = A2k			!C2k = inv A2k
		D2k = B2k			!D2k = inv B2k
	endif
!	--------------------------- 
	return
!
	end
