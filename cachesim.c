#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct rowDataA{
  char *headerName;
  char *charValue;
  int intValue;
  char *rowLine;
  struct rowDataA * next;
} rowData;
   
typedef struct a{
long int address;
int age;
int valid;
} makecache;

int main(int argc, char * argv[])
{
int csize = atoi(argv[1]);
char * assoc = argv[2];
char * prefet = argv[3];
//char * replace = argv[4];
int bsize = atoi(argv[5]);
//printf("%d %s %s %s %d\n", csize, assoc, prefet, replace, bsize);
//making the cache---------------------------------------------
long int calc1 = csize/bsize;
long int s;
long int a;
if (strcmp(assoc,"direct")==0)
{
a = 1;
s = calc1;
}
else if (strstr(assoc,"assoc:")!=NULL)
{
a = atoi((assoc+strlen(assoc)-1));
s = calc1/a;
}
else if (strcmp(assoc,"assoc")==0)
{
a = calc1;
s = 1;
}
//block size-------------------------------------------------
int blockoff =0;
int offtemp =bsize;
while (offtemp%2!=1)
{
offtemp/=2;
blockoff++;
}
int setoff =0;
int settemp =s;
while (settemp%2!=1)
{
settemp/=2;
setoff++;
}
//open file---------------------------------------------------
FILE * file = fopen(argv[6], "r");
char *counter;
counter = (char*)malloc(sizeof(char)*1000);
char rw;
long int address;
int asdf=0;
int counti=0;
int j;
//============================================================
makecache ** cache; 
cache=(makecache**)malloc(sizeof(makecache)*5000);
for (asdf=0; asdf<s;asdf++)
{
cache[asdf]=(makecache*)malloc(sizeof(makecache)*500);
}
for (asdf=0; asdf<s;asdf++)
{
  for(j=0; j<a;j++)
  {
    cache[asdf][j].valid=0;
    cache[asdf][j].address=-2;
  }
}
int memRead=0;
int memWrite=0;
int cacheHit=0;
int cacheMiss=0;
while (fscanf(file, "%s %c %lx", counter, &rw, &address)!=EOF)
{
int varCounter=0;
counti++;
if (strcmp(counter,"#eof")==0)
{
break;
}
//long int original= address;
long int prefadd=address+bsize;
long int tempaddress = (address >> blockoff);
int setIndex = tempaddress & ((1<<setoff)-1);
address = tempaddress>>setoff;
    long int preftempaddress = (prefadd >> blockoff);
    prefadd=prefadd>>(blockoff+setoff);
    int prefsetIndex = preftempaddress & ((1<<setoff)-1);
//printf("NEW PREF: %lx, add %lx, new %lx\n", original, address, prefadd);
//printf("set index: %d , prefsetIndex: %d \n", setIndex, prefsetIndex);
int i=0;
int missP=0; //determaxes if cache miss for prefetching
int missC=0;
if (rw=='W')//if write, this is always true
    {
    memWrite++;
    }

int smallest=0;
int counterVariable=0;
int min[2];
min[0] = cache[setIndex][0].age;//age
min[1]=0;//index number


for(asdf=1; asdf<a;asdf++)//calculate oldest tag
{
//fetchIndicator=0;
 if (min[0]>cache[setIndex][asdf].age)
 {
   min[0]=cache[setIndex][asdf].age;
   min[1]=asdf;
   smallest=min[1];
 }
}

for(i=0; i<a;i++)//Traverse cache lines
{
 if (cache[setIndex][i].valid==0)//1. Check for any invalid line
 {
   cache[setIndex][i].valid=1;//becomes valid
   cache[setIndex][i].address=address;
   cache[setIndex][i].age=counti;
   memRead++;
   cacheMiss++;
   missP++; 
   if (strcmp(prefet,"p1")==0)
    {
    for(j=0; j<a;j++)//check if the tag will hit
      {

     if (cache[prefsetIndex][j].valid==0) //1a. Check for any invalid line
        {
        counti++;
        cache[prefsetIndex][j].valid=1;//becomes valid
        cache[prefsetIndex][j].address=prefadd;
        cache[prefsetIndex][j].age=counti;
        memRead++;
        break;
        }
     else if (cache[prefsetIndex][j].address==prefadd)//2a. Check for hits
      {
      break; //Do nothing if 2a. true
      } 

      varCounter++;
    }//end of loop

    if (varCounter==a)//3a. Miss after searching through all cache lines, no invalid 
    {
    int smallest2=0;
    int min2[2];
min2[0]=cache[prefsetIndex][0].age;
min2[1]=0;
    for(asdf=1; asdf<a;asdf++)//calculate oldest tag
    {
//fetchIndicator=0;
     if (min2[0]>cache[prefsetIndex][asdf].age)
     {
     min2[0]=cache[prefsetIndex][asdf].age;
     min2[1]=asdf;
     smallest2=min2[1];
     }
    }
      //  printf("TYPE2\n");
    // printf("%d, %d, %lx\n", prefsetIndex, j,cache[prefsetIndex][j].address);
      counti++;
      cache[prefsetIndex][smallest2].address=prefadd;
      cache[prefsetIndex][smallest2].age=counti;  
      memRead++;
       //break; This cant break, this will break out of the outer while loop for each new address 
      }//no hit, load
    } //End of prefetch

  break;
}//End of 1. Check for any invalid line

  else if (cache[setIndex][i].valid==1 && cache[setIndex][i].address==address)
//2. Check for cache hits
  {
  cacheHit++;
  missC++;
  break;
  }//End of 2. Check for cache hits
counterVariable++;
}//End of scanning cache lines    
    
if (counterVariable==a)//3. Miss after searching through all cache lines, no invalid
  {
  cache[setIndex][smallest].address=address;
  cache[setIndex][smallest].age=counti;
  memRead++;
  cacheMiss++;
  if (strcmp(prefet,"p1")==0)
    {
    for(j=0; j<a;j++)//check if the tag will hit
    {
        if (cache[prefsetIndex][j].valid==0) //1a. Check for any invalid line
        {
        counti++;
        cache[prefsetIndex][j].valid=1;//becomes valid
        cache[prefsetIndex][j].address=prefadd;
        cache[prefsetIndex][j].age=counti;
        memRead++;
        break;
        }
        else if (cache[prefsetIndex][j].address==prefadd)//check if the tag will hit
        {
        break; //prefetched tag already exists
        }
      varCounter++;
      }//end of loop
         
    //}//end of fetch
    if (varCounter==a)//no invalids, load
      {
      int smallest2=0;
      int min2[2];
      min2[0]=cache[prefsetIndex][0].age;
      min2[1]=0;
      for(asdf=1; asdf<a;asdf++)//calculate oldest tag
      {
       if (min2[0]>cache[prefsetIndex][asdf].age)
       {
        min2[0]=cache[prefsetIndex][asdf].age;
       min2[1]=asdf;
       smallest2=min2[1];
       }
      }
      counti++;
      cache[prefsetIndex][smallest2].address=prefadd;
      cache[prefsetIndex][smallest2].age=counti;  
      memRead++;
       //cant break, this will break out of the outer while loop for each new address 
      }//no hit, load
    } //End of prefetch
}//End of miss 

}//End of reading new blocks
printf("Memory reads: %d\n", memRead);
printf("Memory writes: %d\n", memWrite);
printf("Cache hits: %d\n", cacheHit);
printf("Cache misses: %d\n", cacheMiss);
return 0;
}//end of main
