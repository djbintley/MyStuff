#include "SDCardLog.hpp"

char SD_File[] = "Enviroment_Data.csv";

//Function that runs the SD Card thread
void SDCard_thread()
{
    while (true) {
        char SD_Data[] = "Dave is Cool\n";
        int repeats = 0;
        // TODO: read from queue
        // TODO: write CSV line to SD every N samples
        
        if (repeats == 600){
            if(sd.card_inserted()){
                // Append the string to a file
                sd.write_file(SD_File, SD_Data, true);
            }else{
                printf("SD card not detected...\r\n");
            }   
            repeats = 0;
        }
        repeats++;
        ThisThread::sleep_for(100ms); 
    }
}