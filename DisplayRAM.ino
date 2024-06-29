void DisplayRAM(String inputString) {
  display.clearDisplay();
  
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.print("RAM Used");
  
  int ramStringStart = inputString.indexOf("R", inputString.indexOf("G"));
  int ramStringLimit = inputString.indexOf("|", ramStringStart);
  String ramString = inputString.substring(ramStringStart + 1, ramStringLimit);
  
  // RAM Usage
  display.setCursor(0, 36);
  display.print(ramString);
  // display.print("B");
  display.display();
  delay(2000);
}
