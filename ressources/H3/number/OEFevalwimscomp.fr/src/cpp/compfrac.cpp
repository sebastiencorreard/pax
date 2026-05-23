target=compfrac1 compfrac2 compfrac3 compfrac4 compfrac5
#define TITRE Comparer deux nombres
\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}

\text{v=wims(values v for v=2 to 30)}
\text{v=shuffle(\v)}

#if defined TARGET_compfrac1
 \title{TITRE B1}
 \text{ltrep=\(-\frac{\v[1]}{\v[2]}),\(\frac{\v[3]}{\v[4]})}
#endif

#if defined TARGET_compfrac2
 \title{TITRE B2}
 \integer{a=randint(11..49)}
 \integer{b=randint(51..99)}
 \text{ltrep=\(\frac{\a}{\v[1]}),\(\frac{\b}{\v[1]})}
#endif

#if defined TARGET_compfrac3
 \title{TITRE B3}
 \integer{a=randint(11..49)}
 \integer{b=randint(51..99)}
 \text{ltrep=\(\frac{\v[1]}{\b}),\(\frac{\v[1]}{\a})}
#endif

#if defined TARGET_compfrac4
 \title{TITRE B4}
 \integer{a=randint(11..49)}
 \integer{b=randint(51..99)}
 \text{ltrep=\(-\frac{1}{\a}),\(-\frac{1}{\b})}
#endif

#if defined TARGET_compfrac5
 \title{TITRE B5}
 \integer{a=randint(11..49)}
 \integer{b=randint(51..99)}
 \integer{c=randint(11..49)}
 \integer{d=randint(51..99)}
 \text{ltrep=\(\frac{\a}{\b}),\(\frac{\d}{\c})}
#endif

\integer{ch=randint(1..2)}
\text{good=item(\ch,\ltrep)}
\text{sens=item(\ch,petit,grand)}
\statement{
Quel est le plus \sens de ces deux nombres ?}

\choice{}{\good}{\ltrep}
