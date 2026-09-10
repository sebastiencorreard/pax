target=compderive1 compderive2 compderive3 compderive4
\author{Régine, Mangeard}
\email{regine@mangeard.Fr}
\format{html}
\precision{100}
\computeanswer{yes}
#if defined TARGET_compderive1
# define NUM 1
#endif
#if defined TARGET_compderive2
# define NUM 2
#endif
#if defined TARGET_compderive3
# define NUM 3
#endif
#if defined TARGET_compderive4
# define NUM 4
#endif
#include "lang_titles.inc"

\integer{sing1=randint(1..5)*randint(1,-1)}
\integer{sing2=\sing1+randint(1..5)}
\integer{sing2=\sing2=0?\sing2+randint(1..5)}
\integer{a=randint(1..4)*randint(1,-1)}
\integer{root=\sing1/\a}
\text{D1=\(\RR \setminus \lbrace \sing1 \rbrace)}
\text{D2=\(\RR \setminus \lbrace \sing1 ; \sing2 \rbrace)}
\text{D3=\( \rbrack \sing1; +\infty \rbrack)}
\text{D4=\( \lbrack -\infty ; \sing1 \lbrack)}
\text{D5=\( \rbrack \sing1; \sing2 \lbrack)}
\text{D6=\(\rbrack -\infty; \sing1 \lbrack \cup \rbrack \sing2; +\infty \lbrack)}

\text{D3r=\a>0?\D3:\D4}
\text{D5r=\a<0?\D5:\D6}

\integer{n=randint(3..5)}

#if defined TARGET_compderive1
\text{f=maxima(expand(\a*(x-\sing1)*(x-\sing2)))}
\text{data=(\f)^\n,1/(\f),sqrt(\f),cos(\f),sin(\f)}
\integer{i=randint(1..5)}
\text{g=item(\i,\data)}
\text{defdom=\i=2?\D2:\(\,\RR)}
\text{defdom=\i=3?\D5r}
#endif
#if defined TARGET_compderive2
\text{f=maxima(\a*(x-\sing2)/(x-\sing1))}
\text{data=(\f)^\n,sqrt(\f),cos(\f),sin(\f)}
\integer{i=randint(1..4)}
\text{g=item(\i,\data)}
\text{defdom=\i=2?\D5r:\D1}
#endif
#if defined TARGET_compderive3
\integer{as=\a*\sing1}
\text{f=maxima(sqrt(\a*x-\as))}
\text{data=(\f)^\n,1/(\f),cos(\f),sin(\f)}
\integer{i=randint(1..4)}
\text{g=item(\i,\data)}
\text{defdom=\D3r}
#endif
#if defined TARGET_compderive4
\integer{a2=abs(2*\a)}
\text{f=random(cos(\a*x),sin(\a*x))}
\text{data=(\f)^\n,1/(\f),sqrt(\f)}
\integer{i=randint(1..3)}
\text{g=item(\i,\data)}
\text{defdom=\i=1?\(\;\RR):\(\RR \setminus \lbrace \frac{k\pi}{\a2}, k \in \ZZ \rbrace)}
#endif

\text{ft=texmath(\g)}
\function{fder=diff(\g,x)}

\statement{
  On considère la fonction \(f) définie sur \defdom par
  <div class="wimscenter">\(f(x) = \ft).</div>
  <div class="wims_question">
  Calculer \(f'(x)).
  <div class="wimscenter"><label for="reply1">\(f'(x)=)</label> \embed{reply1} </div>
  </div>
  <div class="wims_instruction">
   Taper <span class="tt">sqrt(x)</span> pour \(\sqrt{x}).</div>
  }
\answer{fonction dérivée}{\fder}{type=formal}
