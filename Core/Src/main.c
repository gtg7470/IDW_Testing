/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
#include "stdio.h"
#include "string.h"
#include "wifi_module.h"
#include "wifi_globals.h"
#include "wifi_interface.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MAX_MSG_SIZE 100
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
WiFi_Status_t wifi_get_AP_settings(void);
uint8_t user_buffer[1024];
__IO char http_char;
wifi_bool http_post_request = WIFI_FALSE;

uint8_t cin[1], console_count=0;
char console_ssid[40];
char console_psk[20];
char console_host[20];
wifi_bool set_AP_config = WIFI_FALSE;

/* Private functions ---------------------------------------------------------*/
void  SystemClock_Config(void);
void  UART_Msg_Gpio_Init(void);
void  USART_PRINT_MSG_Configuration(UART_HandleTypeDef *UART_MsgHandle, uint32_t baud_rate);
WiFi_Status_t wifi_get_AP_settings(void);
void print(char msg[]);
/* Private Declarartion ------------------------------------------------------*/
__IO wifi_state_t wifi_state;
wifi_config config;
UART_HandleTypeDef UART_MsgHandle;

char * ssid = "Grimm";
char * seckey = "aad089f19eb3e374cd436f9adc99a4d8210b14eec9621d8d50110797039cf906";
WiFi_Priv_Mode mode = WPA_Personal;
char * hostname = "httpbin.org";
char * post_hostname = "posttestserver.com";
char * gcfg_key1 = "ip_ipaddr";
char * gcfg_key2 = "nv_model";

char wifi_ip_addr[20];
uint32_t baud_rate = 115200;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */

 /**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	
  WiFi_Status_t status = WiFi_MODULE_SUCCESS;

  char * path = "/get";
  uint32_t  port_num = 80;
  char * post_path = "/post.php/name=demo&email=mymail&subject=subj&body=message";

  HAL_Init();
  SystemClock_Config();


  MX_GPIO_Init();
  MX_USART2_UART_Init();
  
  RetargetInit(&huart2);
  
  printf("UART Init complete!\r\n");
  /*while (1)
  {
    print("Hello world\r\n..");
  }*/
  /* USER CODE END 3 */

  status = wifi_get_AP_settings();
  if(status!=WiFi_MODULE_SUCCESS)
  {
    printf("Error in AP Settings\r\n");
    return 0;
  }
 
  printf("Wifi settings init complete!\r\n");
  printf("SSID: %s PASSCODE %s\r\n", console_ssid, console_psk);
  //UART_Configuration(baud_rate); 
  
  config.power=wifi_active;
  config.power_level=high;
  config.dhcp=on;//use DHCP IP address   
  config.mcu_baud_rate = baud_rate;
  wifi_state = wifi_state_idle;
  
  printf("Initializing the wifi module...\r\n");
  
  /* Init the wi-fi module */  
  status = wifi_init(&config);
  if(status!=WiFi_MODULE_SUCCESS)
  {
    printf("Error in Config\r\n");
    return 0;
  }
  
  printf("Init success, state code: %d\r\n", wifi_state);
  wifi_state = wifi_state_ready;

  while (1)
  {
    switch (wifi_state) 
    {
    case wifi_state_reset:
		printf("\r\n >>RESET\r\n");
        break;

    case wifi_state_ready:
        printf("\r\n >>connecting to AP...\r\n");
        wifi_connect(console_ssid, console_psk, mode);
        wifi_state = wifi_state_idle;
        break;

    case wifi_state_connected:
        printf("\r\n >>connected...\r\n");
        wifi_state = wifi_state_activity;
        break;

    case wifi_state_disconnected:
		printf("\r\n >>Disconnected\r\n");
        wifi_state = wifi_state_reset;
        break;

    case wifi_state_activity:
		printf("\r\n >>Activity\r\n");
        status = wifi_get_IP_address((uint8_t*)wifi_ip_addr);
        //print("\r\n>>IP address is %s\r\n", wifi_ip_addr);
        
        memset(wifi_ip_addr, 0x00, 20);
        
        status = GET_Configuration_Value(gcfg_key2,(uint32_t *)wifi_ip_addr);
        //print("\r\n>>model no is %s\r\n", wifi_ip_addr);

        if(http_post_request)
            wifi_state = wifi_state_inter;//do a HTTP-POST
        else
        {
          printf("\r\n>>WiFi_HTTPGET\r\n");
        
          status = wifi_http_get((uint8_t *)console_host, (uint8_t *)path, port_num);
      
          if(status == WiFi_MODULE_SUCCESS)
          {
             printf("\r\nHTTP GET OK\r\n");
          }
          else
          {
              print("\r\nHTTP GET Error\r\n");
          }
          wifi_state = wifi_state_idle;
        }
        
        break;

    case wifi_state_inter:        

        printf("\r\n>>Posting data to posttestserver.com..\r\n");  

        status = wifi_http_post((uint8_t *)post_hostname, (uint8_t *)post_path, port_num); 

        if(status == WiFi_MODULE_SUCCESS)    
        {
          printf("\r\nHTTP POST OK\r\n");
        }
        else
        {
          printf("\r\nHTTP POST Error\r\n");
        }        

        wifi_state = wifi_state_idle;
        break;

    case wifi_state_print_data:
        printf((char*)user_buffer);

        wifi_state = wifi_state_idle;

        break;
    case wifi_state_idle:        
        printf("."); 
        fflush(stdout);
        HAL_Delay(500);

        break;

    default:
        break;
    }
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

WiFi_Status_t wifi_get_AP_settings(void)
{
  WiFi_Status_t status = WiFi_MODULE_SUCCESS;
  printf("\r\n\n/********************************************************\n");
  printf("\r *                                                      *\n");
  printf("\r * X-CUBE-WIFI1 Expansion Software v3.1.1               *\n");
  printf("\r * X-NUCLEO-IDW0xx1 Wi-Fi Mini-AP Configuration.        *\n");
  printf("\r * HTTP-Request Example                                 *\n");
  printf("\r *                                                      *\n");
  printf("\r *******************************************************/\n");
  fflush(stdout);
  printf("\r\n\nModule will connect with default settings.");
  
  memcpy(console_ssid, (const char*)ssid, strlen((char*)ssid));
  memcpy(console_psk, (const char*)seckey, strlen((char*)seckey));
  memcpy(console_host, (const char*)hostname, strlen((char*)hostname));
  
  printf("\r\n/*************************************************************\r\n");
  printf("\r\n * Configuration Complete                                     \r\n");
  printf("\r\n * Please make sure a Server is running at given hostname     \r\n");
  printf("\r\n *************************************************************\r\n");
  
  return status;
}


/******** Wi-Fi Indication User Callback *********/
void print(char msg[]) {
	//signed char message[MAX_MSG_SIZE];
	//strncpy(message, msg, MAX_MSG_SIZE);
    //HAL_UART_Transmit(&huart2, message, MAX_MSG_SIZE, 1000);
}

void ind_wifi_on()
{
  print("\r\n\nwifi started and ready...\r\n");
  wifi_state = wifi_state_ready;
}
  
void ind_wifi_connected()
{
  print("\r\nwifi connected...\r\n");
  wifi_state = wifi_state_connected;
}

void ind_wifi_http_data_available(uint8_t * data_ptr, uint32_t message_size)
{
  //User is adviced to copy the data immediately to a user buffer memory as the data will be flushed after this callback
  print("\r\nData Callback\r\n");
  memcpy(user_buffer, data_ptr, message_size);
  print((char*)user_buffer);
  print("\r\n");
}

/* USER CODE END 4 */

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: print("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
