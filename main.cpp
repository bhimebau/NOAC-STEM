#include "mbed.h"
#include "ADXL362.h"
#include "TSL2561.h"


// Device Instantiation 
ADXL362 adxl362(PA_0,PA_7,PA_6,PA_1);
TSL2561 tsl2561(PB_7,PB_6,TSL2561_ADDRESS_GND);
DigitalOut led(LED1);
Timer processtimer;
InterruptIn lightsensor(PA_3); 

int count = 0;
float lux = 0;
int lightdata_avail = 0;


void process_light_data(void) {
  lightdata_avail = 1;
  // tsl2561.clear_interrupt_flag();
  // processtimer.stop();
  // tsl2561.clear_interrupt_flag();
  // lux = tsl2561.lux();
  //  tsl2561.set_interrupt_reg(0x10);
  // printf("lux = %f, acquisition time = %f\n\r", lux, processtimer.read());
  // processtimer.reset();
  // processtimer.start();
  // led = led ^ 1; // Toggle LED
  count++;
  //  printf("count=%d\n\r",count);
}

int main() {
  // int8_t x,y,z; 
  adxl362.reset();
  wait_ms(600);
  printf("\n\rReset Start\n\r");
  adxl362.set_mode(ADXL362::MEASUREMENT);
  // tsl2561.set_timing_reg(TIMING_GAIN_16|TIMING_TIME_402);
  lightsensor.mode(PullUp);
  lightsensor.fall(&process_light_data);
  tsl2561.set_timing_reg(0x12); 
  tsl2561.set_interrupt_reg(0x10);
  tsl2561.clear_interrupt_flag();
  led=0;
  
  while(1) {
    if (lightdata_avail) {
      lightdata_avail = 0;
      tsl2561.clear_interrupt_flag();
      lux = tsl2561.lux();
      printf("lux=%f\n\r",lux);
    }
      
      
    // printf("Lux Timing Register = 0x%x\n\r",tsl2561.read_timing_reg());
    // led = !led; // Toggle LED
    // x=adxl362.scanx_u8();
    // y=adxl362.scany_u8();
    // z=adxl362.scanz_u8();
    //  printf("x = %d, y = %d z = %d\r\n", x, y, z);
    // printf("Interrupt Register 0x%0x 0x%0x\n\r",tsl2561.read_interrupt_reg(),count);
    // printf("lux=%f\n\r",lux);

    // processtimer.start();
    // lux = tsl2561.lux();
    // processtimer.stop();
    // printf("lux = %f, acquisition time = %f\n\r", lux, processtimer.read());
    // processtimer.reset();
    //wait_ms(1);
  }
}


 
            
