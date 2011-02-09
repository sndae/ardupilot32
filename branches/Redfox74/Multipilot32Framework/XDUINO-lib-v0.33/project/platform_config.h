/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : platform_config.h
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Evaluation board specific configuration file.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line corresponding to the STMicroelectronics evaluation board
   used to run the example */

#if !defined (USE_STM3210B_EVAL)
 #define USE_STM3210B_EVAL
#endif

/* Define For ET-STM32F103 Board */
/* Uncomment the line corresponding to the select the USART used to run 
   the example */
#define USE_USART1
//#define USE_USART2

#ifdef USE_USART1
  #define  USARTx                     USART1
  #define  GPIOx                      GPIOA
  #define  RCC_APB2Periph_GPIOx       RCC_APB2Periph_GPIOA
  #define  GPIO_RxPin                 GPIO_Pin_10
  #define  GPIO_TxPin                 GPIO_Pin_9
#elif defined USE_USART2 
  #define  USARTx                     USART2
  #define  RCC_APB1Periph_USARTx      RCC_APB1Periph_USART2
  #define  GPIOx                      GPIOA
  #define  RCC_APB2Periph_GPIOx       RCC_APB2Periph_GPIOA
  #define  GPIO_TxPin                 GPIO_Pin_2
  #define  GPIO_RxPin                 GPIO_Pin_3
#endif /* USE_STM3210B_EVAL */



  // Define LCD-NOKIA6610 PinIO Interface Mask Bit 
  #define  LCD_BL_PIN 		GPIO_Pin_8						// BL = PB[8]
  #define  LCD_BL_PORT		GPIOB
  #define  RCC_APB2Periph_GPIO_BL     RCC_APB2Periph_GPIOB

  #define  LCD_CS_PIN		GPIO_Pin_9						// CS = PB[9]
  #define  LCD_CS_PORT		GPIOB
  #define  RCC_APB2Periph_GPIO_CS     RCC_APB2Periph_GPIOB

  #define  LCD_SCLK_PIN		GPIO_Pin_10						// SCLK = PB[10]
  #define  LCD_SCLK_PORT	GPIOB
  #define  RCC_APB2Periph_GPIO_SCLK   RCC_APB2Periph_GPIOB

  #define  LCD_SDATA_PIN	GPIO_Pin_11						// SDATA = PB[11]
  #define  LCD_SDATA_PORT	GPIOB
  #define  RCC_APB2Periph_GPIO_SDATA  RCC_APB2Periph_GPIOB

  #define  LCD_RESET_PIN	GPIO_Pin_12						// RESET = PB[12]
  #define  LCD_RESET_PORT	GPIOB
  #define  RCC_APB2Periph_GPIO_RESET  RCC_APB2Periph_GPIOB

  #define  LCD_BL_HI()    	GPIO_WriteBit(LCD_BL_PORT,LCD_BL_PIN,Bit_SET)
  #define  LCD_BL_LO()		GPIO_WriteBit(LCD_BL_PORT,LCD_BL_PIN,Bit_RESET)

  #define  LCD_CS_HI()    	GPIO_WriteBit(LCD_CS_PORT,LCD_CS_PIN,Bit_SET)  
  #define  LCD_CS_LO() 		GPIO_WriteBit(LCD_CS_PORT,LCD_CS_PIN,Bit_RESET)

  #define  LCD_SCLK_HI() 	GPIO_WriteBit(LCD_SCLK_PORT,LCD_SCLK_PIN,Bit_SET)
  #define  LCD_SCLK_LO() 	GPIO_WriteBit(LCD_SCLK_PORT,LCD_SCLK_PIN,Bit_RESET)
   
  #define  LCD_SDATA_HI() 	GPIO_WriteBit(LCD_SDATA_PORT,LCD_SDATA_PIN,Bit_SET)
  #define  LCD_SDATA_LO()	GPIO_WriteBit(LCD_SDATA_PORT,LCD_SDATA_PIN,Bit_RESET)
  
  #define  LCD_RESET_HI() 	GPIO_WriteBit(LCD_RESET_PORT,LCD_RESET_PIN,Bit_SET)  
  #define  LCD_RESET_LO()	GPIO_WriteBit(LCD_RESET_PORT,LCD_RESET_PIN,Bit_RESET)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __PLATFORM_CONFIG_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
