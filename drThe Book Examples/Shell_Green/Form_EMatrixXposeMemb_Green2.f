	Subroutine Form_EMatrixXposeMemb_Green2(EMat,nG,nE,nC,Iout)
!	----------------------------------------------------------------------------- 
!	Inputs
!		AMat(nC,nC)		= Rotation Matrix
!		nG				= 18
!		C0i(nC)			= initial Curvature vector = k0i for iCurDir i
!		nC				= 3 (= nDim)
!		nE				= 8
!		W(nC,nC)		= W Matrix
!		R1(nC,nC)		= R1 Matrix
!		R2(nC,nC)		= R2 Matrix
!		AAi(nC)			= e + [k0i]d
!		CKi(nC)			= k0i + ki = k0i + W(thetaPrimed)
! 	
!	Outputs 
!		EMat(nG,nE)	= EMat Matrix (18,8)	! Transpose(EMat)
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!============================================
	include 'Material.h'
	include 'LoadStepIter.h'
	include 'CurParams.h'
!	include 'ThetaConstants.h'
	include 'BeamParams.h'
	include 'ShellParams.h'
	include 'EBlocks.h'
!==============================================
	Real(kind=8)	EMat       !,TAMAT     ,TWMAT                      
	Dimension		EMat(nG,nE)!,TAMAT(3,3),TWMAT(3,3)
	Real(kind=8)	AC11   ,AC22   ,AC12   ,AC21                         
	Dimension		AC11(3),AC22(3),AC12(3),AC21(3)

	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/,onem/-1.0D0/ 
!	--------------------------------------------- aabeta cross Coalfa
	call CrossProduct(AA1,C01,AC11,Iout)
	call CrossProduct(AA2,C02,AC22,Iout)
	call CrossProduct(AA1,C02,AC12,Iout)
	call CrossProduct(AA2,C01,AC21,Iout)
!	============================================================================ FORM EMatrix:MEMMBRANE 
!	                                                                                1,2,3
	do 10 j = 1,3

	EMAT(j   ,1  )  = EMAT(j   ,1  ) + Two * AC11(j)				! dbar term
	EMat(j   ,2  )	= EMAT(j   ,2  ) + Two * AC22(j)
	EMat(j   ,3  )	= EMAT(j   ,3  ) + AC12(j) + AC21(j)
!			
	EMAT(j+ 6,1  )  = EMAT(j+ 6,1  ) + Two * AA1(j)					! dbar,1 term
	EMat(j+12,2  )	= EMat(j+12,2  ) + Two * AA2(j)					! dbar,2 term
	EMat(j+ 6,3  )	= EMat(j+ 6,3  ) + AA2(j)						! dbar,1 term
	EMat(j+12,3  )	= EMat(j+12,3  ) + AA1(j)						! dbar,2 term
!			
   10 continue
!	============================================================================ END EMatrix:MEMBRANE
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1030) (i,(EMat(i,j),j = 1,nG),i=1,nE)
	endif
	iPrt = 0
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Current vector..."/2X,3(f10.7,1X))
 1020 format(2X,A3," Matrix(3,3)"/( (I3,3(f10.2,1X))  ))
 1030 format(2X, "E Matrix(8,18)"/(I3,18(f5.0,1X)))
	end
