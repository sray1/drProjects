// Mouse.cpp : implementation file
//


#include "stdafx.h" 
#include <math.h> 

#include "glb_Type.h"
#include "glb_CuPS.h"

#include "drgraf.h"
///////////////////// 
//#include "drawview.h" //for curve/patch 
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "DListMgr.h"
///////////////////// dialogMgr
#include "EDlgMgr.h"  
#include "EDl2Mgr.h"  
///////////////////// elements
#include "eldefine.h"
#include "elextern.h"
#include "DrNode.h"
#include "DrCurve.h"
///////////////////// specials
#include "spdefine.h"
#include "booleans.h"
#include "precison.h"
/////////////////////
#include "MC_Circl.h" 

#include "MI_Cur_I.h" 
/////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////
IMPLEMENT_SERIAL(CMI_Cur_I,CObject,1)
/////////////////////////////////////
#define MIN_INODES_CURVE	2
#define new	DEBUG_NEW
#define	BUFF_SIZE			1024
#define	NUM_LEN				12 
#define	MAX_SEG_ANGLE		120
/////////////////////////////////////////////////////////////////////////////
CMI_Cur_I::CMI_Cur_I()
{

	m_nINodeDone   		= 0;
    /////////////////////////////////////////// Curve
	m_nMaxCurveINodes	= MIN_INODES_CURVE;
	m_bClosed_S			= FALSE;
	m_nSegsOut				= 0;
	/////////////////// Memory
	m_MemErr	= 0;
	m_pMKnot_S	= NULL;
	m_pKnot_S	= NULL;
	m_pWts_DT_S	= NULL;
	m_pWts_BS_S	= NULL;
	m_pWts_BZ_S	= NULL;
	m_pData		= NULL;
	m_pCon_BS_S	= NULL;
	m_pCon_BZ_S	= NULL;
	///////////////////
    
}

CMI_Cur_I::~CMI_Cur_I()
{
 
	/////////////////// Error:MemoryRelease
	if(m_MemErr<0)
	{
		if(m_pMKnot_S)
		{
			delete [] m_pMKnot_S;
			m_pMKnot_S = NULL;
		}	
		if(m_pKnot_S)
		{
			delete [] m_pKnot_S;
			m_pKnot_S = NULL;
		}	
		if(m_pWts_DT_S)
		{
			delete [] m_pWts_DT_S;
			m_pWts_DT_S = NULL;
		}	
		if(m_pWts_BS_S)
		{
			delete [] m_pWts_BS_S;
			m_pWts_BS_S = NULL;
		}	
		if(m_pWts_BZ_S)
		{
			delete [] m_pWts_BZ_S;
			m_pWts_BZ_S = NULL;
		}	
		if(m_pData)
		{
			delete m_pData;
			m_pData = NULL;
		}	
		if(m_pCon_BS_S)
		{
			delete [] m_pCon_BS_S;
			m_pCon_BS_S = NULL;
		}	
		if(m_pCon_BZ_S)
		{
			delete [] m_pCon_BZ_S;
			m_pCon_BZ_S = NULL;
		}	
	}	
    //////////////////////////////// Memory release
	if(m_pCon_BS_S)
	{
		delete [] m_pCon_BS_S;
		m_pCon_BS_S = NULL;
	}	
	if(m_pCon_BZ_S)
	{
		delete [] m_pCon_BZ_S;
		m_pCon_BZ_S = NULL;
	}
	//////////////////////////////	
}	

int CMI_Cur_I::Post_Curve(CDrObject* pObject)
{

	//////////////////////////
	return 0;
}		

int CMI_Cur_I::LBDownInit_CInsert(UINT nType) 
{	
			
//?	m_bDirtyCurve = FALSE;
//?	m_nOut		  = 0;
    /////////
	return 0;

}

int CMI_Cur_I::LBUpInit_CInsert(enum CURVEPROC kind) 
{
//?	m_CurveType	= kind;
	if(!m_nINodeDone)
	{
//		if(kind == CU_BSPLINE)
			m_nMaxCurveINodes = 2; // for BSpline 
/*
		else	
		if(kind == CU_BEZIER)
			m_nMaxCurveCNodes = 4;
		else	
		if(kind == CU_LINEAR)
			m_nMaxCurveCNodes = 2;
		else	
		if(kind == CU_QUADRATIC)
			m_nMaxCurveCNodes = 3;
*/			
	}		
	/////////
	return 0;
}
	
int CMI_Cur_I::LBUp_CInsert(enum CURVEPROC kind,CView* pView,UINT nView) 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
    CELMouse* pELMouse		= pDoc->GetMouseMgr()->GetELMouse(nView);
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////////////
	if(m_nINodeDone <= 0) 								// Firsttime 
	{
		m_pDrCurve 		= C_GetInfo(kind,1);                  	// CGen Dialog
		if(!m_pDrCurve)		// cancel
			return -1;
//?		m_pINodeList	= m_pDrCurve->GetINodeList();
	}	
	///////////////////////////////////////////////////////////
	if(!pELMouse->ShowNode(pID,FALSE,1))       // Interpolation Nodes
	{
		m_nINodeDone++;
		SetCurrentINodeID(*pID);
	}
	else									// cancelled
		return -1;
	///////////		          
	SaveINode(m_pDrCurve->GetINodeList(),pID);
	int index 				= pObjectMgr->GetObjectIndexfromKey(NODE,*pID,1);
	pDListMgr				= pObjectMgr->GetObjectList(NODE);
	CDrNode* pDrNode 		= (CDrNode*)(pDListMgr->GetObject(index));
	pDrNode->GetCurveList()->InsertObject(m_pDrCurve);
	/////////////////////////////////////
	if(m_nINodeDone < m_nMaxCurveINodes)
		return 0;
	///////////////////////////////////////////////////////////////////// Go Generate	
	m_nINodeDone = 0; 	//reset
	CString* str = new CString;
	char* buf = str->GetBuffer(80);
				
	sprintf(buf,"Got All %d Control Nodes",m_pDrCurve->GetINodeList()->GetCount());
	AfxMessageBox(*str);
	str->ReleaseBuffer();
	delete str;
	////////////////////////////
	InsertAllInfo(m_nOrder_S);
	//////////////////////////////////////////////////////////
	CString CurveID	= m_pDrCurve->GetObjectID();
	pDListMgr 		= pObjectMgr->GetObjectList(CURVE);
	int nCurveIndex = pDListMgr->GetObjectIndex(CURVE,CurveID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nCurveIndex);
	pObjectMgr->SetActiveObjectType(CURVE);
    ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nCurveIndex,CURVE);
	/////////
	return 0;		 
}			

int CMI_Cur_I::InsertAllInfo(int nOrder)
{ 

	// 		ALWAYS	B E Z I E R	CurveType
	///////////////////////////////////// Compute No. of Curves
	int nCurves;
	////////////////////////////////////////////////////////////
	m_pDrCurve->NumberOfCurves(CP_BEZIER,m_nMaxCurveCNodes,&nCurves,m_bClosed_S,nOrder);
	//////////////////////////////////// save in DrCurve
	m_pDrCurve->SetCurveType_S(m_CurveType);
	m_pDrCurve->SetMaxCubicCurves(nCurves);
	m_pDrCurve->SetDirty(TRUE);
	m_pDrCurve->SetShow(TRUE);
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	m_pDrCurve->Calc_3DBoundsLocal();											
	////////////////////////////////////// Post NODES & ...
	if(PostNodes_FWD()<0)
		return -1;
	///////////////
	return 0;
	///////////////
	
}			 

int CMI_Cur_I::RBUp_CInsert(enum CURVEPROC kind,CView* pView,UINT nView) 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////////////
	if(kind == CP_CIRCLE)
	{
		CMC_Circl	MC_Circle;
		m_pDrCurve 	= MC_Circle.GoDoIt();
		if(!m_pDrCurve)
			return -1;
	}
	else
	{
		m_pDrCurve 	= C_GetInfo(kind,2);                  	// CCon Dialog
		m_CurveType	= kind;
		///////////////////////////////////////////////////////////////////// Go Generate	
		if(m_pDrCurve)
		{
			CString* str = new CString;
			char* buf = str->GetBuffer(80);
				
			sprintf(buf,"Got All %d Interpolation Nodes",m_pDrCurve->GetINodeList()->GetCount());
			/////////////////////////	
			AfxMessageBox(*str);
			/////////////////////////
			str->ReleaseBuffer();
			delete str;
		}	
		else
			return -1;	// Cancel
		////////////////////////////////////////////////////////// Go Interpolate
		GenerateCurve();
		//////////////////////////////////////////////////////////
		InsertAllInfo(m_nOrder_S);
	}
	//////////////////////////////////////////////////////////
	CString CurveID	= m_pDrCurve->GetObjectID();
	pDListMgr 		= pObjectMgr->GetObjectList(CURVE);
	int nCurveIndex = pDListMgr->GetObjectIndex(CURVE,CurveID);
	int nOldIndex 	= pObjectMgr->GetActiveObjectIndex();
	pObjectMgr->SetActiveObjectIndex(nCurveIndex);
	pObjectMgr->SetActiveObjectType(CURVE);
    ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nCurveIndex,CURVE);
	/////////
	return 0;		 
}			
	 
int CMI_Cur_I::GenerateCurve() 
{
	m_nOrder_S = m_pDrCurve->GetOrder_S();
	////////////////////////////////////// 
	if(m_CurveType == CP_CIRCLE)
			InterPolate_Circle();
	else
	{
		///////////
		if(m_nOrder_S == 4) 			// Cubic
			InterPolate_C3();
		else
		if(m_nOrder_S == 3) 			// Quadratic
			InterPolate_C2();
		else
		if(m_nOrder_S == 2) 			// Linear
			InterPolate_C1();
	}
	/////////
	return 0;
}				

CDrCurve* CMI_Cur_I::C_GetInfo(enum CURVEPROC kind,int nButton)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////////////////
	CEDlgMgr* 	pEDlgMgr;
	CString		Cid;
	int index;
	///////////////////////////////////////////////////
	if(kind == CP_CIRCLE)
	{
		if(nButton ==1)		//Left Button
			if (pEDlgMgr->DoModal_Cur_I_CIRCLE(&Cid,0) == IDCANCEL)
				return (CDrCurve*)NULL;
		if(nButton ==2)		//Right Button
			if (pEDlgMgr->DoModal_Cur_I_CIRCLE(&Cid,m_nMaxCurveINodes) == IDCANCEL)
				return (CDrCurve*)NULL; 
	}
	else
	{
		if(nButton ==1)		//Left Button
			if (pEDlgMgr->DoModal_Cur_I_LB(&Cid,0) == IDCANCEL)
				return (CDrCurve*)NULL;
		if(nButton ==2)		//Right Button
		{
			int nOrder = 4;	// Cubic default
			/////////////////////////////////////////////////////////
			if(kind == CP_LINEAR)
				nOrder = 2;		// 
			else	
			if(kind == CP_QUADRATIC)
				nOrder = 3;		// 
			/////////////////////////////////////////////////////////
			if (pEDlgMgr->DoModal_Cur_I_RB(&Cid,nOrder) == IDCANCEL)
				return (CDrCurve*)NULL;
		}				 
	}				
	    /////////////////////////////////////////////////////// update
	index 				= pObjectMgr->
							GetObjectIndexfromKey(CURVE,Cid,1);
	if(index<0)
		return (CDrCurve*)NULL;
	else
	{
		pDListMgr 			= pObjectMgr->GetObjectList(CURVE);
		CDrCurve* pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
		m_nMaxCurveINodes	= pDrCurve->GetMaxINodes_S();
		m_nSegsOut			= pDrCurve->GetSegmentCount_S();
		m_bClosed_S			= pDrCurve->IsClosed_S();
		m_CurveType			= kind;
		////////////////		
		return pDrCurve;
	}
}			
			
void CMI_Cur_I::SaveINode(CDListMgr* pList,CString* pID)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	////////////////////////////////////////// save in LIST
	int index 				= pObjectMgr->GetObjectIndexfromKey(NODE,*pID,1);
	pDListMgr 				= pObjectMgr->GetObjectList(NODE);
	CDrNode* pDrNode 		= (CDrNode*)(pDListMgr->GetObject(index));
	//////////////////////////////////
	pList->InsertObject(pDrNode);
	//////////////////////////////////
}	

int CMI_Cur_I::RBDown_CInsert(enum CURVEPROC kind,CView* pView,UINT nView) 
{
	return 0; 
}

int CMI_Cur_I::PostNodes_FWD()
{
/*
	//////////////////////////////////////////////////////
	WORLD		LocalPos;
	CString		Nid,CurveID;
	int			nChLen;
	char		buf[20];
    CDrNode* 	pAddNode;
	int s,t=0,j,index;
	//////////////////////////////////// Name
	CurveID	= m_pDrCurve->GetObjectID();
	nChLen	= CurveID.GetLength();
	if(nChLen>NUM_LEN-2)
		nChLen = NUM_LEN-2;
	//////////////////////////////	
	for (s = 0; s<m_nOut; s++)
	{
		///////////////////////////////////////// CREATE	
		Nid	= CurveID.Left(nChLen);
	    //////////////////////////////////// Name
	    sprintf(buf,"%d%d",s,t);
	    Nid += buf; 
		//////////////////////////////////// Node Index in m_pOut
		index = s;
		LocalPos = *(m_pOut+index);
		////////
		pAddNode = PostNode(Nid,LocalPos,FALSE);
		m_pNodeList->InsertObject(pAddNode);
		//////////////////////////////////////// Reciprocate
		pAddNode->GetCurveList()->InsertObject(m_pDrCurve);
		////////
	} 
*/	
	return 0;

}

int CMI_Cur_I::InterPolate_Circle()
{
	CIn_Circle	In_Circle;			// Curve Interpolate: Circle
	////////////////////////////////////////////// Set Memory for Initial data
	if(C1_SetMemory()<0)
		return -1;
	////////////////////////////////////////////// Get Extended Data
	m_pINodeList = m_pDrCurve->GetENodeList();
	if(SetUpINodes(m_pINodeList,m_pData,m_pDrCurve->GetData_Ex_S())<0)
		return -1;
	////////////////////////////////////////////// Set Interpolation Data
	if(Circle_PrepInterpolation(&In_Circle)<0)
		return -1;
	////////////////////////////////////////////// Interpolate
	if(In_Circle.Interpolate()<0)
		return -1;
	////////////////////////////////////////////// Get Interpolation Result
	if(Circle_PostInterpolation(&In_Circle)<0)
		return -1;
	///////////////////////
	return 0; 
}

int CMI_Cur_I::InterPolate_C1()
{
	CInter_C1	Inter_C1;			// Curve Interpolate: Cubic
	////////////////////////////////////////////// Set Memory
	if(C1_SetMemory()<0)
		return -1;
	////////////////////////////////////////////// Set Data
	m_pINodeList = m_pDrCurve->GetINodeList();
	if(SetUpINodes(m_pINodeList,m_pData,m_pDrCurve->GetData_S())<0)
		return -1;
	////////////////////////////////////////////// Set Interpolation Data
	if(C1_PrepInterpolation(&Inter_C1)<0)
		return -1;
	////////////////////////////////////////////// Interpolate
	if(Inter_C1.Interpolate()<0)
		return -1;
	////////////////////////////////////////////// Get Interpolation Result
	if(C1_PostInterpolation(&Inter_C1)<0)
		return -1;
	///////////////////////
	return 0; 
}

int CMI_Cur_I::InterPolate_C2()
{
	CInter_C2	Inter_C2;			// Curve Interpolate: Cubic
	////////////////////////////////////////////// Set Memory
	if(C2_SetMemory()<0)
		return -1;
	////////////////////////////////////////////// Set Data
	m_pINodeList = m_pDrCurve->GetINodeList();
	if(SetUpINodes(m_pINodeList,m_pData,m_pDrCurve->GetData_S())<0)
		return -1;
	////////////////////////////////////////////// Set Interpolation Data
	if(C2_PrepInterpolation(&Inter_C2)<0)
		return -1;
	////////////////////////////////////////////// Interpolate
	if(Inter_C2.Interpolate()<0)
		return -1;
	////////////////////////////////////////////// Get Interpolation Result
	if(C2_PostInterpolation(&Inter_C2)<0)
		return -1;
	///////////////////////
	return 0; 
}

int CMI_Cur_I::InterPolate_C3()
{
	CInter_C3	Inter_C3;			// Curve Interpolate: Cubic
	////////////////////////////////////////////// Set Memory
	if(C3_SetMemory()<0)
		return -1;
	////////////////////////////////////////////// Set Data
	m_pINodeList = m_pDrCurve->GetINodeList();
	if(SetUpINodes(m_pINodeList,m_pData,m_pDrCurve->GetData_S())<0)
		return -1;
	////////////////////////////////////////////// Set Interpolation Data
	if(C3_PrepInterpolation(&Inter_C3)<0)
		return -1;
	////////////////////////////////////////////// Interpolate
	if(Inter_C3.Interpolate()<0)
		return -1;
	////////////////////////////////////////////// Get Interpolation Result
	if(C3_PostInterpolation(&Inter_C3)<0)
		return -1;
	///////////////////////
	return 0; 
}
	
int CMI_Cur_I::C1_SetMemory()
{
    
    ///////////////////////////////////////////////////////// Memory
	if(m_CurveType == CP_CIRCLE)
		m_pData 	= new WORLD[m_pDrCurve->GetData_Ex_S()];
	else
		m_pData 	= new WORLD[m_pDrCurve->GetData_S()];
	/////////////		
	if(!m_pData)
	{
		AfxMessageBox("ERROR:Interpolate -Memory Failure!");
		m_MemErr = -1;
		return m_MemErr;
	}
	/////////////////////////////////////////////////
    return 0;
    
}

int CMI_Cur_I::C2_SetMemory()
{
    
    ///////////////////////////////////////////////////////// Memory
    m_pKnot_S	= m_pDrCurve->GetpKnots_S();
    if(m_pKnot_S == NULL)
	{
		m_pKnot_S = new double[m_pDrCurve->GetnKnots_S()];
		if(!m_pKnot_S)
		{
			AfxMessageBox("ERROR:Interpolate -Memory Failure!");
			m_MemErr = -1;
			return m_MemErr;
		}
	}
	/////////////////////////////////////////		
	m_pWts_DT_S = m_pDrCurve->GetpWts_DT_S();
    if(m_pWts_DT_S == NULL)
    {
		m_pWts_DT_S = new double[m_pDrCurve->GetnKnots_S()];
		if(!m_pWts_DT_S)
		{
			AfxMessageBox("ERROR:Interpolate -Memory Failure!");
			m_MemErr = -1;
			return m_MemErr;
		}
	}
	//////////////////////////////////////////////////////////////////////// Setup Data
	m_pData 	= new WORLD[m_pDrCurve->GetData_S()];
	if(!m_pData)
	{
		AfxMessageBox("ERROR:Interpolate -Memory Failure!");
		m_MemErr = -1;
		return m_MemErr;
	}
	/////////////////////////////////////////////////
    return 0;
    
}

int CMI_Cur_I::C3_SetMemory()
{
    
    ///////////////////////////////////////////////////////// Memory
    m_pKnot_S	= m_pDrCurve->GetpKnots_S();
    if(m_pKnot_S == NULL)
	{
		m_pKnot_S = new double[m_pDrCurve->GetnKnots_S()];
		if(!m_pKnot_S)
		{
			AfxMessageBox("ERROR:Interpolate -Memory Failure!");
			m_MemErr = -1;
			return m_MemErr;
		}
	}
	/////////////////////////////////////////		
	m_pWts_DT_S = m_pDrCurve->GetpWts_DT_S();
    if(m_pWts_DT_S == NULL)
    {
		m_pWts_DT_S = new double[m_pDrCurve->GetnKnots_S()];
		if(!m_pWts_DT_S)
		{
			AfxMessageBox("ERROR:Interpolate -Memory Failure!");
			m_MemErr = -1;
			return m_MemErr;
		}
	}
	//////////////////////////////////////////////////////////////////////// Setup Data
	m_pData 	= new WORLD[m_pDrCurve->GetData_S()];
	if(!m_pData)
	{
		AfxMessageBox("ERROR:Interpolate -Memory Failure!");
		m_MemErr = -1;
		return m_MemErr;
	}
	/////////////////////////////////////////////////
    return 0;
    
}

int CMI_Cur_I::SetUpINodes(CDListMgr* pList,pWORLD inData,int nData)
{

	int k;
	///////////
    if(nData<=0)
    	return -1;
    ///////////////////////
    k = -1;
    double x,y,z;
    //////////////	
	POSITION pos = pList->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		CDrNode* pNode = (CDrNode*)pList->GetNextObject( pos);
		k++;
		x = (pNode->GetNodeCard())->x;
		y = (pNode->GetNodeCard())->y;
		z = (pNode->GetNodeCard())->z;
		inData[k].x = x;
		inData[k].y = y;
		inData[k].z = z;
	}
	///////////
	if(k != (nData-1))
		return -1;
	else
		return 0;
	/////////////		 
}
int CMI_Cur_I::Circle_PrepInterpolation(CIn_Circle* pIn_Circle)
{
	///////////////////////////////////////////////////////// Get Adjusted Number of Data
	int CSeg_DT	= m_pDrCurve->GetData_Ex_S() - 1;				// L
	if(m_bClosed_S)
		CSeg_DT++;
    /////////////
#ifdef _DEBUG
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	if(1 != 1 ) // iDLL = 12 , Module = 1
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);

		int j;
		//////////
		sprintf(buf,"CMI_Cur_I::Circle_PrepInterpolation");
		AfxMessageBox(*str);
		///////////////////
		j  = sprintf( buf,		"nDat_Ex\t = %d\n",m_pDrCurve->GetData_Ex_S());
		j += sprintf( buf + j, 	"nOrder\t = %d\n",m_pDrCurve->GetOrder_S());
		j += sprintf( buf + j, 	"bClosed\t = %s\n",(m_bClosed_S?"CLOSED":"OPEN") );
		j += sprintf( buf + j, 	"Degr\t = %d\n",m_pDrCurve->GetOrder_S()-1);
		j += sprintf( buf + j, 	"CSeg_DT\t = %d\n",CSeg_DT);
		j += sprintf( buf + j, 	"nConBS\t = %d\n",m_pDrCurve->GetnCon_BS_S());
		j += sprintf( buf + j, 	"nConBZ\t = %d\n",m_pDrCurve->GetnCon_BZ_S());
		j += sprintf( buf + j, 	"Theta\t = %f\n",m_pDrCurve->GetTheta_S());
		if(j>500)
		{
			 sprintf( buf, "Increase buffer to %d",j);
			 AfxMessageBox(*str);
			 str->ReleaseBuffer();
			 delete str;
			 return -1;
		}	 
		AfxMessageBox(*str);
		str->ReleaseBuffer();
		delete str;
    	///////////////////
    }
#endif	
	/////////////////////////////////////////////////////////////////// FillUp 
	pIn_Circle->SetnData_S(m_pDrCurve->GetData_Ex_S());	// Adjusted# of Data for Conics(Circle) 
	pIn_Circle->SetnOrder_S(m_pDrCurve->GetOrder_S());				// k
	pIn_Circle->SetbClosed_S(m_pDrCurve->IsClosed_S());
	//////////////////////////////////////////////////////////
	pIn_Circle->SetnSeg_DT_S(CSeg_DT);						// L
	///////////////
	pIn_Circle->SetnDegree_S(m_pDrCurve->GetOrder_S()-1);				// k -1
	pIn_Circle->SetCenter(m_pDrCurve->GetCenter_S());				// k -1
	pIn_Circle->SetRadius(m_pDrCurve->GetRadius_S());				// k -1
	pIn_Circle->SetNormal(m_pDrCurve->GetNormal_S());				// k -1
	
//	pIn_Circle->SetnSeg_BS_S(nSeg_BS);
	pIn_Circle->SetnCon_BS_S(m_pDrCurve->GetnCon_BS_S());
	pIn_Circle->SetnCon_BZ_S(m_pDrCurve->GetnCon_BZ_S()); // = m_nMaxCurveCNodes
	////////////////////////////////////////////// Send Memory
	pIn_Circle->SetpData(m_pData);
	pIn_Circle->SetpCon_BS_S(m_pCon_BS_S);
	pIn_Circle->SetpCon_BZ_S(m_pCon_BZ_S);
	////////////////////////////////////////////////////
	return 0;
}
	 		
int CMI_Cur_I::Circle_PostInterpolation(CIn_Circle* pIn_Circle)
{

	/////////////////////////////////////////////////////////////////// FillUp 
	////////////////////// Memory for Interpolation
//	m_pDrCurve->SetpMKnots_S(m_pMKnot_S)	//---|	 THESE ACTUALLY NOT NEED, OUR
//	m_pDrCurve->SetpWts_BS_S(m_pWts_BS_S)	//---|-- INTERNAL REPRESENTATION: ALWAYS  B E Z I E R
//	m_pDrCurve->SetpCon_BS_S(m_pCon_BS_S)	//---|   RATIONAL or NONraional
	////////////////////////////////////////////////////////////////////
	// Create CNodes from Bezier Pts. and store in:
	//		MainList and
	//		CNodeList of DrCurve
    ///////////////////////////////////////////////////
	WORLD		LocalPos;
	CString		Nid,CurveID;
	int			nChLen;
	char		buf[20];
    CDrNode* 	pAddNode;
	int s,t =0,j;
	/////////////////////////////////////////////////////////// Data
	////////////////////////////////////////////// Get Memory
	m_pData				= pIn_Circle->GetpData();
	m_pWts_BS_S			= pIn_Circle->GetpWts_BS_S();
	m_pWts_BZ_S			= pIn_Circle->GetpWts_BZ_S();
	m_pCon_BS_S			= pIn_Circle->GetpCon_BS_S();
	m_pCon_BZ_S			= pIn_Circle->GetpCon_BZ_S();
	m_pOut				= m_pCon_BZ_S;
	//////////////////////////////////////////////// 
	CurveID				= m_pDrCurve->GetObjectID();
	m_nMaxCurveCNodes 	= m_pDrCurve->GetnCon_BZ_S();
	m_pCNodeList		= m_pDrCurve->GetCNodeList();
	///////////////////////////////////////////// Name
	nChLen	= CurveID.GetLength();
	if(nChLen>NUM_LEN-2)
		nChLen = NUM_LEN-2;
	//////////////////////////////////////////////////////////// Bezier	
	for (s = 0; s<m_nMaxCurveCNodes; s++)
	{
		///////////////////////////////////////// CREATE	
//		Nid		= CurveID.Left(nChLen);
		Nid		= CurveID;
	    //////////////////////////////////// Name
	    sprintf(buf,"%d%d",s,t);
	    Nid += buf; 
		////////////////////////////////////
		j = t*m_nMaxCurveCNodes + s;
		////////////////////////////		
		LocalPos.x	= (m_pOut+j)->x;
		LocalPos.y	= (m_pOut+j)->y;
		LocalPos.z	= (m_pOut+j)->z;
		///////////////////////////////////// in THE List 
		pAddNode = PostNode(Nid,LocalPos,TRUE);	// Create DrCNode
		if(!pAddNode)	// Create DrCNode
			return -1;
		///////////////////////////////////// in Curve 	
		m_pCNodeList->InsertObject(pAddNode); //CNodeList
		//////////////////////////////////////// Reciprocate DONOT:PRIVATE
//		pAddNode->GetCurveList()->InsertObject(m_pDrCurve);
		////////
	}
	/////////////////////////////////////////////////////////////// B-Splines
	// 		CONTROL NODE CREATION WILL BE DONE SIMILARLY LATER
	/////////////////////////////////////////////////////////////// save memory				
	m_pDrCurve->SetpWts_BZ_S(m_pWts_BZ_S);
	////////////////////////////////////////////
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	if(1 != 1 ) // iDLL = 12 , Module = 1
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		int j,k;
		//////////
		sprintf(buf,"BezierWts\nCMI_Cur_I::Circle_PostInterpolation");
		AfxMessageBox(*str);
		///////////////////
		pDOUBLE Wts = m_pDrCurve->GetpWts_BZ_S();
		//////////////////////////////////////////
		j = sprintf(buf,"BZ_Wts[%d]\n      Wts\n",m_nMaxCurveCNodes);
		for(k=0;k<m_nMaxCurveCNodes;k++)
		{
		   j += sprintf( buf + j, "%2d %7.2f\n", k,	Wts[k] );
		}
		if(j>BUFF_SIZE)
		{
			 sprintf( buf, "Increase buffer to %d",j);
			 AfxMessageBox(*str);
			 delete str;
			 return -1;
		}	 
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif				
	/////////////////////////////////////////////////////////////// Now ReleaseMemory
	if(m_pData)
	{
		delete [] m_pData;
		m_pData = NULL;
	}	
	if(m_pCon_BS_S)
	{
		delete [] m_pCon_BS_S;
		m_pCon_BS_S = NULL;
	}	
	if(m_pWts_BS_S)
	{
		delete [] m_pWts_BS_S;
		m_pWts_BS_S = NULL;
	}	
	if(m_pCon_BZ_S)
	{
		delete [] m_pCon_BZ_S;
		m_pCon_BZ_S = NULL;
		m_pOut 		= NULL;
	}	
	if(m_pOut) 
	{
		delete [] m_pOut;
		m_pOut = NULL;
	}
	/////////////////////////////////////////////////////////////////////	
	return 0;
}

int CMI_Cur_I::C1_PrepInterpolation(CInter_C1* pInter_C1)
{
	////////////
	int CSeg_DT	= m_pDrCurve->GetData_S() - 1;				// L
	if(m_bClosed_S)
		CSeg_DT++;
    /////////////
#ifdef _DEBUG
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	if(1 != 1 ) // iDLL = 12 , Module = 1
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);

		int j;
		//////////
		sprintf(buf,"CMI_Cur_I::C1_PrepInterpolation");
		AfxMessageBox(*str);
		///////////////////
		j  = sprintf( buf,"nData_S\t = %d\n",m_pDrCurve->GetData_S());
		j += sprintf( buf + j, "nOrder\t = %d\n",m_pDrCurve->GetOrder_S());
		j += sprintf( buf + j, "bClosed\t = %s\n",(m_bClosed_S?"CLOSED":"OPEN") );
		j += sprintf( buf + j, "nDim\t = %d\n",m_pDrCurve->GetnDim_S());
		j += sprintf( buf + j, "Degr\t = %d\n",m_pDrCurve->GetOrder_S()-1);
		j += sprintf( buf + j, "CSeg_DT\t = %d\n",CSeg_DT);
		j += sprintf( buf + j, "nConBS\t = %d\n",m_pDrCurve->GetnCon_BS_S());
		j += sprintf( buf + j, "nConBZ\t = %d\n",m_pDrCurve->GetnCon_BZ_S());
		if(j>500)
		{
			 sprintf( buf, "Increase buffer to %d",j);
			 AfxMessageBox(*str);
			 str->ReleaseBuffer();
			 delete str;
			 return -1;
		}	 
		AfxMessageBox(*str);
		str->ReleaseBuffer();
		delete str;
    	///////////////////
    }
#endif	
	/////////////////////////////////////////////////////////////////// FillUp 
	pInter_C1->SetnData_S(m_pDrCurve->GetData_S());		// GIVEN: # of Data
	pInter_C1->SetnOrder_S(m_pDrCurve->GetOrder_S());				// k
	pInter_C1->SetbClosed_S(m_pDrCurve->IsClosed_S());
/*
	pInter_C1->SetCurveType(CTyp);
	int nDim 		= 3;			// NonRational
	if(CTyp == CU_NURB)
		nDim 		= 4;			// Homogeneous(Rational)
*/		
	//////////////////////////////////////////////////////////
	pInter_C1->SetnSeg_DT_S(CSeg_DT);						// L
	///////////////
	pInter_C1->SetnDegree_S(m_pDrCurve->GetOrder_S()-1);				// k -1
	pInter_C1->SetbClosed_S(m_pDrCurve->IsClosed_S()); 
	
//	pInter_C1->SetnSeg_BS_S(nSeg_BS);
	pInter_C1->SetnCon_BS_S(m_pDrCurve->GetnCon_BS_S());
	pInter_C1->SetnCon_BZ_S(m_pDrCurve->GetnCon_BZ_S()); // = m_nMaxCurveCNodes
	////////////////////////////////////////////// Send Memory
	pInter_C1->SetpData(m_pData);
	pInter_C1->SetpCon_BS_S(m_pCon_BS_S);
	pInter_C1->SetpCon_BZ_S(m_pCon_BZ_S);
	////////////////////////////////////////////////////
	return 0;
}
	 		
int CMI_Cur_I::C1_PostInterpolation(CInter_C1* pInter_C1)
{

	/////////////////////////////////////////////////////////////////// FillUp 
	////////////////////// Memory for Interpolation
//	m_pDrCurve->SetpMKnots_S(m_pMKnot_S)	//---|	 THESE ACTUALLY NOT NEED, OUR
//	m_pDrCurve->SetpWts_BS_S(m_pWts_BS_S)	//---|-- INTERNAL REPRESENTATION: ALWAYS  B E Z I E R
//	m_pDrCurve->SetpCon_BS_S(m_pWts_BS_S)	//---|   RATIONAL or NONraional
	////////////////////////////////////////////////////////////////////
	// Create CNodes from Bezier Pts. and store in:
	//		MainList and
	//		CNodeList of DrCurve
    ///////////////////////////////////////////////////
	WORLD		LocalPos;
	CString		Nid,CurveID;
	int			nChLen;
	char		buf[20];
    CDrNode* 	pAddNode;
	int s,t =0,j;
	/////////////////////////////////////////////////////////// Data
	////////////////////////////////////////////// Get Memory
	m_pData 			= pInter_C1->GetpData();
	m_pCon_BS_S 		= pInter_C1->GetpCon_BS_S();
	m_pCon_BZ_S 		= pInter_C1->GetpCon_BZ_S();
	m_pOut				= m_pCon_BZ_S; 
	////////////////////////////////////////////////////
	CurveID				= m_pDrCurve->GetObjectID();
	m_nMaxCurveCNodes 	= m_pDrCurve->GetnCon_BZ_S();
	m_pCNodeList		= m_pDrCurve->GetCNodeList();
	///////////////////////////////////////////// Name
	nChLen	= CurveID.GetLength();
	if(nChLen>NUM_LEN-2)
		nChLen = NUM_LEN-2;
	//////////////////////////////////////////////////////////// Bezier	
	for (s = 0; s<m_nMaxCurveCNodes; s++)
	{
		///////////////////////////////////////// CREATE	
//		Nid		= CurveID.Left(nChLen);
		Nid		= CurveID;
	    //////////////////////////////////// Name
	    sprintf(buf,"%d%d",s,t);
	    Nid += buf; 
		////////////////////////////////////
		j = t*m_nMaxCurveCNodes + s;
		////////////////////////////		
		LocalPos.x	= (m_pOut+j)->x;
		LocalPos.y	= (m_pOut+j)->y;
		LocalPos.z	= (m_pOut+j)->z;
		///////////////////////////////////// in THE List 
		pAddNode = PostNode(Nid,LocalPos,TRUE);	// Create DrCNode
		if(!pAddNode)	// Create DrCNode
			return -1;
		///////////////////////////////////// in Curve 	
		m_pCNodeList->InsertObject(pAddNode); //CNodeList 
		//////////////////////////////////////// Reciprocate DONOT:PRIVATE
//		pAddNode->GetCurveList()->InsertObject(m_pDrCurve);
		////////
	}				
	/////////////////////////////////////////// BEZIER Control Nodes
	WORLD Local;
	int ntemp = m_pCNodeList->GetCount();
	CDListMgr* pList = m_pCNodeList;
	////////////////////////////////
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrNode* pNode 	= (CDrNode*)pList->GetNextObject(pos);
		/////////////////////////////////////////// ObjectInfo
		Local = *(pNode->GetLocalPos());
		//////////////////////////////////
	} 
	/////////////////////////////////////////////////////////////// B-Splines
	// 		CONTROL NODE CREATION WILL BE DONE SIMILARLY LATER
	/////////////////////////////////////////////////////////////// save memory
	if(m_pDrCurve->GetnDim_S() == 3)		// Non-Rational
	{				
		m_pWts_BZ_S = new double[m_nMaxCurveCNodes]; // needed later for TensorProduct Patch
		for(s=0;s<m_nMaxCurveCNodes;s++)
			m_pWts_BZ_S[s] = 1.0;
		//////////////////////////////////////		
		m_pDrCurve->SetpWts_BZ_S(m_pWts_BZ_S); 
	}	
	/////////////////////////////////////////////////////////////// Now ReleaseMemory
	if(m_pData)
	{
		delete [] m_pData;
		m_pData = NULL;
	}	
	if(m_pCon_BS_S)
	{
		delete [] m_pCon_BS_S;
		m_pCon_BS_S = NULL;
	}	
	if(m_pCon_BZ_S)
	{
		delete [] m_pCon_BZ_S;
		m_pCon_BZ_S = NULL;
		m_pOut 		= NULL;
	}	
	if(m_pOut) 
	{
		delete [] m_pOut;
		m_pOut = NULL;
	}	
	////////////////////////////////////////////////////
	return 0;
}

int CMI_Cur_I::C2_PrepInterpolation(CInter_C2* pInter_C2)
{
	////////////
	int CSeg_DT	= m_pDrCurve->GetData_S() - 1;				// L
	if(m_bClosed_S)
		CSeg_DT++;
    /////////////
#ifdef _DEBUG
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	if(1 != 1 ) // iDLL = 12 , Module = 1
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);

		int j;
		//////////
		sprintf(buf,"CMI_Cur_I::C2_PrepInterpolation");
		AfxMessageBox(*str);
		///////////////////
		j  = sprintf( buf,"nData_S\t = %d\n",m_pDrCurve->GetData_S());
		j += sprintf( buf + j, "nOrder\t = %d\n",m_pDrCurve->GetOrder_S());
		j += sprintf( buf + j, "bClosed\t = %s\n",(m_bClosed_S?"CLOSED":"OPEN") );
		j += sprintf( buf + j, "nDim\t = %d\n",m_pDrCurve->GetnDim_S());
		j += sprintf( buf + j, "Degr\t = %d\n",m_pDrCurve->GetOrder_S()-1);
		j += sprintf( buf + j, "CSeg_DT\t = %d\n",CSeg_DT);
		j += sprintf( buf + j, "nConBS\t = %d\n",m_pDrCurve->GetnCon_BS_S());
		j += sprintf( buf + j, "nKnots\t = %d\n",m_pDrCurve->GetnKnots_S());
		j += sprintf( buf + j, "nMKnots\t = %d\n",m_pDrCurve->GetnMKnots_S());
		j += sprintf( buf + j, "nConBZ\t = %d\n",m_pDrCurve->GetnCon_BZ_S());
		if(j>500)
		{
			 sprintf( buf, "Increase buffer to %d",j);
			 AfxMessageBox(*str);
			 str->ReleaseBuffer();
			 delete str;
			 return -1;
		}	 
		AfxMessageBox(*str);
		str->ReleaseBuffer();
		delete str;
    	///////////////////
    }
	///////////////////////////////////	
	BOUNDARY BCL= m_pDrCurve->GetBCL_S();
	BOUNDARY BCR= m_pDrCurve->GetBCR_S();
	VECTOR TanL,TanR;
	if(BCL == BC_TANGENT)
		TanL 	= m_pDrCurve->GetTanL_S();
	if(BCL == BC_TANGENT)
		TanR 	= m_pDrCurve->GetTanR_S();
	//////////////////////////////////////////////////////////
	pDOUBLE pWtsDT,pKnot;
	KNOT KnTyp  = m_pDrCurve->GetKnotType_S();
	WEIGHT WtTyp= m_pDrCurve->GetWtType_S();
	if(WtTyp == WT_USER)
		pWtsDT 	= m_pDrCurve->GetpWts_DT_S();	//  
	if(KnTyp == KN_USER)
		pKnot 	= m_pDrCurve->GetpKnots_S();	//  
	//////////////////////////////////////////////////////////
#endif	
	/////////////////////////////////////////////////////////////////// FillUp 
	pInter_C2->SetnData_S(m_pDrCurve->GetData_S());		// GIVEN: # of Data
	pInter_C2->SetnOrder_S(m_pDrCurve->GetOrder_S());				// k
	pInter_C2->SetbClosed_S(m_pDrCurve->IsClosed_S());
/*
	pInter_C2->SetCurveType(CTyp);
	int nDim 		= 3;			// NonRational
	if(CTyp == CU_NURB)
		nDim 		= 4;			// Homogeneous(Rational)
*/		
	pInter_C2->SetKnotType_S(m_pDrCurve->GetKnotType_S());
	pInter_C2->SetWtType_S(m_pDrCurve->GetWtType_S());
	pInter_C2->SetBCL(m_pDrCurve->GetBCL_S());
	pInter_C2->SetBCR(m_pDrCurve->GetBCR_S());
	pInter_C2->SetTanL(m_pDrCurve->GetTanL_S());
	pInter_C2->SetTanR(m_pDrCurve->GetTanR_S());
	//////////////////////////////////////////////////////////
	pInter_C2->SetpWts_DT_S(m_pDrCurve->GetpWts_DT_S());	//  
	pInter_C2->SetpKnot_S(m_pDrCurve->GetpKnots_S());	//
	//////////////////////////////////////////////////////////
	pInter_C2->SetnSeg_DT_S(CSeg_DT);						// L
	///////////////
	pInter_C2->SetnDim_S(m_pDrCurve->GetnDim_S());
	pInter_C2->SetnDegree_S(m_pDrCurve->GetOrder_S()-1);				// k -1
	pInter_C2->SetbClosed_S(m_pDrCurve->IsClosed_S()); 
	
//	pInter_C2->SetnSeg_BS_S(nSeg_BS);
	pInter_C2->SetnCon_BS_S(m_pDrCurve->GetnCon_BS_S());
	pInter_C2->SetnKnots_S(m_pDrCurve->GetnKnots_S());
	pInter_C2->SetnMKnots_S(m_pDrCurve->GetnMKnots_S()); 
	pInter_C2->SetnCon_BZ_S(m_pDrCurve->GetnCon_BZ_S()); // = m_nMaxCurveCNodes
	////////////////////////////////////////////// Send Memory
	pInter_C2->SetpData(m_pData);
	pInter_C2->SetpMKnot_S(m_pMKnot_S);
	pInter_C2->SetpKnot_S(m_pKnot_S);
	pInter_C2->SetpWts_DT_S(m_pWts_DT_S);
	pInter_C2->SetpWts_BS_S(m_pWts_BS_S);
	pInter_C2->SetpWts_BZ_S(m_pWts_BZ_S);
	pInter_C2->SetpCon_BS_S(m_pCon_BS_S);
	pInter_C2->SetpCon_BZ_S(m_pCon_BZ_S);
	////////////////////////////////////////////////////
	return 0;
}
	 		
int CMI_Cur_I::C2_PostInterpolation(CInter_C2* pInter_C2)
{

	/////////////////////////////////////////////////////////////////// FillUp 
	////////////////////// Memory for Interpolation
//	m_pDrCurve->SetpMKnots_S(m_pMKnot_S)	//---|	 THESE ACTUALLY NOT NEED, OUR
//	m_pDrCurve->SetpWts_BS_S(m_pWts_BS_S)	//---|-- INTERNAL REPRESENTATION: ALWAYS  B E Z I E R
//	m_pDrCurve->SetpCon_BS_S(m_pWts_BS_S)	//---|   RATIONAL or NONraional
	////////////////////////////////////////////////////////////////////
	// Create CNodes from Bezier Pts. and store in:
	//		MainList and
	//		CNodeList of DrCurve
    ///////////////////////////////////////////////////
	WORLD		LocalPos;
	CString		Nid,CurveID;
	int			nChLen;
	char		buf[20];
    CDrNode* 	pAddNode;
	int s,t =0,j;
	/////////////////////////////////////////////////////////// Data
	////////////////////////////////////////////// Get Memory
	m_pData				= pInter_C2->GetpData();
	m_pMKnot_S			= pInter_C2->GetpMKnot_S();
	m_pKnot_S			= pInter_C2->GetpKnot_S();
	m_pWts_DT_S			= pInter_C2->GetpWts_DT_S();
	m_pWts_BS_S			= pInter_C2->GetpWts_BS_S();
	m_pWts_BZ_S			= pInter_C2->GetpWts_BZ_S();
	m_pCon_BS_S			= pInter_C2->GetpCon_BS_S();
	m_pCon_BZ_S			= pInter_C2->GetpCon_BZ_S();
	m_pOut				= m_pCon_BZ_S;
	//////////////////////////////////////////////// 
	CurveID				= m_pDrCurve->GetObjectID();
	m_nMaxCurveCNodes 	= m_pDrCurve->GetnCon_BZ_S();
	m_pCNodeList		= m_pDrCurve->GetCNodeList();
	///////////////////////////////////////////// Name
	nChLen	= CurveID.GetLength();
	if(nChLen>NUM_LEN-2)
		nChLen = NUM_LEN-2;
	//////////////////////////////////////////////////////////// Bezier	
	for (s = 0; s<m_nMaxCurveCNodes; s++)
	{
		///////////////////////////////////////// CREATE	
		Nid		= CurveID;
	    //////////////////////////////////// Name
	    sprintf(buf,"%d%d",s,t);
	    Nid += buf; 
		////////////////////////////////////
		j = t*m_nMaxCurveCNodes + s;
		////////////////////////////		
		LocalPos.x	= (m_pOut+j)->x;
		LocalPos.y	= (m_pOut+j)->y;
		LocalPos.z	= (m_pOut+j)->z;
		///////////////////////////////////// in THE List 
		pAddNode = PostNode(Nid,LocalPos,TRUE);	// Create DrCNode
		if(!pAddNode)	// Create DrCNode
			return -1;
		///////////////////////////////////// in Curve 	
		m_pCNodeList->InsertObject(pAddNode); //CNodeList 
		//////////////////////////////////////// Reciprocate DONOT:PRIVATE
//		pAddNode->GetCurveList()->InsertObject(m_pDrCurve);
		////////
	}
#ifdef _DEBUG					
	/////////////////////////////////////////// BEZIER Control Nodes
	WORLD Local;
	int ntemp = m_pCNodeList->GetCount();
	CDListMgr* pList = m_pCNodeList;
	////////////////////////////////
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrNode* pNode 	= (CDrNode*)pList->GetNextObject(pos);
		/////////////////////////////////////////// ObjectInfo
		Local = *(pNode->GetLocalPos());
		//////////////////////////////////
	}
#endif	 
	/////////////////////////////////////////////////////////////// B-Splines
	// 		CONTROL NODE CREATION WILL BE DONE SIMILARLY LATER
	/////////////////////////////////////////////////////////////// save memory				
	m_pDrCurve->SetpKnots_S(m_pKnot_S);
	m_pDrCurve->SetpWts_DT_S(m_pWts_DT_S);
	//////////////////////////////////////
	if(m_pDrCurve->GetnDim_S() == 3)		// Non-Rational
	{				
// 		already assigned
//		m_pWts_BZ_S = new double[m_nMaxCurveCNodes]; // needed later for TensorProduct Patch
		for(s=0;s<m_nMaxCurveCNodes;s++)
			m_pWts_BZ_S[s] = 1.0;
		//////////////////////////////////////		
		m_pDrCurve->SetpWts_BZ_S(m_pWts_BZ_S); 
	}	
	/////////////////////////////////////////////////////////////// Now ReleaseMemory
	if(m_pData)
	{
		delete [] m_pData;
		m_pData = NULL;
	}	
	if(m_pMKnot_S)
	{
		delete [] m_pMKnot_S;
		m_pMKnot_S = NULL;
	}	
	if(m_pCon_BS_S)
	{
		delete [] m_pCon_BS_S;
		m_pCon_BS_S = NULL;
	}	
	if(m_pWts_BS_S)
	{
		delete [] m_pWts_BS_S;
		m_pWts_BS_S = NULL;
	}	
	if(m_pCon_BZ_S)
	{
		delete [] m_pCon_BZ_S;
		m_pCon_BZ_S = NULL;
		m_pOut 		= NULL;
	}	
	if(m_pOut) 
	{
		delete [] m_pOut;
		m_pOut = NULL;
	}
	/////////////////////////////////////////////////////////////////////	
	return 0;
}

int CMI_Cur_I::C3_PrepInterpolation(CInter_C3* pInter_C3)
{
	////////////
	int CSeg_DT	= m_pDrCurve->GetData_S() - 1;				// L
	if(m_bClosed_S)
		CSeg_DT++;
    /////////////
#ifdef _DEBUG
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	if(1 != 1) // iDLL = 12 , Module = 1
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);

		int j;
		//////////
		sprintf(buf,"CMI_Cur_I::C3_PrepInterpolation");
		AfxMessageBox(*str);
		///////////////////
		j  = sprintf( buf,"nData_S\t = %d\n",m_pDrCurve->GetData_S());
		j += sprintf( buf + j, "nOrder\t = %d\n",m_pDrCurve->GetOrder_S());
		j += sprintf( buf + j, "bClosed\t = %s\n",(m_bClosed_S?"CLOSED":"OPEN") );
		j += sprintf( buf + j, "nDim\t = %d\n",m_pDrCurve->GetnDim_S());
		j += sprintf( buf + j, "Degr\t = %d\n",m_pDrCurve->GetOrder_S()-1);
		j += sprintf( buf + j, "CSeg_DT\t = %d\n",CSeg_DT);
		j += sprintf( buf + j, "nConBS\t = %d\n",m_pDrCurve->GetnCon_BS_S());
		j += sprintf( buf + j, "nKnots\t = %d\n",m_pDrCurve->GetnKnots_S());
		j += sprintf( buf + j, "nMKnots\t = %d\n",m_pDrCurve->GetnMKnots_S());
		j += sprintf( buf + j, "nConBZ\t = %d\n",m_pDrCurve->GetnCon_BZ_S());
		if(j>500)
		{
			 sprintf( buf, "Increase buffer to %d",j);
			 AfxMessageBox(*str);
			 str->ReleaseBuffer();
			 delete str;
			 return -1;
		}	 
		AfxMessageBox(*str);
		str->ReleaseBuffer();
		delete str;
    	///////////////////
    }
	///////////////////////////////////	
	BOUNDARY BCL= m_pDrCurve->GetBCL_S();
	BOUNDARY BCR= m_pDrCurve->GetBCR_S();
	VECTOR TanL,TanR;
	if(BCL == BC_TANGENT)
		TanL 	= m_pDrCurve->GetTanL_S();
	if(BCL == BC_TANGENT)
		TanR 	= m_pDrCurve->GetTanR_S();
	//////////////////////////////////////////////////////////
	pDOUBLE pWtsDT,pKnot;
	KNOT KnTyp  = m_pDrCurve->GetKnotType_S();
	WEIGHT WtTyp= m_pDrCurve->GetWtType_S();
	if(WtTyp == WT_USER)
		pWtsDT 	= m_pDrCurve->GetpWts_DT_S();	//  
	if(KnTyp == KN_USER)
		pKnot 	= m_pDrCurve->GetpKnots_S();	//  
	//////////////////////////////////////////////////////////
#endif	
	/////////////////////////////////////////////////////////////////// FillUp 
	pInter_C3->SetnData_S(m_pDrCurve->GetData_S());		// GIVEN: # of Data
	pInter_C3->SetnOrder_S(m_pDrCurve->GetOrder_S());				// k
	pInter_C3->SetbClosed_S(m_pDrCurve->IsClosed_S());
/*
	pInter_C3->SetCurveType(CTyp);
	int nDim 		= 3;			// NonRational
	if(CTyp == CU_NURB)
		nDim 		= 4;			// Homogeneous(Rational)
*/		
	pInter_C3->SetKnotType_S(m_pDrCurve->GetKnotType_S());
	pInter_C3->SetWtType_S(m_pDrCurve->GetWtType_S());
	pInter_C3->SetBCL(m_pDrCurve->GetBCL_S());
	pInter_C3->SetBCR(m_pDrCurve->GetBCR_S());
	pInter_C3->SetTanL(m_pDrCurve->GetTanL_S());
	pInter_C3->SetTanR(m_pDrCurve->GetTanR_S());
	//////////////////////////////////////////////////////////
	pInter_C3->SetpWts_DT_S(m_pDrCurve->GetpWts_DT_S());	//  
	pInter_C3->SetpKnot_S(m_pDrCurve->GetpKnots_S());	//
	//////////////////////////////////////////////////////////
	pInter_C3->SetnSeg_DT_S(CSeg_DT);						// L
	///////////////
	pInter_C3->SetnDim_S(m_pDrCurve->GetnDim_S());
	pInter_C3->SetnDegree_S(m_pDrCurve->GetOrder_S()-1);				// k -1
	pInter_C3->SetbClosed_S(m_pDrCurve->IsClosed_S()); 
	
//	pInter_C3->SetnSeg_BS_S(nSeg_BS);
	pInter_C3->SetnCon_BS_S(m_pDrCurve->GetnCon_BS_S());
	pInter_C3->SetnKnots_S(m_pDrCurve->GetnKnots_S());
	pInter_C3->SetnMKnots_S(m_pDrCurve->GetnMKnots_S()); 
	pInter_C3->SetnCon_BZ_S(m_pDrCurve->GetnCon_BZ_S()); // = m_nMaxCurveCNodes
	////////////////////////////////////////////// Send Memory
	pInter_C3->SetpData(m_pData);
	pInter_C3->SetpMKnot_S(m_pMKnot_S);
	pInter_C3->SetpKnot_S(m_pKnot_S);
	pInter_C3->SetpWts_DT_S(m_pWts_DT_S);
	pInter_C3->SetpWts_BS_S(m_pWts_BS_S);
	pInter_C3->SetpWts_BZ_S(m_pWts_BZ_S);
	pInter_C3->SetpCon_BS_S(m_pCon_BS_S);
	pInter_C3->SetpCon_BZ_S(m_pCon_BZ_S);
	////////////////////////////////////////////////////
	return 0;
}
	 		
int CMI_Cur_I::C3_PostInterpolation(CInter_C3* pInter_C3)
{

	/////////////////////////////////////////////////////////////////// FillUp 
	////////////////////// Memory for Interpolation
//	m_pDrCurve->SetpMKnots_S(m_pMKnot_S)	//---|	 THESE ACTUALLY NOT NEED, OUR
//	m_pDrCurve->SetpWts_BS_S(m_pWts_BS_S)	//---|-- INTERNAL REPRESENTATION: ALWAYS  B E Z I E R
//	m_pDrCurve->SetpCon_BS_S(m_pWts_BS_S)	//---|   RATIONAL or NONraional
	////////////////////////////////////////////////////////////////////
	// Create CNodes from Bezier Pts. and store in:
	//		MainList and
	//		CNodeList of DrCurve
    ///////////////////////////////////////////////////
	WORLD		LocalPos;
	CString		Nid,CurveID;
	int			nChLen;
	char		buf[20];
    CDrNode* 	pAddNode;
	int s,t =0,j;
	/////////////////////////////////////////////////////////// Data
	////////////////////////////////////////////// Get Memory
	m_pData				= pInter_C3->GetpData();
	m_pMKnot_S			= pInter_C3->GetpMKnot_S();
	m_pKnot_S			= pInter_C3->GetpKnot_S();
	m_pWts_DT_S			= pInter_C3->GetpWts_DT_S();
	m_pWts_BS_S			= pInter_C3->GetpWts_BS_S();
	m_pWts_BZ_S			= pInter_C3->GetpWts_BZ_S();
	m_pCon_BS_S			= pInter_C3->GetpCon_BS_S();
	m_pCon_BZ_S			= pInter_C3->GetpCon_BZ_S();
	m_pOut				= m_pCon_BZ_S;
	//////////////////////////////////////////////// 
	CurveID				= m_pDrCurve->GetObjectID();
	m_nMaxCurveCNodes 	= m_pDrCurve->GetnCon_BZ_S();
	m_pCNodeList		= m_pDrCurve->GetCNodeList();
	///////////////////////////////////////////// Name
	nChLen	= CurveID.GetLength();
	if(nChLen>NUM_LEN-2)
		nChLen = NUM_LEN-2;
	//////////////////////////////////////////////////////////// Bezier	
	for (s = 0; s<m_nMaxCurveCNodes; s++)
	{
		///////////////////////////////////////// CREATE	
		Nid		= CurveID;
	    //////////////////////////////////// Name
	    sprintf(buf,"%d%d",s,t);
	    Nid += buf; 
		////////////////////////////////////
		j = t*m_nMaxCurveCNodes + s;
		////////////////////////////		
		LocalPos.x	= (m_pOut+j)->x;
		LocalPos.y	= (m_pOut+j)->y;
		LocalPos.z	= (m_pOut+j)->z;
		///////////////////////////////////// in THE List 
		pAddNode = PostNode(Nid,LocalPos,TRUE);	// Create DrCNode
		if(!pAddNode)	// Create DrCNode
			return -1;
		///////////////////////////////////// in Curve 	
		m_pCNodeList->InsertObject(pAddNode); //CNodeList 
		//////////////////////////////////////// Reciprocate DONOT:PRIVATE
//		pAddNode->GetCurveList()->InsertObject(m_pDrCurve);
		////////
	}
#ifdef _DEBUG					
	/////////////////////////////////////////// BEZIER Control Nodes
	WORLD Local;
	int ntemp = m_pCNodeList->GetCount();
	CDListMgr* pList = m_pCNodeList;
	////////////////////////////////
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrNode* pNode 	= (CDrNode*)pList->GetNextObject(pos);
		/////////////////////////////////////////// ObjectInfo
		Local = *(pNode->GetLocalPos());
		//////////////////////////////////
	} 
#endif	
	/////////////////////////////////////////////////////////////// B-Splines
	// 		CONTROL NODE CREATION WILL BE DONE SIMILARLY LATER
	/////////////////////////////////////////////////////////////// save Memory
	m_pDrCurve->SetpKnots_S(m_pKnot_S);
	m_pDrCurve->SetpWts_DT_S(m_pWts_DT_S);
	//////////////////////////////////////
	if(m_pDrCurve->GetnDim_S() == 3)		// Non-Rational
	{				
// 		already assigned
//		m_pWts_BZ_S = new double[m_nMaxCurveCNodes]; // needed later for TensorProduct Patch
		for(s=0;s<m_nMaxCurveCNodes;s++)
			m_pWts_BZ_S[s] = 1.0;
		//////////////////////////////////////		
		m_pDrCurve->SetpWts_BZ_S(m_pWts_BZ_S); 
	}	
	/////////////////////////////////////////////////////////////// Now ReleaseMemory
	if(m_pData)
	{
		delete [] m_pData;
		m_pData = NULL;
	}	
	if(m_pMKnot_S)
	{
		delete [] m_pMKnot_S;
		m_pMKnot_S = NULL;
	}	
	if(m_pCon_BS_S)
	{
		delete [] m_pCon_BS_S;
		m_pCon_BS_S = NULL;
	}	
	if(m_pWts_BS_S)
	{
		delete [] m_pWts_BS_S;
		m_pWts_BS_S = NULL;
	}	
	if(m_pCon_BZ_S)
	{
		delete [] m_pCon_BZ_S;
		m_pCon_BZ_S = NULL;
		m_pOut 		= NULL;
	}	
	if(m_pOut) 
	{
		delete [] m_pOut;
		m_pOut = NULL;
	}
	/////////////////////////////////////////////////////////////////////	
	return 0;
}

CDrNode* CMI_Cur_I::PostNode(CString& Nid,WORLD Pt,BOOL bCNode)
{

	CEDlgMgr 	EDlgMgr;
	CEDlgMgr* 	pEDlgMgr = &EDlgMgr;
	CDrNode*	pNode;
	/////////////////////////////////////////////
	pNode = pEDlgMgr->CreateNode(Nid,Pt,bCNode);
	//////////////////////////////////////////////
	return pNode;
}

CDrCurve* CMI_Cur_I::PostCurve(CString& Cid,CString& OldID,CURVEPROC CProc)
{

	CEDlgMgr 	EDlgMgr;
	CEDlgMgr* 	pEDlgMgr = &EDlgMgr;
	CDrCurve*	pCurve;
	/////////////////////////////////////////////
	pCurve = pEDlgMgr->CreateCurve(Cid, OldID, CProc);
	//////////////////////////////////////////////
	return pCurve;
}

CDrPatch* CMI_Cur_I::PostPatch(CString& Cid,CString& OldID,PATCHPROC PProc)
{

	CEDl2Mgr 	EDlgMgr;
	CEDl2Mgr* 	pEDlgMgr = &EDlgMgr;
	CDrPatch*	pPatch;
	/////////////////////////////////////////////
	pPatch = pEDlgMgr->CreatePatch(Cid, OldID, PProc);
	//////////////////////////////////////////////
	return pPatch;
}
			
void CMI_Cur_I::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" ELMouse:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" ELMouse:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////		

