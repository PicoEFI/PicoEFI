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
    EFI_VLAN_CONFIG_PROTOCOL *This,
    uint16_t VlanId,
    uint8_t Priority
);

typedef struct {
    uint16_t VlanId;
    uint8_t Priority;
} EFI_VLAN_FIND_DATA;

typedef EFI_STATUS (EFI_API *EFI_VLAN_CONFIG_FIND)(
    EFI_VLAN_CONFIG_PROTOCOL *This,
    uint16_t *VlanId,
    uint16_t *NumberOfVlan,
    EFI_VLAN_FIND_DATA **Entries
);

typedef EFI_STATUS (EFI_API *EFI_VLAN_CONFIG_REMOVE)(
    EFI_VLAN_CONFIG_PROTOCOL *This,
    uint16_t VlanId
);

struct _EFI_VLAN_CONFIG_PROTOCOL {
    EFI_VLAN_CONFIG_SET Set;
    EFI_VLAN_CONFIG_FIND Find;
    EFI_VLAN_CONFIG_REMOVE Remove;
};

#define EFI_EAP_PROTOCOL_GUID \
    {0x5d9f96db, 0xe731, 0x4caa, {0xa0, 0x0d, 0x72, 0xe1, 0x87, 0xcd, 0x77, 0x62}}

typedef struct _EFI_EAP_PROTOCOL EFI_EAP_PROTOCOL;

typedef void *EFI_PORT_HANDLE;

#define EFI_EAP_TYPE_TLS 13

typedef EFI_STATUS (EFI_API *EFI_EAP_SET_DESIRED_AUTHENTICATION_METHOD)(
    struct _EFI_EAP_PROTOCOL *This,
    uint8_t EapAuthType
);

typedef EFI_STATUS (EFI_API *EFI_EAP_BUILD_RESPONSE_PACKET)(
    EFI_PORT_HANDLE PortNumber,
    uint8_t *RequestBuffer,
    size_t RequestSize,
    uint8_t *Buffer,
    size_t *BufferSize
);

typedef EFI_STATUS (EFI_API *EFI_EAP_REGISTER_AUTHENTICATION_METHOD)(
    struct _EFI_EAP_PROTOCOL *This,
    uint8_t EapAuthType,
    EFI_EAP_BUILD_RESPONSE_PACKET Handler
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
    uint8_t ProtocolVersion;
    uint8_t PaeCapabilities;
} EFI_EAPOL_PORT_INFO;

typedef EFI_STATUS (EFI_API *EFI_EAP_GET_SYSTEM_CONFIGURATION)(
    struct _EFI_EAP_MANAGEMENT_PROTOCOL *This,
    bool *SystemAuthControl,
    EFI_EAPOL_PORT_INFO *PortInfo
);

typedef EFI_STATUS (EFI_API *EFI_EAP_SET_SYSTEM_CONFIGURATION)(
    struct _EFI_EAP_MANAGEMENT_PROTOCOL *This,
    bool SystemAuthControl
);

typedef EFI_STATUS (EFI_API *EFI_EAP_INITIALIZE_PORT)(
    struct _EFI_EAP_MANAGEMENT_PROTOCOL *This
);

typedef EFI_STATUS (EFI_API *EFI_EAP_USER_LOGON)(struct _EFI_EAP_MANAGEMENT_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_EAP_USER_LOGOFF)(struct _EFI_EAP_MANAGEMENT_PROTOCOL *This);

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
    uint8_t ValidFieldMask;
    uintptr_t AuthPeriod;
    uintptr_t HeldPeriod;
    uintptr_t StartPeriod;
    size_t MaxStart;
} EFI_EAPOL_SUPPLICANT_PAE_CONFIGURATION;

typedef EFI_STATUS (EFI_API *EFI_EAP_GET_SUPPLICANT_STATUS)(
    struct _EFI_EAP_MANAGEMENT_PROTOCOL *This,
    EFI_EAPOL_SUPPLICANT_PAE_STATE *CurrentState,
    EFI_EAPOL_SUPPLICANT_PAE_CONFIGURATION *Configuration
);

typedef EFI_STATUS (EFI_API *EFI_EAP_SET_SUPPLICANT_CONFIGURATION)(
    struct _EFI_EAP_MANAGEMENT_PROTOCOL *This,
    EFI_EAPOL_SUPPLICANT_PAE_CONFIGURATION *Configuration
);

typedef struct _EFI_EAPOL_SUPPLICANT_PAE_STATISTICS {
    size_t EapolFramesReceived;
    size_t EapolFramesTransmitted;
    size_t EapolStartFramesTransmitted;
    size_t EapolLogoffFramesTransmitted;
    size_t EapRespIdFramesTransmitted;
    size_t EapResponseFramesTransmitted;
    size_t EapReqIdFramesReceived;
    size_t EapRequestFramesReceived;
    size_t InvalidEapolFramesReceived;
    size_t EapLengthErrorFramesReceived;
    uintptr_t LastEapolFrameVersion;
    uintptr_t LastEapolFrameSource;
} EFI_EAPOL_SUPPLICANT_PAE_STATISTICS;

typedef EFI_STATUS (EFI_API *EFI_EAP_GET_SUPPLICANT_STATISTICS)(
    struct _EFI_EAP_MANAGEMENT_PROTOCOL *This,
    EFI_EAPOL_SUPPLICANT_PAE_STATISTICS *Statistics
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
    EFI_EAP_MANAGEMENT2_PROTOCOL *This,
    uint8_t *Msk,
    size_t *MskSize,
    uint8_t *Emsk,
    uint8_t *EmskSize
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

typedef uint8_t EFI_EAP_TYPE;

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
    EFI_EAP_CONFIGURATION_PROTOCOL *This,
    EFI_EAP_TYPE EapType,
    EFI_EAP_CONFIG_DATA_TYPE DataType,
    void *Data,
    size_t DataSize
);

typedef EFI_STATUS (EFI_API *EFI_EAP_CONFIGURATION_GET_DATA)(
    EFI_EAP_CONFIGURATION_PROTOCOL *This,
    EFI_EAP_TYPE EapType,
    EFI_EAP_CONFIG_DATA_TYPE DataType,
    void *Data,
    size_t *DataSize
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
    uint8_t Addr[6];
} EFI_80211_MAC_ADDRESS;

typedef struct {
    uint8_t ElementID;
    uint8_t Length;
} EFI_80211_ELEMENT_HEADER;

typedef struct {
    EFI_80211_ELEMENT_HEADER Hdr;
    uint8_t RequestIDs[1];
} EFI_80211_ELEMENT_REQ;

typedef struct {
    EFI_80211_ELEMENT_HEADER Hdr;
    uint8_t SSId[32];
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
    uint8_t SSIdLen;
    uint8_t *SSId;
    uint8_t PassiveMode;
    uint32_t ProbeDelay;
    uint32_t *ChannelList;
    uint32_t MinChannelTime;
    uint32_t MaxChannelTime;
    EFI_80211_ELEMENT_REQ *RequestInformation;
    EFI_80211_ELEMENT_SSID *SSIDList;
    EFI_80211_ACC_NET_TYPE AccessNetworkType;
    uint8_t *VendorSpecificInfo;
} EFI_80211_SCAN_DATA;

typedef enum {
    EfiScanSuccess,
    EfiScanNotSupported
} EFI_80211_SCAN_RESULT_CODE;

typedef struct {
    uint8_t FirstChannelNum;
    uint8_t NumOfChannels;
    uint8_t MaxTxPowerLevel;
} EFI_80211_COUNTRY_TRIPLET_SUBBAND;

typedef struct {
    uint8_t OperatingExtId;
    uint8_t OperatingClass;
    uint8_t CoverageClass;
} EFI_80211_COUNTRY_TRIPLET_OPERATE;

typedef union {
    EFI_80211_COUNTRY_TRIPLET_SUBBAND Subband;
    EFI_80211_COUNTRY_TRIPLET_OPERATE Operating;
} EFI_80211_COUNTRY_TRIPLET;

typedef struct {
    EFI_80211_ELEMENT_HEADER Hdr;
    uint8_t CountryStr[3];
    EFI_80211_COUNTRY_TRIPLET CountryTriplet[1];
} EFI_80211_ELEMENT_COUNTRY;

/* The rest of the RSN element (suite lists, capabilities, PMKIDs) follows; it varies in length. */
typedef struct {
    uint16_t Version;
    uint32_t GroupDataCipherSuite;
} EFI_80211_ELEMENT_DATA_RSN;

typedef struct {
    EFI_80211_ELEMENT_HEADER Hdr;
    EFI_80211_ELEMENT_DATA_RSN *Data;
} EFI_80211_ELEMENT_RSN;

typedef struct {
    EFI_80211_ELEMENT_HEADER Hdr;
    uint8_t Capabilities[1];
} EFI_80211_ELEMENT_EXT_CAP;

/* BSSId is a value, as in every other structure here; printed with a stray asterisk. */
typedef struct {
    EFI_80211_MAC_ADDRESS BSSId;
    uint8_t *SSId;
    uint8_t SSIdLen;
    EFI_80211_BSS_TYPE BSSType;
    uint16_t BeaconPeriod;
    uint64_t Timestamp;
    uint16_t CapabilityInfo;
    uint8_t *BSSBasicRateSet;
    uint8_t *OperationalRateSet;
    EFI_80211_ELEMENT_COUNTRY *Country;
    EFI_80211_ELEMENT_RSN RSN;
    uint8_t RSSI;
    uint8_t RCPIMeasurement;
    uint8_t RSNIMeasurement;
    uint8_t *RequestedElements;
    uint8_t *BSSMembershipSelectorSet;
    EFI_80211_ELEMENT_EXT_CAP *ExtCapElement;
} EFI_80211_BSS_DESCRIPTION;

typedef struct {
    uint8_t SubElementID;
    uint8_t Length;
    uint8_t Data[1];
} EFI_80211_SUBELEMENT_INFO;

typedef struct {
    EFI_80211_ELEMENT_HEADER Hdr;
    uint8_t Indicator;
    EFI_80211_SUBELEMENT_INFO SubElement[1];
} EFI_80211_MULTIPLE_BSSID;

typedef struct {
    EFI_80211_MAC_ADDRESS BSSId;
    EFI_80211_BSS_TYPE BSSType;
    uint8_t ConCapInfo;
    uint8_t ConCountryStr[2];
    uint8_t OperatingClass;
    uint8_t Channel;
    uint8_t Interval;
    EFI_80211_MULTIPLE_BSSID *MultipleBSSID;
    uint8_t RCPIMeasurement;
    uint8_t RSNIMeasurement;
} EFI_80211_BSS_DESP_PILOT;

typedef struct {
    size_t NumOfBSSDesp;
    EFI_80211_BSS_DESCRIPTION **BSSDespSet;
    size_t NumOfBSSDespFromPilot;
    EFI_80211_BSS_DESP_PILOT **BSSDespFromPilotSet;
    uint8_t *VendorSpecificInfo;
} EFI_80211_SCAN_RESULT;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    EFI_80211_SCAN_DATA *Data;
    EFI_80211_SCAN_RESULT_CODE ResultCode;
    EFI_80211_SCAN_RESULT *Result;
} EFI_80211_SCAN_DATA_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_WIRELESS_MAC_CONNECTION_SCAN)(
    EFI_WIRELESS_MAC_CONNECTION_PROTOCOL *This,
    EFI_80211_SCAN_DATA_TOKEN *Data
);

typedef struct {
    uint8_t FirstChannelNumber;
    uint8_t NumberOfChannels;
} EFI_80211_ELEMENT_SUPP_CHANNEL_TUPLE;

typedef struct {
    EFI_80211_ELEMENT_HEADER Hdr;
    EFI_80211_ELEMENT_SUPP_CHANNEL_TUPLE Subband[1];
} EFI_80211_ELEMENT_SUPP_CHANNEL;

/* ExtCapElement is a pointer: the description allows NULL (printed by value). */
typedef struct {
    EFI_80211_MAC_ADDRESS BSSId;
    uint16_t CapabilityInfo;
    uint32_t FailureTimeout;
    uint32_t ListenInterval;
    EFI_80211_ELEMENT_SUPP_CHANNEL *Channels;
    EFI_80211_ELEMENT_RSN RSN;
    EFI_80211_ELEMENT_EXT_CAP *ExtCapElement;
    uint8_t *VendorSpecificInfo;
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
    uint8_t Type;
    uint32_t Value;
} EFI_80211_ELEMENT_TIMEOUT_VAL;

typedef struct {
    EFI_80211_MAC_ADDRESS BSSId;
    uint16_t CapabilityInfo;
    uint16_t AssociationID;
    uint8_t RCPIValue;
    uint8_t RSNIValue;
    EFI_80211_ELEMENT_EXT_CAP *ExtCapElement;
    EFI_80211_ELEMENT_TIMEOUT_VAL TimeoutInterval;
    uint8_t *VendorSpecificInfo;
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
    EFI_WIRELESS_MAC_CONNECTION_PROTOCOL *This,
    EFI_80211_ASSOCIATE_DATA_TOKEN *Data
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
    uint8_t *VendorSpecificInfo;
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
    EFI_WIRELESS_MAC_CONNECTION_PROTOCOL *This,
    EFI_80211_DISASSOCIATE_DATA_TOKEN *Data
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
    uint32_t FailureTimeout;
    uint8_t *FTContent;
    uint8_t *SAEContent;
    uint8_t *VendorSpecificInfo;
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
    uint8_t *FTContent;
    uint8_t *SAEContent;
    uint8_t *VendorSpecificInfo;
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
    EFI_WIRELESS_MAC_CONNECTION_PROTOCOL *This,
    EFI_80211_AUTHENTICATE_DATA_TOKEN *Data
);

typedef struct {
    EFI_80211_MAC_ADDRESS BSSId;
    EFI_80211_REASON_CODE ReasonCode;
    uint8_t *VendorSpecificInfo;
} EFI_80211_DEAUTHENTICATE_DATA;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    EFI_80211_DEAUTHENTICATE_DATA *Data;
} EFI_80211_DEAUTHENTICATE_DATA_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_WIRELESS_MAC_CONNECTION_DEAUTHENTICATE)(
    EFI_WIRELESS_MAC_CONNECTION_PROTOCOL *This,
    EFI_80211_DEAUTHENTICATE_DATA_TOKEN *Data
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
    uint8_t SSIdLen;
    uint8_t SSId[EFI_MAX_SSID_LEN];
} EFI_80211_SSID;

typedef struct {
    uint32_t NumOfSSID;
    EFI_80211_SSID SSIDList[1];
} EFI_80211_GET_NETWORKS_DATA;

typedef struct {
    uint8_t Oui[3];
    uint8_t SuiteType;
} EFI_80211_SUITE_SELECTOR;

typedef struct {
    uint16_t AKMSuiteCount;
    EFI_80211_SUITE_SELECTOR AKMSuiteList[1];
} EFI_80211_AKM_SUITE_SELECTOR;

typedef struct {
    uint16_t CipherSuiteCount;
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
    uint8_t NetworkQuality;
} EFI_80211_NETWORK_DESCRIPTION;

typedef struct {
    uint8_t NumOfNetworkDesc;
    EFI_80211_NETWORK_DESCRIPTION NetworkDesc[1];
} EFI_80211_GET_NETWORKS_RESULT;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    EFI_80211_GET_NETWORKS_DATA *Data;
    EFI_80211_GET_NETWORKS_RESULT *Result;
} EFI_80211_GET_NETWORKS_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_WIRELESS_MAC_CONNECTION_II_GET_NETWORKS)(
    EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL *This,
    EFI_80211_GET_NETWORKS_TOKEN *Token
);

typedef struct {
    EFI_80211_NETWORK *Network;
    uint32_t FailureTimeout;
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
    EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL *This,
    EFI_80211_CONNECT_NETWORK_TOKEN *Token
);

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
} EFI_80211_DISCONNECT_NETWORK_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_WIRELESS_MAC_CONNECTION_II_DISCONNECT_NETWORK)(
    EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL *This,
    EFI_80211_DISCONNECT_NETWORK_TOKEN *Token
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
    EFI_SUPPLICANT_PROTOCOL *This,
    uint8_t *RequestBuffer,
    size_t RequestBufferSize,
    uint8_t *Buffer,
    size_t *BufferSize
);

typedef struct {
    uint32_t FragmentLength;
    void *FragmentBuffer;
} EFI_SUPPLICANT_FRAGMENT_DATA;

typedef enum {
    EfiSupplicantEncrypt,
    EfiSupplicantDecrypt
} EFI_SUPPLICANT_CRYPT_MODE;

typedef EFI_STATUS (EFI_API *EFI_SUPPLICANT_PROCESS_PACKET)(
    EFI_SUPPLICANT_PROTOCOL *This,
    EFI_SUPPLICANT_FRAGMENT_DATA **FragmentTable,
    uint32_t *FragmentCount,
    EFI_SUPPLICANT_CRYPT_MODE CryptMode
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
    uint8_t GTKRefresh;
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
    uint8_t Key[EFI_MAX_KEY_LEN];
    uint8_t KeyLen;
    uint8_t KeyId;
    EFI_SUPPLICANT_KEY_TYPE KeyType;
    EFI_80211_MAC_ADDRESS Addr;
    uint8_t Rsc[8];
    uint8_t RscLen;
    uint8_t IsAuthenticator;
    EFI_80211_SUITE_SELECTOR CipherSuite;
    EFI_SUPPLICANT_KEY_DIRECTION Direction;
} EFI_SUPPLICANT_KEY;

typedef struct {
    uint8_t GTKCount;
    EFI_SUPPLICANT_KEY GTKList[1];
} EFI_SUPPLICANT_GTK_LIST;

typedef EFI_STATUS (EFI_API *EFI_SUPPLICANT_SET_DATA)(
    EFI_SUPPLICANT_PROTOCOL *This,
    EFI_SUPPLICANT_DATA_TYPE DataType,
    void *Data,
    size_t DataSize
);

typedef EFI_STATUS (EFI_API *EFI_SUPPLICANT_GET_DATA)(
    EFI_SUPPLICANT_PROTOCOL *This,
    EFI_SUPPLICANT_DATA_TYPE DataType,
    uint8_t *Data,
    size_t *DataSize
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
