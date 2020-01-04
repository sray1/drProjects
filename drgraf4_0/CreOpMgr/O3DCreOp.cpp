// Mouse.cpp : implementation file
//


#include "stdafx.h" 
#include <math.h>
#include <float.h>		// DBL_MIN

#include "3DMath.h"
#include "XForm.h"
/////////////////////
#include "drgraf.h"
#include "drgrafrm.h"
#include "UserMsg.h"
#include "drawView.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "DListMgr.h"
/////////////////////
#include "Def_IGen.h"                    
#include "Def_Elem.h"                    
///////////////////// dialogMgr
#include "MNodMgr.h"  
////////////////////// 
#include "MI_OSPN.h" 
#include "Dlg_CrOI.h"
//////////////////////
#include "O3DCreOp.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
///////////////////////////////////////////////////////////////////////////////////////////
// if NODE_SPAWN: Object Grab Node Same As Node
//////////////////////////////////////////////
#define MAX_INFO_XLATE		3	// 1 Object/1 Object Grab Node/1 Node        
#define MAX_INFO_ROTATE		6	// 1 Object/1 Object Grab Node/2 Nodes( for Axis)           
#define MAX_INFO_SCALE		2	// 1 Object/1 Object Grab Node/None but 3 Coords(from Dlg)           
#define MAX_INFO_REFLECT	4	// 1 Object/1 Object Grab Node/	3 Nodes ( defining Plane or
								//			1 Node on Plane + 2 Nodes for Normal        
#define MAX_INFO_SHEAR		2	// 1 Object/1 Object Grab Node/None but 3 Coords(from Dlg) 
#define MAX_INFO_SPAWN		0	// 1 Object   
///////////////////////////////////////////////////////////////////////////////////////////      
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CO3DCreOp,CSolCreOp,1)
/////////////////////////////////////////////////////////////////////////////
CO3DCreOp::CO3DCreOp()
{
	m_bDoModalDone = FALSE;
}

CO3DCreOp::~CO3DCreOp()
{
}

void CO3DCreOp::Init_O3D()
{
	Init_NOD();
	//////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////
	char buf[50];
    m_LastNum		= pObjectMgr->GetLastInputNo(OBJ3D);		// internal
	sprintf(buf,"%d",m_LastNum);
	m_SpawnedID	= "";
	m_SpawnedID	+= buf;
	pObjectMgr->BumpLastInputNo(OBJ3D);		// bump it
	/////////////////////////////////////////// Node
	m_pSpawnedObj3D		= NULL;
	m_pParentObj3D		= NULL;
	m_ParentID			= "";
	m_pCurrentObj3D		= NULL;
	/////////////////////////////////////////// Dlg_CrOI 
	m_NID				= m_ParentID;

}

void CO3DCreOp::Terminate_O3D(BOOL bError)
{
	Terminate_NOD(bError);
	////
	if(bError)
	{
		/////////////////////////////////////////// 
		if(m_pSpawnedObj3D)
		{
			delete m_pSpawnedObj3D;
			m_pSpawnedObj3D = NULL;
		}
		///////////////////////////
	}
}

void CO3DCreOp:: ElementLeftDown_O3D()
{	
	ElementLeftDown_NOD();
}

void CO3DCreOp::OnEBoxLButtonDown_O3D(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point)
{
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
	/////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	CDListMgr* pDListMgr;
	/////////////////////////////////// 
   	m_bDragOn 		= pBool->IsDragOn();
	m_bDialogOn		= pBool->IsDialogOn();
	m_bAutoAcceptOn	= pBool->IsAutoAcceptOn();
	if(m_bDone)			// Reset
		m_nInfoDone		= 0;
	//////////////////////////////////////////////////
	m_nActiveObject = pWnd->GetActiveObjectType(); 
	m_nActiveTool	= pWnd->GetActiveToolType();    // -1= INSERT
	/////////////////////////////////////////////////////////////////////////
	pObjectMgr->SetActiveObjectType(m_nActiveObject);       // Set ObjectType 
	////////////////////////////////////////////////// No Obj3D
	pDListMgr 	= pObjectMgr->GetObjectList(OBJ3D);
	if(pDListMgr->GetCount()<=0)
		return;
	//////////////////////////
    if(m_Gener == FORWARD)
		ElementLeftDown_O3D();
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftDown_I();
	//////////////////////////////////
}

int CO3DCreOp::LeftUp_GetObj3D_Parent(POINT point)
{
	int nResult;
	///////////////////////////////////////////// See if any Existing Node Hit
	nResult = LeftUp_Obj3D_Accept(point);	// TRUE = Parent
	///////////////////
	if(nResult < 0)
		return nResult; // Cancel or No Hit
	///////
	if(nResult>=0)	// Hit
	{
		switch(m_nInfoDone)
		{
			case 0:	// 
				m_pParentObj3D	= m_pCurrentObj3D;
				m_ParentID		= m_pParentObj3D->GetObjectID();
				break;
			default:
				return -1;
		}
	}
	//////////////////////////////////////
	return 0;
}

int CO3DCreOp::LeftUp_TRANSLATE_O3D(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Obj3D	
			nResult = LeftUp_GetObj3D_Parent(point);
			if(nResult<0)
				return nResult;
			return 0;
		case 1://	Grab Node	
		case 2://	To Node
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_XLATE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_XLATE(point,FALSE);	// try INODE
			if(nResult < 0)
				return nResult;
			//
			return 0;
			////////
		default:
			break;
	}
	return -1;
}

int CO3DCreOp::LeftUp_ROTATE_O3D(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Obj3D	
			nResult = LeftUp_GetObj3D_Parent(point);
			if(nResult<0)
				return nResult;
			return 0;
		case 1://	Grab Node	
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);		// try INODE
			if(nResult < 0)
				return nResult;
			//
			return 0;
			////////
		case 2://		// From Rot Direction if Not AngleIn: Reference
			if(m_bAngleIn)
				return -1;
			//////////////
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);		// try INODE
			if(nResult < 0)
				return nResult;
			//
			return 0;
			////////
		case 3://		// To Rot Direction
			if(m_bAngleIn)
				return -1;
			//////////////
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);		// try INODE
			if(nResult < 0)
				return nResult;
			//
			return 0;
			////////
		case 4://		// From Rot Direction if Not AngleIn
			if(m_bAngleIn)
				return -1;
			//////////////
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);	// try INODE
			if(nResult < 0)
				return nResult;
			//
			return 0;
			////////
		case 5://		// To Rot Direction
			if(m_bAngleIn)
				return -1;
			//////////////
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);		// try INODE
			if(nResult < 0)
				return nResult;
			//
			return 0;
			////////
		default:
			break;
	}
	return -1;
}

int CO3DCreOp::LeftUp_SCALE_O3D(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Obj3D	
			nResult = LeftUp_GetObj3D_Parent(point);
			if(nResult<0)
				return nResult;
			return 0;
		case 1://	Grab Node	
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_SCALE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_SCALE(point,FALSE);	// try INODE
			if(nResult < 0)
				return nResult;
			//
			return 0;
		case 2:		// Force Dialog entry
			return -2;
		default:
			break;
	}
	return -1;
}

int CO3DCreOp::LeftUp_REFLECT_O3D(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Obj3D	
			nResult = LeftUp_GetObj3D_Parent(point);
			if(nResult<0)
				return nResult;
			return 0;
		case 1://	Ist Pt. or Node On Plane	
		case 2://	2nd Pt. or Node On Plane OR Ist Pt. on Normal	
		case 3://	Pt. or Node On Plane OR 2nd Pt. on Normal	
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_REFLECT(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_REFLECT(point,FALSE);		// try INODE
			if(nResult < 0)
				return nResult;
			//
			return 0;
			////////
		default:
			break;
	}
	return -1;
}

int CO3DCreOp::LeftUp_SHEAR_O3D(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Obj3D	
			nResult = LeftUp_GetObj3D_Parent(point);
			if(nResult<0)
				return nResult;
			return 0;
		case 1://	Grab Node	
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_SHEAR(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_SHEAR(point,FALSE);	// try INODE
			if(nResult < 0)
				return nResult;
			//
			return 0;
			////////
		case 2:		// Force Dialog entry
			return -2;
		default:
			break;
	}
	return -1;
}

void CO3DCreOp::ElementLeftUp_O3D(CPoint point)
{                          

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	//////////////////////////////////////////////////////////////////
//	char buf[20];
	CString Nid;
	BOOL bRightOn = FALSE;
	m_bStitch		= FALSE;
	///////////////////
	switch(m_nActiveTool) 
	{
		///////////////////////////////////////////////////// Obj3Des Insert
		case COP_TRANSLATE:

			if(m_nInfoDone > MAX_INFO_XLATE)
				return;
			////////////////
			UpdateDlg_TRUE_XLATE();
			//////////////////
			if(!(m_bDirect && m_bDominant) )
			{
				if(LeftUp_TRANSLATE_O3D(point)<0)
				{
					Terminate_O3D(TRUE);
					return;
				}
			}
			/////////////
			m_nInfoDone++;
			UpdateDlg_FALSE_XLATE();
			///////
			return;

		case COP_ROTATE: 

			if(m_bAngleIn)
			{
				if(m_nInfoDone > 2)
					return;
			}
			else
			{
				if(m_nInfoDone > MAX_INFO_ROTATE)
					return;
			}
			////////////////
			UpdateDlg_TRUE_ROTATE();
			//////////////////
			if(!(m_bDirect && m_bDominant) )
			{
				if(LeftUp_ROTATE_O3D(point)<0)
				{
					Terminate_O3D(TRUE);
					return;
				}
			}
			/////////////
			m_nInfoDone++;
			UpdateDlg_FALSE_ROTATE();
			///////
			return;

		case COP_SCALE: 

			if(m_nInfoDone > MAX_INFO_SCALE)
				return;
			////////////////
			UpdateDlg_TRUE_SCALE();
			//////////////////
			if(!(m_bDirect && m_bDominant) )
			{
				if(LeftUp_SCALE_O3D(point)<0)
				{
					Terminate_O3D(TRUE);
					return;
				}
			}
			/////////////
			m_nInfoDone++;
			UpdateDlg_FALSE_SCALE();
			///////
			return;

		case COP_REFLECT: 

			if(m_nInfoDone > MAX_INFO_REFLECT)
				return;
			////////////////
			UpdateDlg_TRUE_REFLECT();
			//////////////////
			if(!(m_bDirect && m_bDominant) )
			{
				if(LeftUp_REFLECT_O3D(point)<0)
				{
					Terminate_O3D(TRUE);
					return;
				}
			}
			/////////////
			m_nInfoDone++;
			UpdateDlg_FALSE_REFLECT();
			///////
			return;

		case COP_SHEAR:

			if(m_nInfoDone > MAX_INFO_SHEAR)
				return;
			////////////////
			UpdateDlg_TRUE_SHEAR();
			//////////////////
			if(!(m_bDirect && m_bDominant) )
			{
				if(LeftUp_SHEAR_O3D(point)<0)
				{
					Terminate_O3D(TRUE);
					return;
				}
			}
			/////////////
			m_nInfoDone++;
				UpdateDlg_FALSE_SHEAR();
				///////
				return;
		////////////////////////////////////////////////// SPAWN	
		case COP_SPAWN:				// 

			if(m_nInfoDone > MAX_INFO_SPAWN)
				return;
			////////////////
			if(LeftUp_OSPAWN(point)<0)
			////////////////
			{
				Terminate_O3D(TRUE);
				return;
			}
			/////////////
			m_nInfoDone++;
			///////
			return;
		////////////////////////////////////////////////// STITCH	
		case COP_STITCH:				// 

			m_bStitch		= TRUE;
			///////		
//			LeftUp_NSTITCH(point);
			return;
		//////////////////////////////////////////////////
		default:  
			return;
	} 
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	j = sprintf(buf,"***** Please Note ****\n");
	j += sprintf(buf+j,"If you are trying to Hit an Object or\n");
	j += sprintf(buf+j,"Click in for Coordinates, UnCheck\n");
	j += sprintf(buf+j,"the Dominant Button in the Dialog Box\n");
	//////
	AfxMessageBox(*str);
	delete str;
	///////////
	m_nInfoDone--;
}	

int CO3DCreOp::LeftUp_Obj3D_Accept(CPoint point)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(OBJ3D);
	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrObj3D*	pDrObj3D;
	int			nActiveIndex,index;
	////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	WORtoWOP(&dTol,&dTol);	// physical
	///////////////////////////////////////////// See if any Existing Obj3D Hit
	index = IsObjectHit(OBJ3D,point,0);
	////////////////////////////////////////////////////
	if(index<0)
		return -1; // No Obj3D Hit
	//////////////////////////////////////////////////////////////// Existing Obj3D
	pDrObj3D	= (CDrObj3D*)pDListMgr->GetObject(index);
	ID			= pDrObj3D->GetObjectID();
	/////////////////////////////////////////
	pList = pObjectMgr->GetObjectList(OBJ3D);
	nActiveIndex = pList->GetObjectIndex(OBJ3D, ID);;
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
	pObjectMgr->SetActiveObjectType(OBJ3D);		    // set Active Type									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,OBJ3D);
	//////////////////////////////////////////////////////////////// MultipleSearch
	int startIndex = index+1;
	int nResult;
	/////////////////////////
	if(!m_bAutoAcceptOn)
	{
		/////////////
		for(;;)
		{
			//////////////////////////////
//			nResult = ShowParentObj3DInfo(pDrObj3D);
			nResult = ShowParentObj3DInfo(pDrObj3D);
			/////////////
			if(nResult == IDYES)
				//////////////////////////////////////////////////////// Accept Old
				break;
			else
			if(nResult == IDNO)
			{
				//////////////////////////////////////////////////////// Retry
				index = IsObjectHit(OBJ3D,point,startIndex);
				if(index>=0)
				{
					pDrObj3D	= (CDrObj3D*)pDListMgr->GetObject(index);
					ID		= pDrObj3D->GetObjectID();
					///////////////////////////////////////// 
					pList = pObjectMgr->GetObjectList(OBJ3D);
					nActiveIndex = pList->GetObjectIndex(OBJ3D, ID);;
					pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
					pObjectMgr->SetActiveObjectType(OBJ3D);		    // set Active Index									
					pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,OBJ3D);
					////////////////////////////////////////
					startIndex  = index+1;
					/////////////////////
				}
				else
					////////////////
					return -2;
				/////////
			}
			else				// Cancel
				//////////////////////////////////////////////////////// Do Nothing
				return -2;
		}						// end for loop
		///////////////////////////////////////
	}				// end !AutoAccept loop
	//////////////////////////////////////////////////////////////////// finally, accept
	m_pCurrentObj3D = pDrObj3D;
	/////////
	return 0;
	/////////
}

int CO3DCreOp::LeftUp_OSPAWN(CPoint point)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Obj3D	
			nResult = LeftUp_GetObj3D_Parent(point);
			if(nResult<0)
				return nResult;
			///////////////////
			strCurr = "Ready with other Info.?@Click Right Button";
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
			///
			return 0;
			////////
		default:
			break;
	}
	return -1;
}

int CO3DCreOp::ShowParentObj3DInfo(CDrObj3D* pDrObj3D)
{
	int nResult;
	CString ID;
	CString* pID = &ID;
	ID = pDrObj3D->GetObjectID();
	//////////////////////////////////////////////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	//////
	j = sprintf(buf,"***** A SubStructure_To_Spawn_From Hit ****\n");
	//////////////////////////////////////////////////// Show Obj3D
	j += sprintf(buf+j,"\nContains:\n");
	j += sprintf(buf+j,"\tNo. of SubStructure\t = %d\n",pDrObj3D->GetObj3DList()->GetCount());
	j += sprintf(buf+j,"\tNo. of Solids\t\t = %d\n",pDrObj3D->GetSolidList()->GetCount());
	j += sprintf(buf+j,"\tNo. of Patches\t\t = %d\n",pDrObj3D->GetPatchList()->GetCount());
	j += sprintf(buf+j,"\tNo. of Curves\t\t = %d\n",pDrObj3D->GetCurveList()->GetCount());
	j += sprintf(buf+j,"\tNo. of Nodes\t\t = %d\n",pDrObj3D->GetNodeList()->GetCount());
	////////////////////////////
	j += sprintf(buf+j,
		"\nYES:\t\tSpawn This SubStructure");
	j += sprintf(buf+j,
		"\nNO:\t\tFind Next SubStructure with Intersecting Trace");
	j += sprintf(buf+j,
		"\nCANCEL:\t\tCancel Selection Process");
	nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
	///////////////
	delete str;
	return nResult;
}

int CO3DCreOp::ShowObj3DToSpawn(CDrObj3D* pParentObj3D,BOOL bUsingDlg)
{
	int nResult = 0;
	////////////////
	C3DMath			Math3D;
	///////////////////////
	CDrGrafFrame*	pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString			strCurr;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
    /////////////////////////////////////////////////////////////////////////// NO New Object
	if(!pBool->IsSpawnOn())
	{
		/////////////////////////////////////////////////////////// XForm : Prep
		m_NDoneList.RemoveAll();
		m_CDoneList.RemoveAll();
		m_PDoneList.RemoveAll();
		m_SDoneList.RemoveAll();
		m_ODoneList.RemoveAll();
		////////////////////////
		nResult = ShowObj3DToSpawnCopyOff(pParentObj3D,bUsingDlg);
		return nResult;
	}
	////////////////////////////////
	strCurr = "Please Wait";
	///////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	///////////////////
	pObjectMgr->SetActiveObjectType(OBJ3D);
	////////////////////////////////////////////////////////////////////////////// Add to DataBase
	int nActiveIndex;
	///////////////
	m_pSpawnedObj3D	= (CDrObj3D*)(pObjectMgr->AddToDataBase(nActiveIndex,OBJ3D));
	///
	m_pSpawnedObj3D->SetShow(FALSE);	// not quite ready
	/////////////////////////////////////////////////////////////// Using CMI_CSPN
	CMI_OSPN MI_OSPN;
	if(bUsingDlg)
	{
		m_pSpawnedObj3D->SetObjectID(m_ObjID);
		///
		nResult = MI_OSPN.SpawnObj3DShowingDlg(m_pSpawnedObj3D,pParentObj3D,pParentObj3D,OBJ3D);
	}
	else
	{
		pMATRIX	pXFMat	= m_pMatObj->GetMatrix();
		CString	SpawnID	= m_ObjID;
		////
		nResult = MI_OSPN.SpawnObj3DWithoutDlg(m_pSpawnedObj3D,pParentObj3D,pXFMat,&m_SpawnedID,
												pParentObj3D,OBJ3D); 
	}
	if(nResult<0)
	{
		/////////////////////////////////////// Reset
		m_nInfoDone		= 0;
		m_bDone			= TRUE;	// 
		////////////////////////// Delete
		pObjectMgr->DeleteFromDataBase(nActiveIndex, OBJ3D);
		m_pSpawnedObj3D	= NULL;
		//////////////////////////
		return nResult;//
	}
	////////////////////////////////////////////////////////// Save
	pObjectMgr->ShowObject_On_Off(pParentObj3D,OBJ3D,TRUE);
	///////////////////////////////
	return 0;
}	 

int CO3DCreOp::ShowObj3DToSpawnCopyOff(CDrObj3D* pParentObj3D,BOOL bUsingDlg)
{
	int	nResult;
	int index;
	///////////////////////
	CDrGrafFrame*	pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString			strCurr;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	////////////////////////////////
	strCurr = "Please Wait";
	///////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	///////////////////
	pObjectMgr->SetActiveObjectType(OBJ3D);
	//////////////////////////////////////////////
	if(!(pParentObj3D->GetObj3DList())->IsEmpty())
	{
		/////////////////////////////////////////////////////////// XForm Obj3D-dependent OBJ3DS
		nResult = Obj3DDependent_SpawnConnectedObjects_CopyOff(pParentObj3D,bUsingDlg,OBJ3D);
		///
		if(nResult == -1)
			goto ERRORHANDLER;
		/////////////////////
	}
	///////////////////////////////////////////////// XForm Current Obj3D, if not done yet
	index = m_ODoneList.GetObjectIndex(pParentObj3D);
	if(index<0)	// not done yet
	{
		pObjectMgr->ShowObject_On_Off(pParentObj3D,OBJ3D,FALSE);
		/////////////////////////////////////////////////////////// XForm Current Obj3D
		nResult = Obj3DSpawnCopyOff(pParentObj3D,bUsingDlg);
		///
		if(nResult == -1)
			goto ERRORHANDLER;
		/////////////////////
		m_ODoneList.InsertObject(pParentObj3D);
	}
	/////////////////////////////////////////////////////////////// walk downward to go upward
	//																from Curve
	if(!(pParentObj3D->GetCurveList())->IsEmpty())
	{
		CDListMgr* pList = pParentObj3D->GetCurveList();
		int nMax = pList->GetCount();
		for(int i=0;i<nMax;i++)
		{
			CDrCurve* pParentCurve = (CDrCurve*)(pList->GetObject(i));
#ifdef _DEBUG
		CString ObjID = pParentCurve->GetObjectID();
#endif
			/////////////////////////////////////////////////////////// XForm Current Curve
			nResult = ShowCurveToSpawnCopyOff(pParentCurve,bUsingDlg);
			///
			if(nResult == -1)
				goto ERRORHANDLER;
			/////////////////////
		}
	}
	/////////////////////////////////////////////////////////////// walk downward to go upward
	//																from Patch
	if(!(pParentObj3D->GetPatchList())->IsEmpty())
	{
		CDListMgr* pList = pParentObj3D->GetPatchList();
		int nMax = pList->GetCount();
		for(int i=0;i<nMax;i++)
		{
			CDrPatch* pParentPatch = (CDrPatch*)(pList->GetObject(i));
#ifdef _DEBUG
		CString ObjID = pParentPatch->GetObjectID();
#endif
			/////////////////////////////////////////////////////////// XForm Current Curve
			nResult = ShowPatchToSpawnCopyOff(pParentPatch,bUsingDlg);
			///
			if(nResult == -1)
				goto ERRORHANDLER;
			/////////////////////
		}
	}
	/////////////////////////////////////////////////////////////// walk downward to go upward
	//																from Patch
	if(!(pParentObj3D->GetSolidList())->IsEmpty())
	{
		CDListMgr* pList = pParentObj3D->GetSolidList();
		int nMax = pList->GetCount();
		for(int i=0;i<nMax;i++)
		{
			CDrSolid* pParentSolid = (CDrSolid*)(pList->GetObject(i));
#ifdef _DEBUG
		CString ObjID = pParentSolid->GetObjectID();
#endif
			/////////////////////////////////////////////////////////// XForm Current Curve
			nResult = ShowSolidToSpawnCopyOff(pParentSolid,bUsingDlg);
			///
			if(nResult == -1)
				goto ERRORHANDLER;
			/////////////////////
		}
	}
	///////////////////////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(pParentObj3D,OBJ3D,TRUE);
	///////////////////////////
	if(!bUsingDlg && m_pMatObj)
	{	
		delete m_pMatObj;	
		m_pMatObj = NULL;
	}
	///////////////////////////////
	return 0;

ERRORHANDLER:
	AfxMessageBox("Internal ERROR\nCCurPatOp::ShowPatchToSpawnCopyOff");
	/////////////////////////////////////// Reset
	m_nInfoDone		= 0;
	m_bDone			= TRUE;	// 
	//////////////////////////
	m_pSpawnedNode	= NULL;
	//////////////////////////
	return nResult;//
	////////
}
	 
int CO3DCreOp::Obj3DDependent_SpawnConnectedObjects_CopyOff(CDrObj3D* pCurrentObj3D,BOOL bUsingDlg,
																					UINT nObjType)
{
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////// XForm Obj3D-dependent OBJECTS
	int nResult = 0;
	////////////////
	CDListMgr* pList;
	int i,nCount;
	//////////////////////////////////////////////// Objects
	switch(nObjType)
	{
		case OBJ3D:
			pList	= pCurrentObj3D->GetObj3DList();
			break;
		default:
			nResult = -1;
			return nResult;
	}
	///
	nCount	= pList->GetCount();
	///////////
	for(i=0;i<nCount;i++)
	{
		CObject* pObject	= pList->GetObject(i);
		////////////////
		if(pObject)
		{
			switch(nObjType)
			{

				case OBJ3D:

					pObjectMgr->ShowObject_On_Off((CDrObject*)pObject,OBJ3D,FALSE);
					///
					nResult = O3DTopo_SpawnConnectedObj3Ds_CopyOff((CDrObj3D*)pObject,bUsingDlg);
					///
					pObjectMgr->ShowObject_On_Off((CDrObject*)pObject,OBJ3D,TRUE);
					break;

				default:
					nResult = -1;
					return nResult;
			}
			///
			if(nResult == -1)
			{
				AfxMessageBox(
					"Internal ERROR\nCO3DCreOp::Obj3DDependent_SpawnConnectedObjects_CopyOff");
				return nResult;
			}
		}
	}
	/////////////////////
	return nResult;
}

int CO3DCreOp::Obj3DSpawnCopyOff(CDrObj3D* pParentObj3D,BOOL bUsingDlg)
{
	int nResult;
	C3DMath			Math3D;
	///////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///////////////////
	pObjectMgr->SetActiveObjectType(OBJ3D);
	/////////////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(pParentObj3D,OBJ3D,FALSE);
	///////////////////////////////
	CDrObj3D* pSpawnedObj3D = pParentObj3D;
	/////////////////////////////////////////////////////////////// Using CMI_CSPN
	CMI_OSPN MI_OSPN;
	/////////////////
	MI_OSPN.SetNDoneList(&m_NDoneList);
	MI_OSPN.SetCDoneList(&m_CDoneList);
	MI_OSPN.SetPDoneList(&m_PDoneList);
	MI_OSPN.SetSDoneList(&m_SDoneList);
	MI_OSPN.SetODoneList(&m_ODoneList);
	///////////////////////////////////
	if(bUsingDlg)
	{
		pSpawnedObj3D->SetObjectID(m_ObjID);
		///
		nResult = MI_OSPN.SpawnObj3DShowingDlg((CDrObj3D*)pSpawnedObj3D,pParentObj3D,pParentObj3D,OBJ3D);
	}
	else
	{
		pMATRIX	pXFMat	= m_pMatObj->GetMatrix();
		CString	SpawnID	= m_ObjID;
		////
		nResult = MI_OSPN.SpawnObj3DWithoutDlg(pSpawnedObj3D,pParentObj3D,pXFMat,&m_SpawnedID,
												pParentObj3D,OBJ3D); 
	}
	if(nResult<0)
	{
		/////////////////////////////////////// Reset
		m_nInfoDone		= 0;
		m_bDone			= TRUE;	// 
		////////////////////////// Delete
		m_pSpawnedCurve	= NULL;
		//////////////////////////
		return nResult;//
	}
	////////////////////////////////////////////////////////// Save
	pObjectMgr->ShowObject_On_Off(pParentObj3D,OBJ3D,TRUE);
	///////////////////////////////
	return 0;
}	 

void CO3DCreOp::OnEBoxMouseMove_O3D(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point)
{  

	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
	/////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CMouseMgr* pMouseMgr	= pWnd->GetMouseMgr(); 
	////////////////////////// LOG: Log/DEScaled
   	m_pdc->DPtoLP(&point);     
	LPOINT LpLOG;
	LpLOG.x = (long)point.x;
	LpLOG.y = (long)point.y;
   	m_pdc->LPtoDP(&point);
    /////////////////////////////////////////////
    if(!m_bDragging)  // not currently dragging 
    { 
    
		//////////////////////////////////////
		LPOINT3 MouseOldTempWIC = GetMouseOldWIC();
	    LPOINT3 MouseTempWIC 	= GetMouseWIC();
   		SetMouseOldWIC(MouseTempWIC);
   		LPOINT3 MouseWIC;
    	///////////////////////  LOG :DEScaled
    	LOGtoWIC2(&MouseWIC,&LpLOG,&MouseTempWIC); //LOG/Scaled WIC
    	////////////////////                 
    	SetMouseWIC(MouseWIC);
    	///////////////////////////
//    	pDoc->UpdateStatusBar(&dc);  WILL BE CALLED FROM VIEW, JUST SET HERE
		pMouseMgr->SetStatusMouseWIC(MouseWIC);
		////////////////////////////
		///////////////////// recover MouseWIC changed for statusbar update 
	    SetMouseOldWIC(MouseOldTempWIC);
	    SetMouseWIC(MouseTempWIC);

		return;
    }	
}

void CO3DCreOp::OnEBoxLButtonUp_O3D(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point)
{
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
	////////////////////////////////
    POINT Logpoint;
    m_pdc->DPtoLP(&point);
    Logpoint.x = point.x;
    Logpoint.y = point.y;
    m_pdc->LPtoDP(&point);							
    ////////////////////
    if(m_Gener == FORWARD)
		ElementLeftUp_O3D(Logpoint);
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftUp_I();
	/////////////////////////
	
}

void CO3DCreOp::OnEBoxRButtonDown_O3D(CClientDC* pdc,CView* pView,GENERATE gener,
									UINT nFlags, CPoint point)
{ 
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
	/////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();

	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
    /////////////////////////////  ELement Dialog On/Off Check
	m_bDialogOn     = pBool->IsDialogOn();
	m_bAutoAcceptOn	= pBool->IsAutoAcceptOn();
	/////////////////////////////////////////////////////////////////////////////
	m_nActiveObject = pWnd->GetActiveObjectType(); 
	m_nActiveTool	= pWnd->GetActiveToolType();    // -1= INSERT
	/////////////////////////////////////////////////////////////////////////
	pObjectMgr->SetActiveObjectType(m_nActiveObject);       // Set ObjectType 
	//////////////////////////////////////////
	switch(m_nActiveTool) 
	{
		case OBJ3D:
			break;
		////////////////////////////////////////////////// Obj3D
		default:
			break;
	}  
}

void CO3DCreOp::OnEBoxRButtonUp_O3D(CClientDC* pdc,CView* pView,GENERATE gener,
								UINT nFlags, CPoint point)
{
	CString strCur;
	//////////
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
	/////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////////////////
	CString ID;
	CString* pID = &ID;
	///////////////////////////////////////////////////////// Update Info
	if(m_nActiveTool != COP_SPAWN && m_nActiveTool != COP_STITCH) 
		UpdateDlg_TRUE();
	///////////////////////////////////////////////////////// Is Enough Info?
	if(RightUp_Premature()<0)
		return;
	///////////////////////////////////////////////////////// Not Auto Accept
	if(RightUp_NotAutoAccept()<0)
	{
		Terminate_O3D(TRUE);
		return;
	}
	///////////////////////////////////////////////////// Show Spawned Node 
	switch(m_nActiveTool) 
	{

		case COP_TRANSLATE:
						
			
			SetUpLocalM_XLATE();
			/////////////////////////////
			if(ShowObj3DToSpawn(m_pParentObj3D,FALSE)<0)		 //FALSE = NoDlg
			////////////////
			{
				Terminate_O3D(TRUE);
				return;
			}
			else
			{
				Terminate_O3D(FALSE);
				Init_O3D();
				/////////////////////////
				UpdateDlg_FALSE_XLATE();
				break;
			}
			///////////////////	
			break;

			
		case COP_ROTATE:
						
			
			SetUpLocalM_ROTATE();
			/////////////////////////////
			if(ShowObj3DToSpawn(m_pParentObj3D,FALSE)<0)		 //FALSE = NoDlg
			////////////////
			{
				Terminate_O3D(TRUE);
				return;
			}
			else
			{
				Terminate_O3D(FALSE);
				Init_O3D();
				/////////////////////////
				UpdateDlg_FALSE_ROTATE();
				break;
			}
			///////////////////	
			break;
		
		case COP_SCALE:
						
			
			SetUpLocalM_SCALE();
			/////////////////////////////
			if(ShowObj3DToSpawn(m_pParentObj3D,FALSE)<0)		 //FALSE = NoDlg
			////////////////
			{
				Terminate_O3D(TRUE);
				return;
			}
			else
			{
				Terminate_O3D(FALSE);
				Init_O3D();
				/////////////////////////
				UpdateDlg_FALSE_SCALE();
				break;
			}
			///////////////////	
			break;
		
		case COP_REFLECT:
						
			
			SetUpLocalM_REFLECT();
			/////////////////////////////
			if(ShowObj3DToSpawn(m_pParentObj3D,FALSE)<0)		 //FALSE = NoDlg
			////////////////
			{
				Terminate_O3D(TRUE);
				return;
			}
			else
			{
				Terminate_O3D(FALSE);
				Init_O3D();
				/////////////////////////
				UpdateDlg_FALSE_REFLECT();
				break;
			}
			///////////////////	
			break;
		
		case COP_SHEAR:
						
			
			SetUpLocalM_SHEAR();
			/////////////////////////////
			if(ShowObj3DToSpawn(m_pParentObj3D,FALSE)<0)		 //FALSE = NoDlg
			////////////////
			{
				Terminate_O3D(TRUE);
				return;
			}
			else
			{
				Terminate_O3D(FALSE);
				Init_O3D();
				/////////////////////////
				UpdateDlg_FALSE_SHEAR();
				break;
			}
			///////////////////	
			break;
		

		
		case COP_STITCH:
		
			//////////////////////////// 	
			return;



		case COP_SPAWN:
		
			/////////////////////////////
			if(ShowObj3DToSpawn(m_pParentObj3D,TRUE)<0)		 //TRUE = Dlg
			////////////////
			{
				Terminate_O3D(TRUE);
				return;
			}
			else
			{
				Terminate_O3D(FALSE);
				Init_O3D();
				////////////////////
				strCur = "Composite Affine/Symmetry Transformations@";
				strCur += "Click on a OBJ3D to Spawn";
				/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCur);
	pWnd->UpdateCurrStat(strCur);
				///////////
				break;
			}
			///////////////////	
		
		default:  
			return;
	} 
	////////////////////////////////////////////////////////////////////////
	char buf[50];
    m_LastNum		= pObjectMgr->GetLastInputNo(OBJ3D);		// internal
	sprintf(buf,"%d",m_LastNum);
	m_SpawnedID	= "";
	m_SpawnedID	+= buf;
	pObjectMgr->BumpLastInputNo(OBJ3D);		// bump it
	////////////////////////////////////////////////////////////////////////
}

long CO3DCreOp::CreateorActivateCreOp_O3D(UINT wParam, long lParam)
{
	/////////////////////////////////////////// Parent Info
	m_ParentType	= OBJ3D;
	m_strParentType = "Obj3D";
	/////////////////////////////////////////////////////////
	GetCreOpDlg()->m_CreOp = m_CreOp;
	///////////////////////////////////////
	if(GetCreOpDlg()->GetSafeHwnd() ==0)	// not created already
	{
		GetCreOpDlg()->Create();
		CRect BoxRect;
		CWnd  wndTopMost;
		GetCreOpDlg()->GetWindowRect(&BoxRect);
		SizeRectDlgIn(BoxRect);
		//////////////////////////////////////////////////////////////
		GetCreOpDlg()->SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
                        BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
		//////////////////////////////////////////////////////////////
		Init_O3D();

	}
	else
	{
		GetCreOpDlg()->SetActiveWindow();
		GetCreOpDlg()->m_CreOp = m_CreOp;
	}
	////////////////
	switch(m_CreOp)
	{
		case COP_TRANSLATE:
			//////////////////////////////
			UpdateDlg_FALSE_XLATE();
			////
			break;
		case COP_ROTATE:
			//////////////////////////////
			UpdateDlg_FALSE_ROTATE();
			////
			break;
		case COP_SCALE:
			//////////////////////////////
			UpdateDlg_FALSE_SCALE();
			////
			break;
		case COP_REFLECT:
			//////////////////////////////
			UpdateDlg_FALSE_REFLECT();
			////
			break;
		case COP_SHEAR:
			//////////////////////////////
			UpdateDlg_FALSE_SHEAR();
			////
			break;
		case COP_SPAWN:
			//////////////////////////////
//			UpdateDlg_FALSE_SPAWN();
			////
			break;
		default:
			break;
	}
	///////////////////////////////////////////////////////////////// if CreODlg Open
	if(GetCreOpDlg()->m_hWnd)
	{
/*
		CStatic* pCtl;
		pCtl = (CStatic*)(GetCreOpDlg()->GetDlgItem(IDC_OTHER));
		////////////////////////////////////////////////////////
		if((UINT)(pWnd->GetActiveViewNumber()) == VIEW12)
			pCtl->SetWindowText("Z");
		else
		if((UINT)(pWnd->GetActiveViewNumber()) == VIEW23)
			pCtl->SetWindowText("X");
		else
		if((UINT)(pWnd->GetActiveViewNumber()) == VIEW31)
			pCtl->SetWindowText("Y");
		else
		if((UINT)(pWnd->GetActiveViewNumber()) == VIEWISO)
		{
			pWnd->SendMessage(ID_GOODBYE_CREOP,IDOK);
			return 0L;
		}
*/

	}

	return 0L;
}
	 
long CO3DCreOp::GoodByeCreOp_O3D(UINT wParam, long lParam)
{
	
	GetCreOpDlg()->DestroyWindow();
	////////////////
	{
		Terminate_O3D(FALSE);
		return 0L;
	}
	//////////
	return 0L;
}
	 
long CO3DCreOp::CancelCreOp_O3D(UINT wParam, long lParam)
{
	
	GetCreOpDlg()->DestroyWindow();
	////////////////
	{
		Terminate_O3D(FALSE);
		return 0L;
	}
	//////////
	return 0L;
}
	 
/////////////////////////////////////////////////////////////////////////////////////// 
UINT CO3DCreOp::ReSetToolID_O3D(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	///////////////////////////////////
	if(IGenID != OBJ3D)
	{
		str = "UNKNOWN";	ID	= UNONE;
		pWnd->SetstrIGenID(str);
		////////////////////////
		return UNONE;
	}
	//////////////////////////////////////////// TaskID
	strCur = "Ready for Spawning a SubStructure@";
	/////////////////////////////
	switch(CntlID)
	{
		//////////////////////////////////////// Elements
		case ELEMENT:
//					pWnd->SetMouseBoxType(ELEMDIMBOX);
			str = "ELEMENT";
			pWnd->SetIGenBoxStatus(TRUE);
			pWnd->SetCntlBoxStatus(FALSE);
			pWnd->SetDrawBoxStatus(FALSE);
			///////////
			pWnd->SetstrCntlID(str);
			////////////////////////
			switch(OperID)
			{
				//////////////////////////////////////////// Create
				case COP_TRANSLATE:
					///////////////////////////// String
					str = "TRANSLATE";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "OBJ3D";		ID	= COP_TRANSLATE;
						strCur += "Click on a SubStructure to Translate";
					break;
				//////////////////////////////////////////// Create
				case COP_ROTATE:
					///////////////////////////// String
					str = "ROTATE";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "OBJ3D";		ID	= COP_ROTATE;
						strCur += "Click on a SubStructure to Rotate";
					break;
				//////////////////////////////////////////// Create
				case COP_SCALE:
					///////////////////////////// String
					str = "SCALE";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "OBJ3D";		ID	= COP_SCALE;
						strCur += "Click on a SubStructure to Scale";
					break;
				//////////////////////////////////////////// Create
				case COP_REFLECT:
					///////////////////////////// String
					str = "REFLECT";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "OBJ3D";		ID	= COP_REFLECT;
						strCur += "Click on a SubStructure to Reflect";
					break;
				//////////////////////////////////////////// Create
				case COP_SHEAR:
					///////////////////////////// String
					str = "SHEAR";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "OBJ3D";		ID	= COP_SHEAR;
						strCur += "Click on a SubStructure to Shear";
					break;
				//////////////////////////////////////////// Create
				case COP_SPAWN:

					Init_O3D();	// No Modeless Dlg, so Init Here
					///////////////////////////// String
					str = "SPAWN";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "OBJ3D";		ID	= COP_SPAWN;
						strCur = "Composite Affine/Symmetry Transformations@";
						strCur += "Click on a SubStructure to Spawn";
					break;
				//////////////////////////////////////////// Create
				default:
					///////////////////////////// String
					str = "DON'T KNOW";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					ID	= UNONE;
					strCur = "UNKNOWN Spawing Option";
					pWnd->SetstrCurrID(strCur);
					break;
			}
			////////////////////////////////////////////////// Overriding everyID above
			ID = OperID;		// afterthought
			//////////////////////////////////////////// CreOp
			m_CreOp = OperID;
			////////////////////////////////////////////////// 
			pWnd->SetstrIGenID(str);
			pWnd->SetstrCurrID(strCur);
			//////////
			return ID;

		default:
			break;
	}
	return UNONE;
}

void CO3DCreOp::Serialize(CArchive& ar)
{

	CSolCreOp::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" O3DCreOp:    Storing\n");	
		

	}
	else
	{
		TRACE(" O3DCreOp:    Loading\n");	

	
	}        
}
///////////////////////////////////// end of Module //////////////////////		

