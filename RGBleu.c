#include <SoftwareSerial.h>
SoftwareSerial mySerial(4,2); // RX, TX

int LedRedPIN = 11;
int LedGreenPIN = 10;
int LedBleuPIN = 9;

int command ; //keep the data that given from bluetooth module
int a = 0;
int duo[2]; //create array for keep the color key and color intensity

void setup() {
//pin declarition

pinMode(LedRedPIN,OUTPUT);
pinMode(LedGreenPIN,OUTPUT);
pinMode(LedBleuPIN,OUTPUT);
  
  
  
  // Open serial communications:
  Serial.begin(9600);
  Serial.println("Type AT commands!");
  
  
  
  // The Hz-06 defaults to 9600 according to the datasheet.
  mySerial.begin(9600);
  mySerial.println("AT+ADDR");
}

void loop() {

  if (mySerial.available()) {
    a %= 2;
    command = mySerial.read();
    Serial.println(command);
    duo[a] = command; 
    a++;
  }

  for(int i=0 ; i<2; i++){ 
    //değişen rengin anahtarını aramak için duo değişkenin elemanlarını teker teker switch komutuna sokar.
    //switch search color key
    switch(duo[i]){
      case 0:
      rgb(0,duo[(i+1)%2]); // dizi değişkenşndekş anahtar yakalandığında anahtardan önceki yada sonraki elemanı rgb() fonksyonuna parlaklık parametresi olarak atar.
      break;               //declare the key and other value of duo array to parametres of rgb(key,intensity) function 
      case 1:
      rgb(1,duo[(i+1)%2]);
      break;
      case 2:
      rgb(2,duo[(i+1)%2]);
      break;
    }
  }
  
  if (Serial.available()){
       //Serial.print("AT");
    delay(10); 
    mySerial.write(Serial.read());
   
  }

  
}

//girilen renk anahtarını saptayıp, ledin tonunu değiştirir.
void rgb(byte key, byte intensity){
if(key == 0){
  analogWrite(LedRedPIN,abs(intensity-255));
}
if(key == 1){
  analogWrite(LedGreenPIN,abs(intensity-255));
}
if(key == 2){
  analogWrite(LedBleuPIN,abs(intensity-255));
}
  
}

