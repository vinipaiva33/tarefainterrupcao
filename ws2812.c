#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "inicia.h"
#include "iniciapino.h"

int numero = 0;
static volatile uint a = 0;


// Variável global para armazenar a cor (Entre 0 e 255 para intensidade)
uint8_t led_r = 100; // Intensidade do vermelho
uint8_t led_g = 100; // Intensidade do verde
uint8_t led_b = 0; // Intensidade do azul


void gpio_irq_handler(uint gpio, uint32_t events)
{
    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    static volatile uint32_t last_timeA = 0; // Armazena o tempo do último evento (em microssegundos)
    static volatile uint32_t last_timeB = 0; // Armazena o tempo do último evento (em microssegundos)



    // Verifica se passou tempo suficiente desde o último evento

    if (gpio == BUTTON_A)
    {
        if (current_time - last_timeA > 200000)
        { // Debouncing de 200ms
            last_timeA = current_time;
            printf("A: %d\n", a); // Para controle quando se usa o monitor serial para verificar se há bouncing
            a++;
            if (numero != 9)
            {
                numero = numero + 1;

                set_one_led(led_r, led_g, led_b, numero);
            }
            else
            {
                printf("Sim\n");
            }
        }
    }
    else if (gpio == BUTTON_B)
    {
        if (current_time - last_timeB > 200000)
        {
            last_timeB = current_time;
            printf("A: %d\n", a); // Para controle quando se usa o monitor serial para verificar se há bouncing
            a++;
            // Debouncing de 200ms
            if (numero != 0)
            {
                numero = numero - 1;
                set_one_led(led_r, led_g, led_b, numero);
            }
            else{
                printf("Nao\n");
            }
        }

    }
}

int main()
{
    pio();
    stdio_init_all();
    pinosInit();

//Led com interrupção
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

//Led repetitivo
    while (true)
    {
        gpio_put(PIN_LED_R,1);
        sleep_ms(tempo);
        gpio_put(PIN_LED_R,0);
        sleep_ms(tempo);
    }
    return 0;
}
