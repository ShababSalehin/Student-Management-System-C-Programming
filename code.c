#include <windows.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool IsRunning = true;
int NextStudentID;
int SetNextStudentId();
void Menu();
void AddNewStudent();
void ShowAllStudents();
int SearchStudents(StudentId);
void EditStudent(int StudentId);
void DeleteStudent();
void DeleteAllStudents();
bool AlreadyExists(char *GivenLine[30],char InfoType);
void ErrorAndRestart(char *error[100]);
void UserGuideline();
void AboutUs();

int main(){

    while(IsRunning == true){
        Menu();
        char *OptionStr[10];
        char Option;
        printf("\t\tEnter The Choice: ");
        scanf("%s",&OptionStr);
        Option = OptionStr[0];
        if(strlen(OptionStr) == 1){
            switch(Option){
                case '0':
                    ExitProject();
                    IsRunning = false;
                    break;
                case '1':
                    AddNewStudent();
                    break;
                case '2':
                    ShowAllStudents();
                    break;
                case '3':
                    system("cls");
                    printf("\n\t\t **** Search Students ****\n\n");
                    int StudentId;
                    printf("Enter The ID: ");
                    scanf("%d",&StudentId);
                    int IsFound = SearchStudents(StudentId);
                    if(IsFound <= 0){
                        printf("No Student Found For This ID: %d\n",StudentId);
                    }
                    GoBackOrExit();
                    break;
                case '4':
                    system("cls");
                    printf("\n\t\t **** Edit Students ****\n\n");

                    int StudentIdForEdit;

                    printf("Enter the ID of the student which one you wan to edit: ");
                    scanf("%d",&StudentIdForEdit);

                    int IsFoundEditSetudent = SearchStudents(StudentIdForEdit);
                    if(IsFoundEditSetudent > 0){
                        EditStudent(StudentIdForEdit);
                    }else{
                        printf("No Student Found For This ID: %d\n",StudentIdForEdit);
                    }

                    GoBackOrExit();
                    break;
                case '5':
                    DeleteStudent();
                    break;
                case '6':
                    DeleteAllStudents();
                    break;
                case '7':
                    system("cls");
                    break;
                case 'i':
                case 'I':
                    UserGuideline();
                    break;
                case 'a':
                case 'A':
                    AboutUs();
                    break;
                default:
                    printf("No option found!\n");
                    exit(0);
                    break;
            }
        }else{
            exit(0);
        }
    }
}
// end main function

int SetNextStudentId(){

    FILE *AllStudentsTextFile;
    int LineCount = 0;
    int LineLenght = 300;
    int TotalStudents = 0;
    char Line[LineLenght];
    AllStudentsTextFile = fopen("All-Students.txt","r");

    while(fgets(Line,LineLenght,AllStudentsTextFile)){
        LineCount++;
        if(LineCount == 5){
            TotalStudents++;
            LineCount = 0;
        }
    }
    TotalStudents++;
    return TotalStudents;
}


void Menu(){
    printf("\n\n\n\t***welcome to the student management system***\n\n");
    printf("\t\t\tMAIN MENU\n");
    printf("\t\t=======================\n");
    printf("\t\t[1] Add a new student.\n");
    printf("\t\t[2] Show all students.\n");
    printf("\t\t[3] Search students.\n");
    printf("\t\t[4] Edit a student.\n");
    printf("\t\t[5] Delete a student.\n");
    printf("\t\t[6] Delete all students.\n");
    printf("\t\t[7] Clear the window.\n");
    printf("\t\t[i] User Guideline.\n");
    printf("\t\t[a] About Us.\n");
    printf("\t\t[0] Exit the program.\n");
    printf("\t\t=======================\n");
}

void AddNewStudent(){
    char *IDStr[10];
    char *Name[20];
    char *Phone[20];
    char *Email[30];
    char *newStudent[200];
    newStudent[0] = 0;
    FILE *AllStudentsTextFile;
    FILE *AllStudentsCourseTextFile;

    NextStudentID = SetNextStudentId();
    itoa(NextStudentID, IDStr, 10);

    printf("\n*Name should be maximum 20 characters long.\n");
    printf("Enter The Name: ");
    scanf(" %[^\n]s",&Name);

    if(strlen(Name) > 20){
        ErrorAndRestart("!!!Error!!!\nName should be maximum 20 characters long.");
        return;
    }

    printf("\n*Phone Number should be unique and maximum 20 characters long.\n");
    printf("Enter The Phone: ");
    scanf("%s",&Phone);

    if(strlen(Phone) > 20){
        ErrorAndRestart("!!!Error!!!\nPhone Number should be maximum 20 characters long.");
        return;
    }
    if(AlreadyExists(Phone,'p') == 1){
        ErrorAndRestart("!!!Error!!!\nThis Phone Number is Already Exists.");
        return;
    }

    printf("\n*Email should be unique and maximum 30 characters long.\n");
    printf("Enter The Email: ");
    scanf("%s",&Email);

    if(strlen(Email) > 30){
        ErrorAndRestart("!!!Error!!!\nEmail should be maximum 30 characters long.");
        return;
    }
    if(AlreadyExists(Email,'e') == 1){
        ErrorAndRestart("!!!Error!!!\nThis Email is Already Exists.");
        return;
    }


    strcat(newStudent,IDStr);
    strcat(newStudent,"\n");
    strcat(newStudent,Name);
    strcat(newStudent,"\n");
    strcat(newStudent,Phone);
    strcat(newStudent,"\n");
    strcat(newStudent,Email);
    strcat(newStudent,"\n");


    // store course
    getchar();
    char *CourseLine[100];
    char *CourseCode[10];
    int CourseMarks;
    char CourseMarksStr[10];
    int NumberOfCourses;
    int i;
    CourseLine[0] = 0;
    printf("Note: ----\n");
    printf("A student can have maximum 5 and minimum 1 Courses.\n");
    printf("Enter Number of Course: ");
    scanf("%d",&NumberOfCourses);
    getchar();
    printf("Note: ----\n");
    printf("Course should maximum 5 characters long.\n");
    printf("Marks Should be maximum 100 and minimum 0.\n");
    for(i=1;i<=NumberOfCourses;i++){
        printf("Enter The Course %d Name: ",i);
        scanf("%s",&CourseCode);
        if(strlen(CourseCode)>5){
            ErrorAndRestart("!!!Error!!!\nCourse should be maximum 5 characters long.");
            return;
        }
        printf("Enter The Course %d Marks: ",i);
        scanf("%d",&CourseMarks);
        if(CourseMarks>100 || CourseMarks<0){
            ErrorAndRestart("!!!Error!!!\nCourse marks be maximum 100 and minimum 0.");
            return;
        }

        itoa(CourseMarks, CourseMarksStr, 10);

        if(strlen(CourseLine) != 0){
            strcat(CourseLine,"|");
            strcat(CourseLine,CourseCode);
            strcat(CourseLine,",");
            strcat(CourseLine,CourseMarksStr);
        }else{
            strcat(CourseLine,CourseCode);
            strcat(CourseLine,",");
            strcat(CourseLine,CourseMarksStr);
        }
    }
    strcat(CourseLine,"\n");

    char NumberOfCoursesStr[10];
    itoa(NumberOfCourses, NumberOfCoursesStr, 10);
    strcat(newStudent,NumberOfCoursesStr);
    strcat(newStudent,"\n");

    AllStudentsTextFile = fopen("All-Students.txt","a");
    fprintf(AllStudentsTextFile,newStudent);
    fclose(AllStudentsTextFile);

    AllStudentsCourseTextFile = fopen("All-Students-Courses.txt","a");
    fprintf(AllStudentsCourseTextFile,CourseLine);
    fclose(AllStudentsCourseTextFile);

    printf("\nSuccessfully added the student\n");
}

void ShowAllStudents(){
    system("cls");

    printf("\n\t\t **** All Students ****\n\n");
    printf("|==========|====================|====================|==============================|==========|\n");
    printf("|    ID    |        Name        |    Phone Number    |          Email               |  Course  |\n");
    printf("|==========|====================|====================|==============================|==========|\n");


    FILE *AllStudentsTextFile;
    int LineCount = 0;
    int LineLenght = 300;
    int TotalStudents = 0;
    char Line[LineLenght];
    AllStudentsTextFile = fopen("All-Students.txt","r");

    while(fgets(Line,LineLenght,AllStudentsTextFile)){
        LineCount++;
        if(LineCount == 1){
            PrintLineWithSpace(Line,'i');
        }else if(LineCount == 2){
            PrintLineWithSpace(Line,'n');
        }else if(LineCount == 3){
            PrintLineWithSpace(Line,'p');
        }else if(LineCount == 4){
            PrintLineWithSpace(Line,'e');
        }else if(LineCount == 5){
            PrintLineWithSpace(Line,'c');
            LineCount = 0;
            TotalStudents++;
        }
    }
    fclose(AllStudentsTextFile);
    printf("You have total %d students\n\n",TotalStudents);
    GoBackOrExit();
}

void PrintLineWithSpace(char *Line[100],char InforType){
    int i;
    char *FormatedLine= NULL;
    FormatedLine = strdup(Line);
    int FormatedLineLenght = strlen(FormatedLine);

    int TotalSpace = 0;
    if(InforType == 'i'){
        TotalSpace = 10 - FormatedLineLenght; // ID
    }else if(InforType == 'n'){
        TotalSpace = 20 - FormatedLineLenght; // name
    }else if(InforType == 'p'){
        TotalSpace = 20 - FormatedLineLenght; // phone
    }else if(InforType == 'e'){
        TotalSpace = 30 - FormatedLineLenght; // email
    }else if(InforType == 'c'){
        TotalSpace = 10 - FormatedLineLenght; // course
    }

    printf("|");
    for(i=0;i<FormatedLineLenght-1;i++){
        printf("%c",FormatedLine[i]);
    }

    for(i=0;i<=TotalSpace;i++){
        printf(" ");
    }


    if(InforType == 'c'){
        printf("|\n");
        printf("|----------|--------------------|--------------------|------------------------------|----------|\n");
    }
}

int SearchStudents(int StudentID){
    char *IDStr[10];
    int LineCount = 0;
    int StudentFound = 0;
    int NeedToPrintLine = 0;
    int LineLenght = 300;
    char Line[LineLenght];
    FILE *AllStudentsTextFile;
    FILE *AllStudentsCourseTextFile;

    itoa(StudentID, IDStr, 10);
    strcat(IDStr,"\n");

    AllStudentsTextFile = fopen("All-students.txt","r");

    while(fgets(Line,LineLenght,AllStudentsTextFile)){
        LineCount++;
        if(LineCount == 1 && strcmp(IDStr,Line) == 0){
            StudentFound = 1;
            NeedToPrintLine = 5;
        }
        if(NeedToPrintLine > 0){
            NeedToPrintLine--;
            if(LineCount == 1){
                printf("\nOne student found for ID %d",StudentID);
                printf("\nID: %s",Line);
            }else if(LineCount == 2){
                printf("Name: %s",Line);
            }else if(LineCount == 3){
                printf("Phone: %s",Line);
            }else if(LineCount == 4){
                printf("Email: %s",Line);
            }else if(LineCount == 5){
                printf("Course: %s\n",Line);
            }
        }

        if(LineCount == 5){
            LineCount = 0;
        }
    }
    fclose(AllStudentsTextFile);

    if(StudentFound > 0){
        AllStudentsCourseTextFile = fopen("All-students-Courses.txt","r");
        LineCount = 0;
        while(fgets(Line,LineLenght,AllStudentsCourseTextFile)){
            LineCount++;
            if(StudentID == LineCount){
                int x = 0;
                int CourseCount = 1;
                printf("Course %d Name: ",CourseCount);
                for(x=0;Line[x] != '\0'; x++){

                    if(Line[x] == '|'){
                        CourseCount++;
                        printf("\n\nCourse %d Name: ",CourseCount);
                    }

                    if(Line[x] == ','){
                        printf("\nCourse %d Mark: ",CourseCount);
                    }

                    if(Line[x] != '|' && Line[x] != ','){
                        printf("%c",Line[x]);
                    }
                }
                printf("\n\n");
                break;
            }
        }
        fclose(AllStudentsCourseTextFile);
    }

    return StudentFound;
}

void EditStudent(int StudentId){
    int LineLength = 300;
    int LineCount = 0;
    int StudentFound = 0;
    int SkipLine = 0;
    int StudentIDint;
    char Line[LineLength];
    char *UpdatedStudent[300];
    UpdatedStudent[0] = 0;
    char *NewID[20];
    char *NewName[20];
    char *NewPhone[20];
    char *NewEmail[30];
    int NewNumberOfCourseInt;
    char NewNumberOfCourseStr[10];

    FILE *ExistingALLStudentsFile;
    FILE *TempALLStudentsFile;
    ExistingALLStudentsFile = fopen("All-students.txt","r");
    TempALLStudentsFile = fopen("Temp-All-students.txt","w");

    char *IDStr[10];
    itoa(StudentId, IDStr, 10);
    strcat(IDStr,"\n");

    while(fgets(Line,LineLength,ExistingALLStudentsFile)){

        LineCount++;
        if(LineCount == 1 && strcmp(Line,IDStr) == 0){
            StudentFound = 1;
            SkipLine = 5;
        }

        if(SkipLine > 0){
            if(LineCount == 1){
                // student id not editable
                strcat(UpdatedStudent,Line);
                SkipLine = 4;
            }else if(LineCount == 2){

                printf("Enter The Name(0 for skip): ");
                scanf(" %[^\n]s",&NewName);

                if(strlen(NewName) > 20){
                    ErrorAndRestart("!!!!Error!!!\nName should be maximum 20 characters long.");
                    return;
                }

                if(strcmp(NewName,"0") == 0){
                    strcat(UpdatedStudent,Line);
                }else{
                    strcat(UpdatedStudent,NewName);
                    strcat(UpdatedStudent,"\n");
                }
                SkipLine = 3;

            }else if(LineCount == 3){
                printf("Enter The Phone(0 for skip): ");
                scanf("%s",&NewPhone);

                if(strlen(NewPhone) > 20){
                    fclose(ExistingALLStudentsFile);
                    fclose(TempALLStudentsFile);
                    remove("Temp-All-students.txt");
                    ErrorAndRestart("!!!!Error!!!\Phone number should be maximum 20 characters long.");
                    return;
                }
                if(AlreadyExists(NewPhone,'p') == 1){
                    fclose(ExistingALLStudentsFile);
                    fclose(TempALLStudentsFile);
                    remove("Temp-All-students.txt");
                    ErrorAndRestart("!!!!Error!!!\nThis Phone number is Already Exists.");
                    return;
                }

                if(strcmp(NewPhone,"0") == 0){
                    strcat(UpdatedStudent,Line);
                }else{
                    strcat(UpdatedStudent,NewPhone);
                    strcat(UpdatedStudent,"\n");
                }
                SkipLine = 2;

            }else if(LineCount == 4){
                printf("Enter The New Email(0 for skip): ");
                scanf("%s",&NewEmail);

                if(strlen(NewEmail) > 30){
                    ErrorAndRestart("!!!!Error!!!\Email should be maximum 30 characters long.");
                    return;
                }
                if(AlreadyExists(NewEmail,'e') == 1){
                    ErrorAndRestart("!!!!Error!!!\nThis email is Already Exists.");
                    return;
                }

                if(strcmp(NewEmail,"0") == 0){
                    strcat(UpdatedStudent,Line);
                }else{
                    strcat(UpdatedStudent,NewEmail);
                    strcat(UpdatedStudent,"\n");
                }
                SkipLine = 1;

            }else if(LineCount == 5){
                printf("Enter The New Number Course(0 for skip): ");
                scanf("%d",&NewNumberOfCourseInt);

                if(NewNumberOfCourseInt > 5){
                    ErrorAndRestart("!!!!Error!!!\nCourse should be maximum 5.");
                    return;
                }

                if(NewNumberOfCourseInt == 0){
                    strcat(UpdatedStudent,Line);
                }else{
                    itoa(NewNumberOfCourseInt, NewNumberOfCourseStr, 10);
                    strcat(UpdatedStudent,NewNumberOfCourseStr);
                    strcat(UpdatedStudent,"\n");
                }
                fprintf(TempALLStudentsFile,UpdatedStudent);
                SkipLine = 0;
            }

        }else{
            fprintf(TempALLStudentsFile,Line);
        }

        if(LineCount == 5){
            LineCount = 0;
        }
    }

    fclose(ExistingALLStudentsFile);
    fclose(TempALLStudentsFile);

    remove("All-students.txt");
    rename("Temp-All-students.txt", "All-students.txt");

    // lets edit or update the course
    if(NewNumberOfCourseInt > 0){
        FILE *AllCoursesFileExisting = fopen("All-Students-Courses.txt","r");
        FILE *AllCoursesFileTemp = fopen("All-Students-Courses-Temp.txt","w");
        LineCount = 0;
        char CourseCode[10];
        int CourseMarks;
        int i;
        char CourseMarksStr[10];
        char NewCourseLine[100];
        NewCourseLine[0] = 0;
        while(fgets(Line, LineLength, AllCoursesFileExisting)){
            LineCount++;
            if(LineCount == StudentId){
                printf("THis is our course line should we edite: %s",Line);

                printf("Note: ----\n");
                printf("Course should maximum 5 characters long.\n");
                printf("Marks Should be maximum 100 and minimum 0.\n");
                for(i=1;i<=NewNumberOfCourseInt;i++){
                    printf("Enter The Course %d Name: ",i);
                    scanf("%s",&CourseCode);
                    if(strlen(CourseCode)>5){
                        ErrorAndRestart("!!!Error!!!\nCourse should be maximum 5 characters long.");
                        return;
                    }
                    printf("Enter The Course %d Marks: ",i);
                    scanf("%d",&CourseMarks);
                    if(CourseMarks>100 || CourseMarks<0){
                        ErrorAndRestart("!!!Error!!!\nCourse marks be maximum 100 and minimum 0.");
                        return;
                    }

                    itoa(CourseMarks, CourseMarksStr, 10);

                    if(strlen(NewCourseLine) != 0){
                        strcat(NewCourseLine,"|");
                        strcat(NewCourseLine,CourseCode);
                        strcat(NewCourseLine,",");
                        strcat(NewCourseLine,CourseMarksStr);
                    }else{
                        strcat(NewCourseLine,CourseCode);
                        strcat(NewCourseLine,",");
                        strcat(NewCourseLine,CourseMarksStr);
                    }
                }
                fprintf(AllCoursesFileTemp,NewCourseLine);
            }else{
                fprintf(AllCoursesFileTemp,Line);
            }
        }

        fclose(AllCoursesFileExisting);
        fclose(AllCoursesFileTemp);
        remove("All-Students-Courses.txt");
        rename("All-Students-Courses-Temp.txt", "All-Students-Courses.txt");
    }

    printf("Student Updated Successfully\n");
    return 0;
}

void DeleteStudent(){

    system("cls");
    printf("\n\t\t **** Delete Students ****\n\n");

    int LineLength = 300;
    int LineCount = 0;
    int StudentFound = 0;
    int SkipLine = 0;
    char Line[LineLength];
    char *DeleteID[30];
    printf("\n*ID should be maximum 10 characters long.\n");
    printf("Enter the ID which one you want to delete: ");
    scanf("%s",DeleteID);
    strcat(DeleteID,"\n");

    FILE *ExistingALLStudentsFile, *TempALLStudentsFile;
    ExistingALLStudentsFile = fopen("All-Students.txt","r");
    TempALLStudentsFile = fopen("Temp-All-Students.txt","w");

    while(fgets(Line,LineLength,ExistingALLStudentsFile)){
        LineCount++;
        if(LineCount == 1 && strcmp(Line,DeleteID) == 0 ){
            SkipLine = 5;
            StudentFound = 1;
        }

        if(SkipLine > 0){
            SkipLine--;
        }else{
            fprintf(TempALLStudentsFile,Line);
        }
        if(LineCount == 5){
            LineCount = 0;
        }
    }

    fclose(ExistingALLStudentsFile);
    fclose(TempALLStudentsFile);

    if(StudentFound == 0){
        printf("Students Not Found!\n");
        remove("Temp-All-students.txt");
    }else{
        printf("Students Deleted Successfully\n");
        remove("All-students.txt");
        rename("Temp-All-students.txt", "All-students.txt");
    }
}

void DeleteAllStudents(){

    system("cls");
    printf("\n\t\t **** Delete All The Students ****\n\n");

    char Option;
    getchar();
    printf("Are you sure want to delete all the contacts? (Y,N)?: ");
    scanf("%c",&Option);
    if(Option=='Y' || Option=='y'){
        int i;
        remove("All-students.txt");
        FILE *AllContactTxtFile = fopen("All-students.txt","a");
        fclose(AllContactTxtFile);

        char Deleting[100] = "Deleting....";
        for(i=0;i<strlen(Deleting);i++){
            printf("%c",Deleting[i]);
            Sleep(40);
        }
        printf("\nSuccessfully Deleted All Students!\n\n");

    }
    GoBackOrExit();
}

bool AlreadyExists(char *GivenLine[30],char InfoType){
    char *ThisLine[35];
    ThisLine[0] = 0;
    strcat(ThisLine,GivenLine);
    strcat(ThisLine,"\n");
    int FileLineNumber = 0;
    if(InfoType == 'i'){
        FileLineNumber = 1; // id
    }else if(InfoType == 'n'){
        FileLineNumber = 2; // name
    }else if(InfoType == 'p'){
        FileLineNumber = 3; // phone
    }else if(InfoType == 'e'){
        FileLineNumber = 4; // email
    }else if(InfoType == 'c'){
        FileLineNumber = 5; // Course
    }


    FILE* AllStudentsFile;
    int LineLength = 300;
    char Line[LineLength];
    AllStudentsFile = fopen("All-students.txt", "r");
    int LineCount = 0;
    int TotalContact = 0;
    int Found = 0;
    while(fgets(Line, LineLength, AllStudentsFile)) {
       LineCount++;
        if(LineCount == FileLineNumber && strcmp(ThisLine, Line) == 0){
            Found = 1;
        }
        if(LineCount == 5){
            LineCount = 0;
        }
    }
    fclose(AllStudentsFile);
    if(Found == 1){
        return true;
    }else{
        return false;
    }
}

void ErrorAndRestart(char *error[100]){
    printf("%s\n",error);
    int i = 0;
    printf("Restarting the program: ");
    for(i=0;i<10;i++){
        printf(".");
        Sleep(500);
    }
    system("cls");
    main();
}

void UserGuideline(){
    system("cls");
    printf("\n\n\t\t\t\tUser Guideline\n");
    printf("\t\t=========================================\n");
    printf("\t\t[>] This project is created using c programming language.\n");
    printf("\t\t[>] All information will store in text file.\n");
    printf("\t\t[>] A Student has Name, Phone, Email, Course\n");
    printf("\t\t[>] Student's ID, Email & Phone should be unique.\n");
    printf("\t\t[>] ID should be maximum 10 characters long.\n");
    printf("\t\t[>] Name should be maximum 20 characters long.\n");
    printf("\t\t[>] Phone should be maximum 20 characters long.\n");
    printf("\t\t[>] Email should be maximum 30 characters long.\n");
    printf("\t\t[>] Course Code should be maximum 10 characters long.\n");
    printf("\t\t=========================================\n");
    GoBackOrExit();
}

void AboutUs(){
    system("cls");
    printf("\n\n\t\t\t\tAbout Us\n");
    printf("\t\t=======================================\n");
    printf("\t\t[>] This project is created using c programming language.\n");
    printf("\t\t[>] All information will store in text file.\n");
    printf("\t\t[>] A Student has Name, Phone, Email, Course\n");
    printf("\t\t[>] Student ID will create automatically.\n");
    printf("\t\t[>] Student's Email & Phone should be unique.\n");
    printf("\t\t[>] Student Name should be maximum 20 characters long.\n");
    printf("\t\t[>] Student Phone should be maximum 20 characters long.\n");
    printf("\t\t[>] Student Email should be maximum 30 characters long.\n");
    printf("\t\t[>] Student Course Code should be maximum 10 characters long.\n");
    printf("\t\t======================================\n");
    GoBackOrExit();
}

void GoBackOrExit(){
    getchar();
    char Option;
    printf("Go back(b)? or Exit(0)?: ");
    scanf("%c",&Option);
    if(Option == '0'){
        ExitProject();
    }else{
        system("cls");
    }
    return 0;
}

void ExitProject(){
    system("cls");
    int i;
    char ThankYou[100]     = "=========Thank You=========\n";
    char SeeYouSoon[100]   = "=========See You Soon======\n";
    for(i=0;i<strlen(ThankYou);i++){
        printf("%c",ThankYou[i]);
        Sleep(40);
    }
    for(i=0;i<strlen(SeeYouSoon);i++){
        printf("%c",SeeYouSoon[i]);
        Sleep(40);
    }
    exit(0);
}




















