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
#define D5 7
#define D6 15
#define D4 6
#define RS 8
#define E 9
#define D7 16
#define buzzer 48
#define pino_DHT 42
#define R_ledRGB 35
#define G_ledRGB 36
#define B_ledRGB 37
#include <DHT.h>
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <vector>
using namespace std;

LiquidCrystal lcd(RS,E,D4,D5,D6,D7);
DHT sensor_dht(pino_DHT,DHT11);

class Display{
    pair<int,int> vaga_atual={0,0};
    bool ultimo_estado[4] = {LOW, LOW, LOW, LOW};
    unsigned long ultimo_tempo[4] = {0, 0, 0, 0};
    char letra_atual='A';
    const unsigned long tempo = 50;
    public:
    
    void MostrarCatalogo(vector<vector<int>>vagas){
        char ascii='A';
        for(int r=0; r<vagas.size(); r++){
            for(int c=0; c<vagas[r].size(); c++){
                if(c%2==0){
                    lcd.setCursor(c,r);
                    lcd.write(ascii);
                    if(ascii<'Z' && (ascii-15)!='A'){
                        ascii++;
                    }
                }
            }
        }
    }

    void MoverCatalogo(){

    String clique = "";

    if(vaga_atual.first < 14){
        clique = VerificarClick(button_right);
    }

    if(clique == "" && vaga_atual.first > 0){
        clique = VerificarClick(button_left);
    }

    if(clique == "" && vaga_atual.second == 1){
        clique = VerificarClick(button_top);
    }

    if(clique == "" && vaga_atual.second == 0){
        clique = VerificarClick(button_bottom);
    }

    if(clique == "direita"){
        vaga_atual.first += 2;
        letra_atual+=1;
    }
    else if(clique == "esquerda"){
        vaga_atual.first -= 2;
        letra_atual-=1;
    }
    else if(clique == "cima"){
        vaga_atual.second -= 1;
        letra_atual=letra_atual-8;
    }
    else if(clique == "baixo"){
        vaga_atual.second += 1;
        letra_atual=letra_atual+8;
    }
    getLetraAtual();
    }

    String VerificarClick(int botao){

    int indice;

    switch(botao){
        case button_right: indice = 0; break;
        case button_left: indice = 1; break;
        case button_top: indice = 2; break;
        case button_bottom: indice = 3; break;
        default: return "";
    }

    bool estado_atual = digitalRead(botao);

    if(estado_atual == HIGH && ultimo_estado[indice] == LOW){

        if(millis() - ultimo_tempo[indice] >= tempo){

            ultimo_tempo[indice] = millis();
            ultimo_estado[indice] = estado_atual;

            switch(indice){
                case 0: return "direita";
                case 1: return "esquerda";
                case 2: return "cima";
                case 3: return "baixo";
            }
        }
    }

    ultimo_estado[indice] = estado_atual;

    return "";
}

     void getLetraAtual(){
        lcd.setCursor(vaga_atual.first,vaga_atual.second);
        lcd.print(letra_atual);
        

     }

    void Tela_padrao(float temp, float umi){
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
};




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
Display display_lcd;
vector<vector<int>> MatrizVagas(2, vector<int>(16,0));

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
    if(iniciarMatriz){
        display_lcd.MoverCatalogo();
    }
    else if (distancia>0 && distancia<50 && iniciarMatriz==false){
        lcd.clear();
        display_lcd.Saudacao_inicial(true);
        delay(3000);
        lcd.clear();
        display_lcd.Saudacao_inicial(false);
        delay(1500);
        iniciarMatriz=true;
        lcd.clear();
        display_lcd.MostrarCatalogo(MatrizVagas);

        
        
    }else{
        if(!isnan(t_temp)&& !isnan(h_temp)){
            display_lcd.Tela_padrao(t_temp,h_temp);    
        }else{
            lcd.clear();
        }
        
    }
    
}
