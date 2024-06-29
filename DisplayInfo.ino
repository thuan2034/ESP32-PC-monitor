void DisplayInfo() {
 int xValue = analogRead(X_PIN);
 if (xValue > 2300) { // Check if joystick is pushed left
   inMenu = true;
   return;
 }

 switch (selectedMenuItem) {
   case 0:
     DisplayCPU(inputString);
     break;
   case 1:
     DisplayGPU(inputString);
     break;
   case 2:
     DisplayRAM(inputString);
     break;
 }
}