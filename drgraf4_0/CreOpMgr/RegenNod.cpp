// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
#include "drgrafrm.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
///////////////////// IGens
#include "Def_IGen.h"
///////////////////// Elems
#include "Def_Elem.h"
/////////////////////
#include "MI_GangN.h" 
#include "MI_LSupp.h" 
#include "MI_StaL.h" 
//////////////////////
#include "RegenNod.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CRegenNod,CMouse,1)
/////////////////////////////////////////////////////////////////////////////
CRegenNod::CRegenNod()
{
}

CRegenNod::~CRegenNod()
{
}
	
int CRegenNod::UpdateNode(CDrNode* pNode)
{
	///////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////////////////////////////////////// Update Dependent Nodes
	CMI_StaL	MI_StaL;
	CMI_LSupp	MI_LSupp;
	//////////////////////			
	pObjectMgr->ShowObject_On_Off(pNode,NODE,FALSE);
	///////////////////////////////// Support, if any
	if(!(pNode->GetSuppList()->IsEmpty()))
		MI_LSupp.RegenNodeBased(pNode);
	///////////////////////////////// Static Load, if any
	if(!(pNode->GetStaLList()->IsEmpty()))
		MI_StaL.RegenNodeBased(pNode);
	///////////////////////////////// Spectral Load, if any
	pObjectMgr->ShowObject_On_Off(pNode,NODE,TRUE);
	//////////
	return 0;
}


void CRegenNod::Serialize(CArchive& ar)
{

	CMouse::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" RegenNod:    Storing\n");	
		

	}
	else
	{
		TRACE(" RegenNod:    Loading\n");	

	
	}        
}

///////////////////////////////////// end of Module //////////////////////		


