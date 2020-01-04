	Subroutine Extract_NonSingularStif(Ss,nSsI,nSsJ,Drop,nDrop,
     &						Sn,nSnI,nSnJ,iOut)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM
!	EQUATIONS 1,13,17 ROWS & COLS NEED TO GO
!
!	Ss(nSsI,nSsJ)		= Stiffness-Singular Matrix (INPUT)	
!	Sn(nSnI,nSnJ)		= Stiffness-NonSingular Matrix (OUTPUT)
!
	Implicit Real(kind=8) (a-h,o-z)

	real(kind = 8)	Sn           ,Ss
	Dimension		Sn(nSnI,nSnJ),Ss(nSsI,nSsJ)
	integer			Drop(nDrop),nDrop	
!
	real(kind = 8)	sum,Add(nSnI)
	integer			i,j,ii,jj
!-------------------------------------- 
	ii = 0
	jj = 0
!			
	do 40 j = 1,nSsJ
	do 10 k = 1,nDrop
	if(j == Drop(k)) then
		go to 40
	end if
   10	continue
	jj = jj+1
!
	ii = 0
	do 30 i = 1,nSsI
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
!	ii = mod(ii,nSnI)		! reset row
   40 continue
!
!	Check each col. vector for NOT Null
!
	Add = 0.D0
	do 70 j = 1,nSnI
	sum = 0.0 
	do 60 i = 1,nSnI	
	sum = sum + Sn(i,j)
   60 continue
	Add(j) = sum
   70 continue			
!
!	done
!
	iPrt = 0
	if(iPrt == 1) then
		write(iOut,1000) nSnI,nSnJ
		do ii = 1,nSnI
			write(iOut,1010) ii,(Sn(ii,jj),jj = 1,nSnJ)
		end do !ii
!		Pause
	endif
	return
!
 1000 format(///"NonSingular Stiffness Matrix:Stif(",i2,",",i2,")"/)
 1010 format(I5/(5(f16.3,1X)))
 1020 format(1x,"Ri =",f10.6/1X,"Si =",f10.6///)
	return
	end   		