#include "typewise-alert.h"
#include <stdio.h>

//modifying this array if the cooling values changes, Increase/decrease the array size based on the colling type
int LowerLimit[MAX_Cooling] = { 0,  0,  0};
int UpperLimit[MAX_Cooling] = {35, 45, 40};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  if(coolingType < MAX_Cooling)
  {
    int lowerLimit = LowerLimit[coolingType];
    int upperLimit = UpperLimit[coolingType];
    return inferBreach(temperatureInC, lowerLimit, upperLimit);
  }
  else
  { 
     return -1;
  }
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  switch(breachType) {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      break;
  }
}
