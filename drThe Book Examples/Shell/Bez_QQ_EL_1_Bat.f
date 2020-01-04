	Subroutine BZ_Coords_EL1_Bat(Qc,nR,nC,Radius,nElem,iOut)
!	HardCoded Angle for Bathe	
!	Degree Elevate to Quintic
	Implicit Real(kind=8) (a-h,o-z)
!
	real(kind = 8)	Qc       ,QcI       ,QcS      ,QcO
	Dimension		Qc(nR,nC),QcI(nR,nC),QcS(nR,4),QcO(nR,nC)
	real(kind = 8)	Radius,xLen
	real(kind = 8)	xK,pi,Si
	integer			nR,nC
!--------------------------------------------------- x & y: Cubic Starting
	nCs				= 4
	QcI				= 0.D0		!zero all			
!-------------------------------- True 3D
!--------------------------------------------------- 1 Element
	if(nElem == 1) Then
!============================= for 1 Element Config
		QcI(2,2)	= 26.521649 
		QcI(1,3)	= 10.535684
		QcI(2,3)	= 51.9570403
		QcI(1,4)	= 29.2893219
		QcI(2,4)	= 70.7106781
	elseif(nElem == 2) Then
		QcI(2,2)	= 13.1321871D0
		QcI(1,3)	=  2.5865763D0
		QcI(2,3)	= 26.1357843D0
		QcI(1,4)	=  7.6120467D0
		QcI(2,4)	= 38.2683432D0
	endif
!============================= for 1 Element Config End
!============================= for 2 Element Config
!	Qcs(2,2)	= 13.1321871
!	Qcs(1,3)	=  2.5865763
!	Qcs(2,3)	= 26.1357843
!	Qcs(1,4)	=  7.6120467
!	Qcs(2,4)	= 38.2683432
!============================= for 2 Element Config End
!--------------------------------------------------- x & y: Elevate
	Qc			= 0.0D0			! zero all
!------------------------------------ Loop
	nDegElev	= nC - nCs
	nCi			= nCs
	nCo			= nCi + 1	
	do 100 i = 1,nDegElev
!
	call DegreeElevate(QcI,nR,nCi,QcO,nCo,iOut)
!
	QcI			= QcO
	nCi			= nCo
	nCo			= nCi + 1	
  100 continue
!------------------------------------ Set
	do 200 i = 1,nR
	do 200 j = 1,nC
	Qc(i,j)		= QcO(i,j)
  200 continue
!------------------------------------  	
	return
	end
