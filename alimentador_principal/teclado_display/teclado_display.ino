
#include <Keypad.h>
#include <TM1637Display.h>

#define CLK 10
#define DIO 11
TM1637Display display = TM1637Display(CLK, DIO);


const byte LINHAS = 4; 
const byte COLUNAS = 3; 

char teclas[LINHAS][COLUNAS] = {
	{'1','2','3'},
	{'4','5','6'},
	{'7','8','9'},
	{'*','0','#'}
};

byte pinos_linhas[LINHAS] = {9, 8, 7, 6}; 
byte pinos_colunas[COLUNAS] = {5, 4, 3};

char display_numbers[] = {'-','-','-','-'};
int passwd = 10;
int soma =0;
//objeto keypad
Keypad keypad = Keypad( makeKeymap(teclas), pinos_linhas, pinos_colunas, LINHAS, COLUNAS );


void setup(){

	display.setBrightness(5);
	display.clear();
	Serial.begin(9600);

}

void loop(){
	
	char tecla = keypad.getKey();
		if (tecla == '#'){
		
			for(int i = 0;i<100;i++){
				Serial.println('h');
				while(true){
					tecla = keypad.getKey();
					if(tecla){	
						Serial.println(tecla);
						break;
					}
				}
	  
			display_numbers[i] = tecla;
    
    //display.showNumberDec(tecla.toInt(), false, 2, 1);
    //displayshowing(display_numbers 
			Serial.println(display_numbers[i]);
			}
		}

}
