target=oeffractlectplac1  oeffractlectplac2 oeffractlectplac3 oeffractlectplac4 oeffractlectplac5
#define TITRE Placer une fraction
\language{fr}
\range{-5..5}
\author{Jean-Luc, Donadoni}
\email{jluc.donadoni@laposte.net}
\computeanswer{no}
\format{html}
\precision{1000}

#if defined TARGET_oeffractlectplac1
\title{TITRE 1}
\integer{u1=2}
\integer{u2=10}
\integer{m=1}
\integer{m1=0}
\text{a=0}
\text{dessin=}
\for{i=\m1 to \m}{
    \integer{a=\i*1}
    \integer{s=\i}
    \text{dessin=\dessin
      text blue, \s,-1, medium,\a}}
\text{den=10}
\text{num=randint( 1..10)}
\rational{a=\num/\den}
#endif

#if defined TARGET_oeffractlectplac2
\title{TITRE 2}
\integer{u1=2}
\integer{u2=10}
\integer{m=3}
\integer{m1=0}
\text{a=0}
\text{dessin=}
\for{i=\m1 to \m}{
    \integer{a=\i*1}
    \integer{s=\i}
    \text{dessin=\dessin
      text blue, \s,-1, medium,\a}}
\text{den=10}
\text{num=randint( 11..29)}
\rational{a=\num/\den}
#endif

#if defined TARGET_oeffractlectplac3
\title{TITRE 3}
\integer{u1=0}
\integer{u2=randint(3..9)}
\integer{m=1}
\integer{m1=0}
\text{a=0}
\text{dessin=}
\for{i=\m1 to \m}{
    \integer{a=\i*1}
    \integer{s=\i}
    \text{dessin=\dessin
      text blue, \s,-1, medium,\a}}
\text{den=\u2}
\text{num=randint( 1..\u2)}
\rational{a=\num/\den}
#endif

#if defined TARGET_oeffractlectplac4
\title{TITRE 4}
\integer{u1=0}
\integer{u2=randint(3..9)}
\integer{m=3}
\integer{m1=0}
\text{a=0}
\text{dessin=}
\for{i=\m1 to \m}{
    \integer{a=\i*1}
    \integer{s=\i}
    \text{dessin=\dessin
      text blue, \s,-1, medium,\a}}
\text{den=\u2}
\text{num=randint( \u2+1..3*\u2-1)}
\rational{a=\num/\den}
#endif

#if defined TARGET_oeffractlectplac5
\title{TITRE 5}
\integer{u1=0}
\integer{u2=randitem(3,4,5,6,8,10)}
\integer{m=3}
\integer{m1=0}
\text{a=0}
\text{dessin=}
\for{i=\m1 to \m}{
    \integer{a=\i*1}
    \integer{s=\i}
    \text{dessin=\dessin
      text blue, \s,-1, medium,\a}}
\integer{den=\u2*2}
\integer{i=randint(1..3*\u2/2-1)}
\integer{num=\i*2+1}
\rational{a=\num/\den}
#endif

\text{gradu=draw(600,80
xrange \m1-0.1,\m+0.1
yrange -2,2.2
hline black,0,0
parallel \m1,-0.8,\m1,0.4,1/\u1,0, 40, blue
parallel \m1,-0.3,\m1,0.3,1/\u2,0, 200, blue
parallel \m1,-0.8,\m1,0.6,1,0, 40, red
\dessin)
}
\integer{dep=600/(\m*10+2)}
\integer{pos=\dep+(600-2*\dep)*\num/(\m*\den)}

\statement{
Nous avons une droite graduée. Placer le quotient
\(\frac{\num}{\den}) en cliquant sur l'axe gradué.
<div class="wimscenter">
\embed{r1}
</div>
}

\answer{numérateur}{\gradu;rectangle,\pos-3,35,\pos+3,45}{type=coord}
