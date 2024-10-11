/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2024-10-31
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2024/10/31  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_ags10_basic.h"
#include "driver_ags10_read_test.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "getopt.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
volatile uint16_t g_len;   /**< uart buffer length */

/**
 * @brief     ags10 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t ags10(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"times", required_argument, NULL, 1},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;

    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }

    /* init 0 */
    optind = 0;

    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);

        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");

                break;
            }

            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");

                break;
            }

            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");

                break;
            }

            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);

                break;
            }

            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);

                break;
            }

            /* running times */
            case 1 :
            {
                /* set the times */
                times = atol(optarg);

                break;
            }

            /* the end */
            case -1 :
            {
                break;
            }

            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_read", type) == 0)
    {
        /* run read test */
        if (ags10_read_test(times) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        uint32_t ppb;

        /* basic init */
        res = ags10_basic_init();
        if (res != 0)
        {
            return 1;
        }

        /* loop */
        for (i = 0; i < times; i++)
        {
            /* delay 2000ms */
            ags10_interface_delay_ms(2000);

            /* read data */
            res = ags10_basic_read((uint32_t *)&ppb);
            if (res != 0)
            {
                (void)ags10_basic_deinit();

                return 1;
            }

            /* output */
            ags10_interface_debug_print("ags10: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
            ags10_interface_debug_print("ags10: tvoc is %dppb.\n", ppb);
        }

        /* deinit */
        (void)ags10_basic_deinit();

        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        ags10_interface_debug_print("Usage:\n");
        ags10_interface_debug_print("  ags10 (-i | --information)\n");
        ags10_interface_debug_print("  ags10 (-h | --help)\n");
        ags10_interface_debug_print("  ags10 (-p | --port)\n");
        ags10_interface_debug_print("  ags10 (-t read | --test=read) [--times=<num>]\n");
        ags10_interface_debug_print("  ags10 (-e read | --example=read) [--times=<num>]\n");
        ags10_interface_debug_print("\n");
        ags10_interface_debug_print("Options:\n");
        ags10_interface_debug_print("  -e <read>, --example=<read>    Run the driver example.\n");
        ags10_interface_debug_print("  -h, --help                     Show the help.\n");
        ags10_interface_debug_print("  -i, --information              Show the chip information.\n");
        ags10_interface_debug_print("  -p, --port                     Display the pin connections of the current board.\n");
        ags10_interface_debug_print("  -t <read>, --test=<read>       Run the driver test.\n");
        ags10_interface_debug_print("      --times=<num>              Set the running times.([default: 3])\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        ags10_info_t info;

        /* print ags10 information */
        ags10_info(&info);
        ags10_interface_debug_print("ags10: chip is %s.\n", info.chip_name);
        ags10_interface_debug_print("ags10: manufacturer is %s.\n", info.manufacturer_name);
        ags10_interface_debug_print("ags10: interface is %s.\n", info.interface);
        ags10_interface_debug_print("ags10: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ags10_interface_debug_print("ags10: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ags10_interface_debug_print("ags10: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ags10_interface_debug_print("ags10: max current is %0.2fmA.\n", info.max_current_ma);
        ags10_interface_debug_print("ags10: max temperature is %0.1fC.\n", info.temperature_max);
        ags10_interface_debug_print("ags10: min temperature is %0.1fC.\n", info.temperature_min);

        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        ags10_interface_debug_print("ags10: SCL connected to GPIOB PIN8.\n");
        ags10_interface_debug_print("ags10: SDA connected to GPIOB PIN9.\n");

        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;

    /* stm32f407 clock init and hal init */
    clock_init();

    /* delay init */
    delay_init();

    /* uart init */
    uart_init(115200);

    /* shell init && register ags10 function */
    shell_init();
    shell_register("ags10", ags10);
    uart_print("ags10: welcome to libdriver ags10.\n");

    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("ags10: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("ags10: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("ags10: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("ags10: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("ags10: param is invalid.\n");
            }
            else
            {
                uart_print("ags10: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
