target=equationD1 equationD2 equationD3 equationD4 equationD5
#include "author.inc"

#define TITRE Résolution équation
#if defined TARGET_equationD1
# define NUM D1
#endif
#if defined TARGET_equationD2
# define NUM D2
#endif
#if defined TARGET_equationD3
# define NUM D3
#endif
#if defined TARGET_equationD4
# define NUM D4
#endif
#if defined TARGET_equationD5
# define NUM D5
#endif
\title{TITRE NUM}


\text{x=x}
\text{ch=wims(values v for v=1 to 10)}
\text{ch=shuffle(\ch)}

#if defined TARGET_equationD1
 \integer{sga=1}
 \integer{sgb=1}
 \integer{sgc=1}
 \integer{sgd=1}
#endif

#if defined TARGET_equationD2
 \integer{sga=1}
 \integer{sgb=-1}
 \integer{sgc=1}
 \integer{sgd=1}
#endif
#if defined TARGET_equationD3
 \integer{sga=-1}
 \integer{sgb=1}
 \integer{sgc=1}
 \integer{sgd=1}
#endif
#if defined TARGET_equationD4
 \integer{sga=-1}
 \integer{sgb=-1}
 \integer{sgc=1}
 \integer{sgd=1}
#endif
#if defined TARGET_equationD5
 \integer{sga=-1}
 \integer{sgb=-1}
 \integer{sgc=-1}
 \integer{sgd=1}
#endif

\integer{a=\ch[1]*\sga}
\integer{b=\ch[2]*\sgb}
\integer{c=\ch[3]*\sgc}
\integer{d=\ch[4]*\sgd}
\text{m1=texmath(\a*\x+\b)}
\text{m2=texmath(\c*\x+\d)}
\text{m=shuffle(\m1,\m2)}
\text{enonce=\m[1] = \m[2]}
\text{rep=simplify(((\d)-(\b))/((\a)-(\c)))}

\statement{
  Quelle est la solution de l'équation suivante :
<div class="wimscenter">\(\enonce)</div>

<b>Votre réponse :</b>
<div><label for="reply1">La solution de cette équation est</label> \embed{r1,7}.</div>}

\answer{Réponse}{\rep}{type=numexp}{option=noreduction}
