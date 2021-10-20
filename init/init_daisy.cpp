/*
   Copyright (c) 2014, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived

      from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <sys/sysinfo.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <android-base/properties.h>
#include "property_service.h"
#include "vendor_init.h"

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void property_override_dual(char const system_prop[], char const vendor_prop[], char const value[])
{
    property_override(system_prop, value);
    property_override(vendor_prop, value);
}

void property_override_multi(char const system_prop[], char const vendor_prop[],char const bootimage_prop[], char const value[]) {
    property_override(system_prop, value);
    property_override(vendor_prop, value);
    property_override(bootimage_prop, value);
}

void load_dalvik_properties() {
    struct sysinfo sys;

    sysinfo(&sys);
    if (sys.totalram > 3072ull * 1024 * 1024) {
        // from - phone-xxhdpi-4096-dalvik-heap.mk
	property_override("dalvik.vm.heapstartsize", "8m");
	property_override("dalvik.vm.heaptargetutilization", "0.6");
	property_override("dalvik.vm.heapgrowthlimit", "192m");
	property_override("dalvik.vm.heapsize", "512m");
	property_override("dalvik.vm.heapmaxfree", "16m");
	property_override("dalvik.vm.heapminfree", "4m");
    } else {
        // from - phone-xhdpi-2048-dalvik-heap.mk
	property_override("dalvik.vm.heapstartsize", "8m");
	property_override("dalvik.vm.heaptargetutilization", "0.6");
	property_override("dalvik.vm.heapgrowthlimit", "192m");
	property_override("dalvik.vm.heapsize", "512m");
	property_override("dalvik.vm.heapmaxfree", "8m");
	property_override("dalvik.vm.heapminfree", "2m");
    }
}

void vendor_load_properties()
{
    load_dalvik_properties();

    // fingerprint
    property_override("ro.build.description", "coral-user 11 RQ3A.211001.001 7641976 release-keys");
    property_override_multi("ro.build.fingerprint", "ro.vendor.build.fingerprint", "ro.bootimage.build.fingerprint", "google/coral/coral:11/RQ3A.211001.001/7641976:user/release-keys");
    // Misc
    property_override("ro.com.google.clientidbase", "android-xiaomi");
    property_override("ro.com.google.clientidbase.ms", "android-xiaomi-rev1");
}