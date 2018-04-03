#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


// Dynamic global array to store the Fibonacci numbers
int *g = NULL;

// The function to be executed by all threads
void *myThreadFun(void *vargp)
{
    // Store the value argument passed to this thread
    int *sz = (int *)vargp;
    int a =  *sz;
    if (a>2){
        g[0]=1;
        g[1]=1;
        for(int i=2; i<*sz; i++){
            g[i]=g[i-1]+g[i-2];
        }

    }
    else if(*sz==2){
        g[0]=1;
        g[1]=1;
    }
    else{
        g[0]=1;
    }
    return NULL;
}

int main()
{
    pthread_t tid;
    g = malloc(1*sizeof(int));
    int f;
    printf("Enter number of Fibonacci numbers to be produced:\n");
    scanf("%d", &f);
    printf("\n");
    //reallocate global array to store f Fibonacci numbers
    g = realloc(g, f* sizeof(int));
    //create a separate thread passing f Fibonacci numbers
    pthread_create(&tid, NULL, myThreadFun, (void *)&f);
    pthread_join(tid,NULL);

    //print out values from global
    for(int j=0; j<f; j++){
        printf("no. %d: %d\n",j+1, g[j]);
    }

    free(g);
    return 0;
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
