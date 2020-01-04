	Subroutine CalcCoords_at_a_Pt_Hem4(Coord,Ao12N,ri,rj,Nel)
!	===================================================================
!	HARDCODED for LINES OF CURVATURES ALONG COORDINATE DIRECTIONS 1 & 2
!	===================================================================
	Implicit Real(kind=8) (a-h,o-z)
!	====================
	include 'SizeVar.h'
	include 'files.h'
	include 'Scratch.h'
!	====================
	Real(kind=8)	Coord                      
	Dimension		Coord(3)
      Real(kind=8)	Ao1   ,Ao2   ,xNor   ,A1hat   ,A2hat                           
      Dimension		Ao1(3),Ao2(3),xNor(3),A1hat(3),A2hat(3)
      Real(kind=8)	Ao12N                                
      Dimension		Ao12N(3,3)
	  Real(kind=8)	sT,cT,xLam1,xLam2,RutAhat                     
	Real(kind=8)	A1      ,A2         
	Dimension		A1(nDim),A2(nDim)

	Real(kind=8)	ftmin   ,ftmax   ,fpmin   ,fpmax        
	Dimension	    ftmin(4),ftmax(4),fpmin(4),fpmax(4)
!	========================================================== HARDCODED for  2x2 elements
	DATA ftmin	/0.0D0,0.5D0,0.0D0,0.5D0/
	DATA ftmax	/0.5D0,1.0D0,0.5D0,1.0D0/
	DATA fpmin	/0.0D0,0.0D0,0.5D0,0.5D0/
	DATA fpmax	/0.5D0,0.5D0,1.0D0,1.0D0/
!	============================================================================== 2X2 END
	DATA factp	/0.80D0/
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/,onm/-1.0D0/ 
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	-------------------------------------------------------------------- Curvatures/Det etc 
	piby2 = asin(1.D0)
	rad = 10.D0			! HARDCODED for radius = 10
!	----------------------------
	tmin = ftmin(Nel)*piby2					! HARDCODED for 90 deg		2x2 elems
	tmax = ftmax(Nel)*piby2					! HARDCODED for 90 deg
	pmin = fpmin(Nel)*factp*piby2			! HARDCODED for 90 deg
	pmax = fpmax(Nel)*factp*piby2			! HARDCODED for 90 deg
!	=========================================================================
	the	= tmax - tmin
	phe = pmax - pmin
!	=========================================================== 
	tri = tmin + (tmax - tmin)*ri
	prj = pmin + (pmax - pmin)*rj
!	----------------------------------------------------------- coords
	Coord(1) = rad*dcos(prj)*dcos(tri)
	Coord(2) = rad*dcos(prj)*dsin(tri)
	Coord(3) = rad*dsin(prj)
!	----------------------------------------------------------- metric Tensor
	A1hat(1) = -rad*dcos(prj)*dsin(tri)*the
	A1hat(2) =  rad*dcos(prj)*dcos(tri)*the
	A1hat(3) = zero
!
	A2hat(1) = -rad*dsin(prj)*dcos(tri)*phe
	A2hat(2) = -rad*dsin(prj)*dsin(tri)*phe
	A2hat(3) =  rad*dcos(prj)*phe
!	---------------------------------------------------- unit normal
	call CrossProduct(A1hat,A2hat,xNor,Iout)
	call VectorNorm(xNor,A,3,Iout)
	call ScaleVector(xNor,xNor,1.D0/A,3,Iout)
!	-------------------------------------------------- Bases: Ao1 & Ao2
!														 & Ao12N Coord Xformation
	A1 = A1hat
	A2 = A2hat
!	------------------------------------------- Lamda1 & Lamda2
	call VectorNorm(A1,xLam1,3,Iout)
	call ScaleVector(A1,Ao1,1.D0/xLam1,3,Iout)
	call VectorNorm(A2,xLam2,3,Iout)
	call ScaleVector(A2,Ao2,1.D0/xLam2,3,Iout)
!
	Ao12N(1,1) = Ao1(1)
	Ao12N(2,1) = Ao1(2)
	Ao12N(3,1) = Ao1(3)
!	------------------------------------------- Xformation:
!												Global Cartesian -> Lines of Curvs.
	Ao12N(1,2) = Ao2(1)
	Ao12N(2,2) = Ao2(2)
	Ao12N(3,2) = Ao2(3)
!
	Ao12N(1,2) = Ao2(1)
	Ao12N(2,2) = Ao2(2)
	Ao12N(3,2) = Ao2(3)
!
	Ao12N(1,3) = xNor(1)
	Ao12N(2,3) = xNor(2)
	Ao12N(3,3) = xNor(3)
!	----------------------------------------------------------- Lines of curvatures
	iPrt = 0
	if(iPrt == 1) then
		call DumpStringVar("Beg:CalcCoords_at_a_Pt_Hem4",iPrt,iOut)
		call DumpRealVar(ri,"ri",iPrt,iOut)
		call DumpRealVar(rj,"rj",iPrt,iOut)
		call DumpRealArray(Coord,3,"Coord",iPrt,iOut)
		call DumpRealMatrix(Ao12N,3,3,"Ao12N",iPrt,iOut)
		call DumpStringVar("End:CalcCoords_at_a_Pt_Hem4",iPrt,iOut)
	endif
	iPrt = 0
!	================================================== save in tape
!	call PutGetRefPropsatGaussPt(iRefPro1,jCInt,1)
!	================================================== save in tape end
!
!	done
!
	return
	end
