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
#include <string>;
using namespace std;

LiquidCrystal lcd(RS,E,D4,D5,D6,D7);
DHT sensor_dht(pino_DHT,DHT11);

class Display{
    pair<int,int> vaga_atual={0,0};
    bool ultimo_estado[5] = {LOW, LOW, LOW, LOW, LOW};
    unsigned long ultimo_tempo[5] = {0, 0, 0, 0, 0};
    char letra_atual='A';
    const unsigned long tempo = 50;
    public:
    
    void MostrarCatalogo(vector<vector<vector<int>>>vagas){
        char ascii='A';
            for(int r=0; r<vagas[0].size(); r++){
            for(int c=0; c<vagas[0][r].size(); c++){
                if(c%2==0){
                    lcd.setCursor(c,r);
                    lcd.write(ascii);
                    if(ascii<'P'){
                        ascii++;
                    }
                }
            }
        
        }
        
    }

    void SaudacaoFinal(){
        lcd.setCursor(0,0);
        lcd.print("Tenha um");
        lcd.setCursor(0,1);
        lcd.print("otimo passeio");
    }

    void MostrarVagas(vector<vector<vector<int>>>vagas){
            for(int r=0; r<vagas[letra_atual-'A'].size(); r++){
            for(int c=0; c<vagas[letra_atual-'A'][r].size(); c++){
                if(c%2==0){
                    lcd.setCursor(c,r);
                    if(vagas[letra_atual-'A'][r][c]==0){
                        lcd.print('o');
                    }else{
                        lcd.print('x');
                    }
                }
            }
        
        }
        
    }
    void VerificarEscolha(){
        String text="A vaga:";
        text+=letra_atual;
        if(vaga_atual.second==0){
            text+=String(vaga_atual.first/2+1);
        }else{
            text+=String(vaga_atual.first/2+9);
        }
        
        Serial.print(text);
        lcd.setCursor(0,0);
        lcd.print("Deseja mesmo");
        lcd.setCursor(0,1);
        lcd.print(text);

        
    }

    bool SelecionarVagas(vector<vector<vector<int>>> &vagas){
        String click = VerificarClick(button_aceitar);
        if(click=="aceitar"){
                vagas[letra_atual-'A'][vaga_atual.second][vaga_atual.first]=1;
                return true;
            }
            
        
        return false;
    }
    void ResetarVaga(bool letra){
        vaga_atual={0,0};
        if(letra){
        letra_atual='A';
        }
    }

    bool SelecionarCatalogo(){
        String click= VerificarClick(button_aceitar);
        if(click=="aceitar"){
            lcd.clear();
            String text="escolhido:";
            text+=letra_atual;
            lcd.setCursor(0,0);
            lcd.print("Catalogo");
            lcd.setCursor(0,1);
            lcd.print(text);
            return true;
        }
        return false;
    }
    void MoverOpcao(){
        String clique="";
        if(clique == "" && vaga_atual.second == 1){
            clique = VerificarClick(button_top);
            if(clique == "cima"){
            vaga_atual.second -= 1;
            tone(buzzer,400,10);
        }
        }

        if(clique == "" && vaga_atual.second == 0){
            clique = VerificarClick(button_bottom);
            if(clique == "baixo"){
            vaga_atual.second += 1;
            tone(buzzer,400,10);
        }
        }
    }

    bool MostrarOpcao(){
        String click=VerificarClick(button_aceitar);
        lcd.setCursor(0,0);
        lcd.print("Sim");
        lcd.setCursor(0,1);
        lcd.print("Nao");
        if(click=="aceitar" && vaga_atual.second==0){
            return true;
        }
        return false;
        
    }

    void MoverVaga(){
        String clique = "";
    if(vaga_atual.first < 14){
        clique = VerificarClick(button_right);
        if(clique == "direita"){
        vaga_atual.first += 2;
        tone(buzzer,400,10);
    }
    }

    if(clique == "" && vaga_atual.first > 0){
        clique = VerificarClick(button_left);
        if(clique == "esquerda"){
        vaga_atual.first -= 2;
        tone(buzzer,400,10);
        }
    }


    if(clique == "" && vaga_atual.second == 1){
        clique = VerificarClick(button_top);
        if(clique == "cima"){
        vaga_atual.second -= 1;
        tone(buzzer,400,10);
    }
    }

    if(clique == "" && vaga_atual.second == 0){
        clique = VerificarClick(button_bottom);
        if(clique == "baixo"){
        vaga_atual.second += 1;
        tone(buzzer,400,10);
    }
    }
    }

    void MoverCatalogo(){

    String clique = "";
    if(vaga_atual.first < 14){
        clique = VerificarClick(button_right);
        if(clique == "direita"){
        vaga_atual.first += 2;
        letra_atual+=1;
        tone(buzzer,400,10);
    }
    }

    if(clique == "" && vaga_atual.first > 0){
        clique = VerificarClick(button_left);
        if(clique == "esquerda"){
        vaga_atual.first -= 2;
        letra_atual-=1;
        tone(buzzer,400,10);
    }
    }

    if(clique == "" && vaga_atual.second == 1){
        clique = VerificarClick(button_top);
        if(clique == "cima"){
        vaga_atual.second -= 1;
        letra_atual=letra_atual-8;
        tone(buzzer,400,10);
    }
    }

    if(clique == "" && vaga_atual.second == 0){
        clique = VerificarClick(button_bottom);
        if(clique == "baixo"){
        vaga_atual.second += 1;
        letra_atual=letra_atual+8;
        tone(buzzer,400,10);
    }
    }

    }

    String VerificarClick(int botao){

    int indice;

    switch(botao){
        case button_right: indice = 0; break;
        case button_left: indice = 1; break;
        case button_top: indice = 2; break;
        case button_bottom: indice = 3; break;
        case button_aceitar: indice=4; break;
        default: return "";
    }

    bool click_atual = digitalRead(botao);

    if(click_atual == HIGH && ultimo_estado[indice] == LOW){
            ultimo_estado[indice] = click_atual;

            switch(indice){
                case 0: return "direita";
                case 1: return "esquerda";
                case 2: return "cima";
                case 3: return "baixo";
                case 4: return "aceitar";
            }
        
    }

    ultimo_estado[indice] = click_atual;

    return "";
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

enum Estados{
    tela_padrao,
    saudacao,
    instrucao,
    catalogo,
    vaga_selecionada,
    vagas,
    verificar_escolha
};

Estados estado_atual=tela_padrao;


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
vector<vector<vector<int>>> MatrizVagas =
        vector<vector<vector<int>>>(16, vector<vector<int>>(2, vector<int>(16, 0)));

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
    
        switch(estado_atual){

        case tela_padrao:{
            float h_temp = sensor_dht.readHumidity();
            float t_temp = sensor_dht.readTemperature();
            float distancia = Iniciar_ultra();
            if(!isnan(t_temp) && !isnan(h_temp)){
                display_lcd.Tela_padrao(t_temp,h_temp);
            }

            if(distancia > 0 && distancia < 50){

                lcd.clear();

                display_lcd.Saudacao_inicial(true);
                delay(2000);
                estado_atual = saudacao;
            }
        }
            break;


        case saudacao:

            lcd.clear();

            display_lcd.Saudacao_inicial(false);
            delay(2000);
            estado_atual = instrucao;
            
            lcd.clear();
            display_lcd.ResetarVaga(false);
            break;


        case instrucao:

            
            if(display_lcd.SelecionarCatalogo()){
                lcd.clear();
                estado_atual=vagas;
                display_lcd.ResetarVaga(false);
            }else{
                 display_lcd.MostrarCatalogo(MatrizVagas);
                display_lcd.MoverCatalogo();
            }

            break;
        case vagas:
            display_lcd.MostrarVagas(MatrizVagas);
            display_lcd.MoverVaga();
            if(display_lcd.SelecionarVagas(MatrizVagas)){
                estado_atual=verificar_escolha;
                lcd.clear();
                display_lcd.VerificarEscolha();
                display_lcd.ResetarVaga(true);
                delay(3000);
                lcd.clear();
            }
            break;
        case verificar_escolha:
            if(display_lcd.MostrarOpcao()){
                estado_atual=tela_padrao;
                display_lcd.ResetarVaga(false);
                display_lcd.SaudacaoFinal();
                delay(2500);
            }else{
                display_lcd.MoverOpcao();
            }
            
            break;


    }
    
}
