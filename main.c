#include "apc.h"

int main(int argc, char *argv[]) 
{
    char option;
    char input1[100], input2[100], operator;
    int calculation_successful = 0;

    if (argc == 4) 
    {
        // Use command-line arguments for the first calculation
        strcpy(input1, argv[1]);
        operator = *argv[2];
        strcpy(input2, argv[3]);
    } 
    else 
    {
        // Prompt for initial input if no command-line arguments are provided
        printf("Usage: Enter num1, operator, num2: ");
        scanf("%s %c %s", input1, &operator, input2);
    }

    while (1)  // Use an infinite loop with explicit break conditions
    {
        // Reset lists for each new calculation
        Dlist *head1 = NULL, *tail1 = NULL, *head2 = NULL, *tail2 = NULL, *headR = NULL;

        // Input validation
        int num1_valid = 1, num2_valid = 1, operator_valid = 1;
        
        // Validate first number
        int start_index1 = (input1[0] == '-') ? 1 : 0;
        for (int i = start_index1; input1[i]; i++) 
        {
            if (!isdigit(input1[i])) 
            {
                num1_valid = 0;
                break;
            }
        }
    // Validate second number
    int start_index2 = (input2[0] == '-') ? 1 : 0;
    for (int i = start_index2; input2[i]; i++) 
    {
    if (!isdigit(input2[i])) 
    {
        num2_valid = 0;
        break;
    }
}

// Validate operator
if (strchr("+-*/", operator) == NULL) 
{
    operator_valid = 0;
}

// Special case: allow consecutive minus signs
if (input1[0] == '-' && input2[0] == '-' && strlen(input1) > 1 && strlen(input2) > 1) 
{
    num1_valid = 1;
    num2_valid = 1;
}

        // Handle invalid input
        if (!num1_valid || !num2_valid || !operator_valid) 
        {
            printf("Invalid input. Please enter integer numbers and a valid operator (+, -, *, /).\n");
            
            // Ask if user wants to continue
            printf("Want to continue? Press [yY | nN]: ");
            scanf(" %c", &option);
            
            if (option == 'y' || option == 'Y') 
            {
                // Prompt for new input
                printf("Enter num1, operator, num2: ");
                scanf("%s %c %s", input1, &operator, input2);
                continue;  // Restart the loop with new input
            }
            else 
            {
                return SUCCESS;  // Exit the program
            }
        }

        // For negative numbers, remove the minus sign for list creation
        char positive_input1[100], positive_input2[100];
        strcpy(positive_input1, (input1[0] == '-') ? input1 + 1 : input1);
        strcpy(positive_input2, (input2[0] == '-') ? input2 + 1 : input2);

        create_list_from_input(&head1, &tail1, positive_input1);
        create_list_from_input(&head2, &tail2, positive_input2);

        int result_status = FAILURE;
        int result_sign = 1;

        switch (operator) 
        {
            case '+':
            // Handle sign for addition
            if (input1[0] == '-' && input2[0] == '-') {
            // Both numbers are negative, sum will be negative
            result_sign = -1;
            result_status = addition(&head1, &tail1, &head2, &tail2, &headR);
        } 
        else if (input1[0] == '-' || input2[0] == '-') {
        // One number is negative, perform subtraction
        if (input1[0] == '-') 
        {
            // (-a) + b = b - a
            result_status = subtraction(&head2, &tail2, &head1, &tail1, &headR);
        } 
        else 
        {
            // a + (-b) = a - b
            result_status = subtraction(&head1, &tail1, &head2, &tail2, &headR);
        }
    } 
    else 
    {
        // Normal addition of positive numbers
        result_status = addition(&head1, &tail1, &head2, &tail2, &headR);
    }
    break;
        case '-':
    // Subtraction sign logic
    if (input1[0] == '-' && input2[0] == '-') 
    {
        // (-a) - (-b) = -a + b
        // For example, -5 - (-5) should be 0
        result_status = subtraction(&head2, &tail2, &head1, &tail1, &headR);
    } 
    else if (input1[0] == '-') 
    {
        // (-a) - b = -(a + b)
        result_status = addition(&head1, &tail1, &head2, &tail2, &headR);
        result_sign = -1;
    } else if (input2[0] == '-') 
    {
        // a - (-b) = a + b
        result_status = addition(&head1, &tail1, &head2, &tail2, &headR);
    } 
    else 
    {
        // a - b (normal subtraction)
        result_status = subtraction(&head1, &tail1, &head2, &tail2, &headR);
    }
    break;
            case '*':
                result_status = multiplication(&head1, &tail1, &head2, &tail2, &headR);
                // Multiplication sign logic
                if (input1[0] == '-' ^ input2[0] == '-') 
                {
                    result_sign = -1;
                }
                break;
            case '/':
                result_status = division(&head1, &tail1, &head2, &tail2, &headR);
                // Division sign logic
                if (input1[0] == '-' ^ input2[0] == '-') 
                {
                    result_sign = -1;
                }
                break;
        }

        // Print result with appropriate sign
        if (result_status == SUCCESS) 
        {
            if (result_sign < 0) printf("-");
            print_list(headR);
        }

        // Free allocated lists
        free_list(head1);
        free_list(head2);
        free_list(headR);

        // Normal continuation prompt
        printf("Want to continue? Press [yY | nN]: ");
        
        // Use a temporary string to capture input and validate
        char temp_input[100];
        scanf("%s", temp_input);

        // Check if input is exactly 'y' or 'Y'
        if (strlen(temp_input) == 1 && 
            (temp_input[0] == 'y' || temp_input[0] == 'Y')) 
        {
            printf("Enter num1, operator, num2: ");
            scanf("%s %c %s", input1, &operator, input2);
        }
        else if (strlen(temp_input) == 1 && 
                (temp_input[0] == 'n' || temp_input[0] == 'N')) 
        {
            return SUCCESS;
        }
        else 
        {
            // Invalid input
            printf("Invalid input. Exiting the program.\n");
            return SUCCESS;
        }
    }

    return SUCCESS;
}