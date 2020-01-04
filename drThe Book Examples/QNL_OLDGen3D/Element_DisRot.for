	Subroutine Element_DisRot(A,nA,cName,iPrt,iOut)

	Implicit Real(kind=8) (a-h,o-z)
	dimension A(nA)
	character*(*) cName
!-------------------------------------------- 
!----------------------------------------------------------------------------
!
!	Extract Element 1 Controls & Evaluate Disp./Strains/Stresses
!
	
		call Extract_DispCon(A(n7),nStifS,A(n4),nStifEL,1,iOut)
		if(nElem == 1) Then
			call Compute_DisRot_2ELModel(A(n1a),nQc,A(n4),nStifEL,P,
     &			A(nU),A(nV),A(nW),A(nRx),A(nRy),A(nRz),A(nMDR),
     &			nDis,(nDis+1)/2,nDis+1,1,iOut)
		else
			call Compare_DisRot_2ELModel(A(n1a),nQc,A(n4),nStifEL,P,
     &			A(nU),A(nV),A(nW),A(nRx),A(nRy),A(nRz),A(nMDR),
     &			nDis,(nDis+1)/2,nDis+1,1,iOut)
		endif
!-------------------------------------------------------------------- 2-Elements
!	Extract Element 2 Controls & Evaluate Disp./Strains/Stresses
!
		if(nElem == 2) Then
			call Extract_DispCon(A(n7),nStifS,A(n4),nStifEL,2,iOut)
			call Compute_DisRot_2ELModel(A(n1b),nQc,A(n4),nStifEL,P,
     &			A(nU),A(nV),A(nW),A(nRx),A(nRy),A(nRz),A(nMDR),
     &			nDis,(nDis+1)/2,nDis+1,2,iOut)
		endif
!--------------------------------------------------------------------
	end if
!--------------------------------------------------------------------
	if(iPrt == 0) return
	write(iOut,1000) cName,nA
	write(iOut,1010) (A(i),i = 1,nA)
!	-------------
	return
 1000 format(1X,A13, "(",I3,") Array"/)
 1010 format(4(F20.10,1X))
	end
