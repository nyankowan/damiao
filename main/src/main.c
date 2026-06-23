#include "damiao.h"
#include "freertos/projdefs.h"
#include <stdio.h>

#define TWAI_TX GPIO_NUM_21
#define TWAI_RX GPIO_NUM_22 

#define MASTER_ID 0x00
#define SLAVE_ID 0x01

void app_main(void)
{
    twai_init(TWAI_TX,TWAI_RX);

    vTaskDelay(pdMS_TO_TICKS(1000));

    dm_enable(SLAVE_ID, pdMS_TO_TICKS(10));

    vTaskDelay(pdMS_TO_TICKS(100));

    while (1)
    {
        printf("send\n");
        dm_transmit_torque(SLAVE_ID, 0.5f, pdMS_TO_TICKS(1));

        dm_feedback_t fb;

        if (dm_receive(MASTER_ID, &fb, pdMS_TO_TICKS(10)))
        {
            dump_dm_feedback(&fb);
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}