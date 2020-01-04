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
#include "MI_PSPN.h" 
#include "Dlg_CrOI.h"
//////////////////////
#include "PatCreOp.h" 

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
IMPLEMENT_SERIAL(CPatCreOp,CCurCreOp,1)
/////////////////////////////////////////////////////////////////////////////
CPatCreOp::CPatCreOp()
{
	m_bDoModalDone = FALSE;
}

CPatCreOp::~CPatCreOp()
{
}

void CPatCreOp::Init_PAT()
{
	Init_NOD();
	//////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////
	char buf[50];
    m_LastNum		= pObjectMgr->GetLastInputNo(PATCH);		// internal
	sprintf(buf,"%d",m_LastNum);
	m_SpawnedID	= "P";
	m_SpawnedID	+= buf;
	pObjectMgr->BumpLastInputNo(PATCH);		// bump it
	/////////////////////////////////////////// Node
	m_pSpawnedPatch		= NULL;
	m_pParentPatch		= NULL;
	m_ParentID			= "";
	m_pCurrentPatch		= NULL;
	/////////////////////////////////////////// Dlg_CrOI 
	m_NID			= m_ParentID;

}

void CPatCreOp::Terminate_PAT(BOOL bError)
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

void CPatCreOp:: ElementLeftDown_PAT()
{	
	ElementLeftDown_NOD();
}

void CPatCreOp::OnEBoxLButtonDown_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
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
	pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
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

int CPatCreOp::LeftUp_GetPatch_Parent(POINT point)
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

int CPatCreOp::LeftUp_TRANSLATE_PAT(POINT point)
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

int CPatCreOp::LeftUp_ROTATE_PAT(POINT point)
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
		case 2://		// From Rot Direction if Not AngleIn
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
			if(m_bAngleIn || m_bAxis)
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
			if(m_bAngleIn || m_SpnType == SPN_ROT_ABT_LINE || m_bAxis)
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
			if(m_bAngleIn || m_SpnType == SPN_ROT_ABT_LINE || m_bAxis)
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

int CPatCreOp::LeftUp_SCALE_PAT(POINT point)
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

int CPatCreOp::LeftUp_REFLECT_PAT(POINT point)
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

int CPatCreOp::LeftUp_SHEAR_PAT(POINT point)
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

void CPatCreOp::ElementLeftUp_PAT(CPoint point)
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

int CPatCreOp::LeftUp_Patch_Accept(CPoint point)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(PATCH);
	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrPatch*	pDrPatch;
	int			nActiveIndex,index;
	////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	WORtoWOP(&dTol,&dTol);	// physical
	///////////////////////////////////////////// See if any Existing Patch Hit
	index = IsObjectHit(PATCH,point,0);
	////////////////////////////////////////////////////
	if(index<0)
		return -1; // No Patch Hit
	//////////////////////////////////////////////////////////////// Existing Patch
	pDrPatch	= (CDrPatch*)pDListMgr->GetObject(index);
	ID			= pDrPatch->GetObjectID();
	/////////////////////////////////////////
	pList = pObjectMgr->GetObjectList(PATCH);
	nActiveIndex = pList->GetObjectIndex(PATCH, ID);;
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
	pObjectMgr->SetActiveObjectType(PATCH);		    // set Active Type									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,PATCH);
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
				index = IsObjectHit(PATCH,point,startIndex);
				if(index>=0)
				{
					pDrPatch	= (CDrPatch*)pDListMgr->GetObject(index);
					ID		= pDrPatch->GetObjectID();
					///////////////////////////////////////// 
					pList = pObjectMgr->GetObjectList(PATCH);
					nActiveIndex = pList->GetObjectIndex(PATCH, ID);;
					pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
					pObjectMgr->SetActiveObjectType(PATCH);		    // set Active Index									
					pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,PATCH);
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

int CPatCreOp::LeftUp_PSPAWN(CPoint point)
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

int CPatCreOp::ShowParentPatchInfo(CDrPatch* pDrPatch)
{
	int nResult;
	CString ID;
	CString* pID = &ID;
	ID = pDrPatch->GetObjectID();
	//////////////////////////////////////////////////////////////////////
	PATCHPROC 		PatProc		= pDrPatch->GetPatchProc();
	PATSUBTYPE 		PatSubType	= pDrPatch->GetPatSubType();
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	//////
	j = sprintf(buf,"***** A Patch_To_Spawn_From Hit ****\n");
	//////////////////////////////////////
	switch(PatProc)
	{
		case PP_EXTRUDE:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Patch %s was Generated by Extrusion\n",*pID);
			break;

		case PP_ROTATE:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Patch %s was Generated by Rotation\n",*pID);
			break;

		case PP_LOFT2:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Patch %s\nGenerated by Lofting\n",*pID);
			break;

		case PP_DUCT:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Patch %s\nGenerated by Ducting\n",*pID);
			break;

		case PP_SWEEP:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Patch %s\nGenerated by\nSweeping\n",*pID);
			break;

		case PP_COONS:
			//////////////////////////////////////////////////// Show Patch
			if(PatSubType == PS_TRIANGLE)
				//////////////////////////////////////////////////// Show Patch
				j += sprintf(buf+j,"Patch %s\nTriangular Coons Type\n",*pID);
			else
			if(PatSubType == PS_QUADRILAT)
				//////////////////////////////////////////////////// Show Patch
				j += sprintf(buf+j,"Patch %s\nQuadrilateral Coons Type\n",*pID);

			////
			break;

		default:
			break;
	}
	////////////////////////////
	j += sprintf(buf+j,
		"\nYES:\t\tSpawn This Patch");
	j += sprintf(buf+j,
		"\nNO:\t\tFind Next Patch with Intersecting Trace");
	j += sprintf(buf+j,
		"\nCANCEL:\t\tCancel Selection Process");
	nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
	///////////////
	delete str;
	return nResult;
}

int CPatCreOp::ShowPatchToSpawn(CDrPatch* pParentPatch,BOOL bUsingDlg)
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
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	///////////////////
	pObjectMgr->SetActiveObjectType(PATCH);
	////////////////////////////////////////////////////////////////////////////// Add to DataBase
	int nActiveIndex;
	/////////////////
	m_pSpawnedPatch	= (CDrPatch*)(pObjectMgr->AddToDataBase(nActiveIndex,PATCH));
	m_pSpawnedPatch->SetShow(FALSE);	// not quite ready
	/////////////////////////////////////////////////////////////// Using CMI_PSPN
	CMI_PSPN MI_PSPN;
	if(bUsingDlg)
	{
		m_pSpawnedPatch->SetObjectID(m_ObjID);
		///
		nResult = MI_PSPN.SpawnPatchShowingDlg(m_pSpawnedPatch,pParentPatch,pParentPatch,PATCH);
	}
	else
	{
		pMATRIX	pXFMat	= m_pMatObj->GetMatrix();
		CString	SpawnID	= m_ObjID;
		////
		nResult = MI_PSPN.SpawnPatchWithoutDlg(m_pSpawnedPatch,pParentPatch,pXFMat,&m_SpawnedID,
												pParentPatch,PATCH); 
	}
	if(nResult<0)
	{
		/////////////////////////////////////// Reset
		m_nInfoDone		= 0;
		m_bDone			= TRUE;	// 
		////////////////////////// Delete
		pObjectMgr->DeleteFromDataBase(nActiveIndex, PATCH);
		m_pSpawnedPatch	= NULL;
		//////////////////////////
		return nResult;//
	}
	/////////////////////////////////////////////////////////// Control RectBound
	m_pSpawnedPatch->SetDirty(TRUE);
	m_pSpawnedPatch->SetShow(TRUE);
	////////////////////////////////////////////////////////// Save
	pObjectMgr->ShowObject_On_Off(m_pSpawnedPatch,PATCH,TRUE);
	///////////////////////////////
	return 0;
}	 

int CPatCreOp::ShowPatchToSpawnCopyOff(CDrPatch* pParentPatch,BOOL bUsingDlg)
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
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	///////////////////
	pObjectMgr->ShowObject_On_Off(pParentPatch,PATCH,FALSE);
	//////////////////////
	if(!(pParentPatch->GetPatchList())->IsEmpty())
	{
		/////////////////////////////////////////////////////////// XForm Patch-dependent PATCHES
		nResult = PatchDependent_SpawnConnectedObjects_CopyOff(pParentPatch,bUsingDlg,PATCH);
		///
		if(nResult == -1)
			goto ERRORHANDLER;
		/////////////////////
	}
	//////////////////////////////////////////////
	if(!(pParentPatch->GetSolidList())->IsEmpty())
	{
		/////////////////////////////////////////////////////////// XForm Patch-dependent SOLIDS
		nResult = PatchDependent_SpawnConnectedObjects_CopyOff(pParentPatch,bUsingDlg,SOLID);
		///
		if(nResult == -1)
			goto ERRORHANDLER;
		/////////////////////
	}
	//////////////////////////////////////////////
	if(!(pParentPatch->GetObj3DList())->IsEmpty())
	{
		/////////////////////////////////////////////////////////// XForm Patch-dependent OBJ3DS
		nResult = PatchDependent_SpawnConnectedObjects_CopyOff(pParentPatch,bUsingDlg,OBJ3D);
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
	if(!(pParentPatch->GetCurveList())->IsEmpty())
	{
		CDListMgr* pList = pParentPatch->GetCurveList();
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
	///////////////////////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(pParentPatch,PATCH,TRUE);
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
	 
int CPatCreOp::PatchDependent_SpawnConnectedObjects_CopyOff(CDrPatch* pCurrentPatch,BOOL bUsingDlg,
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
		case PATCH:
			pList	= pCurrentPatch->GetPatchList();
			break;
		case SOLID:
			pList	= pCurrentPatch->GetSolidList();
			break;
		case OBJ3D:
			pList	= pCurrentPatch->GetObj3DList();
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

				case PATCH:

					pObjectMgr->ShowObject_On_Off((CDrObject*)pObject,PATCH,FALSE);
					///
					nResult = PatTopo_SpawnConnectedPatches_CopyOff((CDrPatch*)pObject,bUsingDlg);
					///
					pObjectMgr->ShowObject_On_Off((CDrObject*)pObject,PATCH,TRUE);
					break;

				case SOLID:

					pObjectMgr->ShowObject_On_Off((CDrObject*)pObject,SOLID,FALSE);
					///
					nResult = SolTopo_SpawnConnectedSolids_CopyOff((CDrSolid*)pObject,bUsingDlg);
					///
					pObjectMgr->ShowObject_On_Off((CDrObject*)pObject,SOLID,TRUE);
					break;

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
					"Internal ERROR\nCPatCreOp::PatchDependent_SpawnConnectedObjects_CopyOff");
				return nResult;
			}
		}
	}
	/////////////////////
	return nResult;
}

int CPatCreOp::PatchSpawnCopyOff(CDrPatch* pParentPatch,BOOL bUsingDlg)
{
	int nResult;
	C3DMath			Math3D;
	///////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///////////////////
	pObjectMgr->SetActiveObjectType(PATCH);
	/////////////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(pParentPatch,PATCH,FALSE);
	///////////////////////////////
	CDrPatch* pSpawnedPatch = pParentPatch;
	/////////////////////////////////////////////////////////////// Using CMI_CSPN
	CMI_PSPN MI_PSPN;
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
		nResult = MI_PSPN.SpawnPatchShowingDlg((CDrPatch*)pSpawnedPatch,pParentPatch,pParentPatch,PATCH);
	}
	else
	{
		pMATRIX	pXFMat	= m_pMatObj->GetMatrix();
		CString	SpawnID	= m_ObjID;
		////
		nResult = MI_PSPN.SpawnPatchWithoutDlg(pSpawnedPatch,pParentPatch,pXFMat,&m_ObjID,
												pParentPatch,PATCH); 
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
	pObjectMgr->ShowObject_On_Off(pParentPatch,PATCH,TRUE);
	///////////////////////////////
	return 0;
}	 

void CPatCreOp::OnEBoxMouseMove_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CPatCreOp::OnEBoxLButtonUp_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CPatCreOp::OnEBoxRButtonDown_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
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
		case PATCH:
			break;
		////////////////////////////////////////////////// Patch
		default:
			break;
	}  
}

void CPatCreOp::OnEBoxRButtonUp_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
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
				strCur += "Click on a PATCH to Spawn";
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
    m_LastNum		= pObjectMgr->GetLastInputNo(PATCH);		// internal
	sprintf(buf,"%d",m_LastNum);
	m_SpawnedID	= "P";
	m_SpawnedID	+= buf;
	pObjectMgr->BumpLastInputNo(PATCH);		// bump it
	////////////////////////////////////////////////////////////////////////
}

long CPatCreOp::CreateorActivateCreOp_PAT(UINT wParam, long lParam)
{
	/////////////////////////////////////////// Parent Info
	m_ParentType	= PATCH;
	m_strParentType = "Patch";
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
	 
long CPatCreOp::GoodByeCreOp_PAT(UINT wParam, long lParam)
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
	 
long CPatCreOp::CancelCreOp_PAT(UINT wParam, long lParam)
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
UINT CPatCreOp::ReSetToolID_PAT(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	///////////////////////////////////
	if(IGenID != PATCH)
	{
		str = "UNKNOWN";	ID	= UNONE;
		pWnd->SetstrIGenID(str);
		////////////////////////
		return UNONE;
	}
	//////////////////////////////////////////// TaskID
	strCur = "Ready for Spawning a Patch@";
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
					str	= "PATCH";		ID	= COP_TRANSLATE;
						strCur += "Click on a PATCH to Translate";
					break;
				//////////////////////////////////////////// Create
				case COP_ROTATE:
					///////////////////////////// String
					str = "ROTATE";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "PATCH";		ID	= COP_ROTATE;
						strCur += "Click on a PATCH to Rotate";
					break;
				//////////////////////////////////////////// Create
				case COP_SCALE:
					///////////////////////////// String
					str = "SCALE";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "PATCH";		ID	= COP_SCALE;
						strCur += "Click on a PATCH to Scale";
					break;
				//////////////////////////////////////////// Create
				case COP_REFLECT:
					///////////////////////////// String
					str = "REFLECT";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "PATCH";		ID	= COP_REFLECT;
						strCur += "Click on a PATCH to Reflect";
					break;
				//////////////////////////////////////////// Create
				case COP_SHEAR:
					///////////////////////////// String
					str = "SHEAR";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "PATCH";		ID	= COP_SHEAR;
						strCur += "Click on a PATCH to Shear";
					break;
				//////////////////////////////////////////// Create
				case COP_SPAWN:

					Init_PAT();	// No Modeless Dlg, so Init Here
					///////////////////////////// String
					str = "SPAWN";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "PATCH";		ID	= COP_SPAWN;
						strCur = "Composite Affine/Symmetry Transformations@";
						strCur += "Click on a PATCH to Spawn";
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

void CPatCreOp::Serialize(CArchive& ar)
{

	CCurCreOp::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" PatCreOp:    Storing\n");	
		

	}
	else
	{
		TRACE(" PatCreOp:    Loading\n");	

	
	}        
}
///////////////////////////////////// end of Module //////////////////////		

