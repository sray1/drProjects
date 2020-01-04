	Subroutine Hem_SupportCheck(iSupIn,nSupIn,InExCn,nodGl,
     &				nEqnMax,nodInMax,nQ,nEdgEnl,iCur,Nel,
     &							nodMax,nDof,nElem,iOut)
!															
	Implicit Real(kind=8) (a-h,o-z)
!	===============================================
	integer nEdgEnl(4,nQ,nElem),InExCn(2,nodInMax)
	integer iSupIn(8,nSupIn)
	integer nodGl(nodMax,nDof)
	LOGICAL bSup
!	===============================================
	nbCur	= nEdgEnl(iCur,1,Nel)
	neCur	= nEdgEnl(iCur,nQ,Nel)
!
	bSup = .FALSE.
	do j = 1, nSupIn						! internal node numbering
		nbS = iSupIn(1,j) 
		neS = iSupIn(2,j)
		do ne = 1,nodInMax
			if(InExCn(1,ne) == nbS) then
				nbS = InExCn(2,ne)
				go to 10
			endif
		end do !ne
   10		continue
		do ne = 1,nodInMax
			if(InExCn(1,ne) == neS) then
				neS = InExCn(2,ne)
				go to 20
			endif
		end do !ne
   20		continue
!
		if ((nbS==nbCur.and.neS==neCur).or.			
     &		 (nbS==neCur.and.neS==nbCur) ) then	
			bSup = .TRUE.
			jSup	 = j
			go to 30
		endif
	end do !j
   30 continue
!	=============================================== Yes Supported Edge
	if (bSup) then										
		do kN = 1,nQ
			do kDof = 1,nDof							
				nod = nEdgEnl(iCur,kN,Nel)
				if(iSupIn(2+kDof,jSup) == 1) then
					nodGl(nod,kDof)	= 0
				else if (nodGl(nod,kDof) == -1) then
					nEqnMax			= nEqnMax + 1
					nodGl(nod,kDof)	= nEqnMax
				endif
			end do !kDof
		end do !kN
!		=======
		return
!		=======
	end if
!	=============================================== Not Supported Edge:Check if Corner supported nBeg
	bSup = .FALSE.
	do j = 1, nSupIn						! internal node numbering
		nbS = iSupIn(1,j) 
		do ne = 1,nodInMax
			if(InExCn(1,ne) == nbS) then
				nbS = InExCn(2,ne)
				go to 40
			endif
		end do !ne
   40		continue
		if((nbS==nbCur)) then			
			bSup = .TRUE.
			jSup	 = j
			go to 50
		endif
	end do !j
	do j = 1, nSupIn						! internal node numbering
		neS = iSupIn(2,j) 
		do ne = 1,nodInMax
			if(InExCn(1,ne) == neS) then
				neS = InExCn(2,ne)
				go to 45
			endif
		end do !ne
   45		continue
		if((neS==nbCur)) then			
			bSup = .TRUE.
			jSup	 = j
			go to 50
		endif
	end do !j
!	=============================================== Corner nBeg supported
   50 continue
	if (bSup) then										
		do kDof = 1,nDof							! Corners supported
			if(iSupIn(2+kDof,jSup) == 1) then
				nodGl(nbCur,kDof)	= 0
			else if(nodGl(nbCur,kDof) == -1) then
				nEqnMax				= nEqnMax + 1
				nodGl(nbCur,kDof)	= nEqnMax
			end if
		end do !kDof
	else										! Corners NOT supported
		do kDof = 1,nDof
			if(nodGl(nbCur,kDof) == -1) then							
				nEqnMax				= nEqnMax + 1
				nodGl(nbCur,kDof)	= nEqnMax
			endif
		end do !kDof
	endif
!	=============================================== Not Supported Edge:Check if Corner supported nEnd
	bSup = .FALSE.
	do j = 1, nSupIn						! internal node numbering
		neS = iSupIn(2,j) 
		do ne = 1,nodInMax
			if(InExCn(1,ne) == neS) then
				neS = InExCn(2,ne)
				go to 60
			endif
		end do !ne
   60		continue
		if((neS==neCur)) then			
			bSup = .TRUE.
			jSup	 = j
			go to 70
		endif
	end do !j
	do j = 1, nSupIn						! internal node numbering
		nbS = iSupIn(1,j) 
		do ne = 1,nodInMax
			if(InExCn(1,ne) == nbS) then
				nbS = InExCn(2,ne)
				go to 65
			endif
		end do !ne
   65		continue
		if((nbS==neCur)) then			
			bSup = .TRUE.
			jSup	 = j
			go to 70
		endif
	end do !j
!	=============================================== Corner nEnd supported
   70 continue
	if (bSup) then										
		do kDof = 1,nDof							! Corbers supported
			if(iSupIn(2+kDof,jSup) == 1) then
				nodGl(neCur,kDof)	= 0
			else if(nodGl(neCur,kDof) == -1) then
				nEqnMax				= nEqnMax + 1
				nodGl(neCur,kDof)	= nEqnMax
			end if
		end do !kDof
	else										! Corbers NOT supported
		do kDof = 1,nDof							
			if(nodGl(neCur,kDof) == -1) then							
				nEqnMax				= nEqnMax + 1
				nodGl(neCur,kDof)	= nEqnMax
			endif
		end do !kDof
	endif
!	=============================================== In-between Edge Nodes
	do kN = 2,nQ-1									
		do kDof = 1,nDof							
			nod = nEdgEnl(iCur,kN,Nel)
			if(nodGl(nod,kDof) == -1) then							
				nEqnMax			= nEqnMax + 1
				nodGl(nod,kDof)	= nEqnMax
			endif
		end do !kDof
	end do !kN
!	===========
	return
	end   		