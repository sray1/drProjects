#ifndef	_CURTOPO_H_
#define	_CURTOPO_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include <afxtempl.h>	// CList

#include "DListMgr.h"
#include "Def_Type.h"
/////////////////////////////////////////////////////////////////////////////
// CCurTopo
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CCurTopo : public CObject
{
// Construction
public:  
	CCurTopo();
//////////////////////////////////////
	DECLARE_DYNAMIC(CCurTopo)
//////////////////////////////////////
public:


	virtual BOOL		IsSubDivided(){return m_bSubDivided;};	// Subdivided?
	virtual void		SetSubDivided(BOOL b){m_bSubDivided = b;};	// Subdivided?
	virtual int			GetSubTriangleIndex(int i){return m_SubTriangleIndex[i];}; 
	virtual void		SetSubTriangleIndex(int Tindex, int i){m_SubTriangleIndex[i]= Tindex;};
	///////////////////////////////////////////////////////////////////////////////////////////
	virtual int			GetType(){return m_Type;};
	virtual void 		SetType(int pM){m_Type = pM;};

			int			GetLinearIndex(int i, int j, int k, int nDeg);
			void		GetIJK(pINT i, pINT j, pINT k, int LIndex, int nDeg);
	////////////////////////////////////////////////
	virtual CList<int,int>*		GetCNIndexList(){return &m_CNIndices;};

	virtual int			GetPatIndex(){return m_PatIndex;};
	virtual void 		SetPatIndex(int pM){m_PatIndex = pM;};

	virtual int			GetDegree(){return m_nDegree;};
	virtual void 		SetDegree(int pM){m_nDegree = pM;};

	virtual int			GetVertexIndex(int n){return m_VtxIndex[n];};
	virtual void		SetVertexIndex(int i,int n){m_VtxIndex[n] = i;};
	virtual pINT		GetVertexIndex(){return m_VtxIndex;};

	virtual int			GetNebrVertexIndex(int n){return m_NebrVtxIndex[n];};
	virtual void		SetNebrVertexIndex(int i,int n){m_NebrVtxIndex[n] = i;};
	virtual pINT		GetNebrVertexIndex(){return m_NebrVtxIndex;};

	virtual int			GetNebrTriangleIndex(int n){return m_NebrTriIndex[n];};
	virtual void		SetNebrTriangleIndex(int i,int n){m_NebrTriIndex[n] = i;};
	virtual pINT		GetNebrTriangleIndex(){return m_NebrTriIndex;};

						////////////////////////////////////////////////////////// Output
	virtual int			GetOutSeg(){return m_nOutSeg;};
	virtual void 		SetOutSeg(int pM){m_nOutSeg = pM;};

	virtual int			GetiOutGlo(){return m_iOutGlo;};
	virtual void 		SetiOutGlo(int pM){m_iOutGlo = pM;};
	virtual int			GetjOutGlo(){return m_jOutGlo;};
	virtual void 		SetjOutGlo(int pM){m_jOutGlo = pM;};





	
protected:


	BOOL		m_bSubDivided;			// Subdivided?
	int			m_SubTriangleIndex[3];
	int			m_Type;					// 1=left or 2=right
	//////////////////////////////////////
	int			m_PatIndex;				// Triangle Index in the Patch
	int			m_nDegree;				// Overall Degree of Triangle
	int			m_VtxIndex[10];			// Vertex indices from Tringulation
										// Triangle# for Cubic = 10 (Array Dimension Max for Cubic)
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
	int			m_nOutSeg;
	int			m_iOutGlo;				// global Barycentric i for the Ist pt of triangle 
	int			m_jOutGlo;				// global Barycentric j for the Ist pt of triangle
	
public:
	virtual ~CCurTopo(){};
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif	// _CURTOPO_H_
