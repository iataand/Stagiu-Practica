#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void writeEntry(char *date) //function to print the entry for a specific date given as argument
{
    FILE *fp = fopen(date, "r"); // opens the file and puts the fp pointer at the start of the file
    int ch;                      // will be used to iterate through the txt file character by character

    if (fp == NULL) //check if the file exists
        printf("Entry not found at specified date.\n");

    while ((ch = fgetc(fp)) != EOF) //executes until ch -> -1 which is equivalent to reaching the end of file
        printf("%c", ch);
}

void addEntry(char *date, char *text)
{
    FILE *fp = fopen(date, "w+"); //opens the file in read and write mode
    int ch = fgetc(fp);

    if (ch != -1) //check if there already is an entry at the specified date
        printf("Entry already found at the specified date. Would you like to modify it?\n");
    else
    {
        fputs(text, fp); //writes the given text to the file
        printf("Entry updated succesfully!\n");
    }
    fclose(fp);
}

int *listEntries() //this function prints all the dates that are elready in the journal
{
    const char *path = "./entries"; //set the path to the entries folder
    struct dirent *entry;
    int index = 0;
    DIR *dir = opendir(path); //opens the directory that contains all the txt files

    while ((entry = readdir(dir)) != NULL)
    {
        printf(entry->d_name);
    }

    closedir(dir);
}

int main()
{
    listEntries();
    return 0;
}