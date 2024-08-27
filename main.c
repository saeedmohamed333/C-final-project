#include <stdio.h>
#include <stdlib.h>

/*Creating Struct for patient's info*/
typedef struct P
{
    char Name[40];
    int Age; 
    char Gender[10];
    int ID;
    int Reservation_slot;               //Stores Slot number
    struct P * Next ;
}Patient_Info;

Patient_Info * Start = NULL;            //Start Pointer to our linked list

//2D Array stores slots
char slots[5][20] = {"2pm to 2:30pm","2:30pm to 3pm","3pm to 3:30pm","4pm to 4:30pm","4:30pm to 5pm"};
//Array Indicates the available slots  0 -> available   1 -> not available
int available_slots[5] = {0};  

void Add_Patient();                      //Add Patient Function Prototype
void Edit_Patient();                     //Edit Patient Function Prototype
void Reserve_Slot();                     //Reserve Slot Function Protoype
void Cancel_Reservation();               //Cancel Reservation Function Prototype
void Patient_record();                   //view patient's record code segment
void Today_reservations();                //view today's reservations code segment

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
        printf("\033[36mFor admin mode type \"a\" - For user mode type \"u\" - Type \"e\" to exit: \033[0m");
        scanf("  %c",&mode);

        if(mode == 'a')       //Checking for the required mode
        {
            /*Admin mode*/
            count = 0;        //Reseting count 
            while(count < 3 )
            {
                printf("\033[36mPlease, Enter your password: \033[0m");
                scanf("%d", &password);
                if(password == Default_Admin_Password)
                {
                    printf("\033[36mTo add new patient record type \"a\" - To edit patient record type \"e\" - To reserve a slot type \"r\" - To Cancel a reservation type \"c\": \033[0m");
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
                        Reserve_Slot();
                    }
                    else if(Admin_mode == 'c')
                    {
                        Cancel_Reservation();
                    }
                    else
                    {
                        printf("\033[31mInvalid Input\033[0m\n");
                    }
                    count = 3;         //Updating count with a value not < 3 to exit the loop
                    password = 0;
                }
                else
                {   
                    printf("\033[31mIncorrect Password. Please, Try again later\033[0m\n");
                    count++;
                }
            }
            mode = 0;         //Reseting mode to ask user again 
        }
        else if(mode == 'u')
        {
            /*User mode*/
            printf("\033[36mTo view patient's record type \"p\" - To view today's reservations type \"r\": \033[0m");
            scanf("  %c",&User_mode);
            if(User_mode == 'p')
            {
                Patient_record();
            }
            else if (User_mode == 'r')
            {
                Today_reservations();
            }
            else
            {
                printf("\033[31mInvalid Input\033[0m\n");
            }
            mode = 0;         //Reseting mode to ask user again
        }
        else if(mode == 'e')
        {
            exit_state = 0;  
        }
        else                             //default case to avoid invalid inputs
        {
            printf("\033[31mInavalid Input - Please try again\033[0m\n");
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
    printf("Enter The Name:");
    scanf(" %[^\n]s",patient->Name);
    printf("Enter The Age:");
    scanf("%d",&patient->Age);
    printf("Enter The Gender:");
    scanf(" %[^\n]s",patient->Gender);
    printf("Enter The ID:");
    scanf("%d",&patient->ID);
    patient -> Reservation_slot = 0;

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
        printf("\033[31mSorry, this ID already exists please try again.\033[0m\n");
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
        printf("\033[31mSorry, this ID does not exist. Please try again.\033[0m\n");  // Patient with the given ID was not found 
    }
}

//Reserve Slot Function Implementation
void Reserve_Slot()
{
    int Patient_Found_Flag = 0;
    int Patient_ID = 0;
    int Slot = 0;

    printf("Enter the ID of the patient to reserve a slot: ");
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

    if (Patient_Found_Flag == 1 && Temp -> Reservation_slot == 0) 
    {
        printf("These are the available Slots: \n");
        for(int counter = 0; counter < 5; counter++)
        {
            if(available_slots[counter] == 0)      //Only print the available slots
            {
                printf(" %d- %s   ", counter + 1 ,slots[counter]);
            }
        }
        printf("\nPlease, enter the number of the required slot: ");
        scanf("%d",&Slot);
        if(Slot >= 1 && Slot <= 5 && available_slots[Slot - 1] == 0)
        {
            Temp -> Reservation_slot = Slot;
            available_slots[(Temp -> Reservation_slot) - 1] = 1;  //The entered Slot is not available any more
        }
        else
        {
            printf("\033[31mYou entered an invalid or reserved slot number\033[0m\n");
        }
    }
    else
    {
        printf("\033[31mSorry, this ID does not exist or there is already a reservation. Please try again.\033[0m\n");
    }

}

//Cancel Reservation Function Implementation
void Cancel_Reservation()
{
    int Patient_Found_Flag = 0;
    int Patient_ID = 0;

    printf("Enter the ID of the patient to cancel reservation: ");
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
    if (Patient_Found_Flag == 1)
    {
        if(Temp -> Reservation_slot != 0)
        {
            available_slots[Temp -> Reservation_slot - 1] = 0;
            Temp -> Reservation_slot = 0;
            printf("The reservation was cancelled successfully. \n");
        }
        else
        {
            printf("There is no reservations to be cancelled \n");
        }
    }
    else
    {
        printf("\033[31mSorry, this ID does not exist. Please try again.\033[0m\n");
    }
}
void Patient_record()
{
   
    int Patient_Found_Flag = 0;
    int Patient_ID = 0;

    printf("Please enter the ID: ");
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

    if (Patient_Found_Flag == 1)  
    {
        printf(" Name: %s\n", Temp->Name);
        printf(" Age: %d\n", Temp->Age);
        printf(" Gender: %s\n", Temp->Gender);
    } 
    else 
	{
        printf("\033[31mSorry, this ID does not exist. Please try again.\033[0m\n");  // Patient with the given ID was not found 
    }
}
void Today_reservations()
{ 
    int reservations_exist = 0;            // Check if any reservations exist
    Patient_Info *Temp = Start;
    while (Temp != NULL)
    { 
        if(Temp->Reservation_slot>0) 
       {
              reservations_exist = 1;
              printf("Slot %d - %s:Is reserved by Patient : %s, ID: %d\n",  Temp->Reservation_slot, slots[Temp->Reservation_slot - 1], Temp->Name,
              Temp->ID);
        }
     Temp = Temp->Next;
    }
if (reservations_exist ==0)
{
    printf("No reservations found for today\n ");
}
}