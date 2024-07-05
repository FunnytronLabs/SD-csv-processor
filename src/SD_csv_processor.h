/*
  SD_csv_processor.h - C++ class for processing elements in csv files, on SD cards, using Arduino ESP32 platform.
  Created by Joseph Elias [Funnytron Labs], July 5, 2024.
  Released into the public domain.
*/

#ifndef SD_csv_processor_h
#define SD_csv_processor_h


// === INCLUDES === //
#include "FS.h"
#include "SD.h"
#include "SPI.h"


// === CLASS === //
class SD_csv_processor
{
  private:
    bool memory_allocation_failure;
    unsigned int maximum_cell_length;
    
  public:
    unsigned int cell_buffer_maximum_length;
    char *cell_buffer;

  public:
    SD_csv_processor(unsigned int maximum_cell_length);
    unsigned int analyse_cell(File SD_file, unsigned long file_position);
    unsigned long seek_cell(File SD_file, unsigned int row, unsigned int column); // returns position in file
    unsigned int remove_character(char trim_character, char *cell_pointer, unsigned int cell_length); // does not need SD card
};

#endif
