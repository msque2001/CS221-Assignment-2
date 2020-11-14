

#include <iostream>
using namespace std;





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
stack con;
void convert(string infix)
{
   
   
    bool check_bracket=true;
    for (int i = 0;infix[i] != '\0' ;i++)
    {
        
        if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^')
        {
            if (con.isEmpty())
            {
                check_bracket = true;
                postfix = postfix + "]";
                con.push(infix[i]);
            }
            else
            {
                check_bracket = true;
                postfix = postfix + "]";
                int count = 0;
                while (!con.isEmpty())
                {
                    char x = con.peek();

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
                char x = con.peek();
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



int main()
{
    string infix;
   
    cout << "\nEnter String: ";
    cin >> infix;
    infix = infix + ')';
  convert(infix);
  cout<<"\nThe converted equation is:  " << postfix;



   return 0;
}


