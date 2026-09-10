target=oefecritvoc1 oefecritvoc2 oefecritvoc3 oefecritvoc4 oefecritvoc5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{chiffre=shuffle(9)}
#if defined TARGET_oefecritvoc1
\integer{n=randint(3..7)}
\integer{n1=randint(1..\n)}
\integer{large=5}
\text{\nb=}
\for{a=1 to \n}{\text{nb=wims(append item \chiffre[\a] to \nb)}}
\integer{res=0}
\for{i=1 to \n}
{\integer{res=\res+\nb[\i]*10^(\n-\i)}}
\text{enonc=\name_enonc[1] \res, \name_enonc[2] \ord[\n-\n1+1] \name_enonc[3] }
\text{rep=\chiffre[\n1]}
#endif
#if defined TARGET_oefecritvoc2
\integer{n=randint(3..7)}
\integer{n1=randint(1..\n)}
\integer{large=18}
\text{\nb=}
\for{a=1 to \n}{\text{nb=wims(append item \chiffre[\a] to \nb)}}
\integer{res=0}
\for{i=1 to \n}
{\integer{res=\res+\nb[\i]*10^(\n-\i)}}
\text{enonc=\name_enonc[1] \res, \chiffre[\n1] \name_enonc[2] }
\text{rep=\ord[\n-\n1+1]}
#endif
#if defined TARGET_oefecritvoc3
\integer{n=randint(3..4)}
\integer{n1=randint(1..9)}
\integer{large=5}
\text{\nb=}
\for{a=1 to \n}{\text{nb=wims(append item \chiffre[\a] to \nb)}}
\integer{res=0}
\for{i=1 to \n}
{\integer{res=\res+\nb[\i]*10^(\n-\i)}}
\text{enonc=\name_enonc[1] \res, \name_enonc[2] \ord[\n1] \name_enonc[3] }
\if{\n1>\n}{\text{rep=0}}{\text{rep=\chiffre[\n-\n1+1]}}
#endif
#if defined TARGET_oefecritvoc4
\integer{large=5}
\integer{n=randint(3..8)}
\integer{n1=randint(1..\n-1)}
\text{\nb=}
\for{a=1 to \n}{\text{nb=wims(append item \chiffre[\a] to \nb)}}
\integer{res=0}
\for{i=1 to \n}
{\integer{res=\res+\nb[\i]*10^(\n-\i)}}
\text{enonc=\name_enonc[1] \res, \name_enonc[2] \ord[\n-\n1+1] \name_enonc[3]}
\integer{rep=floor(\res/10^(\n-\n1))}
#endif
#if defined TARGET_oefecritvoc5
\integer{n=randint(3..7)}
\integer{n1=randint(1..\n-1)}
\integer{large=18}
\text{\nb=}
\for{a=1 to \n}{\text{nb=wims(append item \chiffre[\a] to \nb)}}
\integer{res=0}
\for{i=1 to \n}
{\integer{res=\res+\nb[\i]*10^(\n-\i)}}
\integer{part=floor(\res/10^(\n-\n1))}
\text{enonc=\name_enonc[1] \res, \part \name_enonc[2] }
\text{rep=\ord[\n-\n1+1]}
#endif
\statement{
\name_complete: \enonc \embed{r1,\large}.}
\answer{}{\rep}{}
\latex{
\begin{statement}
\name_complete: \enonc \(\dots\dots\).
\end{statement}
}
