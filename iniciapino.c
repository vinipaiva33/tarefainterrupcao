#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "iniciapino.h"
void pinosInit()
{
    // Inicializa o pino do LED RGB e configura pro GPIO13
    gpio_init(PIN_LED_R);
    gpio_set_dir(PIN_LED_R, GPIO_OUT);

    // Configurar o pino do botão A e B e habilitar o pull-up interno
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);
}