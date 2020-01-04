	Subroutine Augment_LOAD_Arclen(Qdo,Qd,QF,nStif,ArcLen,Iout)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!
!	Inputs
!		Nel				= Element Number
!		nStif			= Row size of Load Vector
!		QF				= Assembled Load Vector (Conrtracted)
!		Qdo				= Starting State control vector
!		Qd				= Current State control vector
!		Iout			= Error Output file#
!		 	
!	Outputs 
!		Stif(64,64)		= Desired Stiffness Matrix
!		Trace			= trace of the matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
	Real(kind=8)	Qdo       ,Qd       ,QF		
	Dimension		Qdo(nStif),Qd(nStif),QF(nStif)
	Data two/2.D0/
!	//////////////////////
	do 60 j = 1,nStif
	qq = Qd(j) - Qdo(j)
   60	QF(nStif) = QF(nStif) + qq*qq
	QF(nStif) = QF(nStif) - ArcLen*ArcLen
!
!	done
!
	iPrt = 0
	if(iPrt == 1) Then
		write(iOut,1010) nStif,(Qf(j),j = 1,nStif)
  110		continue
	endif
!
	return
!
 1010 format("Augmented Load Vector:Qf(",I2,")"/
     &        (5(f10.6,1X)/))
	end   	
