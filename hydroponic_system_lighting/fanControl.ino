/*
   Fan control on high temperature
*/

void fanControl()
{
  temperatureValue = analogRead(tempPin);
  temperatureC = (double) temperatureValue * (5 / 10.24); // convert the voltage to temperture

  Serial.print("temperature: ");
  Serial.print(temperatureC);
  Serial.println("C");
  Serial.print("fan state ");
  Serial.println(fanState);

  lcd.setCursor(0, 1);
  lcd.print(temperatureC);
  lcd.print("C ");
  lcd.print("Fan ");
  lcd.print(fanState);

  if (temperatureC > 50 && fanState == LOW)
  {
    fanState = HIGH;
    digitalWrite(fanPin, !fanState); // 0 to switch on Fan
    Serial.print("fan state");
    Serial.println(fanState);
  } else if (temperatureC < 38 )
  {
    fanState = LOW;
    digitalWrite(fanPin, !fanState); // 1 to switch off fan
    Serial.print("fan state ");
    Serial.println(fanState);
  }
}

