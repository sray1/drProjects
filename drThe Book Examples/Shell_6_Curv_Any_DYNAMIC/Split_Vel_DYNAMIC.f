	Subroutine Split_Vel_RotV_DYNAMIC(Qv,nStif,T,Iout)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!	Notes:	Nint should be atleast 2
!
!	Inputs
!		Qv(nStif)	= Latest velocity controls: state vector
!		Iout		= Error Output file#
!		 	
!	Outputs 
!		Trace		= trace of the matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!	===========================
	include 'CurParams.h'
	include 'SizeVar.h'
	include 'LoadStepIter.h'
!	include 'ShellParams.h'
	include 'ShellParams_DYNAMIC.h'
!============================================
!
!	Input Variables & Arrays
!
	Real(kind=8)	Qv                   
	Dimension		Qv(nStif)
!	
!	Working Variables & Arrays	
!
	Real(kind=8)	HD          
	Dimension		HD(nDof)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	T     
	Dimension		T(nDof,nStif)
!	=============================== 
	DATA zero/0.D0/,one/1.0D0/,onm/-1.0D0/ 
	DATA NC/3/
!	//////////////////////
!--------------------------------------------------------------------- Velocities
	HD		= MATMUL(T,Qv)
!============================================================== 
	iPrt = 0
		if((iStep == 1).AND.(iNut == 2)) Then
			iPrt = 0
		endif
	if(iPrt == 1) then
		call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
		call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
		call DumpStringVar("Beg:Split_Vel_DYNAMIC",iPrt,iOut)
		call DumpRealArray(Hd,nDof,"HDVel array",1,iOut)
		call DumpStringVar("End:Split_Vel_DYNAMIC",iPrt,iOut)
	iPrt = 0
	endif
!============================================================== 
	nG =nDof	! = 6
!	------------------------------------------------------------------- H(dHat):Incremental
	call VectorExtract_Vector(HD,nG,TVel,nC,1,Iout)		!Trans. Velo
	call VectorExtract_Vector(HD,nG,RotV,nC,4,Iout)		!ThetaDot
!	=============================================== 
	return
!
 1010 format("Full Stiffness Matrix:Stif(",I2,",",I2,")"/)
 1020 format(I5/(6(12(f8.1,1X)/)/))
 1030 format("DMat(12,12)"/(12(f7.0,1X)))
 1040 format(2X, "EDG Matrix(18,18)"/(I3,18(f5.0,1X)))
	end   		
	   		