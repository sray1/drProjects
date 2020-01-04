// DrFont.cpp : implementation of the CDrFont class
//
#include "stdafx.h"

#include "Def_Type.h"
#include "Def_Objs.h"
/////////////////////
#include "Ext_Spec.h"
#include "Def_Spec.h"

#include "DrFont.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrFont

IMPLEMENT_SERIAL(CDrFont,CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CDrFont,CDrObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CDrFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////
 
CDrFont::CDrFont()
{
    SetObjectType((int)DRFONT);
    SetElemType((int)SPEC_OBJECT);          //  
} 

void CDrFont::ReadDefaultDrFont()
{
}

void CDrFont::InitDrFont()
{

	////////////////////////////////////////////////////// Font/TextColor
    CFont* pFont = AfxGetApp()->m_pMainWnd->GetFont();
    LOGFONT lf;
	if (pFont != NULL)
	   pFont->GetObject(sizeof(LOGFONT), &lf);
   	else
	   ::GetObject(GetStockObject(SYSTEM_FONT), sizeof(LOGFONT), &lf);
	SetCurrentLogFont(lf);
	SetTextColor(RGB(0,255,0)); // default Green
    ////////////////
}
	
void CDrFont::SetObjectInfo(CDrObject* pObject)
{
	
	CDrFont* pDrFont = (CDrFont*) pObject;
	//////////////////////////////////////////////////
	m_nElemType			= pDrFont->m_nElemType;
	m_nObjectType		= pDrFont->m_nObjectType; 
	m_nObjectNo			= pDrFont->m_nObjectNo;
	///////////////////////////////////////////////// 
	m_bFontSelected		= pDrFont->m_bFontSelected;
	m_FontColor			= pDrFont->m_FontColor;
	m_lf				= pDrFont->m_lf;
    /////////////////////////////////////////////////

	return;
}		

void CDrFont::GetObjectInfo(CDrObject* pObject)
{
	
	CDrFont* pDrFont = (CDrFont*) pObject;
	//////////////////////////////////////////////////   
	pDrFont->m_nObjectType 			= m_nObjectType; 
	pDrFont->m_nElemType			= m_nElemType;	
	pDrFont->m_nObjectNo			= m_nObjectNo;
	///////////////////////////////////////////////// 
	pDrFont->m_bFontSelected		= m_bFontSelected;
	pDrFont->m_FontColor			= m_FontColor;
	pDrFont->m_lf					= m_lf;
	/////////////////////////////////////////
	return;
}		

void CDrFont::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDrFont::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_SpecTypes;i++)
   		if(SpTypes[i].num == DRFONT) 
   		{
   			name = SpTypes[i].ObjName;
   			break;
   		}	
   			
   	static CString pad = " ";
  	////////////////////////
   	AddStr(pstrCard,&name,10);
	/////////////////////// 
	return;

}   

void CDrFont::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	BYTE b;
	WORD w;
	DWORD dw;
	/////// 
	if (ar.IsStoring())
	{
		TRACE(" DrFont:    Storing\n");	// TODO: add storing code here
		
		///////////////////////////////////////////////////	
		ar	<</*int*/	(WORD)m_nElemType	
			<</*int*/	(WORD)m_nObjectType
			<</*UINT*/	(WORD)m_nObjectNo; 
		///////////////////////////////////
		ar	<</*BOOL*/	(BYTE)m_bFontSelected
		  	<</*COLORREF*/	(DWORD)	m_FontColor;
		ar.Write(/*LOGFONT*/&m_lf,sizeof(LOGFONT) );

	}
	else
	{
		TRACE(" DrFont:    Loading\n");	// TODO: add loading code here

		///////////////////////////////////////////////////	
		ar	>>/*int*/w;
		m_nElemType = (int)w;	
		ar	>>/*int*/w;
		m_nObjectType = (int)w;
		ar	>>/*UINT*/w;
		m_nObjectNo = (UINT)w;
		///////////////////////////////////
		ar	>>/*BOOL*/b;
		m_bFontSelected = (BOOL)b;
		ar	>>/*COLORREF*/	dw;
		m_FontColor = (COLORREF) dw;

		ar.Read(/*LOGFONT*/&m_lf,sizeof(LOGFONT) );
		///////////////////////////////////

	}        
	///////////////
	
}

void CDrFont::DoTextFont()
{
	/////////////////////////////////
	LOGFONT lf = GetCurrentLogFont();
    /////////////////////////////////////// fill in choosefont
	CFontDialog dlg(&lf, CF_SCREENFONTS|CF_INITTOLOGFONTSTRUCT|CF_EFFECTS);
	dlg.m_cf.rgbColors = GetTextColor();
    ////////////////////////////////////
	if (dlg.DoModal() == IDOK)
	{ 
	
		// save new font info.

		SetTextColor(dlg.GetColor() );	// set textcolor
		SetCurrentLogFont(lf);	
		m_bFontSelected = TRUE;
		
	}

}
////////////////////////////////// end of module //////////////////
