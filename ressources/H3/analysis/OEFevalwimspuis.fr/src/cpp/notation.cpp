target=notation1 notation2 notation3 notation4 notation5
#define TITRE Notation puissance
#if defined TARGET_notation1
 \title{TITRE 1}
 \integer{p=randint(2..4)}
 \text{enonce=\(10^\p)}
 \text{bad=\(\p\times 10)}
 \text{good=wims(values 10 for v=1 to \p)}
 \text{good=wims(replace internal , by \times in \good)}
 \text{good=\(\good)}
#endif

#if defined TARGET_notation2
 \title{TITRE 2}
 \text{p=wims(values v for v=2 to 5)}
 \text{p=shuffle(\p)}
 \integer{a=\p[1]}
 \integer{p=\p[2]}
 \text{enonce=\(\a^\p)}
 \text{bad=\(\a\times \p)}
 \text{good=wims(values \a for v=1 to \p)}
 \text{good=wims(replace internal , by \times in \good)}
 \text{good=\(\good)}
#endif

#if defined TARGET_notation3
 \title{TITRE 3}
 \integer{p=randint(2..4)}
 \text{enonce=\(10^{-\p})}
 \text{bad=\(10 - \p),\(10 \times (-\p))}
 \text{good=\(\frac{1}{10^\p})}
#endif

#if defined TARGET_notation4
 \title{TITRE 4}
 \integer{p=randint(2..4)}
 \text{enonce=\(10^{-\p})}
 \real{good=10^(-\p)}
 \real{bad1=10^(-\p+1)}
 \text{bad2=0.wims(char -(\p+1) to -1 of 000001)}
 \text{bad=\bad1,\bad2}
#endif

#if defined TARGET_notation5
 \title{TITRE 5}
 \text{p=randint(3,4,5,6)}
 \text{enonce=\(\p^\p)}
 \text{bad=\(\p\times \p)}
 \text{good=wims(values \p for v=1 to \p)}
 \text{good=wims(replace internal , by \times in \good)}
 \text{good=\(\good)}
#endif

\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100000}

\statement{
Parmi les écritures proposées, laquelle est égale à :
<div class="wimscenter">\enonce</div>}

\choice{réponse}{\good}{\bad}
