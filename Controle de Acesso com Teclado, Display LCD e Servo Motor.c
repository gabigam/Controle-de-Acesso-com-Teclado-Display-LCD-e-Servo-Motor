#include <Keypad.h> // Biblioteca para usar o teclado
#include <Adafruit_LiquidCrystal.h> // Biblioteca para usar o display LCD
#include <EEPROM.h> // Biblioteca para usar a memória EEPROM
#include <Servo.h> // Biblioteca para usar o servo motor

// Cria um objeto do tipo Adafruit_LiquidCrystal com o pino 0
Adafruit_LiquidCrystal lcd(0);

// Define o número de linhas e colunas da matriz do teclado
const byte ROWS = 4;
const byte COLS = 4;

int aux = 0; // Variável auxiliar
int pos = 0; // Variável para armazenar a posição
int count = 0; // Variável para contar o número de tentativas
int countaux = EEPROM.read(1); // Variável para ler da memória EEPROM
int countT = 0; // Variável para colocar as tentativas na EEPROM
char keys[ROWS][COLS] = {{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}}; // Matriz com os valores das teclas

byte rowPins[ROWS] = {2, 3, 4, 5}; // Vetor com os pinos das linhas
byte colPins[COLS] = {6, 7, 8, 9}; // Vetor com os pinos das colunas

Servo servo_11; // Cria um objeto do tipo Servo

// Inicializa o objeto Keypad com a matriz, vetores e tamanho da matriz
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); 

int password[] = {6, 9, 6, 9}; // Define a senha como um vetor de inteiros

int inputPassword[] = {0, 0, 0, 0}; // Cria um vetor para armazenar a senha digitada pelo usuário 

void setup() {
// Movimentação inicial do servo motor para a posição 0 graus, por conta de um bug no tinkercad
  for (pos = 90; pos >= 0; pos -= 1) {
        servo_11.write(pos);
        delay(15); 
    }
// Inicialização da comunicação serial
  Serial.begin(9600); 

// Inicialização do display LCD com 16 colunas e 2 linhas
  lcd.begin(16, 2);

// Conexão do servo motor ao pino 11 da placa e definição dos limites de movimento
  servo_11.attach(11, 500, 2500);

// Limpa o display LCD e mostra a quantidade de falhas armazenada na memória EEPROM
  lcd.clear();
  Serial.print("FALHAS: ");
  Serial.println(EEPROM.read(1));
  lcd.print("FALHAS:");
  lcd.print(EEPROM.read(1));
  countT=countaux; // Define o contador de tentativas como o valor atual de countaux

// Aguarda 2 segundos e limpa o display LCD novamente
  delay(2000);
  lcd.clear();

// Posiciona o cursor na primeira linha e primeira coluna do LCD
  lcd.setCursor(0, 0);
// Mostra a mensagem "Digite a senha no teclado:" na comunicação serial e no LCD
  Serial.println("Digita a senha no teclado:");
  lcd.print("senha: ");
}

void loop() {
// Lê a tecla pressionada no teclado
  char key = keypad.getKey(); 
// Verifica se alguma tecla foi pressionada
  if (key != NO_KEY) { 
    // Posiciona o cursor no próximo espaço disponível da segunda linha do LCD
    lcd.setCursor(aux, 1);
    // Mostra a tecla pressionada na comunicação serial e no LCD
    Serial.print(key);
    lcd.print(key); 
    // Aguarda 200ms
    delay(200);
    // Substitui a tecla pressionada por um asterisco no LCD
    lcd.setCursor(aux, 1);
    lcd.print("*");
    // Incrementa o contador aux e armazena a tecla pressionada na posição correta do vetor de senha
    aux++;
    for (int i = 0; i < 4; i++) {
      if (inputPassword[i] == 0) { 
        inputPassword[i] = key - '0'; 
        break; 
      }
    }
  }

// Verifica se a senha foi completamente digitada
  if (inputPassword[3] != 0) {
    bool correct = true; 
    for (int i = 0; i < 4; i++) {
      if (inputPassword[i] != password[i]) { 
        correct = false; 
        break; 
      }
    }
//Se a senha estiver correta, abre a porta
    if (correct) { 
      //Limpa a tela do LCD e mostra que a senha está correta
      lcd.clear();
      Serial.println("SENHA CORRETA");
      lcd.print("SENHA CORRETA");
      delay(2000);
      lcd.clear();
      aux = 0;
     //Abre a porta gradualmente
      Serial.println("ABRINDO");
      lcd.print("ABRINDO");
        
      for (pos = 0; pos <= 90; pos += 1) {   
     servo_11.write(pos);   
     delay(21); 
   }
      
      delay(1000);
      //Mostra que a porta foi aberta
      Serial.println("PORTA ABERTA");
      lcd.clear();
      lcd.print("PORTA ABERTA");
      delay(10000);
      //Fecha a porta gradualmente
      Serial.println("FECHANDO");
      lcd.clear();
      lcd.print("FECHANDO");
        
     for (pos = 90; pos >= 0; pos -= 1) {
        servo_11.write(pos);
        delay(21); 
    }
      delay(1000); 
      //Mostra que a porta foi fechada e limpa o array da senha
      Serial.println("PORTA FECHADA");
      lcd.clear();
      lcd.print("PORTA FECHADA");
      delay(2000);
      Serial.println("senha: ");
      lcd.clear();
      lcd.print("senha: ");
      
      for (int i = 0; i < 4; i++) {
        inputPassword[i] = 0; 
      } 
    } else { 
      countT++;  //Adiciona uma tentativa ao contador de tentativas
      EEPROM.write(1,countT); //Armazena o número de tentativas na memória EEPROM
      lcd.clear();
      Serial.println("SENHA INCORRETA"); 
      lcd.print("SENHA INCORRETA"); 
      delay(2000);
      lcd.clear();
      aux = 0;
      
      count++;
    //Se o número de tentativas ainda for menor que 3, mostra quantas tentativas restam  
    if(count<3){
      Serial.print("TENTATIVAS: ");
      Serial.println(3-count);
      lcd.print("TENTATIVAS: ");
      lcd.print(3-count);
      delay(2000);
      lcd.clear();
     } else {
      //Se o número de tentativas for igual ou maior que 3, bloqueia o acesso por 10 segundos
      Serial.println("BLOQUEADO POR 10 SEGUNDOS");
      lcd.setCursor(1, 0);
      lcd.print("BLOQUEADO POR");
      lcd.setCursor(2,1);
      lcd.print("10 SEGUNDOS");
      count = 0;
      delay(10000);
      lcd.clear();
     }
      
      Serial.println("senha: ");
      lcd.print("senha: ");
      //Limpa o array da senha
      for (int i = 0; i < 4; i++) {
        inputPassword[i] = 0; 
      }
    }
  }
}