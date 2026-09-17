#include "sdk_project_config.h"
#include "stdio.h"
#include "string.h"
#include "stdint.h"
int main(void)
{
	CLOCK_DRV_Init(&clockMan1_InitConfig0); // Intialize clock
	PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0 ,g_pin_mux_InitConfigArr0); // Intialize Pin
	LPUART_DRV_Init(INST_LPUART_1, &lpUartState0, &lpuart_0_InitConfig0);
	ADC_Init(&adc_pal_1_instance, &adc_pal_1_config);
	char txBuff[64];
	while(1)
	{
		ADC_StartGroupConversion(&adc_pal_1_instance, 0u);
		uint16_t Adcstatus=adc_pal_1_results0[0u];
		uint16_t voltage=(((4095-Adcstatus)*3300)/4095);
		uint8_t len= (uint8_t) sprintf(txBuff,"ADC Value=%u\t Voltage=%u mV \r\n", Adcstatus, voltage);
		LPUART_DRV_SendDataBlocking(INST_LPUART_1, (const uint8_t*)txBuff, len,1000U);
		OSIF_TimeDelay(500);
	}
}
