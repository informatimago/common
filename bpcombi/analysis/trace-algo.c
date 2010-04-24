#include <stdio.h>


typedef enum { false,true } bool;

static int   N;
static int   n;
static bool* taken; /*N*/
static int*  choice;/*n*/
static bool  done;

    void uplet(int k)
    {
        int i;
        printf("%*s    +++ choice= ",(k+1)*4,"",k);
        for(i=0;i<n;i++){
            printf("%d ",choice[i]);
        }
        printf("\n%*s    taken= ",(k+1)*4,"");
        for(i=0;i<N;i++){
            printf(" (%d: %s)",i,taken[i]?"taken":"free ");
        }
        printf("\n");
    }/*uplet*/


    void init_r(void)
    {
        int i;
        for(i=0;i<N;i++){
            taken[i]=false;
        }
    }/*init*/


    void block_r(int k)
    {
        // state_0
        if(k<n){
            choice[k]=0;
            while(choice[k]<N){
                // state_1
                if(!taken[choice[k]]){
                    // state_3
                    taken[choice[k]]=true;
                    block_r(k+1);
                    // state_5
                    taken[choice[k]]=false;
                }
                // state_2
                choice[k]++;
            }
        }else{
            uplet(k);
        }
    }/*block_r*/



    void init_i(void)
    {
        int i;
        for(i=0;i<N;i++){
            taken[i]=false;
        }
        done=false;
    }/*init_i*/

    
#define transition(guard,action,state) if(guard){ do{ action }while(0); goto state; }
// #define transition(guard,action,state) if(guard){ \
//      printf("   [ %-30s ] / %-30s --> %-30s\n",#guard,#action,#state); \
//      do{ action }while(0); goto state; }

    void next_i(int k)
    {
printf("next_i(%d)\n",k);
        state_0:
            transition( (k<n),                   {choice[k]=0;},    state_1)
            transition(!(k<n),                   {k=n-1;},          state_5)

        state_1:
            transition( (taken[choice[k]]),      {},                state_2)
            transition(!(taken[choice[k]]),      {},                state_3)

        state_2:
            choice[k]++;
            transition( (choice[k]<N),           {},                state_1);
            transition((!(choice[k]<N))&&(k==0), {done=true;},      terminate);
            transition((!(choice[k]<N))&&(k!=0), {k--;},            state_5);

        state_3:
            taken[choice[k]]=true;
            transition( (k<n-1),                 {k++;},            state_0);
            transition(!(k<n-1),                 {uplet(k);},       terminate);

        state_5:
            taken[choice[k]]=false;
            transition(true,                     {},                state_2);

        terminate:

    }/*next_i*/



int main(int argc,char** argv)
{
    int i=1;
    if(argc<3){
        n=2;
        N=3;
    }else{
        sscanf(argv[i++],"%d",&n);
        sscanf(argv[i++],"%d",&N);
        if(!((0<n)&&(n<=N))){
            fprintf(stderr,"Invalid parameters n=%d N=%d\n",n,N);
            exit(1);
        }
    }
    taken=(bool*)malloc(sizeof(bool)*N);
    choice=(int*)malloc(sizeof(int)*n);
    if((i<argc)&&(strcmp(argv[i],"recursive")==0)){
        init_r(); block_r(0);
    }else{
        init_i(); next_i(0); while(!done){ next_i(n); }
    }
    return(0);
}/*main*/
