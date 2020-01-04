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
	CMapFactor* pMapFactor      = pDoc->GetMapFactor(); 
	///////////////////////////////////////////////// 
	CDrawScale		dlg;
	                        
	                        
	pScaleFactor->SetScaleFactorOld(pScaleFactor->GetScaleFactor() ); 
	// show only Scale Factor
//	dlg.m_dScaleFactor = m_dScaleFactor/(double)GetWorldBase();
	dlg.m_dScaleFactor = pScaleFactor->GetScaleFactor();
	                        
	if(dlg.DoModal() == IDOK)
	{
		// retrieve data: Save with precision
//		m_dScaleFactor = dlg.m_dScaleFactor * (double)GetWorldBase(); 
		pScaleFactor->SetScaleFactor(dlg.m_dScaleFactor); 
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

