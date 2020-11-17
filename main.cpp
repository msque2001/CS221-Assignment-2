#include <iostream>
#include <cmath>
using namespace std;

template<class X>
class Stack
{
    struct Node
    {
        X data;
        Node *nextPtr;
        Node *prevPtr;
    }*headPtr;

    public:
        Stack()
        {
            headPtr = NULL;
        }

        bool isEmpty()
        {
            if(headPtr == NULL) // Stack is empty
                return true;
            return false;
        }

        X top()
        {
            if(!isEmpty())
            {
                return headPtr->data;
            }
            return '\0';
        }

        void push(X x)
        {
            Node *newNode = new Node;
            newNode->data = x;
            
            if(!isEmpty())
            {
                Node *tailPtr = headPtr->prevPtr; // Last node
                headPtr->prevPtr = newNode;
                newNode->nextPtr = headPtr;
                newNode->prevPtr = headPtr->prevPtr;
                headPtr = newNode;
                headPtr->prevPtr = tailPtr; // Circular linking
            }
            else // Empty Stack
            {
                newNode->nextPtr = newNode->prevPtr = NULL;
                headPtr = newNode;
                headPtr->prevPtr = newNode;
            }
        }

        void pop()
        {
            if(!isEmpty()) // Not empty
            {
                Node *temp = headPtr;
                if(temp->nextPtr != NULL)
                {
                    Node *tailPtr = headPtr->prevPtr;
                    headPtr = headPtr->nextPtr;
                    headPtr->prevPtr = tailPtr;
                }
                else // Empty Stack
                {
                    headPtr = NULL;
                }
                
                delete temp;
            }
        }
};
Stack<char>con;


string postfix;
bool precedence(char op,char check)
{
    if (check == '+' )
    {
        if (op == '*' || op == '/' || op == '^'||op=='-' || op == '+')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else  if (check == '-')
    {
        if (op == '*' || op == '/' || op == '^' || op == '+' || op == '-')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (check == '*' )
    {
        if (op == '^' || op == '/' || op == '*')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (check == '/')
    {
        if (op == '^' || op == '*' ||  op == '/'  )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (check == '^')
    {
        return false;
    }
    else
    {
        return false;
    }
    
 
}
void convert(string infix)
{
   
   char temp;
    bool check_bracket=true;
    for (int i = 0;infix[i] != '\0' ;i++)
    {
        temp=infix[i-1];
        if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^')
        {
            if (con.isEmpty())
            {
                check_bracket = true;
                if(temp!=')')
                {
                postfix = postfix + "]";
                }
                con.push(infix[i]);
                
            }
            else
            {
                check_bracket = true;
                  if(temp!=')')
                {
                postfix = postfix + "]";
                }
                int count = 0;
                while (!con.isEmpty())
                {
                    char x = con.top();

                    if (precedence(x, infix[i]))
                    {
                        con.pop();
                        postfix = postfix + x;
                        
                        count++;
                      
                    }
                    else
                        break;
                }
                    con.push(infix[i]);
                }
            
            

        }
        else if (infix[i] == '(' )
        {
            con.push(infix[i]);
        }
        else if (infix[i] == ')')
        {
            if(infix[i+1]!='\0')
            postfix = postfix + "]";
            while (!con.isEmpty())
            {
                char x = con.top();
                if (x != '(')
                {
                    con.pop();
                    postfix = postfix + x;
                }
                else
                {
                    con.pop();
                    
                }
            }
        }
        else 
        {
            if (check_bracket)
            {
                postfix = postfix + "[";
                check_bracket = false;
            }
            
            postfix = postfix + infix[i];
            if(infix[i+2]=='\0')
            postfix = postfix + "]";
          

        }
       
    }

}
void evalute();
void add(Stack<float> &solution, float num1, float num2);
void subtract(Stack<float> &solution, float num1, float num2);
void multiply(Stack<float> &solution, float num1, float num2);
void divide(Stack<float> &solution, float num1, float num2);
void power(Stack<float> &solution, float num1, float num2);
void theProgram()
{
    string infix;
    
    cout << "\nEnter String: ";
    cin >> infix;
    
    infix = infix + ')';
    convert(infix);
    infix.pop_back(); // Removing extra bracket at the end
    system("clear");

    cout << "\nInfix: " << infix << endl;
    cout << "Postfix: " << postfix << endl;
    evalute();

    postfix = "";
}


int main()
{
    bool isComplete = false;
    char choice;
    while(!isComplete)
    {
        theProgram();
        cout << "\n Press y/Y to run the program again. Press any other character to exit the program: ", cin >> choice, cout << endl;

        if(choice != 'Y' && choice != 'y')
        {
            cout << "Bye, bye :)" << endl;
            isComplete = true;
        }
    }


   return 0;
}

void evalute()
{
    Stack<float> solution;
    bool bracketComplete;
    string temp_str = "";
    float num1, num2, newNum;
    for(int i = 0; postfix[i] != '\0'; i++)
    {
        if(postfix[i] == '[' ) // Starting of integer
        {
            bracketComplete = false;
            i++;
            while(!bracketComplete)
            {
                temp_str = temp_str + postfix[i++]; // Making integer
                if(postfix[i] == ']') // Integer complete
                    bracketComplete = true;
            }
            solution.push(stoi(temp_str));
            temp_str = "";
        }
        else // Operator
        {
            num1 = solution.top();
            solution.pop();

            num2 = solution.top();
            solution.pop();

            switch (postfix[i])
            {
            case '+':
                add(solution, num1, num2);
                break;

            case '-':
                subtract(solution, num1, num2);                
                break;
            
            case '*':
                multiply(solution, num1, num2);
                break;

            case '/':
                divide(solution, num1, num2);
                break;

            case '^':
                power(solution, num1, num2);
                break;            
            
            default:
                break;
            }
        }
    }
    newNum = solution.top();
    solution.pop();
    cout << "Solution: " << newNum << endl;
}

void add(Stack<float> &solution, float num1, float num2)
{
    solution.push(num2 + num1);
}
void subtract(Stack<float> &solution, float num1, float num2)
{
    solution.push(num2 - num1);
}
void multiply(Stack<float> &solution, float num1, float num2)
{
    solution.push(num2 * num1);
}
void divide(Stack<float> &solution, float num1, float num2)
{
    solution.push(num2 / num1);
}
void power(Stack<float> &solution, float num1, float num2)
{
    solution.push(pow(num2, num1));
}

