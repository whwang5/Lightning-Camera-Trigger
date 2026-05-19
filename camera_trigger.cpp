//Placeholder thresholds and timing (subject to change)
const int RAD_CHANGE = 100;        //minimum radiation change threshold
const int LIGHT_CHANGE = 100;      //minimum light change threshold
const int TIME_WINDOW = 50;        //window for changes in milliseconds 

//assign pins to the different sensors
const int RAD_SENSOR_PIN = 15;
const int LIGHT_SENSOR_PIN = 26;
const int CAMERA_TRIGGER_PIN = 16;

//create storage space for the times of the time marks of the latest significant changes detected by the sensors
unsigned long lastRadTriggerTime = 0;
unsigned long lastLightTriggerTime = 0;

//stores previous signal values to help calculate the change in value
int previousRadValue = 0;
int previousLightValue = 0;

void setup() {
    pinMode(RAD_SENSOR_PIN, INPUT);
    pinMode(LIGHT_SENSOR_PIN, INPUT);
    pinMode(CAMERA_TRIGGER_PIN, OUTPUT);

    digitalWrite(CAMERA_TRIGGER_PIN, LOW); // starts with the camera off

 //reads the starting values for the sensors

    previousRadValue = analogRead(RAD_SENSOR_PIN); 
    previousLightValue = analogRead(LIGHT_SENSOR_PIN);
}

void loop() {
    unsigned long currentTime = millis(); //sets units to milliseconds

    int currentRadValue = analogRead(RAD_SENSOR_PIN);
    int currentLightValue = analogRead(LIGHT_SENSOR_PIN);

    int radChange = abs(currentRadValue - previousRadValue);
    int lightChange = abs(currentLightValue - previousLightValue);

    if (radChange >= RAD_CHANGE) {
        lastRadTriggerTime = currentTime;
    }

    if (lightChange >= LIGHT_CHANGE) {
        lastLightTriggerTime = currentTime;
    }

    if (abs((long)(lastRadTriggerTime - lastLightTriggerTime)) <= TIME_WINDOW) {
        triggerCamera();
    }

//store current values as the previous ones so they can be compared to the ones in the next cycle
    previousRadValue = currentRadValue;
    previousLightValue = currentLightValue;

    delay(1);
}

void triggerCamera() {
    digitalWrite(CAMERA_TRIGGER_PIN, HIGH); //sends trigger to turn on the camera
    delay(100);   // camera trigger pulse length
    digitalWrite(CAMERA_TRIGGER_PIN, LOW);
}

