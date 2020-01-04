#ifndef	_MOUSELOC_H
#define _MOUSELOC_H 
                    
//#include "globals.h"
////////////////////////////////////////////////////////// Mouse Location Class
class CMouseLoc : public CObject
{

public:

	CMouseLoc();
	DECLARE_SERIAL(CMouseLoc)

// Operations
public:

	//////////////////////////////////////////////// Mouse   
	LPOINT3	GetMouseWIC(){return m_MouseWIC;};	
	void 	SetMouseWIC(LPOINT3 NewMouseWIC);	
	LPOINT3	GetMouseOldWIC(){return m_MouseOldWIC;};	
	void 	SetMouseOldWIC(LPOINT3 NewMouseOldWIC);
	LPOINT	GetScrolledMouseWIC2D(){return m_LptScrolled;};
	void	SetScrolledMouseWIC2D(LPOINT LptScrolled)
			{
				m_LptScrolled.x = LptScrolled.x;
				m_LptScrolled.y = LptScrolled.y;
			};
	//////////////////////////////////////////////			    

protected:

	///////////////////////// Implementation
	void 	ReadDefaults();
	void 	Initialize();   
 

// Attributes
    ///////////////////////////////////////// Mouse
    LPOINT		m_LptScrolled;
	POINT		m_MouseVUC;
	POINT		m_MouseOldVUC;
	POINT		m_AnchorVUC;
	LPOINT3		m_MouseWIC;
	LPOINT3		m_MouseOldWIC;
	LPOINT3		m_MouseDefaultWIC;
  	LPOINT3		m_AnchorWIC;  

public:

	~CMouseLoc(){};
	virtual void Serialize(CArchive& ar);
};
///////////////////////////////////////////
#endif

