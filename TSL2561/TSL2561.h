/*
 * mbed library program
 *  Luminosity sensor -- LIGHT-TO-DIGITAL CONVERTER (light intensity to a digital signal output)
 *  TSL2561 by Texas Advanced Optoelectronic Solutions Inc.
 *
 * Copyright (c) 2015,'17,'18 Kenji Arai / JH1PJL
 *  http://www.page.sannet.ne.jp/kenjia/index.html
 *  http://mbed.org/users/kenjiArai/
 *      Created: Feburary   21st, 2015
 *      Revised: August     23rd, 2017
 *      Revised: Feburary   20th, 2018   bug fix -> read_ID() & who_am_i()
 *                                       Thanks PARK JAICHANG
 */
/*
 *---------------- REFERENCE ----------------------------------------------------------------------
 *  https://docs.google.com/viewer?url=http%3A%2F%2Fwww.adafruit.com%2Fdatasheets%2FTSL256x.pdf
 *  https://learn.adafruit.com/tsl2561?view=all
 *  http://www.adafruit.com/products/439
 *  http://akizukidenshi.com/catalog/g/gM-08219/
 */
 
#ifndef TSL2561_H
#define TSL2561_H
 
#include "mbed.h"
 
// Luminosity sensor, TSL2561
// Address b7=0,b6=1,b5=1,b4=1,b3=0,b2=0,b1=1, b0=R/W
#define TSL2561_ADDRESS_GND         (0x29 << 1)
#define TSL2561_ADDRESS_FLOAT       (0x39 << 1)
#define TSL2561_ADDRESS_VDD         (0x49 << 1)
 
////////////// Registers //////////////////////////////////
// Register definition
#define TSL2561_CONTROL             0x00
#define TSL2561_TIMING              0x01
#define TSL2561_THRESHLOWLOW        0x02
#define TSL2561_THRESHHIGHLOW       0x04
#define TSL2561_INTERRUPT           0x06
#define TSL2561_CRC                 0x08
#define TSL2561_ID                  0x0A
#define TSL2561_DATA0LOW            0x0C
#define TSL2561_DATA0HIGH           0x0D
#define TSL2561_DATA1LOW            0x0E
#define TSL2561_DATA1HIGH           0x0F
 
////////////// TIMING PARAMETER ///////////////////////////
#define TIMING_GAIN_1               (0UL << 4)
#define TIMING_GAIN_16              (1UL << 4)
#define TIMING_TIME_13R7            (0x0)
#define TIMING_TIME_101             (0x1)
#define TIMING_TIME_402             (0x2)
#define TIMING_TIME_MANU            (0x3)
#define TIMING_DEFAULT              (TIMING_GAIN_1 + TIMING_TIME_402)
 
////////////// ID /////////////////////////////////////////
#define I_AM_TSL2561CS              0x01
#define I_AM_TSL2561T_FN_CL         0x05
 
////////////// COMMAND ////////////////////////////////////
#define CMD_CMDMODE                 (1UL << 7)
#define CMD_CLEAR                   (1UL << 6)
#define CMD_WORD                    (1UL << 5)
#define CMD_BLOCK                   (1UL << 4)
#define CMD_SINGLE                  (CMD_CMDMODE)
#define CMD_MULTI                   (CMD_CMDMODE + CMD_WORD)
 
/** Interface for Luminosity sensor, TSL2561
 * @code
 * #include "mbed.h"
 * #include "TSL2561.h"
 *
 * // I2C Communication
 *  TSL2561      lum(dp5,dp27);    // TSL2561 SDA, SCL
 * // If you connected I2C line not only this device but also other devices,
 * //     you need to declare following method.
 *  I2C          i2c(dp5,dp27);    // SDA, SCL
 *  TSL2561      lum(i2c);         // TSL2561 SDA, SCL (Data available every 400mSec)
 *
 * int main() {;
 *   while(true){
 *      printf("Illuminance: %+7.2f [Lux]\r\n", lum.lux());
 *      wait(1.0);
 *   }
 * }
 * @endcode
 */
 
class TSL2561
{
public:
    /** Configure data pin
      * @param data SDA and SCL pins
      */
    TSL2561(PinName p_sda, PinName p_scl);
    TSL2561(PinName p_sda, PinName p_scl, uint8_t addr);
 
    /** Configure data pin (with other devices on I2C line)
      * @param I2C previous definition
      */
    TSL2561(I2C& p_i2c);
    TSL2561(I2C& p_i2c, uint8_t addr);
 
    /** Get approximates the human eye response
      *  in the commonly used Illuminance unit of Lux
      * @param none
      * @return Lux
      */
    float lux(void);
 
    /** Set timing register
      * @param timing parameter
      * @return timing read data
      */
    uint8_t set_timing_reg(uint8_t parameter);
 
    /** Read timing register
      * @param timing parameter
      * @return timing read data
      */
    uint8_t read_timing_reg(void);
 
    /** Set I2C clock frequency
      * @param freq.
      * @return none
      */
    void frequency(int hz);
 
    /** check Device ID number
      * @param none
      * @return TSL2561 = 1, others  0
      */
    uint8_t who_am_i(void);
 
    /** Read ID and Revision Number
      * @param none
      * @return ID + REVNO
      */
    uint8_t read_ID(void);
 
    /** Power Up/Down
      * @param none
      * @return none
      */
    void power_up(void);
    void power_down(void);
 
protected:
    I2C *_i2c_p;
    I2C &_i2c;
 
    void init(void);
 
private:
    uint8_t  TSL2561_addr;
    uint8_t  dt[4];
    uint32_t ch0;
    uint32_t ch1;
    int8_t   gain;
    uint8_t  id_number;
    double   integ_time;
};
 
#endif      // TSL2561_H
