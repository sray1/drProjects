	Subroutine Form_StrainConstrain(constrain,nC,nDof,iOut)

	Implicit Real(kind=8) (a-h,o-z)
!============================================
	include 'SizeVar.h'
	include 'LoadStepIter.h'
	include 'CurParams.h'
	include 'BeamParams.h'
	include 'ShellParams.h'
	include 'LogParams.h'
!==============================================
	Real(kind=8)	v1   ,v2                            
	Dimension		v1(3),v2(3)
	Real(kind=8)	Hat1   ,Hat2   ,rE                                                    
	Dimension		Hat1(3),Hat2(3),rE(12) 
	Equivalence (rE(1),rE1(1)),(rE(7),rE2(1))
!==========================================		
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	DATA nC/3/
	DATA Hat1/1.0D0,0.D0,0.D0/
	DATA Hat2/0.0D0,1.D0,0.D0/
!============================================
!	nCMat	= 12	
!	nC		= 3	
!	nDof	= 6	
!	nDof2	= 18
	nC		= nDim	
!	====================================== Debug
!	if((iStep == 1).AND.(iNut == 2)) Then
	if((iStep == 1).AND.(iNut == 2)) Then
		abc = 1
	endif
!-------------------------------------------------------------------------------------------- Prepare: theta constants
	Di		= DD
	Ro		= RR
!	----------------------------------------
	call FormRotationMatrix(Ro,AMat,nC,Iout)	! rodrigues
!	----------------------------------------
	AugMult		= 0.D0
!======================================================================================= Direction 1
	C0		= C01
	Hat		= Hat1
	Dp		= Dp1
	Rp		= Rp1
!	------------------------------------------------------------------- AA
	call CrossProduct(C0,Di,v1,Iout)		! [k01]d = k01 x d
	call VectorAdd(Hat,Dp,v2,nC,Iout)		!e-vector
	call VectorAdd(v1,v2,AA,nC,Iout)		!a-vector
!	--------------------------------------------------- Real Strains (n-Mn-Qn coords)
	call FormRealStrains_Ncoords(rE1,nDof,3,1,Iout)	! strain in shell coords
!======================================================================================= Direction 2
	C0		= C02
	Hat		= Hat2
	Dp		= Dp2
	Rp		= Rp2
!	------------------------------------------------------------------- AA
	call CrossProduct(C0,Di,v1,Iout)		! [k01]d = k01 x d
	call VectorAdd(Hat,Dp,v2,nC,Iout)		!e-vector
	call VectorAdd(v1,v2,AA,nC,Iout)		!a-vector
!	--------------------------------------------------- Real Strains (n-Mn-Qn coords)
	call FormRealStrains_Ncoords(rE2,nDof,3,2,Iout)	! strain in shell coords
!======================================================================================= constrain
	constrain = re(2) - re(7)
!
!	done
!
!		-------------------------------------------------------- Debug 
	iPrt = 0
	if(iprt == 1) then
		call DumpStringVar("Beg:Check_StrainConvergence",iPrt,iOut)
		call DumpRealVar(Re(2),"Beta12",iPrt,iOut)
		call DumpRealVar(Re(7),"Beta21",iPrt,iOut)
		call DumpRealVar(Re(2)-Re(7),"Beta12-21",iPrt,iOut)
		call DumpStringVar("End:Check_StrainConvergence",iPrt,iOut)
	endif
	iPrt = 0
!		-------------------------------------------------------- Debug : End
	endif 
!	========
	return
	end
