#ifndef EFI_EFIBLUETOOTH_H
#define EFI_EFIBLUETOOTH_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <efi/efidef.h>
#include <efi/efidevp.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_BLUETOOTH_HC_PROTOCOL_GUID \
    { 0xb3930571, 0xbeba, 0x4fc5, { 0x92, 0x3, 0x94, 0x27, 0x24, 0x2e, 0x6a, 0x43 } }

struct efi_bluetooth_hc_protocol;

typedef efi_status (EFI_API *efi_bluetooth_hc_send_command)(
    struct efi_bluetooth_hc_protocol *self,
    size_t *buffer_size,
    void *buffer,
    size_t timeout
);

typedef efi_status (EFI_API *efi_bluetooth_hc_receive_event)(
    struct efi_bluetooth_hc_protocol *self,
    size_t *buffer_size,
    void *buffer,
    size_t timeout
);

typedef efi_status (EFI_API *efi_bluetooth_hc_async_func_callback)(
    void *data,
    size_t data_length,
    void *context
);

typedef efi_status (EFI_API *efi_bluetooth_hc_async_receive_event)(
    struct efi_bluetooth_hc_protocol *self,
    bool is_new_transfer,
    size_t polling_interval,
    size_t data_length,
    efi_bluetooth_hc_async_func_callback callback,
    void *context
);

typedef efi_status (EFI_API *efi_bluetooth_hc_send_acl_data)(
    struct efi_bluetooth_hc_protocol *self,
    size_t *buffer_size,
    void *buffer,
    size_t timeout
);

typedef efi_status (EFI_API *efi_bluetooth_hc_receive_acl_data)(
    struct efi_bluetooth_hc_protocol *self,
    size_t *buffer_size,
    void *buffer,
    size_t timeout
);

typedef efi_status (EFI_API *efi_bluetooth_hc_async_receive_acl_data)(
    struct efi_bluetooth_hc_protocol *self,
    bool is_new_transfer,
    size_t polling_interval,
    size_t data_length,
    efi_bluetooth_hc_async_func_callback callback,
    void *context
);

typedef efi_status (EFI_API *efi_bluetooth_hc_send_sco_data)(
    struct efi_bluetooth_hc_protocol *self,
    size_t *buffer_size,
    void *buffer,
    size_t timeout
);

typedef efi_status (EFI_API *efi_bluetooth_hc_receive_sco_data)(
    struct efi_bluetooth_hc_protocol *self,
    size_t *buffer_size,
    void *buffer,
    size_t timeout
);

typedef efi_status (EFI_API *efi_bluetooth_hc_async_receive_sco_data)(
    struct efi_bluetooth_hc_protocol *self,
    bool is_new_transfer,
    size_t polling_interval,
    size_t data_length,
    efi_bluetooth_hc_async_func_callback callback,
    void *context
);

struct efi_bluetooth_hc_protocol {
    efi_bluetooth_hc_send_command send_command;
    efi_bluetooth_hc_receive_event receive_event;
    efi_bluetooth_hc_async_receive_event async_receive_event;
    efi_bluetooth_hc_send_acl_data send_acl_data;
    efi_bluetooth_hc_receive_acl_data receive_acl_data;
    efi_bluetooth_hc_async_receive_acl_data async_receive_acl_data;
    efi_bluetooth_hc_send_sco_data send_sco_data;
    efi_bluetooth_hc_receive_sco_data receive_sco_data;
    efi_bluetooth_hc_async_receive_sco_data async_receive_sco_data;
};

#define EFI_BLUETOOTH_IO_SERVICE_BINDING_PROTOCOL_GUID \
    { 0x388278d3, 0x7b85, 0x42f0, { 0xab, 0xa9, 0xfb, 0x4b, 0xfd, 0x69, 0xf5, 0xab } }

#define EFI_BLUETOOTH_IO_PROTOCOL_GUID \
    { 0x467313de, 0x4e30, 0x43f1, { 0x94, 0x3e, 0x32, 0x3f, 0x89, 0x84, 0x5d, 0xb5 } }

struct efi_bluetooth_io_protocol;

// Byte-packed as firmware lays it out: the 3-byte Bluetooth Class of Device.
struct efi_bluetooth_class_of_device {
    uint8_t minor;
    uint16_t major;
} __attribute__((__packed__));

#define EFI_BLUETOOTH_CLASS_OF_DEVICE_FORMAT_TYPE_SHIFT 0
#define EFI_BLUETOOTH_CLASS_OF_DEVICE_FORMAT_TYPE_MASK 0x03
#define EFI_BLUETOOTH_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_SHIFT 2
#define EFI_BLUETOOTH_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_MASK 0xfc
#define EFI_BLUETOOTH_CLASS_OF_DEVICE_MAJOR_DEVICE_CLASS_SHIFT 0
#define EFI_BLUETOOTH_CLASS_OF_DEVICE_MAJOR_DEVICE_CLASS_MASK 0x001f
#define EFI_BLUETOOTH_CLASS_OF_DEVICE_MAJOR_SERVICE_CLASS_SHIFT 5
#define EFI_BLUETOOTH_CLASS_OF_DEVICE_MAJOR_SERVICE_CLASS_MASK 0xffe0

struct efi_bluetooth_device_info {
    uint32_t version;
    struct efi_bluetooth_address bd_addr;
    uint8_t page_scan_repetition_mode;
    struct efi_bluetooth_class_of_device class_of_device;
    uint16_t clock_offset;
    uint8_t rssi;
    uint8_t extended_inquiry_response[240];
};

typedef efi_status (EFI_API *efi_bluetooth_io_get_device_info)(
    struct efi_bluetooth_io_protocol *self,
    size_t *device_info_size,
    void **device_info
);

typedef efi_status (EFI_API *efi_bluetooth_io_get_sdp_info)(
    struct efi_bluetooth_io_protocol *self,
    size_t *sdp_info_size,
    void **sdp_info
);

typedef efi_status (EFI_API *efi_bluetooth_io_l2cap_raw_send)(
    struct efi_bluetooth_io_protocol *self,
    size_t *buffer_size,
    void *buffer,
    size_t timeout
);

typedef efi_status (EFI_API *efi_bluetooth_io_l2cap_raw_receive)(
    struct efi_bluetooth_io_protocol *self,
    size_t *buffer_size,
    void *buffer,
    size_t timeout
);

typedef efi_status (EFI_API *efi_bluetooth_io_async_func_callback)(
    uint16_t channel_id,
    void *data,
    size_t data_length,
    void *context
);

typedef efi_status (EFI_API *efi_bluetooth_io_l2cap_raw_async_receive)(
    struct efi_bluetooth_io_protocol *self,
    bool is_new_transfer,
    size_t polling_interval,
    size_t data_length,
    efi_bluetooth_io_async_func_callback callback,
    void *context
);

typedef efi_status (EFI_API *efi_bluetooth_io_l2cap_send)(
    struct efi_bluetooth_io_protocol *self,
    efi_handle handle,
    size_t *buffer_size,
    void *buffer,
    size_t timeout
);

typedef efi_status (EFI_API *efi_bluetooth_io_l2cap_receive)(
    struct efi_bluetooth_io_protocol *self,
    efi_handle handle,
    size_t *buffer_size,
    void **buffer,
    size_t timeout
);

typedef efi_status (EFI_API *efi_bluetooth_io_channel_service_callback)(
    void *data,
    size_t data_length,
    void *context
);

typedef efi_status (EFI_API *efi_bluetooth_io_l2cap_async_receive)(
    struct efi_bluetooth_io_protocol *self,
    efi_handle handle,
    efi_bluetooth_io_channel_service_callback callback,
    void *context
);

typedef efi_status (EFI_API *efi_bluetooth_io_l2cap_connect)(
    struct efi_bluetooth_io_protocol *self,
    efi_handle *handle,
    uint16_t psm,
    uint16_t mtu,
    efi_bluetooth_io_channel_service_callback callback,
    void *context
);

typedef efi_status (EFI_API *efi_bluetooth_io_l2cap_disconnect)(
    struct efi_bluetooth_io_protocol *self,
    efi_handle handle
);

typedef efi_status (EFI_API *efi_bluetooth_io_l2cap_register_service)(
    struct efi_bluetooth_io_protocol *self,
    efi_handle *handle,
    uint16_t psm,
    uint16_t mtu,
    efi_bluetooth_io_channel_service_callback callback,
    void *context
);

struct efi_bluetooth_io_protocol {
    efi_bluetooth_io_get_device_info get_device_info;
    efi_bluetooth_io_get_sdp_info get_sdp_info;
    efi_bluetooth_io_l2cap_raw_send l2cap_raw_send;
    efi_bluetooth_io_l2cap_raw_receive l2cap_raw_receive;
    efi_bluetooth_io_l2cap_raw_async_receive l2cap_raw_async_receive;
    efi_bluetooth_io_l2cap_send l2cap_send;
    efi_bluetooth_io_l2cap_receive l2cap_receive;
    efi_bluetooth_io_l2cap_async_receive l2cap_async_receive;
    efi_bluetooth_io_l2cap_connect l2cap_connect;
    efi_bluetooth_io_l2cap_disconnect l2cap_disconnect;
    efi_bluetooth_io_l2cap_register_service l2cap_register_service;
};

#define EFI_BLUETOOTH_CONFIG_PROTOCOL_GUID \
    { 0x62960cf3, 0x40ff, 0x4263, { 0xa7, 0x7c, 0xdf, 0xde, 0xbd, 0x19, 0x1b, 0x4b } }

struct efi_bluetooth_config_protocol;

typedef efi_status (EFI_API *efi_bluetooth_config_init)(
    struct efi_bluetooth_config_protocol *self
);

#define EFI_BLUETOOTH_HCI_COMMAND_LOCAL_READABLE_NAME_MAX_SIZE 248

struct efi_bluetooth_scan_callback_information {
    struct efi_bluetooth_address bd_addr;
    uint8_t remote_device_state;
    struct efi_bluetooth_class_of_device class_of_device;
    uint8_t remote_device_name[EFI_BLUETOOTH_HCI_COMMAND_LOCAL_READABLE_NAME_MAX_SIZE];
};

typedef efi_status (EFI_API *efi_bluetooth_config_scan_callback_function)(
    struct efi_bluetooth_config_protocol *self,
    void *context,
    struct efi_bluetooth_scan_callback_information *callback_info
);

typedef efi_status (EFI_API *efi_bluetooth_config_scan)(
    struct efi_bluetooth_config_protocol *self,
    bool re_scan,
    uint8_t scan_type,
    efi_bluetooth_config_scan_callback_function callback,
    void *context
);

typedef efi_status (EFI_API *efi_bluetooth_config_connect)(
    struct efi_bluetooth_config_protocol *self,
    struct efi_bluetooth_address *bd_addr
);

// reason is a value, as described and as in the LE protocol; it is printed as
// uint8_t *reason.
typedef efi_status (EFI_API *efi_bluetooth_config_disconnect)(
    struct efi_bluetooth_config_protocol *self,
    struct efi_bluetooth_address *bd_addr,
    uint8_t reason
);

#define EFI_BLUETOOTH_CONFIG_DATA_TYPE_DEVICE_NAME ((uint32_t)0)
#define EFI_BLUETOOTH_CONFIG_DATA_TYPE_CLASS_OF_DEVICE ((uint32_t)1)
#define EFI_BLUETOOTH_CONFIG_DATA_TYPE_REMOTE_DEVICE_STATE ((uint32_t)2)
#define EFI_BLUETOOTH_CONFIG_DATA_TYPE_SDP_INFO ((uint32_t)3)
#define EFI_BLUETOOTH_CONFIG_DATA_TYPE_BDADDR ((uint32_t)4)
#define EFI_BLUETOOTH_CONFIG_DATA_TYPE_DISCOVERABLE ((uint32_t)5)
#define EFI_BLUETOOTH_CONFIG_DATA_TYPE_CONTROLLER_STORED_PAIRED_DEVICE_LIST ((uint32_t)6)
#define EFI_BLUETOOTH_CONFIG_DATA_TYPE_AVAILABLE_DEVICE_LIST ((uint32_t)7)
#define EFI_BLUETOOTH_CONFIG_DATA_TYPE_RANDOM_ADDRESS ((uint32_t)8)
#define EFI_BLUETOOTH_CONFIG_DATA_TYPE_RSSI ((uint32_t)9)
#define EFI_BLUETOOTH_CONFIG_DATA_TYPE_ADVERTISEMENT_DATA ((uint32_t)10)
#define EFI_BLUETOOTH_CONFIG_DATA_TYPE_IO_CAPABILITY ((uint32_t)11)
#define EFI_BLUETOOTH_CONFIG_DATA_TYPE_OOB_DATA_FLAG ((uint32_t)12)
#define EFI_BLUETOOTH_CONFIG_DATA_TYPE_KEY_TYPE ((uint32_t)13)
#define EFI_BLUETOOTH_CONFIG_DATA_TYPE_ENC_KEY_SIZE ((uint32_t)14)
#define EFI_BLUETOOTH_CONFIG_DATA_TYPE_MAX ((uint32_t)15)

typedef uint32_t efi_bluetooth_config_remote_device_state_type;

#define EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_CONNECTED 0x1
#define EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_PAIRED 0x2

#define EFI_BLUETOOTH_HCI_LINK_KEY_SIZE 16

typedef efi_status (EFI_API *efi_bluetooth_config_get_data)(
    struct efi_bluetooth_config_protocol *self,
    uint32_t data_type,
    size_t *data_size,
    void *data
);

typedef efi_status (EFI_API *efi_bluetooth_config_set_data)(
    struct efi_bluetooth_config_protocol *self,
    uint32_t data_type,
    size_t data_size,
    void *data
);

typedef efi_status (EFI_API *efi_bluetooth_config_get_remote_data)(
    struct efi_bluetooth_config_protocol *self,
    uint32_t data_type,
    struct efi_bluetooth_address *bd_addr,
    size_t *data_size,
    void *data
);

#define EFI_BLUETOOTH_CALLBACK_TYPE_USER_PASSKEY_NOTIFICATION ((uint32_t)0)
#define EFI_BLUETOOTH_CALLBACK_TYPE_USER_CONFIRMATION_REQUEST ((uint32_t)1)
#define EFI_BLUETOOTH_CALLBACK_TYPE_OOB_DATA_REQUEST ((uint32_t)2)
#define EFI_BLUETOOTH_CALLBACK_TYPE_PIN_CODE_REQUEST ((uint32_t)3)
#define EFI_BLUETOOTH_CALLBACK_TYPE_MAX ((uint32_t)4)

// Each parameter is printed with a leaked emphasis asterisk; these are the
// described types.
typedef efi_status (EFI_API *efi_bluetooth_config_register_pin_callback_function)(
    struct efi_bluetooth_config_protocol *self,
    void *context,
    uint32_t callback_type,
    void *input_buffer,
    size_t input_buffer_size,
    void **output_buffer,
    size_t *output_buffer_size
);

// callback is taken by value, like its siblings'; it is printed as a pointer
// to the function pointer type.
typedef efi_status (EFI_API *efi_bluetooth_config_register_pin_callback)(
    struct efi_bluetooth_config_protocol *self,
    efi_bluetooth_config_register_pin_callback_function callback,
    void *context
);

typedef efi_status (EFI_API *efi_bluetooth_config_register_get_link_key_callback_function)(
    struct efi_bluetooth_config_protocol *self,
    void *context,
    struct efi_bluetooth_address *bd_addr,
    uint8_t link_key[EFI_BLUETOOTH_HCI_LINK_KEY_SIZE]
);

typedef efi_status (EFI_API *efi_bluetooth_config_register_get_link_key_callback)(
    struct efi_bluetooth_config_protocol *self,
    efi_bluetooth_config_register_get_link_key_callback_function callback,
    void *context
);

typedef efi_status (EFI_API *efi_bluetooth_config_register_set_link_key_callback_function)(
    struct efi_bluetooth_config_protocol *self,
    void *context,
    struct efi_bluetooth_address *bd_addr,
    uint8_t link_key[EFI_BLUETOOTH_HCI_LINK_KEY_SIZE]
);

// callback is taken by value, like its siblings'; it is printed as a pointer
// to the function pointer type.
typedef efi_status (EFI_API *efi_bluetooth_config_register_set_link_key_callback)(
    struct efi_bluetooth_config_protocol *self,
    efi_bluetooth_config_register_set_link_key_callback_function callback,
    void *context
);

#define EFI_BLUETOOTH_CONN_CALLBACK_TYPE_DISCONNECTED ((uint32_t)0)
#define EFI_BLUETOOTH_CONN_CALLBACK_TYPE_CONNECTED ((uint32_t)1)
#define EFI_BLUETOOTH_CONN_CALLBACK_TYPE_AUTHENTICATED ((uint32_t)2)
#define EFI_BLUETOOTH_CONN_CALLBACK_TYPE_ENCRYPTED ((uint32_t)3)

typedef efi_status (EFI_API *efi_bluetooth_config_register_connect_complete_callback_function)(
    struct efi_bluetooth_config_protocol *self,
    void *context,
    uint32_t callback_type,
    struct efi_bluetooth_address *bd_addr,
    void *input_buffer,
    size_t input_buffer_size
);

typedef efi_status (EFI_API *efi_bluetooth_config_register_connect_complete_callback)(
    struct efi_bluetooth_config_protocol *self,
    efi_bluetooth_config_register_connect_complete_callback_function callback,
    void *context
);

struct efi_bluetooth_config_protocol {
    efi_bluetooth_config_init init;
    efi_bluetooth_config_scan scan;
    efi_bluetooth_config_connect connect;
    efi_bluetooth_config_disconnect disconnect;
    efi_bluetooth_config_get_data get_data;
    efi_bluetooth_config_set_data set_data;
    efi_bluetooth_config_get_remote_data get_remote_data;
    efi_bluetooth_config_register_pin_callback register_pin_callback;
    efi_bluetooth_config_register_get_link_key_callback register_get_link_key_callback;
    efi_bluetooth_config_register_set_link_key_callback register_set_link_key_callback;
    efi_bluetooth_config_register_connect_complete_callback
        register_link_connect_complete_callback;
};

#define EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL_GUID \
    { 0x898890e9, 0x84b2, 0x4f3a, { 0x8c, 0x58, 0xd8, 0x57, 0x78, 0x13, 0xe0, 0xac } }

struct efi_bluetooth_attribute_protocol;

typedef efi_status (EFI_API *efi_bluetooth_attribute_callback_function)(
    struct efi_bluetooth_attribute_protocol *self,
    void *data,
    size_t data_length,
    void *context
);

typedef efi_status (EFI_API *efi_bluetooth_attribute_send_request)(
    struct efi_bluetooth_attribute_protocol *self,
    void *data,
    size_t data_length,
    efi_bluetooth_attribute_callback_function callback,
    void *context
);

struct efi_bluetooth_attribute_callback_parameter_notification {
    uint16_t attribute_handle;
};

struct efi_bluetooth_attribute_callback_parameter_indication {
    uint16_t attribute_handle;
};

struct efi_bluetooth_attribute_callback_parameter {
    uint32_t version;
    uint8_t attribute_op_code;
    union {
        struct efi_bluetooth_attribute_callback_parameter_notification notification;
        struct efi_bluetooth_attribute_callback_parameter_indication indication;
    } parameter;
};

typedef efi_status (EFI_API *efi_bluetooth_attribute_register_for_server_notification)(
    struct efi_bluetooth_attribute_protocol *self,
    struct efi_bluetooth_attribute_callback_parameter *callback_parameter,
    efi_bluetooth_attribute_callback_function callback,
    void *context
);

// Byte-packed, as firmware lays out these attribute types; the print shows no
// packing.
struct efi_bluetooth_uuid {
    uint8_t length;
    union {
        uint16_t uuid16;
        uint32_t uuid32;
        uint8_t uuid128[16];
    } __attribute__((__packed__)) data;
} __attribute__((__packed__));

union efi_bluetooth_attribute_permission {
    struct {
        uint16_t read;
        uint16_t write;
    } __attribute__((__packed__)) permission;
    uint32_t data32;
} __attribute__((__packed__));

#define EFI_BLUETOOTH_ATTRIBUTE_PERMISSION_READABLE 0x0001
#define EFI_BLUETOOTH_ATTRIBUTE_PERMISSION_READ_ENCRYPTION 0x0002
#define EFI_BLUETOOTH_ATTRIBUTE_PERMISSION_READ_AUTHENTICATION 0x0004
#define EFI_BLUETOOTH_ATTRIBUTE_PERMISSION_READ_AUTHORIZATION 0x0008
#define EFI_BLUETOOTH_ATTRIBUTE_PERMISSION_READ_KEY_SIZE_SHIFT 4
#define EFI_BLUETOOTH_ATTRIBUTE_PERMISSION_READ_KEY_SIZE_MASK 0x01f0
#define EFI_BLUETOOTH_ATTRIBUTE_PERMISSION_WRITEABLE 0x0001
#define EFI_BLUETOOTH_ATTRIBUTE_PERMISSION_WRITE_ENCRYPTION 0x0002
#define EFI_BLUETOOTH_ATTRIBUTE_PERMISSION_WRITE_AUTHENTICATION 0x0004
#define EFI_BLUETOOTH_ATTRIBUTE_PERMISSION_WRITE_AUTHORIZATION 0x0008
#define EFI_BLUETOOTH_ATTRIBUTE_PERMISSION_WRITE_KEY_SIZE_SHIFT 4
#define EFI_BLUETOOTH_ATTRIBUTE_PERMISSION_WRITE_KEY_SIZE_MASK 0x01f0

struct efi_bluetooth_attribute_header {
    struct efi_bluetooth_uuid type;
    uint16_t length;
    uint16_t attribute_handle;
    union efi_bluetooth_attribute_permission attribute_permission;
} __attribute__((__packed__));

struct efi_bluetooth_gatt_primary_service_info {
    struct efi_bluetooth_attribute_header header;
    uint16_t end_group_handle;
    struct efi_bluetooth_uuid service_uuid;
} __attribute__((__packed__));

struct efi_bluetooth_gatt_include_service_info {
    struct efi_bluetooth_attribute_header header;
    uint16_t start_group_handle;
    uint16_t end_group_handle;
    struct efi_bluetooth_uuid service_uuid;
} __attribute__((__packed__));

struct efi_bluetooth_gatt_characteristic_info {
    struct efi_bluetooth_attribute_header header;
    uint8_t characteristic_properties;
    uint16_t characteristic_value_handle;
    struct efi_bluetooth_uuid characteristic_uuid;
} __attribute__((__packed__));

struct efi_bluetooth_gatt_characteristic_descriptor_info {
    struct efi_bluetooth_attribute_header header;
    struct efi_bluetooth_uuid characteristic_descriptor_uuid;
} __attribute__((__packed__));

typedef efi_status (EFI_API *efi_bluetooth_attribute_get_service_info)(
    struct efi_bluetooth_attribute_protocol *self,
    size_t *service_info_size,
    void **service_info
);

struct efi_bluetooth_le_device_info {
    uint32_t version;
    struct efi_bluetooth_le_address bd_addr;
    struct efi_bluetooth_le_address direct_address;
    uint8_t rssi;
    size_t advertisement_data_size;
    void *advertisement_data;
};

typedef efi_status (EFI_API *efi_bluetooth_attribute_get_device_info)(
    struct efi_bluetooth_attribute_protocol *self,
    size_t *device_info_size,
    void **device_info
);

struct efi_bluetooth_attribute_protocol {
    efi_bluetooth_attribute_send_request send_request;
    efi_bluetooth_attribute_register_for_server_notification register_for_server_notification;
    efi_bluetooth_attribute_get_service_info get_service_info;
    efi_bluetooth_attribute_get_device_info get_device_info;
};

#define EFI_BLUETOOTH_ATTRIBUTE_SERVICE_BINDING_PROTOCOL_GUID \
    { 0x5639867a, 0x8c8e, 0x408d, { 0xac, 0x2f, 0x4b, 0x61, 0xbd, 0xc0, 0xbb, 0xbb } }

#define EFI_BLUETOOTH_LE_CONFIG_PROTOCOL_GUID \
    { 0x8f76da58, 0x1f99, 0x4275, { 0xa4, 0xec, 0x47, 0x56, 0x51, 0x5b, 0x1c, 0xe8 } }

struct efi_bluetooth_le_config_protocol;

typedef efi_status (EFI_API *efi_bluetooth_le_config_init)(
    struct efi_bluetooth_le_config_protocol *self
);

struct efi_bluetooth_le_config_scan_parameter {
    uint32_t version;
    uint8_t scan_type;
    uint16_t scan_interval;
    uint16_t scan_window;
    uint8_t scanning_filter_policy;
    uint8_t advertisement_flag_filter;
};

struct efi_bluetooth_le_scan_callback_information {
    struct efi_bluetooth_le_address bd_addr;
    struct efi_bluetooth_le_address direct_address;
    uint8_t remote_device_state;
    int8_t rssi;
    size_t advertisement_data_size;
    void *advertisement_data;
};

typedef efi_status (EFI_API *efi_bluetooth_le_config_scan_callback_function)(
    struct efi_bluetooth_le_config_protocol *self,
    void *context,
    struct efi_bluetooth_le_scan_callback_information *callback_info
);

typedef efi_status (EFI_API *efi_bluetooth_le_config_scan)(
    struct efi_bluetooth_le_config_protocol *self,
    bool re_scan,
    uint32_t timeout,
    struct efi_bluetooth_le_config_scan_parameter *scan_parameter,
    efi_bluetooth_le_config_scan_callback_function callback,
    void *context
);

struct efi_bluetooth_le_config_connect_parameter {
    uint32_t version;
    uint16_t scan_interval;
    uint16_t scan_window;
    uint16_t conn_interval_min;
    uint16_t conn_interval_max;
    uint16_t conn_latency;
    uint16_t supervision_timeout;
};

typedef efi_status (EFI_API *efi_bluetooth_le_config_connect)(
    struct efi_bluetooth_le_config_protocol *self,
    bool auto_reconnect,
    bool do_bonding,
    struct efi_bluetooth_le_config_connect_parameter *connect_parameter,
    struct efi_bluetooth_le_address *bd_addr
);

typedef efi_status (EFI_API *efi_bluetooth_le_config_disconnect)(
    struct efi_bluetooth_le_config_protocol *self,
    struct efi_bluetooth_le_address *bd_addr,
    uint8_t reason
);

typedef efi_status (EFI_API *efi_bluetooth_le_config_get_data)(
    struct efi_bluetooth_le_config_protocol *self,
    uint32_t data_type,
    size_t *data_size,
    void *data
);

typedef efi_status (EFI_API *efi_bluetooth_le_config_set_data)(
    struct efi_bluetooth_le_config_protocol *self,
    uint32_t data_type,
    size_t data_size,
    void *data
);

typedef efi_status (EFI_API *efi_bluetooth_le_config_get_remote_data)(
    struct efi_bluetooth_le_config_protocol *self,
    uint32_t data_type,
    struct efi_bluetooth_le_address *bd_addr,
    size_t *data_size,
    void *data
);

#define EFI_BLUTOOTH_SMP_AUTHORIZATION_REQUEST_EVENT ((uint32_t)0)
#define EFI_BLUTOOTH_SMP_PASSKEY_READY_EVENT ((uint32_t)1)
#define EFI_BLUTOOTH_SMP_PASSKEY_REQUEST_EVENT ((uint32_t)2)
#define EFI_BLUTOOTH_SMP_OOB_DATA_REQUEST_EVENT ((uint32_t)3)
#define EFI_BLUTOOTH_SMP_NUMERIC_COMPARISON_EVENT ((uint32_t)4)

typedef efi_status (EFI_API *efi_bluetooth_le_smp_callback)(
    struct efi_bluetooth_le_config_protocol *self,
    void *context,
    struct efi_bluetooth_le_address *bd_addr,
    uint32_t event_data_type,
    size_t data_size,
    void *data
);

typedef efi_status (EFI_API *efi_bluetooth_le_config_register_smp_auth_callback)(
    struct efi_bluetooth_le_config_protocol *self,
    efi_bluetooth_le_smp_callback callback,
    void *context
);

typedef efi_status (EFI_API *efi_bluetooth_le_config_send_smp_auth_data)(
    struct efi_bluetooth_le_config_protocol *self,
    struct efi_bluetooth_le_address *bd_addr,
    uint32_t event_data_type,
    size_t data_size,
    void *data
);

#define EFI_BLUETOOTH_SMP_LOCAL_IR ((uint32_t)0)
#define EFI_BLUETOOTH_SMP_LOCAL_ER ((uint32_t)1)
#define EFI_BLUETOOTH_SMP_LOCAL_DHK ((uint32_t)2)
#define EFI_BLUETOOTH_SMP_KEYS_DISTRIBUTED ((uint32_t)0x1000)
#define EFI_BLUETOOTH_SMP_KEY_SIZE ((uint32_t)4097)
#define EFI_BLUETOOTH_SMP_KEY_TYPE ((uint32_t)4098)
#define EFI_BLUETOOTH_SMP_PEER_LTK ((uint32_t)4099)
#define EFI_BLUETOOTH_SMP_PEER_IRK ((uint32_t)4100)
#define EFI_BLUETOOTH_SMP_PEER_CSRK ((uint32_t)4101)
#define EFI_BLUETOOTH_SMP_PEER_RAND ((uint32_t)4102)
#define EFI_BLUETOOTH_SMP_PEER_EDIV ((uint32_t)4103)
#define EFI_BLUETOOTH_SMP_PEER_SIGN_COUNTER ((uint32_t)4104)
#define EFI_BLUETOOTH_SMP_LOCAL_LTK ((uint32_t)4105)
#define EFI_BLUETOOTH_SMP_LOCAL_IRK ((uint32_t)4106)
#define EFI_BLUETOOTH_SMP_LOCAL_CSRK ((uint32_t)4107)
#define EFI_BLUETOOTH_SMP_LOCAL_SIGN_COUNTER ((uint32_t)4108)
#define EFI_BLUETOOTH_SMP_LOCAL_DIV ((uint32_t)4109)
#define EFI_BLUETOOTH_SMP_PEER_ADDRESS_LIST ((uint32_t)4110)
#define EFI_BLUETOOTH_SMP_MAX ((uint32_t)4111)

typedef efi_status (EFI_API *efi_bluetooth_le_config_smp_get_data_callback)(
    struct efi_bluetooth_le_config_protocol *self,
    void *context,
    struct efi_bluetooth_le_address *bd_addr,
    uint32_t data_type,
    size_t *data_size,
    void *data
);

typedef efi_status (EFI_API *efi_bluetooth_le_config_register_smp_get_data_callback)(
    struct efi_bluetooth_le_config_protocol *self,
    efi_bluetooth_le_config_smp_get_data_callback callback,
    void *context
);

typedef efi_status (EFI_API *efi_bluetooth_le_config_smp_set_data_callback)(
    struct efi_bluetooth_le_config_protocol *self,
    void *context,
    struct efi_bluetooth_le_address *bd_addr,
    uint32_t type,
    size_t data_size,
    void *data
);

typedef efi_status (EFI_API *efi_bluetooth_le_config_register_smp_set_data_callback)(
    struct efi_bluetooth_le_config_protocol *self,
    efi_bluetooth_le_config_smp_set_data_callback callback,
    void *context
);

typedef efi_status (EFI_API *efi_bluetooth_le_config_connect_complete_callback)(
    struct efi_bluetooth_le_config_protocol *self,
    void *context,
    uint32_t callback_type,
    struct efi_bluetooth_le_address *bd_addr,
    void *input_buffer,
    size_t input_buffer_size
);

typedef efi_status (EFI_API *efi_bluetooth_le_config_register_connect_complete_callback)(
    struct efi_bluetooth_le_config_protocol *self,
    efi_bluetooth_le_config_connect_complete_callback callback,
    void *context
);

struct efi_bluetooth_le_config_protocol {
    efi_bluetooth_le_config_init init;
    efi_bluetooth_le_config_scan scan;
    efi_bluetooth_le_config_connect connect;
    efi_bluetooth_le_config_disconnect disconnect;
    efi_bluetooth_le_config_get_data get_data;
    efi_bluetooth_le_config_set_data set_data;
    efi_bluetooth_le_config_get_remote_data get_remote_data;
    efi_bluetooth_le_config_register_smp_auth_callback register_smp_auth_callback;
    efi_bluetooth_le_config_send_smp_auth_data send_smp_auth_data;
    efi_bluetooth_le_config_register_smp_get_data_callback register_smp_get_data_callback;
    efi_bluetooth_le_config_register_smp_set_data_callback register_smp_set_data_callback;
    efi_bluetooth_le_config_register_connect_complete_callback
        register_link_connect_complete_callback;
};

#ifdef __cplusplus
}
#endif

#endif
