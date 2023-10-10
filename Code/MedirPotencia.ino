
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(1, 2, 4, 5, 6, 7); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7)

//Tensao
float value = 0; 
float voltage = 0;
float R1 = 45500.0; //47k
float R2 = 31800.0; //33k
float Rin = 325; //entre turbina e BOB



//Corrente alternativa
float value2 = 0;
float voltage2 = 0;
float voltagedrop = 0;
float Corrente;


float potencia;


void setup() {
  lcd.begin(16, 2); //Inicia LCD
}
void loop() {
  lcd.clear();

  //correnteFinal = filtromedia();

  //Leitura da Tensao:
  value = analogRead(A1);
  voltage = value * (5.0 / 1024) * ((R1 + R2) / R2); //ultimos valores sao das resistencias usadas


  //Corrente
  value2 = analogRead(A2);
  voltage2 = value2 * (5.0 / 1024) * ((R1 + R2) / R2);
  voltagedrop = voltage - voltage2; //queda de tensao na resistencia de entrada
  Corrente = (voltagedrop / Rin) * 1000; //*1000 para estar em mA

  potencia = voltage * Corrente;

  lcd.setCursor(1, 0);
  if (voltage < 0.3) //elimina ruidos
    voltage = 0;
  lcd.print(voltage);
  lcd.setCursor(5, 0);
  lcd.print(" V");

  lcd.setCursor(9, 0);
  if (voltage2 < 0.3) //elimina ruidos
    Corrente = 0;
  lcd.print(Corrente);
  lcd.setCursor(13, 0);
  lcd.print(" mA");

  lcd.setCursor(1, 1);
  lcd.print("Power: ");
  lcd.setCursor(8, 1);
  if (voltage < 0.3) //elimina ruidos
    potencia = 0;
  lcd.print(potencia);
  lcd.setCursor(12, 1);
  lcd.print(" mW");

  delay(1000);
}
