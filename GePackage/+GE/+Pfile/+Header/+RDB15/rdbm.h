/*@Start***********************************************************/
/* GEMSBG Include File
 * Copyright (C) 1992 The General Electric Company
 *
 *      Include File Name:  @RDBM@
 *      Developer:  X. Zang
 *
 * $Source: rdbm.h $
 * $Revision: 1.23 $  $Date: 4/4/94 12:41:07 $
 */
// NOT ORIGINAL GE VERSION:
// 090216 slg edited to rid dependencies on coilParameters.h and ConfigParameter.h within op_prescan.h


/*@Synopsis

	Define all constants and structures needed to interface with RDBM.
*/

/*@Description

	Applications who uses RDBM must include this file.
	There are two ways this file can be used.

	1.	Applications who uses the toolsdata, exam header, serise
		header and/or image header section of the raw header must
		include the following files prior to the #include
		directive of this file.

				#include toolsdata.h 
				#include imagedb.h

	2.	Applications who wish to do away with the objcc dependancy
		and have no need to access the sections mentioned above
		can do so by 
		
				#define RECON_FLAG 
				
		prior to the #include directive of this file.

        Generation      Date            Author(s)       Comments
        ----------      ----            --------        --------
          vmx        10/17/94          M. Hartley       Merge 5.5 into vmx
          vmx        12/21/94          Y. Oda           Add YMS's gradient
                                                        coil types

	CV1M3        05.27.98          S. Murthy        Removed GradCoil Definitions
							Added Gradwarp Definitions
        CV2          09/28/99          AKG              MRIge56094 added RDB_FCINE_ET to recon dacq ctrl
	CV2	     11/05/99          A.T.		Add entries for gridding.
        LX           09/21/00          BWL              MRIge61012 - reserved 12th bit of rhdacqctrl for 
                                                        CERD to enable queing at AIME input end for normal
                                                        2D/3D scans.
        CV2          08/11/00          ALP              MRIge61411 - reserved 12th bit of rhdacqctrl for 
                                                        CERD to enable queing at AIME input end for normal
                                                        2D/3D scans.
        PLX          11/06/00          BJM              Added slice_factor.h and SLICE_FACTOR to DATA_ACQ_ORDER 
                                                        table               
         8.34        08/21/00          Y. Oda           Added RDB_LINE_SCAN
                                                        in rdb_hdr_data_collect_type1
         8.34        05/08/01          N. Adachi        Added rdn_hdr_fiestamlf for MFO FIESTA    
                     27/08/02          M. Miyoshi       YMSmr04091. Added RDB_FIESTA_1ST_LAST for FIESTA.
         11.0	     07-Mar-03	       S.Lawrence
	                               T.Abraham        Added entries for EC-TRICKS

        HFO3         12/16/2002        Rakesh Shevde    Added 
                                                        rdb_hdr_retro_control, rdb_hdr_etl for Retro FSE
                                                        phase correction.
                                                        RDB_RETRO_PC bit to identify Retro FSE phase
                                                        correction scan.
	12.0	     10-Mar-04	       Alok Modak	Changes to overcome slice limit of 1024 for Multiphase
							(RDB_SINGLE_PHASE_INFO type) scans. 
							New limit: RDB_MAX_SLICES_MULTIPHASE 10000
							Added entries for >1024
	12.0	     26-Mar-2004       Rakesh Shevde	Added fields to RDB_HEADER_REC to indicate offsets for 
							the respective data structures of the POOL_HEADER.
        11.0         08-Aug-2004       Raman Subramanian MRIge91592 - 8.x comments for 11.0 states that the raw header size is
                                                         60464. It should be 61464
    14.0  08-May-2005  Sanjay Joshi     Changed P-file header revision to
                                        14.0.  Changed comments regarding
                                        P-file header size.
	14.0	     14-June-2005       Alok Modak	Changes to support SWIFT
    14.0  20-Dec-2005  Bhavik Kanabar  Added PRESCAN_HEADER to POOL_HEADER.   
*/

/*@End*********************************************************/
#include "GEtypes.h"
#include "toolsdata.h"
#include "op_global.h"
#include "op_prescan.h"
#include "GElimits.h"
#include "slice_factor.h"

#ifndef RDBM_INCL /* only do this once in any given compilation.*/
#define RDBM_INCL

/*---------------------------------------------------------------------
 | RDBM Function codes
 ---------------------------------------------------------------------*/
#define RDB_ALLOCATE                    1
#define RDB_CLOSE                       2
#define RDB_DEALLOCATE                  3
#define RDB_INIT                        4
#define RDB_LOCK                        5
#define RDB_OPEN                        6
#define RDB_RDHEADER                    7
#define RDB_UNLOCK                      8
#define RDB_WRHEADER                    9
#define RDB_PREALLOCATE                10
#define RDB_LASTRUN                    11
#define RDB_CLEANUP                    12
#define RDB_LOPEN                      13
#define RDB_LCLOSE                     14
#define RDB_READ                       15
#define RDB_WRITE                      16
#define RDB_LOCK_TO_TAPE               17
#define RDB_UNLOCK_FROM_TAPE           18
#define RDB_HDR_UNLOCK                 19
#define RDB_GETADDR                    20
#define RDB_VALID                      21
#define RDB_RDPFRAME                   22
#define RDB_PERM                       23
#define RDB_HIDE                       24
#define RDB_UNHIDE                     25
#define RDB_RDTFRAME                   26
#define RDB_RDPOPS                     27
#define RDB_RDTOPS                     28
#define RDB_CREATE_LINK                29
#define RDB_LOCK_SLICE                 30
#define RDB_DEALLOCATE_RFF             31
#define RDB_PERM_RFF                   32
#define RDB_UNLOCK_RFF                 33
#define RDB_UNLOCK_FROM_TAPE_RFF       34
#define RDB_DEALLOCATE_DS              35
#define RDB_HDR_UNLOCK_RFF             36
#define RDB_SET_RECEIVER               37
#define RDB_DISK_TO_TAPE               38
#define RDB_TAPE_TO_DISK               39
#define RDB_CLEARDB                    40
#define RDB_UNINIT                     41
#define RDB_WRITE_RAW                  42
#define RDB_SAVE_BAM                   43
#define RDB_LOAD_BAM                   44

/*---------------------------------------------------------------------
 | RDBM status codes
 ---------------------------------------------------------------------*/
#define RDB_STATUS_OK                  0
#define RDB_STATUS_ERR                -1
#define RDB_NO_RUNS                   -2

/*---------------------------------------------------------------------
 | rdb_hdr_rdbm_rev
 | RDBM header fields that filled by rdbm routines
 ---------------------------------------------------------------------*/
#define RDB_RDBM_REVISION              14.3F

/*---------------------------------------------------------------------
 | rdb_hdr_transpose
 | Relating to transpose and rotating the image 16 bit integer
 ---------------------------------------------------------------------*/
#define RDB_TRANSPOSE                  3
#define RDB_NO_TRANSPOSE               0
#define RDB_TRANSPOSE_AFTER           -1
#define RDB_TRANSPOSE_BEFORE           1

/*---------------------------------------------------------------------
 | rdb_hdr_rotation
 | For 'ROTATION' field in header 
 ---------------------------------------------------------------------*/
#define RDB_NO_ROTATION                0
#define RDB_ROTATE_90                  1
#define RDB_ROTATE_180                 2
#define RDB_ROTATE_270                 3

/*---------------------------------------------------------------------
 | rdb_hdr_scan_type
 | Scan types, may be added together to form the right combination
 | storage is 16 bit mask.
 ---------------------------------------------------------------------*/
#define RDB_SPIN_ECHO                  0x0002	/* 2 */
#define RDB_PARTIAL_SAT                0x0008	/* 8 */
#define RDB_INVERSION_REC              0x0010	/* 16 */
#define RDB_HADAMARD                   0x0020	/* 32 */
#define RDB_SPIN_WARP                  0x0800	/* 2048 */
#define RDB_GRE                        0x1000	/* 4096 */

/*---------------------------------------------------------------------
 | rdb_hdr_data_collect_type
 | Data collection types are a bitmask which may be added together
 | to form the right combination of bits.
 ---------------------------------------------------------------------*/
#define RDB_CHOPPER                    0x0001
#define RDB_CINE                       0x0002
#define RDB_SHIM                       0x0004
#define RDB_GRASS                      0x0008
#define RDB_HNEX                       0x0010	/* 16 */
#define RDB_STRIP                      0x0020	/* 32 */
#define RDB_Y_STRIP                    0x0020	/* 32 */
#define RDB_3DFFT                      0x0040	/* 64 */
#define RDB_EXORCIST                   0x0080	/* 128 */
#define RDB_NO_PHASE_WRAP              0x0100	/* 256 */
#define RDB_NO_FREQ_WRAP               0x0200	/* 512 */
#define RDB_X_STRIP                    0x0400	/* 1024 */
#define RDB_HECHO                      0x0800	/* 2048 */
#define RDB_OVERSCAN                   0x1000	/* 4096 */
#define RDB_3QNEX                      0x2000	/* 8192 */
#define RDB_POMP                       0x4000	/* 16384 */

/*---------------------------------------------------------------------
| rdb_hdr_data_collect_type1
| Data collection types are a bitmask which may be added together
| to form the right combination of bits.
| RDB_USE_NEXA is used to indicated that the nex abort table will be
| used to store the nex values during the collection of the 2nd echo.
| RDB_USE_NEXA is normally used for Odd Nex Fast Spin Echo scans with
| two echoes.
|
| Added RDB_SFRAME for 64kHz bandwidth multi-coil norec superframe processing
|
| Added RDB_MULTISLAB, RDB_MAX_OVLPROC, RDB_MIN_OVLPROC for MOTSA   
| overlap image processing  
|
| Added RDB_SPIRAL for data acquired using a spiral sequence.
| Added RDB_LINE_SCAN (reserved for hfo/mfo)
| Added RDB_RECON_ALL_PASSES so Recon does not skip any.
| Added RDB_ECTRICKS for EC-TRICKS sequence.
| Added RDB_RETRO_PC for applying Retrospective FSE phase correction(set by PSD).
| RDB_SUPPORT_RDS Set if this scan supports raw data server
| RDB_INITPATH_RDS Set when initial datapath is RDS (instead of regular Recon datapath)
---------------------------------------------------------------------*/
#define RDB_HRHOMO                     0x0001
#define RDB_USE_NEXA                   0x0002
#define RDB_CINE_ODDNEX                0x0004
#define RDB_SFRAME                     0x0008
#define RDB_MULTISLAB                  0x0010   /* 16 */ 
#define RDB_MAX_OVLPROC                0x0020   /* 32 */
#define RDB_MIN_OVLPROC                0x0040   /* 64 */
#define RDB_FAST_PHASE_OFF             0x0080   /* 128 */
#define RDB_AUTO_PASS                  0x0100   /* 256 */
#define RDB_IMG_NEX                    0x0200   /* 512 */
#define RDB_SPIRAL                     0x0400   /* 1024 */
#define RDB_FAST_VRGF                  0x0800   /* 2048 */
#define RDB_RECON_ALL_PASSES           0x1000   /* 4096 */
#define RDB_LINE_SCAN                  0x2000   /* 8192 */
#define RDB_ECTRICKS 		       0x4000	/* 16384 */
#define RDB_VRGF_AFTER_PCOR            0x8000   /* 32768 */
#define RDB_ZERO_ROW_ENDS              0x10000  /* 65536 */
#define RDB_RETRO_PC                   0x20000  /* 131072 */
#define RDB_ZERO_FILL                  0x40000  /* 262144 */
#define RDB_SUPPORT_RDS                0x80000  /* 524288 */
#define RDB_INITPATH_RDS              0x100000  /* 1048576 */
#define RDB_DIFFUSION_EPI              0x200000 /* 2097152 */

/*---------------------------------------------------------------------
 | rdb_hdr_data_format
 | Define bits for the FORMAT offset in the RDBM hdr. These define 
 | various non-data related processes which may be turned on or off 
 | just for fun. These bits may be added together to form a 16-bit    
 | bitmask.  Please note that there is NOT a clear distinction being 
 | made between what should be in the FORMAT offset and what should 
 | be in the DATA COLLECTION offset. It's up to the keeper of the RDBM.	
 ---------------------------------------------------------------------*/
#define RDB_NO_GRADWARP                0x0001	/* 1 */
#define RDB_NO_FERMI                   0x0002	/* 2 */
#define RDB_ZCHOP                      0x0004	/* 4 */
#define RDB_YCHOP                      0x0008	/* 8 */
#define RDB_IIC                        0x0010	/* 16 */
#define RDB_CSI                        0x0020	/* 32 */
#define RDB_HS                         0x0040	/* 64 */
#define RDB_SPECTRO                    0x0080   /* 128 */
#define RDB_IMAGE_CHECKSUM             0x0100   /* 256 */
#define RDB_NOREC_CHECKSUM             0x0200   /* 512 */
#define RDB_GRADWARP_USE_FILE          0x0400   /* 1024 */
#define RDB_USE_FLIPTABLE              0x0800   /* 2048 */
#define RDB_CERD_USE_FLIP_SSP          0x1000   /* 4096 */
#define RDB_PSIR_CORRECTION            0x2000   /* 8192 MRIge65943 */
#define RDB_MCSI					   0x2020   /* 8224 Phase Array MultiVoxel CSI -- Anish Jacob 102705*/
#define RDB_SINGLE_PHASE_INFO          0x4000   /* 16384 */


/*---------------------------------------------------------------------
 | Define the different gradwarp types.
 ---------------------------------------------------------------------*/
#define RDB_GWTYPE_NONE                0
#define RDB_GWTYPE_PHASE               1
#define RDB_GWTYPE_FREQ                2
#define RDB_GWTYPE_RADIAL              3

/*--------------------------------------------------------*/
/* Gradwarp Processing Type                               */
/*--------------------------------------------------------*/
#define RDB_GW_TYPE1            1  /* spherical harmonic correction     */
#define RDB_GW_TYPE2            2  /* polynomical correction            */
#define RDB_GW_TYPE3            3  /* no correction                     */
#define RDB_GW_TYPE4            4  /* zaxis only ?                      */

/*---------------------------------------------------------------------
 | Define a few maximums for number of echoes, slices, 
 | dabs, and the I/O packet size
 ---------------------------------------------------------------------*/
#define RDB_MAX_SLICES                 GEMRI_MAXNOSLICES
#define RDB_MAX_SLICES_MULTIPHASE      10000
#define RDB_MAX_PASSES                 RDB_MAX_SLICES
#define RDB_MAX_ECHOES                 16
#define RDB_IOPACKET_SIZE              sizeof(RDB_IO_PACKET)
#define RDB_MAX_DABS                   1

/*---------------------------------------------------------------------
 |	Value of the dab board.
 ---------------------------------------------------------------------*/
#define DAB_VALUE                      0

/*---------------------------------------------------------------------
 | rdb_hdr_file_contents
 | Data type of locked data set.
 ---------------------------------------------------------------------*/
#define RDB_FILE_EMPTY                 0
#define RDB_FILE_NOREC                 1
#define RDB_FILE_RAW                   2

/*---------------------------------------------------------------------
 | Constants for rdb_tape_disk routine.
 ---------------------------------------------------------------------*/
#define RDB_RET_RUN                    0
#define RDB_OVERWRITE                  1
#define RDB_NOOVERWRITE                2

/*---------------------------------------------------------------------
 | rdb_hdr_dacq_ctrl
 | Control bit definitions for how the data was played out by the psd.
 ---------------------------------------------------------------------*/
#define RDB_RAW_COLLECT                0x0001	/* 1 */
#define RDB_FLIP_PHASE_EVEN            0x0002	/* 2 */
#define RDB_FLIP_PHASE_ODD             0x0004	/* 4 */
#define RDB_FLIP_FREQ_EVEN             0x0008	/* 8 */
#define RDB_FLIP_FREQ_ODD              0x0010	/* 16 */
#define RDB_RAW_WITHOUT_SSP            0x0020	/* 32 */
#define RDB_RAW_WRAP_AROUND            0x0040	/* 64 */
#define RDB_USER_PROCESSING            0x0080   /* 128 */
#define RDB_CARDIAC_MMODE              0x0100   /* 256 */
#define RDB_FASTCINE		       0x0200   /* 512 */ /* used in dacq_tps_init.c
							for fastcine packet */
#define RDB_FCINE_ET                   Ox0400   /* 1024 */ /*MRIge56094 used by CERD for fcine_ET */
#define RDB_PASS_THROUGH_CERD	       0x0800   /* 2048 */
#ifndef RDB_CERD_CONSTANT_FILTER
#define RDB_CERD_CONSTANT_FILTER       0x1000   /* 4096 */ /* MRIge61012  */
#endif

/*---------------------------------------------------------------------
 | rdb_hdr_exec_ctrl
 | Control bit definitions for what results the tps will transfer to the host.
 ---------------------------------------------------------------------*/
#define RDB_AUTO_DISPLAY               0x0001	/* 1 */
#define RDB_AUTO_LOCK                  0x0002	/* 2 */
#define RDB_AUTO_PERM                  0x0004	/* 4 */
#define RDB_XFER_IM                    0x0008	/* 8 */
#define RDB_SAVE_IM                    0x0010	/* 16 */
#define RDB_TAPE_LOCK                  0x0020	/* 32 */
#define RDB_INTERMEDIATE               0x0040	/* 64 */
#define RDB_OVERRIDE_BROADCAST         0x0080	/* 128 */
#define RDB_OVERRIDE_IMG_INSTALL       0x0100	/* 256 */
#define RDB_OVERRIDE_AUTODISPLAY       0x0200	/* 512 */
#define RDB_RTD_XFER_IM_REMOTE         0x0400   /* 1024 */
#define RDB_RTD_SCAN                   0x0800   /* 2048 */
#define RDB_REF_SCAN                   0x1000   /* 4096 */
#define RDB_DONT_WRITE_OR_INSTALL      0x2000   /* 8192 */
#define RDB_RTD_XFER_ALL_IM_PER_PASS   0x4000   /* 16384 */
#define RDB_XFER_IMG_RIR               0x8000   /* 32768 */

/*---------------------------------------------------------------------
 | rdb_hdr_recon_ctrl
 | Control bit definitions for determining what type of images tps will cresate.
 ---------------------------------------------------------------------*/
#define RDB_MAG_IM                     0x0001	/* 1 */
#define RDB_PHASE_IM                   0x0002	/* 2 */
#define RDB_I_IM                       0x0004	/* 4 */
#define RDB_Q_IM                       0x0008	/* 8 */
#define RDB_COMPRESSION                0x0010	/* 16 */
#define RDB_GRID_ON                    0x0020   /* 32 */
                                                /* 64 */

/* the following "raw data mode" definitions describe new bit positions
   being used in rdb_hdr_recon_ctrl.  These bits will be copied from
   rdb_hdr_recon_ctrl into the control_flag at the beginning of
   rc_recon_seg.c
   If the SKIP_ALL_RECON bit is set, all of the SKIP bits will
   be set in the control_flag.
*/
#define RDB_SKIP_ALL_RECON             0x0080   /* 128 */
#define RDB_SKIP_ROW_FFT               0x0100   /* 256 */
#define RDB_SKIP_COL_FFT               0x0200   /* 512 */
#define RDB_SKIP_HALF_FOURIER          0x0400   /* 1024 */
#define RDB_SKIP_FERMI                 0x0800   /* 2048 */
#define RDB_SKIP_NEX_SCALE             0x1000   /* 4096 */
#define RDB_SKIP_IMAGE_SCALE           0x2000   /* 8192 */
#define RDB_SKIP_3DJOB_FFT             0x4000   /* 16384 */
#define RDB_UNUSED                     0x8000   /* 32768 */

/* Previous flags are set by PSD through rdb_hdr_recon_ctrl
   (limited to 16 bits).  Here we define additional recon
   control flags for internal recon use.
 */
#define HECHO_SMOOTH                  0x10000
#define ASSET_CENTER                  0x20000
#define EPI_BASELINE_CORRECT          0x40000

/*---------------------------------------------------------------------
 | rdb_hdr_fd_ctrl
 | Control bits for feeder.
 ---------------------------------------------------------------------*/
#define RDB_FD_DF                      0x0001	/* 1 */
#define RDB_FD_UNLOCKED                0x0002	/* 2 */
#define RDB_FD_ALGOR                   0x0004	/* 4 */
#define RDB_FD_VALIDATE                0x0008	/* 8 */
#define RDB_FD_DEBUG_SS                0x0010	/* 16 */
#define RDB_FD_TE                      0x0020	/* 32 */
#define RDB_FD_ISR_ALGR                0x0040	/* 64 */


#define RDB_FD_SINK_DF                 0x0001
#define RDB_FD_SOURCE_UNLOCKED         0x0002
#define RDB_FD_SOURCE_ALGOR            0x0004
#define RDB_FD_5XVALIDATE              0x0008
#define RDB_FD_5XDEBUG_SS              0x0010
#define RDB_FD_TE_ENABLE               0x0020
#define RDB_FD_ISR_ALGOR               0x0040
#define RDB_FD_SOURCE_LOCKED           0x0080
#define RDB_FD_SOURCE_RCVR             0x0100
#define RDB_FD_SINK_DAB                0x0200
#define RDB_FD_EXTERNAL_SSP            0x0400
#define RDB_FD_DEBUG                   0x8000

#define RDB_FD_AUTOSTART               0x1000
#define RDB_FD_CHKSUM                  0x2000


/*---------------------------------------------------------------------
 | RDBM constants used by rdbm functions.
 ---------------------------------------------------------------------*/
#define RDB_VALID_LOGO                 "GE_MED_NMR"
#define RDB_INVALID_LOGO               "INVALIDNMR"
#define RDB_MAX_OPS                    4
#define RDB_ISVALID                    0
#define RDB_INVALID                   -2

#define RDB_HDR_LOCK_PASS              00
#define RDB_HDR_LOCK_SLICE             01
#define RDB_HDR_LOCK_TAPE              02

#define RDB_DS_SCAN                    -3
#define RDB_RAWFF_SCAN                 -2
#define RDB_RAWFF_TYPE                 -2
#define RDB_RAWFF_ALL                  -1
#define RDB_NORMAL_SCAN                 0

#define PHASE_ORDERED                  0
#define TIME_ORDERED                   1

#define RDB_POOL_FILE                  "HEADER_POOL"
#define RDB_DIR_FILE                   "/usr/g/mrraw"
#define RDB_HDR_FILE                   "/usr/g/mrraw/HEADER_POOL"
#define RDB_LCK_FILE                   "/usr/g/mrraw/Pxxxxx"
#define RDBM_NMRID                     "RDBM_xxxxxx"

#define DATA_AREA                      0
#define SSP_AREA                       1
#define UDA_AREA                       2


/*---------------------------------------------------------------------
 | rdb_hdr_v_type
 | Define constants for Vascular
 ---------------------------------------------------------------------*/
#define RDB_VASC                       0x00000001	/* 1 */
#define RDB_PC                         0x00000002	/* 2 */
#define RDB_2SETS                      0x00000008	/* 8 */
#define RDB_ALIAS                      0x00000010	/* 16 */
#define RDB_PHASE1                     0x00000020	/* 32 */
#define RDB_PHASE2                     0x00000040	/* 64 */
#define RDB_NMASK                      0x00000080	/* 128 */
#define RDB_MAG                        0x00000100	/* 256 */
#define RDB_XFLOW                      0x00000200	/* 512 */
#define RDB_YFLOW                      0x00000400	/* 1024 */
#define RDB_ZFLOW                      0x00000800	/* 2048 */
#define RDB_SLICE                      0x00001000	/* 4096 */
#define RDB_READOUT                    0x00002000	/* 8192 */
#define RDB_PHASE                      0x00004000	/* 16384 */
#define RDB_VINNIE1                    0x00008000	/* 32768 */
#define RDB_VINNIE2                    0x00010000	/* 65536 */
#define RDB_VINNIE3                    0x00020000	/* 131072 */
#define RDB_PROJ10                     0x00080000	/* 524288 */
#define RDB_PROJ5                      0x00100000	/* 1048576 */
#define RDB_NMASK2                     0x00200000	/* 2097152 */
#define RDB_QSHIM                      0x00400000   /* 4194304 */

/*---------------------------------------------------------------------
 |  Constants used to identify vascular image types
 ---------------------------------------------------------------------*/
#define VASC_PROJ                      0x00000200	/* 512 */
#define VASC_ZPHASE                    0x00000400	/* 1024 */
#define VASC_YPHASE                    0x00000800	/* 2048 */
#define VASC_XPHASE                    0x00001000	/* 4096 */
#define VASC_MAG                       0x00002000	/* 8192 */
#define VASC_VASC                      0x00004000	/* 16384 */
#define VASC_COLLAPSE                  0x00008000	/* 32768 */

/*---------------------------------------------------------------------
 |  Constants used to identify variable view sharing
 ---------------------------------------------------------------------*/
/* rdb_hdr_vvsmode */
#define VV_ON              1
#define VV_NN              2
#define VV_LI              4
#define VV_WRAP            8
#define VV_DIASTOLE       16
#define VV_NOREC_VVSHARE  32

/*---------------------------------------------------------------------
 |  Fat and Water Dual Recon
 ---------------------------------------------------------------------*/
/* rdb_hdr_fatwater */

/*---------------------------------------------------------------------
 Bit Name                Definition
 0-2 FW_IMAGE_BIT        used for fat/water/original image
 3   FW_FAT_WATER_SWAP   the flag to swap "fat" and "water"
 4-6 FW_PHASE_DIFF_VALU  used for phase difference value
 ---------------------------------------------------------------------*/

#define FW_FATWATER_OFF    0x0000  /* fat/water recon off */
#define FW_WATER_IMAGE     0x0001  /* water image */
#define FW_FAT_IMAGE       0x0002  /* fat image */
#define FW_ORIGINAL_IMAGE  0x0004  /* original image */
#define FW_IMAGE_BIT_MASK  0x0007  /* mask the bit 0-2 */

#define FW_IS_FATWATER_ON(ARG) (((ARG) & FW_IMAGE_BIT_MASK) != FW_FATWATER_OFF)
    /*****************************************************************************/
    /*                                                                           */
    /* if fat/water is on, return 1.                                             */
    /* else fat/water is off, return 0.                                          */
    /*                                                                           */
    /*****************************************************************************/
#define FW_GET_IMAGE_TYPE_VALUE(ARG) (((ARG) & FW_IMAGE_BIT_MASK))
#define FW_IS_IMAGE_TYPE_SELECTED(ARG, FW_TYPE) ((((ARG) & FW_IMAGE_BIT_MASK) & FW_TYPE ) == FW_TYPE)

#define FW_FAT_WATER_SWAP  0x0008  /* swap real part and imag. part */
    /*****************************************************************************/
    /*                                                                           */
    /* FAT                                                                       */
    /*  ^            FW_REAL_IMAG_SWAP:OFF                                       */
    /*  |__>WATER                                                                */
    /*                                                                           */
    /* WATER                                                                     */
    /*  ^            FW_REAL_IMAG_SWAP:ON                                        */
    /*  |__>FAT                                                                  */
    /*                                                                           */
    /*****************************************************************************/
#define FW_IS_FAT_WATER_SWAP(ARG) (((ARG) & FW_FAT_WATER_SWAP) >> 3)

#define FW_1_2_PI_PHASE_DIFF     0x0000  /* fat/water phase difference is 1/2*PI */
#ifndef FW_1_4_PI_PHASE_DIFF
#define FW_1_4_PI_PHASE_DIFF     0x0001  /* fat/water phase difference is 1/4*PI */
#endif
#ifndef FW_2_3_PI_PHASE_DIFF
#define FW_2_3_PI_PHASE_DIFF     0x0002  /* fat/water phase difference is 2/3*PI */
#endif
#ifndef FW_1_3_PI_PHASE_DIFF
#define FW_1_3_PI_PHASE_DIFF     0x0004  /* fat/water phase difference is 1/3*PI */
#endif
/* MRIhc06477 Dheeraj@extenprise */
#define FW_PHASE_DIFF_VALUE_MASK 0x0070  /* mask the bit 4-6 */

#define FW_GET_PHASE_DIFF_VALUE(ARG) (((ARG) & FW_PHASE_DIFF_VALUE_MASK) >> 4)

    /*****************************************************************************/
    /*                                                                           */
    /*   phase_diff_value = FW_GET_PHASE_DIFF_VALUE(rdb_hdr_fatwater);           */
    /*                                                                           */
    /*   phase_diff_value: FW_1_2_PI_PHASE_DIFF                                  */
    /*                       (fat/water phase difference is 1/2*PI)              */
    /*                   : FW_1_4_PI_PHASE_DIFF                                  */
    /*                       (fat/water phase difference is 1/4*PI)              */
    /*                   : FW_2_3_PI_PHASE_DIFF                                  */
    /*                       (fat/water phase difference is 2/3*PI)              */
    /*                                                                           */
    /*****************************************************************************/

/*--------------------------------------------------------*/
/* rdb_hdr_fiestamlf                                      */
/* Definition for MFO FIESTA Recon     05/08/01 N.Adachi  */
/*--------------------------------------------------------*/
#define RDB_FIESTA_ECHO_DFT 0x0100 /* 9th bit:256 */
#define RDB_FIESTA_FASTCINE 0x0200 /* 10th bit:512 */

#define FIESTA_PROC_TYPE_MASK 0x00FF /* 255 */
#define RDB_FIESTA_AVE 1 /* combine by averaging */
#define RDB_FIESTA_RMS 2 /* combine by root mean square */
#define RDB_FIESTA_MIP 3 /* combine by MIP */
#define RDB_FIESTA_1ST_LAST 4 /* YMSmr04091. combine 1st and last echo */
#define RDB_FIESTA_1ST_ONLY 5 /* YMSmr05612. combine 1st echo only*/

/*--------------------------------------------------------*/
/* rdb_hdr_dfmctrl                                        */
/* Modified for MFO DFM support             09/13/01 N.A  */
/*--------------------------------------------------------*/
#define RDB_DFM_ON 0x0001     /* 1st bit:DFM on/off */
#define RDB_DFM_USESUM 0x0002 /* 2nd bit:DFM TYPE; =1: Use Summation, =0:Non Use */

/*--------------------------------------------------------*/
/* rdb_hdr_dwnav_cor                                      */
/* YMSmr03584                                             */
/* Definition for Nav echo phase correction 02/22/02 N.A  */
/*--------------------------------------------------------*/
#define RDB_DWNAV_NAVCOR 0x0001
#define RDB_DWNAV_PHASESHIFT 0x0002

/*--------------------------------------------------------*/
/* rdb_hdr_clariview_type                                 */
/* YMSmr                                                  */
/* Definition for distinction between ogirin filter       */
/*                                and clariview filter    */
/*--------------------------------------------------------*/
#define OG_FLT_TYPE_OFFSET 100

/*--------------------------------------------------------*/
/* rdb_hdr_herawflt                                       */
/* Half Echo Recon Mode (default = 0)                     */
/* 0: Standard Homodyne II Recon (Real image created)     */
/* 1: Homodyne II + New filter   (Real image created)     */
/* 2: 0 Fill + HPF + New filter  (Magnitude image created)*/
/*--------------------------------------------------------*/
#define RDB_RAWFLT_STANDARD          0
#define RDB_RAWFLT_HOMODYNEII_NEWFLT 1
#define RDB_RAWFLT_0FILL_HPF_NEWFLT  2
#define RDB_RAWFLT_NEWFLT_HOMODYNEII 3
#define RDB_RAWFLT_0FILL_NEWFLT      4


/*--------------------------------------------------------*/
/* rdb_hdr_multiphase_type                                */
/* Definitions to show acq order                          */
/*--------------------------------------------------------*/

#define INTERLEAVED_TYPE 0
#define SEQUENTIAL_TYPE  1

/*--------------------------------------------------------*/
/* rdb_hdr_swiftenable                                    */
/* Definitions to values rhswiftenable can take           */
/*--------------------------------------------------------*/

#define ENABLE_SWIFT 1
#define SWITCH_RECEIVER_WEIGHTS  2
/**********************************************************************
 *
 *	The following is the typedef of the raw header structure.
 *
 **********************************************************************/

/*---------------------------------------------------------------------
 |	Multiple receiver structure
 ---------------------------------------------------------------------*/
typedef struct
{
	short   start_rcv;
	short   stop_rcv;
}       RDB_MULTI_RCV_TYPE;


typedef struct _RDB_HEADER_REC
{
   float    rdb_hdr_rdbm_rev;
   long     rdb_hdr_run_int;           /* Rdy pkt Run Number */
   short    rdb_hdr_scan_seq;          /* Rdy pkt Sequence Number */
   char     rdb_hdr_run_char [6];      /* Rdy pkt Run no in char */
   char     rdb_hdr_scan_date [10];    /*  */
   char     rdb_hdr_scan_time [8];     /*  */
   char     rdb_hdr_logo [10];         /* rdbm  used to verify file */

   short    rdb_hdr_file_contents;     /* Data type 0=emp 1=nrec 2=rw 	0, 1, 2 */
   short    rdb_hdr_lock_mode;         /* unused */
   short    rdb_hdr_dacq_ctrl;         /* rhdacqctrl bit mask		15 bits */
   short    rdb_hdr_recon_ctrl;        /* rhrcctrl bit mask 		15 bits */
   short    rdb_hdr_exec_ctrl;         /* rhexecctrl bit mask 		15 bits */
   short    rdb_hdr_scan_type;         /* bit mask 			15 bits */
   short    rdb_hdr_data_collect_type; /* rhtype  bit mask		15 bits */
   short    rdb_hdr_data_format;       /* rhformat  bit mask 		15 bits */
   short    rdb_hdr_recon;             /* rhrecon proc-a-son recon	0 - 100 */
   short    rdb_hdr_datacq;            /* rhdatacq proc-a-son dacq */

   short    rdb_hdr_npasses;           /* rhnpasses  passes for a scan  0 - 256 */
   short    rdb_hdr_npomp;             /* rhnpomp  pomp group slices  	1,2 */
   short    rdb_hdr_nslices;           /* rhnslices  slices in a pass	0 - 256 */
   short    rdb_hdr_nechoes;           /* rhnecho  echoes of a slice	1 - 32 */
   short    rdb_hdr_navs;              /* rhnavs  num of excitiations  	1 - 32727 */
   short    rdb_hdr_nframes;           /* rhnframes  yres		0 - 1024 */
   short    rdb_hdr_baseline_views;    /* rhbline  baselines		0 - 1028 */
   short    rdb_hdr_hnover;            /* rhhnover  overscans		0 - 1024 */
   unsigned short  rdb_hdr_frame_size; /* rhfrsize  xres 		0 - 32768 */
   short    rdb_hdr_point_size;        /* rhptsize			2 - 4 */

   short    rdb_hdr_vquant;            /* rhvquant 3d volumes		1 */

   short    rdb_hdr_cheart;            /* RX Cine heart phases 		1 - 32 */
   float    rdb_hdr_ctr;               /* RX Cine TR in sec		0 - 3.40282e38*/
   float    rdb_hdr_ctrr;              /* RX Cine RR in sec 		0 - 30.0 */

   short    rdb_hdr_initpass;          /* rhinitpass allocate passes    0 - 32767 */
   short    rdb_hdr_incrpass;          /* rhincrpass tps autopauses	0 - 32767 */

   short    rdb_hdr_method_ctrl;       /* rhmethod  0=recon, 1=psd	0, 1 */
   unsigned short    rdb_hdr_da_xres;  /* rhdaxres 			0 - 32768 */
   short    rdb_hdr_da_yres;           /* rhdayres 			0 - 2049 */
   short    rdb_hdr_rc_xres;           /* rhrcxres 			0 - 1024 */
   short    rdb_hdr_rc_yres;           /* rhrcyres 			0 - 1024 */
   short    rdb_hdr_im_size;           /* rhimsize 			0 - 512 */
   long     rdb_hdr_rc_zres;           /* power of 2 > rhnslices	0 - 128 */

   /*
      These variables are changed to unsigned int to support greater than 2GB of BAM.
      Throughout RECON the same change has been made by using the typedef BAM_size 
      defined in bam.h
      */
   unsigned long int rdb_hdr_raw_pass_size;     /* rhrawsize 			0 - 2147483647*/
   unsigned long int rdb_hdr_sspsave;           /* rhsspsave 			0 - 2147483647*/
   unsigned long int rdb_hdr_udasave;           /* rhudasave 			0 - 2147483647*/
 
   float    rdb_hdr_fermi_radius;      /* rhfermr fermi radius		0 - 3.40282e38*/
   float    rdb_hdr_fermi_width;       /* rhfermw fermi width		0 - 3.40282e38*/
   float    rdb_hdr_fermi_ecc;         /* rhferme fermi excentiricty	0 - 3.40282e38*/
   float    rdb_hdr_clip_min;          /* rhclipmin 4x IP limit		+-16383 */
   float    rdb_hdr_clip_max;          /* rhclipmax 4x IP limit		+-16383 */
   float    rdb_hdr_default_offset;    /* rhdoffset default offset = 0	+-3.40282e38 */
   float    rdb_hdr_xoff;              /* rhxoff scroll img in x 	+-256 */
   float    rdb_hdr_yoff;              /* rhyoff scroll img in y	+-256 */
   float    rdb_hdr_nwin;              /* rhnwin hecho window width	0 - 256 */
   float    rdb_hdr_ntran;             /* rhntran hecho trans width	0 - 256 */
   float    rdb_hdr_scalei;            /* PS rhscalei			+-3.40282e38 */
   float    rdb_hdr_scaleq;            /* PS rhscaleq  def = 0		+-3.40282e38 */
   short    rdb_hdr_rotation;          /* RX 0 90 180 270 deg		0 - 3 */
   short    rdb_hdr_transpose;         /* RX 0, 1 n / y transpose 	0 - 1*/
   short    rdb_hdr_kissoff_views;     /* rhblank zero image views	0 - 512 */
   short    rdb_hdr_slblank;           /* rhslblank  slice blank 3d	0 - 128 */ 
   short    rdb_hdr_gradcoil;          /* RX 0=off 1=Schnk 2=Rmr	0 - 2 */
   short    rdb_hdr_ddaover;           /* rhddaover unused */
 
   short    rdb_hdr_sarr;              /* SARR bit mask 		15 bits */
   short    rdb_hdr_fd_tr;             /* SARR feeder timing info */
   short    rdb_hdr_fd_te;             /* SARR feeder timing info */
   short    rdb_hdr_fd_ctrl;           /* SARR control of feeder */
   short    rdb_hdr_algor_num;         /* SARR df decimation ratio */
   short    rdb_hdr_fd_df_dec;         /* SARR which feeder algor */
 
   RDB_MULTI_RCV_TYPE rdb_hdr_dab[4];  /* rhdab0s rhdab0e st, stp rcv 	0 - 15 */
 
   float    rdb_hdr_user0;             /* rhuser0 			+-3.40282e38 */
   float    rdb_hdr_user1;             /* rhuser1 			+-3.40282e38 */
   float    rdb_hdr_user2;             /* rhuser2 			+-3.40282e38 */
   float    rdb_hdr_user3;             /* rhuser3 			+-3.40282e38 */
   float    rdb_hdr_user4;             /* rhuser4 			+-3.40282e38 */
   float    rdb_hdr_user5;             /* rhuser5 			+-3.40282e38 */
   float    rdb_hdr_user6;             /* rhuser6 			+-3.40282e38 */
   float    rdb_hdr_user7;             /* rhuser7 			+-3.40282e38 */
   float    rdb_hdr_user8;             /* rhuser8 			+-3.40282e38 */
   float    rdb_hdr_user9;             /* rhuser9 			+-3.40282e38 */
   float    rdb_hdr_user10;            /* rhuser10			+-3.40282e38 */
   float    rdb_hdr_user11;            /* rhuser11			+-3.40282e38 */
   float    rdb_hdr_user12;            /* rhuser12			+-3.40282e38 */
   float    rdb_hdr_user13;            /* rhuser13			+-3.40282e38 */
   float    rdb_hdr_user14;            /* rhuser14			+-3.40282e38 */
   float    rdb_hdr_user15;            /* rhuser15			+-3.40282e38 */
   float    rdb_hdr_user16;            /* rhuser16			+-3.40282e38 */
   float    rdb_hdr_user17;            /* rhuser17			+-3.40282e38 */
   float    rdb_hdr_user18;            /* rhuser18			+-3.40282e38 */
   float    rdb_hdr_user19;            /* rhuser19			+-3.40282e38 */
   
   long     rdb_hdr_v_type;	       /* rhvtype  bit mask		31 bits */
   float    rdb_hdr_v_coefxa;	       /* RX x flow direction control	0 - 4 */
   float    rdb_hdr_v_coefxb;	       /* RX x flow direction control	0 - 4 */
   float    rdb_hdr_v_coefxc;	       /* RX x flow direction control	0 - 4 */
   float    rdb_hdr_v_coefxd;	       /* RX x flow direction control	0 - 4 */
   float    rdb_hdr_v_coefya;	       /* RX y flow direction control	0 - 4 */
   float    rdb_hdr_v_coefyb;	       /* RX y flow direction control	0 - 4 */
   float    rdb_hdr_v_coefyc;	       /* RX y flow direction control	0 - 4 */
   float    rdb_hdr_v_coefyd;	       /* RX y flow direction control	0 - 4 */
   float    rdb_hdr_v_coefza;	       /* RX z flow direction control	0 - 4 */
   float    rdb_hdr_v_coefzb;	       /* RX z flow direction control	0 - 4 */
   float    rdb_hdr_v_coefzc;	       /* RX z flow direction control	0 - 4 */
   float    rdb_hdr_v_coefzd;	       /* RX z flow direction control	0 - 4 */
   float    rdb_hdr_vm_coef1;	       /* RX weight for mag image 1	0 - 1 */
   float    rdb_hdr_vm_coef2;	       /* RX weight for mag image 2	0 - 1 */
   float    rdb_hdr_vm_coef3;	       /* RX weight for mag image 3	0 - 1 */
   float    rdb_hdr_vm_coef4;	       /* RX weight for mag image 4	0 - 1 */
   float    rdb_hdr_v_venc;            /* RX vel encodeing cm / sec	0.001 - 5000 */
   
   float    spectral_width;            /* specwidth  filter width kHz	500 - 3355432 */
   short    csi_dims;                  /* spectro */
   short    xcsi;                      /* rhspecrescsix  		2 - 64 */
   short    ycsi;                      /* rhspecrescsiy  		2 - 64 */
   short    zcsi;                      /* spectro */
   float    roilenx;                   /* RX x csi volume dimension */
   float    roileny;                   /* RX y csi volume dimension */
   float    roilenz;                   /* RX z csi volume dimension */
   float    roilocx;                   /* RX x csi volume center */
   float    roilocy;                   /* RX y csi volume center */
   float    roilocz;                   /* RX z csi volume center */
   float    numdwell;                  /* specdwells			0 - 3.40282e38*/

   long     rdb_hdr_ps_command;	       /* PS internal use only	*/
   long     rdb_hdr_ps_mps_r1;         /* PS MPS R1 setting  		1 - 7 */
   long     rdb_hdr_ps_mps_r2;	       /* PS MPS R2 setting		1 - 30 */
   long     rdb_hdr_ps_mps_tg; 	       /* PS MPS Transmit gain setting	0 - 200*/
   long     rdb_hdr_ps_mps_freq;       /* PS MPS Center frequency hz	+-3.40282e38 */
   long     rdb_hdr_ps_aps_r1; 	       /* PS APS R1 setting		1 - 7 */
   long     rdb_hdr_ps_aps_r2; 	       /* PS APS R2 setting		1 - 30 */
   long     rdb_hdr_ps_aps_tg; 	       /* PS APS Transmit gain setting	0 - 200*/
   long     rdb_hdr_ps_aps_freq;       /* PS APS Center frequency hz	+-3.40282e38 */
   float    rdb_hdr_ps_scalei; 	       /* PS rational scaling 		+-3.40282e38 */
   float    rdb_hdr_ps_scaleq; 	       /* PS unused */			
   long     rdb_hdr_ps_snr_warning;    /* PS noise test 0=16 1=32 bits	0, 1 */
   long     rdb_hdr_ps_aps_or_mps;     /* PS prescan order logic	0 - 5 */
   long     rdb_hdr_ps_mps_bitmap;     /* PS bit mask			4 bits*/
   char     rdb_hdr_ps_powerspec [256];/* PS                             */
   long     rdb_hdr_ps_filler1;        /* PS filler */
   long     rdb_hdr_ps_filler2;        /* PS filler */
   float    obsolete1[16];             /* PS mean noise each receiver   +-3.40282e38 */
   float    obsolete2[16];             /* PS noise calc for muti rec  	+-3.40282e38 */

   short    halfecho;                  /* spectro full, half echo       0, 1 */
   /* 858 bytes */

   /* New fields 02-19-92 */
   short    rdb_hdr_im_size_y;         /* rh???? 			0 - 512 */
   long     rdb_hdr_data_collect_type1;/* rh???? bit mask		31 bits */
   float    rdb_hdr_freq_scale;        /* rh???? freq k-space step      +-3.40282e38 */
   float    rdb_hdr_phase_scale;       /* rh???? freq k-space step      +-3.40282e38 */
   /* 14 bytes */
   short    rdb_hdr_ovl;               /* rhovl - overlaps for MOTSA */ 

   /* Phase Correction Control Param. */
   short    rdb_hdr_pclin;             /* Linear Corr. 0:off, 1:linear, 2:polynomial */
   short    rdb_hdr_pclinnpts;         /* fit number of points */
   short    rdb_hdr_pclinorder;        /* fit order */
   short    rdb_hdr_pclinavg;          /* linear phase corr avg 0:off, 1:on */
   short    rdb_hdr_pccon;             /* Const Corr. 0:off, 1:Ky spec., 2:polyfit(2/ilv), 3:polyfit(1/ilv) */
   short    rdb_hdr_pcconnpts;         /* fit number of points */
   short    rdb_hdr_pcconorder;        /* fit order */
   short    rdb_hdr_pcextcorr;         /* external correction file 0:don't use, 1: use */
   short    rdb_hdr_pcgraph;           /* Phase Correction coef. image 0:off, 1:linear & constant */
   short    rdb_hdr_pcileave;          /* Interleaves to use for correction: 0=all, 1=only first */
   short    rdb_hdr_hdbestky;          /* bestky view for fractional Ky scan */
   short    rdb_hdr_pcctrl;            /* phase correction research control */
   short    rdb_hdr_pcthrespts;        /* 2..512 adjacent points */
   short    rdb_hdr_pcdiscbeg;         /* 0..512 beginning point to discard */
   short    rdb_hdr_pcdiscmid;         /* 0..512 middle point to discard */
   short    rdb_hdr_pcdiscend;         /* 0..512 ending point to discard */
   short    rdb_hdr_pcthrespct;        /* Threshold percentage */
   short    rdb_hdr_pcspacial;         /* Spacial best ref scan index 0..512 */
   short    rdb_hdr_pctemporal;        /* Temporal best ref scan index 0..512 */
   short    rdb_hdr_pcspare;           /* spare for phase correction */
   short    rdb_hdr_ileaves;           /* Number of interleaves */
   short    rdb_hdr_kydir;             /* Ky traversal dircetion 0: top-down, 1:center out */
   short    rdb_hdr_alt;               /* Alt read sign 0=no, 1=odd/even, 2=pairs */
   short    rdb_hdr_reps;              /* Number of scan repetitions */
   short    rdb_hdr_ref;               /* Ref Scan 0: off 1: on */

   float    rdb_hdr_pcconnorm;         /* Constant S term normalization factor */
   float    rdb_hdr_pcconfitwt;        /* Constant polyfit weighting factor */
   float    rdb_hdr_pclinnorm;         /* Linear   S term normalization factor */
   float    rdb_hdr_pclinfitwt;        /* Linear   polyfit weighting factor */

   float    rdb_hdr_pcbestky;          /* Best Ky location */

   /* VRG Filter param */
   long     rdb_hdr_vrgf;              /* control word for VRG filter */
   long     rdb_hdr_vrgfxres;          /* control word for VRGF final x resolution */


   /* Bandpass Asymmetry  Correction Param. */
   long     rdb_hdr_bp_corr;           /* control word for bandpass asymmetry */
   float    rdb_hdr_recv_freq_s;       /* starting frequency (+62.5) */
   float    rdb_hdr_recv_freq_e;       /* ending   frequency (-62.5) */

   long     rdb_hdr_hniter;            /* Selects the number of
                                     iterations used in homodyne processing */

   long     rdb_hdr_fast_rec;          /* Added for homodyne II, tells if
                                          teh fast receiver is being used
                                          and the lpf setting of teh fast
                                          receiver, 0: fast receiver off,
                                          1 - 5: lpf settings   */

   long     rdb_hdr_refframes;         /* total # of frames for ref scan */
   long     rdb_hdr_refframep;         /* # of frames per pass for a ref scan */
   long     rdb_hdr_scnframe;          /* total # of frames for a entire scan */
   long     rdb_hdr_pasframe;          /* # of frames per pass */

   unsigned long  rdb_hdr_user_usage_tag;    /* for spectro */
   unsigned long  rdb_hdr_user_fill_mapMSW;  /* for spectro */
   unsigned long  rdb_hdr_user_fill_mapLSW;  /* for Spectro */

   float    rdb_hdr_user20;            /* all following usercv are for spectro */
   float    rdb_hdr_user21;
   float    rdb_hdr_user22;
   float    rdb_hdr_user23;
   float    rdb_hdr_user24;
   float    rdb_hdr_user25;
   float    rdb_hdr_user26;
   float    rdb_hdr_user27;
   float    rdb_hdr_user28;
   float    rdb_hdr_user29;
   float    rdb_hdr_user30;
   float    rdb_hdr_user31;
   float    rdb_hdr_user32;
   float    rdb_hdr_user33;
   float    rdb_hdr_user34;
   float    rdb_hdr_user35;
   float    rdb_hdr_user36;
   float    rdb_hdr_user37;
   float    rdb_hdr_user38;
   float    rdb_hdr_user39;
   float    rdb_hdr_user40;
   float    rdb_hdr_user41;
   float    rdb_hdr_user42;
   float    rdb_hdr_user43;
   float    rdb_hdr_user44;
   float    rdb_hdr_user45;
   float    rdb_hdr_user46;
   float    rdb_hdr_user47;
   float    rdb_hdr_user48;

   short    rdb_hdr_pcfitorig;    /* Adjust view indexes if set so bestky view = 0 */
   short    rdb_hdr_pcshotfirst;  /* First view within an echo group used for fit  */
   short    rdb_hdr_pcshotlast;   /* Last view within an echo group used for fit   */
   short    rdb_hdr_pcmultegrp;   /* If = 1, force pts from other egrps to be used */
   short    rdb_hdr_pclinfix;     /* If = 2, force slope to be set to pclinslope   */
                                  /* If = 1, neg readout slope = pos readout slope */
   short    rdb_hdr_pcconfix;     /* If = 2, force slope to be set to pcconslope   */
                                  /* If = 1, neg readout slope = pos readout slope */
   float    rdb_hdr_pclinslope;   /* Value to set lin slope to if forced           */
   float    rdb_hdr_pcconslope;   /* Value to set con slope to if forced           */
   short    rdb_hdr_pccoil;       /* If 1,2,3,4, use that coil's results for all   */

   /* Variable View Sharing */
   short    rdb_hdr_vvsmode;      /* Variable view sharing mode */
   short    rdb_hdr_vvsaimgs;     /* number of original images */
   short    rdb_hdr_vvstr;        /* TR in microseconds */
   short    rdb_hdr_vvsgender;    /* gender: male or female */

   /* 3D Slice ZIP */
   short    rdb_hdr_zip_factor;   /* Slice ZIP factor: 0=OFF, 2, or 4 */

   /* Maxwell Term Correction Coefficients */
   float    rdb_hdr_maxcoef1a;    /* Coefficient A for flow image 1 */
   float    rdb_hdr_maxcoef1b;    /* Coefficient B for flow image 1 */
   float    rdb_hdr_maxcoef1c;    /* Coefficient C for flow image 1 */
   float    rdb_hdr_maxcoef1d;    /* Coefficient D for flow image 1 */
   float    rdb_hdr_maxcoef2a;    /* Coefficient A for flow image 2 */
   float    rdb_hdr_maxcoef2b;    /* Coefficient B for flow image 2 */
   float    rdb_hdr_maxcoef2c;    /* Coefficient C for flow image 2 */
   float    rdb_hdr_maxcoef2d;    /* Coefficient D for flow image 2 */
   float    rdb_hdr_maxcoef3a;    /* Coefficient A for flow image 3 */
   float    rdb_hdr_maxcoef3b;    /* Coefficient B for flow image 3 */
   float    rdb_hdr_maxcoef3c;    /* Coefficient C for flow image 3 */
   float    rdb_hdr_maxcoef3d;    /* Coefficient D for flow image 3 */

   long     rdb_hdr_ut_ctrl;      /* System utility control variable */
   short    rdb_hdr_dp_type;      /* EPI II diffusion control cv */

   short    rdb_hdr_arw;          /* Arrhythmia rejection window(percentage:1-100)*/

   short    rdb_hdr_vps;	  /* View Per Segment for FastCine */ 

   short    rdb_hdr_mcReconEnable;  /* N-Coil recon map */
   float    rdb_hdr_fov;          /* Auto-NCoil */

   long     rdb_hdr_te;            /* TE for first echo                     */
   long     rdb_hdr_te2;           /* TE for second and later echoes        */
   float    rdb_hdr_dfmrbw;        /* BW for navigator frames               */
   long     rdb_hdr_dfmctrl;       /* Control flag for dfm (0=off, other=on)*/
   long     rdb_hdr_raw_nex;       /* Uncombined NEX at start of recon      */
   long     rdb_hdr_navs_per_pass; /* Max. navigator frames in a pass       */
   long     rdb_hdr_dfmxres;       /* xres of navigator frames              */
   long     rdb_hdr_dfmptsize;     /* point size of navigator frames        */
   long     rdb_hdr_navs_per_view; /* Num. navigators per frame (tag table) */
   long     rdb_hdr_dfmdebug;      /* control flag for dfm debug            */
   float    rdb_hdr_dfmthreshold;  /* threshold for navigator correction    */

   /* Section added to support gridding */
   short    rdb_hdr_grid_control;	/* bit settings controlling gridding */
   short    rdb_hdr_b0map;		/* B0 map enable and map size */
   short    rdb_hdr_grid_tediff;	/* TE difference between b0 map arms */
   short    rdb_hdr_grid_motion_comp;	/* flag to apply motion compensation */
   float    rdb_hdr_grid_radius_a;	/* variable density transition */
   float    rdb_hdr_grid_radius_b;	/* variable density transition */
   float    rdb_hdr_grid_max_gradient;	/* Max gradient amplitude */
   float    rdb_hdr_grid_max_slew;	/* Max slew rate */
   float    rdb_hdr_grid_scan_fov;	/* Rx scan field of view */
   float    rdb_hdr_grid_a2d_time;	/* A to D sample time microsecs */
   float    rdb_hdr_grid_density_factor;	/* change factor for variable density */
   float    rdb_hdr_grid_display_fov;	/* Rx display field of view */

   short    rdb_hdr_fatwater;      /* for Fat and Water Dual Recon */
   short    rdb_hdr_fiestamlf;        /* MFO FIESTA recon control bit 16bits   */

   short    rdb_hdr_app;          /* Auto Post-Processing opcode */
   short    rdb_hdr_rhncoilsel;	 /* Auto-Ncoil */
   short    rdb_hdr_rhncoillimit; /* Auto-Ncoil */
   short    rdb_hdr_app_option; /* Auto Post_processing options */
   short    rdb_hdr_grad_mode;    /* Gradient mode in Gemini project */
   short    rdb_hdr_pfile_passes;    /* Num passes stored in a multi-pass Pfile (0 means 1 pass) */

   /* ASSET MRIge67407 */
   int      rdb_hdr_asset;
   int      rdb_hdr_asset_calthresh;
   float    rdb_hdr_asset_R;
   int      rdb_hdr_coilno;
   int      rdb_hdr_asset_phases;
   float    rdb_hdr_scancent;     /* Table position   */
   int      rdb_hdr_position;     /* Patient position */
   int      rdb_hdr_entry;        /* Patient entry    */
   float    rdb_hdr_lmhor;        /* Landmark         */
   int      rdb_hdr_last_slice_num;   
   float    rdb_hdr_asset_slice_R;   /* Slice reduction factor */
   float    rdb_hdr_asset_slabwrap;

   /* YMSmr03584 For Navigator echo phase correction on MFO2 */
   float    rdb_hdr_dwnav_coeff;   /* Coeff for amount of phase correction */
   short    rdb_hdr_dwnav_cor;     /* Navigator echo correction */
   short    rdb_hdr_dwnav_view;    /* Num of views of nav echoes */
   short    rdb_hdr_dwnav_corecho; /* Num of nav echoes for actual correction */
   short    rdb_hdr_dwnav_sview;   /* Start view for phase correction process */
   short    rdb_hdr_dwnav_eview;   /* End view for phase correction process */
   short    rdb_hdr_dwnav_sshot;   /* Start shot for delta phase estimation in nav echoes */
   short    rdb_hdr_dwnav_eshot;   /* End shot for delta phase estimation in nav echoes */

   /* 3D Windowing  */
   short    rdb_hdr_3dwin_type;    /* 0 = Modified Hanning, 1 = modified Tukey */
   float    rdb_hdr_3dwin_apod;    /* degree of apodization; 0.0 = boxcar, 1.0=hanning */
   float    rdb_hdr_3dwin_q;       /* apodization at ends, 0.0 = max, 1.0 = boxcar */
   
   /* AutoSCIC++, AutoClariview and Enhanced Recon paramaters */
   short    rdb_hdr_ime_scic_enable;   /* Surface Coil Intensity Correction: 1 if enabled */
   short    rdb_hdr_clariview_type;    /* Type of Clariview/Name of Filter */
   float    rdb_hdr_ime_scic_edge;     /* Edge paramaters for Enhanced Recon */
   float    rdb_hdr_ime_scic_smooth;   /* Smooth paramaters for Enhanced Recon */
   float    rdb_hdr_ime_scic_focus;    /* Focus paramaters for Enhanced Recon */
   float    rdb_hdr_clariview_edge;    /* Edge paramaters for clariview */
   float    rdb_hdr_clariview_smooth;  /* Smooth paramaters for clariview */
   float    rdb_hdr_clariview_focus;   /* Focus paramaters for clariview */
   float    rdb_hdr_scic_reduction;    /* Reduction paramater for SCIC */
   float    rdb_hdr_scic_gauss;        /* Gauss paramater for SCIC */
   float    rdb_hdr_scic_threshold;    /* Threshold paramater for SCIC */
   

   /*  parameters added for EC-TRICKS */
   long     rdb_hdr_ectricks_no_regions;	    /* Total no of regions acquired by PSD */
   long     rdb_hdr_ectricks_input_regions;     /* Total no of input regions for reordering */

   /* Smart Prescan */
   short    rdb_hdr_psc_reuse;         /* Header field for smart prescan */

   /*  K-space blanking fields */
   short    rdb_hdr_left_blank;
   short    rdb_hdr_right_blank;

   /*  multi-exciter support */
   short    rdb_hdr_acquire_type;      /* Acquire type information from CV */  

   short    rdb_hdr_retro_control;      /* Retrosective FSE phase correction control flag.
                                           This flag is initilaized by the PSD. */
   short    rdb_hdr_etl;                /* Added for Retrospective FSE phase correction. This
                                           variable has the ETL value set by the user. This 
                                           variable has a generic name, so that any other PSD who
                                           wants to send ETL value to Recon can use this variable.
                                        */
   short   rdb_hdr_pcref_start;        /* 1st view to use for dynamic EPI phase correction. */
   short   rdb_hdr_pcref_stop;         /* Last view to use for dynamic EPI phase correction. */
   short   rdb_hdr_ref_skip;           /* Number of passes to skip for dynamic EPI phase correction. */
   short   rdb_hdr_extra_frames_top;   /* Number of extra frames at top of K-space */
   short   rdb_hdr_extra_frames_bot;   /* Number of extra frames at bottom of K-space */  
   short    rdb_hdr_multiphase_type;   /* 0 = INTERLEAVED ,  1 = SEQUENTIAL */
   short    rdb_hdr_nphases;           /* Number of phases in a multiphase scan */
   short    rdb_hdr_pure;              /* PURE flag from psd */
   float    rdb_hdr_pure_scale;        /* Recon scale factor ratio for cal scan */
   int	    rdb_hdr_off_data;	       /* Byte offset to start of raw data (i.e size of POOL_HEADER)   */
   int	    rdb_hdr_off_per_pass;      /* Byte offset to start of rdb_hdr_per_pass of POOL_HEADER      */
   int	    rdb_hdr_off_unlock_raw;    /* Byte offset to start of rdb_hdr_unlock_raw of POOL_HEADER    */
   int	    rdb_hdr_off_data_acq_tab;  /* Byte offset to start of rdb_hdr_data_acq_tab of POOL_HEADER  */
   int	    rdb_hdr_off_nex_tab;       /* Byte offset to start of rdb_hdr_nex_tab of POOL_HEADER       */
   int	    rdb_hdr_off_nex_abort_tab; /* Byte offset to start of rdb_hdr_nex_abort_tab of POOL_HEADER */
   int	    rdb_hdr_off_tool;	       /* Byte offset to start of rdb_hdr_tool of POOL_HEADER          */
   int	    rdb_hdr_off_exam;	       /* Byte offset to start of rdb_hdr_exam of POOL_HEADER          */
   int	    rdb_hdr_off_series;	       /* Byte offset to start of rdb_hdr_series of POOL_HEADER        */
   int	    rdb_hdr_off_image;	       /* Byte offset to start of rdb_hdr_image of POOL_HEADER         */
   int	    rdb_hdr_off_ps;            /* Byte offset to start of rdb_hdr_ps of POOL_HEADER            */
   int	    rdb_hdr_off_spare_b;       /* spare */
   int      rdb_hdr_new_wnd_level_flag;  	/* New WW/WL algo enable/disable flag */	
   int	    rdb_hdr_wnd_image_hist_area;	/* Image Area % */
   float    rdb_hdr_wnd_high_hist;		/* Histogram Area Top */ 
   float    rdb_hdr_wnd_lower_hist;		/* Histogram Area Bottom */
   short    rdb_hdr_pure_filter;                /* PURE noise reduction on=1/off=0 */
   short    rdb_hdr_cfg_pure_filter;            /* PURE cfg file value */
   short    rdb_hdr_cfg_pure_fit_order;         /* PURE cfg file value */
   short    rdb_hdr_cfg_pure_kernelsize_z;      /* PURE cfg file value */
   short    rdb_hdr_cfg_pure_kernelsize_xy;     /* PURE cfg file value */
   short    rdb_hdr_cfg_pure_weight_radius;     /* PURE cfg file value */
   short    rdb_hdr_cfg_pure_intensity_scale;   /* PURE cfg file value */
   short    rdb_hdr_cfg_pure_noise_threshold;   /* PURE cfg file value */
  
  /* MART deblurring kernel (NDG) */
  float    rdb_hdr_wienera;  /* NB maintain alignment of floats */
  float    rdb_hdr_wienerb;
  float    rdb_hdr_wienert2;
  float    rdb_hdr_wieneresp;
  short    rdb_hdr_wiener;
  short    rdb_hdr_flipfilter;
  short    rdb_hdr_dbgrecon;
  short    rdb_hdr_ech2skip;
      
  int      rdb_hdr_tricks_type;                /* 0 = Subtracted, 1 = Unsubtracted */

   float    rdb_hdr_lcfiesta_phase; /* LC Fiesta */
   short    rdb_hdr_lcfiesta; /* LC Fiesta */
   short    rdb_hdr_herawflt;          /* Half echo raw data filter */
   short    rdb_hdr_herawflt_befnwin;  /* Half echo raw data filter */
   short    rdb_hdr_herawflt_befntran; /* Half echo raw data filter */
   float    rdb_hdr_herawflt_befamp;   /* Half echo raw data filter */
   float    rdb_hdr_herawflt_hpfamp;   /* Half echo raw data filter */
   short    rdb_hdr_heover;            /* Half echo over sampling */

   short    rdb_hdr_pure_correction_threshold;   /* PURE Correction threshold */

   int    rdb_hdr_swiftenable;		/* SWIFT enable/disable flag */
   short  rdb_hdr_numslabs;		/* Number of slabs to be used by TRICKS */		
   unsigned short int rdb_hdr_swiftcoilnos;	/* Number of coils to SWIFT between */

   int      rdb_hdr_ps_autoshim_status; 
         /*1 = autoshim successful, 0 = autoshim failed/smart/OFF */

   int      rdb_hdr_dynaplan_numphases; /* Number of phases for Dynamic Plan */
   
   short    rdb_hdr_excess [216]; /* free space for later expansion */

} RDB_HEADER_REC;
 
/*---------------------------------------------------------------------
 | Per Pass Table and Unlocked RAW Table
 |
 |	Per Pass DACQ table
 |        1. Pointers to data (data, ssp and uda)
 |        2. Index by (pass number - 1) in Data Acquisition Table.
 |
 |	Unlocked RAW table
 |        1. pointers to where UNLOCKED RAW DATA is in BAM
 |        2. index by (pass number - 1)
 |
 ---------------------------------------------------------------------*/
typedef struct
{
	long    bam_modifier;
	long    bam_address;
}       VME_ADDRESS;



typedef struct			       
{
	VME_ADDRESS dab_bam[RDB_MAX_DABS];
}       RDB_PASS_INFO_ENTRY;

typedef RDB_PASS_INFO_ENTRY RDB_PER_PASS_TAB[RDB_MAX_PASSES];

typedef RDB_PASS_INFO_ENTRY RDB_UNLOCK_RAW_TAB[RDB_MAX_PASSES];

/*---------------------------------------------------------------------
 |	DATA ACQUISITION TABLE
 |
 |	CVs used in setting this table up (by Scan):
 |       SI_RDBSLICE RH_SLPASS RH_SLTIME RH_SLLOC
 |
 ---------------------------------------------------------------------*/

typedef struct
{
	short   pass_number;	       /* which pass this slice is in */
	short   slice_in_pass;	       /* which slice in this pass */
	float   gw_point1[3];	       /* corner points of image */
	float   gw_point2[3];
	float   gw_point3[3];
	short	transpose;			/* The transpose value for every slice */
	short	rotate;			/* The rotate value for every slice */
	unsigned int swiftcoilno;	/* Coil to be used by ASSET for SWIFT type of scans */
}       RDB_SLICE_INFO_ENTRY;

typedef RDB_SLICE_INFO_ENTRY RDB_DATA_ACQ_TAB[SLICE_FACTOR * RDB_MAX_SLICES];

/*---------------------------------------------------------------------
 |	NEX Table
 ---------------------------------------------------------------------*/

/***********************/
/* gain table structure */

typedef struct
{
	short        range;          /* view range for this gain */
	float        gaini;          /* real part of gain */
	float        gainq;          /* imaginary part */
} RDB_GAIN_ENTRY;

typedef RDB_GAIN_ENTRY  RDB_GAIN_TAB[5]; /* max # of ranges */

 /* nex table structure */
 typedef short   RDB_NEX_ENTRY;
 typedef RDB_NEX_ENTRY   RDB_NEX_TAB[1026]; /* max da_yres */

typedef struct
{
	short int rdb_hdr_nex_size[1026];
}       RDB_NEX_TYPE;

/* -------------------------------- */
/*  Bandpass Asymmetry Definitions  */
/* -------------------------------- */

#define BP_ASYM_MAX_ROW_SIZE 546
#define BP_TIME_DOMAIN 0
#define BP_FREQ_DOMAIN 1
#define BP_MAX_FREQ (499.877)
#define BP_MIN_FREQ (-498.047)


/*---------------------------------------------------------------------
 |	RDBM HEADER
 ---------------------------------------------------------------------*/
#ifdef RECON_FLAG

	/*
	 * These are dummy arrays which must match the sizes of structures
	 * in include files toolsdata.h and imagedb.h
	 *
	 * If these structure change in size in these header files,
	 * the sizes of these arrays must be changed to match
         * and RDB_RDBM_REVISION must be incremented.
	 */
#ifndef TOOLSDATA_INCL
#define TOOLSDATA_INCL
	typedef char TOOLSDATA[2048];
#endif

#ifndef IMAGEDB_H_INCL     
#define IMAGEDB_H_INCL
	typedef char EXAMDATATYPE[1040];
	typedef char SERIESDATATYPE[2048];
	typedef char MRIMAGEDATATYPE[2048];
#endif

#endif   /* RECON_FLAG */

typedef struct
{
	RDB_HEADER_REC         rdb_hdr_rec;
	RDB_PER_PASS_TAB       rdb_hdr_per_pass;
	RDB_PER_PASS_TAB       rdb_hdr_unlock_raw;
	RDB_DATA_ACQ_TAB       rdb_hdr_data_acq_tab;
	RDB_NEX_TYPE           rdb_hdr_nex_tab;
	RDB_NEX_TYPE           rdb_hdr_nex_abort_tab;
}       RDBM_HEADER;

typedef struct
{
	TOOLSDATA              rdb_hdr_tool;         /* From toolsdata.h */
	EXAMDATATYPE           rdb_hdr_exam;         /* From imagedb.h */
	SERIESDATATYPE         rdb_hdr_series;       /* From imagedb.h */
	MRIMAGEDATATYPE        rdb_hdr_image;        /* From imagedb.h */
}       IMAGE_HEADER;

typedef struct
{                                                /* Byte offset stored at */
	RDB_HEADER_REC         rdb_hdr_rec;          /* offset = 0 */
	RDB_PER_PASS_TAB       rdb_hdr_per_pass;     /* rdb_hdr_off_per_pass */
	RDB_PER_PASS_TAB       rdb_hdr_unlock_raw;   /* rdb_hdr_off_unlock_raw */
	RDB_DATA_ACQ_TAB       rdb_hdr_data_acq_tab; /* rdb_hdr_off_data_acq_tab */
	RDB_NEX_TYPE           rdb_hdr_nex_tab;      /* rdb_hdr_off_nex_tab */
	RDB_NEX_TYPE           rdb_hdr_nex_abort_tab;/* rdb_hdr_off_nex_abort_tab */
	TOOLSDATA              rdb_hdr_tool;         /* rdb_hdr_off_tool */
    PRESCAN_HEADER         rdb_hdr_ps;           /* rdb_hdr_off_ps */
	EXAMDATATYPE           rdb_hdr_exam;         /* rdb_hdr_off_exam */
	SERIESDATATYPE         rdb_hdr_series;       /* rdb_hdr_off_series */
	MRIMAGEDATATYPE        rdb_hdr_image;        /* rdb_hdr_off_image */
}       POOL_HEADER;                             /* rdb_hdr_off_data */

/*
 * The P-file header size can be read from 4 byte 
 * "integer" located 1468 bytes after start of file.  
 * You can also use the following #define's to obtain 
 * offsets or sizes of various P-file header elements.
 */

/*---------------------------------------------------------------------
 |	RDBM header size and offset
 ---------------------------------------------------------------------*/
#define RDB_HDR_OFF				0
#define RDB_HDR_SIZE			sizeof(RDB_HEADER_REC)

#define RDB_PER_PASS_OFF		RDB_HDR_OFF + RDB_HDR_SIZE
#define RDB_PER_PASS_SIZE		sizeof(RDB_PER_PASS_TAB)

#define RDB_UNLOCK_RAW_OFF		RDB_PER_PASS_OFF + RDB_PER_PASS_SIZE
#define RDB_UNLOCK_RAW_SIZE		sizeof(RDB_PER_PASS_TAB)

#define RDB_DATACQ_OFF			RDB_UNLOCK_RAW_OFF + RDB_UNLOCK_RAW_SIZE
#define RDB_DATAACQ_OFF			RDB_UNLOCK_RAW_OFF + RDB_UNLOCK_RAW_SIZE
#define RDB_DATAACQ_SIZE		sizeof(RDB_DATA_ACQ_TAB)

#define RDB_NEX_OFF				RDB_DATAACQ_OFF + RDB_DATAACQ_SIZE
#define RDB_NEX_SIZE			sizeof(RDB_NEX_TYPE)

#define RDB_NEX_ABORT_OFF		RDB_NEX_OFF + RDB_NEX_SIZE
#define RDB_NEX_ABORT_SIZE		sizeof(RDB_NEX_TYPE)

#define RDB_TOOLSDATA_OFF		RDB_NEX_ABORT_OFF + RDB_NEX_ABORT_SIZE
#define RDB_TOOLSDATA_SIZE		sizeof(TOOLSDATA)

#define RDB_PRESCAN_HEADER_OFF	RDB_TOOLSDATA_OFF + RDB_TOOLSDATA_SIZE
#define RDB_PRESCAN_HEADER_SIZE	sizeof(PRESCAN_HEADER)

#define RDB_EXAMDATATYPE_OFF	RDB_PRESCAN_HEADER_OFF + RDB_PRESCAN_HEADER_SIZE
#define RDB_EXAMDATATYPE_SIZE	sizeof(EXAMDATATYPE)

#define RDB_SERIESDATATYPE_OFF	RDB_EXAMDATATYPE_OFF + \
								RDB_EXAMDATATYPE_SIZE
#define RDB_SERIESDATATYPE_SIZE	sizeof(SERIESDATATYPE)

#define RDB_MRIMAGEDATATYPE_OFF	RDB_SERIESDATATYPE_OFF + \
								RDB_SERIESDATATYPE_SIZE
#define RDB_MRIMAGEDATATYPE_SIZE	sizeof(MRIMAGEDATATYPE)


#define RDB_HEADER_SIZE_BYTES   sizeof(POOL_HEADER)

#define RDB_NUMB_HDRS      8
#define RDB_ALL_HEADERS_SIZE_BYTES RDB_HEADER_SIZE_BYTES * RDB_NUMB_HDRS

#define RDB_SHARED_SIZE_BYTES   sizeof( RDB_SHARED_BUFF)

/*---------------------------------------------------------------------
 |	RDBM frame index structure for reading NOPROC data.
 ---------------------------------------------------------------------*/
typedef struct _frame_node
{
	struct _frame_node *time_slice_next;
	struct _frame_node *time_echo_next;
	struct _frame_node *time_view_next;
	struct _frame_node *phase_next;
	short   op_code;
	short   index;
}       frame_node;

typedef struct _op_node
{
	long    frame_cnt;
	frame_node *phase_first;
}       op_node;

typedef struct _view_node
{
	frame_node *time_view_first;
	op_node op_ptr[4];
}       view_node;

typedef struct _echo_node
{
	frame_node *time_echo_first;
	view_node *view_ptr;
}       echo_node;

/*---------------------------------------------------------------------
 |	RDBM IO_PACKET structure
 ---------------------------------------------------------------------*/
typedef struct
{
	long    hdr_no;
	long    fd;
	VME_ADDRESS bam_addr;
	VME_ADDRESS ssp_addr;
	VME_ADDRESS uda_addr;
	long    data_len;
	long    run_num;
	long    rawsize;
	long    sspsave;
	long    udasave;
	long    content;
	long    col_type;
	long    npasses;
	long    nslices;
	long    nechoes;
	long    nframes;
	long    nbaseline;
	long    order;
	long    xres;
	long    yres;
	long    point_size;
	long    start_rcv;
	long    stop_rcv;
	long    rcv_no;
	echo_node	*echo_ptr;
	frame_node	*time_ptr;
	char	scan_date[16];
	char	scan_time[16];
	long	navs;
	char	patname[64];
	char	coil_name[32];
	char	psd_name[32];
	long	exam;
	long	series;
	long	image;
	long	data_type;
	long	coil_type;
	float	dfov;
	float	usercv[20];

}       RDB_IO_PACKET;

/*---------------------------------------------------------------------
 |	RDBM TAPE_PACKET structure.
 ---------------------------------------------------------------------*/
typedef struct
{
	long    fd;
	long    d_type;
	long    offset;
	char   *buffer;
}       RDB_TAPE_PACKET;

/*---------------------------------------------------------------------
 |	RDBM read header codes and other constants
 ---------------------------------------------------------------------*/
#define RDB_HDR_REC_HEADER                    0x0001 
#define RDB_PER_PASS_HEADER                   0x0002 
#define RDB_UNLOCK_RAW_HEADER                 0x0004 
#define RDB_DATA_ACQ_TAB_HEADER               0x0008 
#define RDB_NEX_TAB_HEADER                    0x0010 
#define RDB_NEX_ABORT_TAB_HEADER              0x0020 
#define RDB_TOOLSDATA_HEADER                  0x0040 
#define RDB_EXAM_HEADER                       0x0080 
#define RDB_SERIES_HEADER                     0x0100 
#define RDB_IMAGE_HEADER                      0x0200 
#define RDB_POOL_HEADER                       0x0400 
#define RDB_PRESCAN_HEADER                    0x0800

#define LOCK_SLICE                            1 
#define LOCK_PASS                             2 
#define LOCK_SCAN                             3 

#define RDB_BLOCK                             1 
#define RDB_UNBLOCK                           2 
#define RDB_READONLY                          3 
#define RDB_UNLOCKED                          0
#define RDB_LOCKED                            1

#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE 	0
#endif

/*---------------------------------------------------------------------
 |	RDBM macros
 ---------------------------------------------------------------------*/
#define rdbm_log_error(aMethod) \
{ \
	[theMsgHandler EXCEPTION \
		line	: __LINE__ \
		method	: aMethod \
		ier		: _rdbm_errmes_() \
		args	: _rdbm_err_msg_(), LST_END]; \
}

#define rdbm_nslices(io_pkt)	(io_pkt)->nslices
#define rdbm_npasses(io_pkt)	(io_pkt)->npasses
#define rdbm_nechoes(io_pkt)	(io_pkt)->nechoes
#define rdbm_nframes(io_pkt)	(io_pkt)->nframes
#define rdbm_nbaseline(io_pkt)	(io_pkt)->nbaseline
#define rdbm_content(io_pkt)	(io_pkt)->content
#define rdbm_col_type(io_pkt)	(io_pkt)->col_type
#define rdbm_xres(io_pkt)		(io_pkt)->xres
#define rdbm_yres(io_pkt)		(io_pkt)->yres
#define rdbm_start_rcv(io_pkt)	(io_pkt)->start_rcv
#define rdbm_stop_rcv(io_pkt)	(io_pkt)->stop_rcv
#define rdbm_n_rcv(io_pkt)		(io_pkt)->stop_rcv - (io_pkt)->start_rcv + 1
#define rdbm_raw_pass_size(io_pkt)	(io_pkt)->rawsize

/*----------------------------------------------------------------------------*/
/* rdb_hdr_retro_control						      */
/* Definition for Retrospective FSE Phase correction 12/16/2002 Rakesh Shevde */
/*----------------------------------------------------------------------------*/
#define RDB_RETRO_AHN_CHO_METHOD   1
#define RDB_RETRO_LSQ_METHOD       2
#define RDB_RETRO_ZEROTH_ORDER     4
#define RDB_RETRO_FIRST_ORDER      8
#define RDB_RETRO_ONE_EXTRA_ETL    16
#define RDB_RETRO_TWO_EXTRA_ETL    32


#endif /* RDBM_INCL */
