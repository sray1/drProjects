// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
#include "drgrafrm.h"
#include "UserMsg.h"
#include "drawView.h"
/////////////////////
#include "drgradoc.h"
#include "AxObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
/////////////////////
#include "Def_Objs.h"                    
#include "Def_Mous.h"                    
#include "Def_CuPS.h"                    
#include "Def_Ms.h" // Mesh Types for Patch
///////////////////// dialogMgr
#include "MCurMgr.h"  
#include "EDlgMgr.h"			// PIPE 
///////////////////// elements
#include "Def_IGen.h"
#include "Def_Elem.h"
#include "Ext_Elem.h"
#include "DrNode.h"
#include "DrFE1D.h"
#include "DrFE2D.h"
//#include "DrPipe.h"
//#include "DrPlate.h"
#include "DrCurve.h"
///////////////////// DrawObjs
#include "Def_Draw.h"
#include "DrLabel.h" 	
///////////////////// specials
#include "Def_Spec.h"
#include "Obj3DMnu.h"
#include "PatchMnu.h"
#include "DrPen.h"
#include "Layer.h"
#include "booleans.h"
#include "precison.h"
/////////////////////
#include "mouse.h"
#include "DListMgr.h"
/////////////////////
#include "MI_GangC.h" 
#include "MI_CProf.h" 
/*
//	Moved to CreOMgr Dll   01/14/98 
#include "MI_CSPN.h" 
//	Moved to CreOMgr Dll   01/14/98 end
*/
////////////////////// 
//#include "Dlg_CDlg.h"
//////////////////////
#include "CommRsrc.h"
#include "MCurRsrc.h"
 
#include "CurMouAX.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	DEFAULT_AXIS		3	// Z-Axis for especially 2D Problem and for 3D
								// Later it will be obtained from Document Default		todo
////////////////////////////////////////////////////////////////////////////////////////////
#define COMBO_NIDJ_LOC 		9     // Location of NidJ in element ComboBox Temporary
#define MIN_NODES_CURVE		2        
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
#define MAX_NODES_FE1D		2
////////////////////////////////////
IMPLEMENT_SERIAL(CCurMouAX,CNodMouAX,1)
/////////////////////////////////////////////////////////////////////////////
CCurMouAX::CCurMouAX()
{

	if(!m_ElSegList.IsEmpty())
		m_ElSegList.RemoveAll();
	if(!m_NodeList.IsEmpty())
		m_NodeList.RemoveAll();
	////////////////////////////
	m_pLQCInDlg			= NULL;                                                                                
	m_pCrcInDlg			= NULL;
 	/////////////////////////////////////////// Curve 
    m_LastCurveNum		= 0;		// internal
	m_CurrentCurveType	= CP_LINEAR;
	m_CurrentCurveID	= "C0";
	m_CurrentCurveIDOld	= "";
	m_bCurveDone		= TRUE;		// for dragging
	m_nCirMaxNode		= 3;		// = 3
	m_ElPerSeg			= 1;
	m_Ratio				= 1.0;
	m_bClosed			= FALSE;
	m_bAdvanceOn		= FALSE;
	/////////////////////////////////////////// Circle
	m_CircType			= CIRCLE_BY_NO3;
	m_SegAngle			= 120.;
	m_bAutoSeg			= TRUE;
	m_dAngSpec			= 0.;
	m_bArc				= TRUE;
	m_dAng				= 90.;
	m_FromID			= "";
	m_ToID				= "";
	m_TIID				= "";
	m_CCID				= "";
	m_CAID				= "";
	m_CBID				= "";
	m_dRadius			= 10.;
	///
	m_bAxis				= FALSE;		
	m_nAxis				= DEFAULT_AXIS;				// default
	m_bNegative			= FALSE;
	/////////////////////////////////////////// 
}

CCurMouAX::~CCurMouAX()
{
	/////////////////////////////////// Modeless Dialogs
	if(m_pLQCInDlg->m_hWnd)
		m_pLQCInDlg->DestroyWindow();
	if(m_pCrcInDlg->m_hWnd)
		m_pCrcInDlg->DestroyWindow();
	///////////////////
	delete m_pLQCInDlg; 
	delete m_pCrcInDlg; 
	///////////////////
}

void CCurMouAX::InitDlgIn_CUR()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////////////// System Sizes
	m_pLQCInDlg		= new CDlg_LQCI(pWnd); 
	m_pCrcInDlg		= new CDlg_CrcI(pWnd,m_CircType); 
}
	
int CCurMouAX::LeftDown_CURVE()
{
	
	///////////////////////////////////////////////////////// Disable BLine
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	pWnd->GetMenu()->EnableMenuItem(IDM_OPTION_BLINEON,MF_BYCOMMAND|MF_GRAYED);
	/////////////////////////////////////////////////////////////////////////////
	if( m_nNodeDone >0)   // 2nd time Onward for LeftDown
	{
		//////////////////////////////////// reset mouse to AnchorNode
										  // in case interrupted
		CString NID = GetAnchorNodeID();
		LPOINT3 MouseWIC;
		//////////////////
		CDrNode* pNode;
		if(m_bAnchorCNode)
		{
			pNode = (CDrNode*)GetObjectFromID(NID, CNODE);
			SetMouseWICFromNode(pNode,&MouseWIC);
		}
		else
		{
			pNode = (CDrNode*)GetObjectFromID(NID, INODE);
			SetMouseWICFromNode(pNode,&MouseWIC);
		}
		//////////////////////////////
		SetMouseOldWIC(GetMouseWIC());
		SetMouseWIC(MouseWIC);
		//////////////////////////////////// DragOn
		if(m_bDragOn)
		{   
			//////////////////////
			PostLeft();
			//////////////////////
			m_bDragging =TRUE; 
			m_pView->SetCapture(); 
/*
			///////////// Width/Height TOBEDONE at OnSize
			RECT Rect;
			Rect.left  = 0;
			Rect.top   = 0;
			Rect.right = m_nClientWidth;
			Rect.bottom= m_nClientHeight;
			ClientToScreen(&Rect);
			ClipCursor(&Rect);
*/
			return 0;
		}
		else
		{
			////////////////////////
			UpdateCDlg_FALSE();
			////////////////////////
		}
	}	             
	return 0;
}
	
void CCurMouAX::ElementLeftDown_CUR()
{	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	/////////////////////////////////////////////////////////
//	int nMeshType;
	////////////////////////
	m_bCurveDone	= FALSE;
	/////////////////////
	switch(m_nActiveTool) 
	{
		
		////////////////////////////////////////////////// CURVE	
		case C_CIRCLE:	

			////////////////////////
			if(m_bSingleSegOn == TRUE)
			{ 
				pBool->ToggleSingleSegOn();
				m_bSingleSegOn	= FALSE;
			}		
			m_CurrentCurveType = CP_CIRCLE;
			LeftDown_CURVE();
			return;


		case C_ELLIPSE:

			m_CurrentCurveType = CP_ELLIPSE;
			LeftDown_CURVE();
			return;


		case C_PARABOLA:

			m_CurrentCurveType = CP_PARABOLA;
			LeftDown_CURVE();
			return;


		case C_LINEAR:

			m_CurrentCurveType = CP_LINEAR;
			LeftDown_CURVE();
			return;


		case C_QUADRATIC:

			m_CurrentCurveType = CP_QUADRATIC;
			LeftDown_CURVE();
			return;


		case C_BSPLINE:

			m_CurrentCurveType = CP_BSPLINE;
			LeftDown_CURVE();
			return;


		case C_BEZIER:

			m_CurrentCurveType = CP_BEZIER;
			LeftDown_CURVE();
			return;


		case C_NURB:

			m_CurrentCurveType = CP_NURB;
			LeftDown_CURVE();
			return;


/*
		////////////////////////////////////////////////// POST	
		case C_POST:				// CURVE
			///////		
			m_MI_Cur_I.LBDownInit_CPost();
			return;
		 
*/		
		//////////////////////////////////////////////////
		default:
			break;
	}  

}
	
int CCurMouAX::ShowCurve(CString* pID,BOOL bFinal)
{

	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CAxObjMgr* pObjectMgr  = pDoc->GetAxObjMgr(); 
	CDListMgr*	pList;
	int nActiveIndex;
	////////////////////////////////////////////////////////////////// Save ObjectType/Index
//	UINT nTypeOld			= pObjectMgr->GetActiveObjectType();
// 	int nActiveIndexOld		= pObjectMgr->GetActiveObjectIndex();    // for Calling Object
	///////////////////
	pObjectMgr->SetActiveObjectType(CURVE);
	////////////////////////////////////////////////////// Add to DataBase, if not Existing
	///////////////////////////////////////// delete & Add
	pList = pObjectMgr->GetObjectList(CURVE);
	nActiveIndex = pList->GetObjectIndex(CURVE, *pID);
	if(nActiveIndex>=0)
	{
		pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
		m_pCurrentCurve = (CDrCurve*)NULL;
	}
//////////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
	if(1!=1)
	{
		POSITION pos;
		CDListMgr*	pListD;
		CString* str;
		int i,nodCount;
		///////////////////////////////////////////////////////// Node
		pListD = pObjectMgr->GetObjectList(NODE);
		nodCount = pListD->GetCount();
		////
		str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		sprintf(buf,"# of Nodes in NodeList = %d",nodCount);
		/////////////////////////	
		AfxMessageBox(*str);
		/////////////////////////
		str->ReleaseBuffer();
		delete str;
		///////////
		for(i=0;i<nodCount;i++)
		{
			pos = pListD->FindIndex(i);
			CDrNode* pNode = (CDrNode*)pListD->GetAt(pos);
			CString ID = pNode->GetObjectID();
			int LevelT = pNode->GetLevelType();
			BOOL bCNode= (pNode->GetNodeCard())->bnid_c;
			BOOL bGen  = pNode->IsGenerated();
			////
			str = new CString;
			buf = str->GetBuffer(BUFF_SIZE);
			int j;
			//////
			j = sprintf(buf,"CCurMouAX::ShowCurve()\n");
			j += sprintf(buf + j,"\tNodeID(Node#%d) = %s\n",i,ID);
			//////
			CString yes = "Yes";
			CString no = "No";
			///////////////////
			CString CN = no;
			if(bCNode)
				CN = yes;
			///////////////////
			j += sprintf(buf + j,"\tIsCNode = %s\n",CN);
			///////////////////
			CN = no;
			if(bGen)
				CN = yes;
			///////////////////
			j += sprintf(buf + j,"\tIsGenerated = %s\n",CN);
			///////////////////
			j += sprintf(buf + j,"\tLevelType = %d\n",LevelT);
			/////////////////////////	
			AfxMessageBox(*str);
			/////////////////////////
			str->ReleaseBuffer();
			delete str;
			///////////
		}
		///////////
	}
#endif
//////////////////////////////////////////////////////////////////////////////////////
	m_pCurrentCurve	= (CDrCurve*)(pObjectMgr->AddToDataBase(*pID,nActiveIndex,CURVE));
	m_pCurrentCurve->SetShow(FALSE);	// not quite ready
	///////////////////////////////////////// Get rid of Old CNodes & INodes
	if(!(m_pCurrentCurve->GetCNodeList()->IsEmpty())  )
		m_pCurrentCurve->GetCNodeList()->RemoveAll();
	if(!(m_pCurrentCurve->GetINodeList()->IsEmpty())  )
		m_pCurrentCurve->GetINodeList()->RemoveAll();
	/////////////////////////////////////////////////////////////// Fill Input Nodes
	CDListMgr* pINodeList = m_pCurrentCurve->GetINodeList();
	pINodeList->AddTail(&m_NodeList);	// copy
	///////////////////////////////////////////////////////
	m_pCurrentCurve->SetRatio_S(m_Ratio);
	if(m_nNodeDone<=2)
		m_pCurrentCurve->SetClosed_S(FALSE);
	else
		m_pCurrentCurve->SetClosed_S(m_bClosed);
	/////////////////////////////////////////////////////////////// Using GangC
	CMI_GangC	GangC;
	CDrNode*	pAddNode;
	POSITION	pos;
	switch(m_CurrentCurveType)
	{
		case CP_CIRCLE:

			switch(m_CircType)
			{
				
				case CIRCLE_BY_ROT:

					//////////////////////////////////////////// FromID & ToID
					pos			= pINodeList->FindIndex( 1 );
					pAddNode	= (CDrNode*)(pINodeList->GetAt(pos));
					m_FromID	= pAddNode->GetObjectID();
					pINodeList->RemoveAt(pos);
					////////////
/*
					if(!m_bAxis)	// if Axis input, No ToID Node
					{
*/
						pAddNode	= (CDrNode*)(pINodeList->GetTail());
						m_ToID		= pAddNode->GetObjectID();
						pINodeList->RemoveTail();
/*
					}
*/
					//////////////////////////////////// if Axis Input
					GangC.SetAxisInput(m_bAxis);
					GangC.SetAxis(m_nAxis);
					GangC.SetNegative(m_bNegative);
					////////////////////////////////////
					m_pCurrentCurve = GangC.CreateCircleByRot(
						*pID,m_pCurrentCurve,&m_NodeList,m_CurrentCurveType,
						&m_ElSegList,m_CircType,m_dAng,m_FromID,m_ToID,m_SegAngle,bFinal);
					/////////////////
					if(!m_pCurrentCurve)
					{
						pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
						return -1;
					}
					//////
					break;

					
				case CIRCLE_BY_NO3:

					m_pCurrentCurve = GangC.CreateCircleBy3Node(
						*pID,m_pCurrentCurve,&m_NodeList,m_CurrentCurveType,
						&m_ElSegList,m_CircType,m_SegAngle,m_dAngSpec,m_bArc,bFinal);
					/////////////////
					if(!m_pCurrentCurve)
					{
						pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
						return -1;
					}
					//////
					break;

					
				case CIRCLE_BY_2N_TI:

					//////////////////////////////////////////// TIID
					pos			= pINodeList->FindIndex( 1 );
					pAddNode	= (CDrNode*)(pINodeList->GetAt(pos));
					m_TIID		= pAddNode->GetObjectID();
//					pINodeList->RemoveAt(pos);
					////////////////////////////////////
					m_pCurrentCurve = GangC.CreateCircleBy_2N_TI(
						*pID,m_pCurrentCurve,&m_NodeList,m_CurrentCurveType,
						&m_ElSegList,m_CircType,m_SegAngle,bFinal);
					/////////////////
					if(!m_pCurrentCurve)
					{
						pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
						return -1;
					}
					//////
					break;

					
				case CIRCLE_BY_2N_CC:

					//////////////////////////////////////////// CCID
					pos			= pINodeList->FindIndex( 1 );
					pAddNode	= (CDrNode*)(pINodeList->GetAt(pos));
					m_CCID		= pAddNode->GetObjectID();
//					pINodeList->RemoveAt(pos);
					////////////////////////////////////
					m_pCurrentCurve = GangC.CreateCircleBy_2N_CC(
						*pID,m_pCurrentCurve,&m_NodeList,m_CurrentCurveType,
						&m_ElSegList,m_CircType,m_SegAngle,bFinal);
					/////////////////
					if(!m_pCurrentCurve)
					{
						pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
						return -1;
					}
					//////
					break;

					
				case CIRCLE_BY_2CN_TI_R:

					//////////////////////////////////////////// TIID
					pos			= pINodeList->FindIndex( 1 );
					pAddNode	= (CDrNode*)(pINodeList->GetAt(pos));
					m_TIID		= pAddNode->GetObjectID();
//					pINodeList->RemoveAt(pos);
					//////////////////////////////////////////// CAID
					pAddNode	= (CDrNode*)(pINodeList->GetHead());
					m_CAID		= pAddNode->GetObjectID();
//					pINodeList->RemoveHead();
					//////////////////////////////////////////// CBID
					pAddNode	= (CDrNode*)(pINodeList->GetTail());
					m_CBID		= pAddNode->GetObjectID();
//					pINodeList->RemoveTail();
					////////////////////////////////////
					m_pCurrentCurve = GangC.CreateCircleBy_2CN_TI_R(
						*pID,m_pCurrentCurve,&m_NodeList,m_CurrentCurveType,
						&m_ElSegList,m_CircType,m_dRadius,m_SegAngle,bFinal);
					/////////////////
					if(!m_pCurrentCurve)
					{
						pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
						return -1;
					}
					//////
					break;
				
				default:

					break;

			}
			break;
				
		default:

			m_pCurrentCurve = GangC.CreateCurve(*pID,m_pCurrentCurve,&m_NodeList,m_CurrentCurveType,
											&m_ElSegList,m_bAdvanceOn,bFinal);
			/////////////////
			if(!m_pCurrentCurve)
			{
				pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
				return -1;
			}
			//////
			break;
	}
////////////////////////////////////////////////////////////////////// Debug
#ifdef _DEBUG 
/*
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		int j;
		/////////////////////////
		j  = sprintf(buf,"CCurMouAX::ShowCurve\nAfter CreateCurve\nBefore UpdateViews:\n");
		j += sprintf(buf+j,"Nodes in the CNodeList:\n\t");
		//////////////////////////////
		pList = m_pCurrentCurve->GetCNodeList();
		////////////////////////////////////////
		for (POSITION posI = pList->GetHeadPosition( );posI !=NULL;)
		{
			////
			CDrNode* pNode = (CDrNode*)pList->GetNextObject(posI);
			j += sprintf(buf+j,"%s, ",pNode->GetObjectID());
		}
		sprintf( buf + j-2, ";");
		/////////////////////////	
		AfxMessageBox(*str);
		/////
		delete str;
*/
#endif
////////////////////////////////////////////////////////////////////// Debug End
	//////////////////////////////////////////////////////////////  Posting Dimension
	int nMeshElemDim;
	switch(pWnd->GetCurrentCntlID())
	{
		case EDIM_0: 
			nMeshElemDim = 0;	// Node(0D)
			break;
		default:
			nMeshElemDim = 1;	// pipe,beam etc(1D)
	}
	m_pCurrentCurve->SetMeshElemDim(nMeshElemDim);					// 1D or 2D 
	////////////////////////////////////////////////////////////////////// Show
	m_pCurrentCurve->SetDirty(TRUE);
	m_pCurrentCurve->SetShow(TRUE);	
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
	pObjectMgr->SetActiveObjectType(CURVE);		    // set Active Index									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CURVE);
	//////////////////////////////////////////////////////////////////// restore ObjectType/Index
//	pObjectMgr->SetActiveObjectType(nTypeOld);             
//	pObjectMgr->SetActiveObjectIndex(nActiveIndexOld);		// set Active Index for Calling Object									
	///////////////////////////////
	return 0;
}	 

void CCurMouAX::OnEBoxLButtonDown_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	CDListMgr* pDListMgr;
	/////////////////////////////////// 
   	m_bDragOn 		= pBool->IsDragOn();
	m_bDialogOn		= pBool->IsDialogOn();
	m_bAutoAcceptOn	= pBool->IsAutoAcceptOn();
	m_bSingleSegOn	= pBool->IsSingleSegOn();
	m_bBLineOn		= pBool->IsBLineOn();
	if(!m_bBLineOn && m_bCurveDone)			// Reset
	{
		m_nNodeDone = 0;
		////////////////
		if(!m_ElSegList.IsEmpty())
			m_ElSegList.RemoveAll();
		if(!m_NodeList.IsEmpty())
			m_NodeList.RemoveAll();
		///////////////////////////
/*
		char buf[50];
		int nLastNum = pObjectMgr->GetLastInputNo(NODE);		// internal
		sprintf(buf,"%d",nLastNum);
		m_CurrentNodeID = "";
		m_CurrentNodeID	+= buf;
		pObjectMgr->BumpLastInputNo(NODE);		// bump it
		m_CurrentNodeIDOld	= m_CurrentNodeID;
		m_AnchorNodeID		= m_CurrentNodeID;
*/
		/////
//		UpdateCDlg_FALSE();
		///////////////////
	}
	//////////////////////////////////////////////////////// LOG
	m_pdc->DPtoLP(&point);
	//////////////////////////////////////////////////
	m_nActiveObject = pWnd->GetActiveObjectType(); 
	m_nActiveTool	= pWnd->GetActiveToolType();    // -1= INSERT
	/////////////////////////////////////////////////////////////////////////
	pObjectMgr->SetActiveObjectType(m_nActiveObject);       // Set ObjectType 
	////////////////////////////////////////////////// take care of Edit AllClear
	pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	if(!(pDListMgr->GetSpecificObjectCount(NODE)) ) m_nNodeDone = 0;
	/////////////////////////////////////////////////////////////////
    /////////////////////////////  ELement Dialog On/Off Check
    if(m_Gener == FORWARD)
		ElementLeftDown_CUR();
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftDown_I();
	//////////////////////////////////
}

void CCurMouAX::UpdateCDlg_TRUE()
{
	//////////////////////////////////
	if
		(
			m_CurrentCurveType == CP_LINEAR	||	m_CurrentCurveType == CP_QUADRATIC	||
			m_CurrentCurveType == CP_BEZIER	||
			m_CurrentCurveType == CP_BSPLINE||	m_CurrentCurveType == CP_NURB
		)
	{
		m_pLQCInDlg->UpdateData(TRUE); // from screen
		//////////////////////////////
		m_CurrentCurveID	= m_pLQCInDlg->m_CID;
		m_CurrentNodeID		= m_pLQCInDlg->m_NID;
		m_ThirdCoord		= m_pLQCInDlg->m_dCoord;
		m_ElPerSeg			= m_pLQCInDlg->m_nElperSeg;
		m_Ratio				= m_pLQCInDlg->m_dRatio;
		m_bClosed			= m_pLQCInDlg->m_bClosed;
		m_bAdvanceOn		= m_pLQCInDlg->m_bAdvanceOn;
		////////////////////////////////////////////////
		if(m_bClosed)
			m_bAdvanceOn = FALSE;
		/////////////////////////
	}
	else
	if
		(
			m_CurrentCurveType == CP_CIRCLE	
		)
	{
		m_pCrcInDlg->UpdateData(TRUE); // from screen
		//////////////////////////////
		m_CurrentCurveID	= m_pCrcInDlg->m_CurveID;
		m_CurrentNodeID		= m_pCrcInDlg->m_NID;
		m_ThirdCoord		= m_pCrcInDlg->m_dCoord;
		m_ElPerSeg			= m_pCrcInDlg->m_nMesh;
		m_Ratio				= m_pCrcInDlg->m_Ratio;
		m_SegAngle			= m_pCrcInDlg->m_SegAngle;
		m_bAutoSeg			= m_pCrcInDlg->m_bAutoSeg;
		/////////////////////////////////////////////////
		switch(m_CircType)
		{
			case CIRCLE_BY_NO3:
				m_bClosed		= m_pCrcInDlg->m_bClosed;
				m_dAngSpec		= m_pCrcInDlg->m_dAngSpec;
				m_bArc			= m_pCrcInDlg->m_bArc;
				break;
			case CIRCLE_BY_ROT:
				m_bClosed		= m_pCrcInDlg->m_bClosed;
				m_dAng			= m_pCrcInDlg->m_dAngSpec;
				m_bAxis			= m_pCrcInDlg->m_bAxis;
				m_nAxis			= m_pCrcInDlg->m_nAxis;
				m_bNegative		= m_pCrcInDlg->m_bNegative;
				break;
			case CIRCLE_BY_2N_TI:
			case CIRCLE_BY_2N_CC:
				break;
			case CIRCLE_BY_2CN_TI_R:
				m_dRadius		= m_pCrcInDlg->m_dAngSpec;
			default:
				break;
		}
	}
}			

void CCurMouAX::UpdateCDlg_FALSE()
{
	/////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString str;
	/////////////////////////////////////////////////////////
	if
		(
			m_CurrentCurveType == CP_LINEAR		||	m_CurrentCurveType == CP_QUADRATIC	||
			m_CurrentCurveType == CP_BEZIER		||
			m_CurrentCurveType == CP_BSPLINE	||	m_CurrentCurveType == CP_NURB
		)
	{
		m_pLQCInDlg->m_CID			= m_CurrentCurveID;
//		m_pLQCInDlg->m_NID			= "";	// 012798
		m_pLQCInDlg->m_NID			= m_CurrentNodeID;	
		m_pLQCInDlg->m_dCoord		= m_ThirdCoord;
		m_pLQCInDlg->m_nElperSeg	= m_ElPerSeg;
		m_pLQCInDlg->m_dRatio		= m_Ratio;
		m_pLQCInDlg->m_bClosed		= m_bClosed;
		m_pLQCInDlg->m_bAdvanceOn	= m_bAdvanceOn;
		//////////////////////////////////////
		if(m_nNodeDone>=1)
			m_pLQCInDlg->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
		else
			m_pLQCInDlg->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
		///////////////////
		if(	m_nNodeDone<3 )
		{
			m_bClosed = FALSE;
			m_pLQCInDlg->GetDlgItem(IDC_CLOSED)->EnableWindow(FALSE);
		}
		else
		m_pLQCInDlg->GetDlgItem(IDC_CLOSED)->EnableWindow(TRUE);
		///////////////////
		if(m_CurrentCurveType == CP_LINEAR || m_bClosed == TRUE)
			m_pLQCInDlg->GetDlgItem(IDC_ADVANCED)->EnableWindow(FALSE);
		else
			m_pLQCInDlg->GetDlgItem(IDC_ADVANCED)->EnableWindow(TRUE);
		///////////////////	
		switch(m_nNodeDone)
		{
			case 0:
				if(m_bSingleSegOn)
					str = "Creating Single Segment Curve@Click in the Start Node for the Curve";
				else
					str = "Creating New Curve: Click in @a Node on the Curve";
				break;
			case 1:
				if(m_bSingleSegOn)
					str = "Creating Single Segment Curve@Click in the End Node for the Curve";
				else
				{
					if(m_bCurveDone	== TRUE) // from BLineON
					{
						str = "Creating New Curve: Click in@Another Node on the Curve";
						m_bCurveDone	== FALSE;
					}
					else
						str = "Continuing on Same Curve: Click in@Another Node on the Curve";
				}
				break;
			default:
				str = "Select Another Node or If Ready@with Other Info., Click Right Button";
				break;
		}
		//////////////////////////////
		m_pLQCInDlg->UpdateData(FALSE); // To screen
	}
	else
	if
		(
			m_CurrentCurveType == CP_CIRCLE	
		)
	{
		//////////////////////////////////////
		if(m_nNodeDone>=1)
			m_pCrcInDlg->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
		else
			m_pCrcInDlg->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
		/////////////
		m_pCrcInDlg->m_CurveID		= m_CurrentCurveID;
		m_pCrcInDlg->m_NID			= "";
		m_pCrcInDlg->m_dCoord		= m_ThirdCoord;
		m_pCrcInDlg->m_nMesh		= m_ElPerSeg;
		m_pCrcInDlg->m_Ratio		= m_Ratio;
		m_pCrcInDlg->m_SegAngle		= m_SegAngle;
		m_pCrcInDlg->m_bAutoSeg		= m_bAutoSeg;
		////////////////////////////////////////
		switch(m_CircType)
		{
			case CIRCLE_BY_NO3:
				m_pCrcInDlg->m_bClosed		= m_bClosed;
				m_pCrcInDlg->m_dAngSpec		= m_dAngSpec;
				m_pCrcInDlg->m_bArc			= m_bArc;
				switch(m_nNodeDone)
				{
					case 0:
						m_pCrcInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Ist Node");
						str = "Creating A Circle: Click in@Ist Node on the Circle";
						break;
					case 1:
						m_pCrcInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("2nd Node");
						str = "Creating A Circle: Click in@2nd Node on the Circle";
						break;
					case 2:
						m_pCrcInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Last Node");
						str = "Select@Last Node on the Circle";
						break;
					case 3:
						m_pCrcInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
						m_pCrcInDlg->GetDlgItem(IDC_NID)->EnableWindow(FALSE);
						str = "Ready with Other Info.?@Click Right Button";
						break;
					default:
						break;
				}
				break;
			case CIRCLE_BY_ROT:
				m_pCrcInDlg->m_dAngSpec		= m_dAng;
				m_pCrcInDlg->m_bAxis		= m_bAxis;
				m_pCrcInDlg->m_nAxis		= m_nAxis;
				m_pCrcInDlg->m_bNegative	= m_bNegative;
				////////////////////
				switch(m_nNodeDone)
				{
					case 0:

						m_pCrcInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Rot.Node");
						///
						m_pCrcInDlg->GetDlgItem(IDC_AXIS)->SetWindowText("");
						m_pCrcInDlg->GetDlgItem(IDC_AXIS_X)->SetWindowText("");
						m_pCrcInDlg->GetDlgItem(IDC_AXIS_Y)->SetWindowText("");
						m_pCrcInDlg->GetDlgItem(IDC_AXIS_Z)->SetWindowText("");
						m_pCrcInDlg->GetDlgItem(IDC_NEGATIVE)->SetWindowText("");
						m_pCrcInDlg->GetDlgItem(IDC_AXIS)->EnableWindow(FALSE);
						m_pCrcInDlg->GetDlgItem(IDC_AXIS_X)->EnableWindow(FALSE);
						m_pCrcInDlg->GetDlgItem(IDC_AXIS_Y)->EnableWindow(FALSE);
						m_pCrcInDlg->GetDlgItem(IDC_AXIS_Z)->EnableWindow(FALSE);
						m_pCrcInDlg->GetDlgItem(IDC_NEGATIVE)->EnableWindow(FALSE);
						///
						str = "Creating A Circle: Click in@Node to Rotate";
						break;
					case 1:
						m_pCrcInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("From Node");
						str = "Creating A Circle: Click in@Ist (C)Node defining Axis";
						break;
					case 2:
						///
						m_pCrcInDlg->GetDlgItem(IDC_AXIS)->SetWindowText("Axis");
						m_pCrcInDlg->GetDlgItem(IDC_AXIS)->EnableWindow(TRUE);
						//
/*
						m_pCrcInDlg->GetDlgItem(IDC_AXIS_X)->SetWindowText("X");
						m_pCrcInDlg->GetDlgItem(IDC_AXIS_Y)->SetWindowText("Y");
						m_pCrcInDlg->GetDlgItem(IDC_AXIS_Z)->SetWindowText("Z");
						m_pCrcInDlg->GetDlgItem(IDC_NEGATIVE)->SetWindowText("Negative");
						m_pCrcInDlg->GetDlgItem(IDC_AXIS_X)->EnableWindow("TRUE");
						m_pCrcInDlg->GetDlgItem(IDC_AXIS_Y)->EnableWindow("TRUE");
						m_pCrcInDlg->GetDlgItem(IDC_AXIS_Z)->EnableWindow("TRUE");
						m_pCrcInDlg->GetDlgItem(IDC_NEGATIVE)->EnableWindow("TRUE");
*/
						///
						m_pCrcInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("To Node");
						str = "Circle: Click in 2nd (C)Node defining@Axis or SELECT Axis of Rotation";
						break;
					case 3:
						m_pCrcInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
						m_pCrcInDlg->GetDlgItem(IDC_NID)->EnableWindow(FALSE);
						str = "Ready with Other Info.?@Click Right Button";
						break;
					default:
						break;
				}
				break;
			case CIRCLE_BY_2N_TI:
				switch(m_nNodeDone)
				{
					case 0:
						m_pCrcInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Node_I");
						str = "Creating A Circle: Click in@Node at End_I";
						break;
					case 1:
						m_pCrcInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Node_TI");
						str = "Creating A Circle: Click in@Tangent Intersection CNode";
						break;
					case 2:
						m_pCrcInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Node_J");
						str = "Creating A Circle: Click in@Node at End_J";
						break;
					case 3:
						m_pCrcInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
						m_pCrcInDlg->GetDlgItem(IDC_NID)->EnableWindow(FALSE);
						str = "Ready with Other Info.?@Click Right Button";
						break;
					default:
						break;
				}
				break;
			case CIRCLE_BY_2N_CC:
				switch(m_nNodeDone)
				{
					case 0:
						m_pCrcInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Node_I");
						str = "Creating A Circle: Click in@Node at End_I";
						break;
					case 1:
						m_pCrcInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Node_CC");
						str = "Creating A Circle: Click in@CNode defining Center";
						break;
					case 2:
						m_pCrcInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Node_J");
						str = "Creating A Circle: Click in@CNode defining Angle";
						break;
					case 3:
						m_pCrcInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
						m_pCrcInDlg->GetDlgItem(IDC_NID)->EnableWindow(FALSE);
						str = "Ready with Other Info.?@Click Right Button";
						break;
					default:
						break;
				}
				break;
			case CIRCLE_BY_2CN_TI_R:
				m_dRadius		= m_pCrcInDlg->m_dAngSpec;
				//////////////////////////////////////
				switch(m_nNodeDone)
				{
					case 0:
						m_pCrcInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("CNode_A");
						str = "Creating A Circle: Click in@CNode_CA on Ist Tangent";
						break;
					case 1:
						m_pCrcInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Node_TI");
						str = "Creating A Circle: Click in@Tangent Intersection CNode";
						break;
					case 2:
						m_pCrcInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("CNode_B");
						str = "Creating A Circle: Click in@CNode_CB on 2nd Tangent";
						break;
					case 3:
						m_pCrcInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
						m_pCrcInDlg->GetDlgItem(IDC_NID)->EnableWindow(FALSE);
						str = "Ready with Other Info.?@Click Right Button";
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
		//////////////////////////////
		m_pCrcInDlg->UpdateData(FALSE); // To screen
	}
	//////////////////////////////////////
	pWnd->GetCurrStat()->SetText(str);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
}			

int CCurMouAX::LeftUp_CURVE(CPoint point)
{
	//////////////////////////////////////
	switch(m_CurrentCurveType)
	{
		case CP_CIRCLE:

			switch(m_CircType)
			{
				
				case CIRCLE_BY_NO3:
					if((LeftUp_NODE(point,FALSE)) == -2)		// Cancel
					{
						m_nNodeDone--;
						return -2;
					}
					break;
				case CIRCLE_BY_ROT:
					///////////////////
					switch(m_nNodeDone)
					{
						case 1 :	// Node	
							if((LeftUp_NODE(point,FALSE)) == -2)		// Cancel
							{
								m_nNodeDone--;
								return -2;
							}
							break;
						case 2 :	// CNode
							if((LeftUp_NODE(point,TRUE)) == -2)		// Cancel
							{
								m_nNodeDone--;
								return -2;
							}
							break;	
						case 3 :	// CNode or Axis Input
							if(m_bAxis)
								break;
							///////////
							if((LeftUp_NODE(point,TRUE)) == -2)		// Cancel
							{
								m_nNodeDone--;
								return -2;
							}
							break;	
						default :	
							{
								AfxMessageBox("ERROR:\nCCurMouAX::LeftUp_CURVE\nCIRCLE_BY_ROT\nInvalid Cases");
								return -1;
							}
					}
					break;
				case CIRCLE_BY_2N_TI:	// fall thro'
				case CIRCLE_BY_2N_CC:
					switch(m_nNodeDone)
					{
						case 1 :	// Node
							if((LeftUp_NODE(point,FALSE)) == -2)		// Cancel
							{
								m_nNodeDone--;
								return -2;
							}
								break;
						case 2 :	// CNode
							if((LeftUp_NODE(point,TRUE)) == -2)		// Cancel
							{
								m_nNodeDone--;
								return -2;
							}
							break;	
						case 3 :	// Node
							if((LeftUp_NODE(point,FALSE)) == -2)		// Cancel
							{
								m_nNodeDone--;
								return -2;
							}
							break;
						default :	// Node
							if((LeftUp_NODE(point,FALSE)) == -2)		// Cancel
							{
								m_nNodeDone--;
								return -2;
							}
							break;
					}
					break;
				case CIRCLE_BY_2CN_TI_R:
					switch(m_nNodeDone)
					{
						case 1 :	// CNode Fall thro'
						case 2 :	// CNode
						case 3 :	// CNode
							if((LeftUp_NODE(point,TRUE)) == -2)		// Cancel
							{
								m_nNodeDone--;
								return -2;
							}
							break;	
						default :	// Node
							if((LeftUp_NODE(point,FALSE)) == -2)		// Cancel
							{
								m_nNodeDone--;
								return -2;
							}
							break;
					}
					break;
				
				default:

					break;

			}
			break;
			
		default:

			// Node
			if((LeftUp_NODE(point,FALSE)) == -2)		// Cancel
			{
				m_nNodeDone--;
				return -2;
			}
			break;
	}
	//////////////////////////////////
	m_NodeList.InsertObject(m_pCurrentNode);
	//////////////////////////////////////////////////// Show Curve
	if(m_CurrentCurveType == CP_CIRCLE)
	{
		if(m_nNodeDone == 3) 
		{
//			pID = &m_CurrentCurveID;
			m_ElSegList.AddTail(m_ElPerSeg);
			//////////////////////////
			if(ShowCurve(&m_CurrentCurveID,FALSE)<0)		// FALSE = Not Final
			{
//				AfxMessageBox("ERROR:\nCCurMouAX::LeftUp_CURVE\nShowCurve Problem");
				return -1;
			}
		}
	}
	else
	if(m_nNodeDone >1)
	{		
//		pID = &m_CurrentCurveID;
		m_ElSegList.AddTail(m_ElPerSeg);
		//////////////////////////
		if(ShowCurve(&m_CurrentCurveID,FALSE)<0)		// FALSE = Not Final
		{
//			AfxMessageBox("ERROR:\nCCurMouAX::LeftUp_CURVE\nShowCurve Problem");
			return -1;
		}
	}
	/////////////////////////////////////// Set Anchor
	SetAnchorNodeID(m_CurrentNodeIDOld );
	//////////////////////////////////////
	return 0;
}

void CCurMouAX::ElementLeftUp_CUR(CPoint point)
{                          

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	//////////////////////////////////////////////////////////////////
//	CString*	pID;
	/////////////
//	char buf[20];
	CString Nid;
	BOOL bRightOn = FALSE;
	///////////////////
	switch(m_nActiveTool) 
	{
		
		case FE1D:
/*										
					if(!ShowNode(pID,FALSE,1))
					{
						m_nNodeDone++;
						SetCurrentNodeID(*pID);
					}
					else                             // cancelled
*/
						return;	
					////////////////////////////////
					if(m_nNodeDone == MAX_NODES_FE1D)
					{         
						m_nNodeDone = 1;   // Reset  
						///////////////////////////// Put NodePair in PipeList/draw 
						CString nid[2];
						nid[0] = GetAnchorNodeID();
						nid[1] = GetCurrentNodeID(); 
//						CDrFE1D Pipe;
						if(PutEndIdsInPipeList(nid,2)<0)
						{
							m_nNodeDone--;
							return;
						}
						//////////////////////////////////////
						if(m_bDialogOn)             // Show FE1D PropDlg/draw 
						{
							////////////////////
//							CEDlgMgr*	pEDlgMgr;
							/////////////////////////////////////////
//							if (pEDlgMgr->DoModal_Pipe(0) == IDCANCEL)
								return;
							/////////////////////////////////////////	
						}
					}
					/////////////////////////////////////// Set Anchor
					SetAnchorNodeID(m_CurrentNodeIDOld );
					/////////////////////////////////////
					return;
		///////////////////////////////////////////////////// CURVEs Insert
		case C_CIRCLE:
		case C_ELLIPSE:
		case C_PARABOLA:
		case C_LINEAR:
		case C_QUADRATIC:
		case C_BSPLINE:
		case C_BEZIER:
		case C_NURB:

			m_nNodeDone++;
			////////////////
			UpdateCDlg_TRUE();
			////////////////////
			if(LeftUp_CURVE(point)<0)
			{
				////////////////////////////////////////////////////////////////// 
				if(pWnd->GetCurrentIGenID() == C_CIRCLE)
				{
					/////////////////
					if(m_bClosed)
					{
						if(m_ElPerSeg<3)
						{
							AfxMessageBox("INVALID DATA:\nFor Closed Circle\nAtleast 3 Elements Should be Specified!");
							GetCrcInDlg()->GetDlgItem(IDC_ELEMS)->SetFocus();
							/////////////////
							GetCrcInDlg()->UpdateData(FALSE);
							/////////////////
							return;
						}
					}
					else
					if(m_ElPerSeg<1)
					{
						AfxMessageBox("INVALID DATA:\nFor Open Circle\nAtleast 1 Element Should be Specified!");
						GetCrcInDlg()->GetDlgItem(IDC_ELEMS)->SetFocus();
						/////////////////
						GetCrcInDlg()->UpdateData(FALSE);
						/////////////////
						return;
					}
				}
				/////////////////
				return;
			}
			////////////////////
//			UpdateCDlg_FALSE();
			//////////////////////////////////// Circle 
			if(m_nActiveTool == C_CIRCLE)
			{
				if(m_nNodeDone == 3)
					bRightOn = TRUE;
			}
			//////////////////////////////////// If Single Line, Get RightButton Done
			else
			{
				if(m_nNodeDone>=2 && m_bSingleSegOn)
					bRightOn = TRUE;
			}
			////////////////////////
			if(bRightOn)
			{
				////////////////////
//				UpdateCDlg_TRUE();
				if(RightUp_CURVE()<0)
				{
					m_nNodeDone--;
					return;
				}
//				UpdateCDlg_FALSE();
				////////////////////
			}
			UpdateCDlg_FALSE();
			///////
			return;
	
		////////////////////////////////////////////////// POST
/*
		case C_POST:				// CURVE
			///////		
			m_MI_Solid.LBUpCurvePost();
			return;
*/		
		//////////////////////////////////////////////////
		default:  
			break;
	} 
}	
/*
//	Moved to CreOMgr Dll   01/14/98 

int CCurMouAX::LeftUp_CSPAWN(CPoint point)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CAxObjMgr* pObjectMgr  = pDoc->GetAxObjMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(CURVE);
	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrCurve*	pDrCurve;
	int			nActiveIndex,index;
	////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	WORtoWOP(&dTol,&dTol);	// physical
	///////////////////////////////////////////// See if any Existing Node Hit
	index = IsObjectHit(CURVE,point,0);
	////////////////////////////////////////////////////
	if(index<0)
		return -2;
	//////////////////////////////////////////////////////////////// Existing Curve
	pDrCurve	= (CDrCurve*)pDListMgr->GetObject(index);
	ID			= pDrCurve->GetObjectID();
	/////////////////////////////////////////
	pList = pObjectMgr->GetObjectList(CURVE);
	nActiveIndex = pList->GetObjectIndex(CURVE, ID);;
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
	pObjectMgr->SetActiveObjectType(CURVE);		    // set Active Type									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CURVE);
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
			nResult = ShowCurveInfo(pDrCurve);
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
					///////////////////////////////////////// 
					pList = pObjectMgr->GetObjectList(CURVE);
					nActiveIndex = pList->GetObjectIndex(CURVE, ID);;
					pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
					pObjectMgr->SetActiveObjectType(CURVE);		    // set Active Index									
					pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CURVE);
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
	//////////////////////////////////////////////////////////////////// finally, show Properties
	m_pCurrentCurve = pDrCurve;
	/////////////////////////////
	nResult = ShowCurveToSpawn(pDrCurve);
	///////////
	if( nResult == -1)		// 
	{
		AfxMessageBox("ERROR:\nCCurMouAX::LeftUp_CSpawn\nShowCurveToSpawn Problem");
		return -1;
	}
	else
	if(nResult == -2)		// Cancel
		return -2;
	////////////////////////////
	return 0;
}
//	Moved to CreOMgr Dll   01/14/98 end
*/


int CCurMouAX::ShowCurveInfo(CDrCurve* pDrCurve)
{
	int nResult;
	CString ID;
	CString* pID = &ID;
	ID = pDrCurve->GetObjectID();
	//////////////////////////////////////////////////////////////////////
	CDListMgr*		pNodeList	= pDrCurve->GetINodeList();
    CList<int,int>* pElSegList	= pDrCurve->GetElperSegList();
	CURVEPROC 		CurveType	= pDrCurve->GetCurveType_S();
	CIRCLETYPE		CircType	= pDrCurve->GetCircleType();
	CString			FromID		= pDrCurve->GetFromID_S();
	CString			ToID		= pDrCurve->GetToID_S();
	double			dAng		= pDrCurve->GetTheta_S();
	BOOL			bArc		= pDrCurve->IsArcType();
	BOOL			bClosed		= pDrCurve->IsClosed_S();
	double			dAngSpec	= pDrCurve->GetTheta_S();
	double			dRadius		= pDrCurve->GetRadius_S();
	//
	BOOL			bAxis		= pDrCurve->IsAxisInput();
	int				nAxis		= pDrCurve->GetAxis();
	BOOL			bNegative	= pDrCurve->IsNegative();
	///////////////////////////
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
	j = sprintf(buf,"***** A Curve Hit To Spawn ****\n");
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

					j += sprintf(buf+j,"Circle %s contains:\n\t%d InputNode to Rotate\n\t%d Elements\n",
							*pID,pNodeList->GetCount(),nElems);
					if(bAxis)
					{
						CString strAxis[3] = {"X-Axis","Y-Axis","Z-Axis"};
						CString strNeg = "Positive";
						if(m_bNegative)
							strNeg = "Negative";
						//
						j += sprintf(buf+j,"\tAxis of Rotation = %s %s\n",strNeg,strAxis[nAxis-1]);
					}
					else
						j += sprintf(buf+j,"\t%s and %s are Axis defining Nodes\n",FromID,ToID);
					///
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
	j += sprintf(buf+j,
		"\nYES:\t\tSpawn This Curve");
	j += sprintf(buf+j,
		"\nNO:\t\tFind Next Curve with Intersecting Trace");
	j += sprintf(buf+j,
		"\nCANCEL:\t\tCancel Selection Process");
	nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
	///////////////
	delete str;
	return nResult;
}

/*
//	Moved to CreOMgr Dll   01/14/98 
int CCurMouAX::ShowCurveToSpawn(CDrCurve* pDrCurve)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CAxObjMgr* pObjectMgr  = pDoc->GetAxObjMgr();
	CDrCurve*	pNewCurve;
	CDListMgr* pDListMgr;
	///////////////////
	pObjectMgr->SetActiveObjectType(CURVE);
	/////////////////////////////////////////////////////////////// Using CMI_CSPN
	CMI_CSPN MI_CSPN;
	int nResult = MI_CSPN.SpawnCurveShowingDlg(pNewCurve,pDrCurve, pDrCurve, CURVE); 
	if(nResult<0)
		return nResult;//
	/////////////////////////////////////////////////////////// Control RectBound
	pNewCurve->SetDirty(TRUE);
	pNewCurve->SetShow(TRUE);
	////////////////////////////////////////////////////////// Save
	CString CurveID	= pNewCurve->GetObjectID();
	pDListMgr	 	= pObjectMgr->GetObjectList(CURVE);
	int nCurveIndex = pDListMgr->GetObjectIndex(CURVE,CurveID); 
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nCurveIndex); 
	pObjectMgr->SetActiveObjectType(CURVE); 
    ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nCurveIndex,CURVE);
	///////////////////////////////
	return 0;
}	 
//	Moved to CreOMgr Dll   01/14/98 end
*/

void CCurMouAX::OnEBoxMouseMove_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point)
{  

	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
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
   	//////////////////////////////      ***** START FROM HERE *****
   	CPen    Pen;
	CPen*   PtrOldPen;
	//////////////////////////////
	m_pdc->SetBkMode(TRANSPARENT);
	//////////////////////////////	
	// Create Black Pen 2 Pixel wide;
	int two = 2;
	COLORREF crColor = 0x000000;  
	Pen.CreatePen ((int)PS_SOLID,two,crColor);
	PtrOldPen = m_pdc->SelectObject(&Pen);
	///////////////////////////
	m_MouseLOG = point;              // Device
	POINT MouseLOC;
	/////////////////////////	
	m_pdc->SetROP2 (R2_NOT); 
	
	MouseLOC = m_AnchorNodeLOG;      // Device
	m_pdc->DPtoLP(&MouseLOC);
	m_pdc->MoveTo (MouseLOC);

	MouseLOC = m_MouseOldLOG;        // Device
	m_pdc->DPtoLP(&MouseLOC);
	m_pdc->LineTo (MouseLOC);
	////////////////////////	  
//	m_pdc->SetROP2 (R2_COPYPEN);

	MouseLOC = m_AnchorNodeLOG;      // Device
	m_pdc->DPtoLP(&MouseLOC);
	m_pdc->MoveTo (MouseLOC);

	MouseLOC = m_MouseLOG;
	m_pdc->DPtoLP(&MouseLOC);
	m_pdc->LineTo (MouseLOC);

	m_MouseOldLOG = m_MouseLOG;
	///////////////////////////
   	m_pdc->SelectObject(PtrOldPen);   
	Pen.DeleteObject(); 
	//////////////////////////////////////
    LPOINT3 MouseWIC = GetMouseWIC();
    SetMouseOldWIC(MouseWIC);
   	///////////////////////
   	LOGtoWIC(&MouseWIC,&LpLOG); //LOG/Scaled WIC
   	////////////////////                 
    SetMouseWIC(MouseWIC);
    ///////////////////////////
//  pDoc->UpdateStatusBar(&dc);  WILL BE CALLED FROM VIEW, JUST SET HERE
	pMouseMgr->SetStatusMouseWIC(MouseWIC);
	//////////////////////////////////////////////    
}

void CCurMouAX::OnEBoxLButtonUp_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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
    if(m_bDragging)  // not currently dragging
    {
		m_bDragging = FALSE; 
		::ReleaseCapture();
		//	ClipCursor(NULL);				TOBEDONE 
	}	
	///////////////////////////////////////////////////////// 
	PreLeftUp(point);
    /////////////////////////////  ELement Dialog On/Off Check
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
	/////////////////
	PostLeft();
	/////////////////////////
	
}

void CCurMouAX::OnEBoxRButtonDown_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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
	CAxObjMgr* pObjectMgr  = pDoc->GetAxObjMgr();

	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
    /////////////////////////////  ELement Dialog On/Off Check
	m_bDialogOn     = pBool->IsDialogOn();
	m_bAutoAcceptOn	= pBool->IsAutoAcceptOn();
	m_bSingleSegOn	= pBool->IsSingleSegOn();
	m_bBLineOn		= pBool->IsBLineOn();
	/////////////////////////////////////////////////////////////////////////////
	m_nActiveObject = pWnd->GetActiveObjectType(); 
	m_nActiveTool	= pWnd->GetActiveToolType();    // -1= INSERT
	/////////////////////////////////////////////////////////////////////////
	pObjectMgr->SetActiveObjectType(m_nActiveObject);       // Set ObjectType 
	////////////////////
//	CMCurMgr* pMCurMgr;
	//////////////////////////////////////////
	switch(m_nActiveTool) 
	{
		////////////////////////////////////////////////// Curve	
		case C_CIRCLE:
						
			
			if(m_MI_Cur_I.RBDown_CInsert(CP_CIRCLE,m_pView,m_nView) <0)
				return; 
			//////////////////////////// 	
			return;
		
		case C_ELLIPSE:
						
			if(m_MI_Cur_I.RBDown_CInsert(CP_ELLIPSE,m_pView,m_nView) <0)
				return; 
			//////////////////////////// 	
			return;
		
		case C_PARABOLA:
						
			if(m_MI_Cur_I.RBDown_CInsert(CP_PARABOLA,m_pView,m_nView) <0)
				return; 
			//////////////////////////// 	
			return;
		
		case C_LINEAR:
						
			if(m_MI_Cur_I.RBDown_CInsert(CP_LINEAR,m_pView,m_nView) <0)
				return; 
			//////////////////////////// 	
			return;
		
		case C_QUADRATIC:
						
			if(m_MI_Cur_I.RBDown_CInsert(CP_QUADRATIC,m_pView,m_nView) <0)
				return; 
			//////////////////////////// 	
			return;
		
		case C_BEZIER:
						
			if(m_MI_Cur_I.RBDown_CInsert(CP_BEZIER,m_pView,m_nView) <0)
				return; 
			//////////////////////////// 	
			return;
		
		case C_BSPLINE:
						
			if(m_MI_Cur_I.RBDown_CInsert(CP_BSPLINE,m_pView,m_nView) <0)
				return; 
			//////////////////////////// 	
			return;
		
		case C_NURB:
						
			if(m_MI_Cur_I.RBDown_CInsert(CP_NURB,m_pView,m_nView) <0)
				return; 
			//////////////////////////// 	
			return;
		////////////////////////////////////////////////// Patch
		default:
			break;
	}  
}

int CCurMouAX::RightUp_CURVE()
{
	///////////////////////////////////////////////////////// Enable BLine,if needed
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	//////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CAxObjMgr* pObjectMgr  = pDoc->GetAxObjMgr(); 
	CDListMgr*	pList;
	////////////////////////////////////////////////////////////////// 
	if(pWnd->GetCurrentIGenID() == C_CIRCLE)
	{
		/////////////////
		if(m_bClosed)
		{
			if(m_ElPerSeg<3)
			{
				AfxMessageBox("INVALID DATA:\nFor Closed Circle\nAtleast 3 Elements Should be Specified!");
				GetCrcInDlg()->GetDlgItem(IDC_ELEMS)->SetFocus();
				/////////////////
				GetCrcInDlg()->UpdateData(FALSE);
				/////////////////
				return -1;;
			}
		}
		else
		if(m_ElPerSeg<1)
		{
			AfxMessageBox("INVALID DATA:\nFor Open Circle\nAtleast 1 Element Should be Specified!");
			GetCrcInDlg()->GetDlgItem(IDC_ELEMS)->SetFocus();
			/////////////////
			GetCrcInDlg()->UpdateData(FALSE);
			/////////////////
			return -1;
		}
	}
	/////////////////
	CString* pID;
//	char buf[30];
	int nAnswer = IDOK;
	//////////////////////////////////////////////////// Acceptance Not Automatic
	pID			= &m_CurrentCurveID; 
	//////////////////////////////////////////////////// Check Adequate Node,or cancel
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	//////////////////////////////////////
	switch(m_CurrentCurveType)
	{
		case CP_CIRCLE:

			switch(m_CircType)
			{
				
				case CIRCLE_BY_ROT:
				case CIRCLE_BY_NO3:
				case CIRCLE_BY_2N_TI:
				case CIRCLE_BY_2N_CC:
				case CIRCLE_BY_2CN_TI_R:

					if(m_nNodeDone != 3)
					{
						////////////////////
						j = sprintf(buf,"ERROR:\n\t%d Nodes Input to generate the Circle\n",m_nNodeDone);
						j += sprintf(buf+j,"Exactly 3 Nodes and/or CNodes Combined Needed\n");
						j += sprintf(buf+j,"Do You want to Continue to Get More Node(s) ?");
						/////////////////////////	
						nAnswer = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
					}
					break;
				
				default:

					break;

			}
			break;
				
		default:

			if(m_nNodeDone<2)
			{
				////////////////////
				j = sprintf(buf,"ERROR:\n\t%d Nodes Input to generate the Curve\n",m_nNodeDone);
				j += sprintf(buf+j,"Minimum of 2 Nodes Needed\n");
				j += sprintf(buf+j,"Do You want to Continue to Get More Node(s) ?");
				/////////////////////////	
				nAnswer = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
			}
	}
	delete str;
	/////////////////////////
	if(nAnswer == IDNO)
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		sprintf(buf,"Do You Want to Delete\nCurrent Curve to Start Allover");
		/////////////////////////	
		nAnswer = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
		/////////////////////////
		if(nAnswer == IDYES)		//delete
		{
			///////////////////////////////////////// delete
			pList = pObjectMgr->GetObjectList(CURVE);
			int nActiveIndex = pList->GetObjectIndex(CURVE, *pID);
			//////////////////////////////////////////////////// Reset
			pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
			/////////////////////////////////////// Reset
			m_pCurrentCurve = NULL;
			m_nNodeDone		= 0;	// 
			m_bCurveDone	= TRUE;	//   
			m_ElSegList.RemoveAll();
			m_NodeList.RemoveAll();
			/////////////////// reset
			if(m_nActiveTool == C_CIRCLE)
			{
				if(m_pCrcInDlg->GetSafeHwnd())
						m_pCrcInDlg->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
			}
			else
			{
				if(m_pLQCInDlg->GetSafeHwnd())
					m_pLQCInDlg->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
			}
			/////////////////////////////////////
			pDoc->UpdateAllViews(NULL);
			///////////////////////////
		}
		delete str;
		///////////////////////
		pDoc->UpdateAllViews(NULL);
		pWnd->GetMenu()->EnableMenuItem(IDM_OPTION_BLINEON,MF_BYCOMMAND|MF_ENABLED);
		///////////////////////////
		return 0;

	}
	else
	if(nAnswer == IDYES)		//continue to get more info
		////////
		return 0;
	/////////////////////////////////////////////////////////////// Not AutoAccept
	if(!m_bAutoAcceptOn)
	{
		if(!(m_NodeList.IsEmpty()))
		{
			/////////////////////////////// total elems
			int nElems = 0;
			if(!(m_ElSegList.IsEmpty()))
			{
				for (POSITION posI = m_ElSegList.GetHeadPosition( );posI !=NULL;)
				{
					////
					nElems += m_ElSegList.GetNext(posI); 
				}
			}
			//////////////////////////////
			CString* str = new CString;
			char* buf = str->GetBuffer(BUFF_SIZE);
			int j;
			//////////////////////////////////////
			switch(m_CurrentCurveType)
			{
				case CP_CIRCLE:

					switch(m_CircType)
					{
				
						case CIRCLE_BY_ROT:

							j = sprintf(buf,"Circle %s contains:\n\t%d Node to Rotate\n\t%d Elements\n",
								*pID,m_NodeList.GetCount(),nElems);
							j += sprintf(buf+j,"\t%s and %s are Axis Nodes\n",m_FromID,m_ToID);
							if(m_dAng == 360.)
								j += sprintf(buf+j,"\tClosed Circle\n");
							else
								j += sprintf(buf+j,"\t%f is Angle of Rotation\n",m_dAng);
							break;
				
						case CIRCLE_BY_NO3:

							j = sprintf(buf,"Circle %s contains:\n\t%d Interpolation Nodes\n\t%d Elements\n",
								*pID,m_NodeList.GetCount(),nElems);
							if(m_bClosed)
								j += sprintf(buf+j,"\tClosed Circle\n");
							else
							{
								if(m_bArc)
									j += sprintf(buf+j,"\tArc upto 3rd Node\n");
								else
									j += sprintf(buf+j,"\t%f is Angle of Rotation\n",m_dAngSpec);
							}
							break;
				
				
						case CIRCLE_BY_2N_TI:

							j = sprintf(buf,"Circle %s contains:\n\t%d Nodes\n\t%d Elements\n",
								*pID,m_NodeList.GetCount(),nElems);
							j += sprintf(buf+j,"2 End Nodes & Tangent Intersection\n");
							j += sprintf(buf+j,"\t%s is Tangent Intersection Node\n",m_TIID);
						break;
				
				
						case CIRCLE_BY_2N_CC:

							j = sprintf(buf,"Circle %s contains:\n\t%d Nodes\n\t%d Elements\n",
								*pID,m_NodeList.GetCount(),nElems);
							j += sprintf(buf+j,"2 End Nodes & Center\n");
							j += sprintf(buf+j,"\t%s is Center Node\n",m_CCID);
							break;
				
				
						case CIRCLE_BY_2CN_TI_R:

							j = sprintf(buf,"Circle %s contains:\n\t%d Nodes\n\t%d Elements\n\tRadius = %f\n",
								*pID,m_NodeList.GetCount(),nElems,m_dRadius);
							j+= sprintf(buf+j,"2 Control Nodes on Tangents &\nTangent Intersection\n");
							j += sprintf(buf+j,"\t%s is CNode_CA\n",m_CAID);
							j += sprintf(buf+j,"\t%s is Tangent Intersection Node\n",m_TIID);
							j += sprintf(buf+j,"\t%s is CNode_CB\n",m_CBID);
							break;
	
							
						default:

							break;

					}
					break;

				default:

					//////
					j = sprintf(buf,"Curve %s contains:\n\t%d Interpolation Nodes\n\t%d Elements\n",
					*pID,m_NodeList.GetCount(),nElems);
			}
			/////////////////////////
			j += sprintf(buf+j,"Nodes:\n");
			//////////////////////////////
			for (POSITION posI = m_NodeList.GetHeadPosition( );posI !=NULL;)
			{
				////
				CDrNode* pNode = (CDrNode*)m_NodeList.GetNextObject(posI);
				j += sprintf(buf+j,"%s, ",pNode->GetObjectID());
			}
			sprintf( buf + j-2, ";");
			/////////////////////////	
			nAnswer = AfxMessageBox(*str,MB_OKCANCEL|MB_ICONQUESTION );
			/////////////////////////
			if(nAnswer == IDCANCEL)
			{
				if(m_nActiveTool == C_CIRCLE)
					sprintf(buf,"Do You Want to Delete\nCurrent Circle to Start Allover");
				else
					sprintf(buf,"Do You Want to Delete\nCurrent Curve to Start Allover");
				/////////////////////////	
				nAnswer = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
				/////////////////////////
				if(nAnswer == IDYES)		//delete
				{
					///////////////////////////////////////// delete
					pList = pObjectMgr->GetObjectList(CURVE);
					int nActiveIndex = pList->GetObjectIndex(CURVE, *pID);
					//////////////////////////////////////////////////// Reset
					pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
					////////////////////////// Reset 
					m_pCurrentCurve = NULL;
					m_nNodeDone		= 0;	// 
					m_bCurveDone	= TRUE;	//   
					m_ElSegList.RemoveAll();
					m_NodeList.RemoveAll();
					//////////////////////////////////////////////////////////// reset
					switch(m_CurrentCurveType)
					{
						case CP_CIRCLE:

							if(m_pCrcInDlg->GetSafeHwnd())
										m_pCrcInDlg->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
							break;


						default:

							//////
							if(m_pLQCInDlg->GetSafeHwnd())
								m_pLQCInDlg->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
					}
					///////////
					delete str;
					///////////////////////
					pDoc->UpdateAllViews(NULL);
					pWnd->GetMenu()->EnableMenuItem(IDM_OPTION_BLINEON,MF_BYCOMMAND|MF_ENABLED);
					///////////////////////////
					return 0;
				}
			}
			/////////////////////
			str->ReleaseBuffer();
			delete str;
		}
	}
	/////////////////////////////////////////////////////////////////////// Show NewCurve
	if(ShowCurve(pID,TRUE)<0)		// TRUE = Final
	{
//		AfxMessageBox("ERROR:\nCCurMouAX::RightUp_CURVE\nShowCurve Problem");
		return -1;
	}
	/////////////////////////////////////// Set CurveID
	if(*pID == m_CurrentCurveID)
	{		
		char buf[30];
		/////////////
		m_CurrentCurveIDOld	= m_CurrentCurveID;
		m_LastCurveNum++;		// internal
		sprintf(buf,"%d",m_LastCurveNum);
		m_CurrentCurveID	= "C";
		m_CurrentCurveID	+= buf;
	}
	//////////////////////////////////////////////////////
	CDrNode* pNHead;
	CDrNode* pNTail;
	pNHead = (CDrNode*)(m_NodeList.GetHead());// Ist INode
	pNTail = (CDrNode*)(m_NodeList.GetTail());// End INode
	/////////////////////////////////////////////////////////// BLine
	if(m_bBLineOn)			
	{
		m_nNodeDone		= 1;
		m_bCurveDone	= TRUE;	// 040297
//		m_bCurveDone	= FALSE;	// 040297
		//////////////////////////////////// Retain Only Tails Wrong! 11/20/96
//		int nESeg	= m_ElSegList.GetTail();
		m_ElSegList.RemoveAll();
		m_NodeList.RemoveAll();
//		m_ElSegList.AddTail(nESeg);
		///////////////////////////
		CDrNode* pN;
		////////////
		switch(m_CurrentCurveType)
		{
			case CP_CIRCLE:

				switch(m_CircType)
				{
				
					case CIRCLE_BY_ROT:

						if(m_bClosed)	
							pN	= pNHead;// Ist INode
						else
//							pN	= (CDrNode*)(m_pCurrentCurve->GetCNodeList()->GetTail());// end CNode
							pN	= (CDrNode*)(m_pCurrentCurve->GetElemList()->GetHead());// end Handle CNode

						break;
				
					case CIRCLE_BY_NO3:

						if(m_bClosed)	
							pN	= pNHead;// Ist INode
						else
						{
							if(m_bArc)
								pN	= pNTail;// end INode
							else
//								pN	= (CDrNode*)(m_pCurrentCurve->GetCNodeList()->GetTail());// end CNode
								pN	= (CDrNode*)(m_pCurrentCurve->GetElemList()->GetHead());// end Handle Node
						}
						break;
				
					case CIRCLE_BY_2N_TI:
					case CIRCLE_BY_2N_CC:

							pN	= pNTail;// end INode
						break;
				
					case CIRCLE_BY_2CN_TI_R:

							pN	= (CDrNode*)(m_pCurrentCurve->GetINodeList()->GetTail());// end INode
						break;
				
					default:

						break;

				}
				break;


			default:

				pN	= pNTail;
		}
		m_NodeList.AddTail(pN);
	}
	else
	{
		m_nNodeDone		= 0;
		m_bCurveDone	= TRUE;	//
		//////////////////////////////////// Retain None
		m_ElSegList.RemoveAll();
		m_NodeList.RemoveAll();
	}
	//////////////////////////////////////////////////////////// reset
	CString strLastNodeID;
	m_bAnchorCNode = FALSE;
	////////////////////////////////////
	switch(m_CurrentCurveType)
	{

		case CP_CIRCLE:

			///////////////////////////////////////
			if(m_pCrcInDlg->GetSafeHwnd())
				m_pCrcInDlg->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
			//////////////////
			switch(m_CircType)
			{
				
				case CIRCLE_BY_ROT:

					if(m_bClosed)	
						strLastNodeID = pNHead->GetObjectID();
					else
					{
						strLastNodeID = 
//							((CDrNode*)(m_pCurrentCurve->GetCNodeList()->GetTail()))->GetObjectID();// end CNode
							((CDrNode*)(m_pCurrentCurve->GetElemList()->GetHead()))->GetObjectID();// end Handle CNode
//						m_bAnchorCNode = TRUE;
					}
					break;

					
				case CIRCLE_BY_NO3:

					if(m_bClosed)	
						strLastNodeID = pNHead->GetObjectID();
					else
					{
						if(m_bArc)
							strLastNodeID = pNHead->GetObjectID();
						else
						{
							strLastNodeID = 
//								((CDrNode*)(m_pCurrentCurve->GetCNodeList()->GetTail()))->GetObjectID();// end CNode
								((CDrNode*)(m_pCurrentCurve->GetElemList()->GetHead()))->GetObjectID();// end Handle CNode
//							m_bAnchorCNode = TRUE;
						}
					}
					break;

					
				case CIRCLE_BY_2N_TI:

					strLastNodeID = pNTail->GetObjectID();
					break;
				
				case CIRCLE_BY_2N_CC:

					strLastNodeID = pNTail->GetObjectID();
					break;
				
				case CIRCLE_BY_2CN_TI_R:

					strLastNodeID = 
						((CDrNode*)(m_pCurrentCurve->GetINodeList()->GetTail()))->GetObjectID();// end CNode
					break;
			
				default:

					break;

			}
			break;


		default:

			strLastNodeID = pNTail->GetObjectID();
//			strLastNodeID = m_CurrentNodeID;
			//////
			if(m_pLQCInDlg->GetSafeHwnd())
					m_pLQCInDlg->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
	}
	///////////////////////
	m_CurrentNodeIDOld = strLastNodeID;
	SetAnchorNodeID(m_CurrentNodeIDOld);
	///////////////////
	pWnd->GetMenu()->EnableMenuItem(IDM_OPTION_BLINEON,MF_BYCOMMAND|MF_ENABLED);
	/////////////////////// Send Message For CurrStat
//	pWnd->SendMessage(ID_RESET_MODELESS);
	///////////////
	return 0;
}

void CCurMouAX::OnEBoxRButtonUp_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
	//////////////////////////////////////////////////////////////////
	CMI_CProf	MI_CProf;
//	CMI_CSPN	MI_CSPN;
	/////////////////////
	CString ID;
	CString* pID = &ID;
	CEDlgMgr* pEDlgMgr;
//	int nMeshType;
	////////////////////
	switch(m_nActiveTool) 
	{


		case FE1D:
										
					/////////////////////////////////////////
//					if (pEDlgMgr->DoModal_Pipe(0) == IDCANCEL)
					return;
					////////////////////////////////////////
			break;	
		///////////////////////////////////////////////////// CURVEs INSERT
		case C_LINEAR:
		case C_QUADRATIC:
		case C_CIRCLE:
		case C_ELLIPSE:
		case C_PARABOLA:
		case C_BEZIER:
		case C_BSPLINE:
		case C_NURB:
/*
			if(m_bDialogOn)
			{
				CDlg_CDlg	dlg;
				dlg.DoModal();
			}
			else
			{
*/
				////////////////////
				UpdateCDlg_TRUE();
				RightUp_CURVE();
				UpdateCDlg_FALSE();
				///////////////////	
/*
			}
*/
			return;

		
		/////////////////////////////////////////////////// POST
/*
		case C_POST:				// PATCH 
			///////		
			m_MI_Pat_P.LBUpPatchPost();
			return;
		
*/		
		
		
		
		default:  
			break;
	} 

}

int CCurMouAX::PutEndIdsInPipeList(CString nid[],int nEnds)
{
/*
	///////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER);
	//////////////////////////////////////////////////////////// 
   	if(nid[0] == nid[1])       
   	{
		AfxMessageBox("Pipe has same Node IDs at both ends\n ZERO Length !!");
   		return -1;
	}			
    ////////////////////////////////////////
    CDListMgr* pDListMgr;
    /////////////////////////////////////////////////////////////////////////////// Add	
	int nActiveIndex;
    CDrFE1D* pAddPipe 	= (CDrFE1D*)(pObjectMgr->AddToDataBase(nActiveIndex,FE1D));
	//////////////////
	int index,nIdLen,nRepeat;
	CString EndNids;  
	////////////////	
	nIdLen  = nid[0].GetLength();
	nRepeat = COMBO_NIDJ_LOC - (nIdLen + 1);   // no. of Blank Spaces 
	CString blank(' ',nRepeat);
	EndNids = nid[0] + blank + nid[1]; 
	/////////////////////////////////////////// already exists
   	if(( index = pObjectMgr->GetObjectIndexfromKey(FE1D,EndNids,1))>=0)       
   	{
		AfxMessageBox("Pipe with these NodeIDs Already Exists !!");
   		return -1;
	}			
	else                                         // new Pipe
	{		
		/////////////////////////////////////////////////
		pAddPipe->SetObjectType((int)FE1D);
		pAddPipe->SetLevelType((int)LEVEL_GRAPA);
		pAddPipe->SetElemType((int)ELEM_OBJECT);              // globals.h
	    ///////////////////////////////// Set Info & Create
		(pAddPipe->GetPipeCard())->nid_i= nid[0];
		(pAddPipe->GetPipeCard())->nid_j= nid[1];
		/////////////////////////////////
//    	pAddPipe->SetObjectType((int)FE1D);          		//  
//    	pAddPipe->SetElemType((int)ELEM_OBJECT);          //  
		///////////////////////////////// store node pointers
//        CDrFE1D* pPipe;
//   		if(( index = GetObjectIndexfromKey(FE1D,EndNids,1))>=0)       
//			pPipe = (CDrFE1D*)pDListMgr->GetObject(index);
		//////////////////////////////////////////////////////////// Pen & Layer
		pAddPipe->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),
												pDrPen->GetStyle());
		pAddPipe->SetLayer(pLayer->GetCurrentLayer());
		///////////////////////////////////////////////////// store node pointers 
		pDListMgr = pObjectMgr->GetObjectList(NODE);
   		for(int i=0;i<nEnds;i++)
    	{
			if(( index = pObjectMgr->GetObjectIndexfromKey(NODE,nid[i],1))>=0)
			{
				CDrNode* pDrNode = (CDrNode*)pDListMgr->GetObject(index);
  				pAddPipe->GetNodeList()->AddTail(pDrNode);
				//////////////////////////////// save Current Pipe Pointer in Nodes
				pDrNode->GetElemList()->InsertObject(pAddPipe);
			}			
	
  		}	
		////////////////////////////////////////////////////////////////////////////////													    
		pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
		pObjectMgr->SetActiveObjectType(FE1D);		    // set Active Index									
        ////////////////////////////////////////////////////////// Invalidate
		pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,FE1D);
		//////////////////////////////////////////////////////////
		
	}	
*/
	AfxMessageBox("ERROR:\nCCurMouAX::PutEndIdsInPipeList\nSHOULD NOT BE USED");
	return -1; 
}
    
/////////////////////////////////////////////////////////////////////////////////////// F_M
UINT CCurMouAX::ReSetToolID_CUR(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	//////////////////////////////////////////// TaskID
	strCur = "Ready for Creation@";
	/////////////////////////////
	switch(OperID)
	{
		//////////////////////////////////////////// Create
		case COP_CREATE:
		{
			pWnd->SetIGenBoxStatus(TRUE);
			pWnd->SetCntlBoxStatus(FALSE);
			pWnd->SetDrawBoxStatus(FALSE);
			///////////////////////////// String
			str = "CREATE";
			pWnd->SetstrOperID(str);
			/////////////////////////////
			switch(CntlID)
			{
				//////////////////////////////////////// Elements
				case ELEMENT:
				case EDIM_0:
				case EDIM_1:
				case EDIM_2:
				case EDIM_3:

//					pWnd->SetMouseBoxType(ELEMDIMBOX);
					str = "ELEMENT";
					pWnd->SetstrCntlID(str);
					///////////////////////////////////// EDim0/EDim1...
					switch(IGenID)
					{
						/////////
						case CURVE:			str	= "CURVE";			ID = CURVE;	m_bDoModalDone	= FALSE;
								strCur += "Select a Curve Type";	break;
						case C_CIRCLE:		str = "CIRCULAR@CURVE";	ID = C_CIRCLE;
								strCur += "Select a Circle Type";	break;
						case C_ELLIPSE:		str = "ELLIPTIC@CURVE";	ID = C_ELLIPSE;
								strCur += "An Ellipse";	break;
						case C_PARABOLA:	str = "PARABOLIC@CURVE";ID = C_PARABOLA;
								strCur += "A Parabola";	break;
						case C_LINEAR:		str = "LINEAR@CURVE";	ID = C_LINEAR;
								strCur += "A Linear Curve";	break;
						case C_QUADRATIC:	str = "QUADRATIC@CURVE";ID = C_QUADRATIC;
								strCur += "A Quadratic Curve";	break;
						case C_CUBIC:		str = "CUBIC@CURVE";	ID = C_CUBIC;
								strCur += "A Cubic Curve";	break;
						case C_HERMITE:		str = "HERMITE@CURVE";	ID = C_HERMITE;	
								strCur += "A Hermite Curve";	break;
						case C_BEZIER:		str = "BEZIER@CURVE";	ID = C_BEZIER;
								strCur += "A Bezier Curve";	break;
						case C_BSPLINE:		str = "BSPLINE@CURVE";	ID = C_BSPLINE;
								strCur += "A BSpline Curve";	break;
						case C_NURB:		str = "NURB@CURVE";		ID = C_NURB;
								strCur += "A NURB Curve";	break;
						default:			str = "UNKNOWN@CURVE";	ID = UNONE;
							break;
					}
					pWnd->SetstrIGenID(str);
					////////////////////////
					pWnd->SetstrCurrID(strCur);
					//////////
					return ID;
				/////////
				default:					str = "UNKNOWN";	ID = UNONE;
					pWnd->SetstrIGenID(str);
					return ID;
			}
			pWnd->SetstrCntlID(str);
			return ID;
		////////
		default:							str = "UNKNOWN";	ID = UNONE;
		}
		pWnd->SetstrOperID(str);
		return ID;
	}
}
	
void CCurMouAX::ModeLessOff_CUR()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	if(GetLQCInDlg()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_LQCIN,IDOK);
	if(GetCrcInDlg()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_CRCIN,IDOK);
}

void CCurMouAX::ModeLessOn_CUR()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	int aTool	= pWnd->GetActiveToolType();
	int aObj	= pWnd->GetActiveObjectType();
	//////////////////////
	m_bDoModalDone = FALSE;
	/////////////////////////////////////////////////////////////////////////
	if
	(
		(aTool == C_LINEAR)		||	(aTool == C_QUADRATIC)	||
		(aTool == C_PARABOLA)	||	(aTool == C_BSPLINE)		||		     
		(aTool == C_NURB)		||	(aTool == C_BEZIER)				     
	)
	{
		if(!(GetLQCInDlg()->m_hWnd))
			pWnd->SendMessage(ID_ACTIVE_LQCIN,IDOK);
		if(GetCrcInDlg()->m_hWnd)
			pWnd->SendMessage(ID_GOODBYE_CRCIN,IDOK);
	}
	else
	if
	(	(aTool == C_CIRCLE)		||	(aTool == C_ELLIPSE)		)
	{
		CMCurMgr* pMCurMgr;
		/////////////////////////////////////////////////////////////// Using MCurMgr
		if(!m_bDoModalDone)
		{		
			if(pMCurMgr->DoModal_CIRCLE_Type(m_CircType) == IDCANCEL)
			{
				///////////////////////////////////// Reset TaskID
				pWnd->SetCurrentIGenID(CURVE);
				pWnd->SendMessage(ID_RESET_MODELESS,0);
				return;
			}
			m_bDoModalDone = TRUE;
		}
		///////////////////////////////////////
		if(GetLQCInDlg()->m_hWnd)
			pWnd->SendMessage(ID_GOODBYE_LQCIN,IDOK);
//		if(!(GetCrcInDlg()->m_hWnd))
			pWnd->SendMessage(ID_ACTIVE_CRCIN,IDOK);	// send Always, because of different Options
	}
}

long CCurMouAX::CreateorActivateLQCIn(UINT wParam, long lParam)
{
	
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	m_bBLineOn				= pBool->IsBLineOn();
	CString strCurr;
	/////////////////////////////////////////////////////////
	if(GetLQCInDlg()->GetSafeHwnd() ==0)	// not created already
	{
		GetLQCInDlg()->Create();
		CRect BoxRect;
		CWnd  wndTopMost;
		GetLQCInDlg()->GetWindowRect(&BoxRect);
		SizeRectDlgIn(BoxRect);
		//////////////////////////////////////////////////////////////
		GetLQCInDlg()->SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
                        BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
		//////////////////////////////////////////////////////////////
/*
		m_nNodeDone = 0;
		////////////////
		if(!m_ElSegList.IsEmpty())
			m_ElSegList.RemoveAll();
		if(!m_NodeList.IsEmpty())
			m_NodeList.RemoveAll();
*/
	}
	else
	{
		GetLQCInDlg()->SetActiveWindow();
		/////////////////////////////////
	}
	////
	if(!m_bBLineOn && m_bCurveDone)			// Reset
	{
		///////////////////////////
		char buf[50];
		int nLastNum = pObjectMgr->GetLastInputNo(NODE);		// internal
		sprintf(buf,"%d",nLastNum);
		m_CurrentNodeID = "";
		m_CurrentNodeID	+= buf;
		pObjectMgr->BumpLastInputNo(NODE);		// bump it
		m_CurrentNodeIDOld	= m_CurrentNodeID;
		m_bAnchorCNode		= FALSE;
		m_AnchorNodeID		= m_CurrentNodeID;
		/////
	}
	////////////////////////////////
	switch(pWnd->GetCurrentIGenID())
	{
		case C_ELLIPSE:		strCurr = "Creating An Ellipse";		break;
		case C_PARABOLA:	strCurr = "Creating A Parabola";		break;
		case C_LINEAR:		strCurr = "Creating A Linear Curve";	break;
		case C_QUADRATIC:	strCurr = "Creating A Quadratic Curve";	break;
		case C_CUBIC:		strCurr = "Creating A Cubic Curve";		break;
		case C_HERMITE:		strCurr = "Creating A Hermite Curve";	break;
		case C_BEZIER:		strCurr = "Creating A Bezier Curve";	break;
		case C_BSPLINE:		strCurr = "Creating A BSpline Curve";	break;
		case C_NURB:		strCurr = "Creating A NURB Curve";		break;
	}
	/////////////////
	if(m_nNodeDone>0)
		strCurr = "Last Node Selected as the Ist@Select the 2nd Node on the Curve";
	else
		strCurr += "@Select the Ist Node on the Curve";
	///////////////////////////////////////////////////////////////// if LQCDlg Open
	if(GetLQCInDlg()->m_hWnd)
	{
		CStatic* pCtl;
		pCtl = (CStatic*)(GetLQCInDlg()->GetDlgItem(IDC_OTHER));
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
			pWnd->SendMessage(ID_GOODBYE_LQCIN,IDOK);
			return 0L;
		}
	}
	////////////////////////////////////////////////////////////////// Set Info
	GetLQCInDlg()->m_CID		= GetCurrentCurveID();
	GetLQCInDlg()->m_NID		= GetCurrentNodeID();
	GetLQCInDlg()->m_dCoord		= m_ThirdCoord;
	GetLQCInDlg()->m_nElperSeg	= GetCurrentElPerSeg();
	GetLQCInDlg()->m_dRatio		= GetCurrentRatio();
	GetLQCInDlg()->m_bClosed	= IsClosed();
	GetLQCInDlg()->m_bAdvanceOn	= IsAdvanceOn();
	////////////////////////////////////////////
	m_bClosed = FALSE;
	m_pLQCInDlg->GetDlgItem(IDC_CLOSED)->EnableWindow(FALSE);
	if(m_CurrentCurveType == CP_LINEAR)
		m_pLQCInDlg->GetDlgItem(IDC_ADVANCED)->EnableWindow(FALSE);
	////////////////////////////////
	GetLQCInDlg()->UpdateData(FALSE);
	/////////////////////////////////
	if(!m_bBLineOn)
	{
		m_nNodeDone = 0;
		////////////////
		if(!m_ElSegList.IsEmpty())
			m_ElSegList.RemoveAll();
		if(!m_NodeList.IsEmpty())
			m_NodeList.RemoveAll();
	}
	////////////////////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->SetText(strCurr);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
	////////////////////////////////
	return 0L;
}
	 
long CCurMouAX::CancelLQCIn(UINT wParam, long lParam)
{
	
	GetLQCInDlg()->DestroyWindow();
	//////////
	return 0L;
}

long CCurMouAX::GoodByeLQCIn(UINT wParam, long lParam)
{
	
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
//	CString strCurr;
	/////////////////////////////////////////////////////////
	if(GetLQCInDlg()->m_hWnd)
		GetLQCInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CCurMouAX::UpdateLQCIn(UINT wParam, long lParam)
{

	GetLQCInDlg()->UpdateData(TRUE);
	///////////////////////////////// Reset data in ElMouse
	SetCurrentCurveID(GetLQCInDlg()->m_CID);
	SetCurrentNodeID(GetLQCInDlg()->m_NID);
	SetCurrentThirdCoord(GetLQCInDlg()->m_dCoord);
	SetCurrentElPerSeg(GetLQCInDlg()->m_nElperSeg);
	SetCurrentRatio(GetLQCInDlg()->m_dRatio);
	SetClosed(GetLQCInDlg()->m_bClosed);
	////////////////////////////////////////////
	if((m_CurrentCurveType == CP_LINEAR) && m_bClosed)
	{
		m_pLQCInDlg->GetDlgItem(IDC_ADVANCED)->EnableWindow(FALSE);
		GetLQCInDlg()->m_bAdvanceOn = FALSE;
		SetAdvanceOn(FALSE);
	}
	else
	{
		m_pLQCInDlg->GetDlgItem(IDC_ADVANCED)->EnableWindow(TRUE);
		SetAdvanceOn(GetLQCInDlg()->m_bAdvanceOn);
	}
	////////////////////////////////
	GetLQCInDlg()->UpdateData(FALSE);
	//////////
	return 0L;
}

long CCurMouAX::CreateorActivateCrcIn(UINT wParam, long lParam)
{
	
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	m_bBLineOn				= pBool->IsBLineOn();
	CString strCurr;
	/////////////////////////////////////////////////////////
	if(GetCrcInDlg()->GetSafeHwnd() ==0)	// not created already
	{
		GetCrcInDlg()->m_CircType = m_CircType;
		///////////////////////////////////////
		GetCrcInDlg()->Create();
		CRect BoxRect;
		CWnd  wndTopMost;
		GetCrcInDlg()->GetWindowRect(&BoxRect);
		SizeRectDlgIn(BoxRect);
		//////////////////////////////////////////////////////////////
		GetCrcInDlg()->SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
                        BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
		//////////////////////////////////////////////////////////////  
		switch(m_CircType)
		{
			case CIRCLE_BY_NO3:
			case CIRCLE_BY_ROT:
			case CIRCLE_BY_2N_TI:
			case CIRCLE_BY_2N_CC:
				//////////////////////////////
				strCurr = "Creating Circle@Select a Node for End_I";
				////
				break;
			case CIRCLE_BY_2CN_TI_R:
				//////////////////////////////
				strCurr = "Creating Circle@Select CNode_CA on Ist Tangent";
				////
				break;
			default:
				break;
		}
	}
	else
	{
		GetCrcInDlg()->SetActiveWindow();
		GetCrcInDlg()->m_CircType = m_CircType;
		GetCrcInDlg()->SendMessage(WM_INITDIALOG);
		///////////////////////// CurrStat: Show
		if(!m_bBLineOn)
		{
			m_nNodeDone = 0;
			////////////////
			if(!m_ElSegList.IsEmpty())
				m_ElSegList.RemoveAll();
			if(!m_NodeList.IsEmpty())
				m_NodeList.RemoveAll();
			///////////////////////////
		}
		//////
		switch(m_CircType)
		{
			case CIRCLE_BY_NO3:
				//////////////////////////////
				if(m_bBLineOn)
					strCurr = "Creating Circle@Select the 2nd Node";
				else
					strCurr = "Creating Circle@Select a Node at End_I";
				////
				break;
			case CIRCLE_BY_ROT:
				//////////////////////////////
				if(m_bBLineOn)
					strCurr = "Last Node Selected as@the Node at End_I";
				else
					strCurr = "Creating Circle@Select a Node for End_I";
				////
				break;
			case CIRCLE_BY_2N_TI:
				//////////////////////////////
				if(m_bBLineOn)
					strCurr = "Last Node Selected as Node_I@Select Tangent Intersection Node";
				else
					strCurr = "Creating Circle@Select a Node for End_I";
				////
				break;
			case CIRCLE_BY_2N_CC:
				//////////////////////////////
				if(m_bBLineOn)
					strCurr = "Last Node Selected as Node_I@Select Center";
				else
					strCurr = "Creating Circle@Select a Node for End_I";
				////
				break;
			case CIRCLE_BY_2CN_TI_R:
				//////////////////////////////
				if(m_bBLineOn)
					strCurr = "Last Node Selected as Node_CA@Select Tangent Intersection Node";
				else
					strCurr = "Creating Circle@Select a Node for End_I";
				////
				break;
			default:
				break;
		}
	}
	////////////////////////////// CurrStat
	if(m_nNodeDone<2)
	{
		m_pCrcInDlg->GetDlgItem(IDC_AXIS)->SetWindowText("");
		m_pCrcInDlg->GetDlgItem(IDC_AXIS_X)->SetWindowText("");
		m_pCrcInDlg->GetDlgItem(IDC_AXIS_Y)->SetWindowText("");
		m_pCrcInDlg->GetDlgItem(IDC_AXIS_Z)->SetWindowText("");
		m_pCrcInDlg->GetDlgItem(IDC_NEGATIVE)->SetWindowText("");
		m_pCrcInDlg->GetDlgItem(IDC_AXIS)->EnableWindow(FALSE);
		m_pCrcInDlg->GetDlgItem(IDC_AXIS_X)->EnableWindow(FALSE);
		m_pCrcInDlg->GetDlgItem(IDC_AXIS_Y)->EnableWindow(FALSE);
		m_pCrcInDlg->GetDlgItem(IDC_AXIS_Z)->EnableWindow(FALSE);
		m_pCrcInDlg->GetDlgItem(IDC_NEGATIVE)->EnableWindow(FALSE);
		//////////////////////////
	}
	////
	if(!m_bBLineOn && m_bCurveDone)			// Reset
	{
		///////////////////////////
		char buf[50];
		int nLastNum = pObjectMgr->GetLastInputNo(NODE);		// internal
		sprintf(buf,"%d",nLastNum);
		m_CurrentNodeID = "";
		m_CurrentNodeID	+= buf;
		pObjectMgr->BumpLastInputNo(NODE);		// bump it
		m_CurrentNodeIDOld	= m_CurrentNodeID;
		m_bAnchorCNode		= FALSE;
		m_AnchorNodeID		= m_CurrentNodeID;
		/////
	}
	///////////////////////////////////////////////////////////////// if CrcDlg Open
	if(GetCrcInDlg()->m_hWnd)
	{
		CStatic* pCtl;
		pCtl = (CStatic*)(GetCrcInDlg()->GetDlgItem(IDC_OTHER));
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
			pWnd->SendMessage(ID_GOODBYE_CRCIN,IDOK);
			return 0L;
		}
	}
	////////////////////////////////////////////////////////////////// Set Info
	GetCrcInDlg()->m_CurveID	= m_CurrentCurveID;
	GetCrcInDlg()->m_NID		= m_CurrentNodeID;
	GetCrcInDlg()->m_dCoord		= m_ThirdCoord;
	GetCrcInDlg()->m_nMesh		= m_ElPerSeg;
	GetCrcInDlg()->m_Ratio		= m_Ratio;
	GetCrcInDlg()->m_SegAngle	= m_SegAngle;
	GetCrcInDlg()->m_bAutoSeg	= m_bAutoSeg;
	//////
	switch(m_CircType)
	{
		case CIRCLE_BY_NO3:
			GetCrcInDlg()->m_bClosed	= m_bClosed;
			GetCrcInDlg()->m_dAngSpec	= m_dAngSpec;
			GetCrcInDlg()->m_bArc		= m_bArc;
			////
			break;
		case CIRCLE_BY_ROT:
			GetCrcInDlg()->m_dAngSpec	= m_dAng;
			GetCrcInDlg()->m_bAxis		= m_bAxis;		
			GetCrcInDlg()->m_nAxis		= m_nAxis;
			GetCrcInDlg()->m_bNegative	= m_bNegative;
			////
			break;
		case CIRCLE_BY_2N_TI:
			////
			break;
		case CIRCLE_BY_2N_CC:
//			if(m_nNodeDone == 2)
//				GetCrcInDlg()->m_NID		= m_CCID;
			////
			break;
		case CIRCLE_BY_2CN_TI_R:
//			GetCrcInDlg()->m_NID		= m_CAID;
			GetCrcInDlg()->m_dAngSpec	= m_dRadius;
//			if(m_nNodeDone == 1)
//				GetCrcInDlg()->m_NID		= m_TIID;
//			if(m_nNodeDone == 2)
//				GetCrcInDlg()->m_NID		= m_CBID;
			////
			break;
		default:
			break;
	}
	////////////////////////////////
	GetCrcInDlg()->UpdateData(FALSE);
	///////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->GetCurrStat()->SetText(strCurr);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
	////////////////////////////////
	return 0L;
}
	 
long CCurMouAX::CancelCrcIn(UINT wParam, long lParam)
{
	
	GetCrcInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CCurMouAX::GoodByeCrcIn(UINT wParam, long lParam)
{
	
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	/////////////////////////////////////////////////////////
	GetCrcInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CCurMouAX::UpdateCrcIn(UINT wParam, long lParam)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
	/////////////////////////////////////////////// Circle_by_Rot with Axis
	WORLD LocPos_From,LocaPos_To;
	POSITION pos;
	CDrNode* pNode;
	CDrLabel* pLabel;
	CMI_GangN GangN;
	char buf[50];
	CString ToID;
	int nLastNum;		// internal
	/////////////////////////// Generate ToID Node
	int nNodeIndex = -12345; // Create Anyway
	int nLabelIndex= 0;
	///////////////////////////////////////////////////////////////
	GetCrcInDlg()->UpdateData(TRUE);
	///////////////////////////////// Reset data in ElMouse
	m_CurrentCurveID	= GetCrcInDlg()->m_CurveID;
	m_CurrentNodeID		= GetCrcInDlg()->m_NID;
	m_ElPerSeg			= GetCrcInDlg()->m_nMesh;
	m_Ratio				= GetCrcInDlg()->m_Ratio;
	m_SegAngle			= GetCrcInDlg()->m_SegAngle;
	m_bAutoSeg			= GetCrcInDlg()->m_bAutoSeg;
	SetCurrentThirdCoord(GetCrcInDlg()->m_dCoord);
	//////
	switch(m_CircType)
	{
		case CIRCLE_BY_NO3:

			m_bClosed		= GetCrcInDlg()->m_bClosed;
			m_dAngSpec		= GetCrcInDlg()->m_dAngSpec;
			m_bArc			= GetCrcInDlg()->m_bArc;
			//////////
			break;
		case CIRCLE_BY_ROT:
			m_dAng			= GetCrcInDlg()->m_dAngSpec;
			m_bAxis			= GetCrcInDlg()->m_bAxis;		
			m_nAxis			= GetCrcInDlg()->m_nAxis;
			m_bNegative		= GetCrcInDlg()->m_bNegative;
			/////////////////////////////////
			if(m_bAxis && (m_nNodeDone == 2)) 
				m_nNodeDone++;
			else
				break;
			///////////////////////////////// finish Circle here
			m_ElSegList.AddTail(m_ElPerSeg);
			///////////////////////////////// Create ToID anyway
			pos		= m_NodeList.FindIndex( 1 );
			pNode	= (CDrNode*)(m_NodeList.GetAt(pos));
			LocPos_From	= *(pNode->GetLocalPos());
			///
			LocaPos_To.x = LocPos_From.x;
			LocaPos_To.y = LocPos_From.y;
			LocaPos_To.z = LocPos_From.z;
			//
			switch(m_nAxis)
			{
				case 1:	m_bNegative?LocaPos_To.x += -1.0:LocaPos_To.x += 1.0;	break;
				case 2:	m_bNegative?LocaPos_To.y += -1.0:LocaPos_To.y += 1.0;	break;
				case 3:	m_bNegative?LocaPos_To.z += -1.0:LocaPos_To.z += 1.0;	break;
				default:
					{
						AfxMessageBox("Internal ERROR:\nCCurMouAX::UpdateCrcIn()\nm_nAxis !=1,2or3");
						return -1L;
					}
			}
			//
			pObjectMgr->BumpLastInputNo(CNODE);		// bump it
			nLastNum = pObjectMgr->GetLastInputNo(CNODE);		// internal
			sprintf(buf,"%d",nLastNum);
			ToID = "CN_";
			ToID	+= buf;
			////////////////////////////////
			pNode = GangN.CreateNode(ToID,pLabel,LocaPos_To,TRUE,TRUE,FALSE,
										nNodeIndex,nLabelIndex);// FALSE=Input/TRUE=InternallyGen
			pNode->SetCategory(CA_ELEMENT);
			pNode->SetShow(FALSE);	// only for Internal Use
			//////////////////////////////////////////////// save
			m_NodeList.AddTail(pNode);
			////////////////////////////////////////////////////////////////////// Show
			if(ShowCurve(&m_CurrentCurveID,FALSE)<0)		// FALSE = Not Final
			{
				AfxMessageBox("ERROR:\nCCurMouAX::UpdateCrcIn\nShowCurve Problem");
				return -1;
			}
			/////////////////////
			if(RightUp_CURVE()<0)
			{
				m_nNodeDone--;
				return -1L;
			}
			////////////////////
			UpdateCDlg_FALSE();
			/////////////////
//			PostLeft();
			///////////////////////////////////
			break;
			//////
		case CIRCLE_BY_2N_TI:
		case CIRCLE_BY_2N_CC:
			break;
		case CIRCLE_BY_2CN_TI_R:
			m_dRadius		= GetCrcInDlg()->m_dAngSpec;
			break;
		default:
			break;
	}
	//////////
	return 0L;
}

void CCurMouAX::Serialize(CArchive& ar)
{

	CNodMouAX::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CurMouAX:    Storing\n");	
		

	}
	else
	{
		TRACE(" CurMouAX:    Loading\n");	

	
	}        
	///////////////////////////////////// 
	SerializeNode(ar);      
	SerializePipe(ar);
	//////////////////
}

///////////////////////////////////////////////////////// element serializer
void CCurMouAX::SerializePipe(CArchive& ar)
{ 
	//////////////////////////////////////////////////// STORING				
	if (ar.IsStoring())
	{
		ar	<<	m_CurrentPipeID;
	}
	//////////////////////////////////////////////////// LOADING				
	else
	{
		ar	>>m_CurrentPipeID;
	}
					    				
}
///////////////////////////////////// end of Module //////////////////////		
/*	
	///////////////////////////////////////////////////////////TEMPORARY
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
    /////////////////////////////////////////////////////////////////////
	CEDlgMgr* pEDlgMgr;
	CString nID;
	pEDlgMgr->DoModal_Node(m_nView,&MouseWIC,&nID);
	pEDlgMgr->DoModal_Pipe();
	/////////////////////////
	CDDlgMgr* pDDlgMgr;
	pDDlgMgr->DoModal_Label_Insert();
	pDDlgMgr->DoModal_Label_Edit();
	/////////////////////////////////////////////////////////////////////
*/


