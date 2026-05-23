target=equationA1 equationA2 equationA3 equationA4 equationA5 equationB1 equationB2 equationB3 equationB4 equationB5 equationC1 equationC2 equationC3 equationC4 equationC5

#define TITRE Résolution équation
#include "author.inc"
#if defined TARGET_equationA1
# define NUM A1
#endif
#if defined TARGET_equationA2
# define NUM A2
#endif
#if defined TARGET_equationA3
# define NUM A3
#endif
#if defined TARGET_equationA4
# define NUM A4
#endif
#if defined TARGET_equationA5
# define NUM A5
#endif
#if defined TARGET_equationB1
# define NUM B1
#endif
#if defined TARGET_equationB2
# define NUM B2
#endif
#if defined TARGET_equationB3
# define NUM B3
#endif
#if defined TARGET_equationB4
# define NUM B4
#endif
#if defined TARGET_equationB5
# define NUM B5
#endif
#if defined TARGET_equationC1
# define NUM C1
#endif
#if defined TARGET_equationC2
# define NUM C2
#endif
#if defined TARGET_equationC3
# define NUM C3
#endif
#if defined TARGET_equationC4
# define NUM C4
#endif
#if defined TARGET_equationC5
# define NUM C5
#endif
\title{TITRE NUM}
\text{x=x}

#if defined TARGET_equationA1
 \integer{a=randint(1..100)}
 \integer{b=randint(1..100)*randitem(1,-1)}
 \text{enonce=\x + \a = \b}
 \text{rep=simplify(\b-\a)}
 \text{type=}
#endif
#if defined TARGET_equationA2
 \integer{a=randint(1..100)}
 \integer{b=randint(1..100)*randitem(1,-1)}
 \text{enonce=\x - \a = \b}
 \text{rep=simplify(\b+\a)}
 \text{type=}
#endif
#if defined TARGET_equationA3
 \integer{a=randint(1..100)}
 \integer{b=randint(1..100)*randitem(1,-1)}
 \text{enonce=\a + \x = \b }
 \text{rep=simplify(\b-\a)}
 \text{type=}
#endif

#if defined TARGET_equationA4
 \integer{a=randint(1..100)}
 \integer{b=randint(1..100)*randitem(1,-1)}
 \text{enonce=-\a + \x = \b}
 \text{rep=simplify(\b+\a)}
 \text{type=}
#endif
#if defined TARGET_equationA5
 \integer{n=randint(1..9)}
 \integer{d=randint(\n+1..10)}
 \text{f=simplify(\n/\d)}
 \integer{b=randint(1..100)*randint(1,-1)}
 \text{f2=texmath(\f)}
 \text{enonce=\f2 + \x = \b}
 \text{rep=simplify(\b-(\f))}
 \text{type=noreduction}
#endif
#if defined TARGET_equationB1
 \integer{a=randint(2..10)}
 \integer{b=randint(1..10)*randitem(1,-1)}
 \text{enonce=\a \times \x = \b}
 \text{rep=simplify(\b/\a)}
 \text{type=noreduction}
#endif
#if defined TARGET_equationB2
 \integer{a=randint(1..10)}
 \integer{b=randint(1..10)*randitem(1,-1)}
 \text{enonce=texmath(-\a*\x = \b)}
 \text{rep=simplify(-(\b)/\a)}
 \text{type=noreduction}
#endif
#if defined TARGET_equationB3
 \integer{a=randint(1..10)}
 \integer{b=randint(1..10)*randitem(1,-1)}
 \text{enonce=\frac{\x}{\a} = \b}
 \text{rep=simplify(\b*\a)}
 \text{type=}
#endif
#if defined TARGET_equationB4
 \integer{a=randint(1..10)}
 \integer{b=randint(1..10)*randitem(1,-1)}
 \text{enonce=\frac{\x}{-\a} = \b}
 \text{rep=simplify(-\b*\a)}
 \text{type=}
#endif
#if defined TARGET_equationB5
 \integer{n=randint(1..9)}
 \integer{d=randint(\n+1..10)}
 \text{f=simplify(\n/\d)}
 \integer{b=randint(1..10)*randint(1,-1)}
 \text{f2=texmath(\f)}
 \text{enonce=\f2 \x = \b}
 \text{rep=simplify(\b*\d/\n)}
 \text{type=noreduction}
#endif
#if defined TARGET_equationC1
 \integer{a=randint(1..10)}
 \integer{b=randint(1..10)}
 \integer{c=randint(1..10)*randitem(1,-1)}
 \text{enonce=texmath(\a*\x +\b = \c)}
 \text{rep=simplify((\c-\b)/(\a))}
 \text{type=noreduction}
#endif

#if defined TARGET_equationC2
 \integer{a=randint(1..10)}
 \integer{b=randint(1..10)}
 \integer{c=randint(1..10)*randitem(1,-1)}
 \text{enonce=texmath(\a*\x - \b = \c)}
 \text{rep=simplify((\c+\b)/(\a))}
 \text{type=noreduction}
#endif

#if defined TARGET_equationC3
 \integer{a=randint(1..10)}
 \integer{b=randint(1..10)}
 \integer{c=randint(1..10)*randitem(1,-1)}
 \text{enonce=texmath(-\a*\x + \b = \c)}
 \text{rep=simplify((\c-\b)/(-\a))}
 \text{type=noreduction}
#endif

#if defined TARGET_equationC4
 \integer{a=randint(1..10)}
 \integer{b=randint(1..10)}
 \integer{c=randint(1..10)*randitem(1,-1)}
 \text{enonce=texmath(-\a*\x - \b = \c)}
 \text{rep=simplify((\c+\b)/(-\a))}
 \text{type=noreduction}
#endif

#if defined TARGET_equationC5
 \integer{a=randint(1..100)}
 \integer{c=randint(1..100)*randitem(1,-1)}
 \text{enonce=texmath(\a-\x = \c)}
 \text{rep=simplify(\a-(\c))}
 \text{type=}
#endif

#if defined TARGET_equationD1
 \text{ch=wims(values v for v=1 to 10)}
 \text{ch=shuffle(\ch)}
 \integer{a=\ch[1]}
 \integer{b=\ch[1]}
 \integer{c=\ch[1]}
 \integer{d=\ch[1]}
 \text{enonce=texmath(\a*\x +\b = \c)}
 \text{rep=simplify((\d-\b)/(\a))}
 \text{type=noreduction}
#endif

\statement{
  Quelle est la solution de l'équation suivante :
<div class="wimscenter">\(\enonce)</div>
<div><b>Votre réponse :</b>
  La solution de cette équation est \embed{r1,7}.
</div>}

\answer{Réponse}{\rep}{type=numexp}{option=\type}
