!	Subroutine Set_ExtLoad_Y(Qf,nQ,iOut)
!	Implicit Real(kind=8) (a-h,o-z)
	
!	real(kind = 8)	Qf
!	Dimension		Qf(nQ)
!	
!	Qf		= 0.		! All Zero
!!	Qf(1)	= 1.0D0		! B-Load: Tip w-force	! Palazzotto
!	Qf(1)	= 6.28D0	! B-Load: Tip Moment	! Straight Beam
!
!	return
!	end

	Subroutine LV_Initialize(F,nF,iOut)
!
	Implicit Real(kind=8) (a-h,o-z)
!
!
	Real(kind=8)	F    
	Dimension		F(nF)
	
!
	F			= 0.D0	! All
!   
!	Done
!
	iPrt = 0
	if(iPrt == 1) Then
		write(iOut,1000)
		write(iOut,1010) (F(i),i = 1,nF)
	endif
!   		 
	return
 1000 Format(/2x,"Just before Leaving: Quad_CC_LVY_Initialize"/)
 1010 Format(/2x,"Load Vector"/
     &        3(2x,5F20.7/) )
	end 


	Subroutine LV_SaveforConvergence(Fo,F,nF,iOut)
!
	Implicit Real(kind=8) (a-h,o-z)
!
!
	Real(kind=8)	Fo    ,F    
	Dimension		Fo(nF),F(nF)
	
!
	do 10 i = 1,nF
   	Fo(i) = F(i)
   10 continue
!   
!	Done
!
	iPrt = 0
	if(iPrt == 1) Then
		write(iOut,1000)
		write(iOut,1010) (F(i),i = 1,nF)
	endif
!   		 
	return
 1000 Format(/2x,"Just before Leaving: Quad_CC_LVY_Initialize"/)
 1010 Format(/2x,"Load Vector"/
     &        3(2x,5F20.7/) )
	end 

	Subroutine LV_minus_EndLoad(XLam,P,F,nF,iOut)
!
	Implicit Real(kind=8) (a-h,o-z)
!
!
!	Inputs
!		Qf(3)		= Load Ceffs at Bez. Pts at r = 1 Side
!		xLenY		= Length of side at r = 1
!		 	
!	Outputs 
!		F(12)	1= Desired Load Vector
!
!
!	Input Variables & Arrays: Specifically for Shear Load At r = 1 Surface
!
	Real(kind=8)	P   
	Dimension		P(nF)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	F    ,fmult
	Dimension		F(nF)
!================================
	common/Examples/cEx(10),nEx
	character (30)	cEx
	common/CurrentElem/iCEL
!================================
!
	fmult		= XLam		! Current Load Level, Lambda
	do 10 i = 1,nf
	F(i)	= F(i) - fmult*P(i) 
   10 continue	   
!===================================================== ARGYRIS: perturbation load
	if((nEx == 6).AND.(iCEL == 2)) Then
		F(18)	= F(18) - 2.D-6
	endif
!===================================================== ARGYRIS: perturbation load: END
!   
!	Done
!
	iPrt = 0
	if(iPrt == 1) Then
		write(iOut,1000)
		write(iOut,1010) (F(i),i = 1,nF)
	endif
!   		 
	return
 1000 Format(/2x,"Just before Leaving: LV_minus_EndLoad"/)
 1010 Format(/2x,"Load Vector"/
     &        3(2x,5F16.10/) )
	end 

	Subroutine LV_EndLoad(LocF,ValF,nLod,F,nF,iOut)
!
	Implicit Real(kind=8) (a-h,o-z)
!
!
!	Inputs
!		Qf(3)		= Load Ceffs at Bez. Pts at r = 1 Side
!		xLenY		= Length of side at r = 1
!		 	
!	Outputs 
!		F(12)	1= Desired Load Vector
!
!
!	Input Variables & Arrays: Specifically for Shear Load At r = 1 Surface
!
	integer			LocF
	Dimension		LocF(nLod)
	Real*8			ValF      
	Dimension		ValF(nLod)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	F    ,fmult
	Dimension		F(nF)
!================================
	common/Examples/cEx(10),nEx
	character (30)	cEx
	common/CurrentElem/iCEL
!================================
	fmult		= 1.D0		! 
	do 10 i = 1,nLod
	nLoadLoc = LocF(i)
	F(nLoadLoc)	= fmult*ValF(i) 
   10 continue
!===================================================== ARGYRIS: ADD perturbation load
	if(nEx == 6) Then
		F(51)	= 2.D-4
	endif
!===================================================== ARGYRIS: ADD perturbation load: END
	   
!   
!	Done
!
	iPrt = 0
	if(iPrt == 1) Then
		write(iOut,1000)
		write(iOut,1010) (i,F(i),i = 1,nF)
	endif
!   		 
	return
 1000 Format(/2x,"Just before Leaving: LV_minus_EndLoad"/)
 1010 Format(/2x,"DOFs and Load Vector"/
     &        (2x,6(i5,1x,F7.4) )     )
	end 
