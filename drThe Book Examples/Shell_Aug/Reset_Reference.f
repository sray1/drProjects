	Subroutine ResetReference(Qdo,Qd,nQd,nQc,
     &						RoCOld,CuCOld,RoSav,CKSav,nCInt,Iout)
!	----------------------------------------------------------------------------- 
!	Inputs
! 	
!	Outputs 
!		Qc(nDim,nQc)	= Updated Geometry Controls
!		QD(nQd)			= zeroed
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Qd     ,Qdo           
	Dimension		Qd(nQd),Qdo(nQd)
	Real(kind=8)	RoSav       ,CKSav            
	Dimension		RoSav(nCInt),CKSav(nCInt)
	Real(kind=8)	RoCOld       ,CuCOld            
	Dimension		RoCOld(nCInt),CuCOld(nCInt)
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!-------------------------------------------------------------Update Curvatures
	do 10 i = 1,nCInt
	RoCOld(i) = RoSav(i)
	CuCOld(i) = CKSav(i)
   10 continue
!-------------------------------------------------------------Initialize DisRot Controls
	RoSav	= zero
	CKSav	= zero
	do 20 i = 1,nQc		! zero out rotation rotDerivatives
	Qd(i+5*nQc)		= zero
	Qdo(i+5*nQc)	= zero
   20 continue
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
!		write(Iout,1000) nDim,nQc,(i,(Qc(i,j),j=1,nQc),i=1,nDim)
	endif
!----------------------------------------------------------
	return
!
 1000 format("QC(",I1,",",I1,"): "/
     &        3(I5,5X,6(f10.6,1X)/) )
	end
