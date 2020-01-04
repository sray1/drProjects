	Subroutine Hem_FillElemNodes(nEdgeIn,nEdgEnl,nElem,nodEl,nQ,
     &				nodGl,nodMax,nDof,nodAssign,nPtr,nEqnMax,
     &			     InExCn,nodInMax,ISupIn,nSupIn,Nel,iOut)
!															
	Implicit Real(kind=8) (a-h,o-z)
!	===============================================
!	HARDCODED for nQd1 = nQd2 = 8 and nStifel = 216
!	===============================================
	include 'Scratch.h'
!	------------------	
!		nEqn			= nQd*nQd*ndof
	integer nEdgeIn(nElem,4),nEdgEnl(4,nQ,nElem),InExCn(2,nodInMax)
	integer iSupIn(8,nSupIn)
!	Outputs 
!		Indx(nStifEl)	= Indx of assembly for Element 2
!
	integer nodEl(nQ,nQ),iYes(4),nodGl(nodMax,nDof)
	LOGICAL bFor
!	---------------------------------------------------------- Print
	iPrt = 0
	if(Nel == 9999) then
		iPrt = 1
	end if
	if(iPrt == 1) then
		write(iOut,1000)
		write(iOut,1010) Nel
		write(iOut,1020) (i,(NodGl(i,j),j = 1,nDof),
     &		i = 1,nodMax)
		do ne =1,Nel-1
			write(iOut,1030) ne,((nEdgEnl(i,j,Ne),j = 1,nQ),i = 1,4)
		end do !ne
	endif
	iPrt = 0
!	---------------------------------------------------------- internal nodes
	call Hem_Fill_InternalNodes(nodEl,nQ,
     &				nodGl,nodMax,nDof,nodAssign,nPtr,nEqnMax,
     &			     Nel,iOut)
!	---------------------------------------------------------- check for common Edge(s) w/ assined Nodes
	do i = 1, 4						! order of input of edges:4=left/3=top/2=right/1=bot
		nbeg = nEdgeIn(Nel,i) 
		nend = nEdgeIn(Nel,mod(i,4)+1)
		do ne = 1,nodInMax
			if(InExCn(1,ne) == nBeg) then
				nbE = InExCn(2,ne)
			endif
		end do !ne
		do ne = 1,nodInMax
			if(InExCn(1,ne) == nEnd) then
				neE = InExCn(2,ne)
			endif
		end do !ne
!
		do nn = 1,Nel-1				! with previous elements: is edge existing?
			do j = 1, 4		! 4 edges	1=left/2=top/3=right/4=bot
				nb		= nEdgEnl(j,1,nn)				! Edges enlarged
				ne		= nEdgEnl(j,nQ,nn)
				bFor	= .TRUE.
!		 
				if (nbE==nb.and.neE==ne) then		! a match so copy forward  from nodGl or EdgeEnlarged
!					---------------------------
					call Hem_Fill_EdgeMatch(nEdgEnl,nElem,nodEl,
     &						nQ,i,j,nn,Nel,bFor,iOut)
!					-------------------------------
					go to 100
				else if (nbE==ne.and.neE==nb) then		! a match so copy reverse from nodGl or EdgeEnlarged
					bFor = .FALSE.
!					---------------------------
					call Hem_Fill_EdgeMatch(nEdgEnl,nElem,nodEl,
     &						nQ,i,j,nn,Nel,bFor,iOut)
!					-------------------------------
					go to 100
				end if
			end do !j
		end do !nn
!		================================================================== no Edge Match/Assign new nodes
		! fill with corner and new edge nodes
		call Hem_FillNoEdgeMatch(nEdgeIn,nEdgEnl,nElem,nodEl,nQ,
     &				nodGl,nodMax,nDof,nodAssign,nPtr,nEqnMax,
     &			     InExCn,nodInMax,ISupIn,nSupIn,
     &					Nel,nBeg,nEnd,i,iOut)
  100		continue
	end do	!i
!	---------------------------------------------------------- Print
	iPrt = 0
	if(Nel == 1) then
		iPrt = 1
	end if
	if(iPrt == 1) then
		write(iOut,2000)
		write(iOut,2010) Nel
		write(iOut,2020) (i,(NodGl(i,j),j = 1,nDof),i = 1,nodMax)
		do ne =1,Nel
			write(iOut,2030) ne,((nEdgEnl(i,j,Ne),j = 1,nQ),i = 1,4)
		end do !ne
		write(iOut,3000) ((InExCn(i,j),j = 1,nodInmax),i = 1,2)
!		write(iOut,2040) ((nodEl(i,j),i = 1,nQ),j = nQ,1,-1)
	endif
	iPrt = 0
	if(Nel == 1) then
		abc = 1
	end if
!	=============
	return
 1000 Format(/2x,"Just After Entering: Hem_FillElemNodes")
 1010 Format(/2x,"Indices for Element#",i2," 
     &						for Global Assembly: ")
 1020 Format(/12x,"i,NodGl(i,j),j = 1,nDof),i = 1,nodMax"/(7I10))
 1030 Format(/12x,"For Elem = ",i4," :nEdgEnl(i,j,Nel),j = 1,nQ),",
     &										"i = 1,4)"/(6I10))

 2000 Format(/2x,"Just before Leaving: Hem_FillElemNodes")
 2010 Format(/2x,"Indices for Element#",i2," 
     &						for Global Assembly: ")
 2020 Format(/12x,"i,NodGl(i,j),j = 1,nDof),i = 1,nodMax"/(7I10))
 2030 Format(/12x,"For Elem = ",i4," :nEdgEnl(i,j,Nel),j = 1,nQ),",
     &										"i = 1,4)"/(6I10))
 2040 Format(/12x,"(nodEl(i,j),i = 1,nQ),j = nQ,1,-1"/(6I10))
 3000 Format(/12x,"InExCn(i,j),j = 1,nodInmax),i = 1,2"/(9I8/))
	end   		