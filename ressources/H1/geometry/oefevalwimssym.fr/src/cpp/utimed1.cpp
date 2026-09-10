target=oefutimed1

#define NUM 1
#include "author.inc"
#include "lang_titles.inc"
\keywords{symmetry,perpendicular_bisector}
#include "dessinmed.inc"

\text{t1=La droite (d) est perpendiculaire à la droite (AB)}
\text{t2=et la droite (d) passe par le milieu du segment [AB] &#44;}
\text{t3=donc la droite (d) est la médiatrice du segment [AB].}
\text{rep1=\t1,\t2}
\text{rep2=\t3}
\text{size=320x40}
\statement{
#include "stat_utimed.inc"
}

\answer{}{\rep1}{type=dragfill}
\answer{}{\rep2}{type=dragfill}
