#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "serial.h"
//#include "memoria.h"
#include <inttypes.h> 


extern "C" void app_main() ;

void app_main() {
    serial.begin(9600);
    printf("Funcionando....\n");
}