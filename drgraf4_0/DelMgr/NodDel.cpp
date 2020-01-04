// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
#include "drgrafrm.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
///////////////////// dialogMgr
#include "MNodMgr.h"  
///////////////////// IGens
#include "Def_IGen.h"
/////////////////////
#include "MP_Xtrud.h"
#include "MP_Rotat.h"
#include "MP_Loft2.h"
#include "MP_CoonP.h"
#include "MP_CooP3.h"
#include "MP_Duct.h"
#include "MP_Sweep.h"
///////////////////// Elems
#include "Def_Elem.h"
/////////////////////
#include "MI_GangC.h" 
//////////////////////
#include "NodDel.h" 

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
IMPLEMENT_SERIAL(CNodDel,CMouse,1)
/////////////////////////////////////////////////////////////////////////////
CNodDel::CNodDel()
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

}

CNodDel::~CNodDel()
{
}
	
void CNodDel::ElementLeftDown_NOD()
{	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	/////////////////////////////////////////////////////////
	switch(m_nActiveTool) 
	{
		
		case N_DELETE:
		//////////////////////////////////////////////////
		default:
			break;
	}  

}

int CNodDel::ShowNodeToDelete(CDrNode* pDrNode, BOOL bToBeDeleted)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr*	pObjList;
	int			nActiveIndex;
	///////////////////
	pObjectMgr->SetActiveObjectType(NODE);                   
	////////////////////////////////////////////////////////////////////// Show Node to Delete
	pDrNode->SetToBeDeleted(bToBeDeleted);
	CString ID = pDrNode->GetObjectID();
	/////////////////////////////////////////////
	if(pDrNode->IsControlNode())
	{
		pObjList = pObjectMgr->GetObjectList(CNODE);
		nActiveIndex = pObjList->GetObjectIndex(CNODE, ID);
		pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
		pObjectMgr->SetActiveObjectType(CNODE);		    // set Active Type									
		pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CNODE);
	}
	else
	{
		pObjList = pObjectMgr->GetObjectList(NODE);
		nActiveIndex = pObjList->GetObjectIndex(NODE, ID);
		pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
		pObjectMgr->SetActiveObjectType(NODE);		    // set Active Type									
		pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,NODE);
	}
	////////////////////////////////////////////////////////////////////// Show Dependent Curves
	CDListMgr* pCurList;
	int i,nCurCount;
	POSITION pos;
	//////////////////////////////////////////////// Curves
	pCurList	= pDrNode->GetCurveList(); 
	nCurCount	= pCurList->GetCount();
	///////////
	for(i=0;i<nCurCount;i++)
	{
		pos					= pCurList->FindIndex(i);
		CDrCurve* pDrCurve	= (CDrCurve*)(pCurList->GetAt(pos));
		////////////////
		if(pDrCurve)
		{
			pDrCurve->SetToBeDeleted(bToBeDeleted);
			/////////////////////////////
			pObjList = pObjectMgr->GetObjectList(CURVE);
			nActiveIndex = pObjList->GetObjectIndex(CURVE,pDrCurve->GetObjectID());
			pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
			pObjectMgr->SetActiveObjectType(CURVE);		    // set Active Index									
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CURVE);

		}
	}
	////////////////////////////////////////////////////////////////////// Show Dependent Patches
	CDListMgr*	pPatList;
	int			nPatCount;
	//////////////////////////////////////////////// Patches due to Node
	pPatList	= pDrNode->GetPatchList(); 
	nPatCount	= pPatList->GetCount();
	///////////
	for(i=0;i<nPatCount;i++)
	{
		pos					= pPatList->FindIndex(i);
		CDrPatch* pDrPatch	= (CDrPatch*)(pPatList->GetAt(pos));
		////////////////
		if(pDrPatch)
		{
			pDrPatch->SetShow(FALSE);
			pDrPatch->SetToBeDeleted(bToBeDeleted);
			pDrPatch->SetShow(TRUE);

		}
	}
	//////////////////////////////////////////////// Patches due to Curve
	int j,index;
	CDListMgr	affectList;
	////////////////////////////////////// collect affected patch
	affectList.RemoveAll();
	///////////////////////
	pCurList	= pDrNode->GetCurveList(); 
	nCurCount	= pCurList->GetCount();
	///////////
	for(i=0;i<nCurCount;i++)
	{
		pos					= pCurList->FindIndex(i);
		CDrCurve* pDrCurve	= (CDrCurve*)(pCurList->GetAt(pos));
		////////////////
		pPatList	= pDrCurve->GetPatchList(); 
		nPatCount	= pPatList->GetCount();
		///////////
		for(j=0;j<nPatCount;j++)
		{
			pos					= pPatList->FindIndex(j);
			CDrPatch* pDrPatch	= (CDrPatch*)(pPatList->GetAt(pos));
			//////////////// not in list - insert
			if(pDrPatch)
			{
				index = affectList.GetObjectIndex(pDrPatch);
				if(index<0)	// not in there
					affectList.InsertObject(pDrPatch);
			}
		}
	}
	////////////////////////////////////// now Show
	nPatCount	= affectList.GetCount();
	for(i=0;i<nPatCount;i++)
	{
		pos					= affectList.FindIndex(i);
		CDrPatch* pDrPatch	= (CDrPatch*)(affectList.GetAt(pos));
		////////////////
		if(pDrPatch)
		{
			pDrPatch->SetToBeDeleted(bToBeDeleted);
			/////////////////////////////
			pObjList = pObjectMgr->GetObjectList(PATCH);
			nActiveIndex = pObjList->GetObjectIndex(PATCH,pDrPatch->GetObjectID());
			pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
			pObjectMgr->SetActiveObjectType(PATCH);		    // set Active Index									
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,PATCH);

		}
	}
	////////////////////////////////////////////////////////////////////// Show Dependent LinSupports
	CDListMgr*	pSupList;
	int			nSupCount;
	//////////////////////////////////////////////// Curves
	pSupList	= pDrNode->GetSuppList(); 
	nSupCount	= pSupList->GetCount();
	///////////
	for(i=0;i<nSupCount;i++)
	{
		pos						= pSupList->FindIndex(i);
		CDrLinSup* pDrLinSup	= (CDrLinSup*)(pSupList->GetAt(pos));
		////////////////
		if(pDrLinSup)
		{
			pDrLinSup->SetToBeDeleted(bToBeDeleted);
			/////////////////////////////
			pObjList = pObjectMgr->GetObjectList(LIN_SUPPORT);
			nActiveIndex = pObjList->GetObjectIndex(LIN_SUPPORT,pDrLinSup->GetObjectID());
			pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
			pObjectMgr->SetActiveObjectType(LIN_SUPPORT);	    // set Active Index									
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,LIN_SUPPORT);

		}
	}
	////////////////////////////////////////////////////////////////////// Show Dependent Static
	CDListMgr*	pStLList;
	int			nStLCount;
	//////////////////////////////////////////////// Curves
	pStLList	= pDrNode->GetStaLList(); 
	nStLCount	= pStLList->GetCount();
	///////////
	for(i=0;i<nStLCount;i++)
	{
		pos						= pStLList->FindIndex(i);
		CDrStatic* pDrStatic	= (CDrStatic*)(pStLList->GetAt(pos));
		////////////////
		if(pDrStatic)
		{
			pDrStatic->SetToBeDeleted(bToBeDeleted);
			/////////////////////////////
			pObjList = pObjectMgr->GetObjectList(STATICLOAD);
			nActiveIndex = pObjList->GetObjectIndex(STATICLOAD,pDrStatic->GetObjectID());
			pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
			pObjectMgr->SetActiveObjectType(STATICLOAD);	    // set Active Index									
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,STATICLOAD);

		}
	}
	///////////////////////////////
	return 0;
}	 

int CNodDel::MarkNode_Delete(CDrNode* pDrNode)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///////////////////
	pObjectMgr->SetActiveObjectType(NODE);                   
	////////////////////////////////////////////////////////////////////// Node to Delete
	pDrNode->SetDeleted(TRUE);
	CDrLabel* pDrLabel = (CDrLabel*)(pDrNode->GetLabelList()->GetHead());
	pDrLabel->SetDeleted(TRUE);
	////////////////////////////////////////////////////////////////////// Dependent Curves
	CDListMgr* pCurList;
	int i,nCurCount;
	POSITION pos;
	//////////////////////////////////////////////// Curves
	pCurList	= pDrNode->GetCurveList(); 
	nCurCount	= pCurList->GetCount();
	///////////
	for(i=0;i<nCurCount;i++)
	{
		pos					= pCurList->FindIndex(i);
		CDrCurve* pDrCurve	= (CDrCurve*)(pCurList->GetAt(pos));
		//////////////////////////////////////////////////////// if Marked Deleted: Continue
		if(pDrCurve->IsDeleted())
			continue;
		////////////////
		if(pDrCurve)
		{
			pDrCurve->SetShow(FALSE);
			pDrCurve->SetDeleted(TRUE);
			pDrCurve->SetShow(TRUE);

		}
	}
	////////////////////////////////////////////////////////////////////// Show Dependent Patches
	CDListMgr*	pPatList;
	int			nPatCount;
	//////////////////////////////////////////////// Patches due to Node
	pPatList	= pDrNode->GetPatchList(); 
	nPatCount	= pPatList->GetCount();
	///////////
	for(i=0;i<nPatCount;i++)
	{
		pos					= pPatList->FindIndex(i);
		CDrPatch* pDrPatch	= (CDrPatch*)(pPatList->GetAt(pos));
		//////////////////////////////////////////////////////// if Marked Deleted: Continue
		if(pDrPatch->IsDeleted())
			continue;
		////////////////
		if(pDrPatch)
		{
			pDrPatch->SetShow(FALSE);
			pDrPatch->SetDeleted(TRUE);
			pDrPatch->SetShow(TRUE);

		}
	}
	//////////////////////////////////////////////// Patches due to Curve
	int j,index;
	CDListMgr	affectList;
	////////////////////////////////////// collect affected patch
	affectList.RemoveAll();
	///////////////////////
	pCurList	= pDrNode->GetCurveList(); 
	nCurCount	= pCurList->GetCount();
	///////////
	for(i=0;i<nCurCount;i++)
	{
		pos					= pCurList->FindIndex(i);
		CDrCurve* pDrCurve	= (CDrCurve*)(pCurList->GetAt(pos));
		////////////////
		pPatList	= pDrCurve->GetPatchList(); 
		nPatCount	= pPatList->GetCount();
		///////////
		for(j=0;j<nPatCount;j++)
		{
			pos					= pPatList->FindIndex(j);
			CDrPatch* pDrPatch	= (CDrPatch*)(pPatList->GetAt(pos));
			//////////////////////////////////////////////////////// if Marked Deleted: Continue
			if(pDrPatch->IsDeleted())
				continue;
			//////////////// not in list - insert
			if(pDrPatch)
			{
				index = affectList.GetObjectIndex(pDrPatch);
				if(index<0)	// not in there
					affectList.InsertObject(pDrPatch);
			}
		}
	}
	////////////////////////////////////// now Show
	nPatCount	= affectList.GetCount();
	for(i=0;i<nPatCount;i++)
	{
		pos					= affectList.FindIndex(i);
		CDrPatch* pDrPatch	= (CDrPatch*)(affectList.GetAt(pos));
		////////////////
		if(pDrPatch)
		{
			pDrPatch->SetDeleted(TRUE);

		}
	}
	////////////////////////////////////////////////////////////////////// Dependent LinSup
	CDListMgr* pSupList;
	int nSupCount;
	//////////////////////////////////////////////// LinSups
	pSupList	= pDrNode->GetSuppList(); 
	nSupCount	= pSupList->GetCount();
	///////////
	for(i=0;i<nSupCount;i++)
	{
		pos					= pSupList->FindIndex(i);
		CDrLinSup* pDrLinSup	= (CDrLinSup*)(pSupList->GetAt(pos));
		//////////////////////////////////////////////////////// if Marked Deleted: Continue
		if(pDrLinSup->IsDeleted())
			continue;
		////////////////
		if(pDrLinSup)
		{
			pDrLinSup->SetShow(FALSE);
			pDrLinSup->SetDeleted(TRUE);
			pDrLinSup->SetShow(TRUE);

		}
	}
	////////////////////////////////////////////////////////////////////// Show Dependent Static
	CDListMgr*	pStLList;
	int			nStLCount;
	//////////////////////////////////////////////// Curves
	pStLList	= pDrNode->GetStaLList(); 
	nStLCount	= pStLList->GetCount();
	///////////
	for(i=0;i<nStLCount;i++)
	{
		pos						= pStLList->FindIndex(i);
		CDrStatic* pDrStatic	= (CDrStatic*)(pStLList->GetAt(pos));
		//////////////////////////////////////////////////////// if Marked Deleted: Continue
		if(pDrStatic->IsDeleted())
			continue;
		////////////////
		if(pDrStatic)
		{
			pDrStatic->SetShow(FALSE);
			pDrStatic->SetDeleted(TRUE);
			pDrStatic->SetShow(TRUE);

		}
	}
	////////////////////////////////////////////////////////////////////// Update ShowStuff
	pDoc->SetModifiedFlag();
	pDoc->UpdateAllViews(NULL);
	///////////////////////////////
	return 0;
}	 
	
void CNodDel::OnEBoxLButtonDown_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
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
	//////////////////////////////////////////////////////// LOG
	m_pdc->DPtoLP(&point);
	//////////////////////////////////////////////////
	m_nActiveObject = pWnd->GetActiveObjectType(); 
	m_nActiveTool	= pWnd->GetActiveToolType();    // -1= INSERT
	/////////////////////////////////////////////////////////////////////////
	pObjectMgr->SetActiveObjectType(m_nActiveObject);       // Set ObjectType 
	////////////////////////////////////////////////// No Node
	pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	if(pDListMgr->GetCount()<=0)
		return;
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

int CNodDel::LeftUp_NODE(CPoint point,BOOL bCNode)
{
	// For DELETING
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
			index = IsObjectHit(NODE,point,0);
	}
	////////////////////////////////////////////////////
	if(index>=0)						
	{
		/////////////
		pDrNode	= (CDrNode*)pDListMgr->GetObject(index);
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
				CString* str = new CString;
				char* buf = str->GetBuffer(BUFF_SIZE);
				/////////////
				int j;
				/////////////////////////////// Coords
				WORLD Loc = *(pDrNode->GetLocalPos());
				WORtoWOP(&Loc,&Loc);	// to Physical
				//////////////////////////////
				j = sprintf(buf,"***** A Node Hit to Delete ****\n");
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
					"\n\nYES:\t\tDelete This (C)Node");
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
						pDrNode	= (CDrNode*)pDListMgr->GetObject(index);
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
	if(ShowNodeToDelete(pDrNode,TRUE)<0)
	{
		AfxMessageBox("ERROR:\nCNodDel::LeftUp_Node\nShowNodeToDelete Problem");
		return -1;
	}
	//////////////////////////////////////////////////////////////////// Warning
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	/////////////
	int j;
	//////////////////////////////
	j = sprintf(buf,"***** WARNING !!! ****\n");
	j += sprintf(buf+j,"\nNode %s is About to be DELETED\nWill DELETE Affected Objects Shown\n",ID);
	////////////////////////////
	j += sprintf(buf+j,"\n\nYES:\t\tDelete This Node");
	j += sprintf(buf+j,"\nNO:\t\tCancel Deletion Process");
	int nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
	delete str;
	///////////
	if(nResult == IDYES)
		//////////////////////////////////////////////////////// Delete
		MarkNode_Delete(pDrNode);
	else
	{
		//////////////////////////////////////////////////////// Show Normal/Cancel
		ShowNodeToDelete(pDrNode,FALSE);
		return -2;
	}
	//////////
	return 0;
}

void CNodDel::ElementLeftUp_NOD(CPoint point)
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

		case N_DELETE:

			switch(IGenID)
			{
				case NODE:
				case INODE:
				
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
		//////////////////////////////////////////////////
		default:  
			break;
	} 
}	

void CNodDel::OnEBoxLButtonUp_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
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
void CNodDel::OnEBoxMouseMove_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point)
{
	return;
	///////////do nothing for now
}

void CNodDel::OnEBoxRButtonDown_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
									UINT nFlags, CPoint point)
{
		return;
	//////////// do Nothing For Now
}

void CNodDel::OnEBoxRButtonUp_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
								UINT nFlags, CPoint point)
{
	return;
	//////////// do Nothing For Now
}
/////////////////////////////////////////////////////////////////////////////////////// F_M
UINT CNodDel::ReSetToolID_NOD(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	/////////////////////////////
	switch(OperID)
	{
		//////////////////////////////////////////// Create
		case GOP_DELETE:
		{
			//////////////////////////////////////////// TaskID
			strCur = "Ready for Deleting a Node@";
			/////////////////////////////////////
			pWnd->SetIGenBoxStatus(TRUE);
			pWnd->SetCntlBoxStatus(FALSE);
			pWnd->SetDrawBoxStatus(FALSE);
			///////////////////////////// String
			str = "DELETE";
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
						case NODE:
						case INODE:			str = "Input@NODE";	ID = N_DELETE;
							strCur += "Click on an Input Node";	break;
						case CNODE:			str = "Control@NODE";	ID = N_DELETE;
							strCur += "Click on a Control Node";	break;
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
	}
	return UNONE;
}

void CNodDel::Serialize(CArchive& ar)
{

	CMouse::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	BYTE bDialogOn,bElementMode,bDragOn,bDragging,bRefreshOn; 
	WORD nActiveObject,nActiveTool,nNodeDone;
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" NodDel:    Storing\n");	
		
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
		TRACE(" NodDel:    Loading\n");	

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


