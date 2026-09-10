target=fracteq1a fracteq1b fracteq1c fracteq2a fracteq2b fracteq3a fracteq3b

#include "header.inc"
#define TIT Enaki ulomki
#if #TARGET (fracteq1a)
 \title{TIT Ia}
# define EQCNT 1
# define TAKELIST 2,1
#endif
#if #TARGET (fracteq1b)
 \title{TIT Ib}
# define EQCNT 1
# define TAKELIST 3,1,1
#endif
#if #TARGET (fracteq1c)
 \title{TIT Ic}
# define EQCNT 1
# define TAKELIST 2,1,1,1,1
#endif
#if #TARGET (fracteq2a)
 \title{TIT IIa}
# define EQCNT 2
# define TAKELIST 3,2,1
#endif
#if #TARGET (fracteq2b)
 \title{TIT IIb}
# define EQCNT 2
# define TAKELIST 2,2,1,1,1,1
#endif
#if #TARGET (fracteq3a)
 \title{TIT IIIa}
# define EQCNT 3
# define TAKELIST 2,2,2
#endif
#if #TARGET (fracteq3b)
 \title{TIT IIIb}
# define EQCNT 3
# define TAKELIST 3,2,2,1,1
#endif

\text{mulist=1,2,3,4,5,6}
#include "matrix.inc"

\text{choices=item(1..items(\data),TAKELIST,
 wims(values 0 for x=1 to 100))}
\text{choices=shuffle(\choices)}
\text{select=}
\for{f=1 to items(\data)}{
 \if{\choices[\f]>0}{
  \text{s1=\all[\f;1..\choices[\f]]}
  \text{select=wims(append item \s1 to \select)}
 }
}
\integer{selcnt=items(\select)}
\text{Select=}
\for{s in \select}{
 \text{s1=wims(replace internal / by \over in \s)}
 \text{Select=wims(append item \({\s1}) to \Select)}
}
\text{size=40x60x1}
\text{ch=item(EQCNT,dva, dva para, 
tri pare,)}
\text{zak=item(EQCNT,ki predstavljata, ki predstavljata, ki predstavljajo)}

\statement{Izmed spodnjih ulomkov izberite \ch, \zak
isto vrednost.

<p><center><table border=0>
#if EQCNT ==1
 <tr><td align=right>Ista vrednost:
 <td>\embed{r1,\size} <td> = <td>\embed{r2,\size}
#else
 <tr><td align=right>Prvi par:<td>\embed{r1,\size} <td> = <td>\embed{r2,\size}
 <tr><td align=right>Drugi par:<td>\embed{r3,\size} <td> = <td>\embed{r4,\size}
# if EQCNT > 2
  <tr><td align=right>Tretji par:<td>\embed{r5,\size} <td> = <td>\embed{r6,\size}
# endif
#endif
</table></center>
}

\text{empty=}
\text{os=wims(replace internal \over by / in \o1,\o2,\o3,\o4,\o5,\o6)}
\text{os=wims(text select /1234567890, in \os)}

\answer{Ulomek 1}{\o1;\Select[1],\Select[\EQCNT*2+1..\selcnt]}{type=dragfill}
\answer{Ulomek 2}{\o2;\Select[2]}{type=dragfill}
\text{eq1=pari((\os[1])-(\os[2]))}
\condition{\o1 = \o2 \empty}{\eq1 issametext 0}

#if EQCNT > 1
 \answer{Ulomek 3}{\o3;\Select[3]}{type=dragfill}
 \answer{Ulomek 4}{\o4;\Select[4]}{type=dragfill}
 \text{eq2=pari((\os[3])-(\os[4]))}
 \condition{\o3 = \o4 \empty}{\eq2 issametext 0}
# if EQCNT > 2
  \answer{Ulomek 5}{\o5;\Select[5]}{type=dragfill}
  \answer{Ulomek 6}{\o6;\Select[6]}{type=dragfill}
  \text{eq3=pari((\os[5])-(\os[6]))}
  \condition{\o5 = \o6 \empty}{\eq3 issametext 0}
# endif
#endif
