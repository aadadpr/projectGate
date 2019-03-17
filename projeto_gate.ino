//Reles para ativar os motores
int pnReleGateOpen = 3;
int pnReleGateClose = 4;
//Sensor de presenca
int pnInfra = 5;
//Fim de curso
int pnEndLineOpen = 7;
int pnEndLineClose = 6;
//Botoes
int pnButtonOpen = 8;
int pnButtonClose = 9;
//Rele do controle
int pnReleControl = 2;
//Variavel que define que o portao vai abrir
int openGate = 1;

int lastEndLineClose = 0;
int lastEndLineOpen = 0;

int lastStatControl = 1;
int statControl = 1;
void setup()
{
    pinMode(pnReleControl, OUTPUT);
    //digitalWrite(pnReleControl, HIGH);
    
    pinMode(pnInfra, OUTPUT);
    
    pinMode(pnEndLineOpen, OUTPUT);
    pinMode(pnEndLineClose, OUTPUT);


    pinMode(pnButtonOpen, OUTPUT);
    digitalWrite(pnButtonOpen, HIGH);
    
    pinMode(pnButtonClose, OUTPUT);
    digitalWrite(pnButtonClose, HIGH);
    
    pinMode(pnReleGateOpen, OUTPUT);
    digitalWrite(pnReleGateOpen, HIGH);
    pinMode(pnReleGateClose, OUTPUT);
    digitalWrite(pnReleGateClose, HIGH);
    
    Serial.begin(9600);

    lastStatControl = digitalRead(pnReleControl);
    lastEndLineOpen = digitalRead(pnEndLineOpen);
    lastEndLineClose = digitalRead(pnEndLineClose);
    
    close();
}

void loop()
{
  
    statControl = digitalRead(pnReleControl);
    
    //botao de abrir
    if(digitalRead(pnButtonOpen) == 0){
        Serial.println("lastOPEN:");
        Serial.println(lastEndLineOpen);
        open();
   //botao de fechar
    }else if(digitalRead(pnButtonClose) == 0){
        Serial.println("lastCLOSE:");
        Serial.println(pnEndLineClose);
        close();
    }
}


void open(){

    while(lastEndLineOpen == 0){
        //Ativando rele
        digitalWrite(pnReleGateOpen, LOW);
        delay(10);
        
        //Atualizando sensor para o loop
        lastEndLineOpen = digitalRead(pnEndLineOpen);
        //Atualizando posicao do outro sensor
        lastEndLineClose = digitalRead(pnEndLineClose);
    }
    //Desativando rele
    digitalWrite(pnReleGateOpen, HIGH);
    Serial.println("lastOPEN:");
    Serial.println(lastEndLineOpen);
}

void close(){

    while(lastEndLineClose == 0){
        //Ativando rele
        digitalWrite(pnReleGateClose, LOW);
        delay(10);
        //Condicao para se alguem passar na frente do portao quando ele estiver fechando
        //Caso alguem passe, o portao ira abrir
        if(digitalRead(pnInfra) == 1){
            digitalWrite(pnReleGateClose, HIGH);
            open();
            return;
        }
        lastEndLineClose = digitalRead(pnEndLineClose);
        lastEndLineOpen = digitalRead(pnEndLineOpen);
    }
    
    //Desativando rele
    digitalWrite(pnReleGateClose, HIGH);
    Serial.println("lastCLOSE:");
    Serial.println(pnEndLineClose);
}
