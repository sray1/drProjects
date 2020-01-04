// DrCurves.cpp : implementation of the CCurve_3 class
//

#include "stdafx.h"
#include "UserMsg.h"
#include "drgrafrm.h"
///////////////////
#include "CalcTime.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
IMPLEMENT_DYNAMIC(CCalcTime, CObject)
//////////////////// 
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
CCalcTime::CCalcTime()
{
	m_Duration = -1;
}
 
void CCalcTime::StartClock()
{
#ifdef _DEBUG
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	if(pWnd->IsDebugCTim())
	{
		//////////////////////	
		m_Start		= clock();
		m_Duration	= -1.0;		// reset
		////////////////////////
	}
#endif
}

void CCalcTime::StopClock()
{
#ifdef _DEBUG
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	clock_t		finish;
	/////////////////////////////////////////////////////////
	if(pWnd->IsDebugCTim())
	{
		/////////////////////
		finish = clock();
		m_Duration = (double)(finish - m_Start) / CLOCKS_PER_SEC;
		////////////////////
	}
#endif
}

void CCalcTime::OutDuration(CString& str)
{
#ifdef _DEBUG
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString		strList;
	/////////////////////////////////////////////////////////
	if(pWnd->IsDebugCTim())
	{
		if(m_Duration>=0.0)
		{
			sprintf(strList.GetBuffer(BUFF_SIZE),"%s Takes %8.4f seconds.",str,m_Duration);
			/////////////////////////////
			((CListBox*)(pWnd->GetDlg_CTim()->GetDlgItem(IDC_LIST)))->AddString(strList);
			strList.ReleaseBuffer();
		}
		else
			/////////////////////////////
			((CListBox*)(pWnd->GetDlg_CTim()->GetDlgItem(IDC_LIST)))->AddString(str);
	}
#endif
}

void CCalcTime::OutComment(CString& str)
{
#ifdef _DEBUG
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	if(pWnd->IsDebugCTim())
		((CListBox*)(pWnd->GetDlg_CTim()->GetDlgItem(IDC_LIST)))->AddString(str);
#endif
}

////////////////////////////////// end of module ///////////////////// 

