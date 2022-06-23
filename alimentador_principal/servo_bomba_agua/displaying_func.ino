void display_time(Adafruit_SSD1306 display,String hour1,String minute1,String second1){
    display.clearDisplay();
    // Display Text
    display.setTextSize(2);
    display.setTextColor(1,0);
    display.setCursor(0,28);
    display.println(hour1);
    display.setCursor(20,28);
    display.println(minute1);
    display.setCursor(40,28);
    display.println(second1);
    display.display();
    delay(1000);

}
// need to test the reuse
/**void display_time(Adafruit_SSD1306 display,int hour1,int hour2,int hour3,int minute1){
    
    String hour11 = String(hour1);
    String hour22 = String(hour2);
    String hour33 = String(hour3);
    String minute11 = String(minute1);
    
    display.clearDisplay();
    // Display Text
    display.setTextSize(1);
    display.setTextColor(0,1);
    display.setCursor(0,28);
    display.println(hour11);
    display.setCursor(20,28);
    display.println(hour22);
    display.setCursor(40,28);
    display.println(hour33);
    display.setCursor(60,28);
    display.println(minute11);
    display.display();
    delay(1000);
}
*/

//reuse function or not ?

/**
void chage_time(Adafruit_SSD1306 dispay,int timing[]){
	display_time_change(dispay,timing_array[0],timing_array[1],timing_array[2],timing_array[3]);
	for(int i = 0;i<4;i++){
		while(true){
			butons read()
			 if buttons 1 == hight{
				timing_array[i]++;
			}else if(buttons 2  == hight){
				timing_array[i]--;

			}else if (button1 == high && button2 == hight){
				break;
			}else{
				;//nothin
			}
		}
	}
}
*/
/**
void display_time_change(Adafruit_SSD1306 display,int value1,int value2, int value3,int value4){
    display.clearDisplay();
    // Display Text
    display.setTextSize(1);
    display.setTextColor(0,1);
    display.setCursor(0,28);
    display.println(value1);
    display.setCursor(20,28);
    display.println(value2);
    display.setCursor(40,28);
    display.println(value3);
    display.setCursor(60,28);
    display.println(value4);
    display.display();
    delay(1000);
}
*/
