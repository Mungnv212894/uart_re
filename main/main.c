#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_log.h"
#include <string.h> // Đảm bảo thư viện này được bao gồm

#define UART_PORT_NUM UART_NUM_1
#define UART_TX_PIN 17
#define UART_RX_PIN 16
#define UART_BAUD_RATE 115200
#define UART_BUF_SIZE 1024

void uart_init(void)
{
    uart_config_t uart_config = {
        .baud_rate = UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE};
    uart_param_config(UART_PORT_NUM, &uart_config);
    uart_set_pin(UART_PORT_NUM, UART_TX_PIN, UART_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_PORT_NUM, UART_BUF_SIZE, UART_BUF_SIZE, 0, NULL, 0);
}

void app_main(void)
{
    uart_init();
    char recv_buf[UART_BUF_SIZE];

    while (1)
    {
        // Đọc dữ liệu từ UART
        int len = uart_read_bytes(UART_PORT_NUM, (uint8_t *)recv_buf, UART_BUF_SIZE - 1, 100 / portTICK_PERIOD_MS);
        if (len > 0)
        {
            recv_buf[len] = '\0'; // Kết thúc chuỗi nhận được
            ESP_LOGI("UART", "Received: %s", recv_buf);
        }
    }
}
