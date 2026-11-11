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

struct efi_vlan_config_protocol;

typedef EFI_STATUS (EFI_API *EFI_VLAN_CONFIG_SET)(
    struct efi_vlan_config_protocol *This,
    uint16_t VlanId,
    uint8_t Priority
);

struct efi_vlan_find_data {
    uint16_t VlanId;
    uint8_t Priority;
};

typedef EFI_STATUS (EFI_API *EFI_VLAN_CONFIG_FIND)(
    struct efi_vlan_config_protocol *This,
    uint16_t *VlanId,
    uint16_t *NumberOfVlan,
    struct efi_vlan_find_data **Entries
);

typedef EFI_STATUS (EFI_API *EFI_VLAN_CONFIG_REMOVE)(
    struct efi_vlan_config_protocol *This,
    uint16_t VlanId
);

struct efi_vlan_config_protocol {
    EFI_VLAN_CONFIG_SET Set;
    EFI_VLAN_CONFIG_FIND Find;
    EFI_VLAN_CONFIG_REMOVE Remove;
};

#define EFI_EAP_PROTOCOL_GUID \
    {0x5d9f96db, 0xe731, 0x4caa, {0xa0, 0x0d, 0x72, 0xe1, 0x87, 0xcd, 0x77, 0x62}}

struct efi_eap_protocol;

typedef void *EFI_PORT_HANDLE;

#define EFI_EAP_TYPE_TLS 13

typedef EFI_STATUS (EFI_API *EFI_EAP_SET_DESIRED_AUTHENTICATION_METHOD)(
    struct efi_eap_protocol *This,
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
    struct efi_eap_protocol *This,
    uint8_t EapAuthType,
    EFI_EAP_BUILD_RESPONSE_PACKET Handler
);

struct efi_eap_protocol {
    EFI_EAP_SET_DESIRED_AUTHENTICATION_METHOD SetDesiredAuthMethod;
    EFI_EAP_REGISTER_AUTHENTICATION_METHOD RegisterAuthMethod;
};

#define EFI_EAP_MANAGEMENT_PROTOCOL_GUID \
    {0xbb62e663, 0x625d, 0x40b2, {0xa0, 0x88, 0xbb, 0xe8, 0x36, 0x23, 0xa2, 0x45}}

struct efi_eap_management_protocol;

#define EFI_PAE_SUPPORT_AUTHENTICATOR 0x01
#define EFI_PAE_SUPPORT_SUPPLICANT 0x02

struct efi_eapol_port_info {
    EFI_PORT_HANDLE PortNumber;
    uint8_t ProtocolVersion;
    uint8_t PaeCapabilities;
};

typedef EFI_STATUS (EFI_API *EFI_EAP_GET_SYSTEM_CONFIGURATION)(
    struct efi_eap_management_protocol *This,
    bool *SystemAuthControl,
    struct efi_eapol_port_info *PortInfo
);

typedef EFI_STATUS (EFI_API *EFI_EAP_SET_SYSTEM_CONFIGURATION)(
    struct efi_eap_management_protocol *This,
    bool SystemAuthControl
);

typedef EFI_STATUS (EFI_API *EFI_EAP_INITIALIZE_PORT)(
    struct efi_eap_management_protocol *This
);

typedef EFI_STATUS (EFI_API *EFI_EAP_USER_LOGON)(struct efi_eap_management_protocol *This);

typedef EFI_STATUS (EFI_API *EFI_EAP_USER_LOGOFF)(struct efi_eap_management_protocol *This);

#define EFI_LOGOFF ((uint32_t)0)
#define EFI_DISCONNECTED ((uint32_t)1)
#define EFI_CONNECTING ((uint32_t)2)
#define EFI_ACQUIRED ((uint32_t)3)
#define EFI_AUTHENTICATING ((uint32_t)4)
#define EFI_HELD ((uint32_t)5)
#define EFI_AUTHENTICATED ((uint32_t)6)
#define EFI_MAX_SUPPLICANT_PAE_STATE ((uint32_t)7)

#define EFI_AUTH_PERIOD_FIELD_VALID 0x01
#define EFI_HELD_PERIOD_FIELD_VALID 0x02
#define EFI_START_PERIOD_FIELD_VALID 0x04
#define EFI_MAX_START_FIELD_VALID 0x08

struct efi_eapol_supplicant_pae_configuration {
    uint8_t ValidFieldMask;
    uintptr_t AuthPeriod;
    uintptr_t HeldPeriod;
    uintptr_t StartPeriod;
    size_t MaxStart;
};

typedef EFI_STATUS (EFI_API *EFI_EAP_GET_SUPPLICANT_STATUS)(
    struct efi_eap_management_protocol *This,
    uint32_t *CurrentState,
    struct efi_eapol_supplicant_pae_configuration *Configuration
);

typedef EFI_STATUS (EFI_API *EFI_EAP_SET_SUPPLICANT_CONFIGURATION)(
    struct efi_eap_management_protocol *This,
    struct efi_eapol_supplicant_pae_configuration *Configuration
);

struct efi_eapol_supplicant_pae_statistics {
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
};

typedef EFI_STATUS (EFI_API *EFI_EAP_GET_SUPPLICANT_STATISTICS)(
    struct efi_eap_management_protocol *This,
    struct efi_eapol_supplicant_pae_statistics *Statistics
);

struct efi_eap_management_protocol {
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

struct efi_eap_management2_protocol;

typedef EFI_STATUS (EFI_API *EFI_EAP_GET_KEY)(
    struct efi_eap_management2_protocol *This,
    uint8_t *Msk,
    size_t *MskSize,
    uint8_t *Emsk,
    uint8_t *EmskSize
);

/* The specification prints the members before GetKey as "Same as EFI_EAP_MANAGEMENT_PROTOCOL". */
struct efi_eap_management2_protocol {
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

struct efi_eap_configuration_protocol;

#define EFI_EAP_CONFIG_EAP_AUTH_METHOD ((uint32_t)0)
#define EFI_EAP_CONFIG_EAP_SUPPORTED_AUTH_METHOD ((uint32_t)1)
#define EFI_EAP_CONFIG_IDENTITY_STRING ((uint32_t)2)
#define EFI_EAP_CONFIG_EAP_TLS_CA_CERT ((uint32_t)3)
#define EFI_EAP_CONFIG_EAP_TLS_CLIENT_CERT ((uint32_t)4)
#define EFI_EAP_CONFIG_EAP_TLS_CLIENT_PRIVATE_KEY_FILE ((uint32_t)5)
#define EFI_EAP_CONFIG_EAP_TLS_CLIENT_PRIVATE_KEY_FILE_PASSWORD ((uint32_t)6)
#define EFI_EAP_CONFIG_EAP_TLS_CIPHER_SUITE ((uint32_t)7)
#define EFI_EAP_CONFIG_EAP_TLS_SUPPORTED_CIPHER_SUITE ((uint32_t)8)
#define EFI_EAP_CONFIG_EAP_MS_CHAP_V2_PASSWORD ((uint32_t)9)
#define EFI_EAP_CONFIG_EAP2ND_AUTH_METHOD ((uint32_t)10)

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
    struct efi_eap_configuration_protocol *This,
    EFI_EAP_TYPE EapType,
    uint32_t DataType,
    void *Data,
    size_t DataSize
);

typedef EFI_STATUS (EFI_API *EFI_EAP_CONFIGURATION_GET_DATA)(
    struct efi_eap_configuration_protocol *This,
    EFI_EAP_TYPE EapType,
    uint32_t DataType,
    void *Data,
    size_t *DataSize
);

struct efi_eap_configuration_protocol {
    EFI_EAP_CONFIGURATION_SET_DATA SetData;
    EFI_EAP_CONFIGURATION_GET_DATA GetData;
};

#define EFI_WIRELESS_MAC_CONNECTION_PROTOCOL_GUID \
    {0xda55bc9, 0x45f8, 0x4bb4, {0x87, 0x19, 0x52, 0x24, 0xf1, 0x8a, 0x4d, 0x45}}

struct efi_wireless_mac_connection_protocol;

#define EFI_IEEE_INFRASTRUCTURE_BSS ((uint32_t)0)
#define EFI_IEEE_INDEPENDENT_BSS ((uint32_t)1)
#define EFI_IEEE_MESH_BSS ((uint32_t)2)
#define EFI_IEEE_ANY_BSS ((uint32_t)3)

struct efi_80211_mac_address {
    uint8_t Addr[6];
};

struct efi_80211_element_header {
    uint8_t ElementID;
    uint8_t Length;
};

struct efi_80211_element_req {
    struct efi_80211_element_header Hdr;
    uint8_t RequestIDs[1];
};

struct efi_80211_element_ssid {
    struct efi_80211_element_header Hdr;
    uint8_t SSId[32];
};

#define EFI_IEEE_PRIVATE ((uint32_t)0)
#define EFI_IEEE_PRIVATEWITH_GUEST ((uint32_t)1)
#define EFI_IEEE_CHARGEABLE_PUBLIC ((uint32_t)2)
#define EFI_IEEE_FREE_PUBLIC ((uint32_t)3)
#define EFI_IEEE_PERSONAL ((uint32_t)4)
#define EFI_IEEE_EMERGENCY_SERV_ONLY ((uint32_t)5)
#define EFI_IEEE_TEST_OR_EXP ((uint32_t)14)
#define EFI_IEEE_WILDCARD ((uint32_t)15)

struct efi_80211_scan_data {
    uint32_t BSSType;
    struct efi_80211_mac_address BSSId;
    uint8_t SSIdLen;
    uint8_t *SSId;
    uint8_t PassiveMode;
    uint32_t ProbeDelay;
    uint32_t *ChannelList;
    uint32_t MinChannelTime;
    uint32_t MaxChannelTime;
    struct efi_80211_element_req *RequestInformation;
    struct efi_80211_element_ssid *SSIDList;
    uint32_t AccessNetworkType;
    uint8_t *VendorSpecificInfo;
};

#define EFI_SCAN_SUCCESS ((uint32_t)0)
#define EFI_SCAN_NOT_SUPPORTED ((uint32_t)1)

struct efi_80211_country_triplet_subband {
    uint8_t FirstChannelNum;
    uint8_t NumOfChannels;
    uint8_t MaxTxPowerLevel;
};

struct efi_80211_country_triplet_operate {
    uint8_t OperatingExtId;
    uint8_t OperatingClass;
    uint8_t CoverageClass;
};

union efi_80211_country_triplet {
    struct efi_80211_country_triplet_subband Subband;
    struct efi_80211_country_triplet_operate Operating;
};

struct efi_80211_element_country {
    struct efi_80211_element_header Hdr;
    uint8_t CountryStr[3];
    union efi_80211_country_triplet CountryTriplet[1];
};

/* The rest of the RSN element (suite lists, capabilities, PMKIDs) follows; it varies in length. */
struct efi_80211_element_data_rsn {
    uint16_t Version;
    uint32_t GroupDataCipherSuite;
};

struct efi_80211_element_rsn {
    struct efi_80211_element_header Hdr;
    struct efi_80211_element_data_rsn *Data;
};

struct efi_80211_element_ext_cap {
    struct efi_80211_element_header Hdr;
    uint8_t Capabilities[1];
};

/* BSSId is a value, as in every other structure here; printed with a stray asterisk. */
struct efi_80211_bss_description {
    struct efi_80211_mac_address BSSId;
    uint8_t *SSId;
    uint8_t SSIdLen;
    uint32_t BSSType;
    uint16_t BeaconPeriod;
    uint64_t Timestamp;
    uint16_t CapabilityInfo;
    uint8_t *BSSBasicRateSet;
    uint8_t *OperationalRateSet;
    struct efi_80211_element_country *Country;
    struct efi_80211_element_rsn RSN;
    uint8_t RSSI;
    uint8_t RCPIMeasurement;
    uint8_t RSNIMeasurement;
    uint8_t *RequestedElements;
    uint8_t *BSSMembershipSelectorSet;
    struct efi_80211_element_ext_cap *ExtCapElement;
};

struct efi_80211_subelement_info {
    uint8_t SubElementID;
    uint8_t Length;
    uint8_t Data[1];
};

struct efi_80211_multiple_bssid {
    struct efi_80211_element_header Hdr;
    uint8_t Indicator;
    struct efi_80211_subelement_info SubElement[1];
};

struct efi_80211_bss_desp_pilot {
    struct efi_80211_mac_address BSSId;
    uint32_t BSSType;
    uint8_t ConCapInfo;
    uint8_t ConCountryStr[2];
    uint8_t OperatingClass;
    uint8_t Channel;
    uint8_t Interval;
    struct efi_80211_multiple_bssid *MultipleBSSID;
    uint8_t RCPIMeasurement;
    uint8_t RSNIMeasurement;
};

struct efi_80211_scan_result {
    size_t NumOfBSSDesp;
    struct efi_80211_bss_description **BSSDespSet;
    size_t NumOfBSSDespFromPilot;
    struct efi_80211_bss_desp_pilot **BSSDespFromPilotSet;
    uint8_t *VendorSpecificInfo;
};

struct efi_80211_scan_data_token {
    EFI_EVENT Event;
    EFI_STATUS Status;
    struct efi_80211_scan_data *Data;
    uint32_t ResultCode;
    struct efi_80211_scan_result *Result;
};

typedef EFI_STATUS (EFI_API *EFI_WIRELESS_MAC_CONNECTION_SCAN)(
    struct efi_wireless_mac_connection_protocol *This,
    struct efi_80211_scan_data_token *Data
);

struct efi_80211_element_supp_channel_tuple {
    uint8_t FirstChannelNumber;
    uint8_t NumberOfChannels;
};

struct efi_80211_element_supp_channel {
    struct efi_80211_element_header Hdr;
    struct efi_80211_element_supp_channel_tuple Subband[1];
};

/* ExtCapElement is a pointer: the description allows NULL (printed by value). */
struct efi_80211_associate_data {
    struct efi_80211_mac_address BSSId;
    uint16_t CapabilityInfo;
    uint32_t FailureTimeout;
    uint32_t ListenInterval;
    struct efi_80211_element_supp_channel *Channels;
    struct efi_80211_element_rsn RSN;
    struct efi_80211_element_ext_cap *ExtCapElement;
    uint8_t *VendorSpecificInfo;
};

#define EFI_ASSOCIATE_SUCCESS ((uint32_t)0)
#define EFI_ASSOCIATE_REFUSED_REASON_UNSPECIFIED ((uint32_t)1)
#define EFI_ASSOCIATE_REFUSED_CAPS_MISMATCH ((uint32_t)2)
#define EFI_ASSOCIATE_REFUSED_EXT_REASON ((uint32_t)3)
#define EFI_ASSOCIATE_REFUSED_AP_OUT_OF_MEMORY ((uint32_t)4)
#define EFI_ASSOCIATE_REFUSED_BASIC_RATES_MISMATCH ((uint32_t)5)
#define EFI_ASSOCIATE_REJECTED_EMERGENCY_SERVICES_NOT_SUPPORTED ((uint32_t)6)
#define EFI_ASSOCIATE_REFUSED_TEMPORARILY ((uint32_t)7)

struct efi_80211_element_timeout_val {
    struct efi_80211_element_header Hdr;
    uint8_t Type;
    uint32_t Value;
};

struct efi_80211_associate_result {
    struct efi_80211_mac_address BSSId;
    uint16_t CapabilityInfo;
    uint16_t AssociationID;
    uint8_t RCPIValue;
    uint8_t RSNIValue;
    struct efi_80211_element_ext_cap *ExtCapElement;
    struct efi_80211_element_timeout_val TimeoutInterval;
    uint8_t *VendorSpecificInfo;
};

/* Data and Result are pointers, as described (printed by value). */
struct efi_80211_associate_data_token {
    EFI_EVENT Event;
    EFI_STATUS Status;
    struct efi_80211_associate_data *Data;
    uint32_t ResultCode;
    struct efi_80211_associate_result *Result;
};

typedef EFI_STATUS (EFI_API *EFI_WIRELESS_MAC_CONNECTION_ASSOCIATE)(
    struct efi_wireless_mac_connection_protocol *This,
    struct efi_80211_associate_data_token *Data
);

#define EFI_IEEE80211_UNSPECIFIED_REASON ((uint32_t)1)
#define EFI_IEEE80211_PREVIOUS_AUTHENTICATE_INVALID ((uint32_t)2)
#define EFI_IEEE80211_DEAUTHENTICATED_SINCE_LEAVING ((uint32_t)3)
#define EFI_IEEE80211_DISASSOCIATED_DUE_TO_INACTIVE ((uint32_t)4)
#define EFI_IEEE80211_DISASSOCIATED_SINCE_AP_UNABLE ((uint32_t)5)
#define EFI_IEEE80211_CLASS2_FRAME_NONAUTHENTICATED ((uint32_t)6)
#define EFI_IEEE80211_CLASS3_FRAME_NONASSOCIATED ((uint32_t)7)
#define EFI_IEEE80211_DISASSOCIATED_SINCE_LEAVING ((uint32_t)8)

struct efi_80211_disassociate_data {
    struct efi_80211_mac_address BSSId;
    uint32_t ReasonCode;
    uint8_t *VendorSpecificInfo;
};

#define EFI_DISASSOCIATE_SUCCESS ((uint32_t)0)
#define EFI_DISASSOCIATE_INVALID_PARAMETERS ((uint32_t)1)

struct efi_80211_disassociate_data_token {
    EFI_EVENT Event;
    EFI_STATUS Status;
    struct efi_80211_disassociate_data *Data;
    uint32_t ResultCode;
};

typedef EFI_STATUS (EFI_API *EFI_WIRELESS_MAC_CONNECTION_DISASSOCIATE)(
    struct efi_wireless_mac_connection_protocol *This,
    struct efi_80211_disassociate_data_token *Data
);

#define EFI_OPEN_SYSTEM ((uint32_t)0)
#define EFI_SHARED_KEY ((uint32_t)1)
#define EFI_FAST_BSS_TRANSITION ((uint32_t)2)
#define EFI_SAE ((uint32_t)3)

struct efi_80211_authenticate_data {
    struct efi_80211_mac_address BSSId;
    uint32_t AuthType;
    uint32_t FailureTimeout;
    uint8_t *FTContent;
    uint8_t *SAEContent;
    uint8_t *VendorSpecificInfo;
};

#define EFI_AUTHENTICATE_SUCCESS ((uint32_t)0)
#define EFI_AUTHENTICATE_REFUSED ((uint32_t)1)
#define EFI_AUTHENTICATE_ANTIC_LOGGING_TOKEN_REQUIRED ((uint32_t)2)
#define EFI_AUTHENTICATE_FINITE_CYCLIC_GROUP_NOT_SUPPORTED ((uint32_t)3)
#define EFI_AUTHENTICATION_REJECTED ((uint32_t)4)
#define EFI_AUTHENTICATE_INVALID_PARAMETER ((uint32_t)5)

struct efi_80211_authenticate_result {
    struct efi_80211_mac_address BSSId;
    uint8_t *FTContent;
    uint8_t *SAEContent;
    uint8_t *VendorSpecificInfo;
};

/* Result is a pointer to a buffer the caller frees, as described (printed by value). */
struct efi_80211_authenticate_data_token {
    EFI_EVENT Event;
    EFI_STATUS Status;
    struct efi_80211_authenticate_data *Data;
    uint32_t ResultCode;
    struct efi_80211_authenticate_result *Result;
};

typedef EFI_STATUS (EFI_API *EFI_WIRELESS_MAC_CONNECTION_AUTHENTICATE)(
    struct efi_wireless_mac_connection_protocol *This,
    struct efi_80211_authenticate_data_token *Data
);

struct efi_80211_deauthenticate_data {
    struct efi_80211_mac_address BSSId;
    uint32_t ReasonCode;
    uint8_t *VendorSpecificInfo;
};

struct efi_80211_deauthenticate_data_token {
    EFI_EVENT Event;
    EFI_STATUS Status;
    struct efi_80211_deauthenticate_data *Data;
};

typedef EFI_STATUS (EFI_API *EFI_WIRELESS_MAC_CONNECTION_DEAUTHENTICATE)(
    struct efi_wireless_mac_connection_protocol *This,
    struct efi_80211_deauthenticate_data_token *Data
);

struct efi_wireless_mac_connection_protocol {
    EFI_WIRELESS_MAC_CONNECTION_SCAN Scan;
    EFI_WIRELESS_MAC_CONNECTION_ASSOCIATE Associate;
    EFI_WIRELESS_MAC_CONNECTION_DISASSOCIATE Disassociate;
    EFI_WIRELESS_MAC_CONNECTION_AUTHENTICATE Authenticate;
    EFI_WIRELESS_MAC_CONNECTION_DEAUTHENTICATE Deauthenticate;
};

#define EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL_GUID \
    {0x1b0fb9bf, 0x699d, 0x4fdd, {0xa7, 0xc3, 0x25, 0x46, 0x68, 0x1b, 0xf6, 0x3b}}

struct efi_wireless_mac_connection_ii_protocol;

#define EFI_MAX_SSID_LEN 32

struct efi_80211_ssid {
    uint8_t SSIdLen;
    uint8_t SSId[EFI_MAX_SSID_LEN];
};

struct efi_80211_get_networks_data {
    uint32_t NumOfSSID;
    struct efi_80211_ssid SSIDList[1];
};

struct efi_80211_suite_selector {
    uint8_t Oui[3];
    uint8_t SuiteType;
};

struct efi_80211_akm_suite_selector {
    uint16_t AKMSuiteCount;
    struct efi_80211_suite_selector AKMSuiteList[1];
};

struct efi_80211_cipher_suite_selector {
    uint16_t CipherSuiteCount;
    struct efi_80211_suite_selector CipherSuiteList[1];
};

struct efi_80211_network {
    uint32_t BSSType;
    struct efi_80211_ssid SSId;
    struct efi_80211_akm_suite_selector *AKMSuite;
    struct efi_80211_cipher_suite_selector *CipherSuite;
};

struct efi_80211_network_description {
    struct efi_80211_network Network;
    uint8_t NetworkQuality;
};

struct efi_80211_get_networks_result {
    uint8_t NumOfNetworkDesc;
    struct efi_80211_network_description NetworkDesc[1];
};

struct efi_80211_get_networks_token {
    EFI_EVENT Event;
    EFI_STATUS Status;
    struct efi_80211_get_networks_data *Data;
    struct efi_80211_get_networks_result *Result;
};

typedef EFI_STATUS (EFI_API *EFI_WIRELESS_MAC_CONNECTION_II_GET_NETWORKS)(
    struct efi_wireless_mac_connection_ii_protocol *This,
    struct efi_80211_get_networks_token *Token
);

struct efi_80211_connect_network_data {
    struct efi_80211_network *Network;
    uint32_t FailureTimeout;
};

#define EFI_CONNECT_SUCCESS ((uint32_t)0)
#define EFI_CONNECT_REFUSED ((uint32_t)1)
#define EFI_CONNECT_FAILED ((uint32_t)2)
#define EFI_CONNECT_FAILURE_TIMEOUT ((uint32_t)3)
#define EFI_CONNECT_FAILED_REASON_UNSPECIFIED ((uint32_t)4)

struct efi_80211_connect_network_token {
    EFI_EVENT Event;
    EFI_STATUS Status;
    struct efi_80211_connect_network_data *Data;
    uint32_t ResultCode;
};

typedef EFI_STATUS (EFI_API *EFI_WIRELESS_MAC_CONNECTION_II_CONNECT_NETWORK)(
    struct efi_wireless_mac_connection_ii_protocol *This,
    struct efi_80211_connect_network_token *Token
);

struct efi_80211_disconnect_network_token {
    EFI_EVENT Event;
    EFI_STATUS Status;
};

typedef EFI_STATUS (EFI_API *EFI_WIRELESS_MAC_CONNECTION_II_DISCONNECT_NETWORK)(
    struct efi_wireless_mac_connection_ii_protocol *This,
    struct efi_80211_disconnect_network_token *Token
);

struct efi_wireless_mac_connection_ii_protocol {
    EFI_WIRELESS_MAC_CONNECTION_II_GET_NETWORKS GetNetworks;
    EFI_WIRELESS_MAC_CONNECTION_II_CONNECT_NETWORK ConnectNetwork;
    EFI_WIRELESS_MAC_CONNECTION_II_DISCONNECT_NETWORK DisconnectNetwork;
};

#define EFI_SUPPLICANT_SERVICE_BINDING_PROTOCOL_GUID \
    {0x45bcd98e, 0x59ad, 0x4174, {0x95, 0x46, 0x34, 0x4a, 0x7, 0x48, 0x58, 0x98}}

#define EFI_SUPPLICANT_PROTOCOL_GUID \
    {0x54fcc43e, 0xaa89, 0x4333, {0x9a, 0x85, 0xcd, 0xea, 0x24, 0x5, 0x1e, 0x9e}}

struct efi_supplicant_protocol;

typedef EFI_STATUS (EFI_API *EFI_SUPPLICANT_BUILD_RESPONSE_PACKET)(
    struct efi_supplicant_protocol *This,
    uint8_t *RequestBuffer,
    size_t RequestBufferSize,
    uint8_t *Buffer,
    size_t *BufferSize
);

struct efi_supplicant_fragment_data {
    uint32_t FragmentLength;
    void *FragmentBuffer;
};

#define EFI_SUPPLICANT_ENCRYPT ((uint32_t)0)
#define EFI_SUPPLICANT_DECRYPT ((uint32_t)1)

typedef EFI_STATUS (EFI_API *EFI_SUPPLICANT_PROCESS_PACKET)(
    struct efi_supplicant_protocol *This,
    struct efi_supplicant_fragment_data **FragmentTable,
    uint32_t *FragmentCount,
    uint32_t CryptMode
);

#define EFI_SUPPLICANT_80211_AKM_SUITE ((uint32_t)0)
#define EFI_SUPPLICANT_80211_GROUP_DATA_CIPHER_SUITE ((uint32_t)1)
#define EFI_SUPPLICANT_80211_PAIRWISE_CIPHER_SUITE ((uint32_t)2)
#define EFI_SUPPLICANT_80211_PSK_PASSWORD ((uint32_t)3)
#define EFI_SUPPLICANT_80211_TARGET_SSID_NAME ((uint32_t)4)
#define EFI_SUPPLICANT_80211_STATION_MAC ((uint32_t)5)
#define EFI_SUPPLICANT_80211_TARGET_SSID_MAC ((uint32_t)6)
#define EFI_SUPPLICANT_80211_PTK ((uint32_t)7)
#define EFI_SUPPLICANT_80211_GTK ((uint32_t)8)
#define EFI_SUPPLICANT_STATE ((uint32_t)9)
#define EFI_SUPPLICANT_80211_LINK_STATE ((uint32_t)10)
#define EFI_SUPPLICANT_KEY_REFRESH ((uint32_t)11)
#define EFI_SUPPLICANT_80211_SUPPORTED_AKM_SUITES ((uint32_t)12)
#define EFI_SUPPLICANT_80211_SUPPORTED_SOFTWARE_CIPHER_SUITES ((uint32_t)13)
#define EFI_SUPPLICANT_80211_SUPPORTED_HARDWARE_CIPHER_SUITES ((uint32_t)14)
#define EFI_SUPPLICANT_80211_IGTK ((uint32_t)15)
#define EFI_SUPPLICANT_80211_PMK ((uint32_t)16)
#define EFI_SUPPLICANT_DATA_TYPE_MAXIMUM ((uint32_t)17)

#define EFI_IEEE80211_UNAUTHENTICATED_UNASSOCIATED ((uint32_t)0)
#define EFI_IEEE80211_AUTHENTICATED_UNASSOCIATED ((uint32_t)1)
#define EFI_IEEE80211_PENDING_RSN_AUTHENTICATION ((uint32_t)2)
#define EFI_IEEE80211_AUTHENTICATED_ASSOCIATED ((uint32_t)3)

struct efi_supplicant_key_refresh {
    uint8_t GTKRefresh;
};

#define EFI_MAX_KEY_LEN 64

#define EFI_GROUP ((uint32_t)0)
#define EFI_PAIRWISE ((uint32_t)1)
#define EFI_PEER_KEY ((uint32_t)2)
#define EFI_IGTK ((uint32_t)3)

#define EFI_RECEIVE ((uint32_t)0)
#define EFI_TRANSMIT ((uint32_t)1)
#define EFI_BOTH ((uint32_t)2)

struct efi_supplicant_key {
    uint8_t Key[EFI_MAX_KEY_LEN];
    uint8_t KeyLen;
    uint8_t KeyId;
    uint32_t KeyType;
    struct efi_80211_mac_address Addr;
    uint8_t Rsc[8];
    uint8_t RscLen;
    uint8_t IsAuthenticator;
    struct efi_80211_suite_selector CipherSuite;
    uint32_t Direction;
};

struct efi_supplicant_gtk_list {
    uint8_t GTKCount;
    struct efi_supplicant_key GTKList[1];
};

typedef EFI_STATUS (EFI_API *EFI_SUPPLICANT_SET_DATA)(
    struct efi_supplicant_protocol *This,
    uint32_t DataType,
    void *Data,
    size_t DataSize
);

typedef EFI_STATUS (EFI_API *EFI_SUPPLICANT_GET_DATA)(
    struct efi_supplicant_protocol *This,
    uint32_t DataType,
    uint8_t *Data,
    size_t *DataSize
);

struct efi_supplicant_protocol {
    EFI_SUPPLICANT_BUILD_RESPONSE_PACKET BuildResponsePacket;
    EFI_SUPPLICANT_PROCESS_PACKET ProcessPacket;
    EFI_SUPPLICANT_SET_DATA SetData;
    EFI_SUPPLICANT_GET_DATA GetData;
};

#ifdef __cplusplus
}
#endif

#endif
