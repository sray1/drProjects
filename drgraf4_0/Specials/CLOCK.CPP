// Clock.cpp : implementation of the CClock class
//

//#include "stdafx.h"

#include "Clock.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
///////////////////////////////////////
#define YEAR  (datetime->tm_year % 100)
#define MONTH (datetime->tm_mon  + 1)
#define MDAY  (datetime->tm_mday)
#define WDAY  (datetime->tm_wday)
#define HOUR  (datetime->tm_hour)
#define MIN   (datetime->tm_min)
#define SEC   (datetime->tm_sec) 

CString	sDate,sTime,sAMPM[2];
//char	sDate[2],sTime[2],sAMPM[2][5];
int		iDate,iTime; 
/////////////////////////////////////////////////////////////////////////////
// CClock
IMPLEMENT_DYNAMIC(CClock,CObject)
/////////////////////////////////
CClock::CClock()
{
}
CClock::~CClock()
{
}
void CClock::SetInternational (void)
{
     static char cName [] = "intl" ;

    iDate	 = (int)(AfxGetApp()->GetProfileInt   ("intl", "iDate", 0));
    iTime	 = (int)(AfxGetApp()->GetProfileInt   ("intl", "iTime", 0));
    
	sDate    = AfxGetApp()->GetProfileString("intl", "sDate", "/");
	sTime    = AfxGetApp()->GetProfileString("intl", "sTime", ":");
	sAMPM[0] = AfxGetApp()->GetProfileString("intl", "s1159", "AM");
	sAMPM[1] = AfxGetApp()->GetProfileString("intl", "s2359", "PM"); 
/*	
     iDate = AfxGetApp()->GetProfileInt (cName, "iDate", 0) ;
     iTime = AfxGetApp()->GetProfileInt (cName, "iTime", 0) ;
     AfxGetApp()->GetProfileString (cName, "sDate",  "/", sDate,     2) ;
     AfxGetApp()->GetProfileString (cName, "sTime",  ":", sTime,     2) ;
     AfxGetApp()->GetProfileString (cName, "s1159", "AM", sAMPM [0], 5) ;
     AfxGetApp()->GetProfileString (cName, "s2359", "PM", sAMPM [1], 5) ; 
*/     
}


void CClock::GetTimeDate(CString* pstrDate,CString* pstrTime)
{   

   // Detail Time Format in : strftime function 

	time_t	lTime;
	time(&lTime);
	CTime t( lTime ); //  
	////////////////////
    struct tm* datetime ;
	datetime = t.GetLocalTm(NULL); 
	//////////////////////////////
//    static char szWday[] = "Sun\0Mon\0Tue\0Wed\0Thu\0Fri\0Sat" ;
    static char* szWday[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"} ;
    char        cBuffer[40];
//    short       nLength ;
    /////////////////////////////////////////////////////// 
/*    
     nLength = wsprintf (cBufferDate, "  %s  %d%s%02d%s%02d  \r\n",
               (LPSTR) szWday + 4 * WDAY,
               iDate == 1 ? MDAY  : iDate == 2 ? YEAR  : MONTH, (LPSTR) sDate,
               iDate == 1 ? MONTH : iDate == 2 ? MONTH : MDAY,  (LPSTR) sDate,
               iDate == 1 ? YEAR  : iDate == 2 ? MDAY  : YEAR) ;

     if (iTime == 1)
          nLength = wsprintf (cBufferTime, "  %02d%s%02d%s%02d  ",
                               HOUR, (LPSTR) sTime, MIN, (LPSTR) sTime, SEC) ;
     else
          nLength = wsprintf (cBufferTime, "  %d%s%02d%s%02d %s  ",
                               (HOUR % 12) ? (HOUR % 12) : 12,
                               (LPSTR) sTime, MIN, (LPSTR) sTime, SEC,
                               (LPSTR) sAMPM [HOUR / 12]) ; 
*/
                               
	/////////////
	CString str;
	///////////// 
	if(HOUR>12)
	    sprintf(cBuffer,"%02d:%02d:%02d %2s",(HOUR%12),MIN,SEC,"PM"); 
	else		                                  
	    sprintf(cBuffer,"%02d:%02d:%02d %2s",(HOUR%12),MIN,SEC,"AM");                               
	///////////////////////////////////////
	*pstrTime = cBuffer;
	//////////////////////////////////////////
	sprintf(cBuffer,"%s %02d/%02d/%02d",szWday[WDAY],MONTH,MDAY,YEAR);                               
	///////////////////////////////////////
	*pstrDate = cBuffer;
	//////////////////////////////////////////

}

////////////////////////////////// end of module //////////////////
