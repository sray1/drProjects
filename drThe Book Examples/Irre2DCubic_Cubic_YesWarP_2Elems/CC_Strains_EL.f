	Subroutine CC_Strains_EL
     &	(E,PR,Thk,Qc,nQc,Qd,nStifEL,nLoop,Nel,NelType,Iout)
!	Inputs
!		Qc(1,16)	= Bezier X-Coordinates
!					=	(qc00x qc10x...qc33x)
!		Qc(2,16)	= Bezier Y-Coordinates
!					=	(qc00y qc10y...qc33y)
!		Nel			= Element Number
!		NelType		= Element Type:
!						0 = Plane Stress
!						1 = Plane Strain
!						2 = Axi-symmtric	(NOT DONE YET)
! 	
!	Outputs 
!		B(3,24)		= Strain Displacement Matrix
!						at a point (R,S)
!		Det			= determinant of The Jacobian
!
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Qc       ,E,PR,Thk    
	Dimension		Qc(2,nQc)
	Real(kind=8)	Qd         ,B           ,Str
	Dimension		Qd(nStifEL),B(3,nStifEL),Str(3,nLoop)
	Real(kind=8)	Sig
	Dimension		Sig(3,nLoop)
	Real(kind=8)	Det,R,S
	integer			Nel,NelType,Iout
!
!		ndegR					= Bezier degree in r-dir = 3
!		ndegS					= Bezier degree in s-dir = 3
	Integer			nDegR,nDegS
!
	Real(kind=8)	AM,BM,CM,TH
	Real(kind=8)	D         
	Dimension		D(3,3)
	Real(kind=8)	dum,sumU,sumV,SValues(5)
	Real(kind=8)	H1D	 
	Dimension		H1D(2,16)
	Real(kind=8)	AJI   
	Dimension		AJI(2,2)
	DATA SValues	/0.0D0,.3333333333333D0,0.5D0,
     &				.666666666666667D0,1.0D0/
	DATA nSV		/5/	
!--------------------
!
!	Stress-Strain Law
!
	if(NelType == 0)	Then					! Plain Stress
		AM = E
		BM = PR
		CM = AM/(1-BM*BM)
		TH = Thk			! thickness
	else if(NelType == 1) Then				! Plain Strain
		AM = E/(1-PR*PR)
		BM = PR/(1-PR)
		CM = AM/(1.-BM*BM)
		TH = 1				! thickness
	else
		Stop 'ElType Wrong'
	end if
!
	D(1,1) = CM
	D(1,2) = CM*BM
	D(1,3) = 0.
	D(2,1) = D(1,2)
	D(2,2) = CM
	D(2,3) = 0.
	D(3,1) = 0.
	D(3,2) = 0.
	D(3,3) = CM*(1.-BM)/2.
!	---------------
	delR = 0.1D0
!--------------------------------------------------------- loop for SValues
	do 200 iS = 1,nSV
	S = SValues(iS)
!	---------------
	do 100 k = 1,nLoop
	R = delR*(k-1)
!	--------------------------------------
!
!	Inverse & determinant of Jacobian
!
	call CC_Jacobian(Qc,16,4,4,R,S,H1D,AJI,Det,Nel,Iout,0)
!
!	Strain displacement Matrix
!
	do 50 j = 1,16 
	B(1,j)		= AJI(1,1)*H1D(1,j) + AJI(1,2)*H1D(2,j)
	B(1,j+16)	= 0.D0
!
	B(2,j)		= 0.D0
	B(2,j+16)	= AJI(2,1)*H1D(1,j) + AJI(2,2)*H1D(2,j)
!
	B(3,j)		= AJI(2,1)*H1D(1,j) + AJI(2,2)*H1D(2,j)
	B(3,j+16)	= AJI(1,1)*H1D(1,j) + AJI(1,2)*H1D(2,j)
   50	continue
!--------------------------------------------------------
	do 70 i = 1,3
	sumU = 0.0D0
	sumV = 0.0D0
	do 60 j = 1,16 
   	sumU = sumU + B(i,j)*Qd(j)
   60	sumV = sumV + B(i,j+16)*Qd(j+16)
	Str(i,k) = sumU + sumV
   70	continue
!	--------------------------------------------------- Compute Stresses
	do 170 i = 1,3
	dum = 0.0D0
	do 160 l = 1,3 
  160 dum = dum + D(i,l)*Str(l,k)
	Sig(i,k) = dum
  170	continue
!	---------------------------------------------------- nLoop:RVal
  100 continue
!
	write(iOut,1000) Nel,S
	write(iOut,1010) (Str(1,j),j = 1,nLoop)
	write(iOut,1020) (Str(2,j),j = 1,nLoop)
	write(iOut,1030) (Str(3,j),j = 1,nLoop)
!
	write(iOut,1035) Nel,S
	write(iOut,1040) (Sig(1,j),j = 1,nLoop)
	write(iOut,1050) (Sig(2,j),j = 1,nLoop)
	write(iOut,1060) (Sig(3,j),j = 1,nLoop)
	
!--------------------------------------------------------  Loop : SValues
  200 continue
!
	return
!
 1000 format(//2X," Strains of Element ",I2," At S = ",F5.2/)
 1010 format(/5x,"EpsX "/ 5(2X,F16.10))
 1020 format(/5x,"EpsY "/ 5(2X,F16.10))
 1030 format(/5x,"GamXY"/5(2X,F16.10))
 1035 format(//2X," Stresses of Element ",I2," At S = ",F5.2/)
 1040 format(/5x,"SigX "/ 5(2X,F16.10))
 1050 format(/5x,"SigY "/ 5(2X,F16.10))
 1060 format(/5x,"TaoXY"/5(2X,F16.10))
	end
