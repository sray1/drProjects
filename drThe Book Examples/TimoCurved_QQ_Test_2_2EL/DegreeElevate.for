	Subroutine DegreeElevate(QcI,nR,nCi,QcO,nCo,iOut)
	
	real(kind = 8)	QcI
	Dimension		QcI(nR,nCi)
	real(kind = 8)	QcO
	Dimension		QcO(nR,nCo)
	real(kind = 8)	xj,xn,xjn
	integer			nR,nCi,nCo
!
	if((nCi+1).NE.nCo) Then
		Stop '(nCi+1).NE.nCo'
	endif
!
!	Find n 
!
	n		= nCi - 1
!	-----------------
	do 10 i = 1,nR
	QcO(i,1)	= QcI(i,1)
	QcO(i,nCo)	= QcI(i,nCi)
   10 continue
!	------------------------
	xn1 = n + 1
	do 20 j = 1,n
	xj	= j
	xjn	= xj/xn1
	do 20 i = 1,nR
	QcO(i,j+1)	= xjn*Qci(i,j) + (1.D0- xjn)*Qci(i,j+1)
   20 continue	
!-------------------------------------
	return
	end
	
