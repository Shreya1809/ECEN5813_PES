/**
 * @file clock.c
 * @brief Clock setup functions
 * @author Miles Frain
 * @author Shreya Chakraborty
 * @version 1
 * @date 2018-03-04
 */

#include "MKL25Z4.h"
#include "MKL25Z4_extension.h"

void clock_setup()
{
    SIM_BWR_SOPT2_PLLFLLSEL(SIM, 1); // MCGPLLCLK clock with fixed divide by two

    SIM_BWR_CLKDIV1_OUTDIV1(SIM, 1); // Divide by 2: core, platform, and system clock
    SIM_BWR_CLKDIV1_OUTDIV4(SIM, 3); // Divide by 8 (4 here * 2 above): bus and flash clock

    MCG_BWR_C1_IRCLKEN(MCG, 1); // MCGIRCLK internal reference clock is enabled
    MCG_BWR_C1_IREFS(MCG, 0); // Not selecting slow internal clock reference. Selecting external reference clock instead. Defaults to 1 (slow internal)
    MCG_BWR_C1_FRDIV(MCG, 3); // FLL external reference divider. Divide factor of 256 (C2->RANGE = 2: very high frequency)

    MCG_BWR_C2_EREFS0(MCG, 1); // External reference select, select Oscillator instead of external reference clock (naming logic seems inverted)
    MCG_BWR_C2_RANGE0(MCG, 2); // very high frequency range

    MCG_BWR_C5_PRDIV0(MCG, 1); // Set PLL external refenece divider factor to 9. Should probably set this before enabling PLL

    MCG_BWR_C6_PLLS(MCG, 1); // PLL selected. Make sure to set PRDIV0 correctly first.

    OSC_BWR_CR_ERCLKEN(OSC0, 1); // Enable external reference clock
}
