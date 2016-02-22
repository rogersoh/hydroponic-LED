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

  lcd.setCursor(0, 1);
  lcd.print(temperatureC);
  lcd.print("C ");
  lcd.print("Fan ");
  lcd.print(fanState);

  if (temperatureC > 50 && fanState == LOW)
  {
    fanState = HIGH;
    digitalWrite(fanPin, fanState);
    Serial.print("fan ");
    Serial.println(fanState);
  } else if (temperatureC < 37 && fanState == HIGH)
  {
    fanState = LOW;
    digitalWrite(fanPin, fanState);
    Serial.print("fan ");
    Serial.println(fanState);
  }
}

