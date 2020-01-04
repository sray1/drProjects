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
#include "CurEdit.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CCurEdit,CNodEdit,1)
/////////////////////////////////////////////////////////////////////////////
CCurEdit::CCurEdit()
{

	/////////////////////////////////////////// 
    m_pCurrentCurve		= NULL;
}

CCurEdit::~CCurEdit()
{
}
	
void CCurEdit::ElementLeftDown_CUR()
{	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	/////////////////////////////////////////////////////////
	switch(m_nActiveTool) 
	{
		
		////////////////////////////////////////////////// EDIT	
		case C_EDIT:				// CURVE
		//////////////////////////////////////////////////
		default:
			break;
	}  

}
	
int CCurEdit::ShowCurveToEdit(CDrCurve* pDrCurve)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	pObjectMgr->SetActiveObjectType(CURVE);
	/////////////////////////////////////////////////////////////// Using MCurMgr TODO
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	/////////////
	int j;
	/////////////////////////////// Msg
	j = sprintf(buf,"***** Please Note ****\n");
	j += sprintf(buf+j,"\n\nCurves can not be edited directly\n");
	j += sprintf(buf+j,"You may delete and rebuild a Curve\n");
	j += sprintf(buf+j,"However, you have the option of\n");
	j += sprintf(buf+j,"modifying a Curve by editng the Nodes\n");
	j += sprintf(buf+j,"making up the Curve \n");
	/////////////
	AfxMessageBox(*str,MB_OK|MB_ICONEXCLAMATION);
	delete str;
	return -2;
	////////////////////
//	CMCurMgr* pMCurMgr;
//	if (pMCurMgr->DoModal_ShowCurveToEdit(pDrCurve) == -2)
//		return -2;
	////////////////////////////////////////////////////////////////////// Update Everything
	pDoc->SetModifiedFlag();
	pDoc->UpdateAllViews(NULL);
	///////////////////////////////
	return 0;
}	 

void CCurEdit::OnEBoxLButtonDown_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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

int CCurEdit::LeftUp_CURVE(CPoint point)
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
	nResult = ShowCurveToEdit(pDrCurve);
	///////////
	if( nResult == -1)		// 
	{
		AfxMessageBox("ERROR:\nCCurEdit::LeftUp_Node\nShowCurveToEdit Problem");
		return -1;
	}
	else
	if(nResult == -2)		// Cancel
		return -2;
	////////////////////////////
	return 0;
}

void CCurEdit::ElementLeftUp_CUR(CPoint point)
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
	///////////////////
	switch(m_nActiveTool) 
	{
		
		case C_EDIT:

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

void CCurEdit::OnEBoxMouseMove_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point)
{  

	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
	////////////////////////////////// do nothing for now
	return;
}

void CCurEdit::OnEBoxLButtonUp_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CCurEdit::OnEBoxRButtonDown_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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

int CCurEdit::ShowCurveInfo(CDrCurve* pDrCurve)
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
		"\nYES:\t\tEdit This Curve");
	j += sprintf(buf+j,
		"\nNO:\t\tFind Next Curve with Intersecting Trace");
	j += sprintf(buf+j,
		"\nCANCEL:\t\tCancel Selection Process");
	nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
	///////////////
	delete str;
	return nResult;
}

void CCurEdit::OnEBoxRButtonUp_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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
UINT CCurEdit::ReSetToolID_CUR(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	//////////////////////////////////////////// TaskID
	strCur = "Ready for Editing a Curve@";
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
						case CURVE:			str	= "CURVE";	ID	= C_EDIT;
								strCur += "Click on a Curve";	break;
						default:			str = "CURVE";	ID	= UNONE;	break;
					}
					pWnd->SetstrIGenID(str);
					////////////////////////
					pWnd->SetstrCurrID(strCur);
					/////
				return ID;
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
	

void CCurEdit::Serialize(CArchive& ar)
{

	CNodEdit::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CurEdit:    Storing\n");	
		

	}
	else
	{
		TRACE(" CurEdit:    Loading\n");	

	
	}        
	//////////////////
}

///////////////////////////////////// end of Module //////////////////////		


