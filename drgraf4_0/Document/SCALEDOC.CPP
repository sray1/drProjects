// drgradoc.cpp : implementation of the CDrGrafDoc class
//

#include "drgraf.h"
#include "drgradoc.h"

#include "scaleDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

////////////////////////////////
void CDrGrafDoc::OnDrawScalefactor()
{
	// TODO: Add your command handler code here
	CDrGrafDoc* pDoc 			= (CDrGrafDoc*)(theApp.m_pDoc );
	CScaleFactor* pScaleFactor  = pDoc->GetScaleFactor();
	CMapFactor* pMapFactor      = pDoc->GetMapFactor();  the Status Bar, which describes the action to be executed by the selected menu item or depressed toolbar button, and keyboard latch state. A check mark appears next to the menu item when the Status Bar is displayed.}{
\f4 
\par }{\f4 
\par }{\f4 See }{\f4\uldb Status Bar}{\v\f4 AFX_HIDW_STATUS_BAR}{\f4  for help on using the status bar.}{\f4 
\par }{\f4 \page }{\f4 #{\footnote \pard\plain \sl240 \f3\fs20\lang1033 # AFX_HIDW_STATUS_BAR}}{\fs16\up6 K{\footnote \pard\plain \s245 \f3\fs20\lang1033 {\fs16\u	pScaleFactor->SetScaleFactor(dlg.m_dScaleFactor); 
		//////////////////////////////////// Update MapFactor
		pMapFactor->SetMapFactor();
		UpdateAllViews(NULL);
		/////////////////////
/*		
		CString			m_szDrawScaleFactor;
		char			buf[50];

		sprintf(buf,"Scale Factor 1: %u ",m_nScaleFactor);
		m_szDrawScaleFactor = buf;  
		AfxMessageBox(m_szDrawScaleFactor);
*/	
	}		
	
	
}

