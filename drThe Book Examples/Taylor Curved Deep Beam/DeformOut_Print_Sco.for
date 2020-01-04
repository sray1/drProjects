	Subroutine DeformOut_Print_Sco(XLF,Qd,Qc,Conv,sign,iter,
     &                                 	iOut,iOutS,EndwSav)
	Implicit Real(kind=8) (a-h,o-z)

	include 'LoadStepIter.h'
	include 'Output.h'
	include 'geometry.h'
	include 'SizeVar.h'

	logical SaveStep
!
!	Real(kind=4)	u,v,w,t    
	
	Real(kind=8)	Qc(nDim,nQc1,nQc2),Coord(nDim)    
	
	Real(kind=8)	Qd     ,EndwSav     ,DefSav   
	Dimension		Qd(nQd),EndwSav(4,*),DefSav(3,nPtsi*nPtsj)
	Real(kind=8)	Dis      ,Rot    
	Dimension		Dis(nDim),Rot(nDim)
	character*1		sign
	Data			zero/0.D0/,one/1.D0/,two/2.D0/
!	----------------------------------------------- only last corner node
		ri		= one
		rj		= one
!		-------------------------------------------- Calc Displacements		 
		Dis = 0.D0
		call CalcDis_at_a_Pt(Dis,Qd,nQd,nDim,nQd1,nQd2,ri,rj)
		Rot = 0.D0
		call CalcRot_at_a_Pt(Rot,Qd,nQd,nDim,nQd1,nQd2,ri,rj)
!		--------------
		u	= Dis(1)
		v	= Dis(2)
		w	= Dis(3)
		t	= Rot(2)
!
		uEnd = u 
		wEnd = w 
		tEnd = t 
!
!	done
!
	iPrt = 1
	if(iPrt == 1) Then
		write(iOut,1010) iStep,two*XLF,uEnd,wEnd,tEnd,iter,Conv,
     &			sign
  110		continue
	endif
!
	return
!
 1010 format(i3,1x,4(3x,e12.5),i5,e12.4,2x,a1)
 1020 format(F15.2,",",F15.2,",",F15.2,",")
 1030 format(i3,e15.5)
	end