
#include <Keypad.h>


const byte LINHAS = 4; 
const byte COLUNAS = 3; 

char teclas[LINHAS][COLUNAS] = {
	{'1','2','3'},
	{'4','5','6'},
	{'7','8','9'},
	{'*','0','#'}
};

byte pinos_linhas[LINHAS] = {}; 
byte pinos_colunas[COLUNAS] = {};

char display_numbers = {'-','-','-','-'}
int passwd = {1,2,3,4}

//objeto keypad
Keypad keypad = Keypad( makeKeymap(teclas), pinos_linhas, pinos_colunas, LINHAS, COLUNAS );


void setup(){



}

void loop(){
	
	char tecla = keypad.getKey();
	if tecla == '#'{
	//login
		for(int i == 0;i<4;i++){
			tecla = keypad.getKey();
			delay(1000);	
			display_numbers[i] = tecla
			//displayshowing(display_numbers)
		}
	}	
}
