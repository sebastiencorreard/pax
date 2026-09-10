target= oefcercle2
#include "author.inc"
\precision{100000}
#include "lang_titles.inc"

\text{nom=shuffle(A,B,C,E,F,G,H,I,J,K,L,M,N,R,S,T)}
#include "lang.inc"
\text{dess=draw(300,300
linewidth 1
circle 150,150,260,black
text black,140,150,medium,\nom[1]
segment 58,58,242,242,black
segment 30,100,100,270,black
segment 150,150,210,35,black
arrow 190,150,150,150,10,black
arrow 150,240,150,280,10,black)}

\text{cod1=40x170}
\text{cod2=150x60}
\text{cod3=70x90}
\text{cod4=193x138}
\text{cod5=120x230}

\statement{
  \name_enonc1 \nom[1]. \name_statement:
  <div class="wimscenter">\special{imagefill \dess,300x300,70x24
    r1,\cod1
    r2,\cod2
    r3,\cod3
    r4,\cod4
    r5,\cod5}
</div>
}

\answer{}{\reps[5];\reps}{type=clickfill}{option=shuffle}
\answer{}{\reps[4];\reps}{type=clickfill}{option=shuffle}
\answer{}{\reps[3];\reps}{type=clickfill}{option=shuffle}
\answer{}{\reps[2];\reps}{type=clickfill}{option=shuffle}
\answer{}{\reps[1];\reps}{type=clickfill}{option=shuffle}
