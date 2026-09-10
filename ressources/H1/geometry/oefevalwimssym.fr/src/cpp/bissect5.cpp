target=oefbissect5
#include "lang.inc"
#define NUM 5
#include "lang_titles.inc"
#include "author.inc"

\keywords{angle_bisector}

\text{nom=shuffle(A,B,C,E,F,G,H,J,K,L,M,N,R,S,T)}

\text{dessin=}
\for{i=0 to 9}{
  \integer{ang=\i*20}
  \text{dessin=\dessin
  segment 0,0,cos(\ang*pi/180)*9,sin(\ang*pi/180)*9,black
  text black,cos((\ang+9-\i)*pi/180)*6,sin((\ang+9-\i)*pi/180)*6,medium,\nom[2+\i]
  segment cos((\ang)*pi/180)*5-0.2*sin((\ang)*pi/180),sin((\ang)*pi/180)*5+0.2*cos((\ang)*pi/180),cos((\ang)*pi/180)*5+0.2*sin((\ang)*pi/180),sin((\ang)*pi/180)*5-0.2*cos((\ang)*pi/180),black}
}

\text{dessin=draw(400,200
xrange -10,10
yrange -1,10
\dessin
text black,0,-0.2,medium,\nom[1])}

\integer{a=randint(2..9)}
\integer{b=\a+randint(1..(11-\a)/2)*2}
\text{enonc=\(\widehat{\nom[\a]\nom[1]\nom[\b]})}
\integer{c=(\a+\b)/2}
\text{rep=\nom[1]\nom[\c]}
\text{fig=<img src="\dessin" alt="">}

\statement{
<div class="wimscenter">\fig</div>
  \name_stat[1;]
  <div class="spacer"><label for="reply1">\name_stat[2;1] \enonc
\name_stat[2;2]</label> &#91;\embed{r1,2}&#41;.
  </div>
}

\answer{}{\rep}{type=raw}
