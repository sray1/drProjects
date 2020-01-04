	Subroutine Expand_BezierDispControls(Xc,nXc,Xf,nXf,iCont,iOut)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM
!	EQUATIONS 1,13,17 Rows include = 0.0
!
!	Xc(nXc)		= Solved Bezier Displacement Controls (Input)
!	Xf(nFf)		= Full Bezier Displacement Controls (Output)	
!
	real(kind = 8)	Xf     ,Xc     ,tipdis
	Dimension		Xf(nXf),Xc(nXc)
!
!
	integer i,ii
!
	integer			Drop
	Dimension		Drop(4),DropC0(4),DropC1(4),DropC2(4)	
	DATA DropC0 / 1,5,9,13/
	DATA DropC1 / 1,4,7,10/
	DATA DropC2 / 1,4,7,10/
	DATA nDrop0/4/
	DATA nDrop1/4/
	DATA nDrop2/4/
!
!------------------------------ Initialize
	if( iCont == 0) Then
		nDrop = nDrop0
		do 5 k = 1,nDrop
		Drop(k) = DropC0(k)
    5		continue
	else if( iCont == 1) Then 
		nDrop = nDrop1
		do 6 k = 1,nDrop
		Drop(k) = DropC1(k)
    6		continue
	else if( iCont == 2) Then 
		nDrop = nDrop2
		do 7 k = 1,nDrop
		Drop(k) = DropC2(k)
    7		continue
	end if
!------------------------------
	Xf = 0.0	! initialize
	ii = 0
!			
	do 20 i = 1,nXf
	do 10 k = 1,nDrop
	if(i == Drop(k)) then
		go to 20
	end if
   10	continue
	ii = ii + 1
!
	Xf(i) = Xc(ii)
   20 continue
  100 continue
!
	write(iOut,1000)
	write(iOut,1010) nXc,(XC(i),i = 1,nXc)
	write(iOut,1020) nXf,(XF(i),i = 1,nXf)
!
	if(iCont == 0) Then
!	Tip displacement at r=1;s=1/2
		tipdis = 0.25*(Xf(nXf) + Xf(nXf-6))+0.5*Xf(nXf-3)
		write(iOut,1030) tipdis
	endif
!	
!   		 
	return
 1000 Format(/2x,"Just before Leaving: Expand_BezierDispControls"/)
 1010 Format(/2x,"Supported DisplacementControls: 1x"I3/
     &										7(8(2x,F10.4)/) )
 1020 Format(/2x,"Non-Support DisplacementControls: 1x"I3/
     &										7(8(2x,F10.4)/) )
 1030 Format(/2x,"Tip. Displacement(r=1;s=1/2)   =",F10.4/)
	end
!
	Subroutine Expand_BezierDispControls_C1(T,nStifS,nStifC,Xc,Xf
     &														,iOut)
!
	Real(kind=8)	T
	Dimension		T(nStifS,nStifC)
!
!	Xc(nXc)		= Solved Bezier Displacement Controls (Input)
!	Xf(nFf)		= Full Bezier Displacement Controls (Output)	
!
	real(kind = 8)	Xf     ,Xc           ,tipdis
	Dimension		Xf(nStifS),Xc(nStifC)
!
!
!
	Xf = 0.0D0	! initialize
!
	do 50 i = 1,nStifS
	sum =0.0D0
	do 40 k = 1,nStifC
	sum = sum + T(i,k)*Xc(k)
   40	continue
   	Xf(i) = sum
   50 continue
  100 continue 
!   		 
	write(iOut,1000)
	write(iOut,1010) nStifC,(XC(i),i = 1,nStifC)
	write(iOut,1020) nStifS,(XF(i),i = 1,nStifS)
!
!	Tip displacement at r=1;s=1/2
	tipdis = 0.25*(Xf(nStifS) + Xf(nStifS-6))+0.5*Xf(nStifS-3)
	write(iOut,1030) tipdis
!	
!   		 
	return
 1000 Format(/2x,"Just before Leaving: Expand_BezierDispControls_C1"/)
 1010 Format(/2x,"C1 DisplacementControls: 1x",I3/
     &										7(8(2x,F10.4)/) )
 1020 Format(/2x,"FULL DisplacementControls: 1x",I3/
     &										7(8(2x,F10.4)/) )
 1030 Format(/2x,"Tip. Displacement(r=1;s=1/2)   =",F10.4/)
	end 
