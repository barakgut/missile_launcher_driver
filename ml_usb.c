#include <linux/uaccess.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/usb.h>

#include "ml_usb.h"

#define ML_LOG(fmt, args...) \
	printk(KERN_INFO "[ML-LOG] %s(%d): " fmt "\n", __FUNCTION__, __LINE__, ##args)

static int ml_probe(struct usb_interface *interface, const struct usb_device_id *id);
static void ml_disconnect(struct usb_interface *interface);
static int ml_open(struct inode *inode, struct file *file);
static ssize_t ml_write(struct file *file, const char *user_buffer, size_t count, loff_t *ppos);

/* table of devices that work with this driver */
static struct usb_device_id ml_usb_id_table[] = 
{
	{ USB_DEVICE(ML_VENDOR_ID, ML_PRODUCT_ID) },
	{}
};

/*  USB drivers use ID table to support hotplugging.
	This must be set or our driver probe function will never get called */
MODULE_DEVICE_TABLE(usb, ml_usb_id_table);

static struct file_operations ml_fops = 
{
	.owner =	THIS_MODULE,
	.open =		ml_open,
	.write =	ml_write
};

static struct usb_class_driver ml_class_driver = 
{
	.name = "ml%d",
	.fops = &ml_fops
};

static struct usb_driver ml_driver = 
{
	.name = "ml_driver",
	.probe = ml_probe,
	.disconnect = ml_disconnect,
	.id_table = ml_usb_id_table
};

static int ml_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	struct usb_device * udev = interface_to_usbdev(interface);

	ML_LOG("Probe missile launcher usb device");

	/* Ensure that the interface exists. */
	if(!udev)
	{
		ML_LOG("interface_to_usbdev returned NULL");
		return -ENODEV;
	}

	/* Associate the usb_device with the interface. */
	usb_set_intfdata(interface, udev);

	/* Now attempt to actually create the device. */
	return usb_register_dev(interface, &ml_class_driver);
}

static void ml_disconnect(struct usb_interface *interface)
{
	ML_LOG("Missile launcher usb device disconnected");

	/* Deregister the device we created. */
	usb_deregister_dev(interface, &ml_class_driver);
}

static int ml_open(struct inode *inode, struct file *file)
{
	int subminor = iminor(inode);
	struct usb_interface * interface = usb_find_interface(&ml_driver, subminor);

	ML_LOG("Open ml%d", subminor);

	/* Ensure that the interface is valid. */
	if(!interface)
	{
		ML_LOG("unable to find interface for subminor");
		return -ENODEV;
	}

	/* Store a pointer to the usb_device instance with the file. */
	file->private_data = usb_get_intfdata(interface);

	return 0;
}

static ssize_t ml_write(struct file *file, const char *user_buffer, size_t count, loff_t *ppos)
{
	u8 * buf = NULL;
	int retval = -ENOMEM;
	struct usb_device * udev;

	udev = file->private_data;

	ML_LOG("Send command 0x%.x to Missile launcher usb device size: %d", (int)user_buffer[0], (int)count);
	buf = kzalloc(ML_CTRL_BUFFER_SIZE, GFP_KERNEL);

	if (!file || !user_buffer || count != 1)
	{
		ML_LOG("Invalid arguments");
		return retval;
	}

	if(!buf)
    	{
       		ML_LOG("unable to allocate memory for control message");
		return retval;
	}


	if (0 != copy_from_user(&buf[0], user_buffer, 1))
	{
		ML_LOG("Can't copy buffer from userspace");
		kfree(buf);

		return retval;
	}
	
	memset(&buf[1], 0, ML_CTRL_BUFFER_SIZE - 1);

	/* Send the data to the device and free the memory. */
	retval = usb_control_msg(udev,
		             usb_sndctrlpipe(udev, 0),
		             ML_CTRL_REQUEST,
		             ML_CTRL_REQUEST_TYPE,
		             ML_CTRL_VALUE,
		             ML_CTRL_INDEX,
		             buf,
		             8,
		             2000);
	kfree(buf);

	ML_LOG("usb_control_msg retval %d", retval);

	return retval;
}

static int __init ml_usb_init(void)
{
	int result;

	ML_LOG("Register Missile launcher USB driver to usbcore");

	result = usb_register(&ml_driver);

	if (result < 0) 
	{
		ML_LOG("Registering driver failed error num: %d", result);
	} 
	else 
	{
		ML_LOG("Driver registered successfully");
	}

	return result;
}

static void __exit ml_usb_exit(void)
{
	usb_deregister(&ml_driver);

	ML_LOG("Driver deregistered from usbcore");
}

module_init(ml_usb_init);
module_exit(ml_usb_exit);

MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
MODULE_AUTHOR("Barak Gutman, Nathan Shain, Yuval Goldberg");
MODULE_DESCRIPTION("A USB driver for DreamCheeky missile launcher toy for Linux Course by Netzer, colman ac.");
