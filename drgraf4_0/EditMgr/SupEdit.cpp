// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
#include "drgrafrm.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
///////////////////// dialogMgr
#include "MSupMgr.h"  
///////////////////// elements
#include "Def_IGen.h"
#include "Def_Elem.h"
///////////////////// Supports
#include "Str_Supp.h"
#include "Def_Supp.h"
#include "MI_LSupp.h" 
//////////////////////
#include "SupEdit.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CSupEdit,CSolEdit,1)
/////////////////////////////////////////////////////////////////////////////
CSupEdit::CSupEdit()
{

}

CSupEdit::~CSupEdit()
{
}

void CSupEdit:: ElementLeftDown_SUP()
{	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////
	SetMainType_SUP();
	/////////////
}

void CSupEdit::NoRigidEdit_Msg()
{
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	//////////////
	j = sprintf(buf,"***** Selected Support is RIGID Support  *****\n");
	j += sprintf(buf+j,"\n\nNothing to Edit for a Rigid Support.");
	j += sprintf(buf+j,"\nIf you want:");
	j += sprintf(buf+j,"\n\tYou may First Delete this Support,");
	j += sprintf(buf+j,"\n\tthen Create new Support Type here.");
	//////////////////////////
	AfxMessageBox(*str,MB_OK|MB_ICONEXCLAMATION);
	/////////
	delete str;
}

int CSupEdit::ShowNodeLinSuppToEdit()
{
	//	Since CMI_LSupp::CreateNodeBased always delete old
	//	Support at the node, Use this function to edit	
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	pObjectMgr->SetActiveObjectType(LIN_SUPPORT);                   
	////////////////////
	SUPPPROC SuppProc	= (m_pCurrentSupp->GetSuppCard())->SuppProc;
	if(SuppProc == SUP_RIGID)
	{
		NoRigidEdit_Msg();
		return -2;
	}
	///////////////////////////////////////
	CMSupMgr* pMSupMgr;
	/////////////////////////////////////////////////////////////// Using MSupMgr
	if (pMSupMgr->DoModal_SupToEdit(m_pCurrentSupp) == IDCANCEL)
		return -2;
	/////////////////////////////////////////////////////////////// Using GangSup
	CMI_LSupp MI_LSupp;
	MI_LSupp.RegenNodeBased(m_pCurrentNode);
	///////////////////////////////
	return 0;
}	 

int CSupEdit::ShowCurveLinSuppToEdit()
{
	//	Since CMI_LSupp::CreateCurveBased always delete old
	//	Support at the node, Use this function to edit	
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	pObjectMgr->SetActiveObjectType(LIN_SUPPORT);                   
	////////////////////
	SUPPPROC SuppProc	= (m_pCurrentSupp->GetSuppCard())->SuppProc;
	if(SuppProc == SUP_RIGID)
	{
		NoRigidEdit_Msg();
		return -2;
	}
	///////////////////////////////////////
	CMSupMgr* pMSupMgr;
	/////////////////////////////////////////////////////////////// Using MSupMgr
	if (pMSupMgr->DoModal_SupToEdit(m_pCurrentSupp) == IDCANCEL)
		return -2;
	/////////////////////////////////////////////////////////////// Using GangSup
	CMI_LSupp MI_LSupp;
	MI_LSupp.RegenCurveBased(m_pCurrentCurve);
	/////////////////////
	return 0;
}	 

int CSupEdit::ShowPatchLinSuppToEdit()
{
	//	Since CMI_LSupp::CreatePatchBased always delete old
	//	Support at the node, Use this function to edit	
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	pObjectMgr->SetActiveObjectType(LIN_SUPPORT);                   
	////////////////////
	SUPPPROC SuppProc	= (m_pCurrentSupp->GetSuppCard())->SuppProc;
	if(SuppProc == SUP_RIGID)
	{
		NoRigidEdit_Msg();
		return -2;
	}
	///////////////////////////////////////
	CMSupMgr* pMSupMgr;
	/////////////////////////////////////////////////////////////// Using MSupMgr
	if (pMSupMgr->DoModal_SupToEdit(m_pCurrentSupp) == IDCANCEL)
		return -2;
	/////////////////////////////////////////////////////////////// Using GangSup
	CMI_LSupp MI_LSupp;
	///////////////////////////////
	if(m_pCurrentPatch->GetPatSubType() == PS_QUADRILAT)
		MI_LSupp.RegenPatchBased_4(m_pCurrentPatch);
	if(m_pCurrentPatch->GetPatSubType() == PS_TRIANGLE)
		MI_LSupp.RegenPatchBased_3(m_pCurrentPatch);
	///////////////////////////////
	return 0;
}

int CSupEdit::ShowSolidLinSuppToEdit()
{
	return -1;
}

void CSupEdit::OnEBoxLButtonDown_SUP(CClientDC* pdc,CView* pView,GENERATE gener,
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
//	m_bAutoAcceptOn	= pBool->IsAutoAcceptOn();
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

int CSupEdit::ShowInfo_NodeLinSupport(CDrNode* pDrNode, char* buf, int jStart)
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
		AfxMessageBox("Internal ERROR:\nCSupEdit::FillInfo_NodeLinSupport\npList->GetCount() > 2"); 
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
			AfxMessageBox("Internal ERROR:\nCSupEdit::FillInfo_NodeLinSupport\npDrLinSup=NULL"); 
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

int CSupEdit::FillInfo_Rigid(SUPPCARD supCard,char* buf, int jStart)
{

	int j = jStart;
	///////////////
	j += sprintf(buf+j,"\nSupportID = %s\n",supCard.sup_id);
	j += sprintf(buf+j,"\nStiffness = %f\n",supCard.stiffness);
	/////////
	return j;
}

int CSupEdit::FillInfo_SprOrSnu(CString& Nid,SUPPCARD supCard,char* buf, int jStart,BOOL bPat)
{
	CString dir[] = {"X","Y","Z"};
	//////////////////////////////
	BOOL bTanCur = supCard.bTanCur; 
	BOOL bTanPat = supCard.bTanPat; 
	BOOL bNorPat = supCard.bNorPat; 
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
	j += sprintf(buf+j,"\nStiffness = %f\n",supCard.stiffness);
	/////////////////////////////////////////////////////////////////////// Translational
	j += sprintf(buf+j,"\nTranslational:\n");
	for(i=0;i<3;i++)
	{
		if((BOOL)supCard.kode[i])
			j += sprintf(buf+j,"\tDirection %s = SUPPORTED\n", dir[i]);
		else
			j += sprintf(buf+j,"\tDirection %s = UNSUPPORTED\n", dir[i]);
	}
	/////////////////////////////////////////////////////////////////////// Rotational
	j += sprintf(buf+j,"\nRotational:\n");
	for(i=3;i<6;i++)
	{
		if((BOOL)supCard.kode[i])
			j += sprintf(buf+j,"\tDirection %s = SUPPORTED\n", dir[i-3]);
		else
			j += sprintf(buf+j,"\tDirection %s = UNSUPPORTED\n", dir[i-3]);
	}
	/////////////////////////////////////////////////////////////////////// Skewed
	if(supCard.nid_a != "")		// for Node Support Input
	{	
			j += sprintf(buf+j,"\nJoint Coordinate is Skewed with\n");
			j += sprintf(buf+j,"X-axis defined by Nodes:\n");
			j += sprintf(buf+j,"\t%s and %s\n",Nid,supCard.nid_a);
	}
	else
	if(bTanPat || bNorPat == bTanCur)
	{
		if(bNorPat)		// for Patch Support Input
		{
			j += sprintf(buf+j,"\nJoint Coordinate is Skewed with\n");
			j += sprintf(buf+j,"Z-axis along Normals to Surface\n");
		}
		else
		if(bTanPat)		// for Patch Support Input
		{
			j += sprintf(buf+j,"\nJoint Coordinate is Skewed with\n");
			j += sprintf(buf+j,"X, Y-axes along Iso-Curves to Surface\n");
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
		j += sprintf(buf+j,"\nTranslational:\n");
		for(i=0;i<3;i++)
		{
			if((BOOL)supCard.pgap[i])
				j += sprintf(buf+j,"\tDirection %s = GAP\n", dir[i]);
			else
				j += sprintf(buf+j,"\tDirection %s = NONE\n", dir[i]);
		}
		////
		j += sprintf(buf+j,"\nRotational:\n");
		for(i=3;i<6;i++)
		{
			if((BOOL)supCard.pgap[i])
				j += sprintf(buf+j,"\tDirection %s = GAP\n", dir[i-3]);
			else
				j += sprintf(buf+j,"\tDirection %s = NONE\n", dir[i-3]);
		}
		////
	}
	/////////
	return j;
}

int CSupEdit::LeftUp_NodeLinSupp(CPoint point)
{
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
	/////////////////////////////////////////
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
				"\n\nYES:\t\tEdit This Node-Based Support");
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
				if(index<0)
				{
					////////////////
					delete str;
					return -2;
					//////////
				}
				//////////
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
	nResult = ShowNodeLinSuppToEdit();
	///////////
	if( nResult == -1)		// 
	{
		AfxMessageBox("ERROR:\nCSupEdit::LeftUp_NodeSup\nShowLinSup Problem");
		return -1;
	}
	else
	if(nResult == -2)		// Cancel
		return -2;
	////////////////////////////
	return 0;
}

int CSupEdit::ShowInfo_CurveLinSupport(CDrCurve* pDrCurve, char* buf, int jStart)
{
	int j = jStart;
	///////////////
	CDListMgr* pList;
	///////////////////////////////////////////////////////////// Support Info
	pList = pDrCurve->GetSuppList();
	///////////////////////////////
	if(pList->GetCount() > 2)
	{
		AfxMessageBox("Internal ERROR:\nCSupEdit::ShowInfo_CurveLinSupport\npList->GetCount() > 2"); 
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
			AfxMessageBox("Internal ERROR:\nCSupEdit::ShowInfo_CurveLinSupport\npDrLinSup=NULL"); 
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

int CSupEdit::LeftUp_CurveLinSupp(CPoint point)
{
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
	nResult = ShowCurveLinSuppToEdit();
	///////////
	if( nResult == -1)		// 
	{
		AfxMessageBox("ERROR:\nCSupEdit::LeftUp_CurveSup\nShowLinSup Problem");
		return -1;
	}
	else
	if(nResult == -2)		// Cancel
		return -2;
	////////////////////////////
	return 0;
}

int CSupEdit::ShowInfo_PatchLinSupport(CDrPatch* pDrPatch, char* buf, int jStart)
{
	int j = jStart;
	///////////////
	CDListMgr* pList;
	///////////////////////////////////////////////////////////// Support Info
	pList = pDrPatch->GetSuppList();
	///////////////////////////////
	if(pList->GetCount() > 2)
	{
		AfxMessageBox("Internal ERROR:\nCSupEdit::ShowInfo_PatchLinSupport\npList->GetCount() > 2"); 
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
			AfxMessageBox("Internal ERROR:\nCSupEdit::ShowInfo_PatchLinSupport\npDrLinSup=NULL"); 
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

int CSupEdit::LeftUp_PatchLinSupp(CPoint point)
{
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
	nResult = ShowPatchLinSuppToEdit();
	///////////
	if( nResult == -1)		// 
	{
		AfxMessageBox("ERROR:\nCSupEdit::LeftUp_PatchSup\nShowLinSup Problem");
		return -1;
	}
	else
	if(nResult == -2)		// Cancel
		return -2;
	////////////////////////////
	return 0;
}

int CSupEdit::ShowInfo_SolidLinSupport(CDrSolid* pDrSolid, char* buf, int jStart)
{
	return -1;
}

int CSupEdit::LeftUp_SolidLinSupp(CPoint point)
{
	return -1;
}

void CSupEdit::ElementLeftUp_SUP(CPoint point)
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
		case NSUP_EDIT:

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
		case CSUP_EDIT:

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
		case PSUP_EDIT:

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
		case SSUP_EDIT:

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

void CSupEdit::OnEBoxMouseMove_SUP(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CSupEdit::OnEBoxLButtonUp_SUP(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CSupEdit::OnEBoxRButtonDown_SUP(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CSupEdit::OnEBoxRButtonUp_SUP(CClientDC* pdc,CView* pView,GENERATE gener,
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
UINT CSupEdit::ReSetToolID_SUP(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	//////////////////////////////////////////// TaskID
	strCur = "Ready to Edit Supports@";
	/////////////////////////////
	switch(OperID)
	{
		//////////////////////////////////////////// Create
		case GOP_EDIT:
		{
			pWnd->SetIGenBoxStatus(TRUE);
			pWnd->SetCntlBoxStatus(FALSE);
			pWnd->SetDrawBoxStatus(FALSE);
			///////////////////////////// String
			str = "EDIT";
			pWnd->SetstrOperID(str);
			/////////////////////////////
			switch(CntlID)
			{
				//////////////////////////////////////// Support
				case SUPPORT:

//					pWnd->SetMouseBoxType(SUPPORTBOX);
					str = "Support";
					pWnd->SetstrCntlID(str);
					///////////////////////////////////// RIGID
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";			ID = NSUP_EDIT;
							strCur = "Ready for Node-based Support Edit@";
							strCur += "Click on A Supported Node";	break;
						case CURVE:			str = "CURVE";			ID = CSUP_EDIT;
							strCur = "Ready for Curve-based Support Edit@";
							strCur += "Click on A Supported Curve";	break;
						case PATCH:			str = "PATCH";			ID = PSUP_EDIT;
							strCur = "Ready for Patch-based Support Edit@";
							strCur += "Click on A Supported Patch";	break;
						case SOLID:			str = "SOLID";			ID = SSUP_EDIT;
							strCur = "Ready for Solid-based Support Edit@";
							strCur += "Click on A Supported Solid";	break;

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

void CSupEdit::SetMainType_SUP()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	m_nActiveTool	= pWnd->GetActiveToolType();
	m_nMainType		= m_nActiveTool;
	////////
	return;
}

void CSupEdit::Serialize(CArchive& ar)
{

	CSolEdit::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" SupEdit:    Storing\n");	
		
 			/////////////////////////////////////////////////

	}
	else
	{
		TRACE(" SupEdit:    Loading\n");	

			/////////////////////////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////		


