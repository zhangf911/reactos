/*
 * VideoPort driver
 *
 * Copyright (C) 2002, 2003, 2004 ReactOS Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; see the file COPYING.LIB.
 * If not, write to the Free Software Foundation,
 * 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * $Id: interrupt.c,v 1.1.2.1 2004/03/14 17:16:28 navaraf Exp $
 */

#include "videoprt.h"

/* PRIVATE FUNCTIONS **********************************************************/

BOOLEAN STDCALL
VideoPortInterruptRoutine(
   IN struct _KINTERRUPT *Interrupt,
   IN PVOID ServiceContext)
{
   PVIDEO_PORT_DEVICE_EXTENSION DeviceExtension = ServiceContext;
   PVIDEO_PORT_DRIVER_EXTENSION DriverExtension;

   DriverExtension = IoGetDriverObjectExtension(
      DeviceExtension->FunctionalDeviceObject->DriverObject,
      DeviceExtension->FunctionalDeviceObject->DriverObject);
  
   ASSERT(DriverExtension->InitializationData.HwInterrupt != NULL);

   return DriverExtension->InitializationData.HwInterrupt(
      DeviceExtension->MiniPortDeviceExtension);
}

/* PUBLIC FUNCTIONS ***********************************************************/

/*
 * @implemented
 */

VP_STATUS STDCALL
VideoPortEnableInterrupt(IN PVOID HwDeviceExtension)
{
   PVIDEO_PORT_DEVICE_EXTENSION DeviceExtension;
   BOOLEAN Status;

   DPRINT("VideoPortEnableInterrupt\n");

   DeviceExtension = CONTAINING_RECORD(
      HwDeviceExtension,
      VIDEO_PORT_DEVICE_EXTENSION,
      MiniPortDeviceExtension);

   Status = HalEnableSystemInterrupt(
      DeviceExtension->InterruptVector,
      0,
      DeviceExtension->InterruptLevel);

   return Status ? NO_ERROR : ERROR_INVALID_ACCESS;
}

/*
 * @implemented
 */

VP_STATUS STDCALL
VideoPortDisableInterrupt(IN PVOID HwDeviceExtension)
{
   PVIDEO_PORT_DEVICE_EXTENSION DeviceExtension;
   BOOLEAN Status;

   DPRINT("VideoPortDisableInterrupt\n");

   DeviceExtension = CONTAINING_RECORD(
      HwDeviceExtension,
      VIDEO_PORT_DEVICE_EXTENSION,
      MiniPortDeviceExtension);

   Status = HalDisableSystemInterrupt(
      DeviceExtension->InterruptVector,
      0);

   return Status ? NO_ERROR : ERROR_INVALID_ACCESS;
}
