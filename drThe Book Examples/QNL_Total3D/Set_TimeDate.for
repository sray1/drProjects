	Subroutine Set_TimeDate(iOut)
	USE DFPORT	! for CTime
	Implicit Real(kind=8) (a-h,o-z)
!
	CHARACTER(9) TODAY
	character (24) systime
!-------------------------------------------- 
	systime = CTIME (TIME( ))
	write(iOut,*) 'Run date and time is ',systime
!	write(IoutDef,*) 'Run date and time is ',systime

	!If today's date is October 6, 1995, the following
	!code prints "06-Oct-95"
!	CALL DATE(TODAY)
!	write(iOut,*) "                               Run Date = ",TODAY
	!The next line prints "10/06/95"
!	write(iOut,*) DATE( )
!	-------------
	return
	end
