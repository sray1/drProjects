	Subroutine FormmEndBezs(Rad,AngT,AngP,Q1,Q4,nDim,nCurv,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!	====================================================
	Real(kind=8)	Q1(nDim),Q4(nDim)    
	Real(kind=8)	Rad,Ang    
	
	Data			zero/0.D0/,one/1.D0/,two/2.D0/
!	--------------------------------------------
	SELECT CASE (nCurv)
		CASE (1)							! Edge 1: Longitudinal   Phi = 0					
			Q1(1) = Rad
			Q1(2) = zero
			Q1(3) = zero
!
			Q4(1) = Rad*dcos(AngT)
			Q4(2) = zero
			Q4(3) = Rad*dsin(AngT)
		CASE (2)							! Edge 2: Latitudinal   The = 0
			Q1(1) = Rad
			Q1(2) = zero
			Q1(3) = zero
!
			Q4(1) = Rad*dcos(AngP)
			Q4(2) = Rad*dsin(AngP)
			Q4(3) = zero
		CASE (3)							! Edge 3: Longitudinal   Phi = 90
			Q1(1) = Rad*dcos(AngP)
			Q1(2) = Rad*dsin(AngP)
			Q1(3) = zero
!
			Q4(1) = Rad*dcos(AngT)*dcos(AngP)
			Q4(2) = Rad*dcos(AngT)*dsin(AngP)
			Q4(3) = Rad*dsin(AngT)
		CASE (4)							! Edge 4: Latitudinal   The = 72
			Q1(1) = Rad*dcos(AngT)
			Q1(2) = zero
			Q1(3) = Rad*dsin(AngT)
!
			Q4(1) = Rad*dcos(AngT)*dcos(AngP)
			Q4(2) = Rad*dcos(AngT)*dsin(AngP)
			Q4(3) = Rad*dsin(AngT)
		CASE DEFAULT
			return
	END SELECT
!	=======================================================
!
!	done
!
	return
!
 1020 format(F15.2,",",F15.2,",",F15.2,",")
	end
