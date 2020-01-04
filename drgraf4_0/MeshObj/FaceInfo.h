// Pipe.h : header file
//
#ifndef _FACEINFO_H
#define _FACEINFO_H       

//#include "DrFace.h"
/////////////////////////////////////////////////////////////////////////////
// CFaceInfo    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CFaceInfo: public CObject
{
public:
// Construction                 
	CFaceInfo();
	DECLARE_DYNAMIC(CFaceInfo);
	
	
// Operations
public:


	////////////////////////////////////////////////////////////////////// Members
	CObject*		GetDrFace(){return m_pDrFace;};		// oriented list of faces for 2D/3D Mesh
	void			SetDrFace(CObject* pFace){m_pDrFace = pFace;};
	UINT			GetFaceType(){return m_FaceType;};	// Type:TRUSS,BEAM (1D) etc. or 
															//	QUAD/TRI (2D) Elements
	void			SetFaceType(UINT u){m_FaceType = u;};
	///
	CObject*		GetGenObj(){return m_pGenObj;};		// DrObject:Mesh1D or Mesh2D or Mesh3D
	void			SetGenObj(CObject* pG){m_pGenObj = pG;};
	UINT			GetGenType(){return m_GenType;};	// Type:Mesh1D or Mesh2D or Mesh3D
	void			SetGenType(UINT u){m_GenType = u;};
	///
	UINT			GetFaceDim(){return m_FaceDim;};	// Face Element Dimension: 
										// 0D = BallJoint in Patch Form /1D(WireMesh)/2D
	void			SetFaceDim(UINT u){m_FaceDim = u;};
		



protected:
	
			
			
// Helper functions
protected:
// Attributes

	CObject*			m_pDrFace;	// oriented list of 1D/2D Elements for 2D/3D Mesh
	UINT				m_FaceType;	// Type:TRUSS,BEAM (1D) etc. or QUAD/TRI (2D) Elements
	UINT				m_FaceDim;	// Face Element Dimension: 
										// 0D = BallJoint in Patch Form /1D(WireMesh)/2D
	///
	CObject*			m_pGenObj;	// DrObject:Mesh1D or Mesh2D or Mesh3D
													// parallel to m_FaceList
	UINT				m_GenType;	// Type:Mesh1D or Mesh2D or Mesh3D
													//parallel to m_FaceList


public:
	virtual ~CFaceInfo();
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CFaceInfo)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



