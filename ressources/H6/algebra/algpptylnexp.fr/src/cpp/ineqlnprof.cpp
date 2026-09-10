target=ineqlnprof
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{sa=random(1,-1)}
\integer{a=random(1..10)*\sa}
\integer{sb=random(1,-1)}
\integer{b0=random(0..20)}
\integer{b=\b0*\sb}
\integer{sc=random(1,-1)}
\integer{c=random(1..10)*\sc}
!!! faire en sorte que a diffère de c
\if{\a=\c}{\integer{c = \c +\sc }}
\integer{d=random(-10..10)}

\text{x=randitem(x,y,z,t)}
\function{u=(\b=0)?\a\x:\a\x+\b}
\text{utex=texmath(\u)}
\function{v=(\d=0)?\c\x:\c\x+\d}
\text{vtex=texmath(\v)}
!!!! inequation ln(ax+b) symb ln(cx+d)

\text{symb=randitem(<,>)}
\text{pos=position(\symb,<,>)}

\text{symb1=\a>0?>:<}
\rational{rep1=-\b/\a}
\if{\symb1 issametext <}{
  \text{def1= &#93; -&#8734; ; \rep1 &#91;}
}{
  \text{def1= &#93; \rep1 ; +&#8734;&#91;}
}

\text{symb2=\c>0?>:<}
\rational{rep2=-\d/\c}
\if{\symb2 issametext <}
{\text{def2= &#93; -&#8734; ; \rep2 &#91;}}
{\text{def2= &#93; \rep2 ; +&#8734;&#91;}}

!!! ens def non vide ?
!!! ensdef : vide (1) / a,b (2) / a,+inf (3) / -inf,a (4)
\if{\symb1 issametext \symb2}{
  \if{\symb1 issametext <}{
    \integer{ensdef=4}
    \text{borne1=-&#8734;}
    \text{borne2=(\rep1<\rep2)?\rep1:\rep2}
  }{
    \integer{ensdef=3}
    \text{borne1=(\rep1<\rep2)?\rep2:\rep1}
    \text{borne2=+&#8734;}
  }
}{
  \if{\symb1 issametext <}{
    \if{\rep1<\rep2}{
      \integer{ensdef=1}
    }{
      \integer{ensdef=2}
      \text{borne1=\rep2}
      \text{borne2=\rep1}
    }
  }{
    \if{\rep1<\rep2}{
      \integer{ensdef=2}
      \text{borne1=\rep1}
      \text{borne2=\rep2}
    }{
      \integer{ensdef=1}
    }
  }
}
\text{def=(\ensdef=1)? &#8709; : &#93; \borne1, \borne2 &#91;}

!!! chgment sens inégalité
\integer{m=\a-\c}
\integer{p=\d-\b}
\text{symb3=(\m>0)?\symb}
\text{symb3=(\m<0 && \pos=1)?item(2,<,>)}
\text{symb3=(\m<0 && \pos=2)?item(1,<,>)}

!!! comme on a defini a =/= c alors m =/= 0

\rational{rep3=\p/\m}
\if{\symb3 issametext <}
{\text{def3= &#93; -&#8734;, \rep3 &#91;}}
{\text{def3= &#93; \rep3, +&#8734;&#91;}}

\text{ineq=ln(\u) \symb ln(\v) }

!!! intervalle des solutions ; selon les cas pour ensdef
!!! on ne demande pas les bornes de l'intervalle !

\if{\ensdef=1}{\integer{enssol=1}}
\if{\ensdef=2}{
  \if{\symb3 issametext <}{
    \if{\rep3<=\borne1}{\integer{enssol=1}}
    \if{\rep3>=\borne2}{
      \integer{enssol=2}
      \text{sol=\borne1 ; \borne2}
    }
    \if{\rep3>\borne1 && \rep3<\borne2}{
      \integer{enssol=2}
      \text{sol=\borne1 ; \rep3}
    }
  }{
    \if{\rep3>=\borne2}{\integer{enssol=1}}
    \if{\rep3<=\borne1}{
      \integer{enssol=2}
      \text{sol=\borne1 ; \borne2}
    }
    \if{\rep3>\borne1 && \rep3<\borne2}{
      \integer{enssol=2}
      \text{sol=\rep3 ; \borne2}
    }
  }
}
\if{\ensdef=3}{
  \if{\symb3 issametext <}{
    \if{\rep3<=\borne1}{\integer{enssol=1}}
    \if{\rep3>\borne1}{
      \integer{enssol=2}
      \text{sol=\borne1 ; \rep3}
    }
  }{
    \if{\rep3<=\borne1}{
      \integer{enssol=3}
      \text{sol=\borne1 ; +&#8734;}
    }
    \if{\rep3>\borne1}{
      \integer{enssol=3}
      \text{sol=\rep3 ; +&#8734;}
    }
  }
}
\if{\ensdef=4}{
  \if{\symb3 issametext <}{
    \if{\rep3>=\borne2}{
      \integer{enssol=4}
      \text{sol=-&#8734; ; \borne2}
    }
    \if{\rep3<\borne2}{
      \integer{enssol=4}
      \text{sol=-&#8734; ; \rep3}
    }
  }{
    \if{\rep3>=\borne2}{\integer{enssol=1}
    }
    \if{\rep3<\borne2}{
      \integer{enssol=2}
      \text{sol=\rep3 ; \borne2}
    }
  }
}
\text{intsol=&#93; \sol &#91;}
\statement{
<div>
Résoudre dans \(\mathbb{R}\) l'inéquation (I) : \(\ineq\) .
</div>
Il s'agit de répondre aux questions suivantes :
<ol><li>
  A quelle condition sur \(x\) le premier membre de (I) est-il défini ?
</li><li>
  A quelle condition sur \(x\) le second membre de (I) est-il défini ?
</li><li>Pour \(\x\) vérifiant les conditions 1. et 2. ,
  on peut simplifier (I) en une inéquation
 (I') du premier degré.
<br>Poser l'inéquation (I').
Quelles sont les solutions de (I') ?
</li><li>
En déduire l'ensemble des solutions de (I).
(il faut tenir compte des conditions obtenues en 1., 2. et 3.)
</li></ol>
#include "feedln.inc"
}
