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


    pinMode(pnButtonOpen, INPUT);
    digitalWrite(pnButtonOpen, HIGH);
    
    pinMode(pnButtonClose, OUTPUT);

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
    
//Caso o controle ative permanente o rele

    if (statControl != lastStatControl)
    {
        lastStatControl = statControl;
        if(lastEndLineOpen == 1){
            close();
        }else if(lastEndLineClose == 1){
            open();
        }
    }


//Caso o controle ative como se fosse click  
/*
    if (digitalRead(pnReleControl) == 0)
    {
        Serial.println("Inicial Open");
        Serial.println(digitalRead(pnEndLineOpen));
        Serial.println("Inicial Close");
        Serial.println(digitalRead(pnEndLineClose));
        lastStatControl = statControl;
        
        if(digitalRead(pnEndLineOpen) == 1){
            close();
        }else if(digitalRead(pnEndLineClose) == 1){
            open();
        }
    } 
    */
    if(digitalRead(pnButtonOpen) == 0){
        open();
    }else if(digitalRead(pnButtonClose) == 0){
        close();
    }
}


void open(){
    lastEndLineOpen = digitalRead(pnEndLineOpen);
    while(lastEndLineOpen == 0){
        Serial.println("Open");
        Serial.println("EndLineOpen");
        Serial.println(digitalRead(pnEndLineOpen));
        //Ativando rele
        digitalWrite(pnReleGateOpen, LOW);
        delay(10);

        lastEndLineOpen = digitalRead(pnEndLineOpen);
    }
    //Desativando rele
    digitalWrite(pnReleGateOpen, HIGH);
}

void close(){
    lastEndLineClose = digitalRead(pnEndLineClose)
    while(lastEndLineClose == 0){
        Serial.println("Close");
        Serial.println("EndLineClose");
        Serial.println(digitalRead(pnEndLineClose));
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
    }
    
    //Desativando rele
    digitalWrite(pnReleGateClose, HIGH);
}