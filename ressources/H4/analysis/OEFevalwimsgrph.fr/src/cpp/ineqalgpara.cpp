target=ineqalgpara1 ineqalgpara2 ineqalgpara3 ineqalgpara4 ineqalgpara5
#include "author.inc"
#include "lang_titles.inc"
#if defined TARGET_ineqalgpara4
\integer{dena=randitem(1,1,1,1,1,2,2,3,3,4,5)}
\integer{denb=randitem(1,1,1,1,1,2,2,3,3,4,5)}
\integer{denc=randitem(1,1,1,1,1,4,4,9,9)}
\integer{dend=randitem(1,1,1,1,1,2,2,3,3,4,5)}
\integer{dene=randitem(1,1,1,1,1,2,2,3,3,4,5)}
\integer{denf=randitem(1,1,1,1,1,2,2,3,3,4,5)}
#else
\integer{dena=1}
\integer{denb=1}
\integer{denc=1}
\integer{dend=1}
\integer{dene=1}
\integer{denf=1}
#endif
\integer{numa=randint(1..10)*(randitem(1,-1))}
\rational{a=simplify(\numa/(\dena))}

\integer{numb=randint(1..10)*(randitem(1,-1))}
\rational{b=simplify(\numb/(\denb))}

\integer{numc=randint(1..10)^2*(randitem(1,-1))}
\rational{c=simplify(\numc/(\denc))}

\integer{numd=randint(1..10)*(randitem(1,-1))}
\rational{d=simplify(\numd/(\dend))}

\integer{nume=randint(1..10)*(randitem(1,-1))}
\rational{e=simplify(\nume/(\dene))}

\integer{numf=randint(1..10)*(randitem(1,-1))}
\rational{f=simplify(\numf/(\denf))}

\integer{g=randint(2..5)*(randitem(1,-1))}
\integer{h=randint(2..5)*(randitem(1,-1))}


%%%% choix de la question
\integer{sensineq=random(1..2)}
\integer{strictineq=random(0..1)}
\text{sgt=>}
\text{sge=\(\ge )}
\text{slt=<}
\text{sle=\(\le )}
%%%% la liste des objets que l'on peut cliquer pour résoudre l'exercice %%%%
\text{crocg=&#91;}
\text{crocd=&#93;}
\text{bracg=&#123;}
\text{bracd=&#125;}
\text{union=\(\cup)}
\text{inter=\(\cap)}
\text{infg=\(-\infty)}
\text{infd=\(+\infty)}
\text{empt=\(\emptyset)}
\text{ptvirg=&#59;}


\text{crochg=\strictineq=0?\crocd:\crocg}
\text{crochd=\strictineq=0?\crocg:\crocd}

%%%% préparation de la question
\text{symb=\slt,\sgt,\sle,\sge}
\integer{indsymb=\sensineq+2*\strictineq}


#if defined TARGET_ineqalgpara1
\rational{nv1=simplify(\b /(\a))}
\rational{nv2=simplify(-(\b) /(\a))}
\rational{nv3=simplify(\a /(\b))}
\rational{nv4=simplify(-(\a) /(\b))}
\rational{nv5=\a}
\rational{nv6=-(\a)}
\rational{nv7=\b}
\rational{nv8=-(\b)}
\text{v1=\(texmath(\nv1))}
\text{v2=\(texmath(\nv2))}
\text{v3=\(texmath(\nv3))}
\text{v4=\(texmath(\nv4))}
\text{v5=\(texmath(\nv5))}
\text{v6=\(texmath(\nv6))}
\text{v7=\(texmath(\nv7))}
\text{v8=\(texmath(\nv8))}
\text{v9=0}
\text{permut=\v1,\v2,\v3,\v4,\v5,\v6,\v7,\v8,\v9}
\text{permut=wims(listuniq \permut)}
\text{permut=shuffle(\permut)}

\rational{aa=(\a)^2}
\rational{bb=(\b)^2}
\text{equat= \aa*x^2 - \bb}
\text{equat=\(texmath(\equat))\symb[\indsymb] 0}
       \text{tsing1=\nv1<\nv2?\v1:\v2}
       \text{tsing2=\nv1<\nv2?\v2:\v1}
       \if{\sensineq=1}{
         \text{grep=\crochg,\tsing1,\ptvirg,\tsing2,\crochd}
        }{
         \text{grep=\crocd,\infg,\ptvirg,\tsing1,\crochd,\union,\crochg,\tsing2,\ptvirg,\infd,\crocg}
        }
#endif
#if defined TARGET_ineqalgpara2
\text{equat= (\a*x+\b)^2 }
\text{equat=\(texmath(\equat))\symb[\indsymb] \(texmath(\c))}
\if{\c>0}{
\rational{nv1=simplify((sqrt(\c)-\b) / (\a))}
\rational{nv2=simplify((-sqrt(\c)-\b) / (\a))}
\rational{nv3=simplify((sqrt(\c)-\a) / (\b))}
\rational{nv4=simplify((-sqrt(\c)-\a) / (\b))}
\rational{nv5=simplify(\b /(\a))}
\rational{nv6=simplify(-(\b) /(\a))}
\rational{nv7=simplify(\a /(\b))}
\rational{nv8=simplify(-(\a) /(\b))}
\text{v1=\(texmath(\nv1))}
\text{v2=\(texmath(\nv2))}
\text{v3=\(texmath(\nv3))}
\text{v4=\(texmath(\nv4))}
\text{v5=\(texmath(\nv5))}
\text{v6=\(texmath(\nv6))}
\text{v7=\(texmath(\nv7))}
\text{v8=\(texmath(\nv8))}
\text{v9=0}
\text{permut=\v1,\v2,\v3,\v4,\v5,\v6,\v7,\v8,\v9}
\text{permut=wims(listuniq \permut)}
\text{permut=shuffle(\permut)}
       \text{tsing1=\nv1<\nv2?\v1:\v2}
       \text{tsing2=\nv1<\nv2?\v2:\v1}
       \if{\sensineq=1}{
         \text{grep=\crochg,\tsing1,\ptvirg,\tsing2,\crochd}
        }{
         \text{grep=\crocd,\infg,\ptvirg,\tsing1,\crochd,\union,\crochg,\tsing2,\ptvirg,\infd,\crocg}
        }
 }{
\rational{nv1=simplify((sqrt(-\c)-\b) / (\a))}
\rational{nv2=simplify((-sqrt(-\c)-\b) / (\a))}
\rational{nv3=simplify((sqrt(-\c)-\a) / (\b))}
\rational{nv4=simplify((-sqrt(-\c)-\a) / (\b))}
\rational{nv5=simplify(\b /(\a))}
\rational{nv6=simplify(-(\b) /(\a))}
\rational{nv7=simplify(\a /(\b))}
\rational{nv8=simplify(-(\a) /(\b))}
\text{v1=\(texmath(\nv1))}
\text{v2=\(texmath(\nv2))}
\text{v3=\(texmath(\nv3))}
\text{v4=\(texmath(\nv4))}
\text{v5=\(texmath(\nv5))}
\text{v6=\(texmath(\nv6))}
\text{v7=\(texmath(\nv7))}
\text{v8=\(texmath(\nv8))}
\text{v9=0}
\text{permut=\v1,\v2,\v3,\v4,\v5,\v6,\v7,\v8,\v9}
\text{permut=wims(listuniq \permut)}
\text{permut=shuffle(\permut)}
  \text{grep=\sensineq=1?\empt:\crocd,\infg,\ptvirg,\infd,\crocg}
 }
#endif
#if (defined TARGET_ineqalgpara4  || defined TARGET_ineqalgpara3 )
\rational{nv1=simplify(-(\b) / (\a))}
\rational{nv3=simplify(-(\a) / (\b))}
\rational{nv4=simplify(\b /(\a))}
\rational{nv5=simplify(\a /(\b))}
#if defined TARGET_ineqalgpara3
\text{equat= \a*x^2+\b*x }
\rational{nv2=0}
\rational{nv6=simplify(-(\a) / (\b))}
\rational{nv7=simplify(\b /(\a))}
\rational{nv8=simplify(\a /(\b))}
\integer{c=1}
#endif
#if defined TARGET_ineqalgpara4
\text{equat= (\a*x+\b)*(\c*x+\d) }
\rational{nv2=simplify(-(\d) / (\c))}
\rational{nv6=simplify(-(\c) / (\d))}
\rational{nv7=simplify(\d /(\c))}
\rational{nv8=simplify(\c /(\d))}
#endif

\text{equat=\(texmath(\equat))\symb[\indsymb] 0}
\text{v1=\(texmath(\nv1))}
\text{v2=\(texmath(\nv2))}
\text{v3=\(texmath(\nv3))}
\text{v4=\(texmath(\nv4))}
\text{v5=\(texmath(\nv5))}
\text{v6=\(texmath(\nv6))}
\text{v7=\(texmath(\nv7))}
\text{v8=\(texmath(\nv8))}
\text{v9=\(texmath(\nv8))}
\text{permut=\v1,\v2,\v3,\v4,\v5,\v6,\v7,\v8,\v9}
\text{permut=wims(listuniq \permut)}
\text{permut=shuffle(\permut)}
       \text{tsing1=\nv1<\nv2?\v1:\v2}
       \text{tsing2=\nv1<\nv2?\v2:\v1}
\rational{ac=\a*(\c)}
\if{\nv1=\nv2}{
  \if{(\sensineq=1 and \ac>0) or (\sensineq=2 and \ac<0)}{
    \text{grep=\strictineq=0?\empt:\bracg,\tsing1,\bracd}
    }{
    \text{grep=\strictineq=0?\crocd,\infg,\ptvirg,\tsing1,\crocg,\union,\crocd,\tsing1,\ptvirg,\infd,\crocg:\crocd,\infg,\ptvirg,\infd,\crocg}
    }
  }{
  \if{(\sensineq=1 and \ac>0) or (\sensineq=2 and \ac<0)}{
    \text{grep=\crochg,\tsing1,\ptvirg,\tsing2,\crochd}
    }{
    \text{grep=\crocd,\infg,\ptvirg,\tsing1,\crochd,\union,\crochg,\tsing2,\ptvirg,\infd,\crocg}
    }
  }
#endif
#if defined TARGET_ineqalgpara5
\integer{k=random(1..3)}
\text{equat1= (\a*x+\b)*(\c*x+\d) }
\rational{nv1=simplify(-(\b) / (\a))}
\rational{nv3=simplify(-(\a) / (\b))}
\rational{nv4=simplify(\b /(\a))}
\rational{nv5=simplify(\a /(\b))}
\rational{sol1=-\b/(\a)}
\if{\k=1}{
  \text{equat2= (\a*x+\b)*(\e*x+\f) }
  \rational{nv2=simplify((\f - (\d))/(\c - (\e)))}
  \rational{ac=\a*(\c - (\e))}
  \rational{nv6=simplify(-(\f - (\d))/(\c - (\e)))}
  \rational{nv7=simplify(-(\d) /(\c))}
  \rational{nv8=simplify(-(\f) /(\e))}
 }
\if{\k=2}{
  \text{equat2= (\a*x+\b)^2 }
  \rational{nv2=simplify((\b - (\d))/(\c - (\a)))}
  \rational{ac=\a*(\c - (\a))}
  \rational{nv6=simplify(-(\b - (\d))/(\c - (\a)))}
  \rational{nv7=simplify(-(\c) /(\d))}
  \rational{nv8=simplify(-(\d) /(\c))}
 }
\if{\k=3}{
  \text{equat2= \g*(\a*x+\b) }
  \rational{ac=\a*(\c)}
  \rational{nv2=simplify((\g - (\d))/(\c))}
  \rational{nv6=simplify(-(\g - (\d))/(\c))}
  \rational{nv7=simplify(-(\c) /(\d))}
  \rational{nv8=simplify(-(\d) /(\c))}
 }
\text{v1=\(texmath(\nv1))}
\text{v2=\(texmath(\nv2))}
\text{v3=\(texmath(\nv3))}
\text{v4=\(texmath(\nv4))}
\text{v5=\(texmath(\nv5))}
\text{v6=\(texmath(\nv6))}
\text{v7=\(texmath(\nv7))}
\text{v8=\(texmath(\nv8))}
\text{v9=0}
\text{permut=\v1,\v2,\v3,\v4,\v5,\v6,\v7,\v8,\v9}
\text{permut=wims(listuniq \permut)}
\text{permut=shuffle(\permut)}
       \text{tsing1=\nv1<\nv2?\v1:\v2}
       \text{tsing2=\nv1<\nv2?\v2:\v1}

\text{equat=\(texmath(\equat1)) \symb[\indsymb] \(texmath(\equat2))}
\if{\nv1=\nv2}{
  \if{(\sensineq=1 and \ac>0) or (\sensineq=2 and \ac<0)}{
    \text{grep=\strictineq=0?\empt:\bracg,\tsing1,\bracd}
    }{
    \text{grep=\strictineq=0?\crocd,\infg,\ptvirg,\tsing1,\crocg,\union,\crocd,\tsing1,\ptvirg,\infd,\crocg:\crocd,\infg,\ptvirg,\infd,\crocg}
    }
  }{
  \if{(\sensineq=1 and \ac>0) or (\sensineq=2 and \ac<0)}{
    \text{grep=\crochg,\tsing1,\ptvirg,\tsing2,\crochd}
    }{
    \text{grep=\crocd,\infg,\ptvirg,\tsing1,\crochd,\union,\crochg,\tsing2,\ptvirg,\infd,\crocg}
    }
  }
#endif
#if defined TARGET_ineqalgpara6
\rational{ag=\a*\g}
\rational{bg=\b*\g}
\integer{k=random(1..3)}
\text{equat1= (\ag*x+\bg)*(\c*x+\d) }
\rational{nv1=simplify(-(\b) / (\a))}
\rational{nv3=simplify(-(\a) / (\b))}
\rational{nv4=simplify(\b /(\a))}
\rational{nv5=simplify(\a /(\b))}
\rational{sol1=-\b/(\a)}
\if{\k=1}{
  \text{equat2= (\a*x+\b)*(\e*x+\f) }
  \rational{sol2=(\f - (\d)*(\g))/(\c*(\g) - (\e))}
  \rational{nv2=simplify((\f - (\d)*(\g))/(\c*(\g) - (\e)))}
  \rational{ac=\a*(\c*(\g) - (\e))}
  \rational{nv6=simplify(-(\f - (\d)*(\g))/(\c*(\g) - (\e)))}
  \rational{nv7=simplify(-(\d) /(\c))}
  \rational{nv8=simplify(-(\f) /(\e))}
 }
\if{\k=2}{
  \text{equat2= (\a*x+\b)^2 }
  \rational{sol2=(\b - (\d)*(\g))/(\c*(\g) - (\a))}
  \rational{nv2=simplify((\b - (\d)*(\g))/(\c*(\g) - (\a)))}
  \rational{ac=\a*(\c*(\g) - (\a))}
  \rational{nv6=simplify(-(\b - (\d)*(\g))/(\c*(\g) - (\a)))}
  \rational{nv7=simplify(-(\c) /(\d))}
  \rational{nv8=simplify(-(\d) /(\c))}
 }
\if{\k=3}{
  \text{equat2= \e*(\a*x+\b) }
  \rational{sol2=(\e - (\d)*(\g))/((\c)*(\g))}
  \rational{ac=\a*(\c)*(\g)}
  \rational{nv2=simplify((\e - (\d)*(\g))/((\c)*(\g)))}
  \rational{nv6=simplify(-(\e - (\d)*(\g))/((\c)*(\g)))}
  \rational{nv7=simplify(-(\c) /(\d))}
  \rational{nv8=simplify(-(\d) /(\c))}
 }

\text{v1=\(texmath(\nv1))}
\text{v2=\(texmath(\nv2))}
\text{v3=\(texmath(\nv3))}
\text{v4=\(texmath(\nv4))}
\text{v5=\(texmath(\nv5))}
\text{v6=\(texmath(\nv6))}
\text{v7=\(texmath(\nv7))}
\text{v8=\(texmath(\nv8))}
\text{v9=0}
\text{permut=\v1,\v2,\v3,\v4,\v5,\v6,\v7,\v8,\v9}
\text{permut=wims(listuniq \permut)}
\text{permut=shuffle(\permut)}
       \text{tsing1=\nv1<\nv2?\v1:\v2}
       \text{tsing2=\nv1<\nv2?\v2:\v1}

\text{equat=\(texmath(\equat1)) \symb[\indsymb] \(texmath(\equat2))}
\if{\nv1=\nv2}{
  \if{(\sensineq=1 and \ac>0) or (\sensineq=2 and \ac<0)}{
    \text{grep=\strictineq=0?\empt:\bracg,\tsing1,\bracd}
    }{
    \text{grep=\strictineq=0?\crocd,\infg,\ptvirg,\tsing1,\crocg,\union,\crocd,\tsing1,\ptvirg,\infd,\crocg:\crocd,\infg,\ptvirg,\infd,\crocg}
    }
  }{
  \if{(\sensineq=1 and \ac>0) or (\sensineq=2 and \ac<0)}{
    \text{grep=\crochg,\tsing1,\ptvirg,\tsing2,\crochd}
    }{
    \text{grep=\crocd,\infg,\ptvirg,\tsing1,\crochd,\union,\crochg,\tsing2,\ptvirg,\infd,\crocg}
    }
  }
#endif

\text{clicList=
\crocg,\ptvirg,\crocd,\union,\inter,\infg,\infd,\empt,\bracg,\bracd,\permut}
%%%% taille des symboles et des champs à remplir par clic LxHxnb %%%%
\text{size=50x40x12}

\statement{
  Résoudre dans \(\ \RR) l'inéquation:
<div class="wimscenter">\equat.</div>
  <div class="wimscenter"><b>Brouillon</b></div>

<div class="wimscenter">\embed{reply2,10x30}</div>

  Indiquer l'ensemble solution de l'inéquation :
  <div class="wimscenter"> \(S=)\embed{reply1,\size}</div>
}
\answer{}{\grep;\clicList}{type=clickfill}
\answer{}{\rien}{type=draft}{option=default=empty}
