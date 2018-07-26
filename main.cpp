#include "mbed.h"
#include "ADXL362.h"
#include "TSL2561.h"


// Device Instantiation 
ADXL362 adxl362(PA_0,PA_7,PA_6,PA_1);
TSL2561 tsl2561(PB_7,PB_6,TSL2561_ADDRESS_GND);
DigitalOut led(LED1);
Timer processtimer;
 
int main() {
  int8_t x,y,z; 
  float lux;
  adxl362.reset();
  wait_ms(600);
  adxl362.set_mode(ADXL362::MEASUREMENT);
  // tsl2561.set_timing_reg(TIMING_GAIN_16|TIMING_TIME_402);
  tsl2561.set_timing_reg(0x12); 
  while(1) {
    printf("Lux Timing Register = 0x%x\n\r",tsl2561.read_timing_reg());
    led = !led; // Toggle LED
    x=adxl362.scanx_u8();
    y=adxl362.scany_u8();
    z=adxl362.scanz_u8();
    printf("x = %d, y = %d z = %d\r\n", x, y, z);
    processtimer.start();
    lux = tsl2561.lux();
    processtimer.stop();
    printf("lux = %f, acquisition time = %f\n\r", lux, processtimer.read());
    processtimer.reset();
    wait_ms(500);
  }
}


 
            
