target=alignpts1 alignpts2 alignpts3 alignpts4 alignpts5
\language{fr}
\range{-5..5}
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{100}
#define TITLE Alignement de points
#if defined TARGET_alignpts1
 \integer{dena=randint(1,2)}
 \integer{denb=randint(1,2)}
 \integer{denc=randint(1,2)}
#else
 \integer{dena=1}
 \integer{denb=1}
 \integer{denc=1}
#endif

 \integer{rep=random(1,2)}
 integer{rep=1}
 \integer{numa=randint(1..5)}
 \rational{a=simplify(\numa / \dena)}
 \integer{numb=randint(1..5)}
 \rational{b=simplify(\numb / \denb)}
 \integer{numc=randint(1..5)}
 \rational{c=simplify(\numc / \denc)}
 \integer{ia=random(1,-1)}
 \integer{ib=random(1,-1)}
 \integer{ic=random(1,-1)}
 \text{sa=\ia=1?:-}
 \text{sb=\ib=1?+:-}
 \text{sc=\ic=1?:-}
 \text{ta=\a=1?:texmath(\a)}
 \text{tb=\b=1?:texmath(\b)}
 \text{tc=\c=1?:texmath(\c)}
#if defined TARGET_alignpts1 || defined TARGET_alignpts2 || defined TARGET_alignpts3
  \text{lstpts=\(M\) et \(N\)}
 \text{quest=Les points \(A\), \(M\) et \(N\) sont-ils alignés}
#endif
#if defined TARGET_alignpts1
 \title{TITLE I}
 \if{\rep=1}{
  \rational{d=simplify( (\c) * (\b) / (\a))}
  \integer{id= \ic *\ia *\ib}
  \text{sd=\id=1?+:-}
  }{
  \integer{k=random(1,2)}
  \if{\k=1}{
     \rational{d=simplify((\c) * (\b) / (\a))}
     \integer{id= \ic *\ia *\ib}
     \text{sd=\id=1?-:+}
   }{
     \rational{d=simplify((\c) * (\b) / (\a)+1)}
     \integer{id= random(1,-1)}
     \text{sd=\id=1?-:+}
   }
  }
  \text{td=\d=1?:texmath(\d)}

 \text{defpts=\(\overrightarrow{A M} = \sa \ta \overrightarrow{A B} \sb \tb \overrightarrow{A C})<br>
\(\overrightarrow{A N} =)}
\text{defsuite=\d=0? \(\sc \tc \overrightarrow{A B}): \(\sc \tc \overrightarrow{A B} \sd \td \overrightarrow{A C})}
\text{defpts=\defpts \defsuite}

#endif
#if defined TARGET_alignpts2
 \title{TITLE II}
 \if{\rep=1}{
  \rational{d=simplify((\sc \c) * (\sb \b)  /((\sa \a) - (\sb \b)) )}
  \integer{id= \d>0?1,-1}
  \rational{d=\d<0?\d*(-1)}
  \text{sd=\id=1?+:-}
  }{
  \integer{k=random(1,2)}
  \if{\k=1}
   {
    \rational{d=simplify((\sc \c) * (\sb \b) /((\sa \a) - (\sb \b)) )}
    \integer{id= \d>0?1,-1}
    \rational{d=\d<0?\d*(-1)}
     \text{sd=\id=1?-:+}
   }{
   \rational{d=simplify((\sc \c) * (\sb \b) /((\sa \a) - (\sb \b)) +1 )}
   \rational{d=\d<0?\d*(-1)}
    \integer{id= random(1,-1)}
    \text{sd=\id=1?-:+}
   }
  }
  \text{td=\d=1?:texmath(\d)}
 \text{defpts=\(\overrightarrow{A M} = \sa \ta \overrightarrow{A B} \sb \tb \overrightarrow{B C})<br>
\(\overrightarrow{A N} =)}
\text{defsuite=\d=0? \(\sc \tc \overrightarrow{A B}): \(\sc \tc \overrightarrow{A B} \sd \td \overrightarrow{A C})}
\text{defpts=\defpts \defsuite}
#endif
#if defined TARGET_alignpts3
 \title{TITLE III}
 \if{\rep=1}{
  \if{\sa=\sb and \a=\b}{\text{sb=\ib=1?-:+}}
  \rational{d=simplify((\sc \c+1) * (\sb \b) /((\sa \a) - (\sb \b)) )}
  \integer{id= \d>0?1,-1}
  \rational{d=\d<0?\d*(-1)}
  \text{sd=\id=1?+:-}
  }{
  \integer{k=random(1,2)}
  \if{\k=1}{
    \rational{d=simplify((\sc \c+1) * (\sb \b) /((\sa \a) - (\sb \b)) )}
    \integer{id= \d>0?1,-1}
    \rational{d=\d<0?\d*(-1)}
    \text{sd=\id=1?-:+}
   }{
   \rational{d=simplify((\sc \c+1) * (\sb \b) /((\sa \a) - (\sb \b)) +1 )}
   \rational{d=\d<0?\d*(-1)}
    \integer{id= random(1,-1)}
    \text{sd=\id=1?-:+}
   }
  }
  \text{td=\d=1?:texmath(\d)}
  \text{defpts=\(\overrightarrow{A M} = \sa \ta \overrightarrow{A B} \sb \tb \overrightarrow{B C})<br>
\(\overrightarrow{B N} =)}
\text{defsuite=\d=0? \(\sc \tc \overrightarrow{A B}): \(\sc \tc \overrightarrow{A B} \sd \td \overrightarrow{A C})}
\text{defpts=\defpts \defsuite}
#endif

#if (defined TARGET_alignpts4  || defined TARGET_alignpts5 )
 \text{lstpts=\(M\), \(N\) et \(P\)}
 \text{quest=Les points \(M\), \(N\) et \(P\) sont-ils alignés}
 \integer{numd=randint(1..5)}
 \integer{dend=1}
 \rational{d=simplify(\numd / \dend)}
 \integer{numg=randint(1..5)}
 \integer{deng=1}
 \rational{g=simplify(\numg / \deng)}
 \integer{id=random(1,-1)}
 \text{sd=\id=1?+:-}
 \text{td=\d=1?:texmath(\d)}

 \integer{k=random(1,2)}

#if defined TARGET_alignpts4
 \title{TITLE IV}

 \if{\rep=1}{
    \rational{e=simplify(\g*(\sc \c - (\sa \a)) + (\sa \a))}
    \rational{f=simplify(\g*(\sd \d - (\sb \b)) + (\sb \b))}
  }{
    \rational{e=simplify(\g*(\sc \c - (\sa \a)) - (\sa \a))}
    \rational{f=simplify(\g*(\sd \d +(\sb \b)) + (\sb \b))}
  }
  \text{se=\e>0?:-}
  \text{sf=\f>0?+:-}
  \rational{e=\e<0?\e*(-1)}
  \rational{f=\f<0?\f*(-1)}
  \text{te=\e=1?:texmath(\e)}
  \text{tf=\f=1?:texmath(\f)}

  \text{defpts=\(\overrightarrow{A M} = \sa \ta \overrightarrow{A B} \sb \tb \overrightarrow{A C})<br>
\(\overrightarrow{A N} = \sc \tc \overrightarrow{A B} \sd \td \overrightarrow{A C})<br>
\(\overrightarrow{A P} =)}
\text{defsuite=\e=0?: \(\se \te \overrightarrow{A B})}
\text{defsuite=\f=0?\defsuite:\defsuite \(\sf \tf \overrightarrow{A C})<br>}
\text{defpts=\defpts \defsuite}
#endif
#if defined TARGET_alignpts5
 \title{TITLE V}
 \if{\rep=1}{
  \rational{e=simplify(\g*(\sc \c - (\sa \a) +1) + (\sa \a))}
  \rational{f=simplify(\g*(\sd \d - (\sb \b)) + (\sb \b) -1)}
  }{
  \rational{e=simplify(\g*(\sc \c - (\sa \a) +1) - (\sa \a))}
  \rational{f=simplify(\g*(\sd \d +(\sb \b)) + (\sb \b) -1)}
  }
  \text{se=\e>0?:-}
  \text{sf=\f>0?+:-}
  \rational{e=\e<0?\e*(-1)}
  \rational{f=\f<0?\f*(-1)}
  \text{te=\e=1?:texmath(\e)}
  \text{tf=\f=1?:texmath(\f)}
  \text{defpts=\(\overrightarrow{A M} = \sa \ta \overrightarrow{A B} \sb \tb \overrightarrow{A C})<br>
\(\overrightarrow{B N} = \sc \tc \overrightarrow{A B} \sd \td \overrightarrow{A C})<br>
\(\overrightarrow{C P} =) }
\text{defsuite=\e=0?:\(\se \te \overrightarrow{A B})}
\text{defsuite=\f=0? \defsuite: \defsuite \(\sf \tf \overrightarrow{A C})<br>}
\text{defpts=\defpts \defsuite}
#endif
#endif


\statement{
  On considère un triangle non aplati \(A B C) et les points \lstpts définis par:
<div class="wimscenter">
 \defpts
</div>
\quest ?
}
\answer{Alignement ?}{\rep;Oui,Non}{type=radio}
