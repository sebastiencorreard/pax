target=oeffractlectgrad1 oeffractlectgrad2 oeffractlectgrad3 oeffractlectgrad4 oeffractlectgrad5
#define TITRE Lecture graphique
\language{fr}
\range{-5..5}
\author{Jean-Luc, Donadoni; Bernadette, Perrin-Riou}
\email{jluc.donadoni@laposte.net}
\computeanswer{no}
\format{html}
\precision{1000}

#if defined TARGET_oeffractlectgrad1
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

#if defined TARGET_oeffractlectgrad2
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

#if defined TARGET_oeffractlectgrad3
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

#if defined TARGET_oeffractlectgrad4
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

#if defined TARGET_oeffractlectgrad5
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

\statement{
Nous avons une droite graduée. Le point indiqué par la flèche
a pour abscisse le quotient de deux entiers.
<p>Donner ce quotient :</p>
<table class="wimscenter wimsnoborder">
<tr><td>\embed{reply1,3}</td></tr>
<tr><td><hr></td></tr>
<tr><td>\embed{reply2,3}</td></tr>
</table>
<div class="wimscenter">\draw{600,80}
{xrange \m1-0.1,\m+0.1
yrange -2,2.2
hline black,0,0
parallel \m1,-0.8,\m1,0.4,1/\u1,0, 40, blue
parallel \m1,-0.3,\m1,0.3,1/\u2,0, 200, blue
parallel \m1,-0.8,\m1,0.6,1,0, 40, red
\dessin
arrow \a,2,\a,0, 8, black
}</div>
}
\answer{numérateur}{\reply1}
\answer{dénominateur}{\reply2}
\text{test=round(\reply1)=\reply1 ? 1:0}
\condition{}{\test=1 and \reply1/\reply2=\a}
