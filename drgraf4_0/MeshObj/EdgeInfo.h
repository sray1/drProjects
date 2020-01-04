// Pipe.h : header file
//
#ifndef _EDGEINFO_H
#define _EDGEINFO_H       

//#include "DrFace.h"
/////////////////////////////////////////////////////////////////////////////
// CEdgeInfo    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CEdgeInfo: public CObject
{
public:
// Construction                 
	CEdgeInfo();
	DECLARE_DYNAMIC(CEdgeInfo);
	
	
// Operations
public:


	////////////////////////////////////////////////////////////////////// Members
	CObject*		GetDrEdge(){return m_pDrEdge;};		// oriented list of faces for 2D/3D Mesh
	CObject*		GetGenObj(){return m_pGenObj;};		// DrObject:Mesh1D or Mesh2D or Mesh3D
	UINT			GetGenType(){return m_GenType;};	// Type:Mesh1D or Mesh2D or Mesh3D
	///		
	BOOL			IsOnBndry(){return m_bOnBndry;};
	void			SetOnBndry(BOOL b){m_bOnBndry = b;};
	BOOL			IsPositive(){return m_bPositive;};
	void			SetPositive(BOOL b){m_bPositive = b;};



protected:
	
			
			
// Helper functions
protected:
// Attributes

	CObject*			m_pDrEdge;
	///////////////////////
	BOOL				m_bOnBndry;
	BOOL				m_bPositive;
	///
	CObject*			m_pGenObj;	// DrObject:Mesh1D or Mesh2D or Mesh3D
													// parallel to m_FaceList
	UINT				m_GenType;	// Type:Mesh1D or Mesh2D or Mesh3D
													//parallel to m_FaceList


public:
	virtual ~CEdgeInfo();
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CEdgeInfo)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



