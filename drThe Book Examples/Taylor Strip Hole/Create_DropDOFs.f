	Subroutine Create_DropDOFs(iDis,inDis,iSup,inSup,
     &						iDrop,inDrop,iOut)
!
!	iDis(nDis)		= Specified displacement DOFs (INPUT)	
!	iSup(nSup)		= Specified Supported DOFs (INPUT)	
!	iDrop(nDrop)	= To be Dropped DOFs (OUTPUT)
!	inDrop			= inDis + inSup
!
	integer	iDis(inDis),iSup(inSup),iDrop(inDrop)
!-------------------------------------- 
	do i = 1,inDis
	iDrop(i) = iDis(i)
	end do !i
!
	do i = 1,inSup
	iDrop(i+inDis) = iSup(i)
	end do !i
!
!	done
!
!	write(iOut,1000) (iDrop(i), i = 1, inDrop)
!	Pause
   80	continue
	return
!
 1000 format(/5x,'To be Dropped DOFs'/(16i5))
	end
