target=oefecritdec1 oefecritdec2 oefecritdec3 oefecritdec4 oefecritdec5

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000000}

#if defined TARGET_oefecritdec1
\text{chif=shuffle(9)}
\integer{a=randint(4..7)}
\integer{d=randint(1..\a-3)}
\integer{nb=0}
\for{i=1 to \a}{\integer{nb=\nb+\chif[\i]*10^(\a-\i)}}
\real{nb=\nb/10^\d}
\text{enonc=\name_enonc[1;] \nb. \name_enonc[2;]}
\integer{rep=floor(\nb)}
\integer{larg=8}
#endif
#if defined TARGET_oefecritdec2
\text{chif=shuffle(9)}
\integer{a=randint(4..7)}
\integer{d=randint(1..\a-1)}
\integer{nb=0}
\for{i=1 to \a}{\integer{nb=\nb+\chif[\i]*10^(\a-\i)}}
\real{nb=\nb/10^\d}
\text{enonc=\name_enonc[1;] \nb. \name_enonc[2;]}
\integer{rep=(\nb-floor(\nb))*10^\d}
\text{rep=0.\rep}
\integer{larg=8}
#endif
#if defined TARGET_oefecritdec3
\text{chif=shuffle(9)}
\integer{a=randint(4..7)}
\integer{d=randint(1..\a-1)}
\integer{nb1=0}
\for{i=1 to \a}{\integer{nb1=\nb1+\chif[\i]*10^(\a-\i)}}
\real{rep=\nb1/10^\d}
\integer{min=floor(\rep/10)*10}
\integer{max=ceil(\rep/10)*10}
\text{enonc=\name_enonc[1] \nb1 \name_enonc[2] \min \name_and \max.}
\integer{larg=10}
#endif
#if defined TARGET_oefecritdec4
\integer{a=randint(1..2)}
\text{chif=}
\for{i=1 to \a}{\text{chif=\chif 0}}
\integer{b=randint(1..2)}
\for{i=1 to \b}{\text{chif=\chif randint(1..9)}}
\integer{c=randint(1..2)}
\for{i=1 to \c}{\text{chif=\chif 0}}
\text{chif=\chif .}
\integer{d=randint(0..3-\c)}
\for{i=1 to \d}{\text{chif=\chif 0}}
\integer{e=randint(1..2)}
\for{i=1 to \e}{\text{chif=\chif randint(1..9)}}
\integer{f=randint(1..4-\d)}
\for{i=1 to \f}{\text{chif=\chif 0}}
\real{n=\chif}
\text{enonc=\name_enonc}
\text{rep=\n}
\integer{larg=15}
\text{chif=wims(nospace \chif)}
\text{enonc=\name_enonc[1] \chif \name_enonc[2]: }
#endif
#if defined TARGET_oefecritdec5
\text{chif=0}
\text{chif=\chif .}
\integer{d=randint(0..3)}
\for{i=1 to \d}{\text{chif=\chif 0}}
\integer{e=randint(1..2)}
\for{i=1 to \e}{\text{chif=\chif randint(1..9)}}
\integer{f=randint(1..5-\d)}
\for{i=1 to \f}{\text{chif=\chif 0}}
\text{chif=wims(nospace \chif)}

\real{n=\chif}
\text{enonc=\name_enonc[1] \chif \name_enonc[2]: }
\text{rep=\n}
\integer{larg=15}
#endif
\statement{
\enonc
\embed{r1,\larg}
}
\answer{}{\rep}{type=atext}
\latex{
\begin{statement}
\enonc:
\(\dots\dots\)
\end{statement}
}
