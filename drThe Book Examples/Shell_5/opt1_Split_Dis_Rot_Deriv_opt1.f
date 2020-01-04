	Subroutine Split_Dis_Rot_Deriv(Qd,nStif,B,Iout)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!	Notes:	Nint should be atleast 2
!
!	Inputs
!		Qd(nStif)	= Latest displacement controls: state vector
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
	include 'ShellParams.h'
!============================================
!
!	Input Variables & Arrays
!
	Real(kind=8)	Qd                   
	Dimension		Qd(nStif)
!	
!	Working Variables & Arrays	
!
	Real(kind=8)	HD          
	Dimension		HD(nDof2)
	Real(kind=8)	DD   ,RR   ,DP1   ,Rp1   ,Dp2   ,Rp2                
	Dimension		DD(3),RR(3),DP1(3),Rp1(3),Dp2(3),Rp2(3)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	B             ,T     
	Dimension		B(nDof2,nStif),T(nDof,nStif)
!	=============================== 
	DATA zero/0.D0/,one/1.0D0/,onm/-1.0D0/ 
	DATA NC/3/
!	//////////////////////
!--------------------------------------------------------------------- DisRots & Derivatives
	HD		= MATMUL(B,Qd)
!============================================================== 
	iPrt = 0
	if(iPrt == 1) then
		call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
		call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
		call DumpStringVar("Beg:Split_Dis_Rot_Deriv",iPrt,iOut)
		call DumpRealArray(Hd,nDof2,"HD array",1,iOut)
		call DumpStringVar("End:Split_Dis_Rot_Deriv",iPrt,iOut)
	endif
	iPrt = 0
!============================================================== 
	nG =nDof2
!	------------------------------------------------------------------- H(dHat):Incremental
	call VectorExtract_Vector(HD,nG,DD,nC,1,Iout)		!displacement
	call VectorExtract_Vector(HD,nG,RR,nC,4,Iout)		!rotation
	call VectorExtract_Vector(HD,nG,Dp1,nC,7,Iout)	    !displacementPrimed
	call VectorExtract_Vector(HD,nG,Rp1,nC,10,Iout)	    !rotationPrimed
	call VectorExtract_Vector(HD,nG,Dp2,nC,13,Iout)	    !displacementPrimed
	call VectorExtract_Vector(HD,nG,Rp2,nC,16,Iout)	    !rotationPrimed
!	=============================================== Modify to use beam formulas .
!	---------------------------------- direction 1
	Di1		= DD
	Ro1		= RR
	Dp11	= Dp1
	Rp11	= Rp1
!	---------------------------------- direction 2
	Di2(1)	= DD(2)
	Di2(2)	= DD(1)
	Di2(3)	= -DD(3)
!
	Ro2(1)	= RR(2)
	Ro2(2)	= RR(1)
	Ro2(3)	= -RR(3)
!
	Dp21(1)	= Dp2(2)
	Dp21(2)	= Dp2(1)
	Dp21(3)	= -Dp2(3)
!
	Rp21(1)	= Rp2(2)
	Rp21(2)	= Rp2(1)
	Rp21(3)	= -Rp2(3)
!============================================================== .
!
	return
!
 1010 format("Full Stiffness Matrix:Stif(",I2,",",I2,")"/)
 1020 format(I5/(6(12(f8.1,1X)/)/))
 1030 format("DMat(12,12)"/(12(f7.0,1X)))
 1040 format(2X, "EDG Matrix(18,18)"/(I3,18(f5.0,1X)))
	end   		
	   		