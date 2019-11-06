#include <ForWarning_1.0.h>
#include <Wire.h>
ForWarning dataStructure;

int gasSensor = A0;
int numData = 10;
int numDataOfDust;
float dataOfDust[100];
float avgX;
float avgXsquare;
float slope;
float tip;
float avgY = 0;
float avgYsquare = 0;
float avgXY = 0;

void setup(void){
  Serial.begin(9600);
  dataStructure.resetAll();
  dataStructure.getNumberOfData(10);

  avgX = numData * (numData + 1) / (2*numData);
  avgXsquare = numData * (numData + 1) * (2 * numData + 1) / (6*numData);
}

void loop(){
  float k = analogRead(gasSensor);
  float filtered_k;
  
  Serial.print("before Filter :");
  Serial.print(k);

  dataStructure.SaveDataOfDust(k);
  filtered_k = dataStructure.CalculateFilteredDataForDust();

  Serial.print(" After filter :");
  Serial.println(filtered_k);
  Serial.print("num");
  Serial.print("    ");
  Serial.print("avgX");
  Serial.print("    ");
  Serial.print("avgY");
  Serial.print("    ");
  Serial.print("avgXY");
  Serial.print("    ");
  Serial.print("slope");
  Serial.print("    ");
  Serial.println("tip");
  Serial.print(dataStructure.numData);
  Serial.print("    ");
  Serial.print(dataStructure.avgX);
  Serial.print("    ");
  Serial.print(dataStructure.avgY);
  Serial.print("    ");
  Serial.print(dataStructure.avgXY);
  Serial.print("    ");
  Serial.print(dataStructure.slope);
  Serial.print("    ");
  Serial.println(dataStructure.tip);
  Serial.print(dataStructure.dataOfDust[0]);
  Serial.print("    ");
  Serial.print(dataStructure.dataOfDust[1]);
  Serial.print("    ");
  Serial.print(dataStructure.dataOfDust[2]);
  Serial.print("    ");
  Serial.print(dataStructure.dataOfDust[3]);
  Serial.print("    ");
  Serial.print(dataStructure.dataOfDust[4]);
  Serial.print("    ");
  Serial.print(dataStructure.dataOfDust[5]);
  Serial.print("    ");
  Serial.print(dataStructure.dataOfDust[6]);
  Serial.print("    ");
  Serial.print(dataStructure.dataOfDust[7]);
  Serial.print("    ");
  Serial.print(dataStructure.dataOfDust[8]);
  Serial.print("    ");
  Serial.println(dataStructure.dataOfDust[9]);
  Serial.print("    ");
  Serial.println(dataStructure.numDataOfDust);
  Serial.println();
  delay(1000);
}
/*
void loop(){
  float k = analogRead(gasSensor);
  float filtered_k;
  
  if (numDataOfDust < numData) {
    dataOfDust[numDataOfDust] = k;
  }
  else {
    //shift left
    int i;
    for (i = 0; i < numData - 1; i++) {
      dataOfDust[i] = dataOfDust[i + 1];
    }

    //put new data(input)
    dataOfDust[numData - 1] = k;
    numDataOfDust = numData;
  }

  numDataOfDust++;
  

  if (numDataOfDust < numData-1) {
    filtered_k=dataOfDust[numData-1];
  }
  else {
    avgY = 0;
    avgYsquare = 0;
    avgXY = 0;
    int i;

    for (i = 0; i < numData; i++) {
      avgY += dataOfDust[i] / numData;
      avgXY += (i + 1) * dataOfDust[i] / numData;
    }

    //Find slopes and tips
    slope = (avgXY - 5.5 * avgY) / (38.5 - 5.5 * 5.5);
    tip = (avgY * 38.5 - 5.5 * avgXY) / (38.5 - 5.5 * 5.5);

    filtered_k = slope * (numData + 1) + tip;
  }
  
  Serial.print("before Filter :");
  Serial.print(k);
  Serial.print(" After filter :");
  Serial.println(filtered_k);
  Serial.print(" avgY : ");
  Serial.print(avgY);
  Serial.print(" avgX : ");
  Serial.print(avgX);
  Serial.print(" avgXY : ");
  Serial.print(avgXY);
  Serial.print(" slope : ");
  Serial.print(slope);
  Serial.print(" tip : ");
  Serial.print(tip);
  Serial.print(" avgXsquare : ");
  Serial.println(avgXsquare);
  Serial.print(" numDataOfDust : ");
  Serial.print(numDataOfDust);
  Serial.print(" numData");
  Serial.print(numData);
  Serial.print(" dataOfDust : ");
  Serial.print(dataOfDust[0]);
  Serial.print("  ");
  Serial.print(dataOfDust[1]);
  Serial.print("  ");
  Serial.print(dataOfDust[2]);
  Serial.print("  ");
  Serial.print(dataOfDust[3]);
  Serial.print("  ");
  Serial.print(dataOfDust[4]);
  Serial.print("  ");
  Serial.print(dataOfDust[5]);
  Serial.print("  ");
  Serial.print(dataOfDust[6]);
  Serial.print("  ");
  Serial.print(dataOfDust[7]);
  Serial.print("  ");
  Serial.print(dataOfDust[8]);
  Serial.print("  ");
  Serial.println(dataOfDust[9]);
  Serial.println();
  
  delay(1000);
}
*/
