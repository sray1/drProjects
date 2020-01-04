// Pipe.cpp : implementation file
//


#include "stdafx.h"
#include <Float.h>		// MSVC/INC for DBL_MAX,DBL_MIN
#include "limits.h"

#include "3DMath.h"
#include "XForm.h"
////////////////////// elObjs
#include "Ext_Elem.h"
#include "Def_Elem.h"
#include "DrFE0D.h"
//#include "DrFE2D.h"
//#include "DrFE3D.h"
//////////////
#include "DrFE1D.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////////
#define GREEN	RGB(0,255,0)
#define RED		RGB(255,0,0)
/////////////////////////////////////////////////////////////////////////////
// CDrFE1D
IMPLEMENT_SERIAL(CDrFE1D, CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CDrFE1D, CDrObject)
	//{{AFX_MSG_MAP(CDrFE1D)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CDrFE1D::CDrFE1D()
{  
    	
    //////////////////////////////	
    SetObjectType((int)FE1D);
    SetElemType((int)ELEM_OBJECT);          //
    ////////////////////////////// 
	m_nNodes		= 2;
	m_ElNumID		= "";
	m_ElTypeID		= "";
	m_ElTypeNum		= UNONE;
	m_line_id		= "";
	m_rid[0]		= "";
	m_rid[1]		= "";
	m_pid			= "";
	m_mid			= "";
	m_numseg		= 1 ;
	m_refTemp		= 0.0;
	//////////////////////////////////
    m_rectBounding.SetRectEmpty();
    //////////////////////////////
	m_pIn			= NULL;		// Control Nodes -WorldCoords
	m_pInWts		= NULL;	// Output  Weights -World or Eye Pos for Rational
	m_pInDP			= NULL;    // Control Nodes -ScreenCoords
	m_pOut			= NULL;		// Output  Nodes -World or Eye Pos
	m_pOutWts		= NULL;	// Output  Weights -World or Eye Pos for Rational
	m_pOutDP		= NULL;   // Output  Nodes -ScreenCoords
	///////////////////////	 
} 

CDrFE1D::~CDrFE1D()
{
	/////////////////////////// empty all the lists
	ReadyToDelete();
	///////////////////////////
}	

void CDrFE1D::ReadyToDelete()
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
			CDListMgr* pElemList = pObject->GetFE1DList();
			int index = pElemList->GetObjectIndex(this);
			if(index>=0)
				pElemList->RemoveObject(index); //elem
		/////////////////////////
		}
	//////////
	}
	/////////////////////////////////////////////////////////////
	while(!(GetFE2DList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetFE2DList()->RemoveHead());
		pObject->ReadyToDelete();
	}	
	while(!(GetFE3DList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetFE3DList()->RemoveHead());
		pObject->ReadyToDelete();
	}	
	//////////////////////////////////////////////////////////////
}

int CDrFE1D::DealObjectDialog()
{
/*
	CPipeProp	dlg;
	if(dlg.DoModal() == IDOK)
		return 0;
	else
		return -1;
*/
	return 0;			
}
	
void CDrFE1D::SetObjectInfo(CDrObject* pObject)
{
	
	CDrObject::SetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CDrFE1D* pAdd = (CDrFE1D*) pObject;
	////////////////////////////////////////////////////////
	m_nNodes		= pAdd->m_nNodes;
	m_ElNumID		= pAdd->m_ElNumID;
	m_ElTypeID		= pAdd->m_ElTypeID;
	m_line_id		= pAdd->m_line_id;
	///
	for(int i=0;i<MAX_CORNERS_1D;i++)
	{
		m_rid[i]		= pAdd->m_rid[i];
		m_rel[i]		= pAdd->m_rel[i];
	}
	///
	m_pid			= pAdd->m_pid;
	m_mid			= pAdd->m_mid;
	m_numseg		= pAdd->m_numseg;
	m_refTemp		= pAdd->m_refTemp;				//RefrenceTemperature
	//////////////////////////////////
	m_ElNum			= pAdd->m_ElNum;              // Element Number
	m_ElTypeNum		= pAdd->m_ElTypeNum;        // id Number: Element Type
	m_line_no		= pAdd->m_line_no;
	m_rel[0]		= pAdd->m_rel[0]; 
	m_rel[1]		= pAdd->m_rel[1]; 
	m_prop			= pAdd->m_prop;           //
	m_mat			= pAdd->m_mat;           //
	//////////////////////////////////
	m_nCenter		= pAdd->m_nCenter; 
	////////////////////////////// 
	if(!(pAdd->GetFE0DList()->IsEmpty()))
		m_FE0DList.AddTail(pAdd->GetFE0DList() ); 
	if(!(pAdd->GetFE2DList()->IsEmpty()))
		m_FE2DList.AddTail(pAdd->GetFE2DList() ); 
	if(!(pAdd->GetFE3DList()->IsEmpty()))
		m_FE3DList.AddTail(pAdd->GetFE3DList() ); 
	//
	if(!(pAdd->GetMs0List()->IsEmpty()))
		m_Ms0List.AddTail(pAdd->GetMs0List() ); 
	if(!(pAdd->GetMs1List()->IsEmpty()))
		m_Ms1List.AddTail(pAdd->GetMs1List() ); 
	if(!(pAdd->GetMs2List()->IsEmpty()))
		m_Ms2List.AddTail(pAdd->GetMs2List() ); 
	if(!(pAdd->GetMs3List()->IsEmpty()))
		m_Ms3List.AddTail(pAdd->GetMs3List() ); 
	if(!(pAdd->GetMbj3DList()->IsEmpty()))
		m_Mbj3DList.AddTail(pAdd->GetMbj3DList() ); 
	////////
//082898    m_GenObjType		= pAdd->m_GenObjType;
//082898    m_pGenObj			= pAdd->m_pGenObj;
	////////
	return;
}		

void CDrFE1D::GetObjectInfo(CDrObject* pObject)
{
	
	CDrObject::GetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CDrFE1D* pAdd = (CDrFE1D*) pObject;
	///////////////////////////////////////////////////// FE1DINFO
	pAdd->m_nNodes		= m_nNodes;
	pAdd->m_ElNumID		= m_ElNumID;
	pAdd->m_ElTypeID	= m_ElTypeID;
	pAdd->m_line_id		= m_line_id;
	pAdd->m_rid[0]		= m_rid[0];
	pAdd->m_rid[1]		= m_rid[1];
	pAdd->m_pid			= m_pid;
	pAdd->m_mid			= m_mid;
	pAdd->m_numseg		= m_numseg;
	pAdd->m_refTemp		= m_refTemp;				//RefrenceTemperature
	//////////////////////////////////
	pAdd->m_ElNum		= m_ElNum;              // Element Number
	pAdd->m_ElTypeNum	= m_ElTypeNum;        // id Number: Element Type
	pAdd->m_line_no		= m_line_no;
	pAdd->m_rel[0]		= m_rel[0]; 
	pAdd->m_rel[1]		= m_rel[1]; 
	pAdd->m_prop		= m_prop;           //
	pAdd->m_mat			= m_mat;           //
	//////////////////////////////////
	pAdd->m_nCardNo				= m_nCardNo;
	pAdd->m_nCenter				= m_nCenter; 
	////////////////////////////// 
	if(!(GetFE0DList()->IsEmpty()))
		pAdd->m_FE0DList.AddTail(GetFE0DList() ); 
	if(!(GetFE2DList()->IsEmpty()))
		pAdd->m_FE2DList.AddTail(GetFE2DList() ); 
	if(!(GetFE3DList()->IsEmpty()))
		pAdd->m_FE3DList.AddTail(GetFE3DList() ); 
	///
	if(!(GetMs0List()->IsEmpty()))
		pAdd->m_Ms0List.AddTail(GetMs0List() ); 
	if(!(GetMs1List()->IsEmpty()))
		pAdd->m_Ms1List.AddTail(GetMs1List() ); 
	if(!(GetMs2List()->IsEmpty()))
		pAdd->m_Ms2List.AddTail(GetMs2List() ); 
	if(!(GetMs3List()->IsEmpty()))
		pAdd->m_Ms3List.AddTail(GetMs3List() ); 
	if(!(GetMbj3DList()->IsEmpty()))
		pAdd->m_Mbj3DList.AddTail(GetMbj3DList() ); 
	/////////////////////// Genetics
//082898    pAdd->m_GenObjType		= m_GenObjType;
//082898    pAdd->m_pGenObj			= m_pGenObj;
	////////
	return;
}		

void CDrFE1D::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDrFE1D::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_ElemTypes;i++)
   		if(ElTypes[i].num == FE1D) 
   		{
   			name = ElTypes[i].ObjName;
   			break;
   		}	
   /////////////////////////
   CString pad = " "; 
   ////////////////////////
	return;

}   
//////////////////////////////////////////////////////////
void CDrFE1D::TransformObjectToWorld(pMATRIX pLM,BOOL bYes)
{
	////////////////////////
	TransformToWorldPos(pLM,bYes);
	//////////////////
}
	
void CDrFE1D::TransformObjectToView(pMATRIX pViewM)
{

	//////////////////////
	TransformToEyePos(pViewM);
	//////////////////////
}	

BOOL CDrFE1D::RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType)
{
		return FALSE;	// do nothing
}			 
				
void CDrFE1D::ProjectObject
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

void CDrFE1D::TransformToWorldPos(pMATRIX pLM,BOOL bYes)
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

void CDrFE1D::TransformToEyePos(pMATRIX pViewM)
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

void CDrFE1D::ProjectToScreenPos
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

void CDrFE1D::Calc_ScreenRectFromCNodes()
{
	/////////////////////
	FinishObject();
	///////////////
}
	
void CDrFE1D::FinishObject()
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
void CDrFE1D::InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
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
void CDrFE1D::DoDrawView(CDC* PtrDC,BOOL bPenChange)
{

    ///////////////////////////////////////////// Draw 
	GoDoIt(PtrDC,bPenChange);
   	//////////////////////////////////////////
    
}                            

void CDrFE1D::GoDoIt(CDC* PtrDC,BOOL bPenChange)
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
  
int CDrFE1D::Calc_3DBoundsLocal()
{
	//////////////////////
	CDListMgr*	pNodeList;
	//////////////////////	
	WORLD	dMin,dMax,Coords;
	dMin.x = DBL_MAX; 
	dMin.y = DBL_MAX; 
	dMin.z = DBL_MAX;
	 
	dMax.x = -DBL_MIN; 
	dMax.y = -DBL_MIN; 
	dMax.z = -DBL_MIN;
	///////////////////////////////////////////////////////////////////
	pNodeList = GetFE0DList();     // 
	///////////////////////////
	for (POSITION pos = pNodeList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrNode* pNode 	= (CDrNode*)pNodeList->GetNextObject(pos);
		///////////////////////
		Coords.x = pNode->GetLocalPos()->x; 				
		Coords.y = pNode->GetLocalPos()->y; 				
		Coords.z = pNode->GetLocalPos()->z; 				
		///////////////////////////////////// compare and adjust
		if(Coords.x<dMin.x) dMin.x = Coords.x; 				
		if(Coords.y<dMin.y) dMin.y = Coords.y; 				
		if(Coords.z<dMin.z) dMin.z = Coords.z;
		 				
		if(Coords.x>dMax.x) dMax.x = Coords.x; 				
		if(Coords.y>dMax.y) dMax.y = Coords.y; 				
		if(Coords.z>dMax.z) dMax.z = Coords.z;
		//////////////////////////////////// 				
	}
	////////////////////////
	SetLocalCorner(&dMin,0);
	SetLocalCorner(&dMax,1);
	////////////////////////
	return	0;
}

//////////////////////////////////////////////////////////////////
BOOL CDrFE1D::IsKeyMatch(CString KeyID,UINT KeyNo)
{
	return FALSE;
}
	
BOOL CDrFE1D::IsObjectHit(int nNet,POINT point)
{
	CDListMgr* pList;
	/////////////////////////////////////// Generated Nodes
	pList		= GetFE0DList();
	int nOut	= pList->GetCount();
	///
	if(nOut<=0)
		return FALSE;
	/////////////////////////////////////////// Memory
	if(m_pOutDP)
	{
		FreeMemDP(m_pOutDP);
		m_pOutDP= NULL;
	}		
	m_pOutDP 	= FixMemDP(nOut);		// Output Points
	//////////////////////
	int j = -1;
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrFE0D* pNode = (CDrFE0D*)pList->GetNextObject(pos);
		j++;
		//////////////////////////////////
		POINT pt = *(pNode->GetScreenPos2D());
		//////////////////////////////////////////////////////
		m_pOutDP[j].x = pt.x;
		m_pOutDP[j].y = pt.y;
		/////////////////////////
	}		
	///////////////////////////////////////////////////////////////// Check
	POINT*	pScrenOutPts	= GetMemOutDP();
	///////////////////////////////////////////
	POINT ptOld,ptNew;
	ptOld = *pScrenOutPts;
	//////////////////////
	for(int i=1;i<nOut;i++)
	{
		ptNew = *(pScrenOutPts+i);
		///////////////////////////////////// Find Normal to the Line
		C3DMath Math3D;
		double hl,vl,hn,vn,dLen;
		int netH,netV;
		//////////////////////////////////// line
		hl		= (double)(ptNew.x-ptOld.x);
		vl		= (double)(ptNew.y-ptOld.y);
		dLen	= sqrt(hl*hl + vl*vl);
		hl		/= dLen;
		vl		/= dLen;
		//////////////////////////////////// normal
		hn		= - vl;
		vn		= hl;
		///////////////
		netH	= (int)(hn*nNet);
		netV	= (int)(vn*nNet);
		///////////////////////////////////// Form PolygonalRgn: LP
		CRgn Quad;
		POINT	ptCorners[4];
		/////////////////////
		ptCorners[0].x = ptOld.x + netH;
		ptCorners[0].y = ptOld.y + netV;
		ptCorners[1].x = ptOld.x - netH;
		ptCorners[1].y = ptOld.y - netV;
		/////////
		ptCorners[2].x = ptNew.x - netH;
		ptCorners[2].y = ptNew.y - netV;
		ptCorners[3].x = ptNew.x + netH;
		ptCorners[3].y = ptNew.y + netV;
		////////////////////////////////
		BOOL bOk = Quad.CreatePolygonRgn( ptCorners, 4, ALTERNATE );
   		////////////////////////////////////////////// Check
		if(bOk)
		{
			if(Quad.PtInRegion(point))
			{
				Quad.DeleteObject();
				////////////////////
 				if(m_pOutDP)
				{
					FreeMemDP(m_pOutDP);
					m_pOutDP= NULL;
				}
				////////////////////
      			return TRUE;
			}
		}
		else
		{
			AfxMessageBox(
				"Internal Problem:\nCDrFE1D::IsObjectHit\nCreatePolygonRgn");
			Quad.DeleteObject();
			////////////////////
 			if(m_pOutDP)
			{
				FreeMemDP(m_pOutDP);
				m_pOutDP= NULL;
			}
			////////////////////
			return FALSE;
		}
		/////////////////////////////// Reset
		ptOld = ptNew;
		Quad.DeleteObject();
		//////////////
	}
	////////////////////
	if(m_pOutDP)
	{
		FreeMemDP(m_pOutDP);
		m_pOutDP= NULL;
	}
	////////////////////
	return FALSE;
}

void CDrFE1D::Serialize(CArchive& ar)
{
}

////////////////////// END OF MODULE ///////////////////////

