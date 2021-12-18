
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
  
// y���n t�r�
struct Yigin 
{ 
    int next; 
    unsigned kapasite; 
    int* dizi; 
}; 
  
// Stack i�lemleri
struct Yigin* yigin( unsigned kapasite ) 
{ 
    struct Yigin* stack = (struct Yigin*)  
           malloc(sizeof(struct Yigin)); 
  
    if (!stack)  
        return NULL; 
  
    stack->next = -1; 
    stack->kapasite = kapasite; 
  
    stack->dizi = (int*) malloc(stack->kapasite *  sizeof(int)); 
  
    return stack; 
} 
int bos(struct Yigin* stack) 
{ 
    return stack->next == -1 ; 
} 
char peek(struct Yigin* stack) 
{ 
    return stack->dizi[stack->next]; 
} 
char pop(struct Yigin* stack) 
{ 
    if (!bos(stack)) 
        return stack->dizi[stack->next--] ; 
    return '$'; 
} 
void push(struct Yigin* stack, char o) 
{ 
    stack->dizi[++stack->next] = o; 
} 
  
  

int islenen(char c) 
{ 
    return (c >= 'a' && c <= 'z') ||  
           (c >= 'A' && c <= 'Z'); 
} 
  
 
// gelen operat�r�n �nceli�ine g�re d�nd�r�r.


int oncelik(char c) 
{ 
    switch (c) 
    { 
    case '+': 
    case '-': 
        return 1; 
  
    case '*': 
    case '/': 
        return 2; 
  
    case '^': 
        return 3; 
    } 
    return -1; 
} 
  
  
//verilen infix ifadesini postfixe d�n��t�r. 
int infPost(char* ifade) 
{ 
    int i, j; 
  
    //bir y���n olu�tural�m. 
    
    struct Yigin* stack = yigin(strlen(ifade)); 
    if(!stack) // y���n d�zg�n olu�turuldu mu?
        return -1 ; 
  
    for (i = 0, j = -1; ifade[i]; ++i) 
    { 
          
        // aranan karakterse,��kt�ya ekle
         
        if (islenen(ifade[i])) 
            ifade[++j] = ifade[i]; 
          
        // aranan karakter ise �(� y���na ekle
        
        else if (ifade[i] == '(') 
            push(stack, ifade[i]); 
          
        // Taranan karakter bir ")" ise,bir �(� ile kar��la��l�ncaya kadar devam et.
       
        else if (ifade[i] == ')') 
        { 
            while (!bos(stack) && peek(stack) != '(') 
                ifade[++j] = pop(stack); 
            if (!bos(stack) && peek(stack) != '(') 
                return -1; // ge�ersiz ifade              
            else
                pop(stack); 
        } 
        else 
        { 
            while (!bos(stack) &&  
                 oncelik(ifade[i]) <= oncelik(peek(stack))) 
                ifade[++j] = pop(stack); 
            push(stack, ifade[i]); 
        } 
  
    } 
  
    // y���ndaki t�m operat�rleri a�
    while (!bos(stack)) 
        ifade[++j] = pop(stack ); 
  
    ifade[++j] = '\0'; 
    printf( "%s", ifade ); 
} 
  

int main() 
{ 
    char ifade[] = "a+b*(c-e)^(f+g)-i";
	printf("Girilen infix ifadesini postfixe donusturme: \n") ;
    printf(ifade);
    printf("\n");
    infPost(ifade); 
    return 0; 
} 
