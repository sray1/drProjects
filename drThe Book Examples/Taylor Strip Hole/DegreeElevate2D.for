	Subroutine DegreeElevate2D(QcI,nR,nCi1,nCi2,QcO,nCo1,nCo2,iOut)
!	elevation by one degree in each direction	

	Implicit Real(kind=8) (a-h,o-z)

	real(kind = 8)	QcI
	Dimension		QcI(nR,nCi1,nCi2)
	real(kind = 8)	QcO
	Dimension		QcO(nR,nCo1,nCo2)
	real(kind = 8)	xm1,xn1,xj,xjm,xjm1,xk,xkn,xkn1
	integer			nR,nCi,nCo
!
	if(((nCi1+1).NE.nCo1).or.((nCi2+1).NE.nCo2) ) Then
		Stop '(nCi1+1).NE.nCo1).or.(nCi2+1).NE.nCo2)'
	endif
!
!	Find m,n : input degrees
!
	m		= nCi1 - 1
	n		= nCi2 - 1
!	--------------------------------------- corner nodes same
	do 10 i = 1,nR
	QcO(i,1,1)			= QcI(i,1,1)
	QcO(i,nCo1,1)		= QcI(i,nCi1,1)
	QcO(i,1,nCo2)		= QcI(i,1,nCi2)
	QcO(i,nCo1,nCo2)	= QcI(i,nCi1,nCi2)
   10 continue
!	--------------------------------------- elevate rest
	xm1 = dble(m + 1) 
	xn1 = dble(n + 1)
	do 20 j = 1,m
	do 20 k = 1,n
	xj		= dble(j)
	xjm		=	xj/xm1
	xjm1	= 1.D0 - xjm
	xk		= dble(k)
	xkn		=	xk/xn1
	xkn1	= 1.D0 - xkn
	do 20 i = 1,nR
	QcO(i,j+1,k+1)	= xjm *(xkn*Qci(i,j,k)   + xkn1*Qci(i,j,k+1))
     &                + xjm1*(xkn*Qci(i,j+1,k) + xkn1*Qci(i,j+1,k+1))  
   20 continue	
!-------------------------------------
	return
	end
	
