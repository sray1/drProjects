// Obj3DMnu.cpp : implementation of the CObj3DMnu class
//

#include "stdafx.h"

#include "Def_Type.h"
#include "Def_Objs.h"
/////////////////////
#include "Ext_Spec.h"
#include "Def_Spec.h"

#include "Obj3DMnu.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObj3DMnu

IMPLEMENT_SERIAL(CObj3DMnu,CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CObj3DMnu,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CObj3DMnu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////
 
CObj3DMnu::CObj3DMnu()
{
    SetObjectType((int)OBJ3DMNU);
    SetElemType((int)SPEC_OBJECT);          //  
} 

void CObj3DMnu::ReadDefaultObj3DMnu()
{

	////////////////////////////// Set Obj3DMnu Info.
	m_IDDefault				 = "UNKNOWN";
	/////////////////////////////////////
	m_nObj3DMnuDefault[0][0] = 1;
	m_nObj3DMnuDefault[0][1] = 0;  	//Ist Obj3DMnu=Current(Later Read in from INI)	
//                          save
	m_nCurrentObj3DMnuDefault    = 0;
//                          initialize 			
	for(UINT i=1;i<MAX_OBJ3DMNU;i++)
	{
		m_nObj3DMnuDefault[i][0] = 1;  //    InActive
		m_nObj3DMnuDefault[i][1] = 1;  //	   NOT Current
	}
	m_nObj3DMnuDefault[MAX_OBJ3DMNU-1][0] = 0;  	//Last Obj3DMnu ALWAYS Active

}

void CObj3DMnu::InitObj3DMnu()
{

	////////////////////////////// Set Obj3DMnu Info.
	UINT	i,j;
//                          save
	m_nCurrentObj3DMnu    = m_nCurrentObj3DMnuDefault;
	m_nCurrentObj3DMnuOld = m_nCurrentObj3DMnuDefault;
//                          initialize 			
	for(i=0;i<MAX_OBJ3DMNU;i++)
	{      
		for(j=0;j<2;j++)
		{
			m_nObj3DMnu   [i][j] = m_nObj3DMnuDefault[i][j];  
			m_nObj3DMnuOld[i][j] = m_nObj3DMnuDefault[i][j];
		}
	m_ID[i] 	= m_IDDefault;
	m_CurrentID	= m_IDDefault;				
	}
	
    
}

void CObj3DMnu::SetObjectInfo(CDrObject* pObject)
{
	
	CObj3DMnu* pObj3DMnu = (CObj3DMnu*) pObject;
	//////////////////////////////////////////////////
	m_nElemType				= pObj3DMnu->m_nElemType;
	m_nObjectType			= pObj3DMnu->m_nObjectType; 
	m_nObjectNo				= pObj3DMnu->m_nObjectNo;
	/////////////////////////////////////////////////
	m_CurrentID					= pObj3DMnu->m_CurrentID; 
	m_nCurrentObj3DMnu    		= pObj3DMnu->m_nCurrentObj3DMnu;
	m_nCurrentObj3DMnuOld 		= pObj3DMnu->m_nCurrentObj3DMnuOld;
    m_nCurrentObj3DMnuDefault	= pObj3DMnu->m_nCurrentObj3DMnuDefault;

	for(int i=0;i<MAX_OBJ3DMNU;i++)
	{      
		for(int j=0;j<2;j++)
		{
			m_nObj3DMnu   [i][j] 		= pObj3DMnu->m_nObj3DMnu[i][j];  
			m_nObj3DMnuOld[i][j] 		= pObj3DMnu->m_nObj3DMnu[i][j];
			m_nObj3DMnuDefault[i][j] 	= pObj3DMnu->m_nObj3DMnuDefault[i][j];
		}
		m_ID[i]	= pObj3DMnu->m_ID[i];			
	}
    /////////////////////////////////////////////////

	return;
}		

void CObj3DMnu::GetObjectInfo(CDrObject* pObject)
{
	
	CObj3DMnu* pObj3DMnu = (CObj3DMnu*) pObject;
	//////////////////////////////////////////////////   
	pObj3DMnu->m_nObjectType 		= m_nObjectType; 
	pObj3DMnu->m_nElemType			= m_nElemType;	
	pObj3DMnu->m_nObjectNo			= m_nObjectNo;
	///////////////////////////////////////////////// 
	pObj3DMnu->m_CurrentID					= m_CurrentID; 
	pObj3DMnu->m_nCurrentObj3DMnu    		= m_nCurrentObj3DMnu;
	pObj3DMnu->m_nCurrentObj3DMnuOld 		= m_nCurrentObj3DMnu;
    pObj3DMnu->m_nCurrentObj3DMnuDefault	= m_nCurrentObj3DMnuDefault;

	for(int i=0;i<MAX_OBJ3DMNU;i++)
	{      
		for(int j=0;j<2;j++)
		{
			pObj3DMnu->m_nObj3DMnu   [i][j] 		= m_nObj3DMnu[i][j];  
			pObj3DMnu->m_nObj3DMnuOld[i][j] 		= m_nObj3DMnu[i][j];
			pObj3DMnu->m_nObj3DMnuDefault[i][j] 	= m_nObj3DMnuDefault[i][j];
		}
		pObj3DMnu->m_ID[i]	= m_ID[i];			
	}
	/////////////////////////////////////////
	return;
}		

void CObj3DMnu::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CObj3DMnu::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_SpecTypes;i++)
   		if(SpTypes[i].num == OBJ3DMNU) 
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


void CObj3DMnu::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	WORD w;
	/////// 
	if (ar.IsStoring())
	{
		TRACE(" Obj3DMnu:    Storing\n");	// TODO: add storing code here
		/////////////	
		ar	<<	(WORD)m_nCurrentObj3DMnu
			<<	(WORD)m_nCurrentObj3DMnuOld
			<<	m_CurrentID;                             
			////////////////////////////// 			
		for(int i=0;i<MAX_OBJ3DMNU;i++)
		{      
			for(int j=0;j<2;j++)
			{
				ar	<<	(WORD)m_nObj3DMnu   [i][j]  
					<<	(WORD)m_nObj3DMnuOld[i][j];
			}
			ar	<<	m_ID[i];			
		}

	}
	else
	{
		TRACE(" Obj3DMnu:    Loading\n");	// TODO: add loading code here

		////////////////////////////// Set Obj3DMnu Info.
		ar	>>	w;
		m_nCurrentObj3DMnu = (UINT) w;
		ar	>>	w;
		m_nCurrentObj3DMnuOld = (UINT) w;                             
		ar	>>	m_CurrentID;                             
		////////////////////////////// 			
		for(int i=0;i<MAX_OBJ3DMNU;i++)
		{      
			for(int j=0;j<2;j++)
			{
				ar	>>	w;
				m_nObj3DMnu   [i][j] = (UINT) w;  
				ar	>>	w;
				m_nObj3DMnuOld[i][j] = (UINT) w;
			}			
			ar	>>	m_ID[i];			
		}

	}        
	///////////////
	
}
                    
CString CObj3DMnu::GetObj3DMnuInfo(UINT i)
{
static char* Active[2] = {"  Active","InActive"};
static char* Current[2]= {"/Current",""};

//	Get Most Recent Active & Current Status
	UINT	nActive,nCurrent;
	
	nActive  = m_nObj3DMnu[i][0];
	nCurrent = m_nObj3DMnu[i][1];
	
	CString str;
	char buf[80];
	sprintf(buf,"%u: %s  %s%s",i,m_ID[i],Active[nActive],Current[nCurrent]);
	str = buf;
		
	return(str);		
//   I am saving following to check what's wrong with wsprintf////////////////			
//				wsprintf(str.GetBuffer(80),"%u: %s %s",i,Active[0],Current[0]); 
//				wsprintf(str.GetBuffer(80),"%u: %s %s",i,Active[0],Current[0]); 
//				str.ReleaseBuffer();                                          
//////////////////////////////////////////////////////////////////////////////
}
			
void CObj3DMnu::SetObj3DMnuInfo(UINT i,UINT nType)
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
			m_nObj3DMnu[i][0] = 0;
			break;
			
		case 2:         // make inactive /make it NONCurrent too
			m_nObj3DMnu[i][0]           = 1;
			m_nObj3DMnu[i][1]           = 1;     
			m_nObj3DMnu[MAX_OBJ3DMNU-1][1] = 0;        // last Obj3DMnu current
			m_nCurrentObj3DMnu          = MAX_OBJ3DMNU;   
			break;
			
		case 3:         // make current/ old current noncurrent
			UINT j;
			for(j=0;j<MAX_OBJ3DMNU;j++)
				if(m_nObj3DMnu[j][1] == 0) 
					m_nObj3DMnu[j][1] = 1;
			
			m_nObj3DMnu[i][1]  = 0; 
			m_nCurrentObj3DMnu = i;
			break;
			
		case 4:         // make noncurrent| make Last Obj3DMnu current
			m_nObj3DMnu[i][1]           = 1; 
			m_nObj3DMnu[MAX_OBJ3DMNU-1][1] = 0;        // last Obj3DMnu current
			m_nCurrentObj3DMnu          = MAX_OBJ3DMNU;   
			break;
			
		case 5:			     // Toggle
			if(m_nObj3DMnu[i][0] == 1)
				m_nObj3DMnu[i][0] = 0;
			else
				m_nObj3DMnu[i][0] = 1;
		default:
			break;
		}
		
		m_nObj3DMnu[MAX_OBJ3DMNU-1][0]=0;     // Last Obj3DMnu always Active
		
}		

void CObj3DMnu::GetObj3DMnuIDArray(CString nID[])
{
	for(int i=0;i<MAX_OBJ3DMNU;i++)
		nID[i] = m_ID[i];
}
				
void CObj3DMnu::SetObj3DMnuIDArray(CString nID[])
{
	for(int i=0;i<MAX_OBJ3DMNU;i++)
		m_ID[i] = nID[i];
}	                 

void CObj3DMnu::GetObj3DMnuArray(UINT nObj3DMnu[][2])
{
	for(int i=0;i<MAX_OBJ3DMNU;i++)
	{      
		for(int j=0;j<2;j++)
			nObj3DMnu[i][j] = m_nObj3DMnu[i][j];
	}
}
				
void CObj3DMnu::SetObj3DMnuArray(UINT nObj3DMnu[][2])
{
	for(int i=0;i<MAX_OBJ3DMNU;i++)
	{      
		for(int j=0;j<2;j++)
			m_nObj3DMnu[i][j] = nObj3DMnu[i][j];
	} 
}	                 

void CObj3DMnu::GetObj3DMnuOldArray(UINT nObj3DMnu[][2])
{
	for(int i=0;i<MAX_OBJ3DMNU;i++)
	{      
		for(int j=0;j<2;j++)
			nObj3DMnu[i][j] = m_nObj3DMnuOld[i][j];
	}
}
				
void CObj3DMnu::SetObj3DMnuOldArray(UINT nObj3DMnu[][2])
{
	for(int i=0;i<MAX_OBJ3DMNU;i++)
	{      
		for(int j=0;j<2;j++)
			m_nObj3DMnuOld[i][j] = nObj3DMnu[i][j];
	} 
}	
void CObj3DMnu::GetObj3DMnuDefaultArray(UINT nObj3DMnu[][2])
{
	for(int i=0;i<MAX_OBJ3DMNU;i++)
	{      
		for(int j=0;j<2;j++)
			nObj3DMnu[i][j] = m_nObj3DMnuDefault[i][j];
	}
}
				
void CObj3DMnu::SetObj3DMnuDefaultArray(UINT nObj3DMnu[][2])
{
	for(int i=0;i<MAX_OBJ3DMNU;i++)
	{      
		for(int j=0;j<2;j++)
			m_nObj3DMnuDefault[i][j] = nObj3DMnu[i][j];
	} 
}	
////////////////////////////////// end of module //////////////////
