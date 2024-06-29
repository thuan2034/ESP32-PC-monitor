void DisplayMenu() {
  // Display menu
  display.clearDisplay();
  display.setTextSize(2); // Increase text size to 2
  display.setTextColor(SH110X_WHITE);

  // Calculate center alignment for 2x text size (each character is 16 pixels wide)
  int16_t textWidth = 2 * 6 * menuItems[selectedMenuItem].length(); // Calculate width of current menu item
  int16_t xPos = (display.width() - textWidth) / 2 - 20; // Center align horizontally
  int16_t yPos = 10; // Start menu items at vertical position 10

  display.setCursor(xPos, yPos);

  int xValue = analogRead(X_PIN);
  int yValue = analogRead(Y_PIN);
  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print("\tY: ");
  Serial.println(yValue);

  // Navigate menu with joystick Y-axis
  if (yValue < 870 && selectedMenuItem > 0) {
    selectedMenuItem--;
  } else if (yValue > 2600 && selectedMenuItem < 2) {
    selectedMenuItem++;
  }

  // Simulate button press with joystick X-axis
  if (xValue < 1000) { // Check if joystick is pushed right
    inMenu = false; // Debounce to avoid multiple presses
  }

  for (int i = 0; i < 3; i++) {
    display.setCursor(xPos, yPos + i * 20); // Increase vertical spacing (assuming 20 pixels per line)
    if (i == selectedMenuItem) {
      display.print("> "); 
    }
    display.println(menuItems[i]);
  }

  display.display();

  delay(100); // Add a small delay for smoother reading
}