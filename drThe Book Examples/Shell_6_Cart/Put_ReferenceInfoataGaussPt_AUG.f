	Subroutine Put_ReferenceInfoataGaussPt_AUG
     &							(Ri,Rj,iInt,jInt,T,B,Nel,nRec)
!	----------------------------------------------------------------------------- 
!	Inputs
!		nDim				= 3
!		nCInt					= no. of Gauss Integration points * nDim (=3)
!								= nDim*nInt
!		Ri					= Current Gauss location Pt ith.
!		Rj					= Current Gauss location Pt jth.
!		nInt				= Total Gauss pts = iInt*jInt
!		iInt				= Current Gauss Index along 1
!		jInt				= Current Gauss Index along 2
!		nDof				= 12
!		nDof2				= 18
!		nStif				= 6*nQd1*nQd2
! 	
!	Outputs 
!		C0(nDim)		= Ref Curvature:for the current Gauss Pt.
!		T(nDof,nStif)	= Dof Transformmation Control matrix
!		B(nDof2,nStif)	= Dof2 Transformmation Control matrix
!		RutAhat			= sq. root of Determinant of shell Jacobian
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!	======================
	include 'SizeVar.h'
	include 'Scratch_AUG.h'
	include 'files.h'
!	======================
!	Input Variables & Arrays
!
!
!	Working Variables & Arrays
!
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	B          ,T     
	Dimension		B(nDof2,nStifEL),T(nDof,nStifEL)
!	==========================================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/,onm/-1.0D0/ 
!	-------------------------------------------------------------------- T & B mats for Lamda Augment 
	inquire(iRefPro2A,NEXTREC = nRecShould)
	if(nRec == nRecShould) then
		call Form_B_and_Tmatrices(T,B,ri,rj,nRec)
	endif

!		-------------------------------------------------------- Debug 
		iPrt = 0
		call DumpStringVar
     &			("Beg:Put_ReferenceInfoataGaussPt_AUG",iPrt,iOut)
		call DumpIntegerVar(iInt,"GaussIndex dir_i",iPrt,iOut)
		call DumpIntegerVar(jInt,"GaussIndex dir_j",iPrt,iOut)
		call DumpRealVar(Ri,"GaussPt. dir_i",iPrt,iOut)
		call DumpRealVar(Rj,"GaussPt. dir_j",iPrt,iOut)
		call DumpIntegerVar(nCInt,"nCInt",iPrt,iOut)
		call DumpStringVar
     &			("End:Put_ReferenceInfoataGaussPt_AUG",iPrt,iOut)
!		-------------------------------------------------------- Debug : End
!---------------------------------------------------------- Write:
!	iPrt = 0
!	if (iPrt == 1) Then
!		write(Iout,1000) nDim,nQc1,nQc2,
!     &		(i,j,(Qc(k,i,j),j=1,nQc),i=1,nDim)
!	endif
!----------------------------------------------------------
	return
!
 1000 format("QC(",I1,",",I1,"): "/
     &        3(I5,5X,6(f10.6,1X)/) )
	end
