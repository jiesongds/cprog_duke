#include <stdio.h>
#include <stdlib.h>


struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info; 

void retirement (int startAge,
		 double initial,
		 retire_info working,
		 retire_info retired){
  double balance;
  int curr_age = startAge / 12;
  printf("%d", curr_age);
  balance = initial;
  int curr_mon = startAge % 12;
  
  for (int i=0; i<working.months; i++){
    printf("Age %3d month %2d you have $%.2f\n", curr_age, curr_mon, balance);
    balance = balance * (1 + working.rate_of_return / 12);
    balance = balance + working.contribution;
    if (curr_mon == 11){
      curr_age++;
      curr_mon = 0;
    }
    else{
    curr_mon++;
    }
  }

  for (int i=0; i<retired.months; i++){
    printf("Age %3d month %2d you have $%.2f\n", curr_age, curr_mon, balance);
    balance = balance * (1 + retired.rate_of_return / 12);
    balance = balance + retired.contribution;
    if (curr_mon == 11){
      curr_age++;
      curr_mon = 0;
    }
    else{
    curr_mon++;
    }
  }
  
}
		 
int main(){
  retire_info working;
  retire_info retired;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01;

  retirement(327, 21345, working, retired);

  return 1;

}
