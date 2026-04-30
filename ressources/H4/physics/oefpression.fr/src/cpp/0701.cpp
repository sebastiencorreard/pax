target=0701

#include "author.inc"
#include "lang_0701.inc"
\title{TITLE}
\title_en{TITLE_en}
\text{u1=kg}
\text{u2=N}
\text{u3=Pa}
\text{u4=m}
\integer{casf=randint(1..4)}
\text{symboles=\casf==4?\u1,\u2,\u3,\u4}
\text{symboles=\casf==3?\u1,\u3,\u2,\u4}
\text{symboles=\casf==2?\u3,\u1,\u4,\u2}
\text{symboles=\casf==1?\u4,\u2,\u1,\u3}
\text{reponse=\casf==4?3}
\text{reponse=\casf==3?2}
\text{reponse=\casf==2?1}
\text{reponse=\casf==1?4}

\statement{
<p>
\name_question ?
</p>}
\answer{}{\reponse;\symboles}{type=checkbox}
