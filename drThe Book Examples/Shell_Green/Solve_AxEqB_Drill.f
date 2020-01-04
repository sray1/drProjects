	Subroutine Solve_AxEqB_Drill(Stif,F,X,nStif,nStiR,nSti3,Iout)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!
!	Inputs
!		Stif    		= Assembled Stiffness Matrix
!		F	    		= Assembled Load Vector
!		nStif			= Row or Col size of Stiffness matrix    
!		nSti3			= Col size of Drill DOF Bezier Controls:  d theta3 
!																   q
!		nStiR			= nStif - nSti3 
!		Iout			= Error Output file#
!		 	
!	Outputs 
!		Trace			= trace of the matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!============================================
	include 'LoadStepIter.h'
!==============================================
!
!	Input Variables & Arrays
!
	Real(kind=8)	Stif             ,F	      ,X		 
	Dimension		Stif(nStif,nStif),F(nStif),X(nStif)
!	
!	Working Variables & Arrays	
!
	Real(kind=8)	StiR			 ,Sti3
	Dimension		StiR(nStiR,nStiR),Sti3(nStiR,nSti3)
	Real(kind=8)	StiRS			 
	Dimension		StiRS(nStiR,nStiR)
	Real(kind=8)	S33             ,S33h			 
	Dimension		S33(nSti3,nSti3),S33h(nSti3,nSti3)
	Real(kind=8)	FR		 ,F3
	Dimension		FR(nStiR),F3(nSti3)
	Real(kind=8)	F3H		  ,QrH       ,Qr       ,Q3
	Dimension		F3H(nSti3),QrH(nStiR),Qr(nStiR),Q3(nSti3)
!	======================================================================== Break
!	Stiffness Matrix and Load Vector Break Apart
!
!	======================================================= Debug
	if((iStep == 1).AND.(iNut == 2)) Then
!	if((iStep == 2).AND.(iNut == 1)) Then
		abc = 1
	endif
!	=======================================================
	Call VectorExtract_Matrix2D
     &	(Stif,nStif,nStif,StiR,nStiR,nStiR,1,1,Iout)
	call VectorExtract_Vector(F,nStif,FR,nStiR,1,Iout)
	Call VectorExtract_Matrix2D
     &	(Stif,nStif,nStif,Sti3,nStiR,nSti3,1,nStiR+1,Iout)
!	============================================================ Do not need
	Call VectorExtract_Matrix2D
     &	(Stif,nStif,nStif,S33,nSti3,nSti3,nStiR+1,nStiR+1,Iout)
!	============================================================ Do not need: end
	call VectorExtract_Vector(F,nStif,F3,nSti3,nStiR+1,Iout)
!	======================================================================== Solv: Krr.Qrh = Fr
	call Solve_AxEqB(StiR,FR,QrH,nStiR,nStiR,iOut)
!	-------------------------------------
	if((iStep == 0).AND.(iNut == 0)) Then
		Q3 = 0.D0
		call VectorInsert_Vector(X,nStif,QrH,nStiR,1,Iout)
		call VectorInsert_Vector(X,nStif,Q3,nSti3,nStiR+1,Iout)
		return
	endif
!	======================================================================== SAVE Krr
	StiRS = StiR
!	======================================================================== Invert Krr
	call Invert_A(StiR,nStiR,nStiR,iOut,iFileStiff)
!	======================================================================== Form S33h, F3h
	S33H	= MATMUL(TRANSPOSE(Sti3),MATMUL(StiR,Sti3) )
	F3h		= -F3 + MATMUL(TRANSPOSE(Sti3),QrH)	
!	======================================================================== Solv: K33h.Q3 = F3H
	call Solve_AxEqB(S33H,F3H,Q3,nSti3,nSti3,iOut)
!	call Invert_A(S33H,nSti3,nSti3,iOut,iFileStiff)
!	Q3 = MATMUL(S33H,F3H)
!	======================================================================== Form Frh
	Qrh		= Fr - MATMUL(Sti3,Q3)	
!	======================================================================== Solv: Krr.Qr = FrH
	call Solve_AxEqB(StiRS,QrH,Qr,nStiR,nStiR,iOut)							! FrH = QrH
!	======================================================================== Insert Qr,Q3 in X
	call VectorInsert_Vector(X,nStif,Qr,nStiR,1,Iout)
	call VectorInsert_Vector(X,nStif,Q3,nSti3,nStiR+1,Iout)
!	------------------------
	iPrt = 0
	if(iPrt == 1) then
!		call DumpRealArray(X,nStif,"Solution(nStif)",1,iOut)
		write(iOut,1000)
		write(iOut,1010) nStif,(X(i),i = 1,nStif)
	endif
!   		 
	return
 1000 Format(/2x,"Just before Leaving: Solve_AxEqB_Drill"/)
 1010 Format(/2x,"Solved DisplacementControls: 1x"I3/
     &								3(4(2x,F20.15)/) )
	end
