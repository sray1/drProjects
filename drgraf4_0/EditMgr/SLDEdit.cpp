// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
#include "drgrafrm.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "Def_MouseAct.h"
///////////////////// elements
#include "Def_IGen.h"
#include "Def_Elem.h"
///////////////////// Static Loads
#include "Str_StaL.h"
#include "Def_StaL.h"
#include "DrStatic.h" 
#include "MI_StaL.h" 
#include "SLDNod.h" 
#include "SLDCur.h" 
#include "SLDPat.h" 
//////////////////////
#include "SLDEdit.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CSLDEdit,CSupEdit,1)
/////////////////////////////////////////////////////////////////////////////
CSLDEdit::CSLDEdit()
{
}

CSLDEdit::~CSLDEdit()
{
}

void CSLDEdit:: ElementLeftDown_SLD()
{	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////
	SetMainType_SLD();
	/////////////
	switch(m_nMainType) 
	{
		
		////////////////////////////////////////////////// Force	
		case FORCE:

			m_StaLProc		= STL_FORCE;
			///////
			return;


		case DISPLACE:

			m_StaLProc		= STL_DISPLACE;
			///////
			return;



		case PRESSURE:

			m_StaLProc		= STL_PRESSURE;
			///////
			return;



		case THERMAL:

			m_StaLProc		= STL_THERMAL;
			///////
			return;



		case LUMPWT:

			m_StaLProc		= STL_LUMPWT;
			///////
			return;


		//////////////////////////////////////////////////
		default:
			break;
	}  
	/////////////

}

void CSLDEdit::OnEBoxLButtonDown_SLD(CClientDC* pdc,CView* pView,GENERATE gener,
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
	pDListMgr 	= pObjectMgr->GetObjectList(STATICLOAD);
	if(pDListMgr->IsEmpty())
		return;
	/////////////////////////////////////////////////////////////////
    /////////////////////////////  ELement Dialog On/Off Check
    if(m_Gener == FORWARD)
		ElementLeftDown_SLD();
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftDown_I();
	//////////////////////////////////
}

void CSLDEdit::FillStaticInfo(CDrStatic* pStatic)
{

	m_StaLProc		= pStatic->GetStaLCard()->StaLProc;
	/////////////////////////////////////////////////////////
	m_bTx			= pStatic->GetStaLCard()->kode[0];
	m_bTy			= pStatic->GetStaLCard()->kode[1];
	m_bTz			= pStatic->GetStaLCard()->kode[2];
	m_bRx			= pStatic->GetStaLCard()->kode[3];
	m_bRy			= pStatic->GetStaLCard()->kode[4];
	m_bRz			= pStatic->GetStaLCard()->kode[5];
	///
	m_dTx			= pStatic->GetStaLCard()->value[0];
	m_dTy			= pStatic->GetStaLCard()->value[1];
	m_dTz			= pStatic->GetStaLCard()->value[2];
	m_dRx			= pStatic->GetStaLCard()->value[3];
	m_dRy			= pStatic->GetStaLCard()->value[4];
	m_dRz			= pStatic->GetStaLCard()->value[5];
	///
	m_aNid			= pStatic->GetStaLCard()->nid_a;
	m_bNid			= pStatic->GetStaLCard()->nid_b;
	m_bCN_a			= pStatic->GetStaLCard()->bCN_a;
	m_bCN_b			= pStatic->GetStaLCard()->bCN_b;
	m_bTanCur		= pStatic->GetStaLCard()->bTanCur;
	m_bTanPat		= pStatic->GetStaLCard()->bTanPat;
	m_bNorPat		= pStatic->GetStaLCard()->bNorPat;
	m_bIso			= pStatic->GetStaLCard()->bIso;
	m_cid_Iso		= pStatic->GetStaLCard()->cid_Iso;
	m_cid_ParentT	= pStatic->GetStaLCard()->cid_ParentT;
	m_cid_ParentR	= pStatic->GetStaLCard()->cid_ParentR;
	////////////////////////////////////////////// NonIso
	m_bNonIso		= pStatic->GetStaLCard()->bNonIso;
	m_bIncrement	= pStatic->GetStaLCard()->bIncrement;
	m_Orient		= pStatic->GetStaLCard()->Orient;
	m_dScale		= pStatic->GetStaLCard()->dScale;
	m_dStep			= pStatic->GetStaLCard()->dStep;
	m_dStart		= pStatic->GetStaLCard()->dStart;
	////////////////////////////// Joint Coordinates (Skewed)
/*
	m_SLEPat.m_SkewMat		= *pStatic->GetSkewMat();
	///////////////////////////////////////////////////////////////////// Quick Search
	m_SLEPat.m_CreateBase	= pStatic->GetCreateBase();	// NODE,CURVE,PATCH,SOLID
	m_SLEPat.m_bTriangle	= pStatic->IsTriangle();	// if CreateBase = PATCH, Is It Triangle;
														// if CreateBase = Solid, Is It TetraHed
	m_SLEPat.m_bPentaHed	= pStatic->IsPentaHed;		// if CreateBase = Solid, Is It PentaHed;
	m_SLEPat.m_Create_i		= m_Create_i;		// index in the CreateBaseList or TriangleList, if bTriangle = TRUE
	m_SLEPat.m_Create_j		= m_Create_j;
	m_SLEPat.m_Create_k		= m_Create_k;
	m_SLEPat.m_NodPos		= m_NodPos;		// Needed to avoid Duplicate in Triangle Situation
	//////////////////////////////////////////////
	CDrNode*	m_pLabelNode;	// LabelNode
	CDrLabel*	m_pLabel;
	//////////////////////////
	MATRIX		m_LocalM;	// Local Transformation
	/////////////////////////// Bounding Corners
	BOOL		m_bDoneXform;
	BOOL		m_bDoneProject;
	///////////////////////////
	STALCARD	m_StaLCard;
	int			m_nCardNo;
	/////////////////////////// Current
	int			m_CurDir;
	int			m_nPts[6];
	pWORLD		m_pLoc[6];// stores Local  and then Translated to NodePos	
	pWORLD		m_pEye[6];// EyePos also stores WorPos
	/////////////////////////// Smart Paint
	WORLD		m_dMin;
	WORLD		m_dMax;
*/
}

void CSLDEdit::UpdateSLEObjInfo()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	m_SLEPat.m_dTx			= m_dUnif[0];			// also for Prs,Thr and LWt
	m_SLEPat.m_dTy			= m_dUnif[1];			// also for Prs,Thr and LWt
	m_SLEPat.m_dTz			= m_dUnif[2];			// also for             LWt
	m_SLEPat.m_dRx			= m_dUnif[3];
	m_SLEPat.m_dRy			= m_dUnif[4];
	m_SLEPat.m_dRz			= m_dUnif[5];
	/////
	m_SLEPat.m_ID_CP		= m_ID_CP;		// Used for NodeBased
	m_SLEPat.m_jcType		= m_jcType;		//	JC_DEFAULT,
	m_SLEPat.m_bUniform		= m_bUniform;	// Uniform distribution
	m_SLEPat.m_bConOrDis	= m_bConOrDis;	// IsoParametric Concentrated or Distributed Input
	//////////////////////////
	m_SLEPat.m_bGravMul		= m_bGravMul;

	m_SLEPat.m_StaLProc		= m_StaLProc;
	/////////////////////////////////////////////////////////
	m_SLEPat.m_bRx			= m_bRx;
	m_SLEPat.m_bRy			= m_bRy;
	m_SLEPat.m_bRz			= m_bRz;
	m_SLEPat.m_bTx			= m_bTx;
	m_SLEPat.m_bTy			= m_bTy;
	m_SLEPat.m_bTz			= m_bTz;
	/////////////////////////////
	m_SLEPat.m_aNid			= m_aNid;				
	m_SLEPat.m_bCN_a		= m_bCN_a;
	m_SLEPat.m_bNid			= m_bNid;				
	m_SLEPat.m_bCN_b		= m_bCN_b;
	//////////////////////////////////////////////
	m_SLEPat.m_SkewDir.x	= m_SkewDir.x;
	m_SLEPat.m_SkewDir.y	= m_SkewDir.y;
	m_SLEPat.m_SkewDir.z	= m_SkewDir.z;
	/////////////////////////////////////////////////////////// Tan or Nor?
	m_SLEPat.m_bTanCur		= m_bTanCur;				
	m_SLEPat.m_bTanPat		= m_bTanPat;				
	m_SLEPat.m_bNorPat		= m_bNorPat;				
	m_SLEPat.m_ID_CP		= m_ID_CP;
	m_SLEPat.m_GenKind		= m_GenKind;
	m_SLEPat.m_jcType		= m_jcType;
	//////////////////////////////////////////////
	m_SLEPat.m_bIso			= m_bIso;
	m_SLEPat.m_bConOrDis	= m_bConOrDis;
	////////////////////////////////////////////// NonIso
	m_SLEPat.m_bNonIso		= m_bNonIso;
	m_SLEPat.m_CID			= m_cid_Parent;
	m_SLEPat.m_bIncrement	= m_bIncrement;
	m_SLEPat.m_Orient		= m_Orient;
	m_SLEPat.m_dScale		= m_dScale;
	m_SLEPat.m_dStep		= m_dStep;
	m_SLEPat.m_dStart		= m_dStart;
	///////////////////////////////////
	return;
}

int CSLDEdit::LeftUp_NodeStatic(CPoint point)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 			= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(NODE);
	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CDrStatic*	pStatic;
	CString*	pID;
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
	if(pDrNode->GetStaLList()->IsEmpty())
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
			pList = pDrNode->GetStaLList();
			//////////////
			// Check for same SLPProc, otherwise continue
			BOOL bMatched = FALSE;
			///////////////////////////////////
			for(int indexStaL=0;indexStaL<pList->GetCount();indexStaL++)
			{
				pStatic = (CDrStatic*)pList->GetObject(indexStaL);
				STALPROC StaLProc	= (pStatic->GetStaLCard())->StaLProc;
				UINT CreateBase		= pStatic->GetCreateBase();		
				if( (StaLProc == m_StaLProc) && (CreateBase == NODE) )
				{
					bMatched = TRUE;
					break;
				}
			}
			////////////////////////  A Match ?
			if(!bMatched)
				return 0; 
			//////////////////////////////////////////
			m_CurrentStLID = (pStatic->GetStaLCard())->load_id; 
			//////
			j = sprintf(buf,"***** Selected Node Static Load Info  *****\n");
			j += sprintf(buf+j,"\nNodeID = %s\nCoordinates:\n\t X = %f\n\t Y = %f\n\t Z = %f\n",
						ID,wLoc.x,wLoc.y,wLoc.z);
			///////////////////
			FillStaticInfo(pStatic);
			UpdateSLEObjInfo();
			////////////////////////
//			j = m_SLEPat.ShowInfo_NodeStaticLoad(pDrNode, buf, j,pStatic);
			j = m_SLEPat.ShowInfo_NodeStaticLoad(pDrNode, buf, j,m_CurrentStLID);
			if(j<0)
				return -2;
			////////////////////////////
			j += sprintf(buf+j,
				"\n\nYES:\t\tEdit This Node-Based Static Load");
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
				////////////
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
				/////////////
				delete str;
				return -2;
			}
		}
	}
	//////////////////////////////////////////////////////////////// Show Static
	m_pCurrentNode			= (CDrNode*)pDListMgr->GetObject(index);
	CDrLabel* pCurrentLabel = (CDrLabel*)(m_pCurrentNode->GetLabelList()->GetHead());
	//////////////////////////////////////////////////////////////// Set Info
	FillStaticInfo(pStatic);
	UpdateSLEObjInfo();
	///////////////////
	CString heading = "@Node ";
	heading += m_pCurrentNode->GetObjectID();
	m_SLEPat.Get_Values(m_StaLProc,heading);
	//////////////////////////////////////////////////////////////// Show LinSup
	pID = &m_CurrentStLID;
	////////////////////////////////////////////////////////////////
	strCurr = "Done with Edit Data@";
	strCurr += "Please Sit Back";
	//////
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////////////////////////////////////
	int nAnyway = -12345; // ???????????????????
	if(m_SLEPat.ShowNodeStaticLoad(m_pCurrentNode,pID)<0)		// 
	{
		AfxMessageBox("ERROR:\nCSLDEdit::LeftUp_NodeStatic\nShowNodeStaticLoad Problem");
		return -1;
	}
	////////////////////////////////////////////////////////////////
	strCurr = "Ready for Editing@";
	strCurr += "Another Static Node";
	//////
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////////////////////////////////////
	return 0;
}

int CSLDEdit::LeftUp_CurveStatic(CPoint point)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	///////////////////////////////////////////////////////////////////////
	int nAnyway	= 0;	// Used as an afterthought for Updating Support anyway
						// in CMI_LSupp.CreatePatchLinSup
						// even if same coords Patch exists already !!!
						// when nAnyway == -12345
						// Use nHowmany of ShowPatch to pass the variable
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(CURVE);
	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CDrStatic*	pStatic;
	STALPROC	StaLProc;
	UINT		CreateBase;
	CString*	pID;
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
	if(pDrCurve->GetStaLList()->IsEmpty())
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
			///////////////////////////////////////// Check if This Curve is Already Loaded
			pList = pDrCurve->GetStaLList();
// to do********/////////////////////////////// if Supported, only Displace/rot Allowed 
			// Check for same SLPProc, otherwise continue
			///////////////////////////////////
			BOOL bMatched = FALSE;
			for(int indexStaL=0;indexStaL<pList->GetCount();indexStaL++)
			{
				pStatic		= (CDrStatic*)pList->GetObject(indexStaL);
				StaLProc	= (pStatic->GetStaLCard())->StaLProc;
				CreateBase	= pStatic->GetCreateBase();		
				if( (StaLProc != m_StaLProc) || (CreateBase != CURVE) )
				{
					bMatched = TRUE;
					break;
				}
			}
			////////////////////////  A Match ?
			if(!bMatched)
				return 0; 
			//////////////////////////////////////////
			m_CurrentStLID = (pStatic->GetStaLCard())->load_id; 
			//////
			j = sprintf(buf,"***** A Loaded Curve Hit  *****\n\n");
			/////////////////////////////// total elems
			int nIn		= pDrCurve->GetMaxINodes_S();
			int nElems	= pDrCurve->GetMaxOutPts_S();
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
			FillStaticInfo(pStatic);
			UpdateSLEObjInfo();
			///////////////////
			j = m_SLEPat.ShowInfo_CurveStaticLoad(pDrCurve, buf, j,m_CurrentStLID);
				if(j<0)
					return -2;
			////////////////////////////
			j += sprintf(buf+j,
				"\nYES:\t\tEdit This Existing Curve");
			j += sprintf(buf+j,
				"\nNO:\t\tFind Next Curve with Intersecting Trace");
			j += sprintf(buf+j,
				"\nCANCEL:\t\tCancel Selection Process");
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
				/////////////
				delete str;
				return -2;;
			}
		}
	}
	//////////////////////////////////////////////////// Gotch'a Curve/ Show LinSup
	m_pCurrentCurve			= (CDrCurve*)pDListMgr->GetObject(index);
	/////////////////////////////////////////////
	pID = &m_CurrentStLID;
	//////////////////////////////////////////////////////////////// Get Values
	FillStaticInfo(pStatic);
	UpdateSLEObjInfo();
	///////////////////
	if(m_bIso)
	{
		///////////////////////////// Iso
		m_SLEPat.Get_Values_Iso_Cur(m_pCurrentCurve,m_StaLProc,-1,FALSE); // -1= No skipping of node
		/////////
		CString strID;
		//////////////
		if(m_bTx ||m_bTy ||m_bTz)
		{
			strID = m_CurrentStLID + "_CC";
			strID += "_T";
			m_SLEPat.Generate_IsoCurveControls(m_pCurrentCurve,0,&strID,TRUE);	// TRUE = Translation
		}
		if(m_bRx ||m_bRy ||m_bRz)
		{
			strID = m_CurrentStLID + "_CC";
			strID += "_R";
			m_SLEPat.Generate_IsoCurveControls(m_pCurrentCurve,0,&strID,FALSE);	// FALSE = Rotation
		}
		///////////////////////
	}
	else
	if(m_bNonIso)
		///////////////////////////// NonIso
		m_SLEPat.Get_Values_NonIso_Cur(m_StaLProc);
		//////////////
	else
	{
		///////////////////////////// Uniform
		CString heading = "@Curve ";
		heading += m_pCurrentCurve->GetObjectID();
		m_SLEPat.Get_Values(m_StaLProc,heading);
	}
	////////////////////////////////////////////////////////////////
	strCurr = "Done with Edit Data@";
	strCurr += "Please Sit Back";
	//////
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////////////////////////////////////
	if(m_SLEPat.ShowCurveStaticLoad(m_pCurrentCurve,pID)<0)		// 
	{
		AfxMessageBox("ERROR:\nCSLEEdit::LeftUp_CurveStatic\nShowCurveStaticLoad Problem");
		return -1;
	}
	////////////////////////////////////////////////////////////////
	strCurr = "Ready for Editing@";
	strCurr += "Another Static Curve";
	//////
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////////////////////////////////////
	return 0;
}

int CSLDEdit::LeftUp_PatchStatic(CPoint point)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	///////////////////////////////////////////////////////////////////////
	int nAnyway	= 0;	// Used as an afterthought for Updating Support anyway
						// in CMI_LSupp.CreatePatchLinSup
						// even if same coords Patch exists already !!!
						// when nAnyway == -12345
						// Use nHowmany of ShowPatch to pass the variable
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(PATCH);
	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CDrStatic*	pStatic;
	STALPROC	StaLProc;
	UINT		CreateBase;
	CString*	pID;
	CString		ID;
	CDrPatch*	pDrPatch;
	int			nActiveIndex,index,nResult;
	BOOL		bNew	= TRUE;
	///////////////////////////////////////////// See if any Existing Patch Hit
	index = IsObjectHit(PATCH,point,0);
	//////////////
	if(index<0)
		return -2;
	//////////////////////////////////////////////////////////////// Existing Patch
	pDrPatch				= (CDrPatch*)pDListMgr->GetObject(index);
	if(pDrPatch->GetStaLList()->IsEmpty())
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
			///////////////////////////////////////// Check if This Patch is Already Loaded with same LoadID
			pList = pDrPatch->GetStaLList();
// to do********/////////////////////////////// if Supported, only Displace/rot Allowed 
			// Check for same SLPProc, otherwise continue
			///////////////////////////////////
			BOOL bMatched = FALSE;
			for(int indexStaL=0;indexStaL<pList->GetCount();indexStaL++)
			{
				pStatic		= (CDrStatic*)pList->GetObject(indexStaL);
				StaLProc	= (pStatic->GetStaLCard())->StaLProc;
				CreateBase	= pStatic->GetCreateBase();		
				if( (StaLProc != m_StaLProc) || (CreateBase != PATCH) )
				{
					bMatched = TRUE;
					break;
				}
			}
			////////////////////////  A Match ?
			if(!bMatched)
				return 0; 
			//////////////////////////////////////////
			m_CurrentStLID = (pStatic->GetStaLCard())->load_id; 
			//////
			j = sprintf(buf,"***** A Loaded Patch Hit  *****\n\n");
			//////////////////////////////
			if(pDrPatch->GetPatSubType() == PS_QUADRILAT)
				j += sprintf(buf+j,"Patch %s is \n\tQuadrilateral Type\n",ID);
			if(pDrPatch->GetPatSubType() == PS_TRIANGLE)
				j += sprintf(buf+j,"Patch %s is \n\tTriangular Type\n",ID);
			////////////////////////////
			FillStaticInfo(pStatic);
			UpdateSLEObjInfo();
			///////////////////
			j = m_SLEPat.ShowInfo_PatchStaticLoad(pDrPatch, buf, j,
											pStatic->GetStaLCard()->load_id);
			if(j<0)
				return -2;
			////////////////////////////
			j += sprintf(buf+j,
				"\nYES:\t\tEdit This Existing Patch");
			j += sprintf(buf+j,
				"\nNO:\t\tFind Next Patch with Intersecting Trace");
			j += sprintf(buf+j,
				"\nCANCEL:\t\tCancel Selection Process");
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
				/////////////
				delete str;
				return -2;;
			}
		}
	}
	//////////////////////////////////////////////////// Gotch'a Patch/ Show LinSup
	m_pCurrentPatch			= (CDrPatch*)pDListMgr->GetObject(index);
	/////////////////////////////////////////////
	pID = &m_CurrentStLID;
	m_CurrentStPID = m_CurrentStLID; 
	//////////////////////////////////////////////////////////////// Get Values
	FillStaticInfo(pStatic);
	UpdateSLEObjInfo();
	///////////////////
	if(pStatic->GetStaLCard()->bIso)
	{
		///////////////////////////// Iso
		m_SLEPat.Get_Values_Iso_Pat(m_pCurrentPatch,m_StaLProc,m_CurrentStPID);
		/////////
		CString strID;
		strID = m_CurrentStLID + "_PP";
		//////////////
		if(m_bTx ||m_bTy ||m_bTz)
		{
			strID = m_CurrentStLID + "_PP";
			strID += "_T";
			m_SLEPat.Generate_IsoPatchControls(m_pCurrentPatch,&strID,TRUE);	// TRUE = Translation
		}
		if(m_bRx ||m_bRy ||m_bRz)
		{
			strID = m_CurrentStLID + "_PP";
			strID += "_R";
			m_SLEPat.Generate_IsoPatchControls(m_pCurrentPatch,&strID,FALSE);	// FALSE = Rotation
		}
		///////////////////////
	}
	else
	if(m_bNonIso)
		///////////////////////////// NonIso
		m_SLEPat.Get_Values_NonIso_Pat(m_StaLProc);
		//////////////
	else
	{
		///////////////////////////// Uniform
		CString heading = "@Patch ";
		heading += m_pCurrentPatch->GetObjectID();
		m_SLEPat.Get_Values(m_StaLProc,heading);
	}
	////////////////////////////////////////////////////////////////
	strCurr = "Done with Patch Data@";
	strCurr += "Please Sit Back";
	//////
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////////////////////////////////////
	if(m_SLEPat.ShowPatchStaticLoad(m_pCurrentPatch,pID)<0)		// 
	{
		AfxMessageBox("ERROR:\nCSLDEdit::LeftUp_PatchStatic\nShowPatchStaticLoad Problem");
		return -1;
	}
	////////////////////////////////////////////////////////////////
	strCurr = "Ready for Generation@";
	strCurr += "Another Static Patch";
	//////
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////////////////////////////////////
	return 0;
}

void CSLDEdit::ElementLeftUp_SLD(CPoint point)
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
	SetMainType_SLD();
	///////////////////
	switch(m_nMainType) 
	{
		
		///////////////////////////////////////////////////// Static: Node Based										
		case NSL_FOR_EDIT:
		case NSL_DIS_EDIT:
		case NSL_PRS_EDIT:
		case NSL_THR_EDIT:
		case NSL_LWT_EDIT:

			////////////////////
			LeftUp_NodeStatic(point);	
			////////////////////
			break;

		///////////////////////////////////////////////////// Static: Curve Based										
		case CSL_FOR_EDIT:
		case CSL_DIS_EDIT:
		case CSL_PRS_EDIT:
		case CSL_THR_EDIT:
		case CSL_LWT_EDIT:

			////////////////////
			LeftUp_CurveStatic(point);	
			////////////////////
			break;

		///////////////////////////////////////////////////// Static: Patch Based										
		case PSL_FOR_EDIT:
		case PSL_DIS_EDIT:
		case PSL_PRS_EDIT:
		case PSL_THR_EDIT:
		case PSL_LWT_EDIT:

			////////////////////
			LeftUp_PatchStatic(point);	
			////////////////////
			break;
		//////////////////////////////////////////////////
		default:  
			break;
	} 
}	

void CSLDEdit::OnEBoxMouseMove_SLD(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CSLDEdit::OnEBoxLButtonUp_SLD(CClientDC* pdc,CView* pView,GENERATE gener,
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
		ElementLeftUp_SLD(Logpoint);
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftUp_I();
	/////////////////////////
	
}

void CSLDEdit::OnEBoxRButtonDown_SLD(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CSLDEdit::OnEBoxRButtonUp_SLD(CClientDC* pdc,CView* pView,GENERATE gener,
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
////////////////////////////////////////////////////////////////////	
UINT CSLDEdit::ReSetToolID_SLD(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	//////////////////////////////////////////// TaskID
	strCur = "Ready to Edit Static Loads@";
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
				//////////////////////////////////////// StaticLoad
				case STATICLOAD:

//					pWnd->SetMouseBoxType(STATICLOADBOX);
					str = "Static@Load";
					pWnd->SetstrCntlID(str);
					///////////////////////////////////// Force
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = STATICLOAD;
							strCur = "To Edit Node-based Static Load@";
							strCur += "Select A Static Load Type";	break;
						case CURVE:			str = "CURVE";		ID = STATICLOAD;
							strCur = "To Edit Curve-based Static Load@";
							strCur += "Select A Static Load Type";	break;
						case PATCH:			str = "PATCH";		ID = STATICLOAD;
							strCur = "To Edit Patch-based Static Load@";
							strCur += "Select A Static Load Type";	break;
						case SOLID:			str = "SOLID";		ID = STATICLOAD;
							strCur = "To Edit Solid-based Static Load@";
							strCur += "Select A Static Load Type";	break;
						default:			str = "UNKNOWN";	ID = UNONE;
							strCur += "Select Node, Curve, Patch or Solid basis";	break;
					}
					pWnd->SetstrIGenID(str);
					////////////////////////
					pWnd->SetstrCurrID(strCur);
					//////////
					return ID;
				//////////////////////////////////////// StaticLoad
				case FORCE:

//					pWnd->SetMouseBoxType(STATICLOADBOX);
					str = "FORCE";
					pWnd->SetstrCntlID(str);
					///////////////////////////////////// Force
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = NSL_FOR_EDIT;
								strCur = "To Edit:  Click On@";
								strCur += "A Node with Imposed Force";	break;
						case CURVE:			str = "CURVE";		ID = CSL_FOR_EDIT;
								strCur = "To Edit:  Click On@";
								strCur += "A Curve with Imposed Force";	break;
						case PATCH:			str = "PATCH";		ID = PSL_FOR_EDIT;
								strCur = "To Edit:  Click On@";
								strCur += "A Patch with Imposed Force";	break;
						case SOLID:			str = "SOLID";		ID = SSL_FOR_EDIT;
								strCur = "To Edit:  Click On@";
								strCur += "A Solid with Imposed Force";	break;
						default:			str = "UNKNOWN";	ID = UNONE;
								strCur += "Select Node, Curve, Patch or Solid basis ";	break;
					}
					pWnd->SetstrIGenID(str);
					////////////////////////
					pWnd->SetstrCurrID(strCur);
					//////////
					return ID;
				//////////////////
				case DISPLACE:

					pWnd->SetMouseBoxType(STATICLOADBOX);
					str = "DISPLACE";
					pWnd->SetstrCntlID(str);
					////////////////// Displacement
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = NSL_DIS_EDIT;
							strCur = "To Edit:  Click On@";
							strCur += "A Node with Imposed Displacement";	break;
						case CURVE:			str = "CURVE";		ID = CSL_DIS_EDIT;
								strCur = "To Edit:  Click On@";
								strCur += "A Curve with Imposed Displacement";	break;
						case PATCH:			str = "PATCH";		ID = PSL_DIS_EDIT;
								strCur = "To Edit:  Click On@";
								strCur += "A Patch with Imposed Displacement";	break;
						case SOLID:			str = "SOLID";		ID = SSL_DIS_EDIT;
								strCur = "To Edit:  Click On@";
								strCur += "A Solid with Imposed Displacement";	break;
						default:			str = "UNKNOWN";	ID = UNONE;
								strCur += "Select Node, Curve, Patch or Solid basis ";	break;
					}
					pWnd->SetstrIGenID(str);
					////////////////////////
					pWnd->SetstrCurrID(strCur);
					//////////
					return ID;
				//////////////////
				case PRESSURE:

					pWnd->SetMouseBoxType(STATICLOADBOX);
					str = "PRESSURE";
					pWnd->SetstrCntlID(str);
					////////////////// Pressure
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = NSL_PRS_EDIT;
								strCur = "To Edit:  Click On@";
								strCur += "A Node with Imposed Pressure";	break;
						case CURVE:			str = "CURVE";		ID = CSL_PRS_EDIT;
								strCur = "To Edit:  Click On@";
								strCur += "A Curve with Imposed Pressure";	break;
						case PATCH:			str = "PATCH";		ID = PSL_PRS_EDIT;
								strCur = "To Edit:  Click On@";
								strCur += "A Patch with Imposed Pressure";	break;
						case SOLID:			str = "SOLID";		ID = SSL_PRS_EDIT;
								strCur = "To Edit:  Click On@";
								strCur += "A Solid with Imposed Pressure";	break;
						default:			str = "UNKNOWN";	ID = UNONE;
								strCur += "Select Node, Curve, Patch or Solid basis ";	break;
					}
					pWnd->SetstrIGenID(str);
					////////////////////////
					pWnd->SetstrCurrID(strCur);
					//////////
					return ID;
				////////////////// 
				case THERMAL:

					pWnd->SetMouseBoxType(STATICLOADBOX);
					str = "THERMAL";
					pWnd->SetstrCntlID(str);
					////////////////// Thermal
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = NSL_THR_EDIT;
								strCur = "To Edit:  Click On@";
								strCur += "A Node with Thermal Loading";	break;
						case CURVE:			str = "CURVE";		ID = CSL_THR_EDIT;
								strCur = "To Edit:  Click On@";
								strCur += "A Curve with Thermal Loading";	break;
						case PATCH:			str = "PATCH";		ID = PSL_THR_EDIT;
								strCur = "To Edit:  Click On@";
								strCur += "A Patch with Thermal Loading";	break;
						case SOLID:			str = "SOLID";		ID = SSL_THR_EDIT;
								strCur = "To Edit:  Click On@";
								strCur += "A Solid with Thermal Loading";	break;
						default:			str = "UNKNOWN";	ID = UNONE;
								strCur += "Select Node, Curve, Patch or Solid basis ";	break;
					}
					pWnd->SetstrIGenID(str);
					////////////////////////
					pWnd->SetstrCurrID(strCur);
					//////////
					return ID;
				////////////////// 
				case LUMPWT:

					pWnd->SetMouseBoxType(STATICLOADBOX);
					str = "LUMPWT";
					pWnd->SetstrCntlID(str);
					////////////////// LumpWt
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = NSL_LWT_EDIT;
								strCur = "To Edit:  Click On@";
								strCur += "A Node with Assigned LumpWt";	break;
						case CURVE:			str = "CURVE";		ID = CSL_LWT_EDIT;
								strCur = "To Edit:  Click On@";
								strCur += "A Curve with Assigned LumpWt";	break;
						case PATCH:			str = "PATCH";		ID = PSL_LWT_EDIT;
								strCur = "To Edit:  Click On@";
								strCur += "A Patch with Assigned LumpWt";	break;
						case SOLID:			str = "SOLID";		ID = SSL_LWT_EDIT;
								strCur = "To Edit:  Click On@";
								strCur += "A Solid with Assigned LumpWt";	break;
						default:			str = "UNKNOWN";	ID = UNONE;
								strCur += "Select Node, Curve, Patch or Solid basis ";	break;
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

void CSLDEdit::SetMainType_SLD()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	m_nActiveTool	= pWnd->GetActiveToolType();
	m_nMainType		= m_nActiveTool;
	////////
	return;
}

	
void CSLDEdit::Serialize(CArchive& ar)
{

	CSupEdit::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" SLDEdit:    Storing\n");	
		
 			/////////////////////////////////////////////////

	}
	else
	{
		TRACE(" SLDEdit:    Loading\n");	

			/////////////////////////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////		


