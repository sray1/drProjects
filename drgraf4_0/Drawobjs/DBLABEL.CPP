// drgradoc.cpp : implementation of the CLabelBase class
//

#include "drgraf.h"
#include "drgradoc.h"

#include "dblabel.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif 
/*
BEGIN_MESSAGE_MAP(CLabelBase, CDrLabel)
	//{{AFX_MSG_MAP(CLabelBase)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/

POSITION CLabelBase::GetFirstLabelPos()
{
	///////////////////////////////////////  Get Doc Info
	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc);  
	CDBoxMgr* pDBoxMgr = pDoc->GetDBoxMgr();
	///////////////////////////////////////////////////////////////////   
	return (pDBoxMgr->GetLabelList() )->GetHeadPosition();
}	

CDrLabel* CLabelBase::GetNextLabel( POSITION& pos)
{
	///////////////////////////////////////  Get Doc Info
	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc);
	CDBoxMgr* pDBoxMgr = pDoc->GetDBoxMgr();
	///////////////////////////////////////////////////////////////////   
	return (CDrLabel*)((pDBoxMgr->GetLabelList() )->GetNext(pos));
}

CDrLabel* CLabelBase::NewLabel()
{
	///////////////////////////////////////  Get Doc Info
	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc);
	CDBoxMgr* pDBoxMgr = pDoc->GetDBoxMgr();
	///////////////////////////////////////////////////////////////////   
	CDrLabel* pLabel = new CDrLabel();
	(pDBoxMgr->GetLabelList() )->AddTail(pLabel);
	pDoc->SetModifiedFlag();                   	// Mark document as modified
											// to confirm File Close
	////////////////////////////// Update All Views
	pDoc->UpdateAllViews(NULL);
	/////////////////////										
	return pLabel;
}
												
int CLabelBase::AddLabel(CDrLabel* pAddLabel)
{
	///////////////////////////////////////  Get Doc Info
	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc);
	///////////////////////////////////////////////////////////////////   
	CDrLabel* pLabel; 

	if((pLabel = NewLabel()) == NULL)
		return -1;
	else 
	{     
	
		pLabel->SetInfo(pAddLabel); 
/*		
		///////////////////////////////////////////
//???		pDoc->SetWinMinMaxWIC(pLabel->GetCorner());
		pDoc->SetWinMinMaxWIC(pLabel->GetOtherCorner());      

		pDoc->SetWinExtWIC();
		///////////////////////////////////////////
*/		
		return 0;
	}	
}		

int	CLabelBase::EditLabel(int index,CDrLabel* pEditLabel)
{                                                   
	if(DeleteLabel(index)<0)
		return -1;
	if(AddLabel(pEditLabel)<0)
		return -1;
	return 0;		
}	

int	CLabelBase::DeleteLabel(int index)
{
	///////////////////////////////////////  Get Doc Info
	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc);
	CDBoxMgr* pDBoxMgr = pDoc->GetDBoxMgr();
	///////////////////////////////////////////////////////////////////   
	int nMaxIndex = (pDBoxMgr->GetLabelList() )->GetCount() - 1;
	if ((index>nMaxIndex) || (index<0) )
		return -1;

	POSITION pos2;
	CDrLabel* pTemp;
	POSITION pos = GetFirstLabelPos();
	for (int i=0;((pos2=pos) !=NULL) && (i < index);i++)
	{
		CDrLabel* pLabel = GetNextLabel( pos);
		
	}
	pTemp = (CDrLabel*)((pDBoxMgr->GetLabelList() )->GetAt(pos2));
	/////////////////		
	(pDBoxMgr->GetLabelList() )->RemoveAt(pos2);
	delete pTemp;	
//AfxMessageBox("Just went Past delete Temp!!!");
	return 0;

}		
	 
CDrLabel* CLabelBase::GetLabel(int index)
{
	///////////////////////////////////////  Get Doc Info
	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc);
	CDBoxMgr* pDBoxMgr = pDoc->GetDBoxMgr();
	///////////////////////////////////////////////////////////////////   
	int nMaxIndex = (pDBoxMgr->GetLabelList() )->GetCount() - 1;
	if ((index>nMaxIndex) || (index<0) )
		return (CDrLabel*)NULL;

	POSITION pos = GetFirstLabelPos();
	CDrLabel* pLabel;
	for (int i=0;(pos !=NULL) && (i <= index);i++)
	{
		pLabel = GetNextLabel( pos);
		
	}
	return pLabel;
}
				
int	CLabelBase::GetLabelIndex(CString KeyID,UINT KeyNo)
{

	///////////////////////////////////////  Get Doc Info
	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc);
	CDBoxMgr* pDBoxMgr = pDoc->GetDBoxMgr();
	///////////////////////////////////////////////////////////////////   
	if((pDBoxMgr->GetLabelList() )->IsEmpty() || KeyNo<=0) 
	{

		if((pDBoxMgr->GetLabelList() )->IsEmpty())
		return -1;
	}				
 		
 	POSITION pos = GetFirstLabelPos();
	int i;
	for (i=0;pos !=NULL ;i++)
	{
		CDrLabel* pLabel = GetNextLabel( pos);
		
		switch(KeyNo)
		{ 
			case 1:         // LabelID

				if((pLabel->GetText()) ==KeyID)
					return i;
				break; 
			
		    case 2:	
		    	
				
		  	default:
		  		return -1;					
		}		  
	}
	return -1;
}
//////////////////////////// End of Module /////////////////////		
