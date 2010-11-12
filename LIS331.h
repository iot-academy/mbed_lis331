/**
 * @section LICENSE
 *
 *
 * @section DESCRIPTION
 *
 * LIS331 triple axis, digital interface, accelerometer.
 * Based off Aaron Berk's ITG3200 Gyro Library
 *
 * Datasheet:
 *
 * http://www.st.com/stonline/products/literature/ds/13951.pdf
 */

#ifndef LIS331_H
#define LIS331_H

/**
 * Includes
 */
#include "mbed.h"

/**
 * Defines
 */
#define LIS331_I2C_ADDRESS 0x19 //7-bit address.

//-----------
// Registers
//-----------
#define WHO_AM_I_REG    0x0F
#define ACCEL_XOUT_H_REG 0x29
#define ACCEL_XOUT_L_REG 0x28
#define ACCEL_YOUT_H_REG 0x2B
#define ACCEL_YOUT_L_REG 0x2A
#define ACCEL_ZOUT_H_REG 0x2D
#define ACCEL_ZOUT_L_REG 0x2C



#define CTRL_REG_1      0x20
#define CTRL_REG_2      0x21
#define CTRL_REG_3      0x22
#define CTRL_REG_4      0x23
#define CTRL_REG_5      0x24

#define STATUS_REG      0x27


//------------------------------
// Power Mode and Output Data Rates
//------------------------------
#define POWER_DOWN   0x6F
#define NORMAL_50HZ   0x27
#define NORMAL_100HZ   0x2F
#define NORMAL_400HZ   0x37
#define NORMAL_1000HZ   0x3F
#define LOW_POWER_0_5HZ   0x47
#define LOW_POWER_1HZ   0x67
#define LOW_POWER_2HZ   0x87
#define LOW_POWER_5HZ   0xA7
#define LOW_POWER_10HZ   0xC7

/**
 * LIS331 triple axis digital accelerometer.
 */
class LIS331 {

public:

    /**
     * Constructor.
     *
     * Sets FS_SEL to 0x03 for proper opertaion.
     *
     * @param sda - mbed pin to use for the SDA I2C line.
     * @param scl - mbed pin to use for the SCL I2C line.
     */
    LIS331(PinName sda, PinName scl);

    /**
     * Get the identity of the device.
     *
     * @return The contents of the Who Am I register which contains the I2C
     *         address of the device.
     */
    char getWhoAmI(void);

  
    
    /**
     * Get the current power mode
     *
     * @return 
     */
    
    //char getPowerMode(void);

    
    
    
    /**
     * Set the power mode (power down, low power, normal mode)
     *
     *
     * @param 
     *
     *  Power Mode | Output Data Rate (Hz) | Low-pass Filter Cut off (Hz) | #define
     *  --------------------------------------------------------------------------------
     *  Power-down |          --           |               --             | POWER_DOWN
     *    Normal   |          50           |               37             | NORMAL_50HZ
     *    Normal   |         100           |               74             | NORMAL_100HZ
     *    Normal   |         400           |              292             | NORMAL_400HZ
     *    Normal   |        1000           |              780             | NORMAL_1000HZ
     *   Low-power |         0.5           |               --             | LOW_POWER_0_5HZ
     *   Low-power |           1           |               --             | LOW_POWER_1HZ
     *   Low-power |           2           |               --             | LOW_POWER_2HZ
     *   Low-power |           5           |               --             | LOW_POWER_5HZ
     *   Low-power |          10           |               --             | LOW_POWER_10HZ
     */
    
    //void setPowerMode(char powermode);

    
    char getInterruptConfiguration(void);

    /**
     * Set the interrupt configuration.
     *
     * See datasheet for configuration byte details.
     *
     *    7        6       5      4
     * +-------+-------+------+--------+
     * |  IHL  | PP_OD | LIR2 | I2_CFG |
     * +-------+-------+------+--------+
     *
     *      3        2       1         0
     * +---------+------+---------+---------+
     * | I2_CFG0 | LIR1 | I1_CFG1 | I1-CFG0 |
     * +---------+------+---------+---------+
     *
     * IHL Interrupt active high or low. 0:active high; 1:active low (default:0)
     * PP_OD Push-pull/Open drain selection on interrupt pad. 0:push-pull; 1:open drain (default:0)
     * LIR2 Latch interupt request on INT2_SRC register, with INT2_SRC register cleared by reading INT2_SRC itself
     *      0: irq not latched; 1:irq latched (default:0)
     * I2_CFG1, I2_CFG0 See datasheet table
     * LIR1 Latch interupt request on INT1_SRC register, with INT1_SRC register cleared by reading INT1_SRC itself
     *      0: irq not latched; 1:irq latched (default:0)
     * I1_CFG1, I1_CFG0 See datasheet table
     *
     * @param config Configuration byte to write to INT_CFG register.
     */
   
   
   // void setInterruptConfiguration(char config);

    /**
     * Check the status register
     *
     * @return 
     *
     */
            
    char getAccelStatus(void);




    /**
     * Get the temperature of the device.
     *
     * @return The temperature in degrees celsius.
     */
    //float getTemperature(void);

    /**
     * Get the output for the x-axis gyroscope.
     *
     * Typical sensitivity is 14.375 LSB/(degrees/sec).
     *
     * @return The output on the x-axis in raw ADC counts.
     */
    int getAccelX(void);

    /**
     * Get the output for the y-axis gyroscope.
     *
     * Typical sensitivity is 14.375 LSB/(degrees/sec).
     *
     * @return The output on the y-axis in raw ADC counts.
     */
    int getAccelY(void);

    /**
     * Get the output on the z-axis gyroscope.
     *
     * Typical sensitivity is 14.375 LSB/(degrees/sec).
     * 
     * @return The output on the z-axis in raw ADC counts.
     */
    int getAccelZ(void);

    /**
     * Get the power management configuration.
     *
     * See the datasheet for register contents details.
     *
     *     7        6        5         4
     * +---------+-------+---------+---------+
     * | H_RESET | SLEEP | STBY_XG | STBY_YG |
     * +---------+-------+---------+---------+
     *
     *      3          2         1          0
     * +---------+----------+----------+----------+
     * | STBY_ZG | CLK_SEL2 | CLK_SEL1 | CLK_SEL0 |
     * +---------+----------+----------+----------+
     *
     * H_RESET Reset device and internal registers to the power-up-default settings.
     * SLEEP Enable low power sleep mode.
     * STBY_XG Put gyro X in standby mode (1=standby, 0=normal).
     * STBY_YG Put gyro Y in standby mode (1=standby, 0=normal).
     * STBY_ZG Put gyro Z in standby mode (1=standby, 0=normal).
     * CLK_SEL Select device clock source:
     *
     * CLK_SEL | Clock Source
     * --------+--------------
     *    0      Internal oscillator
     *    1      PLL with X Gyro reference
     *    2      PLL with Y Gyro reference
     *    3      PLL with Z Gyro reference
     *    4      PLL with external 32.768kHz reference
     *    5      PLL with external 19.2MHz reference
     *    6      Reserved
     *    7      Reserved
     *
     * @return The contents of the PWR_MGM register.
     */
   // char getPowerManagement(void);

    /**
     * Set power management configuration.
     *
     * See the datasheet for configuration byte details
     *
     *      7        6        5         4
     * +---------+-------+---------+---------+
     * | H_RESET | SLEEP | STBY_XG | STBY_YG |
     * +---------+-------+---------+---------+
     *
     *      3          2         1          0
     * +---------+----------+----------+----------+
     * | STBY_ZG | CLK_SEL2 | CLK_SEL1 | CLK_SEL0 |
     * +---------+----------+----------+----------+
     *
     * H_RESET Reset device and internal registers to the power-up-default settings.
     * SLEEP Enable low power sleep mode.
     * STBY_XG Put gyro X in standby mode (1=standby, 0=normal).
     * STBY_YG Put gyro Y in standby mode (1=standby, 0=normal).
     * STBY_ZG Put gyro Z in standby mode (1=standby, 0=normal).
     * CLK_SEL Select device clock source:
     *
     * CLK_SEL | Clock Source
     * --------+--------------
     *    0      Internal oscillator
     *    1      PLL with X Gyro reference
     *    2      PLL with Y Gyro reference
     *    3      PLL with Z Gyro reference
     *    4      PLL with external 32.768kHz reference
     *    5      PLL with external 19.2MHz reference
     *    6      Reserved
     *    7      Reserved
     *
     * @param config The configuration byte to write to the PWR_MGM register.
     */
   // void setPowerManagement(char config);

private:

    I2C i2c_;

};

#endif /* LIS331_H */
 
