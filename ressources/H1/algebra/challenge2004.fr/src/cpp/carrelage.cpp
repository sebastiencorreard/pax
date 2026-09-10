target=carrelage carrelageb

#include "header.inc"

#if defined TARGET_carrelage 
\title{Carrelage a}
#endif
#if defined TARGET_carrelageb 
\title{Carrelage b}
#endif

\integer{cote=randint(15,20,25,30,35,40,45,50)}
\integer{sup1=\cote^2}
\integer{side=randint(500..800)}
\integer{lin=floor(\side/\cote/2)*2}
\integer{lin=\lin%10=0?\lin+2}
\integer{num=\lin^2}
\real{side=\lin*\cote/100}
\real{sup2=\side^2}

#if defined TARGET_carrelage 
\statement{
  Une salle carrée est carrelée avec des carreaux carrés. La salle a pour
  superficie \sup2 \(m^2). Il a fallu exactement \num carreaux pour carreler toute
  la salle sans coupe. Trouver la dimension d'un carreau :
<p>
  Le côté d'un carreau mesure \embed{r1,5} cm.
</p>
}

\reply{Le coté d'un carreau}{\cote}
#endif

#if defined TARGET_carrelageb 
\statement{
  Une salle carrée est carrelée avec des carreaux carrés. Chaque carreau mesure
\cote cm par coté. Il a fallu exactement \num carreaux pour carreler toute
  la salle sans coupe. Trouver la superficie de la salle :
<div class="wimscenter">
\embed{r1,7} \(m^2).
</div>
}

\reply{La superficie de la salle}{\sup2}
#endif

