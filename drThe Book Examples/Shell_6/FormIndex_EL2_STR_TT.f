	Subroutine FormIndexEL_2Str_TT(Indx,nStifEL,iOut)
!															
	Implicit Real(kind=8) (a-h,o-z)
!	==============================
!	Coerced Isoparametric Element
!
!	Outputs 
!		Indx(nStifEl)	= Indx of assembly for Element 2
!
	integer Indx(nStifEL)
!
!	Indices of location in global stiffness
!
		Indx( 1) = 11			! u
		Indx( 2) = 12
		Indx( 3) = 73
		Indx( 4) = 74
		Indx( 5) = 75
		Indx( 6) = 76	
		Indx( 7) = 77
		Indx( 8) = 78
		Indx( 9) = 79
		Indx(10) = 80
		Indx(11) = 81	
		Indx(12) = 82
!
		Indx(13) = 23			! v
		Indx(14) = 24
		Indx(15) = 83
		Indx(16) = 84
		Indx(17) = 85	
		Indx(18) = 86
		Indx(19) = 87
		Indx(20) = 88
		Indx(21) = 89
		Indx(22) = 90
		Indx(23) = 91	!
		Indx(24) = 92
!
		Indx(25) = 35
		Indx(26) = 36
		Indx(27) = 93
		Indx(28) = 94
		Indx(29) = 95
		Indx(30) = 96
		Indx(31) = 97
		Indx(32) = 98
		Indx(33) = 99
		Indx(34) = 100
		Indx(35) = 101
		Indx(36) = 102
!
		Indx(37) = 47
		Indx(38) = 48
		Indx(39) = 103
		Indx(40) = 104
		Indx(41) = 105
		Indx(42) = 106
		Indx(43) = 107
		Indx(44) = 108
		Indx(45) = 109
		Indx(46) = 110
		Indx(47) = 111
		Indx(48) = 112
!
		Indx(49) = 59
		Indx(50) = 60
		Indx(51) = 113
		Indx(52) = 114
		Indx(53) = 115
		Indx(54) = 116
		Indx(55) = 117
		Indx(56) = 118
		Indx(57) = 119
		Indx(58) = 120
		Indx(59) = 121
		Indx(60) = 122
!
		Indx(61) = 71
		Indx(62) = 72
		Indx(63) = 123
		Indx(64) = 124
		Indx(65) = 125
		Indx(66) = 126
		Indx(67) = 127
		Indx(68) = 128
		Indx(69) = 129
		Indx(70) = 130
		Indx(71) = 131
		Indx(72) = 132
!
	write(iOut,1000)
	write(iOut,1010) nStifEL,(Indx(i),i = 1,nStifEL)
!   		 
	return
 1000 Format(/2x,"Just before Leaving: FormIndexEL_2"/)
 1010 Format(/2x,"Indices for Element#2 for Global Assembly: 1x"I3/
     &										3(5(2x,I7)/) )
	end   		