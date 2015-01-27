/*
	op_loader.h
*/


#ifndef INCop_loaderh
#define INCop_loaderh

#include "GEtypes.h"
#include "op_global.h"


/*--------------------------------------------------------------------*/
/*        nmrid declarations for booting the TPS/IPG */
/*--------------------------------------------------------------------*/


#define LO_TPS_LOADER_DAEMON_NMRID   "LOAD_DAEMN1"
      /*  network tag for the TPS loader daemon task */ 

#define LO_IPG_LOADER_DAEMON_NMRID   "LOAD_DAEMN2"
     /*   network tag for the IPG loader daemon task  */ 

#define LO_HOST_NMRID   "NSP"
      /*  NMRID which will receive loader daemon startup packets.
	network tag for the host controller task */

/* The port that CM communicates to NSP on for init status */
#define LO_HOST_INIT_STATUS_PORT 5051

/* change start - vardish phase 2 */


#define LO_SCP_LOADER_DAEMON_NMRID   "LOAD_DAEMN1"

#define LO_AGP_LOADER_DAEMON_NMRID   "LOAD_DAEMN2"

#define LO_APS_LOADER_DAEMON_NMRID   "LOAD_DAEMN3"


/* change end - vardish phase 2 */


/*--------------------------------------------------------------------*/
/*        log declarations for TPS */
/*--------------------------------------------------------------------*/

#define TPS_RPC_READY "MrMail Agent Ready"
/*        String in TPS message buffer used to indicate that the */
/*        TPS RPC server for MrMail is now active.  Inserted from */
/*        "cm_rcalls.c" using the "vw_stat_log()" function call. */
/* */
/*        NSP will poll for this string before attempting any RPC */
/*        calls to TPS during MrMail initialization/TPS rebooting. */
 
/*--------------------------------------------------------------------*/
/*        error codes returned in the status field by the loader daemon*/
/*--------------------------------------------------------------------*/
 
#define LO_INVAL_PACK   0X301

/*        invalid packet; opcode not op_fcdg_020_boot, or non-zero status*/
 
#define LO_OPEN_FAIL   0X302

/*        could not open the specified file*/
 
#define LO_HEADER_FAIL   0X303

/*        could not read the first 32 bytes (header) of the open file*/
 
#define LO_NO_RAM   0X304

/*        not enough contiguous ram was available to load the file into*/
 
#define LO_LOAD_FAIL   0X305

/*        failure status returned from the "ldLoadAt()" system call.*/
/*        possible causes: error reading file or a symbol inthe file*/
/*                         could not be resolved on the target.*/


/* ********************************************************************** */
/* *****                                                            ***** */
/* ***** The following entries must match the ERMES values located  ***** */
/* ***** in the file "em_CHECKER_ermes.md" in project "em_CMNetwork ***** */
/* *****                                                            ***** */
/* ***** They are used by CHECKER (actually, by "lo_tests.c") to    ***** */
/* ***** generate the mhandler packets for use by NSP on the host.  ***** */
/* *****                                                            ***** */
/* ********************************************************************** */

#define LO_SYS_CHECKSUM	2227700

/*        the checksum of the platform executable code has changed. */
/*        possible causes: someone has set a breakpoint in vxWorks */
/*                         code space or the code has been corrupted */
/*                         by someone overwriting the segment. */

#define LO_STACK_ERROR	2227701

/*        the bottom of the stack has been written to. */
/*        possible causes: someone using an adjacent buffer has overrun */
/*                         their buffer space or a task did not allocate */
/*                         a deep enough stack to support the subroutines */
/*                         and device drivers that it called. */

#define LO_FREE_MEM_ERROR 2227702

/*        the "free memory" chain has been broken. */
/*        possible causes: a task is writing to memory that it does not */
/*                         own or an old buffer pointer is being used */
/*                         after the block of memory that it is pointing */
/*                         to has been return to the free memory pool. */

#define LO_MCB_CHECKSUM 2227703

/*        the checksum of downloaded executable code has changed. */
/*        possible causes: the downloaded code is self modifying or */
/*                         an appliation has written to an old buffer */
/*                         which is now being used to hold executable */
/*                         code. */
/**/



/*--------------------------------------------------------------------*/
/*        Opcode definition for 020 loader daemon to inform FCDG*/
/*        that the loader daemon is ready to load a file*/
/*--------------------------------------------------------------------*/
 
#define OP_LOAD_020_READY 418

typedef struct
            { OP_HDR_TYPE  hdr;
            } OP_LOAD_020_READY_TYPE;

/*--------------------------------------------------------------------*/
/*        Opcode definition for host NSP process to inform the */
/*        020 loader daemon which file to load and run */
/*--------------------------------------------------------------------*/
 
#define OP_LOAD_020_BOOT   419

/*--------------------------------------------------------------------*/
/*        Opcode definition for 020 applications to use to inform the */
/*        host NSP process that the loaded application has started */
/*--------------------------------------------------------------------*/
 
#define OP_LOAD_START_UP   420

typedef struct
            { s8	filename [80];
              n32	command_word;
              n32	duration;
              n32	loop_counter;
            } OP_LOAD_020_BOOT_PKT_TYPE;
 
typedef struct
            { OP_HDR_TYPE  hdr;
              OP_LOAD_020_BOOT_PKT_TYPE req;
            } OP_LOAD_020_BOOT_TYPE;
/**/

#endif /*INCop_loaderh*/

