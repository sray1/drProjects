	LOGICAL Function ThetaNeedUpdate_STR(Qd,nQd,nQc,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!========================================================================
!	HardCoded Specifically for straight Cantilever Beam with Tip Moment
!========================================================================
	Real(kind=8)	Qd     ,Br    
	Dimension		Qd(nQd),Br(nQc)

	ThetaNeedUpdate_STR =.FALSE.
	Data			zero/0.D0/,one/1.D0/,two/2.D0/,four/4.D0/
!------------------------------
	pi	= four*datan(1.D0)
!---------------------------------------- Temporary Check
	nQ5 = 5*nQc
!	-------------------------------------------- Basis Functions		 
	call Bernstein(Br,nQc,one,iOut)	! one means free end
!		--------------
	sumt = zero	
	do 10 j= 1,nQc
	sumt = sumt + Br(j)*Qd(j+nQ5) 
   10	continue
	tEnd = sumt 
!	--------------------------- Check
	if(tEnd.GT.pi) Then
		ThetaNeedUpdate_STR = .TRUE.
		write(iOut,1010) tEnd
	endif
! 
!	done
!
	iPrt = 0
	if(iPrt == 1) Then
		write(iOut,1010) tEnd
	endif
!
 1010 format("THETA RESET at tEnd = ",e12.5)
	end FUNCTION
