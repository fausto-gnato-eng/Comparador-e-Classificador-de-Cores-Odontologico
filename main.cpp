#include <Arduino.h>

/************************************************
 * TCC II Comparador de cores dentárias
 * Este software é comandado pelo pelo monitor serial 
 * **********************************************/
// Definiçao e chamada de portas/////////////////
#define    S0    12
#define    S1    13
#define    S2    6
#define    S3    7
#define    OUT   8
/////////////////////////////////////////////////
// Funçoes a serem usadas //////////
void measureCol();
void imprime();
void ciclo();
///////////////////////////////////////////////////////
void mediaSF(); //Media sem filtro
void mediaVrm();
void mediaVrd();
void mediaAzl();
////////////////////////////////////////////////////
void (*funcReset)() = 0;
///////////////////////////////////////////////////
void escolheCor();
/////////////////////////////////////////////////////
// Variaveis a serem usadas //////////
long int r, g, b,SF, mdVrm, smVrm,mdVrd, smVrd, mdAzl, smAzl, mdSF,smSF;
int pulse = 0, n = 1;
//////////////////////////////////////////////
void setup() 
{
//////////////////////////////////////////////
// Funçao das portas ////////////////////////
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
/////////////////////////////////////////////
//Colocação do modo de saida de sinais em 100%
 digitalWrite(S0,HIGH);
 digitalWrite(S1,HIGH);
///////////////////////////////////////////// 
  Serial.begin(9600);// Ativaçao do monitor serial
////////////////////////////////////////////
}

void loop() 
{
Serial.println("Pressione qualquer tecla para iniciar"); 
if (Serial.available()>0 ){ 
ciclo();
escolheCor();
delay(100); 
funcReset();
  }

delay(5000);

}
//**********************************************
/// Funçao ciclica /////////////////////////////
void ciclo(){
 for(n; n <= 20 ;n=n+1){  
 // Serial.print(" n = ");
 // Serial.print(n);
 // Serial.print(" | ");
  measureCol(); 
  delay(20);
  } 
  }
//**********************************************
void measureCol()
{
  //Seleciona leitura sem filtro 
  digitalWrite(S2,HIGH);
  digitalWrite(S3,LOW);
  //Lê duração do pulso em LOW
  SF = pulseIn(OUT, LOW);
  delay(20);

  //Seleciona leitura com filtro para vermelho
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  //Lê duração do pulso em LOW
  r = pulseIn(OUT, LOW);
  delay(20);

  //Seleciona leitura com filtro para verde
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  //Lê duração do pulso em LOW
  g = pulseIn(OUT, LOW);
  delay(20);

  //Seleciona leitura com filtro para azul
  digitalWrite(S2, LOW);
  digitalWrite(S3,HIGH);
  //Lê duração do pulso em LOW
  b = pulseIn(OUT, LOW);
  delay(20); 
  imprime();
} //end measureCol
/*****************************************************
****************************************************/
void imprime(){
//******Imprime Sem Filtro ********************************
 // Serial.print("Sem Filtro   = ");
 // Serial.print(SF);
//  Serial.print(" | ");
  mediaSF();
  Serial.print(" | ");
//******Imprime vermelho********************************
 // Serial.print("Vermelho   = ");
 // Serial.print(r);
 // Serial.print(" | ");
  mediaVrm();
  Serial.print(" | ");
//******Imprime verde***********************************
 // Serial.print("Verde = ");
 // Serial.print(g);
  mediaVrd();
  Serial.print(" | ");
//*******Imprime azul***********************************
 // Serial.print("Azul  = ");
 // Serial.print(b);
  mediaAzl();
  }
/******************************************************
*****************************************************/
void mediaSF(){
  smSF = smSF + SF;
  mdSF = smSF/n;
//  Serial.print(" md SF = ");
  Serial.print(mdSF);
  }
////////////////////////////////////////////////////// 
void mediaVrm(){
  smVrm = smVrm + r;
  mdVrm = smVrm/n;
 // Serial.print(" mVerm-mSF= ");
  Serial.print(mdVrm-mdSF);
  }
////////////////////////////////////////////////////// 
void mediaVrd(){
  smVrd = smVrd + g;
  mdVrd = smVrd/n;
 // Serial.print(" mVerde-mSF = ");
  Serial.print(mdVrd-mdSF);
  }
////////////////////////////////////////////////////// 
void mediaAzl(){
  smAzl = smAzl + b;
  mdAzl = smAzl/n;
 // Serial.print(" mAzul-mSF = ");
  Serial.println(mdAzl-mdSF);
  }
/////////////////////////////////////////////////////////
void escolheCor(){
//////////////////////////////////////////////////////////
//////////cor 60/////////////////////////////////////////  
  if(mdVrm > 5450 && mdVrm < 6100 && mdVrd > 7350 && mdVrd < 8180 && mdAzl > 6700 && mdAzl < 7460){
   Serial.println(" Cor 60"); 
   }
////////cor 61////////////////////////////////
 if(mdVrm > 5380 && mdVrm < 5560 && mdVrd > 5550 && mdVrd < 5570 && mdAzl > 5500 && mdAzl < 5700){
   Serial.println(" Cor 61");
  }
}