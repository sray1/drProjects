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
#include "MsObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
/////////////////////
#include "Def_Lims.h"                    
#include "Def_Objs.h"                    
#include "Def_Mous.h"                    
#include "Def_CuPS.h"                    
#include "Def_Ms.h" // Mesh Types for Patch
///////////////////// dialogMgr
#include "MNodMgr.h"  
///////////////////// elements
#include "Def_IGen.h"
#include "Def_Elem.h"
#include "Ext_Elem.h"
#include "DrNode.h"
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
#include "MI_GangN.h" 
#include "MI_Gang0.h" 
////////////////////// 
#include "CommRsrc.h"
#include "Dlg_NodI.h"
//////////////////////
#include "NodMouAX.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define MAX_INFO_INCREMENT	0	// 1 Object Refernce Node           
#define MAX_INFO_DIRECTION	2	// 1 Object Refernce Node/2 Nodes( for Axis)           
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CNodMouAX,CMouse,1)
/////////////////////////////////////////////////////////////////////////////
CNodMouAX::CNodMouAX()
{

	m_CurrentNodeID		= "0";
	m_CurrentNodeIDOld	= "0";
	////////////////////////////
	m_pNodInDlg			= NULL;                                                                                
	m_bDoModalDone		= FALSE;
	////////////////////////////
	m_bAutoAcceptOn		= FALSE;
  	m_bDialogOn    		= FALSE;
  	m_bElementMode 		= FALSE;
	m_bDragOn      		= FALSE;
	m_bDragging	   		= FALSE;
	m_nNodeDone    		= 0;
	m_nCNodeDone   		= 0;
	//////////////////////// Set according to WIC: TOBEDONE
	m_AnchorNodeLOG.x 	= 0;
	m_AnchorNodeLOG.y 	= 0; 
	//////////////////////////////////////
	m_MouseLOG 			= m_AnchorNodeLOG;
	m_MouseOldLOG 		= m_MouseLOG;
	/////////////////////////////////////////// Node 
    m_pCurrentNode		= NULL;
	///////////////////////////////////////////
	m_bRefreshOn		= FALSE;
 	/////////////////////////////////////////// Node 
	m_bAnchorCNode		= FALSE;
	m_ThirdCoord		= 0.0;
	/////////////////////////////////////////// NodIDlg
	m_bCorINodeOpDone	= FALSE;
	m_bCNode			= FALSE;
	////////
	m_bAdvanced			= FALSE;
	m_bDone				= TRUE;;		// for dragging
	m_nInfoDone			= 0;			// for Advance
}

CNodMouAX::~CNodMouAX()
{
	/////////////////////////////////// Modeless Dialogs
	if(m_pNodInDlg->m_hWnd)
		m_pNodInDlg->DestroyWindow();
	///////////////////
	delete m_pNodInDlg;                                                                                
	///////////////////
}

void CNodMouAX::Init_NOD()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	if(pWnd->GetCurrentIGenID() == NODE ||pWnd->GetCurrentIGenID() == INODE )
		m_bCNode = FALSE;
	else
		m_bCNode = TRUE;
	/////////////////////////////////////////////////////////
	C3DMath Math3D;
	///////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
	/////////////////////////////
/*

	char buf[50];
	if(m_bCNode)
	{
		pObjectMgr->BumpLastInputNo(CNODE);		// bump it
	    m_LastNum	= pObjectMgr->GetLastInputNo(CNODE);		// internal
		sprintf(buf,"%d",m_LastNum);
		m_SpawnedNodeID	= "CN_";
		m_SpawnedNodeID	+= buf;
	}
	else
	{
		pObjectMgr->BumpLastInputNo(NODE);		// bump it
	    m_LastNum	= pObjectMgr->GetLastInputNo(NODE);		// internal
		sprintf(buf,"%d",m_LastNum);
		m_SpawnedNodeID	= "";
		m_SpawnedNodeID	+= buf;
	}

*/
	/////////////////////////////////////////// Node
	m_pSpawnedNode		= NULL;
	m_pCurrentNode		= NULL;
	Math3D.Set3DPts(&m_wLoc,0.0,0.0,0.0);
	//////////
	m_bDone				= TRUE;;		// for dragging
	m_nInfoDone			= 0;
	/////////////////////////////////////////// Dlg_NodI 
	m_SpawnedNodeID	= m_CurrentNodeID;
	m_CurrentNodeID		= "";			// because of m_CurrentNodeID snafu when m_bAdvanced = 0
	m_ObjID			= m_SpawnedNodeID;
	///
	m_X				= m_wLoc.x;
	m_Y				= m_wLoc.y;
	m_Z				= m_wLoc.z;
	m_NID			= m_CurrentNodeID;
	m_bDirect		= FALSE;		// Forcing Mouse Search of Node	
	m_bDominant		= FALSE;
	m_bDirection	= FALSE;
	m_bIncrement	= TRUE;
	/////////////////////////////////////////// Spawning Info.
	m_RefPtID		= "";
	Math3D.Set3DPts(&m_wRefPt,0.0,0.0,0.0);
	m_FromID		= "";
	Math3D.Set3DPts(&m_wFrom,0.0,0.0,0.0);
	m_ToID			= "";
	Math3D.Set3DPts(&m_wTo,0.0,0.0,0.0);

	Math3D.Set3DPts(&m_wInc,0.0,0.0,0.0);
	Math3D.Set3DPts(&m_wFin,0.0,0.0,0.0);
	///////////////////////
}

void CNodMouAX::Terminate_NOD(BOOL bError)
{
	if(bError)
	{
		/////////////////////////////////////////// 
		if(m_pSpawnedNode)
		{
			delete m_pSpawnedNode;
			m_pSpawnedNode = NULL;
		}
	}
	///////////////////////////
}

void CNodMouAX::InitDlgIn_NOD()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
	/////////////////////////////////////////////////////////////////// System Sizes
	m_pNodInDlg		= new CDlg_NodI(pWnd,m_bAdvanced);
	/////////////
}
	
void CNodMouAX::SizeRectDlgIn(CRect& BoxRect)
{
	
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////////////// System Sizes
	int cxBorder	= ::GetSystemMetrics(SM_CXBORDER);
	int cyBorder	= ::GetSystemMetrics(SM_CYBORDER);
	int cxVScroll	= ::GetSystemMetrics(SM_CXVSCROLL);
	int cyMenuSize	= ::GetSystemMetrics(SM_CYMENUSIZE);
	int cyEdge		= ::GetSystemMetrics(SM_CYEDGE);
	int cyFrame		= ::GetSystemMetrics(SM_CYSIZEFRAME);
	int cyCapSize	= ::GetSystemMetrics(SM_CYSIZE);
	///////////////////////////////
	CRect FrameRect;
	pWnd->GetWindowRect(&FrameRect);
	/////////////////////////////////////////////////////////////// ...InBox 
	int Boxwidth  		= BoxRect.Width();
	int Boxheight 		= BoxRect.Height();
	///////////////////////////////////////
	BoxRect.top    = 1 + FrameRect.top + cyEdge + cyCapSize;   //		
	BoxRect.bottom = BoxRect.top	+ Boxheight; //
	BoxRect.right  = FrameRect.right - cxBorder;
	BoxRect.left   = BoxRect.right	- Boxwidth;
	////////////////////////////////
	return;
}

void CNodMouAX::PreLeftDown(CPoint point)
{ 

	LPOINT3 MouseWIC;
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
	/////////////////////////////////////////////////////////END TEMPORARY
	if(!m_nNodeDone || !m_bDragOn) 
	{
		///////////////////////////////////////
	    MouseWIC = GetMouseWIC();
	    SetMouseOldWIC(MouseWIC);
	    /////////////////////////
	    LPOINT Lpoint;
	    Lpoint.x = (long)point.x;
	    Lpoint.y = (long)point.y;
	    ////////////////////
	    LOGtoWIC(&MouseWIC,&Lpoint);                 
	    SetMouseWIC(MouseWIC);
	 }
   
}

CDrObject* CNodMouAX::GetObjectFromID(CString& ID, int nObjType)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
	/////////////////////////////////////////////////////////
	int index = pObjectMgr->GetObjectIndexfromKey(nObjType,ID,1);
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(nObjType);
	return (CDrObject*)(pDListMgr->GetObject(index));
}

void CNodMouAX::SetMouseWICFromNode(CDrNode* pDrNode,LPOINT3* pMouseWIC)
//void CNodMouAX::SetMouseWICFromNode(CString& NID,LPOINT3* pMouseWIC)
{
//	CDrNode* pDrNode = (CDrNode*)GetObjectFromID(NID, NODE);
	pMouseWIC->x = pDrNode->GetNodeCard()->x;								  	
	pMouseWIC->y = pDrNode->GetNodeCard()->y;								  	
	pMouseWIC->z = pDrNode->GetNodeCard()->z;								  	
}
	
void CNodMouAX:: ElementLeftDown_NOD()
{	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	/////////////////////////////////////////////////////////
//	int nMeshType; 
	/////////////////////
	switch(m_nActiveTool) 
	{
		
		case INODE:
		case CNODE:
		//////////////////////////////////////////////////
		default:
			break;
	}  

}
	
void CNodMouAX::PreLeftUp(CPoint point)
{
	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CAxObjMgr* pObjectMgr  = pDoc->GetAxObjMgr(); 
	///////////////////////////////////////
    LPOINT3 MouseWIC = GetMouseWIC();
    SetMouseOldWIC(MouseWIC);
	//////////////
    LPOINT Lpoint;
    m_pdc->DPtoLP(&point);
    Lpoint.x = (long)point.x;
    Lpoint.y = (long)point.y;
    m_pdc->LPtoDP(&point);							
    ////////////////////
    LOGtoWIC(&MouseWIC,&Lpoint);    // Log/Scaled             
    SetMouseWIC(MouseWIC);
}

int CNodMouAX::ShowNode(CString* pID,BOOL bnid_c,int nHowMany)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	///////////////////////////////////////////////////////////////////////
//	 nHowmany			// Used as an afterthought for creating Node anyway
						// in GangN.CreateNode
						// even if same coords node exists already !!!
						// when nHowmany == -12345
						// Use nNodeIndex of CreateNode to pass the variable
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CAxObjMgr* pObjectMgr  = pDoc->GetAxObjMgr(); 
	////////////////////////////////////////////////////////////////// Save ObjectType/Index
//	UINT nTypeOld			= pObjectMgr->GetActiveObjectType();
//	int nActiveIndexOld		= pObjectMgr->GetActiveObjectIndex();    // for Calling Object
	///////////////////
	if(m_nActiveTool == MCNODE)
		pObjectMgr->SetActiveObjectType(FE0D); 
	else
		pObjectMgr->SetActiveObjectType(NODE);                   
	////////////////////
/*
	if(m_bDialogOn)
	{
		CMNodMgr* pMNodMgr;
		int i;
		/////////////////////////////////////////////////////////////// Using MNodMgr 
		LPOINT3 MouseWIC = GetMouseWIC();
		pID = &m_CurrentNodeID;
		if (pMNodMgr->DoModal_Node(bnid_c,m_nView,&MouseWIC,pID,nHowMany) == IDCANCEL)
			return -1;
		////////////////////////////////////////////////////////// pNode
	   	if(( i= pObjectMgr->GetObjectIndexfromKey(NODE,*pID,1)) <0)
   		{
			AfxMessageBox("ERROR:\nCNodMouAX::ShowNode\nNo Node Index\nInternal Problem");
   			return -1;
   		}	
 		CDListMgr* pDListMgr = pObjectMgr->GetObjectList(NODE);
		m_pCurrentNode = (CDrNode*)pDListMgr->GetObject(i);
	}
	else
	{
*/
	/////////////////////////////////////////////////////////////// Using GangN
	WORLD wPt;
	LPOINT3 MouseWIC = GetMouseWIC();
	///////////////////////////
	WICtoWOR(&MouseWIC,&wPt);	// actually physical (ie bGen = FALSE in CreateNode below)
	///////////////////////////
	int nNodeIndex = nHowMany;
	int nLabelIndex= 0;
	CMI_GangN GangN;
	CMI_Gang0 Gang0;
	////////////////////////////////
	if(m_nActiveTool == MCNODE)
		m_pCurrentNode = Gang0.CreateFE0D(*pID,m_pCurrentLabel, wPt, bnid_c,FALSE,FALSE,
											nNodeIndex,nLabelIndex);// FALSE=Input/TRUE=InternallyGen
	else
		m_pCurrentNode = GangN.CreateNode(*pID,m_pCurrentLabel, wPt, bnid_c,FALSE,FALSE,
										nNodeIndex,nLabelIndex);// FALSE=Input/TRUE=InternallyGen
	m_pCurrentNode->SetCategory(CA_ELEMENT);
	////////////////////////////////////////////////////////////////////// Show
	pObjectMgr->SetActiveObjectIndex(nLabelIndex);		    // set Active Index for Label									
	pObjectMgr->SetActiveObjectType(LABEL);					// set Active ObjectType									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nLabelIndex,LABEL);
	//////////////////////////////////////////////////////////
	pObjectMgr->SetActiveObjectIndex(nNodeIndex);	// set Active Index
	///
	if(bnid_c)
	{
		if(pWnd->GetCurrentIGenID() == MCNODE)
		{
			pObjectMgr->SetActiveObjectType(MCNODE);		    // set Active Type
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nNodeIndex,MCNODE);
		}
		else
		{
			pObjectMgr->SetActiveObjectType(CNODE);		    // set Active Type
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nNodeIndex,CNODE);
		}
	}
	else
	{
		pObjectMgr->SetActiveObjectType(NODE);		    // set Active Type
		pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nNodeIndex,NODE);
	}
	///////////////////////////////
	return 0;
}	 

void CNodMouAX::PostLeft()
{	
	/////////////////////////////// get New MouseWIndowCoord.
	LPOINT3 MouseWIC = GetMouseWIC();
	/////////////////////////////// Set MouseLOGoords.
	LPOINT L_AnchorNodeLOG;
	WICtoLOG(&MouseWIC,&L_AnchorNodeLOG);  // LOG/DEScaled LOG
	m_AnchorNodeLOG.x = (int) L_AnchorNodeLOG.x;
	m_AnchorNodeLOG.y = (int) L_AnchorNodeLOG.y;
	m_pdc->LPtoDP(&m_AnchorNodeLOG);
	//////////////////////////////
	m_MouseLOG    = m_AnchorNodeLOG;
	m_MouseOldLOG = m_MouseLOG;
	///////////////////////////// Set Cursor Position 
	POINT CurLoc = m_MouseLOG;
//	pWnd->ClientToScreen(&CurLoc);
	m_pView->ClientToScreen(&CurLoc);
	::SetCursorPos(CurLoc.x,CurLoc.y); 
	//////////////////////////////////
}

void CNodMouAX::OnEBoxLButtonDown_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
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
	//////////////////////////////////////////////////////// LOG
	m_pdc->DPtoLP(&point);
	//////////////////////////////////////////////////
	m_nActiveObject = pWnd->GetActiveObjectType(); 
	m_nActiveTool	= pWnd->GetActiveToolType();    // -1= INSERT
	/////////////////////////////////////////////////////////////////////////
	pObjectMgr->SetActiveObjectType(m_nActiveObject);       // Set ObjectType 
	////////////////////////////////////////////////// No Node
	if(pWnd->GetCurrentIGenID() == NODE ||pWnd->GetCurrentIGenID() == INODE )
		pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	else
	if(pWnd->GetCurrentIGenID() == CNODE)
		pDListMgr 	= pObjectMgr->GetObjectList(CNODE);
	else
	if(pWnd->GetCurrentIGenID() == MCNODE)
		pDListMgr 	= pObjectMgr->GetObjectList(MCNODE);
	///
	if(pDListMgr->GetCount()<=0)
		return;
	/////////////////////////////////////////////////////////////////
	if(!(pDListMgr->GetSpecificObjectCount(NODE)) ) m_nNodeDone = 0;
	/////////////////////////////////////////////////////////////////
    /////////////////////////////  ELement Dialog On/Off Check
    if(m_Gener == FORWARD)
		ElementLeftDown_NOD();
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftDown_I();
	//////////////////////////////////
}

void CNodMouAX::UpdateNDlg_TRUE()
{
	//////////////////////////////////
	m_pNodInDlg->UpdateData(TRUE); // from screen
	////////////
	m_CurrentNodeID = m_pNodInDlg->m_ObjID;
//	m_CurrentSupID	= m_pNodInDlg->m_SID;
	m_ThirdCoord	= m_pNodInDlg->m_dCoord;
	/////////////////////////////////////
}
			
void CNodMouAX::UpdateNDlg_FALSE()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString str; 
	/////////////////////////////////////////////////////////
	m_pNodInDlg->m_ObjID		= m_CurrentNodeID;
//	m_pNodInDlg->m_SID		= m_CurrentSupID;
	m_pNodInDlg->m_dCoord	= m_ThirdCoord;
	////////////////////////////// CurrStat
	str = "Ready for Selection@";
	if(m_nActiveTool == INODE)
	{
		str += "An Input Node";
		m_pNodInDlg->SetWindowText("INPUT Node");
	}
	else
	if(m_nActiveTool == CNODE || m_nActiveTool == MCNODE)
	{
		str += "A Control Node";
		m_pNodInDlg->SetWindowText("CONTROL Node");
	}
	///
	pWnd->GetCurrStat()->SetText(str);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
	////////////
	m_pNodInDlg->UpdateData(FALSE); // to screen
	////////////////////////////
}
			
int CNodMouAX::LeftUp_NODE(CPoint point,BOOL bCNode)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	///////////////////////////////////////////////////////////////////////
	int nAnyway	= 0;	// Used as an afterthought for creating Node anyway
						// in GangN.CreateNode
						// even if same coords node exists already !!!
						// when nAnyway == -12345
						// Use nHowmany of ShowNode to pass the variable
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CAxObjMgr* pObjectMgr  = pDoc->GetAxObjMgr();
	CMsObjMgr* pMsObjMgr	= pDoc->GetMsObjMgr();
	///
	CDListMgr* pDListMgr;
	if(bCNode)
	{
		if(pWnd->GetCurrentIGenID() == MCNODE)
			pDListMgr	= pObjectMgr->GetObjectList(MCNODE);
		else
			pDListMgr	= pObjectMgr->GetObjectList(CNODE);
	}
	else
		pDListMgr	= pObjectMgr->GetObjectList(NODE);
	///
	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString*	pID;
	CString		ID;
	CDrNode*	pDrNode;
	int			nActiveIndex,index;
	////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	WORtoWOP(&dTol,&dTol);	// physical
	//////////////////////////////////////////////////////////////////
	pID = &m_CurrentNodeID;
	///////////////////////
	int			j;
	WORLD		wLoc;
	BOOL		bNew	= TRUE;
	////////////////////////////////////////////////////////////////// ERROR:User Selected Same ID
	if(	m_nActiveTool == INODE || m_nActiveTool == NODE ||
		m_nActiveTool == CNODE || m_nActiveTool == MCNODE )
	{
		if(m_nActiveTool == INODE || m_nActiveTool == NODE)
			pList	= pObjectMgr->GetObjectList(NODE);
		else
		if(m_nActiveTool == CNODE)
			pList	= pObjectMgr->GetObjectList(CNODE);
		else
		if(m_nActiveTool == MCNODE)
			pList	= pObjectMgr->GetObjectList(MCNODE);
		///
		index	= pList->GetObjectIndex(NODE, *pID); 
		///
		if(index>=0)						// User selected pID
		{
			pDrNode	= (CDrNode*)pList->GetObject(index);
			wLoc	= *(pDrNode->GetLocalPos());
			/////////////////////
			WORtoWOP(&wLoc,&wLoc);			// to Physical
			//////////////////////////////
			CString*	str		= new CString;
			char*		buf		= str->GetBuffer(BUFF_SIZE);
			///////////////
			j = sprintf(buf,"***** Error: A Node with Same ID Exists: *****");
			j += sprintf(buf+j,"\nNodeID = %s\nCoordinates:\n\t X = %f\n\t Y = %f\n\t Z = %f ",
				*pID,wLoc.x,wLoc.y,wLoc.z);
			////////////////////////////
			AfxMessageBox(*str,MB_OK|MB_ICONEXCLAMATION);
			/////////////
			delete str;
			/////////
			return -1;
		}
	}
	////////////////////////////////////////////////////////////// PreExisting Coords?
	///////////////////////////////////////////// See if any Existing Node Hit
	if(m_ProbLim == PDL_TWO)
	{		
		if(bCNode)
		{	
			if(m_nActiveTool == MCNODE)
				index = IsObjectHit(MCNODE,point,0);
			else
				index = IsObjectHit(CNODE,point,0);
		}
		else
			index = IsObjectHit(NODE,point,0);
	}
	else
	if(m_ProbLim == PDL_THREE)
	{
		LPOINT3 MouseWIC;
		//////////
	    LPOINT Lpoint;
	    Lpoint.x = (long)point.x;
	    Lpoint.y = (long)point.y;
	    ////////////////////
	    LOGtoWIC(&MouseWIC,&Lpoint);
		////////
   		wLoc.x 	= (double)(MouseWIC.x);
   		wLoc.y 	= (double)(MouseWIC.y);
   		wLoc.z 	= (double)(MouseWIC.z);
		////////////////
/*
		if(bCNode)
			index = IsObjectHit(CNODE,&wLoc,0);
		else
			index = IsObjectHit(NODE,&wLoc,0);
		///
*/
		if(bCNode)
		{	
			if(m_nActiveTool == MCNODE)
				index = IsObjectHit(MCNODE,&wLoc,0);
			else
				index = IsObjectHit(CNODE,&wLoc,0);
		}
		else
			index = IsObjectHit(NODE,&wLoc,0);
	}
	/////////////////////////////////////////////////////////////// Right Type
	if(index>=0)						
	{
		bNew = FALSE;
		/////////////
		CDrNode* pDrNode	= (CDrNode*)pDListMgr->GetObject(index);
		ID					= pDrNode->GetObjectID();
		/////////////////////////////////////////////
		if(bCNode)
		{
			if(m_nActiveTool == MCNODE)
			{
				pList = pObjectMgr->GetObjectList(MCNODE);
				nActiveIndex = pList->GetObjectIndex(MCNODE, ID);
				pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
				pObjectMgr->SetActiveObjectType(MCNODE);		    // set Active Type									
				pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,MCNODE);
			}
			else
			{
				pList = pObjectMgr->GetObjectList(CNODE);
				nActiveIndex = pList->GetObjectIndex(CNODE, ID);
				pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
				pObjectMgr->SetActiveObjectType(CNODE);		    // set Active Type									
				pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CNODE);
			}
		}
		else
		{
			pList = pObjectMgr->GetObjectList(NODE);
			nActiveIndex = pList->GetObjectIndex(NODE, ID);
			pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
			pObjectMgr->SetActiveObjectType(NODE);		    // set Active Type									
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,NODE);
		}
		//////////////////////////////////////////////////////////////// MultipleSearch
		int startIndex = index+1;
		/////////////////////////
		if(!m_bAutoAcceptOn)
		{
			/////////////
			for(;;)
			{
				CString* str = new CString;
				char* buf = str->GetBuffer(BUFF_SIZE);
				/////////////
				int j;
				/////////////////////////////// Coords
				WORLD Loc = *(pDrNode->GetLocalPos());
				WORtoWOP(&Loc,&Loc);	// to Physical
				//////////////////////////////
				j = sprintf(buf,"***** A Node Already Exists ****\n");
				j += sprintf(buf+j,"with Similar Coordinates (with %f Tolerance):",dTol);
				j += sprintf(buf+j,"\nExisting NodeID = %s\nCoordinates:\n\t X = %f\n\t Y = %f\n\t Z = %f\n",
					ID,Loc.x,Loc.y,Loc.z);
				//////////////////////////
				WORLD wPt;
				WORtoWOP(&wLoc,&wPt);	// to Physical
				//////////////////////////////
				j += sprintf(buf+j,"\nCurrent NodeID = %s\nCoordinates:\n\t X = %f\n\t Y = %f\n\t Z = %f ",
					*pID,wPt.x,wPt.y,wPt.z);
				////////////////////////////
				j += sprintf(buf+j,
					"\n\nYES:\t\tAccept This Existing (C)Node");
				j += sprintf(buf+j,
					"\nNO:\t\tFind Next Matching (C)Node");
				j += sprintf(buf+j,
					"\nCANCEL:\t\tCreate A New (C)Node Anyway");
				////////////////////////////
				int nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
				/////////////
				if(nResult == IDYES)
				{
					//////////////////////////////////////////////////////// Accept Old
					bNew = FALSE;
					/////////////
					delete str;
					break;
				}
				else
				if(nResult == IDNO)
				{
					//////////////////////////////////////////////////////// Retry
					if(m_ProbLim == PDL_TWO)
					{		
						if(bCNode)
						{
							if(m_nActiveTool == MCNODE)
								index = IsObjectHit(MCNODE,point,startIndex);
							else
								index = IsObjectHit(CNODE,point,startIndex);
						}
						else
							index = IsObjectHit(NODE,point,startIndex);
					}
					else
					if(m_ProbLim == PDL_THREE)
					{
/*
						////////////////
						if(bCNode)
							index = IsObjectHit(CNODE,&wLoc,0);
						else
							index = IsObjectHit(NODE,&wLoc,0);
						///
*/
						if(bCNode)
						{
							if(m_nActiveTool == MCNODE)
								index = IsObjectHit(MCNODE,&wLoc,startIndex);
							else
								index = IsObjectHit(CNODE,&wLoc,startIndex);
						}
						else
							index = IsObjectHit(NODE,&wLoc,startIndex);
					}
					/////////////////////////////////////////////////////////////// Right Type
					if(index>=0)
					{
						pDrNode	= (CDrNode*)pDListMgr->GetObject(index);
						ID		= pDrNode->GetObjectID();
						/////////////////////////////////////////////
						if(bCNode)
						{
							if(m_nActiveTool == MCNODE)
							{
								pList = pObjectMgr->GetObjectList(MCNODE);
								nActiveIndex = pList->GetObjectIndex(MCNODE, ID);
								pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
								pObjectMgr->SetActiveObjectType(MCNODE);		    // set Active Type									
								pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,MCNODE);
							}
							else
							{
								pList = pObjectMgr->GetObjectList(CNODE);
								nActiveIndex = pList->GetObjectIndex(CNODE, ID);
								pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
								pObjectMgr->SetActiveObjectType(CNODE);		    // set Active Type									
								pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CNODE);
							}
						}
						else
						{
							pList = pObjectMgr->GetObjectList(NODE);
							nActiveIndex = pList->GetObjectIndex(NODE, ID);
							pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
							pObjectMgr->SetActiveObjectType(NODE);		    // set Active Type									
							pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,NODE);
						}
						////////////////////////////////////////
						startIndex  = index+1;
						/////////////////////
					}
					else
					{
						////////////////
//						m_nNodeDone--;
						delete str;
						return -2;
					}
					/////////
				}
				else				// Cancel
				{
					//////////////////////////////////////////////////////// Create New
					bNew	= TRUE;
					nAnyway	= -12345;	// Create Anyway
					/////////////
					delete str;
					break;
				}
			}						// end for loop
			///////////////////////////////////////
		}				// end !AutoAccept loop
		//////////////////////////////////
		if(!bNew)
		{
			////////////////////
			if(bCNode)
			{
				if(m_nActiveTool == MCNODE)
					pDListMgr = pObjectMgr->GetObjectList(MCNODE);
				else
					pDListMgr = pObjectMgr->GetObjectList(CNODE);
			}	
			else
				pDListMgr = pObjectMgr->GetObjectList(NODE);
			///
			m_pCurrentNode			= (CDrNode*)pDListMgr->GetObject(index);
			m_CurrentNodeID			= m_pCurrentNode->GetObjectID();
			m_CurrentNodeIDOld		= m_pCurrentNode->GetObjectID();
			m_AnchorNodeID			= m_CurrentNodeIDOld;
			m_bAnchorCNode			= bCNode;
			/////////////////////////////////////////////
			return 0;
		}
	}			// end Index loop
	else		// NewNode	of Curve, Patch or Solid etc
	{
		if((m_nActiveTool != INODE) && (m_nActiveTool != CNODE) && (m_nActiveTool != MCNODE))
		{
			/// Bump ID if Not User or Blank
			/////////////////////////////////////////////////////////////////
//			if(*pID == "" || (*pID == m_CurrentNodeIDOld) )
			if(*pID == "")
			{
/*012798
				char buf[50];
				/////////////
				if(bCNode)
				{
					if(m_nActiveTool == MCNODE)
					{
						pMsObjMgr->BumpLastMeshNo(MCNODE);		// bump it
						int nLastNum = pMsObjMgr->GetLastMeshNo(MCNODE);		// internal
						sprintf(buf,"%d",nLastNum);
						m_CurrentNodeID = "MC_";
						m_CurrentNodeID	+= buf;
//						pObjectMgr->BumpLastInputNo(CNODE);		// bump it
					}
					else
					{
						pObjectMgr->BumpLastInputNo(CNODE);		// bump it
						int nLastNum = pObjectMgr->GetLastInputNo(CNODE);		// internal
						sprintf(buf,"%d",nLastNum);
						m_CurrentNodeID = "CN_";
						m_CurrentNodeID	+= buf;
//						pObjectMgr->BumpLastInputNo(CNODE);		// bump it
					}
				}
				else
				{
					pObjectMgr->BumpLastInputNo(NODE);		// bump it
					int nLastNum = pObjectMgr->GetLastInputNo(NODE);		// internal
					sprintf(buf,"%d",nLastNum);
					m_CurrentNodeID = "";
					m_CurrentNodeID	+= buf;
//					pObjectMgr->BumpLastInputNo(NODE);		// bump it
				}
				////////////
				m_CurrentNodeIDOld	= m_CurrentNodeID;
				m_AnchorNodeID		= m_CurrentNodeIDOld;
				m_bAnchorCNode		= bCNode;
*/
				///////////////////////////////////////////////////////////////// 
				pID = &m_CurrentNodeID;
				///////////////////////
			}
		}
	}
	////////////////////////////////////////////////////////////////////////////// New Node
	if(!m_bAutoAcceptOn)
	{
		CString*	str		= new CString;
		char*		buf		= str->GetBuffer(BUFF_SIZE);
		//////////////////////////
		WORLD wPt;
		WORtoWOP(&wLoc,&wPt);	// to Physical
		//////////////////////////////
		j = sprintf(buf,
			"***** New Node Selection: *****\nNodeID = %s\nCoordinates:\n\tX = %f\n\tY = %f\n\tZ = %f ",
			*pID,wPt.x,wPt.y,wPt.z);
		j += sprintf(buf+j,"\n\nAccept This New Node?");
		////////////////////////////
		int nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
		/////////////
		if(nResult == IDYES)
		{
			///////////
			delete str;
		}
		else
		{
			////////////////
			delete str;
			return -2;
		}
	}
	//////////////////////////////////
	if(ShowNode(pID,bCNode,nAnyway)<0)
	{
		AfxMessageBox("ERROR:\nCNodMouAX::LeftUp_Node\nShowNode Problem");
		return -1;
	}
	////////////////////////// Set NodeID
	m_CurrentNodeIDOld	= *pID;
	m_AnchorNodeID		= m_CurrentNodeIDOld;
	m_bAnchorCNode		= bCNode;
	///
/*012798
	if((m_nActiveTool == INODE) || (m_nActiveTool == CNODE) || (m_nActiveTool == MCNODE))
	{
*/
		/////////////
		char buf[50];
		/////////////
		if(bCNode)
		{
			if(m_nActiveTool == MCNODE)
			{
				pMsObjMgr->BumpLastMeshNo(MCNODE);		// bump it
				int nLastNum = pMsObjMgr->GetLastMeshNo(MCNODE);		// internal
				sprintf(buf,"%d",nLastNum);
				m_CurrentNodeID = "MC_";
				m_CurrentNodeID	+= buf;
//				pObjectMgr->BumpLastInputNo(CNODE);		// bump it
			}
			else
			{
				pObjectMgr->BumpLastInputNo(CNODE);		// bump it
				int nLastNum = pObjectMgr->GetLastInputNo(CNODE);		// internal
				sprintf(buf,"%d",nLastNum);
				m_CurrentNodeID = "CN_";
				m_CurrentNodeID	+= buf;
//				pObjectMgr->BumpLastInputNo(CNODE);		// bump it
			}
		}
		else
		{
			pObjectMgr->BumpLastInputNo(NODE);		// bump it
			int nLastNum = pObjectMgr->GetLastInputNo(NODE);		// internal
//			if(nLastNum == 0)
//				pObjectMgr->BumpLastInputNo(NODE);		// bump it (fudge)!
//			nLastNum = pObjectMgr->GetLastInputNo(NODE);		
//			////
			sprintf(buf,"%d",nLastNum);
			m_CurrentNodeID = "";
			m_CurrentNodeID	+= buf;
//			pObjectMgr->BumpLastInputNo(NODE);		// bump it
		}
		////////////
/*012798
	}
*/
	////////////////////////////
	return 0;
}

void CNodMouAX::UpdateADlg_TRUE()
{
	/////////////////////////////////////////////////////
	//		FOR NODE, GRAB NODE = TARGET NODE
	//		SO case 1 below should be taken out,
	//		we kept it for CURVE, PATCH & SOLID		todo
	/////////////////////////////////////////////////////
	GetNodInDlg()->UpdateData(TRUE); // from screen
	//////////////////////////////
	m_bDirect		= GetNodInDlg()->m_bDirect;	
	m_bDominant		= GetNodInDlg()->m_bDominant;
	m_bIncrement	= GetNodInDlg()->m_bIncrement;
	m_bDirection	= GetNodInDlg()->m_bDirection;
	//////
	m_SpawnedNodeID	= GetNodInDlg()->m_ObjID;
	m_ObjID			= m_SpawnedNodeID;
	//////////////////////////////////
	m_X				= GetNodInDlg()->m_X;
	m_Y				= GetNodInDlg()->m_Y;
	m_Z				= GetNodInDlg()->m_Z;
	m_NID			= m_CurrentNodeID;
	m_dLength		= GetNodInDlg()->m_Z;
	////////////////////////
}			

void CNodMouAX::UpdateDlg_TRUE_ADVANCE()
{
	UpdateADlg_TRUE();
	/////////////////////////////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:		// m_RotPt ( Grab Pt.)
			//////////
			m_bDirect	= GetNodInDlg()->m_bDirect;	// both for Translation & Rotation & Reflection
			m_bDominant	= GetNodInDlg()->m_bDominant;
			if(m_bDirect)
			{
				if(m_bDominant)
				{
					m_X = GetNodInDlg()->m_X;
					m_Y = GetNodInDlg()->m_Y;
					m_Z = GetNodInDlg()->m_Z;
					/////////////////////////
					m_wRefPt.x	= m_X;
					m_wRefPt.y	= m_Y;
					m_wRefPt.z	= m_Z;		// also for other Coord
				}
				else
				{
					// Need Clicking Pt. for x & y
					m_Z				= GetNodInDlg()->m_Z;
					m_ThirdCoord	= m_Z;
				}
			}
			else
				;// Hit Node; 
			break;
		case 1:		// FromID or Coords for FromPt.			// Angle In or Reference Line 
			m_bDirect		= GetNodInDlg()->m_bDirect;	// 
			m_bDominant		= GetNodInDlg()->m_bDominant;
			m_bIncrement	= GetNodInDlg()->m_bIncrement;	// 
			//////////////
			if(m_bIncrement)						// Increment			
			{
				m_X			= GetNodInDlg()->m_X;
				m_Y			= GetNodInDlg()->m_Y;
				m_Z			= GetNodInDlg()->m_Z;
				/////////////////////////
				m_wInc.x	= m_X;
				m_wInc.y	= m_Y;
				m_wInc.z	= m_Z;		// also for other Coord
				////////
				return;
			}
			else								// Parallel
			if(m_bDirect)
			{
				if(m_bDominant)
				{
					m_X = GetNodInDlg()->m_X;
					m_Y = GetNodInDlg()->m_Y;
					m_Z = GetNodInDlg()->m_Z;
					/////////////////////////
					m_wFrom.x = m_X;
					m_wFrom.y = m_Y;
					m_wFrom.z = m_Z;
				}
				else
				{
					// Need Clicking Pt. for x & y
					m_Z				= GetNodInDlg()->m_Z;
					m_ThirdCoord	= m_Z;
				}
			}
			else
				;// Hit Node; 
			break;
		case 2:		// ToID or Coords for ToPt.				// Reference Line
			if(m_bIncrement)
				break;
			//////
			m_bDirect	= GetNodInDlg()->m_bDirect;	// 
			m_bDominant	= GetNodInDlg()->m_bDominant;
			///////
			if(m_bDirect)
			{
				if(m_bDominant)
				{
					m_X = GetNodInDlg()->m_X;
					m_Y = GetNodInDlg()->m_Y;
					m_Z = GetNodInDlg()->m_Z;
					/////////////////////////
					m_wTo.x = m_X;
					m_wTo.y = m_Y;
					m_wTo.z = m_Z;
				}
				else
				{
					// Need Clicking Pt. for x & y
					m_Z				= GetNodInDlg()->m_Z;
					m_ThirdCoord	= m_Z;
				}
			}
			else
				;// Hit Node; 
			break;
		default:
			break;
	}
}

void CNodMouAX::UpdateADlg_FALSE()
{
	m_bDlgExpect = FALSE;
	////////////////////////////////////////////////////////////
	//		m_bDirect = FALSE implies m_bDominant = FALSE
	////////////////////////////////////////////////////////////	
	//	if:
	//		1. m_bDirect = TRUE & m_bDominant = FALSE:
	//		/////////////////////////////////////
	//			Node Third Coord from DialogBox
	//			Node Other Two Coord from Mouse Click
	////////////////////////////////////////////////////////////	
	//		2. m_bDirect = TRUE & m_bDominant = TRUE:
	//		/////////////////////////////////////
	//			Node ALL Coord from DialogBox
	////////////////////////////////////////////////////////////
	//		3. m_bDirect = FALSE & m_bDominant = FALSE:
	//		/////////////////////////////////////
	//			Node Obtained from Mouse Search
	////////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////////////////////////////////////////////////////
	GetNodInDlg()->GetDlgItem(IDC_XHEAD)->SetWindowText("");
	GetNodInDlg()->GetDlgItem(IDC_YHEAD)->SetWindowText("");
	GetNodInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("");
	GetNodInDlg()->GetDlgItem(IDC_TRANHEAD)->SetWindowText("");
	GetNodInDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("");
	GetNodInDlg()->GetDlgItem(IDC_INCREMENT)->SetWindowText("");
	GetNodInDlg()->GetDlgItem(IDC_INCREMENT)->EnableWindow(FALSE);
	GetNodInDlg()->GetDlgItem(IDC_DIRECTION)->SetWindowText("");
	GetNodInDlg()->GetDlgItem(IDC_DIRECTION)->EnableWindow(FALSE);
	GetNodInDlg()->GetDlgItem(IDC_DIRECT)->SetWindowText("");
	GetNodInDlg()->GetDlgItem(IDC_DIRECT)->EnableWindow(FALSE);
	GetNodInDlg()->GetDlgItem(IDC_DOMINANT)->SetWindowText("");
	GetNodInDlg()->GetDlgItem(IDC_DOMINANT)->EnableWindow(FALSE);
	///////
//	GetNodInDlg()->GetDlgItem(IDC_OBJID)->EnableWindow(FALSE);
	///////
	GetNodInDlg()->GetDlgItem(IDC_TRANPT)->EnableWindow(FALSE);
	GetNodInDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(FALSE);
	GetNodInDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(FALSE);
	GetNodInDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(FALSE);
	//////////////////////////////////////////
	if(m_bAdvanced)
	{
		GetNodInDlg()->m_ObjID			= m_ObjID;
		GetNodInDlg()->m_NID			= m_CurrentNodeID;
		GetNodInDlg()->m_X				= m_X;
		GetNodInDlg()->m_Y				= m_Y;
		GetNodInDlg()->m_Z				= m_Z;
		///////////////////
		GetNodInDlg()->GetDlgItem(IDC_DIRECT)->SetWindowText("Direct");
		GetNodInDlg()->GetDlgItem(IDC_DIRECT)->EnableWindow(TRUE);
		GetNodInDlg()->GetDlgItem(IDC_DOMINANT)->SetWindowText("Dominant");
		GetNodInDlg()->GetDlgItem(IDC_DOMINANT)->EnableWindow(TRUE);
		GetNodInDlg()->GetDlgItem(IDC_DIRECTION)->SetWindowText("Direction");
		GetNodInDlg()->GetDlgItem(IDC_DIRECTION)->EnableWindow(TRUE);
		GetNodInDlg()->GetDlgItem(IDC_INCREMENT)->SetWindowText("Increment");
		GetNodInDlg()->GetDlgItem(IDC_INCREMENT)->EnableWindow(TRUE);
		///////////////////
		if(m_nInfoDone>=1)
		{
			GetNodInDlg()->GetDlgItem(IDC_INCREMENT)->EnableWindow(FALSE);
			GetNodInDlg()->GetDlgItem(IDC_DIRECTION)->EnableWindow(FALSE);
			GetNodInDlg()->GetDlgItem(IDC_TRANHEAD)->SetWindowText("Ref. Node");
		}


		/////////
		if((m_nInfoDone >=3) && m_bDirection)	// for Length Input in Direction
		{
//			GetNodInDlg()->GetDlgItem(IDC_OBJID)->EnableWindow(FALSE);
			GetNodInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Length");
			GetNodInDlg()->GetDlgItem(IDC_OTHER)->EnableWindow(TRUE);
			GetNodInDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("value");
			GetNodInDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
		}
	}
}

void CNodMouAX::UpdateDlg_FALSE_ADVANCE()
{
	///////////////////
	UpdateADlg_FALSE();
	///////////////////
	if(!m_bAdvanced)
		return;
	///////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////////////////////////////////////////////////////
	strCurr = "Advanced Node Creation: ";
	///////////////////
	switch(m_nInfoDone)
	{
		case 0:		// Reference Node
			////////////////////////////
			if(GetNodInDlg()->m_bDirect)
			{
				////////////////////
				GetNodInDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
				/////
				if(GetNodInDlg()->m_bDominant) // Dialog Input Dominant over Mouse
				{
					m_bDlgExpect = TRUE;
					////////////////////
					GetNodInDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coords");
					strCurr += "TYPE in@Reference Node Coords. in Dialog Box";
					///////
					GetNodInDlg()->GetDlgItem(IDC_XHEAD)->SetWindowText("X");
					GetNodInDlg()->GetDlgItem(IDC_YHEAD)->SetWindowText("Y");
					GetNodInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
					GetNodInDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(TRUE);
					GetNodInDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(TRUE);
				}
				else
				{
					strCurr += "CLICK in@Reference Node Coords.";
					///////
					GetNodInDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coord");
					GetNodInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Third");
				}
			}
			else
				strCurr += "CLICK On@ A Reference Node or Control Node";
			break;
		case 1:			// Either Incremental Coord Value (Direct) or Direction Cosine Nodes 	
			//////
			if(GetNodInDlg()->m_bIncrement)	// Incremental
			{
				m_bDirect	= TRUE;
				m_bDominant = TRUE;			// force DialogBox
				GetNodInDlg()->m_bDirect	= m_bDirect;
				GetNodInDlg()->m_bDominant	= m_bDominant;
				////////////////////
				m_bDlgExpect = TRUE;
				///
				GetNodInDlg()->GetDlgItem(IDC_DIRECTION)->EnableWindow(FALSE);
				GetNodInDlg()->GetDlgItem(IDC_INCREMENT)->EnableWindow(FALSE);
//				GetNodInDlg()->GetDlgItem(IDC_DIRECT)->EnableWindow(FALSE);
//				GetNodInDlg()->GetDlgItem(IDC_DOMINANT)->EnableWindow(FALSE);
				//////////////////
				GetNodInDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
				GetNodInDlg()->GetDlgItem(IDC_TRANHEAD)->SetWindowText(""); // Grab At
				/////
				strCurr += "TYPE in@Incremental Coords in Dialog Box";
				///////
				GetNodInDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("values");
				GetNodInDlg()->GetDlgItem(IDC_XHEAD)->SetWindowText("DX");
				GetNodInDlg()->GetDlgItem(IDC_YHEAD)->SetWindowText("DY");
				GetNodInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("DZ");
				GetNodInDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(TRUE);
				GetNodInDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(TRUE);
			}
			else	// Not Direct Coords, So Axis Nodes
			{
				//////////////////
				if(GetNodInDlg()->m_bDirect)
				{
					////////////////////
					GetNodInDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
					/////
					if(GetNodInDlg()->m_bDominant) // Dialog Input Dominant over Mouse
					{
						m_bDominant = TRUE;
						////////////////////////
						m_bDlgExpect = TRUE;
						////////////////////
						strCurr += "TYPE in@Axis Node_From Coords in Dialog Box";
						///////
						GetNodInDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coords");
						GetNodInDlg()->GetDlgItem(IDC_XHEAD)->SetWindowText("X");
						GetNodInDlg()->GetDlgItem(IDC_YHEAD)->SetWindowText("Y");
						GetNodInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
						GetNodInDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(TRUE);
						GetNodInDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(TRUE);
					}
					else
					{
						strCurr += "CLICK in@Axis Node_From Coords.";
						///////
						GetNodInDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coord");
						GetNodInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Third");
					}
				}
				else	// Node Input
					strCurr += "CLICK in@Axis_defining Ist Node or CNode";
					///////
			}
			break;
		case 2:
			GetNodInDlg()->GetDlgItem(IDC_INCREMENT)->EnableWindow(FALSE); // Now On
			if(m_bIncrement)
			{
				strCurr = "Ready with other Info.?@Click Right Button";
				break;
			}
			//////////////////
			if(GetNodInDlg()->m_bDirect)
			{
				////////////////////
				GetNodInDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
				/////
				if(GetNodInDlg()->m_bDominant) // Dialog Input Dominant over Mouse
				{
					m_bDominant = TRUE;
					m_bDirect	= TRUE;
					////////////////////////
					m_bDlgExpect = TRUE;
					////////////////////
					strCurr += "TYPE in@Axis Node_To Coords in Dialog Box";
					///////
					GetNodInDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coords");
					GetNodInDlg()->GetDlgItem(IDC_XHEAD)->SetWindowText("X");
					GetNodInDlg()->GetDlgItem(IDC_YHEAD)->SetWindowText("Y");
					GetNodInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
					GetNodInDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(TRUE);
					GetNodInDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(TRUE);
				}
				else
				{
					strCurr += "CLICK in@Axis Node_To Coords.";
					///////
					GetNodInDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coord");
					GetNodInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Third");
				}
			}
			else	// Node Input
				strCurr += "CLICK in@Axis_defining 2nd Node or CNode";
				///////
			break;
		case 3:
			strCurr = "Ready with other Info.?@Click Right Button";
			GetNodInDlg()->GetDlgItem(IDC_DIRECT)->EnableWindow(FALSE);
			GetNodInDlg()->GetDlgItem(IDC_DOMINANT)->EnableWindow(FALSE);
			GetNodInDlg()->GetDlgItem(IDC_OBJID)->EnableWindow(TRUE);
			break;
		default:
			return;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->SetText(strCurr);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
	////////////////////////////////////////////////
	GetNodInDlg()->UpdateData(FALSE); // To screen
	////////////////////////////////////////////////
}

int CNodMouAX::LeftUp_GetNode(POINT point, BOOL bCNode)
{
	int nResult;
	///////////////////////////////////////////// See if any Existing Node Hit
	nResult = LeftUp_Node_Accept(point,bCNode,FALSE);	// FALSE = NOT Parent
	/////////////////////////////////////////////   
	if(nResult>=0)									// Hit(0)
		m_wLoc 	= *(m_pCurrentNode->GetLocalPos());
	else											// Not Hit(-1) or Cancel(-2)	
	{
		m_pCurrentNode = NULL;
		//////////////////////
		if(m_ProbLim == PDL_TWO) 
			m_ThirdCoord = 0.0;
		////////////////////////
		LPOINT3 MouseWIC;
		//////////
		LPOINT Lpoint;
		Lpoint.x = (long)point.x;
		Lpoint.y = (long)point.y;
		////////////////////
		LOGtoWIC(&MouseWIC,&Lpoint);
		////////
		m_wLoc.x 	= (double)(MouseWIC.x);
		m_wLoc.y 	= (double)(MouseWIC.y);
		m_wLoc.z 	= (double)(MouseWIC.z);
	}
	/////////
	return nResult;	
}

int CNodMouAX::LeftUp_GetNode_ADVANCE(POINT point, BOOL bCNode)
{
	int nResult = LeftUp_GetNode(point, bCNode);
	///////////////////
	if(nResult == -2)
		return nResult; // Cancel
	///////
	if(nResult>=0)	// Hit
	{
		switch(m_nInfoDone)
		{
			case 0:
				m_RefPtID	= m_pCurrentNode->GetObjectID();
				m_wRefPt	= *(m_pCurrentNode->GetLocalPos());
				///
				WORtoWOP(&m_wRefPt,&m_wRefPt);// change to physical like in Dlg Input
				break;
			case 1:
				if(m_bIncrement)
					return -1;
				//////////////
				m_FromID		= m_pCurrentNode->GetObjectID();
				m_wFrom		= *(m_pCurrentNode->GetLocalPos());
				WORtoWOP(&m_wFrom,&m_wFrom);// change to physical like in Dlg Input
				break;
			case 2:
				if(m_bIncrement)
					return -1;
				//////////////
				m_ToID		= m_pCurrentNode->GetObjectID();
				m_wTo			= *(m_pCurrentNode->GetLocalPos());
				WORtoWOP(&m_wTo,&m_wTo);// change to physical like in Dlg Input
				break;
			default:
				return -1;
		}
	}
	else	// find from Mouse Coord & Third Coord anyway
	if(m_bCorINodeOpDone)
	{
		///////
		switch(m_nInfoDone)
		{
			case 0:
				m_RefPtID	= "";
				m_wRefPt	= m_wLoc;
				WORtoWOP(&m_wRefPt,&m_wRefPt);// change to physical like in Dlg Input
				break;
			case 1:
				m_FromID		= "";
				m_wFrom		= m_wLoc;
				WORtoWOP(&m_wFrom,&m_wFrom);// change to physical like in Dlg Input
				break;
			case 2:
				m_ToID		= "";
				m_wTo			= m_wLoc;
				WORtoWOP(&m_wTo,&m_wTo);// change to physical like in Dlg Input
				break;
			default:
				return -1;
		}
	}
	else
		return nResult;	// NO Hit
	///////////////////////////////////////// From & To Same,INADMISSIBLE
	if(m_nInfoDone == 2)	// To Node
	{
		C3DMath	Math3D;
		///////////////
		if(Math3D.AreSame_WORLD(&m_wFrom,&m_wTo))
   		{
			AfxMessageBox("Degenerate Reference Line:\nSame Node More than Once!");
			m_nInfoDone--;
			return -2;
		}
	}
	//////////////////////////////////////
	return 0;
}

int CNodMouAX::LeftUp_ADVANCE_NOD(POINT point)
{
	/////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	BOOL bCNode;
	/////////////////////////////////////////////////////////
	if(pWnd->GetCurrentIGenID() == NODE ||pWnd->GetCurrentIGenID() == INODE )
		bCNode = FALSE;
	else
		bCNode = TRUE;
	///
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Ref Node	
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_ADVANCE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_ADVANCE(point,FALSE);		// try INODE
			if(nResult < 0)
				return nResult;
			//
			return 0;
			////////
		case 1://		// From Direction if Not Increment
			if(m_bIncrement)
				return -1;
			//////////////
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_ADVANCE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_ADVANCE(point,FALSE);		// try INODE
			if(nResult < 0)
				return nResult;
			//
			return 0;
			////////
		case 2://		// To Rot Direction
			if(m_bIncrement)
				return -1;
			//////////////
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_ADVANCE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_ADVANCE(point,FALSE);		// try INODE
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

void CNodMouAX::ElementLeftUp_NOD(CPoint point)
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
		
		case INODE:
				
			if(!m_bAdvanced)
			{
				m_nNodeDone = 0;
				////////////////
				UpdateNDlg_TRUE();
				LeftUp_NODE(point,FALSE);		// FALSE = Not CNODE
				UpdateNDlg_FALSE();
				///////
				return;
			}
			else
			{
				if(m_bIncrement)
				{
					if(m_nInfoDone > MAX_INFO_INCREMENT)
						return;
				}
				else
				{
					if(m_nInfoDone > MAX_INFO_DIRECTION)
						return;
				}
				////////////////
				UpdateDlg_TRUE_ADVANCE();
				//////////////////
				if(!(m_bDirect && m_bDominant) )
				{
					if(LeftUp_ADVANCE_NOD(point)<0)
					{
						Terminate_NOD(TRUE);
						return;
					}
				}
				/////////////
				m_nInfoDone++;
				UpdateDlg_FALSE_ADVANCE();
				///////
				return;
			}

				
		case MCNODE:				
		case CNODE:				

				
			if(!m_bAdvanced)
			{
				m_nCNodeDone = 0;
				////////////////
				UpdateNDlg_TRUE();
				LeftUp_NODE(point,TRUE);		// TRUE = CNODE;
				UpdateNDlg_FALSE();
				///////
				return;
			}
			else
			{
				if(m_bIncrement)
				{
					if(m_nInfoDone > MAX_INFO_INCREMENT)
						return;
				}
				else
				{
					if(m_nInfoDone > MAX_INFO_DIRECTION)
						return;
				}
				////////////////
				UpdateDlg_TRUE_ADVANCE();
				//////////////////
				if(!(m_bDirect && m_bDominant) )
				{
					if(LeftUp_ADVANCE_NOD(point)<0)
					{
						Terminate_NOD(TRUE);
						return;
					}
				}
				/////////////
				m_nInfoDone++;
				UpdateDlg_FALSE_ADVANCE();
				///////
				return;
			}
		//////////////////////////////////////////////////
		default:  
			break;
	} 
}	

int CNodMouAX::LeftUp_Node_Accept(CPoint point,BOOL bCNode,BOOL bParent)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CAxObjMgr* pObjectMgr  = pDoc->GetAxObjMgr();
	///
	CDListMgr* pDListMgr;
	if(bCNode)
	{
		if(m_nActiveTool == MCNODE)
			pDListMgr	= pObjectMgr->GetObjectList(MCNODE);
		else
			pDListMgr	= pObjectMgr->GetObjectList(CNODE);
	}	
	else
		pDListMgr	= pObjectMgr->GetObjectList(NODE);
	///
	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrNode*	pDrNode;
	int			nActiveIndex,index;
	////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	WORtoWOP(&dTol,&dTol);	// physical
	//////////////////////////////////////////////////// Check if CorrectType Node/CNode/MNode
	WORLD		wLoc;
	///////////////////////////////////////////// See if any Existing Node Hit
	if(m_ProbLim == PDL_TWO)
	{		
		if(bCNode)
		{
			if(m_nActiveTool == MCNODE)
				index = IsObjectHit(MCNODE,point,0);
			else
				index = IsObjectHit(CNODE,point,0);
		}
		else
			index = IsObjectHit(NODE,point,0);
	}
	else
	if(m_ProbLim == PDL_THREE)
	{
		LPOINT3 MouseWIC;
		//////////
	    LPOINT Lpoint;
	    Lpoint.x = (long)point.x;
	    Lpoint.y = (long)point.y;
	    ////////////////////
	    LOGtoWIC(&MouseWIC,&Lpoint);
		////////
   		wLoc.x 	= (double)(MouseWIC.x);
   		wLoc.y 	= (double)(MouseWIC.y);
   		wLoc.z 	= (double)(MouseWIC.z);
		////////////////
		if(bCNode)
		{
			if(m_nActiveTool == MCNODE)
				index = IsObjectHit(MCNODE,&wLoc,0);
			else
				index = IsObjectHit(CNODE,&wLoc,0);
		}
		else
			index = IsObjectHit(NODE,&wLoc,0);
		///
	}
	/////////////////////////////////////////////////////////////// Right Type
	if(index>=0)						
	{
		/////////////
		pDrNode	= (CDrNode*)pDListMgr->GetObject(index);
		ID		= pDrNode->GetObjectID();
		/////////////////////////////////////////////
		if(bCNode)
		{
			if(m_nActiveTool == MCNODE)
			{
				pList = pObjectMgr->GetObjectList(MCNODE);
				nActiveIndex = pList->GetObjectIndex(MCNODE, ID);
				pObjectMgr->SetActiveObjectIndex(nActiveIndex);		// set Active Index									
				pObjectMgr->SetActiveObjectType(MCNODE);		    // set Active Type									
				pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,MCNODE);
			}
			else
			{
				pList = pObjectMgr->GetObjectList(CNODE);
				nActiveIndex = pList->GetObjectIndex(CNODE, ID);
				pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
				pObjectMgr->SetActiveObjectType(CNODE);		    // set Active Type									
				pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CNODE);
			}
		}
		else
		{
			pList = pObjectMgr->GetObjectList(NODE);
			nActiveIndex = pList->GetObjectIndex(NODE, ID);
			pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
			pObjectMgr->SetActiveObjectType(NODE);		    // set Active Type									
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,NODE);
		}
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
				nResult = ShowNotParentNodeInfo(pDrNode);
				/////////////
				if(nResult == IDYES)
					//////////////////////////////////////////////////////// Accept Old
					break;
				else
				if(nResult == IDNO)
				{
					//////////////////////////////////////////////////////// Retry
					if(m_ProbLim == PDL_TWO)
					{		
						if(bCNode)
						{
							if(m_nActiveTool == MCNODE)
								index = IsObjectHit(MCNODE,point,0);
							else
								index = IsObjectHit(CNODE,point,0);
						}
						else
							index = IsObjectHit(NODE,point,0);
					}
					else
					if(m_ProbLim == PDL_THREE)
					{
						////////////////
						if(bCNode)
						{
							if(m_nActiveTool == MCNODE)
								index = IsObjectHit(MCNODE,&wLoc,0);
							else
								index = IsObjectHit(CNODE,&wLoc,0);
						}
						else
							index = IsObjectHit(NODE,&wLoc,0);
						///
					}
					/////////////////////////////////////////////////////////////// Right Type
					if(index>=0)
					{
						pDrNode	= (CDrNode*)pDListMgr->GetObject(index);
						ID		= pDrNode->GetObjectID();
						/////////////////////////////////////////////
						if(bCNode)
						{
							if(m_nActiveTool == MCNODE)
							{
								pList = pObjectMgr->GetObjectList(MCNODE);
								nActiveIndex = pList->GetObjectIndex(MCNODE, ID);
								pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
								pObjectMgr->SetActiveObjectType(MCNODE);		    // set Active Type									
								pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,MCNODE);
							}
							else
							{
								pList = pObjectMgr->GetObjectList(CNODE);
								nActiveIndex = pList->GetObjectIndex(CNODE, ID);
								pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
								pObjectMgr->SetActiveObjectType(CNODE);		    // set Active Type									
								pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CNODE);
							}
						}
						else
						{
							pList = pObjectMgr->GetObjectList(NODE);
							nActiveIndex = pList->GetObjectIndex(NODE, ID);
							pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
							pObjectMgr->SetActiveObjectType(NODE);		    // set Active Type									
							pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,NODE);
						}
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
	}			// end Index loop
	else
		return -1;	// Not Hit
	//////////////////////////////////////////////////////////////////// finally, accept
	m_pCurrentNode = pDrNode;
	/////////
	return 0;
	/////////
}
	
int CNodMouAX::ShowNotParentNodeInfo(CDrNode* pDrNode)
{
	int nResult;
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	/////////////////////////////// Coords
	j = sprintf(buf,"***** A Node Hit ****\n");
	j = ShowNodeInfo(pDrNode, buf, j);
	////////////////////////////
	j += sprintf(buf+j,
		"\n\nYES:\t\tAccept This Node");
	//////////////////////////
	if(m_ProbLim == PDL_TWO)
	{
		j += sprintf(buf+j,
			"\nNO:\t\tCancel Selection Process");
		nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
		////////////////////
		if(nResult == IDNO)
		{
			delete str;
			return -2;			// cancel: stop Searching
		}
	}
	if(m_ProbLim == PDL_THREE)
	{
		j += sprintf(buf+j,
			"\nNO:\t\tFind Next Node with same Trace");
		j += sprintf(buf+j,
			"\nCANCEL:\t\tCancel Selection Process");
		nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
	}
	///////////////
	delete str;
	return nResult;
}

void CNodMouAX::OnEBoxMouseMove_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CNodMouAX::OnEBoxLButtonUp_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
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
		ElementLeftUp_NOD(Logpoint);
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftUp_I();
	/////////////////
	PostLeft();
	/////////////////////////
	
}

void CNodMouAX::OnEBoxRButtonDown_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
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
	/////////////////////////////////////////////////////////////////////////////
	m_nActiveObject = pWnd->GetActiveObjectType(); 
	m_nActiveTool	= pWnd->GetActiveToolType();    // -1= INSERT
	/////////////////////////////////////////////////////////////////////////
	pObjectMgr->SetActiveObjectType(m_nActiveObject);       // Set ObjectType 
	////////////////////
//	CMNodMgr* pMNodMgr;
	//////////////////////////////////////////
	switch(m_nActiveTool) 
	{
		case INODE:
			break;
		case CNODE:
			break;
		////////////////////////////////////////////////// 
		default:
			break;
	}  
}

int CNodMouAX::RightUp_Premature()
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CAxObjMgr* pObjectMgr  = pDoc->GetAxObjMgr();
	////////////////////////////////////////////////////// 
	int		nAnswer = IDOK;
	BOOL	bPreMature = FALSE;
	//////////////////////////////////////////////////// Check Adequate Node,or cancel
	
	if(m_bIncrement && m_nInfoDone<MAX_INFO_INCREMENT)
		bPreMature = TRUE;
	if(!m_bIncrement && m_nInfoDone<MAX_INFO_DIRECTION)
		bPreMature = TRUE;
	//////////////// PreMature
	if(bPreMature)
		return -1;
	////////
	return 0;
}	

int CNodMouAX::ShowInputInfo_NOD()
{
	///////////////////////////////////////////////////////////// show Info
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	////////////////////
	int j;
	//////////
	j = sprintf(buf,"***** Node Info ******");
	///
	j += sprintf( buf + j, "\n\nNew Node ID = %s\n\n",m_ObjID); // 
	/////////////////////////////////////
	if(m_RefPtID !="")
		j += sprintf( buf + j, "\n\nReference Node ID = %s\n",m_RefPtID); // Ref Node
	else
		j += sprintf( buf + j, "\n\nReference Coords:\n");
	//
	j += sprintf( buf + j, "\n\tX\t= %f",m_wRefPt.x);
	j += sprintf( buf + j, "\n\tY\t= %f",m_wRefPt.y);
	j += sprintf( buf + j, "\n\tZ\t= %f",m_wRefPt.z);
	////
	if(m_bIncrement)
	{
		j += sprintf( buf + j, "\n\nIncrements:\n"); // 
		j += sprintf( buf + j, "\n\tX\t= %f",m_wInc.x);
		j += sprintf( buf + j, "\n\tY\t= %f",m_wInc.y);
		j += sprintf( buf + j, "\n\tZ\t= %f",m_wInc.z);
	}
	else
	{
		//////////////////////////////////////////////////////////// Reference Line
		if(m_FromID != "")
			j += sprintf( buf + j, "\n\nAxis_From Node ID = %s\n",m_FromID); // 
		else
			j += sprintf( buf + j, "\n\nAxis_From Coords:\n");
		//
		j += sprintf( buf + j, "\n\tX\t= %f",m_wFrom.x);
		j += sprintf( buf + j, "\n\tY\t= %f",m_wFrom.y);
		j += sprintf( buf + j, "\n\tZ\t= %f",m_wFrom.z);
		///
		if(m_ToID != "")
			j += sprintf( buf + j, "\n\nAxis_To Node ID = %s\n",m_ToID); // 
		else
			j += sprintf( buf + j, "\n\nAxis_To Coords:\n");
		//
		j += sprintf( buf + j, "\n\tX\t= %f",m_wTo.x);
		j += sprintf( buf + j, "\n\tY\t= %f",m_wTo.y);
		j += sprintf( buf + j, "\n\tZ\t= %f",m_wTo.z);
		///////////////////////////////////////////////////////////////////// Length
		j += sprintf( buf + j, "\n\tLength  = %f",m_dLength);
	}
	///////////////////////////////////////////////////////////////////// Final Coords
	j += sprintf( buf + j, "\n\nFinal Coords: \n"); // 
	//
	j += sprintf( buf + j, "\n\tX\t= %f",m_wFin.x);
	j += sprintf( buf + j, "\n\tY\t= %f",m_wFin.y);
	j += sprintf( buf + j, "\n\tZ\t= %f",m_wFin.z);
	/////////////////////////////////////////////////////////////////////
	if(j>BUFF_SIZE)
	{
		sprintf( buf, "Internal Error:\nIncrease buffer to %d",j);
		AfxMessageBox(*str);
		delete str;
		return -1;
	}	 
	///////////////////////////////////////////////////////////////	
	int nAnswer = AfxMessageBox(*str,MB_OKCANCEL|MB_ICONQUESTION );
	//////
	return nAnswer;
}

int CNodMouAX::ShowNodeInfo(CDrNode* pDrNode, char* buf, int jStart)
{
	CString ID;
	CString* pID = &ID;
	ID = pDrNode->GetObjectID();
	//////////////////////////////
	int j = jStart;
	/////////////////////////////// Coords
	WORLD Loc = *(pDrNode->GetLocalPos());
	WORtoWOP(&Loc,&Loc);	// to Physical
	//////////////////////////////
	j += sprintf(buf+j,
		"\nExisting NodeID = %s\nCoordinates:\n\t X = %f\n\t Y = %f\n\t Z = %f\n",
				ID,Loc.x,Loc.y,Loc.z);
	///
	if(pDrNode->IsControlNode())
		j += sprintf(buf+j,"\nThis is a Control Node\n");
	else
		j += sprintf(buf+j,"\nThis is an Input Node\n");
	/////////
	return j;
}

int CNodMouAX::ResolveReference_Direction()
{
	///////////////////////////////////////////
	WORLD Axis;
	int nResult = UnitAxisFromEndNodes(&Axis);
	if(nResult<0)
		return -1;
	///////////////////////////////////////////
	m_wFin.x = m_wRefPt.x + m_dLength * Axis.x;
	m_wFin.y = m_wRefPt.y + m_dLength * Axis.y;
	m_wFin.z = m_wRefPt.z + m_dLength * Axis.z;
	/////////
	return 0;
}

int CNodMouAX::ResolveReference_Coords()
{
	///////////////////////////////////////////
	m_wFin.x = m_wRefPt.x + m_wInc.x;
	m_wFin.y = m_wRefPt.y + m_wInc.y;
	m_wFin.z = m_wRefPt.z + m_wInc.z;
	/////////
	return 0;
}

int CNodMouAX::UnitAxisFromEndNodes(pWORLD pNormal)
{
	///////////////
	C3DMath	Math3D;
	///////////////////////////////////////////// Vector
	Math3D.Sub3DPts(&m_wTo, &m_wFrom, pNormal);
	Math3D.Normalize(pNormal,pNormal);
	///////////////
	return 0;
}

int CNodMouAX::RightUp_NotAutoAccept()
{
/*
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CAxObjMgr* pObjectMgr  = pDoc->GetAxObjMgr();
	CDListMgr*	pList;
*/
	int nAnswer;
	////////////////////////////////
	if(!m_bAutoAcceptOn)
	{
		///////////////////////////////////////////////////////////// show Info
		nAnswer = ShowInputInfo_NOD();
		if(nAnswer<0)
			return -1;
		//////////////
		if(nAnswer == IDCANCEL)
		{
			CString* str = new CString;
			char* buf	= str->GetBuffer(BUFF_SIZE);
			sprintf(buf,"Do You Want to Delete\nCurrent Node %s to Start Allover");
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

void CNodMouAX::OnEBoxRButtonUp_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
								UINT nFlags, CPoint point)
{
	if(!m_bAdvanced)
		return;
	////////////////
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////////////////////
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
	/////////////////////////////////////////////////////////
	if(pWnd->GetCurrentIGenID() == NODE ||pWnd->GetCurrentIGenID() == INODE )
		m_bCNode = FALSE;
	else
		m_bCNode = TRUE;
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	//////////////////////////////////////////////////////////////////
	CString ID;
	CString* pID = &ID;
	///////////////////////////////////////////////////////// Update Info
	UpdateADlg_TRUE();
	///////////////////////////////////////////////////////// Is Enough Info?
	if(RightUp_Premature()<0)
		return;
	///////////////////////////////////////////////////////// Not Auto Accept
	if(m_bIncrement)
		ResolveReference_Coords();
	else
		ResolveReference_Direction();
	/////////////////////////////////
	if(RightUp_NotAutoAccept()<0)
	{
		Terminate_NOD(TRUE);
		return;
	}
	///////////////////////////////////////////////////// Show Spawned Node 
	int nAnyway	= -12345;	// Create Anyway
	////////////////////////////////////////
	LPOINT3 MouseWIC;
	WORtoWIC(&MouseWIC,&m_wFin);
	SetMouseWIC(MouseWIC);
	////////////////////////////////////////
	switch(m_nActiveTool) 
	{

		case INODE:
						
	
			/////////////////////////////
			if(ShowNode(&m_ObjID,FALSE,nAnyway)<0)
			////////////////
			{
				Terminate_NOD(TRUE);
				return;
			}
			else
			{
				Terminate_NOD(FALSE);
				Init_NOD();
				/////////////////////////
				UpdateADlg_FALSE();
				break;
			}
			///////////////////	
			break;


		case MCNODE:
		case CNODE:
						
			
			/////////////////////////////
			if(ShowNode(&m_ObjID,TRUE,nAnyway)<0)
			////////////////
			{
				Terminate_NOD(TRUE);
				return;
			}
			else
			{
				Terminate_NOD(FALSE);
				Init_NOD();
				/////////////////////////
				UpdateADlg_FALSE();
				break;
			}
			///////////////////	
			break;

			
		
		default:  
			return;
	} 
	////////////////////////////////////////////////////////////////////////
	////////////////////////// Set NodeID
	m_CurrentNodeIDOld	= m_ObjID;
	m_AnchorNodeID		= m_CurrentNodeIDOld;
	m_bAnchorCNode		= m_bCNode;
	///
	char buf[50];
	if(m_bCNode)
	{
		if(m_nActiveTool == MCNODE)
		{
			pMsObjMgr->BumpLastMeshNo(MCNODE);		// bump it
			int nLastNum = pMsObjMgr->GetLastMeshNo(MCNODE);		// internal
			sprintf(buf,"%d",nLastNum);
			m_CurrentNodeID = "MC_";
			m_CurrentNodeID	+= buf;
//			pObjectMgr->BumpLastInputNo(CNODE);		// bump it
		}
		else
		{
			pObjectMgr->BumpLastInputNo(CNODE);		// bump it
		    m_LastNum	= pObjectMgr->GetLastInputNo(CNODE);		// internal
			sprintf(buf,"%d",m_LastNum);
			m_SpawnedNodeID	= "CN_";
			m_SpawnedNodeID	+= buf;
		}
	}
	else
	{
		pObjectMgr->BumpLastInputNo(NODE);		// bump it
	    m_LastNum	= pObjectMgr->GetLastInputNo(NODE);		// internal
		sprintf(buf,"%d",m_LastNum);
		m_SpawnedNodeID	= "";
		m_SpawnedNodeID	+= buf;
	}
	//////////////////////////
	m_ObjID = m_SpawnedNodeID; 
	///////////////////////////////////////////////////////////// Advanced Option
	GetNodInDlg()->GetDlgItem(IDC_ADVANCED)->EnableWindow(TRUE);
	//////////////////////////
	UpdateADlg_FALSE();
	GetNodInDlg()->UpdateData(FALSE);
	////////////////////////////////////////////////////////////////////////
	strCur = "Ready for Another Node Creation. CLICK ON@";
	strCur += "A Reference Node or Control Node";
	///
	pWnd->GetCurrStat()->SetText(strCur);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
	////////////
}
/////////////////////////////////////////////////////////////////////////////////////// F_M
UINT CNodMouAX::ReSetToolID_NOD(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	///////////////////////////////////
	if(IGenID == NODE)
		//////////////////////////////////////////// TaskID
		strCur = "Ready for Creation@";
	else
	if(IGenID == INODE)
		//////////////////////////////////////////// TaskID
		strCur = "Ready for Input Node Creation@";
	else
	if(IGenID == CNODE || IGenID == MCNODE)
		//////////////////////////////////////////// TaskID
		strCur = "Ready for Control Node Creation@";
	else
	{
		str = "UNKNOWN";	ID	= UNONE;
		pWnd->SetstrIGenID(str);
		////////////////////////
		return UNONE;
	}
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
						case NODE:			str = "NODE";		ID	= NODE;
								strCur += "Select Node Type";	break;
						case INODE:			str = "Input@NODE";		ID	= INODE;
								strCur += "Click in an Input Node";	break;
						case CNODE:			str = "Control@NODE";	ID = CNODE;
								strCur += "Click in a Control Node";	break;
						case MCNODE:		str = "Control@NODE";	ID = MCNODE;
								strCur += "Click in a Control Node";	break;
						default:			str = "UNKNOWN@NODE";	ID = UNONE;
					}
					pWnd->SetstrIGenID(str);
					////////////////////////
					pWnd->SetstrCurrID(strCur);
					//////////
					return ID;
				//////////////////
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
	
void CNodMouAX::ModeLessOff_NOD()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	if(GetNodInDlg()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_NODIN,IDOK);
}

void CNodMouAX::ModeLessOn_NOD()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	int aTool	= pWnd->GetActiveToolType();
	int aObj	= pWnd->GetActiveObjectType();
	/////////////////////////////////////////////////////////////////////////
	if
	(	
		(aTool == INODE) ||(aTool == CNODE) ||(aTool == MCNODE)
	)
	{
		if(!(GetNodInDlg()->m_hWnd))
			pWnd->SendMessage(ID_ACTIVE_NODIN,IDOK);
/*
		/////////////////////////////////////// Other Coords
		if(GetNodInDlg()->m_hWnd)
		{
			CStatic* pCtl;
			pCtl = (CStatic*)GetNodInDlg()->GetDlgItem(IDC_OTHER);
			if(pWnd->GetActiveViewNumber() == VIEW12)
				pCtl->SetWindowText("Z");
			else
			if(pWnd->GetActiveViewNumber() == VIEW23)
				pCtl->SetWindowText("X");
			else
			if(pWnd->GetActiveViewNumber() == VIEW31)
				pCtl->SetWindowText("Y");
		}
*/
	}
}

long CNodMouAX::CreateorActivateNodIn(UINT wParam, long lParam)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
//	CString strCurr;
	/////////////////////////////////////////////////////////
	if(	(pWnd->GetCurrentIGenID() != INODE) && (pWnd->GetCurrentIGenID() != CNODE)
											&& (pWnd->GetCurrentIGenID() != MCNODE) )
		return 0L;
	////////////////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	//////////////////////////////////////////////////////////////////
	if(GetNodInDlg()->GetSafeHwnd() ==0)	// not created already
	{
		GetNodInDlg()->Create();
		//////////////////////
		CRect BoxRect;
		CWnd  wndTopMost;
		GetNodInDlg()->GetWindowRect(&BoxRect);
		SizeRectDlgIn(BoxRect);
		//////////////////////////////
		GetNodInDlg()->SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
                        BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
		//////////////////////////////////////////////////////////////
//		Init_NOD();
	}
	else
		GetNodInDlg()->SetActiveWindow();
	/////////////////////////////////////////////////////////////////
	CDListMgr* pDListMgr;
	///
	char buf[50];
	/////////////
	if(pWnd->GetCurrentIGenID() == CNODE)
	{
		pDListMgr = pObjectMgr->GetObjectList(CNODE);
		m_pNodInDlg->SetWindowText("CONTROL Node");
		int nLastNum = pObjectMgr->GetLastInputNo(CNODE);		// internal
		sprintf(buf,"%d",nLastNum);
		m_CurrentNodeID = "CN_";
		m_CurrentNodeID	+= buf;
		m_bAnchorCNode	= TRUE;
		////////////////////////////////////////////////// Not Ist Time
//		if( !pDListMgr->IsEmpty() )
//			pObjectMgr->BumpLastInputNo(CNODE);		// bump it
	}
	else
	if(pWnd->GetCurrentIGenID() == MCNODE)
	{
		pDListMgr = pObjectMgr->GetObjectList(MCNODE);
		m_pNodInDlg->SetWindowText("CONTROL Node");
		int nLastNum = pMsObjMgr->GetLastMeshNo(MCNODE);		// internal
		sprintf(buf,"%d",nLastNum);
		m_CurrentNodeID = "MC_";
		m_CurrentNodeID	+= buf;
		m_bAnchorCNode	= TRUE;
		////////////////////////////////////////////////// Not Ist Time
//		if( !pDListMgr->IsEmpty() )
//			pObjectMgr->BumpLastInputNo(CNODE);		// bump it
	}
	else
	if(pWnd->GetCurrentIGenID() == INODE)
	{
		pDListMgr = pObjectMgr->GetObjectList(NODE);
		m_pNodInDlg->SetWindowText("INPUT Node");
		int nLastNum = pObjectMgr->GetLastInputNo(NODE);		// internal
		sprintf(buf,"%d",nLastNum);
		m_CurrentNodeID = "";
		m_CurrentNodeID	+= buf;
		m_bAnchorCNode	= FALSE;
		////////////////////////////////////////////////// Not Ist Time
//		if( !pDListMgr->IsEmpty() )
//			pObjectMgr->BumpLastInputNo(NODE);		// bump it
	}
	////////////
	m_CurrentNodeIDOld	= m_CurrentNodeID;
	m_AnchorNodeID		= m_CurrentNodeIDOld;
	/////////////////////////////////////////
	UpdateADlg_FALSE();
	///////////////////////////////////////////////////////////////// if NodeDlg Open
	if(GetNodInDlg()->m_hWnd)
	{
		CStatic* pCtl;
		pCtl = (CStatic*)(GetNodInDlg()->GetDlgItem(IDC_OTHER));
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
			pWnd->SendMessage(ID_GOODBYE_NODIN,IDOK);
			return 0L;
		}
		GetNodInDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
	}
	////////////////////////////////////////////////////////////////// Set Info
	GetNodInDlg()->m_ObjID		= GetCurrentNodeID();
//	GetNodInDlg()->m_SID		= GetCurrentSupID();
	GetNodInDlg()->m_nViewNum	= pWnd->GetActiveViewNumber();
	GetNodInDlg()->m_bnid_C		= FALSE;
//	GetNodInDlg()->m_dCoord		= GetCurrentThirdCoord();
	GetNodInDlg()->m_Z			= GetCurrentThirdCoord();
	////////////////////////////////
	GetNodInDlg()->UpdateData(FALSE);
	////////////////////////////////
	return 0L;

}
	 
long CNodMouAX::CancelNodIn(UINT wParam, long lParam)
{
	
	GetNodInDlg()->DestroyWindow();
	////////////////
	{
		Terminate_NOD(FALSE);
		return 0L;
	}
	//////////
	return 0L;
}
	 
long CNodMouAX::GoodByeNodIn(UINT wParam, long lParam)
{
	
	GetNodInDlg()->DestroyWindow();
	////////////////
	{
		Terminate_NOD(FALSE);
		return 0L;
	}
	//////////
	return 0L;
}
	 
long CNodMouAX::UpdateNodIn(UINT wParam, long lParam)
{

	BOOL bAdvancedOld	= m_bAdvanced;
	GetNodInDlg()->UpdateData(TRUE);
	m_bAdvanced = GetNodInDlg()->m_bAdvanced;
	/////////////////////////////////////////////////////////////
	if(!m_bAdvanced)
	{
		GetNodInDlg()->UpdateData(TRUE);
		///////////////////////////////// Reset data in ElMouse
		SetCurrentNodeID(GetNodInDlg()->m_ObjID);
		SetMouseWIC(GetNodInDlg()->m_MouseWIC);
		SetCurrentThirdCoord(GetNodInDlg()->m_dCoord);
		if(bAdvancedOld)
			///////////////////
			UpdateNDlg_FALSE();
			//////////
		return 0L;
	}
	///////////////////////////////////////////////////////////// Advanced Option
	GetNodInDlg()->GetDlgItem(IDC_ADVANCED)->EnableWindow(FALSE);
	////////////////////
	if(m_nInfoDone == 0)
		Init_NOD();
	/////////////////////////
	if(m_bDlgExpect)
	{
		//////
		UpdateDlg_TRUE_ADVANCE();
		///////////////////////// 
		m_nInfoDone++;
	}
	//////////////////////////
	UpdateDlg_FALSE_ADVANCE();
	//////////
	return 0L;
}
	
void CNodMouAX::Serialize(CArchive& ar)
{

	CMouse::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	BYTE bDialogOn,bElementMode,bDragOn,bDragging,bRefreshOn; 
	WORD nActiveObject,nActiveTool,nNodeDone;
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" NodMouAX:    Storing\n");	
		
 			/////////////////////////////////////////////////
		ar	<</*BOOL*/	(BYTE)m_bDialogOn 
			<</*BOOL*/	(BYTE)m_bElementMode 
			<</*int*/	(WORD)m_nActiveObject 
			<</*int*/	(WORD)m_nActiveTool 
			<</*BOOL*/	(BYTE)m_bDragOn 
			<</*BOOL*/	(BYTE)m_bDragging 
			<</*BOOL*/	(BYTE)m_bRefreshOn 
			<</*int*/	(WORD)m_nNodeDone;
 			//////////////////////////////

	}
	else
	{
		TRACE(" NodMouAX:    Loading\n");	

			/////////////////////////////////////////////////
		ar	>>/*BOOL*/	bDialogOn 
			>>/*BOOL*/	bElementMode 
			>>/*int*/	nActiveObject 
			>>/*int*/	nActiveTool 
			>>/*BOOL*/	bDragOn 
			>>/*BOOL*/	bDragging 
			>>/*BOOL*/	bRefreshOn 
			>>/*int*/	nNodeDone;
 		//////////////////////////////
		m_bDialogOn		= (BOOL)bDialogOn;
		m_bElementMode	= (BOOL)bElementMode;
		m_nActiveObject	= (int)nActiveObject;
		m_nActiveTool	= (int)nActiveTool;
		m_bDragOn		= (BOOL)bDragOn;
		m_bDragging		= (BOOL)bDragging;
		m_bRefreshOn	= (BOOL)bRefreshOn;
		m_nNodeDone		= (int)nNodeDone;
	
	}        
	///////////////////////////////////// 
	SerializeNode(ar);      
	//////////////////
}

///////////////////////////////////////////////////////// element serializer
void CNodMouAX::SerializeNode(CArchive& ar)
{ 
	///////////////////////////////////////////////////// STORING				
	if (ar.IsStoring())
	{
		ar	<<	m_CurrentNodeID
			<<	m_AnchorNodeID;
	}
	///////////////////////////////////////////////////// LOADING				
	else
	{
		ar	>>	m_CurrentNodeID
			>>	m_AnchorNodeID;
	}
				    				
}
///////////////////////////////////// end of Module //////////////////////		
/*	
	///////////////////////////////////////////////////////////TEMPORARY
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
    /////////////////////////////////////////////////////////////////////
	CMNodMgr* pMNodMgr;
	CString nID;
	pMNodMgr->DoModal_Node(m_nView,&MouseWIC,&nID);
	pMNodMgr->DoModal_Pipe();
	/////////////////////////
	CDDlgMgr* pDDlgMgr;
	pDDlgMgr->DoModal_Label_Insert();
	pDDlgMgr->DoModal_Label_Edit();
	/////////////////////////////////////////////////////////////////////
*/


