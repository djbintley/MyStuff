#include <Adafruit_NeoPixel.h>
//#include <WiFi.h>
//#include <WebServer.h>

// Define LED pin and number of pixels
#define LED_PIN     48       // Change if your RGB LED is connected to a different pin
#define NUM_PIXELS  1        // Only 1 onboard RGB LED

Adafruit_NeoPixel pixels(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Define the 5 colors to cycle through
uint32_t colors[] = {
  pixels.Color(255, 0, 0),    // Red
  pixels.Color(0, 255, 0),    // Green
  pixels.Color(0, 0, 255),    // Blue
  pixels.Color(255, 255, 0),  // Yellow
  pixels.Color(0, 255, 255)   // Cyan
};

void setup() {
  pixels.begin(); // Initialize the NeoPixel
  pixels.setBrightness(10); // Optional: reduce brightness (0–255)
}

void loop() {
  for (int i = 0; i < 5; i++) {
    pixels.setPixelColor(0, colors[1]);
    pixels.setBrightness((i+1)*63);
    pixels.show();
    delay(500); // Wait 1 second
  }
}
