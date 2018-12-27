#ifndef _DC_IIR_FXP_C_H
#define _DC_IIR_FXP_C_H
/* **************************************************************************
 * dc_iir_fxp_c.h
 * Copyright (C) 2013- Canaan
 * All rights reserved.
 ****************************************************************************/
#ifdef  __cplusplus
extern "C"
{
#endif


#define VC_VER  0   /* 1: for window, 0: for unix or linux */
#if  VC_VER
typedef char                    INT8;
typedef short int               INT16;
typedef int                     INT32;
typedef __int64                 INT64;
typedef unsigned char           UINT8;
typedef unsigned short int      UINT16;
typedef unsigned int            UINT32;
typedef unsigned __int64        UINT64;
#else
typedef char                    INT8;
typedef short int               INT16;
typedef int                     INT32;
typedef long long               INT64;
typedef unsigned char           UINT8;
typedef unsigned short int      UINT16;
typedef unsigned int            UINT32;
typedef unsigned long long      UINT64;
#endif


#define SAT(a, max, min)                        ((a) > (max) ? (max) : ((a) < (min) ? (min) : (a)))
#define OVER_FLOW(a, max, min, sign)            (((sign)==0) ? ((a)&(max)) : ((a)|(min)) )
#define BIT_GET(a, b)                           (((a)>>((b)-1))&1)
#define ABS(a)                                  (((a)>=0) ? (a) : (-(a)))
#define MAX(a,b)                                ((a) > (b) ? (a) : (b))
#define ROUND_LAST_KBIT(a,k)                    ((k)==0 ? (a) : (((a)+(1<<((k)-1)))>>(k)))

#ifdef  __cplusplus
}
#endif
#endif // !DC_IIR_FXP_C_H