// CHitNet.h : header file
//
#ifndef _HITNET_H
#define _HITNET_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h" 
/////////////////////////////////////////////////////////////////////////////
// CHitNet
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CHitNet : public CDrObject
{
// Construction
public:  
	CHitNet();

	DECLARE_SERIAL(CHitNet)


protected: 
public:
// Implementation
public:
	
	///////////////////////////////////////////////////// EXPORTS needed for DLL
	virtual void	DoDataView(CDC* PtrDC, int y);
	virtual int 	GetObjectType(){return m_nObjectType;};
	virtual void	SetObjectType(int nType){m_nObjectType = nType;};
	virtual int 	GetElemType(){return m_nElemType;};
	virtual void	SetElemType(int nType){m_nElemType = nType;};
	virtual long 	GetObjectNo(){return m_nObjectNo;}; 
	virtual void	SetObjectNo(long nNo){ m_nObjectNo = nNo;};
	virtual void	Pack_drPipe(CString* pstrCard);
	virtual void 	GetObjectInfo(CDrObject* pObject);
	virtual void 	SetObjectInfo(CDrObject* pObject);
	/////////////////////////////////////////////////////////////////////// hitnet
	int			GetSearchNet(){return m_nSearchNet;};
	void		SetSearchNet(int nNet){ m_nSearchNet = nNet;};
	int			GetSearchNetOld(){return m_nSearchNetOld;};
	void		SetSearchNetOld(int nNet){ m_nSearchNetOld = nNet;};
	int			GetSearchNetDefault(){return m_nSearchNetDefault;};
	void		SetSearchNetDefault(int nNet){ m_nSearchNetDefault = nNet;};

	double		GetSearchDet(){return m_dSearchNet;};
	void		SetSearchDet(double Net){ m_dSearchNet = Net;};
	double		GetSearchDetOld(){return m_dSearchNetOld;};
	void		SetSearchDetOld(double Net){ m_dSearchNetOld = Net;};
	double		GetSearchDetDefault(){return m_dSearchNetDefault;};
	void		SetSearchDetDefault(double Net){ m_dSearchNetDefault = Net;};

	double		GetDblRatio(){return m_dDblRatio;};
	void		SetDblRatio(double Net){ m_dDblRatio = Net;};
	double		GetDblRatioOld(){return m_dDblRatioOld;};
	void		SetDblRatioOld(double Net){ m_dDblRatioOld = Net;};
	double		GetDblRatioDefault(){return m_dDblRatioDefault;};
	void		SetDblRatioDefault(double Net){ m_dDblRatioDefault = Net;};

	double		GetCoLinear(){return m_dCoLinear;};
	void		SetCoLinear(double Net){ m_dCoLinear = Net;};
	double		GetCoLinearOld(){return m_dCoLinearOld;};
	void		SetCoLinearOld(double Net){ m_dCoLinearOld = Net;};
	double		GetCoLinearDefault(){return m_dCoLinearDefault;};
	void		SetCoLinearDefault(double Net){ m_dCoLinearDefault = Net;};

	double		GetCoPlanar(){return m_dCoPlanar;};
	void		SetCoPlanar(double Net){ m_dCoPlanar = Net;};
	double		GetCoPlanarOld(){return m_dCoPlanarOld;};
	void		SetCoPlanarOld(double Net){ m_dCoPlanarOld = Net;};
	double		GetCoPlanarDefault(){return m_dCoPlanarDefault;};
	void		SetCoPlanarDefault(double Net){ m_dCoPlanarDefault = Net;};

	double		GetMergeNode_X(){return m_dMergeNode_X;};
	void		SetMergeNode_X(double Net){ m_dMergeNode_X = Net;};
	double		GetMergeNode_XOld(){return m_dMergeNode_XOld;};
	void		SetMergeNode_XOld(double Net){ m_dMergeNode_XOld = Net;};
	double		GetMergeNode_XDefault(){return m_dMergeNode_XDefault;};
	void		SetMergeNode_XDefault(double Net){ m_dMergeNode_XDefault = Net;};

	double		GetMergeNode_Y(){return m_dMergeNode_Y;};
	void		SetMergeNode_Y(double Net){ m_dMergeNode_Y = Net;};
	double		GetMergeNode_YOld(){return m_dMergeNode_YOld;};
	void		SetMergeNode_YOld(double Net){ m_dMergeNode_YOld = Net;};
	double		GetMergeNode_YDefault(){return m_dMergeNode_YDefault;};
	void		SetMergeNode_YDefault(double Net){ m_dMergeNode_YDefault = Net;};

	double		GetMergeNode_Z(){return m_dMergeNode_Z;};
	void		SetMergeNode_Z(double Net){ m_dMergeNode_Z = Net;};
	double		GetMergeNode_ZOld(){return m_dMergeNode_ZOld;};
	void		SetMergeNode_ZOld(double Net){ m_dMergeNode_ZOld = Net;};
	double		GetMergeNode_ZDefault(){return m_dMergeNode_ZDefault;};
	void		SetMergeNode_ZDefault(double Net){ m_dMergeNode_ZDefault = Net;};
	////////////////////////
	void 		ReadDefaultHitNet();
	void 		InitHitNet();
	

protected: 

	int			m_nElemType;	
	int			m_nObjectType;
	long		m_nObjectNo;
	///////////////////////////////////////// Hitnet
	int			m_nSearchNet;
	int 		m_nSearchNetOld;
	int			m_nSearchNetDefault;
	double		m_dSearchNet;
	double 		m_dSearchNetOld;
	double		m_dSearchNetDefault;
	////////////////////////////////
	double		m_dDblRatio;		//TOL_DOUBLE_RATIO,	//	.01		// 1%
	double 		m_dDblRatioOld;
	double		m_dDblRatioDefault;
	///////////////////////////////
	double		m_dCoLinear;		//TOL_COLINEAR,		//	.99	
											// within 1% (Dot product) should be 1.0,if Colinear
	double 		m_dCoLinearOld;
	double		m_dCoLinearDefault;
	///////////////////////////////
	double		m_dCoPlanar;		//TOL_COPLANAR		//	.01
											// 1% (distance of 4th point from plane)
	double 		m_dCoPlanarOld;
	double		m_dCoPlanarDefault;
	///////////////////////////////
	double		m_dMergeNode_X;		//TOL_MERGENODE_X
	double 		m_dMergeNode_XOld;
	double		m_dMergeNode_XDefault;
	double		m_dMergeNode_Y;		//TOL_MERGENODE_Y
	double 		m_dMergeNode_YOld;
	double		m_dMergeNode_YDefault;
	double		m_dMergeNode_Z;		//TOL_MERGENODE_Z
	double 		m_dMergeNode_ZOld;
	double		m_dMergeNode_ZDefault;

protected: 

public:
	virtual ~CHitNet(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CHitNet)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
