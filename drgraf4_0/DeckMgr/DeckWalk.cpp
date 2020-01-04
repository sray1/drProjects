#include "stdafx.h"

#include "Def_Objs.h"
////////////////////
#include "DrGraf.h"
#include "DrGraDoc.h"
#include "ObjMgr.h"
#include "DListMgr.h"
////////////////////////// StaticLoads
#include "Def_StaL.h"
////////////////////////// SupportLevel
#include "Def_Supp.h"
#include "DrLinSup.h"		// DrLinSup
////////////////////////// ElementLevel
#include "Def_IGen.h"
#include "Def_Elem.h"	// 
#include "DrMesh2D.h"	// 
#include "DrFE0D.h"		// 
#include "DrFE1D.h"		// 
#include "DrFE2D.h"		// 
#include "DrEdge.h"		// 
////////////////////////////////////////
#include "DeckRsrc.h"
#include "DeckWalk.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CDeckWalk

IMPLEMENT_DYNAMIC(CDeckWalk,CObject)
/*
BEGIN_MESSAGE_MAP(CDeckWalk,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CDeckWalk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/

#define	BUFF_SIZE	1024
#define	COL_CARDNO	200
//////////////////////
CDeckWalk::CDeckWalk(CList<CString,CString>* pDeckList,BOOL bFormatted)
{
	m_pDeckList			= pDeckList;
	m_bFormatted		= bFormatted;
	m_nCardNo			= 0;
	////////////////////////////// Show ALL	
	m_bNS_P_Object		= FALSE;			
	m_bNS_P_Solid		= FALSE;	//Mesh3D	
	m_bNS_P_Patch		= FALSE;	//Mesh2D	
	m_bNS_P_Curve		= FALSE;	//Mesh1D
	////////////////////////////
	m_bNS_RIGID			= FALSE; 
	m_bNS_Lin_Spring	= FALSE; 
	m_bNS_Lin_Snubber	= FALSE; 
	m_bNS_Non_Spring	= FALSE; 
	m_bNS_Non_Snubber	= FALSE;
	////////////////////////////// MeshNode
	m_bNS_MNode			= FALSE;
	////////////////////////////// StaticLoad
	m_bNS_Force			= FALSE;	
	m_bNS_Displace		= FALSE;
	m_bNS_Pressure		= FALSE;
	m_bNS_Thermal		= FALSE;
	m_bNS_LumpWt		= FALSE;
	//////////
}

int CDeckWalk::Init(BOOL bNS[])
{
	////////////////////////////// Posted	
	m_bNS_P_Object		= bNS[27];			
	m_bNS_P_Solid		= bNS[28];	//Mesh3D	
	m_bNS_P_Patch		= bNS[29];	//Mesh2D	
	m_bNS_P_Curve		= bNS[30];	//Mesh1D
	////////////////////////////
	m_bNS_RIGID			= bNS[37]; 
	m_bNS_Lin_Spring	= bNS[38]; 
	m_bNS_Lin_Snubber	= bNS[39]; 
	m_bNS_Non_Spring	= bNS[40]; 
	m_bNS_Non_Snubber	= bNS[41];
	////////////////////////////// MeshNode
	m_bNS_MNode			= bNS[43];
	////////////////////////////// StaticLoad
	m_bNS_Force			= bNS[44];	
	m_bNS_Displace		= bNS[45];
	m_bNS_Pressure		= bNS[46];
	m_bNS_Thermal		= bNS[47];
	m_bNS_LumpWt		= bNS[48];
	//////////
	return 0;
}

int	CDeckWalk::DW_MESH()
{   
	//////////////////////////////////////////////////////////////////
    //	RECALL:                                                 	//
    //		We're walking through THE List which contains:			//
    //					POSTED OBJ3D								//
    //					UNPOSTED PATCH (Dirty)						//
    //					UNPOSTED CURVE (Dirty)						//
    //					ALL Other ElemObjs							//
    //					ALL OTHER DrawObjs							// 
	//////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	///////////////////////////////////////////////////////////////////////// Walk Thro' All Lists
	for(int iList=0;iList<MAX_LIST_ARRAY;iList++)
	{
		UINT nObjType = pObjectMgr->ListIndexToObjType(iList);
		if
		(
			nObjType != MESH3D &&
			nObjType != MESH2D &&
			nObjType != MESH1D 
		)
			////////
			continue;
		//////////////////////////////////////////////////////////////////
		CDListMgr* pList = pObjectMgr->GetObjectListFromIndex(iList);	// 
		int nCount = pList->GetCount();
		if(nCount<=0)
			continue;
		///////////////////////////////////////////////////////////////////
		int iCount = 0;
		for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
			iCount++;
			/////////////////////////////////////////////////////////////// Delete Mark?
			if( pObject->IsDeleted() )
				continue;
			//////////////////////////////////////////////// Draw THE Object
			int nObjType  	= pObject->GetObjectType();
			//////////////////////////////////////////////////////////////
			switch ((UINT)nObjType)
			{
				case MESH3D:
					//////////////////////////////////////////////// Obj3D
					if(!m_bNS_P_Solid)
						/////////////
						DW_Mesh3D(pObject);
						///////////////////////
					break;

				case MESH2D:
					//////////////////////////////////////////////// Obj3D
					if(!m_bNS_P_Patch)
						/////////////
						DW_Mesh2D(pObject);
						///////////////////////
					break;

				case MESH1D:
					//////////////////////////////////////////////// Obj3D
					if(!m_bNS_P_Curve)
						/////////////
						DW_Mesh1D(pObject);
						///////////////////////
					break;


				default:
					break;
			}
			////////// end switch
		}
		///////// end List of Specific Objects 
	}
	////////// end List of All Objects
	return 0;
}

int	CDeckWalk::DW_Mesh3D(CDrObject* pObject)
{
	/////////////////////////////////////////////////////// Mesh3D Info
/*
	CString strCard;
	CString strFmt;
	////////////////
	if(m_bFormatted)
		pObject->DoFormattedCardView(&strCard,strFmt);
	else
		pObject->DoUnFormattedCardView(&strCard);
	////////////////////////// Save in DeckList
	m_pDeckList->AddTail(strCard);
*/
    //////////////////////////////////////////// 0D
	CDListMgr* pListN = pObject->GetFE0DList();
	/////////////////////////////// 1D
	if(DW_Mesh0DObjects(pListN,pObject)<0)
		return -1;
    //////////////////////////////////////////// 1D
	CDListMgr* pListC = pObject->GetFE1DList();
	/////////////////////////////// 1D
	if(DW_Mesh1DObjects(pListC,pObject)<0)
		return -1;
    //////////////////////////////////////////// 2D
	CDListMgr* pListP = pObject->GetFE2DList();
	/////////////////////////////// 1D
	if(DW_Mesh2DObjects(pListP,pObject)<0)
		return -1;
    //////////////////////////////////////////// 3D
	CDListMgr* pListS = pObject->GetFE3DList();
	/////////////////////////////// 1D
	if(DW_Mesh3DObjects(pListS,pObject)<0)
		return -1;
	/////////	
	return 0;
}

int	CDeckWalk::DW_Mesh3DObjects(CDListMgr* pList,CDrObject* pObject)
{
	//////////////////////////////////////////// Posted 2D Elems
	if(!pList->IsEmpty())								  									
	{
//		if(DW_ObjectType(pList,TR_3,FMT_TR_3)<0)		// TR_3
			return -1;
//		if(DW_ObjectType(pList,QU_4,FMT_QU_4)<0)		// Qu_4
//			return -1;
		//////////////////////
	}
	/////////	
	return 0;
}

int	CDeckWalk::DW_Mesh2D(CDrObject* pObject)
{
	CString strCard;
	strCard = "";
	/////////////////////////////////////////////////////// Mesh2D Info
	//////////////////////////////////////////// 0D
 	////////////////////////////////////// Heading
	m_pDeckList->AddTail(strCard); // blank Line
	m_pDeckList->AddTail(strCard); // blank Line
	strCard = "C,,************* Node Definition ****************";
	m_pDeckList->AddTail(strCard);
	strCard = "";
	m_pDeckList->AddTail(strCard); // blank Line
	/////////////////////////////
	CDListMgr* pListN = pObject->GetFE0DList();
	/////////////////////////////// 0D
	if(DW_Mesh0DObjects(pListN,pObject)<0)
		return -1;
 	////////////////////////////////////// Heading
	m_pDeckList->AddTail(strCard); // blank Line
	m_pDeckList->AddTail(strCard); // blank Line
	strCard = "C,,************* Element Definition *************";
	m_pDeckList->AddTail(strCard);
	strCard = "";
	m_pDeckList->AddTail(strCard); // blank Line
	/////////////////////////////
    //////////////////////////////////////////// 1D
	CDListMgr* pListC = pObject->GetFE1DList();
	/////////////////////////////// 1D
	if(DW_Mesh1DObjects(pListC,pObject)<0)
		return -1;
    //////////////////////////////////////////// 2D
	CDListMgr* pListP = pObject->GetFE2DList();
	/////////////////////////////// 2D 
	if(DW_Mesh2DObjects(pListP,pObject)<0)
		return -1;
	//////////////////////////////////////////// Node to Elem
	if(DW_MeshNodeToElement(pListN)<0)
		return -1;
	////////////////////////////////////////////
#ifdef _DEBUG
	/////////////////////////////////////////////////////// Debug Info
	CDListMgr* pListE = ((CDrMesh2D*)pObject)->GetEdgeList();
    //////////////////////////////////////////// Vertex to Vertex
	if(DW_MeshVrtxToVrtx(pListN,pListE)<0)
		return -1;
	//////////////////////////////////////////// Vertex to Edge
    //////////////////////////////////////////// Edge Definition
#endif
	/////////
	return 0;
}

int	CDeckWalk::DW_Mesh2DObjects(CDListMgr* pList,CDrObject* pObject)
{
	//////////////////////////////////////////// Posted 2D Elems
	if(!pList->IsEmpty())								  									
	{
		if(DW_ObjectType(pList,TR_3,FMT_TR_3)<0)		// TR_3
			return -1;
		if(DW_ObjectType(pList,TR_6,FMT_TR_3)<0)		// TR_3
			return -1;
		if(DW_ObjectType(pList,TR_9,FMT_TR_3)<0)		// TR_3
			return -1;
		if(DW_ObjectType(pList,TR_10,FMT_TR_3)<0)		// TR_3
			return -1;
		if(DW_ObjectType(pList,QU_4,FMT_QU_4)<0)		// Qu_4
			return -1;
		if(DW_ObjectType(pList,QU_8,FMT_QU_4)<0)		// Qu_4
			return -1;
		if(DW_ObjectType(pList,QU_9,FMT_QU_4)<0)		// Qu_4
			return -1;
		if(DW_ObjectType(pList,QU_12,FMT_QU_4)<0)		// Qu_4
			return -1;
		if(DW_ObjectType(pList,QU_16,FMT_QU_4)<0)		// Qu_4
			return -1;
		//////////////////////
	}
	/////////	
	return 0;
}

int	CDeckWalk::DW_Mesh1D(CDrObject* pObject)
{
	//////////////////////////////////////////// Mesh1D Info
    //////////////////////////////////////////// 0D
	CDListMgr* pListN = pObject->GetFE0DList();
	/////////////////////////////// 1D
	if(DW_Mesh0DObjects(pListN,pObject)<0)
		return -1;
    //////////////////////////////////////////// 1D
	CDListMgr* pListC = pObject->GetFE1DList();
	/////////////////////////////// 1D
	if(DW_Mesh1DObjects(pListC,pObject)<0)
		return -1;
	/////////
	return 0;
}

int	CDeckWalk::DW_Mesh1DObjects(CDListMgr* pList,CDrObject* pObject)
{
	//////////////////////////////////////////// Posted Curves									
	if(!pList->IsEmpty())								  									
	{
		if(DW_ObjectType(pList,TRUSS,FMT_TRUSS)<0)		// TRUSSes
			return -1;
		if(DW_ObjectType(pList,BEAM,FMT_BEAM)<0)		// BEAMs
			return -1;
		if(DW_ObjectType(pList,PIPE,FMT_PIPE)<0)		// PIPEs
			return -1;
		if(DW_ObjectType(pList,ELBOW,FMT_ELBOW)<0)		// ELBOWs
			return -1;
		//////////////////////
	}
	/////////	
	return 0;
}

int	CDeckWalk::DW_Mesh0D(CDrObject* pObject)
{
	/////////////////////////////////////////////////////// Mesh0D Info
    //////////////////////////////////////////// 0D
	CDListMgr* pListN = pObject->GetFE0DList();
	/////////////////////////////// 1D
	if(DW_Mesh0DObjects(pListN,pObject)<0)
		return -1;
	/////////
	return 0;
}

int	CDeckWalk::DW_Mesh0DObjects(CDListMgr* pList,CDrObject* pObject)
{
	//////////////////////////////////////////// Posted Nodes
	if(!pList->IsEmpty())								  									
	{
		if(DW_ObjectType(pList,FE0D,FMT_NODE)<0)		// MNODEs
			return -1;
	}
	/////////
	return 0;
}
/////////////////////////////////////
static char Fmt[] = "%sxx(%c)";
///////////////////////////////////// 
int	CDeckWalk::DW_ObjectType(CDListMgr* pList,UINT CurrentObjType,UINT CurrentFmt)
{
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////////////////////////
	CString strFmt;
	/////////////////////////////////////////////////////////////////// 
	if (! strFmt.LoadString( CurrentFmt ))
	{
		CString strError = "Error:\nCDeckWalk::DW_Object\nLoading String: ";
		char buf[50];
		sprintf(buf,"%d NOTFOUND",CurrentFmt);
		strError += buf;
		AfxMessageBox(strError);
		return -1;
	}
	///////////////////////////////////////////////////////////
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		int nObjType  		= pObject->GetObjectType();
		////////////
		if((UINT)nObjType != CurrentObjType)
			continue;
		////////////////
//		CString* pstrCard = new CString;
		CString strCard;
		////////////////
		if(m_bFormatted)
			pObject->DoFormattedCardView(&strCard,strFmt);
		else
			pObject->DoUnFormattedCardView(&strCard);
		///////////////////////////////////////////// Add Card No
		m_nCardNo++;
		int nLen = strCard.GetLength();
		if(nLen>COL_CARDNO)
		{
			AfxMessageBox("ERROR:\nCDeckWalk::DW_ObjectType:\nnLen>COL_CARDNO");
			return -1;
		}
/*
		/////////////////////////////////////
		int nblanks = COL_CARDNO - nLen;
		CString strFmt;
		char* buf = strFmt.GetBuffer(BUFF_SIZE);
		////////
		int j;
		j = sprintf(buf,"%%s");
		for(int i=0;i<nblanks;i++)
			j += sprintf(buf+j,"%c",' ');
		j += sprintf(buf+j,"%%d");
		/////
		CString str;
		char buffer[300];
		sprintf(buffer,strFmt,strCard,m_nCardNo);
*/
		/////
		CString str;
		char buffer[300];
		sprintf(buffer,"%-4.4d %s",m_nCardNo,strCard);
		////////////////
		str = buffer;
		int nstrLen = str.GetLength(); 
		strCard = str;
		///////////////////////////////////////////// Save in DeckList
		m_pDeckList->AddTail(str);
	}
	//////////
	return 0;
}

int	CDeckWalk::DW_MeshVrtxToVrtx(CDListMgr* pListV,CDListMgr* pListE)
{
	if(pListV->IsEmpty() || pListE->IsEmpty())
		return -1;
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////////////// Heading
	CString strCard;
	strCard = "";
	m_pDeckList->AddTail(strCard); // blank Line
	m_pDeckList->AddTail(strCard); // blank Line
	strCard = "C,,************* Vertex To Vertex Connectivity **";
	m_pDeckList->AddTail(strCard);
	strCard = "";
	m_pDeckList->AddTail(strCard); // blank Line
	///////////////////////////////////////////////////////////
	int indexV = -1;
	///
	for (POSITION pos = pListV->GetFirstObjectPos();pos !=NULL;)
	{
		CDrFE0D* pObject = (CDrFE0D*)pListV->GetNextObject(pos);
		indexV++; 
		////////////////
//		strCard = pObject->GetElNumID();	// VertexID
		strCard = pObject->GetObjectID() + "     ";	// VertexID
		///////
		for (POSITION pos = pListE->GetFirstObjectPos();pos !=NULL;)
		{
			CDrEdge* pEdge = (CDrEdge*)pListE->GetNextObject(pos);
			////////////////
			int indexI = pEdge->GetVrtxIndex(0); 
			int indexJ = pEdge->GetVrtxIndex(1);
			///
			if(indexI == indexV)
			{
				CDrFE0D* pVrtx = (CDrFE0D*)pListV->GetObject(indexJ);
//				strCard += "  " + pVrtx->GetElNumID();
				strCard += pVrtx->GetObjectID() + "  ";	// VertexID
			}
			else
			if(indexJ == indexV)
			{
				CDrFE0D* pVrtx = (CDrFE0D*)pListV->GetObject(indexI);
//				strCard += "  " + pVrtx->GetElNumID();
				strCard += pVrtx->GetObjectID() + "  ";	// VertexID
			}
			else
				continue;
		}
		///////////////////////////////////////////// Save in DeckList
		m_pDeckList->AddTail(strCard);
	}
	//////////
	return 0;
}

int	CDeckWalk::DW_MeshNodeToElement(CDListMgr* pListV)
{
	if(pListV->IsEmpty())
		return -1;
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////////////// Heading
	CString strCard;
	strCard = "";
	m_pDeckList->AddTail(strCard); // blank Line
	m_pDeckList->AddTail(strCard); // blank Line
	strCard = "C,,************* Node To Element Connectivity ***";
	m_pDeckList->AddTail(strCard);
	strCard = "";
	m_pDeckList->AddTail(strCard); // blank Line
	///////////////////////////////////////////////////////////
	int indexV = -1;
	CString str;
	///
	for (POSITION pos = pListV->GetFirstObjectPos();pos !=NULL;)
	{
		CDrFE0D* pObject = (CDrFE0D*)pListV->GetNextObject(pos);
		indexV++; 
		////////////////
//		strCard = pObject->GetElNumID();	// VertexID
		strCard = pObject->GetObjectID() + "     ";	// VertexID
		//////////////////////////////////////////////////////////// 1D
		CDListMgr* pListE = pObject->GetFE1DList();
		if(!pListE->IsEmpty())
		{
			str = strCard;
			///
			DW_MeshNodeToElementID(pListV,pListE,str,indexV);
			//////////////////////////////// Save in DeckList
			m_pDeckList->AddTail(str);
		}
		//////////////////////////////////////////////////////////// 2D
		pListE = pObject->GetFE2DList();
		if(!pListE->IsEmpty())
		{
			str = strCard;
			///
			DW_MeshNodeToElementID(pListV,pListE,str,indexV);
			//////////////////////////////// Save in DeckList
			m_pDeckList->AddTail(str);
		}
		//////////////////////////////////////////////////////////// 3D
		pListE = pObject->GetFE3DList();
		if(!pListE->IsEmpty())
		{
			str = strCard;
			///
			DW_MeshNodeToElementID(pListV,pListE,str,indexV);
			//////////////////////////////// Save in DeckList
			m_pDeckList->AddTail(str);
		}
	}
	//////////
	return 0;
}

int	CDeckWalk::DW_MeshNodeToElementID(CDListMgr* pListV,CDListMgr* pListE,
												CString& strCard,int indexV)
{
	for (POSITION pos = pListE->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pListE->GetNextObject(pos);
		///
		strCard += pObject->GetObjectID() + "  ";	// 
	}
	//////////
	return 0;
}
/////////////////////////// end of module ///////////////
