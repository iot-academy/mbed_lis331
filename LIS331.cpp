/**
 * @section LICENSE
 *
 *
 * @section DESCRIPTION
 *
 * LIS331DLH triple axis, digital interface, accelerometer.
 * Based off Aaron Berk's ITG3200 Gyro Library 
 *
 * Datasheet:
 *
 * http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/DATASHEET/CD00213470.pdf
 */

/**
 * Includes
 */
 
#include "LIS331.h"

LIS331::LIS331(PinName sda, PinName scl) : i2c_(sda, scl) {
    // set default scaling factor
    scaling_factor = 4096.0;
    
    //set default range to zero.
    current_range = 0;

    //400kHz, fast mode.
    i2c_.frequency(400000);
    
    
    //Power Up Device, Set Output data rate, Enable All 3 Axis
    //See datasheet for details.
    char tx[2];
    //char tx2[2];
    //char rx[1];
    tx[0] = CTRL_REG_1;
    //CTRL_REG_1 [00111111] / [0x3F] to power up, set output rate to 1000Hz, and enable all 3 axis.
    tx[1] = 0x3F;
    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, tx, 2);
    
    
    
    //set default scale of 4g's
    scaling_factor = 8192.0;
    current_range = 4;
    
    tx[0] = CTRL_REG_4;
    tx[1] = 0x10;
        
    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, tx, 2);
    
    
    
}

char LIS331::getWhoAmI(void){

    //WhoAmI Register address.
    char tx = WHO_AM_I_REG_LIS331;
    char rx;
    
    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, &tx, 1);
    
    i2c_.read((LIS331_I2C_ADDRESS << 1) | 0x01, &rx, 1);
    
    return rx;

}




void LIS331::setPowerMode(char power_mode){
// Currently sets all 3 axis to enabled. Will be set to preserve existing status in future
    char tx[2];
    tx[0] = CTRL_REG_1;
    tx[1] = power_mode;

    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, tx, 2);

}

char LIS331::getPowerMode(void){

    char tx = CTRL_REG_1;
    char rx;
    
    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, &tx, 1);
    
    i2c_.read((LIS331_I2C_ADDRESS << 1) | 0x01, &rx, 1);

    
    return rx;

}



char LIS331::getInterruptConfiguration(void){

    char tx = CTRL_REG_3;
    char rx;
    
    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, &tx, 1);
    
    i2c_.read((LIS331_I2C_ADDRESS << 1) | 0x01, &rx, 1);
    
    return rx;

}


void LIS331::setFullScaleRange8g(void){  // Does not preserve rest of CTRL_REG_4!
    scaling_factor = 4096.0;
    current_range = 8;

    char tx[2];
    tx[0] = CTRL_REG_4;
    tx[1] = 0x30;
        
    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, tx, 2);
    
}

void LIS331::setFullScaleRange4g(void){  // Does not preserve rest of CTRL_REG_4!
    scaling_factor = 8192.0;
    current_range = 4;
    
    char tx[2];
    tx[0] = CTRL_REG_4;
    tx[1] = 0x10;
        
    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, tx, 2);
    
}
    

void LIS331::setFullScaleRange2g(void){  // Does not preserve rest of CTRL_REG_4!
    scaling_factor = 16384.0;
    current_range = 2;
    
    char tx[2];
    tx[0] = CTRL_REG_4;
    tx[1] = 0x00;
        
    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, tx, 2);
    
}


char LIS331::getAccelStatus(void){

    char tx = STATUS_REG;
    char rx;
    
    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, &tx, 1);
    
    i2c_.read((LIS331_I2C_ADDRESS << 1) | 0x01, &rx, 1);
    
    return rx;
}



float LIS331::getAccelX(void){

    char tx = ACCEL_XOUT_H_REG;
    char rx[2];
    
    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, &tx, 1);
    
    i2c_.read((LIS331_I2C_ADDRESS << 1) | 0x01, rx, 2);
    
    int16_t output = ((int) rx[0] << 8) | ((int) rx[1]);

    return output/scaling_factor;

}

float LIS331::getAccelY(void){

    char tx = ACCEL_YOUT_H_REG;
    char rx[2];
    
    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, &tx, 1);
    
    i2c_.read((LIS331_I2C_ADDRESS << 1) | 0x01, rx, 2);
    
    int16_t output = ((int) rx[0] << 8) | ((int) rx[1]);

    return output/scaling_factor;

}

float LIS331::getAccelZ(void){

    char tx = ACCEL_ZOUT_H_REG;
    char rx[2];
    
    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, &tx, 1);
    
    i2c_.read((LIS331_I2C_ADDRESS << 1) | 0x01, rx, 2);
    
    int16_t output = ((int) rx[0] << 8) | ((int) rx[1]);

    return output/scaling_factor;
}