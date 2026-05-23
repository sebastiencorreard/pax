target=afeg

#include "author.inc"
#include "header.inc"
#include "lang_titles.inc"
#include "css.inc"

\title{TITRE}
\if{\confparm2=}{\text{confparm2=1}}
\if{\confparm1=}{\text{confparm1=1}}
\if{\confparm1 issametext 1,2}{\text{confparm1=randitem(1,2)}}
%%Détermination du nombre b (rappel:Confparm1=1 affine, confparm1=2 lineaire)
\text{B=}
\for{j=1 to 4}{\if{\confparm1=2}{\integer{tmp=0}}
                                {\integer{tmp=random(1,-1)*(randint(1..5))}}
               \text{B=wims(append item \tmp to \B)}
                 }                  
%%Détermination du coef a (rappel : confparm2 :1 entier, 2 rationnel)
\text{ae=1,2,3,4,5,-1,-2,-3,-4,-5}
\text{ar=1/2,1/3,1/4,1/5,2/3,2/5,3/2,3/4,3/5,4/3,4/5,5/2,5/3,5/4,-1/2,-1/3,-1/4,-1/5,-2/3,-2/5,-3/2,-3/4,-3/5,-4/3,-4/5,-5/2,-5/3,-5/4}
\if{\confparm2=1}{\text{coef=shuffle(slib(data/random 4 item \ae))}}
\if{\confparm2=2}{\text{coef=shuffle(slib(data/random 4 item \ar))}}
\if{1 isitemof \confparm2 and 2 isitemof \confparm2}{\text{coef=shuffle(slib(data/random 4 item \ar,\ae))}}                                         
%%Détermination des abscisses des points d'intersection des droites: abscisses interdites
\text{xinter=}
\for{i=1 to 4}{\for{j=\i+1 to 4}
                  {\real{tmp=-1*(\B[\j]-\B[\i])/(\coef[\j]-\coef[\i])}
                   \text{xinter=wims(append item \tmp to \xinter)}
                  }
              }                
%%Liste des antécédents possibles en retirant les valeurs interdites
\text{choix=-5,-4,-3,-2,-1,0,1,2,3,4,5,\xinter}
\text{choix=wims(listcomplement \xinter in \choix)}
\integer{x1=randitem(\choix)}
\integer{x2=randitem(\choix)}
\integer{x3=randitem(\choix)}
\integer{x4=randitem(\choix)}
\text{ant=\x1,\x2,\x3,\x4}
%%Choix des 4 fonctions
\text{texpf=}
\text{tval=}
\text{img=}
\for{j=1 to 4}{\if{\B[\j]=0}{\text{tB=}}
               \if{\B[\j]<0}{\text{tB=\B[\j]}}
               \if{\B[\j]>0}{\text{tB=\plus \B[\j]}}
               \if{\coef[\j]=-1}{\text{texp=-x \tB}}
               \if{\coef[\j]=1}{\text{texp=x \tB}}
               \if{\coef[\j]<>1 and \coef[\j]<>-1 and \coef[\j] isitemof \ar}{\integer{num=pari(numerator(\coef[\j]))}
                                                                              \integer{deno=pari(denominator(\coef[\j]))}
                                                                              \if{\num<0}{\integer{absnum=abs(\num)}}
                                                                              \if{\num<0}{\text{texp=-\frac{\absnum}{\deno} x \tB}}{\text{texp=\frac{\num}{\deno}x\tB}}
                                                                             }
                                                                             
        \if{\coef[\j]<>1 and \coef[\j]<>-1 and \coef[\j] isitemof \ae}{     \text{texp=\coef[\j] x \tB}
                                                                             }                                                                
 
               \text{liste=\(f:x \mapsto \texp\)}
               \text{tval=wims(append item \texp to \tval)}
               \text{texpf=wims(append item \liste to \texpf)}
               \rational{a=\coef[\j]*\ant[\j]+\B[\j]}
               \text{img=wims(append item \a to \img)}
             } 
                         
                                                              
%%Choix des antécédents et des images
\text{listchant=}
\text{listimg=}
                 
\text{tab2=\(f(\ant[1])=\img[1]\),\(f(\ant[2])=\img[2]\),\(f(\ant[3])=\img[3]\),\(f(\ant[4])=\img[4]\)}
#include "lang.inc"
\statement{
<div class="euler_quest_nobg spacer">\name_quest</div>
<div>\embed{reply1,65x170x170}</div>
}

\answer{}{\tab2;\texpf}{type=correspond}{option=shuffle}
