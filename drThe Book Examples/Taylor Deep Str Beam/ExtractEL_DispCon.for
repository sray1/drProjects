	Subroutine Extract_DispCon(XS,nStifS,XE,nStifEL,
     &					Index,Nel,iOut)
!
!	XS(nStifS)	= Solved Bezier Displacement Controls (Input)
!	XE(nStifEL)	= Element Bezier Displacement Controls (Output)	
!
	real(kind = 8)	XS        ,XE     
	Dimension		XS(nStifS),XE(nStifEL)
	integer i,ii,Index(nStifEL)
!------------------------------
!	call Initiate_ExtractionIndex(Index,nStifEL,Nel,iOut)
!
	XE = 0.D0	! initialize
!
	if (Nel == 1) then
		do  i = 1,nStifEL
			XE(i) = XS(i)
		end do !i
	elseif (Nel == 2) then
		do  i = 1,nStifEL
			XE(i) = XS(Index(i))
		end do !i
	endif
  100 continue
!
	write(iOut,1000)
	write(iOut,1010) Nel,nStifEL,(XE(i),i = 1,nStifEL)
!	
!   		 
	return
 1000 Format(/2x,"Just before Leaving: Extract_DispCon"/)
 1010 Format(/2x,"Extracted DisControls for Element ",I2,": 1x",I3/
     &										3(5(2x,F16.4)/) )
	end
