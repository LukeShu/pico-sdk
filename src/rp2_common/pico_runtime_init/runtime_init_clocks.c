/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/runtime_init.h"
#if !PICO_RUNTIME_NO_INIT_CLOCKS

#include "hardware/clocks.h"
#include "hardware/pll.h"
#include "hardware/ticks.h"
#include "hardware/timer.h"
#include "hardware/vreg.h"
#include "hardware/xosc.h"
#if PICO_RP2040
#include "hardware/regs/rtc.h"
#endif

// \tag::pll_settings[]
// There are two PLLs in RP-series microcontrollers:
// 1. The 'SYS PLL' generates the system clock, the frequency is defined by `SYS_CLK_KHZ`.
// 2. The 'USB PLL' generates the USB clock, the frequency is defined by `USB_CLK_KHZ`.
//
// The two PLLs use the crystal oscillator output directly as their reference frequency input; the PLLs reference
// frequency cannot be reduced by the dividers present in the clocks block. The crystal frequency is defined by `XOSC_HZ` (or
// `XOSC_KHZ` or `XOSC_MHZ`).
//
// The system's default definitions are correct for the above frequencies with a 12MHz
// crystal frequency.  If different frequencies are required, these must be defined in
// the board configuration file together with the revised PLL settings
// Use `vcocalc.py` to check and calculate new PLL settings if you change any of these frequencies.
//
// Default PLL configuration RP2040:
//                   REF     FBDIV VCO            POSTDIV
// PLL SYS: 12 / 1 = 12MHz * 125 = 1500MHz / 6 / 2 = 125MHz
// PLL USB: 12 / 1 = 12MHz * 100 = 1200MHz / 5 / 5 =  48MHz
//
// Default PLL configuration RP2350:
//                   REF     FBDIV VCO            POSTDIV
// PLL SYS: 12 / 1 = 12MHz * 125 = 1500MHz / 5 / 2 = 150MHz
// PLL USB: 12 / 1 = 12MHz * 100 = 1200MHz / 5 / 5 =  48MHz
// \end::pll_settings[]

#ifndef PLL_COMMON_REFDIV
    // backwards compatibility, but now deprecated
    #define PLL_COMMON_REFDIV 1
#endif

// PICO_CONFIG: PLL_SYS_REFDIV, PLL reference divider setting for PLL_SYS, type=int, default=1, advanced=true, group=hardware_clocks
#ifndef PLL_SYS_REFDIV
    // backwards compatibility with deprecated PLL_COMMON_REFDIV
    #ifdef PLL_COMMON_REFDIV
        #define PLL_SYS_REFDIV                   PLL_COMMON_REFDIV
    #else
        #define PLL_SYS_REFDIV                   1
    #endif
#endif

#ifndef PLL_SYS_VCO_FREQ_HZ
    // For backwards compatibility define PLL_SYS_VCO_FREQ_HZ if PLL_SYS_VCO_FREQ_KHZ is defined
    #ifdef PLL_SYS_VCO_FREQ_KHZ
        #define PLL_SYS_VCO_FREQ_HZ                (PLL_SYS_VCO_FREQ_KHZ * KHZ)
    #endif
#endif

#if (SYS_CLK_HZ == 125 * MHZ || SYS_CLK_HZ == 150 * MHZ) && (XOSC_HZ == 12 * MHZ) && (PLL_SYS_REFDIV == 1)
    // PLL settings for standard 125/150 MHz system clock.
    // PICO_CONFIG: PLL_SYS_VCO_FREQ_HZ, System clock PLL frequency, type=int, default=(1500 * MHZ), advanced=true, group=hardware_clocks
    #ifndef PLL_SYS_VCO_FREQ_HZ
        #define PLL_SYS_VCO_FREQ_HZ                (1500 * MHZ)
    #endif
    // PICO_CONFIG: PLL_SYS_POSTDIV1, System clock PLL post divider 1 setting, type=int, default=6 on RP2040 or 5 on RP2350, advanced=true, group=hardware_clocks
    #ifndef PLL_SYS_POSTDIV1
        #if SYS_CLK_HZ == 125 * MHZ
            #define PLL_SYS_POSTDIV1                    6
        #else
            #define PLL_SYS_POSTDIV1                    5
        #endif
    #endif
    // PICO_CONFIG: PLL_SYS_POSTDIV2, System clock PLL post divider 2 setting, type=int, default=2, advanced=true, group=hardware_clocks
    #ifndef PLL_SYS_POSTDIV2
        #define PLL_SYS_POSTDIV2                    2
    #endif
#endif // SYS_CLK_KHZ == 125000 && XOSC_KHZ == 12000 && PLL_COMMON_REFDIV == 1

#if PICO_RP2040 && (SYS_CLK_HZ == 200 * MHZ) && (XOSC_HZ == 12 * MHZ) && (PLL_SYS_REFDIV == 1)
    // PICO_CONFIG: SYS_CLK_VREG_VOLTAGE_AUTO_ADJUST, Should the regulator voltage be adjusted above SYS_CLK_VREG_VOLTAGE_MIN when initializing the clocks, type=bool, default=0, advanced=true, group=hardware_clocks
    #ifndef SYS_CLK_VREG_VOLTAGE_AUTO_ADJUST
        #define SYS_CLK_VREG_VOLTAGE_AUTO_ADJUST 1
    #endif
    // PICO_CONFIG: SYS_CLK_VREG_VOLTAGE_MIN, minimum voltage (see VREG_VOLTAGE_x_xx) for the voltage regulator to be ensured during clock initialization if SYS_CLK_VREG_VOLTAGE_AUTO_ADJUST is 1, type=int, advanced=true, group=hardware_clocks
    #if SYS_CLK_VREG_VOLTAGE_AUTO_ADJUST && !defined(SYS_CLK_VREG_VOLTAGE_MIN)
        #define SYS_CLK_VREG_VOLTAGE_MIN VREG_VOLTAGE_1_15
    #endif
    // PLL settings for fast 200 MHz system clock on RP2040
    #ifndef PLL_SYS_VCO_FREQ_HZ
        #define PLL_SYS_VCO_FREQ_HZ                (1200 * MHZ)
    #endif
    #ifndef PLL_SYS_POSTDIV1
        #define PLL_SYS_POSTDIV1                    6
    #endif
    #ifndef PLL_SYS_POSTDIV2
        #define PLL_SYS_POSTDIV2                    1
    #endif
#else
    #ifndef SYS_CLK_VREG_VOLTAGE_AUTO_ADJUST
        #define SYS_CLK_VREG_VOLTAGE_AUTO_ADJUST 0
    #endif
#endif // PICO_RP2040 && SYS_CLK_KHZ == 200000 && XOSC_KHZ == 12000 && PLL_COMMON_REFDIV == 1

// PICO_CONFIG: SYS_CLK_VREG_VOLTAGE_AUTO_ADJUST_DELAY_US, Number of microseconds to wait after updating regulator voltage due to SYS_CLK_VREG_VOLTAGE_MIN to allow voltage to settle, type=int, default=1, advanced=true, group=hardware_clocks
#ifndef SYS_CLK_VREG_VOLTAGE_AUTO_ADJUST_DELAY_US
    #define SYS_CLK_VREG_VOLTAGE_AUTO_ADJUST_DELAY_US 1000
#endif

#if !defined(PLL_SYS_VCO_FREQ_HZ) || !defined(PLL_SYS_POSTDIV1) || !defined(PLL_SYS_POSTDIV2)
    #error PLL_SYS_VCO_FREQ_HZ, PLL_SYS_POSTDIV1 and PLL_SYS_POSTDIV2 must all be specified when using custom clock setup
#endif

// PICO_CONFIG: PLL_USB_REFDIV, PLL reference divider setting for PLL_USB, type=int, default=1, advanced=true, group=hardware_clocks
#ifndef PLL_USB_REFDIV
    // backwards compatibility with deprecated PLL_COMMON_REFDIV
    #ifdef PLL_COMMON_REFDIV
        #define PLL_USB_REFDIV                   PLL_COMMON_REFDIV
    #else
        #define PLL_USB_REFDIV                   1
    #endif
#endif

#ifndef PLL_USB_VCO_FREQ_HZ
    // For backwards compatibility define PLL_USB_VCO_FREQ_HZ if PLL_USB_VCO_FREQ_KHZ is defined
    #ifdef PLL_USB_VCO_FREQ_KHZ
        #define PLL_USB_VCO_FREQ_HZ                 (PLL_USB_VCO_FREQ_KHZ * KHZ)
    #endif
#endif

#if (USB_CLK_HZ == 48 * MHZ) && (XOSC_HZ == 12 * MHZ) && (PLL_USB_REFDIV == 1)
    // PLL settings for a USB clock of 48MHz.
    // PICO_CONFIG: PLL_USB_VCO_FREQ_HZ, USB clock PLL frequency, type=int, default=(1200 * MHZ), advanced=true, group=hardware_clocks
    #ifndef PLL_USB_VCO_FREQ_HZ
        #define PLL_USB_VCO_FREQ_HZ                 (1200 * MHZ)
    #endif
    // PICO_CONFIG: PLL_USB_POSTDIV1, USB clock PLL post divider 1 setting, type=int, default=5, advanced=true, group=hardware_clocks
    #ifndef PLL_USB_POSTDIV1
        #define PLL_USB_POSTDIV1                    5
    #endif
    // PICO_CONFIG: PLL_USB_POSTDIV2, USB clock PLL post divider 2 setting, type=int, default=5, advanced=true, group=hardware_clocks
    #ifndef PLL_USB_POSTDIV2
        #define PLL_USB_POSTDIV2                    5
    #endif
#endif // USB_CLK_HZ == 48000000 && XOSC_HZ == 12000000 && PLL_COMMON_REFDIV == 1

#if !defined(PLL_USB_VCO_FREQ_HZ) || !defined(PLL_USB_POSTDIV1) || !defined(PLL_USB_POSTDIV2)
    #error PLL_USB_VCO_FREQ_HZ, PLL_USB_POSTDIV1 and PLL_USB_POSTDIV2 must all be specified when using custom clock setup.
#endif

#if PICO_RP2040
// The RTC clock frequency is 48MHz divided by power of 2 (to ensure an integer
// division ratio will be used in the clocks block).  A divisor of 1024 generates
// an RTC clock tick of 46875Hz.  This frequency is relatively close to the
// customary 32 or 32.768kHz 'slow clock' crystals and provides good timing resolution.
#define RTC_CLOCK_FREQ_HZ       (USB_CLK_HZ / 1024)
#endif

static void start_all_ticks(void) {
    uint32_t cycles = clock_get_hz(clk_ref) / MHZ;
    // Note RP2040 has a single tick generator in the watchdog which serves
    // watchdog, system timer and M0+ SysTick; The tick generator is clocked from clk_ref
    // but is now adapted by the hardware_ticks library for compatibility with RP2350
    // npte: hardware_ticks library now provides an adapter for RP2040

    for (int i = 0; i < (int)TICK_COUNT; ++i) {
        tick_start((tick_gen_num_t)i, cycles);
    }
}

void __weak runtime_init_clocks(void) {
    // Note: These need setting *before* the ticks are started
    if (running_on_fpga()) {
        for (uint i = 0; i < CLK_COUNT; i++) {
            clock_set_reported_hz(i, 48 * MHZ);
        }
        // clk_ref is 12MHz in both RP2040 and RP2350 FPGA
        clock_set_reported_hz(clk_ref, 12 * MHZ);
        // RP2040 has an extra clock, the rtc
#if HAS_RP2040_RTC
        clock_set_reported_hz(clk_rtc, RTC_CLOCK_FREQ_HZ);
#endif
    } else {
        // Disable resus that may be enabled from previous software
        clocks_hw->resus.ctrl = 0;

        // Enable the xosc
        xosc_init();

        // Before we touch PLLs, switch sys and ref cleanly away from their aux sources.
        hw_clear_bits(&clocks_hw->clk[clk_sys].ctrl, CLOCKS_CLK_SYS_CTRL_SRC_BITS);
        while (clocks_hw->clk[clk_sys].selected != 0x1)
            tight_loop_contents();
        hw_clear_bits(&clocks_hw->clk[clk_ref].ctrl, CLOCKS_CLK_REF_CTRL_SRC_BITS);
        while (clocks_hw->clk[clk_ref].selected != 0x1)
            tight_loop_contents();

        /// \tag::pll_init[]
        pll_init(pll_sys, PLL_SYS_REFDIV, PLL_SYS_VCO_FREQ_HZ, PLL_SYS_POSTDIV1, PLL_SYS_POSTDIV2);
        pll_init(pll_usb, PLL_USB_REFDIV, PLL_USB_VCO_FREQ_HZ, PLL_USB_POSTDIV1, PLL_USB_POSTDIV2);
        /// \end::pll_init[]

        // Configure clocks

        // RP2040 CLK_REF = XOSC (usually) 12MHz / 1 = 12MHz
        // RP2350 CLK_REF = XOSC (XOSC_MHZ) / N (1,2,4) = 12MHz

        // clk_ref aux select is 0 because:
        //
        // - RP2040: no aux mux on clk_ref, so this field is don't-care.
        //
        // - RP2350: there is an aux mux, but we are selecting one of the
        //   non-aux inputs to the glitchless mux, so the aux select doesn't
        //   matter. The value of 0 here happens to be the sys PLL.

        clock_configure_undivided(clk_ref,
                        CLOCKS_CLK_REF_CTRL_SRC_VALUE_XOSC_CLKSRC,
                        0,
                        XOSC_HZ);

        // This must be done after we've configured CLK_REF to XOSC due to the need to time a delay
#if PICO_RP2040 && SYS_CLK_VREG_VOLTAGE_AUTO_ADJUST && defined(SYS_CLK_VREG_VOLTAGE_MIN)
        if (vreg_get_voltage() < SYS_CLK_VREG_VOLTAGE_MIN) {
            vreg_set_voltage(SYS_CLK_VREG_VOLTAGE_MIN);
            // Go ahead and start the watchdog timer so that we can poll
            // timer_hw to know when SYS_CLK_VREG_VOLTAGE_AUTO_ADJUST_DELAY_US
            // has elapsed.  Counting cycles (i.e. busy_wait_at_least_cycles())
            // won't work because that's counting clk_sys, which we can't
            // configure until after the VREG is configured!
            tick_start(TICK_WATCHDOG, clock_get_hz(clk_ref) / MHZ);
            uint32_t start = timer_hw->timerawl;
            while (timer_hw->timerawl - start < SYS_CLK_VREG_VOLTAGE_AUTO_ADJUST_DELAY_US)
                tight_loop_contents();
        }
#endif

        /// \tag::configure_clk_sys[]
        // CLK SYS = PLL SYS (usually) 125MHz / 1 = 125MHz
        clock_configure_undivided(clk_sys,
                        CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX,
                        CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS,
                        SYS_CLK_HZ);
        /// \end::configure_clk_sys[]

        // CLK USB = PLL USB 48MHz / 1 = 48MHz
        clock_configure_undivided(clk_usb,
                        0, // No GLMUX
                        CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB,
                        USB_CLK_HZ);

        // CLK ADC = PLL USB 48MHZ / 1 = 48MHz
        clock_configure_undivided(clk_adc,
                        0, // No GLMUX
                        CLOCKS_CLK_ADC_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB,
                        USB_CLK_HZ);

#if HAS_RP2040_RTC
        // CLK RTC = PLL USB 48MHz / 1024 = 46875Hz
#if (USB_CLK_HZ % RTC_CLOCK_FREQ_HZ == 0)
        // this doesn't pull in 64 bit arithmetic
        clock_configure_int_divider(clk_rtc,
                        0, // No GLMUX
                        CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB,
                        USB_CLK_HZ,
                        USB_CLK_HZ / RTC_CLOCK_FREQ_HZ);

#else
        clock_configure(clk_rtc,
                        0, // No GLMUX
                        CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB,
                        USB_CLK_HZ,
                        RTC_CLOCK_FREQ_HZ);

#endif
#endif

        // CLK PERI = clk_sys. Used as reference clock for UART and SPI serial.
        clock_configure_undivided(clk_peri,
                        0,
                        CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLK_SYS,
                        SYS_CLK_HZ);

#if HAS_HSTX
        // CLK_HSTX = clk_sys. Transmit bit clock for the HSTX peripheral.
        clock_configure_undivided(clk_hstx,
                        0,
                        CLOCKS_CLK_HSTX_CTRL_AUXSRC_VALUE_CLK_SYS,
                        SYS_CLK_HZ);
#endif
    }

    // Finally, all clocks are configured so start the ticks
    // The ticks use clk_ref so now that is configured we can start them
    start_all_ticks();
}

#endif