/* ===================================================
C code : test.cpp
* ===================================================
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "RCSwitch.h"
#include "RcOok.h"
#include "Sensor.h"
#include <iostream>
#include <stdexcept>

std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

int main(int argc, char *argv[])
{
	int RXPIN = 1;
	int TXPIN = 0;

	if(wiringPiSetup() == -1)
	{
		return 0;
	}

	RCSwitch *rc = new RCSwitch(RXPIN,TXPIN);

	while (1)
	{
		if (rc->OokAvailable())
		{
			char message[100];

			rc->getOokCode(message);

			Sensor *s = Sensor::getRightSensor(message);
			if (s!= NULL)
			{
				if((argc>=2) && (s->getChannel()>0)) {
					char command[1000];
					snprintf(command, sizeof(command), "%spost.sh %d %f %f %d", argv[1], s->getChannel(), s->getTemperature(), s->getHumidity(), s->isBatteryLow());
					exec(command);
				}

				if((argc==3) && (s->getChannel()>0)) {
					printf("Temp : %f\n",s->getTemperature());
					printf("Humidity : %f\n",s->getHumidity());
					printf("Channel : %d\n",s->getChannel());
				}
}
			delete s;
		}
		delay(100);
	}
}
