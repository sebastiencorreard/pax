target=ptcou

#include "author.inc"
#include "header.inc"
#include "lang_titles.inc"
#include "css.inc"

\title{TITRE}

\if{\confparm1=}{\text{confparm1=1}}
\if{\confparm1 issametext 1,2}{\text{confparm1=randitem(1,2)}}
\if{\confparm2=}{\text{confparm2=1}}

%%Mise en place des coefficients a et b confparm1 =1 affine =2 lineaire  confparm2=1 entiers relatifs =2 rationnels
\text{coefe=shuffle(1,2,3,4,5,-1,-2,-3,-4,-5)}
\text{coefr=shuffle(1/2,1/3,1/4,1/5,2/3,2/5,3/2,3/4,3/5,4/3,4/5,5/2,5/3,5/4,-1/2,-1/3,-1/4,-1/5,-2/3,-2/5,-3/2,-3/4,-3/5,-4/3,-4/5,-5/2,-5/3,-5/4)}
\if{\confparm2=1}{\text{coefa=\coefe[1]}}
\if{\confparm2=2}{\text{coefa=\coefr[1]}}
\if{1 isitemof \confparm2 and 2 isitemof \confparm2}{\text{coefa=randomitem(\coefe[1],\coefr[1])}}
\if{\confparm1=1}{\integer{coefb=randitem(-5,-4,-3,-2,-1,1,2,3,4,5)}
                }
                {\text{coefb=0}
                }
\text{nomfct=randitem(f,g,h,i)}
\integer{b=\coefb}
\text{fon=\coefa*x+(\b)}
\text{texfon=texmath(\fon)}
\integer{xok=randint(-10..10)}

%%Calcul de l'image pour la solution
\integer{ant=\xok}                       
\text{tant=\ant<0?(\ant):\ant}
\if{\coefa isitemof \coefr}{\rational{a=\coefa}
                            \integer{denom=pari(denominator(\a))}
                            \text{pa=\a<0?(\a):\a}
                            \text{tpa=\a<0?(texmath(\pa)):\texmath(\pa)}
                            \text{fon=(\a)*x+(\b)}
                            \text{fon1=simplify(\fon)}
                            \text{fon2=pari(Polrev(\fon1))}
                            \text{texfon=texmath(\fon2)}
                            \text{fonction=\nomfct (x)=\texfon}             
                            \integer{num=pari(numerator(\a))}
                            \rational{cim=(\a)*(\ant)+(\b)}
                            \rational{temp=(\a)*(\ant)}
                            \rational{tmp1=\cim-(\b)}
                            \text{tcim=texmath(\cim)}
                            \text{ttemp=texmath(\temp)}
                            \text{ttmp1=texmath(\tmp1)}
                            \if{\b>0}{\text{tim1=\(\nomfct (\ant)= \frac{\num}{\denom} \times \tant + \b\)}
                                      \text{tim2=\(\nomfct (\ant)= \ttemp + \b\)}
                                      \text{tim3=\(\nomfct (\ant) = \tcim\)}
                                      \text{tmp2=\tcim- \b}
                                      }                                     
                            \if{\b=0}{\text{tim1=\(\nomfct (\ant)= \frac{\num}{\denom} \times \tant\)}
                                      \text{tim2=\(\nomfct (\ant)=\tcim\)}
                                      \text{tmp2=\tcim}                                       
                                       }
                            \if{\b<0}{\text{tim1=\(\nomfct (\ant)= \frac{\num}{\denom} \times \tant \b\)}
                                      \text{tim2=\(\nomfct (\ant)= \ttemp \b\)}
                                      \text{tim3=\(\nomfct (\ant)= \tcim\)}
                                      \text{tmp2=\tcim + \absb}     
                                       }    
                           }
                           {\integer{a=\coefa}
                            \text{pa=\a<0?(\a):\a}
                            \text{tpa=\a<0?(texmath(\pa)):\texmath(\pa)}
                            \text{fon=(\a)*x+(\b)}
                            \text{fon1=simplify(\fon)}
                            \text{fon2=pari(Polrev(\fon1))}
                            \text{texfon=texmath(\fon2)}
                            \text{fonction=\nomfct (x)=\texfon}              
                            \integer{cim=(\a)*(\ant)+(\b)}
                            \integer{tmp=(\a)*(\ant)}
                            \integer{tmp1=\cim-\b}
                            \text{tcim=texmath(\cim)}
                            \if{\b>0}{\text{tim1=\a=1?\(\nomfct (\ant)= \ant + \b\):\(\nomfct (\ant)= \a \times \tant + \b\)}
                                      \text{tim2=\a=1?:\(\nomfct (\ant)=\tmp + \b\)}
                                      \text{tim3=\(\nomfct (\ant)=\tcim\)}
                                      \text{ttmp1=\tcim - \b}
                                     }
                            \if{\b=0}{\text{tim1=\a=1?\(\nomfct (\ant)= \tant\):\(\nomfct (\ant)=\a \times \tant\)}
                                      \text{tim2=\a=1?:\(\nomfct (\ant)=\tcim\)}
                                      \text{ttmp1=\tcim}
                                     }
                            \if{\b<0}{\text{tim1=\a=1?\(\nomfct (\ant)= \ant \b\):\(\nomfct (\ant)= \a \times \tant \b\)}
                                      \text{tim2=\a=1?:\(\nomfct (\ant)= \tmp \b\)}
                                      \text{tim3=\(\nomfct (\ant)=\tcim\)}
                                      \text{ttmp1=\tcim + \absb}
                                     }
                          }
\integer{ch=randint(1,2)}
\if{\ch=1}{\rational{ordo=\cim}
           \text{name_ans3=\name_ans31}
          }{
          \rational{ordo=\cim+randint(-1,1)}
          \text{name_ans3=\name_ans32}
          }    
\text{tordo=texmath(\ordo\)}
#include "lang.inc"
\if{\ch=1}{\text{name_ans2=\name_ans21}}{\text{name_ans2=\name_ans22}}  
\hint{\name_hint}
\text{reply_class=euler_answer_nobg}
\statement{
<div class="euler_quest_nobg spacer">
  \name_enon
  <p>\name_quest <span class="nowrap">\(\nomfct\) ?</span>
</div>
<div class="spacer">
  <div class="\reply_class">
      <ul class="wims_nopuce  spacer">
         <li>\embed{r1,1}</li>
         <li>\embed{r1,2}</li>
      </ul>
  </div>
</div>
}
\answer{}{\ch;\name_list}{type=radio}
\if{\sc_reply1<1}{\text{reply_class=euler_rep_bad_nobg cross}
                 }{
                  \text{reply_class=euler_rep_good_nobg tick}
                  }
\solution{\name_hint
\name_ans1
<span class="nowrap">\tim1</span>
<p><span class="nowrap">\tim2</span></p>
<span class="nowrap">\tim3</span>
<p>\name_ans2 <span class="nowrap">\(\nomfct\).</span></p>}
