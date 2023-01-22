// Подключение библиотек
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <IRremote.hpp>


// константы подключения контактов SS и RST
#define RST_PIN 9
#define SS_PIN 10

int piezoPin = 8;
IRrecv irrecv(A1);
decode_results results;

// Инициализация MFRC522
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

void setup()
{
  Serial.begin(9600); // инициализация последовательного порта
  SPI.begin(); // инициализация SPI
  mfrc522.PCD_Init(); // инициализация MFRC522
  Wire.begin();
  irrecv.enableIRIn();
  pinMode(A1, INPUT);
}


void loop()
{
  if ( ! mfrc522.PICC_IsNewCardPresent())
    return;
  // чтение карты
  if ( ! mfrc522.PICC_ReadCardSerial()) 
      return;
    
  // показать результат чтения UID и тип метки
  
  Serial.print(F("Card UID:"));
  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size); 
  Serial.println();

  delay(2000);

  //irc
  if (irrecv.decode(&results))
    {
      Serial.println(results.value);
    }
  
  //
  
}

  
// Вывод результата чтения данных в HEX-виде
void dump_byte_array(byte *buffer, byte bufferSize)
{
  for (byte i = 0; i < bufferSize; i++)
    {
      Serial.print(buffer[i] < 0x10 ? " 0" : " ");
      Serial.print(buffer[i], HEX);  
    }

  Serial.println();
  if (buffer[0] == 0x33 && buffer[1] == 0x99 && buffer[2] == 0x75 && buffer[3] == 0xA9)
    {
      Serial.print("ZBS!");
      tone(piezoPin, 500, 300);
      
      Wire.beginTransmission(8); // transmit to device #8
      //Wire.write("x is ");        // sends five bytes
      Wire.write(1);              // sends one byte
      Wire.endTransmission();    // stop transmitting
      
    }
  else
    {
      Serial.print("NAHUY!");
       tone(piezoPin, 1000, 1500);

      Wire.beginTransmission(8); // transmit to device #8 
      Wire.write(2);              // sends one byte
      Wire.endTransmission();    // stop transmitting
    }
 
}
