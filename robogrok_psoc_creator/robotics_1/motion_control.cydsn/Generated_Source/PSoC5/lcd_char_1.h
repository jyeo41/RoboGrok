/*******************************************************************************
* File Name: lcd_char_1.h
* Version 2.20
*
* Description:
*  This header file contains registers and constants associated with the
*  Character LCD component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CHARLCD_lcd_char_1_H)
#define CY_CHARLCD_lcd_char_1_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define lcd_char_1_CONVERSION_ROUTINES     (1u)
#define lcd_char_1_CUSTOM_CHAR_SET         (0u)

/* Custom character set types */
#define lcd_char_1_NONE                     (0u)    /* No Custom Fonts      */
#define lcd_char_1_HORIZONTAL_BG            (1u)    /* Horizontal Bar Graph */
#define lcd_char_1_VERTICAL_BG              (2u)    /* Vertical Bar Graph   */
#define lcd_char_1_USER_DEFINED             (3u)    /* User Defined Fonts   */


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} lcd_char_1_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void lcd_char_1_Init(void) ;
void lcd_char_1_Enable(void) ;
void lcd_char_1_Start(void) ;
void lcd_char_1_Stop(void) ;
void lcd_char_1_WriteControl(uint8 cByte) ;
void lcd_char_1_WriteData(uint8 dByte) ;
void lcd_char_1_PrintString(char8 const string[]) ;
void lcd_char_1_Position(uint8 row, uint8 column) ;
void lcd_char_1_PutChar(char8 character) ;
void lcd_char_1_IsReady(void) ;
void lcd_char_1_SaveConfig(void) ;
void lcd_char_1_RestoreConfig(void) ;
void lcd_char_1_Sleep(void) ;
void lcd_char_1_Wakeup(void) ;

#if((lcd_char_1_CUSTOM_CHAR_SET == lcd_char_1_VERTICAL_BG) || \
                (lcd_char_1_CUSTOM_CHAR_SET == lcd_char_1_HORIZONTAL_BG))

    void  lcd_char_1_LoadCustomFonts(uint8 const customData[])
                        ;

    void  lcd_char_1_DrawHorizontalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value)
                         ;

    void lcd_char_1_DrawVerticalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value)
                        ;

#endif /* ((lcd_char_1_CUSTOM_CHAR_SET == lcd_char_1_VERTICAL_BG) */

#if(lcd_char_1_CUSTOM_CHAR_SET == lcd_char_1_USER_DEFINED)

    void lcd_char_1_LoadCustomFonts(uint8 const customData[])
                            ;

#endif /* ((lcd_char_1_CUSTOM_CHAR_SET == lcd_char_1_USER_DEFINED) */

#if(lcd_char_1_CONVERSION_ROUTINES == 1u)

    /* ASCII Conversion Routines */
    void lcd_char_1_PrintInt8(uint8 value) ;
    void lcd_char_1_PrintInt16(uint16 value) ;
    void lcd_char_1_PrintInt32(uint32 value) ;
    void lcd_char_1_PrintNumber(uint16 value) ; 
    void lcd_char_1_PrintU32Number(uint32 value) ;
    
#endif /* lcd_char_1_CONVERSION_ROUTINES == 1u */

/* Clear Macro */
#define lcd_char_1_ClearDisplay() lcd_char_1_WriteControl(lcd_char_1_CLEAR_DISPLAY)

/* Off Macro */
#define lcd_char_1_DisplayOff() lcd_char_1_WriteControl(lcd_char_1_DISPLAY_CURSOR_OFF)

/* On Macro */
#define lcd_char_1_DisplayOn() lcd_char_1_WriteControl(lcd_char_1_DISPLAY_ON_CURSOR_OFF)

#define lcd_char_1_PrintNumber(value) lcd_char_1_PrintU32Number((uint16) (value))


/***************************************
*           Global Variables
***************************************/

extern uint8 lcd_char_1_initVar;
extern uint8 lcd_char_1_enableState;
extern uint8 const CYCODE lcd_char_1_customFonts[64u];


/***************************************
*           API Constants
***************************************/

/* Full Byte Commands Sent as Two Nibbles */
#define lcd_char_1_DISPLAY_8_BIT_INIT       (0x03u)
#define lcd_char_1_DISPLAY_4_BIT_INIT       (0x02u)
#define lcd_char_1_DISPLAY_CURSOR_OFF       (0x08u)
#define lcd_char_1_CLEAR_DISPLAY            (0x01u)
#define lcd_char_1_CURSOR_AUTO_INCR_ON      (0x06u)
#define lcd_char_1_DISPLAY_CURSOR_ON        (0x0Eu)
#define lcd_char_1_DISPLAY_2_LINES_5x10     (0x2Cu)
#define lcd_char_1_DISPLAY_ON_CURSOR_OFF    (0x0Cu)

#define lcd_char_1_RESET_CURSOR_POSITION    (0x03u)
#define lcd_char_1_CURSOR_WINK              (0x0Du)
#define lcd_char_1_CURSOR_BLINK             (0x0Fu)
#define lcd_char_1_CURSOR_SH_LEFT           (0x10u)
#define lcd_char_1_CURSOR_SH_RIGHT          (0x14u)
#define lcd_char_1_DISPLAY_SCRL_LEFT        (0x18u)
#define lcd_char_1_DISPLAY_SCRL_RIGHT       (0x1Eu)
#define lcd_char_1_CURSOR_HOME              (0x02u)
#define lcd_char_1_CURSOR_LEFT              (0x04u)
#define lcd_char_1_CURSOR_RIGHT             (0x06u)

/* Point to Character Generator Ram 0 */
#define lcd_char_1_CGRAM_0                  (0x40u)

/* Point to Display Data Ram 0 */
#define lcd_char_1_DDRAM_0                  (0x80u)

/* LCD Characteristics */
#define lcd_char_1_CHARACTER_WIDTH          (0x05u)
#define lcd_char_1_CHARACTER_HEIGHT         (0x08u)

#if(lcd_char_1_CONVERSION_ROUTINES == 1u)
    #define lcd_char_1_NUMBER_OF_REMAINDERS_U32 (0x0Au)
    #define lcd_char_1_TEN                      (0x0Au)
    #define lcd_char_1_8_BIT_SHIFT              (8u)
    #define lcd_char_1_32_BIT_SHIFT             (32u)
    #define lcd_char_1_ZERO_CHAR_ASCII          (48u)
#endif /* lcd_char_1_CONVERSION_ROUTINES == 1u */

/* Nibble Offset and Mask */
#define lcd_char_1_NIBBLE_SHIFT             (0x04u)
#define lcd_char_1_NIBBLE_MASK              (0x0Fu)

/* LCD Module Address Constants */
#define lcd_char_1_ROW_0_START              (0x80u)
#define lcd_char_1_ROW_1_START              (0xC0u)
#define lcd_char_1_ROW_2_START              (0x94u)
#define lcd_char_1_ROW_3_START              (0xD4u)

/* Custom Character References */
#define lcd_char_1_CUSTOM_0                 (0x00u)
#define lcd_char_1_CUSTOM_1                 (0x01u)
#define lcd_char_1_CUSTOM_2                 (0x02u)
#define lcd_char_1_CUSTOM_3                 (0x03u)
#define lcd_char_1_CUSTOM_4                 (0x04u)
#define lcd_char_1_CUSTOM_5                 (0x05u)
#define lcd_char_1_CUSTOM_6                 (0x06u)
#define lcd_char_1_CUSTOM_7                 (0x07u)

/* Other constants */
#define lcd_char_1_BYTE_UPPER_NIBBLE_SHIFT  (0x04u)
#define lcd_char_1_BYTE_LOWER_NIBBLE_MASK   (0x0Fu)
#define lcd_char_1_U16_UPPER_BYTE_SHIFT     (0x08u)
#define lcd_char_1_U16_LOWER_BYTE_MASK      (0xFFu)
#define lcd_char_1_CUSTOM_CHAR_SET_LEN      (0x40u)

#define lcd_char_1_LONGEST_CMD_US           (0x651u)
#define lcd_char_1_WAIT_CYCLE               (0x10u)
#define lcd_char_1_READY_DELAY              ((lcd_char_1_LONGEST_CMD_US * 4u)/(lcd_char_1_WAIT_CYCLE))


/***************************************
*             Registers
***************************************/

/* Device specific registers */
#if (CY_PSOC4)

    #define lcd_char_1_PORT_DR_REG           (*(reg32 *) lcd_char_1_LCDPort__DR)  /* Data Output Register */
    #define lcd_char_1_PORT_DR_PTR           ( (reg32 *) lcd_char_1_LCDPort__DR)
    #define lcd_char_1_PORT_PS_REG           (*(reg32 *) lcd_char_1_LCDPort__PS)  /* Pin State Register */
    #define lcd_char_1_PORT_PS_PTR           ( (reg32 *) lcd_char_1_LCDPort__PS)
    
    #define lcd_char_1_PORT_PC_REG           (*(reg32 *) lcd_char_1_LCDPort__PC)
    #define lcd_char_1_PORT_PC_PTR           (*(reg32 *) lcd_char_1_LCDPort__PC)
    
#else

    #define lcd_char_1_PORT_DR_REG           (*(reg8 *) lcd_char_1_LCDPort__DR)  /* Data Output Register */
    #define lcd_char_1_PORT_DR_PTR           ( (reg8 *) lcd_char_1_LCDPort__DR)
    #define lcd_char_1_PORT_PS_REG           (*(reg8 *) lcd_char_1_LCDPort__PS)  /* Pin State Register */
    #define lcd_char_1_PORT_PS_PTR           ( (reg8 *) lcd_char_1_LCDPort__PS)

    #define lcd_char_1_PORT_DM0_REG          (*(reg8 *) lcd_char_1_LCDPort__DM0) /* Port Drive Mode 0 */
    #define lcd_char_1_PORT_DM0_PTR          ( (reg8 *) lcd_char_1_LCDPort__DM0)
    #define lcd_char_1_PORT_DM1_REG          (*(reg8 *) lcd_char_1_LCDPort__DM1) /* Port Drive Mode 1 */
    #define lcd_char_1_PORT_DM1_PTR          ( (reg8 *) lcd_char_1_LCDPort__DM1)
    #define lcd_char_1_PORT_DM2_REG          (*(reg8 *) lcd_char_1_LCDPort__DM2) /* Port Drive Mode 2 */
    #define lcd_char_1_PORT_DM2_PTR          ( (reg8 *) lcd_char_1_LCDPort__DM2)

#endif /* CY_PSOC4 */


/***************************************
*       Register Constants
***************************************/

/* SHIFT must be 1 or 0 */
#if (0 == lcd_char_1_LCDPort__SHIFT)
    #define lcd_char_1_PORT_SHIFT               (0x00u)
#else
    #define lcd_char_1_PORT_SHIFT               (0x01u)
#endif /* (0 == lcd_char_1_LCDPort__SHIFT) */

#define lcd_char_1_PORT_MASK                ((uint8) (lcd_char_1_LCDPort__MASK))

#if (CY_PSOC4)

    #define lcd_char_1_DM_PIN_STEP              (3u)
    /* Hi-Z Digital is defined by the value of "001b" and this should be set for
    * four data pins, in this way we get - 0x00000249. A similar Strong drive
    * is defined with "110b" so we get 0x00000DB6.
    */
    #define lcd_char_1_HIGH_Z_DATA_DM           ((0x00000249ul) << (lcd_char_1_PORT_SHIFT *\
                                                                          lcd_char_1_DM_PIN_STEP))
    #define lcd_char_1_STRONG_DATA_DM           ((0x00000DB6ul) << (lcd_char_1_PORT_SHIFT *\
                                                                          lcd_char_1_DM_PIN_STEP))
    #define lcd_char_1_DATA_PINS_MASK           (0x00000FFFul)
    #define lcd_char_1_DM_DATA_MASK             ((uint32) (lcd_char_1_DATA_PINS_MASK << \
                                                      (lcd_char_1_PORT_SHIFT * lcd_char_1_DM_PIN_STEP)))

#else

    /* Drive Mode register values for High Z */
    #define lcd_char_1_HIGH_Z_DM0               (0xFFu)
    #define lcd_char_1_HIGH_Z_DM1               (0x00u)
    #define lcd_char_1_HIGH_Z_DM2               (0x00u)

    /* Drive Mode register values for High Z Analog */
    #define lcd_char_1_HIGH_Z_A_DM0             (0x00u)
    #define lcd_char_1_HIGH_Z_A_DM1             (0x00u)
    #define lcd_char_1_HIGH_Z_A_DM2             (0x00u)

    /* Drive Mode register values for Strong */
    #define lcd_char_1_STRONG_DM0               (0x00u)
    #define lcd_char_1_STRONG_DM1               (0xFFu)
    #define lcd_char_1_STRONG_DM2               (0xFFu)

#endif /* CY_PSOC4 */

/* Pin Masks */
#define lcd_char_1_RS                     ((uint8) \
                                                (((uint8) 0x20u) << lcd_char_1_LCDPort__SHIFT))
#define lcd_char_1_RW                     ((uint8) \
                                                (((uint8) 0x40u) << lcd_char_1_LCDPort__SHIFT))
#define lcd_char_1_E                      ((uint8) \
                                                (((uint8) 0x10u) << lcd_char_1_LCDPort__SHIFT))
#define lcd_char_1_READY_BIT              ((uint8) \
                                                (((uint8) 0x08u) << lcd_char_1_LCDPort__SHIFT))
#define lcd_char_1_DATA_MASK              ((uint8) \
                                                (((uint8) 0x0Fu) << lcd_char_1_LCDPort__SHIFT))

/* These names are obsolete and will be removed in future revisions */
#define lcd_char_1_PORT_DR                  lcd_char_1_PORT_DR_REG
#define lcd_char_1_PORT_PS                  lcd_char_1_PORT_PS_REG
#define lcd_char_1_PORT_DM0                 lcd_char_1_PORT_DM0_REG
#define lcd_char_1_PORT_DM1                 lcd_char_1_PORT_DM1_REG
#define lcd_char_1_PORT_DM2                 lcd_char_1_PORT_DM2_REG


/***************************************
*       Obsolete function names
***************************************/
#if(lcd_char_1_CONVERSION_ROUTINES == 1u)
    /* This function names are obsolete and will be removed in future 
    * revisions of the component.
    */
    #define lcd_char_1_PrintDecUint16(x)   lcd_char_1_PrintNumber(x)  
    #define lcd_char_1_PrintHexUint8(x)    lcd_char_1_PrintInt8(x)
    #define lcd_char_1_PrintHexUint16(x)   lcd_char_1_PrintInt16(x)        

#endif /* lcd_char_1_CONVERSION_ROUTINES == 1u */

#endif /* CY_CHARLCD_lcd_char_1_H */


/* [] END OF FILE */
