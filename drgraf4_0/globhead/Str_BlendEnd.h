#ifndef _BLENDEND_H
#define _BLENDEND_H 

#include "Def_CuPS.h"           // Bndry End Conditions
#include "Def_Type.h"           // Bndry End Conditions
//////////////////////////////////////////////////////////////////////////
typedef struct blendend 
	{
		///////////////////////
		BOUNDARY	m_BCL;
		BOUNDARY	m_BCR;
		VECTOR		m_TanL;
		VECTOR		m_TanR;
		///////////////////////
    }BLENDEND, FAR *pBLENDEND;
////////////////////////////////////////////////////////////////////	  		
#endif
