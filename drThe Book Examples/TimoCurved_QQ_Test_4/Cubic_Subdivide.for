	Subroutine Cubic_Subdivide(QcI,nR,nCi,QcO,rs,iOut)
	
	real(kind = 8)	QcI
	Dimension		QcI(nR,nCi)
	real(kind = 8)	QcO        ,rs
	Dimension		QcO(nR,nCi)
	real(kind = 8)	rs2,rs3,rsm1,rsm2,rsm3
	integer			nR,nCi,nCo
!
	if(nCi.NE.4) Then
		Stop 'nCi.NE.4 (Cubic)'
	endif
!	---------------------------------
	rs2		= rs*rs
	rs3		= rs2*rs
	rsm1	= 1.D0 - rs
	rsm2	= rsm1*rsm1
	rsm3	= rsm2*rsm1
!	-----------------
	do 10 i = 1,nR
	QcO(i,1)	=		 QcI(i,1)
	QcO(i,2)	=	rsm1*QcI(i,1) +			  rs*QcI(i,2)
	QcO(i,3)	=	rsm2*QcI(i,1) + 2.D0*rsm1*rs*QcI(i,2) + 
     &					          rs2*QcI(i,3)
	QcO(i,4)	=	rsm3*QcI(i,1) + 3.D0*rsm2*rs*QcI(i,2) + 
     &					3.D0*rsm1*rs2*QcI(i,3) + rs3*QcI(i,4)
   10 continue
!-------------------------------------
	return
	end
	
