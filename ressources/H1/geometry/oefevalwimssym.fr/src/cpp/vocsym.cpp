target=oefvocsym1 oefvocsym2 oefvocsym3 oefvocsym4 oefvocsym5
#define TITRE Phrase à compléter
\keywords{symmetry}
#include "author.inc"
\precision{1000}

\text{let=shuffle(A,B,C,E,F,G,H,K,L,M,N,R,S,T)}

#if defined TARGET_oefvocsym1
\title{TITRE 1}
\text{enonc1=Les points \let[3] et}
\text{enonc2= sont }
\text{enonc3= par rapport à la droite &#40;}
\text{enonc4= &#41;.}
\text{rep1=\let[4]}
\text{rep2=symétriques}
\text{rep3=\let[1]\let[2]|\let[2]\let[1]}
\integer{s1=2}
\integer{s2=12}
\integer{s3=2}
#endif
#if defined TARGET_oefvocsym2
\title{TITRE 2}
\text{enonc1=Le point}
\text{enonc2= est }
\text{enonc3= du point \let[3] par rapport à la droite &#40;}
\text{enonc4= &#41;.}
\text{rep1=\let[4]}
\text{rep2=le symétrique}
\text{rep3=\let[1]\let[2]|\let[2]\let[1]}
\integer{s1=2}
\integer{s2=12}
\integer{s3=2}
#endif
#if defined TARGET_oefvocsym3
\title{TITRE 3}
\text{enonc1=Les points \let[3] et \let[4] sont }
\text{enonc4=&#40;\let[1]\let[2]&#41;.}
\text{rep1=symétriques}
\text{rep2=par rapport}
\text{rep3=à la droite|à l'axe}
\integer{s1=12}
\integer{s2=12}
\integer{s3=12}
#endif
#if defined TARGET_oefvocsym4
\title{TITRE 4}
\text{enonc1=Le point \let[4] est }
\text{enonc2= du point \let[3]}
\text{enonc4=&#40;\let[1]\let[2]&#41;.}
\text{rep1=le symétrique}
\text{rep2=par rapport}
\text{rep3=à la droite|à l'axe}
\integer{s1=12}
\integer{s2=12}
\integer{s3=12}
#endif
#if defined TARGET_oefvocsym5
\title{TITRE 5}
\text{enonc1=La droite &#40;\let[1]\let[2]&#41; est la médiatrice du segment [\let[3]\let[4]]
donc la droite &#40;\let[1]\let[2]&#41; est}
\text{enonc2= de}
\text{enonc3= du}
\text{enonc4=[\let[3]\let[4]].}
\text{rep1=l'axe}
\text{rep2=symétrie}
\text{rep3=segment}
\integer{s1=12}
\integer{s2=12}
\integer{s3=12}
#endif

\text{geom=draw(300,300
segment 0,300,300,0,red
segment 75,215,85,225,black
segment 75,225,85,215,black
segment 70,105,80,95,black
segment 70,95,80,105,black
segment 255,45,245,55,black
segment 255,55,245,45,black
segment 194,219,204,229,black
segment 194,229,204,219,black
segment 75,100,199,224,black
circle 106,131,8,red
circle 168,193,8,red
segment 130,155,137,148,red
segment 137,148,144,155,red
text black,60,100,medium,\let[3]
text black,85,225,medium,\let[2]
text black,255,55,medium,\let[1]
text black,184,225,medium,\let[4]
)}

\statement{
<div class="wims_columns">
  <div class="medium_size">
    <img src="\geom" alt="">
  </div>
  <div class="medium_size">
  <label for="reply1">\enonc1</label> \embed{r1,\s1}
  <label for="reply2">\enonc2</label> \embed{r2,\s2}
  <label for="reply3">\enonc3</label> \embed{r3,\s3}
  \enonc4
  </div>
</div>
}

\answer{}{\rep1}{type=text}
\answer{}{\rep2}{type=text}
\answer{}{\rep3}{type=text}
