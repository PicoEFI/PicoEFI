#ifndef EFI_EFIVLANEAP_H_
#define EFI_EFIVLANEAP_H_

#include "efidef.h"
#include "efierr.h"
#include "efidevp.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_VLAN_CONFIG_PROTOCOL_GUID \
    {0x9e23d768, 0xd2f3, 0x4366, {0x9f, 0xc3, 0x3a, 0x7a, 0xba, 0x86, 0x43, 0x74}}

typedef struct _EFI_VLAN_CONFIG_PROTOCOL EFI_VLAN_CONFIG_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_VLAN_CONFIG_SET)(
    EFI_IN EFI_VLAN_CONFIG_PROTOCOL *This,
    EFI_IN EFI_UINT16 VlanId,
    EFI_IN EFI_UINT8 Priority
);

typedef struct {
    EFI_UINT16 VlanId;
    EFI_UINT8 Priority;
} EFI_VLAN_FIND_DATA;

typedef EFI_STATUS (EFI_API *EFI_VLAN_CONFIG_FIND)(
    EFI_IN EFI_VLAN_CONFIG_PROTOCOL *This,
    EFI_IN EFI_UINT16 *VlanId EFI_OPTIONAL,
    EFI_OUT EFI_UINT16 *NumberOfVlan,
    EFI_OUT EFI_VLAN_FIND_DATA **Entries
);

typedef EFI_STATUS (EFI_API *EFI_VLAN_CONFIG_REMOVE)(
    EFI_IN EFI_VLAN_CONFIG_PROTOCOL *This,
    EFI_IN EFI_UINT16 VlanId
);

struct _EFI_VLAN_CONFIG_PROTOCOL {
    EFI_VLAN_CONFIG_SET Set;
    EFI_VLAN_CONFIG_FIND Find;
    EFI_VLAN_CONFIG_REMOVE Remove;
};

#define EFI_EAP_PROTOCOL_GUID \
    {0x5d9f96db, 0xe731, 0x4caa, {0xa0, 0x0d, 0x72, 0xe1, 0x87, 0xcd, 0x77, 0x62}}

typedef struct _EFI_EAP_PROTOCOL EFI_EAP_PROTOCOL;

typedef EFI_VOID *EFI_PORT_HANDLE;

#define EFI_EAP_TYPE_TLS 13

typedef EFI_STATUS (EFI_API *EFI_EAP_SET_DESIRED_AUTHENTICATION_METHOD)(
    EFI_IN struct _EFI_EAP_PROTOCOL *This,
    EFI_IN EFI_UINT8 EapAuthType
);

typedef EFI_STATUS (EFI_API *EFI_EAP_BUILD_RESPONSE_PACKET)(
    EFI_IN EFI_PORT_HANDLE PortNumber,
    EFI_IN EFI_UINT8 *RequestBuffer,
    EFI_IN EFI_UINTN RequestSize,
    EFI_IN EFI_UINT8 *Buffer,
    EFI_IN EFI_OUT EFI_UINTN *BufferSize
);

typedef EFI_STATUS (EFI_API *EFI_EAP_REGISTER_AUTHENTICATION_METHOD)(
    EFI_IN struct _EFI_EAP_PROTOCOL *This,
    EFI_IN EFI_UINT8 EapAuthType,
    EFI_IN EFI_EAP_BUILD_RESPONSE_PACKET Handler
);

struct _EFI_EAP_PROTOCOL {
    EFI_EAP_SET_DESIRED_AUTHENTICATION_METHOD SetDesiredAuthMethod;
    EFI_EAP_REGISTER_AUTHENTICATION_METHOD RegisterAuthMethod;
};

#define EFI_EAP_MANAGEMENT_PROTOCOL_GUID \
    {0xbb62e663, 0x625d, 0x40b2, {0xa0, 0x88, 0xbb, 0xe8, 0x36, 0x23, 0xa2, 0x45}}

typedef struct _EFI_EAP_MANAGEMENT_PROTOCOL EFI_EAP_MANAGEMENT_PROTOCOL;

#define EFI_PAE_SUPPORT_AUTHENTICATOR 0x01
#define EFI_PAE_SUPPORT_SUPPLICANT 0x02

typedef struct _EFI_EAPOL_PORT_INFO {
    EFI_PORT_HANDLE PortNumber;
    EFI_UINT8 ProtocolVersion;
    EFI_UINT8 PaeCapabilities;
} EFI_EAPOL_PORT_INFO;

typedef EFI_STATUS (EFI_API *EFI_EAP_GET_SYSTEM_CONFIGURATION)(
    EFI_IN struct _EFI_EAP_MANAGEMENT_PROTOCOL *This,
    EFI_OUT EFI_BOOLEAN *SystemAuthControl,
    EFI_OUT EFI_EAPOL_PORT_INFO *PortInfo EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_EAP_SET_SYSTEM_CONFIGURATION)(
    EFI_IN struct _EFI_EAP_MANAGEMENT_PROTOCOL *This,
    EFI_IN EFI_BOOLEAN SystemAuthControl
);

typedef EFI_STATUS (EFI_API *EFI_EAP_INITIALIZE_PORT)(
    EFI_IN struct _EFI_EAP_MANAGEMENT_PROTOCOL *This
);

typedef EFI_STATUS (EFI_API *EFI_EAP_USER_LOGON)(EFI_IN struct _EFI_EAP_MANAGEMENT_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_EAP_USER_LOGOFF)(EFI_IN struct _EFI_EAP_MANAGEMENT_PROTOCOL *This);

typedef enum _EFI_EAPOL_SUPPLICANT_PAE_STATE {
    EfiLogoff,
    EfiDisconnected,
    EfiConnecting,
    EfiAcquired,
    EfiAuthenticating,
    EfiHeld,
    EfiAuthenticated,
    EfiMaxSupplicantPaeState
} EFI_EAPOL_SUPPLICANT_PAE_STATE;

#define EFI_AUTH_PERIOD_FIELD_VALID 0x01
#define EFI_HELD_PERIOD_FIELD_VALID 0x02
#define EFI_START_PERIOD_FIELD_VALID 0x04
#define EFI_MAX_START_FIELD_VALID 0x08

typedef struct _EFI_EAPOL_SUPPLICANT_PAE_CONFIGURATION {
    EFI_UINT8 ValidFieldMask;
    EFI_UINTN AuthPeriod;
    EFI_UINTN HeldPeriod;
    EFI_UINTN StartPeriod;
    EFI_UINTN MaxStart;
} EFI_EAPOL_SUPPLICANT_PAE_CONFIGURATION;

typedef EFI_STATUS (EFI_API *EFI_EAP_GET_SUPPLICANT_STATUS)(
    EFI_IN struct _EFI_EAP_MANAGEMENT_PROTOCOL *This,
    EFI_OUT EFI_EAPOL_SUPPLICANT_PAE_STATE *CurrentState,
    EFI_IN EFI_OUT EFI_EAPOL_SUPPLICANT_PAE_CONFIGURATION *Configuration EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_EAP_SET_SUPPLICANT_CONFIGURATION)(
    EFI_IN struct _EFI_EAP_MANAGEMENT_PROTOCOL *This,
    EFI_IN EFI_EAPOL_SUPPLICANT_PAE_CONFIGURATION *Configuration
);

typedef struct _EFI_EAPOL_SUPPLICANT_PAE_STATISTICS {
    EFI_UINTN EapolFramesReceived;
    EFI_UINTN EapolFramesTransmitted;
    EFI_UINTN EapolStartFramesTransmitted;
    EFI_UINTN EapolLogoffFramesTransmitted;
    EFI_UINTN EapRespIdFramesTransmitted;
    EFI_UINTN EapResponseFramesTransmitted;
    EFI_UINTN EapReqIdFramesReceived;
    EFI_UINTN EapRequestFramesReceived;
    EFI_UINTN InvalidEapolFramesReceived;
    EFI_UINTN EapLengthErrorFramesReceived;
    EFI_UINTN LastEapolFrameVersion;
    EFI_UINTN LastEapolFrameSource;
} EFI_EAPOL_SUPPLICANT_PAE_STATISTICS;

typedef EFI_STATUS (EFI_API *EFI_EAP_GET_SUPPLICANT_STATISTICS)(
    EFI_IN struct _EFI_EAP_MANAGEMENT_PROTOCOL *This,
    EFI_OUT EFI_EAPOL_SUPPLICANT_PAE_STATISTICS *Statistics
);

struct _EFI_EAP_MANAGEMENT_PROTOCOL {
    EFI_EAP_GET_SYSTEM_CONFIGURATION GetSystemConfiguration;
    EFI_EAP_SET_SYSTEM_CONFIGURATION SetSystemConfiguration;
    EFI_EAP_INITIALIZE_PORT InitializePort;
    EFI_EAP_USER_LOGON UserLogon;
    EFI_EAP_USER_LOGOFF UserLogoff;
    EFI_EAP_GET_SUPPLICANT_STATUS GetSupplicantStatus;
    EFI_EAP_SET_SUPPLICANT_CONFIGURATION SetSupplicantConfiguration;
    EFI_EAP_GET_SUPPLICANT_STATISTICS GetSupplicantStatistics;
};

#define EFI_EAP_MANAGEMENT2_PROTOCOL_GUID \
    {0x5e93c847, 0x456d, 0x40b3, {0xa6, 0xb4, 0x78, 0xb0, 0xc9, 0xcf, 0x7f, 0x20}}

typedef struct _EFI_EAP_MANAGEMENT2_PROTOCOL EFI_EAP_MANAGEMENT2_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_EAP_GET_KEY)(
    EFI_IN EFI_EAP_MANAGEMENT2_PROTOCOL *This,
    EFI_IN EFI_OUT EFI_UINT8 *Msk,
    EFI_IN EFI_OUT EFI_UINTN *MskSize,
    EFI_IN EFI_OUT EFI_UINT8 *Emsk,
    EFI_IN EFI_OUT EFI_UINT8 *EmskSize
);

/* The specification prints the members before GetKey as "Same as EFI_EAP_MANAGEMENT_PROTOCOL". */
struct _EFI_EAP_MANAGEMENT2_PROTOCOL {
    EFI_EAP_GET_SYSTEM_CONFIGURATION GetSystemConfiguration;
    EFI_EAP_SET_SYSTEM_CONFIGURATION SetSystemConfiguration;
    EFI_EAP_INITIALIZE_PORT InitializePort;
    EFI_EAP_USER_LOGON UserLogon;
    EFI_EAP_USER_LOGOFF UserLogoff;
    EFI_EAP_GET_SUPPLICANT_STATUS GetSupplicantStatus;
    EFI_EAP_SET_SUPPLICANT_CONFIGURATION SetSupplicantConfiguration;
    EFI_EAP_GET_SUPPLICANT_STATISTICS GetSupplicantStatistics;
    EFI_EAP_GET_KEY GetKey;
};

#define EFI_EAP_CONFIGURATION_PROTOCOL_GUID \
    {0xe5b58dbb, 0x7688, 0x44b4, {0x97, 0xbf, 0x5f, 0x1d, 0x4b, 0x7c, 0xc8, 0xdb}}

typedef struct _EFI_EAP_CONFIGURATION_PROTOCOL EFI_EAP_CONFIGURATION_PROTOCOL;

typedef enum {
    EfiEapConfigEapAuthMethod,
    EfiEapConfigEapSupportedAuthMethod,
    EfiEapConfigIdentityString,
    EfiEapConfigEapTlsCACert,
    EfiEapConfigEapTlsClientCert,
    EfiEapConfigEapTlsClientPrivateKeyFile,
    EfiEapConfigEapTlsClientPrivateKeyFilePassword,
    EfiEapConfigEapTlsCipherSuite,
    EfiEapConfigEapTlsSupportedCipherSuite,
    EfiEapConfigEapMSChapV2Password,
    EfiEapConfigEap2ndAuthMethod
} EFI_EAP_CONFIG_DATA_TYPE;

typedef EFI_UINT8 EFI_EAP_TYPE;

#define EFI_EAP_TYPE_ATTRIBUTE 0
#define EFI_EAP_TYPE_IDENTITY 1
#define EFI_EAP_TYPE_NOTIFICATION 2
#define EFI_EAP_TYPE_NAK 3
#define EFI_EAP_TYPE_MD5CHALLENGE 4
#define EFI_EAP_TYPE_OTP 5
#define EFI_EAP_TYPE_GTC 6
#define EFI_EAP_TYPE_EAPTLS 13
#define EFI_EAP_TYPE_EAPSIM 18
#define EFI_EAP_TYPE_TTLS 21
#define EFI_EAP_TYPE_PEAP 25
#define EFI_EAP_TYPE_MSCHAPV2 26
#define EFI_EAP_TYPE_EAP_EXTENSION 33

typedef EFI_STATUS (EFI_API *EFI_EAP_CONFIGURATION_SET_DATA)(
    EFI_IN EFI_EAP_CONFIGURATION_PROTOCOL *This,
    EFI_IN EFI_EAP_TYPE EapType,
    EFI_IN EFI_EAP_CONFIG_DATA_TYPE DataType,
    EFI_IN EFI_VOID *Data,
    EFI_IN EFI_UINTN DataSize
);

typedef EFI_STATUS (EFI_API *EFI_EAP_CONFIGURATION_GET_DATA)(
    EFI_IN EFI_EAP_CONFIGURATION_PROTOCOL *This,
    EFI_IN EFI_EAP_TYPE EapType,
    EFI_IN EFI_EAP_CONFIG_DATA_TYPE DataType,
    EFI_IN EFI_OUT EFI_VOID *Data,
    EFI_IN EFI_OUT EFI_UINTN *DataSize
);

struct _EFI_EAP_CONFIGURATION_PROTOCOL {
    EFI_EAP_CONFIGURATION_SET_DATA SetData;
    EFI_EAP_CONFIGURATION_GET_DATA GetData;
};

#define EFI_WIRELESS_MAC_CONNECTION_PROTOCOL_GUID \
    {0xda55bc9, 0x45f8, 0x4bb4, {0x87, 0x19, 0x52, 0x24, 0xf1, 0x8a, 0x4d, 0x45}}

typedef struct _EFI_WIRELESS_MAC_CONNECTION_PROTOCOL EFI_WIRELESS_MAC_CONNECTION_PROTOCOL;

typedef enum {
    EfiIeeeInfrastructureBSS,
    EfiIeeeIndependentBSS,
    EfiIeeeMeshBSS,
    EfiIeeeAnyBss
} EFI_80211_BSS_TYPE;

typedef struct {
    EFI_UINT8 Addr[6];
} EFI_80211_MAC_ADDRESS;

typedef struct {
    EFI_UINT8 ElementID;
    EFI_UINT8 Length;
} EFI_80211_ELEMENT_HEADER;

typedef struct {
    EFI_80211_ELEMENT_HEADER Hdr;
    EFI_UINT8 RequestIDs[1];
} EFI_80211_ELEMENT_REQ;

typedef struct {
    EFI_80211_ELEMENT_HEADER Hdr;
    EFI_UINT8 SSId[32];
} EFI_80211_ELEMENT_SSID;

typedef enum {
    EfiIeeePrivate = 0,
    EfiIeeePrivatewithGuest = 1,
    EfiIeeeChargeablePublic = 2,
    EfiIeeeFreePublic = 3,
    EfiIeeePersonal = 4,
    EfiIeeeEmergencyServOnly = 5,
    EfiIeeeTestOrExp = 14,
    EfiIeeeWildcard = 15
} EFI_80211_ACC_NET_TYPE;

typedef struct {
    EFI_80211_BSS_TYPE BSSType;
    EFI_80211_MAC_ADDRESS BSSId;
    EFI_UINT8 SSIdLen;
    EFI_UINT8 *SSId;
    EFI_BOOLEAN PassiveMode;
    EFI_UINT32 ProbeDelay;
    EFI_UINT32 *ChannelList;
    EFI_UINT32 MinChannelTime;
    EFI_UINT32 MaxChannelTime;
    EFI_80211_ELEMENT_REQ *RequestInformation;
    EFI_80211_ELEMENT_SSID *SSIDList;
    EFI_80211_ACC_NET_TYPE AccessNetworkType;
    EFI_UINT8 *VendorSpecificInfo;
} EFI_80211_SCAN_DATA;

typedef enum {
    EfiScanSuccess,
    EfiScanNotSupported
} EFI_80211_SCAN_RESULT_CODE;

typedef struct {
    EFI_UINT8 FirstChannelNum;
    EFI_UINT8 NumOfChannels;
    EFI_UINT8 MaxTxPowerLevel;
} EFI_80211_COUNTRY_TRIPLET_SUBBAND;

typedef struct {
    EFI_UINT8 OperatingExtId;
    EFI_UINT8 OperatingClass;
    EFI_UINT8 CoverageClass;
} EFI_80211_COUNTRY_TRIPLET_OPERATE;

typedef union {
    EFI_80211_COUNTRY_TRIPLET_SUBBAND Subband;
    EFI_80211_COUNTRY_TRIPLET_OPERATE Operating;
} EFI_80211_COUNTRY_TRIPLET;

typedef struct {
    EFI_80211_ELEMENT_HEADER Hdr;
    EFI_UINT8 CountryStr[3];
    EFI_80211_COUNTRY_TRIPLET CountryTriplet[1];
} EFI_80211_ELEMENT_COUNTRY;

/* The rest of the RSN element (suite lists, capabilities, PMKIDs) follows; it varies in length. */
typedef struct {
    EFI_UINT16 Version;
    EFI_UINT32 GroupDataCipherSuite;
} EFI_80211_ELEMENT_DATA_RSN;

typedef struct {
    EFI_80211_ELEMENT_HEADER Hdr;
    EFI_80211_ELEMENT_DATA_RSN *Data;
} EFI_80211_ELEMENT_RSN;

typedef struct {
    EFI_80211_ELEMENT_HEADER Hdr;
    EFI_UINT8 Capabilities[1];
} EFI_80211_ELEMENT_EXT_CAP;

/* BSSId is a value, as in every other structure here; printed with a stray asterisk. */
typedef struct {
    EFI_80211_MAC_ADDRESS BSSId;
    EFI_UINT8 *SSId;
    EFI_UINT8 SSIdLen;
    EFI_80211_BSS_TYPE BSSType;
    EFI_UINT16 BeaconPeriod;
    EFI_UINT64 Timestamp;
    EFI_UINT16 CapabilityInfo;
    EFI_UINT8 *BSSBasicRateSet;
    EFI_UINT8 *OperationalRateSet;
    EFI_80211_ELEMENT_COUNTRY *Country;
    EFI_80211_ELEMENT_RSN RSN;
    EFI_UINT8 RSSI;
    EFI_UINT8 RCPIMeasurement;
    EFI_UINT8 RSNIMeasurement;
    EFI_UINT8 *RequestedElements;
    EFI_UINT8 *BSSMembershipSelectorSet;
    EFI_80211_ELEMENT_EXT_CAP *ExtCapElement;
} EFI_80211_BSS_DESCRIPTION;

typedef struct {
    EFI_UINT8 SubElementID;
    EFI_UINT8 Length;
    EFI_UINT8 Data[1];
} EFI_80211_SUBELEMENT_INFO;

typedef struct {
    EFI_80211_ELEMENT_HEADER Hdr;
    EFI_UINT8 Indicator;
    EFI_80211_SUBELEMENT_INFO SubElement[1];
} EFI_80211_MULTIPLE_BSSID;

typedef struct {
    EFI_80211_MAC_ADDRESS BSSId;
    EFI_80211_BSS_TYPE BSSType;
    EFI_UINT8 ConCapInfo;
    EFI_UINT8 ConCountryStr[2];
    EFI_UINT8 OperatingClass;
    EFI_UINT8 Channel;
    EFI_UINT8 Interval;
    EFI_80211_MULTIPLE_BSSID *MultipleBSSID;
    EFI_UINT8 RCPIMeasurement;
    EFI_UINT8 RSNIMeasurement;
} EFI_80211_BSS_DESP_PILOT;

typedef struct {
    EFI_UINTN NumOfBSSDesp;
    EFI_80211_BSS_DESCRIPTION **BSSDespSet;
    EFI_UINTN NumOfBSSDespFromPilot;
    EFI_80211_BSS_DESP_PILOT **BSSDespFromPilotSet;
    EFI_UINT8 *VendorSpecificInfo;
} EFI_80211_SCAN_RESULT;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    EFI_80211_SCAN_DATA *Data;
    EFI_80211_SCAN_RESULT_CODE ResultCode;
    EFI_80211_SCAN_RESULT *Result;
} EFI_80211_SCAN_DATA_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_WIRELESS_MAC_CONNECTION_SCAN)(
    EFI_IN EFI_WIRELESS_MAC_CONNECTION_PROTOCOL *This,
    EFI_IN EFI_80211_SCAN_DATA_TOKEN *Data
);

typedef struct {
    EFI_UINT8 FirstChannelNumber;
    EFI_UINT8 NumberOfChannels;
} EFI_80211_ELEMENT_SUPP_CHANNEL_TUPLE;

typedef struct {
    EFI_80211_ELEMENT_HEADER Hdr;
    EFI_80211_ELEMENT_SUPP_CHANNEL_TUPLE Subband[1];
} EFI_80211_ELEMENT_SUPP_CHANNEL;

/* ExtCapElement is a pointer: the description allows NULL (printed by value). */
typedef struct {
    EFI_80211_MAC_ADDRESS BSSId;
    EFI_UINT16 CapabilityInfo;
    EFI_UINT32 FailureTimeout;
    EFI_UINT32 ListenInterval;
    EFI_80211_ELEMENT_SUPP_CHANNEL *Channels;
    EFI_80211_ELEMENT_RSN RSN;
    EFI_80211_ELEMENT_EXT_CAP *ExtCapElement;
    EFI_UINT8 *VendorSpecificInfo;
} EFI_80211_ASSOCIATE_DATA;

typedef enum {
    EfiAssociateSuccess,
    EfiAssociateRefusedReasonUnspecified,
    EfiAssociateRefusedCapsMismatch,
    EfiAssociateRefusedExtReason,
    EfiAssociateRefusedAPOutOfMemory,
    EfiAssociateRefusedBasicRatesMismatch,
    EfiAssociateRejectedEmergencyServicesNotSupported,
    EfiAssociateRefusedTemporarily
} EFI_80211_ASSOCIATE_RESULT_CODE;

typedef struct {
    EFI_80211_ELEMENT_HEADER Hdr;
    EFI_UINT8 Type;
    EFI_UINT32 Value;
} EFI_80211_ELEMENT_TIMEOUT_VAL;

typedef struct {
    EFI_80211_MAC_ADDRESS BSSId;
    EFI_UINT16 CapabilityInfo;
    EFI_UINT16 AssociationID;
    EFI_UINT8 RCPIValue;
    EFI_UINT8 RSNIValue;
    EFI_80211_ELEMENT_EXT_CAP *ExtCapElement;
    EFI_80211_ELEMENT_TIMEOUT_VAL TimeoutInterval;
    EFI_UINT8 *VendorSpecificInfo;
} EFI_80211_ASSOCIATE_RESULT;

/* Data and Result are pointers, as described (printed by value). */
typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    EFI_80211_ASSOCIATE_DATA *Data;
    EFI_80211_ASSOCIATE_RESULT_CODE ResultCode;
    EFI_80211_ASSOCIATE_RESULT *Result;
} EFI_80211_ASSOCIATE_DATA_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_WIRELESS_MAC_CONNECTION_ASSOCIATE)(
    EFI_IN EFI_WIRELESS_MAC_CONNECTION_PROTOCOL *This,
    EFI_IN EFI_80211_ASSOCIATE_DATA_TOKEN *Data
);

typedef enum {
    EfiIeee80211UnspecifiedReason = 1,
    EfiIeee80211PreviousAuthenticateInvalid = 2,
    EfiIeee80211DeauthenticatedSinceLeaving = 3,
    EfiIeee80211DisassociatedDueToInactive = 4,
    EfiIeee80211DisassociatedSinceApUnable = 5,
    EfiIeee80211Class2FrameNonauthenticated = 6,
    EfiIeee80211Class3FrameNonassociated = 7,
    EfiIeee80211DisassociatedSinceLeaving = 8
} EFI_80211_REASON_CODE;

typedef struct {
    EFI_80211_MAC_ADDRESS BSSId;
    EFI_80211_REASON_CODE ReasonCode;
    EFI_UINT8 *VendorSpecificInfo;
} EFI_80211_DISASSOCIATE_DATA;

typedef enum {
    EfiDisassociateSuccess,
    EfiDisassociateInvalidParameters
} EFI_80211_DISASSOCIATE_RESULT_CODE;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    EFI_80211_DISASSOCIATE_DATA *Data;
    EFI_80211_DISASSOCIATE_RESULT_CODE ResultCode;
} EFI_80211_DISASSOCIATE_DATA_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_WIRELESS_MAC_CONNECTION_DISASSOCIATE)(
    EFI_IN EFI_WIRELESS_MAC_CONNECTION_PROTOCOL *This,
    EFI_IN EFI_80211_DISASSOCIATE_DATA_TOKEN *Data
);

typedef enum {
    EfiOpenSystem,
    EfiSharedKey,
    EfiFastBSSTransition,
    EFI_SAE
} EFI_80211_AUTHENTICATION_TYPE;

typedef struct {
    EFI_80211_MAC_ADDRESS BSSId;
    EFI_80211_AUTHENTICATION_TYPE AuthType;
    EFI_UINT32 FailureTimeout;
    EFI_UINT8 *FTContent;
    EFI_UINT8 *SAEContent;
    EFI_UINT8 *VendorSpecificInfo;
} EFI_80211_AUTHENTICATE_DATA;

typedef enum {
    EfiAuthenticateSuccess,
    EfiAuthenticateRefused,
    EfiAuthenticateAnticLoggingTokenRequired,
    EfiAuthenticateFiniteCyclicGroupNotSupported,
    EfiAuthenticationRejected,
    EfiAuthenticateInvalidParameter
} EFI_80211_AUTHENTICATE_RESULT_CODE;

typedef struct {
    EFI_80211_MAC_ADDRESS BSSId;
    EFI_UINT8 *FTContent;
    EFI_UINT8 *SAEContent;
    EFI_UINT8 *VendorSpecificInfo;
} EFI_80211_AUTHENTICATE_RESULT;

/* Result is a pointer to a buffer the caller frees, as described (printed by value). */
typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    EFI_80211_AUTHENTICATE_DATA *Data;
    EFI_80211_AUTHENTICATE_RESULT_CODE ResultCode;
    EFI_80211_AUTHENTICATE_RESULT *Result;
} EFI_80211_AUTHENTICATE_DATA_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_WIRELESS_MAC_CONNECTION_AUTHENTICATE)(
    EFI_IN EFI_WIRELESS_MAC_CONNECTION_PROTOCOL *This,
    EFI_IN EFI_80211_AUTHENTICATE_DATA_TOKEN *Data
);

typedef struct {
    EFI_80211_MAC_ADDRESS BSSId;
    EFI_80211_REASON_CODE ReasonCode;
    EFI_UINT8 *VendorSpecificInfo;
} EFI_80211_DEAUTHENTICATE_DATA;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    EFI_80211_DEAUTHENTICATE_DATA *Data;
} EFI_80211_DEAUTHENTICATE_DATA_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_WIRELESS_MAC_CONNECTION_DEAUTHENTICATE)(
    EFI_IN EFI_WIRELESS_MAC_CONNECTION_PROTOCOL *This,
    EFI_IN EFI_80211_DEAUTHENTICATE_DATA_TOKEN *Data
);

struct _EFI_WIRELESS_MAC_CONNECTION_PROTOCOL {
    EFI_WIRELESS_MAC_CONNECTION_SCAN Scan;
    EFI_WIRELESS_MAC_CONNECTION_ASSOCIATE Associate;
    EFI_WIRELESS_MAC_CONNECTION_DISASSOCIATE Disassociate;
    EFI_WIRELESS_MAC_CONNECTION_AUTHENTICATE Authenticate;
    EFI_WIRELESS_MAC_CONNECTION_DEAUTHENTICATE Deauthenticate;
};

#define EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL_GUID \
    {0x1b0fb9bf, 0x699d, 0x4fdd, {0xa7, 0xc3, 0x25, 0x46, 0x68, 0x1b, 0xf6, 0x3b}}

typedef struct _EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL;

#define EFI_MAX_SSID_LEN 32

typedef struct {
    EFI_UINT8 SSIdLen;
    EFI_UINT8 SSId[EFI_MAX_SSID_LEN];
} EFI_80211_SSID;

typedef struct {
    EFI_UINT32 NumOfSSID;
    EFI_80211_SSID SSIDList[1];
} EFI_80211_GET_NETWORKS_DATA;

typedef struct {
    EFI_UINT8 Oui[3];
    EFI_UINT8 SuiteType;
} EFI_80211_SUITE_SELECTOR;

typedef struct {
    EFI_UINT16 AKMSuiteCount;
    EFI_80211_SUITE_SELECTOR AKMSuiteList[1];
} EFI_80211_AKM_SUITE_SELECTOR;

typedef struct {
    EFI_UINT16 CipherSuiteCount;
    EFI_80211_SUITE_SELECTOR CipherSuiteList[1];
} EFI_80211_CIPHER_SUITE_SELECTOR;

typedef struct {
    EFI_80211_BSS_TYPE BSSType;
    EFI_80211_SSID SSId;
    EFI_80211_AKM_SUITE_SELECTOR *AKMSuite;
    EFI_80211_CIPHER_SUITE_SELECTOR *CipherSuite;
} EFI_80211_NETWORK;

typedef struct {
    EFI_80211_NETWORK Network;
    EFI_UINT8 NetworkQuality;
} EFI_80211_NETWORK_DESCRIPTION;

typedef struct {
    EFI_UINT8 NumOfNetworkDesc;
    EFI_80211_NETWORK_DESCRIPTION NetworkDesc[1];
} EFI_80211_GET_NETWORKS_RESULT;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    EFI_80211_GET_NETWORKS_DATA *Data;
    EFI_80211_GET_NETWORKS_RESULT *Result;
} EFI_80211_GET_NETWORKS_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_WIRELESS_MAC_CONNECTION_II_GET_NETWORKS)(
    EFI_IN EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL *This,
    EFI_IN EFI_80211_GET_NETWORKS_TOKEN *Token
);

typedef struct {
    EFI_80211_NETWORK *Network;
    EFI_UINT32 FailureTimeout;
} EFI_80211_CONNECT_NETWORK_DATA;

typedef enum {
    EfiConnectSuccess,
    EfiConnectRefused,
    EfiConnectFailed,
    EfiConnectFailureTimeout,
    EfiConnectFailedReasonUnspecified
} EFI_80211_CONNECT_NETWORK_RESULT_CODE;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    EFI_80211_CONNECT_NETWORK_DATA *Data;
    EFI_80211_CONNECT_NETWORK_RESULT_CODE ResultCode;
} EFI_80211_CONNECT_NETWORK_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_WIRELESS_MAC_CONNECTION_II_CONNECT_NETWORK)(
    EFI_IN EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL *This,
    EFI_IN EFI_80211_CONNECT_NETWORK_TOKEN *Token
);

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
} EFI_80211_DISCONNECT_NETWORK_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_WIRELESS_MAC_CONNECTION_II_DISCONNECT_NETWORK)(
    EFI_IN EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL *This,
    EFI_IN EFI_80211_DISCONNECT_NETWORK_TOKEN *Token
);

struct _EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL {
    EFI_WIRELESS_MAC_CONNECTION_II_GET_NETWORKS GetNetworks;
    EFI_WIRELESS_MAC_CONNECTION_II_CONNECT_NETWORK ConnectNetwork;
    EFI_WIRELESS_MAC_CONNECTION_II_DISCONNECT_NETWORK DisconnectNetwork;
};

#define EFI_SUPPLICANT_SERVICE_BINDING_PROTOCOL_GUID \
    {0x45bcd98e, 0x59ad, 0x4174, {0x95, 0x46, 0x34, 0x4a, 0x7, 0x48, 0x58, 0x98}}

#define EFI_SUPPLICANT_PROTOCOL_GUID \
    {0x54fcc43e, 0xaa89, 0x4333, {0x9a, 0x85, 0xcd, 0xea, 0x24, 0x5, 0x1e, 0x9e}}

typedef struct _EFI_SUPPLICANT_PROTOCOL EFI_SUPPLICANT_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_SUPPLICANT_BUILD_RESPONSE_PACKET)(
    EFI_IN EFI_SUPPLICANT_PROTOCOL *This,
    EFI_IN EFI_UINT8 *RequestBuffer EFI_OPTIONAL,
    EFI_IN EFI_UINTN RequestBufferSize EFI_OPTIONAL,
    EFI_OUT EFI_UINT8 *Buffer,
    EFI_IN EFI_OUT EFI_UINTN *BufferSize
);

typedef struct {
    EFI_UINT32 FragmentLength;
    EFI_VOID *FragmentBuffer;
} EFI_SUPPLICANT_FRAGMENT_DATA;

typedef enum {
    EfiSupplicantEncrypt,
    EfiSupplicantDecrypt
} EFI_SUPPLICANT_CRYPT_MODE;

typedef EFI_STATUS (EFI_API *EFI_SUPPLICANT_PROCESS_PACKET)(
    EFI_IN EFI_SUPPLICANT_PROTOCOL *This,
    EFI_IN EFI_OUT EFI_SUPPLICANT_FRAGMENT_DATA **FragmentTable,
    EFI_IN EFI_UINT32 *FragmentCount,
    EFI_IN EFI_SUPPLICANT_CRYPT_MODE CryptMode
);

typedef enum {
    EfiSupplicant80211AKMSuite,
    EfiSupplicant80211GroupDataCipherSuite,
    EfiSupplicant80211PairwiseCipherSuite,
    EfiSupplicant80211PskPassword,
    EfiSupplicant80211TargetSSIDName,
    EfiSupplicant80211StationMac,
    EfiSupplicant80211TargetSSIDMac,
    EfiSupplicant80211PTK,
    EfiSupplicant80211GTK,
    EfiSupplicantState,
    EfiSupplicant80211LinkState,
    EfiSupplicantKeyRefresh,
    EfiSupplicant80211SupportedAKMSuites,
    EfiSupplicant80211SupportedSoftwareCipherSuites,
    EfiSupplicant80211SupportedHardwareCipherSuites,
    EfiSupplicant80211IGTK,
    EfiSupplicant80211PMK,
    EfiSupplicantDataTypeMaximum
} EFI_SUPPLICANT_DATA_TYPE;

typedef enum {
    EfiIeee80211UnauthenticatedUnassociated,
    EfiIeee80211AuthenticatedUnassociated,
    EfiIeee80211PendingRSNAuthentication,
    EfiIeee80211AuthenticatedAssociated
} EFI_80211_LINK_STATE;

typedef struct {
    EFI_BOOLEAN GTKRefresh;
} EFI_SUPPLICANT_KEY_REFRESH;

#define EFI_MAX_KEY_LEN 64

typedef enum {
    EfiGroup,
    EfiPairwise,
    EfiPeerKey,
    EFI_IGTK
} EFI_SUPPLICANT_KEY_TYPE;

typedef enum {
    EfiReceive,
    EfiTransmit,
    EfiBoth
} EFI_SUPPLICANT_KEY_DIRECTION;

typedef struct {
    EFI_UINT8 Key[EFI_MAX_KEY_LEN];
    EFI_UINT8 KeyLen;
    EFI_UINT8 KeyId;
    EFI_SUPPLICANT_KEY_TYPE KeyType;
    EFI_80211_MAC_ADDRESS Addr;
    EFI_UINT8 Rsc[8];
    EFI_UINT8 RscLen;
    EFI_BOOLEAN IsAuthenticator;
    EFI_80211_SUITE_SELECTOR CipherSuite;
    EFI_SUPPLICANT_KEY_DIRECTION Direction;
} EFI_SUPPLICANT_KEY;

typedef struct {
    EFI_UINT8 GTKCount;
    EFI_SUPPLICANT_KEY GTKList[1];
} EFI_SUPPLICANT_GTK_LIST;

typedef EFI_STATUS (EFI_API *EFI_SUPPLICANT_SET_DATA)(
    EFI_IN EFI_SUPPLICANT_PROTOCOL *This,
    EFI_IN EFI_SUPPLICANT_DATA_TYPE DataType,
    EFI_IN EFI_VOID *Data,
    EFI_IN EFI_UINTN DataSize
);

typedef EFI_STATUS (EFI_API *EFI_SUPPLICANT_GET_DATA)(
    EFI_IN EFI_SUPPLICANT_PROTOCOL *This,
    EFI_IN EFI_SUPPLICANT_DATA_TYPE DataType,
    EFI_OUT EFI_UINT8 *Data EFI_OPTIONAL,
    EFI_IN EFI_OUT EFI_UINTN *DataSize
);

struct _EFI_SUPPLICANT_PROTOCOL {
    EFI_SUPPLICANT_BUILD_RESPONSE_PACKET BuildResponsePacket;
    EFI_SUPPLICANT_PROCESS_PACKET ProcessPacket;
    EFI_SUPPLICANT_SET_DATA SetData;
    EFI_SUPPLICANT_GET_DATA GetData;
};

#ifdef __cplusplus
}
#endif

#endif
