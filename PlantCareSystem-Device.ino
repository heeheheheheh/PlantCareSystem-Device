#define LDR A0
#define SICAKLIK A1
#define LED_KIRMIZI 11
#define LED_YESIL 10
#define LED_MAVI 9
#define PIR 2
#define BUZZER 12
#define NEM A2

//MOTOR PIN 1 SU POMPASI soldaki su pompası
//MOTOR PIN 2 FAN sağdaki fan
#define SU_POMPASI_HIZ 5
#define MOTOR_PIN_1 3
#define MOTOR_PIN_2 4
#define MOTOR_PIN_3 7 
#define MOTOR_PIN_4 8
#define FAN_HIZ 6




int kirmizi = 0;
int yesil = 0;
int mavi = 0;

int isik;
int hareket;

int nem;

int okunan_deger;
float sicaklik_gerilim;
float sicaklik;


int fanHiz = 0;
int suMotorHiz = 0;

int buzzer = 0;


//KOMUTLAR
//fanHiz>x
//suMotorHiz>x
//ledMod>0,1,2,3 0 kapali 1 kirmizi 2 mavi 3 mor
//buzzerMod>0,1


int mesajBufferBoyutu = 24;
char gelenMesaj[24]; // 24 karakterlik haberleşme bufferi
char komut[16];
char deger[8];

void setup(){
  //analogReference(INTERNAL);
  pinMode(LED_KIRMIZI, OUTPUT);
  pinMode(LED_YESIL, OUTPUT);
  pinMode(LED_MAVI, OUTPUT);
  pinMode(PIR, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(MOTOR_PIN_1, OUTPUT);
  pinMode(MOTOR_PIN_2, OUTPUT);
  pinMode(MOTOR_PIN_3, OUTPUT);
  pinMode(MOTOR_PIN_4, OUTPUT);
  pinMode(SU_POMPASI_HIZ, OUTPUT);
  pinMode(FAN_HIZ, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  
 if(Serial.available() > 0){
  Serial.readString().toCharArray(gelenMesaj, mesajBufferBoyutu);
  char * ayracIsaretcisi = strtok(gelenMesaj, ">");
  strcpy(komut, ayracIsaretcisi);
  ayracIsaretcisi = strtok(NULL, ">");
  strcpy(deger, ayracIsaretcisi);

  // Alinan Komutun Seri Porta Yazdirimi
  //Serial.print(komut);
  //Serial.print("<");
  //Serial.print(deger);
  //Serial.print("\n");

  // Motorun hizini ayarlamak icin
  if(strcmp(komut, "fanHiz") == 0){
    fanHiz = atoi(deger);
  }

  if(strcmp(komut, "suMotorHiz") == 0){
    suMotorHiz = atoi(deger);
  }

  if(strcmp(komut, "ledMod") == 0){
    ledAyarla(atoi(deger));
  }

  if(strcmp(komut, "buzzerMod") == 0){
    buzzer = atoi(deger);
  }
  
 }

  //Sensör okumalari
  
  isik = analogRead(LDR);
  okunan_deger = analogRead(SICAKLIK);
  sicaklik_gerilim = (okunan_deger / 1023.0)*5000;
  sicaklik = sicaklik_gerilim/10.0;
  //sicaklik = analogRead(SICAKLIK) / 9.31;
  nem = analogRead(NEM);
  hareket = digitalRead(PIR);
  
  //Buzzer
  digitalWrite(BUZZER, buzzer);

  //LED
  analogWrite(LED_KIRMIZI,kirmizi);
  analogWrite(LED_MAVI, mavi);
  analogWrite(LED_YESIL, yesil);

  //SU MOTORU
  analogWrite(SU_POMPASI_HIZ,  suMotorHiz); //1. motor 255 ile tam hızda dönüyor...
  digitalWrite(MOTOR_PIN_1, HIGH );
  digitalWrite(MOTOR_PIN_2,  LOW);  
   
  //FAN
  analogWrite(FAN_HIZ,  fanHiz);  //2. motor 40 ile yavaş dönüyor...
  digitalWrite(MOTOR_PIN_3, HIGH);
  digitalWrite(MOTOR_PIN_4,  LOW);

/*
 //Arduinodan giden veriler
 String isikCikti = String();
 isikCikti.concat("isik");
 isikCikti.concat("<");
 isikCikti.concat(isik);
 Serial.println(isikCikti);*/

 String sicaklikCikti = String();
 sicaklikCikti.concat("sicaklik");
 sicaklikCikti.concat("<");
 sicaklikCikti.concat(sicaklik);
 Serial.println(sicaklikCikti);
 
 String hareketCikti = String();
 hareketCikti.concat("hareket");
 hareketCikti.concat("<");
 hareketCikti.concat(hareket);
 Serial.println(hareketCikti);


 String nemCikti = String();
 nemCikti.concat("nem");
 nemCikti.concat("<");
 nemCikti.concat(nem);
 Serial.println(nemCikti);


 /*
if(hareket == 1)
  {
  buzzer = 1;
  }else
  {
  buzzer = 0;
  }
  */
}

void ledAyarla(int mod){
    //Mod 0 - Kapali
    //Mod 1 - Kirmizi
    //Mod 2 - Mavi
    //Mod 3 - Mor
    switch(mod){
      case 0:
        mavi = 255;     //KAPALI
        kirmizi = 255;
        yesil = 255;
      break;
           
      case 1:
        mavi = 0;  //MAVİ
        kirmizi = 255;
        yesil = 255;
      break;
      
      case 2:
        mavi = 255;    //KIRMIZI
        kirmizi = 0;
        yesil = 255;
      break;
      
      case 3:
        mavi = 150;     //MOR
        kirmizi = 100;
        yesil = 255;
      break;
      
      case 4:
        kirmizi =0;  //BEYAZ
        mavi = 0;
        yesil = 0;  
      break;
      
    }
}





/* ÇÖPLÜK
  isikMiktari = analogRead(LDR);
  //Serial.println(isikMiktari);

  
  kirmiziMiktari = 0;
  yesilMiktari = 255;
  maviMiktari = 0;
  analogWrite(LED_KIRMIZI, kirmiziMiktari);
  analogWrite(LED_YESIL, yesilMiktari);
  analogWrite(LED_MAVI, maviMiktari);
  
  
  hareket = digitalRead(PIR);
  //Serial.println(hareket);

  if(hareket == 1){
    digitalWrite(BUZZER, HIGH);
  }else{
    digitalWrite(BUZZER,LOW);  
  }


  
  //sicaklik = analogRead(SICAKLIK) / 9.31;
  //Serial.println(sicaklik);
  //delay(10);
  


  analogWrite(SU_POMPASI_HIZ,  255);   //1. motor 255 ile tam hızda dönüyor...
  digitalWrite(MOTOR_PIN_1, HIGH );
  digitalWrite(MOTOR_PIN_2,  LOW);  
   
   // motor 2
  analogWrite(FAN_HIZ,  255);  //2. motor 40 ile yavaş dönüyor...
  digitalWrite(MOTOR_PIN_3, HIGH);
  digitalWrite(MOTOR_PIN_4,  LOW);

  nemMiktari = analogRead(NEM);
  Serial.println(nemMiktari);
 */
