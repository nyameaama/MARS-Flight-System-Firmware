/*MIT License

Copyright (c) 2023 limitless Aeronautics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#ifndef SD_CARD
#define SD_CARD

#include <string.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include "driver/sdmmc_host.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"

#define MOUNT_POINT "/sdcard"

class SD_FILESYSTEM
{
  public:
    //____________________________________________________________
    /* Initializes SD File System
    ===========================================================================
    |    void
    ===========================================================================
    */
    static void SDFS_initialize();

    //____________________________________________________________
    /* Deinitializes SD File System
    ===========================================================================
    |    void
    ===========================================================================
    */
    static void SDFS_deinitialize();

    //____________________________________________________________
    /* Writes data to file path
    ===========================================================================
    |    void
    ===========================================================================
    */
    static esp_err_t SDFS_write_file(const char* path, char* data);

    //____________________________________________________________
    /* Reads data from file path
    ===========================================================================
    |    void
    ===========================================================================
    */
    static esp_err_t SDFS_read_file(const char* path);

    //____________________________________________________________
    /* Creates directory on SD File System
    ===========================================================================
    |    void
    ===========================================================================
    */
    static void create_directory(const char* path);
};

#endif  // SD_CARD