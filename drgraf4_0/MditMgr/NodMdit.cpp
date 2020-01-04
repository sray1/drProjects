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
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
///////////////////// dialogMgr
#include "MditDlgM.h"  
///////////////////// IGens
#include "Def_Elem.h"
#include "DrFE1D.h"
#include "DrFE2D.h"
#include "DrFE3D.h"
/////////////////////
#include "NodCreOM.h"
//////////////////////
#include "RegenMs1.h"
#include "RegenMs2.h"
#include "RegenMs3.h" 
///////////////////// Elems
#include "Def_Elem.h"
//////////////////////
#include "NodMdit.h" 

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
IMPLEMENT_SERIAL(CNodMdit,CMouse,1)
/////////////////////////////////////////////////////////////////////////////
CNodMdit::CNodMdit()
{
	C3DMath Math3D;
	///////////////
	m_bCoordIn		= TRUE;
	m_TranPtID		= "";
	Math3D.Set3DPts(&m_wTranPt,0.0,0.0,0.0);
	Math3D.Set3DPts(&m_wTran,0.0,0.0,0.0);
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

CNodMdit::~CNodMdit()
{
}
	
void CNodMdit::ElementLeftDown_NOD(CPoint point)
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

int CNodMdit::ShowNodeToEdit(CDrFE0D* pDrNode)
{
	int nResult = 0;
	///////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	//////////////////////////////////////////////////////////////////
	pObjectMgr->SetActiveObjectType(FE0D);                   
	//////////////////////////// Edit
	if(m_nActiveTool == N_EDIT)
	{
		CMditDlgM* pEditDlgM;
		/////////////////////////////////////////////////////////////// Using MNodMgr
		if (pEditDlgM->DoModal_ShowNodeToEdit(pDrNode,m_nView) == IDCANCEL)
			return -2;
	}
	//////////////////////////// Move/Copy OFF
	if(!pBool->IsSpawnOn())	// Rigid Body
	{
		CNodCreOM NodCreOp;
		PrepareFor_Xlation(NodCreOp);
		nResult = NodCreOp.ShowNodeToSpawn(m_pCurrentNode,FALSE);
	}
	else	// Regenerate/Flexible
	{
		//All affected Centroids needs to be Recalculated
		//////////////////////////////////// Update Dependent Curves
		CRegenMs1 RegenMs1;
//		RegenCur.SetCurrentView(m_pView);
		RegenMs1.UpdateMeshElemCentroids(pDrNode);
		//////////////////////////////////// Update Dependent Patches
		CRegenMs2 RegenMs2;
//		RegenPat.SetCurrentView(m_pView);
		RegenMs2.UpdateMeshElemCentroids(pDrNode);
		//////////////////////////////////// Update Dependent Solids
		CRegenMs3 RegenMs3;
//		RegenSol.SetCurrentView(m_pView);
		RegenMs3.UpdateMeshElemCentroids(pDrNode);
	}
	//////////////////////////////////////// Show Edited Stuff
	pDoc->SetModifiedFlag();
	pDoc->UpdateAllViews(NULL);
	///////////////////////////////
	return 0;
}
	 
void CNodMdit::PrepareFor_Xlation(CNodCreOM& NodCreOp)
{
	////////////////////
	NodCreOp.SetCoordIn(TRUE);		// for Translation Value
	NodCreOp.SetTranPtID(m_TranPtID);// Grab
	NodCreOp.SetTranPt(m_wTranPt);
	NodCreOp.SetTran(m_wTran);
	////////////////////
	NodCreOp.SetUpLocalM_XLATE();
	/////////
}

void CNodMdit::OnEBoxLButtonDown_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
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
	if(pWnd->GetCurrentIGenID() == FE0D )
		pDListMgr 	= pObjectMgr->GetObjectList(FE0D);
	else
	if(pWnd->GetCurrentIGenID() == MNODE )
		pDListMgr 	= pObjectMgr->GetObjectList(MNODE);
	else
	if(pWnd->GetCurrentIGenID() == MCNODE)
		pDListMgr 	= pObjectMgr->GetObjectList(MCNODE);
	else
		return;
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

int CNodMdit::LeftUp_NODE(CPoint point,BOOL bCNode)
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
		pDListMgr	= pObjectMgr->GetObjectList(MCNODE);
	else
	if(m_bMNode)
		pDListMgr	= pObjectMgr->GetObjectList(MNODE);
	else
		pDListMgr	= pObjectMgr->GetObjectList(FE0D);
	///
//	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString*	pID;
	CString		ID;
	CDrFE0D*	pDrNode;
//	int			nActiveIndex,index;
	int			index;
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
							index = IsObjectHit(MCNODE,point,0);
						else
						if(m_bMNode)
							index = IsObjectHit(MNODE,point,0);
						else
							index = IsObjectHit(FE0D,point,0);
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
							index = IsObjectHit(MCNODE,point,0);
						else
						if(m_bMNode)
							index = IsObjectHit(MNODE,point,0);
						else
							index = IsObjectHit(FE0D,point,0);
	}
	/////////////////////////////////////////////////////////////// Right Type
	if(index>=0)						
	{
		/////////////
		pDrNode	= (CDrFE0D*)pDListMgr->GetObject(index);
		ID		= pDrNode->GetObjectID();
		/////////////////////////////////////////////
		if(bCNode)
			pObjectMgr->ShowObject_On_Off(pDrNode,MCNODE,TRUE);
		else
		if(m_bMNode)
			pObjectMgr->ShowObject_On_Off(pDrNode,MNODE,TRUE);
		else
			pObjectMgr->ShowObject_On_Off(pDrNode,FE0D,TRUE);
/*
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
			pList = pObjectMgr->GetObjectList(NODE);
			nActiveIndex = pList->GetObjectIndex(NODE, ID);
			pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
			pObjectMgr->SetActiveObjectType(NODE);		    // set Active Type									
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,NODE);
		}
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
				CString* str = new CString;
				char* buf = str->GetBuffer(BUFF_SIZE);
				/////////////
				int j;
				/////////////////////////////// Coords
				WORLD Loc = *(pDrNode->GetLocalPos());
				WORtoWOP(&Loc,&Loc);	// to Physical
				//////////////////////////////
				j = sprintf(buf,"***** A Node Hit to Edit ****\n");
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
					"\n\nYES:\t\tEdit This (C)Node");
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
							index = IsObjectHit(MCNODE,point,startIndex);
						else
						if(m_bMNode)
							index = IsObjectHit(MNODE,point,startIndex);
						else
							index = IsObjectHit(FE0D,point,startIndex);
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
							index = IsObjectHit(MCNODE,point,startIndex);
						else
						if(m_bMNode)
							index = IsObjectHit(MNODE,point,startIndex);
						else
							index = IsObjectHit(FE0D,point,startIndex);
					}
					/////////////////////////////////////////////////////////////// Right Type
					if(index>=0)
					{
						pDrNode	= (CDrFE0D*)pDListMgr->GetObject(index);
						ID		= pDrNode->GetObjectID();
						/////////////////////////////////////////////
		if(bCNode)
			pObjectMgr->ShowObject_On_Off(pDrNode,MCNODE,TRUE);
		else
		if(m_bMNode)
			pObjectMgr->ShowObject_On_Off(pDrNode,MNODE,TRUE);
		else
			pObjectMgr->ShowObject_On_Off(pDrNode,FE0D,TRUE);
/*
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
							pList = pObjectMgr->GetObjectList(NODE);
							nActiveIndex = pList->GetObjectIndex(NODE, ID);
							pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
							pObjectMgr->SetActiveObjectType(NODE);		    // set Active Type									
							pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,NODE);
						}
*/
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
		AfxMessageBox("ERROR:\nCNodMdit::LeftUp_Node\nShowNodeToEdit Problem");
		return -1;
	}
	else
	if(nResult == -2)		// Cancel
		return -2;
	////////////////////////////
	return 0;
}

int CNodMdit::LeftUp_NODE_PreMove(CPoint point,BOOL bCNode)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///
	CDListMgr* pDListMgr;
	if(bCNode)
		pDListMgr	= pObjectMgr->GetObjectList(MCNODE);
	else
	if(m_bMNode)
		pDListMgr	= pObjectMgr->GetObjectList(MNODE);
	else
		pDListMgr	= pObjectMgr->GetObjectList(FE0D);
	///
//	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
//	CString*	pID;
	CString		ID;
	CDrFE0D*	pDrNode;
//	int			nActiveIndex,index;
	int			index;
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
			index = IsObjectHit(MCNODE,point,0);
		else
		if(m_bMNode)
			index = IsObjectHit(MNODE,point,0);
		else
			index = IsObjectHit(FE0D,point,0);
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
			index = IsObjectHit(MCNODE,point,0);
		else
		if(m_bMNode)
			index = IsObjectHit(MNODE,point,0);
		else
			index = IsObjectHit(FE0D,point,0);
	}
	/////////////////////////////////////////////////////////////// Right Type
	if(index>=0)						
	{
		/////////////
		pDrNode	= (CDrFE0D*)pDListMgr->GetObject(index);
		ID		= pDrNode->GetObjectID();
		/////////////////////////////////////////////
		if(bCNode)
			pObjectMgr->ShowObject_On_Off(pDrNode,MCNODE,TRUE);
		else
		if(m_bMNode)
			pObjectMgr->ShowObject_On_Off(pDrNode,MNODE,TRUE);
		else
			pObjectMgr->ShowObject_On_Off(pDrNode,FE0D,TRUE);
/*
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
			pList = pObjectMgr->GetObjectList(NODE);
			nActiveIndex = pList->GetObjectIndex(NODE, ID);
			pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
			pObjectMgr->SetActiveObjectType(NODE);		    // set Active Type									
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,NODE);
		}
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
					"\n\nYES:\t\tMove This (C)Node");
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
							index = IsObjectHit(MCNODE,point,startIndex);
						else
						if(m_bMNode)
							index = IsObjectHit(MNODE,point,startIndex);
						else
							index = IsObjectHit(FE0D,point,startIndex);
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
							index = IsObjectHit(MCNODE,point,startIndex);
						else
						if(m_bMNode)
							index = IsObjectHit(MNODE,point,startIndex);
						else
							index = IsObjectHit(FE0D,point,startIndex);
					}
					/////////////////////////////////////////////////////////////// Right Type
					if(index>=0)
					{
						pDrNode	= (CDrFE0D*)pDListMgr->GetObject(index);
						ID		= pDrNode->GetObjectID();
						/////////////////////////////////////////////
		if(bCNode)
			pObjectMgr->ShowObject_On_Off(pDrNode,MCNODE,TRUE);
		else
		if(m_bMNode)
			pObjectMgr->ShowObject_On_Off(pDrNode,MNODE,TRUE);
		else
			pObjectMgr->ShowObject_On_Off(pDrNode,FE0D,TRUE);
/*
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
							pList = pObjectMgr->GetObjectList(NODE);
							nActiveIndex = pList->GetObjectIndex(NODE, ID);
							pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
							pObjectMgr->SetActiveObjectType(NODE);		    // set Active Type									
							pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,NODE);
						}
*/
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
	strCur = "Ready for Moving Node" + ID + "@";
	strCur += "Click Down, Hold & Move The Node";
	pWnd->SetstrCurrID(strCur);
	///////////////////////////////////////////////////////////
	return 0;
}

int CNodMdit::LeftUp_NODE_DoneMove(CPoint point,BOOL bCNode)
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
	////////////////////////////////////// set up transformation (Xlation)
	SetNodeFromMouseWIC(m_pCurrentNode,&MouseWIC);
	////////////////////////////////// IGenID
	UINT IGenID = pWnd->GetCurrentIGenID();
	///////////////////
	switch(IGenID)
	{
		case NODE:
		case INODE:
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
	strCur += "Click On a Node";
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->SetText(strCur);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
	///////////////////////////////////////////////////////////
	return 0;
}

void CNodMdit::ElementLeftUp_NOD(CPoint point)
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
				case MNODE:
					m_bMNode	= TRUE;
					m_bMCNode	= FALSE;
					////////////////
					LeftUp_NODE(point,FALSE);		// FALSE = Not CNODE
					///////
					return;

				case FE0D:
				
					m_bMNode	= FALSE;
					m_bMCNode	= FALSE;
					////////////////
					LeftUp_NODE(point,FALSE);		// FALSE = Not CNODE
					///////
					return;
				
				case MCNODE:				

					m_bMNode	= FALSE;
					m_bMCNode	= TRUE;
					////////////////
					LeftUp_NODE(point,TRUE);			// TRUE = CNODE;
					///////
					return;

			}
			return;

		case N_MOVE:
				
			switch(IGenID)
			{
				case MNODE:
					m_bMNode	= TRUE;
					m_bMCNode	= FALSE;
					////////////////
					if(!m_bDragOn && !m_bAutoAcceptOn)
						LeftUp_NODE_PreMove(point,FALSE);		// FALSE = Not CNODE
					else
						LeftUp_NODE_DoneMove(point,FALSE);		// 
					///////
					return;

				case FE0D:
				
					m_bMNode	= FALSE;
					m_bMCNode	= FALSE;
					////////////////
					if(!m_bDragOn && !m_bAutoAcceptOn)
						LeftUp_NODE_PreMove(point,FALSE);		// FALSE = Not CNODE
					else
						LeftUp_NODE_DoneMove(point,FALSE);		// 
					///////
					return;
				
				case MCNODE:				

					m_bMNode	= FALSE;
					m_bMCNode	= TRUE;
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

void CNodMdit::OnEBoxLButtonUp_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CNodMdit::SetMouseWICFromNode(CDrFE0D* pDrNode,LPOINT3* pMouseWIC)
{
	pMouseWIC->x = pDrNode->GetNodeCard()->x;								  	
	pMouseWIC->y = pDrNode->GetNodeCard()->y;								  	
	pMouseWIC->z = pDrNode->GetNodeCard()->z;								  	
}

void CNodMdit::SetNodeFromMouseWIC(CDrFE0D* pDrNode,LPOINT3* pMouseWIC)
{
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
    /////////////////////////////////////////////////////////////////////////// NO New Object
	if(!pBool->IsSpawnOn())	// Rigid Body
	{
		/////////////////////////////////////////////////////////////////////// Grab Node
		m_TranPtID		= m_pCurrentNode->GetObjectID();
		m_wTranPt		= *(m_pCurrentNode->GetLocalPos());
		///
		WORtoWOP(&m_wTranPt,&m_wTranPt);// change to physical like in Dlg Input
		/////////////////////////////////////////////////////////////////////// To Coord
		m_wTran.x	= (double)(pMouseWIC->x);
		m_wTran.y	= (double)(pMouseWIC->y);
		m_wTran.z	= (double)(pMouseWIC->z);
		/////////
		WORtoWOP(&m_wTran,&m_wTran);// change to physical like in Dlg Input
		///
	}
	else	// Flexible
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
}

int CNodMdit::SetThirdCoordFromNode(CDrFE0D* pDrNode,long* Third)
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
			AfxMessageBox("ERROR:CNodMdit::SetThirdCoordFromNode\nWRONG VIEW");
			return -1;
	}
	return 0;
}

void CNodMdit::PostLeft()
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
	
void CNodMdit::LMovDown_NOD(CPoint point)
{	
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	//////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	switch(pWnd->GetCurrentIGenID())
	{
		case MCNODE:
			m_bMCNode	= TRUE;
			break;
		case FE0D:
			m_bMCNode	= FALSE;
			m_bMNode	= FALSE;
			break;
		case MNODE:		// fall thro'
			m_bMCNode	= FALSE;
			m_bMNode	= TRUE;
		default:
			break;
	}
	BOOL bCNode = m_bMCNode;
	///
	CDListMgr* pDListMgr;
	if(bCNode)
		pDListMgr	= pObjectMgr->GetObjectList(MCNODE);
	else
	if(m_bMNode)
		pDListMgr	= pObjectMgr->GetObjectList(MNODE);
	else
		pDListMgr	= pObjectMgr->GetObjectList(FE0D);
	///
//	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CDrFE0D*	pDrNode;
//	int			nActiveIndex,index;
	int			index;
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
							index = IsObjectHit(MCNODE,point,0);
						else
						if(m_bMNode)
							index = IsObjectHit(MNODE,point,0);
						else
							index = IsObjectHit(FE0D,point,0);
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
							index = IsObjectHit(MCNODE,point,0);
						else
						if(m_bMNode)
							index = IsObjectHit(MNODE,point,0);
						else
							index = IsObjectHit(FE0D,point,0);
		}
		//////////////////////////////////////////////////// Check if CorrectType Node/CNode/MNode
		if(index<0)
			return;
		////////////////////////////////////////////////////
		pDrNode	= (CDrFE0D*)pDListMgr->GetObject(index);
		ID		= pDrNode->GetObjectID();
		/////////////////////////////////////////////
		if(bCNode)
			pObjectMgr->ShowObject_On_Off(pDrNode,MCNODE,TRUE);
		else
		if(m_bMNode)
			pObjectMgr->ShowObject_On_Off(pDrNode,MNODE,TRUE);
		else
			pObjectMgr->ShowObject_On_Off(pDrNode,FE0D,TRUE);
/*
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
			pList = pObjectMgr->GetObjectList(NODE);
			nActiveIndex = pList->GetObjectIndex(NODE, ID);
			pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
			pObjectMgr->SetActiveObjectType(NODE);		    // set Active Type									
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,NODE);
		}
*/
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
			pObjectMgr->ShowObject_On_Off(pDrNode,MCNODE,TRUE);
		else
		if(m_bMNode)
			pObjectMgr->ShowObject_On_Off(pDrNode,MNODE,TRUE);
		else
			pObjectMgr->ShowObject_On_Off(pDrNode,FE0D,TRUE);
/*
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
		pList = pObjectMgr->GetObjectList(NODE);
		nActiveIndex = pList->GetObjectIndex(NODE, ID);
		pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
		pObjectMgr->SetActiveObjectType(NODE);		    // set Active Type									
		pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,NODE);
	}
*/
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
	WICtoWOP(lThird,&m_ThirdCoord);
	/////////
}

void CNodMdit::OnEBoxMouseMove_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CNodMdit::OnEBoxRButtonDown_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
									UINT nFlags, CPoint point)
{
		return;
	//////////// do Nothing For Now
}

void CNodMdit::OnEBoxRButtonUp_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
								UINT nFlags, CPoint point)
{
	return;
	//////////// do Nothing For Now
}
/////////////////////////////////////////////////////////////////////////////////////// F_M
UINT CNodMdit::ReSetToolID_NOD(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	/////////////////////////////////////////////////////////
	switch(OperID)
	{
		//////////////////////////////////////////// Edit
		case GOP_EDIT:
		{
			//////////////////////////////////////////// TaskID
			switch(IGenID)
			{
				case MNODE:
					strCur = "Ready for Editing a Mesh Node@";
					break;
				case FE0D:
					strCur = "Ready for Editing a Vertex Node@";
					break;
				case MCNODE:
					strCur = "Ready for Editing a Control Node@";
					break;
				default:
					str = "UNKNOWN";	ID	= UNONE;
					pWnd->SetstrIGenID(str);
					////////////////////////
					return UNONE;
			}
			/////////////////////////////////////
			pWnd->SetIGenBoxStatus(TRUE);
			pWnd->SetCntlBoxStatus(FALSE);
			pWnd->SetDrawBoxStatus(FALSE);
			///////////////////////////// String
			str = "EDIT";
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
						case MNODE:			str = "Mesh@NODE";		ID = N_EDIT;
							strCur = "Click on a Mesh Node@";
							break;
						case FE0D:			str = "Vertex@NODE";	ID = N_EDIT;
							strCur = "Click on a Vertex Node@";
							break;
						case MCNODE:		str = "Control@NODE";	ID = N_EDIT;
							strCur = "Click on a Control Node@";
							break;
						default:			str = "UNKNOWN@NODE";	ID = UNONE;		break;
					}
					pWnd->SetstrIGenID(str);
					////////////////////////
					pWnd->SetstrCurrID(strCur);
//					pWnd->GetCurrStat()->SetText(strCur);
//					pWnd->GetCurrStat()->Invalidate();
//					pWnd->GetCurrStat()->UpdateWindow();

					return ID;
				//////////////////
			}
		}
		//////////////////////////////////////////// Move
		case GOP_MOVE:
		{
			if(!m_bDragOn)
			{
				switch(IGenID)
				{
					case MNODE:
						strCur = "Ready for Moving a Mesh Node@";
						break;
					case FE0D:
						strCur = "Ready for Moving a Vertex Node@";
						break;
					case MCNODE:
						strCur = "Ready for Moving a Control Node@";
						break;
					default:
						str = "UNKNOWN";	ID	= UNONE;
						pWnd->SetstrIGenID(str);
						////////////////////////
						return UNONE;
				}
			}
			/////////////////////////////////////
			pWnd->SetIGenBoxStatus(TRUE);
			pWnd->SetCntlBoxStatus(FALSE);
			pWnd->SetDrawBoxStatus(FALSE);
			///////////////////////////// String
			str = "MOVE";
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
						case MNODE:			str = "Mesh@NODE";		ID = N_MOVE;
							if(!m_bDragOn)
								strCur = "Drag a Mesh Node@";
							break;
						case FE0D:			str = "Vertex@NODE";	ID = N_MOVE;
							if(!m_bDragOn)
								strCur = "Drag a Vertex Node@";
							break;
						case MCNODE:		str = "Control@NODE";	ID = N_MOVE;
							if(!m_bDragOn)
								strCur = "Drag a Control Node@";
							break;
						default:			str = "UNKNOWN@NODE";	ID = UNONE;		break;
					}
					pWnd->SetstrIGenID(str);
					////////////////////////
					if(!m_bDragOn)
						pWnd->SetstrCurrID(strCur);
//					pWnd->GetCurrStat()->SetText(strCur);
//					pWnd->GetCurrStat()->Invalidate();
//					pWnd->GetCurrStat()->UpdateWindow();

					return ID;
				//////////////////
			}
		}
	}
	return UNONE;
}

void CNodMdit::Serialize(CArchive& ar)
{

	CMouse::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	BYTE bDialogOn,bElementMode,bDragOn,bDragging,bRefreshOn; 
	WORD nActiveObject,nActiveTool,nNodeDone;
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" NodMdit:    Storing\n");	
		
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
		TRACE(" NodMdit:    Loading\n");	

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


