	Subroutine Calc_ReferenceProps(Qc,ri,rj,jCInt)
!	======================================================
!                   n     m-1
!	A1hat = m *  sum {  sum (Dif10*Qij*Bri(ri) ) } Brj(rj)
!                  j=0    i=0
!	======================================================
	Implicit Real(kind=8) (a-h,o-z)
!	====================
	include 'SizeVar.h'
	include 'files.h'
	include 'Scratch.h'
	include 'CurParams.h'
	include 'LogParams.h'
!	====================
	Real(kind=8)	Qc                   
	Dimension		Qc(nDim,nQc1,nQc2)
	Real(kind=8)	X11hat      ,X12hat      ,X22hat         
	Dimension		X11hat(nDim),X12hat(nDim),X22hat(nDim)
	Real(kind=8)	A1      ,A2      ,Atem      ,Btem    
	Dimension		A1(nDim),A2(nDim),Atem(nDim),Btem(nDim)
	Real(kind=8)	A1c1      ,A1c2      ,A2c1      ,A2c2    
	Dimension		A1c1(nDim),A1c2(nDim),A2c1(nDim),A2c2(nDim)
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	----------------------------------------------------------- metric Tensor
	nQcm = MAX(nQc1-1,nQc2-1)
!
	call Calc_A1_Hat(Qc,nDim,nQc1,nQc2,nQcm,ri,rj,A1hat)
!	call VectorNorm(A1hat,A,3,Iout)
!	call ScaleVector(A1hat,uA1hat,1.D0/A,3,Iout)
!
	call Calc_A2_Hat(Qc,nDim,nQc1,nQc2,nQcm,ri,rj,A2hat)
!	call VectorNorm(A2hat,A,3,Iout)
!	call ScaleVector(A2hat,uA2hat,1.D0/A,3,Iout)
!	---------------------------------------------------- unit normal
	call CrossProduct(A1hat,A2hat,xNor,Iout)
	call VectorNorm(xNor,A,3,Iout)
	call ScaleVector(xNor,xNor,1.D0/A,3,Iout)
!	---------------------------------------------------- RootAhat
	call DotProduct(A1hat,A1hat,E,3,Iout)
	call DotProduct(A1hat,A2hat,F,3,Iout)
	call DotProduct(A2hat,A2hat,G,3,Iout)
!
	RutAhat = DSQRT(E*G - F*F)
!	----------------------------------------------------------- curvature Tensor
	X11hat = 0.D0
	X12hat = 0.D0
	X22hat = 0.D0
!
	if(nQc1.gt.2) then		!atleast Quadratic
		call Calc_X11_Hat(Qc,nDim,nQc1,nQc2,nQcm,ri,rj,X11hat)
	endif
	if(nQc2.gt.2) then		!atleast Quadratic
		call Calc_X22_Hat(Qc,nDim,nQc1,nQc2,nQcm,ri,rj,X22hat)
	endif
	if(nQc1.gt.2.AND.nQc2.gt.2) then		!atleast both Quadratic
		call Calc_X12_Hat(Qc,nDim,nQc1,nQc2,nQcm,ri,rj,X12hat)
	endif
!	
	call DotProduct(X11hat,xNor,xL,3,Iout)	! B11hat
	call DotProduct(X12hat,xNor,xM,3,Iout)	! B12hat
	call DotProduct(X22hat,xNor,xN,3,Iout)	! B22hat
!	----------------------------------------------------------- Lines of curvatures
	if (F==0.D0.or.xM==0.d0) then	! already lines of curvatures
		Rho1	= zero		! direction
		Rho2	= zero		! direction
		Cu1		= xL/E		! 1/R1
		Cu2		= xN/G		! 1/R2
!
		ThetaC	= zero
		sT		= zero
		cT		= one
!
	else
		ENmGL		= E*xN - G*xL
		FNmGM		= F*xN - G*xM
		EMmFL		= E*xM - F*xL
		SQ			= DSQRT(ENmGL*ENmGL - 4.D0*FNmGM*EMmFL)
		FNGM2		= 2.D0*FNmGM
!
		Rho1		= (-ENmGL + SQ)/FNGM2
		Rho2		= (-ENmGL - SQ)/FNGM2
!
		EGmFsq		= E*G - F*F
		TEGmFsq		= 2.D0*EGmFsq
		xLNmMsq		= xL*xN - xM*xM
		TFMmENmGL	= 2.D0*F*xM - ENmGL
		SQ		= DSQRT(TFMmENmGL*TFMmENmGL - 4.D0*EGmFsq*xLNmMsq)
		Cu1		= (-TFMmENmGL + SQ)/TEGmFsq 
		Cu2		= (-TFMmENmGL - SQ)/TEGmFsq 
!
		ThetaC	= DATAN(Rho1)
		sT		= DSIN(ThetaC)
		cT		= DCOS(ThetaC)
	endif
!
	iPrt = 0
	if(iPrt == 1) then
		call DumpStringVar("Beg:Calc_ReferenceProps",iPrt,iOut)
		call DumpStringVar("just aft.Cu1,Cu2 etc",iPrt,iOut)
		call DumpRealVar(ThetaC,"ThetaC",iPrt,iOut)
		call DumpRealVar(Cu1,"Cu1",iPrt,iOut)
		call DumpRealVar(Cu2,"Cu2",iPrt,iOut)
		call DumpRealVar(RutAhat,"RutAhat",iPrt,iOut)
		call DumpStringVar("End:Calc_ReferenceProps",iPrt,iOut)
	endif
	iPrt = 0
!	-------------------------------------------------- Bases: Ao1 & Ao2
!														 & Ao12N Coord Xformation
	call ScaleVector(A1hat,aTem,cT,3,Iout)
	call ScaleVector(A2hat,bTem,sT,3,Iout)
	A1 = aTem + bTem
!
	call ScaleVector(A1hat,aTem,-sT,3,Iout)
	call ScaleVector(A2hat,bTem,cT,3,Iout)
	A2 = aTem + bTem
!	------------------------------------------- Lamda1 & Lamda2
	call VectorNorm(A1,xLam1,3,Iout)
	call ScaleVector(A1,Ao1,1.D0/xLam1,3,Iout)
	call VectorNorm(A2,xLam2,3,Iout)
	call ScaleVector(A2,Ao2,1.D0/xLam2,3,Iout)
!
	Ao12N(1,1) = Ao1(1)
	Ao12N(2,1) = Ao1(2)
	Ao12N(3,1) = Ao1(3)
!	------------------------------------------- Xformation:
!												Global Cartesian -> Lines of Curvs.
	Ao12N(1,2) = Ao2(1)
	Ao12N(2,2) = Ao2(2)
	Ao12N(3,2) = Ao2(3)
!
	Ao12N(1,2) = Ao2(1)
	Ao12N(2,2) = Ao2(2)
	Ao12N(3,2) = Ao2(3)
!
	Ao12N(1,3) = xNor(1)
	Ao12N(2,3) = xNor(2)
	Ao12N(3,3) = xNor(3)
!	-------------------------------------------------- (Lamda_alfa,beta)
	call ScaleVector(X11hat,aTem,cT,3,Iout)
	call ScaleVector(X12hat,bTem,sT,3,Iout)
	A1c1 = aTem + bTem			! A1,1
	call DotProduct(A1,A1c1,xLam11hat,3,Iout)	! Lamda1,1hat
	xLam11hat = xLam11hat/xLam1
!
	call ScaleVector(X12hat,aTem,cT,3,Iout)
	call ScaleVector(X22hat,bTem,sT,3,Iout)
	A1c2 = aTem + bTem			! A1,2
	call DotProduct(A1,A1c2,xLam12hat,3,Iout)	! Lamda1,2hat
	xLam12hat = xLam12hat/xLam1
!
	call ScaleVector(X11hat,aTem,-sT,3,Iout)
	call ScaleVector(X12hat,bTem, cT,3,Iout)
	A2c1 = aTem + bTem			! A2,1
	call DotProduct(A2,A2c1,xLam21hat,3,Iout)	! Lamda2,1hat
	xLam21hat = xLam21hat/xLam2
!
	call ScaleVector(X12hat,aTem,-sT,3,Iout)
	call ScaleVector(X22hat,bTem, cT,3,Iout)
	A2c2 = aTem + bTem			! A1,2
	call DotProduct(A2,A2c2,xLam22hat,3,Iout)	! Lamda2,2hat
	xLam22hat = xLam22hat/xLam2
!
!	xLam11 = ( cT*xLam11hat + sT*xLam12hat)/xLam1	! lamda1,1
	xLam21 = ( cT*xLam21hat + sT*xLam22hat)/xLam1	! lamda2,1
	xLam12 = (-sT*xLam11hat + cT*xLam12hat)/xLam2	! lamda1,2
!	xLam22 = (-sT*xLam12hat + cT*xLam22hat)/xLam2	! lamda2,2
!	-------------------------------------------------- Curvatures: ko1 & ko2 
	C01(1) = zero
	C01(2) = Cu1	! was OK membrane
	C01(3) = -xLam12/xLam1
!	----------------------- Save for beam formula usefulness
	C02(1) = Cu2
	C02(2) = xLam21/xLam2
	C02(3) = zero
!	----------------------
	iPrt = 0
	if(iPrt == 1) then
		call DumpStringVar("Beg:Calc_ReferenceProps",iPrt,iOut)
		call DumpStringVar("just bef.PutGetRefPropsatGaussPt",iPrt,iOut)
		call DumpRealMatrix(Ao12N,3,3,"Ao12N",iPrt,iOut)
		call DumpRealArray(C01,3,"C01",iPrt,iOut)
		call DumpRealArray(C02,3,"C02",iPrt,iOut)
		call DumpRealVar(RutAhat,"RutAhat",iPrt,iOut)
		call DumpStringVar("End:Calc_ReferenceProps",iPrt,iOut)
	endif
	iPrt = 0
!	================================================== save in tape
	call PutGetRefPropsatGaussPt(iRefPro1,jCInt,1)
!	================================================== save in tape end
!
!	done
!
	return
	end
