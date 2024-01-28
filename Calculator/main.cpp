#include <iostream>
#include <conio.h>
using namespace std;

int main()
{
    cout << "CALCULATOR" << endl << endl;

    while(true)
    {
        int counter = 0, inputSignCounter = 0;
        int numbersCounter = 0, signsCounter = 0;
        int errorFlag = 0;
        float sum = 0;
        float numbers[50];
        char signs[50];
        char sequence[100];
        char key;

        while(true)
        {
            key = getch();
            if(key >= '0' && key <= '9')
            {
                sequence[counter] = key;
                counter++;
                cout << key;
            }
            else if(((key == '+' || key == '-' || key == '*' || key == '/') && (counter > 0) && (inputSignCounter < 10) && (sequence[counter - 1] >= '0' && sequence[counter - 1] <= '9')))
            {
                sequence[counter] = key;
                counter++;
                inputSignCounter++;
                cout << key;
            }
            else if(key == '\b' && counter > 0)
            {
                counter--;

                if(sequence[counter] == '+' || sequence[counter] == '-' || sequence[counter] == '*' || sequence[counter] == '/')
                    inputSignCounter--;

                sequence[counter] = NULL;
                cout << "\b \b";
            }
            else if((key == '\r') && (inputSignCounter > 0) && (sequence[counter - 1] >= '0' && sequence[counter - 1] <= '9'))
            {
                sequence[counter] = NULL;
                break;
            }
            else if(key == 27)
                return 0;
        }

        for(int i = 0; i < counter; i++)
        {
            if(sequence[i] >= '0' && sequence[i] <= '9')
            {
                int number = 0;
                for(;; i++)
                {
                    if(sequence[i] < '0' || sequence[i] > '9' || i >= counter)
                    {
                        numbers[numbersCounter++] = number;
                        break;
                    }
                    number = number * 10 + (sequence[i] - '0');
                }
            }
            if(sequence[i] == '+' || sequence[i] == '-' || sequence[i] == '*' || sequence[i] == '/')
                signs[signsCounter++] = sequence[i];
        }

        for(int i = 0; i < numbersCounter; i++)
        {
            if(signs[i] == '*' || signs[i] == '/')
            {
                float operationResult;
                if(signs[i] == '*')
                    operationResult = numbers[i] * numbers[i + 1];

                if(signs[i] == '/')
                {
                    if(numbers[i + 1] == 0)
                    {
                        errorFlag = 1;
                        break;
                    }
                    operationResult = numbers[i] / numbers[i + 1];
                }

                int tracker;
                for(tracker = i; tracker <  signsCounter - 1; tracker++)
                    signs[tracker] = signs[tracker + 1];
                signs[tracker] = NULL;

                numbers[i] = operationResult;
                for(tracker = i + 1; tracker < numbersCounter - 1; tracker++)
                    numbers[tracker] = numbers[tracker + 1];
                numbersCounter--;
                i--;
            }
        }

        for(int i = 0; i < numbersCounter; i++)
        {
            if(signs[i] == '-')
                numbers[i + 1] *= -1;
            sum += numbers[i];
        }

        if(!errorFlag)
            cout << " = " << sum << endl;
        else
            cout << " = NOT POSSIBLE" << endl;
    }
    return 0;
}
