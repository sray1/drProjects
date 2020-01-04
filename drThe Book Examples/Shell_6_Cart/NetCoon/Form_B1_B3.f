	Subroutine Form B1_B3(Rad,AngT,AngP,Q1,Q4,B1,B3,nDim,nCurv,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!	====================================================
	Real(kind=8)	Q1(nDim),Q4(nDim)    
	Real(kind=8)	B1(nDim),B3(nDim)    
	Real(kind=8)	Rad,Ang    
	
	Data			zero/0.D0/,one/1.D0/,two/2.D0/,three/3.D0/
!	--------------------------------------------
	et27 = 8.D0/27.D0
	on27 = 1.D0/27.D0
!
	SELECT CASE (nCurv)
		CASE (1)							! Edge 1: Longitudinal   Phi = 0					
			AngT3 = AngT/three
			AngT2 = AngT*two/three
!
			B1(1) = Rad*dcos(AngT3)
			B1(2) = zero
			B1(3) = Rad*dsin(AngT3)
!
			B3(1) = Rad*dcos(AngT2)
			B3(2) = zero
			B3(3) = Rad*dsin(AngT2)
		CASE (2)							! Edge 2: Latitudinal   The = 0
			AngP3 = AngP/three
			AngP2 = AngP*two/three
!
			B1(1) = Rad*dcos(AngP3)
			B1(2) = Rad*dsin(AngP3)
			B1(3) = zero
!
			B3(1) = Rad*dcos(AngP2)
			B3(2) = Rad*dsin(AngP2)
			B3(3) = zero
		CASE (3)							! Edge 3: Longitudinal   Phi = 90
			AngT3 = AngT/three
			AngT2 = AngT*two/three
!
			B1(1) = Rad*dcos(AngT3)*dcos(AngP)
			B1(2) = Rad*dcos(AngT3)*dsin(AngP)
			B1(3) = Rad*dsin(AngT3)
!
			B3(1) = Rad*dcos(AngT2)*dcos(AngP)
			B3(2) = Rad*dcos(AngT2)*dsin(AngP)
			B3(3) = Rad*dsin(AngT2)
		CASE (4)							! Edge 4: Latitudinal   The = 72
			AngP3 = AngP/three
			AngP2 = AngP*two/three
!
			B1(1) = Rad*dcos(AngT)*dcos(AngP3)
			B1(2) = Rad*dcos(AngT)*dsin(AngP3)
			B1(3) = Rad*dsin(AngT)
!
			B3(1) = Rad*dcos(AngT)*dcos(AngP2)
			B3(2) = Rad*dcos(AngT)*dsin(AngP2)
			B3(3) = Rad*dsin(AngT)
		CASE DEFAULT
			return
	END SELECT
!	=============================
	B1	= B1 - et27*Q1 - on27*Q4
	B3	= B3 - et27*Q4 - on27*Q1
!	=============================
!
!	done
!
	return
!
 1020 format(F15.2,",",F15.2,",",F15.2,",")
	end
