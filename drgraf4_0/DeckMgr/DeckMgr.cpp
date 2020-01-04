// MouseMgr.cpp : implementation file
//
#include "stdafx.h"

#include "DeckDll.h"

//#include "drgrafrm.h"
////////////////////
#include "Def_IGen.h"
#include "Def_Elem.h"
#include "Def_Supp.h"
#include "Def_StaL.h"
#include "Def_SpeL.h"
#include "Def_DynL.h"
////////////////////
#include "DeckWalk.h"
#include "DeckRsrc.h"
////////////////////
#include "DeckMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionPMgr_DLL;
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CDeckMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CDeckMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CDeckMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CDeckMgr::CDeckMgr()
{
	m_bFormatted = FALSE;
}

CDeckMgr::~CDeckMgr()
{
}

void CDeckMgr::UpdateDeckList()
{
	///////////////////////////////////////////////// delete Old Stuff
	while(!GetDeckList()->IsEmpty())
		GetDeckList()->RemoveHead(); 	// 
	////////////////////////////////////////////////
	CDeckWalk DeckWalk(GetDeckList(),IsFormatted());
	//////////////////////////////////////////////// Create Deck
	DeckWalk.DW_MESH();
	///////////////////
/*
UINT CDeckMgr::Options(CView* pView,UINT ItemID,UINT SubItemID)
{
	switch(ItemID)
	{
		case A
		//////////////////////////////////////// IGEN
		case MNODE:
		case FE0D:
			Deck_0D(ItemID,SubItemID);
			break;

		case FE1D:
			Deck_1D(ItemID,SubItemID);
			break;

		case FE2D:
			Deck_2D(ItemID,SubItemID);
			break;

		case FE3D:
			Deck_3D(ItemID,SubItemID);
			break;
		//////////////////////////////////////// Support
		case SUPPORT:
		case SUPPORT_RIGID:
		case SUPPORT_LINSPRING:
		case SUPPORT_LINSNUBBER:
		case SUPPORT_NLSPRING:
		case SUPPORT_NLSNUBBER:
			Deck_SUPPORT(ItemID,SubItemID);
			break;
		//////////////////////////////////////// StaticLoad
		case STATICLOAD:
		case FORCE:
		case DISPLACE:
		case PRESSURE:
		case THERMAL:
		case LUMPWT:
			Deck_STATIC(ItemID,SubItemID);
			break;


		default:

			return (UINT)NONE;

	}
*/ 
}
// CDeckMgr serialization

void CDeckMgr::Serialize(CArchive& ar)
{

	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" DeckMgr	:Storing\n");	// TODO: add storing code here 
//		ar.Write(/*LPOINT3*/&m_StatusMouseWIC, sizeof(LPOINT3));

	}
	else
	{
		TRACE(" DeckMgr	:Loading\n");	// TODO: add loading code here
//		ar.Read(/*LPOINT3*/&m_StatusMouseWIC, sizeof(LPOINT3));
	}
	
}
////////////////////// End of Module ////////////////////


