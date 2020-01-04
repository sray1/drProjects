	Subroutine BZ_Coords_EL1(Qc,nR,nC,Radius,iOut)
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
	piby4			= datan(1.D0)
	nCs				= 4
	Si				= 45.0D0			! degree
	Si				= Si*piby4/45.D0	! Radian
!------------------------------------------------------------------
	Qcs				= 0.D0		!zero all			
!============================= for 1 Element Config
	Qcs(2,2)	= 26.521649 
	Qcs(1,3)	= 10.535684
	Qcs(2,3)	= 51.9570403
	Qcs(1,4)	= 29.2893219
	Qcs(2,4)	= 70.7106781
!============================= for 1 Element Config End
!============================= for 2 Element Config
!	Qcs(2,2)	= 13.1321871
!	Qcs(1,3)	=  2.5865763
!	Qcs(2,3)	= 26.1357843
!	Qcs(1,4)	=  7.6120467
!	Qcs(2,4)	= 38.2683432
!============================= for 2 Element Config End
!--------------------------------------------------- x & y: Elevate
	nCo			= nC
!
	Qc			= 0.0D0			! zero all
!------------------------------------ Loop
	nDegElev	= nC - nCs
	nCi			= nCs
	nCo			= nCi + 1	
	QcI			= 0.0D0			! zero all
	do 10 i = 1,nR
	do 10 j = 1,nCs
	QcI(i,j) = Qcs(i,j)
   10 continue
!
	do 100 i = 1,nDegElev
!
	call DegreeElevate(Qci,nR,nCi,QcO,nCo,iOut)
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
	call DumpRealMatrix(Qcs,nR,4,"Element#1: QcS_Cubic",1,iOut)
	call DumpRealMatrix(Qc,nR,nC,"Element#1: Qc",1,iOut)
!------------------------------------  	
	return
	end
