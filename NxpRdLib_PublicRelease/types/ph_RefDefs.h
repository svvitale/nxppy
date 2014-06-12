/*
*         Copyright (c), NXP Semiconductors Gratkorn / Austria
*
*                     (C)NXP Semiconductors
*       All rights are reserved. Reproduction in whole or in part is 
*      prohibited without the written consent of the copyright owner.
*  NXP reserves the right to make changes without notice at any time.
* NXP makes no warranty, expressed, implied or statutory, including but
* not limited to any implied warranty of merchantability or fitness for any
*particular purpose, or that the use will not infringe any third party patent,
* copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
*/

/** \file
* Platform definitions for Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.3 $
* $Date: Fri Apr 15 09:26:54 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PH_REFDEFS_H
#define PH_REFDEFS_H

#include <ph_TypeDefs.h>

/** \defgroup ph_RefDefs Platform Definitions
* \brief Platform depending definitions for memory location of variables.
*
* We distinguish between:
*   - BUFFERs   : Location of storage, usually mid-speed but max. RAM consumption,
*   - COUNTERs  : loop counters or frequently accessed variables, fast access,
*   - REMINDERs : variables holding status values or serving flow control purposes.
*
* If RCL is used on a microcontroller, an own REFDEF.H file must be generated where the
* RCL_MEMLOC_... definition must get according values. Default definitions are empty.
*
* Assignment Example: XDATA for #PH_MEMLOC_BUF,
*                     IDATA for #PH_MEMLOC_COUNT,
*                     EDATA for #PH_MEMLOC_REM.
* @{
*/

/** 
*  Space used for storage (e.g. buffers). 
*/
#define PH_MEMLOC_BUF   /* */

/**
* Space used for fast and frequent access e.g. counters, loop variables).
*/
#define PH_MEMLOC_COUNT /* */      

/**
* Space used for control variables, these could be e.g. status values.
*/
#define PH_MEMLOC_REM   /* */

/**
* Space used for constants, these could be e.g. lookup tables.
*/
#define PH_MEMLOC_CONST_ROM /* */

/** @}
* end of ph_RefDefs group
*/

#endif /*  PH_REFDEFS_H */
