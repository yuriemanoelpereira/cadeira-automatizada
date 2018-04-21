//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>

  //Definindo os pinos para o trigger e echo
#define TRIGGER_PIN  2
#define ECHO_PIN     4

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

unsigned int eixoY;
unsigned int eixoX;
unsigned int pwm_y;
unsigned int pwm_x;

void setup()
{
  //iniciando a porta serial
  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");

  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop()
{

  //Le as informacoes do sensor, em cm
  float cmMsec;
  long microsec = ultrasonic.timing();

   cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
   
  //inicia os pinos do joystick
  eixoY = analogRead(A2);
  eixoX = analogRead(A0);

  pwm_y = map(eixoY, 0, 1023, 0, 255);
  pwm_x = map(eixoX, 0, 1023, 0, 255);

  //cadeira vai para frente
  if (pwm_y > 140) {

    analogWrite(10, pwm_y);
    analogWrite(11, 0);
    analogWrite(5, pwm_y - 8);
    analogWrite(6, 0);
  }

  //cadeira vai para atras
  else if (pwm_y < 50) {

    analogWrite(11, 255 - pwm_y);
    analogWrite(10, 0);
    analogWrite(6, 247 - pwm_y);
    analogWrite(5, 0);
  }



  //cadeira se move no sentido horário
  else if (pwm_x > 240) {

    analogWrite(11, 0);
    analogWrite(10, pwm_x - 25);
    analogWrite(6, 0);
    analogWrite(5, 0);

  }

  //cadeira se move no sentido anti-horário

  else if (pwm_x < 30) {

    analogWrite(11, 0);
    analogWrite(10, 0);
    analogWrite(5, 230 - pwm_x);
    analogWrite(6, 0);

  }

  //posição de repouso
  else {

    analogWrite(10, 0);
    analogWrite(11, 0);
    analogWrite(5, 0);
    analogWrite(6, 0);
  }


  // paramentros para o emisor sonoro ativar

  if (cmMsec < 100 && pwm_y < 10) {

    digitalWrite(8, HIGH);

  }

  else if (cmMsec < 100 && pwm_x > 200) {


     digitalWrite(8, HIGH);

  }


  else if (cmMsec < 100 && pwm_x < 10) {


    digitalWrite(8, HIGH);

  }

  else {

    digitalWrite(8, LOW);

  }


  //Exibe informacoes no serial monitor
  Serial.print("\n Distancia em cm:  ");
  Serial.print(cmMsec);



}
