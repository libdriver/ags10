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
 * @file      driver_ags10_read_test.c
 * @brief     driver ags10 read test source file
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

#include "driver_ags10_read_test.h"
#include <stdlib.h>

static ags10_handle_t gs_handle;        /**< ags10 handle */

/**
 * @brief     read test
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 read failed
 * @note      none
 */
uint8_t ags10_read_test(uint32_t times)
{
    uint8_t res;
    uint8_t version;
    uint8_t addr_7bit;
    uint16_t reg;
    double ohm;
    uint32_t i;
    uint32_t raw;
    uint32_t ppb;
    ags10_info_t info;
   
    /* link interface function */
    DRIVER_AGS10_LINK_INIT(&gs_handle, ags10_handle_t);
    DRIVER_AGS10_LINK_IIC_INIT(&gs_handle, ags10_interface_iic_init);
    DRIVER_AGS10_LINK_IIC_DEINIT(&gs_handle, ags10_interface_iic_deinit);
    DRIVER_AGS10_LINK_IIC_READ_CMD(&gs_handle, ags10_interface_iic_read_cmd);
    DRIVER_AGS10_LINK_IIC_WRITE_CMD(&gs_handle, ags10_interface_iic_write_cmd);
    DRIVER_AGS10_LINK_IIC_WRITE(&gs_handle, ags10_interface_iic_write);
    DRIVER_AGS10_LINK_DELAY_MS(&gs_handle, ags10_interface_delay_ms);
    DRIVER_AGS10_LINK_DEBUG_PRINT(&gs_handle, ags10_interface_debug_print);

    /* get ags10 information */
    res = ags10_info(&info);
    if (res != 0)
    {
        ags10_interface_debug_print("ags10: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print ags10 information */
        ags10_interface_debug_print("ags10: chip is %s.\n", info.chip_name);
        ags10_interface_debug_print("ags10: manufacturer is %s.\n", info.manufacturer_name);
        ags10_interface_debug_print("ags10: interface is %s.\n", info.interface);
        ags10_interface_debug_print("ags10: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ags10_interface_debug_print("ags10: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ags10_interface_debug_print("ags10: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ags10_interface_debug_print("ags10: max current is %0.2fmA.\n", info.max_current_ma);
        ags10_interface_debug_print("ags10: max temperature is %0.1fC.\n", info.temperature_max);
        ags10_interface_debug_print("ags10: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start basic read test */
    ags10_interface_debug_print("ags10: start read test.\n");
    
    /* ags10 init */
    res = ags10_init(&gs_handle);
    if (res != 0)
    {
        ags10_interface_debug_print("ags10: init failed.\n");
       
        return 1;
    }
    
    /* get version */
    res = ags10_get_version(&gs_handle, &version);
    if (res != 0)
    {
        ags10_interface_debug_print("ags10: get version failed.\n");
        (void)ags10_deinit(&gs_handle);
       
        return 1;
    }
    
    /* print result */
    ags10_interface_debug_print("ags10: version is 0x%02X.\n", version);
    
    /* delay 2000 ms for read */
    ags10_interface_delay_ms(2000);
    for (i = 0; i < times; i++)
    {
        /* read tvoc */
        res = ags10_read_tvoc(&gs_handle, (uint32_t *)&raw, (uint32_t *)&ppb);
        if (res != 0)
        {
            ags10_interface_debug_print("ags10: read tvoc failed.\n");
            (void)ags10_deinit(&gs_handle);
           
            return 1;
        }
    
        /* print result */
        ags10_interface_debug_print("ags10: tvoc is %dppb.\n", ppb);

        /* delay 2000 ms*/
        ags10_interface_delay_ms(2000);
    }

    /* get resistance */
    res = ags10_get_resistance(&gs_handle, &raw, &ohm);
    if (res != 0)
    {
        ags10_interface_debug_print("ags10: get resistance failed.\n");
        (void)ags10_deinit(&gs_handle);
       
        return 1;
    }
    
    /* print result */
    ags10_interface_debug_print("ags10: resistance is %0.2fohm.\n", ohm);
    
    /* delay 2000 ms for read */
    ags10_interface_delay_ms(2000);
    
    reg = rand() % 0xFFFFU;
    res = ags10_zero_point_calibration(&gs_handle, reg);
    if (res != 0)
    {
        ags10_interface_debug_print("ags10: zero point calibration failed.\n");
        (void)ags10_deinit(&gs_handle);
       
        return 1;
    }
    
    /* print result */
    ags10_interface_debug_print("ags10: zero point calibration 0x%04X.\n", reg);
    
    /* delay 2000 ms*/
    ags10_interface_delay_ms(2000);
    
    /* current resistance zero point calibration  */
    res = ags10_current_resistance_zero_point_calibration(&gs_handle);
    if (res != 0)
    {
        ags10_interface_debug_print("ags10: current resistance zero point calibration failed.\n");
        (void)ags10_deinit(&gs_handle);
       
        return 1;
    }
    
    /* print result */
    ags10_interface_debug_print("ags10: current resistance zero point calibration.\n");
    
    /* delay 2000 ms*/
    ags10_interface_delay_ms(2000);
    
    /* reset zero point calibration */
    res = ags10_reset_zero_point_calibration(&gs_handle);
    if (res != 0)
    {
        ags10_interface_debug_print("ags10: reset zero point calibration failed.\n");
        (void)ags10_deinit(&gs_handle);
       
        return 1;
    }
    
    /* print result */
    ags10_interface_debug_print("ags10: reset zero point calibration.\n");
    
    /* delay 2000 ms*/
    ags10_interface_delay_ms(2000);
    
    addr_7bit = 0x1A;
    res = ags10_modify_slave_address(&gs_handle, addr_7bit);
    if (res != 0)
    {
        ags10_interface_debug_print("ags10: modify slave address failed.\n");
        (void)ags10_deinit(&gs_handle);
       
        return 1;
    }
    
    /* print result */
    ags10_interface_debug_print("ags10: modify slave address 0x%02X.\n", addr_7bit);
    
    /* finish read test */
    ags10_interface_debug_print("ags10: finish read test.\n");
    (void)ags10_deinit(&gs_handle);
    
    return 0;
}
