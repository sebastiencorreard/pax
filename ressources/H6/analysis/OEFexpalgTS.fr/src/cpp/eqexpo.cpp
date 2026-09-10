target=eqexpo1 eqexpo2 eqexpo3 eqexpo4 eqexpo5 eqexpo6
#include "author.inc"
\precision{100}
#if defined TARGET_eqexpo1
# define NUM 1
#endif
#if defined TARGET_eqexpo2
# define NUM 2
#endif
#if defined TARGET_eqexpo3
# define NUM 3
#endif
#if defined TARGET_eqexpo4
# define NUM 4
#endif
#if defined TARGET_eqexpo5
# define NUM 5
#endif
#if defined TARGET_eqexpo6
# define NUM 6
#endif
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_eqexpo1
\integer{a=randint(1..5)*randint(1,-1)}
\integer{bp=randint(1..5)}
\integer{b=randint(0..5)*randint(1,-1)}
\integer{c=randint(0..5)*randint(1,-1)}
\integer{d=randint(2..10)*randint(1,-1)}

\text{data=e^{\a x}=e^{\d},pari(\d/\a)
e^{\a x+\bp}=e^{\d},pari((\d-(\bp))/\a)
e^{\a x-\bp}=e^{\d},pari((\d+(\bp))/\a)
e^{\a x+\bp}=0,vide
e^{\a x-\bp}=0,vide
e^{\a x+\bp}=1,-\bp/\a
e^{\a x-\bp}=e,pari((1+(\bp))/\a)
e^{\a x+\bp}=-1,vide
e^{\a x-\bp}=-1,vide
e^{\a x+\bp}=-e,vide
e^{\a x-\bp}=-e,vide
e^{\a x+\bp}=\frac{1}{e},pari((-1-(\bp))/\a)
e^{\a x-\bp}=\frac{1}{e},pari((-1+(\bp))/\a)
}
\if{\a==1}{\text{data=wims(replace internal \a x by x in \data)}}
\if{\a==-1}{\text{data=wims(replace internal \a x by -x in \data)}}
#endif
#if defined TARGET_eqexpo2
\integer{sing1=randint(0..8)*randint(1,-1)}
\integer{sing2=randint(0..8)*randint(1,-1)}
\integer{s=\sing1+\sing2}
\integer{p=\sing1*\sing2}
\integer{d=randint(1..5)}
\integer{mp=-\p}
\integer{bp=(\d+(\s)^2)/4+1}
\text{t1=texmath(maxima(\s*x-\p))}
\text{t2=texmath(maxima(x^2+\p))}
\text{t3=texmath(maxima(x^2-\s*x))}
\text{tb1=texmath(maxima(\s*x-\bp))}
\text{tb2=texmath(maxima(x^2+\bp))}
\text{t20=texmath(maxima(x^2-\s*x+\p))}
\text{t30=texmath(maxima(x^2-\s*x+\p+1))}
\text{t2=texmath(maxima(x^2+\p))}
\text{t3=texmath(maxima(x^2-\s*x))}
\integer{p1=randint(2..4)*randint(1,-1)}
\integer{p2=\p-\p1}
\text{t1p=texmath(pari(\s*x-(\p2)))}
\text{t2p=texmath(pari(x^2+(\p1)))}

\text{data=e^{x^2}=e^{\t1},\sing1,\sing2
e^{\t2}=e^{\s x},\sing1,\sing2
e^{\t3}=e^{\mp},\sing1,\sing2
e^{x^2}=e^{\tb1},vide
e^{\tb2}=e^{\s x},vide
e^{\t3}=e^{-\bp},vide
e^{\t20}=1,\sing1,\sing2
e^{\t30}=e,\sing1,\sing2
e^{\t1p}=e^{\t2p},\sing1,\sing2
}
\if{\s==1}{\text{data=wims(replace internal \s x by x in \data)}}
\if{\s==-1}{\text{data=wims(replace internal \s x by -x in \data)}}
\text{tsol=\name_tsol \(e^{u(x)}=e^{v(x)} \Leftrightarrow u(x)=v(x)\).}
#endif
#if (defined TARGET_eqexpo5 || defined TARGET_eqexpo6 )
\integer{sing1=randint(2..8)*randint(1,-1)}
\integer{sing2=randint(2..8)*randint(1,-1)}
\integer{sing2=\sing2=\sing1?2*\sing1}
\integer{sing2=\sing2=-\sing1?2*\sing2}

\integer{s=\sing1+\sing2}
\integer{p=\sing1*\sing2}
\integer{bp=randint(1..5)+2*ln(exp(\sing1)+exp(\sing2))-ln(4)}

\text{t1=texmath(maxima(x+\sing1))}
\text{t2=texmath(maxima(x+\sing2))}

# if defined TARGET_eqexpo5
\integer{sing1p=\sing1+1}
\integer{sing1m=\sing1-1}

\text{data=e^{2 x}-(e^{\sing1}+e^{\sing2})e^x+e^{\s}=0,\sing1,\sing2
e^{2 x}-e^{\t1}+e^{\s}=e^{\t2},\sing1,\sing2
e^{2 x}-e^{\t1}=e^{\t2}-e^{\s},\sing1,\sing2
e^{2 x}-(e^{\sing1}+e^{\sing2})e^x+e^{\bp}=0,vide
e^{2 x}-e^{\t1}+e^{\bp}=e^{\t2},vide
e^{2 x}-e^{\t1}=e^{\t2}-e^{\bp},vide
e^{2 x}-(e^{\sing1}+1)e^x+e^{\sing1}=0,\sing1,0
e^{2 x}-e^{\t1}+e^{\sing1}=e^{x},\sing1,0
e^{2 x}-e^{\t1}=e^{x}-e^{\sing1},\sing1,0
e^{2 x}-(e^{\sing1}+e)e^x+e^{\sing1p}=0,\sing1,1
e^{2 x}-e^{\t1}+e^{\sing1p}=e^{x+1},\sing1,1
e^{2 x}-e^{\t1}=e^{x+1}-e^{\sing1p},\sing1,1
e^{2 x}-(e^{\sing1}+\frac{1}{e})e^x+e^{\sing1m}=0,\sing1,-1
e^{2 x}-e^{\t1}+e^{\sing1m}=e^{x-1},\sing1,-1
e^{2 x}-e^{\t1}=e^{x-1}-e^{\sing1m},\sing1,-1
e^{2 x}-(e^{\sing1}-\frac{1}{e})e^x-e^{\sing1m}=0,\sing1
e^{2 x}-e^{\t1}-e^{\sing1m}=-e^{x-1},\sing1
e^{2 x}-e^{\t1}=-e^{x-1}+e^{\sing1m},\sing1
e^{2 x}-(-e^{\sing1}+\frac{1}{e})e^x-e^{\sing1m}=0,-1
e^{2 x}+e^{\t1}-e^{\sing1m}=e^{x-1},-1
e^{2 x}+e^{\t1}=e^{x-1}+e^{\sing1m},-1
e^{2 x}-(e^{\sing1}-e^{\sing2})e^x-e^{\s}=0,\sing1
e^{2 x}-e^{\t1}-e^{\s}=-e^{\t2},\sing1
e^{2 x}-e^{\t1}=-e^{\t2}+e^{\s},\sing1
}
# endif
# if defined TARGET_eqexpo6
!!!!! On est ramené à une équation du second degré en X que l'on ne peut pas résoudre avec les outils de terminale :
!! on ne dispose pas du théorème avec la somme et les produits de racines.

\text{t3=texmath(maxima(2*x-(\s)))}
\text{t4=texmath(maxima(-x+(\s)))}
\text{t5=texmath(maxima(x-\sing1))}
\text{data=\frac{e^{\t1}-e^{\s}}{-e^{\sing2}+e^x}=e^{x},\sing1
\frac{e^{\sing1}}{1-e^{\t5}+e^{\t3}}=e^{\t4},\sing1,\sing2
\frac{e^{\sing1}+e^{\sing2}}{1+e^{\t3}}=e^{\t4},\sing1,\sing2
\frac{e^{\t1}-e^{\bp}}{-e^{\sing2}+e^x}=e^{x},vide
}
!!! Pour la première ligne de data sing2 ne peut pas être solution (valeur interdite)
# endif
#endif
#if (defined TARGET_eqexpo3 || defined TARGET_eqexpo4 )
\integer{a=randint(1..5)*randint(1,-1)}
\integer{b=randint(-5..5)}
\integer{c=randint(-5..5)}
\integer{d=randint(-5..5)}
\integer{c=\c=\a?\c+1}
\text{u=texmath(maxima(\a*x+\b))}
\text{v=texmath(maxima(\c*x+\d))}
# if defined TARGET_eqexpo3
\integer{k=randint(1..5)*randint(1,-1)}
\text{tk=\k=1? :\k}
\text{tk=\k=-1?-}
\integer{e=randint(1..5)}
\integer{f=\k*\e}
\text{num=texmath(x+\f)}
\text{num=wims(replace internal x by \tk e^{\u} in \num)}
\text{den=texmath(x+\e)}
\text{den=wims(replace internal x by e^{\v} in \den)}
\text{equat=\frac{\num}{\den}=\k}
\text{gsimple=texmath(x+\f)}
\text{gsimple=wims(replace internal x by \tk e^{\u} in \gsimple)}
\text{tsol=\name_tsol[1;]:<br>\(\gsimple=\k(\den)\).<br>
  \name_tsol[2;] \(e^{\u}=e^{\v}\) \name_tsol[3;] \(\u=\v\).}
# endif
# if defined TARGET_eqexpo4
\integer{k=randint(1..5)*randint(1,-1)}
\text{v=texmath(maxima(\c*x+\d-\k))}
\integer{e=randint(1..5)}
\integer{f=\k+\e}
\text{tf=\f=0?1:e^{\f}}
\text{tf=\f=1?e}
\text{tk=\k=0?1:e^{\k}}
\text{tk=\k=1?e}
\text{te=\e=0?1:e^{\e}}
\text{num=e^{\u}+\tf}
\text{den=e^{\v}+\te}
\text{equat=\frac{\num}{\den}=\tk}
\text{gsimple=texmath(e^{\u}+\tf)}
text{gsimple=wims(replace internal x by e^{\u}+\tk in \gsimple)}
\text{vpk=texmath(maxima(\c*x+\d))}
\text{tsol=\name_tsol[1;]:\(\gsimple=\tk(\den)\).
  \name_tsol[2;] \(e^{\u}=e^{\vpk}\), \name_tsol[3;] \(\u=\vpk\).}
# endif
\rational{rep=simplify(\d-\b)/(\a-\c)}
#else
\integer{nb=rows(\data)}
\integer{i=randint(1..\nb)}
integer{i=22}
\text{cedata=row(\i,\data)}
\text{equat=\cedata[1]}
\text{rep=item(2..-1,\cedata)}
#endif
#if defined TARGET_eqexpo1
\text{rep=maxima(\rep)} bonne réponse sous forme réduite.
\text{tsol=\rep issametext vide?\name_tsol}
#endif
#if (defined TARGET_eqexpo5 || defined TARGET_eqexpo6 )
\if{items(\rep)=2}{
  \integer{sing1=\rep[1]}
  \integer{sing2=\rep[2]}
  }{
    \if{\i>=16 and \i<20}{\integer{sing2=-1}}
    \if{\i>=19 and \i<22}{
      \integer{sing2=\sing1}
      \integer{sing1=-1}
    }
  }
\text{trep=\rep issametext vide?\rep:\sing1,\sing2}
\integer{ts=\trep[1]+\trep[2]}
\integer{tp=\rep issametext vide?\bp:\ts}
\text{X1=\rep issametext vide?e^{\sing1}:e^{\trep[1]}}
\text{X2=\rep issametext vide?e^{\sing2}:e^{\trep[2]}}
#include "lang1.inc"
\if{\i>=16}{
  \text{tsol=\name_tsol1}
  }{
    \text{tsol=\name_tsol2}
    \text{tsol=\rep issametext vide? \tsol \name_tsol3:\tsol \name_tsol4}
  }
#endif
#if defined TARGET_eqexpo6
#include "lang1.inc"
\text{tsol=\i==1 ? \name_sol}
#endif
\statement{
  \name_statement \(\equat\).
<div class="wimscenter"><label for="reply1">\(S=\)</label> \embed{reply1} </div>
<div class="wims_instruction">\name_instruction</div>
}
\answer{\name_answer}{\rep}{type=fset}
\solution{\tsol}
