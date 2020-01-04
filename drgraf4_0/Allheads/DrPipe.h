// Pipe.h : header file
//
#ifndef _DRPIPE_H
#define _DRPIPE_H       

#include "Str_Gen.h" 
#include "DrFE1D.h" 
/////////////////////////////////////////////////////////////////////////////
// CDrPipe    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrPipe: public CDrFE1D
{
public:
// Construction                 
	CDrPipe();
	DECLARE_SERIAL(CDrPipe);
	
	
// Operations
public:

	virtual	void 		ReadyToDelete();
	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	virtual void		Parse_drPipe(CString* pstrCard){};                    //  TOBE DONE
	////////////////////////////////////////////////
	// overrides of virtuals in CDrObject;
	// for DECKVIEW
	virtual	void		DoFormattedCardView(CString* pstrCard,CString& strFmt);
	virtual	void		DoUnFormattedCardView(CString* pstrCard);
	///
	virtual void		DoDataView(CDC* PtrDC, int y);
	virtual void 		DoDrawView(CDC* PtrDC,BOOL bPenChange);
	virtual void		InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
					 		pMATRIX pViewM,pMATRIX pvv3DM,double dzMin,
							double dScale_U,double dScale_V);
	virtual void		SetObjectInfo(CDrObject* pObject);
	virtual void 		GetObjectInfo(CDrObject* pObject);
	virtual int 		DealObjectDialog();
	////////////////////////////////////////// for projection
	virtual int			GetMaxCorners(){return (int)MAX_CORNERS_1D;};
	//////////////////////////////////////////////////////////////
	virtual	void 		TransformObjectToWorld(pMATRIX pLM,BOOL bYes);
	virtual	void 		TransformObjectToView(pMATRIX pViewM);
	virtual	BOOL 		RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType);
	virtual	void 		ProjectObject
							(pMATRIX pvv3DM,double dScale_U,double dScale_V);
	virtual	void 		FinishObject();
	virtual BOOL 		IsObjectHit(int nNet,POINT point);
	virtual BOOL 		IsKeyMatch(CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
	////////////////////////////////////////////////////////////////////////////
	CString&			GetSIid(int i){return m_SIid[i];};
 	void				SetSIid(CString p,int i){m_SIid[i] = p;};
	BOOL 				IsValve(){return m_bValve;};
	void 				SetValve(BOOL b){m_bValve = b;};



protected:
	
			void 		TransformToWorldPos(pMATRIX pLM,BOOL bYes);
			void 		TransformToEyePos(pMATRIX pViewM);
			void 		ProjectToScreenPos
							(pMATRIX pvv3DM,double dScale_U,double dScale_V);
			void 		Calc_ScreenRectFromCNodes();
			void 		GoDoIt(CDC* PtrDC,BOOL bPenChange);
			
			
// Helper functions
protected:
// Attributes
 

	CString		m_SIid[MAX_CORNERS_1D];//
	BOOL		m_bValve;
	///////////////////////////////// Render

public:
	virtual ~CDrPipe();
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CDrPipe)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#undef AFX_DATA
#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



