	Subroutine Update_StepQc(Qd,nQd,Qc,nQc,Iout)
!
!
!	Inputs
!		Qd(nQd)		= Latest displacement controls: state vector
!		Qc(1,nQc)	= Bezier X-Coordinates
!					=	(qc00x qc10x...qc33x)
!		Qc(2,nQc)	= Bezier Y-Coordinates
!					=	(qc00y qc10y...qc33y)
!		Qc(3,nQc)	= Bezier Z-Coordinates
!					=	(qc00z qc10z...qc33z)
!		Nint		= Number of Gauss Points
!		Iout		= Error Output file#
!		 	
!	Outputs 
!		Stif(nStif,nStif)	= Desired Stiffness Matrix
!		bFors(nStif)		= Desired Body force Vector Integrals
!		StifK(nStif)		= Desired kLamda Stiffness last column Vector Integrals
!		Trace		= trace of the matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
	Real(kind=8)	Qc       ,Qd           
	Dimension		Qc(3,nQc),Qd(nQd)
!------------------------------
	common/LoadStepIter/iStep,iNut,bReset
!------------------------------ Initialize
	DATA zero/0.D0/,one/1.0D0/ 
!---------------------------------------------------------- Loop over ControlPts
	do 50 i = 1,3
	do 10 j = 1,nQc
	k = j+ (i-1)*nQc
	Qc(i,j) = Qc(i,j) + Qd(k)
   10	continue
   50 continue
!============================================
!	-------------------------------------------------------- Debug 
	iPrt = 0
	if((iStep == 2).AND.(iNut == 2)) Then
		iPrt = 0
		call DumpVar(iOut)
		call DumpArray(Qd,nStif,"Qd",iPrt,iOut)
		call DumpMatrix(Qc,3,nQc,"Qc",iPrt,iOut)
	endif
!	-------------------------------------------------------- Debug : End
!-----------
	return
	end   		
	   		