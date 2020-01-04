	Subroutine Extract_ContractedLoadVector(Ff,nFf,Drop,nDrop,
     &						Fc,nFc,iOut)
!-------------------------------------- 
!
!	Ff(nFf)		= Full Load Vector (INPUT)	
!	Fc(nFc)		= Contracted Load Vector (OUTPUT)
!--------------------------------------
	real(kind = 8)	Ff     ,Fc
	Dimension		Ff(nFf),Fc(nFc)
	integer			Drop(nDrop),nDrop	
	integer i,ii
!----------------------------------------------------
	ii = 0
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
!
	return
	end
