target=cim cant

#include "author.inc"
#include "header.inc"
#include "lang_titles.inc"
#include "css.inc"

\if{\confparm1=}{\text{confparm1=1}}
\if{\confparm1 issametext 1,2}{\text{confparm1=randitem(1,2)}}
\if{\confparm2=}{\text{confparm2=1}}

%%Mise en place des coefficients a et b confparm1 =1 affine =2 lineaire et confparm2 =1 entiers relatifs =2 rationnels
\text{coefe=2,3,4,5,-2,-3,-4,-5}               
\text{coefr=1/2,1/3,1/4,1/5,2/3,2/5,3/2,3/4,3/5,4/3,4/5,5/2,5/3,5/4,-1/2,-1/3,-1/4,-1/5,-2/3,-2/5,-3/2,-3/4,-3/5,-4/3,-4/5,-5/2,-5/3,-5/4}
\if{\confparm2=1}{\text{coef=shuffle(\coefe)}}
\if{\confparm2=2}{\text{coef=shuffle(\coefr)}}
\if{1 isitemof \confparm2 and 2 isitemof \confparm2}{\text{coef=shuffle(\coefe,\coefr)}}
\text{coefa=\coef[1]}
\if{\confparm1=1}{\text{coefb=random(1,-1)*randitem(1,2,3,4,5)}
                }
                {\text{coefb=0}
                }            
\text{nomfct=randitem(f,g,h,i)}
\integer{b=\coefb}
\text{tb=\b<0?(\b):\b}
\text{sb=\b>0? \plus \b:\b}
\integer{absb=abs(\b)}
\text{tcoefa=texmath(\coefa)}
\text{exprfon=pari((\coefa)*x+(\b))}
\text{texprfon=texmath(\exprfon)}
\integer{nb1=random(1,-1)*random(2..35)}
\integer{nb2=random(1,-1)*random(2..35)}
%%Eviter que l'antécédent cherché soit l'image du nombre choisi%%
\real{imant=\b/(1-\coefa)}
\if{\nb1=\imant}{\integer{nb1=\nb1+1}}
           
%%Calcul de l'image 
\integer{ant=\nb1}
\text{tant=\ant<0?(\ant):\ant}

\if{\coefa isitemof \coefr}{\rational{a=\coefa}
                            \text{ta=texmath(\a)}
                            \text{pa=\a<0?(\a):\a}
                            \text{tpa=\a<0?(texmath(\pa)):\texmath(\pa)}
                            \text{fon=(\a)*x+(\b)}
                            \text{fon1=simplify(\fon)}
                            \text{fon2=pari(Polrev(\fon1))}
                            \text{texfon=texmath(\fon2)}
                            \text{fonction=\nomfct (x)=\texfon}             
                            \integer{num=pari(numerator(\a))}
                            \integer{denom=pari(denominator(\a))}
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
                           \text{ta=texmath(\a)}
                            \text{pa=\a<0?(\a):\a}
                            \integer{abspa=abs(\pa)}
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
\text{tnb2=texmath(\nb2)}
#include "lang.inc"
\if{\confparm1=1}{\text{name_enonc1=\name_enonc1a}
                  \text{name_ans1=\name_ans1a}
                 }{
                 \text{name_enonc1=\name_enonc1l}
                 \text{name_ans1=\name_ans1l}
                 }

#if defined TARGET_cim
\title{TITRE}
\rational{sol=\cim}
\solution{\name_ans1
<p>\name_ans2</p>
<p>\name_phrase <span class="nowrap">\(\sol\).</span></p>                
}
\rational{badant=(\nb1-\b)/(\a)}
#endif

#if defined TARGET_cant
\title{TITRE}
\rational{sol=(\nb2-\b)/(\a)}
\integer{numsol=\nb2-\b}
\integer{denomsol=pari(denominator(\sol))}
\text{tsol=texmath(\sol)}
\integer{tmp1=\nb2-\b}
\if{\b>0}{\text{ttmp1=\nb2 - \b}
          \text{eq1=\(\ta x +\b - \b=\ttmp1\)}}
\if{\b=0}{\text{ttmp1=\nb2}
          \text{eq1=\(\tmp1)}}
\if{\b<0}{\text{ttmp1=\(\nb2 -\absb + \absb\)}
           \text{eq1=\(\ta x-\absb + \absb=\nb2 + \absb\)}}
\real{img=\a*\nb2+\b}

\solution{<p>\name_ans1</p>
\name_ans2<span class="nowrap">\(\nomfct (x)=\tnb2\).</span>
<p>\(\texfon=\tnb2\)</p>

\if{\confparm1=1}{\if{\coefa isitemof \coefr}{\name_eq1
                                         <p>\eq1</p>                                             
                                         \(\ta x = \tmp1\)
                                           <p>\(\ta \times x = \tmp1\)</p>
                                          \name_eq2
                                          <p>\(\frac{\ta \times x }{\ta}=\frac{\tmp1}{\ta}\)</p>
                                          \(x=\tmp1 \div \tpa\) 
                                          <p>\name_eq3</p>
                                          \(x=\tmp1 \times \frac{\denom}{\num}\)
                                          <p>\(x=\tsol\)</p>
                                          }
                  \if{\coefa isitemof \coefe and \coefa<>1}{\name_eq1
                                                    <p>\eq1</p>  
                                                    <p>\(\a \times x = \tmp1\)</p>
                                                    \name_eq2
                                                    <p>\(\frac{\a \times x}{\a}=\frac{\tmp1}{\a}\)</p> 
                                                    \if{\abspa<>\denomsol}{\(x=\frac{\tmp1}{\a}\)}
                                                    <p>\(x=\tsol\)</p>                                                    
                                                  }
                 \if{\coefa=1}{\name_eq1
                               <p>\eq1</p>
                               \(x=\tsol\)  
                                 }

                  }                       
                 {\if{\coefa isitemof \coefr}{\(\ta \times x = \ttmp1\)
                                          <p>\name_eq2</p>
                                          <p>\(\frac{\ta \times x }{\ta}=\frac{\tmp1}{\ta}\)</p>
                                          \(x=\tmp1 \div \tpa\) 
                                          <p>\name_eq3</p>
                                          \(x=\tmp1 \times \frac{\denom}{\num}\)
                                          <p>\(x=\tsol\)</p>  
                                              }
                 \if{\coefa isitemof \coefe}{\(\a \times x = \ttmp1\)
                                                   <p>\name_eq2</p>
                                                  \(\frac{\a \times x}{\a}=\frac{\tmp1}{\a}\) 
                                                  \if{\abspa<>\denomsol}{<p>\(x=\frac{\tmp1}{\a}\)}</p>
                                                   <p>\(x=\tsol\)</p>
                                                 }
                \if{\coefa=-1}{<p>\(\a \times x = \tmp1\)</p>
                                   \name_eq2
                                   <p>\(\frac{\a \times x}{\a}=\frac{\tmp1}{\a}\)</p> 
                                    <p>\(x=\tsol\)</p>     
                                    }
                }
<p>\name_phrase <span class="nowrap">\(\tsol\).</span></p>  
}
#endif



\integer{test1=2}
\integer{test2=2}
\text{reply_class=euler_answer_nobg}
\statement{\name_enonc1 
<div class="euler_quest_nobg spacer">\name_quest</div>
<div class="\reply_class"><label for="reply1">\name_phrase</label> \embed{r1,4}.</div>
<div class="wims_instruction spacer">\name_inst</div>
}

#if defined TARGET_cim
\answer{\name_image}{\rep}{type=numexp}{option=noreduction}
\feedback{\rep=\badant}{<div class="highlight">\name_feedi</div>}
#endif
#if defined TARGET_cant
\answer{\name_antecedent}{\rep}{type=numexp}{option=noreduction}
\feedback{\rep=\img}{<div class="highlight">\name_feeda<span class="nowrap">\(\texfon=\tnb2\).</span></div>}

#endif
\condition{\name_cond1}{\rep=\sol}{weight=3}
\condition{\name_cond2}{\rep issamecase \sol}{weight=1}
\integer{test1=\rep=\sol?1:0}
\integer{test2=\rep issamecase \sol?1:0}
\if{\test1<1 or \test2<1}{
    \text{reply_class=euler_rep_bad_nobg cross}
                         }{
    \text{reply_class=euler_rep_good_nobg tick}
                         }
\feedback{\rep=\sol and (\rep notsamecase \sol)}{<div class="highlight">\name_feed</div>}
