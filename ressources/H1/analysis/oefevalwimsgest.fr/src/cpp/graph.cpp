target=oefgraph1 oefgraph2
#include "author.inc"
#if defined TARGET_oefgraph1
# define NUM 1
#endif
#if defined TARGET_oefgraph2
# define NUM 2
#endif
#include "lang_titles.inc"
#include "lang.inc"

\precision{10000}
\text{ss=100}
#if defined TARGET_oefgraph1
\integer{s=randint(5..12)}
\text{s=\s,randint(25..40),randint(\s+1..16)}
\real{ss=\ss-\s[1]-\s[2]-\s[3]}
\text{s=\s,\ss}
\text{ss=100}
\text{u2=randint(8..40)}
\text{s2=\u2}
\real{ss=\ss-\u2}
\text{s2=\s2,\ss}
#endif
#if defined TARGET_oefgraph2
\integer{s1=randint(5..12)}
\integer{s3=randint(\s1+1..16)}
\integer{s2=randint(25..45)}
\integer{s4=\ss-\s1-\s2-\s3}
\if{\s4=\s2}{
  \integer{\s4=\s4+1}
  \integer{\s2=\s2-1}
}
\text{s=\s1,\s2,\s3,\s4}

\text{u2=randint(8..40)}
\text{s2=\u2}
\real{ss=\ss-\u2}
\text{s2=\s2,\ss}
#endif
\text{listecouleur=skyblue,red,yellow,lightgreen}
\text{pos=randint(1..\n)}

\text{dessin= ellipse 0,0,2,2,black
segment 0,0,1,0,black}

\text{anglet=0}
\for{i=1 to 4}{
\real{angle=item(\i,\s)*2*pi/100}
\real{point=\anglet+\angle/2}
\text{couleur=item(\i,\listecouleur)}
\real{anglet=\anglet+\angle}

\text{dessin=\dessin
segment 0,0,cos(\anglet),sin(\anglet),black
fill cos(\point)/2,sin(\point)/2, \couleur
text black,-0.4,1.4,large,\name_reps[7]}
\text{dessin=\dessin
text black, 2*cos(\point)/3,2*sin(\point)/3, medium, item(\i,\s)%
text black, 3.4*cos(\point)/3,3.4*sin(\point)/3, medium, item(\i,\listeabr)
}}

\text{dessin2= ellipse 0,0,2,2,black
segment 0,0,1,0,black}
\text{anglet2=0}
\for{i=1 to 2}{
  \real{angle2=item(\i,\s2)*2*pi/100}
  \real{point2=\anglet2+\angle2/2}
  \text{couleur2=item(\i,\listecouleur)}
  \real{anglet2=\anglet2+\angle2}

  \text{dessin2=\dessin2
  segment 0,0,cos(\anglet2),sin(\anglet2),black
  fill cos(\point2)/2,sin(\point2)/2, \couleur2
  text black,-0.4,1.4,large,\name_reps[6]}
  \text{dessin2=\dessin2
text black, 2*cos(\point2)/3,2*sin(\point2)/3, medium, item(\i,\s2)%
text black, 3.4*cos(\point2)/3,3.4*sin(\point2)/3, medium, item(\i,\listeabr)
}}
#if defined TARGET_oefgraph1
\matrix{reps=\name_reps[1],\s[1],\name_reps[5]
\name_reps[2],\s[2],\name_reps[5]
\name_reps[3],\s[3],\name_reps[5]
\name_reps[4],\s[4],\name_reps[5]
\name_reps[1],\s2[1],\name_reps[6]
\name_reps[2],\s2[2],\name_reps[6]}
\integer{a=randint(1..6)}
\text{reps=row(\a,\reps)}
#endif
#if defined TARGET_oefgraph2
\text{reps=\name_reps[1..4]}
\integer{rep2=2}
\if{\s[2]<\s[4]}{\integer{rep1=4}}{\integer{rep1=2}}
#endif

\statement{
\name_instruction1
<p>\name_instruction2</p>
<div class="wimscenter">
\name_liste
</div>
<div class="wimscenter">
 \draw{300,300}{
xrange -1.5,1.5
yrange -1.5,1.5
\dessin
}
\draw{300,300}{
xrange -1.5,1.5
yrange -1.5,1.5
\dessin2
}
</div>
#if defined TARGET_oefgraph1
<label for="reply1">\name_question[1] \reps[1]
  \name_question[2] \reps[3]</label> ?
\embed{r1,5}&nbsp;%
#endif
#if defined TARGET_oefgraph2
\name_question[1]
<ul><li>\name_question[2]: \embed{r1}</li>
<li>\name_question[3]: \embed{r2}</li></ul>
#endif
}
#if defined TARGET_oefgraph1
\answer{}{\reps[2]}{type=numeric}
#endif
#if defined TARGET_oefgraph2
\answer{}{\rep1;\reps}{type=menu}
\answer{}{\rep2;\reps}{type=menu}
#endif
