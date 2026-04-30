target=pteinverse1 pteinverse2 pteinverse3 pteinverse4 ptecarre3
#if defined TARGET_pteinverse1
# define NUM 1
#endif
#if defined TARGET_pteinverse2
# define NUM 2
#endif
#if defined TARGET_pteinverse3
# define NUM 3
#endif
#if defined TARGET_pteinverse4
# define NUM 4
#endif
#if defined TARGET_ptecarre3
# define NUM 3
#endif
#include "lang_titles.inc"
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\precision{1000}
\computeanswer{yes}


#if defined TARGET_pteinverse1
\text{lstrep=\(x),\(-x),\(\frac{1}{x}),\(\frac{-1}{x})}
\text{lbrack=&#91;}
\text{rbrack=&#93;}
\text{ptvirg=&#59;}
\text{interlst=\rbrack 0\ptvirg 1 \lbrack, \rbrack 1\ptvirg \(+\infty) \lbrack, \rbrack -1\ptvirg 0 \lbrack, \rbrack \(-\infty)\ptvirg -1 \lbrack}
\integer{k=randint(1..4)}
\text{inter=\interlst[\k]}
\text{greplst=\(\frac{-1}{x}),\(-x),\(x),\(\frac{1}{x})
\(-x),\(\frac{-1}{x}),\(\frac{1}{x}),\(x)
\(\frac{1}{x}),\(x),\(-x),\(\frac{-1}{x})
\(x),\(\frac{1}{x}),\(\frac{-1}{x}),\(-x)
}
\text{rep=row(\k,\greplst)}
\text{size=40x40x4}
\statement{
  Ranger dans l'ordre croissant les réels suivants
<div class="wimscenter"> sachant que \(x \in ) \inter</div>
<div class="wimscenter">\embed{reply1,\size}</div>
}
\answer{rangement}{\rep;\lstrep}{type=clickfill}
#endif

#if defined TARGET_pteinverse2
\text{data=\(0 < a < b),\(\frac{1}{b}),\(\frac{1}{a})
\(a< b  \le 0),\(\frac{1}{b}),\(\frac{1}{a})
\(a < 0 < b),\(\frac{1}{a}),\(\frac{1}{b})
}
\text{cedata=randomrow(\data)}
\text{cond=\cedata[1]}
\text{rep1=\cedata[2]}
\text{rep2=\cedata[3]}
\text{lstrep=\rep1,\rep2}
\text{size=40x40x1}
\statement{
  Classer dans l'ordre croissant les inverses des réels \(a) et \(b),
<div class="wimscenter">sachant que \cond</div>
<div class="wimscenter">\embed{reply1,\size} \(<\) \embed{reply2,\size}</div>
}
\answer{}{\rep1;\lstrep}{type=clickfill}
\answer{}{\rep2;\lstrep}{type=clickfill}
#endif

#if defined TARGET_pteinverse3
\integer{a=randint(1..9)*randint(1,-1)}
\integer{b=randint(-9..9)}
\integer{c=randint(-9..9)}
\text{f=texmath(1/(\a*x+\b)+\c)}
\rational{rep=-\b/\a}
\statement{
  Quel est le réel \(x_0) qui n'a pas d'image par la fonction \(f) définie par
<div class="wimscenter">\(f(x)=\f)</div>
<div class="wimscenter">\(x_0=)\embed{reply1}</div>
}
\answer{axe}{\rep}{type=numeric}
#endif

#if (defined TARGET_pteinverse4  || defined TARGET_ptecarre3 )
#if defined TARGET_ptecarre3
\title{Propriété de la fonction carré 3}
\text{xlist=-3,-2,-1,-0.5,0,3,2,1,0.5,\(-10^3),-0.1,\(10^3),\(10^(-3)),0.1,\(-\sqrt{2}),\(2\sqrt{3}),\(\sqrt{2})}
\text{xlistn=-3,-2,-1,-0.5,0,3,2,1,0.5,-10^3,-0.1,10^3,10^(-3),0.1,-sqrt(2),2*sqrt(3),sqrt(2)}
\text{ylist=9,4,1,0.25,0,9,4,1,0.25,\(10^6),0.01,\(10^6),\(10^(-6)),0.01,2,12,2}
\text{ylistn=9,4,1,0.25,0,9,4,1,0.25,10^6,0.01,10^6,10^(-6),0.01,2,12,2}
\integer{nval=items(\xlist)}
\text{ind1=shuffle(9)}
\text{ind2=shuffle(5)}
\text{ind3=shuffle(3)}
\text{ind4=shuffle(5)}
\text{indl=\ind1[1],\ind2[1]+9,\ind3[1]+14,\ind4[1],\ind2[2]+9,\ind4[2]}
\if{\ylistn[\indl[4]]=0}
 {\text{rep4=0}}
 {\real{sol1=\xlistn[\indl[4]]}
  \real{sol2=\sol1*-1}
  \text{rep4=\sol1,\sol2}
 }
\if{\ylistn[\indl[5]]=0}
 {\text{rep5=0}}
 {\real{sol1=\xlistn[\indl[5]]}
  \real{sol2=\sol1*-1}
  \text{rep5=\sol1,\sol2}
 }
\if{\ylistn[\indl[6]]=0}
 {\text{rep6=0}}
 {\real{sol1=\xlistn[\indl[6]]}
  \real{sol2=\sol1*-1}
  \text{rep6=\sol1,\sol2}
 }

\text{tintro=On considère la fonction carré de référence \(f(x)=x^2).}
#endif

#if defined TARGET_pteinverse4
\title{TITRE 4}
\text{xlist=-3,-2,-1,-0.5,\(-10^3),-0.1,\(-\sqrt{2}),3,2,1,0.5,\(10^3),\(10^(-3)),0.1,\(\sqrt{2})}
\text{xlistn=-3,-2,-1,-0.5,-10^3,-0.1,-sqrt(2),3,2,1,0.5,10^3,10^(-3),0.1,sqrt(2)}
\text{ylist=\(-\frac{1}{3}),\(-\frac{1}{2}),-1,-2,\(-10^(-3)),-10,\(-\frac{\sqrt{2}}{2}),\(\frac{1}{3}),\(\frac{1}{2}),1,2,\(10^(-3)),\(10^3),10,\(\frac{\sqrt{2}}{2})}
\text{ylistn=-1/3,-0.5,-1,-2,-10^(-3),-10,-sqrt(2)/2,1/3,1/2,1,2,10^(-3),10^3,10,sqrt(2)/2}
\integer{nval=items(\xlist)}
\text{indl=shuffle(\nval)}
\text{tintro=On considère la fonction inverse de référence \(f(x)=\frac{1}{x}).}
#endif
\statement{
\tintro
<ol>
<li> Donner les images par \(f) des réels suivants&nbsp;:
 <table class="wimscenter wimsborder">
  <tr><th> Réel </th><th> Image </th></tr>
  <tr><td> \xlist[\indl[1]] </td><td> \embed{reply1,6}</td></tr>
  <tr><td> \xlist[\indl[2]] </td><td> \embed{reply2,6}</td></tr>
  <tr><td> \xlist[\indl[3]] </td><td> \embed{reply3,6}</td></tr>
 </table>
</li>
<li> Donner le (ou les) antécédent(s) des réels suivants&nbsp;:
 <table class="wimscenter wimsborder">
  <tr><th> Réel </th><th> Antécédent(s) </th></tr>
  <tr><td> \ylist[\indl[4]] </td><td> \embed{reply4,10}</td></tr>
  <tr><td> \ylist[\indl[5]] </td><td> \embed{reply5,10}</td></tr>
  <tr><td> \ylist[\indl[6]] </td><td> \embed{reply6,10}</td></tr>
 </table>
 <div class="wims_instruction">
 S'il y a plusieurs antécédents, les séparer par une virgule.<br>
  Taper <span class="tt">sqrt(2)</span> pour \(\sqrt{2}).
  </div></li>
</ol>
}
\answer{y1}{\ylistn[\indl[1]]}{type=numeric}
\answer{y2}{\ylistn[\indl[2]]}{type=numeric}
\answer{y3}{\ylistn[\indl[3]]}{type=numeric}
#if defined TARGET_pteinverse4
\answer{x4}{\xlistn[\indl[4]]}{type=fset}
\answer{x5}{\xlistn[\indl[5]]}{type=fset}
\answer{x6}{\xlistn[\indl[6]]}{type=fset}
#else
\answer{x4}{\rep4}{type=fset}
\answer{x5}{\rep5}{type=fset}
\answer{x6}{\rep6}{type=fset}
#endif
#endif
