````md
# 2. C PROGRAMMING

## 1. Write a C program to calculate addition of two numbers.

### Answer:
```c
#include<stdio.h>
int main(){int a,b;scanf("%d%d",&a,&b);printf("Sum = %d",a+b);return 0;}
````

## 2. Write a C program to compare two numbers.

### Answer:

```c
#include<stdio.h>
int main(){int a,b;scanf("%d%d",&a,&b);if(a>b)printf("%d is greater",a);else if(b>a)printf("%d is greater",b);else printf("Both are equal");return 0;}
```

## 3. Write a C program to check whether a number is odd or even.

### Answer:

```c
#include<stdio.h>
int main(){int n;scanf("%d",&n);printf(n%2?"Odd":"Even");return 0;}
```

## 4. Write a C program to calculate the sum of digits of a number.

### Answer:

```c
#include<stdio.h>
int main(){int n,s=0;scanf("%d",&n);while(n){s+=n%10;n/=10;}printf("Sum = %d",s);return 0;}
```

## 5. Write a C program to show the maximum of three numbers.

### Answer:

```c
#include<stdio.h>
int main(){int a,b,c,m;scanf("%d%d%d",&a,&b,&c);m=a>b?a:b;m=m>c?m:c;printf("Maximum = %d",m);return 0;}
```

## 6. Write a C program to divide two integers and handle division by zero.

### Answer:

```c
#include<stdio.h>
int main(){int a,b;scanf("%d%d",&a,&b);if(!b)printf("Division by zero is not allowed");else printf("Result = %d",a/b);return 0;}
```

## 7. Write a C program to print the reverse of a number.

### Answer:

```c
#include<stdio.h>
int main(){int n,r=0;scanf("%d",&n);while(n){r=r*10+n%10;n/=10;}printf("Reverse = %d",r);return 0;}
```

## 8. Write a C program to check whether a number is prime or not.

### Answer:

```c
#include<stdio.h>
int main(){int n,i,p=1;scanf("%d",&n);if(n<2)p=0;for(i=2;i*i<=n;i++)if(n%i==0)p=0;printf(p?"Prime":"Not Prime");return 0;}
```

## 9. Write a C program to display "Welcome" and the current date.

### Answer:

```c
#include<stdio.h>
#include<time.h>
int main(){time_t t=time(0);printf("Welcome\n%s",ctime(&t));return 0;}
```

## 10. Write a C program to display names and sizes of files exceeding 500 bytes in decreasing order of size and print the total number.

### Answer:

```c
#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>
typedef struct{char n[256];long s;}F;
int main(int c,char**v){DIR*d=opendir(v[1]);struct dirent*e;F a[100];int n=0,i,j;struct stat x;while((e=readdir(d))){char p[512];sprintf(p,"%s/%s",v[1],e->d_name);if(stat(p,&x)==0&&S_ISREG(x.st_mode)&&x.st_size>500){strcpy(a[n].n,e->d_name);a[n++].s=x.st_size;}}for(i=0;i<n;i++)for(j=i+1;j<n;j++)if(a[i].s<a[j].s){F t=a[i];a[i]=a[j];a[j]=t;}for(i=0;i<n;i++)printf("%s %ld bytes\n",a[i].n,a[i].s);printf("Total files: %d\n",n);closedir(d);return 0;}
```

## 11. Write a C program to display the last modification time of a file.

### Answer:

```c
#include<stdio.h>
#include<sys/stat.h>
#include<time.h>
int main(int c,char**v){struct stat s;if(stat(v[1],&s)==0)printf("%s",ctime(&s.st_mtime));else printf("File does not exist");return 0;}
```

## 12. Write a C program that accepts two directories and deletes identical files from OS2.

### Answer:

```c
#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<string.h>
int main(int c,char**v){DIR*d=opendir(v[1]);struct dirent*e;char a[512],b[512];struct stat s1,s2;while((e=readdir(d))){sprintf(a,"%s/%s",v[1],e->d_name);sprintf(b,"%s/%s",v[2],e->d_name);if(stat(a,&s1)==0&&stat(b,&s2)==0&&S_ISREG(s1.st_mode)&&S_ISREG(s2.st_mode)&&s1.st_size==s2.st_size){FILE*x=fopen(a,"rb"),*y=fopen(b,"rb");int p,q,s=1;while((p=fgetc(x))!=EOF&&(q=fgetc(y))!=EOF)if(p!=q){s=0;break;}fclose(x);fclose(y);if(s)remove(b);}}closedir(d);return 0;}
```

## 13. Write a C program to list files in the current directory starting with vowels.

### Answer:

```c
#include<stdio.h>
#include<dirent.h>
#include<ctype.h>
#include<sys/stat.h>
int main(){DIR*d=opendir(".");struct dirent*e;struct stat s;while((e=readdir(d))){stat(e->d_name,&s);char c=tolower(e->d_name[0]);if(S_ISREG(s.st_mode)&&(c=='a'||c=='e'||c=='i'||c=='o'||c=='u'))puts(e->d_name);}closedir(d);return 0;}
```

## 14. Write a C program to drop lines which match a given word.

### Answer:

```c
#include<stdio.h>
#include<string.h>
int main(int c,char**v){FILE*f=fopen(v[2],"r");char s[1000];while(fgets(s,sizeof(s),f))if(!strstr(s,v[1]))printf("%s",s);fclose(f);return 0;}
```

## 15. Write a C program to display all non-directory files and calculate their total size.

### Answer:

```c
#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
int main(){DIR*d=opendir(".");struct dirent*e;struct stat s;long sum=0;while((e=readdir(d))){stat(e->d_name,&s);if(S_ISREG(s.st_mode)){printf("%s\n",e->d_name);sum+=s.st_size;}}printf("Total size = %ld bytes",sum);closedir(d);return 0;}
```

## 16. Write a C program to find the number of words, characters and lines in a file.

### Answer:

```c
#include<stdio.h>
#include<ctype.h>
int main(int c,char**v){FILE*f=fopen(v[1],"r");int ch,l=0,w=0,cnt=0,in=0;while((ch=fgetc(f))!=EOF){cnt++;if(ch=='\n')l++;if(isspace(ch))in=0;else if(!in)w++,in=1;}printf("Lines: %d\nWords: %d\nCharacters: %d",l,w,cnt);fclose(f);return 0;}
```

```
```
