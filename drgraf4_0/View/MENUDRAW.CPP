// menudraw.cpp : implementation file
//

#include "stdafx.h"

#include "drgraf.h"
#include "drgradoc.h"

#include "axisDlg.h"
#include "unitdlg.h"
#include "eyepzDlg.h" 

#include "xform.h"
#include "mainview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMenuDraw message handlers


void CMainView::OnDrawAxis()
{
	// TODO: Add your command handler code here
	///////////////////////// D O  N O T  N E E D  F O R  N O W
	return;
	///////////////////////////////////////////////////////////	
	/////////////////////////////////////////////////  
	CDrGrafDoc* pDoc 		= (CDrGrafDoc*)(theApp.m_pDoc ); 
	CGrafObject* pObjectMgr = pDoc->GetObjectMgr();
	CAxis* pAxis    		= pObjectMgr->GetAxis();
	/////////////////////////////////////////////////  
static char* Vertical[] = {"X-Axis","Y-Axis","Z-Axis",""};
static UINT nVertCount  = sizeof(Vertical)/sizeof(Vertical[0]);
static char* Positive[] = {"Upward","Downward",""};
static UINT nPosiCount  = sizeof(Positive)/sizeof(Positive[0]);
/////////////////////////////////////////////////////
	CDrawAxis	dlg;
	
	pAxis->SetVerticalOld(pAxis->GetVertical());
	pAxis->SetPositiveOld(pAxis->GetPositive()); 
	
	dlg.m_szDrawVertical = Vertical[pAxis->GetVertical()-1];
	dlg.m_szDrawPositive = Positive[pAxis->GetPositive()-1];
	
	if(dlg.DoModal() == IDOK)
	{

		for(UINT i=0;i<nVertCount;i++)		
			if(dlg.m_szDrawVertical == Vertical[i])    // Vertical
				break;
        ///////////////////////////// Reset m_nAxes/m_nVertical
        pAxis->SetVertical(i+1);     //save
        /////////////////
//////////////////////////////////////////////////////////////////////////
//	 	BEGIN: THIS WILL BE DONE LATER
//////////////////////////////////////////////////////////////////////////
/*
		m_nAxes[1]  = m_nVertical;
		m_nAxes[0]  = m_nVertical - 1;
		if(!m_nAxes[0])
			m_nAxes[0] = 3;
		m_nAxes[2]  = (m_nVertical + 1)%3;
		if(!m_nAxes[2])
			m_nAxes[2] = 3; 
		////////////////////////////////// SPECIAL: Z-UP to keep
		//											RightHandedScrew
		if(m_nVertical == 3)
		{
			UINT temp  = m_nAxes[0];      //	SWITCH X & Z Axes 
			m_nAxes[0] = m_nAxes[2];
			m_nAxes[2] = temp;
		} 
*/		
////////////////////////////////////////////////////////////////////////
//		END: THIS WILL BE DONE LATER												
////////////////////////////////////////////////////////////////////////	
		for(i=0;i<nPosiCount;i++)		
			if(dlg.m_szDrawPositive == Positive[i])    // Positive
				break;
		pAxis->SetPositive(i+1);     //save
	}
/*
	CString str;
	char buf[80];
	
	sprintf(buf,"VerticalOld = %u",m_nVerticalOld);
	str = buf;
	AfxMessageBox(str);
	
	sprintf(buf,"Vertical    = %u",m_nVertical   );
	str = buf;
	AfxMessageBox(str);
	
	sprintf(buf,"PositiveOld = %u",m_nPositiveOld);
	str = buf;
	AfxMessageBox(str);
	
	sprintf(buf,"Positive    = %u",m_nPositive   );
	str = buf;
	AfxMessageBox(str);
	
*/	
			
}

void CMainView::OnUpdateDrawAxis(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

void CMainView::OnDrawUnits()
{
	// TODO: Add your command handler code here
	/////////////////////////////////////////////////  
	CDrGrafDoc* pDoc 	   = (CDrGrafDoc*)(theApp.m_pDoc ); 
	CUnit* pUnit     	   = pDoc->GetUnit();
	CMapFactor* pMapFactor = pDoc->GetMapFactor(); 
	/////////////////////////////////////////////////  
	CDrawUnit	dlg;
	UINT nUnitCount = pUnit->GetUnitNameCount();
	
	UINT nUnitIndex = pUnit->GetUnitIndex();
	pUnit->SetUnitIndexOld(nUnitIndex);
	//set dialog combo index
	dlg.m_szDrawUnit = pUnit->GetUnitName(nUnitIndex);
	
	if(dlg.DoModal() == IDOK)
	{
		// retrieve data 
		for(UINT i=0; i<nUnitCount; i++)
			if(dlg.m_szDrawUnit == pUnit->GetUnitName(i))
			{
				pUnit->SetUnitIndex(i);
				break;
			}
		///////////////// Reset MapMode
		pMapFactor->SetMapModeIndex();	          
		///////////////// Update MapFactor	
		pMapFactor->SetMapFactor();
		///////////////					
	}	
}

void CMainView::OnUpdateDrawUnits(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

void CMainView::OnDrawEyeposition()
{
	// TODO: Add your command handler code here
/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////  
	CDrGrafDoc* pDoc 		= (CDrGrafDoc*)(theApp.m_pDoc ); 
	CGrafObject* pObjectMgr = pDoc->GetObjectMgr();
	CXForm* pXForm	 		= pObjectMgr->GetXForm();
	/////////////////////////////////////////////////  
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
	CDrawEyePosition dlg;
	double Tran[2][3];
	pXForm->GetTranArray(Tran);  // Get current
	pXForm->SetTranOldArray(Tran);  // save in Old

	dlg.m_nTilt      = pXForm->GetTilt();
	dlg.m_nRotation  = pXForm->GetRotation();
	dlg.m_nIncrement = pXForm->GetIncrement(); 
	
//    AfxMessageBox("About to Open EyePos Dialog");
	if(dlg.DoModal() == IDOK)
	{
		pXForm->SetTilt(dlg.m_nTilt);       		// retrieve data
		pXForm->SetRotation(dlg.m_nRotation);
		pXForm->SetIncrement(dlg.m_nIncrement); 
		// Update Transformation
		pXForm->SetTranArray(Tran);
		pXForm->UpdateTranArray(Tran);
/*		
		CString			m_szDrawEyePosition;
		char			buf[50];

		sprintf(buf,"Tilt = %u ",m_nTilt);
		m_szDrawEyePosition = buf;  
		AfxMessageBox(m_szDrawEyePosition);
*/	

	}
	//////////////////////
	FreeLibrary(hLibrary);
	//////////////////////
	pDoc->UpdateAllViews(NULL);
	/////////////////////
	
}

void CMainView::OnUpdateDrawEyeposition(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}
/*
void CMainView::OnDrawLayer()
{
	// TODO: Add your command handler code here
	
}

void CMainView::OnUpdateDrawLayer(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

void CMainView::OnDrawPaper()
{
	// TODO: Add your command handler code here
	
}

void CMainView::OnUpdateDrawPaper(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

void CMainView::OnDrawPrecision()
{
	// TODO: Add your command handler code here
	
}

void CMainView::OnUpdateDrawPrecision(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

void CMainView::OnDrawScalefactor()
{
	// TODO: Add your command handler code here
	
}

void CMainView::OnUpdateDrawScalefactor(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}
*/
//////////////////////////////////////// end of module ////////////////////
