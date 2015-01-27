/*       "DESC:1*/
/* ************************************************************************/
/**/
/*        This file contains the global TYPES and parameters for the OP Code*/
/*        file.*/
/**/
/*        AUTHOR        : G.E. Medical Systems*/
/*                        NMR Software Engineering*/
/*                        Kevin Murphy*/
/**/
/*        PURPOSE       : Op Code packet definitions.*/
/**/
/*        DETAILS       : This file contains the offset into the Applications*/
/*                        packet header. This header will be identical for*/
/*                        every Op Code. Also contained in this file are the*/
/*                        three possible valid contents of the word which*/
/*                        contains the communications type in the header.*/
/**/
/*        GENERATION    DATE              AUTHOR NAME(S)*/
/*        ----------    ------------      --------------*/
/**/
/*        01.01.00      January 12,1984   Mark A. Leverence*/
/*        04.00.00      August 5,1987	  Mark A. Leverence*/
/*        05.00.00	Sept 28, 1989	  J.L.Foris */
/*        05.01.00	May 12, 1992	  J.L.Foris */
/* ************************************************************************/
/*       "ETX*/
/**/
/*----------------------------------------------------------------------------*/
 
#ifndef INCop_globalh
#define INCop_globalh

#include "GEtypes.h"			/* add reference for hard typecasting */

/*----------------------------------------------------------------------------*/
/* These parameters are the WORD offsets into the applications packet header. */
 
#define OP_HDR_REV		0
#define OP_HDR_LENGTH		1
#define OP_HDR_REQ_NMRID	2
#define OP_HDR_RESP_NMRID	8
#define OP_HDR_OPCODE		14
#define OP_HDR_PACKET_TYPE	15
#define OP_HDR_SEQUENCE_NUM	16
#define OP_HDR_PAD		17	/* not in rev 1 */
#define OP_HDR_STATUS		18	/* was 17 in rev 1 */
#define OP_HDR_APPL		20	/* was 19 in rev 1 */

/*-------------- end of the applications packet header offsets ---------------*/

/*----------------------------------------------------------------------------*/
/* This parameter is placed in the REV portion of the applications */
/* packet header.  It validates the interpretation of the applications */
/* header packet. */

#define OP_REVNUM1  1			/* original rev 1 revision */
#define OP_REVNUM   2			/* current (default) revnum */

/*-------------- end of the applications packet version ----------------------*/

/*----------------------------------------------------------------------------*/
/* This parameter is used in the LENGTH portion of the applications */
/* packet header.  It specifies the maximum number of WORDS of user data */
/* which may follow the applications header. */

#define OP_LENGTHLIM	5000

/*-------------- end of the applications packet length -----------------------*/

/*----------------------------------------------------------------------------*/
/* These parameters are placed in the PACKET_TYPE portion of the applications */
/* packet header. They describe who is the sender and who is the receiver */
/* between the requester NMRID and responder NMRID. */
 
#define OP_REQ_TYPE	1
#define OP_RESP_TYPE	2
#define OP_NEG_RESP_TYPE 3

/*------------- end of the type parameters -----------------------------------*/

/*----------------------------------------------------------------------------*/
/* These parameters are placed in the ENDIAN portion of the applications */
/* packet header. They describe what is this applications endian. */
 
#define OP_UNKNOWN_ENDIAN	0
#define OP_BIG_ENDIAN		1
#define OP_LITTLE_ENDIAN	2

/*------------- end of the endian information -----------------------------------*/

/*--------------------------------------------------------------------------*/
/*      This record type describes the applications packet header           */
/*      for C programmers.                                                  */
 

typedef s8 OP_NMRID_TYPE[12];
 

typedef struct {	/* original OP_HDR, needed for back compatability */

	n16 		rev;		/* Revision number (= OP_REVNUM1) */
	n16 		length;		/* The length of the following user
					   data in WORDS */
	OP_NMRID_TYPE	req_nmrid;	/* Requester NMRID */
	OP_NMRID_TYPE	resp_nmrid;	/* Responder NMRID */
	n16 		opcode;		/* The Opcode */
	n16 		packet_type;	/* Req, Resp, or Neg Resp */
	n16 		seq_num;	/* The sequence number */
	n32 		status;		/* The (return) Status */

	}  OP_HDR1_TYPE;
 

typedef struct {	/* default OP_HDR, 64 bit boundry alligned */

	s8	rev;		/* Revision number  (= OP_REVNUM) */
	s8      endian; /* Endian of this packet */
	n16		length;		/* The length of the following user
					   data in WORDS */
	OP_NMRID_TYPE	req_nmrid;	/* Requester NMRID */
	OP_NMRID_TYPE	resp_nmrid;	/* Responder NMRID */
	n16		opcode;		/* The Opcode */
	n16		packet_type;	/* Req, Resp, or Neg Resp */
	n16		seq_num;	/* The sequence number */
	n16		pad;
	n32		status;		/* The (return) Status */

	}  OP_HDR_TYPE;
 

/*---- end of C TYPE declaration for the appliactions packet header -------*/
#endif /* INCop_globalh */
