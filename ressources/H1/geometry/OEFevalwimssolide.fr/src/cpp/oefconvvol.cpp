target=oefconvvol1 oefconvvol2 oefconvvol3 oefconvvol4 oefconvvol5

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000000}

\text{unit=\(\textrm{km}^3),\(\textrm{hm}^3),\(\textrm{dam}^3),\(\textrm{m}^3),\(\textrm{dm}^3),\(\textrm{cm}^3),\(\textrm{mm}^3)}
#if defined TARGET_oefconvvol1
\integer{n1=randint(1..9)}
\integer{u1=randint(1..6)}
\integer{z1=randint(1..3)}
\if{\u1+\z1>7}{\integer{z1=1}}

\integer{n2=randint(1..9)}
\integer{u2=randint(1..6)}
\integer{z2=randint(1..3)}
\if{\u2+\z2>7}{\integer{z2=1}}

\real{rep1=\n1*10^(\z1*3)}
\real{rep2=\n2*10^(\z2*3)}
#endif
#if defined TARGET_oefconvvol2
\integer{n1=randint(1..9)}
\integer{u1=randint(2..7)}
\integer{z1=randint(-3..-1)}
\if{\u1+\z1<1}{\integer{z1=-1}}

\integer{n2=randint(1..9)}
\integer{u2=randint(2..7)}
\integer{z2=randint(-3..-1)}
\if{\u2+\z2<1}{\integer{z2=-1}}

\real{rep1=\n1*10^(\z1*3)}
\real{rep2=\n2*10^(\z2*3)}
#endif
#if defined TARGET_oefconvvol3
\integer{l1=randint(1..3)}
\integer{d1=randint(1..4-\l1)}
\integer{n1=randint(1111..9999)}
\real{n1=floor(\n1/10^(\l1-1))/10^\d1}

\integer{u1=randint(1..6)}
\integer{z1=randint(1..3)}
\if{\u1+\z1>7}{\integer{z1=1}}

\integer{l2=randint(1..3)}
\integer{d2=randint(1..4-\l2)}
\integer{n2=randint(1111..9999)}
\real{n2=floor(\n2/10^(\l2-1))/10^\d2}
\integer{u2=randint(1..6)}
\integer{z2=randint(1..3)}
\if{\u2+\z2>7}{\integer{z2=1}
\integer{u2=randint(1..5)}}

\real{rep1=\n1*10^(\z1*3)}
\real{rep2=\n2*10^(\z2*3)}
#endif
#if defined TARGET_oefconvvol4
\integer{l1=randint(1..3)}
\integer{d1=randint(1..4-\l1)}
\integer{n1=randint(1111..9999)}
\real{n1=floor(\n1/10^(\l1-1))/10^\d1}
\integer{u1=randint(2..6)}
\integer{z1=randint(-3..-1)}
\if{\u1+\z1<1}{\integer{z1=-1}}

\integer{l2=randint(1..3)}
\integer{d2=randint(1..4-\l2)}
\integer{n2=randint(1111..9999)}
\real{n2=floor(\n2/10^(\l2-1))/10^\d2}
\integer{u2=randint(2..6)}
\integer{z2=randint(-3..-1)}
\if{\u2+\z2<1}{\integer{z2=-1}}

\real{rep1=\n1*10^(\z1*3)}
\real{rep2=\n2*10^(\z2*3)}
#endif
#if defined TARGET_oefconvvol5
\integer{l1=randint(1..3)}
\integer{d1=randint(5-\l1..8-\l1)}
\integer{n1=randint(1111..9999)}
\real{n1=floor(\n1/10^(\l1-1))/10^\d1}
\integer{u1=randint(1..6)}
\integer{z1=randint(1..3)}
\if{\u1+\z1>7}{
  \integer{z1=1}
  \integer{u1=randint(1..5)}}

\integer{l2=randint(1..4)}
\integer{d2=randint(1..\l2-1)}
\integer{n2=randint(11111..99999)}
\real{n2=floor(\n2/10^(\l2-1))*10^\d2}
\integer{u2=randint(2..7)}
\integer{z2=randint(-3..-1)}
\if{\u2+\z2<1}{\integer{z2=-1}}

\real{rep1=\n1*10^(\z1*3)}
\real{rep2=\n2*10^(\z2*3)}
#endif

\statement{
\name_enonce:
<ul><li>
<label for="reply1">\n1 \unit[\u1] =</label> \embed{r1,10} \unit[\u1+\z1]
</li><li><label for="reply2">\n2 \unit[\u2] =</label> \embed{r2,10} \unit[\u2+\z2]
</li></ul>
}

\answer{}{\rep1}{type=numeric}
\answer{}{\rep2}{type=numeric}
