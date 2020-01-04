// Node.cpp : implementation file
//


#include "stdafx.h"
//////////////////////
#include "Def_Auxi.h"

#include "AuxNod.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CAuxNod
IMPLEMENT_SERIAL(CAuxNod, CAuxNod,1)
/*
BEGIN_MESSAGE_MAP(CAuxNod, CAuxNod)
	//{{AFX_MSG_MAP(CAuxNod)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CAuxNod::CAuxNod()
{  
    //////////////////////////////	
    SetObjectType((int)AUXNOD);
    SetElemType((int)AUXI_OBJECT);          //
    //////////////////////////////
	m_NodeCard.z		= 0L;
	//////////////////////////////    							
} 

CAuxNod::~CAuxNod()
{
	///////////////////////////////// empty all the lists/elem delete
	CAuxNod::ReadyToDelete();
	///////////////////////////
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
//   	zWorld_Preci	= (double)m_NodeCard.z;    
   	/////////////////////////////// LOG->Map Factor->World Coord
   	xWorld_Preci	*= m_dMapFactor*m_dScaleFactor;
   	yWorld_Preci	*= m_dMapFactor*m_dScaleFactor;
//   	zWorld_Preci	*= m_dMapFactor*m_dScaleFactor;
	/////////////////////////////////////////////////////////// 
//DrObject::AddNum(CString* pstrDestin,long lNumber,long lmf,long lBase, CString FmtStr)                                        //drPipe
   	///////////////////////////////// 
   	long lWorldBase = (long)(pow(10.,(double)m_nPrecision) );
   	AddNum(pstrCard,(long)xWorld_Preci,m_lmf,lWorldBase,m_FmtStr);
   	AddNum(pstrCard,(long)yWorld_Preci,m_lmf,lWorldBase,m_FmtStr);
//   	AddNum(pstrCard,(long)zWorld_Preci,m_lmf,lWorldBase,m_FmtStr);
/*
   	AddStr(pstrCard,&m_NodeCard.nid_r,5);
	AddStr(pstrCard,&pad,5);
   	AddStr(pstrCard,&m_NodeCard.sup_id,5);
	AddStr(pstrCard,&pad,5);
*/
	/////////////////////// 
	return;

}   

void CAuxNod::Serialize(CArchive& ar)
{

	CAuxNod::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////     
	if (ar.IsStoring())
	{
		TRACE( " AuxNod	:Storing\n");	// TODO: add storing code here
		//////////////////////////////////////////////////////
 	}
	else
	{
		TRACE(" AuxNode	:Loading\n");	// TODO: add loading code here
		//////////////////////////////////////////////////////


	}        
	////////////////////////

}
////////////////////// END OF MODULE ///////////////////////

