// Pipe.h : header file
//
#ifndef _DREDGE_H
#define _DREDGE_H       

#include "DrObject.h"
#include "DrFE0D.h"
#include "FaceInfo.h"
/////////////////////////////////////////////////////////////////////////////
// CDrEdge    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrEdge: public CObject
{
public:
// Construction                 
	CDrEdge();
	DECLARE_SERIAL(CDrEdge);
	
	
// Operations
public:


	virtual void		Serialize(CArchive& ar);
	////////////////////////////////////////////////////////////////////// Members
	CString&		GetObjectID(){return ObjectID;};
	void			SetObjectID(CString& s){ObjectID = s;};
	int				GetVrtxIndex(int index){return m_VrtxIndex[index];};
	void			SetVrtxIndex(int iV,int index){m_VrtxIndex[index] = iV;};
	CDListMgr*		GetFaceInfoList(){return &m_FaceInfoList;}; 
	int				GetHist_RCH(){return m_nHist_RCH;};
	void			SetHist_RCH(int i){m_nHist_RCH = i;};	
	int				GetHistType(){return m_nHistType;};
	void			SetHistType(int i){m_nHistType = i;};	
	CDrObject*		GetMesh(){return m_pMesh;};		
	void			SetMesh(CDrObject* pM){m_pMesh = pM;};		
	UINT			GetMeshType(){return m_nGenType;};
	void			SetMeshType(UINT i){m_nGenType = i;};	
	BOOL			IsOnBndry(){return m_bOnBndry;};
	void			SetOnBndry(BOOL bBndry){m_bOnBndry = bBndry;};



protected:
	
			
			
// Helper functions
protected:
// Attributes

	CString				ObjectID;
	int					m_VrtxIndex[2];	// positive Orientation of vertices
											// indices of FE0DList in pMesh
	CDListMgr			m_FaceInfoList;	// oriented list of faces for 2D/3D Mesh
	////////////////////////////////////////// Mesh Manipulation
	// Note: m_nHistType = 1 means at s = m_nHist_RCH along s-diection, m_nHist_RCH-th edge 
	int					m_nHist_RCH;	// Row/Col/Hgt-index of the generating
											// Curve/Patch/Solid(-1 = Not On Generatrix)
	int					m_nHistType;	// 1=Row(S)/2=Col(T)/3=Hgt(R) for Quadrilat/Hexa
										// 1=Row(U)/2=Col(V)/3=Diag(W)/4=Hgt(R) for Tri/Penta/Tetra
	CDrObject*			m_pMesh;
	UINT				m_nGenType;
	int					m_bOnBndry;		// Is Edge On Bndry  : Global Processing
							

public:
	virtual ~CDrEdge();
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CDrEdge)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



