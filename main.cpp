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
            if(headPtr == NULL)
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
                Node *tailPtr = headPtr->prevPtr;
                headPtr->prevPtr = newNode;
                newNode->nextPtr = headPtr;
                newNode->prevPtr = headPtr->prevPtr;
                headPtr = newNode;
                headPtr->prevPtr = tailPtr;
            }
            else
            {
                newNode->nextPtr = newNode->prevPtr = NULL;
                headPtr = newNode;
                headPtr->prevPtr = newNode;
            }
        }

        void pop()
        {
            if(!isEmpty())
            {
                Node *temp = headPtr;
                if(temp->nextPtr != NULL)
                {
                    Node *tailPtr = headPtr->prevPtr;
                    headPtr = headPtr->nextPtr;
                    headPtr->prevPtr = tailPtr;
                }
                else
                {
                    headPtr = NULL;
                }
                
                delete temp;
            }
        }

        void display()
        {
            Node *temp = headPtr;

            if(!isEmpty())
            {
                while(temp != NULL)
                {
                    // cout << "Current: " << temp->data << "\tprev: " << temp->prevPtr->data << endl;
                    cout << temp->data << '\t';
                    temp = temp->nextPtr;
                }
                cout << endl;
            }
        }

};
Stack<char>con;



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
 
}







string postfix;

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
          

        }
       
    }

}

void evalute();
// [12][3][8]*[3][4]/[2]-*+]
// [6][2][3]+-[3][8][2]/+*2^3+]


int main()
{
    string infix;
    
    cout << "\nEnter String: ";
    cin >> infix;
    infix = infix + ')';
    convert(infix);
    // 8+7^3*(4*2)-6
    // postfix = "[8][7][3]^[4][2]**+[6]-]";
    cout<<"\nThe converted equation is:  " << postfix << endl;

    evalute();


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
        if(postfix[i] == '[' )
        {
            bracketComplete = false;
            i++;
            while(!bracketComplete)
            {
                temp_str = temp_str + postfix[i++];
                if(postfix[i] == ']')
                    bracketComplete = true;
            }
            solution.push(stoi(temp_str));
            temp_str = "";
        }
       /* else if(postfix[i] == ']')
        {
            newNum = solution.top();
            solution.pop();

            cout << "Solution: " << newNum;
            break;
        }*/
        else
        {
            num1 = solution.top();
            solution.pop();

            num2 = solution.top();
            solution.pop();

            switch (postfix[i])
            {
            case '+':
                newNum = num2 + num1;
                solution.push(newNum);
                break;

            case '-':
                newNum = num2 - num1;
                solution.push(newNum);
                break;
            
            case '*':
                newNum = num2 * num1;
                solution.push(newNum);
                break;

            case '/':
                newNum = num2 / num1;
                solution.push(newNum);
                break;

            case '^':
                newNum = pow(num2, num1);
                solution.push(newNum);
                break;            
            
            default:
                break;
            }
        }
    }
    cout << "Solution: " << newNum;

    
}


