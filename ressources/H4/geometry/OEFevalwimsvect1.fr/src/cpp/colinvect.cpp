target=colinvect1 colinvect2 colinvect3 colinvect4 colinvect5
\language{fr}
\range{-5..5}
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{100}
#define TITLE Vecteurs colinéaires
 \integer{rep=randitem(1,2)}
 \integer{numa=randint(2..5)}
 \integer{dena=1}
 \rational{a=simplify(\numa / \dena)}
 \integer{numb=randint(1..5)}
 \integer{denb=1}
 \rational{b=simplify(\numb / \denb)}
 \integer{numc=randint(2..5)}
 \integer{denc=1}
 \rational{c=simplify(\numc / \denc)}
 \integer{ia=randitem(1,-1)}
 \integer{ib=randitem(1,-1)}
 \integer{ic=randitem(1,-1)}
 \text{sa=\ia=1?:-}
 \text{sb=\ib=1?+:-}
 \text{sc=\ic=1?:-}
 \text{ta=\a=1?:texmath(\a)}
 \text{tb=\b=1?:texmath(\b)}
 \text{tc=\c=1?:texmath(\c)}

#if defined TARGET_colinvect1
 \title{TITLE I}
 \text{lstpts=\(\vec{u}) et \(\vec{v})}
 \text{quest=Les vecteurs \(\vec{u}) et \(\vec{v}) sont-ils colinéaires}
 \if{\rep=1}{
  \rational{d=simplify( (\c) * (\b) / (\a))}
  \integer{id= \ic *\ia *\ib}
  \text{sd=\id=1?+:-}
  }{
  \integer{k=randitem(1,2)}
  \if{\k=1}{
     \rational{d=simplify(\c * \b / \a)}
     \integer{id= \ic *\ia *\ib}
     \text{sd=\id=1?-:+}
   }{
     \rational{d=simplify(\c * \b / \a+1)}
     \integer{id= randitem(1,-1)}
     \text{sd=\id=1?-:+}
   }
  }
  \text{td=\d=1?:texmath(\d)}

 \text{defpts=\(\vec{u} = \sa \ta \vec{i} \sb \tb \vec{j})<br>
\(\vec{v} = \sc \tc \vec{i} \sd \td \vec{j})}
\statement{
  On considère deux vecteurs \(\vec{i}) et \(\vec{j}) non colinéaires et les vecteurs \lstpts définis par
<div class="wimscenter">
 \defpts
</div>
\quest ?
}
\answer{Colinéaires ?}{\rep;Oui,Non}{type=radio}
#endif
#if defined TARGET_colinvect2
 \title{TITLE II}
 \text{lstpts=\(I\), \(J\), \(M\), \(N\) et \(P\)}
 \integer{numa=random(1..5)}
 \integer{dena=\numa+random(1..4)}
 \rational{a=simplify(\numa / \dena)}
 \rational{b=1- \a}
 \integer{numc=random(2..5)}
 \integer{denc=1}
 \rational{c1=simplify(\numc / \denc)}
 \integer{numc=random(1..5)}
 \integer{denc=1}
 \rational{c3=simplify(\numc / \denc)}
 \text{quest=Les vecteurs \(\overrightarrow{M N}) et \(\overrightarrow{M P})}
 \text{v1=\(\overrightarrow{M N})}
 \text{v2=\(\overrightarrow{M P})}
 \rational{c2=simplify(\c1-1+(\b)*((\c3)-(\c1)))}
 \if{\rep=2}{
  \integer{k=randitem(1,2)}
  \if{\k=1}{
     \rational{c2=simplify(-1+(\b)*((\c3)-(\c1)))}
    }{
     \rational{c2=simplify(\c1+\b*((\c3)-(\c1)))}
    }
  }
 \text{ta=\a=1?:texmath(\a)}
 \text{tb=\b=1?:texmath(\b)}
 \text{tc1=\c1=1?:texmath(\c1)}
 \text{tc2=\c2=1?:texmath(\c2)}
 \text{tc3=\c3=1?:texmath(\c3)}
 \text{defpts=\(\overrightarrow{A I} = \ta \overrightarrow{A D})<br>
\(\overrightarrow{C J} = \tb \overrightarrow{C B})<br>
\(\overrightarrow{D M} = \tc1 \overrightarrow{D C})<br>
\(\overrightarrow{J N} = \tc2 \overrightarrow{I J})<br>
\(\overrightarrow{A P} = \tc3 \overrightarrow{A B})}
\rational{x1=\c2-\c1+1}
\rational{y1=-\b}
\rational{x2=\c3-\c1}
\rational{y2=-1}
#endif
#if defined TARGET_colinvect3
 \title{TITLE III}
 \text{lstpts=\(I\), \(J\) et \(K\)}
 \text{quest=Les vecteurs \(\overrightarrow{I J}) et \(\overrightarrow{I K})}
 \text{v1=\(\overrightarrow{I J})}
 \text{v2=\(\overrightarrow{I K})}
 \rational{c2=\c}
 \rational{c1= simplify(\b + ((\c2)-1)*(\b-1+(\a)))}
 \integer{rep=1}
 \if{\rep=2}{
    \rational{c1= simplify(\b + ((\c2)+1)*(\b-1+(\a)))}
  }
 \text{tc1=\c1=1?:texmath(\c1)}
 \text{tc2=\c2=1?:texmath(\c2)}
 \text{sc=\c2>0?+}
 \text{defpts=\(\overrightarrow{C I} = \tb \overrightarrow{C D})<br>
\(\overrightarrow{A J} = \ta \overrightarrow{A B})<br>
\(\overrightarrow{B K} = \tc1 \overrightarrow{B A} \sc \tc2 \overrightarrow{B C})}
\rational{x1=\a+\b-1}
\rational{y1=-1}
\rational{x2=\b-\c1}
\rational{y2=\c2-1}
#endif

#if defined TARGET_colinvect4
 \title{TITLE IV}
 \text{lstpts=\(E\), \(F\), \(G\) et \(H\)}
 \text{quest=Les vecteurs \(\overrightarrow{E F}) et \(\overrightarrow{G H})}
 \text{v1=\(\overrightarrow{E F})}
 \text{v2=\(\overrightarrow{G H})}
 \rational{d=simplify(\b*((\c)-1)/((\a)-1))}
 \if{\rep=2}{
   \rational{d=simplify(\b*((\c)-1)/((\a)+1))}
  }
 \text{td=\d=1?:texmath(\d)}
 \text{defpts=\(\overrightarrow{A E} = \ta \overrightarrow{A B})<br>
\(\overrightarrow{B F} = \tb \overrightarrow{B C})<br>
\(\overrightarrow{C G} = \tc \overrightarrow{C D})<br>
\(\overrightarrow{D H} = \td \overrightarrow{D A})
}
\rational{x1=1-\a}
\rational{y1=\b}
\rational{x2=\c-1}
\rational{y2=-\d}

#endif
#if defined TARGET_colinvect5
 \title{TITLE V}
 \text{lstpts=\(E\) et \(M\)}
 \text{quest=Trouver le réel \(k) tel que \(\overrightarrow{A E}= k \overrightarrow{A C})}
 \rational{rep=simplify(\a / (1 + \a))}
 \text{v1=\(\overrightarrow{D E})}
 \text{v2=\(\overrightarrow{D M})}
 \text{x1=k}
 \text{y1=k-1}
 \text{x2=\a}
 \text{y2=-1}
 \text{defpts=\(\overrightarrow{A M} = \ta \overrightarrow{A B})<br>
\(E) est le point d'intersection des droites \((A C)) et \((D M))}

\statement{
  On considère un parallélogramme \(A B C D) et les points \lstpts définis par
<div class="wimscenter">
 \defpts
</div>
<p>\quest</p>
<p>
  Pour cela, exprimer \v1 et \v2 en fonction des vecteurs \(\overrightarrow{A B})
  et \(\overrightarrow{A D}) et du réel \(k):
</p>
<ul>
<li><label for="reply2">\v1=</label>\embed{reply2,4}\(\overrightarrow{A B})+\embed{reply3,4}\(\overrightarrow{A D})</li>
<li><label for="reply4">\v2=</label>\embed{reply4,4}\(\overrightarrow{A B})+\embed{reply5,4}\(\overrightarrow{A D})</li>
</ul>
<div>
  En tenant compte du fait que les points \(D), \(E) et \(M) sont alignés,
  <label for="reply1">en déduire la valeur de \(k\) sous la forme d'un rationnel:</label>
  \embed{reply1}.
</div>
}
\answer{valeur de k :}{\rep}{type=numexp}
\answer{}{\x1}{type=algexp}
\answer{}{\y1}{type=algexp}
\answer{}{\x2}{type=algexp}
\answer{}{\y2}{type=algexp}
#endif
#if (defined TARGET_colinvect4 || defined TARGET_colinvect3 || defined TARGET_colinvect2)
\statement{
  On considère un parallélogramme \(A B C D) et les points \lstpts définis par
<div class="wimscenter">
 \defpts
</div>
  Exprimer \quest en fonction des vecteurs \(\overrightarrow{A B}) et \(\overrightarrow{A D}):
<ul>
<li><label for="reply2">\v1=</label>\embed{reply2,4}\(\overrightarrow{A B})+\embed{reply3,4}\(\overrightarrow{A D})</li>
<li><label for="reply4">\v2=</label>\embed{reply4,4}\(\overrightarrow{A B})+\embed{reply5,4}\(\overrightarrow{A D})</li>
</ul>
\quest sont-ils colinéaires?
}
\answer{Colinéaires ?}{\rep;Oui,Non}{type=radio}
\answer{}{\x1}{type=numeric}
\answer{}{\y1}{type=numeric}
\answer{}{\x2}{type=numeric}
\answer{}{\y2}{type=numeric}
#endif
