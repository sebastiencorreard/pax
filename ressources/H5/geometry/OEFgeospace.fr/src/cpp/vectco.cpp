target=colinvect1 colinvect2 coplanvect1 coplanvect2

#include "author.inc"
#include "lang_titles.inc"
\precision{100}
\text{confparm1= \confparm1 = ? 2 : \confparm1}
#include "css.inc"
#include "lang.inc"
 \integer{rep=random(1,2)}
 \integer{numa=randint(2..5)}
 \integer{dena=1}
 \rational{a=simplify(\numa / \dena)}
 \integer{numb=randint(2..5)}
 \integer{denb=1}
 \rational{b=simplify(\numb / \denb)}
 \integer{numc=randint(2..5)}
 \integer{denc=1}
 \rational{c=simplify(\numc / \denc)}
 \integer{numd=randint(2..5)}
 \integer{dend=1}
 \rational{d=simplify(\numd / \dend)}
 \integer{ia=random(1,-1)}
 \integer{ib=random(1,-1)}
 \integer{ic=random(1,-1)}
 \text{sa=\ia=1?:-}
 \text{sb=\ib=1?+:-}
 \text{sc=\ic=1?:-}
 \text{ta=\a=1?:texmath(\a)}
 \text{tb=\b=1?:texmath(\b)}
 \text{tc=\c=1?:texmath(\c)}

#if defined TARGET_colinvect1
 \text{lstpts=\(\vec{u}) et \(\vec{v})}
 \text{quest=Les vecteurs \(\vec{u}) et \(\vec{v}) sont-ils colinéaires}
 \if{\rep=1}{
  \rational{d=simplify( (\c) * (\b) / (\a))}
  \integer{id= \ic *\ia *\ib}
  \text{sd=\id=1?+:-}
  }{
  \integer{k=random(1,2)}
  \if{\k=1}{
     \rational{d=simplify(\c * \b / \a)}
     \integer{id= \ic *\ia *\ib}
     \text{sd=\id=1?-:+}
   }{
     \rational{d=simplify(\c * \b / \a+1)}
     \integer{id= random(1,-1)}
     \text{sd=\id=1?-:+}
   }
  }
\text{td=\d=1?:texmath(\d)}

\text{vct=shuffle(\overrightarrow{A B},\overrightarrow{A C},\overrightarrow{A D})}
 \text{defpts=\(\vec{u} = \sa \ta \vct[1] \sb \tb \vct[2])<br>
\(\vec{v} = \sc \tc \vct[1] \sd \td \vct[2])}

\statement{
<div class="\style1">
<p>
On considère un tétraèdre \(A B C D) et les vecteurs \lstpts définis par :</p>
<p class="wimscenter"> \defpts </p>
<div>
\quest ? \embed{reply1} </div>
</div>
}
\answer{Colinéaires ?}{\rep;Oui,Non}{type=radio}
#endif
#if defined TARGET_colinvect2
 \integer{numa=random(1..5)}
 \integer{dena=\numa+random(1..4)}
 \rational{a=simplify(\numa / \dena)}
 \text{ta=\a=1?:texmath(\a)}
\text{vct=\overrightarrow{B C},\overrightarrow{A C},\overrightarrow{D B},\overrightarrow{D C}}
\text{vctn=\overrightarrow{B N},\overrightarrow{A N},\overrightarrow{D N},\overrightarrow{D N}}
\integer{ind=randint(1,1,1,2,3,4)}
\integer{rep1=\ind=1?1:2}
\text{mstep=\ind>1?r1:r1
r2}
\rational{valk=1-\a}
 \text{defpts=\(\overrightarrow{A M} = \ta \overrightarrow{A B})<br>
\(\vctn[\ind] = k \vct[\ind])}
\steps{\mstep}

\statement{
<div class="\style1">
<p>
On considère un tétraèdre \(A B C D) et les points \(M) et \(N) définis par :</p>
<p class="wimscenter">\defpts</p>
<div>
\if{\step=1}{
Peut-on trouver une valeur de \(k) telle que les vecteurs \(\overrightarrow{A C})
et \(\overrightarrow{M N}) soient colinéaires ?
\embed{reply1}
}{
Pour quelle valeur de \(k) les vecteurs \(\overrightarrow{A C}) et \(\overrightarrow{M N}) sont-ils colinéaires ?
\(k=)</label>\embed{reply2,3}
}
</div>
</div>
}
\answer{colinéaires?}{\rep1;Oui,Non}{type=radio}
\answer{k}{\valk}{type=numexp}
#endif
#if defined TARGET_coplanvect1
\integer{k=randint(1..3)}
\text{vct2=\k=1?\overrightarrow{A B}:\overrightarrow{A C}}
\integer{ind=\k=2?randint(1..4):randint(5..8)}
\text{vct=\overrightarrow{C B},\overrightarrow{B C},\overrightarrow{A C},\overrightarrow{C A},\overrightarrow{A D},\overrightarrow{D A},\overrightarrow{D B},\overrightarrow{B D}}
\integer{rep1=\k=3?2:1}
 \text{defpts=\(\overrightarrow{A M} = \a \overrightarrow{A B})<br>
\(\overrightarrow{A N} = \b \vct2)<br>
\(\overrightarrow{A P} = \c \overrightarrow{A B} + \d \vct[\ind])}

\statement{
<div class="\style1">
<p>
On considère un tétraèdre \(A B C D) et les points \(M\), \(N\) et \(P\) définis par :
</p>
<p class="wimscenter">\defpts</p>
<div>
Les vecteurs \(\overrightarrow{A M}\), \(\overrightarrow{A N}) et \(\overrightarrow{A P})
sont-ils coplanaires? \embed{reply1}
</div>
</div>
}
\answer{coplanaires?}{\rep1;Oui,Non}{type=radio}
#endif
#if defined TARGET_coplanvect2
 \text{lstpts=\(M\), \(N\), \(P\) et \(Q\)}
 \integer{k=randint(1..4)}
 \text{vct2=\k>2?\overrightarrow{B C}:\overrightarrow{D C}}
 \text{quest=Les vecteurs \(\overrightarrow{M N}), \(\overrightarrow{P Q}) et \(\vct2)}
 \integer{b=\k=1?1-\a:1+\a}
 \integer{c=\k=3?1+\d:1+2*\d}
 \text{tb=\b=1?:texmath(\b)}
 \text{tb=\b=-1?-:\tb}
 \text{tc=\c=1?:texmath(\c)}
 \text{td=\d=1?:texmath(\d)}
 \text{defpts=\(\overrightarrow{A M} = \ta \overrightarrow{A B})<br>
\(\overrightarrow{B N} = \tb \overrightarrow{B C}\)<br>
\(\overrightarrow{C P} = \tc \overrightarrow{C D}\)<br>
\(\overrightarrow{D Q} = \td \overrightarrow{A D}\)<br>
}
\integer{rep1=\k=1 or \k=3?1:2}

\statement{
<div class="\style1">
On considère un tétraèdre \(A B C D) et les points \lstpts définis par :
<p class="wimscenter">\defpts</p>
<div>
\quest sont-ils coplanaires ?
 Votre réponse : \embed{reply1}
</div>
</div>
}
\answer{coplanaires}{\rep1;Oui,Non}{type=radio}
#endif
