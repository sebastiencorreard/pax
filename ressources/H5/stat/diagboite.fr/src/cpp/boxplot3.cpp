target=3
#include "lang_boxplot.inc"
\title{TITRE}
\range{-5..5}

\computeanswer{no}
\precision{100}

\integer{xmin=randint(1..10)}
\integer{xmax=randint(\xmin+5..20)}
\integer{med=randint(\xmin+2..\xmax-2)}
\integer{q1=randint(\xmin+1..\med-1)}
\integer{q3=randint(\med+1..\xmax-1)}
\text{graph=slib(stat/boxplot [\xmin,\xmax,600,150], [\q1,\med,\q3],[f,f,f])}

\statement{
\name_instruction1
<div class="wimscenter">
\graph
</div>
\name_instruction2
<table class="wimsborder wimscenter">
<tr><th>\entete[2]</th><th>\entete[3]</th><th>\entete[4]</th></tr>
<tr><td>\embed{reply1,4}</td><td>\embed{reply2,4}</td><td>\embed{reply3,4}</td></tr>
</table>
}

\answer{\entete[2]}{\q1}{type=numexp}
\answer{\entete[3]}{\med}{type=numexp}
\answer{\entete[4]}{\q3}{type=numexp}
