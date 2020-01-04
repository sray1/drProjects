// Node.cpp : implementation file
//


#include "stdafx.h"
/*
#include <math.h>

#include "Def_Type.h"
#include "Def_Objs.h"
#include "Def_View.h"

#include "3DMath.h"
#include "XForm.h"
#include "DrClip.h"
*/
////////////////////// AuxiObjs
#include "Def_Objs.h"
#include "Def_Auxi.h"
#include "Ext_Auxi.h"
//////////////////////
#include "AuxNod.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////
#define NODE_SIZE	3
/////////////////////////////////////////////////////////////////////////////
// CAuxNod
IMPLEMENT_SERIAL(CAuxNod, CDrNode,1)
/*
BEGIN_MESSAGE_MAP(CAuxNod, CDrNode)
	//{{AFX_MSG_MAP(CAuxNod)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CAuxNod::CAuxNod()
{  
    //////////////////////////////	
    SetObjectType((int)AUXNODE);
    SetElemType((int)AUXI_OBJECT);          //
    //////////////////////////////
	m_NodeCard.z		= 0L;
	//////////////////////////////    							
} 

CAuxNod::~CAuxNod()
{
	///////////////////////////////// empty all the lists/elem delete
	CDrNode::ReadyToDelete();
	///////////////////////////
}	

	
void CAuxNod::SetObjectInfo(CDrObject* pObject)
{

	CDrNode::SetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CAuxNod* pAdd = (CAuxNod*) pObject;
	/////////////////////
	return;
}		

void CAuxNod::GetObjectInfo(CDrObject* pObject)
{
	
	CDrNode::GetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CAuxNod* pAdd = (CAuxNod*) pObject;
	////////////////////
	return;
}		

void CAuxNod::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CAuxNod::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	UINT nType = AUXNODE;
   	if(m_NodeCard.bnid_c)
   		nType = AUXCNOD;
	/////////////////////////
   	for (int i = 0;i<nMax_AuxiTypes;i++)
	{
   		if(AxTypes[i].num == (int)nType) 
   		{
   			name = AxTypes[i].ObjName;
   			break;
   		}
	}
	///////////////////////////////////// Mesh Node
	if(IsMeshNode())
		name = "FNODE";
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
//////////////////////////////////////////////////////////
void CAuxNod::DoDrawView(CDC* PtrDC,BOOL bPenChange)
{
	if(IsClipped())
		return;
    ///////////////////////////////////////////// Draw 
	GoDoIt(PtrDC,&m_pt,bPenChange);
   	//////////////////////////////////////////
    
}                            
	 
void CAuxNod::GoDoIt(CDC* PtrDC,POINT* pt,BOOL bPenChange)
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
void CAuxNod::Serialize(CArchive& ar)
{

	CDrNode::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////     
	if (ar.IsStoring())
	{
		TRACE( " AuxNode	:Storing\n");	// TODO: add storing code here
		//////////////////////////////////////////////////////
 	}
	else
	{
		TRACE(" Node	:Loading\n");	// TODO: add loading code here
		//////////////////////////////////////////////////////
	}        
	////////////////////////

}
////////////////////// END OF MODULE ///////////////////////

