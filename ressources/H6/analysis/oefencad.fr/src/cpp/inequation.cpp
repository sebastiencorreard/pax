target=inequation
\author{Huayi, Chen}
\language{fr}
#include "lang_titles.inc"
#include "lang.inc"
\integer{a=randint(-5..5)}
\integer{b=\a+randint(2..4)}

\text{plus=randitem(+,-)}
text{infer=randitem(<,>)}
\text{choix=random(1,2)}
\text{infer=item(\choix,\leq,\geq)}

\integer{c=randint(-5..5)}
\integer{c=\plus issametext + ? (\b)-(\a)+randint(1..5)}
\integer{c=\plus issametext - ? (\b)-(\a)-randint(1..3)}

\text{forma=simplify(x-(\a))}
\text{formb=simplify(x-(\b))}
\text{formc=\c}

\if{\plus issametext +}{
  \if{\choix=2}{
    \text{lborne1=\(-\infty)}
    \rational{rborne1=((\a)+(\b)-(\c))/2}
    \rational{lborne2=((\a)+(\b)+(\c))/2}
    \text{rborne2=\(+\infty)}
  }
  \if{\choix=1}{
    \rational{lborne1=((\a)+(\b)-(\c))/2}
    \rational{rborne1=((\a)+(\b)+(\c))/2}
  }
}

\if{\plus issametext -}{
  \if{\choix=2}{
     \rational{lborne1=((\a)+(\b)+(\c))/2}
     \text{rborne1=\(+\infty)}
  }
  \if{\choix=1}{
    \text{lborne1=\(-\infty)}
    \rational{rborne1=((\a)+(\b)+(\c))/2}
  }
}

\text{reponse=\plus issametext + and \choix=2 ?
\(\rbrack),\lborne1,&#44;,\rborne1,\(\rbrack),\(\cup),
\(\lbrack),\lborne2,&#44;,\rborne2,\(\lbrack)| ,
\(\lbrack),\lborne2,&#44;,\rborne2,\(\lbrack), \(\cup),\(\rbrack),
\lborne1,&#44;,\rborne1,\(\rbrack)}

\text{reponse=\plus issametext + and \choix=1 ?\(\lbrack),\lborne1,&#44;,
\rborne1,\(\rbrack)}
\text{reponse=\plus issametext - and \choix=2 ? \(\lbrack),
\lborne1,&#44;,\rborne1,\(\lbrack)}
\text{reponse=\plus issametext - and \choix=1 ?
 \(\rbrack),\lborne1,&#44;,\rborne1,\(\rbrack)}

\rational{h1=((\a)+(\b)+(\c))/2}
\rational{h2=((\a)+(\b)-(\c))/2}
\text{mauvais=\h1,\h2,0,1/2,1,3/2,2,5/2,3,7/2,4,9/2,5,-1/2,-1,-3/2,
-2,-5/2,-3,-7/2,-4,-9/2,-5,\(\lbrack),\(\rbrack),\(+\infty),\(-\infty),\(\cup)}
\statement{\name_enonce
  <div class="wimscenter">
  \( |\forma | \plus | \formb | \infer \formc\).</div>
  <div class="wims_instruction">\name_inst</div>
  <div class="wimscenter">\embed{reply1}</div>
}
\answer{Solution}{ \reponse;\mauvais}{type=compose}

\hint{\name_hint}
