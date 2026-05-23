target=reconnaitre1 reconnaitre2 reconnaitre3 reconnaitre4 reconnaitre5
#include "author.inc"
#define TITRE Reconnaître un quadrilatère particulier

#include "ltprop.inc"
#if defined TARGET_reconnaitre1
 \title{TITRE 1}
 \text{good=Quadrilatère seulement}
 \text{liste=7
8
10
11}
#endif
#if defined TARGET_reconnaitre2
 \title{TITRE 2}
 \text{good=Parallélogramme}
 \text{liste=2
3
4
5}
#endif
#if defined TARGET_reconnaitre3
 \title{TITRE 3}
 \text{good=Rectangle}
 \text{liste=9
randitem(2,3,4,5),randitem(8,10)
randitem(2,3,4,5),randitem(8,10)
randitem(2,3,4,5),randitem(8,10)}
#endif
#if defined TARGET_reconnaitre4
 \title{TITRE 4}
 \text{good=Losange}
 \text{liste=6
randitem(2,3,4,5),randitem(7,11)
randitem(2,3,4,5),randitem(7,11)
randitem(2,3,4,5),randitem(7,11)}
#endif
#if defined TARGET_reconnaitre5
 \title{TITRE 5}
 \text{good=Carré}
 \text{liste=6,randitem(8,10)
randitem(2,3,4,5),randitem(7,11),randitem(8,10)
9,randitem(7,11)}
#endif

\text{liste=randrow(\liste)}
\text{nbliste=items(\liste)}
\text{liste=\nbliste>1?shuffle(\liste)}
\text{liste=1,\liste}
\text{nbliste=\nbliste+1}
\text{bad=Quadrilatère seulement,Parallélogramme,Rectangle,Losange,Carré}
\statement{
\name est un quadrilatère possédant les propriétés suivantes :
<ul>
\for{k=1 to \nbliste}{
   <li>\ltprop[\liste[\k]]</li>
 }
</ul>
   Quelle est la nature de \name ?}

\choice{}{\good}{\bad}{option=shuffle}
