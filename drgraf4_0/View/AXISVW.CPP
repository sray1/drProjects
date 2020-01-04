// AxisVW.cpp : implementation of the Draw_Axis Menu Handler
//

#include "stdafx.h" 
//#include <math.h>
#include "mainview.h"
#include "axisDlg.h"
#include "drgraf.h"
#include "drgradoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

////////////////////////////////
void CDrawMenu::OnDrawAxis()
{
	// TODO: Add your command handler code here
	///////////////////////// D O  N O T  N E E D  F O R  N O W
	return;
	///////////////////////////////////////////////////////////	
	/////////////////////////////////////////////////  
	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc ); 
	CAxis* pAxis     = pDoc->GetAxis();
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

	



