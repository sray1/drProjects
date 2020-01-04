// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
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
#include "SLENod.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CSLENod,CSLEObj,1)
/////////////////////////////////////////////////////////////////////////////
CSLENod::CSLENod()
{


}

CSLENod::~CSLENod()
{
}

void CSLENod::GetObjectInfo(CSLEObj* pObject)
{
	
	CSLEObj::GetObjectInfo(pObject);
	///////////////////////////////////   
	CSLENod* pAdd = (CSLENod*) pObject;
	////////////////////////////////////////////////////////////////////// Node
	pAdd->m_pCurrentNode			= m_pCurrentNode;
	pAdd->m_pCurrentLabel			= m_pCurrentLabel;
	////////
}

void CSLENod::SetObjectInfo(CSLEObj* pObject)
{
	
	CSLEObj::SetObjectInfo(pObject);
	///////////////////////////////////   
	CSLENod* pAdd = (CSLENod*) pObject;
	////////////////////////////////////////////////////////////////////// Node
	m_pCurrentNode			= pAdd->m_pCurrentNode;
	m_pCurrentLabel			= pAdd->m_pCurrentLabel;
	////////
}

int CSLENod::ShowNodeStaticLoad(CString* pID,int nHowMany)
{
	///////////////////////////////////////////////////////////////////////
//	 nHowmany			// Used as an afterthought for Updating Support anyway
						// in CMI_LSupp.CreateNodeLinSup
						// even if same coords node exists already !!!
						// when nAnyway == -12345
						// Use nHowmany of ShowNode to pass the variable
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
	/////////////////////
	CDrStatic* pCurrentStaL = Static.CreateNodeBased(m_StaLProc,stLCard,m_pCurrentNode,NODE);
	////////////////////////////////////////////////////////////////////// Show
	int nActiveIndex = pObjectMgr->GetActiveObjectIndex();	// Get Active Index									
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
	pObjectMgr->SetActiveObjectType(STATICLOAD);		    // set Active Type									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,STATICLOAD);
	///////////////////////////////
	return 0;
}	 

int CSLENod::ShowInfo_NodeStaticLoad(CDrNode* pDrNode, char* buf, int jStart,
															CDrStatic* pDrStatic)
{
	int j = jStart;
	////////////////////////////////////////////////////////////////////////
	STALCARD	stLCard;
	////////////////////////////////////////////
	if(pDrStatic)
		stLCard = *(pDrStatic->GetStaLCard());					
	else
	{
		AfxMessageBox("Internal ERROR:\nCSLENod::FillInfo_NodeStaticLoad\npDrLinSup=NULL"); 
		return -2;
	}
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
	//////////
	return j;
}

void CSLENod::Serialize(CArchive& ar)
{

	CSLEObj::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" SLENod:    Storing\n");	
		
 			/////////////////////////////////////////////////

	}
	else
	{
		TRACE(" SLENod:    Loading\n");	

			/////////////////////////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////		


