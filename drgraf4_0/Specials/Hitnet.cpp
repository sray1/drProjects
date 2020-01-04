// HitNet.cpp : implementation of the CHitNet class
//

#include "stdafx.h"

//#include "Def_Lims.h"
#include "Def_Type.h"
#include "Def_Objs.h"
/////////////////////
#include "Ext_Spec.h"
#include "Def_Spec.h"
#include "Def_Toler.h"

#include "HitNet.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHitNet

IMPLEMENT_SERIAL(CHitNet,CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CHitNet,CDrObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CHitNet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////
 
CHitNet::CHitNet()
{
    SetObjectType((int)HITNET);
    SetElemType((int)SPEC_OBJECT);          //  
} 

void CHitNet::ReadDefaultHitNet()
{

	m_nSearchNetDefault		= NET_PIXEL;
	m_dSearchNetDefault		= NET_DOUBLE;
	m_dDblRatioDefault		= TOL_DOUBLE_RATIO;
	m_dCoLinearDefault		= TOL_COLINEAR;
	m_dCoPlanarDefault		= TOL_COPLANAR;
	m_dMergeNode_XDefault	= TOL_MERGENODE_X;
	m_dMergeNode_YDefault	= TOL_MERGENODE_Y;
	m_dMergeNode_ZDefault	= TOL_MERGENODE_Z;

}

void CHitNet::InitHitNet()
{

	///////////////////////////////////////////
	m_nSearchNet    = m_nSearchNetDefault;
	m_nSearchNetOld = m_nSearchNetDefault;
	///////////////////////////////////////////
	m_dSearchNet    = m_dSearchNetDefault;
	m_dSearchNetOld = m_dSearchNetDefault;
	///////////////////////////////////////////
	m_dDblRatio		= m_dDblRatioDefault;
	m_dCoLinear		= m_dCoLinearDefault;
	m_dCoPlanar		= m_dCoPlanarDefault;
	m_dMergeNode_X	= m_dMergeNode_XDefault;
	m_dMergeNode_Y	= m_dMergeNode_YDefault;
	m_dMergeNode_Z	= m_dMergeNode_ZDefault;
    
}
	
void CHitNet::SetObjectInfo(CDrObject* pObject)
{
	
	CHitNet* pHitNet = (CHitNet*) pObject;
	//////////////////////////////////////////////////
	m_nElemType			= pHitNet->m_nElemType;
	m_nObjectType		= pHitNet->m_nObjectType; 
	m_nObjectNo			= pHitNet->m_nObjectNo;
	///////////////////////////////////////////////// 
	m_nSearchNet			= pHitNet->m_nSearchNet;
	m_nSearchNetOld			= pHitNet->m_nSearchNetOld;
	m_nSearchNetDefault		= pHitNet->m_nSearchNetDefault;
	///////////////////////////////////////////////// 
	m_dSearchNet			= pHitNet->m_dSearchNet;
	m_dSearchNetOld			= pHitNet->m_dSearchNetOld;
	m_dSearchNetDefault		= pHitNet->m_dSearchNetDefault;
    /////////////////////////////////////////////////
	m_dDblRatio				= pHitNet->m_dDblRatio;
	m_dDblRatioOld			= pHitNet->m_dDblRatioOld;
	m_dDblRatioDefault		= pHitNet->m_dDblRatioDefault;
    /////////////////////////////////////////////////
	m_dCoLinear				= pHitNet->m_dCoLinear;
	m_dCoLinearOld			= pHitNet->m_dCoLinearOld;
	m_dCoLinearDefault		= pHitNet->m_dCoLinearDefault;
    /////////////////////////////////////////////////
	m_dCoPlanar				= pHitNet->m_dCoPlanar;
	m_dCoPlanarOld			= pHitNet->m_dCoPlanarOld;
	m_dCoPlanarDefault		= pHitNet->m_dCoPlanarDefault;
    /////////////////////////////////////////////////
	m_dMergeNode_X			= pHitNet->m_dMergeNode_X;
	m_dMergeNode_XOld		= pHitNet->m_dMergeNode_XOld;
	m_dMergeNode_XDefault	= pHitNet->m_dMergeNode_XDefault;
    /////////////////////////////////////////////////
	m_dMergeNode_Y			= pHitNet->m_dMergeNode_Y;
	m_dMergeNode_YOld		= pHitNet->m_dMergeNode_YOld;
	m_dMergeNode_YDefault	= pHitNet->m_dMergeNode_YDefault;
    /////////////////////////////////////////////////
	m_dMergeNode_Z			= pHitNet->m_dMergeNode_Z;
	m_dMergeNode_ZOld		= pHitNet->m_dMergeNode_ZOld;
	m_dMergeNode_ZDefault	= pHitNet->m_dMergeNode_ZDefault;
	///////
	return;
}		

void CHitNet::GetObjectInfo(CDrObject* pObject)
{
	
	CHitNet* pHitNet = (CHitNet*) pObject;
	//////////////////////////////////////////////////   
	pHitNet->m_nObjectType 			= m_nObjectType; 
	pHitNet->m_nElemType			= m_nElemType;	
	pHitNet->m_nObjectNo			= m_nObjectNo;
	///////////////////////////////////////////////// 
	pHitNet->m_nSearchNet			= m_nSearchNet;
	pHitNet->m_nSearchNetOld		= m_nSearchNetOld;
	pHitNet->m_nSearchNetDefault	= m_nSearchNetDefault;
	///////////////////////////////////////////////// 
	pHitNet->m_dSearchNet			= m_dSearchNet;
	pHitNet->m_dSearchNetOld		= m_dSearchNetOld;
	pHitNet->m_dSearchNetDefault	= m_dSearchNetDefault;
    /////////////////////////////////////////////////
	pHitNet->m_dDblRatio			= pHitNet->m_dDblRatio;
	pHitNet->m_dDblRatioOld			= pHitNet->m_dDblRatioOld;
	pHitNet->m_dDblRatioDefault		= pHitNet->m_dDblRatioDefault;
    /////////////////////////////////////////////////
	pHitNet->m_dCoLinear			= pHitNet->m_dCoLinear;
	pHitNet->m_dCoLinearOld			= pHitNet->m_dCoLinearOld;
	pHitNet->m_dCoLinearDefault		= pHitNet->m_dCoLinearDefault;
    /////////////////////////////////////////////////
	pHitNet->m_dCoPlanar			= pHitNet->m_dCoPlanar;
	pHitNet->m_dCoPlanarOld			= pHitNet->m_dCoPlanarOld;
	pHitNet->m_dCoPlanarDefault		= pHitNet->m_dCoPlanarDefault;
    /////////////////////////////////////////////////
	pHitNet->m_dMergeNode_X			= pHitNet->m_dMergeNode_X;
	pHitNet->m_dMergeNode_XOld		= pHitNet->m_dMergeNode_XOld;
	pHitNet->m_dMergeNode_XDefault	= pHitNet->m_dMergeNode_XDefault;
    /////////////////////////////////////////////////
	pHitNet->m_dMergeNode_Y			= pHitNet->m_dMergeNode_Y;
	pHitNet->m_dMergeNode_YOld		= pHitNet->m_dMergeNode_YOld;
	pHitNet->m_dMergeNode_YDefault	= pHitNet->m_dMergeNode_YDefault;
    /////////////////////////////////////////////////
	pHitNet->m_dMergeNode_Z			= pHitNet->m_dMergeNode_Z;
	pHitNet->m_dMergeNode_ZOld		= pHitNet->m_dMergeNode_ZOld;
	pHitNet->m_dMergeNode_ZDefault	= pHitNet->m_dMergeNode_ZDefault;
	///////
	return;
}		

void CHitNet::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CHitNet::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_SpecTypes;i++)
   		if(SpTypes[i].num == HITNET) 
   		{
   			name = SpTypes[i].ObjName;
   			break;
   		}	
   			
   	static CString pad = " ";
  	////////////////////////
   	AddStr(pstrCard,&name,10);
	/////////////////////// 
	return;

}   

void CHitNet::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	WORD w;
	/////// 
	if (ar.IsStoring())
	{
		TRACE(" HitNet:    Storing\n");	// TODO: add storing code here
		
		///////////////////////////////////////////////////	
		ar	<</*int*/	(WORD)m_nElemType	
			<</*int*/	(WORD)m_nObjectType
			<</*UINT*/	(WORD)m_nObjectNo; 
		///////////////////////////////////
		ar	<<	(WORD)m_nSearchNet
			<<	(WORD)m_nSearchNetOld                                       	
			<<	(WORD)m_nSearchNetDefault    
			<<	/*double*/m_dSearchNet
			<<	/*double*/m_dSearchNetOld                                       	
			<<	/*double*/m_dSearchNetDefault;    

	}
	else
	{
		TRACE(" HitNet:    Loading\n");	// TODO: add loading code here

		///////////////////////////////////////////////////	
		ar	>>/*int*/w;
		m_nElemType = (int)w;	
		ar	>>/*int*/w;
		m_nObjectType = (int)w;
		ar	>>/*UINT*/w;
		m_nObjectNo = (UINT)w;
		///////////////////////////////////
		ar	>>	w;
		m_nSearchNet	 	= (int) w; 
		ar	>>	w;
		m_nSearchNetOld	 	= (int) w; 
		ar	>>	w;
		m_nSearchNetDefault	= (int) w; 
		///////////////////////////////////
		ar	>>	m_dSearchNet; 
		ar	>>	m_dSearchNetOld; 
		ar	>>	m_dSearchNetDefault; 

	}        
	///////////////
	
}
////////////////////////////////// end of module //////////////////
