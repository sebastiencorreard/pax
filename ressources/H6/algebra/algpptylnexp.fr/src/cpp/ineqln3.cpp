target=ineqln3
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{sa=random(1,-1)}
\integer{a=random(1..15)*\sa}
\integer{sb=random(1,-1)}
\integer{b0=random(0..40)}
\integer{b=\b0*\sb}
\integer{sc=random(1,-1)}
\integer{c=random(1..15)*\sc}
!!! a et c différents
\if{\a = \c}{ \integer{c = 2*\c }}
\integer{d=random(-20..20)}

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
\if{\symb1 issametext <}
{\text{def1= &#93; -&#8734; ; \rep1 &#91;}}
{\text{def1= &#93; \rep1 ; +&#8734;&#91;}}

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

!!! ensemble solution codé par a , b
!!! alpha : réponse "a"  dans la liste de choix
!!! alpha = beta = 0 donné pour ensemble vide
!!! attention au bug  où une repi = 0  (O figurerait deux fois)

\if{\rep1==0 or \rep2==0 or \rep3==0}{
  \text{choix=-&#8734;,\rep1,\rep2,\rep3,+&#8734;}
}{
  \text{choix=-&#8734;,0,\rep1,\rep2,\rep3,+&#8734;}
}
\if{\ensdef=1}{\text{sol=0,0}}
\if{\ensdef=2}{
  \if{\symb3 issametext <}{
    \if{\rep3<=\borne1}{\text{sol=0,0}}
    \if{\rep3>=\borne2}{\text{sol=\borne1,\borne2}}
    \if{\rep3>\borne1 && \rep3<\borne2}{\text{sol=\borne1,\rep3}}
  }{
    \if{\rep3>=\borne2}{\text{sol=0,0}}
    \if{\rep3<=\borne1}{\text{sol=\borne1,\borne2}}
    \if{\rep3>\borne1 && \rep3<\borne2}{\text{sol=\rep3,\borne2}}
  }
}
\if{\ensdef=3}{
  \if{\symb3 issametext <}{
    \if{\rep3<=\borne1}{\text{sol=0,0}}
    \if{\rep3>\borne1}{
      \text{sol=\borne1,\rep3}}
  }{
    \if{\rep3<=\borne1}{\text{sol=\borne1,+&#8734;}}
    \if{\rep3>\borne1}{
      \text{sol=\rep3,+&#8734;}
    }
  }
}
\if{\ensdef=4}{
  \if{\symb3 issametext <}{
    \if{\rep3>=\borne2}{\text{sol=-&#8734;,\borne2}}
    \if{\rep3<\borne2}{\text{sol=-&#8734;,\rep3}}
  }{
    \if{\rep3>=\borne2}{\text{sol=0,0}}
    \if{\rep3<\borne2}{ \text{sol=\rep3,\borne2}}
  }
}
\text{intsol=&#93; \sol &#91;}

\text{alph=item(1,\sol)}
\text{bet=item(2,\sol)}
\integer{alph=position(\alph,\choix)}
\integer{bet=position(\bet,\choix)}

\statement{
<div class="wims_question">On veut résoudre dans \(\,\RR\) l'inéquation (I) : \(\ineq\).
Résoudre (I) sur  papier libre,
puis écrire  son ensemble de solutions à l'aide des menus déroulants ci-dessous.
</div>
<div class="wims_instruction">
Pour écrire l'ensemble vide, saisir <span class="tt"> &#93; 0 ; 0 &#91;</span>.
</div>
<div>
L'ensemble des solutions de (I) est l'intervalle :
 <div class="wimscenter">&#93; \embed{reply1} ; \embed{reply2} &#91;</div>
</div>
}

!!!!ANSWERS

\answer{alpha}{\alph;\choix}{type=menu}
\answer{beta}{\bet;\choix}{type=menu}

!!!!!!!! DETAILED resolution

\feedback{0=0}{
#include "feedln.inc"
\if{\sol=0,0}{
  <p>
  L'intersection \(I_1 \cap I_3 \cap I_3) est vide.
    <br>Conclusion : L'inéquation (I) n'a aucune solution.</p>
  }{
    <div class="wimscenter">\(I_1 \cap I_2 \cap I_3) = \def \cap \def3 = \intsol </div>
    <p>Conclusion : L'ensemble des solutions de (I) est \intsol.</p>
  }
}
