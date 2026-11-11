#ifndef EFI_EFIFWUPDATE_H_
#define EFI_EFIFWUPDATE_H_

#include "efisecureboot.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GUID \
    {0x86c77a67, 0xb97, 0x4633, {0xa1, 0x87, 0x49, 0x10, 0x4d, 0x06, 0x85, 0xc7}}

typedef struct _EFI_FIRMWARE_MANAGEMENT_PROTOCOL EFI_FIRMWARE_MANAGEMENT_PROTOCOL;

/* Printed as a flexible array, which cannot be the only member: the op-codes run on in memory. */
typedef struct {
    uint8_t Dependencies[1];
} EFI_FIRMWARE_IMAGE_DEP;

/*
 * Dependencies is printed as an EFI_FMP_DEP pointer, a type defined nowhere: it points to the
 * op-codes that EFI_FIRMWARE_IMAGE_DEP holds.
 */
typedef struct {
    uint8_t ImageIndex;
    EFI_GUID ImageTypeId;
    uint64_t ImageId;
    uint16_t *ImageIdName;
    uint32_t Version;
    uint16_t *VersionName;
    size_t Size;
    uint64_t AttributesSupported;
    uint64_t AttributesSetting;
    uint64_t Compatibilities;
    uint32_t LowestSupportedImageVersion;
    uint32_t LastAttemptVersion;
    uint32_t LastAttemptStatus;
    uint64_t HardwareInstance;
    EFI_FIRMWARE_IMAGE_DEP *Dependencies;
} EFI_FIRMWARE_IMAGE_DESCRIPTOR;

#define EFI_IMAGE_ATTRIBUTE_IMAGE_UPDATABLE 0x0000000000000001
#define EFI_IMAGE_ATTRIBUTE_RESET_REQUIRED 0x0000000000000002
#define EFI_IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED 0x0000000000000004
#define EFI_IMAGE_ATTRIBUTE_IN_USE 0x0000000000000008
#define EFI_IMAGE_ATTRIBUTE_UEFI_IMAGE 0x0000000000000010
#define EFI_IMAGE_ATTRIBUTE_DEPENDENCY 0x0000000000000020

#define EFI_IMAGE_COMPATIBILITY_CHECK_SUPPORTED 0x0000000000000001

/* Printed as 3, but the descriptor above, ending with Dependencies, is the version 4 one. */
#define EFI_FIRMWARE_IMAGE_DESCRIPTOR_VERSION 4

typedef struct {
    uint64_t MonotonicCount;
    EFI_WIN_CERTIFICATE_UEFI_GUID AuthInfo;
} EFI_FIRMWARE_IMAGE_AUTHENTICATION;

typedef EFI_STATUS (EFI_API *EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GET_IMAGE_INFO)(
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL *This,
    size_t *ImageInfoSize,
    EFI_FIRMWARE_IMAGE_DESCRIPTOR *ImageInfo,
    uint32_t *DescriptorVersion,
    uint8_t *DescriptorCount,
    size_t *DescriptorSize,
    uint32_t *PackageVersion,
    uint16_t **PackageVersionName
);

typedef EFI_STATUS (EFI_API *EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GET_IMAGE)(
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL *This,
    uint8_t ImageIndex,
    void *Image,
    size_t *ImageSize
);

typedef EFI_STATUS (EFI_API *EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS)(
    uintptr_t Completion
);

typedef EFI_STATUS (EFI_API *EFI_FIRMWARE_MANAGEMENT_PROTOCOL_SET_IMAGE)(
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL *This,
    uint8_t ImageIndex,
    const void *Image,
    size_t ImageSize,
    const void *VendorCode,
    EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS Progress,
    uint16_t **AbortReason
);

typedef EFI_STATUS (EFI_API *EFI_FIRMWARE_MANAGEMENT_PROTOCOL_CHECK_IMAGE)(
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL *This,
    uint8_t ImageIndex,
    const void *Image,
    size_t ImageSize,
    uint32_t *ImageUpdatable
);

#define EFI_IMAGE_UPDATABLE_VALID 0x0000000000000001
#define EFI_IMAGE_UPDATABLE_INVALID 0x0000000000000002
#define EFI_IMAGE_UPDATABLE_INVALID_TYPE 0x0000000000000004
#define EFI_IMAGE_UPDATABLE_INVALID_OLD 0x0000000000000008
#define EFI_IMAGE_UPDATABLE_VALID_WITH_VENDOR_CODE 0x0000000000000010

/* This is misprinted as a pointer to a pointer here and in SetPackageInfo(). */
typedef EFI_STATUS (EFI_API *EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GET_PACKAGE_INFO)(
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL *This,
    uint32_t *PackageVersion,
    uint16_t **PackageVersionName,
    uint32_t *PackageVersionNameMaxLen,
    uint64_t *AttributesSupported,
    uint64_t *AttributesSetting
);

#define EFI_PACKAGE_ATTRIBUTE_VERSION_UPDATABLE 0x0000000000000001
#define EFI_PACKAGE_ATTRIBUTE_RESET_REQUIRED 0x0000000000000002
#define EFI_PACKAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED 0x0000000000000004

typedef EFI_STATUS (EFI_API *EFI_FIRMWARE_MANAGEMENT_PROTOCOL_SET_PACKAGE_INFO)(
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL *This,
    const void *Image,
    size_t ImageSize,
    const void *VendorCode,
    uint32_t PackageVersion,
    const uint16_t *PackageVersionName
);

struct _EFI_FIRMWARE_MANAGEMENT_PROTOCOL {
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GET_IMAGE_INFO GetImageInfo;
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GET_IMAGE GetImage;
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_SET_IMAGE SetImage;
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_CHECK_IMAGE CheckImage;
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GET_PACKAGE_INFO GetPackageInfo;
    EFI_FIRMWARE_MANAGEMENT_PROTOCOL_SET_PACKAGE_INFO SetPackageInfo;
};

/* The specification gives the dependency expression op-codes values but no names. */
#define EFI_FMP_DEP_PUSH_GUID 0x00
#define EFI_FMP_DEP_PUSH_VERSION 0x01
#define EFI_FMP_DEP_VERSION_STR 0x02
#define EFI_FMP_DEP_AND 0x03
#define EFI_FMP_DEP_OR 0x04
#define EFI_FMP_DEP_NOT 0x05
#define EFI_FMP_DEP_TRUE 0x06
#define EFI_FMP_DEP_FALSE 0x07
#define EFI_FMP_DEP_EQ 0x08
#define EFI_FMP_DEP_GT 0x09
#define EFI_FMP_DEP_GTE 0x0A
#define EFI_FMP_DEP_LT 0x0B
#define EFI_FMP_DEP_LTE 0x0C
#define EFI_FMP_DEP_END 0x0D
#define EFI_FMP_DEP_DECLARE_LENGTH 0x0E

#define EFI_FIRMWARE_MANAGEMENT_CAPSULE_ID_GUID \
    {0x6dcbd5ed, 0xe82d, 0x4c44, {0xbd, 0xa1, 0x71, 0x94, 0x19, 0x9a, 0xd9, 0x2a}}

/* ItemOffsetList follows: EmbeddedDriverCount + PayloadItemCount uint64_t offsets. */
typedef struct __attribute__((__packed__)) {
    uint32_t Version;
    uint16_t EmbeddedDriverCount;
    uint16_t PayloadItemCount;
} EFI_FIRMWARE_MANAGEMENT_CAPSULE_HEADER;

typedef struct __attribute__((__packed__)) {
    uint32_t Version;
    EFI_GUID UpdateImageTypeId;
    uint8_t UpdateImageIndex;
    uint8_t reserved_bytes[3];
    uint32_t UpdateImageSize;
    uint32_t UpdateVendorCodeSize;
    uint64_t UpdateHardwareInstance;
    uint64_t ImageCapsuleSupport;
} EFI_FIRMWARE_MANAGEMENT_CAPSULE_IMAGE_HEADER;

#define EFI_CAPSULE_SUPPORT_AUTHENTICATION 0x0000000000000001
#define EFI_CAPSULE_SUPPORT_DEPENDENCY 0x0000000000000002

#define EFI_SYSTEM_RESOURCE_TABLE_GUID \
    {0xb122a263, 0x3661, 0x4f68, {0x99, 0x29, 0x78, 0xf8, 0xb0, 0xd6, 0x21, 0x80}}

/* FwResourceCount EFI_SYSTEM_RESOURCE_ENTRY structures (Entries) follow. */
typedef struct {
    uint32_t FwResourceCount;
    uint32_t FwResourceCountMax;
    uint64_t FwResourceVersion;
} EFI_SYSTEM_RESOURCE_TABLE;

#define EFI_SYSTEM_RESOURCE_TABLE_FIRMWARE_RESOURCE_VERSION 1

typedef struct {
    EFI_GUID FwClass;
    uint32_t FwType;
    uint32_t FwVersion;
    uint32_t LowestSupportedFwVersion;
    uint32_t CapsuleFlags;
    uint32_t LastAttemptVersion;
    uint32_t LastAttemptStatus;
} EFI_SYSTEM_RESOURCE_ENTRY;

#define EFI_ESRT_FW_TYPE_UNKNOWN 0x00000000
#define EFI_ESRT_FW_TYPE_SYSTEMFIRMWARE 0x00000001
#define EFI_ESRT_FW_TYPE_DEVICEFIRMWARE 0x00000002
#define EFI_ESRT_FW_TYPE_UEFIDRIVER 0x00000003

#define EFI_LAST_ATTEMPT_STATUS_SUCCESS 0x00000000
#define EFI_LAST_ATTEMPT_STATUS_ERROR_UNSUCCESSFUL 0x00000001
#define EFI_LAST_ATTEMPT_STATUS_ERROR_INSUFFICIENT_RESOURCES 0x00000002
#define EFI_LAST_ATTEMPT_STATUS_ERROR_INCORRECT_VERSION 0x00000003
#define EFI_LAST_ATTEMPT_STATUS_ERROR_INVALID_FORMAT 0x00000004
#define EFI_LAST_ATTEMPT_STATUS_ERROR_AUTH_ERROR 0x00000005
#define EFI_LAST_ATTEMPT_STATUS_ERROR_PWR_EVT_AC 0x00000006
#define EFI_LAST_ATTEMPT_STATUS_ERROR_PWR_EVT_BATT 0x00000007
#define EFI_LAST_ATTEMPT_STATUS_ERROR_UNSATISFIED_DEPENDENCIES 0x00000008

#define EFI_LAST_ATTEMPT_STATUS_ERROR_UNSUCCESSFUL_VENDOR_RANGE_MIN 0x00001000
#define EFI_LAST_ATTEMPT_STATUS_ERROR_UNSUCCESSFUL_VENDOR_RANGE_MAX 0x00004000

#define EFI_JSON_CAPSULE_ID_GUID \
    {0x67d6f4cd, 0xd6b8, 0x4573, {0xbf, 0x4a, 0xde, 0x5e, 0x25, 0x2d, 0x61, 0xae}}

/*
 * __extension__: flexible array members are standard C but an extension in C++, and an array of
 * structures ending in one (ConfigDataList) is an extension in C as well.
 */
__extension__ typedef struct __attribute__((__packed__)) {
    uint32_t Version;
    uint32_t CapsuleId;
    uint32_t PayloadLength;
    uint8_t Payload[];
} EFI_JSON_CAPSULE_HEADER;

__extension__ typedef struct {
    uint32_t ConfigDataLength;
    uint8_t ConfigData[];
} EFI_JSON_CONFIG_DATA_ITEM;

__extension__ typedef struct __attribute__((__packed__)) {
    uint32_t Version;
    uint32_t TotalLength;
    EFI_JSON_CONFIG_DATA_ITEM ConfigDataList[];
} EFI_JSON_CAPSULE_CONFIG_DATA;

#ifdef __cplusplus
}
#endif

#endif
