target=rugby
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\language{fr}
\precision{2}
\computeanswer{no}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
L'essai est marqué à une distance c du poteau de corner
\integer{c=randint(1..24)}

Le joueur se met à une distance b de la ligne de fond
\integer{b=22+randint(0..8)}

a est la distance au milieu des poteaux
\real{a=sqrt(\b*\b+(35-\c)*(35-\c))}

aa est la distance au milieu du terrain
\real{aa=sqrt((50-\b)*(50-\b)+(35-\c)*(35-\c))}

aaa est la distance à l'entraineur
\real{aaa=sqrt((50-\b)*(50-\b)+(70-\c)*(70-\c))}
\matrix{data=\name_data[1], \a
\name_data[2], \aa
\name_data[3], \aaa}

this file is language dependent
\text{fname=rugby.png}

\text{L=randint(1..rows(\data))}
\text{question=\data[\L;1]}
\real{rep1=\data[\L;2]}
\integer{rep=round(\rep1)}
\statement{<p class="wimscenter">
<img src="\imagedir/\fname" alt="rugby"></p>
<p>
\name_enonce[1] \(c=\c\) \name_enonce[2] <br>
\name_enonce[3] \(b=\b) \name_enonce[4] <br>
\question ?</p>
<p class="wimscenter">\embed{r1}</p>
<p style="font-style:italic">\name_instruction</p>}

\answer{\name_answer}{\r}{type=numeric}{option=absolute}
\real{ecart=\reply1-\rep}

\condition{\name_cond1 }{abs(\ecart) <= 0.5}{weight=6}
\condition{\name_cond2 }{abs(\ecart)=0}{weight=4}
\feedback{ 1=1}{\name_feed[1] \(\rep) \name_feed[2]}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\condition{\name_cond3 }{(. notin \reply1) and (/ notin \reply1)}{weight=1}
