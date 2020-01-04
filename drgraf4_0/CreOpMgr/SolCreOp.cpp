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
#include "MI_SSPN.h" 
#include "Dlg_CrOI.h"
//////////////////////
#include "SolCreOp.h" 

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
IMPLEMENT_SERIAL(CSolCreOp,CPatCreOp,1)
/////////////////////////////////////////////////////////////////////////////
CSolCreOp::CSolCreOp()
{
	m_bDoModalDone = FALSE;
}

CSolCreOp::~CSolCreOp()
{
}

void CSolCreOp::Init_SOL()
{
	Init_NOD();
	//////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////
	char buf[50];
    m_LastNum		= pObjectMgr->GetLastInputNo(SOLID);		// internal
	sprintf(buf,"%d",m_LastNum);
	m_SpawnedID	= "";
	m_SpawnedID	+= buf;
	pObjectMgr->BumpLastInputNo(SOLID);		// bump it
	/////////////////////////////////////////// Node
	m_pSpawnedSolid		= NULL;
	m_pParentSolid		= NULL;
	m_ParentID			= "";
	m_pCurrentSolid		= NULL;
	/////////////////////////////////////////// Dlg_CrOI 
	m_NID			= m_ParentID;

}

void CSolCreOp::Terminate_SOL(BOOL bError)
{
	Terminate_NOD(bError);
	////
	if(bError)
	{
		/////////////////////////////////////////// 
		if(m_pSpawnedSolid)
		{
			delete m_pSpawnedSolid;
			m_pSpawnedSolid = NULL;
		}
		///////////////////////////
	}
}

void CSolCreOp:: ElementLeftDown_SOL()
{	
	ElementLeftDown_NOD();
}

void CSolCreOp::OnEBoxLButtonDown_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
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
	////////////////////////////////////////////////// No Solid
	pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	if(pDListMgr->GetCount()<=0)
		return;
	//////////////////////////
    if(m_Gener == FORWARD)
		ElementLeftDown_SOL();
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftDown_I();
	//////////////////////////////////
}

int CSolCreOp::LeftUp_GetSolid_Parent(POINT point)
{
	int nResult;
	///////////////////////////////////////////// See if any Existing Node Hit
	nResult = LeftUp_Solid_Accept(point);	// TRUE = Parent
	///////////////////
	if(nResult < 0)
		return nResult; // Cancel or No Hit
	///////
	if(nResult>=0)	// Hit
	{
		switch(m_nInfoDone)
		{
			case 0:	// 
				m_pParentSolid	= m_pCurrentSolid;
				m_ParentID		= m_pParentSolid->GetObjectID();
				break;
			default:
				return -1;
		}
	}
	//////////////////////////////////////
	return 0;
}

int CSolCreOp::LeftUp_TRANSLATE_SOL(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Solid	
			nResult = LeftUp_GetSolid_Parent(point);
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

int CSolCreOp::LeftUp_ROTATE_SOL(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Solid	
			nResult = LeftUp_GetSolid_Parent(point);
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

int CSolCreOp::LeftUp_SCALE_SOL(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Solid	
			nResult = LeftUp_GetSolid_Parent(point);
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

int CSolCreOp::LeftUp_REFLECT_SOL(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Solid	
			nResult = LeftUp_GetSolid_Parent(point);
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

int CSolCreOp::LeftUp_SHEAR_SOL(POINT point)
{
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Solid	
			nResult = LeftUp_GetSolid_Parent(point);
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

void CSolCreOp::ElementLeftUp_SOL(CPoint point)
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
		///////////////////////////////////////////////////// Solides Insert
		case COP_TRANSLATE:

			if(m_nInfoDone > MAX_INFO_XLATE)
				return;
			////////////////
			UpdateDlg_TRUE_XLATE();
			//////////////////
			if(!(m_bDirect && m_bDominant) )
			{
				if(LeftUp_TRANSLATE_SOL(point)<0)
				{
					Terminate_SOL(TRUE);
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
				if(LeftUp_ROTATE_SOL(point)<0)
				{
					Terminate_SOL(TRUE);
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
				if(LeftUp_SCALE_SOL(point)<0)
				{
					Terminate_SOL(TRUE);
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
				if(LeftUp_REFLECT_SOL(point)<0)
				{
					Terminate_SOL(TRUE);
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
				if(LeftUp_SHEAR_SOL(point)<0)
				{
					Terminate_SOL(TRUE);
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
			if(LeftUp_SSPAWN(point)<0)
			////////////////
			{
				Terminate_SOL(TRUE);
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

int CSolCreOp::LeftUp_Solid_Accept(CPoint point)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(SOLID);
	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrSolid*	pDrSolid;
	int			nActiveIndex,index;
	////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	WORtoWOP(&dTol,&dTol);	// physical
	///////////////////////////////////////////// See if any Existing Solid Hit
	index = IsObjectHit(SOLID,point,0);
	////////////////////////////////////////////////////
	if(index<0)
		return -1; // No Solid Hit
	//////////////////////////////////////////////////////////////// Existing Solid
	pDrSolid	= (CDrSolid*)pDListMgr->GetObject(index);
	ID			= pDrSolid->GetObjectID();
	/////////////////////////////////////////
	pList = pObjectMgr->GetObjectList(SOLID);
	nActiveIndex = pList->GetObjectIndex(SOLID, ID);;
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
	pObjectMgr->SetActiveObjectType(SOLID);		    // set Active Type									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,SOLID);
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
//			nResult = ShowParentSolidInfo(pDrSolid);
			nResult = ShowParentSolidInfo(pDrSolid);
			/////////////
			if(nResult == IDYES)
				//////////////////////////////////////////////////////// Accept Old
				break;
			else
			if(nResult == IDNO)
			{
				//////////////////////////////////////////////////////// Retry
				index = IsObjectHit(SOLID,point,startIndex);
				if(index>=0)
				{
					pDrSolid	= (CDrSolid*)pDListMgr->GetObject(index);
					ID		= pDrSolid->GetObjectID();
					///////////////////////////////////////// 
					pList = pObjectMgr->GetObjectList(SOLID);
					nActiveIndex = pList->GetObjectIndex(SOLID, ID);;
					pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
					pObjectMgr->SetActiveObjectType(SOLID);		    // set Active Index									
					pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,SOLID);
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
	m_pCurrentSolid = pDrSolid;
	/////////
	return 0;
	/////////
}

int CSolCreOp::LeftUp_SSPAWN(CPoint point)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Solid	
			nResult = LeftUp_GetSolid_Parent(point);
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

int CSolCreOp::ShowParentSolidInfo(CDrSolid* pDrSolid)
{
	int nResult;
	CString ID;
	CString* pID = &ID;
	ID = pDrSolid->GetObjectID();
	//////////////////////////////////////////////////////////////////////
	SOLIDPROC 		SolProc		= pDrSolid->GetSolidProc();
	SOLSUBTYPE 		SolSubType	= pDrSolid->GetSolSubType();
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	//////
	j = sprintf(buf,"***** A Solid_To_Spawn_From Hit ****\n");
	//////////////////////////////////////
	switch(SolProc)
	{
		case SP_EXTRUDE:
			//////////////////////////////////////////////////// Show Solid
			j += sprintf(buf+j,"Solid %s was Generated by Extrusion\n",*pID);
			break;

		case SP_ROTATE:
			//////////////////////////////////////////////////// Show Solid
			j += sprintf(buf+j,"Solid %s was Generated by Rotation\n",*pID);
			break;

		case SP_LOFT2:
			//////////////////////////////////////////////////// Show Solid
			j += sprintf(buf+j,"Solid %s\nGenerated by Lofting\n",*pID);
			break;

		case SP_COONSTETRA:
			//////////////////////////////////////////////////// Show Solid
			j += sprintf(buf+j,"Solid %s\nGenerated by Lofting\nTriangular Patches\n",*pID);
			break;

		case SP_COONSHEXA:
			//////////////////////////////////////////////////// Show Solid
			j += sprintf(buf+j,"Solid %s\nGenerated by Lofting\nQuadrangular Patches\n",*pID);
			break;

		case SP_DUCT:
			//////////////////////////////////////////////////// Show Solid
			j += sprintf(buf+j,"Solid %s\nGenerated by Ducting\n",*pID);
			break;

		case SP_SWEEP:
			//////////////////////////////////////////////////// Show Solid
			j += sprintf(buf+j,"Solid %s\nGenerated by\nSweeping\n",*pID);
			break;

		case SP_COONS:
			//////////////////////////////////////////////////// Show Solid
			if(SolSubType == SS_TETRA)
				//////////////////////////////////////////////////// Show Solid
				j += sprintf(buf+j,"Solid %s\nTetraHedral Coons Type\n",*pID);
			else
			if(SolSubType == SS_PENTA)
				//////////////////////////////////////////////////// Show Solid
				j += sprintf(buf+j,"Solid %s\nPentaHedral Coons Type\n",*pID);
			else
			if(SolSubType == SS_HEXA)
				//////////////////////////////////////////////////// Show Solid
				j += sprintf(buf+j,"Solid %s\nHexaHedral Coons Type\n",*pID);

			////
			break;

		default:
			break;
	}
	////////////////////////////
	j += sprintf(buf+j,
		"\nYES:\t\tSpawn This Solid");
	j += sprintf(buf+j,
		"\nNO:\t\tFind Next Solid with Intersecting Trace");
	j += sprintf(buf+j,
		"\nCANCEL:\t\tCancel Selection Process");
	nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
	///////////////
	delete str;
	return nResult;
}

int CSolCreOp::ShowSolidToSpawn(CDrSolid* pParentSolid,BOOL bUsingDlg)
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
	////////////////////////////////
	strCurr = "Please Wait";
	///////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
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
		nResult = ShowSolidToSpawnCopyOff(pParentSolid,bUsingDlg);
		return nResult;
	}
	///////////////////
	pObjectMgr->SetActiveObjectType(SOLID);
	////////////////////////////////////////////////////////////////////////////// Add to DataBase
	int nActiveIndex;
	///////////////
	m_pSpawnedSolid	= (CDrSolid*)(pObjectMgr->AddToDataBase(nActiveIndex,SOLID));
	///
	m_pSpawnedSolid->SetShow(FALSE);	// not quite ready
	/////////////////////////////////////////////////////////////// Using CMI_CSPN
	CMI_SSPN MI_SSPN;
	if(bUsingDlg)
	{
		m_pSpawnedSolid->SetObjectID(m_ObjID);
		///
		nResult = MI_SSPN.SpawnSolidShowingDlg(m_pSpawnedSolid,pParentSolid,pParentSolid,SOLID);
	}
	else
	{
		pMATRIX	pXFMat	= m_pMatObj->GetMatrix();
		CString	SpawnID	= m_ObjID;
		////
		nResult = MI_SSPN.SpawnSolidWithoutDlg(m_pSpawnedSolid,pParentSolid,pXFMat,&m_SpawnedID,
												pParentSolid,SOLID); 
	}
	if(nResult<0)
	{
		/////////////////////////////////////// Reset
		m_nInfoDone		= 0;
		m_bDone			= TRUE;	// 
		////////////////////////// Delete
		pObjectMgr->DeleteFromDataBase(nActiveIndex, SOLID);
		m_pSpawnedSolid	= NULL;
		//////////////////////////
		return nResult;//
	}
	/////////////////////////////////////////////////////////// Control RectBound
	m_pSpawnedSolid->SetDirty(TRUE);
	m_pSpawnedSolid->SetShow(TRUE);
	////////////////////////////////////////////////////////// Save
	pObjectMgr->ShowObject_On_Off(m_pSpawnedSolid,SOLID,TRUE);
	///////////////////////////////
	return 0;
}	 

int CSolCreOp::ShowSolidToSpawnCopyOff(CDrSolid* pParentSolid,BOOL bUsingDlg)
{
	int				nResult;
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
	pObjectMgr->SetActiveObjectType(SOLID);
	//////////////////////////////////////////////
	if(!(pParentSolid->GetSolidList())->IsEmpty())
	{
		/////////////////////////////////////////////////////////// XForm Solid-dependent SOLIDS
		nResult = SolidDependent_SpawnConnectedObjects_CopyOff(pParentSolid,bUsingDlg,SOLID);
		///
		if(nResult == -1)
			goto ERRORHANDLER;
		/////////////////////
	}
	//////////////////////////////////////////////
	if(!(pParentSolid->GetObj3DList())->IsEmpty())
	{
		/////////////////////////////////////////////////////////// XForm Solid-dependent OBJ3DS
		nResult = SolidDependent_SpawnConnectedObjects_CopyOff(pParentSolid,bUsingDlg,OBJ3D);
		///
		if(nResult == -1)
			goto ERRORHANDLER;
		/////////////////////
	}
	///////////////////////////////////////////////// XForm Current Solid, if not done yet
	index = m_SDoneList.GetObjectIndex(pParentSolid);
	if(index<0)	// not done yet
	{
		pObjectMgr->ShowObject_On_Off(pParentSolid,SOLID,FALSE);
		/////////////////////////////////////////////////////////// XForm Current Solid
		nResult = SolidSpawnCopyOff(pParentSolid,bUsingDlg);
		///
		if(nResult == -1)
			goto ERRORHANDLER;
		/////////////////////
		m_SDoneList.InsertObject(pParentSolid);
	}
	/////////////////////////////////////////////////////////////// walk downward to go upward
	//																from Curve
	if(!(pParentSolid->GetCurveList())->IsEmpty())
	{
		CDListMgr* pList = pParentSolid->GetCurveList();
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
	if(!(pParentSolid->GetPatchList())->IsEmpty())
	{
		CDListMgr* pList = pParentSolid->GetPatchList();
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
	///////////////////////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(pParentSolid,SOLID,TRUE);
	///////////////////////////////////////////////////////////
	if(!bUsingDlg && m_pMatObj)
	{	
		delete m_pMatObj;	
		m_pMatObj = NULL;
	}
	///////////////////////////////
	return 0;

ERRORHANDLER:
	AfxMessageBox("Internal ERROR\nCSolCreOp::ShowSolidToSpawnCopyOff");
	/////////////////////////////////////// Reset
	m_nInfoDone		= 0;
	m_bDone			= TRUE;	// 
	//////////////////////////
	m_pSpawnedNode	= NULL;
	//////////////////////////
	return nResult;//
	////////
}
	 
int CSolCreOp::SolidDependent_SpawnConnectedObjects_CopyOff(CDrSolid* pCurrentSolid,BOOL bUsingDlg,
																					UINT nObjType)
{
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////// XForm Solid-dependent OBJECTS
	int nResult = 0;
	////////////////
	CDListMgr* pList;
	int i,nCount;
	//////////////////////////////////////////////// Objects
	switch(nObjType)
	{
		case SOLID:
			pList	= pCurrentSolid->GetSolidList();
			break;
		case OBJ3D:
			pList	= pCurrentSolid->GetObj3DList();
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
					"Internal ERROR\nCSolCreOp::SolidDependent_SpawnConnectedObjects_CopyOff");
				return nResult;
			}
		}
	}
	/////////////////////
	return nResult;
}

int CSolCreOp::SolidSpawnCopyOff(CDrSolid* pParentSolid,BOOL bUsingDlg)
{
	int nResult;
	C3DMath			Math3D;
	///////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///////////////////
	pObjectMgr->SetActiveObjectType(SOLID);
	/////////////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(pParentSolid,SOLID,FALSE);
	///////////////////////////////
	CDrSolid* pSpawnedSolid = pParentSolid;
	/////////////////////////////////////////////////////////////// Using CMI_CSPN
	CMI_SSPN MI_SSPN;
	/////////////////
	MI_SSPN.SetNDoneList(&m_NDoneList);
	MI_SSPN.SetCDoneList(&m_CDoneList);
	MI_SSPN.SetPDoneList(&m_PDoneList);
	MI_SSPN.SetSDoneList(&m_SDoneList);
	MI_SSPN.SetODoneList(&m_ODoneList);
	///////////////////////////////////
	if(bUsingDlg)
	{
		pSpawnedSolid->SetObjectID(m_ObjID);
		///
		nResult = MI_SSPN.SpawnSolidShowingDlg((CDrSolid*)pSpawnedSolid,pParentSolid,pParentSolid,SOLID);
	}
	else
	{
		pMATRIX	pXFMat	= m_pMatObj->GetMatrix();
		CString	SpawnID	= m_ObjID;
		////
		nResult = MI_SSPN.SpawnSolidWithoutDlg(pSpawnedSolid,pParentSolid,pXFMat,&m_SpawnedID,
												pParentSolid,SOLID); 
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
	pObjectMgr->ShowObject_On_Off(pParentSolid,SOLID,TRUE);
	///////////////////////////////
	return 0;
}	 

void CSolCreOp::OnEBoxMouseMove_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CSolCreOp::OnEBoxLButtonUp_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
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
		ElementLeftUp_SOL(Logpoint);
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftUp_I();
	/////////////////////////
	
}

void CSolCreOp::OnEBoxRButtonDown_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
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
		case SOLID:
			break;
		////////////////////////////////////////////////// Solid
		default:
			break;
	}  
}

void CSolCreOp::OnEBoxRButtonUp_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
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
		Terminate_SOL(TRUE);
		return;
	}
	///////////////////////////////////////////////////// Show Spawned Node 
	switch(m_nActiveTool) 
	{

		case COP_TRANSLATE:
						
			
			SetUpLocalM_XLATE();
			/////////////////////////////
			if(ShowSolidToSpawn(m_pParentSolid,FALSE)<0)		 //FALSE = NoDlg
			////////////////
			{
				Terminate_SOL(TRUE);
				return;
			}
			else
			{
				Terminate_SOL(FALSE);
				Init_SOL();
				/////////////////////////
				UpdateDlg_FALSE_XLATE();
				break;
			}
			///////////////////	
			break;

			
		case COP_ROTATE:
						
			
			SetUpLocalM_ROTATE();
			/////////////////////////////
			if(ShowSolidToSpawn(m_pParentSolid,FALSE)<0)		 //FALSE = NoDlg
			////////////////
			{
				Terminate_SOL(TRUE);
				return;
			}
			else
			{
				Terminate_SOL(FALSE);
				Init_SOL();
				/////////////////////////
				UpdateDlg_FALSE_ROTATE();
				break;
			}
			///////////////////	
			break;
		
		case COP_SCALE:
						
			
			SetUpLocalM_SCALE();
			/////////////////////////////
			if(ShowSolidToSpawn(m_pParentSolid,FALSE)<0)		 //FALSE = NoDlg
			////////////////
			{
				Terminate_SOL(TRUE);
				return;
			}
			else
			{
				Terminate_SOL(FALSE);
				Init_SOL();
				/////////////////////////
				UpdateDlg_FALSE_SCALE();
				break;
			}
			///////////////////	
			break;
		
		case COP_REFLECT:
						
			
			SetUpLocalM_REFLECT();
			/////////////////////////////
			if(ShowSolidToSpawn(m_pParentSolid,FALSE)<0)		 //FALSE = NoDlg
			////////////////
			{
				Terminate_SOL(TRUE);
				return;
			}
			else
			{
				Terminate_SOL(FALSE);
				Init_SOL();
				/////////////////////////
				UpdateDlg_FALSE_REFLECT();
				break;
			}
			///////////////////	
			break;
		
		case COP_SHEAR:
						
			
			SetUpLocalM_SHEAR();
			/////////////////////////////
			if(ShowSolidToSpawn(m_pParentSolid,FALSE)<0)		 //FALSE = NoDlg
			////////////////
			{
				Terminate_SOL(TRUE);
				return;
			}
			else
			{
				Terminate_SOL(FALSE);
				Init_SOL();
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
			if(ShowSolidToSpawn(m_pParentSolid,TRUE)<0)		 //TRUE = Dlg
			////////////////
			{
				Terminate_SOL(TRUE);
				return;
			}
			else
			{
				Terminate_SOL(FALSE);
				Init_SOL();
				////////////////////
				strCur = "Composite Affine/Symmetry Transformations@";
				strCur += "Click on a SOLID to Spawn";
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
    m_LastNum		= pObjectMgr->GetLastInputNo(SOLID);		// internal
	sprintf(buf,"%d",m_LastNum);
	m_SpawnedID	= "";
	m_SpawnedID	+= buf;
	pObjectMgr->BumpLastInputNo(SOLID);		// bump it
	////////////////////////////////////////////////////////////////////////
}

long CSolCreOp::CreateorActivateCreOp_SOL(UINT wParam, long lParam)
{
	/////////////////////////////////////////// Parent Info
	m_ParentType	= SOLID;
	m_strParentType = "Solid";
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
		Init_SOL();

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
	 
long CSolCreOp::GoodByeCreOp_SOL(UINT wParam, long lParam)
{
	
	GetCreOpDlg()->DestroyWindow();
	////////////////
	{
		Terminate_SOL(FALSE);
		return 0L;
	}
	//////////
	return 0L;
}
	 
long CSolCreOp::CancelCreOp_SOL(UINT wParam, long lParam)
{
	
	GetCreOpDlg()->DestroyWindow();
	////////////////
	{
		Terminate_SOL(FALSE);
		return 0L;
	}
	//////////
	return 0L;
}
	 
/////////////////////////////////////////////////////////////////////////////////////// 
UINT CSolCreOp::ReSetToolID_SOL(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	///////////////////////////////////
	if(IGenID != SOLID)
	{
		str = "UNKNOWN";	ID	= UNONE;
		pWnd->SetstrIGenID(str);
		////////////////////////
		return UNONE;
	}
	//////////////////////////////////////////// TaskID
	strCur = "Ready for Spawning a Solid@";
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
					str	= "SOLID";		ID	= COP_TRANSLATE;
						strCur += "Click on a SOLID to Translate";
					break;
				//////////////////////////////////////////// Create
				case COP_ROTATE:
					///////////////////////////// String
					str = "ROTATE";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "SOLID";		ID	= COP_ROTATE;
						strCur += "Click on a SOLID to Rotate";
					break;
				//////////////////////////////////////////// Create
				case COP_SCALE:
					///////////////////////////// String
					str = "SCALE";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "SOLID";		ID	= COP_SCALE;
						strCur += "Click on a SOLID to Scale";
					break;
				//////////////////////////////////////////// Create
				case COP_REFLECT:
					///////////////////////////// String
					str = "REFLECT";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "SOLID";		ID	= COP_REFLECT;
						strCur += "Click on a SOLID to Reflect";
					break;
				//////////////////////////////////////////// Create
				case COP_SHEAR:
					///////////////////////////// String
					str = "SHEAR";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "SOLID";		ID	= COP_SHEAR;
						strCur += "Click on a SOLID to Shear";
					break;
				//////////////////////////////////////////// Create
				case COP_SPAWN:

					Init_SOL();	// No Modeless Dlg, so Init Here
					///////////////////////////// String
					str = "SPAWN";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					str	= "SOLID";		ID	= COP_SPAWN;
						strCur = "Composite Affine/Symmetry Transformations@";
						strCur += "Click on a SOLID to Spawn";
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

void CSolCreOp::Serialize(CArchive& ar)
{

	CPatCreOp::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" SolCreOp:    Storing\n");	
		

	}
	else
	{
		TRACE(" SolCreOp:    Loading\n");	

	
	}        
}
///////////////////////////////////// end of Module //////////////////////		

