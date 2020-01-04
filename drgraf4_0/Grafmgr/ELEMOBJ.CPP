// ElemObj.cpp : implementation file
//


#include "drgraf.h"
#include "drgradoc.h"
#include "elglobal.h" 

#include "Elemobj.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CElemObj

IMPLEMENT_SERIAL(CElemObject,CObject,1)
/*
BEGIN_MESSAGE_MAP(CElemObject,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CElemObject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
////////////////////////////
CElemObject::CElemObject()
{
	/******* keywords ************************************/
	CString	ElementNames[] = {"",
    "NODE","PIPE","ELBOW","BEAM","SUPPORT","TRUSS","PLANE","PLATE","SHELL",
    "C","FIXFORMAT","FREEFORMAT","CNODE","END",
    "RIGIDSUP",
    "TSPRING","TSNUBBER",
    "RSPRING","RSNUBBER",
    "MASTER","PIPEPROP"
     };
	UINT	nElementNameCount  = sizeof(ElementNames)/sizeof(ElementNames[0]);
      
    for (int i=0;i<(int)nElementNameCount;i++) 
    	m_ElementNames[i] = ElementNames[i];
	m_nElementNameCount = nElementNameCount;
	////////////////////////////////////////
	m_nElementType = PIPE;   // PIPE 
	m_bElementMode = TRUE;
	m_bElementBox  = TRUE;    // Element Commands On
	/////////////////////////////////////////// Node     
	m_CurrentNodeID = "";
	m_AnchorNodeID  = "";

}

UINT CElemObject::GetLength(LPOINT3 WIC_I,LPOINT3 WIC_J)
{
	////////////////////////////////////////////////  Get Doc Info
	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc);
	CPrecision* pPrecision     = pDoc->GetPrecision();
	///////////////////////////////////////////////////////////////////   
		WORLD I,J;
		double wLength;

		I.x = (double)WIC_I.x;
		I.y = (double)WIC_I.y;
		I.z = (double)WIC_I.z;

		J.x = (double)WIC_J.x;
		J.y = (double)WIC_J.y;
		J.z = (double)WIC_J.z;
		
		wLength  = fabs((I.x * I.x) - (J.x * J.x) );
		wLength += fabs((I.y * I.y) - (J.y * J.y) );
		wLength += fabs((I.z * I.z) - (J.z * J.z) );
		wLength  = fabs(sqrt(wLength) );
		/////////////////////////////
    	long LLength = (long)wLength;
		///////////////////////////// DEScale it
///		pDoc->SCtoDS(&LLength);                   
		long  LWorldBase  = pPrecision->GetWorldBase();
		LLength /= LWorldBase;                    // Take out Precision 
		UINT nLength = (UINT) LLength;            // LOG/DeScaled
		///////////////
		return nLength;
		///////////////    
} 
// CElemObject serialization

void CElemObject::Serialize(CArchive& ar)
{

	
    //////////////////////////////////////
	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	BYTE b;
	WORD w;
	////////////////////
	if (ar.IsStoring())
	{
		TRACE(" Element	:Storing\n");	// TODO: add storing code here
		
    	ar	<</*BOOL*/	(BYTE)m_bElementBox
			<</*BOOL*/	(BYTE)m_bElementMode
			<</*int*/	(WORD)m_nElementType; 
	      
	}
	else
	{
		TRACE(" Element	:Loading\n");	// TODO: add loading code here

    	ar	>>/*BOOL*/	b;
    	m_bElementBox = (BOOL) b;
		ar	>>/*BOOL*/	b;
		m_bElementMode = (BOOL) b;
		ar	>>/*int*/	w;
		m_nElementType = (int) w; 
	      

	}
	
	///////////////////////////////////// 
	SerializeNode(ar);      
	SerializePipe(ar);
	//////////////////
	
}
///////////////////////////////////////////////////////// element serializer
void CElemObject::SerializeNode(CArchive& ar)
{ 
	///////////////////////////////////////////////////// STORING				
	if (ar.IsStoring())
	{
		ar	<<	m_CurrentNodeID
			<<	m_AnchorNodeID;
	}
	///////////////////////////////////////////////////// LOADING				
	else
	{
		ar	>>	m_CurrentNodeID
			>>	m_AnchorNodeID;
	}
				    				
}

int CDrPipe::PutEndIdsInPipeList(CString nid_I,CString nid_J)
{
   	if(nid_I == nid_J)       
   	{
		AfxMessageBox("Pipe has same Node IDs at both ends\n ZERO Length !!");
   		return -1;
	}			

    CObjectBase* pObjectBase;
    ///////////////////	
    CDrPipe		AddPipe;
//	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc); 
	int index,nIdLen,nRepeat;
	CString EndNids;  
	////////////////	
	nIdLen  = nid_I.GetLength();
	nRepeat = COMBO_NIDJ_LOC - (nIdLen + 1);   // no. of Blank Spaces 
	CString blank(' ',nRepeat);
	EndNids = nid_I + blank + nid_J; 
		
	/////////////////////////////////////////// already exists
   	if(( index = GetObjectIndexfromKey(EndNids,1))>=0)       
   	{
		AfxMessageBox("Pipe with these NodeIDs Already Exists !!");
   		return -1;
	}			
	else                                         // new Pipe
	{		
	    ///////////////////////////////// Create
		(AddPipe.GetPipeCard())->nid_i= nid_I;
		(AddPipe.GetPipeCard())->nid_j= nid_J;

   		pObjectBase->AddObject(&AddPipe);
		////////////////////////
	}			    		
	return 0; 
}

void CElemObject::SerializePipe(CArchive& ar)
{ 
	//////////////////////////////////////////////////// STORING				
	if (ar.IsStoring())
	{
		ar	<<	m_CurrentPipeID;
	}
	//////////////////////////////////////////////////// LOADING				
	else
	{
		ar	>>m_CurrentPipeID;
	}
					    				
}

////////////////////// End of Module ////////////////////


