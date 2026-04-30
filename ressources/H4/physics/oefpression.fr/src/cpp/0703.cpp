target=0703
#include "author.inc"
#include "lang_0703b.inc"
\title{TITLE}
\title_en{TITLE_en}
\real{poids=randint(200..500)}
\real{surface=random(15,20,25,30,35,40,45,50,55,60)/10000}
\real{f1=\poids*10}
\real{f2=\poids*\surface}
\real{f3=\surface*1000000}
\real{f4=\poids/\surface}
\integer{casf=randint(1..4)}
\text{formules=\casf==4?\f1,\f2,\f3,\f4}
\text{formules=\casf==3?\f4,\f3,\f2,\f1}
\text{formules=\casf==2?\f3,\f1,\f4,\f2}
\text{formules=\casf==1?\f2,\f4,\f1,\f3}
\text{reponse=\casf==4?4}
\text{reponse=\casf==3?1}
\text{reponse=\casf==2?3}
\text{reponse=\casf==1?2}
\text{image=\imagedir/serie_700_table4.jpg}

\statement{
<div class="float_left spacer"><img src="\image" alt="" style="height:248px;width:184px"></div>

#include "lang_0703.inc"
}
\answer{}{\reponse;\formules}{type=checkbox}
