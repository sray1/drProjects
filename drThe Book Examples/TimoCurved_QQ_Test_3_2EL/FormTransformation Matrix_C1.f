	Subroutine FormTransformationMatrix_C1(Qc1,Qc2,nQc,T,
     &									nStifS,nStifC,iOut)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!------------------------------------------------------------
!	C1- Contraints:
!	------------------------------ Quartic:nQc=5
!	 old Row         new Cols	
!		i5  = 0.5*i4	+ 0.5*i13
!		i10 = 0.5*i8	+ 0.5*i17
!	------------------------------ Quintic:nQc=6
!	 old Row         new Cols	
!		i6  = 0.5*i5	+ 0.5*i16
!		i12 = 0.5*i10	+ 0.5*i21
!-----------------------------------
!
!	Inputs
!		nStifS					= Row or Col size of SinStiffness matrix 
!		nStifC					= Row or Col size of ConStiffness matrix
!		 	
!	Outputs 
!		T(nStifS,nStifC)		= C1 Transformation Matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	Qc1       ,Qc2   
	Dimension		Qc1(2,nQc),Qc2(2,nQc)
	Real(kind=8)	T				,Alfa   ,Beta   
	Dimension		T(nStifS,nStifC),Alfa(4),Beta(4)
	
	Integer DofW,LocW(2)		!
	Integer DofU,LocU(2)		!
	Integer DofR,LocR(2)		!
!----------------------------------------------- Quartic:nQc=5
!	DATA DofW  / 5/			!To be removed by
!	DATA LocW  / 4,14/			! these and
!	DATA DofU  /10/			!To be removed by
!	DATA LocU  / 8,18/			! these and
!----------------------------------------------- Quintic:nQc=6
	DATA DofW  / 6/			!To be removed by
	DATA LocW  / 5,16/			! these and
	DATA DofU  /12/			!To be removed by
	DATA LocU  /10,21/			! these and
!	//////////////////////
!	Transformation Matrix 
!
	Half	= 0.5D0
	T		= 0.0D0	! everything zeroed
!
	iremoved = 0
	do 30 i = 1,nStifS
		if(i == DofW) Then
			T(i,LocW(1)) = Half
			T(i,LocW(2)) = Half
			iremoved = iremoved + 1
			go to 30
		else if(i == DofU) Then
			T(i,LocU(1)) = Half
			T(i,LocU(2)) = Half
			iremoved = iremoved + 1
			go to 30
		end if
   10     continue
	T(i,i-iremoved) = 1.0D0 
   30 continue
   40 continue		 
!
	do 110 i = 1,nStifS
!		write(iOut,1010) nStifS,nStifC,i,(T(i,j),j = 1,nStifC)
  110	continue
  120 continue
!
!
 1010 format("C1 Transformation Matrix:T(",I3,",",I3,")"/
     &        I5/(5(9(f5.2,1X)/)))
 1020 format("Alfa(4)"/4(f10.7,1X)/)
 1030 format("Beta(4)"/4(f10.7,1X)/)
!   		 
!   		 
	return
	end   		