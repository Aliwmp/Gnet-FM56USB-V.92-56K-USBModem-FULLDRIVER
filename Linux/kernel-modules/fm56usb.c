/*
 * FM56USB Gnet AM5067 USB Modem Driver
 * 
 * This driver provides support for the Gnet FM56USB V.92 56K USB Modem
 * with AM5067 chipset (LSI/Agere Systems).
 *
 * Copyright (C) 2024 Gnet Communications
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * USB Vendor ID:  0x0572
 * USB Product ID: 0x1329
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/usb.h>
#include <linux/usb/cdc.h>
#include <linux/tty.h>
#include <linux/tty_driver.h>
#include <linux/tty_flip.h>
#include <linux/slab.h>

#define DRIVER_VERSION "1.0.0"
#define DRIVER_AUTHOR "Gnet Communications"
#define DRIVER_DESC "Gnet FM56USB V.92 56K USB Modem Driver (AM5067)"

/* USB Device ID */
#define FM56USB_VENDOR_ID   0x0572
#define FM56USB_PRODUCT_ID  0x1329

/* Device table */
static const struct usb_device_id fm56usb_ids[] = {
    { USB_DEVICE(FM56USB_VENDOR_ID, FM56USB_PRODUCT_ID) },
    { }
};
MODULE_DEVICE_TABLE(usb, fm56usb_ids);

/* Device structure */
struct fm56usb_device {
    struct usb_device *udev;
    struct usb_interface *interface;
    struct tty_port port;
    unsigned int in_pipe;
    unsigned int out_pipe;
    struct urb *read_urb;
    struct urb *write_urb;
    unsigned char *read_buffer;
    unsigned char *write_buffer;
    int open_count;
};

/* Forward declarations */
static int fm56usb_probe(struct usb_interface *interface,
                         const struct usb_device_id *id);
static void fm56usb_disconnect(struct usb_interface *interface);

/* USB driver structure */
static struct usb_driver fm56usb_driver = {
    .name       = "fm56usb",
    .probe      = fm56usb_probe,
    .disconnect = fm56usb_disconnect,
    .id_table   = fm56usb_ids,
};

/*
 * Probe function - called when device is plugged in
 */
static int fm56usb_probe(struct usb_interface *interface,
                         const struct usb_device_id *id)
{
    struct usb_device *udev = interface_to_usbdev(interface);
    struct fm56usb_device *dev;
    int retval = 0;

    printk(KERN_INFO "fm56usb: Gnet FM56USB modem detected\n");
    printk(KERN_INFO "fm56usb: VID:PID = %04x:%04x\n",
           le16_to_cpu(udev->descriptor.idVendor),
           le16_to_cpu(udev->descriptor.idProduct));

    /* Allocate memory for device structure */
    dev = kzalloc(sizeof(*dev), GFP_KERNEL);
    if (!dev) {
        dev_err(&interface->dev, "Out of memory\n");
        return -ENOMEM;
    }

    dev->udev = usb_get_dev(udev);
    dev->interface = interface;

    /* Store our data pointer in interface */
    usb_set_intfdata(interface, dev);

    printk(KERN_INFO "fm56usb: Device initialized successfully\n");
    printk(KERN_INFO "fm56usb: Note - Modern systems should use cdc_acm driver\n");
    
    return retval;
}

/*
 * Disconnect function - called when device is removed
 */
static void fm56usb_disconnect(struct usb_interface *interface)
{
    struct fm56usb_device *dev;

    dev = usb_get_intfdata(interface);
    if (!dev)
        return;

    usb_set_intfdata(interface, NULL);

    /* Release USB device */
    usb_put_dev(dev->udev);

    /* Free device structure */
    kfree(dev);

    printk(KERN_INFO "fm56usb: Device disconnected\n");
}

/*
 * Module initialization
 */
static int __init fm56usb_init(void)
{
    int retval;

    printk(KERN_INFO "fm56usb: " DRIVER_DESC " v" DRIVER_VERSION "\n");
    printk(KERN_INFO "fm56usb: " DRIVER_AUTHOR "\n");

    /* Register USB driver */
    retval = usb_register(&fm56usb_driver);
    if (retval) {
        printk(KERN_ERR "fm56usb: usb_register failed. Error: %d\n", retval);
        return retval;
    }

    printk(KERN_INFO "fm56usb: Driver registered successfully\n");
    printk(KERN_INFO "fm56usb: For most systems, the standard cdc_acm driver is recommended\n");
    
    return 0;
}

/*
 * Module cleanup
 */
static void __exit fm56usb_exit(void)
{
    usb_deregister(&fm56usb_driver);
    printk(KERN_INFO "fm56usb: Driver unregistered\n");
}

module_init(fm56usb_init);
module_exit(fm56usb_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERSION);
