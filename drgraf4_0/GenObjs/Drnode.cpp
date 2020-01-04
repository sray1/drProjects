// Node.cpp : implementation file
//


#include "stdafx.h"
#include <math.h>

#include "Def_Type.h"
#include "Def_Objs.h"
#include "Def_View.h"

#include "3DMath.h"
#include "XForm.h"
#include "DrClip.h"
////////////////////// elObjs
#include "Def_IGen.h"
#include "Def_Elem.h"
#include "Ext_Elem.h"
//#include "DrFE2D.h"
//#include "DrFE3D.h"
////////////////////// cards
#include "Def_Card.h"        //CNODE
//////////////////////
#include "DrNode.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////
#define GREEN	RGB(0,255,0)
#define RED		RGB(255,0,0)
/////////////////////////////////////////////////////////////////////////////
// CDrNode
IMPLEMENT_SERIAL(CDrNode, CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CDrNode, CDrObject)
	//{{AFX_MSG_MAP(CDrNode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
//////////////////////
#define	NODE_SIZE	4
/////////////////////////////////////////////////////////////////////////////
CDrNode::CDrNode()
{  
    //////////////////////////////	
    SetObjectType((int)NODE);
    SetElemType((int)ELEM_OBJECT);          //
    //////////////////////////////
	m_bMeshNode		= FALSE;
	////////////////////////////// Render
//	m_LocalPos;
//	m_WorldPos;
//	m_EyePos;
//	m_ScreenPos;	//3D
//  m_NormalWorld;
//  m_NormalEye;
//  m_NormalScreen3D;
//  m_NormalScreen2D;
	////////////////////////////
	m_NodeCard.id		= "";
	m_NodeCard.sup_id	= "";
	m_NodeCard.nid_r	= "";
	m_NodeCard.x		= 0L;
	m_NodeCard.y		= 0L;
	m_NodeCard.z		= 0L;
	m_NodeCard.bnid_c	= FALSE; 
	////////////////////////////// Input Info
	m_bCoord			= TRUE;
//	m_dLength;
//	m_Delta;	// coords wrt Ref
	m_FromID			= "";
	m_ToID				= "";
	m_bFromCN			= FALSE;
	m_bToCN				= FALSE;
	//////////////////////////////
	m_nPrecision		= 2;
	m_bTransformed		= FALSE;
//	m_dMapFactor;
//	m_dScaleFactor;
//	m_lmf;           // from MASTER Card
	m_FmtStr			= "";
	/////////////////////////////////// 
	m_pt.x				= 0;
	m_pt.y				= 0;
	//////////////////////////////    							
} 

CDrNode::~CDrNode()
{
	///////////////////////////////// empty all the lists/elem delete
	ReadyToDelete();
	///////////////////////////
}	

void CDrNode::ReadyToDelete()
{

	/////////////////////////////////////
	CDrObject* pObject;
	///////////////////////////////////// 
	while(!(GetLabelList()->IsEmpty()))// delete:private
	{
		pObject = (CDrObject*)(GetLabelList()->RemoveHead());	// Label
		///////////////////////////////// private
		int index;
		CDListMgr* pNodeList = pObject->GetNodeList();
		if(pNodeList)
			index = pNodeList->GetObjectIndex(this);
		if(index>=0)
			pNodeList->RemoveObject(index); //Node
		///////////////////////////////// Public
//		pObject->ReadyToDelete();	//no delete:public	
		delete pObject;	//delete:private	
	}	
	///////////////////////////////////// 
	while(!(GetElemList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetElemList()->RemoveHead());
		///////////////////////////////// private
		if(GetLevelType() != LEVEL_GRAPA)
			continue;
		///////////////////////////////// Public
		int nLevelType = pObject->GetLevelType();
		if(nLevelType == LEVEL_GRAPA) //no delete:public
		{
			int index;
			CDListMgr* pNodeList = pObject->GetNodeList();
			if(pNodeList)
				index = pNodeList->GetObjectIndex(this);
			if(index>=0)
				pNodeList->RemoveObject(index); //Curve
			/////////////////////////
		}
		else
			delete pObject;	//delete:private	
	}	
	while(!(GetCurveList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetCurveList()->RemoveHead());
		///////////////////////////////// private
		if(GetLevelType() != LEVEL_GRAPA)
			continue;
		///////////////////////////////// Public
		int nLevelType = pObject->GetLevelType();
		if(nLevelType == LEVEL_GRAPA) //no delete:public
		{
			int index;
			CDListMgr* pNodeList;
			pNodeList = pObject->GetNodeList();
			if(pNodeList)
				index = pNodeList->GetObjectIndex(this);
			if(index>=0)
				pNodeList->RemoveObject(index); //Curve
			/////////////////////////
			pNodeList = pObject->GetINodeList();
			if(pNodeList)
				index = pNodeList->GetObjectIndex(this);
			if(index>=0)
				pNodeList->RemoveObject(index); //Curve
			/////////////////////////
			pNodeList = pObject->GetCNodeList();
			if(pNodeList)
				index = pNodeList->GetObjectIndex(this);
			if(index>=0)
				pNodeList->RemoveObject(index); //Curve
			/////////////////////////
		}
		else
			delete pObject;	//delete:private	
	}	
	while(!(GetPatchList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetPatchList()->RemoveHead());
		///////////////////////////////// private
		if(GetLevelType() != LEVEL_GRAPA)
			continue;
		///////////////////////////////// Public
		int nLevelType = pObject->GetLevelType();
		if(nLevelType == LEVEL_GRAPA) //no delete:public
		{
			int index;
			CDListMgr* pNodeList;
			pNodeList = pObject->GetNodeList();
			if(pNodeList)
				index = pNodeList->GetObjectIndex(this);
			if(index>=0)
				pNodeList->RemoveObject(index); //Curve
			/////////////////////////
			pNodeList = pObject->GetINodeList();
			if(pNodeList)
				index = pNodeList->GetObjectIndex(this);
			if(index>=0)
				pNodeList->RemoveObject(index); //Curve
			/////////////////////////
			pNodeList = pObject->GetCNodeList();
			if(pNodeList)
				index = pNodeList->GetObjectIndex(this);
			if(index>=0)
				pNodeList->RemoveObject(index); //Curve
			/////////////////////////
		}
		else
			delete pObject;	//delete:private	
	}	
	while(!(GetSolidList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetSolidList()->RemoveHead());
		///////////////////////////////// private
		if(GetLevelType() != LEVEL_GRAPA)
			continue;
		///////////////////////////////// Public
		int nLevelType = pObject->GetLevelType();
		if(nLevelType == LEVEL_GRAPA) //no delete:public
		{
			int index;
			CDListMgr* pNodeList;
			pNodeList = pObject->GetNodeList();
			if(pNodeList)
				index = pNodeList->GetObjectIndex(this);
			if(index>=0)
				pNodeList->RemoveObject(index); //Curve
			/////////////////////////
			pNodeList = pObject->GetINodeList();
			if(pNodeList)
				index = pNodeList->GetObjectIndex(this);
			if(index>=0)
				pNodeList->RemoveObject(index); //Curve
			/////////////////////////
			pNodeList = pObject->GetCNodeList();
			if(pNodeList)
				index = pNodeList->GetObjectIndex(this);
			if(index>=0)
				pNodeList->RemoveObject(index); //Curve
			/////////////////////////
		}
		else
			delete pObject;	//delete:private	
	}	
	///////////////////////////////////// unload 
	while(!(GetSuppList()->IsEmpty()))// unload/no delete Supports: public
	{
		pObject = (CDrObject*)(GetSuppList()->RemoveHead());
		///////////////////////////////// private
		if(GetLevelType() != LEVEL_GRAPA)
			continue;
		///////////////////////////////// Public
		int nLevelType = pObject->GetLevelType();
		if(nLevelType == LEVEL_GRAPA) //no delete:public
			pObject->ReadyToDelete();
		else
			delete pObject;	//delete:private	
	}	
	///////////////////////////////////// unload 
	while(!(GetStaLList()->IsEmpty()))// unload/no delete Statics: private
	{
		pObject = (CDrObject*)(GetStaLList()->RemoveHead());
		///////////////////////////////// private
		if(GetLevelType() != LEVEL_GRAPA)
			continue;
		///////////////////////////////// Public
		int nLevelType = pObject->GetLevelType();
		if(nLevelType == LEVEL_GRAPA) //no delete:public
			pObject->ReadyToDelete();
		else
			delete pObject;	//delete:private	
	}	
	////////////////////////////////////// unload Support Expanded/delete:private
	while(!GetSuppCardList()->IsEmpty())
	{
		GetSuppCardList()->RemoveHead();  //Expanded Support
		//////////
	}
	////////////////////////////////////// unload Static Expanded/delete:private
	while(!GetStaLCardList()->IsEmpty())
	{
		GetStaLCardList()->RemoveHead();  //Expanded Static
		//////////
	}
	/////////////////////////////////////
	
}
	
int CDrNode::DealObjectDialog()
{
/*
	CNodeProp	dlg;
	if(dlg.DoModal() == IDOK)
		return 0;
	else
		return -1;
*/
	return 0;			
}
	
void CDrNode::SetObjectInfo(CDrObject* pObject)
{

	CDrObject::SetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CDrNode* pAdd = (CDrNode*) pObject;
	//////////////////////////////////////////////////////// CopyList
	m_LabelList.AddTail(pAdd->GetLabelList() ); 
	m_ElemList.AddTail(pAdd->GetElemList() ); 
	m_PatchList.AddTail(pAdd->GetPatchList() ); 
	m_CurveList.AddTail(pAdd->GetCurveList() ); 
	m_SolidList.AddTail(pAdd->GetSolidList() ); 
	m_SuppList.AddTail(pAdd->GetSuppList() ); 
	m_StaLList.AddTail(pAdd->GetStaLList() ); 
	if(!(pAdd->m_SuppCardList.IsEmpty()) )
		m_SuppCardList.AddTail(&(pAdd->m_SuppCardList) ); 
	if(!(pAdd->m_StaLCardList.IsEmpty()) )
		m_StaLCardList.AddTail(&(pAdd->m_StaLCardList) ); 
	///////////////////////////////////////////////////////
	m_bSkewed			= pAdd->m_bSkewed;
	m_bLinSpr			= pAdd->m_bLinSpr;
	m_bLinSnu			= pAdd->m_bLinSnu;
	////////////////////////////// 
	m_bMeshNode			= pAdd->m_bMeshNode;		
	////////////////////////////// Render
	m_LocalPos			= pAdd->m_LocalPos;	
	m_WorldPos			= pAdd->m_WorldPos;
	m_EyePos			= pAdd->m_EyePos;
	m_ScreenPos			= pAdd->m_ScreenPos;	//3D
    m_NormalWorld		= pAdd->m_NormalWorld;
    m_NormalEye			= pAdd->m_NormalEye;
    m_NormalScreen3D	= pAdd->m_NormalScreen3D;
    m_NormalScreen2D	= pAdd->m_NormalScreen2D;
	////////////////////////////
	m_NodeCard.id  		= (pAdd->GetNodeCard())->id;
	m_NodeCard.sup_id	= (pAdd->GetNodeCard())->sup_id;
	m_NodeCard.nid_r  	= (pAdd->GetNodeCard())->nid_r;
	m_NodeCard.x		= (pAdd->GetNodeCard())->x;
	m_NodeCard.y  		= (pAdd->GetNodeCard())->y;
	m_NodeCard.z  		= (pAdd->GetNodeCard())->z;
	m_NodeCard.bnid_c  	= (pAdd->GetNodeCard())->bnid_c;
	m_NodeCard.load_id  = (pAdd->GetNodeCard())->load_id;
	m_NodeCard.disp_id	= (pAdd->GetNodeCard())->disp_id;
	m_NodeCard.ElNum	= (pAdd->GetNodeCard())->ElNum;
	m_NodeCard.num_min	= (pAdd->GetNodeCard())->num_min;		// band-minimized
		
	m_nCardNo			= pAdd->m_nCardNo;
	////////////////////////////// Input Info
	m_bCoord			= pAdd->m_bCoord;
	m_dLength			= pAdd->m_dLength;
	m_Delta				= pAdd->m_Delta;	// coords wrt Ref
	m_FromID			= pAdd->m_FromID;
	m_ToID				= pAdd->m_ToID;
	m_bFromCN			= pAdd->m_bFromCN;
	m_bToCN				= pAdd->m_bToCN;
	//////////////////////////////
	m_nPrecision		= pAdd->m_nPrecision;
	m_bTransformed		= pAdd->m_bTransformed;
	m_dMapFactor		= pAdd->m_dMapFactor;
	m_dScaleFactor		= pAdd->m_dScaleFactor;
	m_lmf				= pAdd->m_lmf;           // from MASTER Card
	m_FmtStr			= pAdd->m_FmtStr;
	////////////////////
	m_pt				= pAdd->m_pt;			// Screen Position 2D 
	/////////////////////
	return;
}		

void CDrNode::GetObjectInfo(CDrObject* pObject)
{
	
	CDrObject::GetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CDrNode* pAdd = (CDrNode*) pObject;
	//////////////////////////////////////////////////// NODEINFO   
	pAdd->m_LabelList.AddTail(GetLabelList() ); 
	pAdd->m_ElemList.AddTail(GetElemList() ); 
	pAdd->m_PatchList.AddTail(GetPatchList() ); 
	pAdd->m_CurveList.AddTail(GetCurveList() ); 
	pAdd->m_SolidList.AddTail(GetSolidList() ); 
	pAdd->m_SuppList.AddTail(GetSuppList() ); 
	pAdd->m_StaLList.AddTail(GetStaLList() ); 
	if(!(m_SuppCardList.IsEmpty()) )
		pAdd->m_SuppCardList.AddTail(&m_SuppCardList ); 
	if(!(m_StaLCardList.IsEmpty()) )
		pAdd->m_StaLCardList.AddTail(&m_StaLCardList ); 
	////////////////////////////////////////////////////////   
	pAdd->m_bSkewed			= m_bSkewed;
	pAdd->m_bLinSpr			= m_bLinSpr;
	pAdd->m_bLinSnu			= m_bLinSnu;
	////////////////////////////// 
	pAdd->m_bMeshNode		= m_bMeshNode;		
	////////////////////////////// Render
	pAdd->m_LocalPos		= m_LocalPos;	
	pAdd->m_WorldPos		= m_WorldPos;
	pAdd->m_EyePos			= m_EyePos;
	pAdd->m_ScreenPos		= m_ScreenPos;	//3D
    pAdd->m_NormalWorld		= m_NormalWorld;
    pAdd->m_NormalEye		= m_NormalEye;
    pAdd->m_NormalScreen3D	= m_NormalScreen3D;
    pAdd->m_NormalScreen2D	= m_NormalScreen2D;
	////////////////////////////
	(pAdd->GetNodeCard())->id		= m_NodeCard.id;
	(pAdd->GetNodeCard())->sup_id	= m_NodeCard.sup_id;
	(pAdd->GetNodeCard())->nid_r	= m_NodeCard.nid_r;
	(pAdd->GetNodeCard())->x		= m_NodeCard.x;
	(pAdd->GetNodeCard())->y		= m_NodeCard.y;
	(pAdd->GetNodeCard())->z		= m_NodeCard.z;
	(pAdd->GetNodeCard())->bnid_c	= m_NodeCard.bnid_c;
	(pAdd->GetNodeCard())->load_id  = m_NodeCard.load_id;
	(pAdd->GetNodeCard())->disp_id	= m_NodeCard.disp_id;
	(pAdd->GetNodeCard())->ElNum	= m_NodeCard.ElNum;
	(pAdd->GetNodeCard())->num_min	= m_NodeCard.num_min;		// band-minimized
		
	pAdd->m_nCardNo			= m_nCardNo;
	////////////////////////////// Input Info
	pAdd->m_bCoord			= m_bCoord;
	pAdd->m_dLength			= m_dLength;
	pAdd->m_Delta			= m_Delta;	// coords wrt Ref
	pAdd->m_FromID			= m_FromID;
	pAdd->m_ToID			= m_ToID;
	pAdd->m_bFromCN			= m_bFromCN;
	pAdd->m_bToCN			= m_bToCN;
	//////////////////////////////
	pAdd->m_nPrecision				= m_nPrecision;
	pAdd->m_bTransformed			= m_bTransformed;
	pAdd->m_dMapFactor				= m_dMapFactor;
	pAdd->m_dScaleFactor			= m_dScaleFactor;
	pAdd->m_lmf						= m_lmf;           // from MASTER Card
	pAdd->m_FmtStr					= m_FmtStr;
	////////////////////
	pAdd->m_pt						= m_pt;			// Screen Position 2D 
	////////////////////
	return;
}		

void CDrNode::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDrNode::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	UINT nType = NODE;
   	if(m_NodeCard.bnid_c)
   		nType = CNODE;
	/////////////////////////
   	for (int i = 0;i<nMax_ElemTypes;i++)
	{
   		if(ElTypes[i].num == (int)nType) 
   		{
   			name = ElTypes[i].ObjName;
   			break;
   		}
	}
	///////////////////////////////////// Mesh Node
	if(IsMeshNode())
		name = "NODE";
   	/////////////////////////
   	CString pad = " ";
  	////////////////////////
	AddStr(pstrCard,&name,10);
   	AddStr(pstrCard,&m_NodeCard.id,5);
	AddStr(pstrCard,&pad,5);
	////////////////////////////////////////////////////////// LOG*precision   	
	double xWorld_Preci,yWorld_Preci,zWorld_Preci;
   	xWorld_Preci	= (double)m_NodeCard.x;                 // donot strip precision
   	yWorld_Preci	= (double)m_NodeCard.y;                 // AddNum takes long
   	zWorld_Preci	= (double)m_NodeCard.z;    
   	/////////////////////////////// LOG->Map Factor->World Coord
   	xWorld_Preci	*= m_dMapFactor*m_dScaleFactor;
   	yWorld_Preci	*= m_dMapFactor*m_dScaleFactor;
   	zWorld_Preci	*= m_dMapFactor*m_dScaleFactor;
	/////////////////////////////////////////////////////////// 
//DrObject::AddNum(CString* pstrDestin,long lNumber,long lmf,long lBase, CString FmtStr)                                        //drPipe
   	///////////////////////////////// 
   	long lWorldBase = (long)(pow(10.,(double)m_nPrecision) );
   	AddNum(pstrCard,(long)xWorld_Preci,m_lmf,lWorldBase,m_FmtStr);
   	AddNum(pstrCard,(long)yWorld_Preci,m_lmf,lWorldBase,m_FmtStr);
   	AddNum(pstrCard,(long)zWorld_Preci,m_lmf,lWorldBase,m_FmtStr);
   	AddStr(pstrCard,&m_NodeCard.nid_r,5);
	AddStr(pstrCard,&pad,5);
   	AddStr(pstrCard,&m_NodeCard.sup_id,5);
	AddStr(pstrCard,&pad,5);
	/////////////////////// 
	return;

}   
/*
void CDrNode::GetRawCoords(long* lCoord, int* pnPrecision, int index)
{

	//////////////////////////////////////////
   	lCoord[0] 	= GetNodeCard()->x;
   	lCoord[1] 	= GetNodeCard()->y;
   	lCoord[2]	= GetNodeCard()->z;
   	*pnPrecision 	= GetPrecision();
   	////////////////////////////////////////// 
   	return;
    
}
*/
//////////////////////////////////////////////////////////
void CDrNode::TransformObjectToWorld(pMATRIX pLM,BOOL bYes)
{
	////////////////////////
	TransformToWorldPos(pLM,bYes);
	//////////////////
}
	
void CDrNode::TransformObjectToView(pMATRIX pViewM)
{

	//////////////////////
	TransformToEyePos(pViewM);
	//////////////////////
}	

BOOL CDrNode::RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType)
{
		return FALSE;	// do nothing
}			 
				
void CDrNode::ProjectObject
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

void CDrNode::TransformToWorldPos(pMATRIX pLM,BOOL bYes)
{

	pMATRIX		pLMP;	
	///////////////////////// 
	if(bYes)
		pLMP 	= pLM;
	//////////////////////////////////////////// Transform
	Calc_WorldPos(pLMP,bYes);
	///////////////////	
}

void CDrNode::TransformToEyePos(pMATRIX pViewM)
{

	//////////////////////////////////////////// View Transform
	Calc_EyePos(pViewM);
	///////////////////	
}

void CDrNode::ProjectToScreenPos
				(pMATRIX pvv3DM,double dScale_U,double dScale_V)
{

	//////////////////////////////////////////// Project
	ProjectToScreenPos3D(pvv3DM);
	//////////////////////////////////
	//	Bounding Corners ARE the Nodes
	// 	So no need to do again
	///////////////////////////////////////
	WORLD ScreenPos = *GetScreenPos3D();
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
	SetScreenPos2D(pt);
	//////////////////////
}

void CDrNode::Calc_ScreenRectFromCNodes()
{
	/////////////////////
	FinishObject();
	///////////////
}
	
void CDrNode::FinishObject()
{ 

	///////////////////////////////////// 
	// Calculate the bounding rectangle.  It's needed for smart
	// repainting.
	///////////////////////////////////////////// 
	m_rectBounding.left   = m_pt.x - 2*NODE_SIZE;
	m_rectBounding.right  = m_pt.x + 2*NODE_SIZE;
	m_rectBounding.top    = m_pt.y + 2*NODE_SIZE;
	m_rectBounding.bottom = m_pt.y - 2*NODE_SIZE;

	// Add the pen width to the bounding rectangle.  This is necessary
	// to account for the width of the Node when invalidating
	// the screen.
	m_rectBounding.InflateRect(CSize(m_nPenWidth, -(int)m_nPenWidth));           
	return; 
	
}
//////////////////////////////////////////////////////////////
void CDrNode::Calc_WorldPos(pMATRIX pLM,BOOL bYes)
{

	WORLD LocalPos,WorldPos;
	//////////////////////////
	LocalPos = *GetLocalPos();
	////////////////////////// 
	if(!bYes)
	{
		SetWorldPos(LocalPos);
		return;
	}	
	///////////////////////////////////////////////		
	CXForm XForm;
	//////////////////////
	XForm.Transform(&LocalPos, &WorldPos, pLM);
	/////////////////////////////		
	SetWorldPos(WorldPos);
}				
			
void CDrNode::Calc_EyePos(pMATRIX pViewM)
{
	WORLD WorldPos,EyePos;
	CXForm XForm;
	//////////////////////
	WorldPos = *GetWorldPos();
	XForm.Transform(&WorldPos, &EyePos,pViewM); // Eye at PRP
	//////////////////
	SetEyePos(EyePos);
	
}				

void CDrNode::ProjectToScreenPos3D(pMATRIX pvv3DM)
{
	//////////////////////////////////////////////////////////
	//	Perspective Canonical View Volume should be			// 
	//				Transformed to                      	//
	//	Parallel Canonical View Volume by M(Foley;p658)		//
	//	so that we can use one STANDARD Z_BUFFER Algorithm	//
	//			for TRANSFORMED PARALLEL CVV                //
	//	So, we NEED m_bParallel, if False, then zMin of		//
	//			UNTRANSFORMED PERSPECTIVE CVV				//
	// 	THEN IT IS PROJECTED TO GET SCREEN COORDINATES		//
	//////////////////////////////////////////////////////////
	WORLD EyePos,ScreenPos;
	CXForm XForm;
	/////////////
	EyePos = *GetEyePos();
/////////////////////////////////////// Multiply by M(Foley:p658)
//	It will be done beforehand
//	if(!m_bParallel)
//		XForm->PerspectiveToParallelCVV
//			(&EyePos,&ScreenPos,zMin);
///////////////////////////////////////////////////
	XForm.Project(pvv3DM,&EyePos, &ScreenPos);
	////////////////////////////////////////
	SetScreenPos3D(ScreenPos);
	//////////////////////	
	
}				

void CDrNode::Calc_NormalWorld()
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
//		nCount++;
		N = *(pObject->GetNormalWorld());
		sum.x += N.x;
		sum.y += N.y;
		sum.z += N.z;
		////////
	}
	//	WHY BOTHER DIVIDING, RATHER SAVE TIME!
/*	
	//////////////
	double rPolys 	= 1./nCount;
	////////////////
	sum.x *= rPolys;
	sum.y *= rPolys;
	sum.z *= rPolys;
	//////////////// normalize
	C3DMath	Math3D;
	Math3D.Normalize(&sum,&sum);
	////////////////////////////
*/	
	SetNormalWorld(sum);
	//////////////////////

}
                            

void CDrNode::Calc_NormalEye()
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
//		nCount++;
		N = *(pObject->GetNormalEye());
		sum.x += N.x;
		sum.y += N.y;
		sum.z += N.z;
		////////
	}
	//	WHY BOTHER DIVIDING, RATHER SAVE TIME!
/*	
	//////////////
	double rPolys 	= 1./nCount;
	////////////////
	sum.x *= rPolys;
	sum.y *= rPolys;
	sum.z *= rPolys;
	//////////////// normalize
	C3DMath	Math3D;
	Math3D.Normalize(&sum,&sum);
	////////////////////////////
*/	
	SetNormalEye(sum);
	//////////////////////

}
                            
void CDrNode::Calc_NormalScreen3D()
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
//		nCount++;
		N = *(pObject->GetNormalScreen3D());
		sum.x += N.x;
		sum.y += N.y;
		sum.z += N.z;
		////////
	}
	//	WHY BOTHER DIVIDING, RATHER SAVE TIME!
/*	
	//////////////
	double rPolys 	= 1./nCount;
	////////////////
	sum.x *= rPolys;
	sum.y *= rPolys;
	sum.z *= rPolys;
	//////////////// normalize
	C3DMath	Math3D;
	Math3D.Normalize(&sum,&sum);
	////////////////////////////
*/	
	SetNormalScreen3D(sum);
	//////////////////////

} 

//////////////////////////////////////////////////////////////
void CDrNode::InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
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
	///////////////////////////////////////////////// Clipping Check
	CDrClip DrClip(m_dzMin, !m_bParallel, FALSE); 
	SetClipped(FALSE);
	if( DrClip.ClipPt( GetEyePos() ) == VI_NOT_VISIBLE )
	{
		SetClipped(TRUE); 
//		return;
	}	
	/////////////////////////////////////// if Perspective,change Pers->Par
	if(!m_bParallel)
	{               
		WORLD Per;
		CXForm XForm(m_bParallel);
		XForm.TransformPerToParCVV(m_dzMin, GetEyePos(), &Per);
		SetEyePos(Per); 
	}
	/////////////////////////////////////////////////////////////////////////	 
	ProjectObject(&m_vv3DM,m_dScale_U,m_dScale_V);///	calc Bounding Rect 
	///////////////////////////////////
//	FinishObject();//	calc Bounding Rect  
	/////////////
	return;
}
						
void CDrNode::DoDrawView(CDC* PtrDC,BOOL bPenChange)
{
	if(IsClipped())
		return;
    ///////////////////////////////////////////// Draw 
	GoDoIt(PtrDC,&m_pt,bPenChange);
   	//////////////////////////////////////////
    
}                            
	 
void CDrNode::GoDoIt(CDC* PtrDC,POINT* pt,BOOL bPenChange)
{
   	CPen    Pen;
   	CPen*   PtrOldPen;
	CBrush* pBrOld;
	BYTE	Intensity = 1;
	/////////////////////////////////////////////////// Pen 
	if(bPenChange)
	{
		m_crPenColor |= (  ((WORD) (Intensity)) << 7);
   		Pen.CreatePen (m_nPenStyle,m_nPenWidthHi,m_crPenColor);
	}
	else
   		Pen.CreatePen (m_nPenStyle,m_nPenWidth,m_crPenColor);
   	PtrOldPen = PtrDC->SelectObject(&Pen);
	/////////////////////////////////////////////////// 
//	IF bLayerON = FALSE make PEN: DASHED or something     TO BE Done Later
   	//////////////////////////////////////////////// Draw
   	if(IsControlNode())
   	{
    	////////////////////////////////////// Cross 
    	PtrDC->MoveTo(pt->x-2*NODE_SIZE,pt->y);
    	PtrDC->LineTo(pt->x+2*NODE_SIZE,pt->y);
    	PtrDC->MoveTo(pt->x,pt->y-2*NODE_SIZE);
    	PtrDC->LineTo(pt->x,pt->y+2*NODE_SIZE);
 	}
	else
	{	
  		////////////////////////////////////// ellipse
    	CRect Rect;
		Rect.left   = pt->x - NODE_SIZE;
		Rect.right  = pt->x + NODE_SIZE;
		Rect.top    = pt->y - NODE_SIZE;
		Rect.bottom = pt->y + NODE_SIZE;
		/////////////////////////////////	
		PtrDC->Ellipse(&Rect);
	}	  	
	if(bPenChange)
	{
  		/////////////////////////////////////////////////// Brush
		pBrOld = (CBrush*)PtrDC->SelectStockObject(NULL_BRUSH);
		////////////////////////////////////// ellipse
    	CRect Rect;
		Rect.left   = pt->x - 2*NODE_SIZE;
		Rect.right  = pt->x + 2*NODE_SIZE;
		Rect.top    = pt->y - 2*NODE_SIZE;
		Rect.bottom = pt->y + 2*NODE_SIZE;
		/////////////////////////////////	
		PtrDC->Ellipse(&Rect);
		///////
		PtrDC->SelectObject(pBrOld);
	}
	/////////////////////////////// 
	PtrDC->SelectObject(PtrOldPen);   
	Pen.DeleteObject(); 
	//////////	
}   

/////////////////////////////////////////////////////////////////////////////
BOOL CDrNode::IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo)
{

	CDrNode* pNode = (CDrNode*)(pObject);
	////////////////////////////////////		
	switch(KeyNo)
	{
	 	case 1:         // NodeID

			if((pNode->GetNodeCard())->id ==KeyID)
				return TRUE;
			break;  
			
  		case 2:         // SUPID
			if((pNode->GetNodeCard())->sup_id ==KeyID)
				return TRUE;
			break;
				
	  	case 3:         // REFNodeID
			if((pNode->GetNodeCard())->nid_r ==KeyID)
			return TRUE;
		break;
				
  		default:
  			return FALSE;
	}
	return FALSE;
}

void CDrNode::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////     
	BYTE bnid_c, bTransformed;
	WORD	nElementType,nCardNo,nObjectNo,nObjectType,
				nPenWidth,nPenStyle,nLayer,nPrecision;
	DWORD   crPenColor;
	if (ar.IsStoring())
	{
		TRACE( " Node	:Storing\n");	// TODO: add storing code here

		ar	<<	/*int*/		(WORD)m_nElemType	
			<<	/*int*/		(WORD)m_nObjectType
			<<	/*UINT*/	(WORD)m_nObjectNo 
			//////////////////////////////////
			<<	/*CString*/	m_NodeCard.id    		// Node Card
		   	<<	/*CString*/	m_NodeCard.sup_id        // pad 10 char field
			<<	/*CString*/	m_NodeCard.nid_r
			<<	/*LONG*/	m_NodeCard.x
			<<	/*LONG*/	m_NodeCard.y
			<<	/*LONG*/	m_NodeCard.z
			<<	/*BOOL*/	(BYTE)(m_NodeCard.bnid_c); 
			/////////////////////////////////
		ar	<<	/*int*/		(WORD)m_nCardNo  
		    ///////////////////////////////
			<<	/*int*/		(WORD)m_nPrecision 
			<<	/*BOOL*/	(BYTE)m_bTransformed 
			<<	/*double*/	m_dMapFactor 
			<<	/*double*/	m_dScaleFactor 
			<<	/*long*/	m_lmf            // from MASTER Card
			<<	/*CString*/	m_FmtStr  
			////////////////////////
			<<	/*CRect*/	m_rectBounding // smallest rect that surrounds 
											// Pipe Ends measured in MM_LOENGLISH units
											// (0.01 inches, with Y-axis inverted)
			<<	/*UINT*/	(WORD)m_nPenWidth    // pen width for Pipe
			<<	/*COLORREF*/(DWORD)m_crPenColor
			<<	/*UINT*/	(WORD)m_nPenStyle
			 
			<<	/*UINT*/	(WORD)m_nLayer;
			
		ar	<<	/*POINT*/ 	m_pt;

		//////////////////////////////////////////////////////	
//		ar.Write(/*NODECARD*/	&m_NodeCard,sizeof(NODECARD) );
		//////////////////////////////////////////////////////
 	}
	else
	{
		TRACE(" Node	:Loading\n");	// TODO: add loading code here

		ar	>>	/*int*/		nElementType
			>>	/*int*/		nObjectType
			>>	/*UINT*/	nObjectNo  
			//////////////////////////////
			>>	/*CString*/	m_NodeCard.id    		// Node Card
		   	>>	/*CString*/	m_NodeCard.sup_id        // pad 10 char field
			>>	/*CString*/	m_NodeCard.nid_r
			>>	/*LONG*/	m_NodeCard.x
			>>	/*LONG*/	m_NodeCard.y
			>>	/*LONG*/	m_NodeCard.z
			>>	/*BOOL*/	bnid_c ;
		m_NodeCard.bnid_c = (BOOL) bnid_c;	
			/////////////////////////////////
		ar	>>	/*int*/		nCardNo
		    ////////////////////////////
			>>	/*int*/		nPrecision
			>>	/*BOOL*/	bTransformed 
			>>	/*double*/	m_dMapFactor 
			>>	/*double*/	m_dScaleFactor; 
			////////////////////////////// 
		ar	>>	/*long*/	m_lmf            // from MASTER Card
			>>	/*CString*/	m_FmtStr  
			
			>>	/*CRect*/	m_rectBounding // smallest rect that surrounds 
											// Pipe Ends measured in MM_LOENGLISH units
											// (0.01 inches, with Y-axis inverted)
		  	>>	/*UINT*/	nPenWidth    // pen width for Pipe
			>>	/*COLORREF*/crPenColor
			>>	/*UINT*/	nPenStyle 
			
			>>	/*UINT*/	nLayer; 
			
		ar	>>	/*POINT*/	m_pt;
    //////////////////////////////////////////////    
	m_nElemType		  	= 	(int)nElementType;		// Type = PIPE = 2 in ElGlobal.h
    m_nCardNo			= 	(int)nCardNo;
    m_nObjectType		= 	(int)nObjectType;
    m_nObjectNo			= 	(UINT)nObjectNo;
    m_nPrecision		=	(int)nPrecision;
    m_bTransformed		=   (BOOL)bTransformed;
	m_nPenWidth 		=	(UINT)nPenWidth;    // pen width for Pipe
	m_crPenColor 		= 	(COLORREF)crPenColor;
	m_nPenStyle 		= 	(UINT)nPenStyle; 
	m_nLayer			=	(UINT)nLayer;
    /////////////////////////////        

		//////////////////////////////////////////////////////	
//		ar.Read(/*NODECARD*/	&m_NodeCard,sizeof(NODECARD) );
		//////////////////////////////////////////////////////


	}        
	////////////////////////

}
	
BOOL CDrNode::IsObjectHit(int nNet,POINT point)
{
	/////////////////////////////////////////////////// Project based on Current View
	ProjectToScreenPos(&m_vv3DM,m_dScale_U,m_dScale_V);
	///////////////////////////////////////// Screen Position2D
	POINT pointTemp = *GetScreenPos2D();
   	///////////////////////////////////////// LP
	CRect Rect;
	Rect.left	= pointTemp.x - nNet;
   	Rect.top	= pointTemp.y - nNet;
	////////////////////////////////////////////////////////////
   	Rect.right	= pointTemp.x + nNet; 
   	Rect.bottom	= pointTemp.y + nNet; // LP
   	//////////////////////////////////////////////
    Rect.NormalizeRect();
	///////////////////////
	if(Rect.PtInRect(point)) 
       	return TRUE;
	else
		return FALSE;
}
	
BOOL CDrNode::IsObjectHit(double dNet,WORLD Pt)
{
	double LocXm,LocXp,LocYm,LocYp,LocZm,LocZp;
	/////////////////////////////////
	WORLD Loc = *GetWorldPos();
	/////////
	LocXm = Loc.x - dNet;
	LocXp = Loc.x + dNet;
	LocYm = Loc.y - dNet;
	LocYp = Loc.y + dNet;
	LocZm = Loc.z - dNet;
	LocZp = Loc.z + dNet;
	////////////////////////////////////////// Yes
	if
	(
		(Pt.x >= LocXm && Pt.x <= LocXp) &&
		(Pt.y >= LocYm && Pt.y <= LocYp) &&
		(Pt.z >= LocZm && Pt.z <= LocZp) 
	)
		return TRUE;
	////////////////////////////////////////// No
	else
		return FALSE;
}
////////////////////// END OF MODULE ///////////////////////

