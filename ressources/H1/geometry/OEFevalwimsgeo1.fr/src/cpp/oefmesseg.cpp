target=oefmesseg1 oefmesseg2 oefmesseg3 oefmesseg4 oefmesseg5

#define TITRE Mesure d'un segment
\language{fr}
\author{Jean-Luc, Donadoni}
\email{jluc.donadoni@laposte.net}
\format{html}
\precision{100000}
\text{name_quest= Mesurez sur votre cahier et donner la réponse&nbsp;}

\text{nom=shuffle(A,B,C,E,F,G,R,S,T)}
\real{e=0.1}
\integer{y=150}
\integer{x1=20}
\integer{d1=randint(20..99)}
\integer{d2=randint(110-\d1..220-\d1)}
\integer{x2=\x1+\d1}
\integer{x3=\x2+\d2}
\text{dess=draw(300,300
linewidth 1
segment \x1,\y+4,\x1,\y-4,black
text black,\x1,\y-20,medium,\nom[1]
segment \x2,\y+4,\x2,\y-4,black
text black,\x2,\y-20,medium,\nom[2]
segment \x3,\y+4,\x3,\y-4,black
text black,\x3,\y-20,medium,\nom[3]
segment \x1,\y,\x3,\y,black
)}
#if defined TARGET_oefmesseg1
\title{TITRE 1}
\integer{dd1=\d1/10}
\integer{dd2=\d2/10}
\text{enonc=Nous avons trois points \nom[1], \nom[2] et \nom[3] alignés.
<br>\nom[1]\nom[2] = \dd1 cm et \nom[2]\nom[3] = \dd2 cm}
\text{segment=\nom[1]\nom[3]}
\integer{rep=\dd1 + \dd2}
#endif
#if defined TARGET_oefmesseg2
\title{TITRE 2}
\integer{dd1=\d1/10}
\integer{dd2=\d2/10}
\integer{dd=\dd1+\dd2}
\text{enonc=Nous avons trois points \nom[1], \nom[2] et \nom[3] alignés.
<br>\nom[1]\nom[3] = \dd cm et \nom[2]\nom[3] = \dd2 cm}
\text{segment=\nom[1]\nom[2]}
\integer{rep=\dd1}
#endif
#if defined TARGET_oefmesseg3
\title{TITRE 3}
\real{dd1=\d1/10}
\real{dd2=\d2/10}
\text{enonc=Nous avons trois points \nom[1], \nom[2] et \nom[3] alignés.
<br>\nom[1]\nom[2] = \dd1 cm et \nom[2]\nom[3] = \dd2 cm}
\text{quest= Mesurez sur votre cahier et donnez la réponse :}
\text{segment=\nom[1]\nom[3]}
\real{rep=\dd1 + \dd2}
#endif
#if defined TARGET_oefmesseg4
\title{TITRE 4}
\real{dd1=\d1/10}
\real{dd2=\d2/10}
\real{dd=\dd1+\dd2}
\text{enonc=Nous avons trois points \nom[1], \nom[2] et \nom[3] alignés.
<br>\nom[1]\nom[3] = \dd cm et \nom[2]\nom[3] = \dd2 cm}
\text{quest= Mesurez sur votre cahier et donnez la réponse&nbsp;}
\text{segment=\nom[1]\nom[2]}
\real{rep=\dd1}
#endif

#if defined TARGET_oefmesseg5
\title{TITRE 5}
\integer{x=50}
\integer{y=250}
\integer{d1=randint(50..180)}
\integer{d2=randint(50..180)}
\integer{x2=\x+\d1}
\integer{y3=\y-\d2}
\text{dess=draw(300,300
linewidth 1
text black,\x-10,\y,medium,\nom[1]
text black,\x2+10,\y,medium,\nom[2]
text black,\x,\y3-20,medium,\nom[3]
segment \x,\y,\x2,\y,black
segment \x,\y,\x,\y3,black
segment \x2,\y,\x,\y3,black
square \x,\y-10,10,black)}

\real{dd1=\d1/10}
\real{dd2=\d2/10}
\integer{dd=sqrt(\d1^2+\d2^2)}
\real{dd=\dd/10}
\text{enonc=Nous avons trois points \nom[1], \nom[2] et \nom[3].
<br>Les droites (\nom[1]\nom[2]) et (\nom[1]\nom[3]) sont perpendiculaires.
<br>\nom[1]\nom[2] = \dd1 cm et \nom[1]\nom[3] = \dd2 cm}
\text{segment=\nom[2]\nom[3]}
\real{e=0.2}
\real{rep=\dd}
#endif

\statement{
<div class="wims_columns">
 <div class="medium_size img_col"><img src="\dess" alt=""></div>
 <div class="medium_size text_col">
 <div>Reproduisez le dessin suivant avec les bonnes dimensions sur
   le cahier de brouillon.</div>
  <div>\enonc</div>
  \name_quest:
  <div><label for="reply1">\segment =</label> \embed{r1,5} cm.</div>
</div></div>
}
\answer{}{\r}{type=numeric}
\condition{mesure}{\r<=\rep+\e and \r>=\rep-\e}
