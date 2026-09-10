target=righttriangle
#include "xiao.inc"
#include "lang_titles.inc"
#include "lang.inc"

\computeanswer{yes}
\format{html}
\precision{10000}

\integer{ab=randint(30..100)}
\integer{ac=random(\ab/4..\ab/2)}
\integer{speed=randint(2..20)}
\integer{r=random(10..30)}
\real{sol=\speed*\ac/sqrt(\ac^2+\ab^2)}
\integer{dir=randitem(1,2)}
\text{direction=\name_direction[\dir]}
\real{sol=\dir=1?\sol:-\sol}
\text{unit=random(cm,mm,m)}

\statement{\name_enonce[1], \name_enonce[2]
AB=\ab \unit, \name_enonce[3] AC \direction \name_enonce[4] \speed \unit/s.
\name_question[1] AC=\ac \unit, \name_question[2]
BC (en \unit/s)?
<div class="wimscenter"><img src="\imagedir/pic.gif" alt="image" /></div>
}

\answer{\name_answer \unit/s}{\sol}

