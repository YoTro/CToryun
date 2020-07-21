#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int romanToInt(char * s){
    int len = strlen(s);
    int a = 0;
    int b = 0;
    int c = 0;
    
    for(int i = 0; i < len; i++){
        if(s[i] == 'I'){
            a = 1;
        }
        if(s[i] == 'V'){
            a = 5;
        }
        if(s[i] == 'X'){
            a = 10;
        }
        if(s[i] == 'L'){
            a = 50;
        }
        if(s[i] == 'C'){
            a = 100;
        }
        if(s[i] == 'D'){
            a = 500;
        }
        if(s[i] == 'M'){
            a = 1000;
        }
        if(a > b){
            c += a - 2*b;
        }else{
            c += a;
        }
        b = a;
    }
    return c;
}
char * intToRoman(int num){
    char *s = (char *)malloc(sizeof(char)*12);
    int i = 0;
    while (num > 0){
        printf("num: %d\n", num);
        if(num >= 1000){
            num -= 1000;
            s[i++] = 'M';
            continue;
        }
        if(num >= 900){
            num -= 900;
            s[i++] = 'C';
            s[i++] = 'M';
            continue;
        }
        if(num >= 500){
            num -= 500;
            s[i++] = 'D';
            continue;
        }
        if(num >= 400){
            num -= 400;
            s[i++] = 'C';
            s[i++] = 'D';
            continue;
        }
        if(num >= 100){
            num -= 100;
            s[i++] = 'C';
            continue;
        }
        if(num >= 90){
            num -= 90;
            s[i++] = 'X';
            s[i++] = 'C';
            continue;
        }
        if(num >= 50){
            num -= 50;
            s[i++] = 'L';
            continue;
        }
        if(num >= 40){
            num -= 40;
            s[i++] = 'X';
            s[i++] = 'L';
            continue;
        }
        if(num >= 10){
            num -= 10;
            s[i++] = 'X';
            continue;
        }
        if(num >= 9){
            num -= 9;
            s[i++] = 'I';
            s[i++] = 'X';
            continue;
        }
        if(num >= 5){
            num -= 5;
            s[i++] = 'V';
            continue;
        }
        if(num >= 4){
            num -= 4;
            s[i++] = 'I';
            s[i++] = 'V';
            continue;
        }
        if(num >= 1){
            num--;
            s[i++] = 'I';
            continue;
        }

    }
    return s;
}
int  main(void)
{
	char s[] = {"MCMXCIV"};
	int num = romanToInt(s);
    char *s0 = intToRoman(num);
    int i = 0;
    printf("Int to Roman: \n");
	while(s[i] != '\0'){
        printf("%c", s[i++]);
    }
    printf("\n");
    free(s0);
	return 0;
}