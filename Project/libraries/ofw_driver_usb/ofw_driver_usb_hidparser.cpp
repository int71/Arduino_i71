/* Copyright (C) 2011 Circuits At Home, LTD. All rights reserved.

This software may be distributed and modified under the terms of the GNU
General Public License version 2 (GPL2) as published by the Free Software
Foundation and appearing in the file GPL2.TXT included in the packaging of
this file. Please note that GPL2 Section 2[b] requires that all works based
on this software must also be made publicly available under the terms of
the GPL2 ("Copyleft").

Contact information
-------------------

Circuits At Home, LTD
Web      :  http://www.circuitsathome.com
e-mail   :  support@circuitsathome.com
 */

#include "ofw_driver_usb_hidparser.hpp"

//get HID report descriptor

/* WRONG! Endpoint is _ALWAYS_ ZERO for HID! We want the _INTERFACE_ value here!
uint8_t USBHID::GetReportDescr(uint8_t ep, USBReadParser *parser) {
        const uint8_t constBufLen = 64;
        uint8_t buf[constBufLen];

        uint8_t rcode = pUsb->ctrlReq(bAddress, ep, bmREQ_HID_REPORT, USB_REQUEST_GET_DESCRIPTOR, 0x00,
                HID_DESCRIPTOR_REPORT, 0x0000, 128, constBufLen, buf, (USBReadParser*)parser);

        //return ((rcode != hrSTALL) ? rcode : 0);
        return rcode;
}
 */
uint8_t USBHID::GetReportDescr(uint16_t wIndex, USBReadParser *parser) {
        const uint8_t constBufLen = 64;
        uint8_t buf[constBufLen];

        uint8_t rcode = pUsb->ctrlReq(bAddress, 0x00, bmREQ_HID_REPORT, USB_REQUEST_GET_DESCRIPTOR, 0x00,
                HID_DESCRIPTOR_REPORT, wIndex, 128, constBufLen, buf, (USBReadParser*)parser);

        //return ((rcode != hrSTALL) ? rcode : 0);
        return rcode;
}

//uint8_t USBHID::getHidDescr( uint8_t ep, uint16_t nbytes, uint8_t* dataptr )
//{
//    return( pUsb->ctrlReq( bAddress, ep, bmREQ_GET_DESCR, USB_REQUEST_GET_DESCRIPTOR, 0x00, HID_DESCRIPTOR_HID, 0x0000, nbytes, dataptr ));
//}

uint8_t USBHID::SetReport(uint8_t ep, uint8_t iface, uint8_t report_type, uint8_t report_id, uint16_t nbytes, uint8_t* dataptr) {
        return ( pUsb->ctrlReq(bAddress, ep, bmREQ_HID_OUT, HID_REQUEST_SET_REPORT, report_id, report_type, iface, nbytes, nbytes, dataptr, NULL));
}

uint8_t USBHID::GetReport(uint8_t ep, uint8_t iface, uint8_t report_type, uint8_t report_id, uint16_t nbytes, uint8_t* dataptr) {
        return ( pUsb->ctrlReq(bAddress, ep, bmREQ_HID_IN, HID_REQUEST_GET_REPORT, report_id, report_type, iface, nbytes, nbytes, dataptr, NULL));
}

uint8_t USBHID::GetIdle(uint8_t iface, uint8_t reportID, uint8_t* dataptr) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_HID_IN, HID_REQUEST_GET_IDLE, reportID, 0, iface, 0x0001, 0x0001, dataptr, NULL));
}

uint8_t USBHID::SetIdle(uint8_t iface, uint8_t reportID, uint8_t duration) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_HID_OUT, HID_REQUEST_SET_IDLE, reportID, duration, iface, 0x0000, 0x0000, NULL, NULL));
}

uint8_t USBHID::SetProtocol(uint8_t iface, uint8_t protocol) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_HID_OUT, HID_REQUEST_SET_PROTOCOL, protocol, 0x00, iface, 0x0000, 0x0000, NULL, NULL));
}

uint8_t USBHID::GetProtocol(uint8_t iface, uint8_t* dataptr) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_HID_IN, HID_REQUEST_GET_PROTOCOL, 0x00, 0x00, iface, 0x0001, 0x0001, dataptr, NULL));
}
