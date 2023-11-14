

#ifndef BCM_CFG_H_
#define BCM_CFG_H_


/* Note:
 * LF --> '\n' --> 0x0A
 * CR --> '\r' --> 0x0D
 */


/************************ Send String ******************************/
/* Determine maximum number for How many element in Queue */
#define QUEUE_SEND_SIZE		10
// define 1st last string pattern if you did not want set it to Zero
//#define _1ST_LAST_STR_PATTERN	0x0A
// define 2nd last string pattern if you did not want set it to Zero
//#define _2ST_LAST_STR_PATTERN	 0




/************************ Send Frame ******************************/
/* Size of frame you want to receive in Queue */
#define FRAME_SEND_SIZE			50
/* Determine maximum number for How many element in Queue */
#define QUEUE_SEND_FRAME_SIZE	20
/* Select if you want to send string or frame with fixed size
 * or not fixed size frame and send size declared as first byte of send frame
 * Options: (SEND_FIXED_FRAME - SEND_VAR_FRAME - SEND_STRING)
 * Different string will send until reach NULL
 * Will frame will send data until reach size of frame CFG previous in FRAME_SEND_SIZE macro*/
#define SEND_FRAME_TYPE		SEND_VAR_FRAME



/* define 1st last string pattern if you did not want set it to Zero */
//#define _1ST_LAST_FRAME_PATTERN	'\n'

/* define 2nd last string pattern if you did not want set it to Zero */
//#define _2ST_LAST_FRAME_PATTERN	 0



/************************ Receive String ******************************/

/* Determine maximum number for How many element in Queue */
#define QUEUE_RECSTR_SIZE	3
/* Max Size of string Queue can take by value */
#define MAX_STR_SIZE		100

// Write the end of String you want to receive
// If you Did not want Second Pattern put Zero
// DockLight 1st 0x0D --> 2nd 0x0A
#define _1ST_STR_END_PATTERN	0x0A
#define _2ST_STR_END_PATTERN	0x00

/************************ Receive Frame ******************************/
/* Size of frame you want to receive in Queue */
#define FRAME_SIZE	50
/* Determine maximum number for How many element in Queue */
#define QUEUE_REC_SIZE	20

/* If frame Received has Fixed size
 * or Change and receive size as first byte
 * Options:
 * 			REC_FRAME_FIXED_SIZE
 * 			REC_FRAME_NO_FIXED_SIZE
 */
#define REC_FRAME_TYPE		REC_FRAME_NO_FIXED_SIZE

#endif /* BCM_CFG_H_ */
