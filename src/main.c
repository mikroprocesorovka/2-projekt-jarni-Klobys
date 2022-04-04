#include "stm8s.h"
#include "milis.h"
#include "spse_stm8.h"

#include <stdio.h>
#include "uart1.h"

#define _ISOC99_SOURCE
#define _GNU_SOURCE


void ADC_init(void){

ADC2_SchmittTriggerConfig(ADC2_SCHMITTTRIG_CHANNEL3,DISABLE); //Inicializace, nastavení a zapnutí ADC
ADC2_PrescalerConfig(ADC2_PRESSEL_FCPU_D4);
ADC2_AlignConfig(ADC2_ALIGN_RIGHT);
ADC2_Select_Channel(ADC2_CHANNEL_3);
ADC2_Cmd(ENABLE);
ADC2_Startup_Wait();
}

void setup(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz
    init_milis(); //inicializace mmilisu
    ADC_init(); // vyvolám ADC
    init_uart1(); //vyvolám uart
}


int main(void)
{
    uint32_t time = 0; //inicializace proměnných
    uint16_t adc_hodnota;
    uint16_t teplota;

    setup();  

    while (1) {
     if (milis()-time>1000){ //každých 1000ms se provede tato funkce
        time = milis();
        
        adc_hodnota = ADC_get(ADC2_CHANNEL_3); // do adc_hodnota uložím výsledek převodu vstupu ADC_IN3 (PB3)
        teplota = adc_hodnota*4.882;

        printf("teplota: %u.%u °C\r\n", teplota/10,teplota%10); //zobrazím teplotu do uartu
        }
    }
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
