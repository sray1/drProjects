// Mouse.cpp : implementation file
//


#include "stdafx.h" 
#include <float.h>		// DBL_MIN 

///////////////////// 
#include "3DMath.h"
#include "XForm.h"
/////////////////////
#include "Def_MouseAct.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h"
#include "ObjMgr.h"
#include "HitNet.h"
#include "DListMgr.h"
///////////////////// DlgMgr
#include "MCurMgr.h"
///////////////////// elements
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "DrLinSup.h"
#include "MI_LSupp.h"
#include "DrStatic.h"
#include "MI_StaL.h"
#include "DrProf_C.h"
#include "MatObj.h"
/////////////////////
#include "MI_NSPN.h"
#include "MI_CSPN.h"
/////////////////////
#include "DegElevate.h"
#include "MI_CProf.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define	NUM_LEN	12
/////////////////////////////////////
#define wEQL(a,b)	((a).x ==(b).x) && ((a).y ==(b).y) \
					&& ((a).z ==(b).z)  
////////////////////////////////////
IMPLEMENT_DYNAMIC(CMI_CProf,CMI_GangC)
/////////////////////////////////////
#define new	DEBUG_NEW
#define	BUFF_SIZE	1024
/////////////////////////////////////////////////////////////////////////////
CMI_CProf::CMI_CProf()
{
	m_bBack = FALSE;
}

CMI_CProf::~CMI_CProf()
{
}	

BOOL CMI_CProf::IsAnyCurveClosed()
{
	// If Any Closed: Invalid Data
	/////////////////////////////////// 
	CDListMgr*	pList = m_pDrProf->GetCurveList();	// Curves making up Profile
	//////////////////////////////////////////////////////////// Find If Any Closed
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrCurve* pCurve = (CDrCurve*)pList->GetNextObject(pos);
		if(!pCurve)
			continue;
   	 	///////////////////////////////////////////// Get Degree/Update
		if(pCurve->IsClosed_S())
			return TRUE;	
		/////	
	}
	return FALSE;
}
 
int CMI_CProf::RBUp_CProfile(CDrProf_C* pProfile) // NOT Using Dlg (Used for Now)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////////////
	m_pDrProf	= pProfile;
	//////////////////////////////////////////////////////////////// Data Invalid? 
	if(IsAnyCurveClosed())
	{
		AfxMessageBox("ERROR:\nINVALID DATA\nOne of the Component Curve is Closed");
		return -1;
	}
	///////////////////////////////////////////////////////////////////// Go Generate
	////////////////////////////////////////////////////////// Save
	if(InsertProfileInfo()<0)
		return -1;
	///////////////////////////////////////////////////////// Generate Profile Curve
//	GenerateCurve(); We will just copy INodes to CNodeList	
	///////////////////////////////////////////////////////// CurveInfo
	m_nMaxCurveCNodes_S	= m_pDrCurve->GetnCon_BZ_S();
	InsertAllInfo_Curve(m_nOrder_S);
	/////////
	return 0;		 
}

int CMI_CProf::RBUp_CProfile(CView* pView,UINT nView) 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////////////
	m_pDrProf	= PR_GetInfo();                  	// 
	///////////////////////////////////////////////////////////////////// Go Generate	
	if(m_pDrProf)
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(80);
				
		sprintf(buf,"Got All Profile Info");
		/////////////////////////	
		AfxMessageBox(*str);
		/////////////////////////
		str->ReleaseBuffer();
		delete str;
	}	
	else
		return -1;	// Cancel
	////////////////////////////////////////////////////////// Save
	if(InsertProfileInfo()<0)
		return -1;
	///////////////////////////////////////////////////////// Generate Profile Curve
//	GenerateCurve(); We will just copy INodes to CNodeList	
	///////////////////////////////////////////////////////// CurveInfo
	m_nMaxCurveCNodes_S 	= m_pDrCurve->GetnCon_BZ_S();
	InsertAllInfo_Curve(m_nOrder_S);
	///////////////////////////////////////////////////////// show Profile
	m_pDrProf->SetDirty(FALSE);
	m_pDrProf->SetShow(TRUE);	// make it visible
	///////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off((CDrObject*)m_pDrCurve,CURVE,TRUE);
	/////////
	return 0;		 
}			
	 
CDrProf_C* CMI_CProf::PR_GetInfo()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(C_PROFILE);
	//////////////////////////////////////////////////////////////////
	CMCurMgr* 	pCurMgr;
	CString		Cid;
	int index;
	///////////////////////////////////////////////////
	if (pCurMgr->DoModal_Profile_C(&Cid,1) == IDCANCEL)
				return (CDrProf_C*)NULL; 
    /////////////////////////////////////////////////////// update
	index 	= pObjectMgr->GetObjectIndexfromKey(C_PROFILE,Cid,1);
	if(index<0)
		return (CDrProf_C*)NULL;
	else
	{
		CDrProf_C* pDrProf	= (CDrProf_C*)(pDListMgr->GetObject(index));
		return pDrProf;
	}	
}
	
int CMI_CProf::InsertProfileInfo()
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////////////// Create a Curve
  	int nActiveIndex;
    m_pDrCurve 	= (CDrCurve*)(pObjectMgr->AddToDataBase(nActiveIndex,CURVE));
	/////////////////////////////////////////////////////////
	// Temporarily: Hide from drawing by View which will otherwise
	// 					access The list 
	//	and find pDrCurve which IS NOT  YET Massaged
	/////////////////////////////////////////////////////////
	m_pDrCurve->SetShow(FALSE);
	////////////////////////////////
	m_pDrProf->SetCurve(m_pDrCurve);		// addto Profile 
	m_pDrCurve->GetCProfList()->InsertObject(m_pDrProf);	// reciprocate
	///////////////////////////////////////////////////////// New Curve Info
	if(1==1)
	{
		Generate_CurveControlInfo();	// We are going to use this:Fancy One!!
		Reciprocate_Curves();			// RECIPROCATE: make it a member Curve 
		/////////////////////////////////////// save CurveInfo
		SetInfoForProfileCurveBase_CONTROL(m_pDrCurve);
	}
	else
	{
		Generate_CurveDataInfo();
		/////////////////////////////////////// save CurveInfo
		SetInfoForProfileCurveBase(m_pDrCurve);
	}
	////////////////
	return 0;
}	

int CMI_CProf::Generate_CurveDataInfo()
{

	m_CurveID	= "PC_";
	m_CurveID	+= m_pDrProf->GetObjectID();
	////////////////////////////////////////
	m_nData_S	= FillProfileCurveINodes(); 
	//////////////////////////////////////////////
    m_nDim_S	= 3;	// Always NONRATIONAL				
    /////////////////////////
	m_CurveType_S	= CP_LINEAR;
	m_nOrder_S		= 2;	// k: Always LINEAR FOR NOW!
	m_nSeg_DT_S		= m_nData_S-1;		// L 	= nData - 1	, Open
	m_nMaxOSeg		= 1;	// ALWAYS
	m_bUnifOT		= TRUE;	// ALWAYS
	////////////////////
	return 0;
}
	
BOOL CMI_CProf::IsClosed()
{
	C3DMath Math3D;
	////////////////////////////////////////////////////////
 	CDListMgr* pINList = m_pDrCurve->GetINodeList(); 
	/////////////////////////////////////////////////////
	CDrNode* pNode_Beg = (CDrNode*)pINList->GetHead();
	CDrNode* pNode_End = (CDrNode*)pINList->GetTail();
	////////////////////////////////////////////////////////
	BOOL bClosed = FALSE;
	/////////////////////
	WORLD LocalPosB,LocalPosE;
	LocalPosB = *(pNode_Beg->GetLocalPos());
	LocalPosE = *(pNode_End->GetLocalPos());
	/////////
	Math3D.Sub3DPts(&LocalPosB,&LocalPosE,&LocalPosB);
	if( fabs(Math3D.Len3DPts(&LocalPosB)) < .000001)
		bClosed = TRUE;
	if( wEQL(LocalPosB,LocalPosE) )
		bClosed = TRUE;
	///////////////
	return bClosed;
	
}

int CMI_CProf::FillProfileCurveINodes()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
//	CDListMgr*	pDListMgr;
	/////////////////////////////////// 
 	CDListMgr*	pINodeList	= m_pDrCurve->GetINodeList(); // New Curve in Profile
	CDListMgr*	pCurveList	= m_pDrProf->GetCurveList();	// Curves making up Profile
	CDListMgr*	pLMList		= m_pDrProf->GetLMList();	// Local Matrix making up Profile
	/////////////////////////////////////////////////
	int i=0,nINode=0,nINodeSave=0,nOut,nCurves,nMeshNodes,indexCurve=-1;
	BOOL bLast;
	//////////////////////////////////////////////////////////// Total CNodes
	nCurves = pCurveList->GetCount();
	/////////////////////////////////
	for (POSITION pos = pCurveList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrCurve* pDrCurve = (CDrCurve*)pCurveList->GetNextObject(pos);
		if(!pDrCurve)
		{
			AfxMessageBox("Internal Problem:\nCMI_CProf::GetNumberOfNodes_1");
			return -1;
		}
		/////////
		indexCurve++;
   	 	///////////////////////////////////////////// MeshNode Exist? Find ALL the time
   	 	CDListMgr* pNodeList = pDrCurve->GetNodeList();
/*   	 	 
		/////////////////////////////////////////////////////////////////
		// IF the Curve Mesh Nodes ( in NodeList) NOT Created:
		// 		Need to generate Curve Using Local CNodes
		// ESLE( because THIS Curve Already in some Profile ):
		//		Get Via NodeList  
		/////////////////////////////////////////////////////////////////
		nOut 		= (int)(pDrCurve->GetLongOutPts());
   	 	nMeshNodes	= pNodeList->GetCount();
   	 	if(nMeshNodes<=0)						// Not Posted yet 
			FillMeshNodesCurve(pDrCurve, nOut);
*/			
		nOut 			= (int)(pDrCurve->GetLongOutPts());
   	 	nMeshNodes		= pNodeList->GetCount();
		/////////////////////////////////////////////////////////////
		pWORLD pOut 	= new WORLD[nOut];			// provide memory
		pDOUBLE pOutWts = new double[nOut];
		////////////////////
		CMatObj*	pMatObj;
		pMatObj	= (CMatObj*)pLMList->GetObject(indexCurve);
		/////////////////////////////////// Latch Orientation
		CURVELATCH m_CuLatch = pMatObj->GetCurveLatch();
		CMI_GangC::m_bBack = FALSE;
		if(m_CuLatch == CL_BACKWARD)
			CMI_GangC::m_bBack = TRUE;
		FillMeshNodesCurve(pDrCurve, pOut, pOutWts, nOut);
		///////////////////////////////////////////// Get Transformation
		if(pMatObj->IsInstanced_Prof())
		{
			CXForm XForm(TRUE);
			///////////////////
			MATRIX LM = *(pMatObj->GetMatrix());
			for(int j=0;j<nOut;j++)
				XForm.Transform(pOut+j, pOut+j, &LM);
		}
   		///////////////////////////////////////////// Update Total  Nodes
   		nINode	+= nOut;
   		///////////////////////////////////////////// save MeshNodes As INodes of Profile	
		i++;
		bLast = FALSE;
		if(i==nCurves)
			bLast = TRUE;
		/////////////////                
		nINodeSave += SaveMeshAsNewINodes(pOut,pOutWts,nOut,i,bLast);
		//////////////////
		delete [] pOut;							// Free memory
		delete [] pOutWts;							// Free memory
		//////////////////
	}
   	//////////////////////
   	nINode	-= (nCurves-1);	// tie pts are common
   	///////////////////////
	if(nINodeSave != nINode)
	{
		AfxMessageBox("Internal Problem:\nCMI_CProf::FillProfileCurveINodes()\nDeleteNodeIndex");
		return -1;
	}
	//////////////////////////////////////////////
	m_bClosed_S	= IsClosed();
	////////////////////////////////////////////// if Closed, drop Last Control Node
												// and Adjust nINode
	if(m_bClosed_S)
	{
		CDListMgr* pInList	= m_pDrCurve->GetINodeList();
		CDListMgr* pCnList	= m_pDrCurve->GetCNodeList();
		CDrNode* pDelNode	= (CDrNode*)(pInList->GetTail());
		CDListMgr* pCuList	= pDelNode->GetCurveList();
		////////////////////////////////////////////////
		pCnList->RemoveTail();
		pCuList->RemoveTail();
		////////////////////// Form THE Main List
		CDListMgr*	pDListMgr 	= pObjectMgr->GetObjectList(NODE);
		int index = pDListMgr->GetObjectIndex(pDelNode);
		if(index>=0)
		{
			///////////////////////////////////////////////// DELETE:DataBase
			pObjectMgr->DeleteFromDataBase(index, NODE);
			/////////////////
			nINode--;
			/////////
		}
		else
		{
			AfxMessageBox("Internal Problem:\nCMI_CProf::GetNumberOfNodes_1");
			return -1;
		}
	}
	///////////////////////////////////////////// Save Wts
	pDOUBLE pOutWts = new double[nINodeSave];
	for(i=0;i<nINode;i++)
		*(pOutWts+i) = 1.0;
	////////////////////////////////////// Save Wts:DELETED in DrCurve 
	m_pDrCurve->SetpWts_BZ_S(pOutWts); 
   	//////////////
	return nINode;

}
				
int CMI_CProf::SaveMeshAsNewINodes(pWORLD pMNodes, pDOUBLE pWts, int nMNodes, int nCur, BOOL bLast)
{

	//////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////
	C3DMath	Math3D;
	CXForm	XForm(TRUE);	// TRUE = Parallel
	////////////////////
	MATRIX		LMP;	
	pMATRIX		pLMP = &LMP;
//	Math3D.GetIdentityMATRIX(pLMP);
	/////////
	BOOL bYesP = FALSE;
/*	
	CMatObj*	pMatObj = m_pDrProf->GetMatObj();
	if(pMatObj->IsInstanced())
	{	
		LMP = *(pMatObj->GetMatrix());
		bYesP	= TRUE;
	}
*/
	////////////////////////////////////////// create New Control Nodes
	WORLD		LocalPos;
	CString		Nid,ObjID;
	int			nChLen;
	char		buf[50];
	CDrNode* 	pAddNode;
	CDrNode* 	pAddCNode;
	int			s,t=0,index;
	int			nLastNum;
	//////////////////////////////////// Name
	ObjID	= m_CurveID;	// ProfileCurve Name
	nChLen	= ObjID.GetLength();
	if(nChLen>NUM_LEN-2)
	nChLen = NUM_LEN-2;
	//////////////////////////////////// drop last pt. of all but LAST Curve
	int nTot = nMNodes-1;
	if(bLast)
		nTot++;
	//////////////////////////////	
	for (s = 0; s<nTot; s++)
	{
		/////////////////////////////////////////////////////
		nLastNum	= pObjectMgr->GetLastObjectNo(NODE);		// internal
		sprintf(buf,"%d",nLastNum);
		Nid	= "";
		Nid	+= buf;
		pObjectMgr->BumpLastObjectNo(NODE);		// bump it
		/////////////////////////////////////////////////////////// CREATE	
		//////////////////////////////////// Node Index in m_pOut
		index 		= s;
		LocalPos 	= *(pMNodes+index);
/*
		///////////////////////////////////// Use Xform, if necessary to create Loc
		if(bYesP)
			XForm.Transform(&LocalPos, &LocalPos, pLMP);
*/
		////////////////////////////////////////////////////////////////////////// Node
		CDrLabel*	pLabel;
		int nNodeIndex,nLabelIndex;
		BOOL bGen	= TRUE;
		BOOL bMNode = FALSE;
		BOOL bCNode	= FALSE;
		/////////////////////////// Create Anyway
		nNodeIndex = -12345;
		pAddNode = CreateNode(Nid,pLabel,LocalPos,bCNode,bGen,bMNode,
															nNodeIndex,nLabelIndex);
													// TRUE = Internally Generated
		if(!pAddCNode)	
			return -1;
		///////////////////////////////////////
		m_pDrCurve->GetINodeList()->InsertObject(pAddNode);
		pAddNode->GetCurveList()->InsertObject(m_pDrCurve);
		////////////////////////////////////////////////////////////////////////// CNode
//		Nid	= ObjID.Left(nChLen);
		Nid	= ObjID;
   		//////////////////////////////////// Name
   		sprintf(buf,"%d_%d%d",nCur,s,t);
   		Nid += buf; 
		//////////////////////////////////////////////////
//092798		pAddCNode = PostNode(Nid,LocalPos,FALSE,FALSE);	// Create DrNode
		pAddCNode = PostNode(Nid,LEVEL_KIDDO,LocalPos,FALSE);	// Create DrNode
		if(!pAddCNode)	
			return -1;
		///////////////////////////////////////
		m_pDrCurve->GetCNodeList()->InsertObject(pAddCNode);	// also SAVE AS CONTROL NODES
		//////////////////////////////////////// Reciprocate
//		pAddCNode->SetLevelType(LEVEL_KIDDO);
		pAddCNode->GetCurveList()->InsertObject(m_pDrCurve);
		////////
	}
	////////////////////////////////////// DONOT Save Wts DONE LATER
//	m_pDrCurve->SetpWts_BZ_S(pWts); 
	/////////
	return nTot; 
}

void CMI_CProf::SetInfoForProfileCurveBase(CDrCurve* pDrObject)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
    pDrObject->SetObjectType((int)CURVE);
    pDrObject->SetElemType((int)GENR_OBJECT);          	// globals
    pDrObject->SetLevelType((int)LEVEL_UNCLE);          // globals
    //////////////////////////////
	pDrObject->SetObjectID(m_CurveID);	
	pDrObject->SetClosed_S(m_bClosed_S);
 	////////////////////////////////////////////////////////////// interpolation
	pDrObject->SetData_S(m_nData_S);		// GIVEN: # of Data
	pDrObject->SetMaxINodes_S(m_nData_S);
	pDrObject->SetOrder_S(m_nOrder_S);				// k
	//////////////////////////////////////////////// Update	 
	m_nCon_BS_S 	= m_nData_S + m_nOrder_S - 2;	        // L + k - 1 = nData + k - 2 = n + 1
	m_nSeg_DT_S		= m_nData_S - 1;
	m_nKnots_S 		= m_nData_S;
	m_nMKnots_S		= m_nData_S + (2 * m_nOrder_S - 2);	// n + k + 1 = nData + (2k - 2)
	if(m_bClosed_S)
	{
		m_nSeg_DT_S++;
		m_nKnots_S++;
		m_nMKnots_S++;
	}
    ////////////////////////
    m_CurveType_S	= CP_LINEAR;			// ALWAYS
	pDrObject->SetCurveType_S(m_CurveType_S);
	//////////////////////////////
	pDrObject->SetnDim_S(m_nDim_S);
	////////////////////////////////////////////////////////
	pDrObject->SetnCon_BS_S(m_nCon_BS_S);	// L + k - 1
											// = nData + k - 2
											// = n + 1 (B-Spline));
	pDrObject->SetnKnots_S(m_nKnots_S);
	pDrObject->SetnMKnots_S(m_nMKnots_S);
	////////////////////////////////////////
	int nCon_BZ	= (m_nOrder_S - 1) * m_nSeg_DT_S + 1;	// (k-1) * L + 1 , Open
	if(m_bClosed_S)
		nCon_BZ--; 		
	pDrObject->SetnCon_BZ_S(nCon_BZ); // = m_nMaxCurveCNodes_S(Eventually)
	////////////////////////////////////////////////////////////////////// Mesh(Output)
	pDrObject->SetUniform_S(m_bUnifOT);		// Output Distribution:
	pDrObject->SetOutMethod_S(CO_HORNER);		// Output Method
	pDrObject->SetRatio_S(1.0);					
	///////////////////////////////////////////////////////////// ReDistribute
	int i;
	//////////////////////////////////////////////////// View Matrices
//	int m_nMaxOSeg = 1;// Done in Generate_CurveDataInfo()
	///////////////////
	if(m_bUnifOT)
	{
		m_pOSeg = new int[m_nSeg_DT_S];
		///////////////////////////////
		for (i=0;i<m_nSeg_DT_S;i++)
		{
			m_pOSeg[i] = m_nMaxOSeg;
		}
	}
	//////////////////////////////////////////
	CList<int,int> ElperSegList;
	ElperSegList.AddTail(1);	// 1 elem/seg
	pDrObject->GetElperSegList_S()->AddTail(&ElperSegList);	// save for later editing etc
	//////////////////////////////////////////		 
	pDrObject->SetUniform_S(m_bUnifOT);		// Output Distribution:
	pDrObject->SetMaxOutSeg_S(m_nSeg_DT_S);	// Number of Output Segments
											// = nData - 1 = L = m_nCurveSeg
	pDrObject->SetNum_tPointer_S(m_pOSeg);	// Number of Outputs for
											// each Curve Segment
	//////////////////////////////////////////
	pDrObject->SetOutSegUnif_S(m_nMaxOSeg); 	// for Old Compatibility
    ////////////////////////////////////////////// Total Evaluation Pts
	int nOut = 0;
	
	for (i=0;i<m_nSeg_DT_S;i++)
		nOut += *(m_pOSeg+i);
    nOut++;
	////////////////////////////////
	pDrObject->SetMaxOutPts_S(nOut);
	pDrObject->SetLongOutPts((long)nOut);
	////////////////////////////////////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
} 

////////////////////////////////////////////////////////////////////////// CONTROL INFO
int CMI_CProf::Generate_CurveControlInfo()
{
	int nDegree,nCon_BZ;
	//////////////////////////////////////////////////////////// Prepare
	Prep_CurveControlInfo(m_pDrProf); // TopDegree?,Closed? etc
	nDegree = m_nOrder_S - 1;
	//////////////////////////////////////////////////////////// Do it
	// Total Expected CNodes
	nCon_BZ = GetNumberOfCNodes(m_pDrProf,nDegree,m_bClosed_S);
	pWORLD  pCon_BZ = new WORLD [nCon_BZ]; 	
	pDOUBLE pWts_BZ = new double[nCon_BZ];
	///
	GoDoIt(m_pDrProf,pCon_BZ,pWts_BZ,nCon_BZ,nDegree,m_bClosed_S,m_nDim_S);
	///////////////////////////////////////////////////////////// Post
	Post_CurveControlInfo(m_pDrProf,pCon_BZ,pWts_BZ,nCon_BZ);
	//////
	delete [] pCon_BZ;
	////////////
	return 0;

}

int CMI_CProf::Prep_CurveControlInfo(CDrProf_C* pDrProf)
{
	m_CurveID	= "PC_";
	m_CurveID	+= pDrProf->GetObjectID();
	/////////////////////////////////////// Rational?
	m_nDim_S	= 3;
	if(IsRational(pDrProf))
		m_nDim_S	= 4;
	/////////////////////////////////////// Closed
	m_bClosed_S	= IsProfileClosed(pDrProf);
	/////////////////////////////////////// Find Highest Degree
	int nDegree	= GetTopDegree(pDrProf);
	m_nOrder_S	= nDegree + 1;	// k = n + 1
	////////////
	return 0;
}

int CMI_CProf::Post_CurveControlInfo(CDrProf_C* pDrProf,pWORLD pCon_BZ,pDOUBLE pWts_BZ,
																			int nCon_BZ)
{
	CDrCurve* pCurve = pDrProf->GetCurve(); 
	/////////////////////////////////////////// Create CNodes
	PostNewCNodes(pDrProf,pCon_BZ, nCon_BZ);
	/////////////////////////////////////////// Post Weights,Knots etc
	pCurve->SetpWts_BZ_S(pWts_BZ);
//	delete [] pWts_BZ;	donot delete here, taken care of by DrCurve
	/////////////////////////////////////////////////////////////// ReParametrize? (later!)
	m_nSeg_DT_S = (nCon_BZ - 1)/(m_nOrder_S - 1);
	m_nSeg_DT_S += m_bClosed_S?1:0;
	m_nData_S = m_nSeg_DT_S + 1;		// fictitious
	m_nData_S += m_bClosed_S?-1:0;
	//////////////////////////////
	if(m_nOrder_S == 2) // Linear
		m_CurveType_S = CP_LINEAR;
	else
	if(m_nOrder_S == 3) // Quadratic
		m_CurveType_S = CP_QUADRATIC;
	else
	if(m_nOrder_S == 4) // Cubic
		m_CurveType_S = CP_NURB;
	////////////
	return 0;
}

BOOL CMI_CProf::IsRational(CDrProf_C* pDrProf)
{
	/////////////////////////////////// 
	CDListMgr*	pList = pDrProf->GetCurveList();	// Curves making up Profile
	//////////////////////////////////////////////////////////// Find Highest Degree
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrCurve* pCurve = (CDrCurve*)pList->GetNextObject(pos);
		if(!pCurve)
			continue;
   	 	///////////////////////////////////////////// Get Degree/Update
		int nDim = pCurve->GetnDim_S();
		if(4 == nDim)
			return TRUE;	
		/////	
	}
	return FALSE;
}

int CMI_CProf::GetTopDegree(CDrProf_C* pDrProf)
{
	/////////////////////////////////// 
	CDListMgr*	pList = pDrProf->GetCurveList();	// Curves making up Profile
	int nDegree=0,nDeg_C;
	//////////////////////////////////////////////////////////// Find Highest Degree
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrCurve* pCurve = (CDrCurve*)pList->GetNextObject(pos);
		if(!pCurve)
			continue;
   	 	///////////////////////////////////////////// Get Degree/Update
		nDeg_C = (pCurve->GetOrder_S()) - 1;
		if(nDeg_C>nDegree)
			nDegree = nDeg_C;
		/////	
	}
	return nDegree;
}

BOOL CMI_CProf::IsProfileClosed(CDrProf_C* pDrProf)
{
	// If Profile Closed: Seg = Seg -1;
	////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	///////////////////////////////////////////////
	C3DMath Math3D;
	////////////////////////////////////////////////////////
	CDListMgr*	pList = pDrProf->GetCurveList();	// Curves making up Profile
	//////////////////////////////////////////////////////////// Find Ist & Last
	CDrCurve* pCurBeg = (CDrCurve*)pList->GetHead();
	CDrCurve* pCurEnd = (CDrCurve*)pList->GetTail();
	if(pCurBeg == pCurEnd)								// Only One Curve
		return pCurBeg->IsClosed_S();
	/////////////////////////////////////////////////////////////////
	CDrNode* pNodBeg = (CDrNode*)(pCurBeg->GetCNodeList()->GetHead());
	CDrNode* pNodEnd = (CDrNode*)(pCurEnd->GetCNodeList()->GetTail());
	/////////////////
	WORLD wLocBeg = *(pNodBeg->GetLocalPos());
	WORLD wLocEnd = *(pNodEnd->GetLocalPos());
	//////////////////////////////////////////
	return Math3D.AreSame_WORLD(&wLocBeg,&wLocEnd,pHitNet->GetDblRatio());
}
	
int CMI_CProf::GetNumberOfCNodes(CDrProf_C* pDrProf,int nDegree,BOOL bClosed)
{
	/////////////////////////////////// 
	CDListMgr*	pList = pDrProf->GetCurveList();	// Curves making up Profile
	int nCon_BZ=0,nDeg_C,nElev,nCurveSeg,nCon;
	//////////////////////////////////////////////////////////// Total CNodes
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrCurve* pCurve = (CDrCurve*)pList->GetNextObject(pos);
		if(!pCurve)
			continue;
   	 	///////////////////////////////////////////// Get Degree/Update
		nDeg_C		= (pCurve->GetOrder_S()) - 1;
		nElev		= nDegree - nDeg_C;	// How many Elevations	
		nCon 		= pCurve->GetMaxCNodes_S();
		nCurveSeg 	= pCurve->GetMaxBezSegments_S();
   		///////////////////////////////////////////// Update Total Control Nodes
   		nCon_BZ	+= (nCon-1);	// tie pts are common
   		if(nElev>0)
   			nCon_BZ	+= nElev * nCurveSeg;	// nElev Cnodes per Curve Segment 
   		///////////////////////////////////////////// Not Closed, Add One
	}
	///////////////////////// NOT Closed, Add One
	nCon_BZ += (bClosed)?0:1;
	///////////////
	return nCon_BZ;

}

int CMI_CProf::GoDoIt(CDrProf_C* pDrProf)
		/////////////////////////////////
		// THIS IS FOR REGENERATION
		//////////////////////////////////////////////////////////// 
		// New Control Nodes (Circular Component present)
		// Special for blend situation
		// Temporary Blend Curves are generated as CP_BEZIER(Order=4:Cubic)
		///////////////////////////////////////////////////////////////////
{
	m_pDrProf	= pDrProf;
	m_pDrCurve	= pDrProf->GetCurve();
	///////////////////////////////////////////////
	//////// delete all
	CDListMgr* pCNodeList	= m_pDrCurve->GetCNodeList();
	while(!pCNodeList->IsEmpty())
		delete pCNodeList->RemoveHead();
	/////	
	Generate_CurveControlInfo();
//	Reciprocate_Curves();	// Private: DONOT RECIPROCATE 
	/////////////////////////////////////// save CurveInfo
	SetInfoForProfileCurveBase_CONTROL(m_pDrCurve);
	/////////////////////////////////////
	return MA_OK;
}

int CMI_CProf::GoDoIt(CDrProf_C* pDrProf,pWORLD pCon_BZ,pDOUBLE pWts_BZ,int nCon_BZ,
												int nDegree, BOOL bClosed, int nDim)
{
	/////////////////////////////////////////////////////////////// Degree Elevate 
	int nConActual = Elevate_Profile(pDrProf,pCon_BZ, pWts_BZ, nDegree, bClosed, nDim);
	if(nConActual != nCon_BZ)
	{
		AfxMessageBox("Internal Problem:\nCMI_CProf::Elevate_Profile");
		return -1;
	}									
	/////////
	return 0;
}

int CMI_CProf::Elevate_Profile(CDrProf_C* pDrProf,pWORLD pCon_BZ, pDOUBLE pWts_BZ, 
												int nDegree,BOOL bClosed, int nDim)
{
	CDegElevate DegElevate;
	/////////////////////////////////// 
	int m,nDegOld,nElev,nSeg_BZ,nConOld,nConNew,nConTot=0,nBegNew=0;
	/////////////////////////////////////// 	
	CDListMgr*	pList = pDrProf->GetCurveList();	// Curves making up Profile
	int nCurveMax = pList->GetCount();
	int nCount=0; 			
  	////////////////////////////////////////// memory	
	pWORLD  pConOld;
	pDOUBLE pWtsOld;
	pWORLD  pConNew;
	pDOUBLE pWtsNew;
	//////////////////////////////////////////////////////////// Controls
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrCurve* pCurve = (CDrCurve*)pList->GetNextObject(pos);
		nCount++;
		/////////
		if(!pCurve)
			continue;
		/////////////////////////////////////// GetControl Nodes
		nConOld 	= pCurve->GetMaxCNodes_S();
		nDegOld		= (pCurve->GetOrder_S()) - 1;
		nElev		= nDegree - nDegOld;	// How many Elevations	
		nSeg_BZ 	= pCurve->GetMaxBezSegments_S();
   		/////////////////////////////////////// 
   		nConNew		= nConOld;	
   		if(nElev>0)
   			nConNew	+= nElev * nSeg_BZ;	// nElev Cnodes per Curve Segment 
   		////////////////////////////////////////// memory	
		pConOld 	= new WORLD [nConOld];
		pWtsOld 	= new double[nConOld];
		pConNew 	= new WORLD [nConNew];
		pWtsNew 	= new double[nConNew];
		////////////////////////////////////////// get Old 
		GetCNodeCoords_N_Wts(pCurve, pConOld, pWtsOld);
   	 	///////////////////////////////// 
		int nConActual = DegElevate.Elevate_Curve
							(pConOld, pWtsOld, nDegOld, nElev, pConNew, pWtsNew,
								nSeg_BZ, nDim);
   		////////////////////////////////////////// Free memory
		delete [] pConOld;
		delete [] pWtsOld;
		//////////////////
		if(nConActual != nConNew)
		{
			AfxMessageBox("Internal Problem:\nCMI_CProf::Elevate_Profile");
			return -1;
		}									
		/////////////////////////////////////// save
		for(m=0;m<nConNew-1;m++)	// last Pt = tie Pt (common)
		{
			nConTot++;
			///////////////
			pCon_BZ[nBegNew+m].x = pConNew[m].x; 	
			pCon_BZ[nBegNew+m].y = pConNew[m].y; 	
			pCon_BZ[nBegNew+m].z = pConNew[m].z; 	
			pWts_BZ[nBegNew+m]   = pWtsNew[m]; 	
			///////////////////////////////////
		}
		nBegNew += (nConNew - 1);									
   		////////////////////////////////////////// Free memory
   		if(nCount<nCurveMax)
   		{	
			delete [] pConNew;
			delete [] pWtsNew;
		}	
		////////////////////////////////////////// 
	}
	////////////////////////////////////////////// save Last Curve:Last CNode:If NOT Closed
	if(!bClosed)
	{
		nConTot++;
		///////////////
		pCon_BZ[nBegNew].x = pConNew[nConNew-1].x; 	
		pCon_BZ[nBegNew].y = pConNew[nConNew-1].y; 	
		pCon_BZ[nBegNew].z = pConNew[nConNew-1].z; 	
		pWts_BZ[nBegNew]   = pWtsNew[nConNew-1];
	}		
	////////////////////////////////////////// Free memory: last time
	delete [] pConNew;
	delete [] pWtsNew;
	//////////////////
	return nConTot;
}

int CMI_CProf::GetCNodeCoords_N_Wts(CDrCurve* pCurve, pWORLD pConOld, pDOUBLE pWtsOld)
{
	CDListMgr* pList	= pCurve->GetCNodeList();
	pDOUBLE pWts		= pCurve->GetpWts_BZ_S();
	int nCon_BZ			= pCurve->GetMaxCNodes_S();
	/////////////////////////////////////////////////////////////// Coords 
	int j=-1;
	if(!pList->IsEmpty())
	{
		////////
		for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrNode* pNode = (CDrNode*)pList->GetNextObject(pos);
			//////////////////////////////////
			pConOld[++j] = *(pNode->GetLocalPos());
			//////////////////////////////////
		}
	}
	/////////////////////////////////////////////////////////////// Wts
	for(j=0;j<nCon_BZ;j++)
		pWtsOld[j] = pWts[j];
	/////////
	return 0;
}
/*
int CMI_CProf::Elevate_Curve
				(
					pWORLD pConOld, pDOUBLE pWtsOld,int nDegOld,int nElev,
					pWORLD pConNew, pDOUBLE pWtsNew,int nSeg_BZ, int nDim
				)
{
	//////////////////////////////////////// Elevate, if necessary
	int m,nBegOld,nBegNew,nDegNew = nDegOld;
	//////////////////////////////////////// Memory
	pWORLD  pConOtem = new WORLD[4];
	pWORLD  pConNtem = new WORLD[4]; 	// reserved for cubic
	pDOUBLE pWtsOtem = new double[4];
	pDOUBLE pWtsNtem = new double[4]; 	// reserved for cubic
	/////////////////////////////// save Ist One
	int nConNew = 0;
	///////////////
	pConNew[0].x = pConOld[0].x; 	
	pConNew[0].y = pConOld[0].y; 	
	pConNew[0].z = pConOld[0].z; 	
	pWtsNew[0]   = pWtsOld[0]; 
	////////
	nConNew++;
	/////////////////////////////////////////////////// Loop Seg_BZ
	for(int nc=0;nc<nSeg_BZ;nc++)
	{
		nBegOld = nc * nDegOld;
		nBegNew = nc * nDegNew;
		///////////////////////////
		for(m=0;m<=nDegOld;m++)
		{
			pConOtem[m] = pConOld[nBegOld+m];
			pWtsOtem[m] = pWtsOld[nBegOld+m];
		}
		/////////////////////////////////////// Go Elevate	
		nDegNew = Elevate_BezSeg(pConOtem, pWtsOtem, nDegOld, nElev,
							pConNtem, pWtsNtem, nDim);
		/////////////////////////////////////// save
		for(m=1;m<=nDegNew;m++)
		{
			nConNew++;
			///////////////
			pConNew[nBegNew+m].x = pConNtem[m].x; 	
			pConNew[nBegNew+m].y = pConNtem[m].y; 	
			pConNew[nBegNew+m].z = pConNtem[m].z; 	
			pWtsNew[nBegNew+m]   = pWtsNtem[m]; 	
		}
	}										
	//////////////////////////////////////// Free Memory
	delete [] pConOtem;
	delete [] pConNtem; 
	delete [] pWtsOtem;
	delete [] pWtsNtem; 
    ///////////////////
    return nConNew;
     
}
				
int CMI_CProf::Elevate_BezSeg
				(
					pWORLD pConOld, pDOUBLE pWtsOld,int nDegOld,int nElev,
					pWORLD pConNew, pDOUBLE pWtsNew, int nDim
				)
{
	/////////////////////////////////////////////////////////////////////
	//				 since Maximum Degree = 3 ( Cubic), 
	//		nElev can only be:
	//				 0 = No Elevation
	//				 1 = Lin to Quad or Quad to Cubic
	//				 2 = Lin to Quad to Cubic
	/////////////////////////////////////////////////////////////////////
	int nDegNew = nDegOld;				// for no Elevation
	for(int m=0;m<=nDegOld;m++)  		
	{
		pConNew[m] = pConOld[m];
		pWtsNew[m] = pWtsOld[m];
	}	
	////////////////////////////////////// Once
	if(nElev>0)
	{	  
		DegreeElevate(pConOld, pWtsOld, nDegOld, pConNew, pWtsNew, nDim);
		nDegNew++;
	}	
	////////////////////////////////// Twice
	if(nElev>1)
	{	
		DegreeElevate(pConNew, pWtsNew, nDegNew, pConOld, pWtsOld, nDim);
		nDegNew++;
		//////////////////////////////////////
		for(int m=0;m<nDegNew;m++)
		{
			pConNew[m].x	= pConOld[m].x;		// put it back
			pConNew[m].y	= pConOld[m].y;		// put it back
			pConNew[m].z	= pConOld[m].z;		// put it back
			pWtsNew[m]		= pWtsOld[m];		// put it back
		}
	}
	///////////////
	return nDegNew;
			
}

int CMI_CProf::DegreeElevate(pWORLD Con_BZ, pDOUBLE Wts_BZ, int nDegree, 
							 pWORLD NewCon_BZ, pDOUBLE NewWts_BZ, int nDim)
{

	int	i,nNewDeg = nDegree + 1;
	//////////////////////////////
	NewCon_BZ[0].x 	= Con_BZ[0].x;  							  
	NewCon_BZ[0].y 	= Con_BZ[0].y;  							  
	NewCon_BZ[0].z 	= Con_BZ[0].z;
	//////////////////////////////  							  
	if(4 == nDim)					// Rational
		NewWts_BZ[0]	= Wts_BZ[0];
	else	  							  
		NewWts_BZ[0]	= 1.;  							  
	/////////////////////////////
    for(i=1;i<=nDegree;i++)
    {
		double alfa = ((double)i)/((double)nNewDeg);
		double alf1 = 1. - alfa;
		//////////////////////////////
		if(4 == nDim)					// Rational
		{ 
			NewWts_BZ[i]	= 	Wts_BZ[i-1] * alfa + Wts_BZ[i] * alf1;
			//////////////////////////////////////////////////////////  							  
			NewCon_BZ[i].x 	= (	Wts_BZ[i-1] * Con_BZ[i-1].x * alfa + 
								Wts_BZ[i  ]	* Con_BZ[i  ].x * alf1	)/NewWts_BZ[i];  							  
			NewCon_BZ[i].y 	= (	Wts_BZ[i-1] * Con_BZ[i-1].y * alfa + 
								Wts_BZ[i  ]	* Con_BZ[i  ].y * alf1	)/NewWts_BZ[i];  							  
			NewCon_BZ[i].z 	= (	Wts_BZ[i-1] * Con_BZ[i-1].z * alfa + 
								Wts_BZ[i  ]	* Con_BZ[i  ].z * alf1	)/NewWts_BZ[i];
			/////////////////
		}
		else								// Non-Rational
		{	
			//////////////////////////////////////////////////////////  							  
			NewCon_BZ[i].x 	= (	Con_BZ[i-1].x * alfa + 
								Con_BZ[i  ].x * alf1	);  							  
			NewCon_BZ[i].y 	= (	Con_BZ[i-1].y * alfa + 
								Con_BZ[i  ].y * alf1	);  							  
			NewCon_BZ[i].z 	= (	Con_BZ[i-1].z * alfa + 
								Con_BZ[i  ].z * alf1	);
			NewWts_BZ[i]	= 	1.;
			/////////////////
		}			
	}
	/////////////////////////////
	NewCon_BZ[nNewDeg].x 	= Con_BZ[nDegree].x;  							  
	NewCon_BZ[nNewDeg].y 	= Con_BZ[nDegree].y;  							  
	NewCon_BZ[nNewDeg].z 	= Con_BZ[nDegree].z;
	////////////////////////////////////////////  							  
	if(4 == nDim) 
		NewWts_BZ[nNewDeg]	= Wts_BZ[nDegree];  							  
	else
		NewWts_BZ[nNewDeg]	= 1.;
	/////////////////////////////
	return 0;
}											  							  
*/				
int CMI_CProf::PostNewCNodes(CDrProf_C* pDrProf,pWORLD pCon_BZ, int nCon)
{

	CDrCurve* pCurve = pDrProf->GetCurve(); 
	////////////////////////////////////////// create New Control Nodes
	WORLD		LocalPos;
	CString		ObjID;
	int			nChLen;
	CDrNode* 	pAddNode;
	int s,t=0,index;
	//////////////////////////////////// Name
	ObjID	= pDrProf->GetObjectID();	// Profile Name
	nChLen	= ObjID.GetLength();
	if(nChLen>NUM_LEN-2)
	nChLen = NUM_LEN-2;
	//////////////////////////////	
	for (s = 0; s<nCon; s++)
	{
		///////////////////////////////////////// CREATE	
   		//////////////////////////////////// Name
		CString* pNid = new CString;
		char* buf = pNid->GetBuffer(BUFF_SIZE);
	    sprintf(buf,"%s_PC_%d%d",ObjID,s,t);
		//////////////////////////////////// Node Index in m_pOut
		index 		= s;
		LocalPos 	= *(pCon_BZ+index);
		///////////////////////////////////// in THE List 
		pAddNode = PostNode(*pNid,LEVEL_KIDDO,LocalPos,TRUE);	// Create DrCNode
		delete pNid;
		/////////////
		if(!pAddNode)	
			return -1;
		///////////////////////////////////// in Curve 	
		pAddNode->SetLevelType((int)LEVEL_KIDDO);          // private
		///////////////////////////////////////
		pCurve->GetCNodeList()->InsertObject(pAddNode);
		//////////////////////////////////////// Reciprocate
//		pAddNode->GetCurveList()->InsertObject(pCurve); 	// private:Do Not Reciprocate
		////////
	}
	/////////
	return 0; 
}
				
void CMI_CProf::CollectOutputInfo_CONTROL(CList<int,int>& ElperSegList)
{
	BOOL	bFirst = TRUE;
	WORLD	LocalPos;
	/////////////////////////////////// 
	CDListMgr*	pList		= m_pDrProf->GetCurveList();	// Curves making up Profile
	CDrCurve* pProfCurve	= m_pDrProf->GetCurve();
	pProfCurve->GetBndryPtList()->RemoveAll();
	ElperSegList.RemoveAll();
	//////////////////////////////////////////////////////////// 
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrCurve* pCurve = (CDrCurve*)pList->GetNextObject(pos);
		if(!pCurve)
			continue;
		///////////////////////////////////////////// Output/seg
		int nSegs = pCurve->GetMaxBezSegments_S();
		m_pOSeg   = pCurve->GetNum_tPointer_S();	// Number of Outputs for
													// each Curve Segment
		if(pCurve->GetCurveType_S() == CP_CIRCLE)
			m_pOSeg   = pCurve->GetNum_tPointer_Ex_S();	// Number of Outputs for
		/////
		for(int i=0;i<nSegs;i++)
			ElperSegList.AddTail(m_pOSeg[i]);
		///////////////////////////////////////////////////////// BndryPts
		CDListMgr* pCNodeList = pCurve->GetCNodeList();
		if(bFirst)
		{
			CDrNode* pCNode = (CDrNode*)pCNodeList->GetHead();	// first one
			LocalPos = *(pCNode->GetLocalPos());
			//////////////////////////////////////////////// save
			pProfCurve->GetBndryPtList()->AddTail(LocalPos);
			//////////
			bFirst = FALSE;
		}
		///////////////		
		CDrNode* pCNode = (CDrNode*)pCNodeList->GetTail();	// last ones
		LocalPos = *(pCNode->GetLocalPos());
		//////////////////////////////////////////////// save
		pProfCurve->GetBndryPtList()->AddTail(LocalPos);
		//////////
	}
	return;
}

void CMI_CProf::Reciprocate_Curves()
{
	int index;
	/////////////////////////////////// 
	CDListMgr*	pList = m_pDrProf->GetCurveList();	// Curves making up Profile
	//////////////////////////////////////////////////////////// 
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrCurve* pCurve = (CDrCurve*)pList->GetNextObject(pos);
		if(!pCurve)
			continue;
		///////////////////////////////////////////// Reciprocate
		index = pCurve->GetCProfList()->GetObjectIndex(m_pDrProf);
		if(index<0) // not stored yet
			pCurve->GetCProfList()->InsertObject(m_pDrProf);
		///
	}
	return;
}

int CMI_CProf::GenerateProfileINodes(CDrCurve* pProfCurve,CDrProf_C* pDrProf)
{
	int nResult = MA_OK;
	////////////////////////////////////////////////
	// These Nodes are Handles for Rigid Move etc.
	// For Non-rigid Move etc. Characters of component
	// Curves will be CHANGED !
	////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////// 
 	CDListMgr*	pINodeList	= pProfCurve->GetINodeList(); // New Curve in Profile
	pINodeList->RemoveAll();
	/////////////////////////////////////////////////
	int indexCurve=-1;
	////////////////////////////////////////////////////////////
	CDrNode* pEndNode = NULL;
	CDListMgr*	pCurveList = pDrProf->GetCurveList();	// Curves making up Profile
	for (POSITION pos = pCurveList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrCurve* pDrCurve = (CDrCurve*)pCurveList->GetNextObject(pos);
		if(!pDrCurve)
		{
			AfxMessageBox("Internal Problem:\nCMI_CProf::GenerateProfileINodes()\n!pDrCurve");
			return MA_ERROR;
		}
		/////////
		indexCurve++;
   	 	/////////////////////////////////////////////
		int indexNode = -1;
		///////////////////
   	 	CDListMgr* pCompNodeList = pDrCurve->GetINodeList();
		for (POSITION pos = pCompNodeList->GetFirstObjectPos();pos !=NULL;)
		{
			indexNode++;
			CDrNode* pParentNode = (CDrNode*)pCompNodeList->GetNextObject(pos); // advance
			////////////
			if((indexCurve>0) && (indexNode == 0))	// tiepoints on subsequent curves
			{
				if(pEndNode &&		//  && Merge Only at Generation Time( not at moveTime etc)
					pEndNode !=(CDrNode*)(pDrCurve->GetINodeList()->GetHead()) )
				{
					nResult = MergeComponentCurveEnds(pDrCurve,pEndNode);
				}
				continue;
			}
			/////////////
			pObjectMgr->ShowObject_On_Off(pParentNode,NODE,FALSE);
			//////////////////////////////////////////////////////////////// save in Cprof_Curve
			pINodeList->InsertObject(pParentNode);
			/////////////////////////////////////// Reciprocate
			int index = (pParentNode->GetCurveList())->GetObjectIndex(pProfCurve);
			if(index<0)	// not yet
				(pParentNode->GetCurveList())->InsertObject(pProfCurve);
			/////////////
			pObjectMgr->ShowObject_On_Off(pParentNode,NODE,TRUE);
			///////////////////////////////////////////////////// Update end
			pEndNode = pParentNode;
		}				
		//////////////////
	}
   	//////////////////////
	return MA_OK;
}

int CMI_CProf::MergeComponentCurveEnds(CDrCurve* pDrCurrentCurve,CDrNode* pPrevCurveEndNode)
{
	int nResult = MA_OK;
	////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////// 
	CDrNode* pRemNode = (CDrNode*)(pDrCurrentCurve->GetINodeList()->RemoveHead());
	/// remove Label and delete Node(it deletes Label) from DataBase
	CDListMgr* pDataList;
	pDataList = pObjectMgr->GetObjectList(LABEL);
	int indexRem;
	CDrLabel* pLabel = (CDrLabel*)(pRemNode->GetLabelList()->RemoveHead());
	indexRem = pDataList->GetObjectIndex(pLabel);
	if(indexRem>0)
		pObjectMgr->DeleteFromDataBase(indexRem,LABEL);
	///
	pDataList = pObjectMgr->GetObjectList(NODE);
	indexRem = pDataList->GetObjectIndex(pRemNode);
	pRemNode->SetLevelType((int)LEVEL_KIDDO);	// this will prevent attached
													// Curves deletion by this node	
	if(indexRem>0)
		pObjectMgr->DeleteFromDataBase(indexRem,NODE);
	////////////////////////////////////////////
	pDrCurrentCurve->GetINodeList()->AddHead(pPrevCurveEndNode);
	pPrevCurveEndNode->GetCurveList()->InsertObject(pDrCurrentCurve); //reciprocate
	//////
	return MA_OK;
}

int CMI_CProf::GenerateProfileSupport(CDrCurve* pProfCurve,CDrProf_C* pDrProf)
{
	int nResult = MA_OK;
	////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////////////////////////// PROFILE 
 	CList<SUPPCARD,SUPPCARD>* pStaLCardList = pProfCurve->GetSuppCardList();
	pStaLCardList->RemoveAll();
 	CDListMgr*	pStaLList	= pProfCurve->GetSuppList();
	pStaLList->RemoveAll();
	/////////////////////////////////////////////////
	int nCurCurve=0;
	CDrCurve* pDrCurveOld = NULL;
	////////////////////////////////////////////////////////////
	int nNodPossBeg,nNodPossEnd = 0;
	CDListMgr*	pCurveList = pDrProf->GetCurveList();	// Curves making up Profile
	int nCount = pCurveList->GetCount();
	////////////////////////////////////
	for (POSITION pos = pCurveList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrCurve* pDrCurve = (CDrCurve*)pCurveList->GetNextObject(pos);
		if(!pDrCurve)
		{
			AfxMessageBox("Internal Problem:\nCMI_CProf::GenerateProfileSupport()\n!pDrCurve");
			return MA_ERROR;
		}
		/////////////
		nCurCurve++;
		/////////////
		nNodPossBeg		= nNodPossEnd; 
		nNodPossEnd		= nNodPossBeg + pDrCurve->GetLongOutPts();
		///
		if( (nCurCurve == nCount) && (pDrCurve->IsClosed_S()))
			nNodPossEnd--;
		///
   	 	CList<SUPPCARD,SUPPCARD>* pCompStaLCardList = pDrCurve->GetSuppCardList();
		if(pCompStaLCardList->IsEmpty())
		{
			nNodPossEnd--; // pull back to the joint
			continue;
		}
   	 	/////////////////////////////////////////////////////////////////// StalCard
		int indexList = -1;
		///////////////////////////////////////////// Duplicate
		for (POSITION pos = pCompStaLCardList->GetHeadPosition();pos !=NULL;)
		{
			SUPPCARD StaLCard = pCompStaLCardList->GetNext(pos);
			SUPPPROC StaLProc = StaLCard.SuppProc;
			//////////////////////////////////////
			BOOL bToDrop = FALSE;
			/////////////////////
			if(pDrCurveOld)
			{
				////////////////////////////////////////////////////
				// if previous Curve has same StaLProc as in this
				// StaLCard, the first node Load should be dropped i,e.
				// nNodPos_S_Beg should be advanced by 1
				////////////////////////////////////////////////////
	  	 		CList<SUPPCARD,SUPPCARD>* pOldStaLCardList = pDrCurveOld->GetSuppCardList();
				for (POSITION posO = pOldStaLCardList->GetHeadPosition();posO !=NULL;)
				{
					SUPPCARD StaLCardOld = pOldStaLCardList->GetNext(posO);
					SUPPPROC StaLProcOld = StaLCardOld.SuppProc;
					////////////////////////////////////////////
					if(StaLProcOld == StaLProc)
					{
						bToDrop = TRUE;
						nNodPossEnd--;	// joint dropped, so pull back one
						////////////////////////////////////////////////// Label/LabelNode to show False
						CDListMgr* pCompStaLList = pDrCurve->GetSuppList();
						POSITION posS = pCompStaLList->
							FindIndex((indexList == -1)?0:indexList); // first pt. problem
						CDrLinSup* pStatic = (CDrLinSup*)pCompStaLList->GetAt(posS);
						/////
//						pStatic->GetLabelNode()->SetShow(FALSE);
//						pStatic->GetLabelPtr()->SetShow(FALSE);
						//////////////////////////////////////// increment, to drop
						indexList++;
//						nNodPossBeg++;
						break;
					}
				}
			}
			/////////////////////////////////////
			StaLCard.nNodPos_S_Beg = nNodPossBeg; 
			StaLCard.nNodPos_S_End = nNodPossEnd;
			/////////////////////////////////
			pStaLCardList->AddTail(StaLCard);
			/////////////////////////////////////////////////////////////// stack up
			CDListMgr* pCompStaLList = pDrCurve->GetSuppList();
			for(int iStaL=nNodPossBeg;iStaL<nNodPossEnd;iStaL++)
			{
				indexList++;
				POSITION posS = pCompStaLList->FindIndex(indexList);
				CDrLinSup* pStatic = (CDrLinSup*)pCompStaLList->GetAt(posS);
				///
				pStaLList->InsertObject(pStatic);
			}
		}
//		pProfCurve->GetStaLList()->AddTail(pDrCurve->GetStaLList());
		////////////////////////////////////////// update Old Curve
		pDrCurveOld = pDrCurve;
	}
	///////////////////////////////////////////////////////////////////////// Now,Regenerate
	if(!pStaLCardList->IsEmpty())
	{
		CMI_LSupp MI_Supp;
		MI_Supp.RegenCurveBased(pProfCurve);
	}
   	//////////////////////
	return MA_OK;
}

int CMI_CProf::GenerateProfileStatic(CDrCurve* pProfCurve,CDrProf_C* pDrProf)
{
	int nResult = MA_OK;
	////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////////////////////////// PROFILE 
 	CList<STALCARD,STALCARD>* pStaLCardList = pProfCurve->GetStaLCardList();
	pStaLCardList->RemoveAll();
 	CDListMgr*	pStaLList	= pProfCurve->GetStaLList(); 
	pStaLList->RemoveAll();
	/////////////////////////////////////////////////
	int nCurCurve=0;
	CDrCurve* pDrCurveOld = NULL;
	////////////////////////////////////////////////////////////
	int nNodPossBeg,nNodPossEnd = 0;
	CDListMgr*	pCurveList = pDrProf->GetCurveList();	// Curves making up Profile
	int nCount = pCurveList->GetCount();
	////////////////////////////////////
	for (POSITION pos = pCurveList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrCurve* pDrCurve = (CDrCurve*)pCurveList->GetNextObject(pos);
		if(!pDrCurve)
		{
			AfxMessageBox("Internal Problem:\nCMI_CProf::GenerateProfileStatic()\n!pDrCurve");
			return MA_ERROR;
		}
		/////////////
		nCurCurve++;
		/////////////
		nNodPossBeg		= nNodPossEnd; 
		nNodPossEnd		= nNodPossBeg + pDrCurve->GetLongOutPts();
		///
		if( (nCurCurve == nCount) && (pDrCurve->IsClosed_S()))
			nNodPossEnd--;
		///
   	 	CList<STALCARD,STALCARD>* pCompStaLCardList = pDrCurve->GetStaLCardList();
		if(pCompStaLCardList->IsEmpty())
		{
			nNodPossEnd--; // pull back to the joint
			continue;
		}
   	 	/////////////////////////////////////////////////////////////////// StalCard
		int indexList = -1;
		///////////////////////////////////////////// Duplicate
		for (POSITION pos = pCompStaLCardList->GetHeadPosition();pos !=NULL;)
		{
			STALCARD StaLCard = pCompStaLCardList->GetNext(pos);
			STALPROC StaLProc = StaLCard.StaLProc;
			//////////////////////////////////////
			BOOL bToDrop = FALSE;
			/////////////////////
			if(pDrCurveOld)
			{
				////////////////////////////////////////////////////
				// if previous Curve has same StaLProc as in this
				// StaLCard, the first node Load should be dropped i,e.
				// nNodPos_S_Beg should be advanced by 1
				////////////////////////////////////////////////////
	  	 		CList<STALCARD,STALCARD>* pOldStaLCardList = pDrCurveOld->GetStaLCardList();
				for (POSITION posO = pOldStaLCardList->GetHeadPosition();posO !=NULL;)
				{
					STALCARD StaLCardOld = pOldStaLCardList->GetNext(posO);
					STALPROC StaLProcOld = StaLCardOld.StaLProc;
					////////////////////////////////////////////
					if(StaLProcOld == StaLProc)
					{
						bToDrop = TRUE;
						nNodPossEnd--;	// joint dropped, so pull back one
						////////////////////////////////////////////////// Label/LabelNode to show False
						CDListMgr* pCompStaLList = pDrCurve->GetStaLList();
						POSITION posS = pCompStaLList->
							FindIndex((indexList == -1)?0:indexList); // first pt. problem
						CDrStatic* pStatic = (CDrStatic*)pCompStaLList->GetAt(posS);
						/////
						pStatic->GetLabelNode()->SetShow(FALSE);
						pStatic->GetLabelPtr()->SetShow(FALSE);
						//////////////////////////////////////// increment, to drop
						indexList++;
//						nNodPossBeg++;
						break;
					}
				}
			}
			/////////////////////////////////////
			StaLCard.nNodPos_S_Beg = nNodPossBeg; 
			StaLCard.nNodPos_S_End = nNodPossEnd;
			/////////////////////////////////
			pStaLCardList->AddTail(StaLCard);
			/////////////////////////////////////////////////////////////// stack up
			CDListMgr* pCompStaLList = pDrCurve->GetStaLList();
			for(int iStaL=nNodPossBeg;iStaL<nNodPossEnd;iStaL++)
			{
				indexList++;
				POSITION posS = pCompStaLList->FindIndex(indexList);
				CDrStatic* pStatic = (CDrStatic*)pCompStaLList->GetAt(posS);
				///
				pStaLList->InsertObject(pStatic);
			}
		}
//		pProfCurve->GetStaLList()->AddTail(pDrCurve->GetStaLList());
		////////////////////////////////////////// update Old Curve
		pDrCurveOld = pDrCurve;
	}
	///////////////////////////////////////////////////////////////////////// Now,Regenerate
	if(!pStaLCardList->IsEmpty())
	{
		CMI_StaL MI_StaL;
		MI_StaL.RegenCurveBased(pProfCurve);
	}
   	//////////////////////
	return MA_OK;
}

void CMI_CProf::SetInfoForProfileCurveBase_CONTROL(CDrCurve* pDrObject)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
    pDrObject->SetObjectType((int)CURVE);
    pDrObject->SetElemType((int)GENR_OBJECT);          	// globals
    pDrObject->SetLevelType((int)LEVEL_UNCLE);          // globals
    //////////////////////////////
	pDrObject->SetObjectID(m_CurveID);	
	pDrObject->SetClosed_S(m_bClosed_S);
	//////////////////////////////////////////////////////////////
	GenerateProfileINodes(pDrObject,m_pDrProf);
 	////////////////////////////////////////////////////////////// interpolation
	pDrObject->SetData_S(m_nData_S);		// GIVEN: # of Data
	pDrObject->SetMaxINodes_S(m_nData_S);
	pDrObject->SetOrder_S(m_nOrder_S);				// k
	//////////////////////////////////////////////// Update	 
	m_nCon_BS_S 	= m_nData_S + m_nOrder_S - 2;	        // L + k - 1 = nData + k - 2 = n + 1
	m_nSeg_DT_S		= m_nData_S - 1;
	m_nKnots_S 		= m_nData_S;
	m_nMKnots_S		= m_nData_S + (2 * m_nOrder_S - 2);	// n + k + 1 = nData + (2k - 2)
	if(m_bClosed_S)
	{
		m_nSeg_DT_S++;
		m_nKnots_S++;
		m_nMKnots_S++;
	}
    ////////////////////////
	pDrObject->SetCurveType_S(m_CurveType_S);
	pDrObject->SetnDim_S(m_nDim_S);
	////////////////////////////////////////////////////////
	pDrObject->SetnCon_BS_S(m_nCon_BS_S);	// L + k - 1
											// = nData + k - 2
											// = n + 1 (B-Spline));
	pDrObject->SetnKnots_S(m_nKnots_S);
	pDrObject->SetnMKnots_S(m_nMKnots_S);
	////////////////////////////////////////
	int nCon_BZ	= (m_nOrder_S - 1) * m_nSeg_DT_S + 1;	// (k-1) * L + 1 , Open
	if(m_bClosed_S)
		nCon_BZ--; 		
	pDrObject->SetnCon_BZ_S(nCon_BZ); // = m_nMaxCurveCNodes_S(Eventually)
	pDrObject->SetMaxBezSegments_S(m_nSeg_DT_S);		// Bezier Segments
													// Cubic:MisNomer!!
	/////////////////////////////////////////////////////////////////////// Output Info
	pDrObject->SetOutMethod_S(CO_HORNER);		// Output Method
	pDrObject->SetRatio_S(1.0);					
	pDrObject->SetUniform_S(FALSE);		// Output Distribution:
	pDrObject->SetMaxOutSeg_S(m_nSeg_DT_S);	// Number of Bezier Segments
											// = nData - 1 = L = m_nCurveSeg
	///////////////////////////////////////////////////////////// ReDistribute
	CList<int,int> ElperSegList;
	CollectOutputInfo_CONTROL(ElperSegList);
	//////////////////
	m_pOSeg = new int[m_nSeg_DT_S];
	///////////////////////////////
	for (int i=0;i<m_nSeg_DT_S;i++)
	{
		POSITION pos	= ElperSegList.FindIndex(i); 
		m_pOSeg[i]		= ElperSegList.GetAt(pos);
	}
	//////////////////////////////////////////
	pDrObject->GetElperSegList_S()->AddTail(&ElperSegList);	// save for later editing etc
	pDrObject->SetNum_tPointer_S(m_pOSeg);	// Number of Outputs for
											// each Curve Segment
	//////////////////////////////////////////
	pDrObject->SetMaxBezSegments_S(m_nSeg_DT_S); 	// for Old Compatibility
    ////////////////////////////////////////////// Total Evaluation Pts
	int nOut = 0;
	
	for (i=0;i<m_nSeg_DT_S;i++)
		nOut += *(m_pOSeg+i);
    nOut++;
	////////////////////////////////
	pDrObject->SetMaxOutPts_S(nOut);
	pDrObject->SetLongOutPts((long)nOut);
	////////////////////////////////////////////////////////////// Support & Static
	GenerateProfileSupport(pDrObject,m_pDrProf);
	GenerateProfileStatic(pDrObject,m_pDrProf);
	////////////////////////////////////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
} 
				
int CMI_CProf::SaveCoordsWtsinOldFoggies(CDrProf_C* pDrProf,pWORLD pCon_BZ,pDOUBLE pWts_BZ,int nCon)
{

	CDrCurve* pCurve		= pDrProf->GetCurve(); 
	CDListMgr* pCNodeList	= pCurve->GetCNodeList();
	///////////////////////////////////////////////////////////// store Coords
	WORLD		LocalPos;
	//////////////////////////////	
	for (int s = 0; s<nCon; s++)
	{
		//////////////////////////////////// Node Index in m_pOut
		int index = s;
		CDrNode* pNode = ((CDrNode*)pCNodeList->GetObject(index)); 
		LocalPos 	= *(pCon_BZ+index);
	    //////////////////////////////////////// Save as Local Pos
		pNode->SetLocalPos(LocalPos);
		/////////////////////////////
		(pNode->GetNodeCard())->x = (long)LocalPos.x;	
		(pNode->GetNodeCard())->y = (long)LocalPos.y;	
		(pNode->GetNodeCard())->z = (long)LocalPos.z;
		/////////////////////////////////////////////
	}
	///////////////////////////////////////////////////////////// store Weights
	pDOUBLE pOldWts = pCurve->GetpWts_BZ_S();
	delete pOldWts;
	pCurve->SetpWts_BZ_S(pWts_BZ);
	/////////
	return 0; 
}
///////////////////////////////////// end of Module //////////////////////		


