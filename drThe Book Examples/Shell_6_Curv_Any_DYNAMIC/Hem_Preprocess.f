	Subroutine Hem_Preprocess(iOut)
	
	
	
!															
	Implicit Real(kind=8) (a-h,o-z)
!	===============================================
!	HARDCODED for nQd1 = nQd2 = 8 and nStifel = 216
!	===============================================
	include 'Scratch.h'
!	------------------	
!		nEqn			= nQd*nQd*ndof
!		nEdgeIn(nElem,nQorT) Quadrilateral element: nQorT =4
!		nEdgeIn(nElem,nQorT) Triangular element:	nQorT =3
!		iSupIn(8,nSup) 
!		inExCn(2,nodInMax) nodInMax=no. of max input corner controls
!	Outputs 
!		Indx(nStifEl)	= Indx of assembly for Element 2	integer Indx(nQ,nQ,nDof)
!		nodEl(nQ,nQ)
!		nodGL(nodMax,nDof)
!
!=========================================================================== Quintic
	integer nEdgeIn(4,4),nEdgEnl(4,6,4),InExCn(2,9)!nodInMax
	integer nodEl(6,6),nodGl(121,6),Indx(216),iSupIn(8,4)! for nElem = 4
	DATA	nQ/6/,nDof/6/,nElem/4/,nodMax/121/,nodInmax/9/,
     &		nStifEl/216/,nSupIn/4/,nSupIn/4/,nSup/66/
!=========================================================================== Quintic: End
!=========================================================================== Quadratic
!	integer nEdgeIn(4,4),nEdgEnl(4,3,4),InExCn(2,9)!nodInMax
!	integer nodEl(3,3),nodGl(25,6),Indx(54),iSupIn(8,4)! for nElem = 4
!	DATA	nQ/3/,nDof/6/,nElem/4/,nodMax/25/,nodInmax/9/,
!     &		nStifEl/54/,nSupIn/4/,nSupIn/4/,nSup/30/
!=========================================================================== Quadratic: End
	DATA	nEdgeIn/						! 1=bot
     &			 1, 2, 4, 5,
     &			 2, 3, 5, 6,
     &			 5, 6, 8, 9,
     &			 4, 5, 7, 8/
	DATA	iSupIn/				! for Hem: nElem = 4
     &			 1,4,1,0,0,0,1,1, 
     &			 4,7,1,0,0,0,1,1, 
     &			 3,6,1,0,0,0,1,1, 
     &			 6,9,1,0,0,0,1,1/
!	==========================================================  store Externak Corner Nodes in Colm 1
!																corresponding Internal in Col 2
	iPrt = 1
	if(iPrt == 1) then											
		write(iOut,1001) ((nEdgeIn(i,j),j = 1,4),i = 1,4)
		write(iOut,1002) ((iSupIn(i,j),i = 1,8),j = 1,4)
	end if
	iPrt = 0
!
	InExCn = 0
	nst = 0
	do i = 1, 4
		do j = 1, 4
			nodEx = nEdgeIn(i,j)
			do k = 1,nodInmax
				if(InExCn(1,k) == nodEx) then
					go to 10
				endif
			end do !k
			nst = nst+1
			InExCn(1,nst) = nodEx
   10		continue
		end do !j
	end do !i
	iPrt = 0
	if(iPrt == 1) then
		write(iOut,1000) ((InExCn(i,j),j = 1,nodInmax),i = 1,2)
	end if
	iPrt = 0
!	==========================================================
!	nPtr		= nodInmax
	nPtr		= 0
	nodAssign	= 0
!	nodAssign	= nodInmax
	nEqnMax		= 0
	nodGl		= -1	! Not processed yet
!	---------------------------------------------------------- do it
!	do Nel = 1,nElem
	do Nel = 1,4
	    call Hem_FillElemNodes(nEdgeIn,nEdgEnl,nElem,nodEl,nQ,
     &				nodGl,nodMax,nDof,nodAssign,nPtr,nEqnMax,
     &			     InExCn,nodInMax,ISupIn,nSupIn,Nel,iOut)
!	========================================================= Print
		write(iOut,2030) Nel
		write(iOut,2031) 
		do i = 1,4 ! edges
			write(iOut,2032) (nEdgEnl(i,j,Nel),j = 1,nQ)
		end do	! i
!	========================================================== Element Eqn Index array
		Indx = 0
		call Hem_FormIndex_ELEM(nodEl,nQ,nodGl,nodMax,nDof,
     &							Indx,nStifEL,Nel,iOut)
!		---------------------------------------------------------- Save Indx
		call PutGetIndxEL(iIndxEL,Indx,nStifEL,Nel,1,iOut)	! 1 = write
!		---------------------------------------------------------- Save End
	end do !Nel
!
!	========================================================== Print
	iPrt = 1
	if(iPrt == 1) then
		write(iOut,2000) 
		write(iOut,2020) (i,(NodGl(i,j),j = 1,nDof),i = 1,nodMax)
		write(iOut,1000) ((InExCn(i,j),j = 1,nodInmax),i = 1,2)
	end if
	iPrt = 0
!	===========
	return
 1000 Format(/2x,"InExCn(i,j),j = 1,nodInmax),i = 1,2"/(9I8))
 1001 Format(/2x,"nEdgeIn(i,j),j = 1,4),i = 1,4"/(4I8))
 1002 Format(/2x,"iSupIn(i,j),i = 1,8),j = 1,4"/(8I8))



 2000 Format(/2x,"Just Finished PreProcessing: Hem_FillElemNodes")
 2020 Format(/12x,"GLobal Equations:i,NodGl(i,j),j = 1,nDof),
     &									i = 1,nodMax"/(7I10))
 2030 Format(/12x,"For Element #",I4/)
 2031 Format(/12x,"Enlarged Edges"/)
 2032 Format(15x,(3I10))

	end   		