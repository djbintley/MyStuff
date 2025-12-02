#include "SDCardLog.hpp"

char SD_File[] = "Enviroment_Data.csv";
static const int BUFFER_SIZE = 60;

//Function that runs the SD Card thread
void SDCard_thread(){
    float t, p, l;
    // Buffer to hold 60 CSV rows
    char buffer[BUFFER_SIZE][64];
    int index = 0;
    while (true) {
        sensorData.get(t, p, l);
        //Converts values into CSV 
        sprintf(buffer[index], "%.2f,%.2f,%.0f\n", t, p, l);
        index++;
        if (index >= BUFFER_SIZE){
            if(sd.card_inserted()){
                // Write all 60 buffered lines
                for (int i = 0; i < BUFFER_SIZE; i++) {
                    int result = sd.write_file((char*)SD_File, buffer[i], true);

                    if (result != 0) {
                        printf("SD Card failed writing line %d\n", i);
                    }
                }
                printf("SD Card Updated\r\n");
            }else{
                printf("SD card not detected...\r\n");
            }   
            index = 0;
        }
        //Sleep while sensors read again
        ThisThread::sleep_for(1s); 
    }
}