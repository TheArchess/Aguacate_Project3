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

                Serial.print("1\n");
            }
            else if (command == "outOFF")
            {
                digitalWrite(led, LOW);

                Serial.print("0\n");
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
/*
using UnityEngine;
using System.IO.Ports;
using TMPro;

enum TaskState
{
    INIT,
    WAIT_COMMANDS
}
public class Serial : MonoBehaviour
{
    private static TaskState taskState = TaskState.INIT;
    private SerialPort _serialPort;
    private byte[] buffer;
    public TextMeshProUGUI myText;
    public TextMeshProUGUI myButton;
    public TextMeshProUGUI myLed;
    private int counter = 0;
    public static bool btnOn = false;
    public static bool btnOff = false;
    public static bool btnread = false;
    void Start()
    {
        _serialPort = new SerialPort();
        _serialPort.PortName = "/dev/ttyACM0";
        _serialPort.BaudRate = 115200;
        _serialPort.DtrEnable = true;
        _serialPort.NewLine = "\n";
        _serialPort.Open();
        Debug.Log("Open Serial Port");
        buffer = new byte[128];
    }

    void Update()
    {
        //Codigo contador
        myText.text = counter.ToString();
        counter++;

        switch (taskState)
        {
            case TaskState.INIT:
                taskState = TaskState.WAIT_COMMANDS;
                Debug.Log("WAIT COMMANDS");
                break;
            case TaskState.WAIT_COMMANDS:
                
                if (btnOn==true)
                {
                    _serialPort.Write("outON\n");
                    Debug.Log("Send outON");

                    btnOn = false;
                }
                if (btnOff==true)
                {
                    _serialPort.Write("outOFF\n");
                    Debug.Log("Send outOFF");

                    btnOff = false;
                }

                if (btnread==true)
                {
                    _serialPort.Write("read\n");
                    Debug.Log("Send read");
                    btnread = false;
                }
                
                if (_serialPort.BytesToRead > 0)
                {
                    string response = _serialPort.ReadLine();

                    if (response.Remove('\n') == "0")
                    {
                        myLed.text = response.ToString();
                    }
                    if (response.Remove('\n') == "1")
                    {
                        myLed.text = response.ToString();
                    }
                    else
                    {
                        myButton.text = response.ToString();
                        myLed.text = response.ToString();
                    }
                    
                   
                    break;
                }

                break;
            default:
                Debug.Log("State Error");
                break;
        }
    }
    
    //Botón-OnClick
    public void EventButtonReadSend()
    {
        Debug.Log("Button Read Pressed");
        btnread = true;
    }
    public void EventButtonOFFSend()
    {
        Debug.Log("Button OFF Pressed");
        btnOff = true;
    }
    public void EventButtonONSend()
    {
        Debug.Log("Button ON Pressed");
        btnOn = true;
    }
}


*/