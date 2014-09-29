#include <Servo.h>

#define DEBUG           0
#define FILTER_COUNT    5

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

int last_val0 = 0;
int last_val1 = 0;
int last_val2 = 0;
int last_val3 = 0;

int val_interval = 0;
int loop_count = 0;

void setup()
{
    myservo0.attach(2);    //Grab
    myservo1.attach(3);    //Base
    myservo2.attach(4);    //Vertical
    myservo3.attach(5);    //Front and back
    
    Serial.begin(57600);
    myservo0.write(15);
    delay(15);
    myservo1.write(0);
    myservo2.write(0);
    myservo3.write(0);
}

void loop()
{
    //reset
    delay(10);
    
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
            if(abs(val0 - last_val0) >= FILTER_COUNT) {
                val_interval = (val0 - last_val0) / FILTER_COUNT;
                loop_count = FILTER_COUNT;
            } else {
                val_interval = 1;
                loop_count = abs(val0 - last_val0);
            }
            
            //Move to the place fluently
            for(int i = 1; i < loop_count; i++) {
                myservo0.write(last_val0 + (val_interval * i));
            }
            
            myservo0.write(val0);
            
            last_val0 = val0;
        }
        if(val1 <= 180)
        {
            if(abs(val1 - last_val1) >= FILTER_COUNT) {
                val_interval = (val1 - last_val1) / FILTER_COUNT;
                loop_count = FILTER_COUNT;
            } else {
                val_interval = 1;
                loop_count = abs(val1 - last_val1);
            }
            
            for(int i = 1; i < loop_count; i++) {
                myservo1.write(last_val1 + (val_interval * i));
            }
            
            myservo1.write(val1);
            
            last_val1 = val1;
        }
        if(val2 <= 180)
        {
            if(abs(val2 - last_val2) >= FILTER_COUNT) {
                val_interval = (val2 - last_val2) / FILTER_COUNT;
                loop_count = FILTER_COUNT;
            } else {
                val_interval = 1;
                loop_count = abs(val2 - last_val2);
            }
            
            for(int i = 1; i < loop_count; i++) {
                myservo2.write(last_val2 + (val_interval * i));
            }
            
            myservo2.write(val2);
            
            last_val2 = val2;
        }
        if(val3 <= 180)
        {
            if(abs(val3 - last_val3) >= FILTER_COUNT) {
                val_interval = (val3 - last_val3) / FILTER_COUNT;
                loop_count = FILTER_COUNT;
            } else {
                val_interval = 1;
                loop_count = abs(val3 - last_val3);
            }
            
            for(int i = 1; i < loop_count; i++) {
                myservo3.write(last_val3 + (val_interval * i));
            }
            
            myservo3.write(val3);
            
            last_val3 = val3;
        }
    }
    delay(10);
}


