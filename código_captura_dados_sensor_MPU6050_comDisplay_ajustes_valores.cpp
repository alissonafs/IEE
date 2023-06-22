// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  display.display();
  delay(500); // Pause for 2 seconds
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setRotation(0);


  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);
}

void loop() {
  // variaveis de armazenamento
  double  ax = 0.0, 
          ay = 0.0,
          az = 0.0;

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  
  // 100 leitura para criar estabilidade
  for (int i = 0; i < 100; i++){
    mpu.getEvent(&a, &g, &temp);
    ax = ax + a.acceleration.x * 0.1019716212978; 
    ay = ay + a.acceleration.y * 0.1019716212978;
    az = az + a.acceleration.z * 0.1019716212978;
  }

  display.clearDisplay();
  display.setCursor(0, 0);

  /*codigo para substituir*/
  // pega a media dos valores das variaveis a serem trabalhadas
  ax = ax/100; 
  ay = ay/100;
  az = az/100;

  if (ax > 1.000) ax = 1.000; else if(ax < -1.000) ax = -1.000;
  if (ay > 1.000) ay = 1.000; else if(ay < -1.000) ay = -1.000;
  if (az > 1.000) az = 1.000; else if(az < -1.000) az = -1.000;

  int     ax_graus = (180/M_PI)*acos(ax),
          ay_graus = (180/M_PI)*acos(ay),
          az_graus = (180/M_PI)*acos(az);

  
  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(ax);
  Serial.print(", Y: ");
  Serial.print(ay);
  Serial.print(", Z: ");
  Serial.print(az);
  Serial.println(" g");
/* Print out the values */
  Serial.print("graus X: ");
  Serial.print(ax_graus);
  Serial.print(", Y: ");
  Serial.print(ay_graus);
  Serial.print(", Z: ");
  Serial.print(az_graus);
  Serial.println(" graus");


  display.println("Accelerometer - g");
  display.print(ax, 1);
  display.print(", ");
  display.print(ay, 1);
  display.print(", ");
  display.print(az, 1);
  display.println("");
  display.println("");
  
  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x * 57.2958);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y * 57.2958);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z * 57.2958);
  Serial.println(" deg/s");

  /*Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");*/

  Serial.println("");
  
  display.println("Gyroscope - deg/s");
  display.print(g.gyro.x * 57.2958, 1);
  display.print(", ");
  display.print(g.gyro.y * 57.2958, 1);
  display.print(", ");
  display.print(g.gyro.z * 57.2958, 1);
  display.println("");

  display.display();
  delay(400);
}