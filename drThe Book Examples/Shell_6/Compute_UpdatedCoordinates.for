	Subroutine Compute_UpdatedCoords(Qc,UQc,nDim,nQc,Qd,nQd,
     &							Nel,iType,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!--------------------------------------------------------------
!		nDim = 2 for planar Curve/ = 3 for 3D Curve
!		nQc  = 5 for Quartic/6 for Quintic	
!		Qc(nDim,nQc)		= Coordinate Controls		
!		UQc(nDim,nQc)		= UpdatedCoordinate Controls
!		nQd					= 3*nQc for u,w, theta for planar
!		Qd					= Current State Control
!--------------------------------------------------------------					
	Real(kind=8)	Qc     ,CQc     ,Qd
	Dimension		Qc(nDim,nQc),UQc(nDim,nQc),Qd(nQd)
	character*200	fmt
!
	go to (100,200),iType
!------------------------------------------------------- For Iteration Loop																				
  100 continue
	do 10 i = 1,nDim	 
	do 10 j = 1,nQc
	k = (i-1)*nQc + j	 
	UQc(i,j) = Qc(i,j) + Qd(k)
   10 continue
	go to 500
!------------------------------------------------------- For LoadStep Loop																				
  200 continue
	do 20 i = 1,nDim	 
	do 20 j = 1,nQc
	k = (i-1)*nQc + j	 
	UQc(i,j) = Qc(i,j) + Qd(k)
   20 continue
	do 30 i = 1,nDim	 
	do 30 j = 1,nQc
	k = (i-1)*nQc + j	 
	Qc(i,j) = UQc(i,j)
   30 continue
!
!	done
!
  500 continue
!
	iPrt = 0
	If (iPrt == 1) Then
		write(fmt,1000) nDim,nQc,nDim,nQc
		write(iOut,fmt) Nel,(i,(Qc(i,j),j=1,nQc),i=1,nDim)
	endif

!
	return
!
 1000 format("Updated QC(",I1",",I1,"): Elem# = ,I4//,"
     &        I1,"(I5,5X,",I1,"(f10.6,1X)//)")
	end
