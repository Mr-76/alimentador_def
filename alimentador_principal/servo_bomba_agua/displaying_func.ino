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
