/* Dream Link */
#define ML_VENDOR_ID	0x1941

/* WH1080 Weather Station / USB Missile Launcher */
#define ML_PRODUCT_ID	0x8021

/* These parameters are according to the proprietary protocol of the Dream Cheeky Missile launcher */
#define ML_CTRL_BUFFER_SIZE	8
#define ML_CTRL_REQUEST_TYPE	0x21
#define ML_CTRL_REQUEST		0x09
#define ML_CTRL_VALUE		0x0
#define ML_CTRL_INDEX		0x0

enum ml_cmd_opcode 
{
	ML_CMD_OPCODE_STOP		=	0x00,
	ML_CMD_OPCODE_UP       		=    	0x01,
	ML_CMD_OPCODE_DOWN         	=	0x02,
	ML_CMD_OPCODE_LEFT         	=	0x04,
	ML_CMD_OPCODE_RIGHT        	=	0x08,
	ML_CMD_OPCODE_UP_LEFT      	=	(ML_CMD_OPCODE_UP | ML_CMD_OPCODE_LEFT),
	ML_CMD_OPCODE_DOWN_LEFT    	=	(ML_CMD_OPCODE_DOWN | ML_CMD_OPCODE_LEFT),
	ML_CMD_OPCODE_UP_RIGHT     	=	(ML_CMD_OPCODE_UP | ML_CMD_OPCODE_RIGHT),
	ML_CMD_OPCODE_DOWN_RIGHT   	=	(ML_CMD_OPCODE_DOWN | ML_CMD_OPCODE_RIGHT),
	ML_CMD_OPCODE_FIRE         	=	0x10
};
