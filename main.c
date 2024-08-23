#include <stdio.h>
#include <stdlib.h>

/*Creating Struct for patient's info*/
typedef struct P
{
    char Name[40];
    int Age; 
    char Gender[10];
    int ID;
    int Reservation_slot;
    struct P * Next ;
}Patient_Info;

Patient_Info * Start = NULL;            //Start Pointer to our linked list

void Add_Patient();                      //Add Patient Function Prototype
void Edit_Patient();                     //Edit Patient Function Prototype

int main()
{
    const int Default_Admin_Password  = 1234;   //Constant variable holds admin mode's default password
    int exit_state = 1;      //Variable to check for exiting the program
    char mode = 0;           //Variable to navigate through system modes
    int password = 0;        //Variable to store scanned password
    int count = 0;           //Counter to store no. of incorrect passwords
    char Admin_mode = 0;     //Variable to navigate through admin mode
    char User_mode = 0;      //Variable to navigate through user mode

    //Printing Welcome message
    printf("\033[33m=================== Welcome to Real-Time Rebels Clinic ====================\033[0m\n");
    
    do   //main program loop
    {
        //Asking user for required mode
        printf("For admin mode type \"a\" - For user mode type \"u\" - Type \"e\" to exit: ");
        scanf("  %c",&mode);

        if(mode == 'a')       //Checking for the required mode
        {
            /*Admin mode*/
            count = 0;        //Reseting count 
            while(count < 3 )
            {
                printf("\033[33mPlease, Enter your password:\033[0m ");
                scanf("%d", &password);
                if(password == Default_Admin_Password)
                {
                    printf("To add new patient record type \"a\" - To edit patient record type \"e\" - To reserve a slot type \"r\" - To Cancel a reservation type \"c\": ");
                    scanf("  %c", &Admin_mode);
                    if(Admin_mode == 'a')
                    {
                        Add_Patient();
                    }
                    else if(Admin_mode == 'e')
                    {
                        Edit_Patient();
                    }
                    else if(Admin_mode == 'r')
                    {
                        /*reserve a slot code segment*/
                    }
                    else if(Admin_mode == 'c')
                    {
                        /*cancel reservation code segment*/
                    }
                    else
                    {
                        printf("Invalid Input\n");
                    }
                    count = 3;         //Updating count with a value not < 3 to exit the loop
                    password = 0;
                }
                else
                {   
                    printf("Incorrect Password. Please, Try again later\n");
                    count++;
                }
            }
            mode = 0;         //Reseting mode to ask user again 
        }
        else if(mode == 'u')
        {
            /*User mode*/
            printf("To view patient's record type \"p\" - To view today's reservations type \"r\": ");
            scanf("  %c",&User_mode);
            if(User_mode == 'p')
            {
                /*view patient's record code segment*/
            }
            else if (User_mode == 'r')
            {
                /*view tody's reservations code segment*/
            }
            else
            {
                printf("Invalid Input\n");
            }
            mode = 0;         //Reseting mode to ask user again
        }
        else if(mode == 'e')
        {
            exit_state = 0;  
        }
        else                             //default case to avoid invalid inputs
        {
            printf("Inavalid Input - Please try again\n");
        }

        //Printing exit message
        if(exit_state == 0)
        {
            printf("\033[33mThanks for visiting us\033[0m\n");
        }

    } while (exit_state);
    
    return 0;
}

/*Function Implementation*/
void Add_Patient()
{
    int Already_Existing_ID_Flag = 0; 

    /*Adding Patient*/
    Patient_Info * patient = (Patient_Info*)malloc(sizeof(Patient_Info));
    patient -> Next = NULL;

    /*Scanning Information*/
    printf("Enter your Name:");
    scanf(" %[^\n]s",patient->Name);
    printf("Enter your Age:");
    scanf("%d",&patient->Age);
    printf("Enter your Gender:");
    scanf(" %[^\n]s",patient->Gender);
    printf("Enter your ID:");
    scanf("%d",&patient->ID);

    /*Check on the linkedlist*/
    if(Start == NULL)
    {
        Already_Existing_ID_Flag = 0; //There are no patients so any ID is acceptable
    }
    else
    {
        Patient_Info * Temp  = Start; 
        while(Temp!= NULL) 
        {
            if(Temp -> ID == patient -> ID)
            {
                Already_Existing_ID_Flag = 1;
            }
            Temp = Temp -> Next;
        }
    }

    if(Already_Existing_ID_Flag == 0)  //Making decision to add patient or not
    {
    
    /*Check on the linkedlist*/
    if(Start == NULL)
    {
        Start = patient;
    }
    else
    {
        /*Check on the last Patient*/
        Patient_Info * Temp  = Start; 
        while(Temp->Next != NULL) //Temp->Next == NULL 
        {
            Temp = Temp -> Next;
        }
        Temp -> Next = patient; 

    }
    }
    else if(Already_Existing_ID_Flag == 1)
    {
        free(patient);
        printf("Sorry, this ID already exists please try again\n");
    }
}
void Edit_Patient()
{
    int Patient_Found_Flag = 0;
    int Patient_ID = 0;

    printf("Enter the ID of the patient to edit: ");
    scanf("%d", &Patient_ID);

    /* Searching for the patient with the given ID */
    Patient_Info *Temp = Start;
    while (Temp != NULL) 
    {
        if (Temp->ID == Patient_ID) 
        {
            Patient_Found_Flag = 1;
            break;
        }
        Temp = Temp->Next;
    }

    if (Patient_Found_Flag == 1)  // Patient found, update their information 
    {
       
        printf("Editing patient record:\n");

        printf("Current Name: %s\n", Temp->Name);
        printf("Enter new Name: ");
        scanf(" %[^\n]s", Temp->Name);

        printf("Current Age: %d\n", Temp->Age);
        printf("Enter new Age: ");
        scanf("%d", &Temp->Age);

        printf("Current Gender: %s\n", Temp->Gender);
        printf("Enter new Gender: ");
        scanf(" %[^\n]s", Temp->Gender);

        printf("Patient record updated successfully.\n");
    } 
    else 
	{
        printf("Sorry, this ID does not exist. Please try again.\n");  // Patient with the given ID was not found 
    }
}