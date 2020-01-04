	Subroutine InvertedTangentStiffness(A,ASav,nA,ikod,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	A
	Dimension		A(nA,nA),ASav(nA,nA)
	DATA zero/0.D0/,one/1.0D0/  
	
!
	if(ikod == 1) Then			!SAVE
		do 100 i = 1,nA
		do 100 j = 1,nA	 
		ASav(i,j) = A(i,j)
  100		continue
	elseif(ikod == 2) Then		!RECALL
		do 200 i = 1,nA
		do 200 j = 1,nA	 
		A(i,j) = ASav(i,j)
  200		continue
	endif
!
!	done
!
	iPrt = 0
	if(iPrt == 1) Then
!		write(iOut,1010) nA,(Qd(j),j = 1,nA)
  110		continue
	endif
!
	return
!
 1010 format("Update for the Iteration:deltaUi2(",I2,")"/
     &        (5(f16.10,1X)/))
	end
