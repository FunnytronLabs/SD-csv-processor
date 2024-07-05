/*
  SD_csv_processor.h - C++ class for processing elements in csv files, on SD cards, using Arduino ESP32 platform.
  Created by Joseph Elias [Funnytron Labs], July 5, 2024.
  Released into the public domain.
*/

#include "SD_csv_processor.h"

SD_csv_processor::SD_csv_processor(unsigned int maximum_cell_length)
{
  this->maximum_cell_length = maximum_cell_length;

  if(cell_buffer = (char *) malloc(maximum_cell_length*sizeof(char))) memory_allocation_failure = false;
  else memory_allocation_failure = true;
}

unsigned int SD_csv_processor::analyse_cell(File SD_file, unsigned long file_position)
{
  char current_character;
  unsigned int data_length = 0;

  if(SD_file.seek(file_position)){
    while(SD_file.available()){
      current_character = SD_file.read();
      if(current_character != ','){
        if(data_length < maximum_cell_length && !memory_allocation_failure) cell_buffer[data_length] = current_character;
        data_length++;
      }
      else break;
    }

    return data_length;
  }
  else return 0;
}

unsigned long SD_csv_processor::seek_cell(File SD_file, unsigned int row, unsigned int column) // returns position in file
{
  char current_character;
  bool could_not_find_row = true;
  bool could_not_find_column = true;
  unsigned int data_length = 0;
  unsigned int current_row = 0;
  unsigned int current_column = 0;

  if(SD_file.seek(0)){ // start at the beginning of the file
    if(row > 0){
      while(SD_file.available()){
        current_character = SD_file.read();
        data_length++;
        if(current_character != '\n') continue;
        else {
          if(++current_row == row){
            could_not_find_row = false;
            break;
          }
        }
      }
      if(could_not_find_row) return 0;
    }

    if(column > 0){
      while(SD_file.available()){
        current_character = SD_file.read();
        data_length++;
        if(current_character != ',') continue;
        else {
          if(++current_column == column){
            could_not_find_column = false;
            break;
          }
        }
      }
      if(could_not_find_column) return 0;
    }

    return data_length;
  }
  else return 0;
}

unsigned int SD_csv_processor::remove_character(char trim_character, char *cell_pointer, unsigned int cell_length)
{
  unsigned long i = 0; // i.e. cell index
  
  while(i < cell_length){
    if(cell_pointer[i] == trim_character){
      for(unsigned long j=i; j<cell_length; j++) cell_pointer[j] = cell_pointer[j+1];
      cell_length--;
      continue;
    }
    i++;
  }

  return cell_length;
}
