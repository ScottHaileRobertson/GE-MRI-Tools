/*@Start***********************************************************/
/* GEMSBG Include File
 * Copyright (C) 1992 The General Electric Company
 *
 *      Include File Name:  toolsdata   
 *      Developer:
 *
 * $Source: toolsdata.h $
 * $Revision: 1.3 $  $Date: 1/29/92 15:09:28 $
 */

/*@Synopsis 
*/     

/*@Description
     
*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                          toolsdata.h                               */
/*                                                                    */
/* This include file isn't dependent upon any other include file.     */
/* it defines the structure that is used to fill the toolsdata        */
/* portion of the RDB header.                                         */
/*                                                                    */
/* The maximum number of coils is set to be equal to the number of    */
/* coils that Scan Rx supports.                                       */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
 
/*@End*********************************************************/

/* only do this once in any given compilation.*/
#ifndef  TOOLSDATA_INCL
#define  TOOLSDATA_INCL

#define	TD_MAX_COILS	16

typedef struct
{
	int		fileFormatRev;
	short		researchSite;
	int		lineFreq;
	short		specRFamp;
	short		broadBandXcvr;
	short		trDither;
	int 		rfBodyVectorZ;
	int 		rfBodyLength;
	int 		rfBodyRadius;
	int 		rfHeadVectorY;
	int 		rfHeadVectorZ;
	int 		rfHeadLength;
	int 		rfHeadRadius;
	int 		xfull;
	int 		yfull;
	int 		zfull;
	float		gradientScale;
	int 		minGradRamp;
	int 		ampCalHead;
	int 		ampCalBody;
	int		magnetType;
	int 		fieldStrength;
	int 		isoVectorZ;
	int 		tableLimit;
	int 		begTravel;
	int 		endTravel;
	int 		maxGradShim;
	int 		hpdl;
	int 		bpdl;
	int 		hpsl;
	int 		bpsl;
	int 		hpv;
	int 		bpv;
	float 		hqpc;
	float 		bqpc;
	int 		hllr;
	int 		bllr;
	float		netLoss;
	int 		maxCoilCurrent;
	int 		aveCoilCurrent;
	int 		fixedHWtdel;
	int 		cineTdel;
	int 		minBW;
	int 		edrThreshold;
	int 		numAPs;
	int 		sizeAP0;
	int 		sizeAP1;
	int 		sizeAP2;
	int 		sizeAP3;
	int 		numTPSmemBds;
	int 		sizeTPSmemBd0;
	int 		sizeTPSmemBd1;
	int 		sizeTPSmemBd2;
	int 		sizeTPSmemBd3;
	int 		sizeTPSmemBd4;
	int 		numRcvrs;
}  TD_MR_CFG;
	

typedef struct
{
	char		coilName[16];
	char		korecName[4];
	int		coilType;
	short		extremity;
	float		cableLoss;
	float		coilLoss;
	float		reconScale;
	int		linearQuad;
	short 		multiCoil;
	int		numRec;
	int		startRec;
	int		endRec;
	int		mcPortEnable;
}   TD_COIL_CFG;


typedef struct
{
	float		field_strength;

}   TD_FS_CFG;


typedef struct
{
	TD_MR_CFG	mrCfg;
	TD_COIL_CFG	coilCfg[TD_MAX_COILS];
	TD_FS_CFG	fsCfg;

}   TOOLSDATA_INFO;


typedef union
{
	TOOLSDATA_INFO	toolsdataInfo;
	char		toolsdataBuffer[2048];
}   TOOLSDATA;

#endif /* TOOLSDATA_INCL */

