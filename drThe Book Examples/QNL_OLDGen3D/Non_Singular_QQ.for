	Subroutine Extract_NonSingularStif(Ss,nSs,nStif,Sn,nSn,
     &									Sx,nSx,iCont,iOut)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM
!
!	for Loop: nStif	
!	nSsI,nSsJ are dimensions
!	Ss(nSs,nSs)		= Stiffness-Singular Matrix (INPUT)	
!	Sn(nSn,nSn)		= Stiffness-NonSingular Matrix (OUTPUT)
!
	Implicit Real(kind=8) (a-h,o-z)
	real(kind = 8)	Sn           ,Ss       
	Dimension		Sn(nSn,nSn),Ss(nSs,nSs)
	real(kind = 8)	sum,Add(nSn)
!
!
	integer i,j,ii,jj
!
	integer			Sx     ,Drop   
	Dimension		Sx(nSx),Drop(nSx)	
!==========================================
	common/LoadStepIter/iStep,iNut,bReset
!==========================================
	nDrop = nSx
	do 3 i = 1,nDrop
    3 Drop(i) = Sx(i)
!------------------------------
	Sn = 0.D0	!all
	jj = 0	
	do 40 j = 1,nStif
	do 10 k = 1,nDrop
	if(j == Drop(k)) then
		go to 40
	end if
   10	continue
	jj = jj+1
!
	ii = 0
	do 30 i = 1,nStif
!
	do 20 k = 1,nDrop
	if(i == Drop(k)) then
		go to 30
	end if
   20	continue
!
	ii = ii+1
	Sn(ii,jj) = Ss(i,j)
   30 continue
   40 continue
!
!	Check each col. vector for NOT Null
!
	Add = 0.D0
	do 70 j = 1,nSn
	sum = 0.0D0 
	do 60 i = 1,nSn	
	sum = sum + Sn(i,j)
   60 continue
	Add(j) = sum
   70 continue			
  100	continue

	iPrt = 0
!		-------------------------------------------------------- Debug 
		if((iStep == 0).AND.(iNut == 0)) Then
			iPrt = 0
		endif
!		-------------------------------------------------------- Debug : End
	if(iPrt == 1) Then
!		OPEN (unit = 15, FILE = 'Stiffness.prt',STATUS ='REPLACE')
		do 110 i = 1,nSn
		write(iOut,1010) nSn,nSn,i,(Sn(i,j),j = 1,nSn)
  110		continue
	endif
!--------------------------------------------------------------
 1010 format("Reduced Stiffness Matrix:Stif(",I3,",",I3,")"/
     &        I5/(2(6(f16.6,1X))))
	return
	end

	Subroutine Extract_ContractedLoadVector(Ff,nFf,Fc,nFc,Sx,nSx,
     &										iCont,iOut)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM
!	EQUATIONS 1,13,17 Rows NEED TO GO
!
!	Ff(nFf)		= Full Load Vector (INPUT)	
!	Fc(nFc)		= Contracted Load Vector (OUTPUT)
!
	Implicit Real(kind=8) (a-h,o-z)
	real(kind = 8)	Ff     ,Fc     
	Dimension		Ff(nFf),Fc(nFc)
!
!
	integer i,ii
!
	integer			Sx     ,Drop   
	Dimension		Sx(nSx),Drop(nSx)	
!==========================================
	common/LoadStepIter/iStep,iNut,bReset
!==========================================
	nDrop = nSx
	do 3 i = 1,nDrop
    3 Drop(i) = Sx(i)
!------------------------------
!	
	Fc	= 0.D0	!ALL
	ii	= 0
!			
	do 20 i = 1,nFf
	do 10 k = 1,nDrop
	if(i == Drop(k)) then
		go to 20
	end if
   10	continue
	ii = ii + 1
!
	Fc(ii) = Ff(i)
   20 continue
	iPrt = 0
!		-------------------------------------------------------- Debug 
		if((iStep == 0).AND.(iNut == 0)) Then
			iPrt = 1
		endif
!		-------------------------------------------------------- Debug : End
!--------------------------------------------------------------
	if(iPrt == 1) Then
!	OPEN (unit = 16, FILE = 'ReducedLoadVector.prt',STATUS ='REPLACE')
		write(iOut,1010) nFc,(Fc(i),i = 1,nFc)
	endif
!--------------------------------------------------------------
!
 1010 format("Reduced LoadVector:Fc(",I3,")"/
     &        (3(5(f16.6,1X)/)/))
!
	return
	end
!
