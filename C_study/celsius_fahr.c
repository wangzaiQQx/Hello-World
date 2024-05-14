#include <stdio.h> 
int main() 
{ 
 float fahr, celsius; 
 float lower, upper, step; 
 lower = -50; /* 温度表的下限 */ 
 upper = 100; /* 温度表的上限 */ 
 step = 10; /* 步长 */ 
 celsius = lower; 
 printf("%5s %9s\n", "Celsius", "Fahrenheit");
 while (celsius <= upper) { 
 fahr = 32 + celsius*1.8; 
 printf("%5.0f %9.1f\n", celsius, fahr); 
 celsius = celsius + step; 
 } 
} 