	Subroutine Put_ReferenceInfoataGaussPt
     &							(Qc,Ri,Rj,iInt,jInt,T,B,Nel,nRec)
!     &							(Qc,nDim,nQc1,nQc2,Ri,Rj,iInt,jInt,
!     &								T,B,nDof,nDof2,nStif,Nel,nRec)
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
!	======================
	include 'SizeVar.h'
	include 'Scratch.h'
	include 'CurParams.h'
	include 'LogParams.h'
	include 'files.h'
	include 'Examples.h'
!	======================
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
	Real(kind=8)	B          ,T     
	Dimension		B(nDof2,nStifEL),T(nDof,nStifEL)
	Real(kind=8)	ftmin   ,ftmax   ,fpmin   ,fpmax        
	Dimension	    ftmin(4),ftmax(4),fpmin(4),fpmax(4)
	character*3		readstat
	LOGICAL bReset
!	========================================================== HARDCODED for  1x1 element
!	DATA ftmin	/0.0D0,0.5D0,0.0D0,0.5D0/
!	DATA ftmax	/0.5D0,1.0D0,0.5D0,1.0D0/
!	DATA fpmin	/0.0D0,0.0D0,0.2D0,0.2D0/
!	DATA fpmax	/0.5D0,0.5D0,1.0D0,1.0D0/
!	============================================================================== 1X1 END
!	========================================================== HARDCODED for  2x2 elements
	DATA ftmin	/0.0D0,0.5D0,0.0D0,0.5D0/
	DATA ftmax	/0.5D0,1.0D0,0.5D0,1.0D0/
	DATA fpmin	/0.0D0,0.0D0,0.5D0,0.5D0/
	DATA fpmax	/0.5D0,0.5D0,1.0D0,1.0D0/
!	============================================================================== 2X2 END
	DATA factp	/0.80D0/
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/,onm/-1.0D0/ 
!	-------------------------------------------------------------------- Curvatures/Det etc 
	piby2 = asin(1.D0)
!
	inquire(iRefPro1,NEXTREC = nRecShould)
	if(nRec == nRecShould) then
		if(nEx == 10) then							!Hemisphere
!	=========================================================================
			if(nElem == 1) then
				tmin = ftmin(Nel)*piby2					! HARDCODED for 90 deg		1x1 elem
				tmax = ftmax(Nel)*2.D0*piby2			! HARDCODED for 90 deg
				pmin = fpmin(Nel)*factp*piby2			! HARDCODED for 90 deg
				pmax = fpmax(Nel)*2.D0*factp*piby2		! HARDCODED for 90 deg
			elseif(nElem == 4) then
				tmin = ftmin(Nel)*piby2					! HARDCODED for 90 deg		2x2 elems
				tmax = ftmax(Nel)*piby2					! HARDCODED for 90 deg
				pmin = fpmin(Nel)*factp*piby2			! HARDCODED for 90 deg
				pmax = fpmax(Nel)*factp*piby2			! HARDCODED for 90 deg
			endif
!				----------------------------
			call Calc_ReferenceProps_Hem(Qc,tmin,tmax,pmin,pmax,
     &											ri,rj,nRec)
!			call Calc_ReferenceProps(Qc,ri,rj,nRec)
		else
			call Calc_ReferenceProps(Qc,ri,rj,nRec)
		endif
	endif
!	-------------------------------------------------------------------- T & B matrices 
	inquire(iRefPro2,NEXTREC = nRecShould)
	if(nRec == nRecShould) then
		call Form_B_and_Tmatrices(T,B,ri,rj,nRec)
!		call Form_B_and_Tmatrices(T,nDof,B,nDof2,nStif,
!     &						nDim,nQd1,nQd2,ri,rj,nRec)
	endif

!		-------------------------------------------------------- Debug 
		iPrt = 0
		call DumpStringVar
     &			("Beg:Put_ReferenceInfoataGaussPt",iPrt,iOut)
		call DumpIntegerVar(iInt,"GaussIndex dir_i",iPrt,iOut)
		call DumpIntegerVar(jInt,"GaussIndex dir_j",iPrt,iOut)
		call DumpRealVar(Ri,"GaussPt. dir_i",iPrt,iOut)
		call DumpRealVar(Rj,"GaussPt. dir_j",iPrt,iOut)
		call DumpIntegerVar(nCInt,"nCInt",iPrt,iOut)
!			call DumpRealArray(C0,nC,"C0",iPrt,iOut)
		call DumpStringVar
     &				("End:Put_ReferenceInfoataGaussPt",iPrt,iOut)
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
