/*******************************************************************************
  SYS CLK Static Functions for Clock System Service

  Company:
    Microchip Technology Inc.

  File Name:
    plib_clk.c

  Summary:
    SYS CLK static function implementations for the Clock System Service.

  Description:
    The Clock System Service provides a simple interface to manage the
    oscillators on Microchip microcontrollers. This file defines the static
    implementation for the Clock System Service.

  Remarks:
    Static functions incorporate all system clock configuration settings as
    determined by the user via the Microchip Harmony Configurator GUI.
    It provides static version of the routines, eliminating the need for an
    object ID or object handle.

    Static single-open interfaces also eliminate the need for the open handle.

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************

#include "device.h"
#include "plib_clk.h"

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    void CLK_Initialize( void )

  Summary:
    Initializes hardware and internal data structure of the System Clock.

  Description:
    This function initializes the hardware and internal data structure of System
    Clock Service.

  Remarks:
    This is configuration values for the static version of the Clock System
    Service module is determined by the user via the MHC GUI.

    The objective is to eliminate the user's need to be knowledgeable in the
    function of the 'configuration bits' to configure the system oscillators.
*/

#define EWPLLCON_MSK 0x0438080cU
#define EWPLL_PWRON  0x808U

static void  DelayMs ( uint32_t  delayMs)
{
    uint32_t startCount, endCount;
    /* Calculate the end count for the given delay */
    endCount=((uint32_t)CORE_TIMER_FREQ/1000U)* delayMs;
    startCount=_CP0_GET_COUNT();
    while((_CP0_GET_COUNT()-startCount)<endCount)
    {
        /* Nothing to do */
    }
}

 static void wifi_spi_write(unsigned int spi_addr, unsigned int data)
{
    unsigned int  addr_bit, data_bit, bit_idx;
    unsigned int cs_high, clk_high, en_bit_bang;
    volatile unsigned int *const wifi_spi_ctrl_reg = (unsigned int *const)0xBF8C8028U;
    clk_high = 0x1 ;
    cs_high  = 0x2;
    en_bit_bang  = 0x1UL << 31;
    addr_bit = 0; data_bit = 0;

    *wifi_spi_ctrl_reg = en_bit_bang | cs_high ;
    *wifi_spi_ctrl_reg = (en_bit_bang | cs_high | clk_high );
     *wifi_spi_ctrl_reg = (en_bit_bang);
     *wifi_spi_ctrl_reg = (en_bit_bang | clk_high);

    for (bit_idx=0;bit_idx<=7U;bit_idx++) {
        addr_bit = (spi_addr>>(7U-bit_idx)) & 0x1U;
        *wifi_spi_ctrl_reg = (en_bit_bang | (addr_bit << 2 ));               // Falling edge of clk
        *wifi_spi_ctrl_reg = (en_bit_bang | (addr_bit << 2 ) | clk_high);    // Rising edge of clk
    }

    for (bit_idx=0;bit_idx<=15U;bit_idx++) {
        data_bit = (data>>(15U-bit_idx)) & 0x1U;
        *wifi_spi_ctrl_reg = (en_bit_bang | (data_bit << 2 ));                // Falling edge of clk with data bit
        *wifi_spi_ctrl_reg = (en_bit_bang | (data_bit << 2 ) | clk_high);     // Rising edge of clk
    }

    *wifi_spi_ctrl_reg = (en_bit_bang | cs_high | clk_high); // Rising edge of clk
    *wifi_spi_ctrl_reg = 0;                                // Set the RF override bit and CS_n high
}
void CLK_Initialize( void )
{
    volatile unsigned int *PLLDBG = (unsigned int*) 0xBF8000E0U;
    volatile unsigned int *PMDRCLR = (unsigned int *) 0xBF8000B4U;
	volatile unsigned int *RFSPICTL = (unsigned int *) 0xBF8C8028U;
    
    uint8_t TempPOR = 0, TempEXTR = 0, TempSWR = 0;

    /* unlock system for clock configuration */
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655U;
    SYSKEY = 0x556699AA;

    if(((DEVID & 0x0FF00000U) >> 20) == (uint32_t)PIC32MZW1_B0)
    {
        TempPOR = RCONbits.POR;
        TempEXTR = RCONbits.EXTR; 
        TempSWR = RCONbits.SWR;
        
        if(((CLKSTATbits.SPLLRDY == 0U) && (TempPOR == 1U) && (TempEXTR == 1U))
            || ((1U == CLKSTATbits.SPLLRDY) && (0U == TempPOR) &&
            ((1U == TempEXTR) || (1U == TempSWR))))
		{
			EWPLLCON = 0x808; // Start with PWR-OFF PLL
			SPLLCON  = 0x808; // Start with PWR-OFF PLL
			 DelayMs(5);

			CFGCON2  |= 0x300U; // Start with POSC Turned OFF
			/* if POSC was on give some time for POSC to shut off */
			 DelayMs(5);
			/* make sure we properly reset SPI to a known state */
			*RFSPICTL = 0x80000022U;
			/* make sure we properly take out of reset */
			*RFSPICTL = 0x80000002U;

			if(1U == DEVIDbits.VER)
			{
                wifi_spi_write(0x85, 0x00F2); /* MBIAS filter and A31 analog_test */
                wifi_spi_write(0x84, 0x0001); /* A31 Analog test */
                wifi_spi_write(0x1e, 0x510); /* MBIAS reference adjustment */
                wifi_spi_write(0x82, 0x6000); /* XTAL LDO feedback divider (1.3+v) */
			}
			else
            {
                wifi_spi_write(0x85, 0x00F0); /* MBIAS filter and A31 analog_test */
                wifi_spi_write(0x84, 0x0001); /* A31 Analog test */
                wifi_spi_write(0x1e, 0x510); /* MBIAS reference adjustment */
                wifi_spi_write(0x82, 0x6400); /* XTAL LDO feedback divider (1.3+v) */
			}
             DelayMs(2);
			/* Enable POSC */
			CFGCON2  &= 0xFFFFFCFFU; // enable POSC
			 DelayMs(5);

			/*Configure SPLL*/
			CFGCON3 = 10;
			CFGCON0bits.SPLLHWMD = 1;

			/* SPLLBSWSEL   = 1   */
			/* SPLLPWDN     = PLL_ON     */
			/* SPLLPOSTDIV1 = 6 */
			/* SPLLFLOCK    = NO_ASSERT    */
			/* SPLLRST      = NO_ASSERT      */
			/* SPLLFBDIV    = 150  */
			/* SPLLREFDIV   = 5   */
			/* SPLLICLK     = POSC     */
			/* SPLL_BYP     = NO_BYPASS     */
			SPLLCON = 0x1496061;

			/* OSWEN    = SWITCH_COMPLETE    */
			/* SOSCEN   = OFF   */
			/* UFRCEN   = USBCLK   */
			/* CF       = NO_FAILDET       */
			/* SLPEN    = IDLE    */
			/* CLKLOCK  = UNLOCKED  */
			/* NOSC     = SPLL     */
			/* WAKE2SPD = SELECTED_CLK */
			/* DRMEN    = NO_EFFECT    */
			/* FRCDIV   = OSC_FRC_DIV_1   */
			OSCCON = 0x100;

			OSCCONSET = _OSCCON_OSWEN_MASK;  /* request oscillator switch to occur */

			while( OSCCONbits.OSWEN != 0U)
            {
                /* Nothing to do */
            }
			/****************************************************************
			* check to see if PLL locked; indicates POSC must have started
			*****************************************************************/
			if(0U == (*PLLDBG & 0x1U))
			{
				/*POSC failed to start!*/
				while(true)
                {
                   /* Nothing to do */
                } 
			}
			if(1U == DEVIDbits.VER)
			{
				/*Disabling internal schmitt-trigger to increase noise immunity */
				wifi_spi_write(0x85, 0x00F4);
			}
		}
		/* Power down the EWPLL */
		EWPLLCONbits.EWPLLPWDN = 1;

		/* Power down the UPLL */
		UPLLCONbits.UPLLPWDN = 1;

		/* Power down the BTPLL */
		BTPLLCONbits.BTPLLPWDN = 1;

        *(PMDRCLR)  = 0x1000;
    }
    else if(((DEVID & 0x0FF00000U) >> 20) == (uint32_t)PIC32MZW1_A1)
    {

		CFGCON2  |= 0x300U; // Start with POSC Turned OFF
		 DelayMs(2);

		/* make sure we properly reset SPI to a known state */
		*RFSPICTL = 0x80000022U;
		/* now wifi is properly reset enable POSC */
		CFGCON2  &= 0xFFFFFCFFU; // enable POSC

		 DelayMs(2);

        /* make sure we properly take out of reset */
        *RFSPICTL = 0x80000002U;

        wifi_spi_write(0x85, 0x00F0); // MBIAS filter and A31 analog_test
        wifi_spi_write(0x84, 0x0001); // A31 Analog test
        wifi_spi_write(0x1e, 0x510); // MBIAS reference adjustment
        wifi_spi_write(0x82, 0x6000); // XTAL LDO feedback divider (1.3+v)

		 /* Wait for POSC ready */
        while((CLKSTAT & 0x00000004U) == 0U) 
        {
            /* Nothing to do */
        }

    	OSCCONbits.FRCDIV = 0;

		CFGCON3 = 10;
        CFGCON0bits.SPLLHWMD = 1;
		/* SPLLCON = 0x01496869 */
		/* SPLLBSWSEL   = 1   */
		/* SPLLPWDN     = PLL_ON     */
		/* SPLLPOSTDIV1 = 6 */
		/* SPLLFLOCK    = NO_ASSERT    */
		/* SPLLRST      = NO_ASSERT      */
		/* SPLLFBDIV    = 150  */
		/* SPLLREFDIV   = 5   */
		/* SPLLICLK     = POSC     */
		/* SPLL_BYP     = NO_BYPASS     */
		SPLLCON = 0x1496061;


		/* Power down the UPLL */
		UPLLCONbits.UPLLPWDN = 1;

		/* Power down the EWPLL */
		EWPLLCONbits.EWPLLPWDN = 1;

		/* Power down the BTPLL */
		BTPLLCONbits.BTPLLPWDN = 1;

		/* ETHPLLPOSTDIV2 = a */
		/* SPLLPOSTDIV2   = 0 */
		/* BTPLLPOSTDIV2  = 0 */
		CFGCON3 = 10;

		/* OSWEN    = SWITCH_COMPLETE    */
		/* SOSCEN   = OFF   */
		/* UFRCEN   = USBCLK   */
		/* CF       = NO_FAILDET       */
		/* SLPEN    = IDLE    */
		/* CLKLOCK  = UNLOCKED  */
		/* NOSC     = SPLL     */
		/* WAKE2SPD = SELECTED_CLK */
		/* DRMEN    = NO_EFFECT    */
		/* FRCDIV   = OSC_FRC_DIV_1   */
		OSCCON = 0x100;

		OSCCONSET = _OSCCON_OSWEN_MASK;  /* request oscillator switch to occur */

		Nop();
		Nop();

		while( OSCCONbits.OSWEN != 0U)        /* wait for indication of successful clock change before proceeding */
        {
            /* Nothing to do */
        }
	}
    else
    {
        /* Nothing to do */
    }

  

    /* Peripheral Module Disable Configuration */

    CFGCON0bits.PMDLOCK = 0;

    PMD1 = 0x25818981;
    PMD2 = 0x7e0f0f;
    PMD3 = 0x19031117;

    CFGCON0bits.PMDLOCK = 1;
	if(1U == RCONbits.POR)
    {
		RCONbits.POR = 0;
    }
	if(1U == RCONbits.EXTR)
    {
		RCONbits.EXTR = 0;
    }
    if(1U == RCONbits.SWR)
    {
        RCONbits.SWR = 0;
    }

    /* Lock system since done with clock configuration */
    SYSKEY = 0x33333333;
}
