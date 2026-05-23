target=compdec1 compdec2 compdec3 compdec4 compdec5
#define TITRE Comparer deux nombres
\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}

#if defined TARGET_compdec1
 \title{TITRE A1}
 \integer{a=randint(1111111..9999999)}
 \integer{b=randint(2..4)}
 \real{N=\a/10^(\b)}
 \text{ltrep=-\N,\N}
#endif

#if defined TARGET_compdec2
 \title{TITRE A2}
 \integer{a=randint(11..999)}
 \integer{b=randint(1..7)}
 \integer{c=randint(\b+1..9)}
 \integer{b=\b*10+randint(1..9)}
 \real{b=\a+\b/100}
 \text{ltrep=\b,\a.\c}
#endif

#if defined TARGET_compdec3
 \title{TITRE A3}
 \integer{a=randint(11..50)}
 \integer{b=randint(51..99)}
 \integer{c=randint(1..9)*100+randint(1..9)*10+randint(1..9)}
 \integer{d=randint(1..9)}
 \text{ltrep=\a.\c,\b.\d}
#endif

#if defined TARGET_compdec4
 \title{TITRE A4}
 \integer{a=randint(11..99)}
 \integer{b=randint(1..9)}
 \integer{p1=randint(2..4)}
 \integer{p2=randint(\p1+1..6)}
 \real{N1=\a+\b*10^(-\p1)}
 \real{N2=\a+\b*10^(-\p2)}
 \text{ltrep=\N2,\N1}
#endif

#if defined TARGET_compdec5
 \title{TITRE A5}
 \integer{a=randint(11..999)}
 \integer{b=randint(1..7)}
 \real{c=randint(\b+1..9)*10+randint(1..9)}
 \integer{b=\b*100+randint(1..9)*10+randint(1..9)}
 \real{b=\a+\b/1000}
 \real{c=\a+\c/100}
 \text{ltrep=-\c,-\b}
#endif

\integer{ch=randint(1..2)}
\text{good=item(\ch,\ltrep)}
\text{sens=item(\ch,petit,grand)}
\statement{
Quel est le plus \sens de ces deux nombres ?}

\choice{}{\good}{\ltrep}
