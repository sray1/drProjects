	Subroutine LoadParamChange(Qd1,Qd2,Qd,nA,DelLm,Imaginary,
!     &				DeltaLamdai1,DeltaLamdai2,aa,bb,cc,iOut)
     &				DeltaLamdai1,DeltaLamdai2,aa,bb,cc,iOut,
     &				PLoad,DelLamdaiO)
!=================================================================================
!							THIS SUBROUTINE NEEDS WORK
!=================================================================================
	Implicit Real(kind=8) (a-h,o-z)
!	At the beginning of each Loadstep
!============================================
	include 'LoadStepIter.h'
	include 'Examples.h'
!============================================
	Real(kind=8)	Qd    ,Qd1    ,Qd2
	Dimension		Qd(nA),Qd1(nA),Qd2(nA)
	Real(kind=8)	PLoad    
	Dimension		PLoad(nA)
	Logical Imaginary
	DATA zero/0.D0/,one/1.0D0/,two/2.D0/  
!
	Imaginary = .FALSE.
!
	sumPa	= zero	
	sumPc	= zero	
	suma	= zero	
	sumb	= zero	
	sumc	= zero	
!================================================================================== Without P
	if(nEx.LE.4.or.nEx==11.or.nEx==12.or.(nEx==10)) Then
		do 20 i = 1,nA	 
!	if(nEx.LE.2) Then
!		----------------------------------------------------------------- Lin3D
		suma = suma + Qd2(i) * Qd2(i) 
		sumb = sumb + (Qd(i)+Qd1(i)) * Qd2(i)
		sumc = sumc + (Qd(i)+Qd1(i)) * (Qd(i)+Qd1(i))
!		----------------------------------------------------------------- Lin3D:END
   20		continue
		aa	= suma 
		bb	= sumb
		cc	= sumc - DelLm*DelLm
		if((iStep == 9999.or.iStep == 9999).AND.(iNut == 1)) Then
!		if((iStep == 1.or.iStep == 9999).AND.(iNut.EQ.2)) Then
			call DumpIntegerVar(iStep,"iStep",1,iOut)
			call DumpIntegerVar(iNut,"iNut",1,iOut)
			call DumpRealArray(Qd,nA,"LoadParamChange:Qd",1,iOut)
			call DumpRealArray(Qd1,nA,"LoadParamChange:Qd1",1,iOut)
			call DumpRealArray(Qd2,nA,"LoadParamChange:Qd2",1,iOut)
C                                 Print results
			abc = 1
		endif
!
		b2ac  = bb*bb - aa*cc
		if(b2ac.LT.zero) Then
			Imaginary = .TRUE.
!			DelLm = DelLm/two
			return
		endif
!		----------------------- roots
		DeltaLamdai1 = (-bb + dsqrt(b2ac))/aa
		DeltaLamdai2 = (-bb - dsqrt(b2ac))/aa
	endif
!================================================================================== With P
	if( (nEx == 5).or.(nEx == 6) ) Then
		do 30 i = 1,nA	 
		P2 = PLoad(i) * PLoad(i)
!	elseif( (nEx == 3).or.(nEx == 6) ) Then
!		----------------------------------------------------------------- BatBalony
		suma	= suma	+ Qd2(i) * Qd2(i) 
		sumPa	= sumPa + P2
		sumb	= sumb	+ (Qd(i)+Qd1(i)) * Qd2(i) + P2 * DelLamdaiO
		sumc	= sumc	+ (Qd(i)+Qd1(i)) * (Qd(i)+Qd1(i))
		sumPc	= sumPc + P2 * DelLamdaiO * DelLamdaiO
!		----------------------------------------------------------------- BatBalony:End
   30		continue
		aa	= suma 
		aaP = aa + sumPa
		bb	= sumb
		cc	= sumc - DelLm*DelLm
		ccP = cc + sumPc
		if((iStep == 9999.or.iStep == 9999).AND.(iNut == 1)) Then
!		if((iStep == 1.or.iStep == 9999).AND.(iNut.LE.2)) Then
			abc = 1
			call DumpIntegerVar(iStep,"iStep",1,iOut)
			call DumpIntegerVar(iNut,"iNut",1,iOut)
			call DumpRealArray(Qd,nA,"LoadParamChange:Qd",1,iOut)
			call DumpRealArray(Qd1,nA,"LoadParamChange:Qd1",1,iOut)
			call DumpRealArray(Qd2,nA,"LoadParamChange:Qd2",1,iOut)
C                                 Print results
		endif
!
		b2acP = bb*bb - aaP*ccP 
		if(b2acP.LT.zero) Then
			Imaginary = .TRUE.
!			DelLm = DelLm/two
			return
		endif
!		----------------------- roots
		DeltaLamdai1 = (-bb + dsqrt(b2acP))/aaP
		DeltaLamdai2 = (-bb - dsqrt(b2acP))/aaP
	endif
!
!	done
!
	iPrt = 0
	if(iPrt == 1) Then
		write(iOut,1020) DeltaLamdai1,DeltaLamdai2
	endif
!
	return
!
 1020 format("LoadParamChange:DeltaLamdai1 = ",F16.7,
     &						"DeltaLamdai1 = ",F16.7/)
	end
