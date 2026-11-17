#define button_avancar1 14
#define button_avancar2 13
#define button_aceitar 1
#define button_top 17
#define button_bottom 2
#define button_right 39
#define button_left 21
#define motor_servo 4
#define led_vermelho
#define led_verde 
#define pinoTrigger 5
#define echo 18
#define D5 11
#define D6 12
#define D4 10
#define RS 9
#define E 16
#define D7 15
#define buzzer 48
#define pino_DHT 42
#define R_ledRGB 38
#define G_ledRGB 40
#define B_ledRGB 41
#include <DHT.h>
#include <Arduino.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(RS,E,D4,D5,D6,D7);
DHT sensor_dht(pino_DHT,DHT11);



void Tela_padrao(float temp, float umi) 
{
    lcd.setCursor(0,0);
    lcd.print("Celsius: ");
    lcd.print(temp);
    lcd.setCursor(0,1);
    lcd.print("Umidade: ");
    lcd.print(umi);

}
void Saudacao_inicial(bool saudacao){
    if(saudacao){
        lcd.setCursor(3,0);
        lcd.print("Seja bem");
        lcd.setCursor(4,1);
        lcd.print("vindo");
    }else{
        lcd.setCursor(0,0);
        lcd.print("Escolha");
        lcd.setCursor(0,1);
        lcd.print("sua vaga");
    }
    
    
}

float Iniciar_ultra(){
    digitalWrite(pinoTrigger,LOW);
    delayMicroseconds(2);
    digitalWrite(pinoTrigger,HIGH);
    delayMicroseconds(10);
    digitalWrite(pinoTrigger,LOW);
    unsigned long duracao = pulseIn(echo,HIGH,30000);
    if(duracao==0){
        return -1;
    }
    float distancia = duracao/58;
    return distancia;
}

bool iniciarMatriz=false;

void setup() {
  
  pinMode(button_aceitar,INPUT);
  pinMode(button_avancar1,INPUT);
  pinMode(button_avancar2,INPUT);
  pinMode(button_top,INPUT);
  pinMode(button_bottom,INPUT);
  pinMode(button_left,INPUT);
  pinMode(button_right,INPUT);
  pinMode(motor_servo,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(pino_DHT,INPUT);
  pinMode(pinoTrigger,OUTPUT);
  Serial.begin(9600);
  sensor_dht.begin();
  lcd.begin(16,2);
}

void loop() {
    float h_temp = sensor_dht.readHumidity();
    float t_temp = sensor_dht.readTemperature();
    float distancia = Iniciar_ultra();
    if (distancia>0 && distancia<50 && iniciarMatriz==false){
        lcd.clear();
        Saudacao_inicial(true);
        delay(3000);
        lcd.clear();
        Saudacao_inicial(false);
        delay(1500);
        iniciarMatriz=true;

        
        
    }else{
        if(!isnan(t_temp)&& !isnan(h_temp)){
            Tela_padrao(t_temp,h_temp);    
        }else{
            lcd.clear();
        }
        
    }
    
}
