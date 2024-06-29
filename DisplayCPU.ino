void DisplayCPU(String inputString) {

  display.clearDisplay();

  // Display Title
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor((display.width() - 3 * 12) / 2, 0); // Center "CPU" title
  display.println("CPU");

  // CPU Hardware ID
  display.setTextSize(1);
  display.setCursor(0, 20);

  int cpuNameStart = inputString.indexOf("CPU:") + 4;
  int cpuNameEnd = inputString.indexOf("GPU");
  String cpuName = (cpuNameEnd > -1) ? inputString.substring(cpuNameStart, cpuNameEnd) : inputString.substring(cpuNameStart);
  cpuName.trim(); // Trim the CPU name

  display.print(cpuName);

  // CPU Frequency Display String
  int cpuCoreClockStart = inputString.indexOf("CHC") + 3;
  int cpuCoreClockEnd = inputString.indexOf("|", cpuCoreClockStart);
  String cpuClockString = inputString.substring(cpuCoreClockStart, cpuCoreClockEnd);
  cpuClockString.trim(); // Trim the CPU clock string

  display.setTextSize(1);
  display.setCursor(0, 35); // Place frequency information below the CPU name
  display.print("Freq: ");
  display.print(cpuClockString);
  display.println(" MHz");

  // CPU Temperature and Load
  int cpuStringStart = inputString.indexOf("C");
  int cpuDegree = inputString.indexOf("c");
  int cpuStringLimit = inputString.indexOf("|");
  String cpuTemperature = inputString.substring(cpuStringStart + 1, cpuDegree);
  String cpuLoad = inputString.substring(cpuDegree + 1, cpuStringLimit);
  cpuLoad.trim(); // Trim the CPU load string

  // CPU Load, All Core
  display.setCursor(0, 50); // Adjust for proper spacing
  display.setTextSize(2);
  display.print(cpuLoad);
  display.setTextSize(1);
  display.print("%");

  // CPU Temperature
  display.setCursor(70, 50); // Adjust for proper spacing
  display.setTextSize(2);
  display.print(cpuTemperature);
  display.setTextSize(1);
  display.print((char)247); // Degrees Symbol
  display.println("C");

  display.display();
   delay(2000);
}
