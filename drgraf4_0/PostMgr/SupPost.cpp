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
///////////////////// Supports
#include "Str_Supp.h"
#include "Def_Supp.h"
#include "MI_LSupp.h" 
//////////////////////
#include "SupDel.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CSupDel,CSolDel,1)
/////////////////////////////////////////////////////////////////////////////
CSupDel::CSupDel()
{

}

CSupDel::~CSupDel()
{
}

void CSupDel:: ElementLeftDown_SUP()
{	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////
	SetMainType_SUP();
	/////////////
}

int CSupDel::ShowLinSuppToBeDeleted(CDrLinSup* pDrLinSup, BOOL bToBeDeleted)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr*	pObjList;
	int			nActiveIndex;
	///////////////////
	if(!pDrLinSup)
		return 0;
	////////////////
	pDrLinSup->SetShow(FALSE);
	pDrLinSup->SetToBeDeleted(bToBeDeleted);
	///////////////////
//	CDrLabel* pDrLabel = (CDrLabel*)(pDrNode->GetLabelList()->GetHead());
//	pDrLabel->SetToBeDeleted(bToBeDeleted);
	///////////////////
	pDrLinSup->SetShow(TRUE);
	/////////////////////////////
	pObjList = pObjectMgr->GetObjectList(LIN_SUPPORT);
	nActiveIndex = pObjList->GetObjectIndex(LIN_SUPPORT,pDrLinSup->GetObjectID());
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
	pObjectMgr->SetActiveObjectType(LIN_SUPPORT);	    // set Active Index									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,LIN_SUPPORT);
	///////////////////////////////
	return 0;
}	 

int CSupDel::MarkLinSupp_Delete(CDrLinSup* pDrLinSup)
{
	//////////////////////////////////////////////////////// if Marked Deleted: Continue
	if(pDrLinSup->IsDeleted())
		return 0;
	////////////////
	if(pDrLinSup)
	{
		pDrLinSup->SetShow(FALSE);
		pDrLinSup->SetDeleted(TRUE);
		///////////////////
//		CDrLabel* pDrLabel = (CDrLabel*)(pDrNode->GetLabelList()->GetHead());
//		pDrLabel->SetDeleted(TRUE);
		///////////////////
		pDrLinSup->SetShow(TRUE);
	}
	///////////////////////////////
	return 0;
}	 
	
int CSupDel::MarkNodeLinSupp_Delete(CDrNode* pDrNode, int nType, BOOL bToBeDeleted)
{
	//	nType = 1	: ToBeDeleted or UnDeleted Based on bToBeDeleted
	//	nType = 2	: Delete
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	////////////////////////////////////////////////////////////////////// Dependent LinSup
	CDListMgr*	pSupList;
	int			i,nSupCount;
	POSITION	pos;
	//////////////////////////////////////////////// LinSups
	pSupList	= pDrNode->GetSuppList(); 
	nSupCount	= pSupList->GetCount();
	///////////
	for(i=0;i<nSupCount;i++)
	{
		pos					= pSupList->FindIndex(i);
		CDrLinSup* pDrLinSup	= (CDrLinSup*)(pSupList->GetAt(pos));
		////////////////////
		switch(nType)
		{
			case 1:
			//////////////////////////////////////////////////////// Mark Deleted
				ShowLinSuppToBeDeleted(pDrLinSup,bToBeDeleted);
				break;
			case 2:
			//////////////////////////////////////////////////////// Mark Deleted
				MarkLinSupp_Delete(pDrLinSup);
				break;
		}
	}
	//////////////////////////////////////////////////////////////// Update ShowStuff, if Delete
	if(nType == 2)
	{
		pDoc->SetModifiedFlag();
		pDoc->UpdateAllViews(NULL);
	}
	///////////////////////////////
	return 0;
}	 
	
int CSupDel::MarkCurveLinSupp_Delete(CDrCurve* pDrCurve, int nType, BOOL bToBeDeleted)
{
	//	nType = 1	: ToBeDeleted or UnDeleted Based on bToBeDeleted
	//	nType = 2	: Delete
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	////////////////////////////////////////////////////////////////////// Dependent LinSup
	CDListMgr*	pSupList;
	int			i,nSupCount;
	POSITION	pos;
	//////////////////////////////////////////////// LinSups
	pSupList	= pDrCurve->GetSuppList(); 
	nSupCount	= pSupList->GetCount();
	///////////
	for(i=0;i<nSupCount;i++)
	{
		pos					= pSupList->FindIndex(i);
		CDrLinSup* pDrLinSup	= (CDrLinSup*)(pSupList->GetAt(pos));
		////////////////////
		switch(nType)
		{
			case 1:
			//////////////////////////////////////////////////////// Mark Deleted
				ShowLinSuppToBeDeleted(pDrLinSup,bToBeDeleted);
				break;
			case 2:
			//////////////////////////////////////////////////////// Mark Deleted
				MarkLinSupp_Delete(pDrLinSup);
				break;
		}
	}
	//////////////////////////////////////////////////////////////// Update ShowStuff, if Delete
	if(nType == 2)
	{
		pDoc->SetModifiedFlag();
		pDoc->UpdateAllViews(NULL);
	}
	///////////////////////////////
	return 0;
}	 

int CSupDel::MarkPatchLinSupp_Delete(CDrPatch* pDrPatch, int nType, BOOL bToBeDeleted)
{
	//	nType = 1	: ToBeDeleted or UnDeleted Based on bToBeDeleted
	//	nType = 2	: Delete
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	////////////////////////////////////////////////////////////////////// Dependent LinSup
	CDListMgr*	pSupList;
	int			i,nSupCount;
	POSITION	pos;
	//////////////////////////////////////////////// LinSups
	pSupList	= pDrPatch->GetSuppList(); 
	nSupCount	= pSupList->GetCount();
	///////////
	for(i=0;i<nSupCount;i++)
	{
		pos						= pSupList->FindIndex(i);
		CDrLinSup* pDrLinSup	= (CDrLinSup*)(pSupList->GetAt(pos));
		////////////////////
		switch(nType)
		{
			case 1:
			//////////////////////////////////////////////////////// Mark Deleted
				ShowLinSuppToBeDeleted(pDrLinSup,bToBeDeleted);
				break;
			case 2:
			//////////////////////////////////////////////////////// Mark Deleted
				MarkLinSupp_Delete(pDrLinSup);
				break;
		}
	}
	//////////////////////////////////////////////////////////////// Update ShowStuff, if Delete
	if(nType == 2)
	{
		pDoc->SetModifiedFlag();
		pDoc->UpdateAllViews(NULL);
	}
	///////////////////////////////
	return 0;
}

int CSupDel::MarkSolidLinSupp_Delete(CDrSolid* pDrSolid, int nType, BOOL bToBeDeleted)
{
	//	nType = 1	: ToBeDeleted or UnDeleted Based on bToBeDeleted
	//	nType = 2	: Delete
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	////////////////////////////////////////////////////////////////////// Dependent LinSup
	CDListMgr*	pSupList;
	int			i,nSupCount;
	POSITION	pos;
	//////////////////////////////////////////////// LinSups
	pSupList	= pDrSolid->GetSuppList(); 
	nSupCount	= pSupList->GetCount();
	///////////
	for(i=0;i<nSupCount;i++)
	{
		pos						= pSupList->FindIndex(i);
		CDrLinSup* pDrLinSup	= (CDrLinSup*)(pSupList->GetAt(pos));
		////////////////////
		switch(nType)
		{
			case 1:
			//////////////////////////////////////////////////////// Mark Deleted
				ShowLinSuppToBeDeleted(pDrLinSup,bToBeDeleted);
				break;
			case 2:
			//////////////////////////////////////////////////////// Mark Deleted
				MarkLinSupp_Delete(pDrLinSup);
				break;
		}
	}
	//////////////////////////////////////////////////////////////// Update ShowStuff, if Delete
	if(nType == 2)
	{
		pDoc->SetModifiedFlag();
		pDoc->UpdateAllViews(NULL);
	}
	///////////////////////////////
	return 0;
}

void CSupDel::OnEBoxLButtonDown_SUP(CClientDC* pdc,CView* pView,GENERATE gener,
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
	pDListMgr 	= pObjectMgr->GetObjectList(LIN_SUPPORT);
	if(pDListMgr->GetCount()<=0)
		return;
	/////////////////////////////////////////////////////////////////
    /////////////////////////////  ELement Dialog On/Off Check
    if(m_Gener == FORWARD)
		ElementLeftDown_SUP();
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftDown_I();
	//////////////////////////////////
}

int CSupDel::ShowInfo_NodeLinSupport(CDrNode* pDrNode, char* buf, int jStart)
{
	int j = jStart;
	////////////////////////////////////////
	// The List Should Have ATMOST 2 items:
	//			1	Lin_Spring 
	//			1	Lin_Snubber
	////////////////////////////////////////
	CDListMgr* pList = pDrNode->GetSuppList();
	///////////////////////////////
	if(pList->GetCount() > 2)
	{
		AfxMessageBox("Internal ERROR:\nCSupDel::FillInfo_NodeLinSupport\npList->GetCount() > 2"); 
		return -2;
	}
	////////////////////////////////////////////////////////////////////////
	int i;
	CDrLinSup*	pDrLinSup;
	SUPPCARD	supCard;
	/////////////////////////////////////////////////////////// Go Over List
	for(i=0;i<pList->GetCount();i++)
	{
		if(i==0)
			pDrLinSup = (CDrLinSup*)pList->GetHead();
		else
			pDrLinSup = (CDrLinSup*)pList->GetTail();
		////
		if(pDrLinSup)
			supCard = *(pDrLinSup->GetSuppCard());					
		else
		{
			AfxMessageBox("Internal ERROR:\nCSupDel::FillInfo_NodeLinSupport\npDrLinSup=NULL"); 
			return -2;
		}
		//////
		CString		Nid;
		/////////////////////////////////////////
		switch (supCard.SuppProc)
		{
			case SUP_RIGID:
				j = FillInfo_Rigid(supCard, buf, j);
				break;
			case SUP_LINSPR:	// fall thro'
			case SUP_LINSNU:
				Nid = pDrNode->GetObjectID();
				j	= FillInfo_SprOrSnu(Nid, supCard, buf, j, FALSE);
				break;
/*	These will be in separate List: NSupList
						case SUP_NONSPR:
							j += sprintf(buf+j,"\n\nSupportType = NONLINEAR SPRING\n");
							FillInfo_NonSpring(supCard,buf,j);
							break;
						case SUP_NONSNU:
							j += sprintf(buf+j,"\n\nSupportType = NONLINEAR SNUBBER\n");
							FillInfo_NonSnubber(supCard,buf,j);
							break;
*/ 
			default:
				break;
		}
	}
	/////////////////////////// 
	m_pCurrentSupp = pDrLinSup;
	///////////////////////////
	return j;
}

int CSupDel::FillInfo_Rigid(SUPPCARD supCard,char* buf, int jStart)
{

	int j = jStart;
	///////////////
	j += sprintf(buf+j,"\nSupportID = %s\n",supCard.sup_id);
	j += sprintf(buf+j,"\n\tStiffness = %s\n",supCard.stiffness);
	/////////
	return j;
}

int CSupDel::FillInfo_SprOrSnu(CString& Nid,SUPPCARD supCard,char* buf, int jStart,BOOL bPat)
{
	CString dir[] = {"X","Y","Z"};
	//////////////////////////////
	BOOL bTan = supCard.bTan; 
	/////////////////////////
	int i, j = jStart;
	///////////////
	if(supCard.SuppProc == SUP_LINSPR) 
		j += sprintf(buf+j,"\n\nSupportType = LINEAR SPRING\n");
	else
	if(supCard.SuppProc == SUP_LINSNU) 
		j += sprintf(buf+j,"\n\nSupportType = LINEAR SNUBBER\n");
	else
		return -2;
	//////////////
	j += sprintf(buf+j,"\nSupportID = %s\n",supCard.sup_id);
	j += sprintf(buf+j,"\n\tStiffness = %f\n",supCard.stiffness);
	/////////////////////////////////////////////////////////////////////// Translational
	j += sprintf(buf+j,"\n\tTranslational:\n");
	for(i=0;i<3;i++)
	{
		if((BOOL)supCard.kode[i])
			j += sprintf(buf+j,"\t\tDirection %s = SUPPORTED\n", dir[i]);
		else
			j += sprintf(buf+j,"\t\tDirection %s = UNSUPPORTED\n", dir[i]);
	}
	/////////////////////////////////////////////////////////////////////// Rotational
	j += sprintf(buf+j,"\n\tRotational:\n");
	for(i=3;i<6;i++)
	{
		if((BOOL)supCard.kode[i])
			j += sprintf(buf+j,"\t\tDirection %s = SUPPORTED\n", dir[i-3]);
		else
			j += sprintf(buf+j,"\t\tDirection %s = UNSUPPORTED\n", dir[i-3]);
	}
	/////////////////////////////////////////////////////////////////////// Skewed
	if(supCard.nid_a != "")		// for Node Support Input
	{	
			j += sprintf(buf+j,"\nJoint Coordinate is Skewed with\n");
			j += sprintf(buf+j,"X-axis defined by Nodes:\n");
			j += sprintf(buf+j,"\t%s and %s\n",Nid,supCard.nid_a);
	}
	else
	if(bTan)
	{
		if(bPat)		// for Patch Support Input
		{
			j += sprintf(buf+j,"\nJoint Coordinate is Skewed with\n");
			j += sprintf(buf+j,"Y-axis along Normals to Surface\n");
		}
		else			// for Curve Support Input
		{
			j += sprintf(buf+j,"\nJoint Coordinate is Skewed with\n");
			j += sprintf(buf+j,"X-axis along Tangents to Curve\n");
		}
	}
	/////////////////////////////////////////////////////////////////////// PseudoGap
	BOOL bGap = FALSE;
	for(i=0;i<6;i++)
	{
		if((BOOL)supCard.pgap[i])
		{
			bGap = TRUE;
			break;
		}
	}
	////////
	if(bGap)
	{
		j += sprintf(buf+j,"\nSupport Modeled as PseudoGap(s)\n");
		////
		j += sprintf(buf+j,"\n\tTranslational:\n");
		for(i=0;i<3;i++)
		{
			if((BOOL)supCard.pgap[i])
				j += sprintf(buf+j,"\t\tDirection %s = GAP\n", dir[i]);
			else
				j += sprintf(buf+j,"\t\tDirection %s = NONE\n", dir[i]);
		}
		////
		j += sprintf(buf+j,"\n\tRotational:\n");
		for(i=3;i<6;i++)
		{
			if((BOOL)supCard.pgap[i])
				j += sprintf(buf+j,"\t\tDirection %s = GAP\n", dir[i-3]);
			else
				j += sprintf(buf+j,"\t\tDirection %s = NONE\n", dir[i-3]);
		}
		////
	}
	/////////
	return j;
}

int CSupDel::LeftUp_NodeLinSupp(CPoint point)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 			= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(NODE);
	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CDrNode*	pDrNode;
	int			nActiveIndex,index,nResult;
	WORLD		wLoc;
	BOOL		bNew	= TRUE;
	///////////////////////////////////////////// See if any Existing Node Hit
	index = IsObjectHit(NODE,point,0);
	//////////////
	if(index<0)
		return -2;
	//////////////////////////////////////////////////////////////// Existing Node
	pDrNode				= (CDrNode*)pDListMgr->GetObject(index);
	if(pDrNode->GetSuppList()->IsEmpty())
		return -2;
	ID					= pDrNode->GetObjectID();
	/////////////////////////////////////////
	pList = pObjectMgr->GetObjectList(NODE);
	nActiveIndex = pList->GetObjectIndex(NODE, ID);;
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
	pObjectMgr->SetActiveObjectType(NODE);		    // set Active Index									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,NODE);
	//////////////////////////////////////////////////////////////// MultipleSearch
	int startIndex = index+1;
	/////////////////////////
	if(!m_bAutoAcceptOn)
	{
		for(;;)
		{
			CString* str = new CString;
			char* buf = str->GetBuffer(BUFF_SIZE);
			int j;
			/////////////////////////////// Coords
			wLoc = *(pDrNode->GetLocalPos());
			WORtoWOP(&wLoc,&wLoc);	// to Physical
			//////////////////////////////
			pList = pDrNode->GetSuppList();
			//////////////
			j = sprintf(buf,"***** Selected Node Support Info  *****\n");
			j += sprintf(buf+j,"\nNodeID = %s\nCoordinates:\n\t X = %f\n\t Y = %f\n\t Z = %f\n",
							ID,wLoc.x,wLoc.y,wLoc.z);
			//////////////////////////
			j = ShowInfo_NodeLinSupport(pDrNode, buf, j);
			if(j<0)
				return -2;
			////////////////////////////
			j += sprintf(buf+j,
				"\n\nYES:\tDelete This Node-Based Support");
			//////////////////////////
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
				//////////////////////////////////////////////////////// Accept Old
				delete str;
				break;
			}
			else
			if(nResult == IDNO)
			{
				//////////////////////////////////////////////////////// Retry
				index = IsObjectHit(NODE,point,startIndex);
				if(index>=0)
				{
					pDrNode	= (CDrNode*)pDListMgr->GetObject(index);
					ID		= pDrNode->GetObjectID();
					///////////////////////////////////////// 
					pList = pObjectMgr->GetObjectList(NODE);
					nActiveIndex = pList->GetObjectIndex(NODE, ID);;
					pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
					pObjectMgr->SetActiveObjectType(NODE);		    // set Active Index									
					pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,NODE);
					////////////////////////////////////////
					startIndex  = index+1;
					/////////////////////
				}
				else
				{
					////////////////
					delete str;
					return -2;
				}
				/////////
			}
			else				// Cancel
			{
				//////////////////////////////////////////////////////// Do Nothing
				delete str;
				return -2;
			}
		}						// end for loop
	}				// !AutoAccept
	//////////////////////////////////////////////////////////////// Show LinSup
	m_pCurrentNode = pDrNode;
	/////////////////////////////
	if(MarkNodeLinSupp_Delete(pDrNode,1,TRUE)<0)		// 
	{
		AfxMessageBox("ERROR:\nCSupDel::LeftUp_NodeSup\nMarkNodeLinSupp_Delete Problem");
		return -1;
	}
	//////////////////////////////////////////////////////////////////// Warning
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	/////////////
	int j;
	//////////////////////////////
	j = sprintf(buf		,"				***** WARNING !!! ****\n\n");
	j += sprintf(buf+j	,"		   SUPPORT %s is About to be DELETED\n");
	j += sprintf(buf+j	,"     This Will DELETE Affected Objects Shown\n\n\n",ID);
	////////////////////////////
	j += sprintf(buf+j,  "		YES:\t\tDelete This Support\n");
	j += sprintf(buf+j,"		NO:\t\tCancel Deletion Process");
	nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
	delete str;
	///////////
	if(nResult == IDYES)
		//////////////////////////////////////////////////////// Delete
		MarkNodeLinSupp_Delete(pDrNode,2,TRUE);
	else
	{
		//////////////////////////////////////////////////////// Show Normal/Cancel
		MarkNodeLinSupp_Delete(pDrNode,1,FALSE);
		return -2;
	}
	////////////////////////////////////////////////////////////////
	strCurr = "Ready for Deleting@";
	strCurr += "Another Support";
	//////
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////////////////////////////////////
	return 0;
}

int CSupDel::ShowInfo_CurveLinSupport(CDrCurve* pDrCurve, char* buf, int jStart)
{
	int j = jStart;
	///////////////
	CDListMgr* pList;
	///////////////////////////////////////////////////////////// Support Info
	pList = pDrCurve->GetSuppList();
	///////////////////////////////
	if(pList->GetCount() > 2)
	{
		AfxMessageBox("Internal ERROR:\nCSupDel::ShowInfo_CurveLinSupport\npList->GetCount() > 2"); 
		return -2;
	}
	////////////////////////////////////////////////////////////////////////
	int i;
	CDrLinSup*	pDrLinSup;
	SUPPCARD	supCard;
	/////////////////////////////////////////////////////////// Go Over List
	for(i=0;i<pList->GetCount();i++)
	{
		if(i==0)
			pDrLinSup = (CDrLinSup*)pList->GetHead();
		else
			pDrLinSup = (CDrLinSup*)pList->GetTail();
		////
		if(pDrLinSup)
			supCard = *(pDrLinSup->GetSuppCard());					
		else
		{
			AfxMessageBox("Internal ERROR:\nCSupDel::ShowInfo_CurveLinSupport\npDrLinSup=NULL"); 
			return -2;
		}
		//////
		CString		Cid;
		/////////////////////////////////////////
		switch (supCard.SuppProc)
		{
			case SUP_RIGID:
				j = FillInfo_Rigid(supCard, buf, j);
				break;
			case SUP_LINSPR:	// fall thro'
			case SUP_LINSNU:
				Cid = pDrCurve->GetObjectID();
				j	= FillInfo_SprOrSnu(Cid, supCard, buf, j, FALSE);		//Cid ?????????????
				break;
/*	These will be in separate List: NSupList
						case SUP_NONSPR:
							j += sprintf(buf+j,"\n\nSupportType = NONLINEAR SPRING\n");
							FillInfo_NonSpring(supCard,buf,j);
							break;
						case SUP_NONSNU:
							j += sprintf(buf+j,"\n\nSupportType = NONLINEAR SNUBBER\n");
							FillInfo_NonSnubber(supCard,buf,j);
							break;
*/ 
			default:
				break;
		}
	}
	/////////////////////////// 
	m_pCurrentSupp = pDrLinSup;
	///////////////////////////
	return j;
}

int CSupDel::LeftUp_CurveLinSupp(CPoint point)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(CURVE);
	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CDrCurve*	pDrCurve;
	int			nActiveIndex,index,nResult;
	BOOL		bNew	= TRUE;
	///////////////////////////////////////////// See if any Existing Curve Hit
	index = IsObjectHit(CURVE,point,0);
	//////////////
	if(index<0)
		return -2;
	//////////////////////////////////////////////////////////////// Existing Curve
	pDrCurve				= (CDrCurve*)pDListMgr->GetObject(index);
	if(pDrCurve->GetSuppList()->IsEmpty())
		return -2;
	ID						= pDrCurve->GetObjectID();
	/////////////////////////////////////////
	pList = pObjectMgr->GetObjectList(CURVE);
	nActiveIndex = pList->GetObjectIndex(CURVE, ID);;
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
	pObjectMgr->SetActiveObjectType(CURVE);		    // set Active Index									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CURVE);
	//////////////////////////////////////////////////////////////// MultipleSearch
	int startIndex = index+1;
	/////////////////////////
	if(!m_bAutoAcceptOn)
	{
		for(;;)
		{
			CString* str = new CString;
			char* buf = str->GetBuffer(BUFF_SIZE);
			int j;
			///////////////////////////////////////// Check if This Curve is Already Supported
			pList = pDrCurve->GetSuppList();
			//////////////
			j = sprintf(buf,"***** Selected Curve Support Info  *****\n\n");
			/////////////////////////////// total elems
			int nIn		= pDrCurve->GetMaxINodes_S();
			int nElems	= pDrCurve->GetMaxOutPts_S()-1;
			pList		= pDrCurve->GetINodeList();
			//////////////////////////////
			j += sprintf(buf+j,"Curve %s contains:\n\t%d Interpolation Nodes\n\t%d Elements",
							ID,nIn,nElems);
			j += sprintf(buf+j,"Nodes:\n");
			//////////////////////////////
			for (POSITION posI = pList->GetHeadPosition( );posI !=NULL;)
			{
				////
				CDrNode* pNode = (CDrNode*)pList->GetNextObject(posI);
				j += sprintf(buf+j,"%s, ",pNode->GetObjectID());
			}
			sprintf( buf + j-2, ";");
			////////////////////////////
			j = ShowInfo_CurveLinSupport(pDrCurve, buf, j);
			if(j<0)
				return -2;
			////////////////////////////
			j += sprintf(buf+j,
				"\n\nYES:\t\tEdit This Curve-Based Support");
			j += sprintf(buf+j,
				"\nNO:\t\tFind Next Curve with similar Trace");
			j += sprintf(buf+j,
				"\nCANCEL:\t\tCancel Selection Process");
			////////////////////////////
			nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
			/////////////
			if(nResult == IDYES)
			{
				//////////////////////////////////////////////////////// Accept Old
				delete str;
				break;
			}
			else
			if(nResult == IDNO)
			{
				////////////////////////////////
				index = IsObjectHit(CURVE,point,startIndex);
				if(index<0)
				{
					////////////////
					delete str;
					return -2;
					//////////
				}
				//////////
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
			else				// Cancel
			{
				//////////////////////////////////////////////////////// Do Nothing
				delete str;
				return -2;
			}
		}
	}
	//////////////////////////////////////////////////// Gotch'a Curve/ Show LinSup
	m_pCurrentCurve			= (CDrCurve*)pDListMgr->GetObject(index);
	/////////////////////////////
	if(MarkCurveLinSupp_Delete(pDrCurve,1,TRUE)<0)		// 
	{
		AfxMessageBox("ERROR:\nCSupDel::LeftUp_CurveSup\nMarkCurveLinSupp_Delete Problem");
		return -1;
	}
	//////////////////////////////////////////////////////////////////// Warning
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	/////////////
	int j;
	//////////////////////////////
	j = sprintf(buf		,"				***** WARNING !!! ****\n\n");
	j += sprintf(buf+j	,"		   SUPPORT %s is About to be DELETED\n");
	j += sprintf(buf+j	,"     This Will DELETE Affected Objects Shown\n\n\n",ID);
	////////////////////////////
	j += sprintf(buf+j,  "		YES:\t\tDelete This Support\n");
	j += sprintf(buf+j,"		NO:\t\tCancel Deletion Process");
	nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
	delete str;
	///////////
	if(nResult == IDYES)
		//////////////////////////////////////////////////////// Delete
		MarkCurveLinSupp_Delete(pDrCurve,2,TRUE);
	else
	{
		//////////////////////////////////////////////////////// Show Normal/Cancel
		MarkCurveLinSupp_Delete(pDrCurve,1,FALSE);
		return -2;
	}
	////////////////////////////////////////////////////////////////
	strCurr = "Ready for Deleting@";
	strCurr += "Another Support";
	//////
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////////////////////////////////////
	return 0;
}

int CSupDel::ShowInfo_PatchLinSupport(CDrPatch* pDrPatch, char* buf, int jStart)
{
	int j = jStart;
	///////////////
	CDListMgr* pList;
	///////////////////////////////////////////////////////////// Support Info
	pList = pDrPatch->GetSuppList();
	///////////////////////////////
	if(pList->GetCount() > 2)
	{
		AfxMessageBox("Internal ERROR:\nCSupDel::ShowInfo_PatchLinSupport\npList->GetCount() > 2"); 
		return -2;
	}
	////////////////////////////////////////////////////////////////////////
	int i;
	CDrLinSup*	pDrLinSup;
	SUPPCARD	supCard;
	/////////////////////////////////////////////////////////// Go Over List
	for(i=0;i<pList->GetCount();i++)
	{
		if(i==0)
			pDrLinSup = (CDrLinSup*)pList->GetHead();
		else
			pDrLinSup = (CDrLinSup*)pList->GetTail();
		////
		if(pDrLinSup)
			supCard = *(pDrLinSup->GetSuppCard());					
		else
		{
			AfxMessageBox("Internal ERROR:\nCSupDel::ShowInfo_PatchLinSupport\npDrLinSup=NULL"); 
			return -2;
		}
		//////
		CString		Cid;
		/////////////////////////////////////////
		switch (supCard.SuppProc)
		{
			case SUP_RIGID:
				j = FillInfo_Rigid(supCard, buf, j);
				break;
			case SUP_LINSPR:	// fall thro'
			case SUP_LINSNU:
				Cid = pDrPatch->GetObjectID();
				j	= FillInfo_SprOrSnu(Cid, supCard, buf, j, TRUE);		//Cid ?????????????
				break;
/*	These will be in separate List: NSupList
						case SUP_NONSPR:
							j += sprintf(buf+j,"\n\nSupportType = NONLINEAR SPRING\n");
							FillInfo_NonSpring(supCard,buf,j);
							break;
						case SUP_NONSNU:
							j += sprintf(buf+j,"\n\nSupportType = NONLINEAR SNUBBER\n");
							FillInfo_NonSnubber(supCard,buf,j);
							break;
*/ 
			default:
				break;
		}
	}
	/////////////////////////// 
	m_pCurrentSupp = pDrLinSup;
	///////////////////////////
	return j;
}

int CSupDel::LeftUp_PatchLinSupp(CPoint point)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(PATCH);
	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CDrPatch*	pDrPatch;
	int			nActiveIndex,index,nResult;
	BOOL		bNew	= TRUE;
	///////////////////////////////////////////// See if any Existing Curve Hit
	index = IsObjectHit(PATCH,point,0);
	//////////////
	if(index<0)
		return -2;
	//////////////////////////////////////////////////////////////// Existing Patch
	pDrPatch				= (CDrPatch*)pDListMgr->GetObject(index);
	if(pDrPatch->GetSuppList()->IsEmpty())
		return -2;
	ID						= pDrPatch->GetObjectID();
	/////////////////////////////////////////
	pList = pObjectMgr->GetObjectList(PATCH);
	nActiveIndex = pList->GetObjectIndex(PATCH, ID);;
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
	pObjectMgr->SetActiveObjectType(PATCH);		    // set Active Index									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,PATCH);
	//////////////////////////////////////////////////////////////// MultipleSearch
	int startIndex = index+1;
	/////////////////////////
	if(!m_bAutoAcceptOn)
	{
		for(;;)
		{
			CString* str = new CString;
			char* buf = str->GetBuffer(BUFF_SIZE);
			int j;
			///////////////////////////////////////// Check if This Patch is Already Supported
			pList = pDrPatch->GetSuppList();
			//////////////
			j = sprintf(buf,"***** Selected Patch Support Info  *****\n\n");
			//////////////////////////////
			if(pDrPatch->GetPatSubType() == PS_QUADRILAT)
			j += sprintf(buf+j,"Patch %s is \n\tQuadrilateral Type\n",ID);
			if(pDrPatch->GetPatSubType() == PS_TRIANGLE)
				j += sprintf(buf+j,"Patch %s is \n\tTriangular Type\n",ID);
			////////////////////////////
			j = ShowInfo_PatchLinSupport(pDrPatch, buf, j);
			if(j<0)
				return -2;
			////////////////////////////
			j += sprintf(buf+j,
				"\n\nYES:\t\tEdit This Patch-Based Support");
			j += sprintf(buf+j,
				"\nNO:\t\tFind Next Matching Patch");
			j += sprintf(buf+j,
				"\nCANCEL:\t\tCancel Selection Process");
			////////////////////////////
			nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
			/////////////
			if(nResult == IDYES)
			{
				delete str;
				break;
			}
			else
			if(nResult == IDNO)
			{
				////////////////////////////////
				index = IsObjectHit(PATCH,point,startIndex);
				if(index<0)
				{
					////////////////
					delete str;
					return -2;
					//////////
				}
				//////////
				pDrPatch	= (CDrPatch*)pDListMgr->GetObject(index);
				ID			= pDrPatch->GetObjectID();
				///////////////////////////////////////// 
				pList = pObjectMgr->GetObjectList(PATCH);
				nActiveIndex = pList->GetObjectIndex(PATCH, ID);;
				pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
				pObjectMgr->SetActiveObjectType(PATCH);		    // set Active Index									
				pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,PATCH);
				////////////////////////////////////////
				startIndex  = index+1;
				/////////////////////
			}
			else				// Cancel
			{
				//////////////////////////////////////////////////////// Do Nothing
				delete str;
				return -2;
			}
		}
	}
	//////////////////////////////////////////////////// Gotch'a Patch/ Show LinSup
	m_pCurrentPatch			= (CDrPatch*)pDListMgr->GetObject(index);
	/////////////////////////////
	if(MarkPatchLinSupp_Delete(pDrPatch,1,TRUE)<0)		// 
	{
		AfxMessageBox("ERROR:\nCSupDel::LeftUp_PatchSup\nMarkPatchLinSupp_Delete Problem");
		return -1;
	}
	//////////////////////////////////////////////////////////////////// Warning
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	/////////////
	int j;
	//////////////////////////////
	j = sprintf(buf		,"				***** WARNING !!! ****\n\n");
	j += sprintf(buf+j	,"		   SUPPORT %s is About to be DELETED\n");
	j += sprintf(buf+j	,"     This Will DELETE Affected Objects Shown\n\n\n",ID);
	////////////////////////////
	j += sprintf(buf+j,  "		YES:\t\tDelete This Support\n");
	j += sprintf(buf+j,"		NO:\t\tCancel Deletion Process");
	nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
	delete str;
	///////////
	if(nResult == IDYES)
		//////////////////////////////////////////////////////// Delete
		MarkPatchLinSupp_Delete(pDrPatch,2,TRUE);
	else
	{
		//////////////////////////////////////////////////////// Show Normal/Cancel
		MarkPatchLinSupp_Delete(pDrPatch,1,FALSE);
		return -2;
	}
	////////////////////////////////////////////////////////////////
	strCurr = "Ready for Deleting@";
	strCurr += "Another Support";
	//////
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////////////////////////////////////
	return 0;
}

int CSupDel::ShowInfo_SolidLinSupport(CDrSolid* pDrSolid, char* buf, int jStart)
{
	return -1;
}

int CSupDel::LeftUp_SolidLinSupp(CPoint point)
{
	return -1;
}

void CSupDel::ElementLeftUp_SUP(CPoint point)
{                          

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	//////////////////////////////////////////////////////////////////
//	CString*	pID;
	/////////////
//	char buf[20];
	CString Nid;
	///////////////////
	SetMainType_SUP();
	///////////////////
	switch(m_nMainType) 
	{
		
		///////////////////////////////////////////////////// Node Based										
		///////////////////////////////////// LinSup										
		case NSUP_DELETE:

			////////////////////
			LeftUp_NodeLinSupp(point);	
			////////////////////
			break;

		///////////////////////////////////// NonSup										
		case NSUP_NLSPRING:
		case NSUP_NLSNUBBER:
			break;
		///////////////////////////////////////////////////// Curve Based										
		///////////////////////////////////// LinSup										
		case CSUP_DELETE:

			////////////////////
			LeftUp_CurveLinSupp(point);	
			//////////////////// 
			break;
		///////////////////////////////////// NonSup										
		case CSUP_NLSPRING:
		case CSUP_NLSNUBBER:
			break;
		///////////////////////////////////////////////////// Patch Based										
		///////////////////////////////////// LinSup										
		case PSUP_DELETE:

			////////////////////
			LeftUp_PatchLinSupp(point);	
			////////////////////
			break;

		///////////////////////////////////// NonSup										
		case PSUP_NLSPRING:
		case PSUP_NLSNUBBER:
			break;
		///////////////////////////////////////////////////// Solid Based										
		///////////////////////////////////// LinSup										
		case SSUP_DELETE:

			////////////////////
			LeftUp_SolidLinSupp(point);	
			////////////////////
			break;

		///////////////////////////////////// NonSup										
		case SSUP_NLSPRING:
		case SSUP_NLSNUBBER:
			break;
		//////////////////////////////////////////////////
		default:  
			break;
	} 
}	

void CSupDel::OnEBoxMouseMove_SUP(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point)
{  

	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
	////////////////////////////////// do nothing for now
	return;
}

void CSupDel::OnEBoxLButtonUp_SUP(CClientDC* pdc,CView* pView,GENERATE gener,
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
		ElementLeftUp_SUP(Logpoint);
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftUp_I();
	/////////////////////////
	
}

void CSupDel::OnEBoxRButtonDown_SUP(CClientDC* pdc,CView* pView,GENERATE gener,
									UINT nFlags, CPoint point)
{ 
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
	///////////////////////////////// do nothing
	return;
}

void CSupDel::OnEBoxRButtonUp_SUP(CClientDC* pdc,CView* pView,GENERATE gener,
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
////////////////////////////////////////////////////////////////////	
UINT CSupDel::ReSetToolID_SUP(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	//////////////////////////////////////////// TaskID
	strCur = "Ready to Delete Supports@";
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
				//////////////////////////////////////// Support
				case SUPPORT:

//					pWnd->SetMouseBoxType(SUPPORTBOX);
					str = "SUPPORT";
					pWnd->SetstrCntlID(str);
					///////////////////////////////////// RIGID
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";			ID = NSUP_DELETE;
								strCur += "A Supported Node";	break;
						case CURVE:			str = "CURVE";			ID = CSUP_DELETE;
								strCur += "A Supported Curve";	break;
						case PATCH:			str = "PATCH";			ID = PSUP_DELETE;
								strCur += "A Supported Patch";	break;
						case SOLID:			str = "SOLID";			ID = SSUP_DELETE;
								strCur += "A Supported Solid";	break;

						default:			str = "UNKNOWN";	ID = UNONE;
							strCur += "Select Node, Curve, Patch or Solid basis";	break;
					}
					pWnd->SetstrIGenID(str);
					////////////////////////
					pWnd->SetstrCurrID(strCur);
					//////////
					return ID;
			}
		}
	}
	return UNONE; 
/*
				////////////////////////////////// LINSPRING
				case SUPPORT_LINSPRING:

					pWnd->SetMouseBoxType(SUPPORTBOX);
					str = "Linear@Spring";
					pWnd->SetstrCntlID(str);
					////////////////////////////////// 
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = NSUP_LSP_NODE;			break;
						case CURVE:			str = "CURVE";		ID = CSUP_LINSPRING;		break;
						case PATCH:			str = "PATCH";		ID = PSUP_LINSPRING;		break;
						case SOLID:			str = "SOLID";		ID = SSUP_LINSPRING;		break;

						default:			str = "UNKNOWN";	ID = UNONE;					break;
					}
					pWnd->SetstrIGenID(str);
					return ID;
				////////////////////////////////// LINSNUBBER
				case SUPPORT_LINSNUBBER:

					pWnd->SetMouseBoxType(SUPPORTBOX);
					str = "Linear@Snubber";
					pWnd->SetstrCntlID(str);
					////////////////////////////////// 
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = NSUP_LSN_NODE;			break;
						case CURVE:			str = "CURVE";		ID = CSUP_LINSNUBBER;		break;
						case PATCH:			str = "PATCH";			ID = PSUP_LINSNUBBER;		break;
						case SOLID:			str = "SOLID";			ID = SSUP_LINSNUBBER;		break;

						default:			str = "UNKNOWN";	ID = UNONE;					break;
					}
					pWnd->SetstrIGenID(str);
					return ID;
				////////////////////////////////// NONSPRING
				case SUPPORT_NLSPRING:

					pWnd->SetMouseBoxType(SUPPORTBOX);
					str = "NonLinear@Spring";
					pWnd->SetstrCntlID(str);
					////////////////////////////////// 
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = NSUP_NSP_NODE;			break;
						case CURVE:			str = "CURVE";		ID = CSUP_NLSPRING;			break;
						case PATCH:			str = "PATCH";			ID = PSUP_NLSPRING; 		break;
						case SOLID:			str = "SOLID";			ID = SSUP_NLSPRING;			break;

						default:			str = "UNKNOWN";	ID = UNONE;					break;
					}
					pWnd->SetstrIGenID(str);
					return ID;
				////////////////////////////////// NONSNUBBER
				case SUPPORT_NLSNUBBER:

					pWnd->SetMouseBoxType(SUPPORTBOX);
					str = "NonLinear@RESEVED";
					pWnd->SetstrCntlID(str);
					////////////////////////////////// 
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = NSUP_NSN_NODE;			break;
						case CURVE:			str = "CURVE";		ID = CSUP_NLSNUBBER;		break;
						case PATCH:			str = "PATCH";			ID = PSUP_NLSNUBBER;		break; 
						case SOLID:			str = "SOLID";			ID = SSUP_NLSNUBBER;		break;

						default:			str = "UNKNOWN";	ID = UNONE;
					}
					pWnd->SetstrIGenID(str);
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
*/
}

void CSupDel::SetMainType_SUP()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	m_nActiveTool	= pWnd->GetActiveToolType();
	m_nMainType		= m_nActiveTool;
	////////
	return;
}

void CSupDel::Serialize(CArchive& ar)
{

	CSolDel::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" SupDel:    Storing\n");	
		
 			/////////////////////////////////////////////////

	}
	else
	{
		TRACE(" SupDel:    Loading\n");	

			/////////////////////////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////		


