// GrafObj.cpp : implementation file
//

#include "stdafx.h"     

#include "Def_Objs.h" 
#include "Def_View.h" 
/////////////////////
#include "drgraf.h"
//#include "drgrafrm.h"
#include "drgradoc.h"

#include "NewObjs.h"
///////////////////// StaLObj
#include "Def_Supp.h"
///////////////////// StaLObj
#include "Def_StaL.h"
///////////////////// DynLObj
#include "Def_DynL.h"
///////////////////// SpeLObj
#include "Def_SpeL.h"
///////////////////// ElemObj
#include "Def_Elem.h"
#include "Ext_Elem.h" 
//#include "Def_EInf.h"
//#include "Ext_EInf.h" 
///////////////////// SpecObj
#include "Def_Spec.h"
#include "Ext_Spec.h" 
///////////////////// DrawObj
#include "Def_Draw.h"	// for LABEL
#include "Ext_Draw.h" 
///////////////////// 
#include "Def_3D.h"   // for initialization of the Drawing Operations
#include "Dr3DMgr.h"
/////////////////////
#include "dListMgr.h"
#include "drobject.h"
/////////////////////
#include "AxObjMgr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CAxDataRowHint, CObject)
////////////////////////////////////////////// CDataRowHint class
CAxDataRowHint::CAxDataRowHint()
{
}
/////////////////////////////////////////////////////////////////////////////
// CGrafObj
IMPLEMENT_SERIAL(CAxObjMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CAxObjMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CAxObjMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
/////////////////////////////////////////////////////////////////////////////
CAxObjMgr::CAxObjMgr()
{
	for(int i=0;i<MAX_LIST_ARRAY;i++)
	{
		while(!(GetObjectListFromIndex(i)->IsEmpty()) )// delete all 
			GetObjectListFromIndex(i)->RemoveAll();
	}		
}

CAxObjMgr::~CAxObjMgr()
{
	for(int i=0;i<MAX_LIST_ARRAY;i++)
	{
		while(!(GetObjectListFromIndex(i)->IsEmpty()) )// delete all left
			delete (CDrObject*)(GetObjectListFromIndex(i)->RemoveHead());  //specials
	}

}
/////////////////////////////
void CAxObjMgr::Init()
{
	int i;
	////////////////////////////////		
	SetMeshGenOn(FALSE);
	////////////////////////
	m_bViewChanged		= TRUE;
	///////////////////////////////// InputNo
	for(i=0;i<MAX_INPUT_ARRAY;i++)
		m_nLastInputNo[i] 	= 0;
	///////////////////////////////// ObjectNo
	for(i=0;i<MAX_LIST_ARRAY;i++)
		m_nLastObjectNo[i] 	= 0;
	///
	m_nActiveObjectNo	= 0;
	m_nActiveObjectIndex=-1; 
	///////////////////////////////// init all the Special Objects
	InitBooleans();
	InitDataWindow();
	InitDrFont();
	InitDrPen();
	InitLayer();
	InitPatchMnu();
	InitObj3DMnu();
	////////////////
	InitMapFactor();
	InitPrecision();
	InitScaleFactor();
	InitUnit();
	InitHitNet();
	/////////////////
//	InitElemInfo();
	/////////////////////////////////////////////////////////////// Format for Node data
	CPrecision* pPrecision = (CPrecision*)GetSpecObject(PRECISION);
	/////////////////////////////////////////////////
	long lWorldBase = (long) pPrecision->GetWorldBase();
	UINT nDecPlaces = (UINT) pPrecision->GetPrecision();
    SetFormatParam(nDecPlaces,lWorldBase);
    /////////////////////////////////////////////////////////////// Tolerance Update
	CHitNet*	pHitNet		= (CHitNet*)GetSpecObject(HITNET);
	CMapFactor* pMapFactor	= (CMapFactor*)GetSpecObject(MAPFACTOR);
	double		dWorldBase	= (double)lWorldBase;
	double		dMapFactor	= pMapFactor->GetMapFactor();
	//////////////////////////////////////
	double dTol = pHitNet->GetSearchDet(); 
 	//////////////////////// Scaled Coord
	SCtoDS(&dTol);
   	//////////////////////// Map Factor
   	dTol /= dMapFactor;
	//////////////////////// Precision 
   	dTol *= dWorldBase;
	//////////////////////////////////////
	pHitNet->SetSearchDet(dTol); 
 	////////////////////////////////////////////////////////////////
  		
	return;
}
/////////////////////////////////////////////////////////
//CSize CDrawView::GetDocSize(LPOINT3 WinExtWIC,int nViewNumber)
CSize CAxObjMgr::GetDocSize()
{ 

	//	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc );
	//  m_pDoc not set yet(from OnInitialUpdate call: setscrollsizes
	//	LPOINT3		WinExtWIC = pDoc->GetWinExtWIC();
	////////////////////////////////////////////////
/*
	if(nViewNumber == VIEW12)      // hor = x; ver = y;
	{
		m_sizeDoc.cx = (int)WinExtWIC.x;
		m_sizeDoc.cy = (int)WinExtWIC.y; 
	}
	else if(nViewNumber == VIEW23) // hor = z; ver = y;
	{
		m_sizeDoc.cx = (int)WinExtWIC.z;
		m_sizeDoc.cy = (int)WinExtWIC.y; 
	}
	else if(nViewNumber == VIEW31) // hor = x; ver = z;
	{
		m_sizeDoc.cx = (int)WinExtWIC.x;
		m_sizeDoc.cy = (int)WinExtWIC.z; 
	}
	else if(nViewNumber == VIEWISO) // hor = ? ver = ?;
	{
		m_sizeDoc.cx = (int)WinExtWIC.x;    // TEMPORARILY as VIEW12
		m_sizeDoc.cy = (int)WinExtWIC.y; 
	}
*/	
    ////////////////////////  MMLOENGLISH   7 1/2 x 5 inch
		m_sizeDoc.cx =  750;
		m_sizeDoc.cy =  500; 
        ////////////////////


	return m_sizeDoc;
	
}
////////////////////////////////////////////////////////////////////////////// Input
UINT CAxObjMgr::GetLastInputNo(int nObjectType)
{
	int nInputIndex =	ObjTypeToInputIndex(nObjectType);
	//////////////////////////////////////////////////
	return	(nInputIndex>=0?(m_nLastInputNo[nInputIndex]):-1);
}

int	CAxObjMgr::BumpLastInputNo(int nObjectType)
{
	int nInputIndex =	ObjTypeToInputIndex(nObjectType);
	//////////////////////////////////////////////////
	if(nInputIndex>=0)
	{
		int nLastNo = m_nLastInputNo[nInputIndex];
		nLastNo++;
		m_nLastInputNo[nInputIndex] = nLastNo;
		///////
		return 0;
	}
	else
		return -1;
}

int CAxObjMgr::ObjTypeToInputIndex(int nObjectType)
{
 
	//////////////////
	switch (nObjectType)
	{

//	LastAssigned = 28
		///////////////////////////////////////////////// Generators 	
		case OBJ3D:			return 8;
		case SOLID:			return 7;
		case PATCH:			return 6;
		case CURVE:			return 4;
		case C_PROFILE:		return 5;
		///////////////////////////////////////////////// StaLObjs	
		case STATICLOAD:	return 13;
		case FORCE:			return 13;
		case DISPLACE:		return 13;
		case PRESSURE:		return 13;
		case THERMAL:		return 13;
		case LUMPWT:		return 13;
		case CSTATIC:		return 14;
		case PSTATIC:		return 15;
		case SSTATIC:		return 16;
		///////////////////////////////////////////////// DynLObjs	
//case DYNAMICLOAD:	return ??;
		///////////////////////////////////////////////// SpeLObjs	
//case SPECTRALOAD:	return ??;
		///////////////////////////////////////////////// SuppObjs	
		case LIN_SUPPORT:	return 12;
		///////////////////////////////////////////////// ElemObjs	
		/////////////////////////////// 0D	
		case NODE:			return 0;
		case INODE:			return 0;
		case CNODE:			return 1;
		case MNODE:			return 2;
		///////////////////////////////////////////////// DrawObjs	
		case LABEL:			return 9;
		case FREEHAND:		return 10;
		case GRID:			return 11;
		//////////////////////////////
		default:			return -1;			   
		//////////////////////////////
	}
}

int CAxObjMgr::InputIndexToObjType(int nIndex)
{
 
//	LastAssigned = 28
	//////////////////
	switch (nIndex)
	{
		///////////////////////////////////////////////// Generators 	
		case 8:			return OBJ3D;
		case 7:			return SOLID;
		case 6:			return PATCH;
		case 4:			return CURVE;
		case 5:			return C_PROFILE;
		///////////////////////////////////////////////// StaLObjs	
		case 13:		return STATICLOAD;
//		case 13:		return FORCE;
//		case 13:		return DISPLACE;
//		case 13:		return PRESSURE;
//		case 13:		return THERMAL;
//		case 13:		return LUMPWT;
		case 14:		return CSTATIC;
		case 15:		return PSTATIC;
		case 16:		return SSTATIC;
		///////////////////////////////////////////////// DynLObjs	
//case ??:		return DYNAMICLOAD;
		///////////////////////////////////////////////// SpeLObjs	
//case ??:		return SPECTRALOAD;
		///////////////////////////////////////////////// SuppObjs	
		case 12:		return LIN_SUPPORT;
		///////////////////////////////////////////////// ElemObjs	
		/////////////////////////////// 0D	
		case 0:			return NODE;
//		case 0:			return INODE;
		case 1:			return CNODE;
		case 2:			return MNODE;
		///////////////////////////////////////////////// DrawObjs	
		case 9:			return LABEL;
		case 10:		return FREEHAND;
		case 11:		return GRID;
		//////////////////////////////
		default:		return NONE;			   
		//////////////////////////////
	}
}

////////////////////////////////////////////////////////////////////////////// DataBase
CDrObject* CAxObjMgr::AddToDataBase(CString& ObjID,int& nActiveIndex,int nObjType)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 			= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CDListMgr* pDListMgr 		= GetObjectList(nObjType);
	CDrObject* pAddObject;
	////////////////////////////////////////////////////// Check if it already Exist
	int index = pDListMgr->GetObjectIndex(nObjType, ObjID);
	if(index>=0)
	{
		pAddObject		= (CDrObject*)pDListMgr->GetObject(index);
		nActiveIndex	= index;
		return pAddObject;
	}
	////////////////////////////////////////////////////// Add New
	else
	{
		pAddObject		= AddToDataBase(nActiveIndex,nObjType);
		pAddObject->SetObjectID(ObjID);
		return pAddObject;
	}
	//////////
}

CDrObject* CAxObjMgr::AddToDataBase(int& nActiveIndex,int nObjType)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 			= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CDListMgr* pDListMgr 		= GetObjectList(nObjType);
	/////////////////////////////////////////////
    CNewObjs NewObjs;
    CDrObject* pAddObject 	= NewObjs.NewObject(nObjType);
	if(!pAddObject)
		return (CDrObject*)NULL;
	///////////////////////////////////////////////
  	pDListMgr->InsertObject(pAddObject);          				// add 
   	pAddObject->SetObjectNo(GetLastObjectNo(nObjType));
	BumpLastObjectNo(nObjType);                         // bump it
	///////////////////////////////////////////////////////////////////////////
	pDoc->SetModifiedFlag();                   					// document modified 
	////////////////////////////////////////////////////////////////////////////////													    
	nActiveIndex = GetObjectCount(nObjType) - 1;
	SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
	SetActiveObjectType(nObjType);		    // set Active ObjectType									
	//////////////////////////////////////////////////////////////////////////////// DataView
	AddToRowList( nActiveIndex, nObjType);                         //
	int nRowIndex;
	ObjIndexToRowIndex(nRowIndex, nActiveIndex, nObjType);
	SetActiveRowIndex( nRowIndex);          //
	//////////////////////////////////////////////////////////
	return pAddObject;
}

int CAxObjMgr::DeleteFromDataBase(int nObjIndex, int nObjType)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 			= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CDListMgr* pDListMgr 		= GetObjectList(nObjType);
	//////////////////////////////////////////////////////////////////////////////// DataView/RowList
	int nRowIndex;
	ObjIndexToRowIndex(nRowIndex, nObjIndex, nObjType);
	//////////////////////////////////////////////////////////////// DELETE
	CDrObject* pObject = (CDrObject*)pDListMgr->GetObject(nObjIndex);
	pDListMgr->RemoveObject(nObjIndex);
	delete pObject; 
	/////////////////////////////////// from RowList
	DeleteFromRowList( nRowIndex);                        
	SetActiveRowIndex( nRowIndex-1);          //
	////////////////////
	return 0;
}
///////////////////////////////////////////////////////// helpers 
//void CDrObject::Do_Object_Dialog()
void CAxObjMgr::Do_Object_Dialog(int nActiveObjectType)
{ 

	int nActiveObjIndex = GetActiveObjectIndex();		 // Get Index
	///////////////////////   
	CDListMgr*	pDListMgr = GetObjectList(nActiveObjectType);
	CDrObject* pObject = (CDrObject*)pDListMgr->GetObject(nActiveObjIndex);
    ////////////////////////// Draw Elem Data
	pObject->DealObjectDialog();
	//////////////////////////   	
	
} 

//void CDrObject::Do_Object_DataView(CDC* PtrDC,int y,int nRowIndex)
void CAxObjMgr::Do_Object_DataView(CDC* PtrDC,int y,int nRowIndex)
{
	int		nObjIndex;
	int		nObjType;
	/////////////////
	RowIndexToObjIndex(nRowIndex, nObjIndex, nObjType);
	/////////////////
	CDListMgr*	pDListMgr = GetObjectList(nObjType);
	///////////////////////   
	CDrObject* pObject = (CDrObject*)pDListMgr->GetObject(nObjIndex);
    ////////////////////////// Draw Elem Data
	if(pObject)
		pObject->DoDataView(PtrDC,y);
	//////////////////////////   	
	
} 

//void CDrObject::Do_Object_DrawView(CDC* PtrDC,BOOL bPenChange,int nObjectIndex,
//																int nViewNumber)
void CAxObjMgr::Do_Object_DrawView(CDC* PtrDC,BOOL bPenChange,int nObjectIndex,
												int nViewNumber, int nActiveObjectType)
{ 

	CDListMgr*	pDListMgr = GetObjectList(nActiveObjectType);
	///////////////////////   
	CDrObject* pObject = (CDrObject*)pDListMgr->GetObject(nObjectIndex);
	int nObjType  = pObject->GetObjectType();
	int nElemType = pObject->GetElemType();
    //////////////////////////////////// Zoom 
//    POINT ptZoom;
//    ptZoom.x = 1;
//    ptZoom.y = 1;
//    if (nViewNumber == VIEWISO)
//    		ScalebyZoomFactor(ptZoom,1,nViewNumber);
    //////////////////////////////////////////////// Draw THE Object
    if (nElemType <0) return;  // not viewable 
    /////////////////////////////////////////
    if (nElemType == (int)DRAW_OBJECT)
		pObject->DoDrawView(PtrDC,bPenChange,nViewNumber);
    else
//    if (nElemType == (int)ELEM_OBJECT)
		pObject->DoDrawView(PtrDC,bPenChange);
	////////////////////////////////////////////////   	
                               
}

////////////////////////////////////////////////////////// Data/Card View
//void CDrObject::ChangeSelectionNextObjectIndex(BOOL bNext)
void CAxObjMgr::ChangeSelectionNextObjectIndex(BOOL bNext)
{
	//////////////////////////////////////////////
	UINT nActiveRowIndex = GetActiveRowIndex();
	
	if (bNext)
	{
		if ((int)nActiveRowIndex < (GetRowCount() - 1))
		{ 
			SetActiveRowIndex(++nActiveRowIndex);
		}
	}
	else
	{
		if (nActiveRowIndex > 0)
		{
			SetActiveRowIndex(--nActiveRowIndex);
		}
	}
	int	nObjIndex;
	int	nObjType;
	/////////////////
	RowIndexToObjIndex(nActiveRowIndex, nObjIndex, nObjType);
	SetActiveObjectIndex(nObjIndex);
	SetActiveObjectType(nObjType);
	//////////////////////////////////////////////
//	SetActiveObjectIndex(nNewActiveObjectIndex);
	UpdateAllViewsWithActiveIndex(NULL,nObjIndex,nObjType);
}

//void CDrObject::ChangeSelectionToObjectIndex(UINT nNewActiveObjectIndex)
void CAxObjMgr::ChangeSelectionToObjectIndex(UINT nNewActiveRowIndex)
{
	int	nObjIndex;
	int	nObjType;
	/////////////////
	RowIndexToObjIndex(nNewActiveRowIndex, nObjIndex, nObjType);
	SetActiveObjectIndex(nObjIndex);
	SetActiveObjectType(nObjType);
	//////////////////////////////////////////////
//	SetActiveObjectIndex(nNewActiveObjectIndex);
	UpdateAllViewsWithActiveIndex(NULL,nObjIndex,nObjType);
}


//void CDrObject::UpdateAllViewsWithActiveIndex(CView* pSourceView,
//													UINT nActiveIndex)
void CAxObjMgr::UpdateAllViewsWithActiveIndex(CView* pSourceView,
													UINT nActiveIndex, int nActiveObjType)
{ 

//	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc);
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	/////////////////// get ObjectType for view 
	CDListMgr* pDListMgr = GetObjectList(nActiveObjType);
	CDrObject* pObject = (CDrObject*)pDListMgr->GetObject(nActiveIndex);
//    int nType = pObject->GetObjectType();
    ///////////////////////////////////// set SceneChanged
    SetSceneChanged(TRUE);
    //////////////////////
	CDataRowHint hint;
//	pDoc->UpdateAllViews(pSourceView, MAKELONG(nActiveIndex,nType), &hint);
	pDoc->UpdateAllViews(pSourceView, MAKELONG(nActiveIndex,nActiveObjType), &hint);
	/////////////////////
} 

//int	CDrLabel::GetObjectIndexfromKey(CString KeyID,UINT KeyNo)
int	CAxObjMgr::GetObjectIndexfromKey(int nObjectType,CString KeyID,UINT KeyNo)
{

	CDListMgr* pDListMgr = GetObjectList(nObjectType);
	if(!pDListMgr)
		return -1;
	///////////////////////////////////////////// 
	if(pDListMgr->IsEmpty() || KeyNo<=0) 
	{

		if(pDListMgr->IsEmpty())
		return -1;
	}	
	////////////////////////////////////////////////
	if(pDListMgr->GetSpecificObjectCount(nObjectType) <= 0)
		return -1;
	///////////////////////////////////////////////// ObjType
	//		Special for Node,CNode,MNode,INode
	//		///////////////////////////////////
	//	Since it is the correct List(hopefully) and
	//	CDrNode Class ObjectType is always NODE or FE0D
	//	We Need to convert variations to NODE or FE0D
	/////////////////////////////////////////////////
	UINT nType = (UINT)nObjectType;
	///
	if	( nType == NODE	|| nType == INODE || nType == CNODE	)
		nType = NODE;
	else
	if	( nType == FE0D	|| nType == MNODE || nType == MCNODE )
		nType = FE0D;
    /////////////////////////////////////////////////
	BOOL bYes;			
 	POSITION pos = pDListMgr->GetFirstObjectPos();
	int i;
	for (i=0;pos !=NULL ;i++)
	{
		CDrObject* pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if(pObject->GetObjectType() == (int)nType)
		{ 
			bYes = pObject->IsKeyMatch(pObject,KeyID,KeyNo);
			if(bYes)
				return i;				
        }
	}
	return -1;
}
/////////////////////////////////////////////////////////////////////////////////// ListObjects
int CAxObjMgr::ObjTypeToListIndex(int nObjectType)
{
 
	//////////////////
	switch (nObjectType)
	{

//	LastAssigned = 38
		///////////////////////////////////////////////// Generators 	
		case OBJ3D:			return 8;
		case SOLID:			return 7;
		case PATCH:			return 6;
		case CURVE:			return 4;
		case C_PROFILE:		return 5;
		///////////////////////////////////////////////// StaLObjs	
		case STATICLOAD:	return 13;
		case FORCE:			return 13;
		case DISPLACE:		return 13;
		case PRESSURE:		return 13;
		case THERMAL:		return 13;
		case LUMPWT:		return 13;
		case CSTATIC:		return 14;
		case PSTATIC:		return 15;
		case SSTATIC:		return 16;
		///////////////////////////////////////////////// DynLObjs	
//case DYNAMICLOAD:	return ??;
		///////////////////////////////////////////////// SpeLObjs	
//case SPECTRALOAD:	return ??;
		///////////////////////////////////////////////// SuppObjs	
		case LIN_SUPPORT:	return 12;
		///////////////////////////////////////////////// ElemObjs	
		case MESH1D:		return 21;
		case MESH2D:		return 22;
		case MESH3D:		return 23;
		/////////////////////////////// 0D	
		case NODE:			return 0;
		case INODE:			return 0;
		case CNODE:			return 1;
		///
		case FE0D:			return 2;
		case MNODE:			return 2;
		case MCNODE:		return 38;
		/////////////////////////////// 1D	
		case FE1D:			return 3;
		case TRUSS:			return 25;
		case PIPE:			return 26;
		case ELBOW:			return 27;
		case BEAM:			return 28;
		/////////////////////////////// 2D	
		case FE2D:			return 20;
		case QU_4:			return 29;
		case QU_8:			return 30;
		case QU_9:			return 31;
		case QU_12:			return 32;
		case QU_16:			return 33;
		///
		case TR_3:			return 34;
		case TR_6:			return 35;
		case TR_9:			return 36;
		case TR_10:			return 37;
		/////////////////////////////// 3D	
		case FE3D:			return 17;
		///////////////////////////////////////////////// DrawObjs	
		case LABEL:			return 9;
		case FREEHAND:		return 10;
		case GRID:			return 11;
		//////////////////////////////
		default:			return -1;			   
		//////////////////////////////
	}
}

int CAxObjMgr::ListIndexToObjType(int nIndex)
{
 
//	LastAssigned = 38
	//////////////////
	switch (nIndex)
	{
		///////////////////////////////////////////////// Generators 	
		case 8:			return OBJ3D;
		case 7:			return SOLID;
		case 6:			return PATCH;
		case 4:			return CURVE;
		case 5:			return C_PROFILE;
		///////////////////////////////////////////////// StaLObjs	
		case 13:		return STATICLOAD;
//		case 13:		return FORCE;
//		case 13:		return DISPLACE;
//		case 13:		return PRESSURE;
//		case 13:		return THERMAL;
//		case 13:		return LUMPWT;
		case 14:		return CSTATIC;
		case 15:		return PSTATIC;
		case 16:		return SSTATIC;
		///////////////////////////////////////////////// DynLObjs	
//case ??:		return DYNAMICLOAD;
		///////////////////////////////////////////////// SpeLObjs	
//case ??:		return SPECTRALOAD;
		///////////////////////////////////////////////// SuppObjs	
		case 12:		return LIN_SUPPORT;
		///////////////////////////////////////////////// ElemObjs	
		case 21:		return MESH1D;
		case 22:		return MESH2D;
		case 23:		return MESH3D;
		/////////////////////////////// 0D	
		case 0:			return NODE;
//		case 0:			return INODE;
		case 1:			return CNODE;
//
		case 2:			return FE0D;			// Vertex Points
//		case 2:			return MNODE;			// Mesh Nodes
		case 38:		return MCNODE;
		/////////////////////////////// 1D	
		case 3:			return FE1D;
		case 25:			return TRUSS;
		case 26:			return PIPE;
		case 27:			return ELBOW;
		case 28:			return BEAM;
		/////////////////////////////// 2D	
		case 20:		return FE2D;
		case 29:		return QU_4;
		case 30:		return QU_8;
		case 31:		return QU_9;
		case 32:		return QU_12;
		case 33:		return QU_16;
		///
		case 34:		return TR_3;
		case 35:		return TR_6;
		case 36:		return TR_9;
		case 37:		return TR_10;
		/////////////////////////////// 3D	
		case 17:		return FE3D;
		///////////////////////////////////////////////// DrawObjs	
		case 9:			return LABEL;
		case 10:		return FREEHAND;
		case 11:		return GRID;
		//////////////////////////////
		default:		return NONE;			   
		//////////////////////////////
	}
}

CDListMgr*	CAxObjMgr::GetObjectList(int nObjectType)
{
	int nListIndex =	ObjTypeToListIndex(nObjectType);
	//////////////////////////////////////////////////
	return	(nListIndex>=0?&(m_ObjectList[nListIndex]):(CDListMgr*)NULL);
}

int	CAxObjMgr::AddToRowList(int& nObjIndex, int& nObjType)
{
	long CurrentIndexType = MAKELONG(nObjIndex,nObjType);
	//////////////////////////////////////////
	GetRowList()->AddTail(CurrentIndexType);
	////////////
	return 0;
}
	
int CAxObjMgr::DeleteFromRowList(int& nRowIndex)
{
	if(nRowIndex<0 || nRowIndex>(GetRowCount()-1)	)
		return -1;
	//////////////
	CList<long,long>* pRowList = GetRowList();
	//////////////////////////////////////////
	POSITION pos;
	pos = pRowList->FindIndex(nRowIndex);
	pRowList->RemoveAt(pos);
	return 0;
	//////////////////////////////////////////////////
/*
	int i=-1;
	for (POSITION pos = pRowList->GetHeadPosition();pos !=NULL;)
	{
		i++;
		///////////////////////
		if(i == nRowIndex)
		{
			/////////////////////////////////////////////// remove
			pRowList->RemoveAt(pos);
			/////////
			return 0;
		}
	}
	///////////////
	return -1;
*/
}	
	
int CAxObjMgr::ObjIndexToRowIndex(int& nRowIndex, int& nObjIndex, int& nObjType)
{

	if(nObjIndex<0 || nObjType == NONE)
	{
		nRowIndex	= -1;
		return -1;
	}
	long CurrentIndexType = MAKELONG(nObjIndex,nObjType);
	int i = -1;
	//////////////
	CList<long,long>* pRowList = GetRowList();
	//////////////////////////////////////////////////
	for (POSITION pos = pRowList->GetHeadPosition();pos !=NULL;)
	{
		i++;
		long StoredIndexType = pRowList->GetNext(pos);
		if(StoredIndexType == CurrentIndexType)
		{
			/////////////////////////////////////////////// get info
			nRowIndex  = i;
			/////////
			return 0;
		}
	}
	///////////////
	nRowIndex  = -1;
	return -1;
}	

int CAxObjMgr::RowIndexToObjIndex(int nRowIndex, int& nObjIndex, int& nObjType)
{
	if(nRowIndex<0)
	{
		nObjIndex	= -1;
		nObjType	= NONE;
		return -1;
	}
	//////////
	int i = -1;
	CList<long,long>* pRowList = GetRowList();
	///////////////////////////////////////////////////
	for (POSITION pos = pRowList->GetHeadPosition();pos !=NULL;)
	{
		i++;
		long IndexType = pRowList->GetNext(pos);
		if(i == nRowIndex)
		{
			/////////////////////////////////////////////// get info
			nObjIndex  = LOWORD(IndexType);
			nObjType   = HIWORD(IndexType);
			/////////
			return 0;
		}
	}
	/////////
	return -1;
}

int	CAxObjMgr::GetObjectCount(int nObjectType)
{
	int nListIndex =	ObjTypeToListIndex(nObjectType);
	//////////////////////////////////////////////////
	return	(nListIndex>=0?(m_ObjectList[nListIndex]).GetCount():-1);
}

UINT CAxObjMgr::GetLastObjectNo(int nObjectType)
{
	int nListIndex =	ObjTypeToListIndex(nObjectType);
	//////////////////////////////////////////////////
	return	(nListIndex>=0?(m_nLastObjectNo[nListIndex]):-1);
}

int	CAxObjMgr::BumpLastObjectNo(int nObjectType)
{
	int nListIndex =	ObjTypeToListIndex(nObjectType);
	//////////////////////////////////////////////////
	if(nListIndex>=0)
	{
//		(m_nLastObjectNo[nListIndex])++;
		int nLastNo = m_nLastObjectNo[nListIndex];
		nLastNo++;
		m_nLastObjectNo[nListIndex] = nLastNo;
		///////
//		m_nMasterLastObjectNo++;
		return 0;
	}
	else
		return -1;
}
///////////////////////////////////////////////////////////////////// Helper
/*
UINT CElemObject::GetLength(LPOINT3 WIC_I,LPOINT3 WIC_J)
{
	////////////////////////////////////////////////  Get Doc Info
	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc);
	CPrecision* pPrecision     = pDoc->GetPrecision();
	///////////////////////////////////////////////////////////////////   
		WORLD I,J;
		double wLength;

		I.x = (double)WIC_I.x;
		I.y = (double)WIC_I.y;
		I.z = (double)WIC_I.z;

		J.x = (double)WIC_J.x;
		J.y = (double)WIC_J.y;
		J.z = (double)WIC_J.z;
		
		wLength  = fabs((I.x * I.x) - (J.x * J.x) );
		wLength += fabs((I.y * I.y) - (J.y * J.y) );
		wLength += fabs((I.z * I.z) - (J.z * J.z) );
		wLength  = fabs(sqrt(wLength) );
		/////////////////////////////
    	long LLength = (long)wLength;
		///////////////////////////// DEScale it
///		pDoc->SCtoDS(&LLength);                   
		long  LWorldBase  = pPrecision->GetWorldBase();
		LLength /= LWorldBase;                    // Take out Precision 
		UINT nLength = (UINT) LLength;            // LOG/DeScaled
		///////////////
		return nLength;
		///////////////    
} 
*/
/*                               
void CDrObject::ScalebyZoomFactor(POINT* pt,UINT nMaxPt,UINT nViewNumber)
{

	
//	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd );
	CDrGrafDoc* pDoc   = (CDrGrafDoc*)(theApp.m_pDoc ); 
	CZoom* pZoom = pDoc->GetZoom();
	/////////////////////////////////////////////////////////
	WORLD	ZoomFactor = pZoom->GetZoomFactor(nViewNumber); 
	//////////////////////////////////////////////////
    for (int i = 0;(UINT)i< nMaxPt; i++)
    { 
    	double	ptX  = (double)(pt[i].x);
        double  ptY  = (double)(pt[i].y);
          
    	if (nViewNumber == VIEW12) //View12:rot=0;tilt=0
    	{ 
	    	ptX *= ZoomFactor.x;
	    	ptY *= ZoomFactor.y; 
		}
	    else if (nViewNumber == VIEW23) //View23:rot=90;tilt=0;
		{
	    	ptX *= ZoomFactor.z;
	    	ptY *= ZoomFactor.y; 
	    }
	    else if (nViewNumber == VIEW31) //View31:rot=0;tilt=270;
		{
	    	ptX *= ZoomFactor.x;
	    	ptY *= ZoomFactor.z; 
		}
 	  	else if (nViewNumber == VIEWISO) //ViewISO:rot=?;tilt=?;
		{
	    	ptX *= ZoomFactor.x;
	    	ptY *= ZoomFactor.y; 
		}
    	///////////////////
    	pt[i].x = (int)ptX;    
    	pt[i].y = (int)ptY;
    	///////////////////
    }  

}
*/
/////////////////////////////////////
static char FmtStr[] = "% 4u.%.2u  ";
///////////////////////////////////// 
//void CDrObject::SetFormatParam()
void CAxObjMgr::SetFormatParam(UINT nDecPlaces,long lWorldBase)
{

	/////////////////////////////////////////////
	char c0;
	
	c0 = (9 - nDecPlaces) + '0';
	FmtStr[2] = c0;
	
	c0 = nDecPlaces + '0';
	FmtStr[7] = c0;
	////////////////////////////// set format
	m_strFormat = FmtStr;
	/////////////////////
	return;
	
}
////////////////////////////////////////////////////////// Get: Specials
CDrObject* CAxObjMgr::GetSpecObject(int nObjectType)
{

	CDrGrafFrame* pWnd = (CDrGrafFrame*)AfxGetApp()->m_pMainWnd; 
	CDrObject* pObject = NULL;
	//////////////////////////
	switch(nObjectType)
	{
		case BOOLEANS:
			pObject = (CDrObject*)&m_Booleans;
			break;	
		case DATAWINDOW:
		 	pObject = (CDrObject*)&m_DataWindow;
			break;	
		case DRFONT:
			pObject = (CDrObject*)&m_DrFont;
			break;	
		case DRPEN:
			pObject = (CDrObject*)&m_DrPen;
			break;	
		case HITNET:
			pObject = (CDrObject*)&m_HitNet;
			break;	
		case LAYER:
			pObject = (CDrObject*)&m_Layer;
			break;
		////////////////////////////////////////////////		
		case MAPFACTOR:
			pObject = (CDrObject*)&m_MapFactor;
			break;	
		case PRECISION:
			pObject = (CDrObject*)&m_Precision;
			break;	
		case SCALEFACTOR:
		 	pObject = (CDrObject*)&m_ScaleFactor;
			break;	
		case UNIT:
			pObject = (CDrObject*)&m_Unit;
			break;
		////////////////////////////////////////////////		
		case OBJ3DMNU:
			pObject = (CDrObject*)&m_Obj3DMnu;
			break;	
		case PATCHMNU:
			pObject = (CDrObject*)&m_PatchMnu;
			break;	
		////////////////////////////////////////////////		
//		case ELEMINFO:
//			pObject = (CDrObject*)&m_ElemInfo;
//			break;	
		
		default:
			AfxMessageBox(
				"Error:CAxObjMgr::GetSpecials\n Pointer Not Found");
			break;	
	}		 	 
    ///////////////////////////////
	return pObject;
}	
////////////////////////////////////////////////////////// Init : Specials	
void CAxObjMgr::SetMapFactorInfo()
{
	///////////////////////////////////////////////////// Unit
//	char* MapModes[] ={"","MM_TEXT","MM_LOMETRIC","MM_HIMETRIC","MM_LOENGLISH",
//					  "MM_HIENGLISH","MM_TWIPS","MM_ISOMETRIC","MM-ANISOMETRIC"};
/*
	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc);  
	CUnit* pUnit = (CUnit*)pObject->GetUnit();
	UINT nUnitIndex = pUnit->GetUnitIndex(); 
*/
	double MapValues[]={0.,1.0,.1,.01,.01,.001,.000694,1.,1.};
	/////////////////////////////////////////////////////	
	CUnit* pUnit = GetUnit();
	int nUnitIndex = pUnit->GetUnitIndex();
	/////////////////////////////////////////////////////
	int nMapIndex;
	switch(nUnitIndex)
	{
		case 0:
			nMapIndex = MM_HIENGLISH;                
			break;
				
		case 1:				// inches - Fractional	// TEMPORARY later
													// 1/16 or 1/32 etc.
													// Isotropic Mode Needed  
			nMapIndex = MM_HIENGLISH;                
			break;
				
		case 2:				// Feet
			nMapIndex = MM_LOENGLISH;                
			break;
				
		case 3:				// Feet - Fractional	// TEMPORARY later
													// 1/16 or 1/32 etc.
													// Isotropic Mode Needed  
			nMapIndex = MM_LOENGLISH;                
			break;
				
		case 4:				// Miles
			nMapIndex = MM_LOENGLISH;                
			break;	
			
		case 5:				// Millimeters
			nMapIndex = MM_HIMETRIC;                
			break;	
			
		case 6:				// Centimeters
			nMapIndex = MM_LOMETRIC;                
			break;	
			
		case 7: 			// Meters
			nMapIndex = MM_LOMETRIC;                
			break;	
			
		case 8: 			// Kilometers
			nMapIndex = MM_LOMETRIC;                
			break;	
			
	    default:
	        break;
	}
	/////////////////////////////////////////////////////// set Map Index	
	double dMapFactor;
	CMapFactor* pMapFactor = GetMapFactor();
	pMapFactor->SetMapModeIndex(nMapIndex);
	dMapFactor 	= MapValues[nMapIndex];
	pMapFactor->SetMapFactor(dMapFactor);
	///////////////////////////////////////////////
}

void CAxObjMgr::InitMapFactor()
{

	////////////////////////////////////////////////////////
	m_MapFactor.ReadDefaultMapFactor(); 
	m_MapFactor.InitMapFactor();
    ///////////////////////////////
}

void CAxObjMgr::InitPrecision()
{

	////////////////////////////////////////////////////////
	m_Precision.ReadDefaultPrecision(); 
	m_Precision.InitPrecision();
    ///////////////////////////////
    
}

void CAxObjMgr::InitScaleFactor()
{

	////////////////////////////////////////////////////////
	m_ScaleFactor.ReadDefaultScaleFactor(); 
	m_ScaleFactor.InitScaleFactor();
    ///////////////////////////////
	  	
} 

void CAxObjMgr::InitUnit()
{

	////////////////////////////////////////////////////////
	m_Unit.ReadDefaultUnit(); 
	m_Unit.InitUnit();
    ///////////////////////////////
    
}

void CAxObjMgr::InitBooleans()
{ 
											//   Should be read from .Ini file			
	////////////////////////////////////////////////////////
	m_Booleans.ReadDefaultBooleans(); 
	m_Booleans.InitBooleans();
	//////////////////////
}

void CAxObjMgr::InitDataWindow()
{
	////////////////////////////////////////////////////////
	m_DataWindow.ReadDefaultDataWindow(); 
	m_DataWindow.InitDataWindow();
    ///////////////////////////////
}
	
void CAxObjMgr::InitDrFont()
{
	////////////////////////////////////////////////////////
	m_DrFont.ReadDefaultDrFont(); 
	m_DrFont.InitDrFont();
    ///////////////////////////////
}

void CAxObjMgr::InitDrPen()
{
	////////////////////////////////////////////////////////
	m_DrPen.ReadDefaultDrPen(); 
	m_DrPen.InitDrPen();
    ///////////////////////////////
} 

void CAxObjMgr::InitHitNet()
{
	////////////////////////////////////////////////////////
	m_HitNet.ReadDefaultHitNet(); 
	m_HitNet.InitHitNet();
    ///////////////////////////////
}

void CAxObjMgr::InitLayer()
{
	////////////////////////////////////////////////////////
	m_Layer.ReadDefaultLayer(); 
	m_Layer.InitLayer();
    ///////////////////////////////
}
/*
void CAxObjMgr::InitElemInfo()
{
	////////////////////////////////////////////////////////
	m_ElemInfo.ReadDefault(); 
	m_ElemInfo.Init();
    ///////////////////////////////
}
*/
void CAxObjMgr::InitPatchMnu()
{
	////////////////////////////////////////////////////////
	m_PatchMnu.ReadDefaultPatchMnu(); 
	m_PatchMnu.InitPatchMnu();
    ///////////////////////////////
}

void CAxObjMgr::InitObj3DMnu()
{
	////////////////////////////////////////////////////////
	m_Obj3DMnu.ReadDefaultObj3DMnu(); 
	m_Obj3DMnu.InitObj3DMnu();
    ///////////////////////////////
}
///////////////////////////////////////////////////////////// Helpers	
void CAxObjMgr::DStoSC(double* dpt)
{
	/////////////////////////////////////////////////////////
	CScaleFactor* pScaleFactor = (CScaleFactor*)GetSpecObject(SCALEFACTOR);
	/////////////////////////////////////////////////////////
    double dScaleFactor = pScaleFactor->GetScaleFactor();
//    dScaleFactor       *= pDoc->GetMapFactor();
    *dpt = (*dpt) * dScaleFactor;    
    ///////////////////////////////////////////// 
    return;
}    

void CAxObjMgr::SCtoDS(double* dpt)
{
	/////////////////////////////////////////////////////////
	CScaleFactor* pScaleFactor = (CScaleFactor*)GetSpecObject(SCALEFACTOR);
	/////////////////////////////////////////////////////////
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    *dpt = (*dpt) / dScaleFactor;    
    ///////////////////////////////////////////// 
    return;
}    

void CAxObjMgr::DStoSC(int* npt)
{
	/////////////////////////////////////////////////////////
	CScaleFactor* pScaleFactor = (CScaleFactor*)GetSpecObject(SCALEFACTOR);
	/////////////////////////////////////////////////////////
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    *npt = (int)( ((double)(*npt))*dScaleFactor);    
    ///////////////////////////////////////////// 
    return;
}    

void CAxObjMgr::SCtoDS(int* npt)
{
	/////////////////////////////////////////////////////////
	CScaleFactor* pScaleFactor = (CScaleFactor*)GetSpecObject(SCALEFACTOR);
	/////////////////////////////////////////////////////////
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    *npt = (int)( ((double)(*npt))/dScaleFactor);    
    ///////////////////////////////////////////// 
    return;
}    
void CAxObjMgr::DStoSC(LONG* npt)
{
	/////////////////////////////////////////////////////////
	CScaleFactor* pScaleFactor = (CScaleFactor*)GetSpecObject(SCALEFACTOR);
	/////////////////////////////////////////////////////////
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    *npt = (LONG)( ((double)(*npt))*dScaleFactor);    
    ///////////////////////////////////////////// 
    return;
}    

void CAxObjMgr::SCtoDS(LONG* npt)
{
	/////////////////////////////////////////////////////////
	CScaleFactor* pScaleFactor = (CScaleFactor*)GetSpecObject(SCALEFACTOR);
	/////////////////////////////////////////////////////////
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    *npt = (LONG)( ((double)(*npt))/dScaleFactor);    
    ///////////////////////////////////////////// 
    return;
}    

void CAxObjMgr::DStoSC(POINT* pt)
{
	/////////////////////////////////////////////////////////
	CScaleFactor* pScaleFactor = (CScaleFactor*)GetSpecObject(SCALEFACTOR);
	/////////////////////////////////////////////////////////
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    pt->x = (int)( ((double)(pt->x))*dScaleFactor);    
    pt->y = (int)( ((double)(pt->y))*dScaleFactor); 
    ///////////////////////////////////////////// 
    return;
} 
   
void CAxObjMgr::SCtoDS(POINT* pt)
{
	/////////////////////////////////////////////////////////
	CScaleFactor* pScaleFactor = (CScaleFactor*)GetSpecObject(SCALEFACTOR);
	/////////////////////////////////////////////////////////
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    pt->x = (int)( ((double)(pt->x))/dScaleFactor);    
    pt->y = (int)( ((double)(pt->y))/dScaleFactor); 
    ///////////////////////////////////////////// 
    return;
}    

void CAxObjMgr::DStoSC(LPOINT3* pt)
{
	/////////////////////////////////////////////////////////
	CScaleFactor* pScaleFactor = (CScaleFactor*)GetSpecObject(SCALEFACTOR);
	/////////////////////////////////////////////////////////
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    pt->x = (LONG)( ((double)(pt->x))*dScaleFactor);    
    pt->y = (LONG)( ((double)(pt->y))*dScaleFactor); 
    pt->z = (LONG)( ((double)(pt->z))*dScaleFactor); 
    ///////////////////////////////////////////// 
    return;
}    

void CAxObjMgr::SCtoDS(LPOINT3* pt)
{
	/////////////////////////////////////////////////////////
	CScaleFactor* pScaleFactor = (CScaleFactor*)GetSpecObject(SCALEFACTOR);
	/////////////////////////////////////////////////////////
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    pt->x = (LONG)( ((double)(pt->x))/dScaleFactor);    
    pt->y = (LONG)( ((double)(pt->y))/dScaleFactor); 
    pt->z = (LONG)( ((double)(pt->z))/dScaleFactor); 
    ///////////////////////////////////////////// 
    return;
}    


void CAxObjMgr::DStoSC(LPOINT* pt)
{
	/////////////////////////////////////////////////////////
	CScaleFactor* pScaleFactor = (CScaleFactor*)GetSpecObject(SCALEFACTOR);
	/////////////////////////////////////////////////////////
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    pt->x = (LONG)( ((double)(pt->x))*dScaleFactor);    
    pt->y = (LONG)( ((double)(pt->y))*dScaleFactor); 
    ///////////////////////////////////////////// 
    return;
}    
void CAxObjMgr::SCtoDS(LPOINT* pt)
{
	/////////////////////////////////////////////////////////
	CScaleFactor* pScaleFactor = (CScaleFactor*)GetSpecObject(SCALEFACTOR);
	/////////////////////////////////////////////////////////
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    pt->x = (LONG)( ((double)(pt->x))/dScaleFactor);    
    pt->y = (LONG)( ((double)(pt->y))/dScaleFactor); 
    ///////////////////////////////////////////// 
    return;
}    

void CAxObjMgr::DStoSC(RECT* rect)
{
	/////////////////////////////////////////////////////////
	CScaleFactor* pScaleFactor = (CScaleFactor*)GetSpecObject(SCALEFACTOR);
	/////////////////////////////////////////////////////////
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
 //    dScaleFactor       *= pDoc->GetMapFactor();
    rect->left   = (int)( ((double)(rect->left))*dScaleFactor);    
    rect->top    = (int)( ((double)(rect->top))*dScaleFactor); 
    rect->right  = (int)( ((double)(rect->right))*dScaleFactor);    
    rect->bottom = (int)( ((double)(rect->bottom))*dScaleFactor);    
    ///////////////////////////////////////////// 
    return;
}    

void CAxObjMgr::SCtoDS(RECT* rect)
{
	/////////////////////////////////////////////////////////
	CScaleFactor* pScaleFactor = (CScaleFactor*)GetSpecObject(SCALEFACTOR);
	/////////////////////////////////////////////////////////
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    rect->left   = (int)( ((double)(rect->left))/dScaleFactor);    
    rect->top    = (int)( ((double)(rect->top))/dScaleFactor); 
    rect->right  = (int)( ((double)(rect->right))/dScaleFactor);    
    rect->bottom = (int)( ((double)(rect->bottom))/dScaleFactor);    
    ///////////////////////////////////////////// 
    return;
}
   
void CAxObjMgr::DStoSC(LRECT* rect)
{
	/////////////////////////////////////////////////////////
	CScaleFactor* pScaleFactor = (CScaleFactor*)GetSpecObject(SCALEFACTOR);
	/////////////////////////////////////////////////////////
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    rect->left   = (long)( ((double)(rect->left))*dScaleFactor);    
    rect->top    = (long)( ((double)(rect->top))*dScaleFactor); 
    rect->right  = (long)( ((double)(rect->right))*dScaleFactor);    
    rect->bottom = (long)( ((double)(rect->bottom))*dScaleFactor);    
    ///////////////////////////////////////////// 
    return;
}    

void CAxObjMgr::SCtoDS(LRECT* rect)
{
	/////////////////////////////////////////////////////////
	CScaleFactor* pScaleFactor = (CScaleFactor*)GetSpecObject(SCALEFACTOR);
	/////////////////////////////////////////////////////////
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    rect->left   = (long)( ((double)(rect->left))/dScaleFactor);    
    rect->top    = (long)( ((double)(rect->top))/dScaleFactor); 
    rect->right  = (long)( ((double)(rect->right))/dScaleFactor);    
    rect->bottom = (long)( ((double)(rect->bottom))/dScaleFactor);    
    ///////////////////////////////////////////// 
    return;
}    

/////////////////////////////////////////////////////////////////////////////////////////		
// CAxObjMgr serialization

void CAxObjMgr::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////
	WORD w;
	/////// 
	if (ar.IsStoring())
	{
		TRACE(" AxObjMgr		:Storing\n");	// TODO: add storing code here 
	    /////////////////////////////////////////
		ar.Write(&m_bViewChanged, sizeof(BOOL) );
		ar.Write(&m_sizeDoc, sizeof(CSize) );
//		ar.WriteObject(&m_EBoxMgr );
//		ar.WriteObject(&m_DBoxMgr );
//		ar.WriteObject(&m_ObjectList );
		/////////////////////////////////	
		ar  <</*CString*/     m_strFormat;
		for(int i=0;i<MAX_LIST_ARRAY;i++)
		{
			ar<</*UINT*/	(WORD)m_nLastObjectNo[i];		// Master Object Number:to be assigned 
		} 
		ar	<</*UINT*/	(WORD)m_nActiveObjectNo     // Selected Object No
			<</*int*/	(WORD)m_nActiveObjectIndex  // Selected Object Index in List
			<</*int*/	(WORD)m_nActiveObjectType;	// Selected ObjectType;

	}
	else
	{
		TRACE(" AxObjMgr		:Loading\n");	// TODO: add loading code here

	    /////////////////////////////////////////
		ar.Read(&m_bViewChanged, sizeof(BOOL) );
		ar.Read(&m_sizeDoc, sizeof(CSize) );
//		m_pEBoxMgr 		= ((CEBoxMgr*)ar.ReadObject(RUNTIME_CLASS(CEBoxMgr)) );
//		m_pDBoxMgr 		= ((CDBoxMgr*)ar.ReadObject(RUNTIME_CLASS(CDBoxMgr)) );
//		m_pObjectList	= ((CObList*)ar.ReadObject(RUNTIME_CLASS(CObList)) );
		/////////////////////////////////	
		ar  >>/*CString*/     m_strFormat;
		for(int i=0;i<MAX_LIST_ARRAY;i++)
		{
			ar	>>	w;
			m_nLastObjectNo[i] = (UINT)w;		// Object Number:to be assigned to: 
		}
		ar	>>	w;
		m_nActiveObjectNo = (UINT)w;     // Selected Object No
		ar	>>	w;
		m_nActiveObjectIndex = (int)w;  // Selected Object Index in List
		ar	>>	w;
		m_nActiveObjectType = (int)w;	// Selected ObjectType;
		
	} 
	//////////////////////////////////////////// ToolBoxes
//	GetEBoxMgr()->Serialize(ar);
//	GetDBoxMgr()->Serialize(ar);
	//////////////////////////////////////////// Object List
//	GetObjectList()->Serialize(ar);
	/////////////////////////////////		

}
/////////////////////////// End of Module /////////////////
