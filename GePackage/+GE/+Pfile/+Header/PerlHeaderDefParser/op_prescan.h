/* 090216 edited by slg to avoid further .h dependencies  
     see "slg" comments below 
     assume changes do not affect structure sizes.  That's all I need for rdbm.h to get to MR params section of header struct.
*/

/* GEtypes.h must be included before this include */
/* op_global.h must be included before this include */
/* Lx MGD Changes to support new Time stamp structure. MRIge64719*/

/*****************************************/
/*  Make sure this is compiled only onec */
/*****************************************/
#ifndef OP_PRESCAN_INCL
#define OP_PRESCAN_INCL

#include <time.h> /* for timespec for MGD */
//#include "CoilParameters.h"
//#include "ConfigParameters.h"
//#define MAX_NUM_REC MAX_PRESCAN_WEIGHTS  slg faked the next line:
#define MAX_NUM_REC 99
#define MAX_NUM_EXC 2 /* Maximum exciters */
#define MASTER_EXC  0x1
#define SLAVE1_EXC  0x2

/* for Multi-volume/multi-slab prescan */
#define MAX_PRESCAN_INDICES 3

/* noise calculation defs */
#define PS_MULTICOIL_SIZE 128

/* Smart prescan defs*/
#define REUSE_ENTRY_POINT_VALUE 0
#define IGNORE_ENTRY_POINT_VALUE -1

 /* typedef struct
{
   f32        rec_mean[MAX_NUM_REC];
   f32        rec_std[MAX_NUM_REC];
   s16        recon_enable;
} PS_MULTCOIL_TYPE; */

/* host scan-prescan interface */

#define OP_STARTMPS 30032
#define OP_STARTAPS 30033
#define OP_STARTLOOPING 30034
#define OP_STOPLOOPING 30035
#define OP_STARTSETUP 30036
#define OP_PRESCANDONE 30037
#define OP_MPSDONE 30044
#define OP_STARTAS 30045

#define OP_STARTRTD 30047            /* TWD 4/20/92    */
#define OP_STARTREF 30048            /* TAR 10/27/92   */
#define OP_PSC_SCANOP   30049
#define OP_PSC_MODIFY_RSP 30050
#define OP_SETUPDONE 30051

#define OP_COPYPSCD 30052
#define OP_COPYDONE 30053

/* Definitions for OC Spectro - Prescan GPC mail    */
#define OP_SAVE_XMT			30038
#define OP_RESTORE_XMT			30039
#define OP_GRADSHIM			30040
#define OP_GRADSHIM_SPEC                30046
#define OP_PSC_MODIFY			30041
#define OP_GET_HW_SETTINGS		30042
#define OP_SPECTRO_PRESCAN_DONE         30043

/* the following 2 lines added with merge from
   81_mns to lx2 */
#define OP_SPEC_SET_GRADSHIM		30054
#define OP_SPEC_GET_GRADSHIM		30055

#define OP_MPS_RAISE	30056
#define  OP_AUTO_START_PSC_PREP  30057

#define LOOPING_WITH_MPS 60066
/* changing OP_TOOLS_REQ from 60067 to something less than 32768 */
#define OP_TOOLS_REQ     11704

#define MAX_NUM_LINKS 2
#define PSC_MAX_NAME_LEN 24 + 1
#define PSC_MAX_CONTROL_ARRAY 15

#define PSC_REUSE_STRING_SIZE 52

typedef struct
{
  f32 centerR;
  f32 centerA;
  f32 centerS;
} centerRAS;


typedef struct
{
	long  centerFrequency;
	long  transmitGain;
	short xShim,yShim,zShim;
        long analogReceiveGain, digitalReceiveGain;
	float receiverNoiseStdDev[MAX_NUM_REC];
        long latestCenterFrequency;
        long runCenterFrequencyCourse;
        long runCenterFrequencyFine;
	long runTransmitGain;
	long runAutoShim;
	long runReceiverNoise;
        long runReceiveGain;
    short mxReachable;
    char  reuse[PSC_REUSE_STRING_SIZE];
} MxStartInfo;

typedef struct
{
    long  centerFrequency;
    long  transmitGain;
    short xShim,yShim,zShim;
    long analogReceiveGain, digitalReceiveGain;
    float receiverNoiseStdDev[MAX_NUM_REC];
    s32 autoMode;
    s32 saveCenterFrequency;
    s32 saveTransmitGain;
    s32 saveAutoShim;
    s32 saveReceiverNoise;
} MxDoneInfo;

typedef struct
{
    s32 rdbm_run_number;
    s32 active_psd_pid;
    s32 exam_number;
#ifdef WIN32
    time_t time_stamp;
#else
    struct timespec time_stamp; /* for MGD timestamp */
#endif
    s32 research_mode;
    s32	fautoshim;	/* flag, !=0 for autoshim on, 0 for off */
    s32	fmultiGroup;	/* flag, !=0 for yes, 0 for no */
    /*f32	startR;		 coordinate for start slice
    f32	startA;
    f32	startS;
    f32	endR;		 coordinate for end slice
    f32	endA;
    f32	endS;*/
    centerRAS  scanCenterRAS;
    f32 tablePosition;
    s32 sequence_no;
    s32 scan_pressed;
    centerRAS shimCenterRAS[2]; /* PRESCAN_MAX_VOLUMES]; */
    s32 prescanFov;
    f32 prescanSlabThick;
    /*f32 lmhor;*/
    s32 force_aps;
    s16 contrast_flag;   /* Set by scan value of 1 for contrast scans */
    MxStartInfo mx_info;

    s8	coil_name[PSC_MAX_NAME_LEN];
    s8 	entry_link[MAX_NUM_LINKS][PSC_MAX_NAME_LEN];
    n16	swap_channels; 	        /* 1= swap, 0 = No swap */
    /* slg COIL_CONFIG_PARAM_TYPE coilConfigParam; */
    /// slg MR_CONFIG_PARAM_TYPE mrConfigParam;
    /* slg GRADIENT_CONFIG_PARAM_TYPE gradientConfigParam; */

} OP_PSC_START_TYPE;

typedef struct
{
    s32 r1;
    s32 r2;
    s32 tg;
    s32 ax;
    f32 recon_scale[2];
    s32 status;
	s32 cancel;
	s32 opcode;
	s32 line_width;
	s32 ws_flip;
	s32 supp_lvl;
	s32 spectro_flag;
	s32 message;
    s32 pscsaved;
    s32 psc_full_aps;
    MxDoneInfo mx_info;
} OP_PSC_DONE_TYPE;

typedef struct
{
    s32 seqno_copy_to;
    s32 seqno_copy_from;
} OP_PSC_COPYPSCD_TYPE;

typedef struct
{
    s32 status;
} OP_PSC_COPYDONE_TYPE;

typedef struct
{
   s32 operation;

} OP_PSC_SCANOP_TYPE;


/* Prescan NMRID's */
#define PSC_MAJOR     "psc_major"
#define RDBM_SERVER   "psc_major"
#define PS_EXEC       "ps_exec"

/* 5.0 manual prescan host to tps definitions */

#define PS_PLOT_OFF 0
#define PS_PLOT_ON 1
#define PS_16_MODE   0
#define PS_32_MODE   1
#define PS_POWER_PLOT   1
#define PS_MAG_PLOT   2
#define PS_I_PLOT   3
#define PS_Q_PLOT   4
#define PS_PHASE_PLOT   5
#define PS_ABSORB_PLOT   6
#define PS_INACTIVE 99
#define PS_EP_CFA_COURSE   0
#define MPS_EP_FLIP_ANGLE  1
#define PS_EP_CFA_FINE     2
#define MPS_EP_SCAN_TR     3
#define APS_EP_FLIP_ANGLE  4
#define APS_EP_SCAN_TR     5
#define PS_EP_SCAN         6
#define PS_EP_DEFAULT      7
/* #define PS_LOOP_SIZE   12           */
/* #define PS_CHEMSAT_SIZE 56          */
/* #define MPS_START_SIZE   62         */
/* #define MPS_DATA_SIZE   1036        */
/* #define MPS_STOP_SIZE   0           */
/* #define MPS_NEEDDATA_SIZE   0       */
/* #define MPS_NOISE_SIZE   64         */

#define MPS_RIGHT_GAIN     1
#define MPS_RIGHT_TYPE     2
#define MPS_LEFT_GAIN      4
#define MPS_LEFT_TYPE      8
#define MPS_CHG_R1         1
#define MPS_CHG_R2         2
#define MPS_CHG_TG         4
#define MPS_CHG_AX         8

#define CFL  "cfl"
#define CFH  "cfh"
#define ESCFH  "escfh" /* YMSmr04514 For CFH in each slice */
#define MPS1 "mps1"
#define MPS2 "mps2"
#define APS1 "aps1"
#define APS2 "aps2"
#define SCAN "scan"
#define AWS  "aws"
#define AVS  "avs"
#define FSEPS  "fseps"
#define APA    "apa"
#define NOISE "rcvn"

#define NOTFOUND -1
#define MAXNUC 40
#define PSCMAXINT 2147483647
#define MIN_R1 1
#define MAX_R1 13
#define MIN_R2 1
#define MAX_R2 30
#define MIN_TG 0
#define MAX_TG 200
#define MAX_TG_DELTA 50
#define TG_WARN 100
#define MIN_AX  6250000
#define MAX_AX 80000000
#define MAX_AX_3T 180000000

#define PSCEX EXCEPTION line:__LINE__ method:


/* ------------------------------------------------------------------ */
/* OP_MPS_START - to PS Exec to start mps.                            */
/* ------------------------------------------------------------------ */
#define OP_MPS_START   800
typedef struct
{
        s32   req_opcode;
        s32   pass_desc;
        s32   req_size;
        #ifdef WIN32
            time_t timestamp;
        #else
            struct timespec timestamp;
        #endif
        s32   nframes;
        s32   leftfr1;
        s32   leftfr2;
        s32   leftpg;
        s32   leftpt;
        s32   rtfr1;
        s32   rtfr2;
        s32   rtpg;
        s32   rtpt;
        s32   nexda;
        s32   mode;
        s32   power_on;
        s32   recv_strt;
        s32   recv_end;
        s8    psd_ep[16];
	s32   recv_plot;
        s32   opnecho;
        s32   filter1;
        s32   filter2;
        s32   noadc;
        s32   acq_tagwords;
        s32   fastrcv;           /* 0 for standard receiver, 1 for fast receiver */
        s32   passthrough;
        s32   num_psc_vol;
        s32   num_psc_slab;
        s32   num_psc_rcvn_slab;
        f32   coil_weight[MAX_NUM_REC];
	s32     runReceiverNoise;                 /* 0 resuse recv noise  1 run recv noise*/
	f32     receiverNoiseStdDev[MAX_NUM_REC]; /* send recv noise std to APS
						     if recv noise need not be run */

} OP_MPS_START_TYPE;

typedef struct
{
        OP_HDR_TYPE        hdr;
        OP_MPS_START_TYPE  req;
} OP_MPS_START_PACK_TYPE;


/* ------------------------------------------------------------------ */
/* OP_MPS_DATA - to Host from Tardis mps with plot data.              */
/* ------------------------------------------------------------------ */
#define OP_MPS_DATA   801
typedef struct
{
        s16   leftdata [256];
        s16   rightdata [256];
        s32   adpeak [2];
        s32   bspeak [2];
        s32   minrec;
        s32   maxrec;
} OP_MPS_DATA_TYPE;

typedef struct
{
        OP_HDR_TYPE       hdr;
        OP_MPS_DATA_TYPE  req;
} OP_MPS_DATA_PACK_TYPE;


/* ------------------------------------------------------------------ */
/* OP_MPS_NEEDDATA - to Tardis mps to request ip plot data.           */
/* ------------------------------------------------------------------ */
#define OP_MPS_NEEDDATA   802
typedef struct
{
        OP_HDR_TYPE  hdr;
} OP_MPS_NEEDDATA_PACK_TYPE;


/* ------------------------------------------------------------------ */
/* OP_MPS_STOP - to Tardis mps to stop prescanning.                   */
/* ------------------------------------------------------------------ */
#define OP_MPS_STOP   803
typedef struct
{
        OP_HDR_TYPE  hdr;
} OP_MPS_STOP_PACK_TYPE;


/* ------------------------------------------------------------------ */
/* OP_MPS_TARDSTOP - to Host from Tardis mps on error.                */
/* ------------------------------------------------------------------ */
#define OP_MPS_TARDSTOP   804

typedef struct
{

   f32 rcv_cal[MAX_NUM_REC][13];
   f32 noise_mean[MAX_NUM_REC];
   f32 noise_std[MAX_NUM_REC];

}  OP_MPS_TARDSTOP_TYPE;

typedef struct
{
        OP_HDR_TYPE  hdr;
        OP_MPS_TARDSTOP_TYPE req;
} OP_MPS_TARDSTOP_PACK_TYPE;


/* 5.0 auto prescan host to tps definition file */

#define PS_CURRENT_CF   0
#define PS_MIDPOINT_CF  1
#define PS_WATER_CF     2
#define PS_FAT_CF       3
#define PS_PEAK_CF      4
#define PS_CENTROID_CF  5
#define PS_HEAD_COIL   0
#define PS_BODY_COIL   1
#define PS_SURF_COIL   2
#define PS_EXTR_COIL   3
#define APS_DONE    0
#define APS_LORES   1
#define APS_PASS1   2
#define APS_HIRES   3
#define APS_PASS2   4
#define APS_FSEPS   9
#define APS_APA     10
#define APS_SUPPRESS  101
#define APS_VSHIM     102
#define APS_AUTOSHIM  103
#define APS_FTG       104
#define APS_USER5   105
#define APS_USER6   106
#define APS_USER7   107
#define APS_USER8   108
#define APS_USER9   109
#define APS_USER10  110
#define APS_FTG_INT         111
#define APS_FTG_SHORTT1     112
#define APS_FTG_SHORTT1INT  113
/* YMSmr04514 CFH in Each Slice */
#define APS_ESHIRES	114
#define APS_ESCFH_EL 11
#define APS_NOISE 12


#define APS_SKIPPED -2

/* #define APS_START_SIZE  186 */
/* #define APS_STOP_SIZE   0   */
/* #define APS_DONE_SIZE   84  */

#define APS_GENERAL_SIZE   320
#define APS_SNR_NOADVISE   0
#define APS_SNR_ADVISE   1

/* ------------------------------------------------------------------ */
/* OP_APS_START - to PS Exec to start aps.                            */
/* ------------------------------------------------------------------ */
#define OP_APS_START   805
typedef struct
{
	s32	req_opcode;
	s32	pass_desc;
	s32     req_size;
	s32	start_ta;
	s32	start_rg;
	s32	start_cf;
	s32	cf_start_ta;
	s32	scan_nex;
	s32	acq_mode;
	s32	cf_mode;
	s32	tsp_cfac;
	s32	tsp_cfaf;
	s32	slquant;
	s32	xmtadd [11];
	s32	xaddmax;
	s32	max_r2_16mode;
	s32	max_r2_32mode;
	s32	ad_min_signal;
	s32	amp_cal;
	s32	bamtarget;
	s32	target;
	s32	min_signal;
	s32	max_signal;
	s32	breath_wait;
	s32	discard_points;
	s32     debug;
	s32	min_hi_points;
	s32	min_lo_points;
	s32	min_noise;
	s32	recv_strt;
	s32	recv_end;
#ifdef WIN32
    time_t timestamp;
#else
    struct timespec timestamp;
#endif
	s32	control [PSC_MAX_CONTROL_ARRAY];
	s32	opnecho;
	s32	filter1;
	s32	filter2;
    s32     noadc;
    s32     nolr;
    s32     acq_tagwords;
	s32     cf_min_peak_threshold;

    /**     Spectroscopy related information for AutoPrescan **/
    s32     suppress_pass;
    s32     shim_pass;
    s32     shim_step;
    s32     spec_pts;
    s32     spec_width;

    /**     AutoShim Information for AutoPrescan   **/
    s32     as_pass;        /* 1 for pass1, 2 for pass2 */
    s32     plane_calc3;    /* 1 for true, 0 for false */
    s32     def_plane;      /* 1 for axial, 2 for sag., 3 for cor. */
#ifdef WIN32
    time_t time_stamp;
#else
    struct timespec time_stamp; /* at the time when Gradshim is selected */
#endif
    s32     asxres;         /* 256 */
    s32     asyres;         /* 128 */
    s32     asbaseline;     /* number of baseline */
    s32     asrhblank;      /* kissoffs of views */
    s32     asptsize;       /* extended dynamic range */
    f32     opfov;          /* image fov */
    s32     transpose[3];   /* image orientation */
    s32     rotation[3];
    s32     cur_pos_x;      /* ellipse position */
    s32     cur_pos_y;
    s32     cur_pos_z;
    s32     cur_ax_x;       /* ellipse size */
    s32     cur_ax_y;
    s32     cur_ax_z;
    s32     cur_angle;      /* 0 for now */
    s32     field_strength; /* read from MRconfig */
    s32     position;       /* 1..4 for supine,prone,l.decub,r.decub */
	s32     ftg_rg;         /* rg is unique for fast tg */
    s32     fastrcv;        /* 0 for standard receiver, 1 for fast receiver */
    f32     as_std_above_mean;  /* number of StDev above mean for upper limit */
    f32     as_max_2_floor;     /* percentage of max to be used for floor     */
    f32     as_hard_floor;      /* hard lower limit for autoshim data points  */
    f32     as_mask_ratio;      /* Skip AS, if ratio of points used is < this */
	s32     vox_shim;       /* a flag to turn on Voxilated Autoshimming */
	s32     boresize;           /* PSD_55_CM_COIL:1 or PSD_60_CM_COIL:2 */
    s32     ftg_start_ta;         /* start ta for fast tg */
    s32     delta_TG;         /* delta TG for fast tg */
    s32     fseps_iter;
    s32     fseps_slices;
	s32 	fseps_xres;
    s32     fseps2_iter;
    f32     fseps2_zffactor;
    s32     isZ2;            /* flags for Z2 */
    s32     isZ2autoshim;      /* flag for using uwhfo for calculating shim values */
    s32     ps_connected_coil; /* flag for using connected coil in prescan */
    s32     apa_coilsel;
    f32     apa_fov;
    s8      apa_coilname[20];
    s32     num_psc_vol;
    s32     num_psc_slab;
    s32     num_psc_rcvn_slab;
    s32     cur_pos_vol2x;
    s32     cur_pos_vol2y;
    s32     cur_pos_vol2z;
    s32     cur_ax_vol2x;
    s32     cur_ax_vol2y;
    s32     cur_ax_vol2z;
                            /* YMSmr04514 CFH in each slice */
    s32     ir_flag;      /* Inversion Recovery Flag for MFO4 prescan */
    s32     escfh_slices; /* Num of total slices for CFH in each slice on MFO4 */
    f32     coil_weight[MAX_NUM_REC];
    s32     fseps_rcvr;
	s32     runReceiverNoise;                 /* 0 resuse recv noise  1 run recv noise*/
	f32     receiverNoiseStdDev[MAX_NUM_REC]; /* send recv noise std to APS
						     if recv noise need not be run */
    s32     max_rg;
    s32     psc_prep;
    s32 	cfh_raise_threshold; /* to raise the cfh left peak threshold from 15% to 25% in case of certain coils */
    s32    indicate_single_peak;  /* if looking out for single peak case during CFH */
} OP_APS_START_TYPE;

typedef struct
{
	OP_HDR_TYPE        hdr;
	OP_APS_START_TYPE  req;
} OP_APS_START_PACK_TYPE;


/* ------------------------------------------------------------------ */
/* OP_APS_STOP - to Tardis aps to stop current aps.                   */
/* ------------------------------------------------------------------ */
#define OP_APS_STOP   806
typedef struct
{
	OP_HDR_TYPE  hdr;
} OP_APS_STOP_PACK_TYPE;


/* ------------------------------------------------------------------ */
/* OP_PS_LOOP - from Host to Tardis mps to change psd entry point     */
/* ------------------------------------------------------------------ */
#define OP_PS_LOOP   807
typedef struct
{
	s8  entrylab [16];
	s32  xmitattn;
} OP_PS_LOOP_TYPE;

typedef struct
{
	OP_HDR_TYPE       hdr;
	OP_PS_LOOP_TYPE  req;
} OP_PS_LOOP_PACK_TYPE;


/* ------------------------------------------------------------------ */
/* OP_APS_DONE - from Tardis aps to Host Prescan upon completion      */
/* 02/03/03  Changes made to CF related fields for BBA application    */
/* to support multi-volumes for prescan. For normal prescan only      */
/* the 0th location will be used. i.e. final_cf[0]                    */
/* ------------------------------------------------------------------ */
#define OP_APS_DONE   808
typedef struct
{
   s32	final_ta[MAX_PRESCAN_INDICES];
   s32	final_rg[MAX_PRESCAN_INDICES];
   s32	final_bs[MAX_PRESCAN_INDICES];
   s32	final_cf[MAX_PRESCAN_INDICES];
   s32	snr_advise;
   s32  water[MAX_PRESCAN_INDICES];    /* the location of the water peak  TWD 2/13/92   */
   s32  lipid[MAX_PRESCAN_INDICES];    /* the location of the fat peak                  */
   s32  maximum[MAX_PRESCAN_INDICES];  /* the location of the max pixel in the spectrum */
   s32  signalmax; /* used in guided grafidy */

   /**  Receiver calibration values **/
   f32  rcv_cal[MAX_NUM_REC][13];
   f32 noise_mean[MAX_NUM_REC];
   f32 noise_std[MAX_NUM_REC];

   /**   Spectroscopy Information **/
   s32  gx_shim;
   s32  gy_shim;
   s32  gz_shim;
   s32  line_width;
   s32  ws_flip;
   s32  supp_lvl;
   s32  spectro_flag;

   /***   Shimming Information ***/
   n16   vme_addr[3]; /* magnitude image for display */
   n16   filler;      /* filler to make vme_addr risc compatible */
   f32   x[3];        /* shim results */
   f32   y[3];        /* shim results */
   f32   x2[3];       /* shim results */
   f32   y2[3];       /* shim results */
   s32   window;      /* for image scaling */
   s32   level;
   s32   panel;       /* not_zero to display the panel image */
   s32   recall_roi;  /* recall previous roi, 1 on, 0 off */
   s32 	 cfh_centered_on_left_peak; /* cfh centered on left peak in case of certain coils */
   s32   cfh_single_peak; 

} OP_APS_DONE_TYPE;

typedef struct
{
	OP_HDR_TYPE       hdr;
	OP_APS_DONE_TYPE  req;
} OP_APS_DONE_PACK_TYPE;


/* ------------------------------------------------------------------ */
/* OP_PS_PLOT - to Tardis mps to change ip plot type / gain           */
/* ------------------------------------------------------------------ */
#define OP_PS_PLOT   810
typedef struct
{
	s32	command;
	s32	lplotgain;
	s32	lplottype;
	s32	rplotgain;
	s32	rplottype;
} OP_PS_PLOT_TYPE;

typedef struct
{
	OP_HDR_TYPE  hdr;
	OP_PS_PLOT_TYPE  req;
} OP_PS_PLOT_PACK_TYPE;



/* ------------------------------------------------------------------ */
/* OP_APS_SAT  - from Host to PS Exec to run aps ChemSat pass.        */
/* OP_MPS_SAT  - from Host to PS Exec to run mps ChemSat pass.        */
/* OP_ZERO_SAT - from Host to PS Exec to run null ChemSat pass.       */
/* ------------------------------------------------------------------ */
#define OP_APS_SAT    811
#define OP_MPS_SAT    812
#define OP_ZERO_SAT   813
#define OP_PS_SAT     814
#define OP_PS_SKIP     830
typedef struct
{
	s32	command;
	s32	mps_r1;
	s32	mps_r2;
	s32	mps_tg;
	s32	mps_freq;
	s32	aps_r1;
	s32	aps_r2;
	s32	aps_tg;
	s32	aps_freq;
	f32	scalei;
	f32	scaleq;
	s32	snr_warning;
	s32	aps_or_mps;
	s32	mps_bitmap;
	s8	powerspec [256];
	s32	filler1;
	s32	filler2;
    s16 xshim;
    s16 yshim;
    s16 zshim;
    s16 recon_enable;
    s32 autoshim_status; /* to determine whether autoshim was performed or not(smart/OFF) */
    f32 rec_std[128];
    f32 rec_mean[128];
	s32     line_width;
	s32     ws_flip;
	s32     supp_lvl;
	s32 psc_reuse;
    s8  psc_reuse_string[PSC_REUSE_STRING_SIZE];
    s16 phase_correction_status;
    s8  buffer[74];
} PRESCAN_HEADER;


typedef struct
{
	OP_HDR_TYPE  hdr;
        PRESCAN_HEADER  req;
} OP_PS_CHEMSAT_PACK_TYPE;


typedef struct
{
        s32     mps_r1;
        s32     mps_r2;
        s32     mps_tg;
        s32     mps_freq;
        s32     aps_r1;
        s32     aps_r2;
        s32     aps_tg;
        s32     aps_freq;
        f32     scalei;
        f32     scaleq;
        s32     snr_warning;
        s32     aps_or_mps;
        s32     mps_bitmap;
        s32     nrec;
        f32     noise_mean[MAX_NUM_REC];
        f32     noise_std[MAX_NUM_REC];
        s32     autoshim_status; /* to determine whether autoshim was performed or not(smart/OFF) */
        s16     phase_correction_status;
} OP_PS_SKIP_TYPE;

typedef struct
{
        OP_HDR_TYPE  hdr;
        OP_PS_SKIP_TYPE  req;
} OP_PS_SKIP_PACK_TYPE;



/* ------------------------------------------------------------------ */
/* OP_MPS_RECCHAN - to Tardis mps to change plotted receiver no.      */
/* ------------------------------------------------------------------ */
#define OP_MPS_RECCHAN   815
typedef struct
{
	s32 receiver;
} OP_MPS_RECCHAN_TYPE;

typedef struct
{
	OP_HDR_TYPE  hdr;
	OP_MPS_RECCHAN_TYPE req;
} OP_MPS_RECCHAN_PACK_TYPE;


/* ------------------------------------------------------------------ */
/* OP_MPS_CHGHDW - to Tardis mps to change <TG, R1, R2, AX>           */
/* ------------------------------------------------------------------ */
#define OP_MPS_CHGHDW       817
typedef struct
{
	s32      cmmnd;
	s32      r1;
	n32      r2;
	n32      tg;
	n32      ax;
} OP_MPS_CHGHDW_TYPE;

typedef struct
{
	OP_HDR_TYPE  hdr;
	OP_MPS_CHGHDW_TYPE  req;
} OP_MPS_CHGHDW_PACK_TYPE;

#define PS_MIN_CFREQ     63660000  /* Hz */
#define PS_MAX_CFREQ     64060000  /* Hz */

#define OP_MPS_WRITEDATA   831
typedef struct
{
        s32 message;
} OP_MPS_WRITEDATA_TYPE;

typedef struct
{
        OP_HDR_TYPE  hdr;
        OP_MPS_WRITEDATA_TYPE req;
} OP_MPS_WRITEDATA_PACK_TYPE;


/* ------------------------------------------------------------------ */
/* OP_RDBM_SERVER - to host from Tardis with RDBM request             */
/* ------------------------------------------------------------------ */
#define OP_RDBM_SERVER      818


/* ------------------------------------------------------------------ */
/* OP_PS_WORK_REQ - to ps work from ps work with prescan request      */
/* ------------------------------------------------------------------ */
#define OP_PS_WORK_REQ      819

/* prescan select list typedef */
struct PS_PSL_ELEM_STRUCT {
        s32  opcode;
	s32  reply;
	s32  (*ps_passptr)(void *);
	struct PS_PSL_ELEM_STRUCT * next;
};
typedef struct PS_PSL_ELEM_STRUCT  PS_PSL_ELEM;

/* prescan run list typedef */
struct PS_PRL_ELEM_STRUCT {
	s32   (*ps_passptr)(void *);
	s32   *ps_dataptr;
	struct PS_PRL_ELEM_STRUCT * next;
} ;
typedef struct PS_PRL_ELEM_STRUCT PS_PRL_ELEM;

typedef struct
{
	PS_PRL_ELEM *psreq;
} OP_PS_WORK_REQ_TYPE;

typedef struct
{
	OP_HDR_TYPE  hdr;
	OP_PS_WORK_REQ_TYPE  req;
} OP_PS_WORK_REQ_PACK_TYPE;

typedef struct
{
        OP_HDR_TYPE hdr;
	s8 rec_buf[3000];
} OP_PS_EXEC_PACK_TYPE;

/* ---------------------------------------------------------------- */
/* OP_PS_TPS - To log an message on the bottom porton of the right  */
/*             plasma                                               */
/* ---------------------------------------------------------------- */
#define OP_PS_TPS_LOG  816

typedef struct
{
   n32 ermes;
} OP_PS_TPS_LOG_TYPE;


typedef struct
{
   OP_HDR_TYPE hdr;
   OP_PS_TPS_LOG_TYPE req;
} OP_PS_TPS_LOG_PACK_TYPE;

#define OP_TPS_SNAP_GO          1091  /* TWD 2/9/92 */

typedef struct
{
  OP_HDR_TYPE  hdr;
} OP_TPS_SNAP_GO_PACK_TYPE;

/* ------------------------------------------------------------------ */
/* OP_MPS_PRESCANINDEX_CHANGE - to change prescan index no.           */
/* ------------------------------------------------------------------ */
#define OP_MPS_PRESCANINDEX_CHANGE   832
typedef struct
{
        s32 curr_prescan_index;
} OP_MPS_PRESCANINDEX_CHANGE_TYPE;

typedef struct
{
        OP_HDR_TYPE  hdr;
        OP_MPS_PRESCANINDEX_CHANGE_TYPE req;
} OP_MPS_PRESCANINDEX_CHANGE_PACK_TYPE;


#define OP_MPS_LOOP_STATUS 833
typedef struct
{
  s32 start_status;
  s32 stop_status;
}OP_MPS_LOOP_STATUS_TYPE;

typedef struct
{
  OP_HDR_TYPE  hdr;
  OP_MPS_LOOP_STATUS_TYPE req;
}OP_MPS_LOOP_STATUS_PACK_TYPE;

/*------------------------------------------------------*/
/* OP_UPDATE_MX to update Mx with the Latest Lx values  */
/* incase of SPECTRO,HOSHIM and SVAT                    */
/*------------------------------------------------------*/
#define OP_UPDATE_MX 834
typedef struct
{
  OP_HDR_TYPE  hdr;
  MxDoneInfo req;
}OP_UPDATE_MX_PACK_TYPE;
/* ================================== */
/* ===                            === */
/* ===   Packet Definitions       === */
/* ===   for Hyperscan Ref Scan   === */
/* ===                            === */
/* ================================== */

#define OP_REF_START     1094  /* AL 4/13/92 */


typedef struct
{
   long int  runnumber;
   long int  autolock;
} OP_REF_START_TYPE;

typedef struct
{
   OP_HDR_TYPE  hdr;
   OP_REF_START_TYPE  req;
} OP_REF_START_PACK_TYPE;

/* ================================= */
/* ===                           === */
/* ===     PACKET DEFINITIONS    === */
/* ===     FOR OC SPECTRO TO     === */
/* ===     HOST PRESCAN          === */
/* ===                           === */
/* ================================= */

/* ------------------------------------------------------------------ */
/* OP_SAVE_XMT - OC Spectro tells host prescan to save xmt freq       */
/* ------------------------------------------------------------------ */
typedef struct
{
    s32 		nuc;		/* nucleus, given by OC Spectro */
    f32  	        gamma;		/* gamma value, reported by Prescan */
    s32	        	ax;		/* filled in by Spectro, response */
					/* carries actual setting by Prescan */
    n32         	ermes;		/* 0=no error */
} OP_XMT_PACK_TYPE;

/* ------------------------------------------------------------------ */
/* OP_GRADSHIM - OC Spectro tells host prescan to run gradshim        */
/* ------------------------------------------------------------------ */
typedef struct
{
    s32 	scan_run_num;	/* scan run number, given by OC Spectro */
    s32         alloc_ip;       /* 0=don't allocate IP, 1=do */
    s32		sq;		/* shim quadrant, given by OC Spectro */
    s32		psd_id;		/* PSD process ID, given by OC Spectro */
    s32		mode;		/* 0=research, 1=clinical */
#ifdef WIN32
    time_t timestamp;
#else
    struct timespec timestamp; /* when button was pressed */
#endif
    n32 	ermes;		/* 0=no error */
    s32		exam_number;	/* non-zero: new exam */
    s32		fautoshim;	/* flag, !=0 for autoshim on, 0 for off */
    s32		fmultiGroup;	/* flag, !=0 for yes, 0 for no */
    f32		startR;		/* coordinate for start slice */
    f32		startA;
    f32		startS;
    f32		endR;		/* coordinate for end slice */
    f32		endA;
    f32		endS;

    s8  coil_name[PSC_MAX_NAME_LEN];
    /// slg COIL_CONFIG_PARAM_TYPE coilConfigParam;
} OP_GRADSHIM_PACK_TYPE;

/* ------------------------------------------------------------------ */
/* OP_MODIFY_REQUEST - sent by Spectro to change prescan parameters   */
/* ------------------------------------------------------------------ */
typedef struct
{
    s32		r1;		/* filled in for request and response */
    s32		r2;		/* filled in for request and response */
    s32		tg;		/* filled in for request and response */
    s32		ax;		/* filled in for request and response */
    s32		dx;		/* filled in for request and response */
    s32		nuc;		/* filled in for request and response */
    f32		gamma;		/* filled in for request and response */
    s8		psd_ep[16];	/* PSD entry point */
    n32 	ermes;		/* 0=no error */
    n32		exciter_number;	/* Master or Slave # */
} OP_MODIFY_REQUEST_PACK_TYPE;

/* ------------------------------------------------------------------ */
/* OP_GET_HW_SETTINGS - tells prescan to read entry point tbl         */
/*                      and returns current HW settings to            */
/*                      OC Spectro                                    */
/* ------------------------------------------------------------------ */
typedef struct
{
    s32		r1;		/* filled in for response */
    s32		r2;		/* filled in for response */
    s32		tg;		/* filled in for response */
    s32		ax;		/* filled in for response */
    s32         nuc;            /* filled in for response */
    f32         gamma;          /* filled in for response */
    s32		psd_id;		/* given by OC Spectro */
    s8          psd_ep[16];     /* PSD entry point */
    n32  	ermes;		/* 0=no error */
    s32		exam_number;	/* non-zero: new exam */
    n32		exciter_number;	/* Master or Slave # */

    s8  coil_name[PSC_MAX_NAME_LEN];
    /// slg COIL_CONFIG_PARAM_TYPE coilConfigParam;

} OP_GET_HW_SETTINGS_PACK_TYPE;



/* The definition of OP_SPEC_SET_GRADSHIM and OP_SPEC_GET_GRADSHIM
   are added when 81_mns merge with lx2 */

/* ----------------------------------------------------------------- */
/* OP_SPEC_SET_GRADSHIM - tell prescan to modify gradint shim values */
/*                                                                   */
/*-------------------------------------------------------------------*/
typedef struct
{
    int           gradient;        /* 0: X 1: Y 2: Z       */
    s32           value;           /* between -200 and 200 */
    n32           ermes;           /* 0=no error           */
} OP_SPEC_SET_GRADSHIM_PACK_TYPE;  /* The packet follows existing
                                      PrescanStates GSHIM_entry()
                                      call back format */

/* ----------------------------------------------------------------- */
/* OP_SPEC_GET_GRADSHIM - obtain gradint shim values from prescan    */
/*                                                                   */
/*-------------------------------------------------------------------*/
typedef struct
{
    s32           gx_shim;         /* grad shim value in X dir  */
    s32           gy_shim;         /* grad shim value in Y dir  */
    s32           gz_shim;         /* grad shim value in Z dir  */
    n32             ermes;         /* 0= no error                */
} OP_SPEC_GET_GRADSHIM_PACK_TYPE;  /* The packet follows existing
                                      PrescanStates GSHIM_entry()
                                      call back format */

#define OP_PSC_POLL_EXEC    809




/*******************************************************************/
/*  The following are opcodes and packets needed to support ashim  */
/*  within AutoPrescan                                             */
/*******************************************************************/

#define OP_APS_MODAWSRSP  1088

#define OP_APS_MODAWSCV   1089

#define OP_APS_MODAVSRSP  1090

#define OP_APS_MODAVSCV   1092

#define OP_APS_DFMSHIM    1095


typedef struct
{
   f32 gxshim;
   f32 gyshim;
   f32 gzshim;
   f32 gz2shim;

   s32 shimchg_status;

}  OP_APS_DFMSHIM_TYPE;


typedef struct
{
   OP_HDR_TYPE hdr;
   OP_APS_DFMSHIM_TYPE req;
}  OP_APS_DFMSHIM_PACK_TYPE;


typedef struct
{
   f32 gxshim;
   f32 gyshim;
   f32 gzshim;

   s32 shimchg_status;

}  OP_APS_MODAVS_TYPE;


typedef struct
{
   OP_HDR_TYPE hdr;
   OP_APS_MODAVS_TYPE req;
}  OP_APS_MODAVS_PACK_TYPE;


typedef struct
{
   s32 tip_start;
   s32 tip_delta;
   s32 tip_step;

   s32 supchg_status;

}  OP_APS_MODAWS_TYPE;

typedef struct
{
   OP_HDR_TYPE hdr;
   OP_APS_MODAWS_TYPE req;
}  OP_APS_MODAWS_PACK_TYPE;


#define OP_APS_PSD_DOWNLOAD 1093

typedef struct
{
   s32  flag;
}  OP_APS_PSD_DOWNLOAD_TYPE;

typedef struct
{
   OP_HDR_TYPE hdr;
   OP_APS_PSD_DOWNLOAD_TYPE req;
}  OP_APS_PSD_DOWNLOAD_PACK_TYPE;


#define OP_APS_ASHIM_START  1118

typedef struct
{
   s32   as_pass;        /* 1 for pass1, 2 for pass2 */
   s32   plane_calc3;    /* 1 for true, 0 for false */
   s32   def_plane;      /* 1 for axial, 2 for sag., 3 for cor. */
#ifdef WIN32
    time_t time_stamp;
#else
    struct timespec time_stamp; /* at the time when Gradshim is selected */
#endif
   s32   asxres;         /* 256 */
   s32   asyres;         /* 128 */
   s32   asbaseline;     /* number of baseline */
   s32   asrhblank;      /* kissoffs of views */
   s32   asptsize;       /* extended dynamic range */
   f32   opfov;          /* image fov */
   s32   transpose[3];   /* image orientation */
   s32   rotation[3];
   s32   cur_pos_x;      /* ellipse position */
   s32   cur_pos_y;
   s32   cur_pos_z;
   s32   cur_ax_x;       /* ellipse size */
   s32   cur_ax_y;
   s32   cur_ax_z;
   s32   cur_angle;      /* 0 for now */
   s32   field_strength; /* read from MRconfig */
   s32   position;       /* 1..4 for supine,prone,l.decub,r.decub */
	s32   srec;           /* Start receiver */
	s32   erec;           /* End receiver */
	f32   as_std_above_mean;  /* number of StDev above mean for upper limit */
	f32   as_max_2_floor;     /* percentage of max to be used for floor     */
	f32   as_hard_floor;      /* hard lower limit for autoshim data points  */
	f32   as_mask_ratio;      /* Skip AS, if ratio of points used is < this */
   s32   vox_shim;       /* a flag to turn on Voxilated Autoshimming */
}  OP_APS_ASHIM_START_TYPE;


typedef struct
{
   OP_HDR_TYPE hdr;
   OP_APS_ASHIM_START_TYPE req;
}  OP_APS_ASHIM_START_PACK_TYPE;


#define OP_APS_ASHIM_DONE   1119

typedef struct
{
  n16   vme_addr[3]; /* magnitude image for display */
  n16   filler;      /* filler to make vme_addr risc compatible */
  f32   x[3];        /* shim results */
  f32   y[3];        /* shim results */
  f32   x2[3];       /* shim results */
  f32   y2[3];       /* shim results */
  s32   window;      /* for image scaling */
  s32   level;
  s32   panel;       /* not_zero to display the panel image */
  s32   recall_roi;  /* recall previous roi, 1 on, 0 off */
  n32   ermes;
  f32   points_used[3];
  s32   ashim_status[3];
}  OP_APS_ASHIM_DONE_TYPE;

typedef struct
{
   OP_HDR_TYPE hdr;
   OP_APS_ASHIM_DONE_TYPE req;
}  OP_APS_ASHIM_DONE_PACK_TYPE;

#define OP_QSHIM_REQ  1120
typedef struct
{
  s32   xshim;
  s32   yshim;
  s32   zshim;
  s32   z2shim;
  s32   zxshim;
  s32   zyshim;
  s32   filenum;
} OP_TOOLS_TYPE;

typedef struct
{
  OP_HDR_TYPE hdr;
  OP_TOOLS_TYPE req;
} OP_TOOLS_PACK_TYPE;

/* opcodes for uwhfo z2 processing */
#define OP_UWHFO_DONE 1121
#define OP_AX_SAVED 1122
#define OP_SAG_SAVED 1123
#define OP_COR_SAVED 1124

/* Constants required by CFH */
#define GAUSS_1T  10000.0  /* 1 Tesla = 10000.0 gauss */
#define CHEM_SHIFT_1T  140.0
#define EPSILON_1T   20.0

/* above two constants are too small for mid/low field system */
#define CHEM_SHIFT_1T_MLF 150.0 /* above 3.5ppm */
#define EPSILON_1T_MLF 45.0        /* above 1ppm */
/* YMSmr05010:Customized for HFO system */
#define CHEM_SHIFT_1T_HFO 143.0    /* above 3.35ppm */
#define EPSILON_1T_HFO 50.0        /* above 1.17ppm */

#define MPS_DEBUG 0x1000
#define APS_DEBUG 0x0100

#endif /* OP_PRESCAN_INCL */
