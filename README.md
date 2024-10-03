# Controle de Acesso com Teclado, Display LCD e Servo Motor 🔒

Este repositório contém um programa para Arduino que implementa um sistema de controle de acesso utilizando um teclado, um display LCD e um servo motor. O sistema requer que o usuário digite uma senha no teclado; se a senha estiver correta, a porta controlada pelo servo motor é aberta.

## 📁 Estrutura do Projeto

O código é composto pelo seguinte arquivo principal:

- **Controle-de-Acesso-com-Teclado-Display-LCD-e-Servo-Motor.c**: Implementação do sistema de controle de acesso, incluindo a lógica de verificação de senha e controle do servo motor.

## Funcionamento

### Funcionalidades

- **Digitação da senha**: O programa permite que o usuário digite uma senha de quatro dígitos usando um teclado matricial de 4x4.
- **Verificação da senha**: Após o usuário digitar a senha, o programa verifica se a senha está correta. Se estiver correta, a porta é aberta gradualmente pelo servo motor.
- **Tentativas de senha incorretas**: Se o usuário digitar uma senha incorreta, o programa registra o erro e permite até três tentativas. Após três tentativas incorretas, o acesso é bloqueado por 10 segundos.

## 🚀 Como Usar

1. Monte o circuito conforme necessário, conectando o teclado, o display LCD e o servo motor ao Arduino.
2. Carregue o código para o seu Arduino utilizando o ambiente de desenvolvimento Arduino IDE ou outro software compatível.
3. Abra o monitor serial para visualizar as mensagens de status e instruções do sistema.
4. Digite a senha de quatro dígitos usando o teclado matricial.
5. Se a senha estiver correta, a porta será aberta gradualmente pelo servo motor e a mensagem "PORTA ABERTA" será exibida no display LCD.
6. Se a senha estiver incorreta, o programa registrará a tentativa e permitirá até três tentativas. Após três tentativas incorretas, o acesso será bloqueado por 10 segundos.
7. Após o acesso ser concedido ou bloqueado, o sistema estará pronto para receber uma nova senha.

## 🛠️ Dependências

Este projeto requer as bibliotecas `Keypad.h`, `Adafruit_LiquidCrystal.h`, `EEPROM.h` e `Servo.h` para funcionar corretamente. Certifique-se de instalá-las no seu ambiente de desenvolvimento Arduino IDE antes de carregar o código para o Arduino.

## Observações

- Este código foi desenvolvido e testado em um ambiente Arduino Uno, mas pode ser adaptado para outros modelos e placas compatíveis com o Arduino.
- Certifique-se de ajustar as conexões do seu circuito e os pinos utilizados conforme necessário para o seu ambiente de desenvolvimento.
