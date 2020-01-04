	Subroutine Check_StrainConstrain_Element(Penalt,
     &					AugMulO,AugMul,OldCon,
     &					Qd,nStif,Nel,B,T,bOK,Iout)
!
!
!	Notes:	Nint should be atleast 2
!
!	Inputs
!		Qd(nStif)	= Latest displacement controls: state vector
!		Nel			= Element Number
!		Nint		= Number of Gauss Points
!		Iout		= Error Output file#
!		 	
!	Outputs 
!
	Implicit Real(kind=8) (a-h,o-z)
!	===========================
	include 'Augment.h'
	include 'CurParams.h'
	include 'SizeVar.h'
	include 'LoadStepIter.h'
	include 'Scratch.h'
	include 'ShellParams.h'
	include 'Solve.h'
!	include 'LogParams.h'
!============================================
!
!	Input Variables & Arrays
!
	Real(kind=8)	AugMulO             ,Penalt                                           
	Dimension		AugMulO(Nint1,Nint2),Penalt(Nint1,Nint2)
	Real(kind=8)	AugMul             ,OldCon                                       
	Dimension		AugMul(Nint1,Nint2),OldCon(Nint1,Nint2)
	Real(kind=8)	Qd                   
	Dimension		Qd(nStif)
!	
!	Working Variables & Arrays	
!
!	Real(kind=8)	DD   ,RR   ,DP1   ,Rp1   ,Dp2   ,Rp2                
!	Dimension		DD(3),RR(3),DP1(3),Rp1(3),Dp2(3),Rp2(3)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	B             ,T     
	Dimension		B(nDof2,nStif),T(nDof,nStif)
	Real(kind=8)	HD       ,Rp   
	Dimension		HD(nDof2),Rp(3)
	Real(kind=8)	R0   ,RK          
	Dimension		R0(3),RK(3)
!	=============================== 
	LOGICAL bOK
	DATA zero/0.D0/,one/1.0D0/,onm/-1.0D0/ 
	DATA NC/3/
!============================================================== 
	iPrt = 0
	if(iPrt == 1) then
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
	call DumpStringVar("Beg:Form_StrainConstrain_Element",iPrt,iOut)
		call DumpRealArray(Qd,nStif,"Qd array",1,iOut)
	call DumpStringVar("End:Form_StrainConstrain_Element",iPrt,iOut)
	endif
	iPrt = 0
!============================================================== .
!	Rewind CUrvatureInfo, B & T Scratch files
	rewind iRefPro1
	rewind iRefPro2
!
	nRec = 0
!	Loop over Gauss Locations
	do 60 iGau = 1,Nint1
	do 60 jGau = 1,Nint2
!	------------------------------------------------------------- Get  Geometric Curvature Vector etc.
!	if(iNut == 1) Then
!	if((iStep == 1).AND.(iNut == 5)) Then
	if((iStep == 0).AND.(iNut == 0)) Then
		abc = 1
	endif
!
	nRec = nRec + 1
!	---------------------------------------------------
	T = zero
	B = zero
	call Get_ReferenceInfoataGaussPt
     &					(T,B,nDof,nDof2,nStif,Nel,nRec)
!		-------------------------------------------------------- Debug 
	if((iStep == 0).AND.(iNut == 0)) Then
			iPrt = 0
	call DumpStringVar("Beg:Form_StrainConstrain_Element",iPrt,iOut)
			call DumpIntegerVar(Nel,"Element#",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
			call DumpIntegerVar(iGau,"GIndex:iGau",iPrt,iOut)
			call DumpIntegerVar(jGau,"GIndex:jGau",iPrt,iOut)
			call DumpIntegerVar(nCInt,"nCInt",iPrt,iOut)
			call DumpRealArray(Qd,nStif,"Qd",iPrt,iOut)
			call DumpRealArray(R0,3,"R0",iPrt,iOut)
			call DumpRealArray(C01,3,"C01",iPrt,iOut)
			call DumpRealArray(C02,3,"C02",iPrt,iOut)
			iPrt = 0
			call DumpRealMatrix(T,nDof,nStif,"T",iPrt,iOut)
			call DumpRealMatrix(B,nDof2,nStif,"B",iPrt,iOut)
			iPrt = 0
	call DumpStringVar("End:Quad_QQ_STIF_befEDG",iPrt,iOut)
		endif
!		-------------------------------------------------------- Debug : End
!--------------------------------------------------------------------- DisRots & Derivatives
!	====================================== Debug
!	if((iStep == 1).AND.(iNut == 2)) Then
	if((iStep == 1).AND.(iNut == 2)) Then
		abc = 1
!		call DumpRealArray(Qd,nStif,"Qd",0,iOut)
	endif
!	====================================== Debug End
	call Split_Dis_Rot_Deriv(Qd,nStif,B,Iout)
!	========================================= get constrain at gauss pt
	call Form_StrainConstrain(constrain,iOut)
!	========================================= Update xKbar
	if(xKbar.lt.dabs(constrain)) then
		xKbar = dabs(constrain)
	endif
!	========================================= Update
	constrainO			= OldCon(iGau,jGau)
	OldCon(iGau,jGau)	= constrain
	AugMul(iGau,jGau)	= AugMulO(iGau,jGau) + 
     &				    	penalt(iGau,jGau) * constrain
!	========================================= check constrain at gauss pt
	if(dabs(constrain - constrainO).gt.Tol_Con) then
		bOK = .FALSE.
	endif
!	----------
   60 continue
!	========
  	return
	end   		
	   		