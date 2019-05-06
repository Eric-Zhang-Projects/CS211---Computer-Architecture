#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
int NOT(int input)
{
if (input==0)
{
return 1;
}
else{
return 0;
}
}

int AND(int in1, int in2)
{
if (in1==1 && in2 ==1)
{
return 1;
}

return 0;

}

int OR(int in1, int in2)
{

if (in1==1 ||in2==1)
{

return 1;
}

return 0;

}

int NAND(int in1, int in2)
{
return NOT(AND(in1,in2));
}

int NOR(int in1, int in2)
{
return NOT(OR(in1,in2));
}

int XOR(int in1, int in2)
{
if ((in1==1 && in2!=1) || (in1==!1 && in2==1))
{
return 1;
}
else{
return 0;
}
}

int* DECODER(int numberofInputs, int inputs[])
{
int j;

int *out=(int*)malloc(sizeof(int)*(1<<numberofInputs)*10);
int *in=(int*)malloc(sizeof(int)*numberofInputs);
for (j=0; j< numberofInputs; j++)
{
in[j]=inputs[j]; 
}
int i=0;


int decimalIn=0;
int temp=0;
int x=0;
for (i=numberofInputs-1; i>=0;i--)
{

temp=(1<<x) * in[i];
decimalIn=decimalIn+temp;
x++;
}
temp=0;
for (i=0; i < (1<<numberofInputs); i++)
{
out[i]=0;
}
out[decimalIn]=1;


return out;
}




int MULTIPLEXER(int numberofInputs, int inputs[])
{
//selector goes intobinary form
int j;

int total = numberofInputs + (1 << numberofInputs);

int leftIn[1<<numberofInputs];

int selectIn[numberofInputs];
int j1=0;
for (j=0; j< (1<< numberofInputs); j++)
{
leftIn[j1]=0;
if (inputs[j]==1)
{
leftIn[j1]=j; //stores decimal number in leftIn
j1++;
}
}
int i=0;

for(j=j;j< total;j++)
{
selectIn[i] = inputs[j];
i++;
}
int decimal=0;
int temp=0;
int x=0;
for (i=numberofInputs-1; i>=0;i--)
{

temp=(1<<x) * selectIn[i];
decimal=decimal+temp;
x++;
}

for (i=0;i<j1;i++)
{
if (decimal==leftIn[i])
{
return 1;
}
}
if (numberofInputs==1)
{
if (decimal==leftIn[i])
{
return 1;
}
}
return 0;
}

int PASS(input)
{
return input;
}

typedef struct firstListA{
  char * variableName;
  struct firstListA * next;
  } firstList;
  



int main(int argc, char * argv[])
{
char *line;
char * token;
int counter;
int lineNumber = 0;//checks if first 2 lines for input/output
int numberofInputs;
int numberofOutputs;
size_t linesize = 500;
line = (char*)malloc(sizeof(char)*linesize);

lineNumber=0;
FILE * f = fopen(argv[1], "r");
char * (*variableArray);//[numberofInputs+numberofOutputs+2]; all variables
char * (*copyArray); //input variables
char * *(gates);//stores gates
gates=(char**)malloc(sizeof(char)*5000);
char **outputArr;
int decMultN[5000];//stores decoder or multiplexer input number

int gateCounter=0;//gatecounter specific
int vIndex=0;
char * tok;
int decMultC=0;
while (fgets(line,linesize, f)!=NULL)//first read through of file, will store all variables into a linked list firstList
{
counter =1;
const char *delim="*[: ]\n\r\t";
token = strtok(line, delim);
while (token!=NULL)
{

if (strcmp(token, ":")==0) //ignore ':' character
{
token = strtok(NULL, delim);
counter++;
continue;
}
if (lineNumber <= 1 && counter<=2) //for first 2 lines start recording after 2nd 
{
token = strtok(NULL, delim);
if (strcmp(token, ":")==0) //ignore ':' character
{
token = strtok(NULL, delim);
counter++;
continue;
}
if (lineNumber==0)
{
numberofInputs = atoi(token);
variableArray = (char **)malloc(sizeof(char)*numberofInputs*1000);
variableArray[vIndex]="0";
vIndex++;
variableArray[vIndex]="1";
vIndex++;

}
else if (lineNumber==1)
{
numberofOutputs = atoi(token);
}
token = strtok(NULL, delim);
counter+=2;
}
if (strcmp(token, ":")==0) //ignore ':' character
{
token = strtok(NULL, delim);
counter++;
continue;
}

if (lineNumber >= 2 && counter <=1)//record from second; 
{
//copy inputs and outputs to another array, happens after input output lines only once
if (lineNumber==2 && counter==1)
{
copyArray=(char**)malloc(sizeof(variableArray)*100);
outputArr=(char**)malloc(sizeof(variableArray)*100);
int a;
int aaa=0;
for (a=0; a<numberofInputs+numberofOutputs+2;a++)
{
if (a>=numberofInputs+2)
{
outputArr[aaa]=variableArray[a];
aaa++;
}
copyArray[a] = variableArray[a];
}

}
if (lineNumber >= 2 && counter ==1)
{
tok= strdup(token);
gates[gateCounter]=tok;
//printf("%s\n", gates[gateCounter]);
gateCounter++;
//----------------------------------------------------------- GATE INFORMATION
}
if (strcmp(gates[gateCounter-1],"MULTIPLEXER")==0 || strcmp(gates[gateCounter-1],"DECODER")==0 )//if multi or decoder
{
token = strtok(NULL, delim);
counter++;
tok = strdup(token);
decMultN[decMultC] = atoi(tok);
decMultC++;
}//end of if multi or decoder if 
//all other gates

token = strtok(NULL, delim);
if (strcmp(token, ":")==0) //ignore ':' character
{
token = strtok(NULL, delim);
counter++;
continue;
}
counter++;

}
tok = strdup(token);
variableArray[vIndex]=tok;
vIndex++;
token = strtok(NULL, delim);
counter++;//character number in a line
}//end of token while hloop

lineNumber++;//indicates next line to be read
}//end of reading file while loop

int j;
int k;
int variableRep=2;
int compareArr[vIndex+1];//array of binary values corresponding to each variable
int nodeCounter=0;
compareArr[0]=0;
compareArr[1]=1;
firstList * head=NULL;
firstList * temp;
firstList * curr;
firstList * ptr;
for (j=2; j<vIndex;j++)//fill cmparearray with negative number
{
compareArr[j]=-1;
}
for (k=2; k<numberofInputs+numberofOutputs+2; k++)
{
  for (j = 2; j <vIndex; j++)
  {
  if (strcmp(copyArray[k],variableArray[j])==0)
  {
  compareArr[j] = variableRep;
    }
    else if (strcmp(variableArray[j],"1")==0||strcmp(variableArray[j],"0")==0)
    {
    compareArr[j]=atoi(variableArray[j]);
    }
    }
  variableRep++;
}//end of variable representation as numbers

for (j=2; j<vIndex;j++)//make a linked list of temporary variables by finding where -1 is and storing that variable name in that index into list
{
if (compareArr[j]==-1)
{
if (head==NULL)
     {
   //  printf("1\n");
     head=(firstList*)malloc(sizeof(char)*100);
     head->variableName=variableArray[j];
     head->next=NULL;
     temp = head;
     curr=head;
     nodeCounter++;
     }
     else{
     temp=(firstList*)malloc(sizeof(char)*100);
     temp->variableName = variableArray[j];
     temp->next=NULL;
     curr->next=temp;
     curr=temp;
     nodeCounter++;

     }
}
}

ptr=head;
char * (*linkedList);
linkedList = (char**)malloc(sizeof(char)*nodeCounter*50);
int linkedListNum[nodeCounter];
int k1 = 0;
while(ptr!=NULL)//stores linked list variable names into array
{
linkedList[k1]=ptr->variableName;
linkedListNum[k1]=0;
ptr=ptr->next;
k1++;
}

//truth table generation:
int rows = 1 << numberofInputs;
int a;
int b;
int i;
int tempC=0; //temporary for loop counter for generating table
 //how many zeros needed
int tempC2=0; //temporary for reversing array order
int tempC3=0;//numberofInputs-1; //temporary for above
int array[numberofInputs];
int table1[vIndex];
int output;
for (j=0;j<vIndex;j++)
{
table1[j]=compareArr[j];
}

int rowa=0;

for(a = 0; a<rows;a++)
{

i=0;
rowa=a;
while(rowa>0)
{
array[i]=rowa%2;
rowa=rowa/2;
i++;
}
for (b=i; b<numberofInputs; b++)
{
array[b]=0;
}
tempC2=0;
tempC3=numberofInputs-1;
while (tempC2 < tempC3) //reverse array
 { 
 int temp = array[tempC2];  
 array[tempC2] = array[tempC3]; 
 array[tempC3] = temp; 
 tempC2++; 
 tempC3--; 
 }  
for (b=0; b<numberofInputs; b++)
{
printf("%d ", array[b]);
}
printf("|");
//BEFORE THIS IS COMMAND printf("| ");
//--------------------------------------------------------------------
//begin table run through
for (tempC=0; tempC<numberofInputs;tempC++)//replaces all variables with input numbers
{
for (j=tempC+2; j<vIndex-1; j++)
{
if (compareArr[tempC+2]==compareArr[j+1])
{
table1[j+1]=array[tempC];
}
}
table1[tempC+2]=array[tempC];
}//end of for loop that assigns inputs to variables=----------------------

int outCounter=0;
int currentLLN=0; //linked list num counter
int currentLLN2=0;
int outputCounter=0;
int outputArray[numberofOutputs];
char**outputArrayOrder;
outputArrayOrder=(char**)malloc(sizeof(char)*numberofOutputs*1000);
//int numberofRows=0;
int table[vIndex];
decMultC=0;
for (outCounter=0; outCounter<vIndex;outCounter++)
{
table[outCounter]=table1[outCounter];
}
j= numberofInputs+numberofOutputs+2;
for (tempC=0; tempC<gateCounter;tempC++)
{//size of gate array

if (strcmp(gates[tempC],"AND")==0)
{
output=j+2;
if (table[output]==-1)
{
if (table[j]==-1)
{
table[j] = linkedListNum[currentLLN];
currentLLN++;
}
if (table[j+1]==-1)
{
table[j+1] = linkedListNum[currentLLN];
currentLLN++;
}
table[output]=AND(table[j],table[j+1]);
  for (currentLLN2=currentLLN+1; currentLLN2<nodeCounter;currentLLN2++)
  {
  if (strcmp(linkedList[currentLLN], linkedList[currentLLN2])==0)
  {
  linkedListNum[currentLLN2]=table[output];
  }
  }
linkedListNum[currentLLN]=table[output];
currentLLN++;
}
else if (table[output]!=-1 && table[output]!=0 && table[output]!=1)//output variable
{
if (table[j]==-1)
{
table[j] = linkedListNum[currentLLN];
currentLLN++;
}
if (table[j+1]==-1)
{
table[j+1] = linkedListNum[currentLLN];
currentLLN++;
}
table[output]=AND(table[j],table[j+1]);
outputArray[outputCounter]=table[output];
outputArrayOrder[outputCounter]=variableArray[output];
outputCounter++;
}
j+=3;
}//end of AND



if (strcmp(gates[tempC],"OR")==0)
{

output=j+2;

if (table[output]==-1)
{
if (table[j]==-1)
{
table[j] = linkedListNum[currentLLN];
currentLLN++;
}
if (table[j+1]==-1)
{
table[j+1] = linkedListNum[currentLLN];
currentLLN++;
}

table[output]=OR(table[j],table[j+1]);
  for (currentLLN2=currentLLN+1; currentLLN2<nodeCounter;currentLLN2++)
  {

  if (strcmp(linkedList[currentLLN], linkedList[currentLLN2])==0)
  {
    
  linkedListNum[currentLLN2]=table[output];
  }

  }
linkedListNum[currentLLN]=table[output];

currentLLN++;
}

if (table[output]!=-1 && table[output]!=0 && table[output]!=1)//output variable
{
if (table[j]==-1)
{
table[j] = linkedListNum[currentLLN];
currentLLN++;
}
if (table[j+1]==-1)
{
table[j+1] = linkedListNum[currentLLN];
currentLLN++;
}
table[output]=OR(table[j],table[j+1]);
outputArray[outputCounter]=table[output];
outputArrayOrder[outputCounter]=variableArray[output];
outputCounter++;
}
j+=3;

}//end of OR


if (strcmp(gates[tempC],"NAND")==0)
{
output=j+2;
if (table[output]==-1)
{
if (table[j]==-1)
{
table[j] = linkedListNum[currentLLN];
currentLLN++;
}
if (table[j+1]==-1)
{
table[j+1] = linkedListNum[currentLLN];
currentLLN++;
}
table[output]=NAND(table[j],table[j+1]);
  for (currentLLN2=currentLLN+1; currentLLN2<nodeCounter;currentLLN2++)
  {
  if (strcmp(linkedList[currentLLN], linkedList[currentLLN2])==0)
  {
  linkedListNum[currentLLN2]=table[output];
  }
  }
linkedListNum[currentLLN]=table[output];
currentLLN++;
}

else if (table[output]!=-1 && table[output]!=0 && table[output]!=1)//output variable
{
if (table[j]==-1)
{
table[j] = linkedListNum[currentLLN];
currentLLN++;
}
if (table[j+1]==-1)
{
table[j+1] = linkedListNum[currentLLN];
currentLLN++;
}
table[output]=NAND(table[j],table[j+1]);
outputArray[outputCounter]=table[output];
outputArrayOrder[outputCounter]=variableArray[output];
outputCounter++;
}
j+=3;
}//end of NAND




if (strcmp(gates[tempC],"NOR")==0)
{
output=j+2;
if (table[output]==-1)
{
if (table[j]==-1)
{
table[j] = linkedListNum[currentLLN];
currentLLN++;
}
if (table[j+1]==-1)
{
table[j+1] = linkedListNum[currentLLN];
currentLLN++;
}

table[output]=NOR(table[j],table[j+1]);
  for (currentLLN2=currentLLN+1; currentLLN2<nodeCounter;currentLLN2++)
  {
  if (strcmp(linkedList[currentLLN], linkedList[currentLLN2])==0)
  {
  linkedListNum[currentLLN2]=table[output];
  }
  }
linkedListNum[currentLLN]=table[output];
currentLLN++;
}
else if (table[output]!=-1 && table[output]!=0 && table[output]!=1)//output variable
{
if (table[j]==-1)
{
table[j] = linkedListNum[currentLLN];
currentLLN++;
}
if (table[j+1]==-1)
{
table[j+1] = linkedListNum[currentLLN];
currentLLN++;
}
table[output]=NOR(table[j],table[j+1]);
outputArray[outputCounter]=table[output];
outputArrayOrder[outputCounter]=variableArray[output];
outputCounter++;
}
j+=3;
}//end of NOR


if (strcmp(gates[tempC],"XOR")==0)
{
output=j+2;
if (table[output]==-1)
{
if (table[j]==-1)
{
table[j] = linkedListNum[currentLLN];
currentLLN++;
}
if (table[j+1]==-1)
{
table[j+1] = linkedListNum[currentLLN];
currentLLN++;
}
table[output]=XOR(table[j],table[j+1]);
  for (currentLLN2=currentLLN+1; currentLLN2<nodeCounter;currentLLN2++)
  {
  if (strcmp(linkedList[currentLLN], linkedList[currentLLN2])==0)
  {
  linkedListNum[currentLLN2]=table[output];
  }
  }
linkedListNum[currentLLN]=table[output];
currentLLN++;
}
else if (table[output]!=-1 && table[output]!=0 && table[output]!=1)//output variable
{
if (table[j]==-1)
{
table[j] = linkedListNum[currentLLN];
currentLLN++;
}
if (table[j+1]==-1)
{
table[j+1] = linkedListNum[currentLLN];
currentLLN++;
}
table[output]=XOR(table[j],table[j+1]);
outputArray[outputCounter]=table[output];
outputArrayOrder[outputCounter]=variableArray[output];
outputCounter++;
}
j+=3;
}//end of XOR


if (strcmp(gates[tempC],"NOT")==0)
{
output=j+1;
if (table[output]==-1)
{
if (table[j]==-1)
{
table[j] = linkedListNum[currentLLN];
currentLLN++;
}
table[output]=NOT(table[j]);
  for (currentLLN2=currentLLN+1; currentLLN2<nodeCounter;currentLLN2++)
  {
  if (strcmp(linkedList[currentLLN], linkedList[currentLLN2])==0)
  {
  linkedListNum[currentLLN2]=table[output];
  }
  }
linkedListNum[currentLLN]=table[output];
currentLLN++;
}

else if (table[output]!=-1 && table[output]!=0 && table[output]!=1)//output variable
{
if (table[j]==-1)
{
table[j] = linkedListNum[currentLLN];
currentLLN++;
}
table[output]=NOT(table[j]);
outputArray[outputCounter]=table[output];
outputArrayOrder[outputCounter]=variableArray[output];
outputCounter++;
}

j+=2;
}//end of NOT


if (strcmp(gates[tempC],"PASS")==0)
{
output=j+1;
if (table[output]==-1)
{
if (table[j]==-1)
{
table[j] = linkedListNum[currentLLN];
currentLLN++;
}
table[output]=PASS(table[j]);
  for (currentLLN2=currentLLN+1; currentLLN2<nodeCounter;currentLLN2++)
  {
  if (strcmp(linkedList[currentLLN], linkedList[currentLLN2])==0)
  {
  linkedListNum[currentLLN2]=table[output];
  }
  }
linkedListNum[currentLLN]=table[output];
currentLLN++;
}

else if (table[output]!=-1 && table[output]!=0 && table[output]!=1)//output variable
{
if (table[j]==-1)
{
table[j] = linkedListNum[currentLLN];
currentLLN++;
}
table[output]=PASS(table[j]);
outputArray[outputCounter]=table[output];
outputArrayOrder[outputCounter]=variableArray[output];
outputCounter++;
}

j+=2;
}//end of PASS


if (strcmp(gates[tempC],"MULTIPLEXER")==0)
{


int tempMultCounter=0;

output=j + decMultN[decMultC]+(1 << decMultN[decMultC]);

int jUp=0;
int multiplexerArgs[decMultN[decMultC]+(1 << decMultN[decMultC])+1];
int argsC=0;
if (table[output]==-1)
{
for (tempMultCounter=j; tempMultCounter<output;tempMultCounter++)
{
if (table[tempMultCounter]==-1)
{
table[j+jUp] = linkedListNum[currentLLN];
currentLLN++;
}
multiplexerArgs[argsC]=table[tempMultCounter];
argsC++;
jUp++;
}
table[output]=MULTIPLEXER(decMultN[decMultC], multiplexerArgs);
  for (currentLLN2=currentLLN+1; currentLLN2<nodeCounter;currentLLN2++)
  {
  
  if (strcmp(linkedList[currentLLN], linkedList[currentLLN2])==0)
  {
  linkedListNum[currentLLN2]=table[output];
  }
  }
linkedListNum[currentLLN]=table[output];
currentLLN++;
}

else if (table[output]!=-1 && table[output]!=0 && table[output]!=1)//output variable
{
jUp=0;
for (tempMultCounter=j; tempMultCounter<output;tempMultCounter++)
{
if (table[tempMultCounter]==-1)
{
table[j+jUp] = linkedListNum[currentLLN];
currentLLN++;
}
multiplexerArgs[argsC]=table[tempMultCounter];

argsC++;
jUp++;
}

table[output]=MULTIPLEXER(decMultN[decMultC], multiplexerArgs);
outputArray[outputCounter]=table[output];
outputArrayOrder[outputCounter]=variableArray[output];
outputCounter++;
}

j+=decMultN[decMultC]+(1 << decMultN[decMultC])+1;
decMultC++;
}//end of MULTIPLEXER


if (strcmp(gates[tempC],"DECODER")==0)
{
int tempMultCounter=0;
output=j + decMultN[decMultC];
int multiplexerArgs[decMultN[decMultC]];
int argsC=0;
int jUp=0;
if (table[output]==-1)
{
for (tempMultCounter=j; tempMultCounter<output;tempMultCounter++)
{
if (table[tempMultCounter]==-1)
{
table[j+jUp] = linkedListNum[currentLLN];
currentLLN++;
}
multiplexerArgs[argsC]=table[tempMultCounter];
argsC++;
jUp++;
}
int* decOut= DECODER(decMultN[decMultC], multiplexerArgs);
int decOutC=0;
int output1=output;
int tempOutUpperLimit = (output1+(1 << decMultN[decMultC]));
for (output = output1; output<tempOutUpperLimit;output++)
{
table[output] = decOut[decOutC];
  for (currentLLN2=currentLLN+1; currentLLN2<nodeCounter;currentLLN2++)
  {
  if (strcmp(linkedList[currentLLN], linkedList[currentLLN2])==0)
  {
  linkedListNum[currentLLN2]=table[output];
  }
  }
linkedListNum[currentLLN]=table[output];
currentLLN++;
decOutC++;
}
}

else if (table[output]!=-1 && table[output]!=0 && table[output]!=1)//output variable
{
for (tempMultCounter=j; tempMultCounter<output;tempMultCounter++)
{
if (table[tempMultCounter]==-1)
{
table[j+jUp] = linkedListNum[currentLLN];
currentLLN++;
}
multiplexerArgs[argsC]=table[tempMultCounter];

argsC++;
jUp++;
}

int* decOut= DECODER(decMultN[decMultC], multiplexerArgs);
int decOutC=0;
int output1=output;
int tempOutUpperLimit = (output1+(1 << decMultN[decMultC]));
for (output = output1; output<tempOutUpperLimit;output++)
{
table[output] = decOut[decOutC];
outputArray[outputCounter]=table[output];
outputArrayOrder[outputCounter]=variableArray[output];
outputCounter++;
decOutC++;
}

}

j+=decMultN[decMultC]+(1 << decMultN[decMultC]);
decMultC++;
}//end of decoder


}//end of loop traversing each gate 

int outCounter2;

for (outCounter=0; outCounter<outputCounter; outCounter++)
{
for (outCounter2=0; outCounter2<outputCounter; outCounter2++)
{
if(strcmp(outputArr[outCounter],outputArrayOrder[outCounter2])==0)
{
printf(" %d", outputArray[outCounter2]);
}
}
}
printf("\n");


}//END OF TABLE GENERATION LOOP(OUTER)


free(line);
free(gates);
free(variableArray);
free(copyArray);
free(outputArr);
free(head);
free(linkedList);

return 0 ; 
}//end of main
