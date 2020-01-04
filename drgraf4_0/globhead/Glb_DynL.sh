#ifndef _GLOBDYNL_H
#define _GLOBDYNL_H
///////////////////////////////////////////////////////////// GLOBALS
enum STALPROC				// DYLport Generation PROCedure
	{
		DYL_FORCE,
		DYL_DISPLACE,
		DYL_VELOCITY,
		DYL_ACCEL,
		DYL_PRESSURE,
		DYL_THERMAL,
		DYL_LUMPMASS
	};
	
enum STALSUBTYPE				// DYLport Generation PROCedure
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

