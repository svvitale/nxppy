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
* Type definitions for Reader Library Framework.
* $Author: santosh.d.araballi $
* $Revision: 1.4 $
* $Date: Fri Apr 15 09:26:54 2011 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PH_TYPEDEFS_H
#define PH_TYPEDEFS_H

#ifdef linux
#include <sys/types.h>
#endif

/** \defgroup ph_Typedefs Type Definitions
* \brief Contains definitions for types defined within NxpRdLib
* @{
*/

/** \name Unsigned Types
*/
/*@{*/
#ifndef __uint8_t_defined
#define __uint8_t_defined
/**
* \brief 8 bit unsigned integer
*/
typedef unsigned char uint8_t;
#endif
#ifndef __uint16_t_defined
#define __uint16_t_defined
/**
* \brief 16 bit unsigned integer
*/
typedef unsigned short uint16_t;
#endif
#ifndef __uint32_t_defined
#define __uint32_t_defined
/**
* \brief 32 bit unsigned integer
*/
#ifdef _WIN32
typedef unsigned long uint32_t;
#else
typedef unsigned int uint32_t;
#endif
#endif
/*@}*/

/** \name Signed Types
*/
/*@{*/
#ifndef __int8_t_defined
#define __int8_t_defined
/**
* \brief 8 bit signed integer
*/
typedef char int8_t;
#endif
#ifndef __int16_t_defined
#define __int16_t_defined
/**
* \brief 16 bit signed integer
*/
typedef short int16_t;
#endif
#ifndef __int32_t_defined
#define __int32_t_defined
/**
* \brief 32 bit signed integer
*/
#ifdef _WIN32
typedef long int32_t;
#else
typedef int int32_t;
#endif
#endif
/*@}*/

/** \name Floating-Point Types
*/
/*@{*/
#ifndef __float32_t_defined
#define __float32_t_defined
/**
* \brief 32 bit floating point
*/
typedef float float32_t;
#endif
/*@}*/

/** \name Boolean Types
*/
/*@{*/
#ifndef __BOOL_DEFINED
#define __BOOL_DEFINED    
#ifdef __CX51__     /* If Keil 8051 */
typedef bit bool;
#else
#define bool unsigned char; 
#endif
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif
#endif
/*@}*/

/** \name Other Types
*/
/*@{*/
/**
* \brief phcsBfl_Status_t is a signed short value, using the positive range.
*
* High byte: Category (group) Identifier.\n
* Low byte : Error Specifier.
*/
typedef uint16_t phStatus_t;

#ifndef NULL
#define NULL 0
#endif
/*@}*/

/** @}
* end of ph_Typedefs group
*/

#endif /* PH_TYPEDEFS_H */
