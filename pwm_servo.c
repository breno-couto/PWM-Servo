#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Definição dos pinos
#define SERVO 22
#define LED_R 12

// Definição PWM
#define FREQUENCIA 50
#define MEIO 1470
#define ALTO 2400
#define BAIXO 500
#define ESPERA 5000
#define ATRASO 10
#define PASSO 3

const float DIVISOR_PWM = 16;
const uint16_t PERIODO = 2000;

// Declaração das funções antes da main()
void inicializar_servo();
void inicializar_led();
void pulso_PWM(uint pin, uint pulso);
void oscilar_led(uint pulso);

int main()
{
    stdio_init_all();
    inicializar_servo();
    inicializar_led();

    pulso_PWM(SERVO, ALTO);
    oscilar_led(ALTO);
    sleep_ms(ESPERA);

    pulso_PWM(SERVO, MEIO);
    oscilar_led(MEIO);
    sleep_ms(ESPERA);
    
    pulso_PWM(SERVO, BAIXO);
    oscilar_led(BAIXO);
    sleep_ms(ESPERA);

    while (true) {
        for (int pulso = BAIXO; pulso <= ALTO; pulso += PASSO){
            pulso_PWM(SERVO, pulso);
            oscilar_led(pulso);
            sleep_ms(ATRASO);
        }

        for (int pulso = ALTO; pulso >= BAIXO; pulso -= PASSO){
            pulso_PWM(SERVO, pulso);
            oscilar_led(pulso);
            sleep_ms(ATRASO);
        }
    }
}

void inicializar_servo(){
    uint slice = pwm_gpio_to_slice_num(SERVO);
    gpio_set_function(SERVO, GPIO_FUNC_PWM);
    pwm_set_clkdiv(slice, 64.0f);
    pwm_set_wrap(slice, 12500);
    pwm_set_enabled(slice, true);
}

void pulso_PWM(uint pin, uint pulso){
    uint slice = pwm_gpio_to_slice_num(pin);
    uint wrap = pwm_hw->slice[slice].top;
    pwm_set_gpio_level(pin, (pulso * wrap) / 20000);
}

void inicializar_led(){
    uint slice = pwm_gpio_to_slice_num(LED_R);
    gpio_set_function(LED_R, GPIO_FUNC_PWM);
    pwm_set_clkdiv(slice, 1.0f);
    pwm_set_wrap(slice, 100);
    pwm_set_enabled(slice, true);
}

void oscilar_led(uint pulso){
    uint slice = pwm_gpio_to_slice_num(LED_R);
    uint wrap = pwm_hw->slice[slice].top;
    uint brilho = (pulso - BAIXO) * 100 / (ALTO - BAIXO);
    uint brilho_pwm = (brilho * wrap) / 100;
    pwm_set_gpio_level(LED_R, brilho_pwm);
}