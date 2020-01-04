// Layer.cpp : implementation of the CLayer class
//

#include "stdafx.h"

#include "Def_Type.h"
#include "Def_Objs.h"
/////////////////////
#include "Ext_Spec.h"
#include "Def_Spec.h"

#include "Layer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLayer

IMPLEMENT_SERIAL(CLayer,CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CLayer,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CLayer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////
 
CLayer::CLayer()
{
    SetObjectType((int)LAYER);
    SetElemType((int)SPEC_OBJECT);          //  
} 

void CLayer::ReadDefaultLayer()
{

	////////////////////////////// Set Layer Info.
	m_nLayerDefault[0][0] = 1;
	m_nLayerDefault[0][1] = 0;  	//Ist Layer=Current(Later Read in from INI)	
//                          save
	m_nCurrentLayerDefault    = 0;
//                          initialize 			
	for(UINT i=1;i<MAX_LAYER;i++)
	{
		m_nLayerDefault[i][0] = 1;  //    InActive
		m_nLayerDefault[i][1] = 1;  //	   NOT Current
	}
	m_nLayerDefault[MAX_LAYER-1][0] = 0;  	//Last Layer ALWAYS Active

}

void CLayer::InitLayer()
{

	////////////////////////////// Set Layer Info.
	UINT	i,j;
//                          save
	m_nCurrentLayer    = m_nCurrentLayerDefault;
	m_nCurrentLayerOld = m_nCurrentLayerDefault;
//                          initialize 			
	for(i=0;i<MAX_LAYER;i++)
	{      
		for(j=0;j<2;j++)
		{
			m_nLayer   [i][j] = m_nLayerDefault[i][j];  
			m_nLayerOld[i][j] = m_nLayerDefault[i][j];
		}			
	}
    
}

void CLayer::SetObjectInfo(CDrObject* pObject)
{
	
	CLayer* pLayer = (CLayer*) pObject;
	//////////////////////////////////////////////////
	m_nElemType				= pLayer->m_nElemType;
	m_nObjectType			= pLayer->m_nObjectType; 
	m_nObjectNo				= pLayer->m_nObjectNo;
	///////////////////////////////////////////////// 
	m_nCurrentLayer    		= pLayer->m_nCurrentLayer;
	m_nCurrentLayerOld 		= pLayer->m_nCurrentLayer;
    m_nCurrentLayerDefault	= pLayer->m_nCurrentLayerDefault;

	for(int i=0;i<MAX_LAYER;i++)
	{      
		for(int j=0;j<2;j++)
		{
			m_nLayer   [i][j] 		= pLayer->m_nLayer[i][j];  
			m_nLayerOld[i][j] 		= pLayer->m_nLayer[i][j];
			m_nLayerDefault[i][j] 	= pLayer->m_nLayerDefault[i][j];
		}			
	}
    /////////////////////////////////////////////////

	return;
}		

void CLayer::GetObjectInfo(CDrObject* pObject)
{
	
	CLayer* pLayer = (CLayer*) pObject;
	//////////////////////////////////////////////////   
	pLayer->m_nObjectType 		= m_nObjectType; 
	pLayer->m_nElemType			= m_nElemType;	
	pLayer->m_nObjectNo			= m_nObjectNo;
	///////////////////////////////////////////////// 
	pLayer->m_nCurrentLayer    		= m_nCurrentLayer;
	pLayer->m_nCurrentLayerOld 		= m_nCurrentLayer;
    pLayer->m_nCurrentLayerDefault	= m_nCurrentLayerDefault;

	for(int i=0;i<MAX_LAYER;i++)
	{      
		for(int j=0;j<2;j++)
		{
			pLayer->m_nLayer   [i][j] 		= m_nLayer[i][j];  
			pLayer->m_nLayerOld[i][j] 		= m_nLayer[i][j];
			pLayer->m_nLayerDefault[i][j] 	= m_nLayerDefault[i][j];
		}			
	}
	/////////////////////////////////////////
	return;
}		

void CLayer::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CLayer::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_SpecTypes;i++)
   		if(SpTypes[i].num == LAYER) 
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


void CLayer::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	WORD w;
	/////// 
	if (ar.IsStoring())
	{
		TRACE(" Layer:    Storing\n");	// TODO: add storing code here
		/////////////	
		ar	<<	(WORD)m_nCurrentLayer
			<<	(WORD)m_nCurrentLayerOld;                             
			////////////////////////////// 			
		for(int i=0;i<MAX_LAYER;i++)
		{      
			for(int j=0;j<2;j++)
			{
				ar	<<	(WORD)m_nLayer   [i][j]  
					<<	(WORD)m_nLayerOld[i][j];
			}			
		}

	}
	else
	{
		TRACE(" Layer:    Loading\n");	// TODO: add loading code here

		////////////////////////////// Set Layer Info.
		ar	>>	w;
		m_nCurrentLayer = (UINT) w;
		ar	>>	w;
		m_nCurrentLayerOld = (UINT) w;                             
		////////////////////////////// 			
		for(int i=0;i<MAX_LAYER;i++)
		{      
			for(int j=0;j<2;j++)
			{
				ar	>>	w;
				m_nLayer   [i][j] = (UINT) w;  
				ar	>>	w;
				m_nLayerOld[i][j] = (UINT) w;
			}			
		}

	}        
	///////////////
	
}
                    
CString CLayer::GetLayerInfo(UINT i)
{
static char* Active[2] = {"  Active","InActive"};
static char* Current[2]= {"/Current",""};

//	Get Most Recent Active & Current Status
	UINT	nActive,nCurrent;
	
	nActive  = m_nLayer[i][0];
	nCurrent = m_nLayer[i][1];
	
	CString str;
	char buf[80];
	sprintf(buf,"%u: %s%s",i,Active[nActive],Current[nCurrent]);
	str = buf;
		
	return(str);		
//   I am saving following to check what's wrong with wsprintf////////////////			
//				wsprintf(str.GetBuffer(80),"%u: %s %s",i,Active[0],Current[0]); 
//				wsprintf(str.GetBuffer(80),"%u: %s %s",i,Active[0],Current[0]); 
//				str.ReleaseBuffer();                                          
//////////////////////////////////////////////////////////////////////////////
}
			
void CLayer::SetLayerInfo(UINT i,UINT nType)
{
/////////////////////////////////////////////

//	nType = 0 :Cancel
//			1 :Active
//			2 :InActive
//			3 :Current
//			4 :Not Current
//			5 :Toggle Active/Inactive
// Active[2] = {"  Active","InActive"};
// Current[2]= {"/Current",""};
//////////////////////////////////////////////			
	switch(nType)
	{
		case 0:         // do nothing
			break;
		
		case 1:         // make active
			m_nLayer[i][0] = 0;
			break;
			
		case 2:         // make inactive /make it NONCurrent too
			m_nLayer[i][0]           = 1;
			m_nLayer[i][1]           = 1;     
			m_nLayer[MAX_LAYER-1][1] = 0;        // last layer current
			m_nCurrentLayer          = MAX_LAYER;   
			break;
			
		case 3:         // make current/ old current noncurrent
			UINT j;
			for(j=0;j<MAX_LAYER;j++)
				if(m_nLayer[j][1] == 0) 
					m_nLayer[j][1] = 1;
			
			m_nLayer[i][1]  = 0; 
			m_nCurrentLayer = i;
			break;
			
		case 4:         // make noncurrent| make Last layer current
			m_nLayer[i][1]           = 1; 
			m_nLayer[MAX_LAYER-1][1] = 0;        // last layer current
			m_nCurrentLayer          = MAX_LAYER;   
			break;
			
		case 5:			     // Toggle
			if(m_nLayer[i][0] == 1)
				m_nLayer[i][0] = 0;
			else
				m_nLayer[i][0] = 1;
		default:
			break;
		}
		
		m_nLayer[MAX_LAYER-1][0]=0;     // Last Layer always Active
		
}		

void CLayer::GetLayerArray(UINT nLayer[][2])
{
	for(int i=0;i<MAX_LAYER;i++)
	{      
		for(int j=0;j<2;j++)
			nLayer[i][j] = m_nLayer[i][j];
	}
}
				
void CLayer::SetLayerArray(UINT nLayer[][2])
{
	for(int i=0;i<MAX_LAYER;i++)
	{      
		for(int j=0;j<2;j++)
			m_nLayer[i][j] = nLayer[i][j];
	} 
}	                 

void CLayer::GetLayerOldArray(UINT nLayer[][2])
{
	for(int i=0;i<MAX_LAYER;i++)
	{      
		for(int j=0;j<2;j++)
			nLayer[i][j] = m_nLayerOld[i][j];
	}
}
				
void CLayer::SetLayerOldArray(UINT nLayer[][2])
{
	for(int i=0;i<MAX_LAYER;i++)
	{      
		for(int j=0;j<2;j++)
			m_nLayerOld[i][j] = nLayer[i][j];
	} 
}	
void CLayer::GetLayerDefaultArray(UINT nLayer[][2])
{
	for(int i=0;i<MAX_LAYER;i++)
	{      
		for(int j=0;j<2;j++)
			nLayer[i][j] = m_nLayerDefault[i][j];
	}
}
				
void CLayer::SetLayerDefaultArray(UINT nLayer[][2])
{
	for(int i=0;i<MAX_LAYER;i++)
	{      
		for(int j=0;j<2;j++)
			m_nLayerDefault[i][j] = nLayer[i][j];
	} 
}	
////////////////////////////////// end of module //////////////////
