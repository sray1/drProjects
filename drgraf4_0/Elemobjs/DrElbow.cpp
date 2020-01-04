// Elbow.cpp : implementation file
//


#include "stdafx.h"
#include "limits.h"

#include "3DMath.h"
#include "XForm.h"
////////////////////// elObjs
#include "Ext_Elem.h"
#include "Def_Elem.h"
#include "DrFE0D.h"
//////////////
#include "DrElbow.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////////
#define GREEN	RGB(0,255,0)
#define RED		RGB(255,0,0)
/////////////////////////////////////////////////////////////////////////////
// CDrElbow
IMPLEMENT_SERIAL(CDrElbow, CDrFE1D,1)
/*
BEGIN_MESSAGE_MAP(CDrElbow, CDrFE1D)
	//{{AFX_MSG_MAP(CDrElbow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CDrElbow::CDrElbow()
{  
    	
	m_ElTypeID		= "ELBOW";
	m_ElTypeNum		= ELBOW;
    //////////////////////////////	
    SetObjectType((int)ELBOW);
    SetElemType((int)EL1D_OBJECT);          //
	////////////////////////////
	m_nNodes			= 2;
	m_nEdgeDegree		= 1; // Linear
	///
	m_SIid[0]			= "";
	m_SIid[1]			= "";
    //////////////////////////////
	m_CCID				= "";
	m_TIID				= "";
	m_CAID				= "";
	m_CBID				= "";
	 
} 

CDrElbow::~CDrElbow()
{
	/////////////////////////// empty all the lists
	ReadyToDelete();
	///////////////////////////
}	

void CDrElbow::ReadyToDelete()
{
	////////////////////////////////////// unload Nodes/No delete
	CDListMgr* pNodeList = GetFE0DList();
    //////////////////////////////////////
	CDrObject* pObject,pElem;
	while(!pNodeList->IsEmpty())
	{
		pObject = (CDrObject*)pNodeList->RemoveHead();  //Node
		/////////////////////////////////////////////
		if(pObject)
		{
			CDListMgr* pElemList = pObject->GetElemList();
			int index = pElemList->GetObjectIndex(this);
			if(index>=0)
				pElemList->RemoveObject(index); //elem
		/////////////////////////
		}
	//////////
	}
	/////////////////////////////////////////////////////////////
	while(!(GetCurveList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetCurveList()->RemoveHead());
		pObject->ReadyToDelete();
	}	
	while(!(GetPatchList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetPatchList()->RemoveHead());
		pObject->ReadyToDelete();
	}	
	while(!(GetSolidList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetSolidList()->RemoveHead());
		pObject->ReadyToDelete();
	}
	//////////////////////////////////////////////////////////////
}

int CDrElbow::DealObjectDialog()
{
/*
	CElbowProp	dlg;
	if(dlg.DoModal() == IDOK)
		return 0;
	else
		return -1;
*/
	return 0;			
}
	
void CDrElbow::SetObjectInfo(CDrObject* pObject)
{
	
	CDrFE1D::SetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CDrElbow* pAdd = (CDrElbow*) pObject;
	///////////////////////////////////////////////////// ELBOWINFO
	m_SIid[0]			= pAdd->m_SIid[0];
	m_SIid[1]			= pAdd->m_SIid[1];
	////////////////////
	m_CCID				= pAdd->m_CCID;
	m_TIID				= pAdd->m_TIID;
	m_CAID				= pAdd->m_CAID;
	m_CBID				= pAdd->m_CBID;
	////////////////////
	return;
}		

void CDrElbow::GetObjectInfo(CDrObject* pObject)
{
	
	CDrFE1D::GetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CDrElbow* pAdd = (CDrElbow*) pObject;
	///////////////////////////////////////////////////// ELBOWINFO
	pAdd->m_SIid[0]			= m_SIid[0];
	pAdd->m_SIid[1]			= m_SIid[1];
	////////////////////
	pAdd->m_CCID			= m_CCID;
	pAdd->m_TIID			= m_TIID;
	pAdd->m_CAID			= m_CAID;
	pAdd->m_CBID			= m_CBID;
	////////////////////
	return;
}		

void CDrElbow::DoFormattedCardView(CString* pstrCard,CString& strFmt)
{
	m_bFormatted = TRUE;	// DrObject Element
//	Pack_drPipe(pstrCard);
} 

void CDrElbow::DoUnFormattedCardView(CString* pstrCard)
{
	m_bFormatted = FALSE;	// DrObject Element
	Pack_drPipe(pstrCard);
	///////////////////////////////
} 

void CDrElbow::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDrElbow::Pack_drPipe(CString* pstrCard)
{
	static CString name;
	POSITION	pos;
	int			i; 
	CString blank = "";
   	/////////////////////////
   	for (i = 0;i<nMax_ElemTypes;i++)
   		if(ElTypes[i].num == ELBOW) 
   		{
   			name = ElTypes[i].ObjName;
   			break;
   		}	
	/////////////////////////
	CString pad = " "; 
	//////////////////////////////////////////////////// Name
	AddStr(pstrCard,&name,10);
	//////////////////////////////////////////////////// ElementNum
	AddStr(pstrCard,&m_ElNumID,5);
	//////////////////////////////////////////////////// LineID
	AddStr(pstrCard,&m_line_id,5);
	//////////////////////////////////////////////////// Nodes:I & J
	for (i = 0;i<MAX_CORNERS_1D;i++)
	{
		pos = m_FE0DList.FindIndex(i);
		CDrFE0D* pNode = (CDrFE0D*)m_FE0DList.GetAt(pos);
		AddStr(pstrCard,&((pNode->GetNodeCard())->id),5);
	}
	//////////////////////////////////////////////////// Node:CC
	AddStr(pstrCard,&m_CCID,5);
	//////////////////////////////////////////////////// Node:TI
	AddStr(pstrCard,&m_TIID,5);
	//////////////////////////////////////////////////// Node:CA
	AddStr(pstrCard,&m_CAID,5);
	//////////////////////////////////////////////////// Node:CB
	AddStr(pstrCard,&m_CBID,5);
	//////////////////////////////////////////////////// Property
	AddStr(pstrCard,&m_pid,5);
	//////////////////////////////////////////////////// Material
	AddStr(pstrCard,&m_mid,5);
	//////////////////////////////////////////////////// SI
	for (i = 0;i<MAX_CORNERS_1D;i++)
		AddStr(pstrCard,&(m_SIid[i]),5);
	//////////////////////////////////////////////////// UNUSED
	AddStr(pstrCard,&blank,5);
	//////////////////////////////////////////////////// ReleaseID
	for (i = 0;i<MAX_CORNERS_1D;i++)
		AddStr(pstrCard,&(m_rid[i]),5);
	///////
	return;
}   
//////////////////////////////////////////////////////////
void CDrElbow::TransformObjectToWorld(pMATRIX pLM,BOOL bYes)
{
	////////////////////////
	TransformToWorldPos(pLM,bYes);
	//////////////////
}
	
void CDrElbow::TransformObjectToView(pMATRIX pViewM)
{

	//////////////////////
	TransformToEyePos(pViewM);
	//////////////////////
}	

BOOL CDrElbow::RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType)
{
		return FALSE;	// do nothing
}			 
				
void CDrElbow::ProjectObject
				(pMATRIX pvv3DM,double dScale_U,double dScale_V)
{

	//////////////////////
	ProjectToScreenPos(pvv3DM,dScale_U,dScale_V);
	///////////////////////
	// CNodes are same as Nodes
	////////////////////////////			
	Calc_ScreenRectFromCNodes();
	////////////////////////////

}

void CDrElbow::TransformToWorldPos(pMATRIX pLM,BOOL bYes)
{

	pMATRIX		pLMP;	
	CDListMgr* pList;
	POSITION pos;
	///////////////////////// 
	if(bYes)
		pLMP 	= pLM;
	//////////////////////////////////////////// Transform
	// Bounding Corners are the Nodes
	/////////////////////////////////////// Generated Nodes
	pList = GetFE0DList();
	//////////////////////
	if(!pList->IsEmpty())
	{
		////////
		for (pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrFE0D* pNode = (CDrFE0D*)pList->GetNextObject(pos);
			//////////////////////////////////
			pNode->Calc_WorldPos(pLMP,bYes);
			//////////////////////////////////
		}
	}	
	///////////////////	
}

void CDrElbow::TransformToEyePos(pMATRIX pViewM)
{

	CDListMgr* pList;
	POSITION pos;
	//////////////////////////////////////////// View Transform
	/////////////////////////////////////// Generated Nodes
	pList = GetFE0DList();
	//////////////////////
	if(!pList->IsEmpty())
	{
		////////
		for (pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrFE0D* pNode = (CDrFE0D*)pList->GetNextObject(pos);
			//////////////////////////////////
			pNode->Calc_EyePos(pViewM);
			//////////////////////////////////
		}
	}
	///////////////////	
}

void CDrElbow::ProjectToScreenPos
				(pMATRIX pvv3DM,double dScale_U,double dScale_V)
{

	CDListMgr* 	pList;
	POSITION 	pos;
	//////////////////////////////////////////// Project
	/////////////////////////////////////// Generated Nodes
	pList = GetFE0DList();
	//////////////////////
	if(!pList->IsEmpty())
	{
		////////
		for (pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrFE0D* pNode = (CDrFE0D*)pList->GetNextObject(pos);
			//////////////////////////////////
			pNode->ProjectToScreenPos3D(pvv3DM);
			//////////////////////////////////
			//	Bounding Corners ARE the Nodes
			// 	So no need to do again
			///////////////////////////////////////
			WORLD ScreenPos = *(pNode->GetScreenPos3D());
			///////////////////////////////////////
			POINT pt;
			//////////////////////////////////////////////////////
			// 	3DScreenPos belongs to [0,-1] because of CVV	//
			//	So before we Change into Integer Logical		//
			//	Coordinates, we Must Use Screen Client Data		//
			//////////////////////////////////////////////////////
			pt.x = (int)(ScreenPos.x * dScale_U);
			pt.y = (int)(ScreenPos.y * dScale_V);
			//////////////////////
			pNode->SetScreenPos2D(pt);
			//////////////////////
		}
	}
	////////////////////////////
}

void CDrElbow::Calc_ScreenRectFromCNodes()
{
	/////////////////////
	FinishObject();
	///////////////
}
	
void CDrElbow::FinishObject()
{ 
	CDListMgr* 	pList;
	POSITION 	pos;
	//////////////////////////////////////////////////////
	// Calculate the bounding rectangle.  It's needed for smart
	// repainting.
	
	m_rectBounding = CRect(INT_MAX,INT_MIN,INT_MIN,INT_MAX);//L,T,R,B
	/////////////////////////////////////// Generated Nodes
	pList = GetFE0DList();
	//////////////////////
	if(!pList->IsEmpty())
	{
		////////
		for (pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrFE0D* pNode = (CDrFE0D*)pList->GetNextObject(pos);
			//////////////////////////////////
			POINT pt = *(pNode->GetScreenPos2D());
			// If the point lies outside of the accumulated bounding
			// rectangle, then inflate the bounding rect to include it.
			m_rectBounding.left     = min(m_rectBounding.left, pt.x);
			m_rectBounding.top      = max(m_rectBounding.top, pt.y);
			m_rectBounding.right    = max(m_rectBounding.right, pt.x);
			m_rectBounding.bottom   = min(m_rectBounding.bottom, pt.y);
		}
	}	
    //////////////////////////////////////////////////////////////////
	// Add the pen width to the bounding rectangle.  This is necessary
	// to account for the width of the Plat when invalidating
	// the screen.
	m_rectBounding.InflateRect(CSize(m_nPenWidth, -(int)m_nPenWidth));
	///////
	return; 
	
} 
//////////////////////////////////////////////////////////////
void CDrElbow::InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
					 	pMATRIX pViewM,pMATRIX pvv3DM,
						double dzMin,double dScale_U,double dScale_V)
{ 
	m_bParallel		= bParallel;
    m_nView			= nView;
    m_dzMin			= dzMin;
	m_dScale_U		= dScale_U;		// vv3DToLP:U-direction  
	m_dScale_V		= dScale_V;		// vv3DToLP:V-direction
	m_ViewM			= *pViewM;		// viewers transform MATRIX
	m_vv3DM			= *pvv3DM;		// Window to 3D Viewport MATRIX 
	///////////////////////////////////////////////////////////////// PreProcess
	////////////////////////////////////////////// Coordinates XForm
												// Local->World	  
	MATRIX LM;
	BOOL bXForm = FALSE;
	TransformObjectToWorld(&LM,bXForm);
	///////////////////////////////////////////
	TransformObjectToView(&m_ViewM); 
	ProjectObject(&m_vv3DM,m_dScale_U,m_dScale_V);///	calc Bounding Rect 
	///////////////////////////////////
//	FinishObject();//	calc Bounding Rect  
	/////////////
}
						
//////////////////////////////////////////////////////////////
void CDrElbow::DoDrawView(CDC* PtrDC,BOOL bPenChange)
{

    ///////////////////////////////////////////// Draw 
	GoDoIt(PtrDC,bPenChange);
   	//////////////////////////////////////////
    
}                            

void CDrElbow::GoDoIt(CDC* PtrDC,BOOL bPenChange)
{ 

	CDListMgr* 	pList;
	POSITION 	pos;
    ////////////////
   	CPen    Pen;
   	CPen*   PtrOldPen;
   	                        
	/////////////////////////////////////////////////// 
//	IF bLayerON = FALSE make PEN: DASHED or something     TO BE Done Later
    /////////////////////////////////////////////////// Pen
   	Pen.CreatePen (m_nPenStyle,m_nPenWidth,m_crPenColor); 
   	PtrOldPen = PtrDC->SelectObject(&Pen);
	/////////////////////////////////////// Generated Nodes
	pList = GetFE0DList();
	//////////////////////
	int i;
	pWORLD pMemEye;
	//////////////////////////////////////////////////////
	if(!pList->IsEmpty())
	{
		/////////////////////////////////////// Memory
		int nMaxCorner = pList->GetCount();
		pMemEye = new WORLD[nMaxCorner];
		if(!pMemEye)
		return;
		/////////////////////////////////////// GetNodes
		pWORLD pPtEye; 	
		for (pos = pList->GetFirstObjectPos(),i = 0;pos !=NULL;i++)
		{
			CDrFE0D* pNode = (CDrFE0D*)pList->GetNextObject(pos);
			//////////////////////////////////
			pPtEye = pMemEye+i;
			*pPtEye = *(pNode->GetEyePos());
			/////////////////////////////
		}
    	//////////////////////////////////// Line
		DrawLine3D(PtrDC,pMemEye,pMemEye+1,TRUE);// TRUE = XFormed; FALSE = WORLD 
//		PtrDC->MoveTo(*pPtMem);
//		PtrDC->LineTo(*(pPtMem+1));
		//////////////
		delete [] pMemEye;
	}	
	//////////////////////////////////////////////////////   	
   	PtrDC->SelectObject(PtrOldPen);   
   	Pen.DeleteObject(); 
   	
}   

//////////////////////////////////////////////////////////////////
BOOL CDrElbow::IsKeyMatch(CString KeyID,UINT KeyNo)
{
	return FALSE;
}

void CDrElbow::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////     
	
	if (ar.IsStoring())
	{
		TRACE( " Elbow   :Storing\n");	// TODO: add loading code here
	    /////////////////////////////        

 	}
	else
	{
	
		TRACE( " Elbow   :Loading\n");	// TODO: add loading code here
	    /////////////////////////////        


	}        

}
	
BOOL CDrElbow::IsObjectHit(int nNet, POINT point)
{
	///////////////
	return FALSE;
}

////////////////////// END OF MODULE ///////////////////////

