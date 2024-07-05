// !!! THIS EXAMPLE NEEDS FIXING [INSTALL NEEDED DATA ON SD CARD FIRST] !!!

// === INCLUDES === //
#include "SD_SPI_essential.h" // https://github.com/FunnytronLabs/SD-SPI-essential
#include "SD_csv_processor.h" // https://github.com/FunnytronLabs/SD-csv-processor


// === DEFINES === //
#define TEST_PATH "/TEST00/animals0.csv"

#define MAXIMUM_CELL_LENGTH 10 // maximum characters allowed per cell

#define SD_SPI_SCK  19 // FOR CUSTOM PIN ASSIGNMENT
#define SD_SPI_MISO 21 // FOR CUSTOM PIN ASSIGNMENT
#define SD_SPI_MOSI 18 // FOR CUSTOM PIN ASSIGNMENT
#define SD_SPI_CS   5  // FOR CUSTOM PIN ASSIGNMENT


// === GLOBALS === //
char testBuffer[] = "\nHigh there!... ";
SD_csv_processor fileElementProcessor(MAXIMUM_CELL_LENGTH);


// === MAIN FUNCTIONS === //
void setup() {
  Serial.begin(115200);
  while(!Serial) delay(10);

  Serial.println(__FILE__);
  Serial.println(__DATE__);

  Serial.println("### CELL ANALYSIS ###");
  delay(1000);

  SD_SPI_initialise(SD_SPI_SCK, SD_SPI_MISO, SD_SPI_MOSI, SD_SPI_CS);

  // !!! install test file on SD card here [TEST_PATH)] !!!

  File file = SD.open(TEST_PATH);
  if(!file){
    Serial.println("Failed to open file for reading");
  }
  else {
    Serial.println("Successfully opened file for reading");

    unsigned long current_file_position = 0;

    unsigned int data_length = fileElementProcessor.analyse_cell(file, current_file_position);
    Serial.printf("%d > ", data_length);
    for(int i=0;i<data_length;i++) Serial.print(fileElementProcessor.cell_buffer[i]);
    Serial.print(" : ");

    current_file_position += (++data_length);
    data_length = fileElementProcessor.analyse_cell(file, current_file_position);
    Serial.printf("%d > ", data_length);
    for(int i=0;i<data_length;i++) Serial.print(fileElementProcessor.cell_buffer[i]);
    Serial.println();

    current_file_position += (++data_length);
    data_length = fileElementProcessor.analyse_cell(file, current_file_position);
    Serial.printf("%d > ", data_length);
    if(fileElementProcessor.cell_buffer[0] == '\n') for(int i=1;i<data_length;i++) Serial.print(fileElementProcessor.cell_buffer[i]);
    else for(int i=0;i<data_length;i++) Serial.print(fileElementProcessor.cell_buffer[i]);
    Serial.print(" : ");

    current_file_position += (++data_length);
    data_length = fileElementProcessor.analyse_cell(file, current_file_position);
    Serial.printf("%d > ", data_length);
    for(int i=0;i<data_length;i++) Serial.print(fileElementProcessor.cell_buffer[i]);
    Serial.println();

    ////////////////////////////////////////////////////////////////////////////////////
    current_file_position += (++data_length);
    data_length = fileElementProcessor.analyse_cell(file, current_file_position);
    Serial.printf("%d > ", data_length);
    if(fileElementProcessor.cell_buffer[0] == '\n') for(int i=1;i<data_length;i++) Serial.print(fileElementProcessor.cell_buffer[i]);
    else for(int i=0;i<data_length;i++) Serial.print(fileElementProcessor.cell_buffer[i]);
    Serial.print(" : ");

    current_file_position += (++data_length);
    data_length = fileElementProcessor.analyse_cell(file, current_file_position);
    Serial.printf("%d > ", data_length);
    for(int i=0;i<data_length;i++) Serial.print(fileElementProcessor.cell_buffer[i]);
    Serial.println();

    ////////////////////////////////////////////////////////////////////////////////////
    current_file_position += (++data_length);
    data_length = fileElementProcessor.analyse_cell(file, current_file_position);
    Serial.printf("%d > ", data_length);
    if(fileElementProcessor.cell_buffer[0] == '\n') for(int i=1;i<data_length;i++) Serial.print(fileElementProcessor.cell_buffer[i]);
    else for(int i=0;i<data_length;i++) Serial.print(fileElementProcessor.cell_buffer[i]);
    Serial.print(" : ");

    current_file_position += (++data_length);
    data_length = fileElementProcessor.analyse_cell(file, current_file_position);
    Serial.printf("%d > ", data_length);
    for(int i=0;i<data_length;i++) Serial.print(fileElementProcessor.cell_buffer[i]);
    Serial.println();

    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    Serial.println(testBuffer);
    Serial.println(testBuffer);
    Serial.println(testBuffer);

    Serial.print("\n");

    unsigned int new_data_length = 0;

    Serial.printf("new data length = %d\n", new_data_length);

    new_data_length = fileElementProcessor.remove_character('\n',testBuffer,16);
    Serial.printf("new data length after removing newLine = %d\n", new_data_length);
    Serial.print(testBuffer);Serial.print("X\n");
    Serial.print(testBuffer);Serial.print("X\n");
    Serial.print(testBuffer);Serial.print("X\n");

    Serial.print("\n");

    Serial.println("--- GOT HERE ---");
    
    new_data_length = fileElementProcessor.remove_character(' ',testBuffer,new_data_length);
    Serial.printf("new data length after removing spaceBar = %d\n", new_data_length);
    for(int i=0;i<new_data_length;i++) Serial.print(testBuffer[i]);Serial.print("X\n");
    for(int i=0;i<new_data_length;i++) Serial.print(testBuffer[i]);Serial.print("X\n");
    for(int i=0;i<new_data_length;i++) Serial.print(testBuffer[i]);Serial.print("X\n");

    Serial.print("\n");

    new_data_length = fileElementProcessor.remove_character('.',testBuffer,new_data_length);
    Serial.printf("new data length after removing fullStop = %d\n", new_data_length);
    for(int i=0;i<new_data_length;i++) Serial.print(testBuffer[i]);Serial.print("X\n");
    for(int i=0;i<new_data_length;i++) Serial.print(testBuffer[i]);Serial.print("X\n");
    for(int i=0;i<new_data_length;i++) Serial.print(testBuffer[i]);Serial.print("X\n");

    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////

    Serial.println("*** COORDINATE (1,1): ");
    unsigned long position_in_file = fileElementProcessor.seek_cell(file, 1, 1);
    data_length = fileElementProcessor.analyse_cell(file, position_in_file);
    Serial.printf("%d > ", data_length);
    if(fileElementProcessor.cell_buffer[0] == '\n') for(int i=1;i<data_length;i++) Serial.print(fileElementProcessor.cell_buffer[i]);
    else for(int i=0;i<data_length;i++) Serial.print(fileElementProcessor.cell_buffer[i]);
    Serial.print("\n");

    Serial.println("*** COORDINATE (0,1): ");
    position_in_file = fileElementProcessor.seek_cell(file, 0, 1);
    data_length = fileElementProcessor.analyse_cell(file, position_in_file);
    Serial.printf("%d > ", data_length);
    if(fileElementProcessor.cell_buffer[0] == '\n') for(int i=1;i<data_length;i++) Serial.print(fileElementProcessor.cell_buffer[i]);
    else for(int i=0;i<data_length;i++) Serial.print(fileElementProcessor.cell_buffer[i]);
    Serial.print("\n");

    Serial.println("*** COORDINATE (0,0): ");
    position_in_file = fileElementProcessor.seek_cell(file, 0, 0);
    data_length = fileElementProcessor.analyse_cell(file, position_in_file);
    Serial.printf("%d > ", data_length);
    if(fileElementProcessor.cell_buffer[0] == '\n') for(int i=1;i<data_length;i++) Serial.print(fileElementProcessor.cell_buffer[i]);
    else for(int i=0;i<data_length;i++) Serial.print(fileElementProcessor.cell_buffer[i]);
    Serial.print("\n");

    Serial.println("*** COORDINATE (1,0): ");
    position_in_file = fileElementProcessor.seek_cell(file, 1, 0);
    data_length = fileElementProcessor.analyse_cell(file, position_in_file);
    Serial.printf("%d > ", data_length);
    if(fileElementProcessor.cell_buffer[0] == '\n') for(int i=1;i<data_length;i++) Serial.print(fileElementProcessor.cell_buffer[i]);
    else for(int i=0;i<data_length;i++) Serial.print(fileElementProcessor.cell_buffer[i]);
    Serial.print("\n");

    Serial.println("*** COORDINATE (3,0): ");
    position_in_file = fileElementProcessor.seek_cell(file, 3, 0);
    data_length = fileElementProcessor.analyse_cell(file, position_in_file);
    Serial.printf("%d > ", data_length);
    if(fileElementProcessor.cell_buffer[0] == '\n') for(int i=1;i<data_length;i++) Serial.print(fileElementProcessor.cell_buffer[i]);
    else for(int i=0;i<data_length;i++) Serial.print(fileElementProcessor.cell_buffer[i]);
    Serial.print("\n");

    Serial.println("*** COORDINATE (2,1): ");
    position_in_file = fileElementProcessor.seek_cell(file, 2, 1);
    data_length = fileElementProcessor.analyse_cell(file, position_in_file);
    Serial.printf("%d > ", data_length);
    if(fileElementProcessor.cell_buffer[0] == '\n') for(int i=1;i<data_length;i++) Serial.print(fileElementProcessor.cell_buffer[i]);
    else for(int i=0;i<data_length;i++) Serial.print(fileElementProcessor.cell_buffer[i]);
    Serial.print("\n");
    
  }

}

void loop() {
  delay(100);
}
