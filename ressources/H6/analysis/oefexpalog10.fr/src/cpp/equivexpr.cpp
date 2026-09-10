target=expacorresp expacases expasimplquot logcorresp
\author{Cyrille, Douriez}##adaptation d'un module de Régine Mangeard##
\email{cyrille.douriez@ac-amiens.fr}
\format{html}
\language{fr}
\range{-5..5}
\computeanswer{no}
\precision{100}

\real{base=randint(21..95)/10}

#define TITLE Simplification d'écriture
#if defined TARGET_expacorresp
\title{TITLE avec une exponentielle 1}
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

\text{data=\base^{\a x}\times \base^{\b x},\base^{\apb x},\frac{\base^{\a x}}{ \base^{\b x}},\base^{\amb x},
\frac{\base^{\b x}}{ \base^{\a x}},\base^{\bma x},\frac{\base^{\a x}}{ (\base^{\b x})^2},\base^{\am2b x},
\base^{\a x}\times (\base^{\b x})^2,\base^{\ap2b x},(\base^{\a x})^2\times \base^{\b x},\base^{\bp2a x},\frac{\base^{\b x}}{ (\base^{\a x})^2},\base^{\bm2a x},
\frac{(\base^{\a x})^2}{ \base^{\b x}},\base^{\damb x},
\frac{(\base^{\b x})^2}{ \base^{\a x}},\base^{\dbma x}
}

\integer{nb=items(\data)/2}
\text{lstexp=}
\text{lste=}
\text{lstr=}
\for{i=1 to \nb}
 {
 \text{f=\(\data[2*\i-1])}
 \text{g=\(\data[2*\i])}
 \text{lstexp=wims(append item \f to \lstexp)}
 \text{lste=wims(append item \g to \lste)}
 \text{lstr=wims(append item \data[2*\i] to \lstr)}
 }
\text{size=60x300x200}
\text{ind=shuffle(\nb)}
\text{lstexpf=\lstexp[\ind[1]],\lstexp[\ind[2]],\lstexp[\ind[3]],\lstexp[\ind[4]],\lstexp[\ind[5]]}
\text{lstef=\lste[\ind[1],\ind[2],\ind[3],\ind[4],\ind[5]]}

\statement{<p>
Mettre en correspondance les expressions égales :
</p>
<div class="wimscenter">\embed{repl1,\size}</div>
}
\answer{}{\lstexpf;\lstef}{type=correspond}{option=split}
\solution{On utilise les propriétés des fonctions exponentielles : \(\base^{a}\times \base^{b}=\base^{a+b}); \(\frac{\base^{a}}{\base^{b}}=\base^{a-b})
et \(\left (\base^{a} \right )^n=\base^{n \times a}).}
#endif

#if defined TARGET_expacases
\title{TITLE avec une exponentielle 2}

\text{data=\frac{\base^x+\base^{-x}}{\base^x-\base^{-x}},\frac{\base^{2x}+1}{\base^{2x}-1},\frac{1+\base^{-2x}}{1-\base^{-2x}},\frac{\base^{2x}(1+\base^{-2x})}{\base^{2x}-1}
\frac{\base^{-x}+\base^{x}}{\base^{-x}-\base^{x}},\frac{\base^{-2x}+1}{\base^{-2x}-1},\frac{1+\base^{2x}}{1-\base^{2x}},\frac{\base^{2x}(\base^{-2x}+1)}{1-\base^{2x}}
\frac{\base^{2x}}{1-\base^{2x}},\frac{1}{\base^{-2x}-1},\frac{\base^x}{\base^{-x}-\base^{x}},\frac{1}{\base^{-2x}(1-\base^{2x})}
\frac{\base^{-2x}}{1-\base^{-2x}},\frac{1}{\base^{2x}-1},\frac{\base^{-x}}{\base^{x}-\base^{-x}},\frac{1}{\base^{2x}(1-\base^{-2x})}
}
\text{baddata=\frac{\base^{-x}+\base^{x}}{\base^{-x}-\base^{x}},\frac{\base^{-2x}+1}{\base^{-2x}-1},\frac{1+\base^{2x}}{1-\base^{2x}},\frac{\base^{x}+1}{\base^{x}-1}
\frac{\base^x+\base^{-x}}{\base^x-\base^{-x}},\frac{\base^{2x}+1}{\base^{2x}-1},\frac{1+\base^{-2x}}{1-\base^{-2x}},\frac{\base^{-x}+1}{\base^{-x}-1}
\frac{\base^{-2x}}{1-\base^{-2x}},\frac{1}{\base^{2x}-1},\frac{\base^{-x}}{\base^{x}-\base^{-x}},\frac{1}{1-\base^{x}}
\frac{\base^{2x}}{1-\base^{2x}},\frac{1}{\base^{-2x}-1},\frac{\base^x}{\base^{-x}-\base^{x}},\frac{1}{\base^{x}-1}
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

\statement{<p>
Parmi les expressions suivantes, cochez celles qui sont, pour tout réel \(x) non nul, égales à :
</p>
<div class="wimscenter"> \(\quest) </div>
<div class="wimscenter">\embed{reply1}</div>
}

\answer{}{\rep;\lstrep}{type=checkbox}{option=shuffle split}
\solution{On utilise des factorisations et on exploite les propriétés des fonctions exponentielles : \(\base^{a}\times \base^{b}=\base^{a+b}); \(\frac{\base^{a}}{\base^{b}}=\base^{a-b})
et \(\left (\base^{a} \right )^n=\base^{n \times a}).}
#endif

#if defined TARGET_expasimplquot
\title{TITLE avec une exponentielle 3}

\text{data=\base^x+\base^(-x),\base^x-\base^(-x),\base^(2*x)+1,\base^(2*x)-1,1+\base^(-2*x),1-\base^(-2*x)
\base^(-x)+\base^x,\base^(-x)-\base^x,\base^(-2*x)+1,\base^(-2*x)-1,1+\base^(2*x),1-\base^(2*x)
\base^(2*x),1-\base^(2*x),1,\base^(-2*x)-1,\base^x,\base^(-x)-\base^x
\base^(-2*x),1-\base^(-2*x),1,\base^(2*x)-1,\base^(-x),\base^x-\base^(-x)
}

\integer{nb=rows(\data)}
\integer{i=randint(1..\nb)}
\text{cedata=row(\i,\data)}
\integer{nb=items(\cedata)}
\text{ind=shuffle( \nb/2)}
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

\statement{<p>
Compléter:
</p>
<div class="wimscenter">
\if{\cas=1}
{
\(\quest= )\special{mathmlinput [\frac{\fnumtex}{reply1}],12,noanswer
reply 1}
}
{
\(\quest= )\special{mathmlinput [\frac{reply2}{\fdentex}],12,noanswer
reply 2}
}
</div>
}

\answer{}{\fden}{type=algexp}
\answer{}{\fnum}{type=algexp}
\solution{On utilise des factorisations et on exploite les propriétés des fonctions exponentielles : \(\base^{a}\times \base^{b}=\base^{a+b}); \(\frac{1}{\base^{b}}=\base^{-b}); \(\frac{\base^{a}}{\base^{b}}=\base^{a-b})
et \(\left (\base^{a} \right )^n=\base^{n \times a}).}
#endif

#if defined TARGET_logcorresp
\title{Associer des logarithmes}

\integer{a=randint(2..9)}
\integer{b=randint(11..15)}
\integer{n=randint(2..15)}
\integer{p=randint(3..15)}

\text{data=log(\a\times \b),log(\a)+log(\b),
log\left(\frac{1}{\b}\right),-log(\b),
log\left(\frac{\a}{\b}\right),log(\a)-log(\b),
log(\a^\n),\n\times log(\a),
log(\a^\n\times\b^\p),\n\times log(\a)+\p\times log(\b),
log(10^\p),\p,
log(10^{-\n}),-\n,
log(\a \times 10^{\n}),\n+log(\a),
log\left(\frac{\a^\n}{\b^\p}\right),\n\times log(\a)-\p\times log(\b)
}
\integer{nb=items(\data)/2}
\text{lstexp=}
\text{lste=}
\text{lstr=}
\for{i=1 to \nb}
 {
 \text{f=\(\data[2*\i-1])}
 \text{g=\(\data[2*\i])}
 \text{lstexp=wims(append item \f to \lstexp)}
 \text{lste=wims(append item \g to \lste)}
 \text{lstr=wims(append item \data[2*\i] to \lstr)}
 }
\text{size=60x300x300}
\text{ind=shuffle(\nb)}
\text{lstexpf=\lstexp[\ind[1]],\lstexp[\ind[2]],\lstexp[\ind[3]],\lstexp[\ind[4]],\lstexp[\ind[5]]}
\text{lstef=\lste[\ind[1],\ind[2],\ind[3],\ind[4],\ind[5]]}
\statement{<p>
Mettre en correspondance les différentes écritures d'une même expression:
</p>
<div class="wimscenter">\embed{repl1,\size}</div>
}
\answer{}{\lstexpf;\lstef}{type=correspond}{option=split}
\solution{On utilise les propriétés du logarithme : \(log(\a \times \b)=log(\a)+log(\b));\(log\left (\frac{1}{\b} \right )=-log(\b));
\(log \left (\frac{\a}{\b} \right )=log(\a)-log(\b)); \(log(\a^\n)=\n \;log(\a)).}
#endif
