target=oefrang1 oefrang2 oefrang3 oefrang4 oefrang5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{1000000}
#if defined TARGET_oefrang1
\text{chif=shuffle(9)}
\integer{a=randint(4..7)}
\integer{d=randint(1..\a-3)}
\integer{r=randint(1..\a-\d)}
\integer{nb=0}
\for{i=1 to \a}{\integer{nb=\nb+\chif[\i]*10^(\a-\i)}}
\real{nb=\nb/10^\d}
\text{enonc=\name_enonc[1;] \nb.
  \name_enonc[2;1,2] \rangent[\r] ?}
\integer{rep=\chif[\a-\d-\r+1]}
\integer{larg=4}
#endif
#if defined TARGET_oefrang2
\text{chif=shuffle(9)}
\integer{a=randint(4..7)}
\integer{d=randint(1..\a-3)}
\integer{r=randint(1..\a-\d)}
\integer{nb=0}
\for{i=1 to \a}{\integer{nb=\nb+\chif[\i]*10^(\a-\i)}}
\real{nb=\nb/10^\d}
\text{enonc=\name_enonc[1;] \nb.
\name_enonc[2;1,2] \chif[\a-\d-\r+1] \name_enonc[2;3] }
\text{rep=\rangent[\r]}
\integer{larg=15}
#endif
#if defined TARGET_oefrang3
\text{chif=shuffle(9)}
\integer{a=randint(4..7)}
\integer{d=randint(\a-2..\a-1)}
\integer{r=randint(2..\d+1)}
\integer{nb=0}
\for{i=1 to \a}{\integer{nb=\nb+\chif[\i]*10^(\a-\i)}}
\real{nb=\nb/10^\d}
\text{enonc=\name_enonc[1;] \nb.
  \name_enonc[2;] \rangdec[\r] ?}
\integer{rep=\chif[\a-\d+\r-1]}
\integer{larg=4}
#endif
#if defined TARGET_oefrang4
\text{chif=shuffle(9)}
\integer{a=randint(4..7)}
\integer{d=randint(\a-2..\a-1)}
\integer{r=randint(2..\d+1)}
\integer{nb=0}
\for{i=1 to \a}{\integer{nb=\nb+\chif[\i]*10^(\a-\i)}}
\real{nb=\nb/10^\d}
\text{enonc=\name_enonc[1;] \nb.
  \name_enonc[2;1,2] \chif[\a-\d+\r-1] \name_enonc[2;3]}
\text{rep=\rangdec[\r]}
\integer{larg=15}
#endif
#if defined TARGET_oefrang5
\text{chif=shuffle(9)}
\integer{a=randint(4..7)}
\integer{c=randint(1..2)}
\if{\c=1}{
  \integer{d=randint(1..\a-3)}
  \integer{r=randint(1..\a-\d)}
}{
  \integer{d=randint(\a-2..\a-1)}
  \integer{r=randint(2..\d)}}
\integer{nb1=0}
\for{i=1 to \a}{\integer{nb1=\nb1+\chif[\i]*10^(\a-\i)}}
\real{rep=\nb1/10^\d}

\if{\c=1}{
  \integer{ch=\chif[\a-\d-\r+1]}
  \text{rg=\rangent[\r]}
}{
  \integer{ch=\chif[\a-\d+\r-1]}
  \text{rg=\rangdec[\r]}
}
\text{enonc=\name_enonc[1] \nb1 \name_enonc[2] \ch \name_enonc[3] \rg.}
\integer{larg=10}
#endif
\statement{
<label for="reply1">\enonc</label>
\embed{r1,\larg}}

\answer{}{\rep}{}
\latex{
\begin{statement}
\enonc
\(\dots\dots\)
\end{statement}
}
