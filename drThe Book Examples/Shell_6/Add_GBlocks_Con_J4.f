	Subroutine AddGBlocks_Con_J4(nF,nC,G22,iCurDir,Iout)
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
	Real(kind=8)	G22                  
	Dimension		G22(nC,nC)
	Real(kind=8)	Fo                      
	Dimension		Fo(nC)
	Real(kind=8)	BB                            
	Dimension		BB(nC)
	Real(kind=8)	W       ,R       ,SM       ,SF       ,SC     
	Dimension		W(nC,nC),R(nC,nC),SM(nC,nC),SF(nC,nC),SC(nC,nC)
	Real(kind=8)	FA       ,TA       ,ATA                               
	Dimension		FA(nC,nC),TA(nC,nC),ATA(nC,nC)
!	Real(kind=8)	WMR       ,TMT       ,SMt                       
!	Dimension		WMR(nC,nC),TMT(nC,nC),SMt(nC,nC)
!
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
!	call VectorExtract_Vector(FMt,nF,XM,nC,4,Iout)	!Moment 
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
!	---------------------------------------------------------------AlfaBxRot + RotxAlfaB
	call FormThetaAlfaTrans_Matrix(Ro,BB,TA,nC,c1,c2,c1b,c2b,Iout)	!RotxAlfa
	ATA = 0.5D0*(TA + TRANSPOSE(TA))
!	--------------------------------------- .5*FA + c2(theta dot b)I
	FA = 0.5D0*FA
	FA(1,1) = FA(1,1) + C2TdotB
	FA(2,2) = FA(2,2) + C2TdotB
	FA(3,3) = FA(3,3) + C2TdotB
!	------------------------------------------------------------------------ G22Block 
	G22 = FA + ATA
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
!		write(Iout,1010) (G(j),j = 1,nS)
		write(Iout,1005) iCurDir
		write(Iout,1020) "G22", (i,(G22(i,j),j = 1,nC),i=1,nC)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1005 format(1X,"Current direction for GC_J4_Matrix ="I2/)
 1010 format(1X,"Current vector..."/2X,3(f10.7,1X))
 1020 format(2X,A3," Matrix(3,3)"/( (I5,3(f20.7,1X))  ))
	end
