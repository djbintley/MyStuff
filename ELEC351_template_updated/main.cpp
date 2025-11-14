#include "mbed.h"
#include "uop_msb.h"

/*
#define TRAFFIC_LIGHT_DELAY 1000
#define ENV_SAMPLE_DELAY 500

// Function prototypes
void Traffic_Lights();
void LCD_BackLight_Effect();
void Bar_Flash();
void clearMatrix();
void matrix_scan();
void sevenseg_count_thread();
float sample_adc(int);
void environment_data();
void dac_thread();
void dac_out(int, float);
void mpu_thread();
void button_thread();

// Thread handles
Thread traffic_thr;
Thread lcd_bl_thr;
Thread bar_thr;
Thread matrix_thr;
Thread seven_seg_thr;
Thread env_sensor_thr;
Thread dac_thr;
Thread motion_thr;
Thread button_thr;
*/

int main()
{

    printf("\n\nStarting...\n");

    /*********SD Card*********/
    #ifdef USE_SD_CARD
    if(sd.card_inserted()){
        // Create test string 
        char test_string[] = "This is the Plymouth University EEER Module Support Board Test\n";
        // Write the string to a file
        sd.write_file("msb_test.txt", test_string,true);
        // print the contents of the file we've just written to
        sd.print_file("msb_test.txt",true);
        // Copy the contents back into another array
        char array_to_copy_to[256];
        sd.copy_file("msb_test.txt", array_to_copy_to,sizeof(array_to_copy_to),true);
        // Print the new array
        printf("%s\n",array_to_copy_to);
    }
    else{
        printf("SD card not detected...\r\n");
    }
    #endif
    
    while(1){
        ThisThread::sleep_for(osWaitForever);
    }

}




