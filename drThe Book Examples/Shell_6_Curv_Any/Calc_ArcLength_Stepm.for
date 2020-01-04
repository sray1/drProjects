	Subroutine Calc_ArcLength_Stepm(delLmO,delLm,iTermO,iTerm,iStep,
     &								iOut)
	Implicit Real(kind=8) (a-h,o-z)
!
	DATA zero/0.D0/,one/1.0D0/  
	
!
	DelLm = delLmO * (dble(iTerm)/dble(iTermO))
!!!=============================================== Temporary
!	DelLm = delLmO
!!!=============================================== Temporary: End
!
!	done
!
	iPrt = 0
	if(iStep == 5) then
		abc = 1
	endif
	if(iPrt == 1) Then
	write(iOut,1020) DelLm
  110		continue
	endif
!
	return
!
 1020 format("DelLm = ",F16.7/)
	end
