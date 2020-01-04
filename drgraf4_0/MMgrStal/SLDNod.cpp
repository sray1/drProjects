// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
#include "Def_MouseAct.h" // Mouse Action                   
///////////////////// elements
#include "Def_IGen.h"
///////////////////// Static Loads
#include "Str_StaL.h"
#include "Def_StaL.h"
#include "DrStatic.h" 
#include "MI_StaL.h" 
//////////////////////
#include "MSTLMgr.h" 
//////////////////////
#include "SLDNod.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CSLDNod,CSLDObj,1)
/////////////////////////////////////////////////////////////////////////////
CSLDNod::CSLDNod()
{


}

CSLDNod::~CSLDNod()
{
}

void CSLDNod::GetObjectInfo(CSLDObj* pObject)
{
	
	CSLDObj::GetObjectInfo(pObject);
	///////////////////////////////////   
	CSLDNod* pAdd = (CSLDNod*) pObject;
	////////////////////////////////////////////////////////////////////// Node
	pAdd->m_pCurrentNode			= m_pCurrentNode;
	pAdd->m_pCurrentLabel			= m_pCurrentLabel;
	////////
}

void CSLDNod::SetObjectInfo(CSLDObj* pObject)
{
	
	CSLDObj::SetObjectInfo(pObject);
	///////////////////////////////////   
	CSLDNod* pAdd = (CSLDNod*) pObject;
	////////////////////////////////////////////////////////////////////// Node
	m_pCurrentNode			= pAdd->m_pCurrentNode;
	m_pCurrentLabel			= pAdd->m_pCurrentLabel;
	////////
}

int CSLDNod::ShowNodeStaticLoad(CDrNode* pN,CString* pID)
{
	int nResult = MA_OK;
	////////////////////
	m_nNodPos_S_Beg = 0;		// index of Output NodPos in s direction:Begin
	m_nNodPos_S_End = 1;
								// index of Output NodPos in s direction:End
	m_pCurrentNode	= pN;
	m_pCurrentLabel = (CDrLabel*)(m_pCurrentNode->GetLabelList()->GetHead());;
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	pObjectMgr->SetActiveObjectType(STATICLOAD);                   
	/////////////////////////////////////////////////////////////// Using GangSup
	CMI_StaL Static;
	/////////////////////
	STALCARD stLCard;
	FillStLCard(stLCard,pID);
	//////////////
	CList<STALCARD,STALCARD> TempList;
	TempList.RemoveAll();
	TempList.AddTail(stLCard);
	///
	nResult = Static.CreateNodeBased(m_pCurrentNode,&TempList);
	///
	stLCard = TempList.GetTail(); 
	m_pCurrentNode->GetStaLCardList()->AddTail(stLCard);
	////////////////////////////////////////////////////////////////////// Show
	// Loads are not exposed to general lists, so update container
	// but Load labels are exposed so that it can be manipulated
	pObjectMgr->ShowObject_On_Off(m_pCurrentNode,NODE,TRUE); // 
	//
	CDListMgr* pStaLList = m_pCurrentNode->GetStaLList(); 
	for (POSITION posI = pStaLList->GetFirstObjectPos( );posI !=NULL;)
	{
		CDrStatic* pStatic	= (CDrStatic*)pStaLList->GetNext(posI);
		CDrNode* pNode		= pStatic->GetLabelNode();
		pObjectMgr->ShowObject_On_Off(pNode,NODE,TRUE);
		CDrLabel* pLabel	= pStatic->GetLabelPtr();
		pObjectMgr->ShowObject_On_Off(pLabel,LABEL,TRUE);
	}
	///////////////////////////////
	return 0;
}	 

int CSLDNod::ShowInfo_NodeStaticLoad(CDrNode* pDrNode, char* buf, int jStart,CString& CurrentStLID)
{
	int j = jStart;
	////////////////////////////////////////
	CDListMgr* pList = pDrNode->GetStaLList();
	////////////////////////////////////////////////////////////////////////
	int i;
	CDrStatic*	pDrStatic;
	STALCARD	stLCard;
	POSITION	pos;
	/////////////////////////////////////////////////////////// Go Over List for correct LID
	for(i=0;i<pList->GetCount();i++)
	{
		pos			= pList->FindIndex(i);
		pDrStatic	= (CDrStatic*)pList->GetAt(pos);
		////
		if(pDrStatic)
			stLCard = *(pDrStatic->GetStaLCard());					
		else
		{
			AfxMessageBox("Internal ERROR:\nCSLDNod::FillInfo_NodeStaticLoad\npDrLinSup=NULL"); 
			return -2;
		}
		/////////////////////////////////////////
		if(stLCard.load_id != CurrentStLID)
			continue;
		////////////////////////////////////////////////////// Same LID
		CString		Nid;
		Nid = pDrNode->GetObjectID();
		/////////////////////////////////////////
		switch (stLCard.StaLProc)
		{
			case STL_FORCE:
			case STL_DISPLACE:	// fall thro'
				j	= FillInfo_6(Nid, stLCard, buf, j);
				break;
			case STL_LUMPWT:	// fall thro'
			case STL_THERMAL:
			case STL_PRESSURE:
				j	= FillInfo_3(Nid, stLCard, buf, j);
				break;
			default:
				break;
		}
	}
	//////////
	return j;
}

void CSLDNod::Serialize(CArchive& ar)
{

	CSLDObj::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" SLDMousN:    Storing\n");	
		
 			/////////////////////////////////////////////////

	}
	else
	{
		TRACE(" SLDMousN:    Loading\n");	

			/////////////////////////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////		


