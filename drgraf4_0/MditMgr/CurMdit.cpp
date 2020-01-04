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
//#include "MCurMgr.h" 
#include "CurMdit.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CCurMdit,CNodMdit,1)
/////////////////////////////////////////////////////////////////////////////
CCurMdit::CCurMdit()
{

	/////////////////////////////////////////// 
    m_pCurrentCurve		= NULL;
}

CCurMdit::~CCurMdit()
{
}
	
void CCurMdit::ElementLeftDown_CUR()
{	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	/////////////////////////////////////////////////////////
	switch(m_nActiveTool) 
	{
		
		////////////////////////////////////////////////// EDIT	
		case C_EDIT:				// MESH1D
		//////////////////////////////////////////////////
		default:
			break;
	}  

}
	
int CCurMdit::ShowCurveToEdit(CDrMesh1D* pDrCurve)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	pObjectMgr->SetActiveObjectType(MESH1D);
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

void CCurMdit::OnEBoxLButtonDown_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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
	pDListMgr 	= pObjectMgr->GetObjectList(MESH1D);
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

int CCurMdit::LeftUp_CURVE(CPoint point)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(MESH1D);
//	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrMesh1D*	pDrCurve;
//	int			nActiveIndex,index;
	int			index;
	////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	WORtoWOP(&dTol,&dTol);	// physical
	///////////////////////////////////////////// See if any Existing Node Hit
	index = IsObjectHit(MESH1D,point,0);
	////////////////////////////////////////////////////
	if(index<0)
		return -2;
	//////////////////////////////////////////////////////////////// Existing Curve
	pDrCurve	= (CDrMesh1D*)pDListMgr->GetObject(index);
	ID			= pDrCurve->GetObjectID();
	/////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(pDrCurve,MESH1D,TRUE);
/*
	pList = pObjectMgr->GetObjectList(MESH1D);
	nActiveIndex = pList->GetObjectIndex(MESH1D, ID);;
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
	pObjectMgr->SetActiveObjectType(MESH1D);		    // set Active Type									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,MESH1D);
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
				index = IsObjectHit(MESH1D,point,startIndex);
				if(index>=0)
				{
					pDrCurve	= (CDrMesh1D*)pDListMgr->GetObject(index);
					ID		= pDrCurve->GetObjectID();
					///////////////////////////////////////// 
	pObjectMgr->ShowObject_On_Off(pDrCurve,MESH1D,TRUE);
/*
	pList = pObjectMgr->GetObjectList(MESH1D);
	nActiveIndex = pList->GetObjectIndex(MESH1D, ID);;
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
	pObjectMgr->SetActiveObjectType(MESH1D);		    // set Active Type									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,MESH1D);
*/
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
		AfxMessageBox("ERROR:\nCCurMdit::LeftUp_Node\nShowCurveToEdit Problem");
		return -1;
	}
	else
	if(nResult == -2)		// Cancel
		return -2;
	////////////////////////////
	return 0;
}

void CCurMdit::ElementLeftUp_CUR(CPoint point)
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
		case C_POST:				// MESH1D
			///////		
			m_MI_Solid.LBUpCurvePost();
			return;
		////////////////////////////////////////////////// EDIT	
		case C_EDIT:				// MESH1D
			///////		
			m_MI_Solid.LBUpCurveEdit();
			return;
		
		////////////////////////////////////////////////// MOVE	
		case C_MOVE:				// MESH1D
			///////		
			m_MI_Solid.LBUpCurveMove();
			return;
*/		
		//////////////////////////////////////////////////
		default:  
			break;
	} 
}	

void CCurMdit::OnEBoxMouseMove_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CCurMdit::OnEBoxLButtonUp_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CCurMdit::OnEBoxRButtonDown_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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

int CCurMdit::ShowCurveInfo(CDrMesh1D* pDrCurve)
{
	int nResult = 0;
	////////////////
	// todo from DATABASE DLL
	////////////////
	return nResult;
}

void CCurMdit::OnEBoxRButtonUp_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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
UINT CCurMdit::ReSetToolID_CUR(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	//////////////////////////////////////////// TaskID
	strCur = "Ready for Editing a Mesh1D@";
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
						case MESH1D:			str	= "MESH1D";	ID	= C_EDIT;
								strCur += "Click on a Mesh1D";	break;
						default:			str = "MESH1D";	ID	= UNONE;	break;
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
				case MESH1D:				return C_MOVE;
				case MESH1D:				return C_POST;
				case MESH1D:				return C_UNPOST;
				case MESH1D:				return C_DELETE;
*/
}
	

void CCurMdit::Serialize(CArchive& ar)
{

	CNodMdit::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CurMdit:    Storing\n");	
		

	}
	else
	{
		TRACE(" CurMdit:    Loading\n");	

	
	}        
	//////////////////
}

///////////////////////////////////// end of Module //////////////////////		


