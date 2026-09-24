### Day 1: Utilities
**1-2. Dir & HOME:** Location for files. HOME is user's absolute path.
**3. Ops:** `pwd`, `cd`, `mkdir`, `rmdir`
**4-6. Paths, Cmd, ls:** Abs from `/`, Rel from `.`. Cmd performs tasks. `ls` lists.
**7-12. Utils:** Switch: `cd`, User: `whoami`, OS: `uname -a`, Cal: `cal`, Date: `date`, Echo: `echo`
**File Ops:** `cat`, `touch`, `cp`, `mv`, `rm`. Count: `wc`. Compare: `cmp`, `comm`. Zip: `gzip`, `tar`. Perms: `chown`, `chmod`. Filters: `head`, `tail`, `cut`, `sort`, `uniq`, `tr`, `grep`, `sed`.

### Day 2: Shell Programming (C)
**1. Add:**
```c
#include <stdio.h>
int main(){int a,b;scanf("%d%d",&a,&b);printf("%d\n",a+b);}
```
**2. Compare:**
```c
#include <stdio.h>
int main(){int a,b;scanf("%d%d",&a,&b);if(a>b)printf("%d> \n",a);else if(b>a)printf("%d> \n",b);else printf("=\n");}
```
**3. Odd/Even:**
```c
#include <stdio.h>
int main(){int a;scanf("%d",&a);printf(a%2==0?"Even\n":"Odd\n");}
```
**4. Sum digits:**
```c
#include <stdio.h>
int main(){int n,s=0;scanf("%d",&n);while(n){s+=n%10;n/=10;}printf("%d\n",s);}
```
**5. Max of 3:**
```c
#include <stdio.h>
int main(){int a,b,c;scanf("%d%d%d",&a,&b,&c);printf("%d\n",a>b&&a>c?a:(b>c?b:c));}
```
**6. Div:**
```c
#include <stdio.h>
int main(){int a,b;scanf("%d%d",&a,&b);if(b==0)printf("Err\n");else printf("%d\n",a/b);}
```
**7. Rev:**
```c
#include <stdio.h>
int main(){int n,r=0;scanf("%d",&n);while(n){r=r*10+n%10;n/=10;}printf("%d\n",r);}
```
**8. Prime:**
```c
#include <stdio.h>
int main(){int n,f=0;scanf("%d",&n);for(int i=2;i<=n/2;i++)if(n%i==0)f=1;printf((f||n<=1)?"Not\n":"Prime\n");}
```
**9. Date:**
```c
#include <stdio.h>
#include <time.h>
int main(){time_t t=time(0);printf("welcome\n%s",ctime(&t));}
```
**10. >500B files:**
```c
#include <stdlib.h>
#include <stdio.h>
int main(int c,char**v){char m[256];sprintf(m,"find %s -type f -size +500c -exec ls -l {} \\; | awk '{print $5, $9}' | sort -nr",v[1]);system(m);}
```
**11. Mod time:**
```c
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
int main(int c,char**v){struct stat s;if(stat(v[1],&s)==0)printf("%s",ctime(&s.st_mtime));else printf("No\n");}
```
**12. Del identical:**
```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int c,char**v){char m[256];sprintf(m,"cd %s; for f in *; do if [ -f ../%s/$f ]; then rm $f; fi; done",v[2],v[1]);system(m);}
```
**13. Vowel start:**
```c
#include <stdlib.h>
int main(){system("ls | grep -i '^[aeiou]'");}
```
**14. Drop match:**
```c
#include <stdlib.h>
#include <stdio.h>
int main(int c,char**v){char m[256];sprintf(m,"grep -v %s %s",v[1],v[2]);system(m);}
```
**15. Size sum:**
```c
#include <stdlib.h>
int main(){system("ls -l | grep '^-' | awk '{s+=$5} END{print s}'");}
```
**16. wc:**
```c
#include <stdlib.h>
#include <stdio.h>
int main(int c,char**v){char m[256];sprintf(m,"wc %s",v[1]);system(m);}
```

### Day 3: Process-1
**1. Creation:**
```c
#include <unistd.h>
int main(){fork();return 0;}
```
**2. PID:**
```c
#include <stdio.h>
#include <unistd.h>
int main(){pid_t p=fork();printf(p?"P:%d C:%d\n":"C:%d P:%d\n",getpid(),p?p:getppid());}
```
**3. Orphan:**
```c
#include <unistd.h>
int main(){if(fork()==0){sleep(1);}return 0;}
```
**4. Zombie:**
```c
#include <unistd.h>
int main(){if(fork()>0)sleep(1);return 0;}
```
**5. Vars fork:**
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int g=1;int main(){int l=1;if(fork()==0){g++;l++;}else wait(0);printf("g:%d l:%d\n",g,l);}
```
**6. Vars vfork:**
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int g=1;int main(){int l=1;if(vfork()==0){g++;l++;printf("g:%d l:%d\n",g,l);exit(0);}wait(0);printf("g:%d l:%d\n",g,l);}
```

### Day 4: Process-2
**1. exec:**
```c
#include <unistd.h>
#include <sys/wait.h>
int main(){if(fork()==0)execlp("who","who",0);if(fork()==0)execlp("ls","ls","-al",0);if(fork()==0)execl("/bin/date","date",0);wait(0);wait(0);wait(0);}
```
**2. Background:**
```c
#include <unistd.h>
#include <stdlib.h>
int main(){if(fork()==0){system("uname -a");sleep(50);exit(0);}}
```
**3. 1 to 10:**
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
void f(){for(int i=1;i<=10;i++)printf("%d P:%d PP:%d\n",i,getpid(),getppid());exit(0);}
int main(){if(fork()==0)f();if(fork()==0)f();wait(0);wait(0);printf("Good Bye\n");}
```

### Day 5: Threads-1
**1. Welcome:**
```c
#include <stdio.h>
#include <pthread.h>
void* m(void* a){printf("WELCOME\n");return 0;}
int main(){pthread_t t;pthread_create(&t,0,m,0);pthread_join(t,0);}
```
**2. 5 Threads:**
```c
#include <stdio.h>
#include <pthread.h>
void* m(void* a){printf("Hello\n");return 0;}
int main(){pthread_t t[5];for(int i=0;i<5;i++)pthread_create(&t[i],0,m,0);for(int i=0;i<5;i++)pthread_join(t[i],0);}
```
**3. Args:**
```c
#include <stdio.h>
#include <pthread.h>
void* m(void* a){printf("Arg:%d\n",*(int*)a);return 0;}
int main(){pthread_t t;int x=10;pthread_create(&t,0,m,&x);pthread_join(t,0);}
```

### Day 6: Threads-2
**1. Odd/Even:**
```c
#include <stdio.h>
#include <pthread.h>
int s,e;
void* o(void* a){for(int i=s;i<=e;i++)if(i%2)printf("Odd:%d\n",i);return (void*)1;}
void* ev(void* a){for(int i=s;i<=e;i++)if(!(i%2))printf("Ev:%d\n",i);return (void*)2;}
int main(){pthread_t t1,t2;scanf("%d%d",&s,&e);pthread_create(&t1,0,o,0);pthread_create(&t2,0,ev,0);void *r1,*r2;pthread_join(t1,&r1);pthread_join(t2,&r2);printf("%ld %ld\n",(long)r1,(long)r2);}
```
**2. Sum/Prime:**
```c
#include <stdio.h>
#include <pthread.h>
int s,e;
void* sum(void* a){long sum=0;for(int i=s;i<=e;i++)sum+=i;printf("Sum:%ld\n",sum);return(void*)1;}
void* p(void* a){for(int i=s;i<=e;i++){int f=0;for(int j=2;j<=i/2;j++)if(i%j==0)f=1;if(!f&&i>1)printf("Pr:%d\n",i);}return(void*)2;}
int main(){pthread_t t1,t2;scanf("%d%d",&s,&e);pthread_create(&t1,0,sum,0);pthread_create(&t2,0,p,0);pthread_join(t1,0);pthread_join(t2,0);}
```

### Day 7: Signals
**1. SIGCHLD:**
```c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
void h(int s){printf("SIGCHLD\n");}
int main(){signal(SIGCHLD,h);if(fork()==0)exit(0);wait(0);}
```
**2. SIGINT:**
```c
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
void h(int s){printf("INT by %s\n",getenv("USER"));exit(0);}
int main(){signal(SIGINT,h);while(1);}
```
**3. Ignore:**
```c
#include <signal.h>
#include <unistd.h>
int main(){signal(SIGINT,SIG_IGN);sleep(5);signal(SIGINT,SIG_DFL);sleep(5);}
```
**4. Wake:**
```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
void h(int s){printf("Awake\n");exit(0);}
int main(){pid_t p1=fork();if(p1==0){signal(SIGUSR1,h);while(1);}pid_t p2=fork();if(p2==0){signal(SIGUSR2,h);while(1);}sleep(1);kill(p1,SIGUSR1);kill(p2,SIGUSR2);}
```
**5. Delay Kill:**
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
int main(int c,char**v){pid_t p=fork();if(p==0){sleep(2);exit(0);}int s,w=0,d=atoi(v[1]);while(w<d){if(waitpid(p,&s,WNOHANG)==p)return 0;sleep(1);w++;}kill(p,SIGKILL);printf("Killed\n");}
```

### Day 8: Pipes
**1. Pipe:**
```c
#include <stdio.h>
#include <unistd.h>
int main(){int p[2];char b[5];pipe(p);if(fork()==0)write(p[1],"hi",2);else{read(p[0],b,2);printf("%s\n",b);}}
```
**2. popen:**
```c
#include <stdio.h>
int main(){FILE *f=popen("ls","r");char b[99];while(fgets(b,99,f))printf("%s",b);pclose(f);}
```
**3. Reverse Quit:**
```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main(){int p[2];pipe(p);if(fork()==0){char b[99];while(1){read(p[0],b,99);if(!strcmp(b,"quit\n"))break;for(int i=strlen(b)-2;i>=0;i--)putchar(b[i]);puts("");}}else{char s[99];while(1){fgets(s,99,stdin);write(p[1],s,99);if(!strcmp(s,"quit\n"))break;}}}
```
**4. 2-way Sum:**
```c
#include <stdio.h>
#include <unistd.h>
int main(){int p1[2],p2[2];pipe(p1);pipe(p2);if(fork()==0){int n,s;while(1){read(p1[0],&n,4);if(!n)break;s=0;for(int i=1;i<=n;i++)s+=i;write(p2[1],&s,4);}}else{int n,s;while(1){scanf("%d",&n);write(p1[1],&n,4);if(!n)break;read(p2[0],&s,4);printf("%d\n",s);}}}
```
**5. 3 Children Prime:**
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
void f(int p){int r[2];read(p,r,8);for(int i=r[0];i<=r[1];i++){int x=0;for(int j=2;j<=i/2;j++)if(i%j==0)x=1;if(!x&&i>1)printf("Pr:%d\n",i);}}
int main(){int p[3][2];for(int i=0;i<3;i++){pipe(p[i]);if(fork()==0){f(p[i][0]);return 0;}}int s,e;scanf("%d%d",&s,&e);int st=(e-s+1)/3;for(int i=0;i<3;i++){int r[2]={s+i*st,i==2?e:s+(i+1)*st-1};write(p[i][1],r,8);}wait(0);wait(0);wait(0);}
```

### Day 9: Semaphores
**1. Producer/Consumer:**
```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
sem_t e,f;int d;
void* p(void* a){sem_wait(&e);d=1;sem_post(&f);return 0;}
void* c(void* a){sem_wait(&f);printf("%d\n",d);sem_post(&e);return 0;}
int main(){pthread_t t1,t2;sem_init(&e,0,1);sem_init(&f,0,0);pthread_create(&t1,0,p,0);pthread_create(&t2,0,c,0);pthread_join(t1,0);pthread_join(t2,0);}
```
**2. 2 Consumers:**
```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
sem_t e,f;int d;
void* p(void* a){sem_wait(&e);d=1;sem_post(&f);sem_post(&f);return 0;}
void* c(void* a){sem_wait(&f);printf("%d\n",d);return 0;}
int main(){pthread_t t1,t2,t3;sem_init(&e,0,1);sem_init(&f,0,0);pthread_create(&t1,0,p,0);pthread_create(&t2,0,c,0);pthread_create(&t3,0,c,0);pthread_join(t1,0);pthread_join(t2,0);pthread_join(t3,0);}
```
**3. Bounded:**
```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
sem_t e,f,m;int b[5],in=0,out=0;
void* p(void* a){sem_wait(&e);sem_wait(&m);b[in]=1;in=(in+1)%5;sem_post(&m);sem_post(&f);return 0;}
void* c(void* a){sem_wait(&f);sem_wait(&m);printf("%d\n",b[out]);out=(out+1)%5;sem_post(&m);sem_post(&e);return 0;}
int main(){pthread_t t1,t2;sem_init(&e,0,5);sem_init(&f,0,0);sem_init(&m,0,1);pthread_create(&t1,0,p,0);pthread_create(&t2,0,c,0);pthread_join(t1,0);pthread_join(t2,0);}
```
**4. Cond Var:**
```c
#include <stdio.h>
#include <pthread.h>
pthread_mutex_t m;pthread_cond_t c;int cnt=0;
void* w(void* a){for(int i=0;i<300;i++){pthread_mutex_lock(&m);if(++cnt==500)pthread_cond_signal(&c);pthread_mutex_unlock(&m);}return 0;}
void* wt(void* a){pthread_mutex_lock(&m);while(cnt<500)pthread_cond_wait(&c,&m);printf("500\n");pthread_mutex_unlock(&m);return 0;}
int main(){pthread_t t1,t2,t3;pthread_mutex_init(&m,0);pthread_cond_init(&c,0);pthread_create(&t3,0,wt,0);pthread_create(&t1,0,w,0);pthread_create(&t2,0,w,0);pthread_join(t1,0);pthread_join(t2,0);pthread_join(t3,0);}
```
**5. Dining Phil:**
```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
sem_t f[5];
void* p(void* a){int i=*(int*)a;sem_wait(&f[i]);sem_wait(&f[(i+1)%5]);printf("Eat %d\n",i);sem_post(&f[(i+1)%5]);sem_post(&f[i]);return 0;}
int main(){pthread_t t[5];int id[5];for(int i=0;i<5;i++)sem_init(&f[i],0,1);for(int i=0;i<5;i++){id[i]=i;pthread_create(&t[i],0,p,&id[i]);}for(int i=0;i<5;i++)pthread_join(t[i],0);}
```

### Day 10: Deadlock
**1. Banker's:**
```c
#include <stdio.h>
int main(){
    int al[5][3]={{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}},mx[5][3]={{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
    int av[3]={3,3,2},nd[5][3],f[5]={0},ans[5],ind=0;
    for(int i=0;i<5;i++)for(int j=0;j<3;j++)nd[i][j]=mx[i][j]-al[i][j];
    for(int k=0;k<5;k++)for(int i=0;i<5;i++)if(!f[i]){
        int fl=0;for(int j=0;j<3;j++)if(nd[i][j]>av[j])fl=1;
        if(!fl){ans[ind++]=i;for(int y=0;y<3;y++)av[y]+=al[i][y];f[i]=1;}
    }
    for(int i=0;i<5;i++)printf("%d ",ans[i]);printf("\n");
}
```
