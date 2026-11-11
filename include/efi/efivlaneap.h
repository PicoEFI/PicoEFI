#ifndef EFI_EFIVLANEAP_H
#define EFI_EFIVLANEAP_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <efi/efidef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_VLAN_CONFIG_PROTOCOL_GUID \
    { 0x9e23d768, 0xd2f3, 0x4366, { 0x9f, 0xc3, 0x3a, 0x7a, 0xba, 0x86, 0x43, 0x74 } }

struct efi_vlan_config_protocol;

typedef efi_status (EFI_API *efi_vlan_config_set)(
    struct efi_vlan_config_protocol *self,
    uint16_t vlan_id,
    uint8_t priority
);

struct efi_vlan_find_data {
    uint16_t vlan_id;
    uint8_t priority;
};

typedef efi_status (EFI_API *efi_vlan_config_find)(
    struct efi_vlan_config_protocol *self,
    uint16_t *vlan_id,
    uint16_t *number_of_vlan,
    struct efi_vlan_find_data **entries
);

typedef efi_status (EFI_API *efi_vlan_config_remove)(
    struct efi_vlan_config_protocol *self,
    uint16_t vlan_id
);

struct efi_vlan_config_protocol {
    efi_vlan_config_set set;
    efi_vlan_config_find find;
    efi_vlan_config_remove remove;
};

#define EFI_EAP_PROTOCOL_GUID \
    { 0x5d9f96db, 0xe731, 0x4caa, { 0xa0, 0x0d, 0x72, 0xe1, 0x87, 0xcd, 0x77, 0x62 } }

struct efi_eap_protocol;

typedef void *efi_port_handle;

#define EFI_EAP_TYPE_TLS 13

typedef efi_status (EFI_API *efi_eap_set_desired_authentication_method)(
    struct efi_eap_protocol *self,
    uint8_t eap_auth_type
);

typedef efi_status (EFI_API *efi_eap_build_response_packet)(
    efi_port_handle port_number,
    uint8_t *request_buffer,
    size_t request_size,
    uint8_t *buffer,
    size_t *buffer_size
);

typedef efi_status (EFI_API *efi_eap_register_authentication_method)(
    struct efi_eap_protocol *self,
    uint8_t eap_auth_type,
    efi_eap_build_response_packet handler
);

struct efi_eap_protocol {
    efi_eap_set_desired_authentication_method set_desired_auth_method;
    efi_eap_register_authentication_method register_auth_method;
};

#define EFI_EAP_MANAGEMENT_PROTOCOL_GUID \
    { 0xbb62e663, 0x625d, 0x40b2, { 0xa0, 0x88, 0xbb, 0xe8, 0x36, 0x23, 0xa2, 0x45 } }

struct efi_eap_management_protocol;

#define EFI_PAE_SUPPORT_AUTHENTICATOR 0x01
#define EFI_PAE_SUPPORT_SUPPLICANT 0x02

struct efi_eapol_port_info {
    efi_port_handle port_number;
    uint8_t protocol_version;
    uint8_t pae_capabilities;
};

typedef efi_status (EFI_API *efi_eap_get_system_configuration)(
    struct efi_eap_management_protocol *self,
    bool *system_auth_control,
    struct efi_eapol_port_info *port_info
);

typedef efi_status (EFI_API *efi_eap_set_system_configuration)(
    struct efi_eap_management_protocol *self,
    bool system_auth_control
);

typedef efi_status (EFI_API *efi_eap_initialize_port)(
    struct efi_eap_management_protocol *self
);

typedef efi_status (EFI_API *efi_eap_user_logon)(struct efi_eap_management_protocol *self);

typedef efi_status (EFI_API *efi_eap_user_logoff)(struct efi_eap_management_protocol *self);

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
    uint8_t valid_field_mask;
    size_t auth_period;
    size_t held_period;
    size_t start_period;
    size_t max_start;
};

typedef efi_status (EFI_API *efi_eap_get_supplicant_status)(
    struct efi_eap_management_protocol *self,
    uint32_t *current_state,
    struct efi_eapol_supplicant_pae_configuration *configuration
);

typedef efi_status (EFI_API *efi_eap_set_supplicant_configuration)(
    struct efi_eap_management_protocol *self,
    struct efi_eapol_supplicant_pae_configuration *configuration
);

struct efi_eapol_supplicant_pae_statistics {
    size_t eapol_frames_received;
    size_t eapol_frames_transmitted;
    size_t eapol_start_frames_transmitted;
    size_t eapol_logoff_frames_transmitted;
    size_t eap_resp_id_frames_transmitted;
    size_t eap_response_frames_transmitted;
    size_t eap_req_id_frames_received;
    size_t eap_request_frames_received;
    size_t invalid_eapol_frames_received;
    size_t eap_length_error_frames_received;
    size_t last_eapol_frame_version;
    size_t last_eapol_frame_source;
};

typedef efi_status (EFI_API *efi_eap_get_supplicant_statistics)(
    struct efi_eap_management_protocol *self,
    struct efi_eapol_supplicant_pae_statistics *statistics
);

struct efi_eap_management_protocol {
    efi_eap_get_system_configuration get_system_configuration;
    efi_eap_set_system_configuration set_system_configuration;
    efi_eap_initialize_port initialize_port;
    efi_eap_user_logon user_logon;
    efi_eap_user_logoff user_logoff;
    efi_eap_get_supplicant_status get_supplicant_status;
    efi_eap_set_supplicant_configuration set_supplicant_configuration;
    efi_eap_get_supplicant_statistics get_supplicant_statistics;
};

#define EFI_EAP_MANAGEMENT2_PROTOCOL_GUID \
    { 0x5e93c847, 0x456d, 0x40b3, { 0xa6, 0xb4, 0x78, 0xb0, 0xc9, 0xcf, 0x7f, 0x20 } }

struct efi_eap_management2_protocol;

typedef efi_status (EFI_API *efi_eap_get_key)(
    struct efi_eap_management2_protocol *self,
    uint8_t *msk,
    size_t *msk_size,
    uint8_t *emsk,
    uint8_t *emsk_size
);

// The specification prints "Same as EFI_EAP_MANAGEMENT_PROTOCOL" for the
// members before get_key.
struct efi_eap_management2_protocol {
    efi_eap_get_system_configuration get_system_configuration;
    efi_eap_set_system_configuration set_system_configuration;
    efi_eap_initialize_port initialize_port;
    efi_eap_user_logon user_logon;
    efi_eap_user_logoff user_logoff;
    efi_eap_get_supplicant_status get_supplicant_status;
    efi_eap_set_supplicant_configuration set_supplicant_configuration;
    efi_eap_get_supplicant_statistics get_supplicant_statistics;
    efi_eap_get_key get_key;
};

#define EFI_EAP_CONFIGURATION_PROTOCOL_GUID \
    { 0xe5b58dbb, 0x7688, 0x44b4, { 0x97, 0xbf, 0x5f, 0x1d, 0x4b, 0x7c, 0xc8, 0xdb } }

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

typedef uint8_t efi_eap_type;

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

typedef efi_status (EFI_API *efi_eap_configuration_set_data)(
    struct efi_eap_configuration_protocol *self,
    efi_eap_type eap_type,
    uint32_t data_type,
    void *data,
    size_t data_size
);

typedef efi_status (EFI_API *efi_eap_configuration_get_data)(
    struct efi_eap_configuration_protocol *self,
    efi_eap_type eap_type,
    uint32_t data_type,
    void *data,
    size_t *data_size
);

struct efi_eap_configuration_protocol {
    efi_eap_configuration_set_data set_data;
    efi_eap_configuration_get_data get_data;
};

#define EFI_WIRELESS_MAC_CONNECTION_PROTOCOL_GUID \
    { 0xda55bc9, 0x45f8, 0x4bb4, { 0x87, 0x19, 0x52, 0x24, 0xf1, 0x8a, 0x4d, 0x45 } }

struct efi_wireless_mac_connection_protocol;

#define EFI_IEEE_INFRASTRUCTURE_BSS ((uint32_t)0)
#define EFI_IEEE_INDEPENDENT_BSS ((uint32_t)1)
#define EFI_IEEE_MESH_BSS ((uint32_t)2)
#define EFI_IEEE_ANY_BSS ((uint32_t)3)

struct efi_80211_mac_address {
    uint8_t addr[6];
};

struct efi_80211_element_header {
    uint8_t element_id;
    uint8_t length;
};

struct efi_80211_element_req {
    struct efi_80211_element_header hdr;
    uint8_t request_ids[1];
};

struct efi_80211_element_ssid {
    struct efi_80211_element_header hdr;
    uint8_t ss_id[32];
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
    uint32_t bss_type;
    struct efi_80211_mac_address bss_id;
    uint8_t ss_id_len;
    uint8_t *ss_id;
    uint8_t passive_mode;
    uint32_t probe_delay;
    uint32_t *channel_list;
    uint32_t min_channel_time;
    uint32_t max_channel_time;
    struct efi_80211_element_req *request_information;
    struct efi_80211_element_ssid *ssid_list;
    uint32_t access_network_type;
    uint8_t *vendor_specific_info;
};

#define EFI_SCAN_SUCCESS ((uint32_t)0)
#define EFI_SCAN_NOT_SUPPORTED ((uint32_t)1)

struct efi_80211_country_triplet_subband {
    uint8_t first_channel_num;
    uint8_t num_of_channels;
    uint8_t max_tx_power_level;
};

struct efi_80211_country_triplet_operate {
    uint8_t operating_ext_id;
    uint8_t operating_class;
    uint8_t coverage_class;
};

union efi_80211_country_triplet {
    struct efi_80211_country_triplet_subband subband;
    struct efi_80211_country_triplet_operate operating;
};

struct efi_80211_element_country {
    struct efi_80211_element_header hdr;
    uint8_t country_str[3];
    union efi_80211_country_triplet country_triplet[1];
};

// The rest of the RSN element (suite lists, capabilities, PMKIDs) follows; it
// varies in length.
struct efi_80211_element_data_rsn {
    uint16_t version;
    uint32_t group_data_cipher_suite;
};

struct efi_80211_element_rsn {
    struct efi_80211_element_header hdr;
    struct efi_80211_element_data_rsn *data;
};

struct efi_80211_element_ext_cap {
    struct efi_80211_element_header hdr;
    uint8_t capabilities[1];
};

// bss_id is a value, as in every other structure here; printed with a stray
// asterisk.
struct efi_80211_bss_description {
    struct efi_80211_mac_address bss_id;
    uint8_t *ss_id;
    uint8_t ss_id_len;
    uint32_t bss_type;
    uint16_t beacon_period;
    uint64_t timestamp;
    uint16_t capability_info;
    uint8_t *bss_basic_rate_set;
    uint8_t *operational_rate_set;
    struct efi_80211_element_country *country;
    struct efi_80211_element_rsn rsn;
    uint8_t rssi;
    uint8_t rcpi_measurement;
    uint8_t rsni_measurement;
    uint8_t *requested_elements;
    uint8_t *bss_membership_selector_set;
    struct efi_80211_element_ext_cap *ext_cap_element;
};

struct efi_80211_subelement_info {
    uint8_t sub_element_id;
    uint8_t length;
    uint8_t data[1];
};

struct efi_80211_multiple_bssid {
    struct efi_80211_element_header hdr;
    uint8_t indicator;
    struct efi_80211_subelement_info sub_element[1];
};

struct efi_80211_bss_desp_pilot {
    struct efi_80211_mac_address bss_id;
    uint32_t bss_type;
    uint8_t con_cap_info;
    uint8_t con_country_str[2];
    uint8_t operating_class;
    uint8_t channel;
    uint8_t interval;
    struct efi_80211_multiple_bssid *multiple_bssid;
    uint8_t rcpi_measurement;
    uint8_t rsni_measurement;
};

struct efi_80211_scan_result {
    size_t num_of_bss_desp;
    struct efi_80211_bss_description **bss_desp_set;
    size_t num_of_bss_desp_from_pilot;
    struct efi_80211_bss_desp_pilot **bss_desp_from_pilot_set;
    uint8_t *vendor_specific_info;
};

struct efi_80211_scan_data_token {
    efi_event event;
    efi_status status;
    struct efi_80211_scan_data *data;
    uint32_t result_code;
    struct efi_80211_scan_result *result;
};

typedef efi_status (EFI_API *efi_wireless_mac_connection_scan)(
    struct efi_wireless_mac_connection_protocol *self,
    struct efi_80211_scan_data_token *data
);

struct efi_80211_element_supp_channel_tuple {
    uint8_t first_channel_number;
    uint8_t number_of_channels;
};

struct efi_80211_element_supp_channel {
    struct efi_80211_element_header hdr;
    struct efi_80211_element_supp_channel_tuple subband[1];
};

// ext_cap_element is a pointer: the description allows NULL (printed by
// value).
struct efi_80211_associate_data {
    struct efi_80211_mac_address bss_id;
    uint16_t capability_info;
    uint32_t failure_timeout;
    uint32_t listen_interval;
    struct efi_80211_element_supp_channel *channels;
    struct efi_80211_element_rsn rsn;
    struct efi_80211_element_ext_cap *ext_cap_element;
    uint8_t *vendor_specific_info;
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
    struct efi_80211_element_header hdr;
    uint8_t type;
    uint32_t value;
};

struct efi_80211_associate_result {
    struct efi_80211_mac_address bss_id;
    uint16_t capability_info;
    uint16_t association_id;
    uint8_t rcpi_value;
    uint8_t rsni_value;
    struct efi_80211_element_ext_cap *ext_cap_element;
    struct efi_80211_element_timeout_val timeout_interval;
    uint8_t *vendor_specific_info;
};

// data and result are pointers, as described (printed by value).
struct efi_80211_associate_data_token {
    efi_event event;
    efi_status status;
    struct efi_80211_associate_data *data;
    uint32_t result_code;
    struct efi_80211_associate_result *result;
};

typedef efi_status (EFI_API *efi_wireless_mac_connection_associate)(
    struct efi_wireless_mac_connection_protocol *self,
    struct efi_80211_associate_data_token *data
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
    struct efi_80211_mac_address bss_id;
    uint32_t reason_code;
    uint8_t *vendor_specific_info;
};

#define EFI_DISASSOCIATE_SUCCESS ((uint32_t)0)
#define EFI_DISASSOCIATE_INVALID_PARAMETERS ((uint32_t)1)

struct efi_80211_disassociate_data_token {
    efi_event event;
    efi_status status;
    struct efi_80211_disassociate_data *data;
    uint32_t result_code;
};

typedef efi_status (EFI_API *efi_wireless_mac_connection_disassociate)(
    struct efi_wireless_mac_connection_protocol *self,
    struct efi_80211_disassociate_data_token *data
);

#define EFI_OPEN_SYSTEM ((uint32_t)0)
#define EFI_SHARED_KEY ((uint32_t)1)
#define EFI_FAST_BSS_TRANSITION ((uint32_t)2)
#define EFI_SAE ((uint32_t)3)

struct efi_80211_authenticate_data {
    struct efi_80211_mac_address bss_id;
    uint32_t auth_type;
    uint32_t failure_timeout;
    uint8_t *ft_content;
    uint8_t *sae_content;
    uint8_t *vendor_specific_info;
};

#define EFI_AUTHENTICATE_SUCCESS ((uint32_t)0)
#define EFI_AUTHENTICATE_REFUSED ((uint32_t)1)
#define EFI_AUTHENTICATE_ANTIC_LOGGING_TOKEN_REQUIRED ((uint32_t)2)
#define EFI_AUTHENTICATE_FINITE_CYCLIC_GROUP_NOT_SUPPORTED ((uint32_t)3)
#define EFI_AUTHENTICATION_REJECTED ((uint32_t)4)
#define EFI_AUTHENTICATE_INVALID_PARAMETER ((uint32_t)5)

struct efi_80211_authenticate_result {
    struct efi_80211_mac_address bss_id;
    uint8_t *ft_content;
    uint8_t *sae_content;
    uint8_t *vendor_specific_info;
};

// result is a pointer to a buffer the caller frees, as described (printed by
// value).
struct efi_80211_authenticate_data_token {
    efi_event event;
    efi_status status;
    struct efi_80211_authenticate_data *data;
    uint32_t result_code;
    struct efi_80211_authenticate_result *result;
};

typedef efi_status (EFI_API *efi_wireless_mac_connection_authenticate)(
    struct efi_wireless_mac_connection_protocol *self,
    struct efi_80211_authenticate_data_token *data
);

struct efi_80211_deauthenticate_data {
    struct efi_80211_mac_address bss_id;
    uint32_t reason_code;
    uint8_t *vendor_specific_info;
};

struct efi_80211_deauthenticate_data_token {
    efi_event event;
    efi_status status;
    struct efi_80211_deauthenticate_data *data;
};

typedef efi_status (EFI_API *efi_wireless_mac_connection_deauthenticate)(
    struct efi_wireless_mac_connection_protocol *self,
    struct efi_80211_deauthenticate_data_token *data
);

struct efi_wireless_mac_connection_protocol {
    efi_wireless_mac_connection_scan scan;
    efi_wireless_mac_connection_associate associate;
    efi_wireless_mac_connection_disassociate disassociate;
    efi_wireless_mac_connection_authenticate authenticate;
    efi_wireless_mac_connection_deauthenticate deauthenticate;
};

#define EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL_GUID \
    { 0x1b0fb9bf, 0x699d, 0x4fdd, { 0xa7, 0xc3, 0x25, 0x46, 0x68, 0x1b, 0xf6, 0x3b } }

struct efi_wireless_mac_connection_ii_protocol;

#define EFI_MAX_SSID_LEN 32

struct efi_80211_ssid {
    uint8_t ss_id_len;
    uint8_t ss_id[EFI_MAX_SSID_LEN];
};

struct efi_80211_get_networks_data {
    uint32_t num_of_ssid;
    struct efi_80211_ssid ssid_list[1];
};

struct efi_80211_suite_selector {
    uint8_t oui[3];
    uint8_t suite_type;
};

struct efi_80211_akm_suite_selector {
    uint16_t akm_suite_count;
    struct efi_80211_suite_selector akm_suite_list[1];
};

struct efi_80211_cipher_suite_selector {
    uint16_t cipher_suite_count;
    struct efi_80211_suite_selector cipher_suite_list[1];
};

struct efi_80211_network {
    uint32_t bss_type;
    struct efi_80211_ssid ss_id;
    struct efi_80211_akm_suite_selector *akm_suite;
    struct efi_80211_cipher_suite_selector *cipher_suite;
};

struct efi_80211_network_description {
    struct efi_80211_network network;
    uint8_t network_quality;
};

struct efi_80211_get_networks_result {
    uint8_t num_of_network_desc;
    struct efi_80211_network_description network_desc[1];
};

struct efi_80211_get_networks_token {
    efi_event event;
    efi_status status;
    struct efi_80211_get_networks_data *data;
    struct efi_80211_get_networks_result *result;
};

typedef efi_status (EFI_API *efi_wireless_mac_connection_ii_get_networks)(
    struct efi_wireless_mac_connection_ii_protocol *self,
    struct efi_80211_get_networks_token *token
);

struct efi_80211_connect_network_data {
    struct efi_80211_network *network;
    uint32_t failure_timeout;
};

#define EFI_CONNECT_SUCCESS ((uint32_t)0)
#define EFI_CONNECT_REFUSED ((uint32_t)1)
#define EFI_CONNECT_FAILED ((uint32_t)2)
#define EFI_CONNECT_FAILURE_TIMEOUT ((uint32_t)3)
#define EFI_CONNECT_FAILED_REASON_UNSPECIFIED ((uint32_t)4)

struct efi_80211_connect_network_token {
    efi_event event;
    efi_status status;
    struct efi_80211_connect_network_data *data;
    uint32_t result_code;
};

typedef efi_status (EFI_API *efi_wireless_mac_connection_ii_connect_network)(
    struct efi_wireless_mac_connection_ii_protocol *self,
    struct efi_80211_connect_network_token *token
);

struct efi_80211_disconnect_network_token {
    efi_event event;
    efi_status status;
};

typedef efi_status (EFI_API *efi_wireless_mac_connection_ii_disconnect_network)(
    struct efi_wireless_mac_connection_ii_protocol *self,
    struct efi_80211_disconnect_network_token *token
);

struct efi_wireless_mac_connection_ii_protocol {
    efi_wireless_mac_connection_ii_get_networks get_networks;
    efi_wireless_mac_connection_ii_connect_network connect_network;
    efi_wireless_mac_connection_ii_disconnect_network disconnect_network;
};

#define EFI_SUPPLICANT_SERVICE_BINDING_PROTOCOL_GUID \
    { 0x45bcd98e, 0x59ad, 0x4174, { 0x95, 0x46, 0x34, 0x4a, 0x7, 0x48, 0x58, 0x98 } }

#define EFI_SUPPLICANT_PROTOCOL_GUID \
    { 0x54fcc43e, 0xaa89, 0x4333, { 0x9a, 0x85, 0xcd, 0xea, 0x24, 0x5, 0x1e, 0x9e } }

struct efi_supplicant_protocol;

typedef efi_status (EFI_API *efi_supplicant_build_response_packet)(
    struct efi_supplicant_protocol *self,
    uint8_t *request_buffer,
    size_t request_buffer_size,
    uint8_t *buffer,
    size_t *buffer_size
);

struct efi_supplicant_fragment_data {
    uint32_t fragment_length;
    void *fragment_buffer;
};

#define EFI_SUPPLICANT_ENCRYPT ((uint32_t)0)
#define EFI_SUPPLICANT_DECRYPT ((uint32_t)1)

typedef efi_status (EFI_API *efi_supplicant_process_packet)(
    struct efi_supplicant_protocol *self,
    struct efi_supplicant_fragment_data **fragment_table,
    uint32_t *fragment_count,
    uint32_t crypt_mode
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
    uint8_t gtk_refresh;
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
    uint8_t key[EFI_MAX_KEY_LEN];
    uint8_t key_len;
    uint8_t key_id;
    uint32_t key_type;
    struct efi_80211_mac_address addr;
    uint8_t rsc[8];
    uint8_t rsc_len;
    uint8_t is_authenticator;
    struct efi_80211_suite_selector cipher_suite;
    uint32_t direction;
};

struct efi_supplicant_gtk_list {
    uint8_t gtk_count;
    struct efi_supplicant_key gtk_list[1];
};

typedef efi_status (EFI_API *efi_supplicant_set_data)(
    struct efi_supplicant_protocol *self,
    uint32_t data_type,
    void *data,
    size_t data_size
);

typedef efi_status (EFI_API *efi_supplicant_get_data)(
    struct efi_supplicant_protocol *self,
    uint32_t data_type,
    uint8_t *data,
    size_t *data_size
);

struct efi_supplicant_protocol {
    efi_supplicant_build_response_packet build_response_packet;
    efi_supplicant_process_packet process_packet;
    efi_supplicant_set_data set_data;
    efi_supplicant_get_data get_data;
};

#ifdef __cplusplus
}
#endif

#endif
