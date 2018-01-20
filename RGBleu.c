#include <SoftwareSerial.h>
SoftwareSerial mySerial(4,2); // RX, TX

int LedRedPIN = 11;
int LedGreenPIN = 10;
int LedBleuPIN = 9;

int command ;// Bluetooth üzerinde alınan seri veriyi tutar 
int a = 0;
int dizi[2];//bluetooth üzerinden alınan 2 li veriyi tutar.

void setup() {
//pin tanımlama

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
  



  // Android cihazdan  veri alındığında if komutu çalışır 
  if (mySerial.available()) {
    a %= 2; //alınan sıralı veriyi(renk anahtarı ve renk şiddeti), her döngüde dizi değişkenine kaydeder.
    command = mySerial.read();
    Serial.println(command);
    dizi[a] = command; 
    //command +=(char)mySerial.read();
    a++;
  }

  for(int i=0 ; i<2; i++){ //değişen rengin anahtarını aramak için dizi değişkenin elemanlarını teker teker switch komutuna sokar.
    switch(dizi[i]){//dizi değişkenini yorumlar, hangi rengin değiştirildiğini saptayıp rgb() fonksyonuna parametre vererek rgb ledlerin parlıklığını değiştirir. 
      case 0:
      rgb(0,dizi[(i+1)%2]); // dizi değişkenşndekş anahtar yakalandığında anahtardan önceki yada sonraki elemanı rgb() fonksyonuna parlaklık parametresi olarak atar.
      break;
      case 1:
      rgb(1,dizi[(i+1)%2]);
      break;
      case 2:
      rgb(2,dizi[(i+1)%2]);
      break;
    }
  }
  
  // bilgisayarın seri monitörü üzerinden ardunio-cihaz haberleşmesi için gerekli kodlar.
  if (Serial.available()){
       //Serial.print("AT");
    delay(10); 
    mySerial.write(Serial.read());
   
  }

  
}

//girilen renk anahtarını saptayıp, ledin tonunu değiştirir.
void rgb(byte renk, byte ton){
if(renk == 0){
  analogWrite(LedRedPIN,abs(ton-255));
}
if(renk == 1){
  analogWrite(LedGreenPIN,abs(ton-255));
}
if(renk == 2){
  analogWrite(LedBleuPIN,abs(ton-255));
}
  
}

