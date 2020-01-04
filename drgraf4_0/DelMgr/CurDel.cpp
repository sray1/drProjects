// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
#include "drgrafrm.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
///////////////////// elements
#include "Def_IGen.h"
#include "Def_Elem.h"
//////////////////////
#include "MCurMgr.h" 
#include "CurDel.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CCurDel,CNodDel,1)
/////////////////////////////////////////////////////////////////////////////
CCurDel::CCurDel()
{

	/////////////////////////////////////////// 
    m_pCurrentCurve		= NULL;
}

CCurDel::~CCurDel()
{
}
	
void CCurDel::ElementLeftDown_CUR()
{	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	/////////////////////////////////////////////////////////
	switch(m_nActiveTool) 
	{
		
		case C_DELETE:				// CURVE
		//////////////////////////////////////////////////
		default:
			break;
	}  

}

int CCurDel::ShowCurveToDelete(CDrCurve* pDrCurve, BOOL bToBeDeleted)
{
	//  ISOCURVES todo
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr*	pObjList;
	int			nActiveIndex;
	///////////////////
	pObjectMgr->SetActiveObjectType(CURVE);                   
	////////////////////////////////////////////////////////////////////// Show Curve to Delete
	pDrCurve->SetToBeDeleted(bToBeDeleted);
	//////////////////////////////
	pObjList = pObjectMgr->GetObjectList(CURVE);
	nActiveIndex = pObjList->GetObjectIndex(CURVE,pDrCurve->GetObjectID());
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
	pObjectMgr->SetActiveObjectType(CURVE);		    // set Active Index									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CURVE);
	////////////////////////////////////////////////////////////////////// Show Dependent Patches
	CDListMgr* pPatList;
	int i,nPatCount;
	POSITION pos;
	//////////////////////////////////////////////// Patches
	pPatList	= pDrCurve->GetPatchList(); 
	nPatCount	= pPatList->GetCount();
	///////////
	for(i=0;i<nPatCount;i++)
	{
		pos					= pPatList->FindIndex(i);
		CDrPatch* pDrPatch	= (CDrPatch*)(pPatList->GetAt(pos));
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
	////////////////////////////////////////////////////////////////////// Show Dependent Solids
	CDListMgr*	pSolList;
	int			nSolCount;
	//////////////////////////////////////////////// Solids due to Curve
	pSolList	= pDrCurve->GetSolidList(); 
	nSolCount	= pSolList->GetCount();
	///////////
	for(i=0;i<nSolCount;i++)
	{
		pos					= pSolList->FindIndex(i);
		CDrSolid* pDrSolid	= (CDrSolid*)(pSolList->GetAt(pos));
		////////////////
		if(pDrSolid)
		{
			pDrSolid->SetShow(FALSE);
			pDrSolid->SetToBeDeleted(bToBeDeleted);
			pDrSolid->SetShow(TRUE);

		}
	}
	//////////////////////////////////////////////// Solids due to Patches
	int j,index;
	CDListMgr	affectList;
	////////////////////////////////////// collect affected patch
	affectList.RemoveAll();
	///////////////////////
	pPatList	= pDrCurve->GetPatchList(); 
	nPatCount	= pPatList->GetCount();
	///////////
	for(i=0;i<nPatCount;i++)
	{
		pos					= pPatList->FindIndex(i);
		CDrPatch* pDrPatch	= (CDrPatch*)(pPatList->GetAt(pos));
		////////////////
		pSolList	= pDrCurve->GetSolidList(); 
		nSolCount	= pSolList->GetCount();
		///////////
		for(j=0;j<nSolCount;j++)
		{
			pos					= pSolList->FindIndex(j);
			CDrSolid* pDrSolid	= (CDrSolid*)(pSolList->GetAt(pos));
			//////////////// not in list - insert
			if(pDrSolid)
			{
				index = affectList.GetObjectIndex(pDrSolid);
				if(index<0)	// not in there
					affectList.InsertObject(pDrSolid);
			}
		}
	}
	////////////////////////////////////// now Show
	nSolCount	= affectList.GetCount();
	for(i=0;i<nSolCount;i++)
	{
		pos					= affectList.FindIndex(i);
		CDrSolid* pDrSolid	= (CDrSolid*)(affectList.GetAt(pos));
		////////////////
		if(pDrSolid)
		{
			pDrSolid->SetToBeDeleted(bToBeDeleted);
			/////////////////////////////
			pObjList = pObjectMgr->GetObjectList(SOLID);
			nActiveIndex = pObjList->GetObjectIndex(SOLID,pDrSolid->GetObjectID());
			pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
			pObjectMgr->SetActiveObjectType(SOLID);		    // set Active Index									
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,SOLID);

		}
	}
	////////////////////////////////////////////////////////////////////// Show Dependent LinSupports
	CDListMgr*	pSupList;
	int			nSupCount;
	//////////////////////////////////////////////// Curves
	pSupList	= pDrCurve->GetSuppList(); 
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
	pStLList	= pDrCurve->GetStaLList(); 
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

int CCurDel::MarkCurve_Delete(CDrCurve* pDrCurve)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///////////////////
	pObjectMgr->SetActiveObjectType(CURVE);                   
	////////////////////////////////////////////////////////////////////// Curve to Delete
	pDrCurve->SetDeleted(TRUE);
//	CDrLabel* pDrLabel = (CDrLabel*)(pDrNode->GetLabelList()->GetHead());
//	pDrLabel->SetDeleted(TRUE);
	////////////////////////////////////////////////////////////////////// Dependent Patches
	CDListMgr* pPatList;
	int i,nPatCount;
	POSITION pos;
	//////////////////////////////////////////////// Curves
	pPatList	= pDrCurve->GetPatchList(); 
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
	////////////////////////////////////////////////////////////////////// Show Dependent Patches
	CDListMgr*	pSolList;
	int			nSolCount;
	//////////////////////////////////////////////// Patches due to Node
	pSolList	= pDrCurve->GetSolidList(); 
	nSolCount	= pSolList->GetCount();
	///////////
	for(i=0;i<nSolCount;i++)
	{
		pos					= pPatList->FindIndex(i);
		CDrSolid* pDrSolid	= (CDrSolid*)(pSolList->GetAt(pos));
		//////////////////////////////////////////////////////// if Marked Deleted: Continue
		if(pDrSolid->IsDeleted())
			continue;
		////////////////
		if(pDrSolid)
		{
			pDrSolid->SetShow(FALSE);
			pDrSolid->SetDeleted(TRUE);
			pDrSolid->SetShow(TRUE);

		}
	}
	//////////////////////////////////////////////// Solids due to Patch
	int j,index;
	CDListMgr	affectList;
	////////////////////////////////////// collect affected Solids
	affectList.RemoveAll();
	///////////////////////
	pPatList	= pDrCurve->GetPatchList(); 
	nPatCount	= pPatList->GetCount();
	///////////
	for(i=0;i<nPatCount;i++)
	{
		pos					= pPatList->FindIndex(i);
		CDrPatch* pDrPatch	= (CDrPatch*)(pPatList->GetAt(pos));
		////////////////
		pSolList	= pDrPatch->GetSolidList(); 
		nSolCount	= pSolList->GetCount();
		///////////
		for(j=0;j<nSolCount;j++)
		{
			pos					= pSolList->FindIndex(j);
			CDrSolid* pDrSolid	= (CDrSolid*)(pSolList->GetAt(pos));
			//////////////////////////////////////////////////////// if Marked Deleted: Continue
			if(pDrSolid->IsDeleted())
				continue;
			//////////////// not in list - insert
			if(pDrSolid)
			{
				index = affectList.GetObjectIndex(pDrSolid);
				if(index<0)	// not in there
					affectList.InsertObject(pDrSolid);
			}
		}
	}
	////////////////////////////////////// now Show
	nSolCount	= affectList.GetCount();
	for(i=0;i<nSolCount;i++)
	{
		pos					= affectList.FindIndex(i);
		CDrSolid* pDrSolid	= (CDrSolid*)(affectList.GetAt(pos));
		////////////////
		if(pDrSolid)
		{
			pDrSolid->SetDeleted(TRUE);

		}
	}
	////////////////////////////////////////////////////////////////////// Dependent LinSup
	CDListMgr* pSupList;
	int nSupCount;
	//////////////////////////////////////////////// LinSups
	pSupList	= pDrCurve->GetSuppList(); 
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
	pStLList	= pDrCurve->GetStaLList(); 
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
	
void CCurDel::OnEBoxLButtonDown_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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
	////////////////////////////////////////////////// take care of Edit AllClear
	pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	if(pDListMgr->GetCount()<=0 )
		return;
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

int CCurDel::LeftUp_CURVE(CPoint point)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
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
	///////////////////////////////////////////// See if any Existing Curve Hit
	index = IsObjectHit(CURVE,point,0);
	////////////////////////////////////////////////////
	if(index>=0)						
	{
		/////////////
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
				nResult = ShowCurveInfo(pDrCurve);
				/////////////
				if(nResult == IDYES)
				{
					//////////////////////////////////////////////////////// Accept Old
					break;
				}
				else
				if(nResult == IDNO)
				{
					//////////////////////////////////////////////////////// Retry
					index = IsObjectHit(CURVE,point,startIndex);
					if(index>=0)
					{
						pDrCurve	= (CDrCurve*)pDListMgr->GetObject(index);
						ID			= pDrCurve->GetObjectID();
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
					{
						////////////////
						return -2;
					}
					/////////
				}
				else				// Cancel
				{
					//////////////////////////////////////////////////////// Do Nothing
					return -2;
				}
			}						// end for loop
			///////////////////////////////////////
		}				// end !AutoAccept loop
	}			// end Index loop
	else
		return 0;	// Not Hit
	//////////////////////////////////////////////////////////////////// finally, show Properties
	m_pCurrentCurve = pDrCurve;
	if(ShowCurveToDelete(pDrCurve,TRUE)<0)
	{
		AfxMessageBox("ERROR:\nCCurDel::LeftUp_Curve\nShowCurveToDelete Problem");
		return -1;
	}
	//////////////////////////////////////////////////////////////////// Warning
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	/////////////
	int j;
	//////////////////////////////
	j = sprintf(buf		,"				***** WARNING !!! ****\n\n");
	j += sprintf(buf+j	,"		   Curve %s is About to be DELETED\n");
	j += sprintf(buf+j	,"     This Will DELETE Affected Objects Shown\n\n\n",ID);
	////////////////////////////
	j += sprintf(buf+j,  "		YES:\t\tDelete This Curve\n");
	j += sprintf(buf+j,"		NO:\t\tCancel Deletion Process");
	int nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
	delete str;
	///////////
	if(nResult == IDYES)
		//////////////////////////////////////////////////////// Delete
		MarkCurve_Delete(pDrCurve);
	else
	{
		//////////////////////////////////////////////////////// Show Normal/Cancel
		ShowCurveToDelete(pDrCurve,FALSE);
		return -2;
	}
	//////////
	return 0;
}

void CCurDel::ElementLeftUp_CUR(CPoint point)
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
		
		case C_DELETE:

			////////////////////
			LeftUp_CURVE(point);	
			////////////////////
			return;
	
		////////////////////////////////////////////////// POST
/*
		case C_POST:				// CURVE
			///////		
			m_MI_Solid.LBUpCurvePost();
			return;
		////////////////////////////////////////////////// EDIT	
		case C_EDIT:				// CURVE
			///////		
			m_MI_Solid.LBUpCurveEdit();
			return;
		
		////////////////////////////////////////////////// MOVE	
		case C_MOVE:				// CURVE
			///////		
			m_MI_Solid.LBUpCurveMove();
			return;
*/		
		//////////////////////////////////////////////////
		default:  
			break;
	} 
}	

void CCurDel::OnEBoxLButtonUp_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point)
{
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
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
	/////////////////////////
	
}

void CCurDel::OnEBoxMouseMove_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point)
{  
	return;
	///////////do nothing for now
}

void CCurDel::OnEBoxRButtonDown_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
									UINT nFlags, CPoint point)
{ 
	return;
	///////////do nothing for now
}

int CCurDel::ShowCurveInfo(CDrCurve* pDrCurve)
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
	j = sprintf(buf,"***** A Curve Hit ****\n");
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
	j += sprintf(buf+j,
		"\nYES:\t\tDelete This Curve");
	j += sprintf(buf+j,
		"\nNO:\t\tFind Next Curve with Intersecting Trace");
	j += sprintf(buf+j,
		"\nCANCEL:\t\tCancel Selection Process");
	nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
	///////////////
	delete str;
	return nResult;
}

void CCurDel::OnEBoxRButtonUp_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
								UINT nFlags, CPoint point)
{
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
	//////////////////////////////// do nothing Op
	return;
}

/////////////////////////////////////////////////////////////////////////////////////// F_M
UINT CCurDel::ReSetToolID_CUR(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	//////////////////////////////////////////// TaskID
	strCur = "Ready for Deleting@";
	/////////////////////////////
	switch(OperID)
	{
		//////////////////////////////////////////// Create
		case GOP_DELETE:
		{
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
						case CURVE:			str = "CURVE";			ID = C_DELETE;
								strCur += "Click on a Curve";	break;
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
/*
				case CURVE:				return C_MOVE;
				case CURVE:				return C_POST;
				case CURVE:				return C_UNPOST;
				case CURVE:				return C_DELETE;
*/
}
	

void CCurDel::Serialize(CArchive& ar)
{

	CNodDel::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CurDel:    Storing\n");	
		

	}
	else
	{
		TRACE(" CurDel:    Loading\n");	

	
	}        
	//////////////////
}

///////////////////////////////////// end of Module //////////////////////		


