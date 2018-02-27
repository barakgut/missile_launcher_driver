#include <linux/usb.h>
#include <linux/mutex.h>
#include <linux/kernel.h>

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

/* Structure to hold all of our device specific stuff */
struct ml_usb_driver_ctx {
	struct usb_device		*udev;				/* the usb device for this device */
	struct usb_interface		*interface;			/* the interface(physical) for this device */
	spinlock_t			cmd_lock;			/* lock while using cmd (urb) */
	struct mutex			io_mutex;			/* synchronize I/O with disconnect and limiting the access to this struct*/
	unsigned char			last_issued_cmd;		/* Last issued command */
	struct usb_endpoint_descriptor 	*int_in_endpoint;		/* Interrupt IN endpoint */
	unsigned char			*int_in_buffer;			/* 'wMaxPacketSize' bytes buffer to read from interrupt endpoint*/
	struct urb			*int_in_urb;			/* Interrupt IN URB to read data with*/
	unsigned char			*ctrl_buffer;			/* 8 bytes buffer control message */
	struct urb			*ctrl_urb;			/* control URB to rw data with*/
	struct usb_ctrlrequest 		*ctrl_pkt;			/* control setup packet*/
};

enum ml_cmd_opcode {
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

enum ml_mech_max {
	ML_MECH_MAX_UP       		=	0x80,
	ML_MECH_MAX_DOWN     		=	0x40,
	ML_MECH_MAX_LEFT     		=	0x04,
	ML_MECH_MAX_RIGHT    		=	0x08
};

