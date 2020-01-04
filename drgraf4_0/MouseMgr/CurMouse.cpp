// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
#include "drgrafrm.h"
#include "UserMsg.h"
#include "drawView.h"
//#include "Def_Eror.h" // Mouse Action ERROR
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
/////////////////////
#include "Def_Objs.h"                    
#include "Def_Mous.h"                    
#include "Def_MouseAct.h" // Mouse Action                   
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
//#include "DrPipe.h"
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
#include "MC_Circle.h" 
#include "MC_Parab.h" 
//////////////////////
#include "CommRsrc.h"
#include "MCurRsrc.h"
 
#include "CurMouse.h" 

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
IMPLEMENT_SERIAL(CCurMouse,CNodMouse,1)
/////////////////////////////////////////////////////////////////////////////
CCurMouse::CCurMouse()
{
}

CCurMouse::~CCurMouse()
{
	/////////////////////////////////// Modeless Dialogs
	if(m_pLQCInDlg)
	{
		if(m_pLQCInDlg->m_hWnd)
			m_pLQCInDlg->DestroyWindow();
		delete m_pLQCInDlg;
	}	
	///////////////////
	if(m_pCrcInDlg)
	{
		if(m_pCrcInDlg->m_hWnd)
			m_pCrcInDlg->DestroyWindow();
		delete m_pCrcInDlg;
	}	
	///////////////////
}

void CCurMouse::InitDlgIn_CUR()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	/////////////////////////////////////////////////////////////////// System Sizes
	m_pLQCInDlg		= new CDlg_LQCI(pWnd); 
	m_pCrcInDlg		= new CDlg_CrcI(pWnd,m_CircType);
	/////////////////////////////////////////////////
	pObjectMgr->SetObjInfoID(m_CurrentCurveID,CURVE);
	/////////////////////
	ResetVariables_CUR();
}

int CCurMouse::Terminate_CUR(BOOL bError)
{
	if(!bError) // return for now
		return 0;
	/////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	pWnd->GetMouseMgr()->SetCurrentProcessDone(TRUE);
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr*	pList;
	int nActiveIndex;
	///////////////////
	pObjectMgr->SetActiveObjectType(CURVE);
	///////////////////////////////////////// delete
	pList = pObjectMgr->GetObjectList(CURVE);
	nActiveIndex = pList->GetObjectIndex(CURVE, m_CurrentCurveID);
	if(nActiveIndex>=0)
	{
		pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
		m_pCurrentCurve = (CDrCurve*)NULL;
	}
	/////////////////////////////////////// Reset
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
	/////////////////////
	ResetVariables_CUR();
	/////////////////////////////////////
	pDoc->UpdateAllViews(NULL);
	/////////
	return 0;
}

void CCurMouse::ResetVariables_CUR()
{
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	////////////////////////////
	if(!m_ElSegList.IsEmpty())
		m_ElSegList.RemoveAll();
	if(m_bBLineOn)	// save only the head
	{
		if(!m_NodeList.IsEmpty())
		{		
			CDrNode* pHead = (CDrNode*)m_NodeList.GetHead();
			m_NodeList.RemoveAll();
			m_NodeList.InsertObject(pHead);
			m_nNodeDone	= 1;
		}
		else
			m_nNodeDone		= 0;	// 
	}
	else
	{
		m_NodeList.RemoveAll();
		m_nNodeDone		= 0;	// 
	}
	m_bCurveDone		= TRUE;	//   
	////////////////////////////
//	m_pLQCInDlg			= NULL;                                                                                
//	m_pCrcInDlg			= NULL;
 	/////////////////////////////////////////// Curve 
    m_LastCurveNum		= 0;		// internal
//	m_CurrentCurveType	= CP_LINEAR;
//	m_CurrentCurveID	= "C0";
//	m_CurrentCurveIDOld	= "";
	m_nCirMaxNode		= 3;		// = 3
	m_ElPerSeg			= 1;
	m_Ratio				= 1.0;
	m_bClosed			= FALSE;
	m_bAdvanceOn		= FALSE;
	/////////////////////////////////////////// Circle
//	m_CircType			= CIRCLE_BY_NO3;
	m_SegAngle			= 120.;
	m_bAutoSeg			= TRUE;
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
	m_nTotElems			= 0;	// UserGiven tot for Last Segment
	m_nTotElPerSeg		= 0;	// Sum of Individual Seg Elems
	/////////////////////////////////////////// 
}
	
int CCurMouse::LeftDown_CURVE()
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
		LPOINT3 MouseWIC = GetMouseWIC();
		//////////////////
		CDrNode* pNode;
		if(m_bAnchorCNode)
			pNode = (CDrNode*)GetObjectFromID(NID, CNODE);
		else
			pNode = (CDrNode*)GetObjectFromID(NID, INODE);
		//////////////////////////////
		if(pNode)
			SetMouseWICFromNode(pNode,&MouseWIC);
		else
		{
			SetMouseOldWIC(GetMouseWIC());
			SetMouseWIC(MouseWIC);
		}
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
/*
		else
		{
			////////////////////////
			UpdateCDlg_FALSE();
			////////////////////////
		}
*/
	}	             
	return 0;
}
	
void CCurMouse::ElementLeftDown_CUR()
{	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
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

			if(m_bSingleSegOn == TRUE)
			{ 
				pBool->ToggleSingleSegOn();
				m_bSingleSegOn	= FALSE;
			}		
			m_CurrentCurveType = CP_ELLIPSE;
			LeftDown_CURVE();
			return;


		case C_HYPERBOLA:

			if(m_bSingleSegOn == TRUE)
			{ 
				pBool->ToggleSingleSegOn();
				m_bSingleSegOn	= FALSE;
			}		
			m_CurrentCurveType = CP_HYPERBOLA;
			LeftDown_CURVE();
			return;


		case C_PARABOLA:

			if(m_bSingleSegOn == TRUE)
			{ 
				pBool->ToggleSingleSegOn();
				m_bSingleSegOn	= FALSE;
			}		
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

			if(m_bSingleSegOn == TRUE)
			{ 
				pBool->ToggleSingleSegOn();
				m_bSingleSegOn	= FALSE;
			}		
			m_CurrentCurveType = CP_BEZIER;
			LeftDown_CURVE();
			return;


		case C_NURB:

			m_CurrentCurveType = CP_NURB;
			LeftDown_CURVE();
			return;
		//////////////////////////////////////////////////
		default:
			break;
	}  

}
	
int CCurMouse::ShowCurve(CString* pID,BOOL bFinal)
{

	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr*	pList;
	int nActiveIndex;
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
			j = sprintf(buf,"CCurMouse::ShowCurve()\n");
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
	CMC_Circle	MC_Circle;
	CMC_Parab	MC_Parabola;
	CDrNode*	pAddNode;
	CDrNode*	pFromNode;
	CDrNode*	pToNode;
	POSITION	pos;
	switch(m_CurrentCurveType)
	{
		case CP_CIRCLE:

			switch(m_CircType)
			{
				
				case CIRCLE_BY_ROT:

					//////////////////////////////////////////// FromID & ToID
					pos			= pINodeList->FindIndex( 1 );
					pFromNode	= (CDrNode*)(pINodeList->GetAt(pos));
					m_FromID	= pFromNode->GetObjectID();
					pINodeList->RemoveAt(pos);
					////////////
					pToNode	= (CDrNode*)(pINodeList->GetTail());
					m_ToID		= pToNode->GetObjectID();
					pINodeList->RemoveTail();
					//////////////////////////////////// if Axis Input
					MC_Circle.SetAxisInput(m_bAxis);
					MC_Circle.SetAxis(m_nAxis);
					MC_Circle.SetNegative(m_bNegative);
					///////////////////////////////////
					break;

				case CIRCLE_BY_NO3:
					break;

				case CIRCLE_BY_2N_TI:

					//////////////////////////////////////////// TIID
					pos			= pINodeList->FindIndex( 1 );
					pAddNode	= (CDrNode*)(pINodeList->GetAt(pos));
					m_TIID		= pAddNode->GetObjectID();
					//////
					break;

					
				case CIRCLE_BY_2N_CC:

					//////////////////////////////////////////// CCID
					pos			= pINodeList->FindIndex( 1 );
					pAddNode	= (CDrNode*)(pINodeList->GetAt(pos));
					m_CCID		= pAddNode->GetObjectID();
					//////
					break;

					
				case CIRCLE_BY_2CN_TI_R:

					//////////////////////////////////////////// TIID
					pos			= pINodeList->FindIndex( 1 );
					pAddNode	= (CDrNode*)(pINodeList->GetAt(pos));
					m_TIID		= pAddNode->GetObjectID();
					//////////////////////////////////////////// CAID
					pAddNode	= (CDrNode*)(pINodeList->GetHead());
					m_CAID		= pAddNode->GetObjectID();
					//////////////////////////////////////////// CBID
					pAddNode	= (CDrNode*)(pINodeList->GetTail());
					m_CBID		= pAddNode->GetObjectID();
					//////
					break;
				
				default:

					break;

			}
			////////////////////////////////////
			m_pCurrentCurve = MC_Circle.CreateCircle(
								*pID,m_pCurrentCurve,&m_NodeList,m_CurrentCurveType,
								&m_ElSegList,m_CircType,m_dAng,m_SegAngle,m_dRadius,
								m_bArc,pFromNode,pToNode,bFinal);
			/////////////////
			if(!m_pCurrentCurve)
			{
				pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
				return -1;
			}
			break;
				
		case CP_PARABOLA:
			m_pCurrentCurve = MC_Parabola.CreateParabola(*pID,m_pCurrentCurve,&m_NodeList,m_CurrentCurveType,
											&m_ElSegList,/*m_bAdvanceOn*/FALSE,bFinal);
			break;
			
		default:

			if(m_CurrentCurveType == CP_BEZIER)
			{
				GangC.SetNoDefault(TRUE);
				GangC.SetBezierType(BEZIER_BY_PTS);	// Bez. by Data Pts. Interpolation
			}
			///////////////
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
	////////////////////////////////////////////////////////////////////// Elem Segment Nodes
	if(bFinal)
	{
		//////////
		GangC.GenerateCurveVNodes(m_pCurrentCurve,m_CurrentNodeID);
		/////////////////////////////////////// Adjust Current NodeID
		m_CurrentNodeIDOld = m_CurrentNodeID;
	}
	////////////////////////////////////////////////////////////////////// Show
	m_pCurrentCurve->SetDirty(TRUE);
	m_pCurrentCurve->SetShow(TRUE);	
	///
	pObjectMgr->ShowObject_On_Off(m_pCurrentCurve,CURVE,TRUE);
	///////////////////////////////
	return 0;
}	 

int CCurMouse::CurTopo_Update(CDrCurve* pCurrentCurve,UINT CurrentCurveType,
											CDListMgr* pINodList/*m_NodeList*/)
{
#ifdef _DEBUG
			CString ObjID = pCurrentCurve->GetObjectID();
			CString strBum;
			if(ObjID == "C4")
				strBum = "C4 Specific";
#endif
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	//////////////////////////////////////////////////////////////////
	int nResult = 0;
	///////////////////////////////////////////////////////////////////////
	// NOTE:	Curves could be:
	//				1) regular type where Input Nodes are in INodeList, or,
	//				2) Circular Type where Input Nodes are in INodeList &
	//						ElemList(internally generated End Nodes)			
	/////////////////////////////////////////////////////////////////////// Get Ends
	CDListMgr HeadTail;
//	CDrNode* (*ppNHead);
//	CDrNode* (*ppNTail);
	////////////////////
	CurTopo_GetEndNodes(pCurrentCurve,CurrentCurveType,pINodList,&HeadTail);
	////////////////////
	CDrNode* pNHead = (CDrNode*)(HeadTail.GetHead());
	CDrNode* pNTail = (CDrNode*)(HeadTail.GetTail());
	///
	HeadTail.RemoveAll();
	///////////////////////////////////////////////// save in its NodTopoList
	CDListMgr* pList;
	///
	pList = pCurrentCurve->GetNodTopoList();
	pList->InsertObject(pNHead);
	pList->InsertObject(pNTail);
	/////////////////////////////////////////////////////////// Try Two Ends of Current Curve 
	int i,nCount,index;
	///////////
	pList	= pObjectMgr->GetObjectList(CURVE);
	nCount	= pList->GetCount();
	if(nCount <= 1)// for Ist curve Input, do nothing, ie i=1
		return nResult;
	////////////////////////
	for(i=0;i<nCount;i++)	
	{
		CDrCurve* pOtherCurve	= (CDrCurve*)(pList->GetObject(i));
#ifdef _DEBUG
			CString ObjID = pOtherCurve->GetObjectID();
#endif
		////////////////
		if(!pOtherCurve)
		{
			AfxMessageBox(
				"Internal ERROR:\nCCurMouse::CurTopo_EndNodeInOtherCurve\n!pOtherCurve");
			nResult = -1;
			return nResult;
		}
		///////////////////////////////// dont want this!
		if (pOtherCurve == pCurrentCurve)
			continue;
		///////////////////////////////// already taken care of
		CDListMgr* pLocalList = pCurrentCurve->GetCurveList();
		index = pLocalList->GetObjectIndex(pOtherCurve);
		if(index>=0)
			continue;
		///////////////////////////////////////////////////////// Try One End
		nResult = CurTopo_EndNodeInOtherCurves(pCurrentCurve,pOtherCurve,pNHead);
		////
		if(nResult == -1)	//ERROR
			return nResult;
		///////////////////////////
		if(nResult == 2/*already in*/ && nResult == 1/*DID FIND it*/ )
			continue;
		///////////////////////////////////////////////////////// Try other End
		nResult = CurTopo_EndNodeInOtherCurves(pCurrentCurve,pOtherCurve,pNTail);
		////
		if(nResult == -1)	//ERROR
			return nResult;
	}
	//////////////
	return nResult;
}

int CCurMouse::CurTopo_GetEndNodes(CDrCurve* pCurrentCurve,UINT CurrentCurveType,
								CDListMgr* pNodeList,CDListMgr* pHeadTail)
{
	int nResult = 0;
	///////////////////////////////////////////////////////////////////////
	// NOTE:	Curves could be:
	//				1) regular type where Input Nodes are in INodeList, or,
	//				2) Circular Type where Input Nodes are in INodeList &
	//						ElemList(internally generated End Nodes)			
	///////////////////////////////////////////////////////////////////////
	CDrNode* pNHead = (CDrNode*)(pNodeList->GetHead());// Ist INode
	CDrNode* pNTail = (CDrNode*)(pNodeList->GetTail());// End INode
	//////////////////////////////////////////////// Curves
	switch(CurrentCurveType)
	{
		case CP_CIRCLE:

			if(m_bClosed)	
				pNTail	= pNHead;// Ist INode
			else
				pNTail	= (CDrNode*)(pCurrentCurve->GetINodeList()->GetTail());// end Handle CNode
/*				
			switch(m_CircType)
			{
				case CIRCLE_BY_ROT:

					if(m_bClosed)	
						pNTail	= pNHead;// Ist INode
					else
//						pNTail	= (CDrNode*)(pCurrentCurve->GetENodeList()->GetHead());// end Handle CNode
						pNTail	= (CDrNode*)(pCurrentCurve->GetINodeList()->GetTail());// end Handle CNode

					break;
				
				case CIRCLE_BY_NO3:

					if(m_bClosed)	
						pNTail	= pNHead;// Ist INode
					else
					{
						if(m_bArc)
							;	//	pNTail	= pNTail;// end INode 
						else
							pNTail	= (CDrNode*)(pCurrentCurve->GetENodeList()->GetHead());// end Handle Node
					}
					break;
				
				case CIRCLE_BY_2N_TI:
				case CIRCLE_BY_2N_CC:

					//		pNTail	= pNTail;// end INode
					break;
				
				case CIRCLE_BY_2CN_TI_R:

					pNTail	= (CDrNode*)(pCurrentCurve->GetINodeList()->GetTail());// end INode
					break;
				
				default:

					break;
			}
			break;
*/


		default:

			;//	pNTail	= pNTail;
	}
	/////////////////////////////// save
	pHeadTail->InsertObject(pNHead);
	pHeadTail->InsertObject(pNTail);
	///////////
	return nResult;
}

int CCurMouse::CurTopo_EndNodeInOtherCurves(CDrCurve* pCurrentCurve,CDrCurve* pOtherCurve,
											CDrNode* pEndNode)
{
#ifdef _DEBUG
			CString		ObjID = pCurrentCurve->GetObjectID();
						ObjID = pOtherCurve->GetObjectID();
#endif
	int nResult = 0;	
	////////////////
//	int nResult = 0;	// DID NOT FIND it, may be try other end
//	int nResult = 1;	// DID FIND it
//	int nResult = 2;	// already taken care of before
//	int nResult = -1;	// internal ERROR
	///////////////////////////////////////////////////////////////////////
	// NOTE:	Curves could be:
	//				1) regular type where Input Nodes are in INodeList, or,
	//				2) Circular Type where Input Nodes are in INodeList &
	//						ElemList(internally generated End Nodes)			
	/////////////////////////////////////////////////////////////////////// Try given End
	CDListMgr*  pNodList;
	int index;
	///////////////////////////////// already taken care of
	CDListMgr* pLocalCurList = pCurrentCurve->GetCurveList();
	index = pLocalCurList->GetObjectIndex(pOtherCurve);
	if(index>=0)
	{
		nResult = 2;	// CONTINUE
		return nResult;
	}
	///////////////////////////////////////////////////////// Check End Nodes (NodTopoList)
	pNodList	= pOtherCurve->GetNodTopoList();
	index	= pNodList->GetObjectIndex(pEndNode);
	if(index>=0)	// EXIST in other curve
	{
		pLocalCurList->InsertObject(pOtherCurve);
		////////////////////////////////////// Reciprocate Curve, if necessary
		pLocalCurList = pOtherCurve->GetCurveList();
		index = pLocalCurList->GetObjectIndex(pCurrentCurve);
		if(index<0)		// not in the list yet
			pLocalCurList->InsertObject(pCurrentCurve);
		////////////////////////////////////// Reciprocate Curve, if necessary
		pLocalCurList = pCurrentCurve->GetCurveList();
		index = pLocalCurList->GetObjectIndex(pOtherCurve);
		if(index<0)		// not in the list yet
			pLocalCurList->InsertObject(pOtherCurve);
/*
		////////////////////////////////////// Reciprocate NodeTopo, if necessary
		CDrNode* pOtherNode;
		if(index == 0) // Head Match
			pOtherNode = (CDrNode*)(pNodList->GetTail()); // Tail
		else
			pOtherNode = (CDrNode*)(pNodList->GetHead()); // Head
		/////////
		NodTopo_Update(pEndNode,pOtherNode);
*/
		//////////////////////////////
		nResult = 1;	// DID FIND it
		return nResult;
	}
	else			// DO NOT EXIST in other curve
	{
		/////////// nothing else to do
		nResult = 0;	// DID NOT FIND it
		return nResult;
	}
	///////////////
	return nResult;
}

void CCurMouse::OnEBoxLButtonDown_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point)
{
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
	/////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
	{
		pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
		////////////////////////////////
		ResetVariables_CUR();
		/////////////////////
		m_bCurveDone		= FALSE;	  // 
	}
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	/////////////////////////////////// 
   	m_bDragOn 		= pBool->IsDragOn();
	m_bDialogOn		= pBool->IsDialogOn();
	m_bAutoAcceptOn	= pBool->IsAutoAcceptOn();
	m_bSingleSegOn	= pBool->IsSingleSegOn();
	m_bBLineOn		= pBool->IsBLineOn();
/*
	if(!m_bBLineOn && m_bCurveDone)			// Reset
	{
		m_nNodeDone = 0;
		////////////////
		if(!m_ElSegList.IsEmpty())
			m_ElSegList.RemoveAll();
		if(!m_NodeList.IsEmpty())
			m_NodeList.RemoveAll();
		///////////////////
	}
*/
	//////////////////////////////////////////////////////// LOG
	m_pdc->DPtoLP(&point);
	//////////////////////////////////////////////////
	m_nActiveObject = pWnd->GetActiveObjectType(); 
	m_nActiveTool	= pWnd->GetActiveToolType();    // -1= INSERT
	///////////////////////////////////////// make sure Dlg is Open
	if( !(GetLQCInDlg()->m_hWnd) && (m_nActiveTool != C_CIRCLE) )
		pWnd->SendMessage(ID_ACTIVE_LQCIN,IDOK);
	if( !(GetCrcInDlg()->m_hWnd) && (m_nActiveTool == C_CIRCLE) )
			pWnd->SendMessage(ID_ACTIVE_CRCIN,IDOK);	// send Always, because of different Options
	/////////////////////////////////////////////////////////////////////////
	pObjectMgr->SetActiveObjectType(m_nActiveObject);       // Set ObjectType 
	////////////////////////////////////////////////// take care of Edit AllClear
//	pDListMgr 	= pObjectMgr->GetObjectList(NODE);
//	if(!(pDListMgr->GetSpecificObjectCount(NODE)) ) m_nNodeDone = 0;
	/////////////////////////////////////////////////////////////////
	if(!m_bBLineOn && m_bCurveDone)
	{
		///////////////////////////////////////
	    LPOINT3 MouseWIC = GetMouseWIC();
	    SetMouseOldWIC(MouseWIC);
	    /////////////////////////
	    LPOINT Lpoint;
	    Lpoint.x = (long)point.x;
	    Lpoint.y = (long)point.y;
	    ////////////////////
	    LOGtoWIC(&MouseWIC,&Lpoint);                 
	    SetMouseWIC(MouseWIC);
	}
    /////////////////////////////  ELement Dialog On/Off Check
    if(m_Gener == FORWARD)
		ElementLeftDown_CUR();
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftDown_I();
	//////////////////////////////////
}

void CCurMouse::UpdateCDlg_TRUE()
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
		m_ElPerSeg			= m_pCrcInDlg->m_nElemPerSeg;
		m_nTotElems			= m_pCrcInDlg->m_nTotElems;
		m_Ratio				= m_pCrcInDlg->m_Ratio;
		m_SegAngle			= m_pCrcInDlg->m_SegAngle;
//		m_bAutoSeg			= m_pCrcInDlg->m_bAutoSeg;
		m_bClosed			= m_pCrcInDlg->m_bClosed;
		m_dAng				= m_pCrcInDlg->m_dAngSpec;
		m_bArc				= m_pCrcInDlg->m_bArc;
		/////////////////////////////////////////////////
		switch(m_CircType)
		{
			case CIRCLE_BY_NO3:
				break;
			case CIRCLE_BY_ROT:
				m_bAxis			= m_pCrcInDlg->m_bAxis;
				m_nAxis			= m_pCrcInDlg->m_nAxis;
				m_bNegative		= m_pCrcInDlg->m_bNegative;
				break;
			case CIRCLE_BY_2N_TI:
			case CIRCLE_BY_2N_CC:
				break;
			case CIRCLE_BY_2CN_TI_R:
				m_dRadius		= m_pCrcInDlg->m_dRadius;
			default:
				break;
		}
	}
}			

void CCurMouse::UpdateCDlg_FALSE()
{
	/////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString str;
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////
	if
		(
			m_CurrentCurveType == CP_ELLIPSE	||	m_CurrentCurveType == CP_PARABOLA	||
			m_CurrentCurveType == CP_HYPERBOLA	||
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
		//
		if(	m_CurrentCurveType == CP_PARABOLA	||	m_CurrentCurveType == CP_HYPERBOLA	||
			m_CurrentCurveType == CP_BEZIER)
		{
			m_bClosed = FALSE;
			m_pLQCInDlg->GetDlgItem(IDC_CLOSED)->EnableWindow(FALSE);
		}
		//////////////////////////////////////
		if(m_nNodeDone>=1)
		{
			if(m_nNodeDone==1 && !(pObjectMgr->GetObjectList(CURVE)->IsEmpty()) && m_bBLineOn)
				m_pLQCInDlg->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
			else
				m_pLQCInDlg->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
		}
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
		if
			(	m_CurrentCurveType == CP_ELLIPSE	||	m_CurrentCurveType == CP_PARABOLA	||
				m_CurrentCurveType == CP_HYPERBOLA	||	m_CurrentCurveType == CP_BEZIER	
			)
		{
			m_bAdvanceOn = FALSE;
			m_pLQCInDlg->GetDlgItem(IDC_ADVANCED)->EnableWindow(FALSE);
		}
		else
			m_pLQCInDlg->GetDlgItem(IDC_ADVANCED)->EnableWindow(TRUE);
		//
		m_pLQCInDlg->m_bClosed		= m_bClosed;
		m_pLQCInDlg->m_bAdvanceOn	= m_bAdvanceOn;
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
			case 2:
				if(	m_CurrentCurveType == CP_ELLIPSE	||	m_CurrentCurveType == CP_PARABOLA	||
					m_CurrentCurveType == CP_HYPERBOLA	
					)
				{
					str = "Continuing on Same Curve: Click in@Last Node on the Conic";
					break;
				}
				// otherwise,fall thro'
			case 3:
				if(	m_CurrentCurveType == CP_BEZIER	)
				{
					str = "Single Segment Bezier Curve@(Upto Cubic) Click in Last Node";
					break;
				}
				// otherwise,fall thro'
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
//		m_pCrcInDlg->m_NID			= "";	// 081198
		m_pCrcInDlg->m_NID			= m_CurrentNodeID;	
		m_pCrcInDlg->m_dCoord		= m_ThirdCoord;
		m_pCrcInDlg->m_nElemPerSeg	= m_ElPerSeg;
		m_pCrcInDlg->m_nTotElems	= m_nTotElems;
		m_pCrcInDlg->m_Ratio		= m_Ratio;
		m_pCrcInDlg->m_SegAngle		= m_SegAngle;
//		m_pCrcInDlg->m_bAutoSeg		= m_bAutoSeg;
		m_pCrcInDlg->m_bClosed		= m_bClosed;
		m_pCrcInDlg->m_dAngSpec		= m_dAng;
		m_pCrcInDlg->m_bArc			= m_bArc;
		////////////////////////////////////////
		switch(m_CircType)
		{
			case CIRCLE_BY_NO3:
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
						///
						m_pCrcInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("To Node");
						str = "Circle: Click in 2nd (C)Node defining@Axis or SELECT Axis of Revolution";
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
				m_dRadius		= m_pCrcInDlg->m_dRadius;
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
	pWnd->UpdateCurrStat(str);
}			
	
int CCurMouse::LeftUp_Cur_Node(CPoint point,BOOL bCNode,BOOL bDistinct,BOOL bNoOtherType)
{
	///////////////////////////////////////////////////////////////////////
	//	bDistinct		=		TRUE	-> Should Not be in m_NODELIST
	//							FALSE	-> DONT CARE
	//	bNoOtherType	=		TRUE	-> Should Not be other than Type dictated by bCNode
	//							FALSE	-> DONT CARE
	///////////////////////////////////////////////////////////////////////
	int nResult = 0;
	////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	///////////////////////////////////////////// See if any Existing Node Hit w/ same Coords
	m_bCorINodeOpDone = FALSE;
	BOOL bControl	  = FALSE;
	if(bCNode)
		bControl = TRUE;
	////////////////////
SEARCH:
	nResult = LeftUp_Node_Accept_OtherContext(point,bControl,pWnd->IsMeshMode(),
						m_bCorINodeOpDone,m_bAutoAcceptOn,&m_pCurrentNode);
	/////////////////////////////////////////////   
	//	MA_CREATENEW	// Create Anyway
	//	MA_ACCEPTOLD	// Accept Old	
	//	MA_ACCEPTNEW	// Accept New	
	//	MA_NOHIT		// No Hit	
	//	MA_CANCEL		// Cancel Process
	switch(nResult)
	{
		case MA_ACCEPTOLD:		// Accept Old One
			/////////////////// matches previous Node in m_NodeList,INADMISSIBLE
			nResult = OldNode_N_Update_CURContext(m_pCurrentNode->IsControlNode(),bDistinct); // right type
				return nResult;

		case MA_NOHIT:			// NoHit
			if(!bNoOtherType)
			{
				if(!m_bCorINodeOpDone)	// Not Final
				{
					m_bCorINodeOpDone = TRUE;	// try Final
					bControl = TRUE;
					if(bCNode)
						bControl = FALSE;	// other type
					goto SEARCH;
				}
			}
			else
				; // fall thro for NEW NODE

		case MA_CREATENEW:			// Hit or Not , Create NEW anyway (m_wLoc Set)
			nResult = NewNode_N_Update_OtherContext(point,bCNode); // desired Type
			return nResult;
			/////////
		case MA_CANCEL:		// Cancel
			return -2;
		default:		// Error
			return -1;
	}					
}

int CCurMouse::NewNode_N_Update_OtherContext(CPoint point,BOOL bCNode)
{
	int nResult;
	/////////////////////////////////////////////////////////// NEW Node
	nResult = NewNode_OtherContext(point,bCNode);	// desired Type
	if(nResult<0)
		return nResult;
	/////////////////////////////////////////////////////////// Update
	m_NodeList.InsertObject(m_pCurrentNode);
	nResult = UpdateforNewNode(bCNode);
	/////////////
	return MA_OK;
}

int CCurMouse::OldNode_N_Update_CURContext(BOOL bCNode,BOOL bDistinct)
{
	///
	if(bDistinct)
	{
		/////////////////// matches previous Node in m_NodeList,INADMISSIBLE
		if(m_nNodeDone>1)
		{
			////////////////////////////////////////////////// already exists
			if(m_NodeList.GetObjectIndex(m_pCurrentNode) >=0)
			{
				if(!m_bClosed || (m_bClosed && m_nNodeDone<3) )	// not closed or premature:Error
				{
					m_pCurrentNode = NULL;
					AfxMessageBox(
					"ERROR:\nSame Node More than Once!\nNeed at least 3 Nodes or\nClick Closed Option");
					return MA_CANCEL;
				}
				else	// accept but don't include in the List
				{
					UpdateforOldNode(bCNode);
					return MA_OK;
				}
			}
		}	
	}
	/////////////////////
	// not in the list or "distinct" not required
	m_NodeList.InsertObject(m_pCurrentNode);
	UpdateforOldNode(bCNode);
	/////////////
	return MA_OK;
}

int CCurMouse::LeftUp_Node_Accept_OtherContext(CPoint point,BOOL bCNode,BOOL bMeshMode,
						BOOL bCorINodeOpDone,BOOL bAutoAcceptOn,CDrNode** pCurrentNode)
{
	//	Return:
	//	MA_CREATENEW	// Create Anyway
	//	MA_ACCEPTOLD	// Accept Old	
	//	MA_ACCEPTNEW	// Accept New	
	//	MA_NOHIT		// No Hit	
	//	MA_CANCEL		// Cancel Process
	///////////////
	int nResult;
	/////////////////////////////////
	// multiple search fr same coord
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	WORtoWOP(&dTol,&dTol);	// physical
	///
	CDListMgr* pDListMgr = pObjectMgr->GetNodeList_OtherContext(bCNode,bMeshMode);
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrNode*	pDrNode;
	int			index;
	//////////////////////////////////////////////////// Check if CorrectType Node/CNode/MNode
	// first check projected on current View
	if(bCNode)
	{	
		if(bMeshMode)
			index = IsObjectHit(MCNODE,point,0);
		else
			index = IsObjectHit(CNODE,point,0);
	}
	else
	{
		if(bMeshMode)
			index = IsObjectHit(MNODE,point,0);
		else
			index = IsObjectHit(NODE,point,0);
	}
	/////////////////////////////////////////////////////////////// 
	if(index<0)						
		//////////////// NO HIT
		return MA_NOHIT;
	///////////////////////////////////////////////////////////////// Object HIT
	pDrNode	= (CDrNode*)pDListMgr->GetObject(index);
	ID		= pDrNode->GetObjectID();
	/////////////////////////////////////////////
	if(bCNode)
		pObjectMgr->ShowObject_On_Off(pDrNode,CNODE,TRUE);
	else
		pObjectMgr->ShowObject_On_Off(pDrNode,NODE,TRUE);
	//////////////////////////////////////////////////////////////// 
	//	if 
	//		Existing Node Hit Always Ask if 3D Problem 
	//		Existing Node Hit Only	 Ask if 2D Problem & m_bAutoAccept = Off 
	//
	////////////////////////////////////////////////////////////////
	if(m_bAutoAcceptOn && m_ProbLim == PDL_TWO)
	{
		///////////////// Accept Old
		*pCurrentNode = pDrNode;
		return MA_ACCEPTOLD;
	}
	//////////////////////////////////////////////////////////////// MultipleSearch
	int startIndex = index+1;
	/////////////////////////
	for(;;)
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		/////////////
		int j;
		//////////////////////////////
		if(bCNode)
			j = sprintf(buf,"***** A Control Node Hit ****\n");
		else
			j = sprintf(buf,"***** An Input Node Hit ****\n");
		j += sprintf(buf+j,"(with a Net Sieve of %f)\n",dTol);
		j = ShowNodeInfo(pDrNode, buf, j);
		////////////////////////////
		j += sprintf(buf+j,
			"\n\nYES:\t\tAccept This Existing (C)Node");
		j += sprintf(buf+j,
			"\nNO:\t\tContinue Searching (C)Node");
		j += sprintf(buf+j,
			"\nCANCEL:\t\tCreate A New (C)Node Anyway");
		////////////////////////////
		nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
		/////////////
		delete str;
		if(nResult == IDYES)	// Hit
		{
			///////////////// Accept Old
			*pCurrentNode = pDrNode;
			return MA_ACCEPTOLD;
		}
		else
		if(nResult == IDNO)		// Rejected and Try Again
		{
			//////////////////////////////////////////////////////// Retry
			if(bCNode)
				index = IsObjectHit(CNODE,point,startIndex);
			else
				index = IsObjectHit(NODE,point,startIndex);
			////////////////////////////////////////////////////////
			if(index>=0)
			{
				pDrNode	= (CDrNode*)pDListMgr->GetObject(index);
				ID		= pDrNode->GetObjectID();
				/////////////////////////////////////////////
				if(bCNode)
					pObjectMgr->ShowObject_On_Off(pDrNode,CNODE,TRUE);
				else
					pObjectMgr->ShowObject_On_Off(pDrNode,NODE,TRUE);
				////////////////////////////////////////
				startIndex  = index+1;
				/////////////////////
			}
			else
			{
				if(!bCorINodeOpDone)	// search Not Done yet
					//////////////// NO HIT
					return MA_NOHIT;
				///////////////////////////////////////////////////// End of Search
				CString* str = new CString;
				char* buf = str->GetBuffer(BUFF_SIZE);
				/////////////
				int j;
				//////////////////////////////
				j = sprintf(buf,"***** No More Node Found ****\n");
				j += sprintf(buf+j,"(with a Net Sieve of %f)\n",dTol);
				////////////////////////////
				j += sprintf(buf+j,
					"\n\nYES:\t\tCreate A New (C)Node Anyway");
				j += sprintf(buf+j,
					"\nNO:\t\tCancel Selection Process");
				////////////////////////////
				int nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
				/////////////
				delete str;
				if(nResult == IDYES)
				//////////////// Create New
					return MA_CREATENEW;
				else
				if(nResult == IDNO)
					//////////////// Cancel
					return MA_CANCEL;
			}
		}
		else				// 
			//////////////// Create New
			return MA_CREATENEW;
	}	// end for Loop			
	//////////////// Create New
	return MA_CREATENEW;
}
	
int CCurMouse::NewNode_OtherContext(CPoint point,BOOL bCNode)
{
	int nResult = 0;
	////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	///////////////////////////////////////////////////////////////////////
	int nAnyway	= -12345;	// Used as an afterthought for creating Node anyway
							// in GangN.CreateNode
							// even if same coords node exists already !!!
							// when nAnyway == -12345
							// Use nHowmany of ShowNode to pass the variable
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CMsObjMgr* pMsObjMgr	= pDoc->GetMsObjMgr();
	///
	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CDrNode*	pDrNode;
	int			index;
	//////////////////////////////////////////////////////////////////////////// NEW Node
	///////////////////////////////////////////////////// Blank NodeID? provide
	if(m_CurrentNodeID == "")
	{
		/////////////
		UINT uType;
		if(bCNode)
			uType = pWnd->IsMeshMode()?MCNODE:CNODE;
		else
			uType = pWnd->IsMeshMode()?MNODE:NODE;
		///
		pObjectMgr->SetNodeInfoID(m_CurrentNodeID,bCNode,uType);
		/////////
	}
	///////////////////////////////////////////////////// ERROR:Conflicting ID
	pList = pObjectMgr->GetNodeList_OtherContext(bCNode,pWnd->IsMeshMode());
	///
	if(pWnd->IsMeshMode())
		index	= pList->GetObjectIndex(FE0D, m_CurrentNodeID);
	else
		index	= pList->GetObjectIndex(NODE, m_CurrentNodeID);
	///
	if(index>=0)						// User selected CONFLICTING pID
	{
		pDrNode = (CDrNode*)(pList->GetObject(index));
		ShowNodeInfo_SameID(pDrNode);
		/////////
		return -1;
	}
	////////////////////////////////////////////////////// finally New Node
	if(!m_bAutoAcceptOn)
	{
		/////////////////////////////////////////////////
		CString*	str		= new CString;
		char*		buf		= str->GetBuffer(BUFF_SIZE);
		int j;
		///////////////////////////////// Using GangN
		LPOINT3 MouseWIC = GetMouseWIC();
		WICtoWOR(&MouseWIC,&m_wLoc);	
		//////////////////////////
		WORLD wPt;
		WORtoWOP(&m_wLoc,&wPt);	// to Physical
		//////////////////////////////
		j = sprintf(buf,
			"***** A New Node Creation: *****\nNodeID = %s\nCoordinates:\n\tX = %f\n\tY = %f\n\tZ = %f ",
			m_CurrentNodeID,wPt.x,wPt.y,wPt.z);
		j += sprintf(buf+j,"\n\nAccept This New Node?");
		////////////////////////////
		int nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
		/////////////
		if(nResult == IDNO)
			return -2;
		//////////////
		delete str;
	}
	//////////////////////////////////
	if(ShowNode(&m_CurrentNodeID,bCNode,nAnyway)<0)
	{
		AfxMessageBox("ERROR:\nCCurMouse::NewNode_OtherContext\nShowNode Problem");
		return -1;
	}
	////////////
	return 0;
}

int CCurMouse::UpdateforOldNode(BOOL bCNode)
{
	int nResult = MA_OK;
	////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////// Update
	m_CurrentNodeIDOld	= m_pCurrentNode->GetObjectID();
	m_AnchorNodeID		= m_CurrentNodeIDOld;
	m_bAnchorCNode		= bCNode;
	/////////////
	// DO NOT UPDATE m_CurrentNodeID 
	////////////
	return nResult;
	/////////
}

int CCurMouse::UpdateforNewNode(BOOL bCNode)
{
	int nResult = 0;
	////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////// Update
	m_CurrentNodeIDOld	= m_pCurrentNode->GetObjectID();
	m_AnchorNodeID		= m_CurrentNodeIDOld;
	m_bAnchorCNode		= bCNode;
	/////////////
	UINT uType;
	if(bCNode)
		uType = pWnd->IsMeshMode()?MCNODE:CNODE;
	else
		uType = pWnd->IsMeshMode()?MNODE:NODE;
	//////////////////////////////////////////////////////// tempo Correction for Illogic!!!
	if(m_CurrentNodeID == "1")
		pObjectMgr->BumpLastInputNo(uType);					// bump it
	pObjectMgr->SetNodeInfoID(m_CurrentNodeID,bCNode,uType);		
	////////////
	return nResult;
	/////////
}

int CCurMouse::ShowNodeInfo_SameCoords_OtherContext(CDrNode* pDrNode)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CPrecision* pPrecision 	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor 	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	int nResult;
	//////////////////////////////////////////////////////////////////////////////
	LONG  lWorldBase  = pPrecision->GetWorldBase(); 
	double dWorldBase = (double)lWorldBase; 
	double dMapFactor   = pMapFactor->GetMapFactor();
	//////////////////////////////////////////////////////////
	dTol 	= ((double)(dTol))/dWorldBase*dMapFactor;
	pObjectMgr->DStoSC(&dTol);
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	/////////////////////////////// Coords
	j = sprintf(buf,"***** A Node with same Coords Exists! ****\n");
	j += sprintf(buf+j,"(with a Net Sieve of %f)\n",dTol);
	j = ShowNodeInfo(pDrNode, buf, j);
	////////////////////////////
	j += sprintf(buf+j,
		"\n\nYES:\t\tAccept Existing Node");
	j += sprintf(buf+j,
		"\nNO:\t\tCreate New Node Anyway\n");
	j += sprintf(buf+j,"\n***To set Sievesize, Adjust NetSize in Spec Menu***\n");
	//////////////
	if(!m_bAutoAcceptOn)
		nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
	else
		nResult = IDYES;
//	nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
	///////////////
	delete str;
	return nResult;
}

int CCurMouse::LeftUp_CURVE(CPoint point)
{
	int nResult = 0;
	//////////////////////////////////////
	switch(m_CurrentCurveType)
	{
		case CP_CIRCLE:

			switch(m_CircType)
			{
				
				case CIRCLE_BY_NO3:
					nResult = LeftUp_Cur_Node(point,FALSE,TRUE,TRUE);
					if(nResult<0)		// Cancel/Error
					{
						m_nNodeDone--;
						return nResult;
					}
					break;
				case CIRCLE_BY_ROT:
					///////////////////
					switch(m_nNodeDone)
					{
						case 1 :	// Node	
							nResult = LeftUp_Cur_Node(point,FALSE,TRUE,TRUE);
							if(nResult<0)		// Cancel/Error
							{
								m_nNodeDone--;
								return nResult;
							}
							break;
						case 2 :	// CNode
							nResult = LeftUp_Cur_Node(point,TRUE,TRUE,FALSE);
							if(nResult<0)		// Cancel/Error
							{
								m_nNodeDone--;
								return nResult;
							}
							break;	
						case 3 :	// CNode or Axis Input
							if(m_bAxis)
								break;
							///////////
							nResult = LeftUp_Cur_Node(point,TRUE,TRUE,FALSE);
							if(nResult<0)		// Cancel/Error
							{
								m_nNodeDone--;
								return nResult;
							}
							break;	
						default :	
							{
								AfxMessageBox("ERROR:\nCCurMouse::LeftUp_CURVE\nCIRCLE_BY_ROT\nInvalid Cases");
								return -1;
							}
					}
					break;
				case CIRCLE_BY_2N_TI:	// fall thro'
				case CIRCLE_BY_2N_CC:
					switch(m_nNodeDone)
					{
						case 1 :	// Node
							nResult = LeftUp_Cur_Node(point,FALSE,TRUE,TRUE);
							if(nResult<0)		// Cancel/Error
							{
								m_nNodeDone--;
								return nResult;
							}
								break;
						case 2 :	// CNode/Node
							nResult = LeftUp_Cur_Node(point,TRUE,TRUE,FALSE);
							if(nResult<0)		// Cancel/Error
							{
								m_nNodeDone--;
								return nResult;
							}
							break;	
						case 3 :	// Node
							nResult = LeftUp_Cur_Node(point,FALSE,TRUE,TRUE);
							if(nResult<0)		// Cancel/Error
							{
								m_nNodeDone--;
								return nResult;
							}
							break;
						default :	// Node
							nResult = LeftUp_Cur_Node(point,FALSE,TRUE,TRUE);
							if(nResult<0)		// Cancel/Error
							{
								m_nNodeDone--;
								return nResult;
							}
							break;
					}
					break;
				case CIRCLE_BY_2CN_TI_R:
					switch(m_nNodeDone)
					{
						case 1 :	// CNode/Node Fall thro'
						case 2 :	// CNode/Node
						case 3 :	// CNode/Node
							nResult = LeftUp_Cur_Node(point,TRUE,TRUE,FALSE);
							if(nResult<0)		// Cancel/Error
							{
								m_nNodeDone--;
								return nResult;
							}
							break;	
						default :	// CNode/Node
							nResult = LeftUp_Cur_Node(point,TRUE,TRUE,FALSE);
							if(nResult<0)		// Cancel/Error
							{
								m_nNodeDone--;
								return nResult;
							}
							break;
					}
					break;
				
				default:

					break;

			}
			break;
			
		default:	// Non-Circular Curve

			// Node
			nResult = LeftUp_Cur_Node(point,FALSE,TRUE,TRUE);
			if(nResult<0)		// Cancel/Error
			{
				m_nNodeDone--;
				return nResult;
			}
			break;
	}
	//////////////////////////////////////////////////// Dont Show Curve
	if(	m_CurrentCurveType == CP_CIRCLE		||
		m_CurrentCurveType == CP_ELLIPSE	||	m_CurrentCurveType == CP_PARABOLA	||
		m_CurrentCurveType == CP_HYPERBOLA
	) 			
	{
		if(m_nNodeDone >1 && (m_CircType != CIRCLE_BY_ROT) )
		{
			m_ElSegList.AddTail(m_ElPerSeg);
			m_nTotElPerSeg += m_ElPerSeg;
		}
		if(m_nNodeDone == 3) 
		{
			if(!m_bArc)
			{
				int nLastSegElem = m_nTotElems;
				m_ElSegList.AddTail(nLastSegElem);
				m_nTotElPerSeg += nLastSegElem;
			}
		}
	}
	else
	if(m_nNodeDone >1)
	{		
		m_ElSegList.AddTail(m_ElPerSeg);
		//////////////////////////
		if(ShowCurve(&m_CurrentCurveID,FALSE)<0)		// FALSE = Not Final
			return -1;
	}
	/////////////////////////////////////// Set Anchor
	SetAnchorNodeID(m_CurrentNodeIDOld );
	//////////////////////////////////////
	return 0;
}

void CCurMouse::ElementLeftUp_CUR(CPoint point)
{                          
	int nResult = MA_OK;
	////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	//////////////////////////////////////////////////////////////////
	CString Nid;
	BOOL bRightOn = FALSE;
	///////////////////
	switch(m_nActiveTool) 
	{
		
		///////////////////////////////////////////////////// CURVEs Insert
		case C_LINEAR:
		case C_QUADRATIC:
		case C_BSPLINE:
		case C_NURB:

			m_nNodeDone++;
			////////////////
			UpdateCDlg_TRUE();
			////////////////////
			if(LeftUp_CURVE(point)<0)
				/////////////////
				return;
			//////////////////////////////////// If Single Line, Get RightButton Done
			if(m_nNodeDone>=2 && m_bSingleSegOn)
				bRightOn = TRUE;
			////////////////////////
			if(bRightOn)
			{
				////////////////////
				nResult = RightUp_CURVE();
/* done in RightUp_CURVE
				{
					m_nNodeDone--;
					Terminate_CUR(TRUE); // bError
					///////
					return;
				}
				////////////////////
				pWnd->GetMouseMgr()->SetCurrentProcessDone(TRUE);
				///
*/
			}	
			UpdateCDlg_FALSE();
			///////
			return;
		///////////////////////////////////////////////////// BEZIER Insert(Upto Cubic for Now)
		case C_BEZIER:


			m_nNodeDone++;
			////////////////
			UpdateCDlg_TRUE();
			////////////////////
			if(LeftUp_CURVE(point)<0)
				/////////////////
				return;
			//////////////////////////////////// Upto Cubic, Get RightButton Done
			if(m_nNodeDone>=4)
				bRightOn = TRUE;
			////////////////////////
			if(bRightOn)
				nResult = RightUp_CURVE();
			UpdateCDlg_FALSE();
			///////
			return;
		///////////////////////////////////////////////////// CONICSs Insert
		case C_CIRCLE:
		case C_ELLIPSE:
		case C_HYPERBOLA:
		case C_PARABOLA:

			if(m_nNodeDone>=3)
				return;
			m_nNodeDone++;
			////////////////
			UpdateCDlg_TRUE();
			////////////////////
			if(LeftUp_CURVE(point)<0)
				return;
			///////////////////
			UpdateCDlg_FALSE();
			///////
			return;
	
		//////////////////////////////////////////////////
		default:  
			break;
	} 
}	

int CCurMouse::ShowCurveInfo(CDrCurve* pDrCurve)
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
	CString			FromID		= pDrCurve->GetFromIDNode_S()->GetObjectID();
	CString			ToID		= pDrCurve->GetToIDNode_S()->GetObjectID();
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
	j = sprintf(buf,"***** A Curve Hit *****\n");
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
	sprintf( buf + j-2, "; ");
	////////////////////////////
	j += sprintf(buf+j,
		"\nYES:\t\tAccept This Curve");
	j += sprintf(buf+j,
		"\nNO:\t\tFind Next Curve with Intersecting Trace");
	j += sprintf(buf+j,
		"\nCANCEL:\t\tCancel Selection Process");
	///////////////
	if(!m_bAutoAcceptOn)
		nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
	else
		nResult = IDYES;
//	nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
	///////////////
	delete str;
	return nResult;
}

void CCurMouse::OnEBoxMouseMove_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CCurMouse::OnEBoxLButtonUp_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CCurMouse::OnEBoxRButtonDown_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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
						
			
//			if(m_MI_Cur_I.RBDown_CInsert(CP_CIRCLE,m_pView,m_nView) <0)
//				return; 
			//////////////////////////// 	
			return;
		
		case C_ELLIPSE:
						
//			if(m_MI_Cur_I.RBDown_CInsert(CP_ELLIPSE,m_pView,m_nView) <0)
//				return; 
			//////////////////////////// 	
			return;
		
		case C_PARABOLA:
						
//			if(m_MI_Cur_I.RBDown_CInsert(CP_PARABOLA,m_pView,m_nView) <0)
//				return; 
			//////////////////////////// 	
			return;
		
		case C_LINEAR:
						
//			if(m_MI_Cur_I.RBDown_CInsert(CP_LINEAR,m_pView,m_nView) <0)
//				return; 
			//////////////////////////// 	
			return;
		
		case C_QUADRATIC:
						
//			if(m_MI_Cur_I.RBDown_CInsert(CP_QUADRATIC,m_pView,m_nView) <0)
//				return; 
			//////////////////////////// 	
			return;
		
		case C_BEZIER:
						
//			if(m_MI_Cur_I.RBDown_CInsert(CP_BEZIER,m_pView,m_nView) <0)
//				return; 
			//////////////////////////// 	
			return;
		
		case C_BSPLINE:
						
//			if(m_MI_Cur_I.RBDown_CInsert(CP_BSPLINE,m_pView,m_nView) <0)
//				return; 
			//////////////////////////// 	
			return;
		
		case C_NURB:
						
//			if(m_MI_Cur_I.RBDown_CInsert(CP_NURB,m_pView,m_nView) <0)
//				return; 
			//////////////////////////// 	
			return;
		////////////////////////////////////////////////// Patch
		default:
			break;
	}  
}

int CCurMouse::RightUp_CURVE()
{
	int nResult = MA_OK;
	///////////////////////////////////////////////////////// Enable BLine,if needed
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	//////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	//////////////////////////////////////////////////// Error 
	nResult = RightUp_CURVE_Error();
	switch(nResult)
	{
		case MA_OK:break;
		case MA_ERROR:Terminate_CUR(TRUE);return MA_ERROR;
		case MA_CANCEL:Terminate_CUR(TRUE);return MA_CANCEL;
		case MA_GETMOREINFO:return MA_GETMOREINFO;
	}
	//////////////////////////////////////////////////// Premature?
	nResult = RightUp_CURVE_Premature();
	switch(nResult)
	{
		case MA_OK:break;
		case MA_ERROR:Terminate_CUR(TRUE);return MA_ERROR;
		case MA_CANCEL:Terminate_CUR(TRUE);return MA_CANCEL;
		case MA_GETMOREINFO:return MA_GETMOREINFO;
	}
	/////////////////////////////////////////////////////////////// Not AutoAccept
	if(!m_bAutoAcceptOn)
	{
		nResult = RightUp_CURVE_NotAutoAccept();
		switch(nResult)
		{
			case MA_OK:break;
			case MA_ERROR:Terminate_CUR(TRUE);return MA_ERROR;
			case MA_CANCEL:Terminate_CUR(TRUE);return MA_CANCEL;
			case MA_GETMOREINFO:return MA_GETMOREINFO;
		}
	}
	/////////////////
	CString* pID;
	int nAnswer = IDOK;
	pID			= &m_CurrentCurveID; 
	/////////////////////////////////////////////////////////////////////// Show NewCurve
	nResult = ShowCurve(pID,TRUE);		// TRUE = Final
	switch(nResult)
	{
		case MA_OK:break;
		case MA_ERROR:Terminate_CUR(TRUE);return MA_ERROR;
		case MA_CANCEL:Terminate_CUR(TRUE);return MA_CANCEL;
		case MA_GETMOREINFO:return MA_GETMOREINFO;
	}
	/////////////////////////////////////////////////////////// Update Curve Topology
	nResult = CurTopo_Update(m_pCurrentCurve,m_CurrentCurveType,&m_NodeList);
	switch(nResult)
	{
		case MA_OK:break;
		case MA_ERROR:Terminate_CUR(TRUE);return MA_ERROR;
		case MA_CANCEL:Terminate_CUR(TRUE);return MA_CANCEL;
		case MA_GETMOREINFO:return MA_GETMOREINFO;
	}
	/////////////////////////////////////// Set next CurveID
	if(*pID == m_CurrentCurveID)
		pObjectMgr->SetObjInfoID(m_CurrentCurveID,CURVE);
	//////////////////////////////////////////////
	CDListMgr	HeadTail;
	////////////////////
	CDrNode*	pNHead;
	CDrNode*	pNTail;
	/////////////////////////////////////////////////////////////////////// Get Ends
	CurTopo_GetEndNodes(m_pCurrentCurve,m_CurrentCurveType,&m_NodeList,&HeadTail);
	////////////////////
	pNHead = (CDrNode*)(HeadTail.GetHead());
	pNTail = (CDrNode*)(HeadTail.GetTail());
	HeadTail.RemoveAll();
	/////////////////////
	CString		strLastNodeID;
	/////////////////////////////////////////////////////////// BLine
	if(m_bBLineOn)			
	{
		m_nNodeDone		= 1;
		m_bCurveDone	= TRUE;	// 040297
		m_ElSegList.RemoveAll();
		m_NodeList.RemoveAll();
		m_NodeList.AddTail(pNTail);
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
	strLastNodeID = pNTail->GetObjectID();
	m_bAnchorCNode = FALSE;
	/////////////////////
	if(m_pLQCInDlg->GetSafeHwnd())
		m_pLQCInDlg->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
	if(m_pCrcInDlg->GetSafeHwnd())
		m_pCrcInDlg->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
	////////////////////////////////////
	m_CurrentNodeIDOld = strLastNodeID;
	SetAnchorNodeID(m_CurrentNodeIDOld);
	///////////////////
	pWnd->GetMouseMgr()->SetCurrentProcessDone(TRUE);
	pWnd->GetMenu()->EnableMenuItem(IDM_OPTION_BLINEON,MF_BYCOMMAND|MF_ENABLED);
	/////////////////////// Send Message For CurrStat
//	pWnd->SendMessage(ID_RESET_MODELESS);
	///////////////
	return MA_OK;
}

int CCurMouse::RightUp_CURVE_Error()
{
	///////////////////////////////////////////////////////// Enable BLine,if needed
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	//////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
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
				return -1;
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
	else
	if(m_ElPerSeg<1)
	{
		AfxMessageBox("INVALID DATA:\nFor Curve\nAtleast 1 Element Should be Specified!");
		GetLQCInDlg()->GetDlgItem(IDC_ELEMS)->SetFocus();
		/////////////////
		GetLQCInDlg()->UpdateData(FALSE);
		/////////////////
		return -1;
	}
	//////////
	return 0;
}

int CCurMouse::RightUp_CURVE_Premature()
{
	int nAnswer = MA_OK;
	////////////////////
//	int nAnswer = IDOK		= MA_OK;				// no problem
//	int nAnswer = IDOK		= MA_GETMOREINFO;		// continue get more info
//	int nAnswer = IDCANCEL	= MA_CANCEL;			// Cancel Process
	///////////////////////////////////////////////////////// Enable BLine,if needed
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	//////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	BOOL bPreMature = FALSE;
	////////////////////////////////////////////////////////////////// 
	CString* pID;
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
						bPreMature = TRUE;
					}
					break;
				
				default:

					break;

			}
			break;
				
		case CP_PARABOLA:
		case CP_HYPERBOLA:
		case CP_ELLIPSE:	// for now
			if(m_nNodeDone<3)
			{
				////////////////////
				j = sprintf(buf,"ERROR:\n\t%d Nodes Input to generate the Curve\n",m_nNodeDone);
				j += sprintf(buf+j,"Exactly 3 Nodes Needed\n");
				j += sprintf(buf+j,"Do You want to Continue to Get More Node(s) ?");
				/////////////////////////	
				bPreMature = TRUE;
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
				bPreMature = TRUE;
			}
	}
	/////////////////////////////////
	if(bPreMature)
	{
		nAnswer = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
		delete str;
	}
	else
		return MA_OK;
	//////////////////////////////////////////////////////////////////// Dialog result
	if(nAnswer == IDNO)		// Cancel
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		sprintf(buf,"Are You Sure You Want to\nDelete Current Curve?");
		/////////////////////////	
		nAnswer = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
		delete str;
		/////////////////////////
		if(nAnswer == IDYES)		//delete
		{
			Terminate_CUR(TRUE);
			/////////////////////////////////////
			pDoc->UpdateAllViews(NULL);
			///////////////////////////
			return MA_CANCEL;
		}
/*
			///////////////////////////////////////// delete
			pList = pObjectMgr->GetObjectList(CURVE);
			int nActiveIndex = pList->GetObjectIndex(CURVE, *pID);
			//////////////////////////////////////////////////// Reset
			if(nActiveIndex>=0)
				pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
			/////////////////////////////////////// Reset
			ResetVariables_CUR();
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
*/
	}
	////////
	return MA_GETMOREINFO;
}

int CCurMouse::RightUp_CURVE_NotAutoAccept()
{
//	return = IDOK;		// Continue Process
//	return = IDCANCEL;	// Cancel Process
	/////////////////////////////////////////////////////////////// Not AutoAccept
	switch(m_CurrentCurveType)
	{
		case CP_CIRCLE:

			return RightUp_CIRCLE_NotAutoAccept();
			//////
	
		case CP_PARABOLA:
		case CP_HYPERBOLA:
		case CP_ELLIPSE:	// for now
		default:			// other types

			return RightUp_NOTCIRCLE_NotAutoAccept();
			//////
	}
	///////////////
	return IDOK;
}

int CCurMouse::RightUp_NOTCIRCLE_NotAutoAccept()
{
//	int nAnswer = IDOK;		// Continue Process
//	int nAnswer = IDCANCEL;	// Cancel Process
	///////////////////
	int nAnswer = MA_OK;
	///////////////////////////////////////////////////////// Enable BLine,if needed
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	//////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr*	pList;
	////////////////////////////////////////////////////////////////// 
	CString* pID;
	pID			= &m_CurrentCurveID; 
	//////////////////////////////////////////////////// Check Adequate Node,or cancel
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	/////////////////////////////////////////////////////////////// Not AutoAccept
	int nElems = m_nTotElPerSeg;
	switch(m_CurrentCurveType)
	{
		case CP_PARABOLA:
		case CP_HYPERBOLA:
		case CP_ELLIPSE:	// for now
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
	sprintf( buf + j-2, "; ");
	/////////////////////////	
	nAnswer = AfxMessageBox(*str,MB_OKCANCEL|MB_ICONQUESTION );
	/////////////////////////
	if(nAnswer == IDCANCEL)
	{
		sprintf(buf,"Are You Sure You Want to\nDelete Current Curve?");
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
			ResetVariables_CUR();
			//////////////////////////////////////////////////////////// reset
			switch(m_CurrentCurveType)
			{
				case CP_PARABOLA:
				case CP_HYPERBOLA:
				case CP_ELLIPSE:	// for now
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
			return MA_CANCEL;
		}
	}
	/////////////////////
	str->ReleaseBuffer();
	delete str;
	///////////////
	return MA_OK;
}

int CCurMouse::RightUp_CIRCLE_NotAutoAccept()
{
//	int nAnswer = IDOK;		// Continue Process
//	int nAnswer = IDCANCEL;	// Cancel Process
	///////////////////
	int nAnswer = MA_OK;
	///////////////////////////////////////////////////////// Enable BLine,if needed
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	//////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr*	pList;
	////////////////////////////////////////////////////////////////// 
	CString* pID;
	pID			= &m_CurrentCurveID; 
	//////////////////////////////////////////////////// Check Adequate Node,or cancel
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	/////////////////////////////////////////////////////////////// Not AutoAccept
	int nElems = m_nTotElPerSeg;
	//////////////////
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
					j += sprintf(buf+j,"\t%f is Angle of Rotation\n",m_dAng);
			}
			break;

		case CIRCLE_BY_2N_TI:

			j = sprintf(buf,"Circle %s contains:\n\t%d Nodes\n\t%d Elements\n",
					*pID,m_NodeList.GetCount(),nElems);
			j += sprintf(buf+j,"2 End Nodes & Tangent Intersection\n");
			j += sprintf(buf+j,"\t%s is Tangent Intersection Node\n",m_TIID);
			if(m_bClosed)
				j += sprintf(buf+j,"\tClosed Circle\n");
			else
			{
				if(m_bArc)
					j += sprintf(buf+j,"\tArc upto 3rd Node\n");
				else
					j += sprintf(buf+j,"\t%f is Angle of Rotation\n",m_dAng);
			}
			break;

		case CIRCLE_BY_2N_CC:

			j = sprintf(buf,"Circle %s contains:\n\t%d Nodes\n\t%d Elements\n",
					*pID,m_NodeList.GetCount(),nElems);
			j += sprintf(buf+j,"2 End Nodes & Center\n");
			j += sprintf(buf+j,"\t%s is Center Node\n",m_CCID);
			if(m_bClosed)
				j += sprintf(buf+j,"\tClosed Circle\n");
			else
			{
				if(m_bArc)
					j += sprintf(buf+j,"\tArc upto 3rd Node\n");
				else
					j += sprintf(buf+j,"\t%f is Angle of Rotation\n",m_dAng);
			}
			break;
				
		case CIRCLE_BY_2CN_TI_R:

			j = sprintf(buf,"Circle %s contains:\n\t%d Nodes\n\t%d Elements\n\tRadius = %f\n",
					*pID,m_NodeList.GetCount(),nElems,m_dRadius);
			j+= sprintf(buf+j,"2 Control Nodes on Tangents &\nTangent Intersection\n");
			j += sprintf(buf+j,"\t%s is CNode_CA\n",m_CAID);
			j += sprintf(buf+j,"\t%s is Tangent Intersection Node\n",m_TIID);
			j += sprintf(buf+j,"\t%s is CNode_CB\n",m_CBID);
			if(m_bClosed)
				j += sprintf(buf+j,"\tClosed Circle\n");
			else
			{
				if(m_bArc)
					j += sprintf(buf+j,"\tArc upto 3rd Node\n");
				else
					j += sprintf(buf+j,"\t%f is Angle of Rotation\n",m_dAng);
			}
			break;
	
		default:

			break;

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
	sprintf( buf + j-2, "; ");
	/////////////////////////	
	nAnswer = AfxMessageBox(*str,MB_OKCANCEL|MB_ICONQUESTION );
	/////////////////////////
	if(nAnswer == IDCANCEL)
	{
		sprintf(buf,"Are You Sure You Want to\nDelete Current Curve?");
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
			ResetVariables_CUR();
			//////////////////////////////////////////////////////////// reset
			switch(m_CurrentCurveType)
			{
				case CP_CIRCLE:

					if(m_pCrcInDlg->GetSafeHwnd())
						m_pCrcInDlg->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
					break;

				default:
					break;
			}
			///////////
			delete str;
			///////////////////////
			pDoc->UpdateAllViews(NULL);
			pWnd->GetMenu()->EnableMenuItem(IDM_OPTION_BLINEON,MF_BYCOMMAND|MF_ENABLED);
			///////////////////////////
			return MA_CANCEL;
		}
	}
	/////////////////////
	str->ReleaseBuffer();
	delete str;
	///////////////
	return MA_OK;
}

void CCurMouse::OnEBoxRButtonUp_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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
	CString ID;
	CString* pID = &ID;
	////////////////////
	switch(m_nActiveTool) 
	{
		///////////////////////////////////////////////////// CURVEs INSERT
		case C_LINEAR:
		case C_QUADRATIC:
		case C_CIRCLE:
		case C_ELLIPSE:
		case C_PARABOLA:
		case C_HYPERBOLA:
		case C_BEZIER:
		case C_BSPLINE:
		case C_NURB:

		default:  
				////////////////////
				UpdateCDlg_TRUE();
				////////////////////
				nResult = RightUp_CURVE();
/* done in RightUp_Curve
				switch(nResult)
				{
					case MA_OK:break;
					case MA_ERROR:Terminate_CUR(TRUE);return;
					case MA_CANCEL:Terminate_CUR(TRUE);return;
					case MA_GETMOREINFO:return;
				}
*/
				////////////////////
				UpdateCDlg_FALSE();
				///////////////////	
			return;
	} 
}

int CCurMouse::PutEndIdsInPipeList(CString nid[],int nEnds)
{
/*
	///////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
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
	AfxMessageBox("ERROR:\nCCurMouse::PutEndIdsInPipeList\nSHOULD NOT BE USED");
	return -1; 
}
    
/////////////////////////////////////////////////////////////////////////////////////// F_M
UINT CCurMouse::ReSetToolID_CUR(UINT CntlID,UINT IGenID, UINT OperID)
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
						case C_HYPERBOLA:	str = "HYPERBOLIC@CURVE";ID = C_HYPERBOLA;
								strCur += "A Hyperbola";	break;
						case C_LINEAR:		str = "LINEAR@BSPLINE";	ID = C_LINEAR;
								strCur += "A Linear Curve";	break;
						case C_QUADRATIC:	str = "QUADRATIC@BSPLINE";ID = C_QUADRATIC;
								strCur += "A Quadratic Curve";	break;
						case C_CUBIC:		str = "CUBIC@BSPLINE";	ID = C_CUBIC;
								strCur += "A Cubic Curve";	break;
						case C_HERMITE:		str = "HERMITE@CURVE";	ID = C_HERMITE;	
								strCur += "A Hermite Curve";	break;
						case C_BEZIER:		str = "ONE_SEG@BEZIER";	ID = C_BEZIER;
								strCur += "A Bezier Curve";	break;
						case C_BSPLINE:		str = "CUBIC@BSPLINE";	ID = C_BSPLINE;
								strCur += "A BSpline Curve";	break;
						case C_NURB:		str = "CUBIC@NURB";		ID = C_NURB;
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
	
void CCurMouse::ModeLessOff_CUR()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	if(GetLQCInDlg()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_LQCIN,IDOK);
	if(GetCrcInDlg()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_CRCIN,IDOK);
}

void CCurMouse::ModeLessOn_CUR()
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
		(aTool == C_PARABOLA)	||	(aTool == C_ELLIPSE)		||		     
		(aTool == C_HYPERBOLA)	||	(aTool == C_BSPLINE)		||		     
		(aTool == C_NURB)		||	(aTool == C_BEZIER)				     
	)
	{
//		if(!(GetLQCInDlg()->m_hWnd))
			pWnd->SendMessage(ID_ACTIVE_LQCIN,IDOK);
		if(GetCrcInDlg()->m_hWnd)
			pWnd->SendMessage(ID_GOODBYE_CRCIN,IDOK);
	}
	else
	if (aTool == C_CIRCLE)
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

long CCurMouse::CreateorActivateLQCIn(UINT wParam, long lParam)
{
	
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	m_bBLineOn				= pBool->IsBLineOn();
	CString strCurr;
	/////////////////////////////////////////////////////////
	if(GetLQCInDlg()->GetSafeHwnd() ==0)	// not created already
	{
		GetLQCInDlg()->Create();
		//////////////////////
		CRect BoxRect;
		CWnd  wndTopMost;
		GetLQCInDlg()->GetWindowRect(&BoxRect);
		SizeRectDlgIn(BoxRect);
		//////////////////////////////////////////////////////////////
		GetLQCInDlg()->SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
                        BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
		//////////////////////////////////////////////////////////////
//		if(!m_bBLineOn && m_bCurveDone)			// Reset
//			pObjectMgr->SetNodeInfoID(m_CurrentNodeID,FALSE,(UINT)NODE);
	}
	else
	{
		GetLQCInDlg()->SetActiveWindow();
	}
	////
	if(!m_bBLineOn && m_bCurveDone)			// Reset
	{
		m_bAnchorCNode		= FALSE;
		////
		m_CurrentNodeIDOld	= m_CurrentNodeID;
		m_AnchorNodeID		= m_CurrentNodeID;
		/////
		m_nNodeDone = 0;
		////////////////
		if(!m_ElSegList.IsEmpty())
			m_ElSegList.RemoveAll();
		if(!m_NodeList.IsEmpty())
			m_NodeList.RemoveAll();
	}
	////////////////////////////////
	switch(pWnd->GetCurrentIGenID())
	{
		case C_ELLIPSE:		strCurr = "Creating An Ellipse";		break;
		case C_PARABOLA:	strCurr = "Creating A Parabola";		break;
		case C_HYPERBOLA:	strCurr = "Creating A Hyperbola";		break;
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
		ResetVuBasedVars_CurDlg();
	}
	////////////////////////////////////////////////////////////////// Set Info
	m_bClosed = FALSE;
	m_pLQCInDlg->GetDlgItem(IDC_CLOSED)->EnableWindow(FALSE);
	if(m_CurrentCurveType == CP_LINEAR)
		m_pLQCInDlg->GetDlgItem(IDC_ADVANCED)->EnableWindow(FALSE);
	if
		(	m_CurrentCurveType == CP_ELLIPSE	||	m_CurrentCurveType == CP_PARABOLA	||
			m_CurrentCurveType == CP_HYPERBOLA	||  m_CurrentCurveType == CP_BEZIER	
		)
	{
		m_bAdvanceOn = FALSE;
		m_pLQCInDlg->GetDlgItem(IDC_ADVANCED)->EnableWindow(FALSE);
	}
	////////////////////////////////
	GetLQCInDlg()->m_CID		= GetCurrentCurveID();
	GetLQCInDlg()->m_NID		= GetCurrentNodeID();
	GetLQCInDlg()->m_dCoord		= m_ThirdCoord;
	GetLQCInDlg()->m_nElperSeg	= GetCurrentElPerSeg();
	GetLQCInDlg()->m_dRatio		= GetCurrentRatio();
	GetLQCInDlg()->m_bClosed	= IsClosed();
	GetLQCInDlg()->m_bAdvanceOn	= IsAdvanceOn();
	////////////////////////////////////////////
	GetLQCInDlg()->UpdateData(FALSE);
	/////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////
	return 0L;
}
 
void CCurMouse::ResetVuBasedVars_CurDlg()
{
	////////////////////////////////////////////////////////////////// Set Info
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CStatic* pCtl;
	///////////////////////////////////////////////////////////////// if NodeDlg Open
	switch(pWnd->GetCurrentIGenID())
	{
		case C_CIRCLE:
		//////////////////
			if(GetCrcInDlg()->m_hWnd)
			{
				pCtl = (CStatic*)(GetCrcInDlg()->GetDlgItem(IDC_OTHER));
				////////////////////////////////////////////////////////
				SwitchThirdCoordHeading(pCtl,
					(UINT)(pWnd->GetActiveViewNumber()) );
			}
			return;
		//////////////////
		case C_LINEAR:
		case C_QUADRATIC:
		case C_CUBIC:
		case C_PARABOLA:
		case C_HYPERBOLA:
		case C_ELLIPSE:
		case C_BSPLINE:
		case C_NURB:
		//////////////////
			if(GetLQCInDlg()->m_hWnd)
			{
				pCtl = (CStatic*)(GetLQCInDlg()->GetDlgItem(IDC_OTHER));
				////////////////////////////////////////////////////////
				SwitchThirdCoordHeading(pCtl,
					(UINT)(pWnd->GetActiveViewNumber()) );
			}
			return;
		//////////////////
		default:
			return;
	}
}
	 
long CCurMouse::CancelLQCIn(UINT wParam, long lParam)
{
	
	GetLQCInDlg()->DestroyWindow();
	//////////
	return 0L;
}

long CCurMouse::GoodByeLQCIn(UINT wParam, long lParam)
{
	
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
//	CString strCurr;
	/////////////////////////////////////////////////////////
	if(GetLQCInDlg()->m_hWnd)
		GetLQCInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CCurMouse::UpdateLQCIn(UINT wParam, long lParam)
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
	if
		(	m_CurrentCurveType == CP_ELLIPSE	||	m_CurrentCurveType == CP_PARABOLA	||
			m_CurrentCurveType == CP_HYPERBOLA	||	m_CurrentCurveType == CP_BEZIER	
		)
	{
		m_bAdvanceOn = FALSE;
		m_pLQCInDlg->GetDlgItem(IDC_ADVANCED)->EnableWindow(FALSE);
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

long CCurMouse::CreateorActivateCrcIn(UINT wParam, long lParam)
{
	
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
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
//		if(!m_bBLineOn && m_bCurveDone)			// Reset
//			pObjectMgr->SetNodeInfoID(m_CurrentNodeID,FALSE,(UINT)NODE);
		/////////////////////////////////////
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
		///
		GetCrcInDlg()->m_CircType = m_CircType;
		GetCrcInDlg()->SendMessage(WM_INITDIALOG);
		///////////////////////// CurrStat: Show
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
	////
	if(!m_bBLineOn && m_bCurveDone)			// Reset
	{
		m_bAnchorCNode		= FALSE;
		////
		m_CurrentNodeIDOld	= m_CurrentNodeID;
		m_AnchorNodeID		= m_CurrentNodeID;
		/////
		m_nNodeDone = 0;
		////////////////
		if(!m_ElSegList.IsEmpty())
			m_ElSegList.RemoveAll();
		if(!m_NodeList.IsEmpty())
			m_NodeList.RemoveAll();
		///////////////////////////
	}
	////////////////////////////// CurrStat
	if(m_CircType != CIRCLE_BY_ROT)
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
	///////////////////////////////////////////////////////////////// if CrcDlg Open
	if(GetCrcInDlg()->m_hWnd)
	{
		ResetVuBasedVars_CurDlg();
	}
	////////////////////////////////////////////////////////////////// Set Info
	GetCrcInDlg()->m_CurveID	= m_CurrentCurveID;
	GetCrcInDlg()->m_NID		= m_CurrentNodeID;
	GetCrcInDlg()->m_dCoord		= m_ThirdCoord;
	GetCrcInDlg()->m_nElemPerSeg= m_ElPerSeg;
	GetCrcInDlg()->m_nTotElems	= m_ElPerSeg;
	///////
	if(m_CircType == CIRCLE_BY_ROT)
		GetCrcInDlg()->m_nTotElems	= m_nTotElems;
	///////	
	GetCrcInDlg()->m_Ratio		= m_Ratio;
	GetCrcInDlg()->m_SegAngle	= m_SegAngle;
//	GetCrcInDlg()->m_bAutoSeg	= m_bAutoSeg;
	GetCrcInDlg()->m_bArc		= m_bArc;
	GetCrcInDlg()->m_bClosed	= m_bClosed;
	GetCrcInDlg()->m_dAngSpec	= m_dAng;
	//////
	switch(m_CircType)
	{
		case CIRCLE_BY_2N_TI:
		case CIRCLE_BY_2N_CC:
		case CIRCLE_BY_NO3:
			////
			break;
		case CIRCLE_BY_ROT:
			m_bArc		= FALSE;
			m_bClosed	= FALSE;
			GetCrcInDlg()->m_bArc		= m_bArc;
			GetCrcInDlg()->m_bClosed	= m_bClosed;
			GetCrcInDlg()->m_bAxis		= m_bAxis;		
			GetCrcInDlg()->m_nAxis		= m_nAxis;
			GetCrcInDlg()->m_bNegative	= m_bNegative;
			////
			break;
			break;
		case CIRCLE_BY_2CN_TI_R:
			GetCrcInDlg()->m_dRadius	= m_dRadius;
			////
			break;
		default:
			break;
	}
	////////////////////////////////
	GetCrcInDlg()->UpdateData(FALSE);
	/////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////
	return 0L;
}
	 
long CCurMouse::CancelCrcIn(UINT wParam, long lParam)
{
	
	GetCrcInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CCurMouse::GoodByeCrcIn(UINT wParam, long lParam)
{
	
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	/////////////////////////////////////////////////////////
	GetCrcInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CCurMouse::UpdateCrcIn(UINT wParam, long lParam)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// Circle_by_Rot with Axis
	WORLD LocPos_From,LocaPos_To;
	POSITION pos;
	CDrNode* pNode;
	CDrLabel* pLabel;
	CMI_GangN GangN;
	CString ToID;
	/////////////////////////// Generate ToID Node
	int nNodeIndex = -12345; // Create Anyway
	int nLabelIndex= 0;
	///////////////////////////////////////////////////////////////
	GetCrcInDlg()->UpdateData(TRUE);
	///////////////////////////////// Reset data in ElMouse
	m_CurrentCurveID	= GetCrcInDlg()->m_CurveID;
	m_CurrentNodeID		= GetCrcInDlg()->m_NID;
	///////////////////////////////////////////////////
	m_ElPerSeg			= GetCrcInDlg()->m_nElemPerSeg;
	m_nTotElems			= GetCrcInDlg()->m_nTotElems;	// User
	///////////////////////////////////////////////////
	m_Ratio				= GetCrcInDlg()->m_Ratio;
	m_SegAngle			= GetCrcInDlg()->m_SegAngle;
//	m_bAutoSeg			= GetCrcInDlg()->m_bAutoSeg;
	SetCurrentThirdCoord(GetCrcInDlg()->m_dCoord);
	m_bClosed			= GetCrcInDlg()->m_bClosed;
	m_dAng				= GetCrcInDlg()->m_dAngSpec;
	m_bArc				= GetCrcInDlg()->m_bArc;
	//////
	switch(m_CircType)
	{
		case CIRCLE_BY_2CN_TI_R:
			m_dRadius		= GetCrcInDlg()->m_dRadius;
		case CIRCLE_BY_2N_TI:
		case CIRCLE_BY_2N_CC:
		case CIRCLE_BY_NO3:

			//////////
			break;
		case CIRCLE_BY_ROT:

			////////////////
			m_ElSegList.RemoveAll();
			m_ElSegList.AddTail(m_ElPerSeg);
			m_ElSegList.AddTail(m_nTotElems);	// it is Actually # of BezierSegments
			////////////////////
			if(m_nNodeDone >= 3)
				break;
			////////////////////////////////
			m_bAxis			= GetCrcInDlg()->m_bAxis;		
			m_nAxis			= GetCrcInDlg()->m_nAxis;
			m_bNegative		= GetCrcInDlg()->m_bNegative;
			/////////////////////////////////
			if(m_bAxis && (m_nNodeDone == 2)) 
				m_nNodeDone++;
			else
				break;
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
						AfxMessageBox("Internal ERROR:\nCCurMouse::UpdateCrcIn()\nm_nAxis !=1,2or3");
						return -1L;
					}
			}
			////////////
			pObjectMgr->SetNodeInfoID(ToID,TRUE,CNODE);
			////
			pNode = GangN.CreateNode(ToID,pLabel,LocaPos_To,TRUE,TRUE,
								nNodeIndex,nLabelIndex,LEVEL_GRAPA);// FALSE=Input/TRUE=InternallyGen
			pNode->SetCategory(CA_ELEMENT);
			pNode->SetShow(FALSE);	// only for Internal Use
			//////////////////////////////////////////////// save
			m_NodeList.AddTail(pNode);
			////////////////////
			UpdateCDlg_FALSE();
			////////////////////
			break;
			//////
		default:
			break;
	}
	//////////
	return 0L;
}

void CCurMouse::Serialize(CArchive& ar)
{

	CNodMouse::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CurMouse:    Storing\n");	
		

	}
	else
	{
		TRACE(" CurMouse:    Loading\n");	

	
	}        
	///////////////////////////////////// 
	SerializeNode(ar);      
	SerializePipe(ar);
	//////////////////
}

///////////////////////////////////////////////////////// element serializer
void CCurMouse::SerializePipe(CArchive& ar)
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


