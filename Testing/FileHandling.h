
#if !defined(FILEHANDLING_H)
#define FILEHANDLING_H
# include <stdio.h> 
# include <string.h> 

void writeIntoCsvFile(const char* fileName, const char* msg,const char *topicName)
{
    
    FILE* filePointer ;

    filePointer = fopen(fileName, "a");

   
    if (filePointer == NULL)
    {
        printf("PatientDetails.csv file failed to open.");
    }
    else
    {

        printf("The file is now opened.\n");

        if (strlen(msg) > 0)
        {
            fputs(topicName, filePointer);
            fputs(",", filePointer);
            fputs(msg, filePointer);
            fputs("\n", filePointer);
        }
        printf("File Closed");
        fclose(filePointer);
    }
}
#endif