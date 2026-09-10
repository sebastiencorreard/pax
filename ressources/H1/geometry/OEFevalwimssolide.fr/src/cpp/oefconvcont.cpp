target=oefconvcont1 oefconvcont2 oefconvcont3 oefconvcont4 oefconvcont5

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000000}

\text{unit=\(\textrm{hL}),\(\textrm{daL}),\(\textrm{L}),\(\textrm{dL}),\(\textrm{cL}),\(\textrm{mL})}

#if defined TARGET_oefconvcont1
\integer{n1=randint(1..9)}
\integer{u1=randint(1..5)}
\integer{z1=randint(1..5)}
\if{\u1+\z1>6}{\integer{z1=1}}

\integer{n2=randint(1..9)}
\integer{u2=randint(1..5)}
\integer{z2=randint(1..5)}
\if{\u2+\z2>6}{\integer{z2=1}}

\real{rep1=\n1*10^\z1}
\real{rep2=\n2*10^\z2}
#endif
#if defined TARGET_oefconvcont2
\integer{n1=randint(1..9)}
\integer{u1=randint(2..6)}
\integer{z1=randint(-5..-1)}
\if{\u1+\z1<1}{\integer{z1=-1}}

\integer{n2=randint(1..9)}
\integer{u2=randint(2..6)}
\integer{z2=randint(-5..-1)}
\if{\u2+\z2<1}{\integer{z2=-1}}

\real{rep1=\n1*10^\z1}
\real{rep2=\n2*10^\z2}
#endif
#if defined TARGET_oefconvcont3
\integer{l1=randint(1..3)}
\integer{d1=randint(1..4-\l1)}
\integer{n1=randint(1111..9999)}
\real{n1=floor(\n1/10^(\l1-1))/10^\d1}
\integer{u1=randint(1..5)}
\integer{z1=randint(1..5)}
\if{\u1+\z1>6}{\integer{z1=1}}

\integer{l2=randint(1..3)}
\integer{d2=randint(1..4-\l2)}
\integer{n2=randint(1111..9999)}
\real{n2=floor(\n2/10^(\l2-1))/10^\d2}
\integer{u2=randint(1..5)}
\integer{z2=randint(1..5)}
\if{\u2+\z2>6}{\integer{z2=1}}

\real{rep1=\n1*10^\z1}
\real{rep2=\n2*10^\z2}
#endif
#if defined TARGET_oefconvcont4
\integer{l1=randint(1..3)}
\integer{d1=randint(1..4-\l1)}
\integer{n1=randint(1111..9999)}
\real{n1=floor(\n1/10^(\l1-1))/10^\d1}
\integer{u1=randint(1..5)}
\integer{z1=randint(-5..-1)}
\if{\u1+\z1<1}{
  \integer{z1=-1}
  \integer{u1=randint(2..5)}}

\integer{l2=randint(1..3)}
\integer{d2=randint(1..4-\l2)}
\integer{n2=randint(1111..9999)}
\real{n2=floor(\n2/10^(\l2-1))/10^\d2}
\integer{u2=randint(1..5)}
\integer{z2=randint(-5..-1)}
\if{\u2+\z2<1}{\integer{z2=-1}
\integer{u2=randint(2..5)}}

\real{rep1=\n1*10^\z1}
\real{rep2=\n2*10^\z2}
#endif
#if defined TARGET_oefconvcont5
\integer{l1=randint(1..3)}
\integer{d1=randint(5-\l1..8-\l1)}
\integer{n1=randint(1111..9999)}
\real{n1=floor(\n1/10^(\l1-1))/10^\d1}
\integer{u1=randint(1..5)}
\integer{z1=randint(1..5)}
\if{\u1+\z1>6}{
  \integer{u1=randint(1..4)}
  \integer{z1=1}}

\integer{l2=randint(1..4)}
\integer{d2=randint(1..\l2-1)}
\integer{n2=randint(11111..99999)}
\real{n2=floor(\n2/10^(\l2-1))*10^\d2}
\integer{u2=randint(2..6)}
\integer{z2=randint(-5..-1)}
\if{\u2+\z2<1}{\integer{z2=-1}}

\real{rep1=\n1*10^\z1}
\real{rep2=\n2*10^\z2}
#endif

\statement{
\name_enonce:
<ul><li>
<label for="reply1">\n1 \unit[\u1] =</label> \embed{r1,10} \unit[\u1+\z1]
</li><li><label for="reply2">\n2 \unit[\u2] = </label> \embed{r2,10} \unit[\u2+\z2]
</li></ul>
}

\answer{}{\rep1}{type=numeric}
\answer{}{\rep2}{type=numeric}
