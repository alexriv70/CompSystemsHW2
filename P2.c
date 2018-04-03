#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int *p_arr = NULL;//list of numbers <= inserted number
int *c_arr = NULL;//array of booleans confirming primality

    int check_primality(int val){
        //check each possible divisor for primality by checking if modulus is ==0
    for (int i=2; i<val/2; i++){
        if (val%i==0){
            return (0);
        }
    }
    return (1);
    }

void *Eratosthenes_Thread(void *vargp){
    double *up = (double *) vargp;
    int l= *up;
    l=floor(sqrt(*up));
    for (int i = 2; i<=l; i++){
        if (check_primality(i)){
            for (int j=2; j<ceil(*up/i); j++){
                c_arr[i*j]=0;
            }
        }
        else{
            c_arr[i]=0;

        }
    }
    return NULL;
    }

    int main(){
    //get upper value to be checked for primality
    double p;
    int get;
    printf("Enter the highest number greater than 1 to be checked for primality:\n");
    scanf("%d",&get);
    p=get;
    if (p<=1){
        printf("Error, the number inserted does not meet the requirements for the check, please reset the application and try again\n");
        return(1);
    }

    //reserve space for array of p and c
    p_arr=malloc(1*sizeof(int));
    p_arr=realloc(p_arr,(get+1)*sizeof(int));
    c_arr=malloc(1*sizeof(int));
    c_arr=realloc(c_arr,(get+1)*sizeof(int));
    c_arr[0]=0;
    c_arr[1]=1;
    for (int i=2; i<p; i++){
        c_arr[i]=1;
    }
    printf("\n");

    //set p_arr to contain every interger form 0->get
    for(int i=0; i<=get; i++){
    p_arr[i]=i;
    }


    pthread_t tid;
    pthread_create(&tid, NULL, Eratosthenes_Thread, (void *)&p);
    pthread_join(tid,NULL);

    for(int i =2;i<get;i++){
        if(c_arr[i]==1){
            printf("%d\n", p_arr[i]);
        }
    }

    return (0);
    }



    /*
           +hhhho.                      `/yhhhy.
          sd////ohy-                  `ods+//:sm`
         .N++.`-/+ody.              `+ds+:.``+:do
         +m/:````-++sm+            -hh+/.````/:sd
         yho......./oody://++++//:/mso:......-++M`
         dyo...--.../o+yssssossssyyso:..---...o/M-
         myo..--::://o++//////++++++o+//::--..o/N-
         dyo..-/++++/////////////////+++oo/-..s+M-
         hhs-/++////////:::::///////////+++o/:ssM`
         om+++////:-----:::::::-.....:////+++ooym
        -hh+/////-`     `.:::-`       .////++++ym/
       +ds+/////: `:://`  `-`   -://.  :////++++sds`                       ``...``
      sdo////:::- :mosN/       `dssNy  .---::/++oohh.                 .:+ossooooosso/.`-.
     /Ns+/:.````   :o+:`        -oo:`        `.:+oymy              `:ss+-.`       `-/shdyo`
     :md+.                                      :ohNo             :ys-                .:`sh`
     `Ns/`             .-::::.                  .osN:            +h-         ```````     `ds:
     `ddy:`        `` -mmysddh    `            `:ydm-           oh.        `..........``  /sm:
      `-hh/`       --`.hmmdmd+`` `/           .+hm:.           :m.       `..--::::::---..```ho
        `+ds-`     `/:-:+syo:-.`:/.        `./sydho:..```     `d+        `.-:////////::--.``m+
          .sho.      .oo+os++s+-.        `-/ossooosyhhhhyyyssssN`       `.-:/++oosyso//:--./Ny`
            -ym+.     :o:-::/s`       `.:+++o++ooooooooooosssssh         .-:/+oshsooo+//:--:om`
             `No/-     :/+++/.      `-/+++++++++++oooooooooooooh.        `.-/+ohoo+++++/::-+m-
              hy::-                .////+++++++++++ooooooooooooss`        `.-:oho++++++/:/yh.
              sh:::`              -//////++++++++++++oooooooooooss.         `.-yo+++o//ohy:
              od:::.              :////////++++++++++++ooooooooooos+`         `.os++ohN+.
              od:::.              ./////////+++++++++++++++oooooooooso:+/.      -+ho++ds
              yh:::`               ./////////+++++++++++++++++++++++++oo+ss+/:--/h++++:m/
              dy::`                 .//////////+++++++++++++++++++++++++++++++++++++//:oh
              mo::                   -///////////+++++++++++++++++++++++++++++++++////:+d
              ds::.                  .//////////////+++++++++++++++++++++++++++///////:oh
              sd:::`                 .::////////////////++++++y+++++++++++++//////////-sy
              .N+:::`                -::::////////////////:--:so++++++////////////////.ys
               sd/::-                -:::::///+///////:-..:++//y//////////////////////`ho
               `mo:::`               .:::::::/o///:-.``-o+/::::++:///////////////////- ys
                /m/::`            `   ::::::::s..`` `:shm:::::::o/.:///////////////:-  +d
                 hy::.  ``        :   -:::::::s  `-oyo-`ds:::::::+/``-::////////::-`   .N-
                 -N+:.  `.:-.     /`  `::::::/y:oso:`   .ds:::::::/+:.```.......``      /d:
                  dh:.    `-:os+/://   ::::::/No-`       .sh+:::::::://:-`               -d/
                  +N/.     `.+N://hy   .:::::+N`           -sho:--------:/o+-`            :N`
                  `Ny.      `:N`  /m    :::::sm              .oho:--------dyoso/.`        `N:
                   ym`       :N`  -N`   .::::hy                .yh-------:N.  ./sy/        d/
                   :N.       :N   .N.    -::/m+                 yy----...sh      -N`       d/
                   `m/       /m   `N-     .-:N.                +m:......:m-      -N`       m/
                    h+       oh   `N-       +d                :m:.......hs       /m       `N-
                    yo       ys   .N.       do               /d/.......od`       ys       -N`
                    ho       d/   -N`      -N.              +d:......./m-       .N-       +d
                    d+      .N.   /d       sy             `sd-.......+d-        yy        d+
                   `N-      /m    ys      `N:             .hyyyyyyyssy.        :m.       :m`
                   /m`      ys   `m:      oh                                  .m:       `d+
                   odssoossyh-   -N.    `-m:                                  smoo+++ooshy
                      `.``       `+syyyys+:                                    `..---..`


*/
