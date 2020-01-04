// PatchMnu.cpp : implementation of the CPatchMnu class
//

#include "stdafx.h"

#include "Def_Type.h"
#include "Def_Objs.h"
/////////////////////
#include "Ext_Spec.h"
#include "Def_Spec.h"

#include "PatchMnu.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPatchMnu

IMPLEMENT_SERIAL(CPatchMnu,CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CPatchMnu,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPatchMnu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////
 
CPatchMnu::CPatchMnu()
{
    SetObjectType((int)PATCHMNU);
    SetElemType((int)SPEC_OBJECT);          //  
} 

void CPatchMnu::ReadDefaultPatchMnu()
{

	////////////////////////////// Set PatchMnu Info.
	m_IDDefault				 = "UNKNOWN";
	/////////////////////////////////////
	m_nPatchMnuDefault[0][0] = 1;
	m_nPatchMnuDefault[0][1] = 0;  	//Ist PatchMnu=Current(Later Read in from INI)	
//                          save
	m_nCurrentPatchMnuDefault    = 0;
//                          initialize 			
	for(UINT i=1;i<MAX_PATCHMNU;i++)
	{
		m_nPatchMnuDefault[i][0] = 1;  //    InActive
		m_nPatchMnuDefault[i][1] = 1;  //	   NOT Current
	}
	m_nPatchMnuDefault[MAX_PATCHMNU-1][0] = 0;  	//Last PatchMnu ALWAYS Active

}

void CPatchMnu::InitPatchMnu()
{

	////////////////////////////// Set PatchMnu Info.
	UINT	i,j;
//                          save
	m_nCurrentPatchMnu    = m_nCurrentPatchMnuDefault;
	m_nCurrentPatchMnuOld = m_nCurrentPatchMnuDefault;
//                          initialize 			
	for(i=0;i<MAX_PATCHMNU;i++)
	{      
		for(j=0;j<2;j++)
		{
			m_nPatchMnu   [i][j] = m_nPatchMnuDefault[i][j];  
			m_nPatchMnuOld[i][j] = m_nPatchMnuDefault[i][j];
		}
	m_ID[i] 	= m_IDDefault;
	m_CurrentID	= m_IDDefault;				
	}
	
    
}

void CPatchMnu::SetObjectInfo(CDrObject* pObject)
{
	
	CPatchMnu* pPatchMnu = (CPatchMnu*) pObject;
	//////////////////////////////////////////////////
	m_nElemType				= pPatchMnu->m_nElemType;
	m_nObjectType			= pPatchMnu->m_nObjectType; 
	m_nObjectNo				= pPatchMnu->m_nObjectNo;
	/////////////////////////////////////////////////
	m_CurrentID					= pPatchMnu->m_CurrentID; 
	m_nCurrentPatchMnu    		= pPatchMnu->m_nCurrentPatchMnu;
	m_nCurrentPatchMnuOld 		= pPatchMnu->m_nCurrentPatchMnuOld;
    m_nCurrentPatchMnuDefault	= pPatchMnu->m_nCurrentPatchMnuDefault;

	for(int i=0;i<MAX_PATCHMNU;i++)
	{      
		for(int j=0;j<2;j++)
		{
			m_nPatchMnu   [i][j] 		= pPatchMnu->m_nPatchMnu[i][j];  
			m_nPatchMnuOld[i][j] 		= pPatchMnu->m_nPatchMnu[i][j];
			m_nPatchMnuDefault[i][j] 	= pPatchMnu->m_nPatchMnuDefault[i][j];
		}
		m_ID[i]	= pPatchMnu->m_ID[i];			
	}
    /////////////////////////////////////////////////

	return;
}		

void CPatchMnu::GetObjectInfo(CDrObject* pObject)
{
	
	CPatchMnu* pPatchMnu = (CPatchMnu*) pObject;
	//////////////////////////////////////////////////   
	pPatchMnu->m_nObjectType 		= m_nObjectType; 
	pPatchMnu->m_nElemType			= m_nElemType;	
	pPatchMnu->m_nObjectNo			= m_nObjectNo;
	///////////////////////////////////////////////// 
	pPatchMnu->m_CurrentID					= m_CurrentID; 
	pPatchMnu->m_nCurrentPatchMnu    		= m_nCurrentPatchMnu;
	pPatchMnu->m_nCurrentPatchMnuOld 		= m_nCurrentPatchMnu;
    pPatchMnu->m_nCurrentPatchMnuDefault	= m_nCurrentPatchMnuDefault;

	for(int i=0;i<MAX_PATCHMNU;i++)
	{      
		for(int j=0;j<2;j++)
		{
			pPatchMnu->m_nPatchMnu   [i][j] 		= m_nPatchMnu[i][j];  
			pPatchMnu->m_nPatchMnuOld[i][j] 		= m_nPatchMnu[i][j];
			pPatchMnu->m_nPatchMnuDefault[i][j] 	= m_nPatchMnuDefault[i][j];
		}
		pPatchMnu->m_ID[i]	= m_ID[i];			
	}
	/////////////////////////////////////////
	return;
}		

void CPatchMnu::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CPatchMnu::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_SpecTypes;i++)
   		if(SpTypes[i].num == PATCHMNU) 
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


void CPatchMnu::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	WORD w;
	/////// 
	if (ar.IsStoring())
	{
		TRACE(" PatchMnu:    Storing\n");	// TODO: add storing code here
		/////////////	
		ar	<<	(WORD)m_nCurrentPatchMnu
			<<	(WORD)m_nCurrentPatchMnuOld
			<<	m_CurrentID;                             
			////////////////////////////// 			
		for(int i=0;i<MAX_PATCHMNU;i++)
		{      
			for(int j=0;j<2;j++)
			{
				ar	<<	(WORD)m_nPatchMnu   [i][j]  
					<<	(WORD)m_nPatchMnuOld[i][j];
			}
			ar	<<	m_ID[i];			
		}

	}
	else
	{
		TRACE(" PatchMnu:    Loading\n");	// TODO: add loading code here

		////////////////////////////// Set PatchMnu Info.
		ar	>>	w;
		m_nCurrentPatchMnu = (UINT) w;
		ar	>>	w;
		m_nCurrentPatchMnuOld = (UINT) w;                             
		ar	>>	m_CurrentID;                             
		////////////////////////////// 			
		for(int i=0;i<MAX_PATCHMNU;i++)
		{      
			for(int j=0;j<2;j++)
			{
				ar	>>	w;
				m_nPatchMnu   [i][j] = (UINT) w;  
				ar	>>	w;
				m_nPatchMnuOld[i][j] = (UINT) w;
			}			
			ar	>>	m_ID[i];			
		}

	}        
	///////////////
	
}
                    
CString CPatchMnu::GetPatchMnuInfo(UINT i)
{
static char* Active[2] = {"  Active","InActive"};
static char* Current[2]= {"/Current",""};

//	Get Most Recent Active & Current Status
	UINT	nActive,nCurrent;
	
	nActive  = m_nPatchMnu[i][0];
	nCurrent = m_nPatchMnu[i][1];
	
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
			
void CPatchMnu::SetPatchMnuInfo(UINT i,UINT nType)
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
			m_nPatchMnu[i][0] = 0;
			break;
			
		case 2:         // make inactive /make it NONCurrent too
			m_nPatchMnu[i][0]           = 1;
			m_nPatchMnu[i][1]           = 1;     
			m_nPatchMnu[MAX_PATCHMNU-1][1] = 0;        // last PatchMnu current
			m_nCurrentPatchMnu          = MAX_PATCHMNU;   
			break;
			
		case 3:         // make current/ old current noncurrent
			UINT j;
			for(j=0;j<MAX_PATCHMNU;j++)
				if(m_nPatchMnu[j][1] == 0) 
					m_nPatchMnu[j][1] = 1;
			
			m_nPatchMnu[i][1]  = 0; 
			m_nCurrentPatchMnu = i;
			break;
			
		case 4:         // make noncurrent| make Last PatchMnu current
			m_nPatchMnu[i][1]           = 1; 
			m_nPatchMnu[MAX_PATCHMNU-1][1] = 0;        // last PatchMnu current
			m_nCurrentPatchMnu          = MAX_PATCHMNU;   
			break;
			
		case 5:			     // Toggle
			if(m_nPatchMnu[i][0] == 1)
				m_nPatchMnu[i][0] = 0;
			else
				m_nPatchMnu[i][0] = 1;
		default:
			break;
		}
		
		m_nPatchMnu[MAX_PATCHMNU-1][0]=0;     // Last PatchMnu always Active
		
}		

void CPatchMnu::GetPatchMnuIDArray(CString nID[])
{
	for(int i=0;i<MAX_PATCHMNU;i++)
		nID[i] = m_ID[i];
}
				
void CPatchMnu::SetPatchMnuIDArray(CString nID[])
{
	for(int i=0;i<MAX_PATCHMNU;i++)
		m_ID[i] = nID[i];
}	                 

void CPatchMnu::GetPatchMnuArray(UINT nPatchMnu[][2])
{
	for(int i=0;i<MAX_PATCHMNU;i++)
	{      
		for(int j=0;j<2;j++)
			nPatchMnu[i][j] = m_nPatchMnu[i][j];
	}
}
				
void CPatchMnu::SetPatchMnuArray(UINT nPatchMnu[][2])
{
	for(int i=0;i<MAX_PATCHMNU;i++)
	{      
		for(int j=0;j<2;j++)
			m_nPatchMnu[i][j] = nPatchMnu[i][j];
	} 
}	                 

void CPatchMnu::GetPatchMnuOldArray(UINT nPatchMnu[][2])
{
	for(int i=0;i<MAX_PATCHMNU;i++)
	{      
		for(int j=0;j<2;j++)
			nPatchMnu[i][j] = m_nPatchMnuOld[i][j];
	}
}
				
void CPatchMnu::SetPatchMnuOldArray(UINT nPatchMnu[][2])
{
	for(int i=0;i<MAX_PATCHMNU;i++)
	{      
		for(int j=0;j<2;j++)
			m_nPatchMnuOld[i][j] = nPatchMnu[i][j];
	} 
}	
void CPatchMnu::GetPatchMnuDefaultArray(UINT nPatchMnu[][2])
{
	for(int i=0;i<MAX_PATCHMNU;i++)
	{      
		for(int j=0;j<2;j++)
			nPatchMnu[i][j] = m_nPatchMnuDefault[i][j];
	}
}
				
void CPatchMnu::SetPatchMnuDefaultArray(UINT nPatchMnu[][2])
{
	for(int i=0;i<MAX_PATCHMNU;i++)
	{      
		for(int j=0;j<2;j++)
			m_nPatchMnuDefault[i][j] = nPatchMnu[i][j];
	} 
}	
////////////////////////////////// end of module //////////////////
