target=trajet1
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{range=20}
\text{S=0,randint(1..9)}
\text{mid=randint(8..14)}
\text{ecran=\mid,randitem(randint(2..5),randint(6,8)),\mid,10}

\text{obj=randint(\mid+2..\range-2),randint(2..8)}
\real{ecrany=\S[2]+(\obj[2]-\S[2])/(\obj[1]-\S[1])*\ecran[1]}
\if{pari(abs(\ecrany-\ecran[2]))<4}{
  \real{tmp=\ecrany+randitem(1,-1)}
  \text{ecran=\mid,\tmp,\mid,10}
}
\real{test=(\S[1]-\ecran[1])*(\obj[2]-\ecran[2])-(\S[2]-\ecran[2])*(\obj[1]-\ecran[1])}
\text{obs=randint(\mid+2..\range-2),10}

\text{dessin=xrange -2,\range+2
yrange -2,12
frectangle 0,0,\range,10, grey}

\text{dessin=\dessin
linewidth 6
crosshair \S,yellow
text black,-1,\S[2],large,S
segment \ecran,black
linewidth 2
crosshair \obj,black
text black,\obj[1],\obj[2],large,A
crosshair \obs,blue
text blue,\obs[1],\obs[2],large,B
}
\text{rep=\test>0? 1:2}
\if{\test>0}{
  \text{dessinfeed=linewidth 1
arrow \S,\obj,10,yellow
arrow \obj,\obs,10,yellow}
}{
\text{dessinfeed=linewidth 1
arrow \S,\mid,\ecrany,10,yellow}
}

\statement{\name_enonce
<div class="wimscenter">
\canvasdraw{400,200}{
\dessin
userdraw segment,blue}
</div>
<div class="wims_question">
\name_question \embed{r1,1},\embed{r1,2}
</div>
<div class="wims_instruction">\name_hint</div>
}
\answer{}{\rep;\name_yesno}{type=radio}
\feedback{1=1}{\canvasdraw{400,200}{
\dessin
\dessinfeed}
}
