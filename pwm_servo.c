#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Definição dos pinos
#define SERVO 22
#define LED_R 12

// Definição PWM
#define FREQUENCIA 50     // 50Hz (Período de 20ms)
#define ALTO 2400          // 180 graus -> 2400µs
#define MEIO 1470          // 90 graus -> 1470µs
#define BAIXO 500          // 0 graus -> 500µs
#define ESPERA 5000        // Espera de 5 segundos em cada posição
#define ATRASO 10          // Atraso de 10ms entre incrementos
#define PASSO 5            // Passo de incremento do PWM

const float DIVISOR_PWM = 64.0f;  // Ajuste fino do clock PWM
const uint16_t PERIODO = 20000;   // Período do PWM em microsegundos (20ms)

// Declaração das funções
void inicializar_servo();
void inicializar_led();
void pulso_PWM(uint pin, uint pulso);
void oscilar_led(uint pulso);

int main()
{
    stdio_init_all();// inicia programa
    sleep_ms(2000); // Delay inicial para estabilizar o sistema

    inicializar_servo();
    inicializar_led();

    // Movimentos iniciais
    pulso_PWM(SERVO, ALTO);  // Posição 180 graus
    oscilar_led(ALTO);       // LED com brilho correspondente a 180 graus
    sleep_ms(ESPERA);

    pulso_PWM(SERVO, MEIO);  // Posição 90 graus
    oscilar_led(MEIO);       // LED com brilho correspondente a 90 graus
    sleep_ms(ESPERA);
    
    pulso_PWM(SERVO, BAIXO); // Posição 0 graus
    oscilar_led(BAIXO);      // LED com brilho correspondente a 0 graus
    sleep_ms(ESPERA);

    // Movimentação suave entre os pontos
    while (true) {
        // Do 0 graus (BAIXO) até 180 graus (ALTO)
        for (int pulso = BAIXO; pulso <= ALTO; pulso += PASSO) {
            pulso_PWM(SERVO, pulso);
            oscilar_led(pulso);
            sleep_ms(ATRASO);
        }

        // De 180 graus (ALTO) até 0 graus (BAIXO)
        for (int pulso = ALTO; pulso >= BAIXO; pulso -= PASSO) {
            pulso_PWM(SERVO, pulso);
            oscilar_led(pulso);
            sleep_ms(ATRASO);
        }
    }
}

// Inicializa o PWM para o servo motor
void inicializar_servo(){
    uint slice = pwm_gpio_to_slice_num(SERVO);
    gpio_set_function(SERVO, GPIO_FUNC_PWM);
    pwm_set_clkdiv(slice, DIVISOR_PWM);  // Ajuste da frequência
    pwm_set_wrap(slice, PERIODO);        // Define o período para 20ms (50Hz)
    pwm_set_enabled(slice, true);
}

// Ajusta o pulso PWM do servo (conversão para nível correto)
void pulso_PWM(uint pin, uint pulso){
    uint slice = pwm_gpio_to_slice_num(pin);
    uint wrap = pwm_hw->slice[slice].top;
    
    // Ajuste proporcional correto para pulsos de 500µs a 2400µs dentro de 20ms (50Hz)
    uint level = (pulso * wrap) / PERIODO;
    
    pwm_set_gpio_level(pin, level);
}

// Inicializa o LED PWM
void inicializar_led(){
    uint slice = pwm_gpio_to_slice_num(LED_R);
    gpio_set_function(LED_R, GPIO_FUNC_PWM);
    pwm_set_clkdiv(slice, 1.0f);  // Frequência do PWM do LED
    pwm_set_wrap(slice, 100);     // Período do PWM do LED
    pwm_set_enabled(slice, true);
}

// Faz o brilho do LED variar conforme a posição do servo
void oscilar_led(uint pulso){
    uint slice = pwm_gpio_to_slice_num(LED_R);
    uint wrap = pwm_hw->slice[slice].top;
    uint brilho = (pulso - BAIXO) * 100 / (ALTO - BAIXO);  // Mapeia o pulso para o brilho
    uint brilho_pwm = (brilho * wrap) / 100;  // Converte para o nível de PWM do LED
    pwm_set_gpio_level(LED_R, brilho_pwm);
}