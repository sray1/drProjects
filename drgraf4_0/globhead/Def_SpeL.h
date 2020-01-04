#ifndef _DEF_SPEL_H
#define _DEF_SPEL_H 
////////////////////////////////////////// Last Number already assigned
#define SPEL_LAST_NUMBER	7047
////////////////////////////////////////// Objects
#define SPECTRALOAD			7100       
#define SPL_FORCE			7101       
#define SPL_DISPLACE		7102        
#define SPL_VELOCITY		7103        
#define SPL_ACCEL			7104        
#define SPL_PRESSURE		7105        
#define SPL_THERMAL			7106
#define	SPL_LUMPMASS		7107
///////////////////////////////////////////////////
#define NSPL_FORCE			7000
#define NSPL_DISPLACE		7001
#define NSPL_VELOCITY		7002
#define NSPL_ACCEL			7003
#define NSPL_PRESSURE		7004
#define NSPL_THERMAL	    7005
#define NSPL_LUMPMASS		7006
///////////////////////////////////////////
#define CSPL_FORCE          7007
#define CSPL_DISPLACE       7008
#define CSPL_VELOCITY		7009
#define CSPL_ACCEL			7010
#define CSPL_PRESSURE		7011
#define CSPL_THERMAL	    7012
#define CSPL_LUMPMASS       7013
///////////////////////////////////////////
#define PSPL_FORCE          7014
#define PSPL_DISPLACE       7015
#define PSPL_VELOCITY	    7016
#define PSPL_ACCEL			7017
#define PSPL_PRESSURE       7018
#define PSPL_THERMAL	    7019
#define PSPL_LUMPMASS       7020
///////////////////////////////////////////
#define SSPL_FORCE          7021
#define SSPL_DISPLACE       7022
#define SSPL_VELOCITY	    7023
#define SSPL_ACCEL			7024
#define SSPL_PRESSURE       7025
#define SSPL_THERMAL        7026
#define SSPL_LUMPMASS       7027
//////////////////////////////////////////////////////// 
#define NSPL_EDIT			7028
#define NSPL_MOVE			7029
#define NSPL_POST			7030
#define NSPL_UNPOST			7031
#define NSPL_DELETE			7032
////////////////////////////////
#define SSPL_EDIT			7033
#define SSPL_MOVE			7034
#define SSPL_POST			7035
#define SSPL_UNPOST			7036
#define SSPL_DELETE			7037
////////////////////////////////
#define PSPL_EDIT			7038
#define PSPL_MOVE			7039
#define PSPL_POST			7040
#define PSPL_UNPOST			7041
#define PSPL_DELETE			7042
////////////////////////////////
#define CSPL_EDIT			7043
#define CSPL_MOVE			7044
#define CSPL_POST			7045
#define CSPL_UNPOST			7046
#define CSPL_DELETE			7047
///////////////////////////////////////////////////////////// GLOBALS
enum MODAPROC				// FRQport Generation PROCedure
	{
		MOD_FORCE,
		MOD_DISPLACE,
		MOD_VELOCITY,
		MOD_ACCEL,
		MOD_PRESSURE,
		MOD_THERMAL,
		MOD_LUMPMASS
	};
	
enum MODASUBTYPE				// FRQport Generation PROCedure
	{
		SMOD_FORCE_T,
		SMOD_FORCE_R,
		SMOD_DISPLACE_T,
		SMOD_DISPLACE_R,
		SMOD_VELOCITY_T,
		SMOD_VELOCITY_R,
		SMOD_ACCEL_T,
		SMOD_ACCEL_R
	};
/////////////////////////////////////////////////////////////////////////////
#endif

