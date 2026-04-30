target=0702

#include "author.inc"
#include "lang_0702b.inc"
\title{TITLE}
\title_en{TITLE_en}
\text{u1=are}
\text{u2=bar}
\text{u3=ha}
\text{u4=N}
\integer{casf=randint(1..4)}
\text{symboles=\casf==4?\u1,\u2,\u3,\u4}
\text{symboles=\casf==3?\u1,\u3,\u2,\u4}
\text{symboles=\casf==2?\u3,\u1,\u4,\u2}
\text{symboles=\casf==1?\u2,\u4,\u1,\u3}
\text{reponse=\casf==4?2}
\text{reponse=\casf==3?3}
\text{reponse=\casf==2?4}
\text{reponse=\casf==1?1}

\statement{
<p>
\name_question
 ?
</p>}
\answer{}{\reponse;\symboles}{type=checkbox}
