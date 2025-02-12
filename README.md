# PWM-Servo
Atividade 1 - Aula Síncrona 06/02 - EmbarcaTech

Controle de Servomotor com PWM
Este projeto visa controlar um servomotor utilizando um sinal PWM gerado na GPIO 22 de um microcontrolador, realizando movimentações do braço do servomotor em diferentes ângulos, de acordo com as especificações fornecidas.

Funcionalidades
1. Configuração da Frequência de PWM
A frequência do PWM é configurada para aproximadamente 50Hz (período de 20ms). Isso garante a operação correta do servomotor, que requer essa frequência para funcionar de forma eficiente.

2. Posição do Servomotor - 180 graus
O ciclo ativo do módulo PWM é configurado para 2.400µs (microsegundos), o que corresponde a um Duty Cycle de 12%. Essa configuração ajusta o braço do servomotor para a posição de aproximadamente 180 graus. Após isso, o sistema aguarda 5 segundos nesta posição.

3. Posição do Servomotor - 90 graus
O ciclo ativo do módulo PWM é configurado para 1.470µs (microsegundos), resultando em um Duty Cycle de 7,35%. Isso move o braço do servomotor para a posição de aproximadamente 90 graus, aguardando 5 segundos nesta posição.

4. Posição do Servomotor - 0 graus
O ciclo ativo do módulo PWM é configurado para 500µs (microsegundos), o que corresponde a um Duty Cycle de 2,5%. Isso move o braço do servomotor para a posição de aproximadamente 0 graus, com uma espera de 5 segundos nesta posição.

5. Movimentação Periódica
Após as configurações anteriores, o sistema executa uma rotina que realiza uma movimentação periódica e suave do braço do servomotor entre os ângulos de 0 a 180 graus. A movimentação é ajustada de forma gradual, com um incremento de ciclo ativo de ±5µs e um atraso de 10ms entre os ajustes, garantindo que o movimento seja suave.
