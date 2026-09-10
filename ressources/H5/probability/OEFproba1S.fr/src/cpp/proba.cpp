target=proba1 proba2 proba3

#include "header.inc"

\precision{10000}
\keywords{probability}

#if defined TARGET_proba1
# define NUM 1
#endif
#if defined TARGET_proba2
# define NUM 2
#endif
#if defined TARGET_proba3
# define NUM 3
#endif

#include "lang_titles.inc"

\integer{a=randint(1..80)}
\real{a=\a/100}
#if defined TARGET_proba1
\real{aetb=0}
\real{m=100-\a*100}
\integer{b=randint(1..\m)}
\real{b=\b/100}
#else
\integer{b=randint(1..80)}
\real{b=\b / 100}
\integer{m=\a>\b?\b*100:\a*100}
\integer{n=\a+\b>1?100*(\a+\b-1):1}
\integer{aetb=randint(\n..\m)}
\real{aetb=\aetb / 100}
#endif

#include "lang.inc"

\real{na=1-\a}
\real{nb=1-\b}
\real{aoub=\a+\b -\aetb}
\real{naetnb=1-\aoub}
\real{naounb=1-\aetb}
\real{aetnb=\a-\aetb}
\real{naetb=\na-\naetnb}
\real{aounb=\aetb+\aetnb+\naetnb}
\text{data=\(P(A) = \a,\)   \(P(B) = \b\) \name_and \(P(A \cup B)\) = \aoub,\(P(A \cap B)\),\aetb
\(P(A) = \a,\) \(P(B) = \b\) \name_and \(P(A \cap B)\) = \aetb,\(P(A \cup B)\),\aoub
\(P(A) = \a,\)  \(P(A \cup B) = \aoub\) \name_and \(P(A \cap B)\) = \aetb,\(P(B)\),\b
\(P(A) = \a,\)  \(P(B) = \b\) \name_and \(P(A \cup B)\) = \aoub,\(P(A \cap \bar{B})\),\aetnb
\(P(A) = \a,\)  \(P(B) = \b\) \name_and \(P(A \cup B)\) = \aoub,\(P(A \cup \bar{B})\),\aounb
\(P(A) = \a,\)  \(P(B) = \b\) \name_and \(P(A \cup B)\) = \aoub,\(P(\bar{A} \cup \bar{B})\),\naounb
\(P(A) = \a,\)  \(P(B) = \b\) \name_and \(P(A \cup B)\) = \aoub,\(P(\bar{A} \cap \bar{B})\),\naetnb
\(P(A) = \a,\)  \(P(B) = \b\) \name_and \(P(A \cap B)\) = \aetb,\(P(A \cap \bar{B})\),\aetnb
\(P(A) = \a,\)  \(P(B) = \b\) \name_and \(P(A \cap B)\) = \aetb,\(P(A \cup \bar{B})\),\aounb
\(P(A) = \a,\)  \(P(B) = \b\) \name_and \(P(A \cap B)\) = \aetb,\(P(\bar{A} \cup \bar{B})\),\naounb
\(P(A) = \a,\)  \(P(B) = \b\) \name_and \(P(A \cap B)\) = \aetb,\(P(\bar{A} \cap \bar{B})\),\naetnb
}
#if defined TARGET_proba1
\text{comp=  \name_incomp}
\text{data=\(P(A) = \a\) \name_and \(P(B) = \b\),\(P(A \cap B)\),\aetb
\(P(A) = \a\) \name_and \(P(B) = \b\),\(P(A \cup B)\),\aoub
\(P(A) = \a\) \name_and \(P(A \cup B) = \aoub\),\(P(B)\),\b
\(P(A) = \a\) \name_and \(P(B) = \b\),\(P(A \cap \bar{B})\),\aetnb
\(P(A) = \a\) \name_and \(P(B) = \b\),\(P(A \cup \bar{B})\),\aounb
\(P(A) = \a\) \name_and \(P(B) = \b\),\(P(\bar{A} \cup \bar{B})\),\naounb
\(P(A) = \a\) \name_and \(P(B) = \b\),\(P(\bar{A} \cap \bar{B})\),\naetnb
}
\text{cedata=randomrow(\data)}
#endif
#if defined TARGET_proba2
\text{comp=}
\integer{i=randint(1..3)}
\text{cedata=row(\i,\data)}
#endif
#if defined TARGET_proba3
\text{comp=}
\integer{i=randint(4..11)}
\text{cedata=row(\i,\data)}
\text{cedata=row(5,\data)}
#endif
\text{info=\cedata[1]}
\text{quest=\cedata[2]}
\real{rep=\cedata[3]}
\text{trace=<table><tr><td>&nbsp;</td><td> B </td><td> non B </td><td>total</td></tr>
<tr><td>A</td><td>\aetb</td><td>\aetnb</td><td>\a</td></tr>
<tr><td>non A</td><td>\naetb</td><td>\naetnb</td><td>\na</td></tr>
<tr><td>&nbsp;</td><td>\b</td><td>\nb</td></tr></table>}

\statement{
 \name_statement[1] \(P\) \name_statement[2] \(\Omega\;\) \name_statement[3] \comp \(A\) \name_and \(B\),
 \name_statement[4]:
<div class="wimscenter"> \info. </div>
<label for="reply1">\name_question \quest</label> = \embed{reply1,5}
}
\answer{\quest}{\rep}{type=numexp}{option=noreduction}

\latex{
\begin{statement}
\name_statement[1] \(P\) \name_statement[2] \(\Omega\;\) \name_statement[3] \comp \(A\) \name_and \(B\),
 \name_statement[4]:
\begin{center} \info. \end{center}
\name_question \quest. 
\end{statement}
}
