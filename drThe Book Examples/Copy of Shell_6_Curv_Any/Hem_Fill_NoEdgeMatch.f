	Subroutine Hem_FillNoEdgeMatch(nEdgeIn,nEdgEnl,nElem,nodEl,nQ,
     &				nodGl,nodMax,nDof,nodAssign,nPtr,nEqnMax,
     &			     InExCn,nodInMax,ISupIn,nSupIn,
     &					Nel,nBeg,nEnd,iCur,iOut)
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
	integer nodEl(nQ,nQ),nodGl(nodMax,nDof)
	LOGICAL bSup
!		================================================================== no Edge Match/Assign new nodes
		! fill with corner and new edge nodes
		SELECT CASE (iCur)	
			CASE (4)																! left edge 
				do ne = 1,nodInMax						! common Corner or assign
					if(InExCn(1,ne) == nEnd) then
							if(InExCn(2,ne) == 0) then													
								nodAssign				= nodAssign+1
								nPtr					= nPtr + 1
								nodEl(1,1)				= nodAssign
								InExCn(2,ne)			= nodAssign
								nEdgEnl(iCur,nQ,Nel)	= nodAssign ! update enlarged edge nodes
							else
								nodEl(1,1)				= InExCn(2,ne)
								nEdgEnl(iCur,nQ,Nel)	= InExCn(2,ne) ! update enlarged edge nodes
							end if
					end if
				end do !ne
				do ifil = 2,nQ-1								! in-between
					nodAssign				= nodAssign+1
						nPtr				= nPtr + 1
					nodEl(1,ifil)			= nodAssign
					nEdgEnl(iCur,ifil,Nel)	= nodAssign ! update enlarged edge nodes
				end do	!ifil
				do ne = 1,nodInMax						! common Corner or assign
					if(InExCn(1,ne) == nBeg) then
							if(InExCn(2,ne) == 0) then													
								nodAssign				= nodAssign+1
								nPtr					= nPtr + 1
								nodEl(1,nQ)				= nodAssign
								InExCn(2,ne)			= nodAssign
								nEdgEnl(iCur,1,Nel)		= nodAssign ! update enlarged edge nodes
							else
								nodEl(1,nQ)			= InExCn(2,ne)
								nEdgEnl(iCur,1,Nel) = InExCn(2,ne) ! update enlarged edge nodes
							end if
					end if
				end do !ne
!				nodEl(1,nQ)				= nBeg
			CASE (3)																! top edge 
				do ne = 1,nodInMax						! common Corner or assign
					if(InExCn(1,ne) == nEnd) then
							if(InExCn(2,ne) == 0) then													
								nodAssign		= nodAssign+1
								nPtr			= nPtr + 1
								nodEl(1,nQ)		= nodAssign
								InExCn(2,ne)	= nodAssign
								nEdgEnl(iCur,nQ,Nel)	= nodAssign ! update enlarged edge nodes
							else
								nodEl(1,nQ)				= InExCn(2,ne)
								nEdgEnl(iCur,nQ,Nel)	= InExCn(2,ne) ! update enlarged edge nodes
							end if
					end if
				end do !ne				
				do ifil = 2,nQ-1								! in-between
					nodAssign				= nodAssign+1
						nPtr				= nPtr + 1
					nodEl(ifil,nQ)			= nodAssign
					nEdgEnl(iCur,ifil,Nel)	= nodAssign ! update enlarged edge nodes
				end do	!ifil
				do ne = 1,nodInMax						! common Corner or assign
					if(InExCn(1,ne) == nBeg) then
							if(InExCn(2,ne) == 0) then													
								nodAssign		= nodAssign+1
								nPtr			= nPtr + 1
								nodEl(nQ,nQ)	= nodAssign
								InExCn(2,ne)	= nodAssign
								nEdgEnl(iCur,1,Nel) = nodAssign ! update enlarged edge nodes
							else
								nodEl(nQ,nQ)		= InExCn(2,ne)
								nEdgEnl(iCur,1,Nel) = InExCn(2,ne) ! update enlarged edge nodes
							end if
					end if
				end do !ne
!				nodEl(nQ,nQ)			= nBeg
			CASE (2)																! right forward
				do ne = 1,nodInMax						! common Corner or assign
					if(InExCn(1,ne) == nBeg) then
							if(InExCn(2,ne) == 0) then													
								nodAssign		= nodAssign+1
								nPtr			= nPtr + 1
								nodEl(nQ,1)		= nodAssign
								InExCn(2,ne)	= nodAssign
								nEdgEnl(iCur,1,Nel)	= nodAssign ! update enlarged edge nodes
							else
								nodEl(nQ,1)		= InExCn(2,ne)
								nEdgEnl(iCur,1,Nel)	= InExCn(2,ne) ! update enlarged edge nodes
							end if
					end if
				end do !ne
				do ifil = 2,nQ-1								! in-between
					nodAssign			= nodAssign+1
						nPtr			= nPtr + 1
					nodEl(nQ,ifil)		= nodAssign
					nEdgEnl(iCur,ifil,Nel)	= nodAssign ! update enlarged edge nodes
				end do	!ifil
				do ne = 1,nodInMax						! common Corner or assign
					if(InExCn(1,ne) == nEnd) then
							if(InExCn(2,ne) == 0) then													
								nodAssign		= nodAssign+1
								nPtr			= nPtr + 1
								nodEl(nQ,nQ)	= nodAssign
								InExCn(2,ne)	= nodAssign
								nEdgEnl(iCur,nQ,Nel) = nodAssign ! update enlarged edge nodes
							else
								nodEl(nQ,nQ)		= InExCn(2,ne)
								nEdgEnl(iCur,nQ,Nel) = InExCn(2,ne) ! update enlarged edge nodes
							end if
					end if
				end do !ne
			CASE (1)																! bot forward
				do ne = 1,nodInMax						! common Corner or assign
					if(InExCn(1,ne) == nBeg) then
							if(InExCn(2,ne) == 0) then													
								nodAssign		= nodAssign+1
								nPtr			= nPtr + 1
								nodEl(1,1)		= nodAssign
								InExCn(2,ne)	= nodAssign
								nEdgEnl(iCur,1,Nel) = nodAssign ! update enlarged edge nodes
							else
								nodEl(1,1)		= InExCn(2,ne)
								nEdgEnl(iCur,1,Nel) = InExCn(2,ne) ! update enlarged edge nodes
							end if
							go to 10 
					end if
				end do !ne
   10				continue
				do ifil = 2,nQ-1								! in-between
					nodAssign				= nodAssign+1
						nPtr				= nPtr + 1
					nodEl(ifil,1)			= nodAssign
					nEdgEnl(iCur,ifil,Nel)	= nodAssign ! update enlarged edge nodes
				end do	!ifil
				do ne = 1,nodInMax						! common Corner or assign
					if(InExCn(1,ne) == nEnd) then
							if(InExCn(2,ne) == 0) then													
								nodAssign		= nodAssign+1
								nPtr			= nPtr + 1
								nodEl(nQ,1)		= nodAssign
								InExCn(2,ne)	= nodAssign
								nEdgEnl(iCur,nQ,Nel) = nodAssign ! update enlarged edge nodes
							else
								nodEl(nQ,1)		= InExCn(2,ne)
								nEdgEnl(iCur,nQ,Nel) = InExCn(2,ne) ! update enlarged edge nodes
							end if
							go to 20 
					end if
				end do !ne
   20				continue
			CASE DEFAULT
				stop 'Hem_FillNoEdgeMatch:iCur.NE.1->4'
		END SELECT
!	===================================================== global eqn numbers
	call Hem_SupportCheck(iSupIn,nSupIn,InExCn,nodGl,
     &				nEqnMax,nodInMax,nQ,nEdgEnl,iCur,Nel,
     &							nodMax,nDof,nElem,iOut)
!	===================================================== global eqn numbers: End
	return
	end   		