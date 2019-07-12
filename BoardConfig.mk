#
# Copyright (C) 2017-2021 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from sakura-common
include device/xiaomi/sakura-common/BoardConfigCommon.mk

DEVICE_PATH := device/xiaomi/daisy

# Kernel
TARGET_KERNEL_CONFIG := daisy_defconfig

# Filesystem
TARGET_USERIMAGES_SPARSE_EXT_DISABLED := false
TARGET_NO_RECOVERY := true
TARGET_COPY_OUT_VENDOR := vendor
TARGET_COPY_OUT_PRODUCT := system/product
TARGET_COPY_OUT_SYSTEM_EXT := system/system_ext

# A/B
AB_OTA_UPDATER := true

AB_OTA_PARTITIONS += \
    boot \
    system \
    vendor

# Partitions
BOARD_VENDORIMAGE_PARTITION_SIZE := 805306368
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 2684354560

BOARD_BUILD_SYSTEM_ROOT_IMAGE := true
BOARD_HAS_REMOVABLE_STORAGE := true
BOARD_USES_RECOVERY_AS_BOOT := true
BOARD_VENDORIMAGE_FILE_SYSTEM_TYPE := ext4

# HIDL
DEVICE_MANIFEST_FILE += $(DEVICE_PATH)/manifest.xml

# Recovery
TARGET_RECOVERY_FSTAB := $(DEVICE_PATH)/rootdir/etc/fstab.qcom

# Security Patch Level
VENDOR_SECURITY_PATCH := 2021-07-01

# Inherit the proprietary files
include vendor/xiaomi/daisy/BoardConfigVendor.mk
