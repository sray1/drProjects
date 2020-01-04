	subroutine DeformOut_MatLab_ElLoop(Conv,sign,iOut)
!-------------------------
	include 'Implicit.h'
!========================================================================
	include 'Blank.h'
	include 'LoadStepIter.h'
	include 'Wpointers.h'
	include 'Addpoints.h'
	include 'SizeVar.h'
!	------------------------------------------
	character*1		sign,pos,neg
	data			pos/'+'/,neg/'-'/
!------------------------------------------------------------------------- Elemental StepDisRot
		do 25 iEL = 1,nElem
			m1 =n1a
			if(iEL == 2) Then
				m1 =n1b
			elseif(iEL == 3) Then
				m1 =n1c
			endif
!			if(iEL.NE.nElem) then
!				goto 25
!			endif!			--------------------------------------------------------- 
			call Extract_DispCon(A(nxm),nStifS,A(ndelUiEL),	!Extract DisRotCOntrols
     &			nStifEL,iEL,iOut)
			call DeformOut_MatLab(A(m1),A(ndelUiEL),Conv,sign,
     &							A(nEndwSav),iEL)
   25		continue
!	--------------------------------------------------------------
	return
	end 
