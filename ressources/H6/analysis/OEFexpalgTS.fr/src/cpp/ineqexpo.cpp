target=ineqexpo1 ineqexpo2 ineqexpo3 ineqexpo4 ineqexpo5
#define TITRE Inéquation avec exponentielle
#if defined TARGET_ineqexpo1
# define NUM 1
#endif
#if defined TARGET_ineqexpo2
# define NUM 2
#endif
#if defined TARGET_ineqexpo3
# define NUM 3
#endif
#if defined TARGET_ineqexpo4
# define NUM 4
#endif
#if defined TARGET_ineqexpo5
# define NUM 5
#endif
#include "author.inc"
\precision{100}
#include "lang_titles.inc"
#include "lang.inc"

\integer{chsymb1=randint(1,2)} inegalite < ou >
\integer{chsymb2=randint(0,1)} stricte ou pas
\integer{chsymb=2*\chsymb2+\chsymb1}
\text{lstsymb=<,\leq,>,\geq}
\text{symb=\lstsymb[\chsymb]}
\integer{mchsymb=2*(1-\chsymb2)+\chsymb1}
\text{msymb=\lstsymb[\mchsymb]}

\text{plus=<span style="color:red;font-size:15px">+</span>}
\text{moins=<span style="color:red;font-size:15px">-</span>}
text{vesp=&nbsp;}
\text{v0=0}
\text{infg=\(-\infty)}
\text{infd=\(+\infty)}

\text{permut=wims(makelist \(x) for x=-15 to 15)}
\text{permut=\permut,\infg,\infd}
text{permut=wims(listuniq \permut)}

\text{crocg=&#91;}
\text{crocd=&#93;}
\text{bracg=&#123;}
\text{bracd=&#125;}
\text{union=\(\cup)}
\text{inter=\(\cap)}
\text{infg=\(-\infty)}
\text{infd=\(+\infty)}
\text{empt=\(\,\emptyset\)}
\text{ptvirg=&#59;}
\text{size=40x40x11}
\text{crochg=\chsymb1=1?\crocd:\crocg}
\text{crochd=\chsymb1=1?\crocg:\crocd}

#if defined TARGET_ineqexpo1
\integer{a=randint(1..5)*randint(1,-1)}
\integer{bp=randint(1..5)*abs(\a)}
\integer{d=randint(2..10)*randint(1,-1)*\a}

\text{exp1 = texmath(pari(\a*x+(\bp)) )}
\text{exp2 = texmath(pari(\a*x-(\bp)) )}
\text{exp3 = texmath(pari(\a*x-(\bp)+1))}
\text{exp4 = texmath(pari(\a*x-(\bp)-1))}
\text{data=exp(\a x) \symb e^{\d},pari(\d/\a)
e^{\exp1}\symb e^{\d},pari((\d-(\bp))/(\a))
e^{\exp2} \symb e^{\d},pari((\d+(\bp))/(\a))
e^{\exp1} \symb 0,vide
e^{\exp2} \symb 0,vide
e^{\exp1}\symb 1,pari(-(\bp)/\a)
e^{\exp3}\symb e,pari(\bp/\a)
e^{\exp1} \symb -1,vide
e^{\exp2}\symb -1,vide
e^{\exp1} \symb -e,vide
e^{\exp2} \symb -e,vide
e^{\exp1}\symb \frac{1}{e^{\d}},pari((-(\d)-(\bp))/\a)
e^{\exp4} \symb \frac{1}{e},pari((-1+(\bp))/(\a))
}
\integer{nb=rows(\data)}
\integer{i=randint(1..\nb)}
\text{cedata=row(\i,\data)}
\text{equat=\cedata[1]}
\text{rep=\cedata[2]}
\if{\rep issametext vide}{
 \text{grep=\chsymb2=0?\empt:\crocd,\infg,\ptvirg,\infd,\crocg}
 }{
 \integer{borne=\rep}
 \text{vborne=\(\borne)}
 \text{grep=(\a>0 and \chsymb2=1) or (\a<0 and \chsymb2=0)?\crochg,\vborne,\ptvirg,\infd,\crocg:\crocd,\infg,\ptvirg,\vborne,\crochd}
 }
#endif
#if defined TARGET_ineqexpo2
\integer{sing1=randint(0..8)*randint(1,-1)}
\integer{sing2=randint(0..8)*randint(1,-1)}
\integer{s=\sing1+(\sing2)}
\integer{p=\sing1*(\sing2)}
\integer{d=randint(1..5)}
\integer{bp=(\d+(\s)^2)/4+1}
\integer{bpp=-(\s)^2/4-\d}
\text{t1=pari(\s*x-(\p))}
\text{t2=pari(x^2+(\p))}
\text{t3=pari(x^2-(\s*x))}
\text{tb1=pari(\s*x-(\bp))}
\text{tb2=pari(x^2+(\bp))}
\text{t20=pari(x^2-(\s)*x+(\p))}
\text{t30=pari(x^2-(\s)*x+(\p)+1)}
\integer{p1=randint(2..4)*randint(1,-1)}
\integer{p2=\p-(\p1)}
\text{t1p=pari(\s*x-(\p2))}
\text{t2p=pari(x^2+(\p1))}
\text{tm1p=pari(-(\t1p))}
\text{tm2p=pari(-(\t2p))}
\text{tm1=pari(-(\t1))}
\text{tm2=pari(-(\t2))}
\text{tm3=pari(-(\t3))}
\text{tmb1=pari(-(\tb1))}
\text{tmb2=pari(-(\tb2))}
\text{tm20=pari(-(\t20))}
\text{tm30=pari(-(\t30))}
\text{sx=pari(\s*x)}

\text{data=e^(x^2), \symb ,e^(\t1),\sing1,\sing2
e^(\t2), \symb, e^(\sx),\sing1,\sing2
e^(\t3), \symb, e^(-\p),\sing1,\sing2
e^(x^2), \symb, e^(\tb1),vide
e^(\tb2), \symb, e^(\sx),vide
e^(\t3), \symb, e^(-\bp),vide
e^(\t20), \symb, 1,\sing1,\sing2
e^(\t30), \symb, e,\sing1,\sing2
e^(-x^2), \symb, e^(\tm1),\sing1,\sing2
e^(\tm2), \symb, 1/e^(\sx),\sing1,\sing2
e^(\tm3), \symb, 1/e^\p,\sing1,\sing2
e^(-x^2), \symb, e^(\tmb1),vide
e^(\tmb2), \symb, 1/e^(\sx),vide
e^(\tm3), \symb, 1/e^\bpp,vide
e^(\tm20), \symb, 1,\sing1,\sing2
e^(\tm30), \symb, 1/e,\sing1,\sing2}
\integer{nb=rows(\data)}
\integer{i=randint(1..\nb)}
\text{cedata=row(\i,\data)}
\text{equat=texmath(\cedata[1]) \cedata[2] texmath(\cedata[3]) }
\text{rep=\cedata[4]}
\if{\rep issametext vide}{
  \text{grep=(\chsymb2=0 and \i<=\nb/2) or (\chsymb2=1 and \i>\nb/2)?\empt:\crocd,\infg,\ptvirg,\infd,\crocg}
}{
  \integer{borne1=\rep}
  \integer{borne2=\cedata[5]}
  \text{vborneg=\borne1<\borne2?\(\borne1):\(\borne2)}
  \text{vborned=\borne1<\borne2?\(\borne2):\(\borne1)}
  \if{\borne1=\borne2}{
    \if{\chsymb1=1}{
      \text{grep=(\i<=\nb/2 and \chsymb2=0) or (\i>\nb/2 and \chsymb2=1)?\empt:\crocd,\infg,\ptvirg,\vborneg,\crocg,\union,\crocd,\vborned,\ptvirg,\infd,\crocg:
      }
    }{
      \text{grep=(\i<=\nb/2 and \chsymb2=0) or (\i>\nb/2 and \chsymb2=1)?
        \crochg,\vborneg,\ptvirg,\vborned,\crochd:
        \crocd,\infg,\ptvirg,\infd,\crocg}
    }
  }{
    \text{grep=(\i<=\nb/2 and \chsymb2=1) or (\i>\nb/2 and \chsymb2=0)?
  \crocd,\infg,\ptvirg,\vborneg,\crochd,\union,\crochg,\vborned,\ptvirg,\infd,\crocg:
  \crochg,\vborneg,\ptvirg,\vborned,\crochd}
  }
}
#endif
#if (defined TARGET_ineqexpo4 || defined TARGET_ineqexpo5 )
\integer{sing1=randint(2..8)*randint(1,-1)}
\integer{sing2=randint(2..8)*randint(1,-1)}
\integer{sing2=\sing2=\sing1?2*\sing1}
\integer{sing2=\sing2=-\sing1?2*\sing2}

\integer{s=\sing1+\sing2}
\integer{p=\sing1*\sing2}
\integer{d=randint(1..5)+ln(exp(2*\sing1)+exp(2*\sing2)+2*exp(\sing1+\sing2))}
\integer{bp=\d+\s}
\text{t1=texmath(pari(x+(\sing1)))}
\text{t2=texmath(pari(x+(\sing2)))}

\integer{sing1p=\sing1+1}
\integer{sing1m=\sing1-1}
# if defined TARGET_ineqexpo4
\text{data=e^{2 x}-(e^{\sing1}+e^{\sing2})e^x+e^{\s} \symb 0,\sing1,\sing2
e^{2 x}-e^{\t1}+e^{\s} \symb e^{\t2},\sing1,\sing2
e^{2 x}-e^{\t1} \symb e^{\t2}-e^{\s},\sing1,\sing2
e^{2 x}-(e^{\sing1}+e^{\sing2})e^x+e^{\bp} \symb 0,vide
e^{2 x}-e^{\t1}+e^{\bp}\symb e^{\t2},vide
e^{2 x}-e^{\t1} \symb e^{\t2}-e^{\bp},vide
e^{2 x}-(e^{\sing1}+1)e^x+e^{\sing1} \symb 0,\sing1,0
e^{2 x}-e^{\t1}+e^{\sing1} \symb e^{x},\sing1,0
e^{2 x}-e^{\t1} \symb e^{x}-e^{\sing1},\sing1,0
e^{2 x}-(e^{\sing1}+e)e^x+e^{\sing1p} \symb 0,\sing1,1
e^{2 x}-e^{\t1}+e^{\sing1p} \symb e^{x+1},\sing1,1
e^{2 x}-e^{\t1} \symb e^{x+1}-e^{\sing1p},\sing1,1
e^{2 x}-(e^{\sing1}+\frac{1}{e})e^x+e^{\sing1m} \symb 0,\sing1,-1
e^{2 x}-e^{\t1}+e^{\sing1m} \symb e^{x-1},\sing1,-1
e^{2 x}-e^{\t1} \symb e^{x-1}-e^{\sing1m},\sing1,-1
}
# else
\text{t3=texmath(pari(2*x-(\s)))}
\text{t4=texmath(pari(-x+(\s)))}
\text{t5=texmath(pari(x-(\sing1)))}
\text{data=\frac{e^{\t1}-e^{\s}}{-e^{\sing2}+e^x} \symb e^{x},\sing1
\frac{e^{\sing1}}{1-e^{\t5}+e^{\t3}} \symb e^{\t4},\sing1,\sing2
\frac{e^{\sing1}+e^{\sing2}}{1+e^{\t3}} \symb e^{\t4},\sing1,\sing2
\frac{e^{\t1}-e^{\bp}}{-e^{\sing2}+e^x} \symb e^{x},vide
}
# endif
\integer{nb=rows(\data)}
integer{i=1}
\integer{i=randint(1..\nb)}
\text{cedata=row(\i,\data)}
\text{equat=\cedata[1]}
\text{rep=\cedata[2]}
# if defined TARGET_ineqexpo4
\if{\rep issametext vide}{
 \text{grep=\chsymb2=0?\empt:\crocd,\infg,\ptvirg,\infd,\crocg}
 }{
 \integer{borne1=\rep}
 \integer{borne2=\cedata[3]}
 \text{vborneg=\borne1<\borne2?\(\borne1):\(\borne2)}
 \text{vborned=\borne1<\borne2?\(\borne2):\(\borne1)}

 \if{\borne1=\borne2 and \chsymb1=2}{
  \text{grep=\chsymb2=1?\crocd,\infg,\ptvirg,\infd,\crocg:\empt}
  }{
  \text{grep=\chsymb2=1?\crocd,\infg,\ptvirg,\vborneg,\crochd,\union,\crochg,\vborned,\ptvirg,\infd,\crocg:\crochg,\vborneg,\ptvirg,\vborned,\crochd}
  }
 }
# else
 \integer{borne1=\sing1}
 \integer{borne2=\sing2}
 \text{vborneg=\borne1<\borne2?\(\borne1):\(\borne2)}
 \text{vborned=\borne1<\borne2?\(\borne2):\(\borne1)}
 \text{vi=\borne1<\borne2?\vborned:\vborneg}
\if{\rep issametext vide}{
  \text{grep=\chsymb2=1?\empt:\crocd,\infg,\ptvirg,\vi,\crocg,\union,\crocd,\vi,\ptvirg,\infd,\crocg}
}{
  \if{items(\cedata)>2}{
    \text{grep=\chsymb2=0?\crocd,\infg,\ptvirg,\vborneg,\crochd,\union,\crochg,\vborned,\ptvirg,\infd,\crocg:\crochg,\vborneg,\ptvirg,\vborned,\crochd}
  }{
    \if{\borne1<\borne2}{
      \text{grep=\chsymb2=0?\crocd,\infg,\ptvirg,\vborneg,\crochd,\union,\crocd,\vborned,\ptvirg,\infd,\crocg:\crochg,\vborneg,\ptvirg,\vborned,\crocg}
    }{
      \text{grep=\chsymb2=0?\crocd,\infg,\ptvirg,\vborneg,\crocg,\union,\crochg,\vborned,\ptvirg,\infd,\crocg:\crocd,\vborneg,\ptvirg,\vborned,\crochd}
    }
  }
}
# endif
#endif
#if defined TARGET_ineqexpo3
\integer{a=randint(1..5)*randint(1,-1)}
\integer{b=randint(-5..5)}
\integer{c=randint(1..5)*randint(1,-1)}
\integer{d=randint(-5..5)}
\integer{k=randint(1..5)*randint(1,-1)}
\integer{ak=\a*\k}
\text{u=texmath(pari(\a*x+(\b)))}
\text{v=texmath(pari(\c*x+(\d)))}
\rational{sing1=simplify(-(\b)/(\a))}
\rational{sing2=simplify(-(\d)/(\c))}
\text{tk=\k=1? :\k}
\text{tk=\k=-1?-}

\text{data=\tk e^{\v}\times (\u) \symb 0,\sing1
\frac{\u}{\tk e^{\v}} \symb 0,\sing1
\frac{\tk e^{\v}}{\u} \symb 0,\sing1
}
\integer{nb=rows(\data)}
\integer{i=randint(1..\nb)}
\text{crochg=\chsymb1=1 or \i=3 ?\crocd:\crocg}
\text{crochd=\chsymb1=1 or \i=3 ?\crocg:\crocd}
\text{cedata=row(\i,\data)}
\text{equat=\cedata[1]}
\text{rep=\cedata[2]}
\if{\rep issametext vide}{
 \text{grep=\chsymb2=0?\empt:\crocd,\infg,\ptvirg,\infd,\crocg}
 }{
 \text{permut=\permut,\(\sing1),\(\sing2)}
 \text{vborne=\(\sing1)}
 \text{grep=(\ak>0 and \chsymb2=1) or (\ak<0 and \chsymb2=0)?\crochg,\vborne,\ptvirg,\infd,\crocg:\crocd,\infg,\ptvirg,\vborne,\crochd}
 }
#endif
\text{clicList=\permut,\crocg,\crocd,\union,\inter,\ptvirg,\empt}
text{seed=slib(oef/env seed)}
\statement{<p>
  \name_statement \(\equat\).
</p>
<div class="wimscenter"> \(S=\) \embed{reply1,\size} </div>
}
\answer{\name_answer}{\grep;\clicList}{type=clickfill}
