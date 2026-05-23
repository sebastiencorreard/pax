target=repar

%Inspiré d'un exercice de Fabrice Guérimand

#include "author.inc"
#include "header.inc"
#include "lang_titles.inc"
#include "css.inc"

\title{TITRE}
\if{\confparm1=}{\text{confparm1=1}}
\if{\confparm1 issametext 1,2}{\text{confparm1=randitem(1,2)}}
\if{\confparm2=}{\text{confparm2=1}}

\text{don=shuffle(1,2,3,4,5,6,7,8,9,10)}
\integer{pgcd1=gcd(\don[1],\don[2])}
\integer{a=\don[1]/\pgcd1}
\integer{b=\don[2]/\pgcd1}
\integer{pgcd2=gcd(\don[3],\b)}
\integer{b=\b/\pgcd2}
\integer{c=\don[3]/\pgcd2}
\integer{a=randomitem(1,-1)*\a}
\integer{c=randomitem(1,-1)*\c}
\integer{temp=randint(11..20)}
\if{\b=1}{\text{b=pari(nextprime(\temp))}}
\text{ta=\a>0?\a:(\a)}
\text{ta2=\a>0?\plus \a:\a}
\text{ta3=\a>0?\plus \a:\plus (\a)}
\integer{a2=\a*(\a)}
\text{nomfct=randitem(f,g,h)}
\text{tc=\c>0? \plus \c:\c}
\text{tb=\b>0? \plus \b:\b}
\text{tc2=\c<0? (\c):\c}
\text{nomfct=randitem(f,g,h)}

\if{\confparm1=2}{
  \if{1 isitemof \confparm2}{\if{\a=1}{\matrix{datae=x,1,1 \times x}}
                    \if{\a=-1}{\matrix{datae=-x,-1,-1 \times x
                                              x \times (-1),-1,-1 \times x}}
                    \if{\a<>1 and \a<>-1}{\matrix{datae=\a x,\a,\a \times x
                                                        x \times \ta,\a,\a \times x}}
                  }
  \if{2 isitemof \confparm2}{\if{\a=1}{\matrix{datar=\frac{1}{\b} x,1/\b,\frac{1}{\b} \times x
                                            \frac{x}{\b},1/\b,\frac{1}{\b} \times x}}
                    \if{\a=-1}{\matrix{datar=\frac{-1}{\b} x,-1/\b,\frac{-1}{\b} \times x
                                             \frac{-x}{\b},-1/\b,\frac{-1 \times x}{\b},\frac{-1}{\b} \times x}}
                    \if{\a<>1 and \a<>-1}{\matrix{datar=\frac{\a}{\b} x,\a/\b,\frac{\a}{\b} \times x
                                                        \frac{\a x}{\b},\a/\b,\frac{\a \times x}{\b},\frac{\a}{\b} \times x
                                                        \frac{x \times \ta}{\b},\a/\b,\frac{\ta \times x}{\b},\frac{\a}{\b} \times x}}
                   }
                 }
\if{\confparm1=1}{
  \if{1 isitemof \confparm2}{\if{\a=1}{\matrix{datae=x \tc,1,\c,1 \times x +\tc2
                                            \c + x,1,\c,1 \times x +\tc2}}
                    \if{\a=-1}{\matrix{datae=-x \tc,-1,\c,-1 \times x +\tc2
                                              \c - x,-1,\c,-1 \times x +\tc2}}
                    \if{\a<>1 and \a<>-1}{\matrix{datae=\a x \tc,\a,\c,\a \times x + \tc2
                                                        \c + \a x,\a,\c,\a \times x + \tc2
                                                        x \times \ta \tc,\a,\c,\a \times x + \tc2
                                                        \c + x \times \ta,\a,\c,\a \times x + \tc2
                                                        \ta^2 x \tc,\a2,\c,\a2 \times x + \tc2
                                                        \c \plus \ta^2 x,\a2,\c,\a2 \times x + \tc2
                                                        -\ta^2 x \tc,-\a2,\c,-\a2 \times x + \tc2
                                                        \c \minus \ta^2 x,-\a2,\c,-\a2 \times x + \tc2}}
                    }
  \if{2 isitemof \confparm2}{\if{\a=1}{\matrix{datar=\frac{1}{\b} x \tc,1/\b,\c,\frac{1}{\b} \times x +\tc2
                                            \c + \frac{1}{\b} x,1/\b,\c,\frac{1}{\b} \times x +\tc2
                                            \frac{x}{\b} \tc,1/\b,\c,\frac{1 \times x}{\b} +\tc2,\frac{1}{\b} \times x +\tc2
                                            \c + \frac{x}{\b},1/\b,\c,\frac{1 \times x}{\b} +\tc2,\frac{1}{\b} \times x +\tc2
                                            \frac{x \tc}{\b},1/\b,\c/\b,\frac{1 \times x + \tc2}{\b},\frac{1 \times x}{\b} + \frac{\c}{\b},\frac{1}{\b} \times x + \frac{\c}{\b}
                                            \frac{\c + x}{\b},1/\b,\c/\b,\frac{1 \times x + \tc2}{\b},\frac{1 \times x}{\b} + \frac{\c}{\b},\frac{1}{\b} \times x + \frac{\c}{\b}}}
                    \if{\a=-1}{\matrix{datar=\frac{-1}{\b} x \tc,-1/\b,\c,- \frac{1}{\b} \times x +\tc2
                                             \c + \frac{-1}{\b} x,-1/\b,\c,- \frac{1}{\b} \times x +\tc2
                                             \frac{-x}{\b} \tc,-1/\b,\c,\frac{-1 \times x}{\b} +\tc2,-\frac{1}{\b}\times x + \tc2
                                             \c + \frac{-x}{\b},-1/\b,\c,\frac{-1 \times x}{\b} +\tc2,-\frac{1}{\b}\times x + \tc2
                                             \frac{x \times (-1)}{\b} \tc,-1/\b,\c,\frac{-1 \times x}{\b} + \tc2,-\frac{1}{\b} \times x +\tc2
                                             \c + \frac{x \times (-1)}{\b},-1/\b,\c,\frac{-1 \times x}{\b} + \tc2,-\frac{1}{\b} \times x +\tc2
                                             \frac{-x \tc}{\b},-1/\b,\c/\b,\frac{-1 \times x + \tc2}{\b},\frac{-1 \times x}{\b} + \frac{\c}{\b}, - \frac{1}{\b} \times x + \frac{\c}{\b}
                                             \frac{\c -x}{\b},-1/\b,\c/\b,\frac{-1 \times x + \tc2}{\b},\frac{-1 \times x}{\b} + \frac{\c}{\b}, - \frac{1}{\b} \times x + \frac{\c}{\b}}}
                    \if{\a<>1 and \a<>-1}{\matrix{datar=\frac{\a}{\b} x \tc,\a/\b,\c,\frac{\a}{\b} \times x + \tc2
                                                        \c + \frac{\a}{\b} x,\a/\b,\c,\frac{\a}{\b} \times x + \tc2
                                                        \frac{\a x}{\b} \tc,\a/\b,\c,\frac{\a \times x}{\b}+ \tc2,\frac{\a}{\b} \times x + \tc2
                                                        \c + \frac{\a x}{\b},\a/\b,\c,\frac{\a \times x}{\b}+ \tc2,\frac{\a}{\b} \times x + \tc2
                                                        \frac{x \times \ta}{\b} \tc,\a/\b,\c,\frac{\a \times x}{\b} + \tc2,\frac{\a}{\b} \times x + \tc2
                                                        \c + \frac{x \times \ta}{\b},\a/\b,\c,\frac{\a \times x}{\b} + \tc2,\frac{\a}{\b} \times x + \tc2
                                                        \frac{\a x \tc}{\b},\a/\b,\c/\b,\frac{\a \times x + \tc2}{\b},\frac{\a \times x}{\b} + \frac{\c}{\b},\frac{\a}{\b} \times x + \frac{\c}{\b}
                                                        \frac{\c \ta2 x}{\b},\a/\b,\c/\b,\frac{\a \times x + \tc2}{\b},\frac{\a \times x}{\b} + \frac{\c}{\b},\frac{\a}{\b} \times x + \frac{\c}{\b}}}
                   }
                }
                
\if{\confparm2=1}{\matrix{data=\datae}}
\if{\confparm2=2}{\matrix{data=\datar}}              
\if{1 isitemof \confparm2 and 2 isitemof \confparm2}{\matrix{data=\datae,\datar}}
\text{data=randomrow(\data)}
\integer{nbdata=items(\data)}

#include "lang.inc"
\text{name_hint=\confparm1=2?\name_hintl:\name_hinta}
\text{sol1=\(\nomfct(x)=\data[1]\)}
\if{\confparm1=2}{\text{name_quest=\name_questl}
                  \text{name_ans1=\name_ans1l}
                  \text{sol2=\(\nomfct(x)=\data[3]\)}
                  \if{\nbdata=4}{\text{sol2=\sol2
                                            <p>\(\nomfct(x)=\data[4]\)
                                      }
                                }
                  \text{sol3=\name_ans1 <span class="nowrap">\(\data[2]\).</span>}
                 }{\text{name_quest=\name_questa}
                   \text{name_ans1=\name_ans1a}
                   \text{name_ans2=\name_ans2a}
                   \text{sol2=\(\nomfct(x)=\data[4]\)}
                   \if{\nbdata>4}{\text{sol2=\sol2
                                             <p>\(\nomfct(x)=\data[5]\)</p>}
                                 }
                   \if{\nbdata>5}{\text{sol2=\sol2
                                             <p>\(\nomfct(x)=\data[6]\)</p>
                                       }
                                 }
                   \text{sol3=\name_sol3a}
                 }             

\hint{\name_hint}
\text{r=\confparm1=2?r1:r1,r2}
\steps{\r}
\text{reply_class1=euler_answer_nobg}
\text{reply_class2=euler_answer_nobg}

\statement{
<div class="euler_quest_nobg">\name_quest</div>
<div class="\reply_class1">
    <label for="reply1">\name_ans1</label><span class="nowrap"> \embed{reply1,6}.</span>             
</div>               
\if{\confparm1=1}{
    <div class="\reply_class2">
      <label for="reply2">\name_ans2</label><span class="nowrap"> \embed{reply2,6}.</span>
    </div>
                 }
<div class="wims_instruction">\name_inst</div>
}

\answer{}{\data[2]}{type=numexp}
\answer{}{\data[3]}{type=numexp}
\if{\sc_reply1<1}{\text{reply_class1=euler_rep_bad_nobg cross}
                 }{
                   \text{reply_class1=euler_rep_good_nobg tick}
                   }
\if{\sc_reply2<1}{\text{reply_class2=euler_rep_bad_nobg cross}
                 }{
                  \text{reply_class2=euler_rep_good_nobg tick}
                   } 
\feedback{\reply1=\data[3] and \reply2=\data[2]}{<div class="highlight">Vous avez inversé coefficient directeur et ordonnée à l'origine.</div>}
\feedback{\reply1=-1*\data[2] and \reply1<>\data[3]}{<div class="highlight spacer">Vous vous êtes trompé dans le signe du coefficient directeur.</div>}
\feedback{\reply2=-1*\data[3] and \reply2<>\data[2]}{<div class="highlight spacer">Vous vous êtes trompé dans le signe de l'ordonnée à l'origine.</div>}                               
\solution{\sol1
<p>\name_hint</p>
\sol2
<p>\sol3</p>
}
