#ifndef	_PENTAHED_H_
#define	_PENTAHED_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include <afxtempl.h>

#include "DListMgr.h"
#include "Def_Type.h"
/////////////////////////////////////////////////////////////////////////////
// CPentaHed
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CPentaHed : public CObject
{
// Construction
public:  
	CPentaHed();
//////////////////////////////////////
	DECLARE_DYNAMIC(CPentaHed)
//////////////////////////////////////
public:


	virtual int			GetType(){return m_Type;};
	virtual void 		SetType(int pM){m_Type = pM;};

			int			GetLinearIndex(int i, int j, int k, int nDeg);
			void		GetIJK(pINT i, pINT j, pINT k, int LIndex, int nDeg);
	////////////////////////////////////////////////
	virtual CList<int,int>*		GetCNIndexList(){return &m_CNIndices;};

	virtual int			GetSolIndex(){return m_SolIndex;};
	virtual void 		SetSolIndex(int pM){m_SolIndex = pM;};

	virtual int			GetDegree_ST(){return m_nDegree_ST;};
	virtual void 		SetDegree_ST(int pM){m_nDegree_ST = pM;};
	virtual int			GetDegree_R(){return m_nDegree_R;};
	virtual void		SetDegree_R(int n){m_nDegree_R = n;};

	virtual int			GetVertexIndex(int n){return m_VtxIndex[n];};
	virtual void		SetVertexIndex(int i,int n){m_VtxIndex[n] = i;};
	virtual pINT		GetVertexIndex(){return m_VtxIndex;};

	virtual int			GetNebrVertexIndex(int n){return m_NebrVtxIndex[n];};
	virtual void		SetNebrVertexIndex(int i,int n){m_NebrVtxIndex[n] = i;};
	virtual pINT		GetNebrVertexIndex(){return m_NebrVtxIndex;};

	virtual int			GetNebrPentaHedIndex(int n){return m_NebrTriIndex[n];};
	virtual void		SetNebrPentaHedIndex(int i,int n){m_NebrTriIndex[n] = i;};
	virtual pINT		GetNebrPentaHedIndex(){return m_NebrTriIndex;};
						////////////////////////////////////////////////////////// Output
	virtual int			GetOutStartIndex(){return m_OutStartIndex;};
	virtual void 		SetOutStartIndex(int pM){m_OutStartIndex = pM;};
	virtual int			GetOutSeg_S(){return m_nOutSeg_S;};
	virtual void 		SetOutSeg_S(int pM){m_nOutSeg_S = pM;};
	virtual int			GetOutSeg_R(){return m_nOutSeg_R;};
	virtual void 		SetOutSeg_R(int pM){m_nOutSeg_R = pM;};

	virtual int			GetiOutGlo_ST(){return m_iOutGlo_ST;};
	virtual void 		SetiOutGlo_ST(int pM){m_iOutGlo_ST = pM;};
	virtual int			GetjOutGlo_ST(){return m_jOutGlo_ST;};
	virtual void 		SetjOutGlo_ST(int pM){m_jOutGlo_ST = pM;};

	
protected:

	int			m_Type;					// Base Triangle:
										//	1=left or 2=right
	//////////////////////////////////////
	int			m_SolIndex;				// PentaHed Index in the Patch
	int			m_nDegree_ST;			// Overall Degree of PentaHed in ST plane
	int			m_nDegree_R;			// Overall Degree of PentaHed in R-dir
	int			m_VtxIndex[6];			// Vertex indices from Tringulation :
										// Needs to be Changed for Quad & Cubic Bezier
	// todo: Provision based on cubic triangle#
	int			m_NebrVtxIndex[3];		// Neighboring Vertex indices from Tringulation
	int			m_NebrTriIndex[3];		// Neighboring Tringle Index in the list
/*
	CDListMgr	m_CNodeList;			// Bezier Control Nodes ( Linearly Stored): TRINGLE NUMBER
										//		Tringle Number = (degree+1)*(degree+2)/2
										//		Actual Number depends on Degree:
										//		Linear(degree 1):	3 Nodes
										//		Quad(degree 2):		6 Nodes
										//		Cubic(degree 3):	10 Nodes,	etc.
*/
	CList<int,int>	m_CNIndices;		// Bezier Control Nodes indices in m_pCNodeList
										// and for Wts
										// Total Objects depends on TRINGLE NUMBER as
										// computed from nDegree
	////////////////////////////////////////////////////////////////////////////////
	// Relation between Linear Storage and u,v indices:
	//
	//			#define BARY2LIN_PT(u,v,nP)		(v)  + (u)*(nP)-(u)*((u)-1)/2
	//			#define BARY2LIN_TRI_1(u,v,nP)	(v)  + (u)*(2*(nP)-(u)-2)
	//			#define BARY2LIN_TRI_2(u,v,nP)	(v)  + (u)*(2*(nP)-(u)-2) - (nP) + (u)
	//////////////////////////////////////////////////////////////////////////////// Output
  	int			m_OutStartIndex;		// Starting Index for this PentaHed in
										// m_pOut & m_pOutWts for Bottom Triangle
										// Total length depends on TRINGLE NUMBER as
										// computed from nOutSeg
	int			m_nOutSeg_S;
	int			m_nOutSeg_R;
	int			m_iOutGlo_ST;			// global Barycentric i for the base triangle 
	int			m_jOutGlo_ST;			// global Barycentric j for the base triangle

	
public:
	virtual ~CPentaHed(){};
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif	// _PentaHed_H_
