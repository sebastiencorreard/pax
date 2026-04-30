target=ordre1,ordre2,ordre3,ordre4,ordre5

#define TITRE Hypothèses de la réciproque
\author{Fabrice,Guerimand}
\email{fguerima@free.fr}
#if defined TARGET_ordre1
# define NUM 1
#endif
#if defined TARGET_ordre2
# define NUM 2
#endif
#if defined TARGET_ordre3
# define NUM 3
#endif
#if defined TARGET_ordre4
# define NUM 4
#endif
#if defined TARGET_ordre5
# define NUM 5
#endif
\title{TITRE NUM}

\matrix{sommets=A,B,C,D,E,F,G
E,F,G,H,I,J,K
M,N,O,P,Q,R,S}
\text{sommet=randrow(\sommets)}
\text{sommet=shuffle(\sommet)}

\text{A=item(1,\sommet)}
\text{B=item(2,\sommet)}
\text{C=item(3,\sommet)}
\text{D=item(4,\sommet)}
\text{E=item(5,\sommet)}
\text{F=item(6,\sommet)}
\text{G=item(7,\sommet)}


#if defined TARGET_ordre1
 \text{enonce=\(\A \B \C) est un triangle. \(\D) et \(\E) sont respectivement des points des segments
 \([\A \B]) et \([\A \C]) tels que}
 \text{good=1}
 \real{k=randitem(0.7,0.8,0.9,1.1,1.2)}
 \integer{b=randint(5..19)}
 \integer{a=\b+randint(\b/3..2*\b/3)}
 \real{c=\k*\a}
 \real{d=\k*\b}
#endif
#if defined TARGET_ordre2
 \text{enonce=\(\A \B \C) est un triangle. \(\D) et \(\E) sont respectivement des points
 des droites \((\A \B)) et \((\A \C)) tels que}
 \text{good=3}
 \real{k=randitem(0.7,0.8,0.9,1.1,1.2)}
 \integer{b=randint(5..19)}
 \integer{a=\b+randint(\b/3..2*\b/3)}
 \real{c=\k*\a}
 \real{d=\k*\b}
#endif
#if defined TARGET_ordre3
 \text{lc=wims(char 1 of [])}
 \text{rp=wims(char 2 of ())}
 \text{enonce=\(\A \B \C) est un triangle. \(\D) et \(\E) sont respectivement des points
 appartenant aux demi-droites \(\lbrack \B \A \rpar\) et \(\lbrack \C \A\rpar\) tels que}
 \text{good=1}
 \real{k=randitem(0.7,0.8,0.9,1.1,1.2)}
 \integer{a=randint(5..19)}
 \integer{b=\a+randint(\a/3..2*\a/3)}
 \real{c=\k*\a}
 \real{d=\k*\b}
#endif
#if defined TARGET_ordre4
 \text{enonce=Les droites \((\E \C)) et \((\B \D)) se coupent en \(\A) telles que \(\D)
  est un point du segment \([\A \B]) et \(\A) un point du segment \([\E \C]).}
 \text{good=2}
 \real{k=randitem(0.7,0.8,0.9,1.1,1.2)}
 \integer{b=randint(5..19)}
 \integer{a=\b+randint(\b/3..2*\b/3)}
 \real{c=\k*\a}
 \real{d=\k*\b}
#endif
#if defined TARGET_ordre5
 \text{enonce=Les droites \((\E \C)) et \((\B \D)) se coupent en \(\A) telles que}
 \text{good=3}
 \real{k=randitem(0.7,0.8,0.9,1.1,1.2)}
 \integer{a=randint(5..19)}
 \integer{b=\a+randint(\a/3..2*\a/3)}
 \real{c=\k*\a}
 \real{d=\k*\b}
#endif

\text{list=Oui,Non,Pas obligatoirement}
\text{Good=item(\good,\list)}

\statement{
<ul class="wims_nopuce">
 <li>
\(\A\), \(\B\), \(\C\), \(\D\) et \(\E\) sont cinq points distincts du plan.
</li><li>
 \enonce
<div class="wimscenter">
\(\A \D = \b\) ; \(\A \B = \a\) ; \(\A \E = \d\) ; \(\A \C = \c\).
</div>
  Les droites \((\D \E)) et \((\B \C)) sont-elles parallèles ?
</li></ul>}

\choice{Réponse}{\Good}{\list}
