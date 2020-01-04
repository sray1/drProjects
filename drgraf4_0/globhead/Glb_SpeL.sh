#ifndef _GLOBSPEL_H
#define _GLOBSPEL_H
///////////////////////////////////////////////////////////// GLOBALS
enum FREQPROC				// FRQport Generation PROCedure
	{
		SPL_FORCE,
		SPL_DISPLACE,
		SPL_VELOCITY,
		SPL_ACCEL,
		SPL_PRESSURE,
		SPL_THERMAL,
		SPL_LUMPMASS
	};
	
enum STALSUBTYPE				// FRQport Generation PROCedure
	{
		SSPL_FORCE_T,
		SSPL_FORCE_R,
		SSPL_DISPLACE_T,
		SSPL_DISPLACE_R,
		SSPL_VELOCITY_T,
		SSPL_VELOCITY_R,
		SSPL_ACCEL_T,
		SSPL_ACCEL_R
	};
/////////////////////////////////////////////////////////////////////////////
#endif 

