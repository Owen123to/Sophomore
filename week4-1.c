#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct Node_double
{
    double data;
    struct Node_double *prev, *next;
} Node_double;
typedef struct Node_char
{
    char data;
    struct Node_char *prev, *next;
} Node_char;
void DinitLinkList(Node_double **head)
{
    (*head) = NULL;
}
void CinitLinkList(Node_char **head)
{
    (*head) = NULL;
}
void DoubleaddToHead(Node_double **head, double data)
{
    Node_double  *newNode = malloc(sizeof(Node_double));
    newNode->data = data;
    newNode->prev = NULL;
    if(*head == NULL)
    {
        newNode->next = NULL;
        *head = newNode;
        return ;
    }
    (*head)->prev = newNode;
    newNode->next = *head;
    *head = newNode;
}
void CharaddToHead(Node_char **head, char data)
{
    Node_char *newNode = malloc(sizeof(Node_char));
    newNode->data = data;
    newNode->prev = NULL;
    if(*head == NULL)
    {
        newNode->next = NULL;
        *head = newNode;
        return ;
    }
    (*head)->prev = newNode;
    newNode->next = *head;
    *head = newNode;
}
void CharaddToTail(Node_char **head, char data)
{
    Node_char *newNode = malloc(sizeof(Node_char));
    newNode->data = data;
    newNode->next = NULL;
    if(*head == NULL)
    {
        *head = newNode;
        newNode->prev = NULL;
        return;
    }
    Node_char *temp = *head;
    while(temp->next!=NULL)
        temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
    return ;
}
void DoubleaddToTail(Node_double **head, double data)
{
    Node_double *newNode = malloc(sizeof(Node_double));
    newNode->data = data;
    newNode->next = NULL;
    if(*head == NULL)
    {
        *head = newNode;
        newNode->prev = NULL;
        return;
    }
    Node_double *temp = *head;
    while(temp->next!=NULL)
        temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
    return ;
}
void ChardeleteData(Node_char **head, char data)
{
    Node_char *temp = *head;
    if(temp == NULL)
        return;
    if(temp->prev == NULL && temp->next == NULL)
        *head = NULL;
    while(temp->data!=data)
    {
        if(temp->next == NULL&&temp->data!=data)
            return ;
        temp = temp->next;
    }
    if(temp->prev == NULL && temp->next!=NULL)
    {
        temp->next->prev = NULL;
        (*head) = temp->next;
        temp->next = NULL;
    }
    else if(temp->prev!=NULL && temp->next == NULL)
    {
        temp->prev->next = NULL;
        temp->prev = NULL;
    }
    else if(temp->prev!=NULL && temp->next!=NULL)
    {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        temp->next = NULL;
        temp->prev = NULL;
    }
    free(temp);
    return ;
}
void DoubledeleteData(Node_double **head, double data)
{
    Node_double *temp = *head;
    if(temp == NULL)
        return;
    if(temp->prev == NULL && temp->next == NULL)
        *head = NULL;
    while(temp->data!=data)
    {
        if(temp->next == NULL&&temp->data!=data)
            return ;
        temp = temp->next;
    }
    if(temp->prev == NULL && temp->next!=NULL)
    {
        temp->next->prev = NULL;
        (*head) = temp->next;
        temp->next = NULL;
    }
    else if(temp->prev!=NULL && temp->next == NULL)
    {
        temp->prev->next = NULL;
        temp->prev = NULL;
    }
    else if(temp->prev!=NULL && temp->next!=NULL)
    {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        temp->next = NULL;
        temp->prev = NULL;
    }
    free(temp);
    return ;
}
void ChardeleteDatas(Node_char **head, char data, int n)
{
    while(n--)
        ChardeleteData(head,data);
}
void DoubledeleteDatas(Node_double **head, double data, int n)
{
    while(n--)
        DoubledeleteData(head,data);
}
void Chardisplay(Node_char *head)
{
    if(head == NULL)
        return ;
    printf("(");
    Node_char *temp = head;
    while(1)
    {
        if(temp->next == NULL)
        {
            printf("%c)",temp->data);
            printf("\n");
            return;
        }
        else
        {
            printf("%c, ",temp->data);
            temp = temp->next;
        }
    }
}
void Doubledisplay(Node_double *head)
{
    if(head == NULL)
        return ;
    printf("(");
    Node_double *temp = head;
    while(1)
    {
        if(temp->next == NULL)
        {
            printf("%f)",temp->data);
            printf("\n");
            return;
        }
        else
        {
            printf("%f, ",temp->data);
            temp = temp->next;
        }
    }
}
void Charpush(Node_char **stack, char data)
{
    CharaddToTail(stack,data);
}
void Doublepush(Node_double **stack, double data)
{
    DoubleaddToTail(stack,data);
}
char Charpop(Node_char **stack)
{
    if(*stack == NULL)
        return ;
    Node_char *temp = *stack;
    while(temp->next!=NULL)
        temp = temp->next;
    if(temp->prev == NULL)
        *stack = NULL;
    if(temp->prev!=NULL)
    {
        temp->prev->next = NULL;
        temp->prev = NULL;
    }
    return temp->data;
}
double Doublepop(Node_double **stack)
{
    if(*stack == NULL)
        return ;
    Node_double *temp = *stack;
    while(temp->next!=NULL)
        temp = temp->next;
    if(temp->prev == NULL)
        *stack = NULL;
    if(temp->prev!=NULL)
    {
        temp->prev->next = NULL;
        temp->prev = NULL;
    }
    return temp->data;
}
char Chartop(Node_char *stack)
{
    Node_char *temp = stack;
    while(temp->next!=NULL)
        temp = temp->next;
    return temp->data;
}
double Doubletop(Node_double *stack)
{
    Node_double *temp = stack;
    while(temp->next!=NULL)
        temp = temp->next;
    return temp->data;
}
int  CharisEmpty(Node_char *stack)
{
    if(stack == NULL)
        return 1;
    return 0;
}
int DoubleisEmpty(Node_double *stack)
{
    if(stack == NULL)
        return 1;
    return 0;
}
int Charsize(Node_char *stack)
{
    Node_char *temp = stack;
    int i = 0;
    while(temp!=NULL)
    {
        i++;
        temp = temp->next;
    }
    return i;
}
int Doublesize(Node_double *stack)
{
    Node_double *temp = stack;
    int i = 0;
    while(temp!=NULL)
    {
        i++;
        temp = temp->next;
    }
    return i;
}
int first = 0;
int  decide(char a,char b,char c)
{
    if(b == '+'||b=='*'||b=='/'||b=='^')
    {
        if(a=='-'||a==')'||isdigit(a))
            if(c=='-'||c=='('||isdigit(c))
                return 0;
        return 1;
    }
    else if(b=='-')
    {
        if(a==' '||c==' '||c=='\0')
            return 1;
        return 0;
    }
    else if(b=='(')
    {
        if(a==' '||isdigit(a))
            return 1;
        if(isdigit(c)||c=='('||c==')'||c=='-')
            return 0;
        return 1;
    }
    else
    {
        if(isdigit(a)||a=='('||a==')')
            if(c!=' '&&!isdigit(c))
                return 0;
        return 1;
    }
}
char input[999];
int err_exp()
{
    for(int i = 0; i<strlen(input); i++)
    {
        if(input[i] == '+'||input[i]=='-'||input[i]=='*'||input[i]=='/'||input[i]=='^'||input[i]=='('||input[i]==')')
        {
            if(decide(input[i-1],input[i],input[i+1]))
            {
                printf("ERROR\n");
                return 1;
            }
        }
    }
    int count1 =0;
    for(int i = 0; i<strlen(input); i++)
    {
        if(input[i] == '(')
            count1++;
        else if(input[i]==')')
            count1--;
    }
    if(count1!=0)
    {
        printf("ERROR\n");
        return 1;
    }
    return 0;
}
int get_operator(char ch)
{
    if(ch == '+' || ch == '-')
        return 1;
    if(ch == '*' || ch == '/')
        return 2;
    if(ch == '^')
        return 3;
    else return 0;
}
double B_round(double ee)
{
    return (double)(lrint(ee*100)/100.0);
}
int main()
{
    while((scanf("%s",&input)!=EOF))
    {
        first = 0;
        if(err_exp())
            continue;
        //change_impression
        char temp2[999] = {};
        char temp3[999] = {};
        for(int i = 0; input[i] != '\0'; i++)
        {
            if(input[i] == '-'&&input[i+1] == '-'&&input[i+2] == '-')
            {
                for(int j = 0;j<999; j++)
                {
                    if(temp3[j]=='\0')
                    {
                        temp3[j] = '+';
                        temp3[j+1] = '0';
                        temp3[j+2] = '\0';
                        break;
                    }
                }
                i = i+1;
            }
            else if(input[i]==')'&&input[i+1] == '-'&&isdigit(input[i+2]))
            {
                for(int j = 0; j<999; j++)
                {
                    if(temp3[j]=='\0')
                    {
                        temp3[j] = input[i];
                        temp3[j+1] = '+';
                        temp3[j+2] = '0';
                        temp3[j+3] = '\0';
                        break;
                    }
                }
            }
            else
            {
                for(int j = 0; j<999; j++)
                {
                    if(temp3[j]=='\0')
                    {
                        temp3[j] = input[i];
                        temp3[j+1] = '\0';
                        break;
                    }
                }
            }
        }
        Node_char *stack1;
        CinitLinkList(&stack1);
        for(first = 0; temp3[first]!='\0'; first++)
        {
            if(temp3[first] == '(')
            {
                Charpush(&stack1,temp3[first]);
            }
            else if(temp3[first] == ')')
            {
                while(Chartop(stack1)!='(')
                {
                    for(int j = 0; j<999; j++)
                    {
                        if(temp2[j] == '\0')
                        {
                            temp2[j] = Charpop(&stack1);
                            temp2[j+1] = ' ';
                            temp2[j+2] = '\0';
                            break;
                        }
                    }
                }
                Charpop(&stack1);
            }
            else if(temp3[first] == '-'&&isdigit(temp3[first+1])&&!isdigit(temp3[first-1]))
            {
                for(int j =0; j<999; j++)
                {
                    if(temp2[j] == '\0')
                    {
                        temp2[j] = temp3[first];
                        j++;
                        for(int k =first+1; k<999; k++)
                        {
                            if(temp3[k]>='0'&&temp3[k]<='9'||temp3[k] == '.')
                            {
                                temp2[j] = temp3[k];
                                j++;
                                if(k == 998)
                                    first = k;
                            }
                            else if(temp3[k]<='0'||temp3[k]>='9'||temp3[k]!='.')
                            {
                                first = k-1;
                                break;
                            }
                        }
                        temp2[j] = ' ';
                        temp2[j+1] = '\0';
                        break;
                    }
                }
            }
            else if(temp3[first] == '+' || temp3[first] == '-' || temp3[first] == '*' || temp3[first] == '/' || temp3[first] == '^')
            {
                if(CharisEmpty(stack1))
                {
                    Charpush(&stack1,temp3[first]);
                }
                else
                {
                    if(get_operator(Chartop(stack1))>=get_operator(temp3[first]))
                    {
                        for(int j = 0; j<999; j++)
                        {
                            if(temp2[j] == '\0')
                            {
                                temp2[j] = Charpop(&stack1);
                                temp2[j+1] = ' ';
                                temp2[j+2] = '\0';
                                break;
                            }
                        }
                        Charpush(&stack1,temp3[first]);
                    }
                    else
                    {
                        Charpush(&stack1,temp3[first]);
                    }
                }
            }
            else
            {
                for(int j =0; j<999; j++)
                {
                    if(temp2[j] == '\0')
                    {
                        temp2[j] = temp3[first];
                        j++;
                        for(int k =first+1; k<999; k++)
                        {
                            if(temp3[k]>='0'&&temp3[k]<='9'||temp3[k] == '.')
                            {
                                temp2[j] = temp3[k];
                                j++;
                                if(k == 998)
                                    first = k;
                            }
                            else if(temp3[k]<='0'||temp3[k]>='9'||temp3[k]!='.')
                            {
                                first = k-1;
                                break;
                            }
                        }
                        temp2[j] = ' ';
                        temp2[j+1] = '\0';
                        break;
                    }
                }
            }
        }
        if(!CharisEmpty(stack1))
        {
            while(!CharisEmpty(stack1))
            {
                for(int j= 0; j<999; j++)
                {
                    if(temp2[j] == '\0')
                    {
                        temp2[j] = Charpop(&stack1);
                        temp2[j+1] = ' ';
                        temp2[j+2] = '\0';
                        break;
                    }
                }
            }
        }
        free(stack1);
        //evalue
        Node_double *eve;
        DinitLinkList(&eve);
        for(first = 0; first<strlen(temp2); first++)
        {
            if((temp2[first]>='0'&&temp2[first]<='9')||(temp2[first] == '-'&&isdigit(temp2[first+1])&&!isdigit(temp2[first-1])))
            {
                char temp5[999] = {};
                for(int j =0; j<999; j++)
                {
                    if(temp5[j] == '\0')
                    {
                        temp5[j] = temp2[first];
                        j++;
                        for(int k =first+1; k<999; k++)
                        {
                            if(temp2[k]>='0'&&temp2[k]<='9'||temp2[k] == '.')
                            {
                                temp5[j] = temp2[k];
                                j++;
                                if(k == 998)
                                    first = k;
                            }
                            else if(temp2[k]<='0'||temp2[k]>='9'||temp2[k]!='.')
                            {
                                first = k-1;
                                break;
                            }
                        }
                        temp5[j] = ' ';
                        temp5[j+1] = '\0';
                        break;
                    }
                }
                Doublepush(&eve,atof(temp5));
            }
            else if(temp2[first]!=' ')
            {
                double en1 = Doublepop(&eve);
                double en2 = Doublepop(&eve);
                switch(temp2[first])
                {
                case'+' :
                    Doublepush(&eve,B_round(en2+en1));
                    break;
                case'-' :
                    Doublepush(&eve,B_round(en2-en1));
                    break;
                case'*' :
                    Doublepush(&eve,B_round(en2*en1));
                    break;
                case'/' :
                    Doublepush(&eve,B_round(en2/en1));
                    break;
                case'^' :
                    Doublepush(&eve,B_round(pow(en2,en1)));
                    break;
                }
            }
        }
        printf("%.2f\n",Doubletop(eve));
        free(eve);
    }
    return 0;
}
