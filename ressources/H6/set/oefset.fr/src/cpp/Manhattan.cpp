target=Manhattan
#define GGG C5 -
\title{GGG Distance de Manhattan}
\author{Sophie, Lemaire}
\email{sophie.lemaire@universite-paris-saclay.fr}
\computeanswer{yes}
\description{exercice de modélisation comportant deux questions dont une de dénombrement.}
\observation{exercice de dénombrement d'un ensemble de chemins. Un codage des chemins est suggéré dans un feedback.}
#include "common.inc"
#include "css.inc"

\precision{100000}
\integer{a1=randint(1..50)}
\integer{da=randint(2..10)}
\integer{n1=randint(1..50)}
\integer{dn=randint(2..10)}
\integer{sa=random(0,1)}
\integer{sn=random(0,1)}
\integer{n2=\n1+\dn}
\integer{a2=\a1+\da}
\if{\sn=0}{
 \integer{x1=\n1*10}
 \integer{x2=\n2*10}
 \text{sign=+}
 }
 {\integer{x1=\n2*10}
 \integer{x2=\n1*10}
 \text{sign=-}
}
\text{siga=+}
\if{\sa=1}{
 \integer{v=\a1}
 \integer{a1=\a2}
 \integer{a2=\v}
 \text{siga=-}
 }
\integer{c=\da+\dn}
integer{nb=\c!/\da!*\dn!}
\integer{nb=binomial(\c,\da)}

Dessin
\integer{x1v=\x1+10}
\integer{a1v=\a1-1}

#include "lang_Manhattan_fr.inc"
\if{\lang=it}{
#include "lang_Manhattan_it.inc"
}
\if{\lang=es}{
#include "lang_Manhattan_es.inc"
}

\text{dessin=draw(190,190
frect 10,10,60,60,gray
frect 70,10,120,60,gray
frect 130,10,180,60,gray
frect 10,70,60,120,gray
frect 70,70,120,120,gray
frect 130,70,180,120,gray
frect 10,130,60,180,gray
frect 70,130,120,180,gray
frect 130,130,180,180,gray
fcircle 70,70,5,red
fcircle 130,130,5,green
text black, 10,60,,avenue \a1
text black, 75,65,, \x1
text black, 10,120,,avenue \a1v
text black, 135,125,, \x1v)}
\steps{reply1
reply2}
\statement{<div class="color1">
\pointv.
\point2.
</div>
\warning
<div class="wims_question">
<ol><li>
\if{\step>=1}{\question1 ?}
\if{\step=1}{\embed{reply1,6}}
</li>
\if{\step>1}{
<span class="oef_indgood">
\name_good
</span>
</li><li>
\question2?
\embed{reply2,10}
</li>}
</ol>
</div>
}
\answer{1- \label[1;]}{\c}{type=numeric}
\answer{2- \label[2;]}{\reponse2}{type=numeric}
answer{Nb de parcours différents }{\nb}{type=formal}
\integer{r=pari(if(\reponse2-\nb,0,1))}
\condition{}{\r=1}{option=hide}
\real{ec1=\reply1-floor(\reply1)}
\integer{ar=\a1\siga min(\reply1,\da)}
\integer{nr=\x1 \sign 10*max(\reply1-\da,0)}

\hint{ \name_hint <div class="wimscenter"><img src="\dessin" alt=""></div>}

#include "lang_Manhattan_feed_fr.inc"
\if{\lang=it}{
#include "lang_Manhattan_feed_it.inc"
}
\if{\lang=es}{
#include "lang_Manhattan_feed_es.inc"
}

\feedback{\reply1>\c and \ec1=0}{<div class="oef_indbad">
\name_feed1
</div>}
\feedback{\reply1<\c and \ec1=0}{<div class="oef_indbad">
\name_feed2
</div>}

\feedback{\r=1 and \step>1}{<div class="oef_indgood">
\name_feed3[1;]</div>}
\feedback{\r=0 and \step>1}{<div class="oef_indbad">
\name_feed3[2;]</div>
\name_hint2
}
