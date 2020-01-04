 // ELMouse.h : header file
//
#ifndef _TWIST_H 
#define _TWIST_H 


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
//class AFX_EXT_CLASS CTwist : public CMI_Cur_I
class AFX_EXT_CLASS CTwist : public CObject
{
public:

	CTwist();
//////////////////////////////////////
	DECLARE_DYNAMIC(CTwist)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 
	////////////////////////////////////////////
	int		Zero(PWMAT2 CornerTwist);
	int		Bessel
			(
				CDListMgr* pNodeList,CList<double,double>* pWtList,
				int n_Nodes_U,int n_Nodes_V,PWMAT2 CornerTwist
			);		
	int		Adini
			(
				CDListMgr* pNodeList,CList<double,double>* pWtList,
				int n_Nodes_U,int n_Nodes_V,PWMAT2 CornerTwist,
				CList<WORLD,WORLD>& EndTanList_U,CList<WORLD,WORLD>& EndTanList_V
			);		
	int		Spline
			(
				CDListMgr* pNodeList,CList<double,double>* pWtList,
				int n_Nodes_U,int n_Nodes_V,PWMAT2 CornerTwist,
				CList<WORLD,WORLD>& EndTanList_U,CList<WORLD,WORLD>& EndTanList_V
			);		
	int		Energy
			(
				CDListMgr* pNodeList,CList<double,double>* pWtList,
				int n_Nodes_U,int n_Nodes_V,PWMAT2 CornerTwist
			);		
	//////////////////////////////////////////////////////////////////// Reparametrize
	
protected:
	
   



//Operations
public:

	~CTwist();
/*
	// Generated message map functions

	//{{AFX_MSG(CTwist)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
