#ifndef	_PO_FE1D_H_
#define	_PO_FE1D_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Str_Gen.h"
#include "DrObject.h"
#include "DrFE1D.h"
#include "Po_FE0D.h"
/////////////////////////////////////////////////////////////////////////////
// CPo_FE1D
/////////////////////////////////////////////////////////////////////////////
class CPo_FE1D : public CPo_FE0D
{
// Construction
public:  
	CPo_FE1D(){};
//////////////////////////////////////
	DECLARE_DYNAMIC(CPo_FE1D)
//////////////////////////////////////

protected: 
public:
// Implementation

	int					Post_FE1D(CDrFE1D* pAddEdge,CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],
												pWORLD LocalPos,CString& Eid);		
	int					FillData_1D(CDrFE1D* pNewObj,CDrObject* pMesh,UINT nGenType);
				  

public:

	////////////////////////////////////////////////////////////////////// Members
 	CString&			Getline_id(){return m_line_id;};
 	void				Setline_id(CString p){m_line_id = p;};
 	CString&			Getrid(int i){return m_rid[i];};
 	void				Setrid(CString p,int i){m_rid[i] = p;};
	//////////////////////////////////
	UINT				Getline_no(){return m_line_no;};		
	void				Setline_no(UINT u){m_line_no = u;};		
	UINT				Getrel(int i){return m_rel[i];};				
	void				Setrel(UINT u,int i){m_rel[i] = u;};			
	UINT				Getnumseg(){return m_numseg;};		
	void				Setnumseg(UINT u){m_numseg = u;};
   ////////////////////////////////////////////////////////////////////// helper
	virtual	POINT 		GetCenter(){return m_nCenter;};
	virtual	void		SetCenter(POINT ptCenter){m_nCenter = ptCenter;};
	//////////////////////////
	BOOL				IsOnBndry(){return m_bOnBndry;};
	void				SetOnBndry(BOOL b){m_bOnBndry = b;};

	/////////////////////////////////////////////////////////////////
	int					SetFE1DInfo(CDrFE1D* pFE1D,CDrFE0D* pVert[],CDrObject* pMesh,UINT nGenType,
																						int nEnds);

	int					Make_CentroidLabel_EDGE(CDrFE1D* pEdge,pWORLD LocalPos,CString& Eid);
	CDrNode*			Make_CentroidLabel(WORLD& LocalPos,CString& Eid);
	void				CalcCentroid_EDGE(pWORLD Local,pWORLD pC);
	void				CalcCentroid(pWORLD pCentroid,pWORLD Local,int nVert);


	
	
protected:

	/////////////////////////////////////////////////////////////////////
	// Note: 
		//	# of Vertex = 2 always;
		//	# of Nodes is Variable Based on ElementType;	 
	/////////////////////////////////////////////////////////////////////
	short		m_nNodes;			// intermediate + corner Nodes = ALL
	short		m_nEdgeDegree;		// 1 = Linear/ 2 = Quadratic etc
	//////////////////////////////////
	CString		m_line_id;
	CString		m_rid[MAX_CORNERS_1D];//
	//////////////////////////////////
	UINT		m_line_no;
	UINT		m_rel[MAX_CORNERS_1D]; 
	UINT		m_numseg;				//
	////////////////////////////// 
	POINT 		m_nCenter; 
	///////////////////////
	BOOL		m_bOnBndry;
	/////////////////////////////////////////// Fe1DIn_Dlg
//	BOOL		m_bValve;
//	CString		m_stressID_I;
//	CString		m_stressID_J;
//	CString		m_KNodeID;
	////////////////////////

public:
	virtual ~CPo_FE1D(){};
/*
	// Generatioed message map functions
	//{{AFX_MSG(CPo_FE1D)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif

