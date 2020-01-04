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
///////////////////// Mesh
#include "Def_Mesh.h"
///////////////////// ElemObj
#include "Def_Elem.h"
#include "Ext_Elem.h" 
#include "Def_EInf.h"
#include "Ext_EInf.h" 
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
#include "MsObjMgr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CMeshRowHint, CObject)
////////////////////////////////////////////// CDataRowHint class
CMeshRowHint::CMeshRowHint()
{
}
/////////////////////////////////////////////////////////////////////////////
// CGrafObj
IMPLEMENT_SERIAL(CMsObjMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CMsObjMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CMsObjMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
/////////////////////////////////////////////////////////////////////////////
CMsObjMgr::CMsObjMgr()
{
}

CMsObjMgr::~CMsObjMgr()
{
}
/////////////////////////////
void CMsObjMgr::Init()
{
	int i;
	///////////////////////////////// MeshNo
	for(i=0;i<MAX_MESH_ARRAY;i++)
		m_nLastMeshNo[i] 	= 0;
	///////////////
	InitElemInfo();
	///////  		
	return;
}
/////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////// FEMesh
UINT CMsObjMgr::GetLastMeshNo(int nObjectType)
{
	int nMeshIndex =	ObjTypeToMeshIndex(nObjectType);
	//////////////////////////////////////////////////
	return	(nMeshIndex>=0?(m_nLastMeshNo[nMeshIndex]):-1);
}

int	CMsObjMgr::BumpLastMeshNo(int nObjectType)
{
	int nMeshIndex =	ObjTypeToMeshIndex(nObjectType);
	//////////////////////////////////////////////////
	if(nMeshIndex>=0)
	{
		int nLastNo = m_nLastMeshNo[nMeshIndex];
		nLastNo++;
		m_nLastMeshNo[nMeshIndex] = nLastNo;
		///////
		return 0;
	}
	else
		return -1;
}

int CMsObjMgr::ObjTypeToMeshIndex(int nObjectType)
{
	//////////////////
	switch (nObjectType)
	{

//	LastAssigned = 54
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
		case MESH1D:		return 6;
		case MESH2D:		return 7;
		case MESH3D:		return 8;
		case FE0D:			return 4;			
		case FE1D:			return 5;			
		case FE2D:			return 45;			
		case FE3D:			return 46;			
		case M1_PROFILE:	return 52;			
		case M2_PROFILE:	return 53;			
		case M3_PROFILE:	return 54;			
		/////////////////////////////// 0D	
		case NODE:			return 0;
		case INODE:			return 0;
		case CNODE:			return 1;
		case MNODE:			return 2;
		case MCNODE:		return 51;
		/////////////////////////////// 1D	
		case TRUSS:			return 3;
		case PIPE:			return 17;
		case ELBOW:			return 18;
		case BEAM:			return 19;
		/////////////////////////////// 2D	
		case QU_4:			return 20;
		case QU_8:			return 21;
		case QU_9:			return 22;
		case QU_12:			return 23;
		case QU_16:			return 24;
		///
		case TR_3:			return 25;
		case TR_6:			return 26;
		case TR_9:			return 27;
		case TR_10:			return 28;
		/////////////////////////////// 3D
		///////////////////////////////////////////////// ElemInfo	
		case PROP_BALL:		return 44;	
		/// 1D
		case PROP_PIPE:		return 29;
		case PROP_ELBOW:	return 30;
		case PROP_BEAM:		return 31;
		case PROP_TRUSS:	return 32;
		/// 2D
		case PROP_2D:		return 33;
		/// 3D
		case PROP_3D:		return 34;
		///////////////////////////////////// Mat
		/// 0D
		case MAT_BALL:		return 35;	
		/// 1D
		case MAT_PIPE:		return 36;	
		case MAT_ELBOW:		return 37;	
		case MAT_BEAM:		return 38;	
		case MAT_TRUSS:		return 39;	
		/// 2D
		case MAT_2D:		return 40;
		/// 3D
		case MAT_3D:		return 41;
		///////////////////////////////////// Release
		case RELEASE:		return 42;
		///////////////////////////////////// STRESSINDEX
		case SINDEX:		return 43;
		///////////////////////////////////////////////// DrawObjs	
		case LABEL:			return 9;
		case FREEHAND:		return 10;
		case GRID:			return 11;
		//////////////////////////////
		case GREF_VRTX:		return 47;        
		case GREF_EDGE:		return 48;        
		case GREF_FACE:		return 49;        
		case GREF_CUBE:		return 50;        
		//////////////////////////////
		default:			return -1;			   
		//////////////////////////////
	}
}

int CMsObjMgr::MeshIndexToObjType(int nIndex)
{
	//////////////////
 
//	LastAssigned = 54
	//////////////////
	switch (nIndex)
	{
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
		case 6:			return MESH1D;
		case 7:			return MESH2D;
		case 8:			return MESH3D;
		case 4:			return FE0D;			
		case 5:			return FE1D;			
		case 45:		return FE2D;			
		case 46:		return FE3D;			
		case 52:		return M1_PROFILE;        
		case 53:		return M2_PROFILE;        
		case 54:		return M3_PROFILE;        
		/////////////////////////////// 0D	
		case 0:			return NODE;
//		case 0:			return INODE;
		case 1:			return CNODE;
		case 2:			return MNODE;
		case 51:		return MCNODE;
		/////////////////////////////// 1D	
		case 3:			return TRUSS;
		case 17:		return PIPE;
		case 18:		return ELBOW;
		case 19:		return BEAM;
		/////////////////////////////// 2D	
		case 20:		return QU_4;
		case 21:		return QU_8;
		case 22:		return QU_9;
		case 23:		return QU_12;
		case 24:		return QU_16;
		///
		case 25:		return TR_3;
		case 26:		return TR_6;
		case 27:		return TR_9;
		case 28:		return TR_10;
		/////////////////////////////// 3D	
		///////////////////////////////////////////////// ElemInfo	
		case 44:		return PROP_BALL;	
		/// 1D
		case 29:		return PROP_PIPE;
		case 30:		return PROP_ELBOW;
		case 31:		return PROP_BEAM;
		case 32:		return PROP_TRUSS;
		/// 2D
		case 33:		return PROP_2D;
		/// 3D
		case 34:		return PROP_3D;
		///////////////////////////////////// Mat
		/// 0D
		case 35:		return MAT_BALL;	
		/// 1D
		case 36:		return MAT_PIPE;	
		case 37:		return MAT_ELBOW;	
		case 38:		return MAT_BEAM;	
		case 39:		return MAT_TRUSS;	
		/// 2D
		case 40:		return MAT_2D;
		/// 3D
		case 41:		return MAT_3D;
		///////////////////////////////////// Release
		case 42:		return RELEASE;
		///////////////////////////////////// StressIndex
		case 43:		return SINDEX;
		///////////////////////////////////////////////// DrawObjs	
		case 9:			return LABEL;
		case 10:		return FREEHAND;
		case 11:		return GRID;
		//////////////////////////////
		case 47:		return GREF_VRTX;        
		case 48:		return GREF_EDGE;        
		case 49:		return GREF_FACE;        
		case 50:		return GREF_CUBE;        
		//////////////////////////////
		default:		return NONE;			   
		//////////////////////////////
	}
}

////////////////////////////////////////////////////////////////////////////// DataBase
CDrObject* CMsObjMgr::AddToDataBase(CString& ObjID,int& nActiveIndex,int nObjType)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 			= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjMgr			= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 		= pObjMgr->GetObjectList(nObjType);
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

CDrObject* CMsObjMgr::AddToDataBase(int& nActiveIndex,int nObjType)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 			= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjMgr			= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 		= pObjMgr->GetObjectList(nObjType);
	/////////////////////////////////////////////
    CNewObjs NewObjs;
    CDrObject* pAddObject 	= NewObjs.NewObject(nObjType);
	if(!pAddObject)
		return (CDrObject*)NULL;
	///////////////////////////////////////////////
  	pDListMgr->InsertObject(pAddObject);          				// add 
   	pAddObject->SetObjectNo(pObjMgr->GetLastObjectNo(nObjType));
	pObjMgr->BumpLastObjectNo(nObjType);                         // bump it
	///////////////////////////////////////////////////////////////////////////
	pDoc->SetModifiedFlag();                   					// document modified 
	////////////////////////////////////////////////////////////////////////////////													    
	nActiveIndex = pObjMgr->GetObjectCount(nObjType) - 1;
	pObjMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
	pObjMgr->SetActiveObjectType(nObjType);		    // set Active ObjectType									
	//////////////////////////////////////////////////////////////////////////////// DataView
	AddToRowList( nActiveIndex, nObjType);                         //
	int nRowIndex;
	ObjIndexToRowIndex(nRowIndex, nActiveIndex, nObjType);
	SetActiveRowIndex( nRowIndex);          //
	//////////////////////////////////////////////////////////
	return pAddObject;
}

int CMsObjMgr::DeleteFromDataBase(int nObjIndex, int nObjType)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 			= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjMgr			= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 		= pObjMgr->GetObjectList(nObjType);
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
void CMsObjMgr::Do_Object_Dialog(int nActiveObjectType)
{ 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 			= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjMgr			= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 		= pObjMgr->GetObjectList(nActiveObjectType);
	////////////////////
	int nActiveObjIndex = pObjMgr->GetActiveObjectIndex();		 // Get Index
	CDrObject* pObject = (CDrObject*)pDListMgr->GetObject(nActiveObjIndex);
    ////////////////////////// Draw Elem Data
	pObject->DealObjectDialog();
	//////////////////////////   	
	
} 

//void CDrObject::Do_Object_DataView(CDC* PtrDC,int y,int nRowIndex)
void CMsObjMgr::Do_Object_DataView(CDC* PtrDC,int y,int nRowIndex)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 			= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjMgr			= pDoc->GetObjectMgr();
	//////////////////////////////////////////////
	int		nObjIndex;
	int		nObjType;
	/////////////////
	RowIndexToObjIndex(nRowIndex, nObjIndex, nObjType);
	///////////////////////   
	CDListMgr*	pDListMgr		= pObjMgr->GetObjectList(nObjType);
	CDrObject* pObject = (CDrObject*)pDListMgr->GetObject(nObjIndex);
    ////////////////////////// Draw Elem Data
	if(pObject)
		pObject->DoDataView(PtrDC,y);
	//////////////////////////   	
	
} 
////////////////////////////////////////////////////////// Data/Card View
void CMsObjMgr::ChangeSelectionNextObjectIndex(BOOL bNext)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 			= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjMgr			= pDoc->GetObjectMgr();
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
	pObjMgr->SetActiveObjectIndex(nObjIndex);
	pObjMgr->SetActiveObjectType(nObjType);
	//////////////////////////////////////////////
//	SetActiveObjectIndex(nNewActiveObjectIndex);
	UpdateAllViewsWithActiveIndex(NULL,nObjIndex,nObjType);
}

void CMsObjMgr::ChangeSelectionToObjectIndex(UINT nNewActiveRowIndex)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 			= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjMgr			= pDoc->GetObjectMgr();
	//////////////////////////////////////////////
	int	nObjIndex;
	int	nObjType;
	/////////////////
	RowIndexToObjIndex(nNewActiveRowIndex, nObjIndex, nObjType);
	pObjMgr->SetActiveObjectIndex(nObjIndex);
	pObjMgr->SetActiveObjectType(nObjType);
	//////////////////////////////////////////////
//	SetActiveObjectIndex(nNewActiveObjectIndex);
	UpdateAllViewsWithActiveIndex(NULL,nObjIndex,nObjType);
}


//void CDrObject::UpdateAllViewsWithActiveIndex(CView* pSourceView,
//													UINT nActiveIndex)
void CMsObjMgr::UpdateAllViewsWithActiveIndex(CView* pSourceView,
													UINT nActiveIndex, int nActiveObjType)
{ 

//	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc);
	CDrGrafDoc* pDoc 			= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjMgr			= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 		= pObjMgr->GetObjectList(nActiveObjType);
	/////////////////// get ObjectType for view 
	CDrObject* pObject = (CDrObject*)pDListMgr->GetObject(nActiveIndex);
//    int nType = pObject->GetObjectType();
    ///////////////////////////////////// set SceneChanged
    pObjMgr->SetSceneChanged(TRUE);
    //////////////////////
	CMeshRowHint hint;
//	pDoc->UpdateAllViews(pSourceView, MAKELONG(nActiveIndex,nType), &hint);
	pDoc->UpdateAllViews(pSourceView, MAKELONG(nActiveIndex,nActiveObjType), &hint);
	/////////////////////
} 

int	CMsObjMgr::AddToRowList(int& nObjIndex, int& nObjType)
{
	long CurrentIndexType = MAKELONG(nObjIndex,nObjType);
	//////////////////////////////////////////
	GetRowList()->AddTail(CurrentIndexType);
	////////////
	return 0;
}
	
int CMsObjMgr::DeleteFromRowList(int& nRowIndex)
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
	
int CMsObjMgr::ObjIndexToRowIndex(int& nRowIndex, int& nObjIndex, int& nObjType)
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

int CMsObjMgr::RowIndexToObjIndex(int nRowIndex, int& nObjIndex, int& nObjType)
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
///////////////////////////////////////////////////////////////////// Helper
////////////////////////////////////////////////////////// Get: Specials
CDrObject* CMsObjMgr::GetSpecObject(int nObjectType)
{

	CDrGrafFrame* pWnd = (CDrGrafFrame*)AfxGetApp()->m_pMainWnd; 
	CDrObject* pObject = NULL;
	//////////////////////////
	switch(nObjectType)
	{
		////////////////////////////////////////////////		
		case ELEMINFO:
			pObject = (CDrObject*)&m_ElemInfo;
			break;	
		
		default:
			AfxMessageBox(
				"Error:CMsObjMgr::GetSpecials\n Pointer Not Found");
			break;	
	}		 	 
    ///////////////////////////////
	return pObject;
}	

void CMsObjMgr::InitElemInfo()
{
	////////////////////////////////////////////////////////
	m_ElemInfo.ReadDefault(); 
	m_ElemInfo.Init();
    ///////////////////////////////
}

int CMsObjMgr::SetElemInfoID(CString& ObjID,UINT nObjType)		
{
	///////////////////////////////////////////////////////// 
	char buf[50];
	/////////////////////////////
	BumpLastMeshNo(nObjType);					// bump it
    int nLastNum	= GetLastMeshNo(nObjType);		// internal
	sprintf(buf,"%d",nLastNum);
	ObjID	= "";
	ObjID	+= buf;
	///
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////		
// CMsObjMgr serialization

void CMsObjMgr::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" MeshMgr		:Storing\n");	// TODO: add storing code here 
	    /////////////////////////////////////////

	}
	else
	{
		TRACE(" MeshMgr		:Loading\n");	// TODO: add loading code here
	    /////////////////////////////////////////
		
	} 

}
/////////////////////////// End of Module /////////////////
