// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
#include "drgrafrm.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
///////////////////// dialogMgr
#include "EditDlgM.h"  
///////////////////// IGens
#include "Def_IGen.h"
/////////////////////
#include "Regen1D.h"
#include "Regen2D.h"
#include "Regen3D.h"
///////////////////// Elems
#include "Def_Elem.h"
//////////////////////
#include "MNodEdit.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define MIN_NODES_CURVE		2        
#define MIN_CURVES_PATCH	3        
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
#define MAX_NODES_FE1D		2
#define MAX_NODES_FE2D		4
////////////////////////////////////
IMPLEMENT_SERIAL(CMNodEdit,CMouse,1)
/////////////////////////////////////////////////////////////////////////////
CMNodEdit::CMNodEdit()
{

	////////////////////////////
	m_bAutoAcceptOn		= FALSE;
  	m_bDialogOn    		= FALSE;
	m_bDragOn      		= FALSE;
	m_bDragging	   		= FALSE;
	/////////////////////////////////////////// Node 
    m_pCurrentNode		= NULL;
	///////////////////////////////////////////
	m_bRefreshOn		= FALSE;
	///////////////////////////////////////////
	//////////////////////// Set according to WIC: TOBEDONE
	m_AnchorNodeLOG.x 	= 0;
	m_AnchorNodeLOG.y 	= 0; 
	//////////////////////////////////////
	m_MouseLOG 			= m_AnchorNodeLOG;
	m_MouseOldLOG 		= m_MouseLOG;
}

CMNodEdit::~CMNodEdit()
{
}
	
void CMNodEdit::ElementLeftDown_NOD(CPoint point)
{	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	/////////////////////////////////////////////////////////
	switch(m_nActiveTool) 
	{
		
		////////////////////////////////////////////////// Edit
		case N_EDIT:
			break;
		////////////////////////////////////////////////// Move
		case N_MOVE:
			if(m_bDragOn || m_bAutoAcceptOn)
				LMovDown_NOD(point);
			break;
		//////////////////////////////////////////////////
		default:
			break;
	}  

}

int CMNodEdit::ShowNodeToEdit(CDrFE0D* pDrNode)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	//////////////////////////////////////////////////////////////////
	pObjectMgr->SetActiveObjectType(NODE);                   
	////////////////////
	if(m_nActiveTool == N_EDIT)
	{
		CEditDlgM* pEditDlgM;
		/////////////////////////////////////////////////////////////// Using MNodMgr
		if (pEditDlgM->DoModal_ShowNodeToEdit(pDrNode,m_nView) == IDCANCEL)
			return -2;
	}
	/////////////////////////////////////////////////////////////////// Update Dependent Curves
	CRegen1D Regen1D;
	Regen1D.SetCurrentView(m_pView);
	Regen1D.Update1Ds(pDrNode);
	/////////////////////////////////////////////////////////////////// Update Dependent Patches
	CRegen2D Regen2D;
	Regen2D.SetCurrentView(m_pView);
	Regen2D.Update2Ds(pDrNode);
	/////////////////////////////////////////////////////////////////// Update Dependent Solids
	CRegen3D Regen3D;
	Regen3D.SetCurrentView(m_pView);
	Regen3D.Update3Ds(pDrNode);
	////////////////////////////////////////////////////////////////////// Show Edited Stuff
	pDoc->SetModifiedFlag();
	pDoc->UpdateAllViews(NULL);
	///////////////////////////////
	return 0;
}	 

void CMNodEdit::OnEBoxLButtonDown_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
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
//   	m_bDragOn 		= pBool->IsDragOn();
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
	if(pWnd->GetCurrentIGenID() == NODE ||pWnd->GetCurrentIGenID() == MNODE )
		pDListMgr 	= pObjectMgr->GetObjectList(MNODE);
	else
	if(pWnd->GetCurrentIGenID() == CNODE)
		pDListMgr 	= pObjectMgr->GetObjectList(CNODE);
	///
	if(pDListMgr->GetCount()<=0)
		return;
	/////////////////////////////////////////////////////////////////
    if(m_Gener == FORWARD)
		ElementLeftDown_NOD(point);
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftDown_I();
	//////////////////////////////////
}

int CMNodEdit::LeftUp_NODE(CPoint point,BOOL bCNode)
{
	// For EDITING
	///////////////////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///
	CDListMgr* pDListMgr;
	if(bCNode)
		pDListMgr	= pObjectMgr->GetObjectList(CNODE);
	else
		pDListMgr	= pObjectMgr->GetObjectList(MNODE);
	///
	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString*	pID;
	CString		ID;
	CDrFE0D*	pDrNode;
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
			index = IsObjectHit(CNODE,point,0);
		else
			index = IsObjectHit(MNODE,point,0);
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
			index = IsObjectHit(CNODE,point,0);
		else
			index = IsObjectHit(MNODE,point,0);
	}
	/////////////////////////////////////////////////////////////// Right Type
	if(index>=0)						
	{
		/////////////
		pDrNode	= (CDrFE0D*)pDListMgr->GetObject(index);
		ID		= pDrNode->GetObjectID();
		/////////////////////////////////////////////
		if(bCNode)
		{
			pList = pObjectMgr->GetObjectList(CNODE);
			nActiveIndex = pList->GetObjectIndex(CNODE, ID);
			pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
			pObjectMgr->SetActiveObjectType(CNODE);		    // set Active Type									
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CNODE);
		}
		else
		{
			pList = pObjectMgr->GetObjectList(MNODE);
			nActiveIndex = pList->GetObjectIndex(MNODE, ID);
			pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
			pObjectMgr->SetActiveObjectType(MNODE);		    // set Active Type									
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,MNODE);
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
				CString* str = new CString;
				char* buf = str->GetBuffer(BUFF_SIZE);
				/////////////
				int j;
				/////////////////////////////// Coords
				WORLD Loc = *(pDrNode->GetLocalPos());
				WORtoWOP(&Loc,&Loc);	// to Physical
				//////////////////////////////
				j = sprintf(buf,"***** A Mesh Node Hit to Edit ****\n");
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
					"\n\nYES:\t\tEdit This Mesh Node");
				////////////////////////////
				if(m_ProbLim == PDL_TWO)
				{
					j += sprintf(buf+j,
						"\nNO:\t\tCancel Selection Process");
					nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
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
				/////////////
				if(nResult == IDYES)
				{
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
							index = IsObjectHit(CNODE,point,startIndex);
						else
							index = IsObjectHit(MNODE,point,startIndex);
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
							index = IsObjectHit(CNODE,point,startIndex);
						else
							index = IsObjectHit(MNODE,point,startIndex);
					}
					/////////////////////////////////////////////////////////////// Right Type
					if(index>=0)
					{
						pDrNode	= (CDrFE0D*)pDListMgr->GetObject(index);
						ID		= pDrNode->GetObjectID();
						/////////////////////////////////////////////
						if(bCNode)
						{
							pList = pObjectMgr->GetObjectList(CNODE);
							nActiveIndex = pList->GetObjectIndex(CNODE, ID);
							pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
							pObjectMgr->SetActiveObjectType(CNODE);		    // set Active Type									
							pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CNODE);
						}
						else
						{
							pList = pObjectMgr->GetObjectList(MNODE);
							nActiveIndex = pList->GetObjectIndex(MNODE, ID);
							pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
							pObjectMgr->SetActiveObjectType(MNODE);		    // set Active Type									
							pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,MNODE);
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
					/////////////
					delete str;
					return -2;
				}
			}						// end for loop
			///////////////////////////////////////
		}				// end !AutoAccept loop
	}			// end Index loop
	else
		return 0;	// Not Hit
	//////////////////////////////////////////////////////////////////// finally, show Properties
	m_pCurrentNode = pDrNode;
	/////////////////////////////
	int nResult = ShowNodeToEdit(pDrNode);
	///////////
	if( nResult == -1)		// 
	{
		AfxMessageBox("ERROR:\nCMNodEdit::LeftUp_Node\nShowNodeToEdit Problem");
		return -1;
	}
	else
	if(nResult == -2)		// Cancel
		return -2;
	////////////////////////////
	return 0;
}

int CMNodEdit::LeftUp_NODE_PreMove(CPoint point,BOOL bCNode)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///
	CDListMgr* pDListMgr;
	if(bCNode)
		pDListMgr	= pObjectMgr->GetObjectList(CNODE);
	else
		pDListMgr	= pObjectMgr->GetObjectList(MNODE);
	///
	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CDrFE0D*	pDrNode;
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
			index = IsObjectHit(CNODE,point,0);
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
/*
		////////////////
		if(bCNode)
			index = IsObjectHit(CNODE,&wLoc,0);
		else
			index = IsObjectHit(NODE,&wLoc,0);
		///
*/
		if(bCNode)
			index = IsObjectHit(CNODE,point,0);
		else
			index = IsObjectHit(NODE,point,0);
	}
	/////////////////////////////////////////////////////////////// Right Type
	if(index>=0)						
	{
		/////////////
		pDrNode	= (CDrFE0D*)pDListMgr->GetObject(index);
		ID		= pDrNode->GetObjectID();
		/////////////////////////////////////////////
		if(bCNode)
		{
			pList = pObjectMgr->GetObjectList(CNODE);
			nActiveIndex = pList->GetObjectIndex(CNODE, ID);
			pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
			pObjectMgr->SetActiveObjectType(CNODE);		    // set Active Type									
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CNODE);
		}
		else
		{
			pList = pObjectMgr->GetObjectList(MNODE);
			nActiveIndex = pList->GetObjectIndex(MNODE, ID);
			pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
			pObjectMgr->SetActiveObjectType(MNODE);		    // set Active Type									
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,MNODE);
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
				CString* str = new CString;
				char* buf = str->GetBuffer(BUFF_SIZE);
				/////////////
				int j;
				/////////////////////////////// Coords
				WORLD Loc = *(pDrNode->GetLocalPos());
				WORtoWOP(&Loc,&Loc);	// to Physical
				//////////////////////////////
				j = sprintf(buf,"***** A Node Hit to Move ****\n");
				j += sprintf(buf+j,"with Similar Coordinates (with %f Tolerance):",dTol);
				j += sprintf(buf+j,"\nExisting NodeID = %s\nCoordinates:\n\t X = %f\n\t Y = %f\n\t Z = %f\n",
					ID,Loc.x,Loc.y,Loc.z);
				////////////////////////////
				j += sprintf(buf+j,
					"\n\nYES:\t\tMove This Mesh Node");
				////////////////////////////
				if(m_ProbLim == PDL_TWO)
				{
					j += sprintf(buf+j,
						"\nNO:\t\tCancel Selection Process");
					nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
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
				/////////////
				if(nResult == IDYES)
				{
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
							index = IsObjectHit(CNODE,point,startIndex);
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
							index = IsObjectHit(CNODE,point,startIndex);
						else
							index = IsObjectHit(NODE,point,startIndex);
					}
					/////////////////////////////////////////////////////////////// Right Type
					if(index>=0)
					{
						pDrNode	= (CDrFE0D*)pDListMgr->GetObject(index);
						ID		= pDrNode->GetObjectID();
						/////////////////////////////////////////////
						if(bCNode)
						{
							pList = pObjectMgr->GetObjectList(CNODE);
							nActiveIndex = pList->GetObjectIndex(CNODE, ID);
							pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
							pObjectMgr->SetActiveObjectType(CNODE);		    // set Active Type									
							pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CNODE);
						}
						else
						{
							pList = pObjectMgr->GetObjectList(MNODE);
							nActiveIndex = pList->GetObjectIndex(MNODE, ID);
							pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
							pObjectMgr->SetActiveObjectType(MNODE);		    // set Active Type									
							pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,MNODE);
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
					/////////////
					delete str;
					return -2;
				}
			}						// end for loop
			///////////////////////////////////////
		}				// end !AutoAccept loop
	}			// end Index loop
	else
		return 0;	// Not Hit
	//////////////////////////////////////////////////////////////////// finally, show Properties
	m_pCurrentNode = pDrNode;
	////////////////////////////////////// Set Drag On Now
	m_bDragOn = TRUE;
	////////////////////////////////////// Set Click On Message
	strCur = "Ready for Moving Mesh Node" + ID + "@";
	strCur += "Click Down, Hold & Move The Node";
	pWnd->SetstrCurrID(strCur);
	pWnd->UpdateCurrStat(strCur);
	///////////////////////////////////////////////////////////
	return 0;
}

int CMNodEdit::LeftUp_NODE_DoneMove(CPoint point,BOOL bCNode)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	///////////////////////////////////////////////////////////////////////
    if(m_bDragging)  // not currently dragging
    {
		m_bDragging = FALSE;
		::ReleaseCapture();
		//	ClipCursor(NULL);				TOBEDONE 
	}
	else
		return 0;
	//////////////////////////////////////////////////////////////////// Fix Coords
    LPOINT3 MouseWIC = GetMouseWIC();
    SetMouseOldWIC(MouseWIC);
	//////////////
    LPOINT Lpoint;
//    m_pdc->DPtoLP(&point);
    Lpoint.x = (long)point.x;
    Lpoint.y = (long)point.y;
//    m_pdc->LPtoDP(&point);							
    ////////////////////
    LOGtoWIC(&MouseWIC,&Lpoint);    // Log/Scaled             
    SetMouseWIC(MouseWIC);
	//////////////////////////////////////
	SetNodeFromMouseWIC(m_pCurrentNode,&MouseWIC);
	////////////////////////////////// IGenID
	UINT IGenID = pWnd->GetCurrentIGenID();
	///////////////////
	switch(IGenID)
	{
		case NODE:
		case MNODE:
			(m_pCurrentNode->GetNodeCard())->bnid_c = FALSE;
			break;
		case CNODE:
			(m_pCurrentNode->GetNodeCard())->bnid_c = TRUE;
			break;
	}
	//////////////////////////////////////////////////////////////////// finally, show Moved
	ShowNodeToEdit(m_pCurrentNode);
	////////////////////////////////////// Set Drag OFF Now
	m_bDragOn		= FALSE;
	m_pCurrentNode	= NULL;
	////////////////////////////////////// Set Click On Message
	strCur = "Ready for Moving Another Node@";
	strCur += "Click On a Mesh Node";
	pWnd->SetstrCurrID(strCur);
	pWnd->UpdateCurrStat(strCur);
	///////////////////////////////////////////////////////////
	return 0;
}

void CMNodEdit::ElementLeftUp_NOD(CPoint point)
{                          

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	//////////////////////////////////////////////////////////////////
//	CString*	pID;
	/////////////
//	char buf[20];
	CString Nid;
	BOOL bRightOn = FALSE;
	////////////////////////////////// IGenID
	UINT IGenID = pWnd->GetCurrentIGenID();
	///////////////////
	switch(m_nActiveTool) 
	{

		case N_EDIT:

			switch(IGenID)
			{
				case NODE:
				case MNODE:
				
					////////////////
					LeftUp_NODE(point,FALSE);		// FALSE = Not CNODE
					///////
					return;
				
				case CNODE:				

					////////////////
					LeftUp_NODE(point,TRUE);			// TRUE = CNODE;
					///////
					return;

			}
			return;

		case N_MOVE:
				
			switch(IGenID)
			{
				case NODE:
				case MNODE:
				
					////////////////
					if(!m_bDragOn && !m_bAutoAcceptOn)
						LeftUp_NODE_PreMove(point,FALSE);		// FALSE = Not CNODE
					else
						LeftUp_NODE_DoneMove(point,FALSE);		// 
					///////
					return;
				
				case CNODE:				
				
					////////////////
					if(!m_bDragOn && !m_bAutoAcceptOn)
						LeftUp_NODE_PreMove(point,TRUE);		// TRUE = CNODE
					else
						LeftUp_NODE_DoneMove(point,TRUE);		// 
					///////
					return;
				
			}
			break;
		//////////////////////////////////////////////////
		default:  
			break;
	} 
}	

void CMNodEdit::OnEBoxLButtonUp_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point)
{
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
  	/////////////////////////////////////////////////////////
//	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
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
	/////////////////////////
	
}

void CMNodEdit::SetMouseWICFromNode(CDrFE0D* pDrNode,LPOINT3* pMouseWIC)
{
	pMouseWIC->x = pDrNode->GetNodeCard()->x;								  	
	pMouseWIC->y = pDrNode->GetNodeCard()->y;								  	
	pMouseWIC->z = pDrNode->GetNodeCard()->z;								  	
}

void CMNodEdit::SetNodeFromMouseWIC(CDrFE0D* pDrNode,LPOINT3* pMouseWIC)
{
	pDrNode->GetNodeCard()->x	= pMouseWIC->x;								  	
	pDrNode->GetNodeCard()->y	= pMouseWIC->y;								  	
	pDrNode->GetNodeCard()->z	= pMouseWIC->z;								  	
	//////////////////////
   	WORLD LocalPos;
   	///////////////
   	LocalPos.x = (double)pMouseWIC->x; 
   	LocalPos.y = (double)pMouseWIC->y; 
   	LocalPos.z = (double)pMouseWIC->z;
    //////////////////////////////////////// Save as Local Pos
    pDrNode->SetLocalPos(LocalPos);
    /////////////////////////////
}

int CMNodEdit::SetThirdCoordFromNode(CDrFE0D* pDrNode,long* Third)
{
    //////////////////////
	switch (m_nView)
	{
		case VIEW12:        // hor = x; ver = y;
			*Third = pDrNode->GetNodeCard()->z;
			return 0;
		case VIEW23:        // hor = z; ver = y;
			*Third = pDrNode->GetNodeCard()->x;
			return 0;
		case VIEW31:        // hor = x; ver = z;
			*Third = pDrNode->GetNodeCard()->y;
			return 0;
		default:
			AfxMessageBox("ERROR:CMNodEdit::SetThirdCoordFromNode\nWRONG VIEW");
			return -1;
	}
	return 0;
}

void CMNodEdit::PostLeft()
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
	
void CMNodEdit::LMovDown_NOD(CPoint point)
{	
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	//////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	BOOL bCNode = FALSE;
	if(pWnd->GetCurrentIGenID() == CNODE)
		bCNode = TRUE;
	///
	CDListMgr* pDListMgr;
	if(bCNode)
		pDListMgr	= pObjectMgr->GetObjectList(CNODE);
	else
		pDListMgr	= pObjectMgr->GetObjectList(MNODE);
	///
	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CDrFE0D*	pDrNode;
	int			nActiveIndex,index;
	////////////////////////////////////////////////////////////////////// No PreMove
	if(m_bAutoAcceptOn)
	{
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
				index = IsObjectHit(CNODE,point,0);
			else
				index = IsObjectHit(MNODE,point,0);
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
				index = IsObjectHit(CNODE,point,0);
			else
				index = IsObjectHit(MNODE,point,0);
		}
		//////////////////////////////////////////////////// Check if CorrectType Node/CNode/MNode
		if(index<0)
			return;
		////////////////////////////////////////////////////
		pDrNode	= (CDrFE0D*)pDListMgr->GetObject(index);
		ID		= pDrNode->GetObjectID();
		/////////////////////////////////////////////
		if(bCNode)
		{
			pList = pObjectMgr->GetObjectList(CNODE);
			nActiveIndex = pList->GetObjectIndex(CNODE, ID);
			pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
			pObjectMgr->SetActiveObjectType(CNODE);		    // set Active Type									
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CNODE);
		}
		else
		{
			pList = pObjectMgr->GetObjectList(MNODE);
			nActiveIndex = pList->GetObjectIndex(MNODE, ID);
			pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
			pObjectMgr->SetActiveObjectType(MNODE);		    // set Active Type									
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,MNODE);
		}
		////////////////////////////////////////
		m_pCurrentNode = pDrNode;
		/////////////////////////
	}
	//////////////////////////////////////////
	if(!m_pCurrentNode)
		return;
	////////////////////////////////////
	pDrNode = m_pCurrentNode;
	ID		= pDrNode->GetObjectID();
	/////////////////////////////////////////////
	if(bCNode)
	{
		pList = pObjectMgr->GetObjectList(CNODE);
		nActiveIndex = pList->GetObjectIndex(CNODE, ID);
		pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
		pObjectMgr->SetActiveObjectType(CNODE);		    // set Active Type									
		pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CNODE);
	}
	else
	{
		pList = pObjectMgr->GetObjectList(MNODE);
		nActiveIndex = pList->GetObjectIndex(MNODE, ID);
		pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
		pObjectMgr->SetActiveObjectType(MNODE);		    // set Active Type									
		pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,MNODE);
	}
	////////////////////////////////////////
	m_bDragging = TRUE; 
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
	//////////////////
	LPOINT3 MouseWIC;
	SetMouseWICFromNode(pDrNode,&MouseWIC);
   	////////////////////                 
   	SetMouseWIC(MouseWIC);
	SetMouseOldWIC(MouseWIC);
   	///////////////////////////
//    	pDoc->UpdateStatusBar(&dc);  WILL BE CALLED FROM VIEW, JUST SET HERE
	CMouseMgr* pMouseMgr = pWnd->GetMouseMgr(); 
	pMouseMgr->SetStatusMouseWIC(MouseWIC);
	/////////////////////////////////////////// Set AnchorLog etc.
	PostLeft();
	/////////////////////////////////////////// Node:3rd Coord
	long lThird;
	SetThirdCoordFromNode(pDrNode,&lThird);
	m_ThirdCoord		= 0.0;
	WICtoWOR(lThird,&m_ThirdCoord);
	/////////
}

void CMNodEdit::OnEBoxMouseMove_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
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
		return;
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

void CMNodEdit::OnEBoxRButtonDown_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
									UINT nFlags, CPoint point)
{
		return;
	//////////// do Nothing For Now
}

void CMNodEdit::OnEBoxRButtonUp_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
								UINT nFlags, CPoint point)
{
	return;
	//////////// do Nothing For Now
}
/////////////////////////////////////////////////////////////////////////////////////// F_M
UINT CMNodEdit::ReSetToolID_NOD(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString str,strCur;
	UINT ID;
	///////////////////////////////////
	if(IGenID != EDIM_0)
	{
		str = "UNKNOWN";	ID	= UNONE;
		pWnd->SetstrIGenID(str);
		////////////////////////
		return UNONE;
	}
	//////////////////////////////////////////// PostID
	UINT PostID = pWnd->GetCurrentPostID();
	//////////////////////////////////////////// TaskID
	strCur = "Ready for ";
	/////////////////////////////
	switch(OperID)
	{
		//////////////////////////////////////////// Edit
		case GOP_EDIT:
		{
			//////////////////////////////////////////// TaskID
			strCur = "Ready for Editing a Mesh Node@";
			/////////////////////////////////////
			pWnd->SetIGenBoxStatus(TRUE);
			pWnd->SetCntlBoxStatus(FALSE);
			pWnd->SetDrawBoxStatus(FALSE);
			///////////////////////////// String
			str = "EDIT";
			pWnd->SetstrOperID(str);
			/////////////////////////////
			switch(IGenID)
			{
				//////////////////////////////////////// Elements
				case EDIM_0:
				case EDIM_1:
				case EDIM_2:
				case EDIM_3:

					///////////////////////////////////// EDim0/EDim1...
					switch(PostID)
					{
						/////////
						case MNODE:			str = "Mesh@NODE";	ID = N_EDIT;
							strCur += "Click on a Mesh Node";	break;
						default:			str = "UNKNOWN@NODE";	ID = UNONE;		break;
					}
					pWnd->SetstrIGenID(str);
					////////////////////////
					pWnd->SetstrCurrID(strCur);
	pWnd->UpdateCurrStat(strCur);

					return ID;
				//////////////////
			}
		}
		//////////////////////////////////////////// Move
		case GOP_MOVE:
		{
			if(!m_bDragOn)
				//////////////////////////////////////////// TaskID
				strCur = "Ready for Moving a Mesh Node@";
			/////////////////////////////////////
			pWnd->SetIGenBoxStatus(TRUE);
			pWnd->SetCntlBoxStatus(FALSE);
			pWnd->SetDrawBoxStatus(FALSE);
			///////////////////////////// String
			str = "MOVE";
			pWnd->SetstrOperID(str);
			/////////////////////////////
			switch(IGenID)
			{
				//////////////////////////////////////// Elements
				case EDIM_0:
				case EDIM_1:
				case EDIM_2:
				case EDIM_3:

					///////////////////////////////////// EDim0/EDim1...
					switch(PostID)
					{
						/////////
						case MNODE:			str = "Mesh@NODE";	ID = N_MOVE;
							if(!m_bDragOn)
							strCur += "Drag a Mesh Node";	break;
						default:			str = "UNKNOWN@NODE";	ID = UNONE;		break;
					}
					pWnd->SetstrIGenID(str);
					////////////////////////
					if(!m_bDragOn)
						pWnd->SetstrCurrID(strCur);
					return ID;
				//////////////////
			}
		}
	}
	return UNONE;
}

void CMNodEdit::Serialize(CArchive& ar)
{

	CMouse::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	BYTE bDialogOn,bElementMode,bDragOn,bDragging,bRefreshOn; 
	WORD nActiveObject,nActiveTool,nNodeDone;
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" NodEdit:    Storing\n");	
		
 			/////////////////////////////////////////////////
		ar	<</*BOOL*/	(BYTE)m_bDialogOn 
			<</*int*/	(WORD)m_nActiveObject 
			<</*int*/	(WORD)m_nActiveTool 
			<</*BOOL*/	(BYTE)m_bDragOn 
			<</*BOOL*/	(BYTE)m_bDragging 
			<</*BOOL*/	(BYTE)m_bRefreshOn; 
 			//////////////////////////////

	}
	else
	{
		TRACE(" NodEdit:    Loading\n");	

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
		m_nActiveObject	= (int)nActiveObject;
		m_nActiveTool	= (int)nActiveTool;
		m_bDragOn		= (BOOL)bDragOn;
		m_bDragging		= (BOOL)bDragging;
		m_bRefreshOn	= (BOOL)bRefreshOn;
	
	}        
}

///////////////////////////////////// end of Module //////////////////////		


