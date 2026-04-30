target=convertirp3

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}


\text{size=20x25x}
\integer{basep=row(1,\confparm4)}
\text{S=row(3,\confparm4)}
\text{S=item(1 to \basep,\S)}

\text{p=randint(3..5)}
\text{N=randint(1..\basep-1)}
\for{k=1 to \p}{
 \integer{n=randint(1..\basep-1)}
 \text{N=\basep*(\N)+\n}
}
\integer{t=\N}
\text{a=texmath(\N)}
\text{n=slib(basep \t,\S)}
\text{rep=slib(char2item \n)}
\integer{maxchar=items(\rep)}

\text{size=\size\maxchar}



#include "lang.inc"

\statement{
\txtstatement1<p>
\txtstatement2</p>
<table class="wimscenter wimsborder">
 <tr><th>\txtbaseten</th><th>\txtbase \basep</th></tr>
 <tr><td>\(\a) </td><td> \embed{r1,\size}</td></tr>
</table>
}

\answer{}{\rep;\S}{type=clickfill}
