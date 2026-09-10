target=oefutigraph5
#include "author.inc"
\precision{10000}
#define NUM 5
#include "lang_titles.inc"
#include "lang.inc"
\integer{a=randint(1..4)}
\integer{n=randint(15..40)*20}

\text{ss=100}
\integer{s=random(5,10,15,20,25,30)}
\text{s=\s,random(5,10,15,20,25,30),randint(5,10,15,20,25,30)}
\real{ss=\ss-\s[1]-\s[2]-\s[3]}
\text{s=\s,\ss}

\integer{rp=\n*\s[\a]/100}

\text{ss=100}
\text{u2=randint(8..40)}
\text{s2=\u2}
\real{ss=\ss-\u2}
\text{s2=\s2,\ss}

\text{listecouleur=skyblue,red,yellow,lightgreen}
\text{pos=randint(1..\n)}

\text{dessin= ellipse 0,0,2,2,black
segment 0,0,1,0,black
text black,-1,1.4,large,\name_choixcouleur}

\text{anglet=0}
\for{i=1 to 4}{
  \real{angle=item(\i,\s)*2*pi/100}
  \real{point=\anglet+\angle/2}
  \text{couleur=item(\i,\listecouleur)}
  \real{anglet=\anglet+\angle}
  \text{dessin=\dessin
segment 0,0,cos(\anglet),sin(\anglet),black
fill cos(\point)/2,sin(\point)/2, \couleur}
\text{dessin=\dessin
text black, 3.3*cos(\point)/3,3.3*sin(\point)/3, large, item(\i,\listeabr)
text black, 2.2*cos(\point)/3,2.2*sin(\point)/3, medium, item(\i,\s)%

}}
\text{pic=draw(300,300
xrange -1.5,1.5
yrange -1.5,1.5
\dessin)}
#include "solution.inc"
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">
  <img src="\pic" alt="">
  </div>
  <div class="medium_size text_col">
  \name_instruction \n \name_pupil.
  <div class="spacer">
  <label for="reply1">\name_question \listefr[\a] ?</label>
  \embed{r1,5}</div>
  </div></div>
}

\answer{}{\rp}{type=numeric}
\solution{\sol}
