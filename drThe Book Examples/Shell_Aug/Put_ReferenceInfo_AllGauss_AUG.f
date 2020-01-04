	Subroutine Put_Reference_AllGauss(Qc,T,B,Nel)
!	Subroutine Put_Reference_AllGauss(Qc,nDim,nQc1,nQc2,nQd1,nQd2,
!     &						T,B,nDof,nDof2,nStif,Nel,Nint1,Nint2)
!	----------------------------------------------------------------------------- 
!	Inputs
!		Qc(nDim,nQc1,nQc2)	= Geometry Controls
!		nDim				= 3
!		nQc1					= order of Bezier
!		nQc2					= order of Bezier
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
!	====================
	include 'SizeVar.h'
	include 'CurParams.h'
	include 'LoadStepIter.h'
	include 'files.h'
	include 'LogParams.h'
!	common/LoadStepIter/iStep,iNut,bReset
!      common/files/iFileStiff,Ioutt,IoutDef,IoutEnd,iRotCur
!
!	Input Variables & Arrays
!
	Real(kind=8)	Qc                    
	Dimension		Qc(nDim,nQc1,nQc2)
!
!	Working Variables & Arrays
!
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	B               ,T     
	Dimension		B(nDof2,nStifEL),T(nDof,nStifEL)
	character*3		readstat
	character*5		cOp(2)
!	==========================================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/,onm/-1.0D0/ 
	DATA cOp/"TRUE ","FALSE"/
!	-------------------------------------------------- Curvatures: ko1 & ko2 Options
	if(bOpt1) then
		write(iOut,1010) cOp(1)
	else
		write(iOut,1010) cOp(2)
	endif
	!------------------------------------------------------------------------- Geom:Curvature Vector etc.
	nRec = 0
!	Loop over Gauss Locations
	do 60 iInt = 1,Nint1
	do 60 jInt = 1,Nint2
!	------------------------------ gauss positions
	Ri = GaussPtVal(iInt,Nint1,1) 
	Rj = GaussPtVal(jInt,Nint2,1) 
!	-------------------------------------------------------------------- Curvatures/Det etc 
	nRec = nRec + 1
	call Put_ReferenceInfoataGaussPt
     &							(Qc,Ri,Rj,iInt,jInt,T,B,Nel,nRec)
!     &			(Qc,nDim,nQc1,nQc2,Ri,Rj,iInt,jInt,
!     &				T,B,nDof,nDof2,nStifEL,Nel,nRec)
!		-------------------------------------------------------- Debug 
		iPrt = 0
		if((iStep == 1).AND.(iNut == 2)) Then
			iPrt = 0
			call DumpStringVar("Beg:Put_ReferenceInfo",iPrt,iOut)
			call DumpIntegerVar(iInt,"GaussIndex",iPrt,iOut)
			call DumpRealVar(Ri,"GaussPt.",iPrt,iOut)
			call DumpIntegerVar(jInt,"GaussIndex",iPrt,iOut)
			call DumpRealVar(Rj,"GaussPt.",iPrt,iOut)
			call DumpStringVar("End:Get_ReferenceInfo",iPrt,iOut)
		endif
!		-------------------------------------------------------- Debug : End
   60 continue
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
 1010 format(2x,"Put_Reference_AllGauss: Opt1 = ",A5/)
	end
