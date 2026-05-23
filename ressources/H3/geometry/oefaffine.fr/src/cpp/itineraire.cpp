target=itineraire
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{n=randint(7..10)}
\text{liste=-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6}
\text{point=shuffle(A,B,C,D,E,F,G,H,J,K)}
\text{A=item(1,\point)}
\text{B=item(\n,\point)}
\text{C=item([2..\n-1],\point)}
\text{C1=shuffle(\C)}
\text{a=shuffle(\liste)}s
\text{a1=item(1,\a)}
\text{dessin=xrange -7.2,7.2
yrange -7.2,7.2
parallel -7,-7,7,-7,0,1,16, grey
parallel -7,-7,-7,7,1,0,16, grey
hline 0,0,black
arrow 0,0,1,0,8, black
arrow 0,0,0,1,8, black
vline 0,0,black
}
\for{i=1 to \n}{
\integer{j=\i%2}
\if{\j=0}{
	\text{a1=item(\i+1,\a)}
	}{
\text{a2=item(\i+1,\a)}
}
\text{pt=item(\i,\point)}
\text{dessin=\dessin
disk \a1,\a2,8,blue
text black,\a1,\a2-0.2,medium,\pt}}

\statement{\name_enonce:
<div class="wimscenter"> \draw{300,300}{\dessin
}
</div>
\name_question
<div class="wimscenter"> <label for ="reply1">\(\A) </label>,
\embed{reply 1,20}, \(\B\) </div>
<div class="wims_instruction">\name_inst</div>
}
\answer{Itinéraire}{\C}{type=atext}
