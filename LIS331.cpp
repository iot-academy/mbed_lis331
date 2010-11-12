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

/**
 * Includes
 */
#include "LIS331.h"

LIS331::LIS331(PinName sda, PinName scl) : i2c_(sda, scl) {

    //400kHz, fast mode.
    i2c_.frequency(400000);
    
    
    //Power Up Device, Set Output data rate, Enable All 3 Axis
    //See datasheet for details.
    char tx[2];
    tx[0] = CTRL_REG_1;
    //CTRL_REG_1 [00111111] / [0x3F] to power up, set output rate to 1000Hz, and enable all 3 axis.
    tx[1] = 0x3F;
    
    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, tx, 2);
    
}

char LIS331::getWhoAmI(void){

    //WhoAmI Register address.
    char tx = WHO_AM_I_REG;
    char rx;
    
    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, &tx, 1);
    
    i2c_.read((LIS331_I2C_ADDRESS << 1) | 0x01, &rx, 1);
    
    return rx;

}


/* Needs to be implemented
char LIS331::getPowerMode(void){

    char tx = CTRL_REG_1;
    char rx;
    
    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, &tx, 1);
    
    i2c_.read((LIS331_I2C_ADDRESS << 1) | 0x01, &rx, 1);

    
    return rx;

}

*/



void LIS331::setPowerMode(char power_mode){
// Currently sets all 3 axis to enabled. Will be set to preserve existing status in future
    char tx[2];
    tx[0] = CTRL_REG_1;
    tx[1] = power_mode;

    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, tx, 2);

}


/*
int LIS331::getInternalSampleRate(void){

    char tx = DLPF_FS_REG;
    char rx;
    
    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, &tx, 1);
    
    i2c_.read((LIS331_I2C_ADDRESS << 1) | 0x01, &rx, 1);
    
    //DLPF_CFG == 0 -> sample rate = 8kHz.
    if(rx == 0){
        return 8;
    } 
    //DLPF_CFG = 1..7 -> sample rate = 1kHz.
    else if(rx >= 1 && rx <= 7){
        return 1;
    }
    //DLPF_CFG = anything else -> something's wrong!
    else{
        return -1;
    }
    
}


*/



char LIS331::getInterruptConfiguration(void){

    char tx = CTRL_REG_3;
    char rx;
    
    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, &tx, 1);
    
    i2c_.read((LIS331_I2C_ADDRESS << 1) | 0x01, &rx, 1);
    
    return rx;

}





/*
void LIS331::setInterruptConfiguration(char config){

    char tx[2];
    tx[0] = INT_CFG_REG;
    tx[1] = config;
    
    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, tx, 2);

}

*/



/*
bool LIS331::isPllReady(void){

    char tx = INT_STATUS;
    char rx;
    
    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, &tx, 1);
    
    i2c_.read((LIS331_I2C_ADDRESS << 1) | 0x01, &rx, 1);
    
    //ITG_RDY bit is bit 4 of INT_STATUS register.
    if(rx & 0x04){
        return true;
    }
    else{
        return false;
    }
    
}

*/



char LIS331::getAccelStatus(void){

    char tx = STATSUS_REG;
    char rx;
    
    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, &tx, 1);
    
    i2c_.read((LIS331_I2C_ADDRESS << 1) | 0x01, &rx, 1);
    
    return rx;
    }
    
}


int LIS331::getAccelX(void){

    char tx = ACCEL_XOUT_H_REG;
    char rx[2];
    
    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, &tx, 1);
    
    i2c_.read((LIS331_I2C_ADDRESS << 1) | 0x01, rx, 2);
    
    int16_t output = ((int) rx[1] << 8) | ((int) rx[0]);

    return output;

}

int LIS331::getAccelY(void){

    char tx = ACCEL_YOUT_H_REG;
    char rx[2];
    
    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, &tx, 1);
    
    i2c_.read((LIS331_I2C_ADDRESS << 1) | 0x01, rx, 2);
    
    int16_t output = ((int) rx[1] << 8) | ((int) rx[0]);

    return output;

}

int LIS331::getAccelZ(void){

    char tx = ACCEL_ZOUT_H_REG;
    char rx[2];
    
    i2c_.write((LIS331_I2C_ADDRESS << 1) & 0xFE, &tx, 1);
    
    i2c_.read((LIS331_I2C_ADDRESS << 1) | 0x01, rx, 2);
    
    int16_t output = ((int) rx[1] << 8) | ((int) rx[0]);

    return output;
}


