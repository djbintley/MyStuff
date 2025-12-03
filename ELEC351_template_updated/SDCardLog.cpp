#include "SDCardLog.hpp"

char SD_File[] = "Enviroment_Data.csv";
static const int BUFFER_SIZE = 60;     //number of samples to buffer
static const int LINE_MAX = 64;        //bytes per CSV line

 // Local buffer and mutex/state (file-scope)
static char sample_buffer[BUFFER_SIZE][LINE_MAX];
static int buffer_index = 0;
static bool buffer_full = false;
static Mutex buffer_mutex;

//Function that puts sensor data into the circular buffer
void sd_push_sample(float temperature, float pressure, float light){
    //Format data into a temp string first
    char tmp[LINE_MAX];
    int len = snprintf(tmp, LINE_MAX, "%.2f,%.2f,%.0f\n", temperature, pressure, light);
    if (len <= 0) return;

    //Copy into buffer under mutex
    buffer_mutex.lock();
    //copy line into the current slot
    strncpy(sample_buffer[buffer_index], tmp, LINE_MAX - 1);
    sample_buffer[buffer_index][LINE_MAX - 1] = '\0';
    buffer_index++;
    if (buffer_index >= BUFFER_SIZE) {
        buffer_full = true;
        buffer_index = 0; // prepare for overwrite after flush (circular)
    }
    buffer_mutex.unlock();

}


//Function that runs the SD Card thread
//Copies all the data from the circular buffer and the writes it to the SD card
void SDCard_thread()
{
    // big buffer: BUFFER_SIZE * LINE_MAX, but keep a little headroom
    static const int BIGBUF_MAX = BUFFER_SIZE * LINE_MAX + 16;
    char bigbuf[BIGBUF_MAX];

    while (true) {
        bool to_write = false;

        // Check buffer state
        buffer_mutex.lock();
        if (buffer_full) {
            //Copy the whole buffer out while holding the lock to keep data consistent
            char tmp_copy[BUFFER_SIZE][LINE_MAX];
            for (int i = 0; i < BUFFER_SIZE; ++i) {
                strncpy(tmp_copy[i], sample_buffer[i], LINE_MAX);
            }
            //Set buffer as empty
            buffer_full = false;
            buffer_mutex.unlock();

            // Build one big string
            bigbuf[0] = '\0';
            int offset = 0;
            for (int i = 0; i < BUFFER_SIZE; ++i) {
                int l = strlen(tmp_copy[i]);
                if (offset + l >= BIGBUF_MAX - 1) break; // prevent overflow
                memcpy(&bigbuf[offset], tmp_copy[i], l);
                offset += l;
            }
            bigbuf[offset] = '\0';

            // Only now write once to SD card
            if (sd.card_inserted()) {
                int result = sd.write_file(SD_File, bigbuf, true);
                if (result == 0) {
                    printf("SD Card Written to\r\n");
                } else {
                    printf("SD Card error %d\r\n", result);
                }
            } else {
                printf("SD card not detected ...\r\n");
            }
        } else {
            buffer_mutex.unlock();
        }

        // Sleep a bit and poll again. Using 500ms to be responsive; adjust if needed.
        ThisThread::sleep_for(500ms);
    }
}