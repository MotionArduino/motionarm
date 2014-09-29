#include <Servo.h>

#define DEBUG    0

int numdata[6] = {0};
String comdata = "";
Servo myservo0;
Servo myservo1;
Servo myservo2;
Servo myservo3;

int mark = 0;
int val0 = 0;
int val1 = 0;
int val2 = 0;
int val3 = 0;

void setup()
{
    myservo0.attach(2);    //Grab
    myservo1.attach(3);    //Base
    myservo2.attach(4);    //Vertical
    myservo3.attach(5);    //Front and back
    
    Serial.begin(9600);
    myservo0.write(15);
    delay(15);
    myservo1.write(0);
    myservo2.write(0);
    myservo3.write(0);
}

void loop()
{
    //reset
    delay(50);
    int j = 0;            // output range of X or Y movement; affects movement sp
    comdata = "";
    mark = 0;
    for(int i = 0; i < 6; i++)
    {
        numdata[i] = 0;
    }

    while (Serial.available() > 0)
    {
        //读入之后将字符串，串接到comdata上面。
        comdata += char(Serial.read());
        //延时一会，让串口缓存准备好下一个数字，不延时会导致数据丢失，
        delay(2);
        //标记串口读过数据，如果没有数据的话，直接不执行这个while了。
        mark = 1;
    }
    
    if(mark == 1) //如果接收到数据则执行comdata分析操作，否则什么都不做。
    {
#if DEBUG
        //显示刚才输入的字符串（可选语句）
        Serial.println(comdata);
        //显示刚才输入的字符串长度（可选语句）
        Serial.println(comdata.length());
        Serial.println("Info:");
#endif
        /*******************下面是重点*******************/
        for(int i = 0; i < comdata.length() ; i++)
        {
#if DEBUG          
            Serial.println(comdata[i]);
#endif
            if(comdata[i] == ',')
            {
                j++;
            }
            else
            {
                numdata[j] = numdata[j] * 10 + (comdata[i] - '0');
            }
        }

#if DEBUG
        Serial.println("Print res:");
#endif

        comdata = String("");
        val0 = numdata[0];
        val1 = numdata[1];
        val2 = numdata[2];
        val3 = numdata[3];

#if DEBUG        
        Serial.println(val0);
        Serial.println(val1);
        Serial.println(val2);
        Serial.println(val3);
#endif

        if(val0 <= 180)
        {
            myservo0.write(val0);
        }
        if(val1 <= 180)
        {
            myservo1.write(val1);
        }
        if(val2 <= 180)
        {
            myservo2.write(val2);
        }
        if(val3 <= 180)
        {
            myservo3.write(val3);
        }
    }
    delay(10);
}


