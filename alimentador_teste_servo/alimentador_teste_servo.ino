#include <Servo.h>

Servo myservo; // def o objeto servo se referindo ao servo motor

int angulo = 0;   //inteiro para delcarar posiçao

void setup() {
  myservo.attach(9); // define que pin o servo esta conectado 
  
}
void loop() {
//time goes up here
repetidordeFuncao(1,97);



}

int repetidordeFuncao(int repeticao,int angulo){ //later use pointers to call the function
int i = 0;
for(i;i<2;i++){
AbrindoeFechando(angulo);
}
myservo.write(50);
}

int AbrindoeFechando(int angulo){
myservo.write(angulo);
delay(1200);
myservo.write(50); //fecha //closes
delay(1200);
}
