// Truss.cpp : implementation file
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
#include "DrTruss.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////////
#define GREEN	RGB(0,255,0)
#define RED		RGB(255,0,0)
/////////////////////////////////////////////////////////////////////////////
// CDrTruss
IMPLEMENT_SERIAL(CDrTruss, CDrFE1D,1)
/*
BEGIN_MESSAGE_MAP(CDrTruss, CDrFE1D)
	//{{AFX_MSG_MAP(CDrTruss)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CDrTruss::CDrTruss()
{  
    	
	m_ElTypeID		= "TRUSS";
	m_ElTypeNum		= TRUSS;
    //////////////////////////////	
    SetObjectType((int)TRUSS);
    SetElemType((int)EL1D_OBJECT);          //
	////////////////////////////
	m_nNodes			= 2;
	m_nEdgeDegree		= 1; // Linear
    //////////////////////////////
	 
} 

CDrTruss::~CDrTruss()
{
	/////////////////////////// empty all the lists
	ReadyToDelete();
	///////////////////////////
}	

void CDrTruss::ReadyToDelete()
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

int CDrTruss::DealObjectDialog()
{
/*
	CTrussProp	dlg;
	if(dlg.DoModal() == IDOK)
		return 0;
	else
		return -1;
*/
	return 0;			
}
	
void CDrTruss::SetObjectInfo(CDrObject* pObject)
{
	
	CDrFE1D::SetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CDrTruss* pAdd = (CDrTruss*) pObject;
	///////////////////////////////////////////////////// TRUSSINFO
	////////////////////
	return;
}		

void CDrTruss::GetObjectInfo(CDrObject* pObject)
{
	
	CDrFE1D::GetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CDrTruss* pAdd = (CDrTruss*) pObject;
	///////////////////////////////////////////////////// TRUSSINFO
	////////////////////
	return;
}		

void CDrTruss::DoFormattedCardView(CString* pstrCard,CString& strFmt)
{
	m_bFormatted = TRUE;	// DrObject Element
//	Pack_drPipe(pstrCard);
} 

void CDrTruss::DoUnFormattedCardView(CString* pstrCard)
{
	m_bFormatted = FALSE;	// DrObject Element
	Pack_drPipe(pstrCard);
	///////////////////////////////
} 

void CDrTruss::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDrTruss::Pack_drPipe(CString* pstrCard)
{
	static CString name;
	POSITION	pos;
	int			i; 
	CString blank = "";
   	/////////////////////////
   	for (i = 0;i<nMax_ElemTypes;i++)
   		if(ElTypes[i].num == TRUSS) 
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
	//////////////////////////////////////////////////// ReleaseID
	for (i = 0;i<MAX_CORNERS_1D;i++)
		AddStr(pstrCard,&(m_rid[i]),5);
	//////////////////////////////////////////////////// UNUSED
	AddStr(pstrCard,&blank,5);
	//////////////////////////////////////////////////// Property
	AddStr(pstrCard,&m_pid,5);
	//////////////////////////////////////////////////// Material
	AddStr(pstrCard,&m_mid,5);
	//////////////////////////////////////////////////// UNUSED*3
	for (i = 0;i<3;i++)
		AddStr(pstrCard,&blank,5);
	//////////////////////////////////////////////////// NSeg
	AddInt(pstrCard,m_numseg);
	///////
	return;
}   
//////////////////////////////////////////////////////////
void CDrTruss::TransformObjectToWorld(pMATRIX pLM,BOOL bYes)
{
	////////////////////////
	TransformToWorldPos(pLM,bYes);
	//////////////////
}
	
void CDrTruss::TransformObjectToView(pMATRIX pViewM)
{

	//////////////////////
	TransformToEyePos(pViewM);
	//////////////////////
}	

BOOL CDrTruss::RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType)
{
		return FALSE;	// do nothing
}			 
				
void CDrTruss::ProjectObject
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

void CDrTruss::TransformToWorldPos(pMATRIX pLM,BOOL bYes)
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

void CDrTruss::TransformToEyePos(pMATRIX pViewM)
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

void CDrTruss::ProjectToScreenPos
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

void CDrTruss::Calc_ScreenRectFromCNodes()
{
	/////////////////////
	FinishObject();
	///////////////
}
	
void CDrTruss::FinishObject()
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
void CDrTruss::InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
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
void CDrTruss::DoDrawView(CDC* PtrDC,BOOL bPenChange)
{

    ///////////////////////////////////////////// Draw 
	GoDoIt(PtrDC,bPenChange);
   	//////////////////////////////////////////
    
}                            

void CDrTruss::GoDoIt(CDC* PtrDC,BOOL bPenChange)
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
BOOL CDrTruss::IsKeyMatch(CString KeyID,UINT KeyNo)
{
	return FALSE;
}

void CDrTruss::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////     
	
	if (ar.IsStoring())
	{
		TRACE( " Truss   :Storing\n");	// TODO: add loading code here
	    /////////////////////////////        

 	}
	else
	{
	
		TRACE( " Truss   :Loading\n");	// TODO: add loading code here
	    /////////////////////////////        


	}        

}
	
BOOL CDrTruss::IsObjectHit(int nNet, POINT point)
{
	if(CDrFE1D::IsObjectHit(nNet,point))
		return TRUE;
	else
		return FALSE;
}

////////////////////// END OF MODULE ///////////////////////

