// drgradoc.cpp : implementation of the CFreeHandBase class
//

#include "drgraf.h"
#include "drgradoc.h"

#include "dbFreHnd.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif 
/*
BEGIN_MESSAGE_MAP(CFreeHandBase, CDrFreeHand)
	//{{AFX_MSG_MAP(CFreeHandBase)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/

POSITION CFreeHandBase::GetFirstFreeHandPos()
{
	///////////////////////////////////////  Get Doc Info
	CDrGrafDoc* pDoc 		= (CDrGrafDoc*)(theApp.m_pDoc);
	CGrafObject* pObjectMgr = pDoc->GetObjectMgr();
	CDBoxMgr* pDBoxMgr    	= pObjectMgr->GetDBoxMgr();
	///////////////////////////////////////////////////////////////////   
	return (pDBoxMgr->GetFreeHandList() )->GetHeadPosition();
}	

CDrFreeHand* CFreeHandBase::GetNextFreeHand( POSITION& pos)
{
	///////////////////////////////////////  Get Doc Info
	CDrGrafDoc* pDoc 		= (CDrGrafDoc*)(theApp.m_pDoc);
	CGrafObject* pObjectMgr = pDoc->GetObjectMgr();
	CDBoxMgr* pDBoxMgr    	= pObjectMgr->GetDBoxMgr();
	///////////////////////////////////////////////////////////////////   
	return (CDrFreeHand*)((pDBoxMgr->GetFreeHandList() )->GetNext(pos));
}

CDrFreeHand* CFreeHandBase::NewFreeHand()
{
	///////////////////////////////////////  Get Doc Info
	CDrGrafDoc* pDoc 		= (CDrGrafDoc*)(theApp.m_pDoc);
	CGrafObject* pObjectMgr = pDoc->GetObjectMgr();
	CDBoxMgr* pDBoxMgr    	= pObjectMgr->GetDBoxMgr();
	///////////////////////////////////////////////////////////////////   
	CDrFreeHand* pFreeHand = new CDrFreeHand();
	(pDBoxMgr->GetFreeHandList() )->AddTail(pFreeHand);
	pDoc->SetModifiedFlag();                   	// Mark document as modified
											// to confirm File Close
	////////////////////////////// Update All Views
	pDoc->UpdateAllViews(NULL);
	/////////////////////										
	return pFreeHand;
}
												
int CFreeHandBase::AddFreeHand(CDrFreeHand* pAddFreeHand)
{
	///////////////////////////////////////  Get Doc Info
	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc);
	CDataWindow* pDataWin = pDoc->GetDataWindow(); 
	///////////////////////////////////////////////////////////////////   
	CDrFreeHand* pFreeHand; 

	if((pFreeHand = NewFreeHand()) == NULL)
		return -1;
	else 
	{     
	
		pFreeHand->SetInfo(pAddFreeHand);
		///////////////////////////////////////////
		pDataWin->SetWinMinMaxWIC(pFreeHand->GetCorner());
		pDataWin->SetWinMinMaxWIC(pFreeHand->GetOtherCorner());      

		pDataWin->SetWinExtWIC();
		///////////////////////////////////////////
		return 0;
	}	
}		

int	CFreeHandBase::EditFreeHand(int index,CDrFreeHand* pEditFreeHand)
{                                                   
	if(DeleteFreeHand(index)<0)
		return -1;
	if(AddFreeHand(pEditFreeHand)<0)
		return -1;
	return 0;		
}	

int	CFreeHandBase::DeleteFreeHand(int index)
{
	///////////////////////////////////////  Get Doc Info
	CDrGrafDoc* pDoc 		= (CDrGrafDoc*)(theApp.m_pDoc);
	CGrafObject* pObjectMgr = pDoc->GetObjectMgr();
	CDBoxMgr* pDBoxMgr    	= pObjectMgr->GetDBoxMgr();
	///////////////////////////////////////////////////////////////////   
	int nMaxIndex = (pDBoxMgr->GetFreeHandList() )->GetCount() - 1;
	if ((index>nMaxIndex) || (index<0) )
		return -1;

	POSITION pos2;
	CDrFreeHand* pTemp;
	POSITION pos = GetFirstFreeHandPos();
	for (int i=0;((pos2=pos) !=NULL) && (i < index);i++)
	{
		CDrFreeHand* pFreeHand = GetNextFreeHand( pos);
		
	}
	pTemp = (CDrFreeHand*)((pDBoxMgr->GetFreeHandList() )->GetAt(pos2));
	/////////////////		
	(pDBoxMgr->GetFreeHandList() )->RemoveAt(pos2);
	delete pTemp;	
//AfxMessageBox("Just went Past delete Temp!!!");
	return 0;

}		
	 
CDrFreeHand* CFreeHandBase::GetFreeHand(int index)
{
	///////////////////////////////////////  Get Doc Info
	CDrGrafDoc* pDoc 		= (CDrGrafDoc*)(theApp.m_pDoc);
	CGrafObject* pObjectMgr = pDoc->GetObjectMgr();
	CDBoxMgr* pDBoxMgr    	= pObjectMgr->GetDBoxMgr();
	///////////////////////////////////////////////////////////////////   
	int nMaxIndex = (pDBoxMgr->GetFreeHandList() )->GetCount() - 1;
	if ((index>nMaxIndex) || (index<0) )
		return (CDrFreeHand*)NULL;

	POSITION pos = GetFirstFreeHandPos();
	CDrFreeHand* pFreeHand;
	for (int i=0;(pos !=NULL) && (i <= index);i++)
	{
		pFreeHand = GetNextFreeHand( pos);
		
	}
	return pFreeHand;
}
				
int	CFreeHandBase::GetFreeHandIndex(UINT KeyNo)
{

	///////////////////////////////////////  Get Doc Info
	CDrGrafDoc* pDoc 		= (CDrGrafDoc*)(theApp.m_pDoc);
	CGrafObject* pObjectMgr = pDoc->GetObjectMgr();
	CDBoxMgr* pDBoxMgr    	= pObjectMgr->GetDBoxMgr();
	///////////////////////////////////////////////////////////////////   
	if((pDBoxMgr->GetFreeHandList() )->IsEmpty() || KeyNo<=0) 
	{

		if((pDBoxMgr->GetFreeHandList() )->IsEmpty())
		return -1;
	}				
 		
 	POSITION pos = GetFirstFreeHandPos();
	int i;
	for (i=0;pos !=NULL ;i++)
	{
		CDrFreeHand* pFreeHand = GetNextFreeHand( pos);
		

		if((pFreeHand->GetKeyNo()) ==KeyNo)
			return i;
				  
	}
	return -1;
}
//////////////////////////// End of Module /////////////////////
/*		
/////////////////////////////////////////////////////////////////////////////
CStroke::CStroke(UINT nPenWidth)
{
	m_nPenWidth = nPenWidth;
	m_rectBounding.SetRectEmpty();
}

/////////////////////////////////////////////////////////////////////////////
void CStroke::AddPoint(CPoint pt)
{
	m_pointArray.Add(MAKELONG(pt.x, pt.y));
}

/////////////////////////////////////////////////////////////////////////////
*/