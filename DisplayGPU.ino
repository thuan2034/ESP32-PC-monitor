void DisplayGPU(String inputString) {
  
  display.clearDisplay();

  // Display Title
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor((display.width() - 3 * 12) / 2, 0); // Center "GPU" title
  display.println("GPU");

  // GPU Hardware ID
  if (inputString.indexOf("GPU") > -1) {
    display.setTextSize(1);
    display.setCursor(0, 20);

    int gpuNameStart = inputString.indexOf("GPU:") + 4;
    if (inputString.indexOf("NVIDIA", gpuNameStart) > -1) {
      gpuNameStart += 7; // Skip "NVIDIA "
    }
    int gpuNameEnd = inputString.indexOf("|", gpuNameStart);
    String gpuName = inputString.substring(gpuNameStart, gpuNameEnd);
    gpuName.trim(); // Trim the GPU name

    display.print(gpuName);
  }

  // GPU Core Frequency Display String
  int gpuCoreClockStart = inputString.indexOf("GCC") + 3;
  int gpuCoreClockEnd = inputString.indexOf("|", gpuCoreClockStart);
  String gpuCoreClockString = inputString.substring(gpuCoreClockStart, gpuCoreClockEnd);
  gpuCoreClockString.trim(); // Trim the GPU core clock string

  display.setTextSize(1);
  display.setCursor(0, 35); // Place frequency information below the GPU name
  display.print("Freq: ");
  display.print(gpuCoreClockString);
  display.println(" MHz");

  // GPU Temperature and Load
  int gpuStringStart = inputString.indexOf("G", inputString.indexOf("C"));
  int gpuDegree = inputString.indexOf("c", gpuStringStart);
  int gpuStringLimit = inputString.indexOf("|", gpuStringStart);
  String gpuTemperature = inputString.substring(gpuStringStart + 1, gpuDegree);
  String gpuLoad = inputString.substring(gpuDegree + 1, gpuStringLimit);
  gpuLoad.trim(); // Trim the GPU load string

  // GPU Load, All Core
  display.setCursor(0, 50); // Adjust for proper spacing
  display.setTextSize(2);
  display.print(gpuLoad);
  display.setTextSize(1);
  display.print("%");

  // GPU Temperature
  display.setCursor(70, 50); // Adjust for proper spacing
  display.setTextSize(2);
  display.print(gpuTemperature);
  display.setTextSize(1);
  display.print((char)247); // Degrees Symbol
  display.println("C");

  display.display();
  delay(2000);
}
