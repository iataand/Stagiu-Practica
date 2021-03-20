// #include <dirent.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char entries[100][100];
int i = 0;

void writeEntry(char *date) // function to print the entry for a date
{
  char path[20];
  strcpy(path, "./entries/");
  strcat(path, date);

  FILE *fp = fopen(
      path,
      "r"); // opens the file and puts the fp pointer at the start of the file
  int ch; // will be used to iterate through the txt file character by character

  if (fp == NULL) // check if the file exists
    printf("Entry not found at specified date.\n");

  while ((ch = fgetc(fp)) != EOF) // executes until ch -> -1 which is equivalent
                                  // to reaching the end of file
    printf("%c", ch);
}

void addEntry(char *date, char *text) {
  FILE *fp = fopen(date, "w+"); // opens the file in read and write mode
  int ch = fgetc(fp);

  if (ch != -1) // check if there already is an entry at the specified date
    printf("Entry already found at the specified date. Would you like to "
           "modify it?\n");
  else {
    fputs(text, fp); // writes the given text to the file
    printf("Entry updated succesfully!\n");
  }
  fclose(fp);
}

char **findEntries() // this function prints all the dates that are
                     // elready in the journal
{
  int i = 0;
  char **files = (char **)malloc(10 * sizeof(char *));

  const char *path = "./entries"; // set the path to the entries folder
  struct dirent *entry;
  DIR *dir =
      opendir(path); // opens the directory that contains all the txt files

  while ((entry = readdir(dir)) != NULL) {
    files[i++] = malloc(strlen(entry->d_name));
    strcpy(files[i - 1], entry->d_name);
  }

  files[i] = "|";

  return files;
}

int main() {
  int optiune = -1;

  char **files = findEntries();

  printf("Aplicatie Jurnal\n----------------\n\n");

  while (1) {
    system("cls");
    printf("Va rog selectati o optiune de mai jos: \n\n");
    printf("(1) Afiseaza intrarile din jurnal.\n");
    printf("(2) Adauga o intrare in jurnal.\n");
    printf("(3) Cauta dupa un cuvant cheie.\n");
    printf("(4) Inchide aplicatia.\n");

    printf("\n#: ");
    scanf("%d", &optiune);
    system("cls");

    if (optiune == 1) {

      while (1) {
        int i = 2, j = 1, optiune2 = -1;
        system("cls");
        printf("\nSelectati una dintre optiunile de mai jos: \n\n");

        while (strcmp(files[i], "|") != 0)
          printf("(%d)%s\n", j++, files[i++]);

        printf("(%d)Reveniti la meniul principal.\n", j);
        i = 2;
        printf("\n#: ");
        scanf("%d", &optiune2);

        if (optiune2 <= j && optiune2 >= 1) {
          system("cls");
          writeEntry(files[optiune2 + 1]);
          printf("\n(1)Alegeti o noua data.           (2)Reveniti la meniul "
                 "principal.\n");

          int x;
          fflush(stdout);
          scanf("%d", &x);

          if (x == 2)
            break;

        } else
          printf("\nVa rog selectati o optiune valida.\n");
      }
    }
  }

  return 0;
}