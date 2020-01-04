// Force & Moment.h : header file
//
#ifndef _DRPRS_H
#define _DRPRS_H       


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h"
#include "DListMgr.h" 
#include "Def_Type.h"
#include "Def_CuPS.h"
#include "DrNode.h" 
#include "DrLabel.h" 
//////////////////// 
// CDrPrs    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrPrs: public CDrObject
{
///////////////////////////////////////////////////
public:
// Construction                 
	CDrPrs();
//////////////////////////////////////
	DECLARE_SERIAL(CDrPrs);
//////////////////////////////////////
	
	
// Operations
public:

	virtual	void 		ReadyToDelete();
	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	virtual int			GetCardNo(){return m_nCardNo;};
	virtual void		SetCardNo(int nCardNo){m_nCardNo = nCardNo;}; 
	////////////////////////////////////////////////
	// overrides of virtuals in CDrObject;
	virtual void		DoDataView(CDC* PtrDC, int y);
	virtual void 		DoDrawView(CDC* PtrDC,BOOL bPenChange);
	virtual void		InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
					 		pMATRIX pViewM,pMATRIX pvv3DM,double dzMin,
							double dScale_U,double dScale_V);
	virtual void		SetObjectInfo(CDrObject* pObject);
	virtual void 		GetObjectInfo(CDrObject* pObject);
	virtual int 		DealObjectDialog();
	//////////////////////////////////////////////////////////////
	virtual	void 		TransformObjectToWorld(pMATRIX pLM,BOOL bYes);
	virtual	void 		TransformObjectToView(pMATRIX pViewM);
	virtual void		TransformObjectToViewDirect
							(pMATRIX pLM,pMATRIX pViewM,pMATRIX pComposedM,BOOL bYes);
	virtual	BOOL 		RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType);
	virtual	void 		ProjectObject
							(pMATRIX pvv3DM,double dScale_U,double dScale_V);
	virtual void 		FinishObject();
	virtual BOOL 		IsObjectHit(int nNet,POINT point);
	virtual BOOL 		IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
    ////////////////////////////////////////////////////////////////////// 
	virtual	CDrNode*	GetLabelNode(){return m_pLabelNode;};	// use when new Transformation
	virtual void		SetLabelNode(CDrNode* ptr){m_pLabelNode = ptr;};
	virtual	CDrLabel*	GetLabelPtr(){return m_pLabel;};	// use when new Transformation
	virtual void		SetLabelPtr(CDrLabel* ptr){m_pLabel = ptr;};
	virtual long 		GetLabelNo(){return m_nLabelNo;}; 
	virtual void		SetLabelNo(long nNo){ m_nLabelNo = nNo;};
	/////////////////////////////////////////////////////////////
	virtual pMATRIX		GetLocalM(){return &m_LocalM;}; 
	virtual void		SetLocalM(pMATRIX pM){m_LocalM = *pM;};

	virtual CString&	GetLoadID(){return m_LoadID;}; 
	virtual void		SetLoadID(CString& i){ m_LoadID = i;};

	virtual COLORREF	GetColor(){return m_Color;}; 
	virtual void		SetColor(COLORREF f){ m_Color = f;};

	virtual WORLD		GetForce(){return m_Force;}; 
	virtual void		SetForce(WORLD f){ m_Force = f;};

	virtual WORLD		GetMoment(){return m_Moment;}; 
	virtual void		SetMoment(WORLD f){ m_Moment = f;};

	virtual BYTE 		Getkode(int i){return m_kode[i];}; 
	virtual void		Setkode(int i,BYTE nNo){ m_kode[i] = nNo;};

	virtual int			GetnPts(int i){return m_nPts[i];};
	virtual pWORLD		GetpLoc(int i){return m_pLoc[i];};
	//////////////////////////////////////////////////////
			void		InitRawData();

	 
protected:
	
	
			void 		TransformToWorldPos(pMATRIX pLM,BOOL bYes);
			void		TransformToEyePosDirect
							(pMATRIX pLM,pMATRIX pViewM,pMATRIX pComposedM,BOOL bYes);
			void 		TransformToEyePos(pMATRIX pViewM);
			void 		ProjectToScreenPos
							(pMATRIX pvv3DM,double dScale_U,double dScale_V);
			int			Calc_3DBoundsLocal(pWORLD pOut, int nPts);
			void 		Calc_ScreenRectFromCNodes();
			void		Rearrange2DCorners();
			void 		GoDoIt(CDC* PtrDC,int direction);
			void		GoConnect_Force(CDC* PtrDC);
			void		GoConnect_Moment(CDC* PtrDC);
			/////////////////////////////////////////////////////////////////////// Prepare
			void		GetApproPts(WORLD pOut[],
									int nPts,int direction);
			int			GetApproDataLen(int direction);

		
// Helper functions
protected:
// Attributes
 
	
	CDrNode*	m_pLabelNode;	// LabelNode
	CDrLabel*	m_pLabel;
	//////////////////////////
	MATRIX		m_LocalM;	// Local Transformation
	///////////////////////////
	int			m_IDNum; // 0 = Force
	CString		m_LoadID;
	WORLD		m_Force;
	WORLD		m_Moment;
	/////////////////////////// Bounding Corners
	BOOL		m_bDoneXform;
	BOOL		m_bDoneProject;
	///////////////////////////
	int			m_nCardNo;
	/////////////////////////// Current
	int			m_CurDir;
	BYTE		m_kode[2];
	int			m_nPts[2];
	pWORLD		m_pLoc[2];// stores Local  and then Translated to NodePos	
	pWORLD		m_pEye[2];// EyePos also stores WorPos
	/////////////////////////// Smart Paint
	WORLD		m_dMin;
	WORLD		m_dMax;

public:
	virtual ~CDrPrs();
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CDrPrs)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



