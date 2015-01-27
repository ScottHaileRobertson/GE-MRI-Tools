 /*@Start***********************************************************/
/* GEMSBG Include File
        General Electric Medical Systems-Europe
        Advantage Windows
        File    :           imagedb.h
        Created :           Sat Jun 10 20:24:49 CDT 1995
        By      :           John Heinen
        In      :           ./include/genesis
        Purpose :           Update with Genesis 6.0 headers
        Original version:   imagedb.h 1.3 # 95/05/18 08:20:19
 * Copyright (C) 1988, 1989, 1990, 1991, 1992, 1993, 1994, 1995 GE Medical Systems
 *
 *    Include File Name:  imagedb.h   
 *    Developer:          David J. Johnson
 *
 * $Source: imagedb.h $
 * $Revision: 1.9 $  $Date: 11 Dec 1998 08:56:04 $Siddu, Subramanya
 */

/*@End*********************************************************/

/* only do this once in any given compilation.*/
#ifndef  IMAGEDB_H_INCL
#define  IMAGEDB_H_INCL

#define NO_SUITE_FIELDS 8
#define NO_EXAM_FIELDS 65
#define NO_SERIES_FIELDS 86
#define NO_MRIMAGE_FIELDS 214
#define NO_PROTOCOL_FIELDS 208
#define NO_PATCNTL_FIELDS 2
#define NO_IDBCONTROL_FIELDS 10
#define NO_MODEL_FIELDS 98
#define NO_EXAMUID_FIELDS 1
#define NO_SERIESUID_FIELDS 1
#define NO_MRIMAGEUID_FIELDS 1
 
#define RASPOINT float
#define REFCHANTYPE short int
#define IMATRIXTYPE short int
#define DIMXYTYPE float
#define PIXSIZETYPE float
#define BLOCK char
#define ATOMIC long

typedef struct _SUITEDATATYPE {
        unsigned long         su_checksum;        /*Suite Record Checksum*/
   unsigned long         long_padding[4];    /*Please use this if you are adding any long*/
        int                   int_padding[4];     /*Please use this if you are adding any ints*/
        short int             su_uniq;            /*Make Unique Flag*/
        short int             short_padding[7];   /*Please use this if you are adding any Shorts */
        char                  prodid [13];        /*Product ID*/
        char                  su_diskid;          /*Disk ID*/
        BLOCK                 su_id [4];          /*Suite ID*/
        BLOCK                 su_verscre [2];     /*Genesis Version of Record*/
        BLOCK                 su_verscur [2];     /*Genesis Version of Record*/
        BLOCK                 su_padding [42];    /*Spare Space only for BLOCK*/
}  SUITEDATATYPE ;
 
typedef struct _EXAMDATATYPE {
        double                firstaxtime;        /*Start time(secs) of first axial in exam*/
        double                double_padding[9];  /*Please use this if you are adding any doubles*/
        float                 zerocell;           /*Cell number at theta*/
        float                 cellspace;          /*Cell spacing*/
        float                 srctodet;           /*Distance from source to detector*/
        float                 srctoiso;           /*Distance from source to iso*/
        float                 float_padding[8];   /*Please use this if you are adding any floats*/
        ATOMIC                ex_delta_cnt;       /*Indicates number of updates to header*/
        ATOMIC                ex_complete;        /*Exam Complete Flag*/
        ATOMIC                ex_seriesct;        /*Last Series Number Used*/
        ATOMIC                ex_numarch;         /*Number of Series Archived*/
        ATOMIC                ex_numseries;       /*Number of Series Existing*/
        ATOMIC                ex_numunser;        /*Number of Unstored Series*/
        ATOMIC                ex_toarchcnt;       /*Number of Unarchived Series*/
        ATOMIC                ex_prospcnt;        /*Number of Prospective/Scout Series*/
        ATOMIC                ex_modelnum;        /*Last Model Number used*/
        ATOMIC                ex_modelcnt;        /*Number of ThreeD Models*/
        unsigned long         ex_checksum;        /*Exam Record Checksum*/
        long                  long_padding[8];    /*Please use this if you are adding any longs*/
        int                   numcells;           /*Number of cells in det*/
        int                   magstrength;        /*Magnet strength (in gauss)*/
        int                   patweight;          /*Patient Weight*/
        int                   ex_datetime;        /*Exam date/time stamp*/
        int                   ex_lastmod;         /*Date/Time of Last Change*/
        int                   int_padding[12];     /*Please use this if you are adding any ints*/
        unsigned short int    ex_no;              /*Exam Number*/
        short int             ex_uniq;            /*The Make-Unique Flag*/
        short int             detect;             /*Detector Type*/
        short int             tubetyp;            /*Tube type*/
        short int             dastyp;             /*DAS type*/
        short int             num_dcnk;           /*Number of Decon Kernals*/
        short int             dcn_len;            /*Number of elements in a Decon Kernal*/
        short int             dcn_density;        /*Decon Kernal density*/
        short int             dcn_stepsize;       /*Decon Kernal stepsize*/
        short int             dcn_shiftcnt;       /*Decon Kernal Shift Count*/
        short int             patage;             /*Patient Age (years, months or days)*/
        short int             patian;             /*Patient Age Notation*/
        short int             patsex;             /*Patient Sex*/
        short int             ex_format;          /*Exam Format*/
        short int             trauma;             /*Trauma Flag*/
        short int             protocolflag;       /*Non-Zero indicates Protocol Exam*/
        short int             study_status;       /*indicates if study has complete info(DICOM/genesis)*/
   short int             short_padding[11];  /*Please use this if you are adding any shorts*/
        char                  hist [61];          /*Patient History*/
        char                  reqnum [13];        /*Requisition Number*/
        char                  refphy [33];        /*Referring Physician*/
        char                  diagrad [33];       /*Diagnostician/Radiologist*/
        char                  op [4];             /*Operator*/
        char                  ex_desc [65];       /*Exam Description*/
        char                  ex_typ [3];         /*Exam Type*/
        char                  ex_sysid [9];       /*Creator Suite and Host*/
        char                  ex_alloc_key [13];  /*Process that allocated this record*/
        char                  ex_diskid;          /*Disk ID for this Exam*/
        char                  hospname [33];      /*Hospital Name*/
        char                  patid [13];         /*Patient ID for this Exam*/
        char                  patname [25];       /*Patient Name*/
        BLOCK                 ex_suid [4];        /*Suite ID for this Exam*/
        BLOCK                 ex_verscre [2];     /*Genesis Version - Created*/
        BLOCK                 ex_verscur [2];     /*Genesis Version - Now*/
        BLOCK                 uniq_sys_id [16];   /*Unique System ID*/
        BLOCK                 service_id [16];    /*Unique Service ID*/
        BLOCK                 mobile_loc [4];     /*Mobile Location Number*/
        BLOCK                 study_uid [32];     /*Study Entity Unique ID*/
        BLOCK                 refsopcuid[32];     /* Ref SOP Class UID */
        BLOCK                 refsopiuid[32];     /* Ref SOP Instance UID */
                                                  /* Part of Ref Study Seq */
        BLOCK                 patnameff[65];      /* FF Patient Name */
        BLOCK                 patidff[65];        /* FF Patient ID */
        BLOCK                 reqnumff[17];       /* FF Requisition No */
        BLOCK                 dateofbirth[9];     /* Date of Birth */
        BLOCK                 mwlstudyuid[32];    /* Genesis Exam UID */
        BLOCK                 mwlstudyid[16];     /* Genesis Exam No */
        BLOCK                 ex_padding [62];   /*Spare Space only for BLOCKs*/
                                                  /* It doesn't affect the offsets on IRIX */
}  EXAMDATATYPE ;
 
typedef struct _SERIESDATATYPE {
        double                double_padding[7];  /*Please use this if you are adding any doubles*/
        float                 se_pds_a;           /*PixelData size - as stored*/
        float                 se_pds_c;           /*PixelData size - Compressed*/
        float                 se_pds_u;           /*PixelData size - UnCompressed*/
        float                 lmhor;              /*Horizontal Landmark*/
        float                 start_loc;          /*First scan location (L/S)*/
        float                 end_loc;            /*Last scan location (L/S)*/
        float                 echo1_alpha;        /*Echo 1 Alpha Value*/
        float                 echo1_beta;         /*Echo 1 Beta Value*/
        float                 echo2_alpha;        /*Echo 2 Alpha Value*/
        float                 echo2_beta;         /*Echo 2 Beta Value*/
        float                 echo3_alpha;        /*Echo 3 Alpha Value*/
        float                 echo3_beta;         /*Echo 3 Beta Value*/
        float                 echo4_alpha;        /*Echo 4 Alpha Value*/
        float                 echo4_beta;         /*Echo 4 Beta Value*/
        float                 echo5_alpha;        /*Echo 5 Alpha Value*/
        float                 echo5_beta;         /*Echo 5 Beta Value*/
        float                 echo6_alpha;        /*Echo 6 Alpha Value*/
        float                 echo6_beta;         /*Echo 6 Beta Value*/
        float                 echo7_alpha;        /*Echo 7 Alpha Value*/
        float                 echo7_beta;         /*Echo 7 Beta Value*/
        float                 echo8_alpha;        /*Echo 8 Alpha Value*/
        float                 echo8_beta;         /*Echo 8 Beta Value*/
        float                 float_padding[8];   /*Please use this if you are adding any floats*/
        unsigned long         se_checksum;        /*Series Record checksum*/
        ATOMIC                se_complete;        /*Series Complete Flag*/
        ATOMIC                se_numarch;         /*Number of Images Archived*/
        ATOMIC                se_imagect;         /*Last Image Number Used*/
        ATOMIC                se_numimages;       /*Number of Images Existing*/
        ATOMIC                se_delta_cnt;       /*Indicates number of updates to header*/
        ATOMIC                se_numunimg;        /*Number of Unstored Images*/
        ATOMIC                se_toarchcnt;       /*Number of Unarchived Images*/
        long                  long_padding[8];    /*Please use this if you are adding any longs*/
        int                   se_datetime;        /*Allocation Series Data/Time stamp*/
        int                   se_actual_dt;       /*Actual Series Data/Time stamp*/
        int                   position;           /*Patient Position*/
        int                   entry;              /*Patient Entry*/
        int                   se_lndmrkcnt;       /*Landmark Counter*/
        int                   se_lastmod;         /*Date/Time of Last Change*/
   int            ExpType;
   int                   TrRest;
   int                   TrActive;
   int                   DumAcq;
   int            ExptTimePts;
        int                   int_padding[16];     /*Please use this if you are adding any ints*/
        unsigned short int    se_exno;            /*Exam Number*/
        unsigned short int    echo1_window;       /*Echo 1 Window Value*/
        unsigned short int    echo2_window;       /*Echo 2 Window Value*/
        unsigned short int    echo3_window;       /*Echo 3 Window Value*/
        unsigned short int    echo4_window;       /*Echo 4 Window Value*/
        unsigned short int    echo5_window;       /*Echo 5 Window Value*/
        unsigned short int    echo6_window;       /*Echo 6 Window Value*/
        unsigned short int    echo7_window;       /*Echo 7 Window Value*/
        unsigned short int    echo8_window;       /*Echo 8 Window Value*/
        short int             echo8_level;        /*Echo 8 Level Value*/
        short int             echo7_level;        /*Echo 7 Level Value*/
        short int             echo6_level;        /*Echo 6 Level Value*/
        short int             echo5_level;        /*Echo 5 Level Value*/
        short int             echo4_level;        /*Echo 4 Level Value*/
        short int             echo3_level;        /*Echo 3 Level Value*/
        short int             echo2_level;        /*Echo 2 Level Value*/
        short int             echo1_level;        /*Echo 1 Level Value*/
        short int             se_no;              /*Series Number*/
        short int             se_typ;             /*Series Type*/
        short int             se_source;          /*Series from which prescribed*/
        short int             se_plane;           /*Most-like Plane (for L/S)*/
        short int             scan_type;          /*Scout or Axial (for CT)*/
        short int             se_uniq;            /*The Make-Unique Flag*/
        short int             se_contrast;        /*Non-zero if > 0 image used contrast(L/S)*/
        short int             se_pseq;            /*Last Pulse Sequence Used (L/S)*/
        short int             se_sortorder;       /*Image Sort Order (L/S)*/
        short int             se_nacq;            /*Number of Acquisitions*/
        short int             xbasest;            /*Starting number for baselines*/
        short int             xbaseend;           /*Ending number for baselines*/
        short int             xenhst;             /*Starting number for enhanced scans*/
        short int             xenhend;            /*Ending number for enhanced scans*/
        short int         table_entry;        /*Table position for nMR and iMR*/
   short int             SwingAngle;         /*nMR - Swing Angle*/
        short int             LateralOffset;      /*nMR - Offset*/ 
   short int         GradientCoil;       /* Gradient Coil Selection */
   short int             se_subtype;         /* supplements se_typ, see DICOM (0008,0008)  //GSAge04506 */
   short int             BWRT;        /* for fMRI till ExptTimePts */
        short int             assetcal_serno;     /*Calibration Series number */    
        short int             assetcal_scnno;     /*Calibration Scan number*/
        short int             content_qualifn;    /*PRODUCT/RESEARCH/SERVICE*/
        short int             purecal_serno;      /*Calibration Series number*/
        short int             purecal_scnno;      /*Calibration Scan number*/
   short int             short_padding[26];  /*Please use this if you are adding any shots*/
        BLOCK                 se_verscre [2];     /*Genesis Version - Created*/
        BLOCK                 se_verscur [2];     /*Genesis Version - Now*/
        BLOCK                 se_suid [4];        /*Suite ID for this Series*/
        char                  se_alloc_key [13];  /*Process that allocated this record*/
        char                  se_diskid;          /*Disk ID for this Series*/
        char                  se_desc [65];       /*Series Description*/
        char                  pr_sysid [9];       /*Primary Receiver Suite and Host*/
        char                  pansysid [9];       /*Archiver Suite and Host*/
        char                  anref [3];          /*Anatomical reference*/
        char                  prtcl [25];         /*Scan Protocol Name*/
        char                  start_ras;          /*RAS letter for first scan location (L/S)*/
        char                  end_ras;            /*RAS letter for last scan location (L/S)*/
        BLOCK                 series_uid [32];    /*Series Entity Unique ID*/
        BLOCK                 landmark_uid [32];  /*Landmark Unique ID*/
        BLOCK                 equipmnt_uid [32];  /*Equipment Unique ID*/
        BLOCK                 refsopcuids[32];    /*Ref SOP Class UID */
        BLOCK                 refsopiuids[32];    /* Ref SOP Instance UID */
        BLOCK                 schacitval[16];     /* Sched Proc Action Item Seq - Value */
        BLOCK                 schacitdesc[16];    /*Sched Proc Action Item Seq - Description */
        BLOCK                 schacitmea[64];     /*Sched Proc Action Item Seq - Meaning */
        BLOCK                 schprocstdesc[65];  /*Sched Proc Step Desc */
        BLOCK                 schprocstid[16];    /*Sched Proc Step ID 1*/
        BLOCK                 reqprocstid[16];    /*Req Proc Step ID 1*/
        BLOCK                 perprocstid[16];    /*PPS ID */
        BLOCK                 perprocstdesc[65];  /*PPS Description*/

        BLOCK                 reqprocstid2[16];   /*Req Proc Step ID 2*/
        BLOCK                 reqprocstid3[16];   /*Req Proc Step ID 3*/
        BLOCK                 schprocstid2[16];    /*Sched Proc Step ID 2*/
        BLOCK                 schprocstid3[16];    /*Sched Proc Step ID 3*/
        BLOCK             refImgUID[4][32];      /* Dicom Reference Image */
    BLOCK                 PdgmStr[64];
   BLOCK            PdgmDesc[256];
   BLOCK            PdgmUID[64];
   BLOCK            ApplName[16];
   BLOCK            ApplVer[16];
        BLOCK                 asset_appl[12];     /*Asset application name*/
        BLOCK                 scic_a[32];         /*Scic_a values from CoilConfig.cfg*/
        BLOCK                 scic_s[32];         /*Scic_s values from CoilConfig.cfg*/
        BLOCK                 scic_c[32];         /*Scic_c values from CoilConfig.cfg*/
   BLOCK                 pure_cfg_params[64]; /* PURE Config Parameters from pure.cfg */
   char            operator_new[65];
   BLOCK                 se_padding[150];      /*Spare Space*/
}  SERIESDATATYPE ;
 
typedef struct _MRIMAGEDATATYPE {
        double                double_padding[8];  /*Please use this if you are adding any doubles*/
        float                 dfov;               /*Display field of view - X (mm)*/
        float                 dfov_rect;          /*Display field of view - Y (if different)*/
        float                 sctime;             /*Duration of scan*/
        float                 slthick;            /*Slice Thickness (mm)*/
        float                 scanspacing;        /*Spacing between scans (mm?)*/
        float                 loc;                /*Image location*/
        float                 tbldlta;            /*Table Delta*/
        float                 nex;                /*Number of Excitations*/
        float                 reptime;            /*Cardiac repetition time*/
        float                 saravg;             /*Average SAR*/
        float                 sarpeak;            /*Peak SAR*/
        float                 pausetime;          /*Pause Time*/
        float                 vbw;                /*Variable Bandwidth (Hz)*/
        float                 user0;              /*User Variable 0*/
        float                 user1;              /*User Variable 1*/
        float                 user2;              /*User Variable 2*/
        float                 user3;              /*User Variable 3*/
        float                 user4;              /*User Variable 4*/
        float                 user5;              /*User Variable 5*/
        float                 user6;              /*User Variable 6*/
        float                 user7;              /*User Variable 7*/
        float                 user8;              /*User Variable 8*/
        float                 user9;              /*User Variable 9*/
        float                 user10;             /*User Variable 10*/
        float                 user11;             /*User Variable 11*/
        float                 user12;             /*User Variable 12*/
        float                 user13;             /*User Variable 13*/
        float                 user14;             /*User Variable 14*/
        float                 user15;             /*User Variable 15*/
        float                 user16;             /*User Variable 16*/
        float                 user17;             /*User Variable 17*/
        float                 user18;             /*User Variable 18*/
        float                 user19;             /*User Variable 19*/
        float                 user20;             /*User Variable 20*/
        float                 user21;             /*User Variable 21*/
        float                 user22;             /*User Variable 22*/
        float                 proj_ang;           /*Projection Angle*/
        float                 concat_sat;         /*Concat Sat Type Flag*/
        float                 user23;             /*User Variable 23*/
        float                 user24;             /*User Variable 24*/
        float                 x_axis_rot;         /*X Axis Rotation*/
        float                 y_axis_rot;         /*Y Axis Rotation*/
        float                 z_axis_rot;         /*Z Axis Rotation*/
        float                 ihtagfa;            /*Tagging Flip Angle*/
        float                 ihtagor;            /*Cardiac Tagging Orientation*/
        float                 ihbspti;            /*Blood Suppression TI*/
        float                 rtia_timer;         /*Float Slop Field 4*/
        float                 fps;                /*Float Slop Field 5*/
        float                 vencscale;          /*Scale Weighted Venc*/
        float                 dbdt;               /*peak rate of change of gradient field, tesla/sec*/
        float                 dbdtper;            /*limit in units of percent of theoretical curve*/
        float                 estdbdtper;         /*PSD estimated limit in units of percent*/
        float                 estdbdtts;          /*PSD estimated limit in Teslas/sec*/
        float                 saravghead;         /*Avg head SAR*/
   float                 neg_scanspacing;    /*Negative scan spacing for overlap slices*/
        float                 user25;             /*User Variable 25*/
        float                 user26;             /*User Variable 26*/
        float                 user27;             /*User Variable 27*/
        float                 user28;             /*User Variable 28*/
        float                 user29;             /*User Variable 29*/
        float                 user30;             /*User Variable 30*/
        float                 user31;             /*User Variable 31*/
        float                 user32;             /*User Variable 32*/
        float                 user33;             /*User Variable 33*/
        float                 user34;             /*User Variable 34*/
        float                 user35;             /*User Variable 35*/
        float                 user36;             /*User Variable 36*/
        float                 user37;             /*User Variable 37*/
        float                 user38;             /*User Variable 38*/
        float                 user39;             /*User Variable 39*/
        float                 user40;             /*User Variable 40*/
        float                 user41;             /*User Variable 41*/
        float                 user42;             /*User Variable 42*/
        float                 user43;             /*User Variable 43*/
        float                 user44;             /*User Variable 44*/
        float                 user45;             /*User Variable 45*/
        float                 user46;             /*User Variable 46*/
        float                 user47;             /*User Variable 47*/
        float                 user48;             /*User Variable 48*/
   #define CAI_eff_res user48
   float                 RegressorVal;
   float                 SliceAsset;     /* Slice Asset in Asset Screen */
   float                 PhaseAsset;      /* Phase Asset in Asset Screen */
   float            sarValues[4];  /* correspoding SAR values for defined terms */
        float                 shim_fov[2];
        RASPOINT              shim_ctr_R[2];
        RASPOINT              shim_ctr_A[2];
        RASPOINT              shim_ctr_S[2];
        DIMXYTYPE             dim_X;              /*Image dimension - X*/
        DIMXYTYPE             dim_Y;              /*Image dimension - Y*/
        PIXSIZETYPE           pixsize_X;          /*Image pixel size - X*/
        PIXSIZETYPE           pixsize_Y;          /*Image pixel size - Y*/
        RASPOINT              ctr_R;              /*Center R coord of plane image*/
        RASPOINT              ctr_A;              /*Center A coord of plane image*/
        RASPOINT              ctr_S;              /*Center S coord of plane image*/
        RASPOINT              norm_R;             /*Normal R coord*/
        RASPOINT              norm_A;             /*Normal A coord*/
        RASPOINT              norm_S;             /*Normal S coord*/
        RASPOINT              tlhc_R;             /*R Coord of Top Left Hand Corner*/
        RASPOINT              tlhc_A;             /*A Coord of Top Left Hand Corner*/
        RASPOINT              tlhc_S;             /*S Coord of Top Left Hand Corner*/
        RASPOINT              trhc_R;             /*R Coord of Top Right Hand Corner*/
        RASPOINT              trhc_A;             /*A Coord of Top Right Hand Corner*/
        RASPOINT              trhc_S;             /*S Coord of Top Right Hand Corner*/
        RASPOINT              brhc_R;             /*R Coord of Bottom Right Hand Corner*/
        RASPOINT              brhc_A;             /*A Coord of Bottom Right Hand Corner*/
        RASPOINT              brhc_S;             /*S Coord of Bottom Right Hand Corner*/
        float                 float_padding[32];  /*Please use this if you are adding any floats*/
        unsigned long         cal_fldstr;         /*Calibrated Field Strength (x10 uGauss)*/
        unsigned long         im_checksum;        /*AcqRecon record checksum*/
        unsigned long         user_usage_tag;     /*Defines how following user CVs are to be filled in*/
                                                  /*Default value = 0x00000000*/
                                                  /*GE range = 0x00000001 - 0x7fffffff*/
                                                  /*Research = 0x80000000 - 0xffffffff*/
        unsigned long         user_fill_mapMSW;   /*Define what process fills in the user CVs, ifcc or TIR*/
        unsigned long         user_fill_mapLSW;   /*Define what process fills in the user CVs, ifcc or TIR*/
        ATOMIC                im_archived;        /*Image Archive Flag*/
        ATOMIC                im_complete;        /*Image Complete Flag*/
        long                  long_padding[8];    /*Please use this if you are adding any longs*/
        int                   im_datetime;        /*Allocation Image date/time stamp*/
        int                   im_actual_dt;       /*Actual Image date/time stamp*/
        int                   tr;                 /*Pulse repetition time(usec)*/
        int                   ti;                 /*Pulse inversion time(usec)*/
        int                   te;                 /*Pulse echo time(usec)*/
        int                   te2;                /*Second echo echo (usec)*/
        int                   tdel;               /*Delay time after trigger (msec)*/
        int                   mindat;             /*Minimum Delay after Trigger (uSec)*/
        int                   obplane;            /*Oblique Plane*/
        int                   slocfov;            /*Slice Offsets on Freq axis*/
        int                   obsolete1;          /*Center Frequency (0.1 Hz)*/
        int                   obsolete2;          /*Auto Center Frequency (0.1 Hz)*/
        int                   user_bitmap;        /*Bitmap defining user CVs*/
        int                   iopt;               /*Imaging Options*/
        int                   psd_datetime;       /*PSD Creation Date and Time*/
        int                   rawrunnum;          /*RawData Run Number*/
        int                   intr_del;           /*Interimage/interloc delay (uSec)*/
        int                   im_lastmod;         /*Date/Time of Last Change*/
        int                   im_pds_a;           /*PixelData size - as stored*/
        int                   im_pds_c;           /*PixelData size - Compressed*/
        int                   im_pds_u;           /*PixelData size - UnCompressed*/
        int                   thresh_min1;        /*Lower Range of Pixels 1*/
        int                   thresh_max1;        /*Upper Range of Pixels 1*/
        int                   thresh_min2;        /*Lower Range of Pixels 2*/
        int                   thresh_max2;        /*Upper Range of Pixels 2*/
   int                   numslabs;           /*Number of 3D Slabs*/
        int                   locsperslab;        /*Slice Locs Per 3D Slab*/
        int                   overlaps;           /*# of Slice Locs on Each Slab Which Overlap N eighbors*/
        int                   slop_int_4;         /*Image Filtering 0.5/0.2T*/
        int                   dfax;               /* Diffusion Direction for DW-EPI */
        int                   fphase;             /*Number Of Phases*/
        int                   offsetfreq;         /*Offset Frequency - Mag.Transfer*/
        int                   b_value;            /*B-value for DW-EPI*/
        int                   iopt2;              /*Imaging Option2*/
        int                   ihtagging;          /*tag type */
        int                   ihtagspc;           /*tag space */
        int                   ihfcineim;          /*Fast CINE interpolation method*/
        int                   ihfcinent;     /*Fast CINE normalization type*/
   int                   num_seg;          /*YMSge05074*/
   int                   oprtarr;             /*Respiratory Trigger windo*/
   int                   averages;             /*Number of averages for spectro*/
        int                   station_index;     /*Station Index*/ 
        int                   station_total;     /*Station Total*/
        int                   iopt3;             /*Imaging Option3*/
   int             delAcq;    /* Delay after Acquisition (MP / fMRI screen) */
        int                   rxmbloblen;     /* fMRI: RXM blob size */
        char*                 rxmblob;            /* When moving to 64 bit OS move this to top of the struct as it shall be 8 bytes */
        int                   int_padding[32];    /*Please use this if you are adding any ints*/
        IMATRIXTYPE           imatrix_X;          /*Image matrix size - X*/
        IMATRIXTYPE           imatrix_Y;          /*Image matrix size - Y*/
        unsigned short int    im_exno;            /*Exam number for this image*/
        unsigned short int    img_window;         /*Window Value*/
        short int             img_level;          /*Level Value*/
        short int             numecho;            /*Number of echoes*/
        short int             echonum;            /*Echo Number*/
        short int             im_uniq;            /*The Make-Unique Flag*/
        short int             im_seno;            /*Series Number for this image*/
        short int             im_no;              /*Image Number*/
        short int             contmode;           /*Image Contrast Mode*/
        short int             serrx;              /*Series from which prescribed*/
        short int             imgrx;              /*Image from which prescribed*/
        short int             screenformat;       /*Screen Format(8/16 bit)*/
        short int             plane;              /*Plane Type*/
        short int             im_compress;        /*Image compression type for allocation*/
        short int             im_scouttype;       /*Scout Type (AP or lateral)*/
        short int             contig;             /*Continuous Slices Flag*/
        short int             hrtrate;            /*Cardiac Heart Rate (bpm)*/
        short int             trgwindow;          /*Trigger window (% of R-R interval)*/
        short int             imgpcyc;            /*Images per cardiac cycle*/
        short int             obsolete3;            /*Actual Transmit Gain (.1 db)*/
        short int             obsolete4;           /*Actual Receive Gain Analog (.1 db)*/
        short int             obsolete5;           /*Actual Receive Gain Digital (.1 db)*/
        short int             mr_flip;            /*Flip Angle for GRASS scans (deg.)*/
        short int             cphase;             /*Total Cardiac Phase prescribed*/
        short int             swappf;             /*Swap Phase/Frequency Axis*/
        short int             pauseint;           /*Pause Interval (slices)*/
        short int             obsolete6;          /*Auto Transmit Gain (0.1 dB)*/
        short int             obsolete7;          /*PreScan R1 - Analog*/
        short int             obsolete8;          /*PreScan R2 - Digital*/
        short int             not_used_1;         /* Available for use */
        short int             imode;              /*Imaging Mode*/
        short int             pseq;               /*Pulse Sequence*/
        short int             pseqmode;           /*Pulse Sequence Mode*/
        short int             unused_monsar;      /*Monitor SAR flag No longer is use */
        short int             ctyp;               /*Coil Type*/
        short int             surfctyp;           /*Surface Coil Type*/
        short int             surfcext;           /*Extremity Coil Flag*/
        short int             supp_tech;          /*SAT fat/water/none*/
        short int             slquant;            /*Number of slices in this scan group*/
        short int             gpre;               /*Graphically prescribed*/
        short int             satbits;            /*Bitmap of SAT selections*/
        short int             scic;               /*Surface Coil Intensity Correction Flag*/
        short int             satxloc1;           /*R-side SAT pulse loc rel to lndmrk*/
        short int             satxloc2;           /*L-side SAT pulse loc rel to lndmrk*/
        short int             satyloc1;           /*A-side SAT pulse loc rel to lndmrk*/
        short int             satyloc2;           /*P-side SAT pulse loc rel to lndmrk*/
        short int             satzloc1;           /*S-side SAT pulse loc rel to lndmrk*/
        short int             satzloc2;           /*I-side SAT pulse loc rel to lndmrk*/
        short int             satxthick;          /*Thickness of X-axis SAT pulse*/
        short int             satythick;          /*Thickness of Y-axis SAT pulse*/
        short int             satzthick;          /*Thickness of Z-axis SAT pulse*/
        short int             flax;               /*Phase contrast flow axis*/
        short int             venc;               /*Phase contrast velocity encoding*/
        short int             thk_disclmr;        /*Slice Thickness*/
        short int             obsolete9;            /*Auto/Manual Prescan flag*/
        short int             obsolete10;          /*Bitmap of changed values*/
        short int             image_type;         /*Magnitude, Phase, Imaginary, or Real*/
        short int             vas_collapse;       /*Collapse Image*/
        short int             proj_alg;           /*Projection Algorithm*/
        short int             echo_trn_len;       /*Echo Train Length for Fast Spin Echo*/
        short int             frac_echo;          /*Fractional Echo - Effective TE Flag*/
        short int             prep_pulse;         /*Preporatory Pulse Option*/
        short int             cphasenum;          /*Cardiac Phase Number*/
        short int             var_echo;           /*Variable Echo Flag*/
        short int             scanactno;          /*Scan Acquisition Number*/
        short int             vasflags;           /*Magnitude Weighting Flag*/
        short int             integrity;          /*GE Image Integrity*/
        short int             freq_dir;           /*Frequency Direction*/
        short int             vas_mode;           /*Vascular Mode*/
   short int             hole;
        short int             pscopts;            /*bitmap of prescan options*/
        short int             obsolete11;          /*gradient offset in X-direction*/
        short int             obsolete12;          /*gradient offset in Y-direction*/
        short int             obsolete13;          /*gradient offset in Z-direction*/
        short int             unoriginal;         /*identifies image as original or unoriginal*/
        short int             interleaves;        /*number of EPI shots*/
        short int             effechospace;       /*effective echo spacing for EPI*/
        short int             viewsperseg;        /*views per segment*/
        short int             rbpm;               /*respiratory rate, breaths per min*/
        short int             rtpoint;            /*respiratory trigger point as percent of max.*/
        short int             rcvrtype;           /*type of receiver used*/
        short int             sarMode;  /* Sar Ctrl Mode (Normal, 1st or 2nd) */
        short int             dBdtMode; /* dBdt Ctrl Mode (Normal, 1st or 2nd) */
   short int         govBody;  /* Governing Body MHW/IEC/FDA  */
   short int         sarDefinition; /* Defined terms avaialble */
        short int             no_shimvol;
        short int             shim_vol_type;
        short int             current_phase;      /*Current Phase for this image (DP)*/
        short int             art_level;          /* Acoustic reduction level */
        short int             slice_group_number; /*value 0=no group defined, 1=this slice belongs to group 1 and so on*/
        short int             number_of_slice_groups; /*value 0=no groups defined, 1=total group is one and so on*/
     short int             show_in_autoview;   /* if 1 image will be displayed in auto view */
        short int             short_padding[32];  /*Please use this if you are adding any shorts*/
        char                  psdname [33];       /*Pulse Sequence Name*/
        char                  proj_name [13];     /*Projection Algorithm Name*/
        char                  psd_iname [13];     /*PSD name from inside PSD*/
        char                  im_diskid;          /*Disk ID for this Image*/
        BLOCK                 pdid [14];          /*Pixel Data ID*/
        BLOCK                 im_suid [4];        /*Suite id for this image*/
        char                  contrastIV [17];    /*IV Contrast Agent*/
        char                  contrastOral [17];  /*Oral Contrast Agent*/
        char                  loc_ras;            /*RAS letter of image location*/
        char                  forimgrev [4];      /*Foreign Image Revision*/
        char                  cname [17];         /*Coil Name*/
        BLOCK                 im_verscre [2];     /*Genesis Version - Created*/
        BLOCK                 im_verscur [2];     /*Genesis Version - Now*/
        char                  im_alloc_key [13];  /**/
        char                  ref_img;            /*Reference Image Field*/
        char                  sum_img;            /*Summary Image Field*/
        char                  filter_mode [16];    /*String Slop Field 1*/
        char                  slop_str_2 [16];    /*String Slop Field 2*/
        BLOCK                 image_uid [32];     /*Image Unique ID*/
        BLOCK                 sop_uid [32];       /*Service Obj Class Unique ID*/
        BLOCK                 GEcname[24];   /*GECoilname for the cname */
        BLOCK                 usedCoilData[100];  /*Concatenated str of coilcode and chip serialID */
        BLOCK                 astcalseriesuid[32];
        BLOCK                 purecalseriesuid[32];
        BLOCK                 xml_psc_shm_vol[32];
   BLOCK            rxmpath[64];
   char                  psdnameannot [33];       /*Pulse Sequence Name Annotation */
        BLOCK                 img_hdr_padding[210];

}  MRIMAGEDATATYPE ;

#define GENESIS_DATABASE_REVISION       "14"

/* * * Constants to support locking/unlocking and in-use counts * * */

#define DB_SUITEMAGIC_MASK 0x7c00
#define DB_EXAMMAGIC_MASK  0x7fe0
#define MAX_SUITEMAGIC 31
#define MAX_EXAMMAGIC  31
#define MAX_SERIESMAGIC 31


#define SUITE_ID_LENGTH 4
typedef unsigned short int dbkey_exam_type;
typedef short int dbkey_magic_type;
typedef short int dbkey_series_type;
typedef short int dbkey_image_type;

/* the Image Database Key as a Structure */
struct DbKeyNamer {
   char su_id[SUITE_ID_LENGTH];
   dbkey_magic_type      mg_no;
   dbkey_exam_type       ex_no;
   dbkey_series_type     se_no;
   dbkey_image_type      im_no;
};
typedef struct DbKeyNamer DbKey;

/* File names used by the Image Database */


/* Key lengths used by the Image Database */

/* Some specific values that can be in image DbKeys */
#define NULLEXAM   0
#define NULLSERIES   0
#define NULLIMAGE   0
#define MINNORMEXAM   1
#define MAXNORMEXAM   50000
#define MINDIAGEXAM   50001
#define MAXDIAGEXAM   63500
#define EXAMERROR    65535
#define NORMALEXAM   0
#define DIAGEXAM   1
#define MAXIMAGENUM   999
#define MAXSERIESNUM   999

#define SUITEKEYTYPE   4
#define EXAMKEYTYPE   3
#define SERIESKEYTYPE   2
#define IMAGEKEYTYPE   1

#define DB_LOG_ERRORS      1
#define DB_DONT_LOG_ERRORS   0

#define PCR001      "pcr001"  /* record key for the one record in file */


/* Allocation Structures and Checksum Macros */

struct AllocStructNamer {
        char            suite[4];               /*** Suite Checksum Fields  ***/
        char            disk_id;
        char            prodid[13];             /*** end                    ***/

        unsigned short int      exam;           /*** Exam Checksum Fields   ***/
        int             exam_timestamp;
        char            ex_type[3];
        char            patient_name[25];
        char            patient_id[13];         /*** end                    ***/

        short int       series;                 /*** Series Checksum Fields ***/
        int             series_timestamp;
        char            sysid[9];       /*** end                    ***/

        short int       image;                  /*** Image Checksum Fields  ***/
        int             image_timestamp;        /*** end                    ***/

        short int       series_type;            /*** Other needed fields    ***/
        short int       source_series;
        char            hospital[33];
        char            pan_sysid[9];
        short int       image_alloc_cnt;
        short int       suite_magic;
        short int       exam_magic;
        short int       series_magic;
        int             pixelHeight;
        int             pixelWidth;
        int             pixelDepth;
        int             pixelCompType;          /*** end                    ***/
};
typedef struct AllocStructNamer AllocStruct;


#define ARRAYOFFSET(X,Y) (((unsigned long)Y.X) - ((unsigned long)&Y))
#ifndef OFFSET
#define OFFSET(X,Y) (((unsigned long)&Y.X) - ((unsigned long)&Y))
#endif

#define CSUM_SULEN(x) (short)(OFFSET(exam,(x)) - ARRAYOFFSET(suite,(x)))
#define CSUM_EXSTART(x) CSUM_SULEN(x)
#define CSUM_EXLEN(x) (short)(OFFSET(series,(x)) - OFFSET(exam,(x)))
#define CSUM_SESTART(x) CSUM_EXSTART(x) + CSUM_EXLEN(x)
#define CSUM_SELEN(x) (short)(OFFSET(image,(x)) - OFFSET(series,(x)))
#define CSUM_IMSTART(x) CSUM_SESTART(x) + CSUM_SELEN(x)
#define CSUM_IMLEN(x) (short)(OFFSET(series_type,(x)) - OFFSET(image,(x)))

#define SUITE_CHECKSUM(x) idb_checksum((unsigned char *)&(x), CSUM_SULEN(x))
#define EXAM_CHECKSUM(x) idb_checksum((unsigned char *)&(x) + CSUM_EXSTART(x),\
               CSUM_EXLEN(x))
#define SERIES_CHECKSUM(x) idb_checksum((unsigned char *)&(x) \
                      + CSUM_SESTART(x), CSUM_SELEN(x))
#define IMAGE_CHECKSUM(x) idb_checksum((unsigned char *)&(x) + CSUM_IMSTART(x),\
               CSUM_IMLEN(x))

/* This was pulled from net_uid_create.c (NetUID) because
   it was not include-file available. */
#define GEMS_UID_HEADER "1.2.840.113619.2.1."
#define UID_LEN 64
#define DB_UID_LEN 32



#endif /*IMAGEDB_H_INCL*/

