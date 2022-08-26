#include <stdio.h>
#include "driver/gpio.h"
#include <stdint.h>
//#include <USBAPI.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "as5311.h"

extern "C"
void app_main(void)
{

AS5311* in;
//Serial.begin(9600);
in = new AS5311(GPIO_NUM_4, GPIO_NUM_3, GPIO_NUM_2);
in->setup();

while(1) {
//int16_t pos = in->readRawPosition();
//int32_t getPos = in->getPosition();
//int32_t absPos = in->calculateAbsPosition(pos);
//printf(getPos);
//ESP_LOGI(TAG, "Example configured to blink GPIO LED!");
//Serial.println(pos);
//delay(1000);
//Serial.println(absPos);
//Serial.println(getPos+1, DEC);
}

}
