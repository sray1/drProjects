	Subroutine Expand_BzDispCons(Xc,nXc,
     &			iDrop,inDrop,Dis,iDis,inDis,Xt,nXt,iOut)
!
!
!	Xc(nXc)		= Solved Bezier Displacement Controls (Input)
!	Xf(nFf)		= Full Bezier Displacement Controls (Output)	
!
	real(kind = 8)	Dis(inDis),Xt(nXt),Xc(nXc)
	integer			iDis(inDis),iDrop(inDrop)
!-----------------------------------------------
	integer i,ii
!
	Xt = 0.0	! initialize
	ii = 0
!			
	do 20 i = 1,nXt
		do k = 1,inDrop
			if (i == iDrop(k)) then			!supported or specified displacement
				do j = 1,inDis
					if (i == iDis(j)) then		!specified displacement; 
						Xt(i) = Dis(j)			!fill with specified displacement
						go to 20
					endif
				end do !j
				go to 20				!supported, so do nothing = 0.0
			endif
		end do !k
!	----------------------- Not Supported nor Displacement specified
	ii = ii + 1
!
	Xt(i) = Xc(ii)
   20 continue
!
	iPrt = 1
	if(iPrt == 1) Then
		write(iOut,1000)
!		write(iOut,1010) nXc,(XC(i),i = 1,nXc)
		write(iOut,1020) nXt,(Xt(i),i = 1,nXt)
	endif
!
	return
!
 1000 Format(/2x,"Just before Leaving: Expand_BezierDispControls"/)
 1010 Format(/2x,"NonSingular DisplacementControls: 1x"I3/
     &										3(4(2x,F16.8)/) )
 1020 Format(/2x,"Total DisplacementControls: 1x"I3/
     &										(4(2x,F16.8)) )
	end 
!
