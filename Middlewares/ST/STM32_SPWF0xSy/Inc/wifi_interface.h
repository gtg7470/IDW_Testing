/**
  ******************************************************************************
  * @file    wifi_interface.h
  * @author  Central LAB 
  * @version V2.0.1
  * @date    17-May-2016
  * @brief   Header file for X-CUBE-WIFI1 API
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WIFI_INTERFACE_H
#define __WIFI_INTERFACE_H

#ifdef __cplusplus
 extern "C" {
#endif
   
/* Includes ------------------------------------------------------------------*/   
#include <stdint.h>
#include "stm32_spwf_wifi.h"
	 
   /** @addtogroup MIDDLEWARES
* @{
*/ 


/** @addtogroup  NUCLEO_WIFI_API 
  * @brief Wi-Fi_interface API
  * @{
  */ 


/** @addtogroup NUCLEO_WIFI_API_Private_Macros
  * @{
  */   
   
   
   /**
  * @}
  */


/** @addtogroup NUCLEO_WIFI_API_Private_Variables
  * @{
  */
/* Private variables ---------------------------------------------------------*/
   
   
/* Exported macro ------------------------------------------------------------*/
#define _ARG6(_0, _1, _2, _3, _4, _5, _6, ...) _6
#define NARG6(...) _ARG6(__VA_ARGS__, 6, 5, 4, 3, 2, 1, 0)
#define _FIVE_OR_SIX_ARGS_5(NAME, a, b, c, d, e) a, b, c, d, e, 1453727657
#define _FIVE_OR_SIX_ARGS_6(NAME, a, b, c, d, e, f) a, b, c, d, e, f
#define __FIVE_OR_SIX_ARGS(NAME, N, ...) _FIVE_OR_SIX_ARGS_ ## N (NAME, __VA_ARGS__)
#define _FIVE_OR_SIX_ARGS(NAME, N, ...) __FIVE_OR_SIX_ARGS(NAME, N, __VA_ARGS__)
#define FIVE_OR_SIX_ARGS(NAME, ...) NAME(_FIVE_OR_SIX_ARGS(NAME, NARG6(__VA_ARGS__), __VA_ARGS__))

//#define wifi_socket_client_security(...) FIVE_OR_SIX_ARGS(wifi_socket_client_security, __VA_ARGS__)

/* Exported constants --------------------------------------------------------*/
#define GPIO_IN                 "in"
#define GPIO_OUT                "out"

#define  GPIO_Off               '0'
#define  GPIO_Rising            'R'
#define  GPIO_Falling           'F'
#define  GPIO_Both              'B'
   
typedef enum
{ 
  GPIO_OFF      = 0,
  GPIO_ON,
} GpioWriteValue;

typedef enum
{ 
  GPIO_PIN0     = 0,
  GPIO_PIN1,
  GPIO_PIN2,
  GPIO_PIN3,
  GPIO_PIN4,
  GPIO_PIN5,
  GPIO_PIN6,
  GPIO_PIN7,
  GPIO_PIN8,
  GPIO_PIN9,
  GPIO_PIN10,
  GPIO_PIN11,
  GPIO_PIN12,
  GPIO_PIN13,
  GPIO_PIN14,
  GPIO_PIN15
} GpioPin;

typedef enum
{
  WIFI_FALSE         = 0,
  WIFI_TRUE          = 1,
  Undefine      = 0xFF
} wifi_bool;

typedef enum
{
  None          = 0, 
  WEP           = 1,
  WPA_Personal  = 2,
} WiFi_Priv_Mode;

/********** Wi-Fi Error *************/
typedef enum
{ 
  WiFi_MODULE_SUCCESS           = 0,
  WiFi_TIME_OUT_ERROR           = 1,  
  WiFi_MODULE_ERROR,
  WiFi_HAL_OK,
  WiFi_NOT_SUPPORTED,
  WiFi_NOT_READY,
  WiFi_SCAN_FAILED,
  WiFi_AT_CMD_BUSY,
  WiFi_SSID_ERROR,
  WiFi_SecKey_ERROR,
  WiFi_CONFIG_ERROR,
  WiFi_STA_MODE_ERROR,
  WiFi_AP_MODE_ERROR,
  WiFi_AT_CMD_RESP_ERROR,
  WiFi_AT_FILE_LENGTH_ERROR,
  WiFi_HAL_UART_ERROR,
  WiFi_IN_LOW_POWER_ERROR,
  WiFi_HW_FAILURE_ERROR,
  WiFi_HEAP_TOO_SMALL_WARNING,
  WiFi_STACK_OVERFLOW_ERROR,
  WiFi_HARD_FAULT_ERROR,
  WiFi_MALLOC_FAILED_ERROR,
  WiFi_INIT_ERROR,
  WiFi_POWER_SAVE_WARNING,
  WiFi_SIGNAL_LOW_WARNING,
  WiFi_JOIN_FAILED,
  WiFi_SCAN_BLEWUP,
  WiFi_START_FAILED_ERROR,
  WiFi_EXCEPTION_ERROR,
  WiFi_DE_AUTH,
  WiFi_DISASSOCIATION,
  WiFi_UNHANDLED_IND_ERROR,
  WiFi_RX_MGMT,
  WiFi_RX_DATA,
  WiFi_RX_UNK  
} WiFi_Status_t;

typedef enum
{
  WEB_SOCKET = 0x1,
  NET_SOCKET = 0x2
} WiFi_Socket_t;

typedef enum
{
  CLIENT_NET_SOCKET = 0x1,
  CLIENT_WEB_SOCKET = 0x2,
  SERVER_SOCKET
} Socket_type_t;

typedef enum
{
  NO_TYPE = 0x0,
  CONNECT = 0x1,
  SUBSCRIBE,
  PUBLISH,
  UNSUBSCRIBE,
  DISCONNECT,
} WiFi_Mqtt_t;

typedef enum
{
  wifi_active        = 0,
  wifi_reactive      = 1,
  wifi_sleep         = 2,
} power_mode;

typedef enum
{
  low           = 0,
  medium        = 1,
  high          = 2,
  max           = 3,
} tx_power_level;

typedef enum
{
  off           = 0,
  on            = 1,
  custom        = 2,
} dhcp_mode;

typedef struct
{
  uint8_t *certificate;
  uint32_t certificate_size;
} TLS_Certificate;

typedef struct
{  
  wifi_bool     wpa;
  wifi_bool     wpa2;
  wifi_bool     wps;
} wifi_security;

typedef struct
{  
  uint8_t       channel_num;
  int           rssi;                     
  char          ssid[30];  
  wifi_security sec_type;
} wifi_scan;

typedef struct
{  
  wifi_bool             ht_mode;
  power_mode            power;
  tx_power_level        power_level;
  dhcp_mode             dhcp;
  char*                 ip_addr;
  char*                 netmask_addr;
  char*                 gateway_addr;
  char*                 dns_addr;
  char*                 host_name;
  wifi_bool             web_server;
  char*                 ap_domain_name;
  char*                 ap_config_page_name;
  uint32_t              http_timeout;
  uint32_t              dhcp_timeout;
  uint8_t               wifi_region;     
  uint32_t              wifi_baud_rate;
  uint32_t              mcu_baud_rate;
} wifi_config;

/* Exported functions ------------------------------------------------------- */

#ifdef WIFI_USE_VCOM
void wifi_vcom(void);
#endif

#ifdef SPWF04
#define COUNT_PARAMS(...) NARG6(__VA_ARGS__)
#define wifi_socket_server_close(...) socket_server_close(COUNT_PARAMS(__VA_ARGS__),__VA_ARGS__ )
#endif

WiFi_Status_t   wifi_init(wifi_config* config);
WiFi_Status_t   wifi_restore(void);
WiFi_Status_t   wifi_enable(wifi_bool enable);
WiFi_Status_t   wifi_disconnect(void);
WiFi_Status_t   wifi_connect(char * ssid, char * sec_key, WiFi_Priv_Mode priv_mode);
WiFi_Status_t   wifi_ap_start(uint8_t * ssid, char * sec_key, uint8_t channel_num, WiFi_Priv_Mode priv_mode);
WiFi_Status_t   wifi_adhoc_create(uint8_t * ssid, WiFi_Priv_Mode priv_mode);
WiFi_Status_t   wifi_network_scan(wifi_scan *scan_result, uint16_t max_scan_number);
WiFi_Status_t   wifi_ping(uint8_t * hostname);
void            wifi_reset(void);

/******** Wi-Fi Socket Function **********/
WiFi_Status_t   wifi_socket_client_open(uint8_t * hostname, uint32_t port_number, uint8_t * protocol, uint8_t * sock_id);
WiFi_Status_t   wifi_socket_client_write(uint8_t sock_id, uint32_t DataLength,char * pData);
WiFi_Status_t   wifi_socket_client_close(uint8_t sock_close_id);
WiFi_Status_t   wifi_list_open_client_socket(void);
WiFi_Status_t   wifi_set_socket_certificates(TLS_Certificate ca_certificate, TLS_Certificate tls_certificate, TLS_Certificate certificate_key, TLS_Certificate client_domain, uint32_t tls_epoch_time);

/********* Wi-Fi Socket Server ********/
#ifdef SPWF04
WiFi_Status_t   wifi_socket_server_open(uint32_t port_number, uint8_t * protocol, uint8_t * sock_id);
WiFi_Status_t   wifi_socket_server_write(uint8_t server_id, uint8_t client_id, uint32_t DataLength,char * pData);
WiFi_Status_t   wifi_list_bound_client_socket(void);
#else
WiFi_Status_t   wifi_socket_server_open(uint32_t port_number, uint8_t * protocol);
WiFi_Status_t   wifi_socket_server_write(uint32_t DataLength,char * pData);
WiFi_Status_t   wifi_socket_server_close(void);
#endif

/******** Wi-Fi Web Socket Function **********/
WiFi_Status_t   wifi_websocket_client_open(uint8_t * hostname, uint32_t port_number, uint8_t * protocol, uint8_t * sock_id);
WiFi_Status_t   wifi_websocket_client_write(uint8_t sock_id, uint32_t DataLength,char * pData);
WiFi_Status_t   wifi_list_open_web_client_socket(void);
WiFi_Status_t   wifi_websocket_client_close(uint8_t sock_close_id);

/*** FileSystem Request ***********/
#if defined(SPWF04)
WiFi_Status_t   wifi_file_rename(char *FileName, char *Mod_FileName);
WiFi_Status_t   wifi_unmount_user_memory(int8_t volume, int8_t erase);

/*** MQTT Protocol ****************/
WiFi_Status_t   wifi_mqtt_connect(uint8_t * hostname, uint32_t port_num);
WiFi_Status_t   wifi_mqtt_publish(uint8_t *topic, uint32_t DataLength, char *pData);
WiFi_Status_t   wifi_mqtt_disconnect(void);
WiFi_Status_t   wifi_mqtt_subscribe(uint8_t *topic);
WiFi_Status_t   wifi_mqtt_unsubscribe(uint8_t *topic);

/*** TFTP File Request ***********/
WiFi_Status_t   wifi_tftp_get(uint8_t * hostname, uint32_t port_number, uint8_t * filename);
WiFi_Status_t   wifi_tftp_put(uint8_t * hostname, uint32_t port_number, uint8_t * filename);

/*** SMTP Protocol ***************/
WiFi_Status_t   wifi_send_mail(uint8_t *hostname, uint32_t port_num, uint8_t *from, uint8_t *to, uint8_t *subject, uint32_t length, char *Data);

#endif

/*** Input SSI ***************/
WiFi_Status_t   wifi_fill_input_buffer(uint32_t DataLength, char * Data);

WiFi_Status_t   wifi_file_list(void);
WiFi_Status_t   wifi_file_delete(char * FileName);
WiFi_Status_t   wifi_file_erase_external_flash(void);
WiFi_Status_t   wifi_file_create(char *FileName, uint16_t length, char *UserFileBuff);
WiFi_Status_t   wifi_file_image_create(uint8_t * HostName,uint8_t * FileName, uint32_t port_number);
WiFi_Status_t   wifi_file_print_content(uint8_t * FileName);

#if 0
WiFi_Status_t   wifi_file_print_content(uint8_t *FileName, int16_t offset, int16_t length);
#endif

/*** HTTP File Request ***********/
WiFi_Status_t   wifi_http_get(uint8_t * hostname, uint8_t * path, uint32_t port_number);
WiFi_Status_t   wifi_http_post(uint8_t * hostname, uint8_t * path, uint32_t port_number);

WiFi_Status_t   wifi_fw_update(uint8_t * hostname, uint8_t * filename_path, uint32_t port_number);

/*** Power Configuration **********/
WiFi_Status_t   wifi_standby(uint8_t arg_standby_time);
#ifdef SPWF04
WiFi_Status_t   wifi_powersave(power_mode mode);
#endif
WiFi_Status_t   wifi_wakeup(wifi_bool enable);

/*** GPIO Configuration **********/
uint8_t         wifi_gpio_init(GpioPin pin, char* dir, char irq);
uint8_t         wifi_gpio_read(GpioPin pin, uint8_t *val, uint8_t *dir);
uint8_t         wifi_gpio_write(GpioPin pin, GpioWriteValue value);

void            UART_Configuration(uint32_t baud_rate);
void            GPIO_Configuration(void);
void            Timer_Config(void);

WiFi_Status_t   socket_server_close(int count,...);

/****** Wi-Fi Status Variable Information *******/
WiFi_Status_t   wifi_get_IP_address(uint8_t *ip_addr);
WiFi_Status_t   wifi_get_MAC_address(uint8_t *mac_addr);
uint32_t        wifi_get_status_variable_value(uint8_t *status_variable_name, uint8_t *status_variable_value);

/******** Wi-Fi Indication User Callback: For User to implement *********/
void            ind_wifi_warning(WiFi_Status_t warning_code);
void            ind_wifi_error(WiFi_Status_t error_code);
void            ind_wifi_connection_error(WiFi_Status_t status_code);
void            ind_wifi_connected(void);
void            ind_wifi_ap_ready(void);
void            ind_wifi_ap_client_joined(uint8_t * client_mac_address);
void            ind_wifi_ap_client_left(uint8_t * client_mac_address);
void            ind_wifi_on(void);
void            ind_wifi_packet_lost(WiFi_Status_t status_code);
void            ind_wifi_gpio_changed(void);
void            ind_wifi_socket_data_received(int8_t server_id, int8_t socket_id, uint8_t * data_ptr, uint32_t message_size, uint32_t chunk_size, WiFi_Socket_t socket_type);
void            ind_wifi_socket_client_remote_server_closed(uint8_t * socketID, WiFi_Socket_t socket_type);
void            ind_wifi_socket_server_data_lost(void);
void            ind_socket_server_client_joined(void);
void            ind_socket_server_client_left(void);
void            ind_wifi_http_data_available(uint8_t * data_ptr,uint32_t message_size);
void            ind_wifi_file_data_available(uint8_t * data_ptr);
void            ind_wifi_socket_list_data_available(uint8_t * data_ptr);
void            ind_wifi_resuming(void);
void            ind_wifi_mqtt_data_received(uint8_t client_id, uint8_t *topic,uint32_t chunk_size,uint32_t message_size, uint32_t total_message_size, uint8_t *data_ptr);
void            ind_wifi_mqtt_closed(uint8_t client_id);
void            ind_wifi_inputssi_callback(void);
void            ind_wifi_output_from_remote_callback(uint8_t *data_ptr);


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
  
/**
  * @}
  */
  
#ifdef __cplusplus
  }
#endif
	
#endif /* __WIFI_INTERFACE_H */
