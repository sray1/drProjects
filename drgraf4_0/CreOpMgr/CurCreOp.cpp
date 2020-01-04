// Mouse.cpp : implementation file
//


#include "stdafx.h" 
#include <math.h>
#include <float.h>		// DBL_MIN
#include <afxtempl.h>	// CList


#include "3DMath.h"
#include "XForm.h"
/////////////////////
#include "drgraf.h"
#include "drgrafrm.h"
#include "UserMsg.h"
#include "drawView.h"
#include "Def_MouseAct.h"                    
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "DListMgr.h"
/////////////////////
#include "Def_IGen.h"                    
#include "Def_Elem.h"                    
///////////////////// dialogMgr
#include "MNodMgr.h"  
#include "MCurMgr.h"	// for stitching
#include "Dlg_CurveBlend.h"
////////////////////// 
#include "MI_GangC.h" 
#include "MC_Circle.h" 
#include "MC_Parab.h" 
#include "MI_CSPN.h" 
#include "MI_CProf.h" 
#include "Dlg_CrOI.h"
//////////////////////
#include "CurCreOp.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
///////////////////////////////////////////////////////////////////////////////////////////
// if CURVE_SPAWN: Object Grab Node Same As Node
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
IMPLEMENT_SERIAL(CCurCreOp,CNodCreOp,1)
/////////////////////////////////////////////////////////////////////////////
CCurCreOp::CCurCreOp()
{
	m_bStitch		= FALSE;
	m_bBlend		= FALSE;
	m_bDoModalDone	= FALSE;
}

CCurCreOp::~CCurCreOp()
{
}

void CCurCreOp::Init_CUR()
{
	Init_NOD();
	//////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////
	pObjectMgr->SetObjInfoID(m_SpawnedID,CURVE);
	m_SpawnedID	+= "_Cu";
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

void CCurCreOp::Terminate_CUR(BOOL bError)
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

void CCurCreOp:: ElementLeftDown_CUR()
{	
	ElementLeftDown_NOD();
}

void CCurCreOp::OnEBoxLButtonDown_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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
	pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
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

int CCurCreOp::LeftUp_GetCurve_Parent(POINT point)
{
	int nResult;
	///////////////////////////////////////////// See if any Existing Node Hit
	nResult = LeftUp_Curve_Accept(point);	// TRUE = Parent
	///////////////////
//	if(nResult < 0)
	if(nResult != MA_OK)
		return nResult; // Cancel or No Hit
	///////
	switch(m_nInfoDone)
	{
		case 0:	// 
			m_pParentCurve	= m_pCurrentCurve;
			m_ParentID		= m_pParentCurve->GetObjectID();
			break;
		default:
//			return -1;
			return MA_ERROR;
	}
	//////////////////////////////////////
//	return 0;
	return MA_OK;
}

int CCurCreOp::LeftUp_TRANSLATE_CUR(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Curve	
			nResult = LeftUp_GetCurve_Parent(point);
//			if(nResult<0)
			return nResult;
//			return 0;
		case 1://	Grab Node	
		case 2://	To Node
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_XLATE(point,TRUE);		// try CNODE
//			if(nResult == 0 || nResult == -2)
			if(nResult != MA_OK)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_XLATE(point,FALSE);	// try INODE
//			if(nResult < 0)
			return nResult;
			////////
		default:
			break;
	}
//	return -1;
	return MA_ERROR;
}

int CCurCreOp::LeftUp_ROTATE_CUR(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Curve	
			nResult = LeftUp_GetCurve_Parent(point);
//			if(nResult<0)
			return nResult;
//			return 0;
		case 1://	Grab Node	
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,TRUE);		// try CNODE
//			if(nResult == 0 || nResult == -2)
			if(nResult != MA_OK)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);		// try INODE
//			if(nResult < 0)
				return nResult;
			//
//			return 0;
			////////
		case 2://		// From Rot Direction if Not AngleIn
			if(m_bAngleIn)
//				return -1;
				return MA_ERROR;
			//////////////
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,TRUE);		// try CNODE
//			if(nResult == 0 || nResult == -2)
			if(nResult != MA_OK)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);		// try INODE
//			if(nResult < 0)
				return nResult;
			//
//			return 0;
			////////
		case 3://		// To Rot Direction
			if(m_bAngleIn || m_bAxis)
//				return -1;
				return MA_ERROR;
			//////////////
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,TRUE);		// try CNODE
//			if(nResult == 0 || nResult == -2)
			if(nResult != MA_OK)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);		// try INODE
//			if(nResult < 0)
				return nResult;
			//
//			return 0;
			////////
		case 4://		// From Rot Direction if Not AngleIn
			if(m_bAngleIn || m_SpnType == SPN_ROT_ABT_LINE || m_bAxis)
				return -1;
				return MA_ERROR;
			//////////////
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,TRUE);		// try CNODE
//			if(nResult == 0 || nResult == -2)
			if(nResult != MA_OK)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);	// try INODE
//			if(nResult < 0)
				return nResult;
			//
//			return 0;
			////////
		case 5://		// To Rot Direction
			if(m_bAngleIn || m_SpnType == SPN_ROT_ABT_LINE || m_bAxis)
//				return -1;
				return MA_ERROR;
			//////////////
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,TRUE);		// try CNODE
//			if(nResult == 0 || nResult == -2)
			if(nResult != MA_OK)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);		// try INODE
//			if(nResult < 0)
				return nResult;
			//
//			return 0;
			////////
		default:
			break;
	}
//	return -1;
	return MA_ERROR;
}

int CCurCreOp::LeftUp_SCALE_CUR(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Curve	
			nResult = LeftUp_GetCurve_Parent(point);
//			if(nResult<0)
				return nResult;
//			return 0;
		case 1://	Grab Node	
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_SCALE(point,TRUE);		// try CNODE
//			if(nResult == 0 || nResult == -2)
			if(nResult != MA_OK)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_SCALE(point,FALSE);	// try INODE
//			if(nResult < 0)
				return nResult;
			//
//			return 0;
		case 2:		// Force Dialog entry
			return MA_CANCEL;
		default:
			break;
	}
//	return -1;
	return MA_ERROR;
}

int CCurCreOp::LeftUp_REFLECT_CUR(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Curve	
			nResult = LeftUp_GetCurve_Parent(point);
//			if(nResult<0)
				return nResult;
//			return 0;
		case 1://	Ist Pt. or Node On Plane	
		case 2://	2nd Pt. or Node On Plane OR Ist Pt. on Normal	
		case 3://	Pt. or Node On Plane OR 2nd Pt. on Normal	
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_REFLECT(point,TRUE);		// try CNODE
//			if(nResult == 0 || nResult == -2)
			if(nResult != MA_OK)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_REFLECT(point,FALSE);		// try INODE
//			if(nResult < 0)
				return nResult;
			//
//			return 0;
			////////
		default:
			break;
	}
//	return -1;
	return MA_ERROR;
}

int CCurCreOp::LeftUp_SHEAR_CUR(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Curve	
			nResult = LeftUp_GetCurve_Parent(point);
//			if(nResult<0)
				return nResult;
//			return 0;
		case 1://	Grab Node	
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_SHEAR(point,TRUE);		// try CNODE
//			if(nResult == 0 || nResult == -2)
			if(nResult != MA_OK)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_SHEAR(point,FALSE);	// try INODE
//			if(nResult < 0)
				return nResult;
			//
//			return 0;
			////////
		case 2:		// Force Dialog entry
			return MA_CANCEL;
		default:
			break;
	}
//	return -1;
	return MA_ERROR;
}

void CCurCreOp::ElementLeftUp_CUR(CPoint point)
{                          
	int nResult = 0;
	////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	//////////////////////////////////////////////////////////////////
//	char buf[20];
	CString Nid;
	BOOL bRightOn	= FALSE;
	m_bStitch		= FALSE;
	m_bBlend		= FALSE;
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
//				if(LeftUp_TRANSLATE_CUR(point)<0)
				nResult = LeftUp_TRANSLATE_CUR(point);
				if(nResult == MA_ERROR || nResult == MA_CANCEL)
				{
					Terminate_CUR(TRUE);
					return;
				}
				else
				if(nResult == MA_NOHIT)
					return;
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
//				if(LeftUp_ROTATE_CUR(point)<0)
				nResult = LeftUp_ROTATE_CUR(point);
				if(nResult == MA_ERROR || nResult == MA_CANCEL)
				{
					Terminate_CUR(TRUE);
					return;
				}
				else
				if(nResult == MA_NOHIT)
					return;
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
//				if(LeftUp_SCALE_CUR(point)<0)
				nResult = LeftUp_SCALE_CUR(point);
				if(nResult == MA_ERROR || nResult == MA_CANCEL)
				{
					Terminate_CUR(TRUE);
					return;
				}
				else
				if(nResult == MA_NOHIT)
					return;
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
//				if(LeftUp_REFLECT_CUR(point)<0)
				nResult = LeftUp_REFLECT_CUR(point);
				if(nResult == MA_ERROR || nResult == MA_CANCEL)
				{
					Terminate_CUR(TRUE);
					return;
				}
				else
				if(nResult == MA_NOHIT)
					return;
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
//				if(LeftUp_SHEAR_CUR(point)<0)
				nResult = LeftUp_SHEAR_CUR(point);
				if(nResult == MA_ERROR || nResult == MA_CANCEL)
				{
					Terminate_CUR(TRUE);
					return;
				}
				else
				if(nResult == MA_NOHIT)
					return;
			}
			/////////////
			m_nInfoDone++;
				UpdateDlg_FALSE_SHEAR();
				///////
				return;
		////////////////////////////////////////////////// SPAWN	
		case COP_SPAWN:				// 
			///////		
//			if(LeftUp_CSPAWN(point)<0)
			nResult = LeftUp_CSPAWN(point);
			////////////////
			if(nResult == MA_ERROR || nResult == MA_CANCEL)
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
			nResult = LeftUp_CSTITCH(point);
//			if(nResult == -1)	// Error: start again
			if(nResult == MA_ERROR || nResult == MA_CANCEL)	// Error/Cancel: start again
			////////////////
			{
				Terminate_CUR(TRUE);
				return;
			}
			else
//			if(nResult == -3)	// Invalid curve: No hit
			if(nResult == MA_NOHIT)	// Invalid curve: No hit
				return;
			///////////////////	
			m_nInfoDone++;
			return;
		////////////////////////////////////////////////// BLEND	
		case COP_BLEND:
			
			m_bBlend = TRUE;
			///////		
			nResult = LeftUp_CBLEND(point);
//			if(nResult == -1)	// Error: start again
			if(nResult == MA_ERROR || nResult == MA_CANCEL)	// Error/Cancel: start again
			////////////////
			{
				Terminate_CUR(TRUE);
				return;
			}
			else
//			if(nResult == -3)	// Invalid curve: No hit
			if(nResult == MA_NOHIT)	// Invalid curve: No hit
				return;
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

int CCurCreOp::LeftUp_Curve_Accept(CPoint point)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(CURVE);
//	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrCurve*	pDrCurve;
//	int			nActiveIndex,index;
	int			index;
	////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	WORtoWOP(&dTol,&dTol);	// physical
	///////////////////////////////////////////// See if any Existing Curve Hit
	index = IsObjectHit(CURVE,point,0);
	////////////////////////////////////////////////////
	if(index<0)
//		return -1; // No Curve Hit
		return MA_NOHIT; // No Curve Hit
	//////////////////////////////////////////////////////////////// Existing Curve
	pDrCurve	= (CDrCurve*)pDListMgr->GetObject(index);
	ID			= pDrCurve->GetObjectID();
	if(pDrCurve->IsClosed_S() && (m_nActiveTool == COP_STITCH))
	{
		AfxMessageBox("ERROR:\nCurve is Closed\nClosed Curve Can Not be Spliced !!");
//		return -1; // No Curve Hit
		return MA_NOHIT; // No Curve Hit
	}
	//////////////////////////////////////////////////////////////// for Stitching,Check Contiguity
	if(m_bStitch && !m_CurveList.IsEmpty())
	{
		if(IsInvalidSplicing(pDrCurve))
//			return -1; // No Curve Hit
			return MA_NOHIT; // No Curve Hit
	}
	/////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(pDrCurve,CURVE,TRUE);
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
				index = IsObjectHit(CURVE,point,startIndex);
				if(index>=0)
				{
					pDrCurve	= (CDrCurve*)pDListMgr->GetObject(index);
					ID		= pDrCurve->GetObjectID();
					///////////////////////////////////////// for Stitching,Check Contiguity
					if(m_bStitch)
					{
						if(IsInvalidSplicing(pDrCurve))
//						return -1; // No Curve Hit
						return MA_NOHIT; // No Curve Hit
					}
					///////////////////////////////////////// 
					pObjectMgr->ShowObject_On_Off(pDrCurve,CURVE,TRUE);
					////////////////////////////////////////
					startIndex  = index+1;
					/////////////////////
				}
				else
					////////////////
//					return -2;
					return MA_CANCEL;
				/////////
			}
			else				// Cancel
				//////////////////////////////////////////////////////// Do Nothing
//				return -2;
				return MA_CANCEL;
		}						// end for loop
		///////////////////////////////////////
	}				// end !AutoAccept loop
	//////////////////////////////////////////////////////////////////// finally, accept
	m_pCurrentCurve = pDrCurve;
	/////////
//	return 0;
	return MA_OK;
	/////////
}

BOOL CCurCreOp::IsInvalidSplicing(CDrCurve* pDrCurve)
{
	C3DMath Math3D;
	////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	///////////////////////////////////////////////
	CDListMgr* pCNList;
	//////////////////////////////////////////////////////// Last Curve
	pCNList = m_pLastCurve->GetCNodeList(); 
	CDrNode* pNode_End = (CDrNode*)pCNList->GetTail();
	//////////////////////////////////////////////////////// Current Curve
	pCNList = pDrCurve->GetCNodeList(); 
	CDrNode* pNode_Beg = (CDrNode*)pCNList->GetHead();
	////////////////////////////////////////////////////////
	WORLD LocalPosB,LocalPosE;
	LocalPosB = *(pNode_Beg->GetLocalPos());
	LocalPosE = *(pNode_End->GetLocalPos());
	/////////
//	if(pNode_Beg->GetObjectID() != pNode_End->GetObjectID())
	if(!Math3D.AreSame_WORLD(&LocalPosB, &LocalPosE,pHitNet->GetDblRatio()) )
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
		j += sprintf(buf+j,"Node of Current Curve do not have the same Coordinates\n");
		j += sprintf(buf+j,"Select Curves that are Contiguous or Make sure\n");
		j += sprintf(buf+j,"that the Nodes of Contiguous Curves are Merged\n\n");
		//////////////////////////
		AfxMessageBox(*str,MB_OK|MB_ICONINFORMATION);
		return TRUE; // Invalid 
	}
	//////
	return FALSE;	// Valid 
}

int CCurCreOp::ShowParentCurveInfo(CDrCurve* pDrCurve)
{
	int nResult;
	CString ID;
	CString* pID = &ID;
	ID = pDrCurve->GetObjectID();
	//////////////////////////////////////////////////////////////////////
	CDListMgr*		pNodeList	= pDrCurve->GetINodeList();
    CList<int,int>* pElSegList	= pDrCurve->GetElperSegList_S();
	CURVEPROC 		CurveType	= pDrCurve->GetCurveType_S();
	CIRCLETYPE		CircType	= pDrCurve->GetCircleType();
	double			dAng		= pDrCurve->GetTheta_S();
	BOOL			bArc		= pDrCurve->IsArcType();
	BOOL			bClosed		= pDrCurve->IsClosed_S();
	double			dAngSpec	= pDrCurve->GetTheta_S();
	double			dRadius		= pDrCurve->GetRadius_S();
	///////////////////////////
	CString			FromID = "";
	CString			ToID = "";
	CString			CCID = "";
	CString			TIID = "";
	CString			CAID = "";
	CString			CBID = "";
	CDrNode*		pCN; 
	/////////////////////////////////////////////////////////////////////// total elems
	int nElems = 0;
	if(!(pElSegList->IsEmpty()))
	{
		for (POSITION posI = pElSegList->GetHeadPosition( );posI !=NULL;)
		{
			////
			nElems += pElSegList->GetNext(posI); 
		}
	}
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	//////
	if(m_bStitch)
		j = sprintf(buf,"***** A Curve_To_Stitch_In Hit ****\n");
	else
	if(m_bBlend)
		j = sprintf(buf,"***** A Curve_To_Blend_In Hit ****\n");
	else
		j = sprintf(buf,"***** A Curve_To_Spawn_From Hit ****\n");
	//////////////////////////////////////
	switch(CurveType)
	{
		case CP_CIRCLE:

			pCN = pDrCurve->GetCNode_CC(); 
			if(pCN)
				CCID = (pDrCurve->GetCNode_CC())->GetObjectID();
			pCN = pDrCurve->GetCNode_TI(); 
			if(pCN)
				TIID = (pDrCurve->GetCNode_TI())->GetObjectID();
			pCN = pDrCurve->GetCNode_CA(); 
			if(pCN)
				CAID = (pDrCurve->GetCNode_CA())->GetObjectID();
			pCN = pDrCurve->GetCNode_CB(); 
			if(pCN)
				CBID = (pDrCurve->GetCNode_CB())->GetObjectID();
			////////////////
			switch(CircType)
			{
				
				case CIRCLE_BY_ROT:

					FromID	= pDrCurve->GetFromIDNode_S()->GetObjectID();
					ToID	= pDrCurve->GetToIDNode_S()->GetObjectID();
					//////////////////////////////////////////////////////
					j += sprintf(buf+j,"Circle %s contains:\n\t%d InputNode to Rotate\n\t%d Elements\n",
							*pID,pNodeList->GetCount(),nElems);
					j += sprintf(buf+j,"\t%s and %s are Axis Nodes\n",FromID,ToID);
					if(dAng == 360.)
						j += sprintf(buf+j,"\tClosed Circle\n");
					else
						j += sprintf(buf+j,"\t%f is Angle of Rotation\n",dAng);
					break;
				
				case CIRCLE_BY_NO3:

					j = sprintf(buf,"Circle %s contains:\n\t%d Input Nodes\n\t%d Elements\n",
							*pID,pNodeList->GetCount(),nElems);
					if(bClosed)
						j += sprintf(buf+j,"\tClosed Circle\n");
					else
					{
						if(bArc)
							j += sprintf(buf+j,"\tArc upto 3rd Node\n");
						else
							j += sprintf(buf+j,"\t%f is Angle of Rotation\n",dAngSpec);
					}
					break;
				
				
				case CIRCLE_BY_2N_TI:

					j = sprintf(buf,"Circle %s contains:\n\t%d Input Nodes\n\t%d Elements\n",
							*pID,pNodeList->GetCount(),nElems);
					j += sprintf(buf+j,"2 End Nodes & Tangent Intersection\n");
					j += sprintf(buf+j,"\t%s is Tangent Intersection Node\n",TIID);
					break;
				
				
				case CIRCLE_BY_2N_CC:

					j = sprintf(buf,"Circle %s contains:\n\t%d Input Nodes\n\t%d Elements\n",
							*pID,pNodeList->GetCount(),nElems);
						j += sprintf(buf+j,"2 End Nodes & Center\n");
						j += sprintf(buf+j,"\t%s is Center Node\n",CCID);
						break;
						
				case CIRCLE_BY_2CN_TI_R:

					j = sprintf(buf,"Circle %s contains:\n\t%d InPut Nodes\n\t%d Elements\n\tRadius = %f\n",
							*pID,pNodeList->GetCount(),nElems,dRadius);
					j += sprintf(buf+j,"2 Control Nodes on Tangents &\nTangent Intersection\n");
					j += sprintf(buf+j,"\t%s is CNode_CA\n",CAID);
					j += sprintf(buf+j,"\t%s is Tangent Intersection Node\n",TIID);
					j += sprintf(buf+j,"\t%s is CNode_CB\n",CBID);
					break;
	
							
				default:
					break;

			}
			break;

		default:

			//////
			j = sprintf(buf,"Curve %s contains:\n\t%d Input Nodes\n\t%d Elements\n",
			*pID,pNodeList->GetCount(),nElems);
	}
	/////////////////////////
	j += sprintf(buf+j,"Nodes:\n");
	//////////////////////////////
	for (POSITION posI = pNodeList->GetHeadPosition( );posI !=NULL;)
	{
		////
		CDrNode* pNode = (CDrNode*)pNodeList->GetNextObject(posI);
		j += sprintf(buf+j,"%s, ",pNode->GetObjectID());
	}
	sprintf( buf + j-2, ";");
	////////////////////////////
	if(m_bStitch)
		j += sprintf(buf+j,
			"\nYES:\t\tStitch This Curve");
	else
	if(m_bBlend)
		j += sprintf(buf+j,
			"\nYES:\t\tBlend This Curve");
	else
		j += sprintf(buf+j,
			"\nYES:\t\tSpawn This Curve");
	//////
	j += sprintf(buf+j,
		"\nNO:\t\tFind Next Curve with Intersecting Trace");
	j += sprintf(buf+j,
		"\nCANCEL:\t\tCancel Selection Process");
	nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
	///////////////
	delete str;
	return nResult;
}

int CCurCreOp::LeftUp_CSPAWN(CPoint point)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	////////////////
	int nResult;
	////////////
	nResult = LeftUp_GetCurve_Parent(point);
	///
//	if(nResult<0)
	if(nResult!= MA_OK)
		return nResult;
	////////////////////////////////////////
	nResult = ShowCurveToSpawn(m_pParentCurve,TRUE); // TRUE = With Dlg
	///////////
//	if( nResult == -1)		// 
	if( nResult == MA_ERROR)		// 
	{
		AfxMessageBox("ERROR:\nCCurMouse::LeftUp_CSpawn\nShowCurveToSpawn Problem");
//		return -1;
		return MA_ERROR;
	}
	////////////////////////////
	strCurr = "Ready for Spawning a Curve@";
	strCurr += "Click on a CURVE to Spawn";
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	///////////
//	if(nResult == -2)		// Cancel
//		return -2;
	if(nResult == MA_CANCEL)		// Cancel
		return nResult;
	///
//	return 0;
	return MA_OK;
}

int CCurCreOp::ShowCurveToSpawn(CDrCurve* pParentCurve,BOOL bUsingDlg)
{
	int nResult;
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
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	///////////////////
	pObjectMgr->SetActiveObjectType(CURVE);
	////////////////////////////////////////////////////////////////////////////// Add to DataBase
	int nActiveIndex;
	///////////////
	m_pSpawnedCurve	= (CDrCurve*)(pObjectMgr->AddToDataBase(nActiveIndex,CURVE));
	m_pSpawnedCurve->SetShow(FALSE);	// not quite ready
	/////////////////////////////////////////////////////////////// Using CMI_CSPN
	CMI_CSPN MI_CSPN;
	///
	if(bUsingDlg)
	{
		m_pSpawnedCurve->SetObjectID(m_ObjID);
		///
		nResult = MI_CSPN.SpawnCurveShowingDlg(m_pSpawnedCurve,pParentCurve,pParentCurve,CURVE);
	}
	else
	{
		pMATRIX	pXFMat	= m_pMatObj->GetMatrix();
		CString	SpawnID	= m_ObjID;
		////
		nResult = MI_CSPN.SpawnCurveWithoutDlg(m_pSpawnedCurve,pParentCurve,pXFMat,&m_SpawnedID,
												pParentCurve,CURVE); 
	}
//	if(nResult<0)
	if(nResult != MA_OK)
	{
		/////////////////////////////////////// Reset
		m_nInfoDone		= 0;
		m_bDone			= TRUE;	// 
		////////////////////////// Delete
		pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
		m_pSpawnedCurve	= NULL;
		//////////////////////////
		return nResult;//
	}
	/////////////////////////////////////////////////////////// Control RectBound
	m_pSpawnedCurve->SetDirty(TRUE);
	m_pSpawnedCurve->SetShow(TRUE);
	////////////////////////////////////////////////////////// Save
	pObjectMgr->ShowObject_On_Off(m_pSpawnedCurve,CURVE,TRUE);
	///////////////////////////////
//	return 0;
	return MA_OK;
}	 

int CCurCreOp::ShowCurveToSpawnCopyOff(CDrCurve* pParentCurve,BOOL bUsingDlg)
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
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	///////////////////
	pObjectMgr->ShowObject_On_Off(pParentCurve,CURVE,FALSE);
	//////////////////////
	if(!(pParentCurve->GetCurveList())->IsEmpty())
	{
#ifdef _DEBUG
		CString ObjID = pParentCurve->GetObjectID();
		CString strBum;
		if(ObjID == "C4")
			strBum = "Bum String C4";
#endif
		/////////////////////////////////////////////////////////// XForm Curve-dependent CURVES
		nResult = CurveDependent_SpawnConnectedObjects_CopyOff(pParentCurve,bUsingDlg,CURVE);
		///
//		if(nResult == -1)
		if(nResult == MA_ERROR)
			goto ERRORHANDLER;
		/////////////////////
	}
	//////////////////////////////////////////////
	if(!(pParentCurve->GetPatchList())->IsEmpty())
	{
		/////////////////////////////////////////////////////////// XForm Curve-dependent PATCHES
		nResult = CurveDependent_SpawnConnectedObjects_CopyOff(pParentCurve,bUsingDlg,PATCH);
		///
//		if(nResult == -1)
		if(nResult == MA_ERROR)
			goto ERRORHANDLER;
		/////////////////////
	}
	//////////////////////////////////////////////
	if(!(pParentCurve->GetSolidList())->IsEmpty())
	{
		/////////////////////////////////////////////////////////// XForm Curve-dependent SOLIDS
		nResult = CurveDependent_SpawnConnectedObjects_CopyOff(pParentCurve,bUsingDlg,SOLID);
		///
//		if(nResult == -1)
		if(nResult == MA_ERROR)
			goto ERRORHANDLER;
		/////////////////////
	}
	//////////////////////////////////////////////
	if(!(pParentCurve->GetObj3DList())->IsEmpty())
	{
		/////////////////////////////////////////////////////////// XForm Curve-dependent OBJ3DS
		nResult = CurveDependent_SpawnConnectedObjects_CopyOff(pParentCurve,bUsingDlg,OBJ3D);
		///
//		if(nResult == -1)
		if(nResult == MA_ERROR)
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
//		if(nResult == -1)
		if(nResult == MA_ERROR)
			goto ERRORHANDLER;
		/////////////////////
		m_CDoneList.InsertObject(pParentCurve);
	}
	///////////////////////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(pParentCurve,CURVE,TRUE);
	////////////////////////////
	if(!bUsingDlg && m_pMatObj)
	{	
		delete m_pMatObj;	
		m_pMatObj = NULL;
	}
	/////////
//	return 0;
	return MA_OK;

ERRORHANDLER:
	AfxMessageBox("Internal ERROR\nCCurCreOp::ShowCurveToSpawnCopyOff");
	/////////////////////////////////////// Reset
	m_nInfoDone		= 0;
	m_bDone			= TRUE;	// 
	//////////////////////////
	m_pSpawnedNode	= NULL;
	//////////////////////////
	return nResult;//
	////////
}
	 
int CCurCreOp::CurveDependent_SpawnConnectedObjects_CopyOff(CDrCurve* pCurrentCurve,BOOL bUsingDlg,
																					UINT nObjType)
{
#ifdef _DEBUG
		CString ObjID = pCurrentCurve->GetObjectID();
		CString strBum;
		if(ObjID == "C5")
			strBum = "Bum String C5";
#endif
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////// XForm Node-dependent OBJECTS
//	int nResult = 0;
	int nResult = MA_OK;
	////////////////
	CDListMgr* pList;
	int i,nCount;
	//////////////////////////////////////////////// Objects
	switch(nObjType)
	{
		case CURVE:
			pList	= pCurrentCurve->GetCurveList();
			break;
		case PATCH:
			pList	= pCurrentCurve->GetPatchList();
			break;
		case SOLID:
			pList	= pCurrentCurve->GetSolidList();
			break;
		case OBJ3D:
			pList	= pCurrentCurve->GetObj3DList();
			break;
		default:
//			nResult = -1;
//			return nResult;
			return MA_ERROR;
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
		if(ObjID == "C5")
			strBum = "Bum String C5";
#endif
		////////////////
		if(pObject)
		{
			switch(nObjType)
			{
				case CURVE:

					pObjectMgr->ShowObject_On_Off((CDrObject*)pObject,CURVE,FALSE);
					///
					nResult = CurTopo_SpawnConnectedCurves_CopyOff((CDrCurve*)pObject,bUsingDlg);
					///
					pObjectMgr->ShowObject_On_Off((CDrObject*)pObject,CURVE,TRUE);
					break;

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
//					nResult = -1;
					return MA_ERROR;
			}
			///
//			if(nResult == -1)
			if(nResult == MA_ERROR)
			{
				AfxMessageBox(
					"Internal ERROR\nCCurCreOp::CurveDependent_SpawnConnectedObjects_CopyOff");
				return nResult;
			}
		}
	}
	/////////////////////
	return nResult;
}

int CCurCreOp::CurveSpawnCopyOff(CDrCurve* pParentCurve,BOOL bUsingDlg)
{
	int nResult;
	C3DMath			Math3D;
	///////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///////////////////
	pObjectMgr->SetActiveObjectType(CURVE);
	/////////////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(pParentCurve,CURVE,FALSE);
	///////////////////////////////
	CDrCurve* pSpawnedCurve = pParentCurve;
	/////////////////////////////////////////////////////////////// Using CMI_CSPN
	CMI_CSPN MI_CSPN;
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
		nResult = MI_CSPN.SpawnCurveShowingDlg((CDrCurve*)pSpawnedCurve,pParentCurve,pParentCurve,CURVE);
	}
	else
	{
		pMATRIX	pXFMat	= m_pMatObj->GetMatrix();
		CString	SpawnID	= m_ObjID;
		////
		nResult = MI_CSPN.SpawnCurveWithoutDlg(pSpawnedCurve,pParentCurve,pXFMat,&m_ObjID,
												pParentCurve,CURVE); 
	}
//	if(nResult<0)
	if(nResult != MA_OK)
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
	pObjectMgr->ShowObject_On_Off(pParentCurve,CURVE,TRUE);
	///////////////////////////////
//	return 0;
	return MA_OK;
}	 

int CCurCreOp::LeftUp_CSTITCH(CPoint point)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	////////////////
	int nResult;
	///////////////////////////////////////////// See if any Existing Curve Hit
	nResult = LeftUp_Curve_Accept(point);	// TRUE = Parent
	///
//	if(nResult<0)
	if(nResult != MA_OK)
		return nResult;
	//////////////////////////////////////////////// Closed Curve Invalid
	if(m_pCurrentCurve->IsClosed_S())
	{
		AfxMessageBox("ERROR:\nINVALID DATA\nCan Not Stitch Closed Curve");
//		nResult = -3; // Component error: ask again
		nResult = MA_NOHIT; // Component error: ask again
	}
	else
	{
		//////////////////////////////////////////////// Save it in the List
		m_CurveList.InsertObject(m_pCurrentCurve);
		m_pLastCurve = m_pCurrentCurve; 
	}
	////////////////////////////////////////////////
	strCurr = "Profiling a Curve. CLICK On Another";
	strCurr += "@Curve or CLICK In Right Mouse Button";
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	///////////
	return nResult;
}

int CCurCreOp::Update_Status_CSTITCH()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	////////////////////////////
	strCurr = "Ready for Another Curve Profile";
	strCurr += "@CLICK On a Curve to Stitch In";
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	///////////
//	return 0;
	return MA_OK;
}

int CCurCreOp::ShowCProfileToStitch()
{
	int nResult = MA_OK;
	////////////////////
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
	pObjectMgr->SetActiveObjectType(CURVE);
	////////////////////////////////////////////////////////////////////////////// Add to DataBase
	int nActiveIndex;
	///////////////
	m_pCProfile	= (CDrProf_C*)(pObjectMgr->AddToDataBase(nActiveIndex,C_PROFILE));
	m_pCProfile->SetShow(FALSE);	// not quite ready
	/////////////////////////////////////////////////////////////// ID
	m_pCProfile->SetObjectID(m_SpawnedID);	
	/////////////////////////////////////////////////////////////// Copy CurveList
	nResult = CloneCurvesForPrivateListofCProf(m_pCProfile,&m_CurveList);
	///
//	if(nResult<0)
	if(nResult != MA_OK)
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
	int nCount = (m_pCProfile->GetCurveList())->GetCount();
	for (int c=0;c<nCount;c++)
		m_LMList.InsertObject(pMatObj);	// same One
	///////////////////////////////////////////////////// Insert LMList
	(m_pCProfile->GetLMList())->AddTail(&m_LMList);
	m_LMList.RemoveAll();
	/////////////////////////////////////////////////////////////// Using CMI_CProf
	CMI_CProf MI_CProf;
	nResult = MI_CProf.RBUp_CProfile(m_pCProfile); // NOT Using Dlg (Used for Now)
	///
//	if(nResult<0)
	if(nResult != MA_OK)
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
	///////////////////////////////c Type
	if(m_bBlend)
		m_pCProfile->SetProfileType(PRT_BLEND);
	else
	if(m_bStitch)
		m_pCProfile->SetProfileType(PRT_STITCH);
	///
	m_pCProfile->SetShow(FALSE);
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(CURVE);
	///////////////////////////////////////////////////////////////
	CDrCurve* pCurve = m_pCProfile->GetCurve();
	pCurve->SetShow(TRUE);
	pCurve->SetDirty(TRUE);
	//////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(pCurve,CURVE,TRUE);
	/////////
//	return 0;
	return MA_OK;

}
	 
int CCurCreOp::CloneCurvesForPrivateListofCProf(CDrProf_C* pCProfile,CDListMgr* pCurveList)
{
	int nResult = MA_OK;
	////////////////////
	CMI_CSPN MI_CSPN;
	C3DMath Math3D;
	MATRIX XFMat;
	pMATRIX pXFMat = &XFMat;
	Math3D.GetIdentityMATRIX(pXFMat);
	/////////////////////////////////////////////////////////////////
	CString strProf = pCProfile->GetObjectID();
	///////////////////////////////////////////
	int nCount = -1;
	for (POSITION pos = pCurveList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrCurve* pCurve = (CDrCurve*)pCurveList->GetNextObject(pos);
		if(!pCurve)
			continue;
		//////////////////////////////////////////////////////////// Clone
		nCount++;
		CDrCurve* pNewCurve = new CDrCurve;
		//
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		sprintf(buf,"%s_%d",strProf,nCount);
		//
		CString	SpawnID	= *str;
		////
		nResult = MI_CSPN.SpawnCurveWithoutDlg(pNewCurve,pCurve,pXFMat,&SpawnID,
												pCurve,CURVE); 
		///
//		if(nResult<0)
		if(nResult != MA_OK)
		{
			AfxMessageBox("Internal ERROR:\nCCurCreOp::CloneCurvesForPrivateListofCProf");
			return MA_ERROR;
		}
		else
			(pCProfile->GetCurveList())->AddTail(pNewCurve);	// Do NOT reciprocate
	}
	////////////////////////
	pCurveList->RemoveAll();
	/////////////
	return MA_OK;
}

int CCurCreOp::LeftUp_CBLEND(CPoint point)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	////////////////
	int nResult;
	///////////////////////////////////////////// See if any Existing Curve Hit
	nResult = LeftUp_Curve_Accept(point);	// TRUE = Parent
	///
//	if(nResult<0)
	if(nResult != MA_OK)
		return nResult;
	//////////////////////////////////////////////// Closed Curve Invalid
	if(m_pCurrentCurve->IsClosed_S())
	{
		AfxMessageBox("ERROR:\nINVALID DATA\nCan Not Blend Closed Curve");
//		nResult = -3; // Component error: ask again
		nResult = MA_NOHIT; // Component error: ask again
	}
	else
	{
		//////////////////////////////////////////////// Save it in the List
		m_CurveList.InsertObject(m_pCurrentCurve);
		m_pLastCurve = m_pCurrentCurve; 
	}
	////////////////////////////////////////////////
	strCurr = "Blending Curves: CLICK On Another Curve";
	strCurr += "@or CLICK In Right Mouse Button";
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	///////////
	return nResult;


}

int CCurCreOp::Get_N_FillBlendInfo(CDListMgr* pBCurList,CDListMgr* pCurList)
{
	if(pCurList->IsEmpty())
		return MA_ERROR;
	///////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	int i,nResult;
	CDListMgr TemList;
	CDrCurve* pBCurve;
	CDrCurve* pCurveL;
	CDrCurve* pCurveR;
	POSITION  pos;
	/////////////////////////////////////////////// 
	int nCurves = pCurList->GetCount();
	int nBlends	= nCurves - 1;
	/////////////////////////////////////////////// Get & Create Temp Blend Curves
	for(i=0;i<nBlends;i++)
	{
		// ID
		CString ID;
		pObjectMgr->SetObjInfoID(ID,CURVE);
		ID	+= "_Tmp";
		///
		pBCurve = TempInDataBase_BlendCurve(&ID);
		pBCurve->SetObjectID(ID);
		if(!pBCurve)
			return MA_ERROR;
		//////////////////////////////////////////////// Ask for Blending Info (Always Cubic)
		CDlg_CurveBlend Dlg;
		//////
		Dlg.m_nCur1 = i+1;
		Dlg.m_nCur2 = i+2;
		Dlg.m_pDrCurve = pBCurve;
		if(Dlg.DoModal() == IDCANCEL)
			return MA_ERROR;
		//////////////////////////////////////////////// Plug INodes & End Tangents from two End Curves
		pos		= pCurList->FindIndex(i);
		pCurveL	= (CDrCurve*)pCurList->GetAt(pos);
		//
		pos		= pCurList->FindIndex(i+1);
		pCurveR	= (CDrCurve*)pCurList->GetAt(pos);
		//
		nResult = SetOtherInfo_BlendCubic(pBCurve,pCurveL,pCurveR);
		//
		nResult = CreateTemp_BlendCurve(pBCurve);
		if(nResult == MA_ERROR)
			return MA_ERROR;
		///////////////////////////////
		TemList.InsertObject(pCurveL);
		TemList.InsertObject(pBCurve);
		pBCurList->InsertObject(pBCurve); // temp.
		///
	}
	//////////////////////////////////// Last One
	TemList.InsertObject(pCurveR);
	//////////////////////////////////////////////////// Save
	pCurList->RemoveAll();
	pCurList->AddTail(&TemList);
	TemList.RemoveAll();
	////////////////////
	return MA_OK;
}
	
CDrCurve* CCurCreOp::TempInDataBase_BlendCurve(CString* pID)
{
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	int nActiveIndex;
	CDrCurve* pCurve;
	///////////////////
	pObjectMgr->SetActiveObjectType(CURVE);
	////////////////////////////////////////////////////// Add to DataBase, if not Existing
	///////////////////////////////////////// delete & Add
	CDListMgr* pList = pObjectMgr->GetObjectList(CURVE);
	nActiveIndex = pList->GetObjectIndex(CURVE, *pID);
	if(nActiveIndex>=0)
	{
		pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
		pCurve = (CDrCurve*)NULL;
	}
	//////////////////////////////////////////////////////////////////////////////////////
	pCurve	= (CDrCurve*)(pObjectMgr->AddToDataBase(*pID,nActiveIndex,CURVE));
	pCurve->SetShow(FALSE);	// not quite ready
	///////////////////////////////
	return pCurve;
}
	 
int CCurCreOp::SetOtherInfo_BlendCubic(CDrCurve* pCurve,CDrCurve* pCurveL,CDrCurve* pCurveR)
{
	C3DMath Math3D;
	////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	///////////////////////////////////////////////
	CDrNode*	pNode; 
	VECTOR		tan;
	////////////////////////////////////////////////////// INodes
	pNode = (CDrNode*)pCurveL->GetINodeList()->GetTail(); 
	pCurve->GetINodeList()->InsertObject(pNode);
	//
	pNode = (CDrNode*)pCurveR->GetINodeList()->GetHead(); 
	pCurve->GetINodeList()->InsertObject(pNode);
	////////////////////////////////////////////////////// Tangents
	pCurve->SetCurveType_S(CP_BEZIER);
	pCurve->SetOrder_S(4);	// Cubic
	/////////////////////////////////// CurveL
	pCurveL->Get_EndTangent_Vector(tan,FALSE/*bBegin*/,pHitNet->GetDblRatio());
	pCurve->SetTanL_S(tan);
	pCurve->SetBCL_S(BC_TANGENT);
	/////////////////////////////////// CurveR
	pCurveR->Get_EndTangent_Vector(tan,TRUE/*bBegin*/,pHitNet->GetDblRatio());
	pCurve->SetTanR_S(tan);
	pCurve->SetBCR_S(BC_TANGENT);
	///
	return MA_OK;
}
	
int CCurCreOp::CreateTemp_BlendCurve(CDrCurve* pCurve)
{
	CMI_GangC	GangC;
	/////////////////////////////////////////////////////////////// Using GangC
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///
	CDListMgr* pList = pObjectMgr->GetObjectList(CURVE);
//	int nActiveIndex = pList->GetObjectIndex(pCurve);
	//////////////////
	CString ID = pCurve->GetObjectID();
	CDListMgr NodeList;
	NodeList.AddTail(pCurve->GetINodeList());
	CURVEPROC CurveType = pCurve->GetCurveType_S();
	CList<int,int> ElSegList;
	ElSegList.AddTail(pCurve->GetElperSegList_S());
	//////////////////////////////////////////////////////////////// Set other Info
	GangC.SetNoDefault(TRUE);	// Wts & Knots & BC
	GangC.SetBezierType(BEZIER_BY_TAN);	// Bez. by End Tans
//
	pCurve = GangC.CreateCurve(ID,pCurve,&NodeList,CurveType,
						&ElSegList,FALSE/*m_bAdvanceOn*/,TRUE/*bFinal*/);
	////////////////////////////////////////////////////////////////////// No Show
	pCurve->SetDirty(TRUE);
	///
//	pObjectMgr->ShowObject_On_Off(m_pCurrentCurve,CURVE,FALSE);	// Temporary
	///////////////////////////////
	return MA_OK;
}	 

int CCurCreOp::Update_Status_CBLEND()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	////////////////////////////
	strCurr = "Ready for Another Blended Curve";
	strCurr += "@CLICK On a Curve to Blend In";
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	///////////
//	return 0;
	return MA_OK;
}

//int CNodEdit::ReGen_SpawnedCurveControls(CDrCurve* pSpawnedCurve)
int CCurCreOp::ReGen_SpawnedCurveControls(CDrCurve* pSpawnedCurve)
{

	//////////////////////////////////////////////////////////////////
	pSpawnedCurve->SetShow(FALSE);	// not quite ready
	/////////////////////////////////////////////////// Get rid of Old CNodes & Delete 
	CDrObject* pObject;
	while(!(pSpawnedCurve->GetCNodeList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(pSpawnedCurve->GetCNodeList()->RemoveHead());
		int nLevelType = pObject->GetLevelType();
		if(nLevelType == LEVEL_GRAPA) //no delete:public
			pObject->ReadyToDelete();
		else
			delete pObject;	//delete:private	
	}	
	/////////////////////////////////////////////////////// Copy ElperSegList
	CDListMgr	NodeList;
	CList<int,int> ElSegList;
	ElSegList.RemoveAll();
	ElSegList.AddTail(pSpawnedCurve->GetElperSegList_S());
	(pSpawnedCurve->GetElperSegList_S())->RemoveAll();		// now Remove, later stored in GangC
	/////////////////////////////////////////////////////////////// Fill Input Nodes
	CDListMgr* pINodeList = pSpawnedCurve->GetINodeList();
	/////////////////////////////////////////////////////////////// Using GangC
	CMI_GangC	GangC;
	CMC_Circle	MC_Circle;
	CDrNode*	pAddNode;
	POSITION	pos;
	///////////////////////////////////////////// Curve Info
	double		SegAngle,dAng,dAngSpec,dRadius;
	BOOL		bArc,bAdvanceOn;
	CString		FromID,ToID,TIID,CCID,CAID,CBID;
	CDrNode*	pFromNode;
	CDrNode*	pToNode;
	////////////////////////////////////////////////////////
	CString		ID			= pSpawnedCurve->GetObjectID();
	CURVEPROC	SCurveType	= pSpawnedCurve->GetCurveType_S();
	CIRCLETYPE	CircType	= pSpawnedCurve->GetCircleType();
	////////////////////////////////////////////////////////
	switch(SCurveType)
	{
		case CP_CIRCLE:

			SegAngle		= pSpawnedCurve->GetSegAngle_S(); 
			dAngSpec		= pSpawnedCurve->GetTheta_S();
			dAng			= dAngSpec;
			bArc			= pSpawnedCurve->IsArcType();
			///////////////////////////////////////
			switch(CircType)
			{
				
				case CIRCLE_BY_ROT:

					dAng		= pSpawnedCurve->GetTheta_S();
					//////////////////////////////////////////// FromID & ToID
					FromID		= pSpawnedCurve->GetFromIDNode_S()->GetObjectID();
					ToID		= pSpawnedCurve->GetToIDNode_S()->GetObjectID();
					pFromNode	= pSpawnedCurve->GetFromIDNode_S();
					pToNode		= pSpawnedCurve->GetToIDNode_S();
					////////////////////////////////////
					break;

					
				case CIRCLE_BY_NO3:

					//////////////////////////////////////////////				
					break;

					
				case CIRCLE_BY_2N_TI:
		
					//////////////////////////////////////////// TIID
					pos			= pINodeList->FindIndex( 1 );
					pAddNode	= (CDrNode*)(pINodeList->GetAt(pos));
					TIID		= pAddNode->GetObjectID();
					////////////////////////////////////
					break;

					
				case CIRCLE_BY_2N_CC:

					//////////////////////////////////////////// CCID
					pos			= pINodeList->FindIndex( 1 );
					pAddNode	= (CDrNode*)(pINodeList->GetAt(pos));
					CCID		= pAddNode->GetObjectID();
					////////////////////////////////////
					break;

					
				case CIRCLE_BY_2CN_TI_R:

					dRadius		= pSpawnedCurve->GetRadius_S();
					//////////////////////////////////////////// TIID
					pos			= pINodeList->FindIndex( 1 );
					pAddNode	= (CDrNode*)(pINodeList->GetAt(pos));
					TIID		= pAddNode->GetObjectID();
					//////////////////////////////////////////// CAID
					pAddNode	= (CDrNode*)(pINodeList->GetHead());
					CAID		= pAddNode->GetObjectID();
					//////////////////////////////////////////// CBID
					pAddNode	= (CDrNode*)(pINodeList->GetTail());
					CBID		= pAddNode->GetObjectID();
					////////////////////////////////////
					break;
				
				default:

					break;

			}
			////////////////////////////////////
			pSpawnedCurve = MC_Circle.CreateCircle(
								ID,pSpawnedCurve,&NodeList,SCurveType,
								&ElSegList,CircType,dAng,SegAngle,dRadius,
								bArc,pFromNode,pToNode,TRUE);
			break;
				
		default:
			
			bAdvanceOn = FALSE; // because data already Known
			GangC.SetBezierType(pSpawnedCurve->GetBezierType());
			/////////////////////
			pSpawnedCurve = GangC.CreateCurve(ID,pSpawnedCurve,&NodeList,SCurveType,
											&ElSegList,bAdvanceOn,TRUE);// TRUE = Final
	}
	//////////////////////////////////
	return MA_OK;
}

void CCurCreOp::OnEBoxMouseMove_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CCurCreOp::OnEBoxLButtonUp_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CCurCreOp::OnEBoxRButtonDown_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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
		case CURVE:
			break;
		////////////////////////////////////////////////// Patch
		default:
			break;
	}  
}

void CCurCreOp::OnEBoxRButtonUp_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
								UINT nFlags, CPoint point)
{
	int nResult = MA_OK;
	////////////////////
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
	CString		ID;
	CString*	pID = &ID;
	CDrCurve*	pCurve;
	CDListMgr*	pList;
	int			nActiveIndex;
	///////////////////////////////////////////////////////// Is Enough Info?
	if(RightUp_Premature()<0)
		return;
	///////////////////////////////////////////////////////// Not Auto Accept:BLEND/STITCH
	if(m_bBlend || m_bStitch)
	{
		if(RightUp_NotAutoAccept_CSTITCH()<0)
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
//			if(ShowCurveToSpawn(m_pParentCurve,FALSE)<0)		 //FALSE = NoDlg
			nResult = ShowCurveToSpawn(m_pParentCurve,FALSE);		 //FALSE = NoDlg
			////////////////
			if(nResult == MA_ERROR || nResult == MA_CANCEL)
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
//			if(ShowCurveToSpawn(m_pParentCurve,FALSE)<0)		 //FALSE = NoDlg
			nResult = ShowCurveToSpawn(m_pParentCurve,FALSE);		 //FALSE = NoDlg
			////////////////
			if(nResult == MA_ERROR || nResult == MA_CANCEL)
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
//			if(ShowCurveToSpawn(m_pParentCurve,FALSE)<0)		 //FALSE = NoDlg
			nResult = ShowCurveToSpawn(m_pParentCurve,FALSE);		 //FALSE = NoDlg
			////////////////
			if(nResult == MA_ERROR || nResult == MA_CANCEL)
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
//			if(ShowCurveToSpawn(m_pParentCurve,FALSE)<0)		 //FALSE = NoDlg
			nResult = ShowCurveToSpawn(m_pParentCurve,FALSE);		 //FALSE = NoDlg
			////////////////
			if(nResult == MA_ERROR || nResult == MA_CANCEL)
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
//			if(ShowCurveToSpawn(m_pParentCurve,FALSE)<0)		 //FALSE = NoDlg
			nResult = ShowCurveToSpawn(m_pParentCurve,FALSE);		 //FALSE = NoDlg
			////////////////
			if(nResult == MA_ERROR || nResult == MA_CANCEL)
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
//			if(ShowCProfileToStitch()<0)		
			nResult = ShowCProfileToStitch();
			////////////////
			if(nResult == MA_ERROR || nResult == MA_CANCEL)
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

		
		case COP_BLEND:
						
			
			nResult = Get_N_FillBlendInfo(&m_BCurveList,&m_CurveList);
			if(nResult == MA_OK)
			{
				/////////////////////////////
				nResult = ShowCProfileToStitch();
				////////////////
			}
			//
			if(nResult == MA_ERROR || nResult == MA_CANCEL)
			////////////////
			{
				Terminate_CUR(TRUE);
				return;
			}
			else
			{
				Terminate_CUR(FALSE);
				Init_CUR();
				///////////////////////// Delete Temporary Blend Curves
				pList = pObjectMgr->GetObjectList(CURVE);
				while(!(m_BCurveList.IsEmpty()))// delete:private
				{
					pCurve = (CDrCurve*)m_BCurveList.RemoveHead();
					nActiveIndex = pList->GetObjectIndex(pCurve);
					if(nActiveIndex>=0)
						pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
					else
					{
						AfxMessageBox(
							"Internal ERROR\nCCurCreOp::OnEBoxRButtonUp_CUR\nIndex Prob");
						return;
					}
				}
				/////////////////////////
				Update_Status_CBLEND();
				break;
			}
			///////////////////	
			break;
		//////////////	
		default:  
			return;
	} 
	////////////////////////////////////////////////////////////////////////
	pObjectMgr->SetObjInfoID(m_SpawnedID,CURVE);
	m_SpawnedID	+= "_Cu";
	////////////////////////////////////////////////////////////////////////
}

int CCurCreOp::RightUp_NotAutoAccept_CSTITCH()
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
		if(m_bBlend)
			nAnswer = ShowInputInfo_CBLEND();
		else
		if(m_bStitch)
			nAnswer = ShowInputInfo_CSTITCH();
		///////////////////////
		if(nAnswer == MA_ERROR)
			return MA_ERROR;
		/////////////////////////
		if(nAnswer == MA_CANCEL)
		{
			CString* str = new CString;
			char* buf	= str->GetBuffer(BUFF_SIZE);
			if(m_bBlend)
				sprintf(buf,"Do You Want to Delete\nCurrent Curve Blending to Start Allover");
			else
			if(m_bStitch)
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
				return MA_CANCEL;
			}
		}
		/////////////////////
		return MA_OK; 
	}
	/////////
	return MA_OK;
}

int CCurCreOp::ShowInputInfo_CSTITCH()
{
	UINT nAnswer;
	///////////////////////////////////////////////////////////// show Info:DoModal
	CMCurMgr	MCurMgr;
	nAnswer = MCurMgr.DoModal_Profile_C_ShowInfo(&m_SpawnedID,&m_CurveList);  	//Profile
	if(nAnswer == IDCANCEL)
		return MA_CANCEL;	// CAncel
	else
		return MA_OK;
}


int CCurCreOp::ShowInputInfo_CBLEND()
{
	UINT nAnswer;
	///////////////////////////////////////////////////////////// show Info:DoModal
	CMCurMgr	MCurMgr;
	nAnswer = MCurMgr.DoModal_Profile_C_ShowInfo(&m_SpawnedID,&m_CurveList);  	//Profile
	if(nAnswer == IDCANCEL)
		return MA_CANCEL;	// CAncel
	else
		return MA_OK;
}

long CCurCreOp::CreateorActivateCreOp_CUR(UINT wParam, long lParam)
{
	/////////////////////////////////////////// Parent Info
	m_ParentType	= CURVE;
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
	 
long CCurCreOp::GoodByeCreOp_CUR(UINT wParam, long lParam)
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
	 
long CCurCreOp::CancelCreOp_CUR(UINT wParam, long lParam)
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
UINT CCurCreOp::ReSetToolID_CUR(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	///////////////////////////////////
	if(IGenID != CURVE)
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
					str	= "CURVE";		ID	= COP_TRANSLATE;
						strCur += "Click on a CURVE to Translate";
					break;
				//////////////////////////////////////////// Create
				case COP_ROTATE:
					///////////////////////////// String
					str = "ROTATE";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "CURVE";		ID	= COP_ROTATE;
						strCur += "Click on a CURVE to Rotate";
					break;
				//////////////////////////////////////////// Create
				case COP_SCALE:
					///////////////////////////// String
					str = "SCALE";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "CURVE";		ID	= COP_SCALE;
						strCur += "Click on a CURVE to Scale";
					break;
				//////////////////////////////////////////// Create
				case COP_REFLECT:
					///////////////////////////// String
					str = "REFLECT";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "CURVE";		ID	= COP_REFLECT;
						strCur += "Click on a CURVE to Reflect";
					break;
				//////////////////////////////////////////// Create
				case COP_SHEAR:
					///////////////////////////// String
					str = "SHEAR";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "CURVE";		ID	= COP_SHEAR;
						strCur += "Click on a CURVE to Shear";
					break;
				//////////////////////////////////////////// Create
				case COP_SPAWN:

					Init_CUR();	// No Modeless Dlg, so Init Here
					///////////////////////////// String
					str = "SPAWN";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "CURVE";		ID	= COP_SPAWN;
						strCur += "Click on a CURVE to Spawn";
					break;
				//////////////////////////////////////////// Create
				case COP_STITCH:

					Init_CUR();	// No Modeless Dlg, so Init Here
					///////////////////////////// String
					str = "STITCH";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "CURVE";		ID	= COP_STITCH;
						strCur += "Click on a CURVE to Stitch In";
					break;
				//////////////////////////////////////////// Create
				case COP_BLEND:

					Init_CUR();	// No Modeless Dlg, so Init Here
					///////////////////////////// String
					str = "BLEND";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "CURVE";		ID	= COP_BLEND;
						strCur += "Click on a CURVE to Blend In";
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

void CCurCreOp::Serialize(CArchive& ar)
{

	CNodCreOp::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CurCreOp:    Storing\n");	
		

	}
	else
	{
		TRACE(" CurCreOp:    Loading\n");	

	
	}        
}
///////////////////////////////////// end of Module //////////////////////		

