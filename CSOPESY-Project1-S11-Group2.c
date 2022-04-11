//Francheska A. Roque
//Francesca Yzabel A. Mendoza
//CSOPESY-S11

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#include <windows.h>
#define row 150 
#define col 25 
#define SIZE 25


// This function parses the user input and stores the parsed user input to string_command and string_param
// The cmd_id corresponds to each command
int parse_input(char *string_input, char *string_command, char *string_param, int *cmd_id) {
  
  // Declare variables for parsing the string input
  char delimiter[] = " ";
  char *rem, *param, *temp;

  // parse the input
  if(strchr(string_input, ' ') != NULL){
    int length = strlen(string_input);
    char *input_copy = (char*) calloc(length + 1, sizeof(char));
    strncpy(input_copy, string_input, length);
    temp = strtok_r (input_copy, delimiter, &param);

    // Assign the parsed input to string_command and string_param
    strcpy(string_command, temp);
    strcpy(string_param, param);
     
    free(input_copy);
  } 
  else 
  	strcpy(string_command, string_input);
  
	  if (!strcmp(string_command, "say")) *cmd_id = 1;
	  else if (!strcmp(string_command, "cls")) *cmd_id = 2;
	  else if (!strcmp(string_command, "dir")) *cmd_id = 3;
	  else if (!strcmp(string_command, "pwd")) *cmd_id = 4;
	  else if (!strcmp(string_command, "time")) *cmd_id = 5;
	  else if (!strcmp(string_command, "title")) *cmd_id = 6;
	  else if (!strcmp(string_command, "color")) *cmd_id = 7;
	  else if (!strcmp(string_command, "mkfldr")) *cmd_id = 8;
	  else if (!strcmp(string_command, "find")) *cmd_id = 9;
	  else if (!strcmp(string_command, "open")) *cmd_id = 10;
	  else if (!strcmp(string_command, "copy")) *cmd_id = 11;
	  else if (!strcmp(string_command, "rename")) *cmd_id = 12;
	  else if (!strcmp(string_command, "delete")) *cmd_id = 13; 
	  else if (!strcmp(string_command, "sort")) *cmd_id = 14; 
	  else if (!strcmp(string_command, "marquee")) *cmd_id = 15;
	  else if (!strcmp(string_command, "exit")) *cmd_id = 16;
	  else *cmd_id = -1;
	
	  return 1;
}

// Compare Name to Other Name with File Extension
int cmpfn(char *to_compare,char *fname_extension){
  if(!strcmp(fname_extension, ".") || !strcmp(fname_extension, "..")) 
  return 1;
  char *file_name_copy = strcpy(file_name_copy, fname_extension);
  char *result = strtok(file_name_copy, ".");

  return strcmp(to_compare, result);
}

//function for the commands input by the user
void list_command(int cmd_id, char *string_input) {
  // Declare variable for current working directory
  char cwd[PATH_MAX];

  switch(cmd_id){
    
    // Say command - display the string input next to the say command
	case 1: {
      if(!strlen(string_input)) 
      	printf("Say something...\n\n");
      else 
	  	printf("%s\n\n", string_input);

      break;
    }
	
	// clear screen command - will clear the entire screen
	case 2: {
      system("cls");
      break;
    }
    
    // Print directory
    case 3: {

      struct dirent *currentD;
      struct stat size;

      DIR *dr = opendir(".");

      if (dr == NULL){
        printf("Directory cannot be opened." );
      }

      while ((currentD = readdir(dr)) != NULL){
        stat(currentD->d_name, &size);
        printf("Filename: %s\n", currentD->d_name);
        printf("File size: %d Bytes\n", size.st_size);
        printf("Created on: %s\n\n", ctime(&size.st_mtime));
      }
      closedir(dr);

      break;
    }
    
    // Print current directory path
    case 4: {
      if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf(cwd);
        printf("\n\n");
      } else {
        perror("getcwd() error");
      }

      break;
    }

    // Print current time
    case 5: {
      time_t origTime;
      struct tm * timeInfo;
      time ( &origTime );
      timeInfo = localtime ( &origTime );
      printf (asctime (timeInfo) );
      printf("\n");

      break;
    }
    
	// Change window title
	case 6: {
      HANDLE handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
      SetConsoleTitle(string_input);
      while(1){
      	printf("Title changed successfully.\n\n");
      	break;
	  }
      break;
    }
    
     /* Change Background Color and Foreground color
      0 = Black 1 = Blue 2 = Green  4 = Red 5 = Purple 6 = Yellow 7 = White
      8 = Gray */
    case 7: {
    char str[10][10]; 
    int i, j = 0, ind = 0;

    for (i = 0; i <= (strlen(string_input)); i++) {
        if (string_input[i] == ' ' || string_input[i] == '\0') {
            str[ind][j] = '\0';
            ind++; 
            j = 0; 
        }
        else {
            str[ind][j] = string_input[i];
            j++;
        }
    }
    
    char color[15] = "color ";
    color[6] = '\0';
    color[7] = '\0';
    
      if(!strcmp(str[0], "black"))  color[6] = '0';
      else if(!strcmp(str[0], "blue"))  color[6] = '1';
      else if(!strcmp(str[0], "green")) color[6] = '2';
      else if(!strcmp(str[0], "red"))  color[6] = '4';
      else if(!strcmp(str[0], "purple"))  color[6] = '5';
      else if(!strcmp(str[0], "yellow"))  color[6] = '6';
      else if(!strcmp(str[0], "white"))  color[6] = '7';
      else if(!strcmp(str[0], "gray")) color[6] = '8';
 	 fflush(stdin);
      if(!strcmp(str[1], "black")) color[7] = '0';
      else if(!strcmp(str[1], "blue"))  color[7] = '1';
      else if(!strcmp(str[1], "green"))  color[7] = '2';
      else if(!strcmp(str[1], "red"))  color[7] = '4';
      else if(!strcmp(str[1], "purple"))  color[7] = '5';
      else if(!strcmp(str[1], "yellow"))  color[7] = '6';
      else if(!strcmp(str[1], "white"))  color[7] = '7';
      else if(!strcmp(str[1], "gray")) color[7] = '8';
      system(color);
      break;
    }
    
    // Make folder function - make a folder in the current directory
    case 8: {

    int checker;
    checker = mkdir(string_input);
    if (!checker)
        printf("Folder created\n\n");

    else
    {
        printf("Unable to create folder!\n\n");
        exit(1);  
    } 
		break;
    }
    
    //will be used for case 9: Find command
    long int findSize(char file_name[])
{
    // open the file in read mode
    FILE* fp = fopen(file_name, "r");
  
    // check if the file exists or not in the current directory
    if (fp == NULL) {
        printf("File not found in the directory!\n\n");
        return -1;
    }
  
    fseek(fp, 0L, SEEK_END);
  
    // calculate the size of the file
    long int res = ftell(fp);
    fclose(fp);
  
    return res;
}
    // Find a file in the current directory
    case 9: {
		struct dirent *currDir;
		struct stat acc;
		
		DIR *dr = opendir(".");
		
		
		char temp[64];
		char fname[64];
		strcpy(temp, string_input);
		sprintf(fname, "%s.txt", temp);
    	long int res = findSize(fname);
    	while ((currDir = readdir(dr)) != NULL){
		
    	if (res != -1){
    		stat(currDir->d_name, &acc);
			printf("File found! \n");
			printf("Filename: %s\n", fname);
			printf("Size of the file is %ld bytes \n", res);
        	printf("Created on: %s\n\n", ctime(&acc.st_mtime));
        	break;
		}
		else{
			break;
		}
		
		closedir(dr);	
    }
		break;
	}

    // Open the file in the current directory
	case 10: {
    FILE *f1;
	char temp[64];
	char fname[64];
	strcpy(temp, string_input);
	sprintf(fname, "%s.txt", temp);
	f1 = fopen(fname, "r");
	char show[150];
	if (f1 == NULL){
		printf("File can't be opened: File does not exist\n\n");
		break;
	}
	else{
		while(!feof(f1)) {
				fgets(show, 150, f1);
				puts(show);
				printf("\n\n");
		}
	}
	
	fclose(f1);
	break;
	}
	
	// Copy the content of the txt file to another txt file
	case 11: {
    char str[10][10]; 
    int i, j = 0, ind = 0;

    for (i = 0; i <= (strlen(string_input)); i++) {
        if (string_input[i] == ' ' || string_input[i] == '\0') {
            str[ind][j] = '\0';
            ind++; 
            j = 0; 
        }
        else {
            str[ind][j] = string_input[i];
            j++;
        }
    }
    
    char tempString[64];
	char fname[64];
	strcpy(tempString, str[0]);
	sprintf(fname, "%s.txt", tempString);

	char ch, source_file[20], target_file[20];
    FILE *source, *destination;
   source = fopen(fname, "r");

   if (source == NULL)
   {
      printf("Source file is empty!\n\n");
     
   } else {
   	  printf("File copied successfully.\n\n");
   	  strcpy(tempString, str[1]);
      sprintf(fname, "%s.txt", tempString);

    destination = fopen(fname, "w");
   }

   while ((ch = fgetc(source)) != EOF)
      fputc(ch, destination);


   fclose(source);
   fclose(destination);
		break;
	}
    
    // Rename a txt file chosen by the user inside the current directory
	case 12: {
    char str[10][10]; 
    int i, j = 0, ind = 0;

    for (i = 0; i <= (strlen(string_input)); i++) {
        if (string_input[i] == ' ' || string_input[i] == '\0') {
            str[ind][j] = '\0';
            ind++; 
            j = 0; 
        }
        else {
            str[ind][j] = string_input[i];
            j++;
        }
    }
    
    char tempString[64];
	char oldname[64];
	char newname[64];
	strcpy(tempString, str[0]);
	sprintf(oldname, "%s.txt", tempString);
    strcpy(tempString, str[1]);
	sprintf(newname, "%s.txt", tempString);
        
    int check;
   check = rename(oldname, newname);
	
   if(check == 0) {
      printf("File renamed successfully!\n\n");
   } else {
      printf("File does not exist, can't be renamed!\n\n");
   }

      break;
    }
    
	// Delete a txt file inside the current directory
	case 13: {
		char tempString[64];
		char fname[64];
		strcpy(tempString, string_input);
		sprintf(fname, "%s.txt", tempString);
		int del = remove(fname);
   if (!del)
      printf("The file is Deleted successfully\n\n");
   else
      printf("The file can't be deleted. It does not exist.\n\n");
		break;
	}
	
	// Sort the texts per line inside the txt file in the current directory
	case 14: {
	 char str[10][10]; 
    int i, j = 0, ind = 0;

    for (i = 0; i <= (strlen(string_input)); i++) {
        if (string_input[i] == ' ' || string_input[i] == '\0') {
            str[ind][j] = '\0';
            ind++; 
            j = 0; 
        }
        else {
            str[ind][j] = string_input[i];
            j++;
        }
    }
    
	int numLines = atoi(str[1]);
	numLines +=1;
		 		  
  	FILE *f1 = NULL; 
  
  
    char tempString[64];
	char filename[64];	
	strcpy(tempString, str[0]);
	sprintf(filename, "%s.txt", tempString);

   char arr[row][col];

  f1 = fopen(filename, "r");
  
  for(i = 0;fgets(arr[i], col, f1) && i != numLines; i++) {
  	 arr[i][strlen(arr[i]) - 1] = '\0';
  }
  
  int lines = i;
    
  for(i = 0; i < lines; ++i){
      printf(" %s\n", arr[i]);
  }
  printf("\n");
  fclose(f1);

  char temp[35];

    //Sort array using the Bubble Sort algorithm
  for(i=0; i<lines; i++){
    for(j=0; j<lines-1-i; j++){
      if(strcmp(arr[j], arr[j+1]) > 0){
        //swap array[j] and array[j+1]
        strcpy(temp, arr[j]);
        strcpy(arr[j], arr[j+1]);
        strcpy(arr[j+1], temp);
      }
    }
  }
  
  for(i = 0; i < lines; i++){
    printf(" %s\n", arr[i]);
  }
  
  printf("\n");
		 
  break;
	} 
	
char *marquee(char * string_input, int move, int i)
{
    char * str = malloc(sizeof(char) * (move + 1)); 
    char * ind = malloc(sizeof(char) * 256);
	char * temp = malloc(sizeof(char) * (strlen(string_input) + 1));
    int j = 0;
    strcpy(ind, string_input);
    
    for (j = 0; j< i; j++) {
    	temp[j] = ind[0];
        ind++;
        
        if (j == i - 1) {
        	 temp[j + 1] = '\0';
        	 strcat(ind, " ");
    		 strcat(ind, temp);
		}
	}
	 
    strncpy(str, ind, move);
    str[move] = '\0';
  
    return str;
}
	//marquee - the text will move from left to right
	case 15: {
   
    int i, j;
	 strcat(string_input, "                                                                                                           ");
    
       	 for (i = 0; i < strlen(string_input); i++)
        {
            printf("Wait for marquee to finish for next input :)");
			printf("%s\n", marquee(string_input, 100, i));
            Sleep(10);
			system("@cls||clear");
        } 
		break;
	}
	
	
	// Ends/Exits the program
	case 16:{
		printf("Emulator ended...");
	    exit(0);
	    break;
	}
	
	// Invalid command 
    case -1:{
    	printf("Invalid command. Please try again.\n\n");
		break;
	}
  }

  // Clear input buffer
  strcpy(string_input, "");
}

int main() {
  char string_input[120] = "";
  char string_command[120] = "";
  char string_param[120] = "";

  int nExecmd = 0;
  int cmd_id = 0;
  pthread_t pids[100];
  int pid_counter = 0;

  // Get user input until the exit command is executed
  while (1) { 
    printf("MyOS> ");

	
	char buffer[120];
	buffer[0] = '\0';
  	scanf("%[^\n]%*c", buffer);
  
 
 	if (strlen(buffer) == 0) {
 		 printf("error");
 		 char buffer[120];
		buffer[0] = '\0';
	    scanf("%[^\n]%*c", buffer);
	 }

  // If there is no input, return 0. Else return 1.
 	 if (strlen(buffer) != 0) {
	    strcpy(string_input, buffer);
	    
	    // Parse the input and execute the command
	   	nExecmd = parse_input(string_input, string_command, string_param, &cmd_id);
	    list_command(cmd_id, string_param);
  } 
  
  else {
	   printf("Please say a command! Exit and try again...");
	   break;
  }


  }
  
  return 0;
}
