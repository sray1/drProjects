	Subroutine FormGBlocks(nF,nC,G12,G22,G23,G24,iCurDir,Iout)
!	----------------------------------------------------------------------------- 
!	Inputs
!		FM(nC)			= {forcei,momenti} for dir iCurDir 
!		nF				= 6
!		C0(nC)			= initial Curvature vector for dir iCurDir
!		nC				= 3
! 	
!	Outputs 
!		G22(nC,nC)		= GThetaBarDelThetaBlock
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	include 'ThetaConstants.h'
	include 'BeamParams.h'
!	===============================
	Real(kind=8)	G12       ,G22       ,G23       ,G24                   
	Dimension		G12(nC,nC),G22(nC,nC),G23(nC,nC),G24(nC,nC)
	Real(kind=8)	Fo    ,XM                  
	Dimension		Fo(nC),XM(nC)
	Real(kind=8)	BB    ,CC                        
	Dimension		BB(nC),CC(nC)
	Real(kind=8)	W       ,R       ,SM       ,SF       ,SC     
	Dimension		W(nC,nC),R(nC,nC),SM(nC,nC),SF(nC,nC),SC(nC,nC)
	Real(kind=8)	FA       ,XMK       ,TA       ,ATA                               
	Dimension		FA(nC,nC),XMK(nC,nC),TA(nC,nC),ATA(nC,nC)
	Real(kind=8)	WMR       ,TMT       ,SMt                       
	Dimension		WMR(nC,nC),TMT(nC,nC),SMt(nC,nC)
!
	DATA nV/3/
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	------------------------------------------------------------------- 
	W = WMat
	R = RMat
!	========
!	istart = (iCurdir-1)*6
!		
!	call VectorExtract_Vector(HD,nG,Ro,nC,4,Iout)	!rotation
!	call VectorExtract_Vector(HD,nG,Rp,nC,istart+10,Iout)!rotationPrimed
!
	call VectorExtract_Vector(FMt,nF,Fo,nC,1,Iout)	!Force 
	call VectorExtract_Vector(FMt,nF,XM,nC,4,Iout)	!Moment 
!-----------------------------------------------------------------------------------------G22Block
!	------------------------------------------------------------------- Translational
!	---------------------------------------------------- FA = WTran(Fxa + axF -2(F.a)I)W
	call FormF_a_PartMatrix(Fo,AA,FA,3,1,Iout)	!Fxa + axF -2(F.a)I
!
!	call Form_WMatrix(Ro,W,nC,c1,c2,c1b,c2b,Iout)
	FA = MATMUL(FA, W)				!(Fxa + axF -2(F.a)I)W
	FA = MATMUL(TRANSPOSE(W), FA)	!WTran(Fxa + axF -2(F.a)I)W
!
	call CrossProduct(Fo,AA,BB,Iout)		! b = F x a
	call DotProduct(Ro,BB,dot,nV,Iout)		! theta dot b
	C2TdotB = c2*dot						! c2*(theta dot b)
!	--------------------------------------- .5*FA + c2(theta dot b)I
	FA = 0.5D0*FA
	FA(1,1) = FA(1,1) + C2TdotB
	FA(2,2) = FA(2,2) + C2TdotB
	FA(3,3) = FA(3,3) + C2TdotB
!	----------------------------------------------------------------------------- Rotational
!	-----------------------------------------XMK = WTran(Mxkc + kcxM -2(M.kc)I)W 
	call FormF_a_PartMatrix(XM,CK,XMK,3,2,Iout)	!Mxkc + kcxM -2(M.kc)I
!
	XMK = MATMUL(XMK, W)				!(Mxkc + kcxM -2(M.kc)I)W
	XMK = MATMUL(TRANSPOSE(W), XMK)	!WTran(Mxkc + kcxM -2(M.kc)I)W
!   	 
	call CrossProduct(XM,CK,CC,Iout)		! c = M x kc
	call DotProduct(Ro,CC,dot,nV,Iout)	! theta dot c
	C2TdotC = c2*dot						! c2*(theta dot c)
!	--------------------------------------- .5*XMK + c2(theta dot c)I
	XMK = 0.5D0*XMK
	XMK(1,1) = XMK(1,1) + C2TdotC
	XMK(2,2) = XMK(2,2) + C2TdotC
	XMK(3,3) = XMK(3,3) + C2TdotC
!	---------------------------------------------------------------AlfaCxRot + RotxAlfaC
	call FormThetaAlfaTrans_Matrix(Ro,CC,TA,nC,c1,c2,c1b,c2b,Iout)	!RotxAlfa
	ATA = 0.5D0*(TA + TRANSPOSE(TA))
!	---------------------------------------------------------------AlfaBxRot + RotxAlfaB
	call FormThetaAlfaTrans_Matrix(Ro,BB,TA,nC,c1,c2,c1b,c2b,Iout)	!RotxAlfa
	ATA = ATA + 0.5D0*(TA + TRANSPOSE(TA))
!	-------------------------------------------------------------------- WTranMR+RTranMTranW
	call FormSkew(XM,nC,SM,Iout)		!skew[M]
!	call FormR_Matrix(Ro,Rp,R,nC,c1,c2,c1b,c2b,Iout) !R matrix
!
	WMR = MATMUL(TRANSPOSE(W),SM)	!WTran[M]
	WMR = MATMUL(WMR,R)				!WTran[M]R
!
	WMR = WMR + TRANSPOSE(WMR)
!	------------------------------------------------------------------------ G22Block 
	G22 = FA + XMK + ATA + WMR
!-----------------------------------------------------------------------------------------G12Block
!-------------------------------------------------------------------------------------------------
	call FormSkew(Fo,nC,SF,Iout)		!skew[F]
	call FormSkew(C0,nC,SC,Iout)		!skew[k0]
!
	G12 = MATMUL(SC,SF)					![k0][Ft]
	G12 = MATMUL(G12,W)					![k0][Ft]W
!-----------------------------------------------------------------------------------------G23Block
!-------------------------------------------------------------------------------------------------
	G23 = MATMUL(TRANSPOSE(W),SF)		!WTran[Ft]	
!-----------------------------------------------------------------------------------------G24Block
!-------------------------------------------------------------------------------------------------

	TMT = MATMUL(TRANSPOSE(W),SM)		!WTran[Mt]
	TMT = MATMUL(TMT,W)					!WTran[Mt]W
!
	call FormS_Matrix(Ro,XM,SMt,nC,c1,c2,c1b,c2b,Iout) !S(Mt) Matrix
!
	G24 = TMT + SMt
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		call DumpRealArray(Ro,3,"Ro",iPrt,iOut)
		call DumpRealArray(BB,3,"BB",iPrt,iOut)
		call DumpRealArray(CC,3,"CC",iPrt,iOut)
		call DumpRealVar(c2,"c2",iPrt,iOut)
		call DumpRealVar(C2TdotB,"C2TdotB",iPrt,iOut)
		call DumpRealVar(C2TdotC,"C2TdotC",iPrt,iOut)
	endif
	iPrt = 0
	if (iPrt == 1) Then
!		write(Iout,1010) (G(j),j = 1,nS)
		write(Iout,1005) iCurDir
		write(Iout,1020) "G12", (i,(G12(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "G22", (i,(G22(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "G23", (i,(G23(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) "G24", (i,(G24(i,j),j = 1,nC),i=1,nC)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1005 format(1X,"Current direction for G_Matrix ="I2/)
 1010 format(1X,"Current vector..."/2X,3(f10.7,1X))
 1020 format(2X,A3," Matrix(3,3)"/( (I5,3(f20.7,1X))  ))
	end
