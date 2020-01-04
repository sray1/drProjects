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
#include "MMs1Mgr.h"	// for stitching
////////////////////// 
#include "MI_Gang1.h" 
#include "MI_1SPN.h" 
#include "MI_1Prof.h" 
#include "Mlg_CrOI.h"
//////////////////////
#include "CurCreOM.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
///////////////////////////////////////////////////////////////////////////////////////////
// if MESH1D_SPAWN: Object Grab Node Same As Node
//////////////////////////////////////////////
#define MAX_INFO_XLATE		3	// 1 Object/1 Object Grab Node/1 Node        
#define MAX_INFO_ROTATE		6	// 1 Object/1 Object Grab Node/2 Nodes( for Axis)           
#define MAX_INFO_ROT_LINE	3	// 1 Object/1 Object Grab Node/2 Nodes( for Axis)           
#define MAX_INFO_SCALE		2	// 1 Object/1 Object Grab Node/None but 3 Coords(from Dlg)           
#define MAX_INFO_REFLECT	4	// 1 Object/1 Object Grab Node/	3 Nodes ( defining Plane or
								//			1 Node on Plane + 2 Nodes for Normal        
#define MAX_INFO_SHEAR		2	// 1 Object/1 Object Grab Node/None but 3 Coords(from Dlg) 
#define MAX_INFO_SPAWN		0	// 1 Object   
#define MAX_INFO_STITCH		1	// Atleast Two Objects   
///////////////////////////////////////////////////////////////////////////////////////////      
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CCurCreOM,CNodCreOM,1)
/////////////////////////////////////////////////////////////////////////////
CCurCreOM::CCurCreOM()
{
	m_bStitch		= FALSE;
	m_bDoModalDone	= FALSE;
}

CCurCreOM::~CCurCreOM()
{
}

void CCurCreOM::Init_CUR()
{
	Init_NOD();
	//////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	/////////////////////////////
	CMI_Gang0 Gang0;
	Gang0.SetElemInfoID(m_SpawnedID,MESH1D);		
	/////////////////////////////////////////// Node
	m_pSpawnedCurve		= NULL;
	m_pParentCurve		= NULL;
	m_ParentID			= "";
	m_pCurrentCurve		= NULL;
	/////////////////////////////////////////// Dlg_CrOI 
	m_NID			= m_ParentID;
	/////////////////////////////////////////// STitch
	m_pCProfile		= NULL;
	m_pLastCurve	= NULL;
	m_CurveList.RemoveAll();

}

void CCurCreOM::Terminate_CUR(BOOL bError)
{
	Terminate_NOD(bError);
	////
	if(bError)
	{
		/////////////////////////////////////////// 
		if(m_pSpawnedCurve)
		{
			delete m_pSpawnedCurve;
			m_pSpawnedCurve = NULL;
		}
		/////////////////////////////////////////// 
		if(m_pCProfile)
		{
			delete m_pCProfile;
			m_pCProfile		= NULL;
			m_pCurrentCurve	= NULL;
			m_pLastCurve	= NULL;
			m_CurveList.RemoveAll();
		}
		///////////////////////////
	}
}

void CCurCreOM:: ElementLeftDown_CUR()
{	
	ElementLeftDown_NOD();
}

void CCurCreOM::OnEBoxLButtonDown_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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
	////////////////////////////////////////////////// No Curve
	pDListMgr 	= pObjectMgr->GetObjectList(MESH1D);
	if(pDListMgr->GetCount()<=0)
		return;
	//////////////////////////
    if(m_Gener == FORWARD)
		ElementLeftDown_CUR();
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftDown_I();
	//////////////////////////////////
}

int CCurCreOM::LeftUp_GetCurve_Parent(POINT point)
{
	int nResult;
	///////////////////////////////////////////// See if any Existing Node Hit
	nResult = LeftUp_Curve_Accept(point);	// TRUE = Parent
	///////////////////
	if(nResult < 0)
		return nResult; // Cancel or No Hit
	///////
	if(nResult>=0)	// Hit
	{
		switch(m_nInfoDone)
		{
			case 0:	// 
				m_pParentCurve	= m_pCurrentCurve;
				m_ParentID		= m_pParentCurve->GetObjectID();
				break;
			default:
				return -1;
		}
	}
	//////////////////////////////////////
	return 0;
}

int CCurCreOM::LeftUp_TRANSLATE_CUR(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Curve	
			nResult = LeftUp_GetCurve_Parent(point);
			if(nResult<0)
				return nResult;
			return 0;
		case 1://	Grab Node	
		case 2://	To Node
			m_bCorMNodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_XLATE(point,TRUE);		// try MCNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			///
			nResult = LeftUp_GetNode_XLATE(point,FALSE);	// try MNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorMNodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_XLATE(point,FALSE);	// try FE0D
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

int CCurCreOM::LeftUp_ROTATE_CUR(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Curve	
			nResult = LeftUp_GetCurve_Parent(point);
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

int CCurCreOM::LeftUp_SCALE_CUR(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Curve	
			nResult = LeftUp_GetCurve_Parent(point);
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

int CCurCreOM::LeftUp_REFLECT_CUR(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Curve	
			nResult = LeftUp_GetCurve_Parent(point);
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

int CCurCreOM::LeftUp_SHEAR_CUR(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Curve	
			nResult = LeftUp_GetCurve_Parent(point);
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

void CCurCreOM::ElementLeftUp_CUR(CPoint point)
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
				if(LeftUp_TRANSLATE_CUR(point)<0)
				{
					Terminate_CUR(TRUE);
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
							"Internal ERROR:\nCCurCreOM::ElementLeftUp_NOD\nINVALID m_SpnType");
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
				if(LeftUp_ROTATE_CUR(point)<0)
				{
					Terminate_CUR(TRUE);
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
				if(LeftUp_SCALE_CUR(point)<0)
				{
					Terminate_CUR(TRUE);
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
				if(LeftUp_REFLECT_CUR(point)<0)
				{
					Terminate_CUR(TRUE);
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
				if(LeftUp_SHEAR_CUR(point)<0)
				{
					Terminate_CUR(TRUE);
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
			if(LeftUp_CSPAWN(point)<0)
			////////////////
			{
				Terminate_CUR(TRUE);
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
			///////////////////	
			break;
		////////////////////////////////////////////////// STITCH	
		case COP_STITCH:
			
			m_bStitch = TRUE;
			///////		
			if(LeftUp_CSTITCH(point)<0)
			////////////////
			{
				Terminate_CUR(TRUE);
				return;
			}
			///////////////////	
			m_nInfoDone++;
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

int CCurCreOM::LeftUp_Curve_Accept(CPoint point)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(MESH1D);
//	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrMesh1D*	pDrCurve;
//	int			nActiveIndex,index;
	int			index;
	////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	WORtoWOP(&dTol,&dTol);	// physical
	///////////////////////////////////////////// See if any Existing Curve Hit
	index = IsObjectHit(MESH1D,point,0);
	////////////////////////////////////////////////////
	if(index<0)
		return -1; // No Curve Hit
	//////////////////////////////////////////////////////////////// Existing Curve
	pDrCurve	= (CDrMesh1D*)pDListMgr->GetObject(index);
	ID			= pDrCurve->GetObjectID();
	//////////////////////////////////////////////////////////////// for Stitching,Check Contiguity
	if(m_bStitch && !m_CurveList.IsEmpty())
	{
		if(IsInvalidSplicing(pDrCurve))
		return -1; // No Curve Hit
	}
	/////////////////////////////////////////
			pObjectMgr->ShowObject_On_Off(pDrCurve,MESH1D,TRUE);
/*
	pList = pObjectMgr->GetObjectList(MESH1D);
	nActiveIndex = pList->GetObjectIndex(MESH1D, ID);;
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
	pObjectMgr->SetActiveObjectType(MESH1D);		    // set Active Type									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,MESH1D);
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
//			nResult = ShowParentCurveInfo(pDrCurve);
			nResult = ShowParentCurveInfo(pDrCurve);
			/////////////
			if(nResult == IDYES)
				//////////////////////////////////////////////////////// Accept Old
				break;
			else
			if(nResult == IDNO)
			{
				//////////////////////////////////////////////////////// Retry
				index = IsObjectHit(MESH1D,point,startIndex);
				if(index>=0)
				{
					pDrCurve	= (CDrMesh1D*)pDListMgr->GetObject(index);
					ID		= pDrCurve->GetObjectID();
					///////////////////////////////////////// for Stitching,Check Contiguity
					if(m_bStitch)
					{
						if(IsInvalidSplicing(pDrCurve))
						return -1; // No Curve Hit
					}
					///////////////////////////////////////// 
			pObjectMgr->ShowObject_On_Off(pDrCurve,MESH1D,TRUE);
/*
					pList = pObjectMgr->GetObjectList(MESH1D);
					nActiveIndex = pList->GetObjectIndex(MESH1D, ID);;
					pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
					pObjectMgr->SetActiveObjectType(MESH1D);		    // set Active Index									
					pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,MESH1D);
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
	m_pCurrentCurve = pDrCurve;
	/////////
	return 0;
	/////////
}

BOOL CCurCreOM::IsInvalidSplicing(CDrMesh1D* pDrCurve)
{
	CDListMgr* pINList;
	//////////////////////////////////////////////////////// Last Curve
	pINList = m_pLastCurve->GetFE0DList(); 
	CDrFE0D* pNode_End = (CDrFE0D*)pINList->GetTail();
	//////////////////////////////////////////////////////// Current Curve
	pINList = pDrCurve->GetFE0DList(); 
	CDrFE0D* pNode_Beg = (CDrFE0D*)pINList->GetHead();
	////////////////////////////////////////////////////////
/*
		WORLD LocalPosB,LocalPosE;
		LocalPosB = *(pNode_Beg->GetLocalPos());
		LocalPosE = *(pNode_End->GetLocalPos());
*/
	/////////
	if(pNode_Beg->GetObjectID() != pNode_End->GetObjectID())
	{
		//////////////////////////////
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		int j;
		//////
		j = sprintf(buf,"***** INVALID SELECTION ****\n\n");
		//////////////////////////////////////
		j += sprintf(buf+j,"Curve is Not Contiguous to Previous Curve\n");
		j += sprintf(buf+j,"i.e., End Node of Previous Curve and Beginning\n");
		j += sprintf(buf+j,"Node of Current Curve do not have the same ID\n");
		j += sprintf(buf+j,"Select Curves that are Contiguous or Make sure\n");
		j += sprintf(buf+j,"that the Nodes of Contiguous Curves are Merged\n\n");
		//////////////////////////
		AfxMessageBox(*str,MB_OK|MB_ICONINFORMATION);
		return TRUE; // Invalid 
	}
	//////
	return FALSE;	// Valid 
}

int CCurCreOM::LeftUp_CSPAWN(CPoint point)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	////////////////
	int nResult;
	////////////
	nResult = LeftUp_GetCurve_Parent(point);
	///
	if(nResult<0)
		return nResult;
	////////////////////////////////////////
	nResult = ShowCurveToSpawn(m_pParentCurve,TRUE); // TRUE = With Dlg
	///////////
	if( nResult == -1)		// 
	{
		AfxMessageBox("ERROR:\nCCurMouse::LeftUp_CSpawn\nShowCurveToSpawn Problem");
		return -1;
	}
	////////////////////////////
	strCurr = "Ready for Spawning a MESH1D@";
	strCurr += "Click on a MESH1D to Spawn";
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->SetText(strCurr);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
	///////////
	if(nResult == -2)		// Cancel
		return -2;
	///
	return 0;
}

int CCurCreOM::ShowParentCurveInfo(CDrMesh1D* pDrCurve)
{
	int nResult = IDYES;
	/////////////////
	AfxMessageBox("CCurCreOM::ShowParentCurveInfo\nNot Done Yet");
	///
	return nResult;
}

int CCurCreOM::ShowCurveToSpawn(CDrMesh1D* pParentCurve,BOOL bUsingDlg)
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
		nResult = ShowCurveToSpawnCopyOff(pParentCurve,bUsingDlg);
		return nResult;
	}
	/////////////////////////////////////////////////////////////////////////// New Object
	strCurr = "Please Wait";
	///////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->SetText(strCurr);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
	///////////////////
	pObjectMgr->SetActiveObjectType(MESH1D);
	////////////////////////////////////////////////////////////////////////////// Add to DataBase
	int nActiveIndex;
	///////////////
	m_pSpawnedCurve	= (CDrMesh1D*)(pObjectMgr->AddToDataBase(nActiveIndex,MESH1D));
	m_pSpawnedCurve->SetShow(FALSE);	// not quite ready
	/////////////////////////////////////////////////////////////// Using CMI_CSPN
	CMI_1SPN MI_CSPN;
	///
	if(bUsingDlg)
	{
		m_pSpawnedCurve->SetObjectID(m_ObjID);
		///
		nResult = MI_CSPN.SpawnCurveShowingDlg(m_pSpawnedCurve,pParentCurve,pParentCurve,MESH1D);
	}
	else
	{
		pMATRIX	pXFMat	= m_pMatObj->GetMatrix();
		CString	SpawnID	= m_ObjID;
		////
		nResult = MI_CSPN.SpawnCurveWithoutDlg(m_pSpawnedCurve,pParentCurve,pXFMat,&m_SpawnedID,
												pParentCurve,MESH1D); 
	}
	if(nResult<0)
	{
		/////////////////////////////////////// Reset
		m_nInfoDone		= 0;
		m_bDone			= TRUE;	// 
		////////////////////////// Delete
		pObjectMgr->DeleteFromDataBase(nActiveIndex, MESH1D);
		m_pSpawnedCurve	= NULL;
		//////////////////////////
		return nResult;//
	}
	/////////////////////////////////////////////////////////// Control RectBound
//	m_pSpawnedCurve->SetDirty(TRUE);
	m_pSpawnedCurve->SetShow(TRUE);
	////////////////////////////////////////////////////////// Save
	pObjectMgr->ShowObject_On_Off(m_pSpawnedCurve,MESH1D,TRUE);
	///////////////////////////////
	return 0;
}	 

int CCurCreOM::ShowCurveToSpawnCopyOff(CDrMesh1D* pParentCurve,BOOL bUsingDlg)
{
	int	nResult;
	int index;
	///////////////////////
	CDrGrafFrame*	pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString			strCurr;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
//	CDListMgr* pList;
	////////////////////////////////
	strCurr = "Please Wait";
	///////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->SetText(strCurr);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
	///////////////////
	pObjectMgr->ShowObject_On_Off(pParentCurve,MESH1D,FALSE);
	//////////////////////
	if(!(pParentCurve->GetMs1List())->IsEmpty())
	{
#ifdef _DEBUG
		CString ObjID = pParentCurve->GetObjectID();
		CString strBum;
		if(ObjID == "M4")
			strBum = "Bum String M4";
#endif
		/////////////////////////////////////////////////////////// XForm Curve-dependent MESH1DS
		nResult = CurveDependent_SpawnConnectedObjects_CopyOff(pParentCurve,bUsingDlg,MESH1D);
		///
		if(nResult == -1)
			goto ERRORHANDLER;
		/////////////////////
	}
	//////////////////////////////////////////////
	if(!(pParentCurve->GetMs2List())->IsEmpty())
	{
		/////////////////////////////////////////////////////////// XForm Curve-dependent MESH2DES
		nResult = CurveDependent_SpawnConnectedObjects_CopyOff(pParentCurve,bUsingDlg,MESH2D);
		///
		if(nResult == -1)
			goto ERRORHANDLER;
		/////////////////////
	}
	//////////////////////////////////////////////
	if(!(pParentCurve->GetMs3List())->IsEmpty())
	{
		/////////////////////////////////////////////////////////// XForm Curve-dependent MESH3DS
		nResult = CurveDependent_SpawnConnectedObjects_CopyOff(pParentCurve,bUsingDlg,MESH3D);
		///
		if(nResult == -1)
			goto ERRORHANDLER;
		/////////////////////
	}
	//////////////////////////////////////////////
	if(!(pParentCurve->GetMbj3DList())->IsEmpty())
	{
		/////////////////////////////////////////////////////////// XForm Curve-dependent MBJ3DS
		nResult = CurveDependent_SpawnConnectedObjects_CopyOff(pParentCurve,bUsingDlg,MBJ3D);
		///
		if(nResult == -1)
			goto ERRORHANDLER;
		/////////////////////
	}
	///////////////////////////////////////////////// XForm Current Curve, if not done yet
	index = m_CDoneList.GetObjectIndex(pParentCurve);
	if(index<0)	// not done yet
	{
		/////////////////////////////////////////////////////////// XForm Current Curve
		nResult = CurveSpawnCopyOff(pParentCurve,bUsingDlg);
		///
		if(nResult == -1)
			goto ERRORHANDLER;
		/////////////////////
		m_CDoneList.InsertObject(pParentCurve);
	}
	///////////////////////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(pParentCurve,MESH1D,TRUE);
	////////////////////////////
	if(!bUsingDlg && m_pMatObj)
	{	
		delete m_pMatObj;	
		m_pMatObj = NULL;
	}
	/////////
	return 0;

ERRORHANDLER:
	AfxMessageBox("Internal ERROR\nCCurCreOM::ShowCurveToSpawnCopyOff");
	/////////////////////////////////////// Reset
	m_nInfoDone		= 0;
	m_bDone			= TRUE;	// 
	//////////////////////////
	m_pSpawnedNode	= NULL;
	//////////////////////////
	return nResult;//
	////////
}
	 
int CCurCreOM::CurveDependent_SpawnConnectedObjects_CopyOff(CDrMesh1D* pCurrentCurve,BOOL bUsingDlg,
																					UINT nObjType)
{
#ifdef _DEBUG
		CString ObjID = pCurrentCurve->GetObjectID();
		CString strBum;
		if(ObjID == "M5")
			strBum = "Bum String M5";
#endif
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////// XForm Node-dependent OBJECTS
	int nResult = 0;
	////////////////
	CDListMgr* pList;
	int i,nCount;
	//////////////////////////////////////////////// Objects
	switch(nObjType)
	{
		case MESH1D:
			pList	= pCurrentCurve->GetMs1List();
			break;
		case MESH2D:
			pList	= pCurrentCurve->GetMs2List();
			break;
		case MESH3D:
			pList	= pCurrentCurve->GetMs3List();
			break;
		case MBJ3D:
			pList	= pCurrentCurve->GetMbj3DList();
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
#ifdef _DEBUG
		CString ObjID = ((CDrObject*)pObject)->GetObjectID();
		CString strBum;
		if(ObjID == "M5")
			strBum = "Bum String M5";
#endif
		////////////////
		if(pObject)
		{
			switch(nObjType)
			{
				case MESH1D:

					pObjectMgr->ShowObject_On_Off((CDrObject*)pObject,MESH1D,FALSE);
					///
					nResult = CurTopo_SpawnConnectedCurves_CopyOff((CDrMesh1D*)pObject,bUsingDlg);
					///
					pObjectMgr->ShowObject_On_Off((CDrObject*)pObject,MESH1D,TRUE);
					break;

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
					"Internal ERROR\nCCurCreOM::CurveDependent_SpawnConnectedObjects_CopyOff");
				return nResult;
			}
		}
	}
	/////////////////////
	return nResult;
}

int CCurCreOM::CurveSpawnCopyOff(CDrMesh1D* pParentCurve,BOOL bUsingDlg)
{
	int nResult;
	C3DMath			Math3D;
	///////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///////////////////
	pObjectMgr->SetActiveObjectType(MESH1D);
	/////////////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(pParentCurve,MESH1D,FALSE);
	///////////////////////////////
	CDrMesh1D* pSpawnedCurve = pParentCurve;
	/////////////////////////////////////////////////////////////// Using CMI_CSPN
	CMI_1SPN MI_CSPN;
	/////////////////
	MI_CSPN.SetNDoneList(&m_NDoneList);
	MI_CSPN.SetCDoneList(&m_CDoneList);
	MI_CSPN.SetPDoneList(&m_PDoneList);
	MI_CSPN.SetSDoneList(&m_SDoneList);
	MI_CSPN.SetODoneList(&m_ODoneList);
	//////////////////////////////////////
	m_ObjID = pParentCurve->GetObjectID();
	///////////////////////////////////
	if(bUsingDlg)
	{
//		pSpawnedCurve->SetObjectID(m_ObjID);
		///
		nResult = MI_CSPN.SpawnCurveShowingDlg((CDrMesh1D*)pSpawnedCurve,pParentCurve,pParentCurve,MESH1D);
	}
	else
	{
		pMATRIX	pXFMat	= m_pMatObj->GetMatrix();
		CString	SpawnID	= m_ObjID;
		////
		nResult = MI_CSPN.SpawnCurveWithoutDlg(pSpawnedCurve,pParentCurve,pXFMat,&m_ObjID,
												pParentCurve,MESH1D); 
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
	pObjectMgr->ShowObject_On_Off(pParentCurve,MESH1D,TRUE);
	///////////////////////////////
	return 0;
}	 

int CCurCreOM::LeftUp_CSTITCH(CPoint point)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	////////////////
	int nResult;
	///////////////////////////////////////////// See if any Existing Curve Hit
	nResult = LeftUp_Curve_Accept(point);	// TRUE = Parent
	///
	if(nResult<0)
		return nResult;
	//////////////////////////////////////////////// Save it in the List
	m_CurveList.InsertObject(m_pCurrentCurve);
	m_pLastCurve = m_pCurrentCurve; 
	////////////////////////////////////////////////
	strCurr = "Merging MESH1Ds. CLICK On Another";
	strCurr += "@MESH1D or CLICK In Right Mouse Button";
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->SetText(strCurr);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
	///////////
	return 0;
}

int CCurCreOM::Update_Status_CSTITCH()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	////////////////////////////
	strCurr = "Ready for Another Stitching";
	strCurr += "@CLICK On a MESH1D to Stitch In";
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->SetText(strCurr);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
	///////////
	return 0;
}

int CCurCreOM::ShowCProfileToStitch()
{

	CDrGrafFrame*	pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString			strCurr;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CMsObjMgr* pMsObjMgr	= pDoc->GetMsObjMgr();
	////////////////////////////////
	strCurr = "Please Wait";
	///////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->SetText(strCurr);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
	///////////////////
	pObjectMgr->SetActiveObjectType(MESH1D);
	////////////////////////////////////////////////////////////////////////////// Add to DataBase
	//			.Add to DataBase
	/////////////////////////////////////
	int nActiveIndex;
	///////////////
	m_pCProfile	= (CDrProf_1*)(pObjectMgr->AddToDataBase(nActiveIndex,M1_PROFILE));
	m_pCProfile->SetShow(FALSE);	// not quite ready
	/////////////////////////////////////////////////////////////// ID
	m_pCProfile->SetObjectID(m_SpawnedID);	
	/////////////////////////////////////////////////////////////// Insert CurveList
	(m_pCProfile->GetMs1List())->AddTail(&m_CurveList);
	m_CurveList.RemoveAll();
	/////////////////////////////////////////////////////////////// LMList
	MATRIX		Mat;
	pMATRIX		pM = &Mat;
	///
	C3DMath	Math3D;
	Math3D.GetIdentityMATRIX(pM);
	///////////////////////////////////////////////////// Save: Defaults	
	CMatObj* pMatObj = new CMatObj;
	///////
	pMatObj->SetInstanced_Prof(FALSE);
	pMatObj->SetMatrix(pM);
	pMatObj->SetCurveLatch(CL_FORWARD);	// ALWAYS for Now
	///////////////////////////////////////////////////// save in the list
	int nCount = (m_pCProfile->GetMs1List())->GetCount();
	for (int c=0;c<nCount;c++)
		m_LMList.InsertObject(pMatObj);	// same One
	///////////////////////////////////////////////////// Insert LMList
	(m_pCProfile->GetLMList())->AddTail(&m_LMList);
	m_LMList.RemoveAll();
	/////////////////////////////////////////////////////////////// Using CMI_CProf
	CMI_1Prof MI_CProf;
	int nResult;
	////
	nResult = MI_CProf.RBUp_1Profile(m_pCProfile); // NOT Using Dlg (Used for Now)
	///
	if(nResult<0)
	{
		/////////////////////////////////////// Reset
		m_nInfoDone		= 0;
		m_bDone			= TRUE;	//
		m_CurveList.RemoveAll();
		////////////////////////// Delete
		pObjectMgr->DeleteFromDataBase(nActiveIndex, C_PROFILE);
		m_pCProfile	= NULL;
		//////////////////////////
		return nResult;//
	}
	///////////////////////////////
	m_pCProfile->SetShow(FALSE);
	/////////////////////////////// 
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(MESH1D);
	///////////////////////////////////////////////////////////////
	CDrMesh1D* pCurve = m_pCProfile->GetMesh1D();
	pCurve->SetShow(TRUE);
	pCurve->SetDirty(TRUE);
	//////////////////////////////////////////
			pObjectMgr->ShowObject_On_Off(pCurve,MESH1D,TRUE);
/*
	CString CurveID	= pCurve->GetObjectID();
	int nCurveIndex = pDListMgr->GetObjectIndex(MESH1D,CurveID); 
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nCurveIndex); 
	pObjectMgr->SetActiveObjectType(MESH1D);
    ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nCurveIndex,MESH1D);
	/////////
*/
	/////////
	return 0;
}	 

void CCurCreOM::OnEBoxMouseMove_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CCurCreOM::OnEBoxLButtonUp_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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
		ElementLeftUp_CUR(Logpoint);
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftUp_I();
	/////////////////////////
	
}

void CCurCreOM::OnEBoxRButtonDown_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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
		case MESH1D:
			break;
		////////////////////////////////////////////////// Patch
		default:
			break;
	}  
}

void CCurCreOM::OnEBoxRButtonUp_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	//////////////////////////////////////////////////////////////////
	CString ID;
	CString* pID = &ID;
	///////////////////////////////////////////////////////// Is Enough Info?
	if(RightUp_Premature()<0)
		return;
	///////////////////////////////////////////////////////// Not Auto Accept
	if(m_bStitch)
	{
		if(RightUp_NotAutoAccept_STITCH()<0)
		{
			Terminate_CUR(TRUE);
			return;
		}
	}
	else
	{
		////////////////////////////////////////////////// Update Info
		UpdateDlg_TRUE();
		/////////////////
		if(RightUp_NotAutoAccept()<0)
		{
			Terminate_CUR(TRUE);
			return;
		}
	}
	///////////////////////////////////////////////////// Show Spawned Node 
	switch(m_nActiveTool) 
	{

		case COP_TRANSLATE:
						
			
			SetUpLocalM_XLATE();
			/////////////////////////////
			if(ShowCurveToSpawn(m_pParentCurve,FALSE)<0)		 //FALSE = NoDlg
			////////////////
			{
				Terminate_CUR(TRUE);
				return;
			}
			else
			{
				Terminate_CUR(FALSE);
				Init_CUR();
				/////////////////////////
				UpdateDlg_FALSE_XLATE();
				break;
			}
			///////////////////	
			break;

			
		case COP_ROTATE:
						
			
			SetUpLocalM_ROTATE();
			/////////////////////////////
			if(ShowCurveToSpawn(m_pParentCurve,FALSE)<0)		 //FALSE = NoDlg
			////////////////
			{
				Terminate_CUR(TRUE);
				return;
			}
			else
			{
				Terminate_CUR(FALSE);
				Init_CUR();
				/////////////////////////
				UpdateDlg_FALSE_ROTATE();
				break;
			}
			///////////////////	
			break;
		
		case COP_SCALE:
						
			
			SetUpLocalM_SCALE();
			/////////////////////////////
			if(ShowCurveToSpawn(m_pParentCurve,FALSE)<0)		 //FALSE = NoDlg
			////////////////
			{
				Terminate_CUR(TRUE);
				return;
			}
			else
			{
				Terminate_CUR(FALSE);
				Init_CUR();
				/////////////////////////
				UpdateDlg_FALSE_SCALE();
				break;
			}
			///////////////////	
			break;
		
		case COP_REFLECT:
						
			
			SetUpLocalM_REFLECT();
			/////////////////////////////
			if(ShowCurveToSpawn(m_pParentCurve,FALSE)<0)		 //FALSE = NoDlg
			////////////////
			{
				Terminate_CUR(TRUE);
				return;
			}
			else
			{
				Terminate_CUR(FALSE);
				Init_CUR();
				/////////////////////////
				UpdateDlg_FALSE_REFLECT();
				break;
			}
			///////////////////	
			break;
		
		case COP_SHEAR:
						
			
			SetUpLocalM_SHEAR();
			/////////////////////////////
			if(ShowCurveToSpawn(m_pParentCurve,FALSE)<0)		 //FALSE = NoDlg
			////////////////
			{
				Terminate_CUR(TRUE);
				return;
			}
			else
			{
				Terminate_CUR(FALSE);
				Init_CUR();
				/////////////////////////
				UpdateDlg_FALSE_SHEAR();
				break;
			}
			///////////////////	
			break;



		case COP_SPAWN:
		
			//////////////////////////// 	
			return;
		

		
		case COP_STITCH:
						
			
			/////////////////////////////
			if(ShowCProfileToStitch()<0)		
			////////////////
			{
				Terminate_CUR(TRUE);
				return;
			}
			else
			{
				Terminate_CUR(FALSE);
				Init_CUR();
				/////////////////////////
				Update_Status_CSTITCH();
				break;
			}
			///////////////////	
			break;
		//////////////	
		default:  
			return;
	} 
	////////////////////////////////////////////////////////////////////////
	CMI_Gang0 Gang0;
	Gang0.SetElemInfoID(m_SpawnedID,MESH1D);		
	////////////////////////////////////////////////////////////////////////
}

int CCurCreOM::RightUp_NotAutoAccept_STITCH()
{
/*
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr*	pList;
*/
	////////////////////////////////////////////////////// 
	int nAnswer = IDOK;
	////////////////////////////////
	if(!m_bAutoAcceptOn)
	{
		///////////////////////////////////////////////////////////// show Info
		nAnswer = ShowInputInfo_STITCH();
		if(nAnswer == -1)
			return -1;
		/////////////////////////
		if(nAnswer == -2)
		{
			CString* str = new CString;
			char* buf	= str->GetBuffer(BUFF_SIZE);
			sprintf(buf,"Do You Want to Delete\nCurrent Curve Profile to Start Allover");
			/////////////////////////	
			nAnswer = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
			delete str;
			/////////////////////////
			if(nAnswer == IDYES)		//delete
			{
				/////////////////////////////////////// Reset
				m_nInfoDone		= 0;	// 
				m_bDone			= TRUE;	// 
				/////////////////////////////////////
				return -1;
			}
		}
		/////////////////////
		return 0; 
	}
	/////////
	return 0;
}

int CCurCreOM::ShowInputInfo_STITCH()
{
	UINT nAnswer;
	///////////////////////////////////////////////////////////// show Info:DoModal
	CMMs1Mgr	MMs1Mgr;
	nAnswer = MMs1Mgr.DoModal_Merge_1_ShowInfo(&m_SpawnedID,&m_CurveList);  	//Profile
	if(nAnswer == IDCANCEL)
		return -2;	// CAncel
	else
		return 0;
}

long CCurCreOM::CreateorActivateCreOp_CUR(UINT wParam, long lParam)
{
	/////////////////////////////////////////// Parent Info
	m_ParentType	= MESH1D;
	m_strParentType = "Curve";
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
		Init_CUR();

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
		case COP_STITCH:
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
	 
long CCurCreOM::GoodByeCreOp_CUR(UINT wParam, long lParam)
{
	
	GetCreOpDlg()->DestroyWindow();
	////////////////
	{
		Terminate_CUR(FALSE);
		return 0L;
	}
	//////////
	return 0L;
}
	 
long CCurCreOM::CancelCreOp_CUR(UINT wParam, long lParam)
{
	
	GetCreOpDlg()->DestroyWindow();
	////////////////
	{
		Terminate_CUR(FALSE);
		return 0L;
	}
	//////////
	return 0L;
}
	 
/////////////////////////////////////////////////////////////////////////////////////// 
UINT CCurCreOM::ReSetToolID_CUR(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	///////////////////////////////////
	if(IGenID != MESH1D)
	{
		str = "UNKNOWN";	ID	= UNONE;
		pWnd->SetstrIGenID(str);
		////////////////////////
		return UNONE;
	}
	//////////////////////////////////////////// TaskID
	if(OperID == COP_STITCH)
		strCur = "Ready for Curve Profile@";
	else
		strCur = "Ready for Spawning a Curve@";
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
					str	= "MESH1D";		ID	= COP_TRANSLATE;
						strCur += "Click on a MESH1D to Translate";
					break;
				//////////////////////////////////////////// Create
				case COP_ROTATE:
					///////////////////////////// String
					str = "ROTATE";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "MESH1D";		ID	= COP_ROTATE;
						strCur += "Click on a MESH1D to Rotate";
					break;
				//////////////////////////////////////////// Create
				case COP_SCALE:
					///////////////////////////// String
					str = "SCALE";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "MESH1D";		ID	= COP_SCALE;
						strCur += "Click on a MESH1D to Scale";
					break;
				//////////////////////////////////////////// Create
				case COP_REFLECT:
					///////////////////////////// String
					str = "REFLECT";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "MESH1D";		ID	= COP_REFLECT;
						strCur += "Click on a MESH1D to Reflect";
					break;
				//////////////////////////////////////////// Create
				case COP_SHEAR:
					///////////////////////////// String
					str = "SHEAR";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "MESH1D";		ID	= COP_SHEAR;
						strCur += "Click on a MESH1D to Shear";
					break;
				//////////////////////////////////////////// Create
				case COP_SPAWN:

					Init_CUR();	// No Modeless Dlg, so Init Here
					///////////////////////////// String
					str = "SPAWN";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "MESH1D";		ID	= COP_SPAWN;
						strCur = "Composite Affine/Symmetry Transformations@";
						strCur += "Click on a MESH1D to Spawn";
					break;
				//////////////////////////////////////////// Create
				case COP_STITCH:

					Init_CUR();	// No Modeless Dlg, so Init Here
					///////////////////////////// String
					str = "STITCH";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "MESH1D";		ID	= COP_STITCH;
						strCur += "Click on a MESH1D to Stitch In";
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

void CCurCreOM::Serialize(CArchive& ar)
{

	CNodCreOM::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CurCreOM:    Storing\n");	
		

	}
	else
	{
		TRACE(" CurCreOM:    Loading\n");	

	
	}        
}
///////////////////////////////////// end of Module //////////////////////		

