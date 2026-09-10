target=dirderive1 dirderive2 dirderive3 dirderive4
\author{Régine, Mangeard}
\email{regine@mangeard.Fr}
\format{html}
\precision{100}
\computeanswer{yes}
#if defined TARGET_dirderive1
# define NUM 1
#endif
#if defined TARGET_dirderive2
# define NUM 2
#endif
#if defined TARGET_dirderive3
# define NUM 3
#endif
#if defined TARGET_dirderive4
# define NUM 4
#endif
#include "lang_titles.inc"

\integer{a=randint(1..9)*randint(1,-1)}
\integer{b=randint(1..9)*randint(1,-1)}
\integer{c=randint(1..9)*randint(1,-1)}
\integer{d=randint(1..9)}
\integer{e=randint(1..9)}
\rational{sing=simplify(-\e/\d)}
\integer{n=randint(3..5)}

\text{data=\a*x^2+\b*x+\c/x+\d*sqrt(x),\(\rbrack 0; +\infty \rbrack)
(\a*x^2+\b*x+\c)*(\d*x+\e),\(\;\RR)
(\a*x+\b)*sqrt(x),\(\rbrack 0; +\infty \rbrack)
(\a*x+\b)/(\d*x+\e),\(\RR \setminus \lbrace \sing \rbrace)
(\a*x+\b)/(\d*x^2+\e),\(\;\RR)
(\a*x^2+\b)/(\d*x+\e),\(\RR \setminus \lbrace \sing \rbrace)
(\a*x+\b)^\n,\(\;\RR)
1/(\d*x+\e)^\n,\(\RR \setminus \lbrace \sing \rbrace)
(\d*x+\e)^(-\n),\(\RR \setminus \lbrace \sing \rbrace)
sqrt(\d*x+\e),\(\rbrack \sing; +\infty \rbrack)
cos(\a*x+\b),\(\;\RR)
sin(\a*x+\b),\(\;\RR)
}

#if defined TARGET_dirderive1
\integer{i=1}
#endif
#if defined TARGET_dirderive2
\integer{i=randint(2,3)}
#endif
#if defined TARGET_dirderive3
\integer{i=randint(4,5,6)}
#endif
#if defined TARGET_dirderive4
\integer{i=randint(7..12)}
#endif
\text{cedata=row(\i,\data)}
\text{f=\cedata[1]}
\text{ft=texmath(\f)}
\function{fder=diff(\f,x)}
\text{defdom=\cedata[2]}

\statement{<p>
On considère la fonction \(f) définie sur \defdom par:
</p>
<div class="wimscenter"> \(f(x)=\ft).</div>
<div class="wims_question">
Calculer \(f'(x)):
<div class="wimscenter"><label for="reply1">\(f'(x)=)</label> \embed{reply1} </div>
</div>
<div class="wims_instruction">Taper <span class="tt">sqrt(x)</span> pour \(\sqrt{x}).</div>
}
\answer{fonction dérivée}{\fder}{type=formal}
