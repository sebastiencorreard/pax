target=oefordre1 oefordre2 oefordre3 oefordre4 oefordre5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

#if defined TARGET_oefordre1
\text{chif=shuffle(9)}
\integer{rg=randint(1..3)}
\text{nb1=item(1..3,\chif)}
\text{nb2=}
\for{i=1 to 3}
   {\if{\i<>\rg}{\text{nb2=\nb2,\nb1[\i]}}{\text{nb2=\nb2,0}}}
\text{nb2=item(2..4,\nb2)}
\integer{v1=0}
\integer{v2=0}
\for{i=1 to 3}
   {\real{v1=\v1+\nb1[\i]*10^(3-\i)}
    \real{v2=\v2+\nb2[\i]*10^(3-\i)}}
\text{v=\v1,\v2}
\integer{c=random(-1,1)}
\if{\v1*\c>\v2*\c}{\integer{rep1=2}}{\integer{rep1=1}}
\integer{rep2=\rg}
\text{enonc1=\name_enonc1 \pl[\c/2+1.5] :}
#endif
#if defined TARGET_oefordre2
\text{chif=shuffle(9)}
\integer{rg=randint(1..4)}
\text{nb1=item(1..4,\chif)}
\text{nb2=}
\for{i=1 to 4}
   {\if{\i<>\rg}{\text{nb2=\nb2,\nb1[\i]}}{\text{nb2=\nb2,\chif[5]}}}
\text{nb2=item(2..5,\nb2)}
\integer{v1=0}
\integer{v2=0}
\for{i=1 to 4}
   {\real{v1=\v1+\nb1[\i]/10^(\i-1)}
    \real{v2=\v2+\nb2[\i]/10^(\i-1)}}
\text{v=\v1,\v2}
\integer{c=random(-1,1)}
\if{\v1*\c>\v2*\c}{\integer{rep1=2}}{\integer{rep1=1}}
\integer{rep2=\rg+2}
\text{enonc1=\name_enonc1 \pl[\c/2+1.5] :}
#endif
#if defined TARGET_oefordre3
\text{chif=shuffle(9)}
\integer{rg=randint(1..4)}
\text{nb1=item(1..4,\chif)}
\text{nb2=}
\for{i=1 to 4}
   {\if{\i<>\rg}{\text{nb2=\nb2,\nb1[\i]}}}
\text{nb2=item(2..4,\nb2)}
\integer{v1=0}
\integer{v2=0}
\for{i=1 to 4}
   {\real{v1=\v1+\nb1[\i]/10^(\i-1)}}
\for{i=1 to 3}
    {\real{v2=\v2+\nb2[\i]/10^(\i-1)}}
\text{v=\v1,\v2}
\integer{c=random(-1,1)}
\if{\v1*\c>\v2*\c}{\integer{rep1=2}}{\integer{rep1=1}}
\integer{rep2=\rg+2}
\text{enonc1=\name_enonc1 \pl[\c/2+1.5] :}
#endif
#if defined TARGET_oefordre4
\text{chif=shuffle(9)}
\integer{a=randint(2..4)}
\text{nb1=item(1..4,\chif)}
\integer{rg=randint(1..2)}
\integer{v1=0}
\for{i=1 to \a}
   {\real{v1=\v1+\nb1[\i]/10^(\rg+\i-\a)}}
\integer{b=randint(1..9)}
\integer{s=random(-1,1)}
\real{v2=\v1+\s*\b/10^(\rg+1)}
\text{v=\v1,\v2}
\integer{c=random(-1,1)}
\if{\v1*\c>\v2*\c}{\integer{rep1=2}}{\integer{rep1=1}}
\integer{rep2=\rg+3+(1+\s)/2}
\text{enonc1=\name_enonc1 \pl[\c/2+1.5] :}
#endif
#if defined TARGET_oefordre5
\text{chif=shuffle(9)}
\text{nb=item(1..3,\chif)}
\integer{v1=0}
\for{i=1 to 3}
   {\integer{v1=\v1+\nb[\i]*10^(3-\i)}}
\real{v2=\v1/10}
\real{v3=\v1/100}
\real{v4=\v1/1000}

\text{v=\v1,\v2,\v3,\v4}
\integer{c=random(1,2)}
\integer{c=1}
\if{\c=1}{\integer{rep1=1}}{\integer{rep1=4}}
\integer{rep2=1}
\text{enonc1=\name_enonc1 \pl[\c] :}
#endif

\statement{
<ul><li>\enonc1 \embed{r1}</li><li>\enonc2 \embed{r2}</li></ul>
}

\answer{}{\rep1;\v}{type=checkbox}{option=shuffle}
\answer{}{\rep2;\rang}{type=checkbox}
