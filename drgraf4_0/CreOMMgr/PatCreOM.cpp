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
//#include "MNodMgr.h"  
#include "MMs2Mgr.h"	// for stitching
////////////////////// 
#include "MI_Gang2.h" 
#include "MI_2SPN.h" 
#include "Mlg_CrOI.h"
//////////////////////
#include "PatCreOM.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
///////////////////////////////////////////////////////////////////////////////////////////
// if NODE_SPAWN: Object Grab Node Same As Node
//////////////////////////////////////////////
#define MAX_INFO_XLATE		3	// 1 Object/1 Object Grab Node/1 Node        
#define MAX_INFO_ROTATE		6	// 1 Object/1 Object Grab Node/2 Nodes( for Axis)           
#define MAX_INFO_ROT_LINE	3	// 1 Object/1 Object Grab Node/2 Nodes( for Axis)           
#define MAX_INFO_SCALE		2	// 1 Object/1 Object Grab Node/None but 3 Coords(from Dlg)           
#define MAX_INFO_REFLECT	4	// 1 Object/1 Object Grab Node/	3 Nodes ( defining Plane or
								//			1 Node on Plane + 2 Nodes for Normal        
#define MAX_INFO_SHEAR		2	// 1 Object/1 Object Grab Node/None but 3 Coords(from Dlg) 
#define MAX_INFO_SPAWN		1	// 1 Object   
///////////////////////////////////////////////////////////////////////////////////////////      
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CPatCreOM,CCurCreOM,1)
/////////////////////////////////////////////////////////////////////////////
CPatCreOM::CPatCreOM()
{
	m_bDoModalDone = FALSE;
}

CPatCreOM::~CPatCreOM()
{
}

void CPatCreOM::Init_PAT()
{
	Init_NOD();
	//////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////
	CMI_Gang0 Gang0;
	Gang0.SetElemInfoID(m_SpawnedID,MESH2D);		
	/////////////////////////////////////////// Node
	m_pSpawnedPatch		= NULL;
	m_pParentPatch		= NULL;
	m_ParentID			= "";
	m_pCurrentPatch		= NULL;
	/////////////////////////////////////////// Dlg_CrOI 
	m_NID			= m_ParentID;

}

void CPatCreOM::Terminate_PAT(BOOL bError)
{
	Terminate_NOD(bError);
	////
	if(bError)
	{
		/////////////////////////////////////////// 
		if(m_pSpawnedPatch)
		{
			delete m_pSpawnedPatch;
			m_pSpawnedPatch = NULL;
		}
		///////////////////////////
	}
}

void CPatCreOM:: ElementLeftDown_PAT()
{	
	ElementLeftDown_NOD();
}

void CPatCreOM::OnEBoxLButtonDown_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
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
	////////////////////////////////////////////////// No Patch
	pDListMgr 	= pObjectMgr->GetObjectList(MESH2D);
	if(pDListMgr->GetCount()<=0)
		return;
	//////////////////////////
    if(m_Gener == FORWARD)
		ElementLeftDown_PAT();
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftDown_I();
	//////////////////////////////////
}

int CPatCreOM::LeftUp_GetPatch_Parent(POINT point)
{
	int nResult;
	///////////////////////////////////////////// See if any Existing Node Hit
	nResult = LeftUp_Patch_Accept(point);	// TRUE = Parent
	///////////////////
	if(nResult < 0)
		return nResult; // Cancel or No Hit
	///////
	if(nResult>=0)	// Hit
	{
		switch(m_nInfoDone)
		{
			case 0:	// 
				m_pParentPatch	= m_pCurrentPatch;
				m_ParentID		= m_pParentPatch->GetObjectID();
				break;
			default:
				return -1;
		}
	}
	//////////////////////////////////////
	return 0;
}

int CPatCreOM::LeftUp_TRANSLATE_PAT(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Patch	
			nResult = LeftUp_GetPatch_Parent(point);
			if(nResult<0)
				return nResult;
			return 0;
		case 1://	Grab Node	
		case 2://	To Node
			m_bCorMNodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_XLATE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			///
			nResult = LeftUp_GetNode_XLATE(point,FALSE);	// try MNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorMNodeOpDone = TRUE;
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

int CPatCreOM::LeftUp_ROTATE_PAT(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Patch	
			nResult = LeftUp_GetPatch_Parent(point);
			if(nResult<0)
				return nResult;
			return 0;
		case 1://	Grab Node	
			m_bCorMNodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);		// try MNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorMNodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);		// try INODE
			if(nResult < 0)
				return nResult;
			//
			return 0;
			////////
		case 2://		// From Rot Direction if Not AngleIn
			if(m_bAngleIn)
				return -1;
			//////////////
			m_bCorMNodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);		// try MNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorMNodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);		// try INODE
			if(nResult < 0)
				return nResult;
			//
			return 0;
			////////
		case 3://		// To Rot Direction
			if(m_bAngleIn || m_bAxis)
				return -1;
			//////////////
			m_bCorMNodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);		// try MNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorMNodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);		// try INODE
			if(nResult < 0)
				return nResult;
			//
			return 0;
			////////
		case 4://		// From Rot Direction if Not AngleIn
			if(m_bAngleIn || m_SpnType == SPN_ROT_ABT_LINE || m_bAxis)
				return -1;
			//////////////
			m_bCorMNodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);		// try MNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorMNodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);	// try INODE
			if(nResult < 0)
				return nResult;
			//
			return 0;
			////////
		case 5://		// To Rot Direction
			if(m_bAngleIn || m_SpnType == SPN_ROT_ABT_LINE || m_bAxis)
				return -1;
			//////////////
			m_bCorMNodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);		// try MNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorMNodeOpDone = TRUE;
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

int CPatCreOM::LeftUp_SCALE_PAT(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Patch	
			nResult = LeftUp_GetPatch_Parent(point);
			if(nResult<0)
				return nResult;
			return 0;
		case 1://	Grab Node	
			m_bCorMNodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_SCALE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			///
			nResult = LeftUp_GetNode_SCALE(point,FALSE);	// try MNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorMNodeOpDone = TRUE;
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

int CPatCreOM::LeftUp_REFLECT_PAT(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Patch	
			nResult = LeftUp_GetPatch_Parent(point);
			if(nResult<0)
				return nResult;
			return 0;
		case 1://	Ist Pt. or Node On Plane	
		case 2://	2nd Pt. or Node On Plane OR Ist Pt. on Normal	
		case 3://	Pt. or Node On Plane OR 2nd Pt. on Normal	
			m_bCorMNodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_REFLECT(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			///
			nResult = LeftUp_GetNode_REFLECT(point,FALSE);		// try MNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorMNodeOpDone = TRUE;
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

int CPatCreOM::LeftUp_SHEAR_PAT(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Patch	
			nResult = LeftUp_GetPatch_Parent(point);
			if(nResult<0)
				return nResult;
			return 0;
		case 1://	Grab Node	
			m_bCorMNodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_SHEAR(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			///
			nResult = LeftUp_GetNode_SHEAR(point,FALSE);	// try MNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorMNodeOpDone = TRUE;
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

void CPatCreOM::ElementLeftUp_PAT(CPoint point)
{                          

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	//////////////////////////////////////////////////////////////////
//	char buf[20];
	CString Nid;
	BOOL bRightOn	= FALSE;
	m_bStitch		= FALSE;
	///////////////////
	switch(m_nActiveTool) 
	{
		///////////////////////////////////////////////////// Patches Insert
		case COP_TRANSLATE:

			if(m_nInfoDone > MAX_INFO_XLATE)
				return;
			////////////////
			UpdateDlg_TRUE_XLATE();
			//////////////////
			if(!(m_bDirect && m_bDominant) )
			{
				if(LeftUp_TRANSLATE_PAT(point)<0)
				{
					Terminate_PAT(TRUE);
					return;
				}
			}
			/////////////
			m_nInfoDone++;
			UpdateDlg_FALSE_XLATE();
			///////
			return;

		case COP_ROTATE: 

			if(m_bAngleIn || m_bAxis)
			{
				if(m_nInfoDone > 2)
					return;
			}
			else
			{
				switch(m_SpnType)
				{
					case SPN_ROT_REF_2_TAR: 
						if(m_nInfoDone > MAX_INFO_ROTATE)
							return;
						break;
					case SPN_ROT_ABT_LINE: 
						if(m_nInfoDone > MAX_INFO_ROT_LINE)
							return;
						break;
					default:
						AfxMessageBox(
							"Internal ERROR:\nCCurCreOp::ElementLeftUp_NOD\nINVALID m_SpnType");
						return;

				}
			}
			////////////////
			UpdateDlg_TRUE_ROTATE();
			//////////////////
			if((m_nInfoDone == 1) && (m_bOrigin))
				///////
				m_nInfoDone++;
			else
			//////////////////////////////////
			if(!(m_bDirect && m_bDominant) )
			{
				if(LeftUp_ROTATE_PAT(point)<0)
				{
					Terminate_PAT(TRUE);
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
				if(LeftUp_SCALE_PAT(point)<0)
				{
					Terminate_PAT(TRUE);
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
				if(LeftUp_REFLECT_PAT(point)<0)
				{
					Terminate_PAT(TRUE);
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
				if(LeftUp_SHEAR_PAT(point)<0)
				{
					Terminate_PAT(TRUE);
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
			if(LeftUp_PSPAWN(point)<0)
			////////////////
			{
				Terminate_PAT(TRUE);
				return;
			}
			else
			{
				Terminate_CUR(FALSE);
				Init_CUR();
				/////////////////////////
//				UpdateDlg_FALSE_SPAWN();
				return;
			}
			/////////////
//			m_nInfoDone++;
			///////
			break;
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

int CPatCreOM::LeftUp_Patch_Accept(CPoint point)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(MESH2D);
//	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrMesh2D*	pDrPatch;
//	int			nActiveIndex,index;
	int			index;
	////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	WORtoWOP(&dTol,&dTol);	// physical
	///////////////////////////////////////////// See if any Existing Patch Hit
	index = IsObjectHit(MESH2D,point,0);
	////////////////////////////////////////////////////
	if(index<0)
		return -1; // No Patch Hit
	//////////////////////////////////////////////////////////////// Existing Patch
	pDrPatch	= (CDrMesh2D*)pDListMgr->GetObject(index);
	ID			= pDrPatch->GetObjectID();
	/////////////////////////////////////////
			pObjectMgr->ShowObject_On_Off(pDrPatch,MESH2D,TRUE);
/*
	pList = pObjectMgr->GetObjectList(MESH2D);
	nActiveIndex = pList->GetObjectIndex(MESH2D, ID);;
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
	pObjectMgr->SetActiveObjectType(MESH2D);		    // set Active Type									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,MESH2D);
*/
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
//			nResult = ShowParentPatchInfo(pDrPatch);
			nResult = ShowParentPatchInfo(pDrPatch);
			/////////////
			if(nResult == IDYES)
				//////////////////////////////////////////////////////// Accept Old
				break;
			else
			if(nResult == IDNO)
			{
				//////////////////////////////////////////////////////// Retry
				index = IsObjectHit(MESH2D,point,startIndex);
				if(index>=0)
				{
					pDrPatch	= (CDrMesh2D*)pDListMgr->GetObject(index);
					ID		= pDrPatch->GetObjectID();
					///////////////////////////////////////// 
			pObjectMgr->ShowObject_On_Off(pDrPatch,MESH2D,TRUE);
/*
					pList = pObjectMgr->GetObjectList(MESH2D);
					nActiveIndex = pList->GetObjectIndex(MESH2D, ID);;
					pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
					pObjectMgr->SetActiveObjectType(MESH2D);		    // set Active Index									
					pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,MESH2D);
*/
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
	m_pCurrentPatch = pDrPatch;
	/////////
	return 0;
	/////////
}

int CPatCreOM::LeftUp_PSPAWN(CPoint point)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Patch	
			nResult = LeftUp_GetPatch_Parent(point);
			if(nResult<0)
				return nResult;
			///////////////////
			strCurr = "Ready with other Info.?@Click Right Button";
			pWnd->GetCurrStat()->SetText(strCurr);
			pWnd->GetCurrStat()->Invalidate();
			pWnd->GetCurrStat()->UpdateWindow();
			///
			return 0;
			////////
		default:
			break;
	}
	return -1;
}

int CPatCreOM::ShowParentPatchInfo(CDrMesh2D* pDrPatch)
{
	int nResult = IDYES;
	/////////////////
	AfxMessageBox("CPatCreOM::ShowParentPatchInfo\nNot Done Yet");
	///
	return nResult;
}

int CPatCreOM::ShowPatchToSpawn(CDrMesh2D* pParentPatch,BOOL bUsingDlg)
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
		nResult = ShowPatchToSpawnCopyOff(pParentPatch,bUsingDlg);
		return nResult;
	}
	////////////////////////////////
	strCurr = "Please Wait";
	///////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->SetText(strCurr);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
	///////////////////
	pObjectMgr->SetActiveObjectType(MESH2D);
	////////////////////////////////////////////////////////////////////////////// Add to DataBase
	int nActiveIndex;
	/////////////////
	m_pSpawnedPatch	= (CDrMesh2D*)(pObjectMgr->AddToDataBase(nActiveIndex,MESH2D));
	m_pSpawnedPatch->SetShow(FALSE);	// not quite ready
	/////////////////////////////////////////////////////////////// Using CMI_PSPN
	CMI_2SPN MI_PSPN;
	if(bUsingDlg)
	{
		m_pSpawnedPatch->SetObjectID(m_ObjID);
		///
		nResult = MI_PSPN.SpawnPatchShowingDlg(m_pSpawnedPatch,pParentPatch,pParentPatch,MESH2D);
	}
	else
	{
		pMATRIX	pXFMat	= m_pMatObj->GetMatrix();
		CString	SpawnID	= m_ObjID;
		////
		nResult = MI_PSPN.SpawnPatchWithoutDlg(m_pSpawnedPatch,pParentPatch,pXFMat,&m_SpawnedID,
												pParentPatch,MESH2D); 
	}
	if(nResult<0)
	{
		/////////////////////////////////////// Reset
		m_nInfoDone		= 0;
		m_bDone			= TRUE;	// 
		////////////////////////// Delete
		pObjectMgr->DeleteFromDataBase(nActiveIndex, MESH2D);
		m_pSpawnedPatch	= NULL;
		//////////////////////////
		return nResult;//
	}
	/////////////////////////////////////////////////////////// Control RectBound
//	m_pSpawnedPatch->SetDirty(TRUE);
	m_pSpawnedPatch->SetShow(TRUE);
	////////////////////////////////////////////////////////// Save
	pObjectMgr->ShowObject_On_Off(m_pSpawnedPatch,MESH2D,TRUE);
	///////////////////////////////
	return 0;
}	 

int CPatCreOM::ShowPatchToSpawnCopyOff(CDrMesh2D* pParentPatch,BOOL bUsingDlg)
{
#ifdef _DEBUG
	CString ObjID = pParentPatch->GetObjectID();
#endif
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
	pWnd->GetCurrStat()->SetText(strCurr);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
	///////////////////
	pObjectMgr->ShowObject_On_Off(pParentPatch,MESH2D,FALSE);
	//////////////////////
	if(!(pParentPatch->GetMs2List())->IsEmpty())
	{
		/////////////////////////////////////////////////////////// XForm Patch-dependent MESH2DES
		nResult = PatchDependent_SpawnConnectedObjects_CopyOff(pParentPatch,bUsingDlg,MESH2D);
		///
		if(nResult == -1)
			goto ERRORHANDLER;
		/////////////////////
	}
	//////////////////////////////////////////////
	if(!(pParentPatch->GetMs3List())->IsEmpty())
	{
		/////////////////////////////////////////////////////////// XForm Patch-dependent MESH3DS
		nResult = PatchDependent_SpawnConnectedObjects_CopyOff(pParentPatch,bUsingDlg,MESH3D);
		///
		if(nResult == -1)
			goto ERRORHANDLER;
		/////////////////////
	}
	//////////////////////////////////////////////
	if(!(pParentPatch->GetMbj3DList())->IsEmpty())
	{
		/////////////////////////////////////////////////////////// XForm Patch-dependent MBJ3DS
		nResult = PatchDependent_SpawnConnectedObjects_CopyOff(pParentPatch,bUsingDlg,MBJ3D);
		///
		if(nResult == -1)
			goto ERRORHANDLER;
		/////////////////////
	}
	///////////////////////////////////////////////// XForm Current Patch, if not done yet
	index = m_PDoneList.GetObjectIndex(pParentPatch);
	if(index<0)	// not done yet
	{
		/////////////////////////////////////////////////////////// XForm Current Patch
		nResult = PatchSpawnCopyOff(pParentPatch,bUsingDlg);
		///
		if(nResult == -1)
			goto ERRORHANDLER;
		/////////////////////
		m_PDoneList.InsertObject(pParentPatch);
	}
	/////////////////////////////////////////////////////////////// walk downward to go upward
	if(!(pParentPatch->GetMs1List())->IsEmpty())
	{
		CDListMgr* pList = pParentPatch->GetMs1List();
		int nMax = pList->GetCount();
		for(int i=0;i<nMax;i++)
		{
			CDrMesh1D* pParentCurve = (CDrMesh1D*)(pList->GetObject(i));
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
	///////////////////////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(pParentPatch,MESH2D,TRUE);
	///////////////////////////
	if(!bUsingDlg && m_pMatObj)
	{	
		delete m_pMatObj;	
		m_pMatObj = NULL;
	}
	/////////
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
	 
int CPatCreOM::PatchDependent_SpawnConnectedObjects_CopyOff(CDrMesh2D* pCurrentPatch,BOOL bUsingDlg,
																					UINT nObjType)
{
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////// XForm Patch-dependent OBJECTS
	int nResult = 0;
	////////////////
	CDListMgr* pList;
	int i,nCount;
	//////////////////////////////////////////////// Objects
	switch(nObjType)
	{
		case MESH2D:
			pList	= pCurrentPatch->GetMs2List();
			break;
		case MESH3D:
			pList	= pCurrentPatch->GetMs3List();
			break;
		case MBJ3D:
			pList	= pCurrentPatch->GetMbj3DList();
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

				case MESH2D:

					pObjectMgr->ShowObject_On_Off((CDrObject*)pObject,MESH2D,FALSE);
					///
					nResult = PatTopo_SpawnConnectedPatches_CopyOff((CDrMesh2D*)pObject,bUsingDlg);
					///
					pObjectMgr->ShowObject_On_Off((CDrObject*)pObject,MESH2D,TRUE);
					break;

				case MESH3D:

					pObjectMgr->ShowObject_On_Off((CDrObject*)pObject,MESH3D,FALSE);
					///
					nResult = SolTopo_SpawnConnectedSolids_CopyOff((CDrMesh3D*)pObject,bUsingDlg);
					///
					pObjectMgr->ShowObject_On_Off((CDrObject*)pObject,MESH3D,TRUE);
					break;

				case MBJ3D:

					pObjectMgr->ShowObject_On_Off((CDrObject*)pObject,MBJ3D,FALSE);
					///
					nResult = O3DTopo_SpawnConnectedObj3Ds_CopyOff((CDrMbj3D*)pObject,bUsingDlg);
					///
					pObjectMgr->ShowObject_On_Off((CDrObject*)pObject,MBJ3D,TRUE);
					break;

				default:
					nResult = -1;
					return nResult;
			}
			///
			if(nResult == -1)
			{
				AfxMessageBox(
					"Internal ERROR\nCPatCreOM::PatchDependent_SpawnConnectedObjects_CopyOff");
				return nResult;
			}
		}
	}
	/////////////////////
	return nResult;
}

int CPatCreOM::PatchSpawnCopyOff(CDrMesh2D* pParentPatch,BOOL bUsingDlg)
{
	int nResult;
	C3DMath			Math3D;
	///////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///////////////////
	pObjectMgr->SetActiveObjectType(MESH2D);
	/////////////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(pParentPatch,MESH2D,FALSE);
	///////////////////////////////
	CDrMesh2D* pSpawnedPatch = pParentPatch;
	/////////////////////////////////////////////////////////////// Using CMI_CSPN
	CMI_2SPN MI_PSPN;
	/////////////////
	MI_PSPN.SetNDoneList(&m_NDoneList);
	MI_PSPN.SetCDoneList(&m_CDoneList);
	MI_PSPN.SetPDoneList(&m_PDoneList);
	MI_PSPN.SetSDoneList(&m_SDoneList);
	MI_PSPN.SetODoneList(&m_ODoneList);
	///////////////////////////////////
	m_ObjID = pParentPatch->GetObjectID();
	//////////////////////////////////////
	if(bUsingDlg)
	{
		///
		nResult = MI_PSPN.SpawnPatchShowingDlg((CDrMesh2D*)pSpawnedPatch,pParentPatch,pParentPatch,MESH2D);
	}
	else
	{
		pMATRIX	pXFMat	= m_pMatObj->GetMatrix();
		CString	SpawnID	= m_ObjID;
		////
		nResult = MI_PSPN.SpawnPatchWithoutDlg(pSpawnedPatch,pParentPatch,pXFMat,&m_ObjID,
												pParentPatch,MESH2D); 
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
	pObjectMgr->ShowObject_On_Off(pParentPatch,MESH2D,TRUE);
	///////////////////////////////
	return 0;
}	 

void CPatCreOM::OnEBoxMouseMove_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CPatCreOM::OnEBoxLButtonUp_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
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
		ElementLeftUp_PAT(Logpoint);
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftUp_I();
	/////////////////////////
	
}

void CPatCreOM::OnEBoxRButtonDown_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
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
		case MESH2D:
			break;
		////////////////////////////////////////////////// Patch
		default:
			break;
	}  
}

void CPatCreOM::OnEBoxRButtonUp_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
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
		Terminate_PAT(TRUE);
		return;
	}
	///////////////////////////////////////////////////// Show Spawned Node 
	switch(m_nActiveTool) 
	{

		case COP_TRANSLATE:
						
			
			SetUpLocalM_XLATE();
			/////////////////////////////
			if(ShowPatchToSpawn(m_pParentPatch,FALSE)<0)		 //FALSE = NoDlg
			////////////////
			{
				Terminate_PAT(TRUE);
				return;
			}
			else
			{
				Terminate_PAT(FALSE);
				Init_PAT();
				/////////////////////////
				UpdateDlg_FALSE_XLATE();
				break;
			}
			///////////////////	
			break;

			
		case COP_ROTATE:
						
			
			SetUpLocalM_ROTATE();
			/////////////////////////////
			if(ShowPatchToSpawn(m_pParentPatch,FALSE)<0)		 //FALSE = NoDlg
			////////////////
			{
				Terminate_PAT(TRUE);
				return;
			}
			else
			{
				Terminate_PAT(FALSE);
				Init_PAT();
				/////////////////////////
				UpdateDlg_FALSE_ROTATE();
				break;
			}
			///////////////////	
			break;
		
		case COP_SCALE:
						
			
			SetUpLocalM_SCALE();
			/////////////////////////////
			if(ShowPatchToSpawn(m_pParentPatch,FALSE)<0)		 //FALSE = NoDlg
			////////////////
			{
				Terminate_PAT(TRUE);
				return;
			}
			else
			{
				Terminate_PAT(FALSE);
				Init_PAT();
				/////////////////////////
				UpdateDlg_FALSE_SCALE();
				break;
			}
			///////////////////	
			break;
		
		case COP_REFLECT:
						
			
			SetUpLocalM_REFLECT();
			/////////////////////////////
			if(ShowPatchToSpawn(m_pParentPatch,FALSE)<0)		 //FALSE = NoDlg
			////////////////
			{
				Terminate_PAT(TRUE);
				return;
			}
			else
			{
				Terminate_PAT(FALSE);
				Init_PAT();
				/////////////////////////
				UpdateDlg_FALSE_REFLECT();
				break;
			}
			///////////////////	
			break;
		
		case COP_SHEAR:
						
			
			SetUpLocalM_SHEAR();
			/////////////////////////////
			if(ShowPatchToSpawn(m_pParentPatch,FALSE)<0)		 //FALSE = NoDlg
			////////////////
			{
				Terminate_PAT(TRUE);
				return;
			}
			else
			{
				Terminate_PAT(FALSE);
				Init_PAT();
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
			if(ShowPatchToSpawn(m_pParentPatch,TRUE)<0)		 //TRUE = Dlg
			////////////////
			{
				Terminate_PAT(TRUE);
				return;
			}
			else
			{
				Terminate_PAT(FALSE);
				Init_PAT();
				////////////////////
				strCur = "Composite Affine/Symmetry Transformations@";
				strCur += "Click on a MESH2D to Spawn";
				/////////////////////////////////////////////// CurrStat: Show
				pWnd->GetCurrStat()->SetText(strCur);
				pWnd->GetCurrStat()->Invalidate();
				pWnd->GetCurrStat()->UpdateWindow();
				///////////
				break;
			}
			///////////////////	
		
		default:  
			return;
	} 
	////////////////////////////////////////////////////////////////////////
	char buf[50];
    m_LastNum		= pObjectMgr->GetLastInputNo(MESH2D);		// internal
	sprintf(buf,"%d",m_LastNum);
	m_SpawnedID	= "P";
	m_SpawnedID	+= buf;
	pObjectMgr->BumpLastInputNo(MESH2D);		// bump it
	////////////////////////////////////////////////////////////////////////
}

long CPatCreOM::CreateorActivateCreOp_PAT(UINT wParam, long lParam)
{
	/////////////////////////////////////////// Parent Info
	m_ParentType	= MESH2D;
	m_strParentType = "Mesh2D";
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
		Init_PAT();

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
	 
long CPatCreOM::GoodByeCreOp_PAT(UINT wParam, long lParam)
{
	
	GetCreOpDlg()->DestroyWindow();
	////////////////
	{
		Terminate_PAT(FALSE);
		return 0L;
	}
	//////////
	return 0L;
}
	 
long CPatCreOM::CancelCreOp_PAT(UINT wParam, long lParam)
{
	
	GetCreOpDlg()->DestroyWindow();
	////////////////
	{
		Terminate_PAT(FALSE);
		return 0L;
	}
	//////////
	return 0L;
}
	 
/////////////////////////////////////////////////////////////////////////////////////// 
UINT CPatCreOM::ReSetToolID_PAT(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	///////////////////////////////////
	if(IGenID != MESH2D)
	{
		str = "UNKNOWN";	ID	= UNONE;
		pWnd->SetstrIGenID(str);
		////////////////////////
		return UNONE;
	}
	//////////////////////////////////////////// TaskID
	strCur = "Ready for Spawning a Mesh2D@";
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
					str	= "MESH2D";		ID	= COP_TRANSLATE;
						strCur += "Click on a MESH2D to Translate";
					break;
				//////////////////////////////////////////// Create
				case COP_ROTATE:
					///////////////////////////// String
					str = "ROTATE";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "MESH2D";		ID	= COP_ROTATE;
						strCur += "Click on a MESH2D to Rotate";
					break;
				//////////////////////////////////////////// Create
				case COP_SCALE:
					///////////////////////////// String
					str = "SCALE";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "MESH2D";		ID	= COP_SCALE;
						strCur += "Click on a MESH2D to Scale";
					break;
				//////////////////////////////////////////// Create
				case COP_REFLECT:
					///////////////////////////// String
					str = "REFLECT";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "MESH2D";		ID	= COP_REFLECT;
						strCur += "Click on a MESH2D to Reflect";
					break;
				//////////////////////////////////////////// Create
				case COP_SHEAR:
					///////////////////////////// String
					str = "SHEAR";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "MESH2D";		ID	= COP_SHEAR;
						strCur += "Click on a MESH2D to Shear";
					break;
				//////////////////////////////////////////// Create
				case COP_SPAWN:

					Init_PAT();	// No Modeless Dlg, so Init Here
					///////////////////////////// String
					str = "SPAWN";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "MESH2D";		ID	= COP_SPAWN;
						strCur = "Composite Affine/Symmetry Transformations@";
						strCur += "Click on a MESH2D to Spawn";
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

void CPatCreOM::Serialize(CArchive& ar)
{

	CCurCreOM::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" PatCreOM:    Storing\n");	
		

	}
	else
	{
		TRACE(" PatCreOM:    Loading\n");	

	
	}        
}
///////////////////////////////////// end of Module //////////////////////		

