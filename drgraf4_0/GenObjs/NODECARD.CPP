// NodeCard.cpp : implementation of the CNodeCard class
//

#include "NodeCard.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CNodeCard

IMPLEMENT_SERIAL(CNodeCard,CCardMgr,1)
/*
BEGIN_MESSAGE_MAP(CNodeCard,CCardMgr)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CNodeCard)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////
CNodeCard::CNodeCard()
{
} 

void CNodeCard::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	WORD w;
	/////// 
	if (ar.IsStoring())
	{
		TRACE(" NodeCard:    Storing\n");	// TODO: add storing code here
		
		///////////////////////////////////
/*		
		ar	<<	(WORD)m_nSearchNet
			<<	(WORD)m_nSearchNetOld                                       	
			<<	(WORD)m_nSearchNetDefault;    
*/
	}
	else
	{
		TRACE(" NodeCard:    Loading\n");	// TODO: add loading code here

		/////////////////////////////////// 
/*		
		ar	>>	w;
		m_nSearchNet	 	= (int) w; 
		ar	>>	w;
		m_nSearchNetOld	 	= (int) w; 
		ar	>>	w;
		m_nSearchNetDefault	= (int) w;
*/		 

	}        
	///////////////
	
}

/////////////////////////////////////////////////////////////////// Helpers
void CNodeCard::ParseCard(CDrNode* pNode)
{

	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc);
	CElemObject* pElDoc        = pDoc->GetElementDoc(); 
	CPrecision* pPrecision     = pDoc->GetPrecision();
	CScaleFactor* pScaleFactor = pDoc->GetScaleFactor();
	CMapFactor* pMapFactor     = pDoc->GetMapFactor(); 
	//////////////////////////////////////////////////// Update Current Node
	LONG  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase;
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	///////////////////////////////////////////
	(pNode->GetNodeCard())->id 		= m_id;	
	(pNode->GetNodeCard())->sup_id	= m_sup_id;
	(pNode->GetNodeCard())->nid_r 	= m_nid_r;
	//////////////////////// strip World Coord
	pScaleFactor->SCtoDS(&m_xWorld);
	pScaleFactor->SCtoDS(&m_yWorld);
	pScaleFactor->SCtoDS(&m_zWorld);
    ////////////////////////
	(pNode->GetNodeCard())->x 		= (long) (m_xWorld*dWorldBase/dMapFactor );	
	(pNode->GetNodeCard())->y 		= (long) (m_yWorld*dWorldBase/dMapFactor );	
	(pNode->GetNodeCard())->z 		= (long) (m_zWorld*dWorldBase/dMapFactor );
	//////////////////////////////////////////	
	(pNode->GetNodeCard())->bnid_c 	= m_bnid_c; 
    
	///////////////////////////////
	return;
} 

          case 4: /* NODE */
          case 5: /* CNODE */
            if(Max_Nodes>=MAX_NODES) {
               OpenErrorMessage("NODE/CNODE data area overflow.");
               return(0);
            }
            if(ReadStr(b,&bp,Node_Table[Max_Nodes].id,5)==0)
               return(0);
            if(ReadNum(b,&bp,&(Node_Table[Max_Nodes].x))==0) 
               return(0);
            if(ReadNum(b,&bp,&(Node_Table[Max_Nodes].y))==0) 
               return(0);
            if(ReadNum(b,&bp,&(Node_Table[Max_Nodes].z))==0) 
               return(0);
            if(ReadStr(b,&bp,Node_Table[Max_Nodes].nid_r,5)==0)
               return(0);
            if(ReadStr(b,&bp,Node_Table[Max_Nodes].sup_id,5)==0)
               return(0);
            Node_Table[Max_Nodes].data[0]=(i==5) ? 1:0;
            Node_Table[Max_Nodes].show=1;
            Max_Nodes++;
            break;
}

void CNodeCard::PackCard(CDrNode* pNode)
{

WriteDataFile(fh)
int fh;
{
    int i,j;
    char t[CARD_SIZE],tt[MAXSTRINGLENGTH];
    static char pad[]=" ";   
    
    /**** Nodes/Cnodes *****/
   if(Max_Nodes>0) 
   {
    WriteLine(fh,"");
    sprintf(t,"C,, NODES & CNODES :%d",Max_Nodes);
    WriteLine(fh,t);
    WriteLine(fh,"C,,       |ID---|---------X|---------Y|---------Z|REFID|SUPID|");
    for(i=0;i<Max_Nodes;i++) 
      if(Node_Table[i].show) {
        t[0]=0;
        if(Node_Table[i].data[0])
          AddStr(t,"CNODE",10);
        else
          AddStr(t,"NODE",10);
        AddStr(t,Node_Table[i].id,5);
        AddNum(t,Node_Table[i].x);
        AddNum(t,Node_Table[i].y);
        AddNum(t,Node_Table[i].z);
        AddStr(t,Node_Table[i].nid_r,5);
        if(strcmp(Node_Table[i].sup_id,RIGID)==0)
           AddStr(t,pad,5);
        else
           AddStr(t,Node_Table[i].sup_id,5);
        t[strlen(t)-1]=0;
        WriteLine(fh,t);
    }
}

////////////////////////////////// end of module //////////////////
