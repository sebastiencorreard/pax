target=ineqln ineqln1bis
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
!!! eviter que a soit egal à c ; changer c en une valeur non nulle
\if{\a = \c}{ \integer{c = \c+\sc }}
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
\rational{rep3=\p/\m}
\if{\symb3 issametext <}
{\text{def3= &#93; -&#8734;, \rep3 &#91;}}
{\text{def3= &#93; \rep3, +&#8734;&#91;}}

#if defined TARGET_ineqln1bis
\text{ineq=texmath(ln(\u) \symb ln(\v))}
#endif
#if defined TARGET_ineqln
\text{ineq=ln(\u) \symb ln(\v)}
#endif

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
#if defined TARGET_ineqln1bis
choix1
\text{liste1=>,<}
\text{choix1=position(\symb1,\liste1)}
choix3
\text{choix3=position(\symb2,\liste1)}
choix5
\text{choix5=position(\symb3,\liste1)}
\steps{reply1,reply2
reply3,reply4
reply5,reply6,reply7}
#endif
\statement{
#if defined TARGET_ineqln
<div>On veut résoudre dans \(\mathbb{R}\) l'inéquation (I) : \(\ineq\).
Résolvez (I) sur papier libre,
puis complétez les affirmations suivantes.
</div>
<ol><li>
Le premier membre de (I) est défini à condition que \(\x\) \embed{choice1} \embed{reply1,5}.
</li><li>
Le second membre de (I) est défini à condition que  \(\x\) \embed{choice2} \embed{reply2,5}.
</li><li>
Pour tout réel \(\x) vérifiant les  conditions 1. et 2. ,  on a :
<div class="wimscenter">
  \( \ineq\) \( \Longleftrightarrow \x \)
  \embed{choice3} \embed{reply3,5}
</div>
</li><li>
L'ensemble des solutions de (I) est
  \embed{reply4}
</li></ol>
#endif
#if defined TARGET_ineqln1bis
<i>Cet exercice comporte 3 étapes.</i>
<div>On veut résoudre dans \(\mathbb{R}\) l'inéquation (I) :  \(\ineq) .
</div>
\if{\step=1}
{<div>1. Le premier membre de (I) est défini à condition que \(\x) \embed{reply1} \embed{reply2,5}.</div>}
\if{\step=2}
{\if{\sc_reply2=1 and \reply1=\symb1}{<span class="oef_indgood">Bonne réponse !</span>}
<div>2. Le second membre de (I) est défini à condition que  \(\x) \embed{reply3} \embed{reply4,5}.</div>}
\if{\step=3}{
\if{\sc_reply4=1 and \reply3=\symb2}{<span class="oef_indgood">Bonne réponse !</span>}
<p>3. Effectivement, l'inéquation (I) est défini pour tout réel \(\x\)
vérifiant les  conditions \({\x \symb1 \rep1}) et \({\x \symb2 \rep2}).</p>
On peut alors écrire :
<div class="wimscenter">
  \( \ineq\) \(\; \Longleftrightarrow \; \x \)
  \embed{reply5} \embed{reply6,5}
</div><div>
On en déduit que l'ensemble des solutions de (I) est
  \embed{reply7}
</div>
  }
#endif
}

!!!!ANSWERS
#if defined TARGET_ineqln
\choice{ensdef1a}{\symb1}{<,>}
\answer{ensdef1b}{\rep1}{type=numexp}
\choice{ensdef2a}{\symb2}{<,>}
\answer{ensdef2b}{\rep2}{type=numexp}
\choice{resoa}{\symb3}{<,>}
#endif
#if defined TARGET_ineqln1bis
\answer{ensdef1a}{\choix1;\liste1}{type=menu}
\answer{ensdef1b}{\rep1}{type=numexp}
\answer{ensdef2a}{\choix3;\liste1}{type=menu}
\answer{ensdef2b}{\rep2}{type=numexp}
\answer{resoa}{\choix5;\liste1}{type=menu}
#endif
\answer{resob}{\rep3}{type=numexp}
\answer{enssol}{\enssol;vide, un intervalle borné, un intervalle du type &#93;&#945;&#160;&#59;&#160;+&#8734;&#91;, un intervalle du type &#93;-&#8734;&#160;&#59;&#160;&#945;&#91;}{type=menu}
#if defined TARGET_ineqln
\feedback{0=0}{
#include "feedln.inc"
Formons d'abord l'intersection des deux premiers intervalles :
<div class="wimscenter">\(I_1 \cap I_2) = \def1 \cap \def2 = \def
</div>
#include "feedln1.inc"
}
#endif
#if defined TARGET_ineqln1bis
\solution{
#include "feedln.inc"
#include "feedln1.inc"
}
#endif
