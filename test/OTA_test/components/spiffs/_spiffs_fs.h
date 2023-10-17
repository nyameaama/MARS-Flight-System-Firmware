#ifndef _SPIFFS
#define _SPIFFS

class _SPIFFS_FILEX{
    public:
        void init_spiffs();

        void create_spiffs_file(char* filename);

        void rename_spiffs_file(char* filename);

        char* read_spiffs_file(char* filename);
};

#endif