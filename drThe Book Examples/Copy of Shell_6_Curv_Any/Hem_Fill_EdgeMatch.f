	Subroutine Hem_Fill_EdgeMatch(nEdgEnl,nElem,nodEl,nQ,
     &				iCur,jCur,nCur,Nel,bFor,iOut)
!															
	Implicit Real(kind=8) (a-h,o-z)
!	===============================================
!	HARDCODED for nQd1 = nQd2 = 8 and nStifel = 216
!	===============================================
	include 'Scratch.h'
!	------------------	
	integer nEdgEnl(4,nQ,nElem)
	LOGICAL bFor
!	Outputs 
!		Indx(nStifEl)	= Indx of assembly for Element 2
!
	integer nodEl(nQ,nQ)
!	---------------------------------------------------------- check for common Edge(s) w/ assined Nodes
	SELECT CASE (iCur)	
		CASE (4)										
			do ifil = 1,nQ
				if(bFor) then										
					nodEl(1,ifil) = nEdgEnl(jCur,nQ+1-ifil,nCur)		! left edge forward copy
				else															
					nodEl(1,ifil) = nEdgEnl(jCur,ifil,nCur)				! left edge backward copy
				end if						
			end do !ifil 
		CASE (3)										
			do ifil = 1,nQ
				if(bFor) then											
					nodEl(ifil,nQ) = nEdgEnl(jCur,nQ+1-ifil,nCur)		! top edge backward copy	
				else															
					nodEl(ifil,nQ) = nEdgEnl(jCur,ifil,nCur)			! top edge forward copy
				end if						
			end do !ifil 
		CASE (2)										
			do ifil = 1,nQ
 				if(bFor) then										! right edge backward copy
    					nodEl(nQ,ifil) = nEdgEnl(jCur,nQ+1-ifil,nCur)	
				else
    					nodEl(nQ,ifil) = nEdgEnl(jCur,ifil,nCur)	
				end if						
			end do !ifil 
		CASE (1)										! bot edge reverse copy
			do ifil = 1,nQ
  				if(bFor) then
    					nodEl(ifil,1) = nEdgEnl(jCur,nQ+1-ifil,nCur)	
				else										! bot edge backward copy
    					nodEl(ifil,1) = nEdgEnl(jCur,ifil,nCur)	
				end if						
			end do !ifil 
		CASE DEFAULT
			stop 'Hem_FillElemNodes:iCur.NE.1->4'
	END SELECT
!	==============
  100	continue
	do ifil = 1,nQ
 		if(bFor) then										
			nEdgEnl(iCur,ifil,Nel) 
     &					= nEdgEnl(jCur,ifil,nCur)
		else
			nEdgEnl(iCur,ifil,Nel) 
     &					= nEdgEnl(jCur,nQ+1-ifil,nCur)
		end if						
	end do !ifil 
!	=============
	return
	end   		