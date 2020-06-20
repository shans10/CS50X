#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check if program is run with only 1 argument if not then terminate with exit code 1 and remind user of correct usage
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }

    // Open file give as arguement by the user in read only mode
    FILE *in = fopen(argv[1], "r");

    // Create an array to store 512 bytes of data at once
    BYTE buffer[512];

    // Image count initially set to 0
    int images = 0;

    // Allocating size for output filename
    char fname[8];

    // Output file point initialized to Null
    FILE *out = NULL;

    // Infinite loop to read input file until all data is read and file end is reached
    while (1)
    {
        // Read 512 bytes of data and store it in buffer array
        int read = fread(buffer, sizeof(BYTE), 512, in);

        // Break out of loop if no data is read in current iteration and file end is reached
        if (read == 0 && feof(in))
        {
            break;
        }

        // Checking for jpeg headers
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If a file is opened previously and new jpeg is found then close previous file
            if (out != NULL)
            {
                fclose(out);
                images++;
            }

            // Set filename based on image count
            sprintf(fname, "%0.3i.jpg", images);
            // Open new file if new jpeg header found
            out = fopen(fname, "w");
        }

        // If output file is opened write the data stored in buffer array into the opened file
        if (out != NULL)
        {
            fwrite(buffer, sizeof(BYTE), 512, out);
        }
    }

    // Close last output file
    fclose(in);

    //Close input file
    fclose(out);
}
