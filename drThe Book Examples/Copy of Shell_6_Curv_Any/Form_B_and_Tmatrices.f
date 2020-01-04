	Subroutine Form_B_and_Tmatrices(T,B,ri,rj,jCInt)
!===============================================================================
!	THIS ROUTINE WILL NOT WORK FOR NONORTHOGONAL ISOLINES: WE WILL CHANGE IT
!				WE HAVE APPROPRIATE FORMULI FOR NONORTHOGONAL ISOLINES
!===============================================================================
!	Inputs
!		ri			= 1-directional root domain value	
!		rj			= 2-directional root domain value	
!		Nel			= Element Number
!		nDof		= no. of DOF
!		nT			= 6  (nDof)   (d1,d2,d3,t1,t2,t3)
!		nB			= 18 (nDof*3) (d1,d2,d3,t1,t2,t3)
!							      (d11,d21,d31,t11,t21,t31)	derivatives wrt s1
!								  (d12,d22,d32,t12,t22,t32)	derivatives wrt s2
!		nD			= (nDof*nQd1*nQd2) = 6n
! 	
!	Outputs 
!		T(nT,nD)	= Dis & Rot at a gauss point (Ri,Rj)
!		B(nB,nD)	= DisRot & Primed Transformation Matrix
!							at a gauss point (Ri,Rj)
!
	Implicit Real(kind=8) (a-h,o-z)
!	====================
	include 'SizeVar.h'
	include 'files.h'
	include 'Scratch.h'
	include 'CurParams.h'
!	====================
	Real(kind=8)	T              ,B
	Dimension		T(nDof,nStifEL),B(nDof2,nStifEL)		! T(6,6n),B(18,6n)
	Real(kind=8)	Bri      ,Brj      ,DBri      ,DBrj         
	Dimension		Bri(nQd1),Brj(nQd2),DBri(nQd1),DBrj(nQd2)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	--------------------------------------------- Check compatibility
	nT = nDof
	nB = nDof2
	nD = nStifEL
!	------------
	if (nB.NE.nT*3) Then
		stop 'nDof2.NE.nnDof*3 in Form__B_and_Tmatrices'
	endif
!	-------------------------------------------------- Basis Functions		 
	call Bernstein(Bri,nQd1,ri,iOut)
	call Bernstein(Brj,nQd2,rj,iOut)
!	-------------------------------------------------- Basis Derivatives
	call Bernstein_IstDerivative(DBri,nQd1,ri,iOut)		! wrt 1-hat
	call Bernstein_IstDerivative(DBrj,nQd2,rj,iOut)		! wrt 2-hat
!	------------------------------
	nQd12	= nQd1*nQd2
	nQd123	= nQd12*three
	T		= zero
	B		= zero
!	-------------------------------------------------- T & B  (nT=1..6,nD)
	do 20 i = 1,nQd1	! 
	m = (i-1)*nQd2
	do 20 j = 1,nQd2	! 
	Brij	= Bri(i)*Brj(j)
	do 10 k = 1,nDof			
	kStart	= (k-1)*nQd12
	loc		= kStart + m + j
!
!	if(k==5) then
!		Brij = -Brij
!	T(k,loc)	= Brij			! d1,d2,d3,t1,-t2,t3						
!	B(k,loc)	= Brij			! d1,d2,d3,t1,-t2,t3						
!	endif
!
	T(k,loc)	= Brij			! d1,d2,d3,t1,t2,t3						
	B(k,loc)	= Brij			! d1,d2,d3,t1,t2,t3						
   10	continue
   20	continue
!	-------------------------------------------------- B  (7..12,nD):derivatives wrt s1
	rxLam1 = one/xLam1
	do 40 i = 1,nQd1	! 
	m = (i-1)*nQd2
	do 40 j = 1,nQd2	! 
	Brij	= (cT*DBri(i)*Brj(j) + sT*Bri(i)*DBrj(j))*rxLam1
	do 30 k = 1,nDof			
	kStart	= (k-1)*nQd12
	loc		= kStart + m + j
!
!	if(k==5) then
!		Brij = -Brij
!	B(k+6,loc)	= Brij		! d11,d21,d31,t11,-t21,t31						
!	endif
!
	B(k+6,loc)	= Brij		! d11,d21,d31,t11,t21,t31						
   30	continue
   40	continue
!	-------------------------------------------------- B  (13..18,nD):derivatives wrt s2
	rxLam2 = one/xLam2
	do 60 i = 1,nQd1	! 
	m = (i-1)*nQd2
	do 60 j = 1,nQd2	! 
	Brij	= (-sT*DBri(i)*Brj(j) + cT*Bri(i)*DBrj(j))*rxLam2
	do 50 k = 1,nDof			 
	kStart	= (k-1)*nQd12
	loc		= kStart + m + j
!
!	if(k==6.or.k==5) then
!		Brij = -Brij
!	B(k+12,loc)	= Brij		! d12,d22,d32,t12,t22,-t32						
!	endif
!
	B(k+12,loc)	= Brij		! d12,d22,d32,t12,t22,t32						
   50	continue
   60	continue
!	================================================== save in tape
	call PutGetTBatGaussPt(T,nDof,B,nDof2,nStifEL,iRefPro2,jCInt,1)
!	================================================== save in tape end
	return
!
 1000	format(A,I5,A)
	end
