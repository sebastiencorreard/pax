target=vocangle1

\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
\matrix {angle = A E B,E B A,\comp,1
A E B,E B C,\alt,4
A B E,E B C,\comp,1
A E C,C E D,\supp,2
B F C,C F E,\supp,2
F E C,E C D,\alt,4
B C F,E D C,\rien,6
A B E,A E B,\comp,1
A E B,E D C,\corr,5
E D C,D C B,\supp,2}
\integer{n=random(1..10)}
\text{mot=randomrow(\angle)}
\text{\ang1=item(1,\mot)}
\text{\ang2=item(2,\mot)}
\text{\rep=item(4,\mot)}
 #include "lang.inc"
\statement{<div class="wims_columns">
<div class="medium_size text_col">
\draw{200,200}{
xrange -20,20
yrange -20,20
triangle -15,-11,-15,11,0,11,black
triangle 0,11,4,-11,-9,-2.2,black
triangle -15,-11,-9,-2.2,4,-11,black
triangle 0,11,19,11,4,-11,black
segment -4,-7,-2,-5,red
segment -5,6,-3,4,red
text black,-17,13,medium,A
text black,-17,-10,medium,B
text black,6,-10,medium,C
text black,18,14,medium,D
text black,0,14,medium,E
text black,-11,0,medium,F
}
</div>
<div class="medium_size text_col">
\name_info_voc1
<div class="spacer">
\name_quest \embed{r1}.
</div></div></div>}

\answer{}{\rep;\comp,\supp,\opp,\alt,\corr,\rien}{type=menu}
