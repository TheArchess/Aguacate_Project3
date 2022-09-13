#include <Arduino.h>
#include "task1.h"

String btnState(uint8_t btnState)
{
    if (btnState == HIGH)
    {
        return "OFF";
    }
    else
        return "ON";
}

void task2()
{
    enum class TaskStates
    {
        INIT,
        WAIT_COMMANDS
    };

    static TaskStates taskState = TaskStates::INIT;
    constexpr uint8_t led = 14;
    constexpr uint8_t button = 12;

    switch (taskState)
    {
    case TaskStates::INIT:
    {
        Serial.begin(115200);
        pinMode(led, OUTPUT);
        digitalWrite(led, LOW);
        pinMode(button, INPUT_PULLUP);

        taskState = TaskStates::WAIT_COMMANDS;
        break;
    }
    case TaskStates::WAIT_COMMANDS:
    {
        if (Serial.available() > 0)
        {
            String command = Serial.readStringUntil('\n');
            if (command == "outON")
            {
                digitalWrite(led, HIGH);

                Serial.print("1");
                Serial.print('\n');

            }
            else if (command == "outOFF")
            {
                digitalWrite(led, LOW);

                Serial.print("0");
                Serial.print('\n');
            }
            else if (command == "read")
            {
                if ((digitalRead(button) == LOW) && (digitalRead(led) == LOW))
                {
                    Serial.print("0,0");
                    Serial.print('\n');
                }
                else if ((digitalRead(button) == HIGH) && (digitalRead(led) == LOW))
                {
                    Serial.print("1,0");
                    Serial.print('\n');
                }
                else if ((digitalRead(button) == LOW) && (digitalRead(led) == HIGH))
                {
                    Serial.print("0,1");
                    Serial.print('\n');
                }
                else if ((digitalRead(button) == HIGH) && (digitalRead(led) == HIGH))
                {
                    Serial.print("1,1");
                    Serial.print('\n');
                }
            }
        }
        break;
    }

    default:
    {
        break;
    }
    }
}
