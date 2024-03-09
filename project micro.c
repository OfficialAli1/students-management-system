#include <stdio.h>
#include <string.h> //function for strings
#include <ctype.h>  //additional functions for strings ex is alpha.
void removeLineFromFile(char *filename, int lineToRemove) {  // a function used to remove data from file.takes from main the file name and the line to be removed
    FILE *file = fopen(filename, "r");
    FILE *tempFile = fopen("temp.txt", "w"); // Temporary file

    if (file == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char buffer[1024];   // To create a character array with size 1024 "1KB"
    int line = 0;

    // Copy lines from original file to temporary file except the one to be removed
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        line++;
        if (line != lineToRemove)
        {
            fputs(buffer, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Remove original file and rename the temporary file
    remove(filename);
    rename("temp.txt", filename);
}
void printLineFromFile(char *filename, int lineNumber) {  // Function to print line from file used to retrieve the students data. takes from main the file name and the line to be printed
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    char buffer[1024];
    int currentLine = 0;
    // Find the desired line and print it
    while (fgets(buffer, sizeof(buffer), file) != NULL) {   //a while loop that contains a pointer incremented to read each line in the file if its found the data will be placed in the buffer if not = NULL
        currentLine++;
        if (currentLine == lineNumber) {
            printf("%s\n",buffer);
            break;
        }
    }

    fclose(file);
}
void printNUMFromFile(char *filename, int lineNumber) {  // To print the GPA
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    char buffer[1024];
    int currentLine = 0;
    // Find the desired line and print it
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        currentLine++;
        if (currentLine == lineNumber) {
            printf("%s\n",buffer);
            break;
        }
    }

    fclose(file);
}
void editLineInFile(char *filename, int lineNumber,int *newContent) { // Used for the edit case to change the data in the in the given line of the chosen file
    FILE *file = fopen(filename, "r");
    FILE *tempFile = fopen("temp.txt", "w"); // Temporary file
    if (file == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        return;
    }
    char buffer[1024];
    int currentLine = 0;
    // Copy lines from original file to temporary file, editing the desired line
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        currentLine++;
        if (currentLine == lineNumber) {
            // Replace the line with new content
            fprintf(tempFile, "%d\n", newContent);
        } else {
            // Copy unchanged line
            fputs(buffer, tempFile);
        }
    }
    fclose(file);
    fclose(tempFile);
    // Remove original file and rename the temporary file
    remove(filename);
    rename("temp.txt", filename);
}
void editNUMInFile(const char *filename, int lineNumber, double newContent) {
    FILE *file = fopen(filename, "r");
    FILE *tempFile = fopen("temp.txt", "w"); // Temporary file

    if (file == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char buffer[1024];
    int currentLine = 0;

    // Copy lines from original file to temporary file, editing the desired line
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        currentLine++;
        if (currentLine == lineNumber) {
            // Replace the line with new content
            fprintf(tempFile, "%lf\n", newContent); // Assuming two decimal places for the double number
        } else {
            // Copy unchanged line
            fputs(buffer, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Remove original file and rename the temporary file
    remove(filename);
    rename("temp.txt", filename);
}

struct student
{
    char name[100];
    int ID;
    char gender[6];
    int acdemic_year;
    double GPA;
};

int main()
{
    struct student newStudent;   // Struct used to enter all of the students data.
    int choice;
    FILE* namefile;
    FILE* file = fopen("IDs.txt", "r");
    // All the files needed to extract the project.
    FILE* genderfile;
    FILE* academicfile;
    FILE* GPAfile;
    FILE* tempFile;
    FILE* IDfile;
    char buffer[1024];
    char tempFilename[100];
    int lineNumber;
    puts("please enter one of the following numbers\n1 for adding a new student\n2 for removing a student\n3 for retrieving a student's data\n4 for updating student's data\n");
    scanf("%d",&choice);
    switch (choice)
    {
        case 1:
        {
            int alpha; // Indicator for alphabets
            int spaceCounter=0;    // Counter for space.
            puts("please enter the student's name (first and last name only)");
            while(1)
            {
                spaceCounter=0;
                gets(newStudent.name);
                for(int i=0;i<strlen(newStudent.name);i++)
                {
                    if(isalpha(newStudent.name[i])==0)   // Function isalpha used to alphabetical characters only. Its used in a for loop to make sure no special characters are used.
                    {
                        if(newStudent.name[i]==' ')
                        {
                            spaceCounter++;
                        }
                        else
                        {
                            printf("name should not include special characters or numbers\n");
                            alpha=0;
                            spaceCounter=0;
                            break;
                        }
                    }
                    else
                    {
                        alpha=1;
                    }
                }
                if(spaceCounter!=1)
                {
                    printf("you must enter the FISRT and LAST name ONLY\n");
                }
                if(spaceCounter==1 && alpha==1)   //If user entered one space only and no special character then the while loop terminates.
                {
                    break;
                }
            }
            FILE* namefile=fopen("names.txt","a");  //To open the file named "names".
            if(namefile==NULL)
            {
                printf("error opening the file\n");   //Indicates if an error occurred while opening the file
            }
            fprintf(namefile,"\n%s",newStudent.name); //To print the successful name in the file of names.
            fclose(namefile);                         //To close the opened file "names".
            printf("name is added successfully\n");
/*--------------------------------------------------------------------------------------*/
            int newID=0;  // Indication that the ID is 7 digits only.
            int idExists = 0; //Indication that the user entered an existing ID.
            FILE* file = fopen("IDs.txt", "r");
            if (file == NULL)
            {
                printf("Error opening file.\n");
                //return 1;
            }
            printf("please enter student's ID\n");
            scanf("%d",&newStudent.ID);
            getchar();   //function to avoid having errors because of mixing between scanf and gets.
            int existingId;
            do
            {
                if(newStudent.ID>=1000000 && newStudent.ID<=9999999) // If statement to check that the ID is only 7 digits
                {
                    newID=1;
                }
                else
                {
                printf("ID should be 7 numbers\n");
                scanf("%d",&newStudent.ID);
                newID=0;
            }
            }while(newID==0);
            while (fscanf(file, "%d", &existingId) == 1)   //scan from the file of IDs the id and put it in a variable called existingID.
            {
                if (existingId == newStudent.ID)      //If the scanned ID from the user equaled the already existed in the file.
                {
                    idExists = 1;
                    break;
                }
            }
            while(idExists==1)
            {
                printf("ID already exists. ID must be unique\n");
                scanf("%d",&newStudent.ID);
                file = fopen("IDs.txt", "r");
                while (fscanf(file, "%d", &existingId) == 1)
                {
                    if (existingId == newStudent.ID)
                    {
                        idExists = 1;
                        fclose(file);
                        break;
                    }
                    else
                    {
                        idExists=0;
                    }
                }
                if(idExists==0)
                {
                    fclose(file);
                    break;
                }
            }
            file = fopen("IDs.txt", "a");
            if (file == NULL)
            {
                printf("Error opening file.\n");
                return 1;
            }
            fprintf(file,"\n%d",newStudent.ID); //add the new ID to the system (file).
            fclose(file);
            IDfile=fopen("dupID.txt","a");
            fprintf(IDfile,"\n%d",newStudent.ID);
            fclose(IDfile);
            printf("ID added successfully.\n");
/*--------------------------------------------------------------------------------------*/
            printf("please enter the gender: M/m for male or F/f for female\n");
            while(1) //while loop that keeps iterating until a break is ordered.
            {
                scanf("%s",&newStudent.gender);
                if(strlen(newStudent.gender)==1&&(newStudent.gender[0] == 'M' || newStudent.gender[0] == 'm' || newStudent.gender[0] == 'F' || newStudent.gender[0] == 'f'))   //check the length of the characters the user entered and if it satisfies the condition.
                {
                    break; //break from the while when the user enters the right gender.
                }
                else
                {
                    printf("invalid input. please try again\n");
                }
            }
            FILE* genderfile=fopen("gender.txt","a");
            if(genderfile==NULL)
            {
                printf("error opening file\n");
            }
            fprintf(genderfile,"\n%s",newStudent.gender);    //adds the gender to the system
            fclose(genderfile);
            printf("gender is added successfully\n");
/*--------------------------------------------------------------------------------------*/
            getchar();
            printf("please enter the student's academic year\n");
            while(1)
            {
                scanf("%d",&newStudent.acdemic_year);
                if(newStudent.acdemic_year<1 || newStudent.acdemic_year>5)
                {
                    printf("the academic year should be between 1 and 5 years\n");
                }
                else
                {
                    break;
                }
            }
            FILE* academicfile=fopen("academic year.txt","a");
            if(genderfile==NULL)
            {
                printf("error opening file\n");
            }
            fprintf(academicfile,"\n%d",newStudent.acdemic_year); //adds the academic year to the system
            fclose(academicfile);
            printf("academic year was added successfully\n");
/*--------------------------------------------------------------------------------------*/
            getchar();
            printf("please enter the student's GPA\n");
            while(1)
            {
                scanf("%lf",&newStudent.GPA);
                if(newStudent.GPA<0 || newStudent.GPA>4)
                {
                    printf("the GPA should be a decimal number between 0 and 4\n");
                }
                else
                {
                    break;
                }
            }
            FILE* GPAfile=fopen("GPA.txt","a");
            if(genderfile==NULL)
            {
                printf("error opening file\n");
            }
            fprintf(GPAfile,"\n%lf",newStudent.GPA);  //adds the GPA to the system.
            fclose(GPAfile);
            printf("student was added successfully\n");
            break;
/*--------------------------------------------------------------------------------------*/
        }
        case 2:
        {
            int existingId;
            int idExists;
            printf("please enter the student's ID you wish to remove\n");
            while(1)
            {
                scanf("%d",&newStudent.ID);
                while(1)
                {
                    if(newStudent.ID<1000000 || newStudent.ID>9999999)
                    {
                        printf("invalid. ID should be 7 digits\n");
                        scanf("%d",&newStudent.ID);
                    }
                    else
                    {
                        break;
                    }
                }
                IDfile = fopen("dupID.txt", "r");
                if (IDfile == NULL)
                {
                    printf("Error opening file.\n");
                    return 1;
                }
                while(fscanf(IDfile, "%d", &existingId) == 1)
                {
                    lineNumber++;    //count the lines in the file.
                    if(existingId==newStudent.ID)
                    {
                        idExists=1;    //if the ID existed break from the while (file)
                        break;
                    }
                    else
                    {

                        idExists=0;
                    }
                }
                fclose(IDfile);
                if(idExists)
                {
                    removeLineFromFile("names.txt", lineNumber); // remove the counted line from the file "names" using removeLineFromFile.
                    removeLineFromFile("gender.txt",lineNumber);
                    removeLineFromFile("GPA.txt",lineNumber);
                    removeLineFromFile("academic year.txt",lineNumber);
                    removeLineFromFile("dupID.txt",lineNumber);
                    printf("students data is removed\n");
                    break;
                }
                else
                {
                    printf("ID is not found\n");
                    lineNumber=0;
                }
            }
            break;

        }
        case 3:
        {
            int option;
            int existingId;
            int idExists;
            int line=0;
            printf("please enter one of the 2 options:\n1 to search for student's data by name.\n2 to search for student's data by ID\n");
            scanf("%d",&option);
            if(option==1) //check by name.
            {
                getchar();
                puts("please enter the student's name");
                gets(newStudent.name);
                printf("student's data is retrieved\n");
            }
            else if(option==2)  //check by ID.
            {
                getchar();
                printf("please enter the student's ID\n");
                while(1)
                {
                    scanf("%d",&newStudent.ID);
                    while(1)
                    {
                        if(newStudent.ID<1000000 || newStudent.ID>9999999)
                        {
                            printf("invalid. ID should be 7 digits\n");
                            scanf("%d",&newStudent.ID);
                        }
                        else
                        {
                            break; //if the ID is a 7 digit then terminates the first loop.
                        }
                    }
                    IDfile = fopen("dupID.txt", "r");
                    if (IDfile == NULL)
                    {
                        printf("Error opening file.\n");
                        return 1;
                    }
                    while(fscanf(IDfile, "%d", &existingId) == 1)   //keep taking IDs from the file until the lines filled in the file is finished.
                    {
                        line++;   //counts the lines in the file until the the ID the user entered is found in the system.
                        if(existingId==newStudent.ID)
                        {
                            idExists=1;
                            break;
                        }
                        else
                        {
                            idExists=0;
                        }
                    }
                    fclose(IDfile);
                    if(idExists)
                    {
                       printf("student's data is retrieved\n");
                       printf("name: ");
                       printLineFromFile("names.txt",line);  //print the counted line from the file to the screen using printLineFromFile.
                       printf("gender: ");
                       printLineFromFile("gender.txt",line);
                       printf("academic year: ");
                       printLineFromFile("academic year.txt",line);
                       printf("GPA: ");
                       printNUMFromFile("GPA.txt",line);
                       break;
                    }
                    else
                    {
                        printf("student not found\n");
                        line=0;
                    }
                }
            }
            else
            {
                printf("invalid input\n");
            }
            break;
        }
        case 4:
        {
            int option;
            int existingId;
            int idExists;
            int line=0;
            printf("please enter the student's ID\n");
            while(1)
            {
                scanf("%d",&newStudent.ID);
                while(1)
                {
                    if(newStudent.ID<1000000 || newStudent.ID>9999999)
                    {
                        printf("invalid. ID should be 7 digits\n");
                        scanf("%d",&newStudent.ID);
                    }
                    else
                    {
                        break;
                    }
                }
                IDfile = fopen("dupID.txt", "r");
                if (IDfile == NULL)
                {
                    printf("Error opening file.\n");
                    return 1;
                }
                while(fscanf(IDfile, "%d", &existingId) == 1)
                {
                    line++;
                    if(existingId==newStudent.ID)
                    {
                        idExists=1;
                        break;
                    }
                    else
                    {
                        idExists=0;
                        line=0;
                    }
                }
                fclose(IDfile);
                if(idExists)
                {
                    while(1)
                    {
                        printf("please select one of the following options:\n1 for updating the academic year\n2 for updating the GPA\n3 to exit\n");
                        scanf("%d",&option);
                        if(option==1)
                        {
                            printf("please enter the new academic year\n");
                            scanf("%d",&newStudent.acdemic_year);
                            editLineInFile("academic year.txt",line,newStudent.acdemic_year); // edits a line in the file by the user's input using the function editLineFromFile.
                            printf("student's data is updated\n");
                        }
                        else if(option==2)
                        {
                            printf("please enter the new GPA\n");
                            scanf("%lf",&newStudent.GPA);
                            editNUMInFile("GPA.txt",line,newStudent.GPA);
                            printf("student's data is updated\n");
                        }
                        else if(option==3)
                        {
                            printf("exiting...\n");
                            break;
                        }
                        else
                        {
                            printf("invalid input\n");
                        }
                    }
                }
                else
                {
                    printf("student not found\n");
                    line=0;
                }
                break;
            }
            break;
        }
    }
}

