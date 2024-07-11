const int numSensors = 5;
const int flexPins[numSensors] = {A0, A1, A2, A3, A4};
const String flexNames[numSensors] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
int maxResistance[numSensors] = {0, 0, 0, 0, 0};
int minResistance[numSensors] = {1023, 1023, 1023, 1023, 1023};
bool calibrationComplete = false;
const int matchThreshold = 50;

struct Gesture {
  int values[5];  
  char letter;    
};

const int numberOfLetters = 6;
Gesture gestures[numberOfLetters] = { 
  // Thumb, Index, Middle, Ring, Pinky 
  {{0, 180, 180, 180, 180}, 'A'}, 
  {{180, 0, 0, 0, 0}, 'B'},   
  {{90, 90, 90, 90, 90}, 'C'}, 
  {{180, 0, 180, 180, 180}, 'D'},
  {{180, 180, 180, 180, 180}, 'E'},
  {{180, 180, 0, 0, 0}, 'F'},
};

void setup() {
  Serial.begin(9600);
}

void loop() {
  // calibration sequence
  static int calibrationCount = 0;
  int flexValues[numSensors];

  for (int i = 0; i < numSensors; i++) {
    flexValues[i] = analogRead(flexPins[i]);

    if (!calibrationComplete) {
      if (flexValues[i] > maxResistance[i]) {
        maxResistance[i] = flexValues[i];
      }
      if (flexValues[i] < minResistance[i]) {
        minResistance[i] = flexValues[i];
      }
    } 
    else {
      // added +30 nd -10 arbitrarily to adjust for offset
      int angle = map(flexValues[i], maxResistance[i]-10, minResistance[i]+30, 0, 180); 
      
      // constrain the angle to stay within 0 to 180
      angle = constrain(angle, 0, 180);
      flexValues[i] = angle;

      Serial.print("Sensor: ");
      Serial.print(flexNames[i]);
      Serial.print(" | Angle: ");
      Serial.print(angle);
      Serial.print(" | Flex Value: ");
      Serial.print(flexValues[i]); 
      Serial.print(" | MaxResistance: ");
      Serial.print(maxResistance[i]);
      Serial.print(" | MinResistance: ");
      Serial.println(minResistance[i]);
    }
  }

  // calibration logic
  if (calibrationComplete) {
    char recognizedLetter = recognizeGesture(flexValues);
    if (recognizedLetter != '\0') {
      Serial.print("Gesture recognized: ");
      Serial.println(recognizedLetter);
    }
  }

  if (!calibrationComplete) {
    Serial.println("Calibrating...");
    calibrationCount++;
    if (calibrationCount > 10) {
      calibrationComplete = true;
      Serial.println("Calibration Complete!");
    }
  }

  Serial.println();
  delay(500);
}

char recognizeGesture(int currentValues[5]) {
  for (int i = 0; i < numberOfLetters; i++) {
    int difference = 0;
    for (int j = 0; j < 5; j++) {
      difference += abs(currentValues[j] - gestures[i].values[j]);
    }
    if (difference < matchThreshold) {
      return gestures[i].letter;
    }
  }
  return '\0';
}


// Old Code

// // const int flexPinThumb = A0;
// // const int flexPinIndex = A1;
// // const int flexPinMiddle = A2;
// // const int flexPinRing = A3;
// // const int flexPinPinky = A4;
// const int flexPin = A0;
// int maxVal = 0;

// void setup() {
//   Serial.begin(9600);
// }

// void loop() {
//   int flexVal = analogRead(flexPin);
//   if (flexVal > maxVal) {
//     maxVal = flexVal;
//   }

//   Serial.print("Sensor: ");
//   Serial.println(flexVal); 
//   Serial.print("MaxVal: ");
//   Serial.println(maxVal);
//   Serial.println();
//   delay(500);
//   // int resistanceThumb = analogRead(flexPinThumb);
//   // int resistanceIndex = analogRead(flexPinIndex);
//   // int resistanceMiddle = analogRead(flexPinMiddle);
//   // int resistanceRing = analogRead(flexPinRing);
//   // int resistancePinky = analogRead(flexPinPinky);
// }

/*
const int flexPin = A1;
int maxResistance = 0;
int minResistance = 1023;
bool calibrationComplete = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int flexVal = analogRead(flexPin);
  
  // Update the maxResistance and minResistance values based on current reading
  if (!calibrationComplete) {
    if (flexVal > maxResistance) {
      maxResistance = flexVal;
    }
    if (flexVal < minResistance) {
      minResistance = flexVal;
    }

    // Add a condition to stop calibration after a certain number of readings or time
    // Here we assume a simple example with 1000 readings for calibration
    static int calibrationCount = 0;
    calibrationCount++;
    if (calibrationCount > 10) {
      calibrationComplete = true;
    }
  }

  // Map the sensor value to the desired range (0 to 180) after calibration
  int angle = map(flexVal, maxResistance-10, minResistance+30, 0, 180);
  
  // Constrain the angle to stay within 0 to 180
  angle = constrain(angle, 0, 180);

  Serial.print("Sensor: ");
  Serial.println(flexVal); 
  Serial.print("Angle: ");
  Serial.println(angle);
  Serial.print("Max Resistance: ");
  Serial.println(maxResistance);
  Serial.print("Min Resistance: ");
  Serial.println(minResistance);
  Serial.println();
  
  delay(500);
}

*/

 /*
const int numSensors = 5;
const int flexPins[numSensors] = {A0, A1, A2, A3, A4};
const String flexNames[numSensors] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
int maxResistance[numSensors] = {0, 0, 0, 0, 0};
int minResistance[numSensors] = {1023, 1023, 1023, 1023, 1023};
bool calibrationComplete = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
  static int calibrationCount = 0;

  for (int i = 0; i < numSensors; i++) {
    int flexVal = analogRead(flexPins[i]);

    if (!calibrationComplete) {
      if (flexVal > maxResistance[i]) {
        maxResistance[i] = flexVal;
      }
      if (flexVal < minResistance[i]) {
        minResistance[i] = flexVal;
      }
    } else {
      int angle = map(flexVal, maxResistance[i]-10, minResistance[i]+30, 0, 180); // added +30 nd -10 arbitrarily to adjust for offset
      
      // constrain the angle to stay within 0 to 180
      angle = constrain(angle, 0, 180);

      Serial.print("Sensor: ");
      Serial.print(flexNames[i]);
      // Serial.print(": ");
      // Serial.print(flexVal); 
      Serial.print(" | Angle: ");
      Serial.print(angle);
      Serial.print(" | MaxResistance: ");
      Serial.print(maxResistance[i]);
      Serial.print(" | MinResistance: ");
      Serial.println(minResistance[i]);

      // Serial.println();
      // Serial.print("Letter: ");
      // Serial.println("[implement later]");
    }
  }

  // Update calibration status
  if (!calibrationComplete) {
    calibrationCount++;
    if (calibrationCount > 10) {
      calibrationComplete = true;
      Serial.println("Calibration Complete");
    }
  }

  Serial.println();
  delay(500);
}

*/




// const int flexPinThumb = A0;
// const int flexPinIndex = A1;
// const int flexPinMiddle = A2;
// const int flexPinRing = A3;
// const int flexPinPinky = A4;

// int maxResistanceThumb = 0;
// int maxResistanceIndex = 0;
// int maxResistanceMiddle = 0;
// int maxResistanceRing = 0;
// int maxResistancePinky = 0;

// int minResistanceThumb = 1024;
// int minResistanceIndex = 1024;
// int minResistanceMiddle = 1024;
// int minResistanceRing = 1024;
// int minResistancePinky = 1024;

// bool calibrationComplete = false;

// void setup() {
//   Serial.begin(9600);
// }

// void loop() {
//   int resistanceThumb = analogRead(flexPinThumb);
//   int resistanceIndex = analogRead(flexPinIndex);
//   int resistanceMiddle = analogRead(flexPinMiddle);
//   int resistanceRing = analogRead(flexPinRing);
//   int resistancePinky = analogRead(flexPinPinky);
  
//   // Update the maxResistance and minResistance values based on current reading
//   if (!calibrationComplete) {
//     if (resistanceThumb > maxResistanceThumb) {
//       maxResistanceThumb = resistanceThumb;
//     }
//     if (resistanceThumb < minResistanceThumb) {
//       minResistanceThumb = resistanceThumb;
//     }

//     if (resistanceIndex > maxResistanceIndex) {
//       maxResistanceIndex = resistanceIndex;
//     }
//     if (resistanceIndex < minResistanceIndex) {
//       minResistanceIndex = resistanceIndex;
//     }

//     if (resistanceMiddle > maxResistanceMiddle) {
//       maxResistanceMiddle = resistanceMiddle;
//     }
//     if (resistanceMiddle < minResistanceMiddle) {
//       minResistanceMiddle = resistanceMiddle;
//     }

//     if (resistanceRing > maxResistanceRing) {
//       maxResistanceRing = resistanceRing;
//     }
//     if (resistanceRing < minResistanceRing) {
//       minResistanceRing = resistanceRing;
//     }

//     if (resistancePinky > maxResistancePinky) {
//       maxResistancePinky = resistancePinky;
//     }
//     if (resistancePinky < minResistancePinky) {
//       minResistancePinky = resistancePinky;
//     }

//     // Add a condition to stop calibration after a certain number of readings or time
//     // Here we assume a simple example with 1000 readings for calibration
//     static int calibrationCount = 0;
//     calibrationCount++;
//     if (calibrationCount > 100) {
//       calibrationComplete = true;
//     }
//   }

//   // Map the sensor value to the desired range (0 to 180) after calibration
//   int angleThumb = map(resistanceThumb, maxResistanceThumb-10, minResistanceThumb+30, 0, 180);
//   int angleIndex = map(resistanceIndex, maxResistanceIndex-10, minResistanceIndex+30, 0, 180);
//   int angleMiddle = map(resistanceMiddle, maxResistanceMiddle-10, minResistanceMiddle+30, 0, 180);
//   int angleRing = map(resistanceRing, maxResistanceRing-10, minResistanceRing+30, 0, 180);
//   int anglePinky = map(resistancePinky, maxResistancePinky-10, minResistancePinky+30, 0, 180);
  
//   // Constrain the angle to stay within 0 to 180
//   angleThumb = constrain(angleThumb, 0, 180);
//   angleIndex = constrain(angleIndex, 0, 180);
//   angleMiddle = constrain(angleMiddle, 0, 180);
//   angleRing = constrain(angleRing, 0, 180);
//   anglePinky = constrain(anglePinky, 0, 180);

//   Serial.print("Sensor: " + resistanceThumb);
//   Serial.print(" Angle: " + angleThumb);
//   Serial.print(" Max Resistance: " + maxResistanceThumb);
//   Serial.print(" Min Resistance: " + minResistanceThumb);
//   Serial.println();

//   // Serial.print("Sensor: " + resistanceIndex + " Angle: " + angleIndex + " Max Resistance: " + maxResistanceIndex + " Min Resistance: " + minResistanceIndex);
//   // Serial.println();
  
//   // Serial.print("Sensor: " + resistanceMiddle + " Angle: " + angleMiddle + " Max Resistance: " + maxResistanceMiddle + " Min Resistance: " + minResistanceMiddle);
//   // Serial.println();
  
//   // Serial.print("Sensor: " + resistanceRing + " Angle: " + angleRing + " Max Resistance: " + maxResistanceRing + " Min Resistance: " + minResistanceRing);
//   // Serial.println();
  
//   // Serial.print("Sensor: " + resistancePinky + " Angle: " + anglePinky + " Max Resistance: " + maxResistancePinky + " Min Resistance: " + minResistancePinky);
//   // Serial.println();
  
//   delay(500);
// }