#ifndef _DEF_DYNL_H
#define _DEF_DYNL_H 

////////////////////////////////////////// Last Number already assigned
#define DYNL_LAST_NUMBER	8047
////////////////////////////////////////// Objects
#define DYNAMICLOAD		    8100       
#define TIMEHISTORY		    8101
#define HIS_FORCE		    8102       
#define HIS_DISPLACE	    8103        
#define HIS_VELOCITY	    8144        
#define HIS_ACCEL		    8145        
#define HIS_PRESSURE	    8106        
#define HIS_THERMAL		    8107
#define	HIS_LUMPMASS	    8108
///////////////////////////////////////////////////
#define NHIS_FORCE			8000
#define NHIS_DISPLACE		8001
#define NHIS_VELOCITY		8002
#define NHIS_ACCEL			8003
#define NHIS_PRESSURE		8004
#define NHIS_THERMAL	    8005
#define NHIS_LUMPMASS       8006
///////////////////////////////////////////
#define CHIS_FORCE          8007
#define CHIS_DISPLACE       8008
#define CHIS_VELOCITY		8009
#define CHIS_ACCEL			8010
#define CHIS_PRESSURE		8011
#define CHIS_THERMAL	    8012
#define CHIS_LUMPMASS       8013
///////////////////////////////////////////
#define PHIS_FORCE          8014
#define PHIS_DISPLACE       8015
#define PHIS_VELOCITY		8016
#define PHIS_ACCEL			8017
#define PHIS_PRESSURE       8018
#define PHIS_THERMAL	    8019
#define PHIS_LUMPMASS       8020
///////////////////////////////////////////
#define SHIS_FORCE          8021
#define SHIS_DISPLACE       8022
#define SHIS_VELOCITY		8023
#define SHIS_ACCEL			8024
#define SHIS_PRESSURE       8025
#define SHIS_THERMAL	    8026
#define SHIS_LUMPMASS       8027
//////////////////////////////////////////////////////// 
#define NHIS_EDIT			8028
#define NHIS_MOVE			8029
#define NHIS_POST			8030
#define NHIS_UNPOST			8031
#define NHIS_DELETE			8032
////////////////////////////////
#define SHIS_EDIT			8033
#define SHIS_MOVE			8034
#define SHIS_POST			8035
#define SHIS_UNPOST			8036
#define SHIS_DELETE			8037
////////////////////////////////
#define PHIS_EDIT			8038
#define PHIS_MOVE			8039
#define PHIS_POST			8040
#define PHIS_UNPOST			8041
#define PHIS_DELETE			8042
////////////////////////////////
#define CHIS_EDIT			8043
#define CHIS_MOVE			8044
#define CHIS_POST			8045
#define CHIS_UNPOST			8046
#define CHIS_DELETE			8047
///////////////////////////////////////////////////////////// GLOBALS
enum DYNLPROC				// DYLport Generation PROCedure
	{
		DYL_FORCE,
		DYL_DISPLACE,
		DYL_VELOCITY,
		DYL_ACCEL,
		DYL_PRESSURE,
		DYL_THERMAL,
		DYL_LUMPMASS
	};
	
enum DYNLSUBTYPE				// DYLport Generation PROCedure
	{
		SDYL_FORCE_T,
		SDYL_FORCE_R,
		SDYL_DISPLACE_T,
		SDYL_DISPLACE_R,
		SDYL_VELOCITY_T,
		SDYL_VELOCITY_R,
		SDYL_ACCEL_T,
		SDYL_ACCEL_R
	};
/////////////////////////////////////////////////////////////////////////////
#endif

