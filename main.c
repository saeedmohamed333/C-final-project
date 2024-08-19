#include <stdio.h>

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
                    printf("To add new patient record type \"a\" - To edit patient record type \"e\" - To reserve a slot type \"r\" - To Cancel a reservation type \"c\" - Type \"e\" to exit: ");
                    scanf("  %c", &Admin_mode);
                    if(Admin_mode == 'a')
                    {
                        /*add new patient code segment*/
                    }
                    else if(Admin_mode == 'e')
                    {
                        /*edit patient rercord code segment*/
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
                }
                else
                {   
                    printf("Incorrect Password. Please, Try again\n");
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