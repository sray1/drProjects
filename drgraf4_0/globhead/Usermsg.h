// UserMsg.h : header file
//
#ifndef _USERMSG_H
#define _USERMSG_H

//Control-specific messages
///////////////////////////
//	LASTASSIGNED	126


#define ELM_NODE			(WM_USER+21)       // Node
#define ELM_PIPE			(WM_USER+22)       // Pipe
#define ELM_ELBOW			(WM_USER+23)       // Elbow
#define ELM_BEAM			(WM_USER+24)       // Beam
#define ELM_SUPPORT			(WM_USER+25)       // SubLibrary:SUPPORT 
#define ELM_TRUSS			(WM_USER+26)       // Truss
#define ELM_PLANE			(WM_USER+27)       // Plane
#define ELM_PLATE			(WM_USER+28)       // PLate
#define ELM_SHELL			(WM_USER+29)       // Shell
///////////////////////////////////////////////// Dialogs
#define ID_ACTIVE_O3DIN		(WM_USER+114)  
#define ID_UPDATE_O3DIN		(WM_USER+115)	
#define ID_CANCEL_O3DIN		(WM_USER+116)   
#define ID_GOODBYE_O3DIN	(WM_USER+117)   
#define ID_ACTIVE_SOLIN		(WM_USER+110)  
#define ID_UPDATE_SOLIN		(WM_USER+111)	
#define ID_CANCEL_SOLIN		(WM_USER+112)   
#define ID_GOODBYE_SOLIN	(WM_USER+113)   
#define ID_ACTIVE_PATIN		(WM_USER+30)  
#define ID_UPDATE_PATIN		(WM_USER+31)	
#define ID_CANCEL_PATIN		(WM_USER+72)   
#define ID_GOODBYE_PATIN	(WM_USER+32)   
#define ID_ACTIVE_SUPIN		(WM_USER+33)     
#define ID_UPDATE_SUPIN 	(WM_USER+34)    
#define ID_CANCEL_SUPIN		(WM_USER+73)   
#define ID_GOODBYE_SUPIN	(WM_USER+35)    
#define ID_ACTIVE_LQCIN 	(WM_USER+36)    
#define ID_UPDATE_LQCIN 	(WM_USER+37)    
#define ID_CANCEL_LQCIN		(WM_USER+74)   
#define ID_GOODBYE_LQCIN	(WM_USER+38)    
#define ID_ACTIVE_NODIN 	(WM_USER+39)    
#define ID_UPDATE_NODIN		(WM_USER+40)    
#define ID_CANCEL_NODIN		(WM_USER+75)   
#define ID_GOODBYE_NODIN	(WM_USER+41)    
#define ID_ACTIVE_CRCIN 	(WM_USER+42)    
#define ID_UPDATE_CRCIN 	(WM_USER+43)    
#define ID_CANCEL_CRCIN		(WM_USER+76)   
#define ID_GOODBYE_CRCIN	(WM_USER+44)
#define ID_ACTIVE_CREIN 	(WM_USER+69)    
#define ID_UPDATE_CREIN 	(WM_USER+70)    
#define ID_CANCEL_CREIN		(WM_USER+77)   
#define ID_GOODBYE_CREIN	(WM_USER+71)
//////////////////////////////////////// Post
#define ID_ACTIVE_FE0IN 	(WM_USER+86)    
#define ID_UPDATE_FE0IN 	(WM_USER+87)    
#define ID_CANCEL_FE0IN		(WM_USER+88)   
#define ID_GOODBYE_FE0IN	(WM_USER+89)
///
#define ID_ACTIVE_FE1IN 	(WM_USER+90)    
#define ID_UPDATE_FE1IN 	(WM_USER+91)    
#define ID_CANCEL_FE1IN		(WM_USER+92)   
#define ID_GOODBYE_FE1IN	(WM_USER+93)
///
#define ID_ACTIVE_FE2IN 	(WM_USER+94)    
#define ID_UPDATE_FE2IN 	(WM_USER+95)    
#define ID_CANCEL_FE2IN		(WM_USER+96)   
#define ID_GOODBYE_FE2IN	(WM_USER+97)
///
#define ID_ACTIVE_FE3IN 	(WM_USER+98)    
#define ID_UPDATE_FE3IN 	(WM_USER+99)    
#define ID_CANCEL_FE3IN		(WM_USER+100)   
#define ID_GOODBYE_FE3IN	(WM_USER+101)
////////////////////////////////////////    
#define ID_RESET_MODELESS	(WM_USER+45)
//////////////////////////////////////// Static Load    
#define ID_ACTIVE_FANDMIN	(WM_USER+46)     
#define ID_UPDATE_FANDMIN 	(WM_USER+47)    
#define ID_CANCEL_FANDMIN	(WM_USER+78)   
#define ID_GOODBYE_FANDMIN	(WM_USER+48)    
#define ID_ACTIVE_DANDRIN	(WM_USER+49)     
#define ID_UPDATE_DANDRIN 	(WM_USER+50)    
#define ID_CANCEL_DANDRIN	(WM_USER+79)   
#define ID_GOODBYE_DANDRIN	(WM_USER+51)    
#define ID_ACTIVE_PRESSIN	(WM_USER+52)     
#define ID_UPDATE_PRESSIN 	(WM_USER+53)    
#define ID_CANCEL_PRESSIN	(WM_USER+80)   
#define ID_GOODBYE_PRESSIN	(WM_USER+54)    
#define ID_ACTIVE_THERMIN	(WM_USER+55)     
#define ID_UPDATE_THERMIN 	(WM_USER+56)    
#define ID_CANCEL_THERMIN	(WM_USER+81)   
#define ID_GOODBYE_THERMIN	(WM_USER+57)    
#define ID_ACTIVE_LUMPWTIN	(WM_USER+83)     
#define ID_UPDATE_LUMPWTIN 	(WM_USER+84)    
#define ID_CANCEL_LUMPWTIN	(WM_USER+82)   
#define ID_GOODBYE_LUMPWTIN	(WM_USER+85)    
/////////////////////////////// Advanced
#define ID_ADVANCE_FANDMIN	(WM_USER+58)     
#define ID_ADVANCE_DANDRIN	(WM_USER+59)     
#define ID_ADVANCE_PRESSIN	(WM_USER+60)     
#define ID_ADVANCE_THERMIN	(WM_USER+61)     
#define ID_ADVANCE_LUMPWTIN	(WM_USER+62)     
#define ID_ADVANCE_PATIN	(WM_USER+63)     
#define ID_ADVANCE_SUPIN	(WM_USER+64)     
#define ID_ADVANCE_LQCIN	(WM_USER+65)     
#define ID_ADVANCE_NODIN	(WM_USER+66)     
#define ID_ADVANCE_CRCIN	(WM_USER+67)
//////////////////////////////////////// RestBox/Task     
#define ID_RESET_CNTLOPEN	(WM_USER+102)     
#define ID_RESET_IGENOPEN	(WM_USER+103)     
#define ID_RESET_TASKID		(WM_USER+68)     
////////////////////////////////////////
#define ID_UPDATE_STATCNTLS	(WM_USER+104)     
////////////////////////////////////////
#define ID_RESET_VASKID		(WM_USER+105)     
//
#define ID_ACTIVE_VOROTIN	(WM_USER+106)     
#define ID_UPDATE_VOROTIN 	(WM_USER+107)    
#define ID_CANCEL_VOROTIN	(WM_USER+108)   
#define ID_GOODBYE_VOROTIN	(WM_USER+109)    
////////////////////////////////////////
#define ID_RESET_MASKID		(WM_USER+118)     
#define ID_RESET_MODELESS_MESH	(WM_USER+119)
#define ID_RESET_CNTLOPEN_MESH	(WM_USER+120)     
#define ID_RESET_IGENOPEN_MESH	(WM_USER+121)     
//////////////////////////////////////// RestBox/Task : AUXILLIARY    
#define ID_RESET_XASKID		(WM_USER+122)     
#define ID_RESET_MODELESS_AUXI	(WM_USER+123)
#define ID_RESET_CNTLOPEN_AUXI	(WM_USER+124)     
#define ID_RESET_IGENOPEN_AUXI	(WM_USER+125) 
/////////////////////////////////////////////    
#define ID_OPTION_MODE			(WM_USER+126) // Current Mode    
//////////////////////////////////////////////////////////////
#endif
