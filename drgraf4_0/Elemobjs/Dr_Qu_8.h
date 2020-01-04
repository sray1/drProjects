// Quad.h : header file
//
#ifndef _DR_QU_8_H
#define _DR_QU_8_H       


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrFE2D.h" 
/////////////////////////////////////////////////////////////////////////////
// CDr_Qu_8    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDr_Qu_8: public CDrFE2D
{
public:
// Construction                 
	CDr_Qu_8();
//////////////////////////////////////
	DECLARE_SERIAL(CDr_Qu_8);
//////////////////////////////////////
	
	
// Operations
public:

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
	//////////////////////////////////////////////////////////////
	virtual BOOL 		IsObjectHit(int nNet, POINT point);
	virtual BOOL 		IsKeyMatch(CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
    //////////////////////////////////////////////////////

	 
protected:
	
			void 		GoDoIt(CDC* PtrDC,BOOL bPenChange);
			
// Helper functions
protected:
// Attributes


	/////////////////////////////////


public:
	virtual ~CDr_Qu_8();
public:
};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



