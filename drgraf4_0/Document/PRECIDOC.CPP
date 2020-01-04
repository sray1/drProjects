// drgradoc.cpp : implementation of the CDrGrafDoc class
//

#include "drgraf.h"
#include "drgradoc.h"

#include "preciDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////////////////////////
void CDrGrafDoc::OnDrawPrecision()
{
	// TODO: Add your command handler code here
	/////////////////////////////////////////////////  
	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc ); 
	CPrecision* pPrecision     = pDoc->GetPrecision();
	/////////////////////////////////////////////////  
	CDrawPrecision	dlg; 
	
	pPrecision->SetPrecisionOld(pPrecision->GetPrecision()); 	
	dlg.m_nDrawPrecision = pPrecision->GetPrecision();
	
	if(dlg.DoModal() == IDOK)
	{
		// retrieve data
		pPrecision->SetPrecision(dlg.m_nDrawPrecision);                  
		pPrecision->SetWorldBaseOld(pPrecision->GetWorldBase());
		pPrecision->SetWorldBase( (LONG)(pow(10.,(double)dlg.m_nDrawPrecision) ) );
/*		
		// Update Total Scale Factor and MapFactor
		m_dScaleFactor = m_dScaleFactor / (double)m_lWorldBaseOld; 
		m_dScaleFactor = m_dScaleFactor * (double)m_lWorldBase;
		SetMapFactor();
*/		
		/////////////// 
/*		
		CString			m_szDrawPrecision;
		char			buf[50]; 
		sprintf(buf,"No. of Decimal Places = %u",m_nPrecision); 
		m_szDrawPrecision = buf;
		AfxMessageBox(m_szDrawPrecision);
*/
	}		
	
	
}

