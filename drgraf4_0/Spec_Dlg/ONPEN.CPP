// drgradoc.cpp : implementation of the CDrGrafDoc class
//

#include "stdafx.h"

#include "drgraf.h"
#include "drgradoc.h"

#include "penDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrGrafDoc commands


void CDrGrafDoc::OnOptionsPenchange()
{
	// TODO: Add your command handler code here
				  		
/////////////////////////////////////////////////////////////////////////////
// Run the test

	HINSTANCE hLibrary;
	if ((hLibrary = LoadLibrary("MUSCROLL.DLL")) < HINSTANCE_ERROR)
	{
		AfxMessageBox("Can not do this test without custom control library");

		// prevent it from happening again
//		GetMenu()->EnableMenuItem(IDM_TEST_SPIN_EDIT, MF_DISABLED|MF_GRAYED);
		return;
	}

	TRACE("running dialog with spin controls in it\n");

	/////////////////////////////////////////////////  
	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc ); 
	CDrPen* pDrPen     = pDoc->GetDrPen();
	/////////////////////////////////////////////////  
	CPenDlg	dlg;
	UINT nStyleCount = pDrPen->GetStyleNameCount();
	
	pDrPen->SetStyleOld(pDrPen->GetStyle() );       // save old
	//set dialog combo index
	dlg.m_StyleName = pDrPen->GetStyleName(pDrPen->GetIndex());
	
	if(dlg.DoModal() == IDOK)
	{
		// retrieve data 
		for(UINT i=0; i<nStyleCount; i++)
		{
			if(dlg.m_StyleName == pDrPen->GetStyleName(i))
			{
				pDrPen->SetIndex(i);
				break;
			}
		}
   		UINT index = pDrPen->GetIndex(); 
		UINT nStyle= pDrPen->GetStyleConstant(index);
		////////////////////////	
		pDrPen->SetStyle(nStyle);
		pDrPen->SetColor(dlg.m_PenColor);
		pDrPen->SetWidth(dlg.m_nWidth);
		if(nStyle != PS_SOLID)
			pDrPen->SetWidth(1);    // all other Penstyles valid for width = 1			
		///////////////// Reset Pen
		pDrPen->ReplacePen();	          
		///////////////					
	}		
	//////////////////////
	FreeLibrary(hLibrary);
	//////////////////////
	
}

