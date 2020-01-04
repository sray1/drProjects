// Pipe.cpp : implementation file
//


#include "stdafx.h"
#include "limits.h"

#include "3DMath.h"
#include "XForm.h"
////////////////////// elObjs
#include "Ext_Elem.h"
#include "Def_Elem.h"
#include "DrFE2D.h"
//#include "DrFE3D.h"
//////////////
#include "DrFE0D.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////
#define COMBO_NIDJ_LOC 	9     // Location of NidJ in element ComboBox
////////////////////////////
#define GREEN	RGB(0,255,0)
#define RED		RGB(255,0,0)
/////////////////////////////////////////////////////////////////////////////
// CDrFE0D
IMPLEMENT_SERIAL(CDrFE0D, CDrNode,1)
/*
BEGIN_MESSAGE_MAP(CDrFE0D, CDrNode)
	//{{AFX_MSG_MAP(CDrFE0D)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CDrFE0D::CDrFE0D()
{  
    	
    //////////////////////////////
	m_bMeshNode		= FALSE;
	//////////////////////////////	
    SetObjectType((int)FE0D);
    SetElemType((int)MESH_OBJECT);          //
    ////////////////////////////// 
	m_ElNumID		= "";
	m_ElTypeID		= "";
	m_ElTypeNum		= UNONE;
	m_refTemp		= 0.0;
	//////////////////////////////////
    m_rectBounding.SetRectEmpty();
    //////////////////////////////
	 
} 

CDrFE0D::~CDrFE0D()
{
	/////////////////////////// empty all the lists
	ReadyToDelete();
	///////////////////////////
}	

void CDrFE0D::ReadyToDelete()
{
	CDrObject* pObject;
	/////////////////////////////////////////////////////////////
	while(!(GetFE0DList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetFE0DList()->RemoveHead());
		pObject->ReadyToDelete();
	}	
	while(!(GetFE1DList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetFE1DList()->RemoveHead());
		pObject->ReadyToDelete();
	}	
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

int CDrFE0D::DealObjectDialog()
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
	
void CDrFE0D::SetObjectInfo(CDrObject* pObject)
{
	
	CDrNode::SetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CDrFE0D* pAdd = (CDrFE0D*) pObject;
	///////////////////////////////////////////////////// FE1DINFO
	m_ElNumID			= pAdd->m_ElNumID;
	m_ElTypeID			= pAdd->m_ElTypeID;
	///
	m_refTemp			= pAdd->m_refTemp;				//RefrenceTemperature
	//////////////////////////////////
	m_ElNum				= pAdd->m_ElNum;              // Element Number
	m_ElTypeNum			= pAdd->m_ElTypeNum;        // id Number: Element Type
	////////////////////
    m_NormalWorld		= pAdd->m_NormalWorld;
    m_NormalEye			= pAdd->m_NormalEye;
    m_NormalScreen3D	= pAdd->m_NormalScreen3D;
    m_NormalScreen2D	= pAdd->m_NormalScreen2D;
	////////////////////////////// 
	m_bMeshNode			= pAdd->m_bMeshNode;
	///
	if(!(pAdd->GetFE1DList()->IsEmpty()))
		m_FE1DList.AddTail(pAdd->GetFE1DList() ); 
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
 //082898   m_pGenObj			= pAdd->m_pGenObj;
	////////
	return;
}		

void CDrFE0D::GetObjectInfo(CDrObject* pObject)
{
	
	CDrNode::GetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CDrFE0D* pAdd = (CDrFE0D*) pObject;
	///////////////////////////////////////////////////// FE1DINFO
	pAdd->m_ElNumID			= m_ElNumID;
	pAdd->m_ElTypeID		= m_ElTypeID;
	pAdd->m_refTemp			= m_refTemp;				//RefrenceTemperature
	//////////////////////////////////
	pAdd->m_ElNum			= m_ElNum;              // Element Number
	pAdd->m_ElTypeNum		= m_ElTypeNum;        // id Number: Element Type
	////////////////////
    pAdd->m_NormalWorld		= m_NormalWorld;
    pAdd->m_NormalEye		= m_NormalEye;
    pAdd->m_NormalScreen3D	= m_NormalScreen3D;
    pAdd->m_NormalScreen2D	= m_NormalScreen2D;
	////////////////////////////// 
	pAdd->m_bMeshNode		= m_bMeshNode;
	///
	if(!(GetFE1DList()->IsEmpty()))
		pAdd->m_FE1DList.AddTail(GetFE1DList() ); 
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

void CDrFE0D::DoFormattedCardView(CString* pstrCard,CString& strFmt)
{
	m_bFormatted = TRUE;	// DrObject Element
//	Pack_drPipe(pstrCard);
} 

void CDrFE0D::DoUnFormattedCardView(CString* pstrCard)
{
	m_bFormatted = FALSE;	// DrObject Element
	CDrNode::Pack_drPipe(pstrCard);
	///////////////////////////////
} 

void CDrFE0D::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDrFE0D::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
	/////////////////////////
	CDrNode::Pack_drPipe(pstrCard);	// MNode
	///////////////////////////////////// Not Mesh Node
	if(!IsMeshNode())
	{
		//      1234567890
		name = "VERTEX    ";
		int len = pstrCard->GetLength();
		int nrt = len - 10;
		CString str = name;
		str += pstrCard->Right(nrt);
		*pstrCard = str;
	}
	///////
	return;

}   
//////////////////////////////////////////////////////////
void CDrFE0D::TransformObjectToWorld(pMATRIX pLM,BOOL bYes)
{
	////////////////////////
	TransformToWorldPos(pLM,bYes);
	//////////////////
}
	
void CDrFE0D::TransformObjectToView(pMATRIX pViewM)
{

	//////////////////////
	TransformToEyePos(pViewM);
	//////////////////////
}	

BOOL CDrFE0D::RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType)
{
		return FALSE;	// do nothing
}			 
				
void CDrFE0D::ProjectObject
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

//////////////////////////////////////////////////////////////
void CDrFE0D::InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
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
void CDrFE0D::DoDrawView(CDC* PtrDC,BOOL bPenChange)
{
	if(IsClipped())
		return;
    ///////////////////////////////////////////// Draw 
	GoDoIt(PtrDC,&m_pt,bPenChange);
   	//////////////////////////////////////////
    
}                            

void CDrFE0D::Calc_NormalWorld()
{
	//////////////////////////////////////////////
	//			Normal is NOT NORMALIZED		//
	//		DO it after the Call, if needed		//
	//////////////////////////////////////////////                                                  
                                                  
	CDListMgr* 	pList;
	POSITION 	pos;
	WORLD 		N,sum = {0.0,0.0,0.0};
//	int			nCount = 0; 	
	///////////////////
	pList = GetFE2DList();
	///////////////////////////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		//////////////////////////
		CDrFE2D* pPoly = (CDrFE2D*)pObject;
//		nCount++;
		N = *(pPoly->GetNormalWorld());
		sum.x += N.x;
		sum.y += N.y;
		sum.z += N.z;
		////////
	}
	SetNormalWorld(sum);
	//////////////////////

}

void CDrFE0D::Calc_NormalEye()
{
	//////////////////////////////////////////////
	//			Normal is NOT NORMALIZED		//
	//		DO it after the Call, if needed		//
	//////////////////////////////////////////////                                                  
                                                  
	CDListMgr* 	pList;
	POSITION 	pos;
	WORLD 		N,sum = {0.0,0.0,0.0};
//	int			nCount = 0; 	
	///////////////////
	pList = GetFE2DList();
	///////////////////////////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		//////////////////////////
		CDrFE2D* pPoly = (CDrFE2D*)pObject;
//		nCount++;
		N = *(pPoly->GetNormalEye());
		sum.x += N.x;
		sum.y += N.y;
		sum.z += N.z;
		////////
	}
	SetNormalEye(sum);
	//////////////////////

}
                            
void CDrFE0D::Calc_NormalScreen3D()
{
	//////////////////////////////////////////////
	//			Normal is NOT NORMALIZED		//
	//		DO it after the Call, if needed		//
	//////////////////////////////////////////////                                                  
                                                  
	CDListMgr* 	pList;
	POSITION 	pos;
	WORLD 		N,sum = {0.0,0.0,0.0};
//	int			nCount = 0; 	
	///////////////////
	pList = GetFE2DList();
	///////////////////////////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		//////////////////////////
		CDrFE2D* pPoly = (CDrFE2D*)pObject;
//		nCount++;
		N = *(pPoly->GetNormalScreen3D());
		sum.x += N.x;
		sum.y += N.y;
		sum.z += N.z;
		////////
	}
	SetNormalScreen3D(sum);
	//////////////////////

} 
//////////////////////////////////////////////////////////////////
BOOL CDrFE0D::IsKeyMatch(CString KeyID,UINT KeyNo)
{
	return FALSE;
}
	
BOOL CDrFE0D::IsObjectHit(int nNet,POINT point)
{
	return CDrNode::IsObjectHit(nNet,point);
	///////////////
}

void CDrFE0D::Serialize(CArchive& ar)
{
}

////////////////////// END OF MODULE ///////////////////////

