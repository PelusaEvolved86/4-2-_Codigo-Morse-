#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


char letras[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','Ñ','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
String letras_morse[]={".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","--.--","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};


//char numeros[]={"  1  ","  2  ","  3  ","  4  ","  5  ","  6  ","  7  ","  8  ","  9  ","  0  "};
//char numeros_morse={".----","..---","...--","....-",".....","-....","--...","---..","----.","-----"};
String palabra;
int tem;
int coutPalabra =0;
String letra="";
int boton = 11 ;
long tiempo;
int cant;
float micro;
float seg;
bool presion = true;
char codigo[5];
bool toque = true;


LiquidCrystal_I2C lcd(0x27,16,2);




void setup()
{
  pinMode(boton, INPUT);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  lcd.begin(16,2);
}




void loop()
{
  
  presion = true;
  comienzo();
  if (!presion){
    convertir_caracteres();
  }
  if (cant >= 1){
    Serial.print("Código Morse recibido: ");
    for (int i = 0; i < cant; i++) {
      letra = letra+codigo[i];
    }
    Serial.println(letra);
    for (int i=0;i<27;i++){
      if (letra == letras_morse[i]){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(letras[i]);
        palabra = palabra + letras[i];
        Serial.println(letras[i]);
      }
    }
  }
  
  if( coutPalabra >= 8 || tem == 8)
  {
    palabra ="";
    coutPalabra=0;
    toque = true;
    tem = 0;
  }
   
  letra = "";
  for (int i = 0;i < 5; i++){
    codigo[i]='0';
  }
  cant = 0;
  //Serial.print("Frase:");
  //Serial.println(palabra);
  lcd.setCursor(0,1);
  lcd.print( palabra );
}
void comienzo(){
  Serial.println(toque);
  if (!toque){
      tem ++;
    }
  Serial.println("Inicio");
  micro = pulseIn(boton, LOW,3000000);
  seg = micro / 1000000;
  Serial.println(seg);
  if (seg > 0.00 && seg < 0.22){
    codigo[0]='.';
    presion = !presion;
    toque = false;
    cant ++;
    Serial.println(codigo[0]);
  }else if(seg >= 0.22){
    codigo[0]='-';
    presion = !presion;
    toque = false;
    cant ++;
    Serial.println(codigo[0]);
  }
}


void convertir_caracteres(){
    for (int i=1;i<5;i++){
      micro = pulseIn(boton, LOW,2000000);
      seg = micro / 1000000;
      if (seg > 0.00 && seg < 0.2200){
        codigo[i]='.';
        cant ++;
        Serial.println(codigo[i]);
      }else if(seg >= 0.22 ){
        codigo[i]='-';
        cant++;
        Serial.println(codigo[i]);
      }else {
        i=6;
      }
      presion = !presion;
    }  
    coutPalabra++;
}
