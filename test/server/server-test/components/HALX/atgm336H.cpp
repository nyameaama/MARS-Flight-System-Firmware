#include"driver/uart.h"
#include "esp_log.h"
#include <cstring>
#include"atgm336H.h"
#include "minmea.h"

#define GPS_UART_NUM UART_NUM_2
#define GPIO_NUM_RX 16
#define GPIO_NUM_TX 17
#define ECHO_TEST_RTS (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS (UART_PIN_NO_CHANGE)
#define BUF_SIZE (1024)

double latX,longX,speedX;
double latdev,longdev,altdev;
minmea_float* trueTrackdeg, magTrackdeg, speed_kph;
int hrs,mins,secs,day,month,year,hour_offset,min_offset;
int sat_nr, elevation, azimuth, snr;

void ATGM336H::init_ATGM_module(){
    //Configure parameters of an UART driver,
    //communication pins and install the driver 
    uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };
    int intr_alloc_flags = 0;

#if CONFIG_UART_ISR_IN_IRAM
    intr_alloc_flags = ESP_INTR_FLAG_IRAM;
#endif

    ESP_ERROR_CHECK(uart_param_config(GPS_UART_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(GPS_UART_NUM, GPIO_NUM_TX, GPIO_NUM_RX, ECHO_TEST_RTS, ECHO_TEST_CTS));
    ESP_ERROR_CHECK(uart_driver_install(GPS_UART_NUM, BUF_SIZE * 2, 0, 0, NULL, intr_alloc_flags));

}

char* ATGM336H::pullATGM_data() {
    static char nmea_buffer[128]; // Static buffer to store NMEA sentence
    uint8_t data;

    // Read one byte from UART
    uart_read_bytes(GPS_UART_NUM, &data, 1, portMAX_DELAY);

    if (data == '\n') {
        // Print NMEA sentence buffer as a string
        ESP_LOGI("TAG", "Received NMEA: %s", nmea_buffer);
        memset(nmea_buffer, 0, sizeof(nmea_buffer)); // Clear buffer
    } else {
        // Append received byte to NMEA sentence buffer
        strncat(nmea_buffer, (const char *)&data, 1);
    }

    return nmea_buffer;
}

void ATGM336H::updateStack(){
    auto line = pullATGM_data();
    switch (minmea_sentence_id(line, false)) {
        case MINMEA_SENTENCE_RMC: {
            struct minmea_sentence_rmc frame;
            if (minmea_parse_rmc(&frame, line)) {
                //"$xxRMC floating point degree coordinates and speed: (%f,%f) %f\n",
                latX = minmea_tocoord(&frame.latitude);
                longX = minmea_tocoord(&frame.longitude);
                speedX = minmea_tofloat(&frame.speed);
            }
            else {
                //printf(INDENT_SPACES "$xxRMC sentence is not parsed\n");
            }
            } break;

        case MINMEA_SENTENCE_GGA: {
            struct minmea_sentence_gga frame;
            if (minmea_parse_gga(&frame, line)) {
                //printf(INDENT_SPACES "$xxGGA: fix quality: %d\n", frame.fix_quality);
            }
            else {
                //printf(INDENT_SPACES "$xxGGA sentence is not parsed\n");
            }
        } break;

        case MINMEA_SENTENCE_GST: {
            struct minmea_sentence_gst frame;
            if (minmea_parse_gst(&frame, line)) {
                //printf(INDENT_SPACES "$xxGST floating point degree latitude, longitude and altitude error deviation: (%f,%f,%f)",
                latdev = minmea_tofloat(&frame.latitude_error_deviation);
                longdev = minmea_tofloat(&frame.longitude_error_deviation),
                altdev = minmea_tofloat(&frame.altitude_error_deviation);
            }
            else {
                //printf(INDENT_SPACES "$xxGST sentence is not parsed\n");
            }
        } break;

        case MINMEA_SENTENCE_GSV: {
            struct minmea_sentence_gsv frame;
            if (minmea_parse_gsv(&frame, line)) {
                //printf(INDENT_SPACES "$xxGSV: message %d of %d\n", frame.msg_nr, frame.total_msgs);
                //printf(INDENT_SPACES "$xxGSV: satellites in view: %d\n", frame.total_sats);
                for (int i = 0; i < 4; i++){
                    //printf(INDENT_SPACES "$xxGSV: sat nr %d, elevation: %d, azimuth: %d, snr: %d dbm\n",
                    sat_nr = frame.sats[i].nr;
                    elevation = frame.sats[i].elevation;
                    azimuth = frame.sats[i].azimuth;
                    snr = frame.sats[i].snr;
                }
            }else {
                //printf(INDENT_SPACES "$xxGSV sentence is not parsed\n");
            }
            } break;

            case MINMEA_SENTENCE_VTG: {
               struct minmea_sentence_vtg frame;
               if (minmea_parse_vtg(&frame, line)) {
                    //printf(INDENT_SPACES "$xxVTG: true track degrees = %f\n",
                    //trueTrackdeg = (&frame.true_track_degrees);
                    //printf(INDENT_SPACES "        magnetic track degrees = %f\n",
                    //magTrackdeg = (&frame.magnetic_track_degrees);
                    //printf(INDENT_SPACES "        speed kph = %f\n",
                    //speed_kph = (&frame.speed_kph);
               }
               else {
                    //printf(INDENT_SPACES "$xxVTG sentence is not parsed\n");
               }
            } break;

            case MINMEA_SENTENCE_ZDA: {
                struct minmea_sentence_zda frame;
                if (minmea_parse_zda(&frame, line)) {
                    //printf(INDENT_SPACES "$xxZDA: %d:%d:%d %02d.%02d.%d UTC%+03d:%02d\n",
                    hrs = frame.time.hours;
                    mins = frame.time.minutes;
                    secs = frame.time.seconds;
                    day = frame.date.day;
                    month = frame.date.month;
                    year = frame.date.year;
                    hour_offset = hour_offset;
                    min_offset = frame.minute_offset;
                }
                else {
                    //printf(INDENT_SPACES "$xxZDA sentence is not parsed\n");
                }
            } break;

            case MINMEA_INVALID: {
                //printf(INDENT_SPACES "$xxxxx sentence is not valid\n");
            } break;

        default: {
                //printf(INDENT_SPACES "$xxxxx sentence is not parsed\n");
        } break;
    }
}

double ATGM336H::getLatitude(){
    updateStack();
    return latX;
}

double ATGM336H::getLongitude(){
    updateStack();
    return longX;
}

double ATGM336H::getAltitude(){
    //updateStack();
    return 0;
}

double ATGM336H::getSpeed(){
    updateStack();
    return speedX;
}

std::vector<int> ATGM336H::getTimeVector(){
    std::vector<int> timeVx{hrs,mins,secs,day,month,year,hour_offset,min_offset};
    return timeVx;
}