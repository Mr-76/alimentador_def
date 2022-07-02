void display_time(String hour1, String minute1, String second1) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 28);
  display.println(hour1);
  display.setCursor(30, 28);
  display.println(minute1);
  display.setCursor(70, 28);
  display.println(second1);
  display.display();
  delay(1000);
}

void display_time(String hour1, String hour2, String hour3, String minute1) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(5, 28);
  display.println(hour1);
  display.setCursor(40, 28);
  display.println(hour2);
  display.setCursor(80, 28);
  display.println(hour3);
  display.setCursor(120, 28);
  display.println(minute1);
  display.display();
  delay(1000);
}
