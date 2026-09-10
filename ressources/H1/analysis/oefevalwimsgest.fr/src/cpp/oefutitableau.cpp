target=oefutitableau1 oefutitableau2 oefutitableau3 oefutitableau4 oefutitableau5
#if defined TARGET_oefutitableau1
# define NUM 1
#endif
#if defined TARGET_oefutitableau2
# define NUM 2
#endif
#if defined TARGET_oefutitableau3
# define NUM 3
#endif
#if defined TARGET_oefutitableau4
# define NUM 4
#endif
#if defined TARGET_oefutitableau5
# define NUM 5
#endif
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

\matrix{v=50,50,50,60,70,60,40,50,50,50,50,50
80,60,60,70,50,40,20,20,80,140,100,90
50,40,50,50,60,60,60,40,50,60,50,60
50,50,40,50,40,30,15,30,50,80,60,60
30,40,40,40,80,80,70,60,60,50,50,40
60,40,60,50,60,70,60,50,60,70,70,70}

\integer{ch=randint(1..6)}
\text{ville=\ville[\ch]}
\text{v=row(\ch,\v)}
\text{t=}
\text{a=}
\integer{tot1=0}
\integer{tot2=0}
\for{i=1 to 6}{
  \integer{a=randint(\v[\i]-10..\v[\i]+10)}
  \integer{tot1=\tot1+\a}
  \text{t=wims(append item \a to \t)}
}
\for{i=7 to 12}{
  \integer{a=randint(\v[\i]-10..\v[\i]+10)}
  \integer{tot2=\tot2+\a}
  \text{t=wims(append item \a to \t)}
}
\text{rp=\rp mm}
\integer{l=20}
#if defined TARGET_oefutitableau1 || defined TARGET_oefutitableau2
\text{typ=mark}
\integer{mm=50}
\text{rp=}
#endif
#if defined TARGET_oefutitableau1
\for{j=1 to 12}{
  \if{\mm>\t[\j]}{\text{rp=wims(append item \j to \rp)}}}
\text{rp=\rp;\mois}
\integer{l=20}
#endif
#if defined TARGET_oefutitableau2
\for{j=1 to 12}{
  \if{\mm=\t[\j] or \mm<\t[\j]}{\text{rp=wims(append item \j to \rp)}}}
\text{rp=\rp;\mois}
\integer{l=20}
#endif
#if defined TARGET_oefutitableau3
\text{typ=mark}
\integer{mm=50}
\integer{mi=\mm-10*randint(1..3)}
\integer{ma=\mm+10*randint(1..3)}
\text{enonc1=\name_enonc1[1;] \mi \name_enonc1[2;] \ma \name_enonc1[3;]
  (\name_enonc1[4;] \mi \name_enonc1[5;] \ma \name_enonc1[6;]).}
\text{rp=}
\for{j=1 to 12}{
    \if{\mi<\t[\j] and \ma>\t[\j]}{\text{rp=wims(append item \j to \rp)}}}
\text{rp=\rp;\mois}
\integer{l=20}
#endif
#if defined TARGET_oefutitableau4
\text{typ=units}
\text{ch=randitem(\name_ch)}
\text{enonc1=\name_enonc1[1] \ch.}
\if{\ch=\name_ch[1]}{\integer{rp=\tot1}}{\integer{rp=\tot2}}
\text{rp=\rp mm}
\integer{l=20}
#endif
#if defined TARGET_oefutitableau5
\text{typ=units}
\integer{rp=\tot1+\tot2}
\text{rp=\rp mm}
\integer{l=20}
#endif
\statement{
\name_enonce \ville.
<table class="wimscenter wimsborder table-scroll">
<tr>
\for{m=1 to 12}{<th>\mois[\m]</th>}
</tr><tr>
\for{k=1 to 12}{<td>\t[\k]</td>}
</tr></table>
<div class="spacer"><label for="reply1">\enonc1</label>
<div>\embed{r1,\l}.</div></div>
\if{\name_instruction!=}
{<div class="wims_instruction">\name_instruction</div>}
}

\answer{}{\rp}{type=\typ}{option=nocase}
