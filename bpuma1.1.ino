#include <LiquidCrystal.h>  
#include <Keypad.h>
#include <Password.h>
#include <PN532.h>
 
#define SCK         52
#define MOSI        51
#define SS          53
#define MISO        50
 
#define miTarjeta 4154856923
#define anclada 1
#define desanclada 0

PN532 nfc(SCK,MISO,MOSI,SS);

int bicicleta = desanclada;

Password password = Password("1974B");  
int dlugosc = 5;                        
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); 
 
int ledRed = 11;
int ledGreen = 12 ;
int iman = 10;
boolean bandera = true;

int ilosc;

const byte ROWS = 4; 
const byte COLS = 4; 

char keys[ROWS][COLS] = { 
{'1','2','3','A'}, 
{'4','5','6','B'}, 
{'7','8','9','C'},  
{'*','0','#','D'}
};

byte rowPins[ROWS] = {  9, 8, 7, 6 };
byte colPins[COLS] = { 5, 4, 3, 2, };

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup()
{
   //Serial.begin(9600);
   nfc.begin();
   nfc.SAMConfig();
  
 keypad.addEventListener(keypadEvent);  
 pinMode(ledRed, OUTPUT);  
 pinMode(iman,OUTPUT);
 pinMode(ledGreen, OUTPUT);
 
 digitalWrite(ledRed, HIGH);
 digitalWrite(iman, HIGH);
 digitalWrite(ledGreen, LOW);
 lcd.begin(16, 2);

 lcd.setCursor(0,0);
 lcd.print("   BIENVENIDO");
 lcd.setCursor(0,1);
 lcd.print("INGRESE CODIGO");
}

void loop()
{
  if (bandera == true){
  keypad.getKey();
  }
  else 
  {
  uint32_t id = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A);
  if(miTarjeta == id) 
      {
        if(bicicleta == desanclada){
      bandera=true;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("   BICICLETA");
      lcd.setCursor(0,1);
      lcd.print("    ANCLADA");
      digitalWrite(ledRed, HIGH);
      digitalWrite(iman, HIGH);
      digitalWrite(ledGreen, LOW);
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   BIENVENIDO");
    lcd.setCursor(0,1);
    lcd.print("INGRESE CODIGO");
        }
      }
}
}

void keypadEvent(KeypadEvent eKey)
{
  switch (keypad.getState())  {
    case PRESSED:
    
      //Serial.print("Pressed: ");
      //Serial.println(eKey);
        switch (eKey)
          {
             default:
             ilosc=ilosc+1;
             password.append(eKey);
           }
         if(ilosc == 1)
           {
             lcd.clear();
             lcd.setCursor(1,0);
             lcd.print("CODIGO:");
             lcd.setCursor(0,1);
             lcd.print("*_");
            }
         if(ilosc == 2)
            {
              lcd.clear();
              lcd.setCursor(1,0);
              lcd.print("CODIGO:");
              lcd.setCursor(0,1);
              lcd.print("**_");
             }
         if(ilosc == 3)
         {
           lcd.clear();
           lcd.setCursor(1,0);
           lcd.print("CODIGO:");
           lcd.setCursor(0,1);
           lcd.print("***_");
         }
     if(ilosc == 4)
        {
          lcd.clear();
          lcd.setCursor(1,0);
          lcd.print("CODIGO:");
          lcd.setCursor(0,1);
          lcd.print("****_");
        }
     if(ilosc == 5)
        {
          lcd.clear();
          lcd.setCursor(1,0);
          lcd.print("CODIGO:");
          lcd.setCursor(0,1);
          lcd.print("*****_");
        }
     if(ilosc == 6)
        {
          lcd.clear();
          lcd.setCursor(1,0);
          lcd.print("CODIGO:");
          lcd.setCursor(0,1);
          lcd.print("******_");
        }
     if(ilosc == 7)
        {
          lcd.clear();
          lcd.setCursor(1,0);
          lcd.print("CODIGO:");
          lcd.setCursor(0,1);
          lcd.print("*******_");
        }
     if(ilosc == 8)
        {
          lcd.clear();
          lcd.setCursor(1,0);
          lcd.print("CODIGO:");
          lcd.setCursor(0,1);
          lcd.print("********");
        }
     if(ilosc == dlugosc)
        {
          delay(250);
          checkPassword();
          ilosc = 0;
        }
      }
    }
void checkPassword()
{  
    if (password.evaluate())
    {
      
      ilosc = 0;   
      password.reset();
      
    //  Serial.println("Correcto");
    
      digitalWrite(ledRed, LOW);
      digitalWrite(iman, LOW);
      digitalWrite(ledGreen, HIGH);

      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("<<PIN CORRECTO>>");
      bandera=false;
    }
    else
    {
    ilosc = 0;
    password.reset();

    //Serial.println("Error");

    digitalWrite(ledRed, HIGH);
    digitalWrite(iman, HIGH);
    digitalWrite(ledGreen, LOW);

    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("<<PIN ERRONEO>>");
    delay(2000);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   BIENVENIDO");
    lcd.setCursor(0,1);
    lcd.print("INGRESE CODIGO");
    }

}

