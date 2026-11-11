#ifndef EFI_EFIUSB_H
#define EFI_EFIUSB_H 1

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

#define EFI_USB_DATA_IN ((uint32_t)0)
#define EFI_USB_DATA_OUT ((uint32_t)1)
#define EFI_USB_NO_DATA ((uint32_t)2)

#define EFI_USB_NOERROR 0x0000
#define EFI_USB_ERR_NOTEXECUTE 0x0001
#define EFI_USB_ERR_STALL 0x0002
#define EFI_USB_ERR_BUFFER 0x0004
#define EFI_USB_ERR_BABBLE 0x0008
#define EFI_USB_ERR_NAK 0x0010
#define EFI_USB_ERR_CRC 0x0020
#define EFI_USB_ERR_TIMEOUT 0x0040
#define EFI_USB_ERR_BITSTUFF 0x0080
#define EFI_USB_ERR_SYSTEM 0x0100

struct efi_usb_device_request {
    uint8_t request_type;
    uint8_t request;
    uint16_t value;
    uint16_t index;
    uint16_t length;
} __attribute__((__packed__));

typedef efi_status (EFI_API *efi_async_usb_transfer_callback)(
    void *data,
    size_t data_length,
    void *context,
    uint32_t status
);

#define EFI_USB2_HC_PROTOCOL_GUID \
    {0x3e745226, 0x9818, 0x45b6, {0xa2, 0xac, 0xd7, 0xcd, 0x0e, 0x8b, 0xa2, 0xbc}}

struct efi_usb2_hc_protocol;

#define EFI_USB_SPEED_FULL 0x0000
#define EFI_USB_SPEED_LOW 0x0001
#define EFI_USB_SPEED_HIGH 0x0002
#define EFI_USB_SPEED_SUPER 0x0003

typedef efi_status (EFI_API *efi_usb2_hc_protocol_get_capability)(
    struct efi_usb2_hc_protocol *self,
    uint8_t *max_speed,
    uint8_t *port_number,
    uint8_t *is_64_bit_capable
);

#define EFI_USB_HC_RESET_GLOBAL 0x0001
#define EFI_USB_HC_RESET_HOST_CONTROLLER 0x0002
#define EFI_USB_HC_RESET_GLOBAL_WITH_DEBUG 0x0004
#define EFI_USB_HC_RESET_HOST_WITH_DEBUG 0x0008

typedef efi_status (EFI_API *efi_usb2_hc_protocol_reset)(
    struct efi_usb2_hc_protocol *self,
    uint16_t attributes
);

#define EFI_USB_HC_STATE_HALT ((uint32_t)0)
#define EFI_USB_HC_STATE_OPERATIONAL ((uint32_t)1)
#define EFI_USB_HC_STATE_SUSPEND ((uint32_t)2)
#define EFI_USB_HC_STATE_MAXIMUM ((uint32_t)3)

typedef efi_status (EFI_API *efi_usb2_hc_protocol_get_state)(
    struct efi_usb2_hc_protocol *self,
    uint32_t *state
);

typedef efi_status (EFI_API *efi_usb2_hc_protocol_set_state)(
    struct efi_usb2_hc_protocol *self,
    uint32_t state
);

struct efi_usb2_hc_transaction_translator {
    uint8_t translator_hub_address;
    uint8_t translator_port_number;
};

typedef efi_status (EFI_API *efi_usb2_hc_protocol_control_transfer)(
    struct efi_usb2_hc_protocol *self,
    uint8_t device_address,
    uint8_t device_speed,
    size_t maximum_packet_length,
    struct efi_usb_device_request *request,
    uint32_t transfer_direction,
    void *data,
    size_t *data_length,
    uintptr_t time_out,
    struct efi_usb2_hc_transaction_translator *translator,
    uint32_t *transfer_result
);

/* The specification refers to this value but never prints it; it is the one firmware uses. */
#define EFI_USB_MAX_BULK_BUFFER_NUM 10

typedef efi_status (EFI_API *efi_usb2_hc_protocol_bulk_transfer)(
    struct efi_usb2_hc_protocol *self,
    uint8_t device_address,
    uint8_t end_point_address,
    uint8_t device_speed,
    size_t maximum_packet_length,
    uint8_t data_buffers_number,
    void *data[EFI_USB_MAX_BULK_BUFFER_NUM],
    size_t *data_length,
    uint8_t *data_toggle,
    uintptr_t time_out,
    struct efi_usb2_hc_transaction_translator *translator,
    uint32_t *transfer_result
);

typedef efi_status (EFI_API *efi_usb2_hc_protocol_async_interrupt_transfer)(
    struct efi_usb2_hc_protocol *self,
    uint8_t device_address,
    uint8_t end_point_address,
    uint8_t device_speed,
    size_t maximum_packet_length,
    bool is_new_transfer,
    uint8_t *data_toggle,
    uintptr_t polling_interval,
    size_t data_length,
    struct efi_usb2_hc_transaction_translator *translator,
    efi_async_usb_transfer_callback call_back_function,
    void *context
);

typedef efi_status (EFI_API *efi_usb2_hc_protocol_sync_interrupt_transfer)(
    struct efi_usb2_hc_protocol *self,
    uint8_t device_address,
    uint8_t end_point_address,
    uint8_t device_speed,
    size_t maximum_packet_length,
    void *data,
    size_t *data_length,
    uint8_t *data_toggle,
    uintptr_t time_out,
    struct efi_usb2_hc_transaction_translator *translator,
    uint32_t *transfer_result
);

#define EFI_USB_MAX_ISO_BUFFER_NUM 7
#define EFI_USB_MAX_ISO_BUFFER_NUM1 2

typedef efi_status (EFI_API *efi_usb2_hc_protocol_isochronous_transfer)(
    struct efi_usb2_hc_protocol *self,
    uint8_t device_address,
    uint8_t end_point_address,
    uint8_t device_speed,
    size_t maximum_packet_length,
    uint8_t data_buffers_number,
    void *data[EFI_USB_MAX_ISO_BUFFER_NUM],
    size_t data_length,
    struct efi_usb2_hc_transaction_translator *translator,
    uint32_t *transfer_result
);

typedef efi_status (EFI_API *efi_usb2_hc_protocol_async_isochronous_transfer)(
    struct efi_usb2_hc_protocol *self,
    uint8_t device_address,
    uint8_t end_point_address,
    uint8_t device_speed,
    size_t maximum_packet_length,
    uint8_t data_buffers_number,
    void *data[EFI_USB_MAX_ISO_BUFFER_NUM],
    size_t data_length,
    struct efi_usb2_hc_transaction_translator *translator,
    efi_async_usb_transfer_callback isochronous_call_back,
    void *context
);

struct efi_usb_port_status {
    uint16_t port_status;
    uint16_t port_change_status;
};

#define EFI_USB_PORT_STAT_CONNECTION 0x0001
#define EFI_USB_PORT_STAT_ENABLE 0x0002
#define EFI_USB_PORT_STAT_SUSPEND 0x0004
#define EFI_USB_PORT_STAT_OVERCURRENT 0x0008
#define EFI_USB_PORT_STAT_RESET 0x0010
#define EFI_USB_PORT_STAT_POWER 0x0100
#define EFI_USB_PORT_STAT_LOW_SPEED 0x0200
#define EFI_USB_PORT_STAT_HIGH_SPEED 0x0400
#define EFI_USB_PORT_STAT_SUPER_SPEED 0x0800
#define EFI_USB_PORT_STAT_OWNER 0x2000

#define EFI_USB_PORT_STAT_C_CONNECTION 0x0001
#define EFI_USB_PORT_STAT_C_ENABLE 0x0002
#define EFI_USB_PORT_STAT_C_SUSPEND 0x0004
#define EFI_USB_PORT_STAT_C_OVERCURRENT 0x0008
#define EFI_USB_PORT_STAT_C_RESET 0x0010

typedef efi_status (EFI_API *efi_usb2_hc_protocol_get_roothub_port_status)(
    struct efi_usb2_hc_protocol *self,
    uint8_t port_number,
    struct efi_usb_port_status *port_status
);

#define EFI_USB_PORT_ENABLE ((uint32_t)1)
#define EFI_USB_PORT_SUSPEND ((uint32_t)2)
#define EFI_USB_PORT_RESET ((uint32_t)4)
#define EFI_USB_PORT_POWER ((uint32_t)8)
#define EFI_USB_PORT_OWNER ((uint32_t)13)
#define EFI_USB_PORT_CONNECT_CHANGE ((uint32_t)16)
#define EFI_USB_PORT_ENABLE_CHANGE ((uint32_t)17)
#define EFI_USB_PORT_SUSPEND_CHANGE ((uint32_t)18)
#define EFI_USB_PORT_OVER_CURRENT_CHANGE ((uint32_t)19)
#define EFI_USB_PORT_RESET_CHANGE ((uint32_t)20)

typedef efi_status (EFI_API *efi_usb2_hc_protocol_set_roothub_port_feature)(
    struct efi_usb2_hc_protocol *self,
    uint8_t port_number,
    uint32_t port_feature
);

typedef efi_status (EFI_API *efi_usb2_hc_protocol_clear_roothub_port_feature)(
    struct efi_usb2_hc_protocol *self,
    uint8_t port_number,
    uint32_t port_feature
);

/* The specification's structure body types sync_interrupt_transfer as the asynchronous call. */
struct efi_usb2_hc_protocol {
    efi_usb2_hc_protocol_get_capability get_capability;
    efi_usb2_hc_protocol_reset reset;
    efi_usb2_hc_protocol_get_state get_state;
    efi_usb2_hc_protocol_set_state set_state;
    efi_usb2_hc_protocol_control_transfer control_transfer;
    efi_usb2_hc_protocol_bulk_transfer bulk_transfer;
    efi_usb2_hc_protocol_async_interrupt_transfer async_interrupt_transfer;
    efi_usb2_hc_protocol_sync_interrupt_transfer sync_interrupt_transfer;
    efi_usb2_hc_protocol_isochronous_transfer isochronous_transfer;
    efi_usb2_hc_protocol_async_isochronous_transfer async_isochronous_transfer;
    efi_usb2_hc_protocol_get_roothub_port_status get_root_hub_port_status;
    efi_usb2_hc_protocol_set_roothub_port_feature set_root_hub_port_feature;
    efi_usb2_hc_protocol_clear_roothub_port_feature clear_root_hub_port_feature;
    uint16_t major_revision;
    uint16_t minor_revision;
};

#define EFI_USB_IO_PROTOCOL_GUID \
    {0x2B2F68D6, 0x0CD2, 0x44cf, {0x8E, 0x8B, 0xBB, 0xA2, 0x0B, 0x1B, 0x5B, 0x75}}

struct efi_usb_io_protocol;

typedef efi_status (EFI_API *efi_usb_io_control_transfer)(
    struct efi_usb_io_protocol *self,
    struct efi_usb_device_request *request,
    uint32_t direction,
    uint32_t timeout,
    void *data,
    size_t data_length,
    uint32_t *status
);

typedef efi_status (EFI_API *efi_usb_io_bulk_transfer)(
    struct efi_usb_io_protocol *self,
    uint8_t device_endpoint,
    void *data,
    size_t *data_length,
    uintptr_t timeout,
    uint32_t *status
);

typedef efi_status (EFI_API *efi_usb_io_async_interrupt_transfer)(
    struct efi_usb_io_protocol *self,
    uint8_t device_endpoint,
    bool is_new_transfer,
    uintptr_t polling_interval,
    size_t data_length,
    efi_async_usb_transfer_callback interrupt_call_back,
    void *context
);

typedef efi_status (EFI_API *efi_usb_io_sync_interrupt_transfer)(
    struct efi_usb_io_protocol *self,
    uint8_t device_endpoint,
    void *data,
    size_t *data_length,
    uintptr_t timeout,
    uint32_t *status
);

typedef efi_status (EFI_API *efi_usb_io_isochronous_transfer)(
    struct efi_usb_io_protocol *self,
    uint8_t device_endpoint,
    void *data,
    size_t data_length,
    uint32_t *status
);

typedef efi_status (EFI_API *efi_usb_io_async_isochronous_transfer)(
    struct efi_usb_io_protocol *self,
    uint8_t device_endpoint,
    void *data,
    size_t data_length,
    efi_async_usb_transfer_callback isochronous_call_back,
    void *context
);

struct efi_usb_device_descriptor {
    uint8_t length;
    uint8_t descriptor_type;
    uint16_t bcd_usb;
    uint8_t device_class;
    uint8_t device_sub_class;
    uint8_t device_protocol;
    uint8_t max_packet_size0;
    uint16_t id_vendor;
    uint16_t id_product;
    uint16_t bcd_device;
    uint8_t str_manufacturer;
    uint8_t str_product;
    uint8_t str_serial_number;
    uint8_t num_configurations;
} __attribute__((__packed__));

typedef efi_status (EFI_API *efi_usb_io_get_device_descriptor)(
    struct efi_usb_io_protocol *self,
    struct efi_usb_device_descriptor *device_descriptor
);

struct efi_usb_config_descriptor {
    uint8_t length;
    uint8_t descriptor_type;
    uint16_t total_length;
    uint8_t num_interfaces;
    uint8_t configuration_value;
    uint8_t configuration;
    uint8_t attributes;
    uint8_t max_power;
} __attribute__((__packed__));

typedef efi_status (EFI_API *efi_usb_io_get_config_descriptor)(
    struct efi_usb_io_protocol *self,
    struct efi_usb_config_descriptor *configuration_descriptor
);

struct efi_usb_interface_descriptor {
    uint8_t length;
    uint8_t descriptor_type;
    uint8_t interface_number;
    uint8_t alternate_setting;
    uint8_t num_endpoints;
    uint8_t interface_class;
    uint8_t interface_sub_class;
    uint8_t interface_protocol;
    uint8_t interface;
} __attribute__((__packed__));

typedef efi_status (EFI_API *efi_usb_io_get_interface_descriptor)(
    struct efi_usb_io_protocol *self,
    struct efi_usb_interface_descriptor *interface_descriptor
);

struct efi_usb_endpoint_descriptor {
    uint8_t length;
    uint8_t descriptor_type;
    uint8_t endpoint_address;
    uint8_t attributes;
    uint16_t max_packet_size;
    uint8_t interval;
} __attribute__((__packed__));

typedef efi_status (EFI_API *efi_usb_io_get_endpoint_descriptor)(
    struct efi_usb_io_protocol *self,
    uint8_t endpoint_index,
    struct efi_usb_endpoint_descriptor *endpoint_descriptor
);

typedef efi_status (EFI_API *efi_usb_io_get_string_descriptor)(
    struct efi_usb_io_protocol *self,
    uint16_t lang_id,
    uint8_t string_id,
    uint16_t **string
);

typedef efi_status (EFI_API *efi_usb_io_get_supported_languages)(
    struct efi_usb_io_protocol *self,
    uint16_t **lang_id_table,
    uint16_t *table_size
);

typedef efi_status (EFI_API *efi_usb_io_port_reset)(struct efi_usb_io_protocol *self);

/* The specification's structure body misspells the type of usb_sync_interrupt_transfer. */
struct efi_usb_io_protocol {
    efi_usb_io_control_transfer usb_control_transfer;
    efi_usb_io_bulk_transfer usb_bulk_transfer;
    efi_usb_io_async_interrupt_transfer usb_async_interrupt_transfer;
    efi_usb_io_sync_interrupt_transfer usb_sync_interrupt_transfer;
    efi_usb_io_isochronous_transfer usb_isochronous_transfer;
    efi_usb_io_async_isochronous_transfer usb_async_isochronous_transfer;
    efi_usb_io_get_device_descriptor usb_get_device_descriptor;
    efi_usb_io_get_config_descriptor usb_get_config_descriptor;
    efi_usb_io_get_interface_descriptor usb_get_interface_descriptor;
    efi_usb_io_get_endpoint_descriptor usb_get_endpoint_descriptor;
    efi_usb_io_get_string_descriptor usb_get_string_descriptor;
    efi_usb_io_get_supported_languages usb_get_supported_languages;
    efi_usb_io_port_reset usb_port_reset;
};

#define EFI_USBFN_IO_PROTOCOL_GUID \
    {0x32d2963a, 0xfe5d, 0x4f30, {0xb6, 0x33, 0x6e, 0x5d, 0xc5, 0x58, 0x3, 0xcc}}

#define EFI_USBFN_IO_PROTOCOL_REVISION 0x00010001

struct efi_usbfn_io_protocol;

#define EFI_USB_UNKNOWN_PORT ((uint32_t)0)
#define EFI_USB_STANDARD_DOWNSTREAM_PORT ((uint32_t)1)
#define EFI_USB_CHARGING_DOWNSTREAM_PORT ((uint32_t)2)
#define EFI_USB_DEDICATED_CHARGING_PORT ((uint32_t)3)
#define EFI_USB_INVALID_DEDICATED_CHARGING_PORT ((uint32_t)4)

typedef efi_status (EFI_API *efi_usbfn_io_detect_port)(
    struct efi_usbfn_io_protocol *self,
    uint32_t *port_type
);

struct efi_usb_interface_info {
    struct efi_usb_interface_descriptor *interface_descriptor;
    struct efi_usb_endpoint_descriptor **endpoint_descriptor_table;
};

struct efi_usb_config_info {
    struct efi_usb_config_descriptor *config_descriptor;
    struct efi_usb_interface_info **interface_info_table;
};

struct efi_usb_device_info {
    struct efi_usb_device_descriptor *device_descriptor;
    struct efi_usb_config_info **config_info_table;
};

typedef efi_status (EFI_API *efi_usbfn_io_configure_enable_endpoints)(
    struct efi_usbfn_io_protocol *self,
    struct efi_usb_device_info *device_info
);

/* No isochronous (0x01) or interrupt (0x03) type: the protocol supports neither. */
#define EFI_USB_ENDPOINT_CONTROL ((uint32_t)0x00)
#define EFI_USB_ENDPOINT_BULK ((uint32_t)0x02)

#define EFI_USB_BUS_SPEED_UNKNOWN ((uint32_t)0)
#define EFI_USB_BUS_SPEED_LOW ((uint32_t)1)
#define EFI_USB_BUS_SPEED_FULL ((uint32_t)2)
#define EFI_USB_BUS_SPEED_HIGH ((uint32_t)3)
#define EFI_USB_BUS_SPEED_SUPER ((uint32_t)4)
#define EFI_USB_BUS_SPEED_MAXIMUM EFI_USB_BUS_SPEED_SUPER

typedef efi_status (EFI_API *efi_usbfn_io_get_endpoint_maxpacket_size)(
    struct efi_usbfn_io_protocol *self,
    uint32_t endpoint_type,
    uint32_t bus_speed,
    uint16_t *max_packet_size
);

#define EFI_USB_DEVICE_INFO_UNKNOWN ((uint32_t)0)
#define EFI_USB_DEVICE_INFO_SERIAL_NUMBER ((uint32_t)1)
#define EFI_USB_DEVICE_INFO_MANUFACTURER_NAME ((uint32_t)2)
#define EFI_USB_DEVICE_INFO_PRODUCT_NAME ((uint32_t)3)

typedef efi_status (EFI_API *efi_usbfn_io_get_device_info)(
    struct efi_usbfn_io_protocol *self,
    uint32_t id,
    size_t *buffer_size,
    void *buffer
);

typedef efi_status (EFI_API *efi_usbfn_io_get_vendor_id_product_id)(
    struct efi_usbfn_io_protocol *self,
    uint16_t *vid,
    uint16_t *pid
);

#define EFI_USB_ENDPOINT_DIRECTION_HOST_OUT ((uint32_t)0)
#define EFI_USB_ENDPOINT_DIRECTION_HOST_IN ((uint32_t)1)
#define EFI_USB_ENDPOINT_DIRECTION_DEVICE_TX EFI_USB_ENDPOINT_DIRECTION_HOST_IN
#define EFI_USB_ENDPOINT_DIRECTION_DEVICE_RX EFI_USB_ENDPOINT_DIRECTION_HOST_OUT

typedef efi_status (EFI_API *efi_usbfn_io_abort_transfer)(
    struct efi_usbfn_io_protocol *self,
    uint8_t endpoint_index,
    uint32_t direction
);

typedef efi_status (EFI_API *efi_usbfn_io_get_endpoint_stall_state)(
    struct efi_usbfn_io_protocol *self,
    uint8_t endpoint_index,
    uint32_t direction,
    bool *state
);

typedef efi_status (EFI_API *efi_usbfn_io_set_endpoint_stall_state)(
    struct efi_usbfn_io_protocol *self,
    uint8_t endpoint_index,
    uint32_t direction,
    bool state
);

#define EFI_USB_MSG_NONE ((uint32_t)0)
#define EFI_USB_MSG_SETUP_PACKET ((uint32_t)1)
#define EFI_USB_MSG_ENDPOINT_STATUS_CHANGED_RX ((uint32_t)2)
#define EFI_USB_MSG_ENDPOINT_STATUS_CHANGED_TX ((uint32_t)3)
#define EFI_USB_MSG_BUS_EVENT_DETACH ((uint32_t)4)
#define EFI_USB_MSG_BUS_EVENT_ATTACH ((uint32_t)5)
#define EFI_USB_MSG_BUS_EVENT_RESET ((uint32_t)6)
#define EFI_USB_MSG_BUS_EVENT_SUSPEND ((uint32_t)7)
#define EFI_USB_MSG_BUS_EVENT_RESUME ((uint32_t)8)
#define EFI_USB_MSG_BUS_EVENT_SPEED ((uint32_t)9)

#define EFI_USB_TRANSFER_STATUS_UNKNOWN ((uint32_t)0)
#define EFI_USB_TRANSFER_STATUS_COMPLETE ((uint32_t)1)
#define EFI_USB_TRANSFER_STATUS_ABORTED ((uint32_t)2)
#define EFI_USB_TRANSFER_STATUS_ACTIVE ((uint32_t)3)
#define EFI_USB_TRANSFER_STATUS_NONE ((uint32_t)4)

struct efi_usbfn_transfer_result {
    size_t bytes_transferred;
    uint32_t transfer_status;
    uint8_t endpoint_index;
    uint32_t direction;
    void *buffer;
};

union efi_usbfn_message_payload {
    struct efi_usb_device_request udr;
    struct efi_usbfn_transfer_result utr;
    uint32_t ubs;
};

typedef efi_status (EFI_API *efi_usbfn_io_eventhandler)(
    struct efi_usbfn_io_protocol *self,
    uint32_t *message,
    size_t *payload_size,
    union efi_usbfn_message_payload *payload
);

typedef efi_status (EFI_API *efi_usbfn_io_transfer)(
    struct efi_usbfn_io_protocol *self,
    uint8_t endpoint_index,
    uint32_t direction,
    size_t *buffer_size,
    void *buffer
);

typedef efi_status (EFI_API *efi_usbfn_io_get_maxtransfer_size)(
    struct efi_usbfn_io_protocol *self,
    size_t *max_transfer_size
);

typedef efi_status (EFI_API *efi_usbfn_io_allocate_transfer_buffer)(
    struct efi_usbfn_io_protocol *self,
    size_t size,
    void **buffer
);

typedef efi_status (EFI_API *efi_usbfn_io_free_transfer_buffer)(
    struct efi_usbfn_io_protocol *self,
    void *buffer
);

typedef efi_status (EFI_API *efi_usbfn_io_start_controller)(struct efi_usbfn_io_protocol *self);

typedef efi_status (EFI_API *efi_usbfn_io_stop_controller)(struct efi_usbfn_io_protocol *self);

#define EFI_USB_POLICY_UNDEFINED ((uint32_t)0)
#define EFI_USB_POLICY_MAX_TRANSACTION_SIZE ((uint32_t)1)
#define EFI_USB_POLICY_ZERO_LENGTH_TERMINATION_SUPPORT ((uint32_t)2)
#define EFI_USB_POLICY_ZERO_LENGTH_TERMINATION ((uint32_t)3)

/* Named as the protocol structure names them; the prototypes print these two without _IO. */
typedef efi_status (EFI_API *efi_usbfn_io_set_endpoint_policy)(
    struct efi_usbfn_io_protocol *self,
    uint8_t endpoint_index,
    uint32_t direction,
    uint32_t policy_type,
    size_t buffer_size,
    void *buffer
);

typedef efi_status (EFI_API *efi_usbfn_io_get_endpoint_policy)(
    struct efi_usbfn_io_protocol *self,
    uint8_t endpoint_index,
    uint32_t direction,
    uint32_t policy_type,
    size_t *buffer_size,
    void *buffer
);

struct efi_usbfn_io_protocol {
    uint32_t revision;
    efi_usbfn_io_detect_port detect_port;
    efi_usbfn_io_configure_enable_endpoints configure_enable_endpoints;
    efi_usbfn_io_get_endpoint_maxpacket_size get_endpoint_max_packet_size;
    efi_usbfn_io_get_device_info get_device_info;
    efi_usbfn_io_get_vendor_id_product_id get_vendor_id_product_id;
    efi_usbfn_io_abort_transfer abort_transfer;
    efi_usbfn_io_get_endpoint_stall_state get_endpoint_stall_state;
    efi_usbfn_io_set_endpoint_stall_state set_endpoint_stall_state;
    efi_usbfn_io_eventhandler event_handler;
    efi_usbfn_io_transfer transfer;
    efi_usbfn_io_get_maxtransfer_size get_max_transfer_size;
    efi_usbfn_io_allocate_transfer_buffer allocate_transfer_buffer;
    efi_usbfn_io_free_transfer_buffer free_transfer_buffer;
    efi_usbfn_io_start_controller start_controller;
    efi_usbfn_io_stop_controller stop_controller;
    efi_usbfn_io_set_endpoint_policy set_endpoint_policy;
    efi_usbfn_io_get_endpoint_policy get_endpoint_policy;
};

#ifdef __cplusplus
}
#endif

#endif
