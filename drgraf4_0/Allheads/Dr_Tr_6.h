//Tri.h : header file
//
#ifndef _DR_TR_6_H
#define _DR_TR_6_H       


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrFE2D.h" 
/////////////////////////////////////////////////////////////////////////////
// CDr_Tr_6    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDr_Tr_6: public CDrFE2D
{
public:
// Construction                 
	CDr_Tr_6();
//////////////////////////////////////
	DECLARE_SERIAL(CDr_Tr_6);
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
	virtual ~CDr_Tr_6();
public:
};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



