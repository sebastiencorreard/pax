target=sumprod1 sumprod2 sumprod3 sumprod4 sumprod5
#include "author.inc"
\precision{100}
#if defined TARGET_sumprod1
# define NUM 1
#endif
#if defined TARGET_sumprod2
# define NUM 2
#endif
#if defined TARGET_sumprod3
# define NUM 3
#endif
#if defined TARGET_sumprod4
# define NUM 4
#endif
#if defined TARGET_sumprod5
# define NUM 5
#endif
#include "lang_titles.inc"
#include "lang.inc"
#if (defined TARGET_sumprod1 || defined TARGET_sumprod2 || defined TARGET_sumprod4 )
\integer{a=randint(2..5)*randint(1,-1)}
\integer{b=randint(12..15)*randint(1,-1)}
\integer{c=randint(22..25)*randint(1,-1)}
\integer{amb=\a-\b}
\integer{apb=\a+\b}
\integer{bma=\b-\a}
\integer{am2b=\a-2*\b}
\integer{ap2b=\a+2*\b}
\integer{bp2a=2*\a+\b}
\integer{bm2a=\b-2*\a}
\integer{damb=2*\a-\b}
\integer{dbma=2*\b-\a}

# if defined TARGET_sumprod1
\text{data=exp(\a x)\times exp(\b x),e^{\apb x},\frac{exp(\a x)}{ exp(\b x)},e^{\amb x},
\frac{exp(\b x)}{ exp(\a x)},e^{\bma x},\frac{exp(\a x)}{ (exp(\b x))^2},e^{\am2b x},
exp(\a x)\times (exp(\b x))^2,e^{\ap2b x},(exp(\a x))^2\times exp(\b x),e^{\bp2a x},\frac{exp(\b x)}{ (exp(\a x))^2},e^{\bm2a x},
\frac{(exp(\a x))^2}{ exp(\b x)},e^{\damb x},
\frac{(exp(\b x))^2}{ exp(\a x)},e^{\dbma x},
exp(\a x)+exp(\b x),e^{\a x}+e^{\b x},
exp(\a x)-exp(\b x),e^{\a x}-e^{\b x}
}
# endif
# if defined TARGET_sumprod2
\text{data=e^{\a x}\times e^{\b x},exp(\apb x),\frac{e^{\a x}}{ e^{\b x}},exp(\amb x),
\frac{e^{\b x}}{ e^{\a x}},exp(\bma x),\frac{e^{\a x}}{ (e^{\b x})^2},exp(\am2b x),
e^{\a x}\times (e^{\b x})^2,exp(\ap2b x),(e^{\a x})^2\times e^{\b x},exp(\bp2a x),\frac{e^{\b x}}{ (e^{\a x})^2},exp(\bm2a x),
\frac{(e^{\a x})^2}{ e^{\b x}},exp(\damb x),
\frac{(e^{\b x})^2}{ e^{\a x}},exp(\dbma x),
e^{\a x}+e^{\b x},exp(\a x)+exp(\b x),
e^{\a x}-e^{\b x},exp(\a x)-exp(\b x)
}
# endif
# if defined TARGET_sumprod4
%% ne pas mettre d'espace dans la bonne reponse (mathmlinput)
\text{data=exp(\a x)\times exp(\b x),\apb*x,\frac{exp(\a x)}{ exp(\b x)},\amb*x,
\frac{exp(\b x)}{ exp(\a x)},\bma*x,\frac{exp(\a x)}{ (exp(\b x))^2},\am2b*x,
exp(\a x)\times (exp(\b x))^2,\ap2b*x,(exp(\a x))^2\times exp(\b x),\bp2a*x,\frac{exp(\b x)}{(exp(\a x))^2},\bm2a*x,
\frac{(exp(\a x))^2}{ exp(\b x)},\damb*x,
\frac{(exp(\b x))^2}{ exp(\a x)},\dbma*x
}
# endif
\integer{nb=items(\data)/2}
\text{lstexp=}
\text{lste=}
\text{lstr=}
\for{i=1 to \nb}{
  \text{f=\(\data[2*\i-1])}
  \text{g=\(\data[2*\i])}
  \text{lstexp=wims(append item \f to \lstexp)}
  \text{lste=wims(append item \g to \lste)}
  \text{lstr=wims(append item \data[2*\i] to \lstr)}
 }
\text{size=50x300x200}
\text{ind=shuffle(\nb)}
text{ind=7,8,9,10,11}
\text{lstexpf=\lstexp[\ind[1]],\lstexp[\ind[2]],\lstexp[\ind[3]],\lstexp[\ind[4]],\lstexp[\ind[5]]}
\text{lstef=\lste[\ind[1],\ind[2],\ind[3],\ind[4],\ind[5]]}
# if defined TARGET_sumprod4
\integer{j=randint(1..items(\lstexp))}
\statement{
\name_statement[1]:
<p>\name_statement[2] \(x\),</p>
<div class="wimscenter">
<label for="reply1">\lstexp[\j]</label>=\special{mathmlinput [e^{reply1} ], 4
reply 1}
</div>
}
\answer{\name_answer}{\lstr[\j]}{type=algexp}
#else
\statement{<p>\name_statement:</p>
<div class="wimscenter">\embed{reply1,\size}</div>
}
\answer{}{\lstexpf;\lstef}{type=correspond}{option=split}
#endif
#endif

#if defined TARGET_sumprod3
\text{data=\frac{e^x+e^{-x}}{e^x-e^{-x}},\frac{e^{2x}+1}{e^{2x}-1},\frac{1+e^{-2x}}{1-e^{-2x}},\frac{e^{2x}(1+e^{-2x})}{e^{2x}-1}
\frac{e^{-x}+e^{x}}{e^{-x}-e^{x}},\frac{e^{-2x}+1}{e^{-2x}-1},\frac{1+e^{2x}}{1-e^{2x}},\frac{e^{2x}(e^{-2x}+1)}{1-e^{2x}}
\frac{e^{2x}}{1-e^{2x}},\frac{1}{e^{-2x}-1},\frac{e^x}{e^{-x}-e^{x}},\frac{1}{e^{-2x}(1-e^{2x})}
\frac{e^{-2x}}{1-e^{-2x}},\frac{1}{e^{2x}-1},\frac{e^{-x}}{e^{x}-e^{-x}},\frac{1}{e^{2x}(1-e^{-2x})}
}
\text{baddata=\frac{e^{-x}+e^{x}}{e^{-x}-e^{x}},\frac{e^{-2x}+1}{e^{-2x}-1},\frac{1+e^{2x}}{1-e^{2x}},\frac{e^{x}+1}{e^{x}-1}
\frac{e^x+e^{-x}}{e^x-e^{-x}},\frac{e^{2x}+1}{e^{2x}-1},\frac{1+e^{-2x}}{1-e^{-2x}},\frac{e^{-x}+1}{e^{-x}-1}
\frac{e^{-2x}}{1-e^{-2x}},\frac{1}{e^{2x}-1},\frac{e^{-x}}{e^{x}-e^{-x}},\frac{1}{1-e^{x}}
\frac{e^{2x}}{1-e^{2x}},\frac{1}{e^{-2x}-1},\frac{e^x}{e^{-x}-e^{x}},\frac{1}{e^{x}-1}
}

\integer{nb=rows(\data)}
\integer{i=randint(1.. \nb)}
\text{cedata=row(\i,\data)}
\text{cebad=row(\i,\baddata)}
\integer{j=randint(1..items(\cedata))}
\text{quest=\cedata[\j]}
\integer{nbbrep=random(2,3)}
\text{rep=\nbbrep==2?1,2:1,2,3}
\text{cedata=wims(replace item number \j by in \cedata)}
\text{cedata=wims(nonempty items \cedata)}

\if{\nbbrep==3}{\text{lstrep=\(\cedata[1]),\(\cedata[2]),\(\cedata[3]),\(\cebad[1]),\(\cebad[2]),\(\cebad[3])}}
{\text{cedata=wims(shuffle(\cedata))}
\text{lstrep=\(\cedata[1]),\(\cedata[2]),\(\cebad[1]),\(\cebad[2]),\(\cebad[3]),\(\cebad[4])}
}

\statement{<p>\name_statement:</p>
<div class="wimscenter">\(\quest)</div>
<div class="wimscenter">\embed{reply1}</div>
}
\answer{}{\rep;\lstrep}{type=checkbox}{option=shuffle split}
#endif
#if defined TARGET_sumprod5
\text{data=e^x+e^(-x),e^x-e^(-x),e^(2*x)+1,e^(2*x)-1,1+e^(-2*x),1-e^(-2*x)
e^(-x)+e^x,e^(-x)-e^x,e^(-2*x)+1,e^(-2*x)-1,1+e^(2*x),1-e^(2*x)
e^(2*x),1-e^(2*x),1,e^(-2*x)-1,e^x,e^(-x)-e^x
e^(-2*x),1-e^(-2*x),1,e^(2*x)-1,e^(-x),e^x-e^(-x)
}
\integer{nb=rows(\data)}
\integer{i=randint(1..\nb)}
\text{cedata=row(\i,\data)}
\integer{nb=items(\cedata)}
\text{ind=shuffle(\nb/2)}
\integer{i=\ind[1]}
\integer{j=\ind[2]}
\text{gnum=texmath(\cedata[2*\j-1])}
\text{gden=texmath(\cedata[2*\j])}
\text{quest=\frac{\gnum}{\gden}}
\text{fnum=\cedata[2*\i-1]}
\text{fden=\cedata[2*\i]}
\text{fnumtex=texmath(\fnum)}
\text{fdentex=texmath(\fden)}
\integer{cas=randint(1,2)}
\text{mstep=\cas=1?r1:r2}
\steps{\mstep}

\statement{<p>\name_statement:</p>
<div class="wimscenter">
\if{\cas=1}{
\(\quest= )\special{mathmlinput [\frac{\fnumtex}{reply1}],12,noanswer
reply 1}
}{
\(\quest= )\special{mathmlinput [\frac{reply2}{\fdentex}],12,noanswer
reply 2}
}
</div>
}

\answer{}{\fden}{type=algexp}
\answer{}{\fnum}{type=algexp}
#endif
