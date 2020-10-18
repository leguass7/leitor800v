// --- Mapemanto de Hardware ---
// #define     cs     13                           //chip select
// #define     wr     12                           //clock
// #define     dat    11                           //data 
// #define     bl      5                           //backlight
#define n_gen  9  //oscilador para gerar tensão negativa
#define vIn    A0 //entrada para medida de tensão

// --- Variáveis Globais ---
const int  vMax = 5.0; 
float     voltage = 0.0;  //armazena tensão lida


long average_volt(); 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("LIGADO");

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(n_gen, OUTPUT);  // config saída para oscilador de tensão negativa
  analogWrite(n_gen, 128); // onda quadrada para gerador de tensão negativa
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  
  voltage = (average_volt() * vMax) / 1023.0; //calcula tensão em volts

  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println(voltage);
  delay(500);
  

}

/* 
 * Calcula a Média de tensão
 * garante maior precisão na medida
 * returns long 
 */
long average_volt() {
   unsigned char i;
   long volt_store = 0;

   // faz 10 leituras
   for (i=0; i<10; i++) {
    volt_store += analogRead(vIn);
   }                         

   // retorna a média das iterações
   return (volt_store / 10.0);                     
};
