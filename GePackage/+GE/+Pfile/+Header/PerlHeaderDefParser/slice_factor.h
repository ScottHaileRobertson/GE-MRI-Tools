/*
 *  GE Medical Systems
 *  Copyright (C) 1997 The General Electric Company
 *  
 *  Simple header file that is shared with rdbm.h and epic.h.  Contains 
 *  SLICE_FACTOR which is a multiplicative factor for the data acq order
 *  table size
 *  
 *  Language : ANSI C
 *  Author   : Bryan Mock
 *  Date     : 10/26/2000
 */
/* do not edit anything above this line */

/*
   Revision Information

   Internal
   Release #  Date	Person  Comments

   CNV4     04/10/01    ALP     Updated limit to 2
   MGD Version          BJM     Go back to 1 until Recon Ready
            11/16/01  
   14.0     08/15/05    ZL      move MAX_DIRECTIONS and MAX_T2 from epic.h
                                to here since for TENSOR, since they are
                                shared between PSD and recon. 

*/

#ifndef SLICE_FACTOR
#define SLICE_FACTOR 1
#endif /* SLICE_FACTOR */

#ifndef MAX_DIRECTIONS
#define MAX_DIRECTIONS 150
#endif

#ifndef MIN_DIRECTIONS
#define MIN_DIRECTIONS 1
#endif

#ifndef MAX_T2
#define MAX_T2 10
#endif

