target=oefliretableau1 oefliretableau2 oefliretableau3 oefliretableau4 oefliretableau5
#include "author.inc"
#if defined TARGET_oefliretableau1
# define NUM 1
#endif
#if defined TARGET_oefliretableau2
# define NUM 2
#endif
#if defined TARGET_oefliretableau3
# define NUM 3
#endif
#if defined TARGET_oefliretableau4
# define NUM 4
#endif
#if defined TARGET_oefliretableau5
# define NUM 5
#endif
#include "lang_titles.inc"
#include "lang.inc"

\precision{10000}

\matrix{v=5,2,2,3,4,4,2,1,3,4,5,3
13,1,2,2,4,3,3,1,2,4,4,2
5,1,3,3,4,3,2,1,3,4,5,2
7,1,3,3,4,4,3,1,3,4,5,3
1,1,4,3,4,3,2,1,4,5,5,3
3,1,2,2,4,3,2,1,3,4,4,2}

\integer{ch=randint(1..6)}
\text{ville=\ville[\ch]}
\text{v=row(\ch,\v)}

\text{t=randint(\v[1]..\v[1]+1)}
\text{a=\t}

\for{i=2 to 8}{
    \integer{a=\a+randint(\v[\i]-1..\v[\i]+1)}
    \text{t=wims(append item \a to \t)}
}
\for{i=9 to 12}{
    \integer{a=\a-randint(\v[\i]..\v[\i]+1)}
    \text{t=wims(append item \a to \t)}
}
#if defined TARGET_oefliretableau1
\integer{b=randint(1..12)}
\text{enonc1=\name_enonc1 \ms[\b] :}
\integer{rp=\t[\b]}
\integer{l=10}
#endif
#if defined TARGET_oefliretableau2
\text{enonc1=\name_enonc1}
\integer{rp=50}
\for{j=1 to 12}{\integer{rp=min(\rp,\t[\j])}}
\integer{l=10}
#endif
#if defined TARGET_oefliretableau3
\text{enonc1=\name_enonc1}
\integer{rp=0}
\for{j=1 to 12}{\integer{rp=max(\rp,\t[\j])}}
\integer{l=10}
#endif
#if defined TARGET_oefliretableau4
\text{enonc1=\name_enonc1 <div class="wims_instruction">\name_hint</div>}
\integer{mm=50}
\for{j=1 to 12}{\integer{mm=min(\mm,\t[\j])}}
\text{rp=}
\for{j=1 to 12}{
    \if{\mm=\t[\j]}{\text{rp=wims(append item \mois[\j] to \rp)}}}
\integer{l=20}
#endif
#if defined TARGET_oefliretableau5
\text{enonc1=\name_enonc1 <div class="wims_instruction">\name_hint</div>}
\integer{mm=0}
\for{j=1 to 12}{\integer{mm=max(\mm,\t[\j])}}
\text{rp=}
\for{j=1 to 12}{
    \if{\mm=\t[\j]}{\text{rp=wims(append item \mois[\j] to \rp)}}}
\integer{l=20}
#endif
\statement{\name_instruction \ville.
<table class="wimscenter wimsborder table-scroll">
<tr>
\for{m=1 to 12}{<th>\mois[\m]</th>}
</tr><tr>
\for{k=1 to 12}{<td>\t[\k]</td>}
</tr></table>
<div class="spacer"><label for="reply1">\enonc1</label> \embed{r1,\l}.</div>
}

\answer{}{\rp}{type=raw}{option=nocase}
