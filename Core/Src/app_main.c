#include "app_main.h"
#include "Max31856.h"
#include <stdio.h>
#include <string.h>


// Estructura para cada sensor//
//is git updated?
Max31856_HandleTypeDef mySensor1;
Max31856_HandleTypeDef mySensor2;
Max31856_HandleTypeDef mySensor3;
Max31856_HandleTypeDef mySensor4;

extern SPI_HandleTypeDef hspi2;
extern UART_HandleTypeDef huart1;

const char MSG_INIT_ERROR[] = "Error: Could not initialize thermocouple\n\r";
const char MSG_THERMO_PREFIX[] = "T1: %.2f, T2: %.2f, T3: %.2f , T4: %.2f C\n\r";

// Puedes aumentar el buffer para estar seguro
#define TOTAL_MESSAGE_BUFFER_SIZE (64)


void app_main(void)
{
    if (!MAX31856_Init(&mySensor1, &hspi2, SPI_CS1_GPIO_Port, SPI_CS1_Pin)) {
        HAL_UART_Transmit(&huart1, (uint8_t*)MSG_INIT_ERROR, strlen(MSG_INIT_ERROR), HAL_MAX_DELAY);
        while (1) HAL_Delay(10);
    }
    if (!MAX31856_Init(&mySensor2, &hspi2, SPI_CS2_GPIO_Port, SPI_CS2_Pin)) {
        HAL_UART_Transmit(&huart1, (uint8_t*)MSG_INIT_ERROR, strlen(MSG_INIT_ERROR), HAL_MAX_DELAY);
        while (1) HAL_Delay(10);
    }
    if (!MAX31856_Init(&mySensor3, &hspi2, SPI_CS3_GPIO_Port, SPI_CS3_Pin)) {
        HAL_UART_Transmit(&huart1, (uint8_t*)MSG_INIT_ERROR, strlen(MSG_INIT_ERROR), HAL_MAX_DELAY);
        while (1) HAL_Delay(10);
    }

    if (!MAX31856_Init(&mySensor3, &hspi2, SPI_CS4_GPIO_Port, SPI_CS4_Pin)) {
            HAL_UART_Transmit(&huart1, (uint8_t*)MSG_INIT_ERROR, strlen(MSG_INIT_ERROR), HAL_MAX_DELAY);
            while (1) HAL_Delay(10);
    }

    HAL_Delay(200);

    float temp1, temp2, temp3,temp4;
    char combined_buffer[TOTAL_MESSAGE_BUFFER_SIZE];

    while (1)
    {
        temp1 = MAX31856_ReadThermocoupleTemperature(&mySensor1);
        temp2 = MAX31856_ReadThermocoupleTemperature(&mySensor2);
        temp3 = MAX31856_ReadThermocoupleTemperature(&mySensor3);
        temp4 = MAX31856_ReadThermocoupleTemperature(&mySensor4);

        sprintf(combined_buffer, MSG_THERMO_PREFIX, temp1, temp2, temp3,temp4);
        HAL_UART_Transmit(&huart1, (uint8_t*)combined_buffer, strlen(combined_buffer), HAL_MAX_DELAY);

        // HAL_Delay(20); // opcional
    }
}
