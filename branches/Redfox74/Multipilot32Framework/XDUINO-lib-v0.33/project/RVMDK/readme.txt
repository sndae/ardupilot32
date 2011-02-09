/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : This sub-directory contains all the user-modifiable files 
*                      needed to create a new project linked with the STM32F10x  
*                      Firmware Library and working with RealView Microcontroller
*                      Development Kit(RVMDK) software toolchain (Version 3.21 and later).
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

Directory contents
===================
- Project.Uv2/.Opt: A pre-configured project file with the provided library structure
                    that produces an executable image with RVMDK.
              
- stm32f10x_vector.s: This file contains the vector table for STM32F10x, Stack
                      and Heap definition. User can also enable the use of external
                      SRAM mounted on ET-STM32F103 board as data memory.                
                      
- cortexm3_macro.s: Instruction wrappers for special Cortex-M3 instructions. 

- note.txt        : Steps to follow when using the default startup file provided 
                    by RVMDK when creating new projects.
      
How to use it
=============
- Open the Project.Uv2 project
- In the build toolbar select the project config:
    - ET-STM32F103: to configure the project 
- Rebuild all files: Project->Rebuild all target files
- Load project image: Debug->Start/Stop Debug Session
- Run program: Debug->Run (F5)
    
******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
