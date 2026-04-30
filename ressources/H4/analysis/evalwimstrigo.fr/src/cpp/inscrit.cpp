target=inscrit1,inscrit2,inscrit3,inscrit4,inscrit5
#include "author.inc"

#define TITRE Angle inscrit
\text{dessin=range -70,70,-70,70
circle 0,0,100,black
fcircle 0,0,5,red}
\text{v=shuffle(A,B,D,E,F,G,H,I,K,L,M,N,P,Q,R,S,T,U,V,W,X,Y,Z)}

#if defined TARGET_inscrit1
 \title{TITRE 1}
 \text{x=randint(-40..-30),randint(20..45)}
 \real{y1=sqrt(2500-(\x[1])^2)}
 \real{y2=sqrt(2500-(\x[2])^2)}
 \text{dessin=draw(140,140
\dessin
triangle \x[1],\y1,-\x[1],-\y1,\x[2],\y2,black
fcircle \x[1],\y1,5,red
fcircle \x[2],\y2,5,red
fcircle -\x[1],-\y1,5,red
text black,\x[1]-5,\y1-5,medium,\v[1]
text black,-\x[1],-\y1-10,medium,\v[3]
text black,\x[2],\y2+15,medium,\v[2])}
\text{rep=90}
#endif


#if defined TARGET_inscrit2
 \title{TITRE 2}
 \text{x=randint(-45..-30),randint(-15..15),randint(30..45)}
 \real{y1=-sqrt(2500-(\x[1])^2)}
 \real{y2=sqrt(2500-(\x[2])^2)}
 \real{y3=-sqrt(2500-(\x[3])^2)}
 \text{dessin=draw(140,140
\dessin
segment \x[1],\y1,\x[2],\y2,black
segment \x[2],\y2,\x[3],\y3,black
segment \x[1],\y1,0,0,black
segment 0,0,\x[3],\y3,black
fcircle \x[1],\y1,5,red
fcircle \x[2],\y2,5,red
fcircle \x[3],\y3,5,red
text black,\x[1]-5,\y1-5,medium,\v[1]
text black,0,-3,medium,\v[4]
text black,\x[2],\y2+15,medium,\v[2]
text black,\x[3],\y3-10,medium,\v[3])}
\integer{rep=randint(20..35)}
\integer{mes=2*\rep}
\text{compenon=sachant que le mesure de l'angle \(\widehat{\v[1]\v[4]\v[3]}) est de \mes °}
#endif

#if defined TARGET_inscrit3
 \title{TITRE 3}
 \text{x=randint(-45..-30),randint(-15..15),randint(30..45)}
 \real{y1=-sqrt(2500-(\x[1])^2)}
 \real{y2=sqrt(2500-(\x[2])^2)}
 \real{y3=-sqrt(2500-(\x[3])^2)}
 \text{dessin=draw(140,140
\dessin
segment \x[1],\y1,\x[2],\y2,black
segment \x[2],\y2,\x[3],\y3,black
segment \x[1],\y1,0,0,black
segment 0,0,\x[3],\y3,black
fcircle \x[1],\y1,5,red
fcircle \x[2],\y2,5,red
fcircle \x[3],\y3,5,red
text black,\x[1]-5,\y1-5,medium,\v[1]
text black,0,-3,medium,\v[2]
text black,\x[2],\y2+15,medium,\v[4]
text black,\x[3],\y3-10,medium,\v[3])}
\integer{mes=randint(20..35)}
\integer{rep=2*\mes}
\text{compenon=sachant que le mesure de l'angle \(\widehat{\v[1]\v[4]\v[3]}) est de \mes °}
#endif



#if defined TARGET_inscrit4
 \title{TITRE 4}
 \text{x=randint(-45..-30),randint(-20..-5),randint(30..45),randint(5..20)}
 \real{y1=-sqrt(2500-(\x[1])^2)}
 \real{y2=sqrt(2500-(\x[2])^2)}
 \real{y3=-sqrt(2500-(\x[3])^2)}
 \real{y4=sqrt(2500-(\x[4])^2)}
 \text{dessin=draw(140,140
\dessin
segment \x[1],\y1,\x[2],\y2,black
segment \x[2],\y2,\x[3],\y3,black
segment \x[1],\y1,\x[4],\y4,black
segment \x[4],\y4,\x[3],\y3,black
fcircle \x[1],\y1,5,red
fcircle \x[2],\y2,5,red
fcircle \x[3],\y3,5,red
fcircle \x[4],\y4,5,red
text black,\x[1]-5,\y1-5,medium,\v[1]
text black,\x[2],\y2+15,medium,\v[2]
text black,\x[3],\y3-10,medium,\v[3]
text black,\x[4],\y4+15,medium,\v[4])}
 \integer{mes=randint(20..45)}
 \integer{rep=\mes}
 \text{compenon=sachant que le mesure de l'angle \(\widehat{\v[1]\v[4]\v[3]}) est de \mes °}
#endif

#if defined TARGET_inscrit5
 \title{TITRE 5}
 \text{x=randint(-46..-38),randint(-10..10),randint(38..46)}
 \real{y1=-sqrt(2500-(\x[1])^2)}
 \real{y2=-sqrt(2500-(\x[2])^2)}
 \real{y3=-sqrt(2500-(\x[3])^2)}
 \text{dessin=draw(140,140
\dessin
segment \x[1],\y1,\x[2],\y2,black
segment \x[2],\y2,\x[3],\y3,black
segment \x[1],\y1,0,0,black
segment 0,0,\x[3],\y3,black
fcircle \x[1],\y1,5,red
fcircle \x[2],\y2,5,red
fcircle \x[3],\y3,5,red
text black,\x[1]-5,\y1-5,medium,\v[1]
text black,0,-3,medium,\v[2]
text black,\x[2],\y2+15,medium,\v[4]
text black,\x[3],\y3-10,medium,\v[3])}
 \integer{mes=randint(100..130)}
 \integer{rep=360-2*\mes}
 \text{compenon=sachant que le mesure de l'angle \(\widehat{\v[1]\v[4]\v[3]}) est de \mes °}
#endif

\text{name=\(\widehat{\v[1]\v[2]\v[3]})}

\statement{
Quelle est la mesure de l'angle \name \compenon ?
<div class="wimscenter"><img src="\dessin" alt=""></div>
<b>Réponse :</b><p>
<label for="reply1">\name =</label> \embed{r1,5} °.
</p>}


\answer{\name}{\rep}{type=numexp}
