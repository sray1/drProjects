	Subroutine Calc_ReferenceProps_Hem(Qc,ri,rj,jCInt)
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
!	=========================================================================
	piby2 = asin(1.D0)
	rad = 10.D0			! HARDCODED for radius = 10
	the = piby2			! HARDCODED for 90 deg
	phe = 0.8D0*piby2	! HARDCODED for 72 deg
!	----------------------------------------------------------- Coords along Lines of Curvatures
	cT	= one
	sT	= zero
!	----------------------------------------------------------- metric Tensor
	tri = the*ri
	prj = phe*rj
!
	A1hat(1) = -rad*dcos(prj)*dsin(tri)*the
	A1hat(2) =  rad*dcos(prj)*dcos(tri)*the
	A1hat(3) = zero
!
	A2hat(1) = -rad*dsin(prj)*dcos(tri)*phe
	A2hat(2) = -rad*dsin(prj)*dsin(tri)*phe
	A2hat(3) =  rad*dcos(prj)*phe
!	---------------------------------------------------- unit normal
	call CrossProduct(A1hat,A2hat,xNor,Iout)
	call VectorNorm(xNor,A,3,Iout)
	call ScaleVector(xNor,xNor,1.D0/A,3,Iout)
!	---------------------------------------------------- RootAhat
	call DotProduct(A1hat,A1hat,E,3,Iout)	! A11hat
	call DotProduct(A1hat,A2hat,F,3,Iout)	! A12hat
	call DotProduct(A2hat,A2hat,G,3,Iout)	! A22hat
!
	RutAhat = DSQRT(E*G - F*F)
!	-------------------------------------------------- Bases: Ao1 & Ao2
!														 & Ao12N Coord Xformation
	A1 = A1hat
	A2 = A2hat
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
	X11hat(1) = -rad*dcos(prj)*dcos(tri)*the*the
	X11hat(2) = -rad*dcos(prj)*dsin(tri)*the*the
	X11hat(3) = zero
!
	X22hat(1) = -rad*dcos(prj)*dcos(tri)*phe*phe
	X22hat(2) = -rad*dcos(prj)*dsin(tri)*phe*phe
	X22hat(3) = -rad*dsin(prj)*phe*phe
!
	X12hat(1) =  rad*dsin(prj)*dsin(tri)*the*phe
	X12hat(2) = -rad*dsin(prj)*dcos(tri)*the*phe
	X12hat(3) = zero
!	=================================================== Surface Curvatures Tensor
	call DotProduct(xNor,X11hat,B11,3,Iout)	! B11
	call DotProduct(xNor,X12hat,B12,3,Iout)	! B12	! SHOULD BE ZERO
	call DotProduct(xNor,X12hat,B21,3,Iout)	! B21	! SHOULD BE ZERO
	call DotProduct(xNor,X22hat,B22,3,Iout)	! B22
!
	Cu1 = B11/(xLam1*xLam1)		! B11/A11
	Cu2 = B22/(xLam2*xLam2)		! B22/A22
!	==================================================== Curvature End
	call DotProduct(A1,X11hat,xLam11hat,3,Iout)	! Lamda1,1hat
	xLam11hat = xLam11hat/xLam1
!
	call DotProduct(A1,X12hat,xLam12hat,3,Iout)	! Lamda1,2hat
	xLam12hat = xLam12hat/xLam1
!
	call DotProduct(A2,X12hat,xLam21hat,3,Iout)	! Lamda2,1hat
	xLam21hat = xLam21hat/xLam2
!
	call DotProduct(A2,X22hat,xLam22hat,3,Iout)	! Lamda2,2hat
	xLam22hat = xLam22hat/xLam2
!
	xLam21 = xLam21hat/xLam1						! lamda2,1
	xLam12 = xLam12hat/xLam2						! lamda1,2
!	-------------------------------------------------- Curvatures: ko1 & ko2 
	C01(1) = zero
	C01(2) = -Cu1
!	C01(2) = Cu1
	C01(3) = -xLam12/xLam1
!	----------------------
	C01 = MATMUL(Transpose(Ao12N),C01) - C01
!	=============================
	C02(1) = Cu2
	C02(2) = zero
	C02(3) = xLam21/xLam2
!	----------------------
	C02 = MATMUL(Transpose(Ao12N),C02) - C02
!	----------------------------------------------------------- Lines of curvatures
	iPrt = 0
	if(iPrt == 1) then
		call DumpStringVar("Beg:Calc_ReferenceProps",iPrt,iOut)
		call DumpRealVar(ri,"ri",iPrt,iOut)
		call DumpRealVar(rj,"rj",iPrt,iOut)
		call DumpRealVar(Cu1,"Cu1",iPrt,iOut)
		call DumpRealVar(Cu2,"Cu2",iPrt,iOut)
		call DumpRealVar(RutAhat,"RutAhat",iPrt,iOut)
		call DumpRealMatrix(Ao12N,3,3,"Ao12N",iPrt,iOut)
		call DumpRealArray(C01,3,"C01",iPrt,iOut)
		call DumpRealArray(C02,3,"C02",iPrt,iOut)
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
