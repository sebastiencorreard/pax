target=eq_deg1_1 eq_deg1_2 ord_orig coord_mil eq_prod

\text{data=shuffle(2,3,4,5,6,7,8,9,0.2,1.4,2.5,3.7,0.05,4.5,1.25,7.75)}
\if{\confparm1=Z}{
 \text{data=shuffle(2,-3,4,-5,-6,7,-8,9,0.2,-1.4,2.5,-3.7,0.05,-4.5,1.25,-7.75)}
}
\if{\confparm1=Q}{
 \text{data=shuffle(-1/2,1/3,-2/3,1/4,-3/4,1/5,-2/5,3/5,-4/5,1/6,-5/6,2,-3,4,-5,6)}
}

\precision{1000}
\text{question=}
\text{sol=}
\text{solexact=}
\text{complement=}
\text{solu=solution}
\text{ac1=}
\text{ac2=}
\integer{nmax=2}
\author{Paul, Byache}

#if #TARGET(coord_mil)
 \title{Calcul de coordonnées avec un milieu.}
 \for{k=1 to \nmax} {

  //équations de la forme : (a+x)/2=b
  \text{complement=(l'inconnue est notée \(x) ou \(y)) }
  \rational{a=\data[4*(\k-1)+1]}
  \rational{b=\data[4*(\k-1)+2]}
  \text{inc= \k=1 ? x : y}
  \text{x1=x}
  \text{x2=y}
  
  \text{quest=\frac{\a+\inc}{2}=\b}

  \rational{sexact=-\a+2*\b}
  \real{sapprox=round(\sexact*1000)/1000}
  \if{. isin \sexact}{
   \text{s=abs(\sapprox-\sexact)>10^(-20) ? \inc \approx \sapprox : \inc=\sexact}
  }{
   \text{s=\inc=\sexact}
  }
  
  \text{exemple=<table><tr><td>\(\frac{3+x}{2}=5)</td></tr><tr><td>\(\Leftrightarrow 3+x=5\times 2)</td></tr><tr><td>\(\Leftrightarrow 3+x=10)</td></tr><tr><td>\(\Leftrightarrow x=10-3=7)</td></tr></table>}
  \if{\confparm1=Z}{
    \text{exemple=<table><tr><td>\(\frac{-3+x}{2}=-5)</td></tr><tr><td>\(\Leftrightarrow -3+x=-5\times 2)</td></tr><tr><td>\(\Leftrightarrow -3+x=-10)</td></tr><tr><td>\(\Leftrightarrow x=-10+3=-7)</td></tr></table>}
  }
  \if{\confparm1=Q}{
    \text{exemple=<table><tr><td>\(\frac{2/3+x}{2}=1/5)</td></tr><tr><td>\(\Leftrightarrow 2/3+x=2\times (1/5))</td></tr><tr><td>\(\Leftrightarrow 2/3+x=2/5)</td></tr><tr><td>\(\Leftrightarrow x=(2/5)-(2/3)=(6/15)-(10/15)=-4/15)</td></tr></table>}
  }
  
  \text{question=wims(append item \quest to \question)}
  \text{sol=wims(append item \s to \sol)}
  \text{solexact=wims(append item \sexact to \solexact)}

 }

#endif

#if #TARGET(ord_orig)
 \title{Calcul de l'ordonnée à l'origine.}
 
 \for{k=1 to \nmax} {

  //équations de la forme : a=bc+p (inconnue notée p)
  \text{complement=(l'inconnue est notée \(p)) }
  \rational{a=\data[4*(\k-1)+1]}
  \rational{b=\data[4*(\k-1)+2]}
  \rational{c=\data[4*(\k-1)+3]}
  
  \text{x1=p}
  \text{x2=p}

  \text{b= (- isin \b or / isin \b) ? (\b) : \b }
  \text{c= (- isin \c or / isin \c) ? (\c) : \c }
  
  \text{quest=\a=\b\times\c+p}

  \rational{sexact=\a-\b*\c}
  \real{sapprox=round(\sexact*1000)/1000}
  \if{. isin \sexact}{
   \text{s=abs(\sapprox-\sexact)>10^(-20) ? p \approx \sapprox : p=\sexact}
  }{
   \text{s=p=\sexact}
  }
  
  \text{exemple=<table><tr><td>\(3=2\times 7+p)</td></tr><tr><td>\(\Leftrightarrow 3=14+p)</td></tr><tr><td>\(\Leftrightarrow 3-14=p)</td></tr><tr><td>\(\Leftrightarrow -11=p)</td></tr><tr><td>ou encore :\(p=-11)</td></tr></table>}
  \if{\confparm1=Z}{
    \text{exemple=<table><tr><td>\(-3=2\times (-7)+p)</td></tr><tr><td>\(\Leftrightarrow -3=-14+p)</td></tr><tr><td>\(\Leftrightarrow -3+14=p)</td></tr><tr><td>\(\Leftrightarrow 11=p)</td></tr><tr><td>ou encore :\(p=11)</td></tr></table>}
  }
  \if{\confparm1=Q}{
   \text{exemple=<table><tr><td>\(3=(2/3) \times (7/5)+p)</td></tr><tr><td>\(\Leftrightarrow 3=(14/15)+p)</td></tr><tr><td>\(\Leftrightarrow 3-(14/15)=p)</td></tr><tr><td>\(\Leftrightarrow (45/15)-(14/15)=p)</td></tr><tr><td>\(\Leftrightarrow 31/15=p)</td></tr><tr><td>ou encore :\(p=31/15)</td></tr></table>}
  }
  
  \text{question=wims(append item \quest to \question)}
  \text{solexact=wims(append item \sexact to \solexact)}
  \text{sol=wims(append item \s to \sol)}
 }

#endif


#if #TARGET(eq_deg1_1)
 \title{Equation du 1er degré (1)}

 \text{x=randitem(x,x,y,z,t)}
 \text{complement=(l'inconnue est notée par la lettre \(\x)) }
 \text{x1=\x}
 \text{x2=\x}

 \for{k=1 to \nmax} {

  //équations de la forme : ax+b=c
  \rational{a=\data[4*(\k-1)+1]}
  \rational{b=\data[4*(\k-1)+2]}
  \rational{c=\data[4*(\k-1)+3]}
  
  \if{\k=1}{
    \text{quest=\a*\x+\b=\c}
  }{
    \text{quest=\c=\a*\x+\b}
  }

  \rational{sexact=(\c-\b)/\a}
  \real{sapprox=round(\sexact*1000)/1000}
  \if{. isin \sexact}{
   \text{s=abs(\sapprox-\sexact)>10^(-20) ? \x \approx \sapprox : \x=\sexact}
  }{
   \text{s=x=\sexact}
  }
  
  \text{exemple=<table><tr><td>\(3x+2=7)</td></tr><tr><td>\(\Leftrightarrow 3x=7-2)</td></tr><tr><td>\(\Leftrightarrow x=5/3)</td></tr></table>}
  \if{\confparm1=Z}{
   \text{exemple=<table><tr><td>\(-3x+2=7)</td></tr><tr><td>\(\Leftrightarrow -3x=7-2)</td></tr><tr><td>\(\Leftrightarrow x=\frac{5}{-3}=-\frac{5}{3})</td></tr></table>}
  }
  \if{\confparm1=Q}{
   \text{exemple=<table><tr><td>\(2/3 x+2=7)</td></tr><tr><td>\(\Leftrightarrow 2/3 x=7-2)</td></tr><tr><td>\(\Leftrightarrow x=\frac{5}{\frac{2}{3}}=5\times\frac{3}{2}=\frac{15}{2})</td></tr></table>}
  }
  
  \text{question=wims(append item \quest to \question)}
  \text{sol=wims(append item \s to \sol)}
  \text{solexact=wims(append item \sexact to \solexact)}

 }

#endif


#if #TARGET(eq_deg1_2)
 \title{Equation du 1er degré (2)}

 \text{x=randitem(x,x,y,z,t)}
 \text{complement=(l'inconnue est notée par la lettre \(\x)) }

 \text{x1=\x}
 \text{x2=\x}
 
 \for{k=1 to \nmax} {

  //équations de la forme : ax+b=cx+d
  \rational{a=\data[4*(\k-1)+1]}
  \rational{b=\data[4*(\k-1)+2]}
  \rational{c=\data[4*(\k-1)+3]}
  \rational{d=\data[4*(\k-1)+4]}
  
  \text{quest=\a*\x+\b=\c*\x+\d}

  \rational{sexact=(\d-\b)/(\a-\c)}
  \real{sapprox=round(\sexact*1000)/1000}
  \if{. isin \sexact}{
   \text{s=abs(\sapprox-\sexact)>10^(-20) ?\x \approx \sapprox : \x=\sexact}
  }{
   \text{s=x=\sexact}
  }
  
  
  \text{exemple=<table><tr><td>\(5x+2=3x+7)</td></tr><tr><td>\(\Leftrightarrow 5x-3x=7-2)</td></tr><tr><td>\(\Leftrightarrow 2x=5)</td></tr><tr><td>\(\Leftrightarrow x=5/2)</td></tr></table>}
  \if{\confparm1=Z}{
   \text{exemple=<table><tr><td>\(-3x+2=-x-7)</td></tr><tr><td>\(\Leftrightarrow -3x+x=-7-2)</td></tr><tr><td>\(\Leftrightarrow -2x=-9)</td></tr><tr><td>\(\Leftrightarrow x=\frac{-9}{-2}=\frac{9}{2})</td></tr></table>}
  }
  \if{\confparm1=Q}{
   \text{exemple=<table><tr><td>\(\frac{2}{3} x+\frac{1}{2}=\frac{x}{4}-7)</td></tr><tr><td>\(\Leftrightarrow \frac{2}{3} x-\frac{x}{4} =-7-\frac{1}{2})</td></tr><tr><td>\(\Leftrightarrow \frac{8}{12} x-\frac{3}{12} x =-\frac{14}{2}-\frac{1}{2})</td></tr><tr><td>\(\Leftrightarrow \frac{5}{12} x =-\frac{15}{2})</td></tr><tr><td>\(\Leftrightarrow x=\frac{-\frac{15}{2}}{\frac{5}{12}}=-\frac{15}{2}\times\frac{12}{5}=-18)</td></tr></table>}
  }
  
  \text{question=wims(append item \quest to \question)}
  \text{sol=wims(append item \s to \sol)}
  \text{solexact=wims(append item \sexact to \solexact)}

 }

#endif

\statement{
Résoudre \complement: 
<ul>
 <li> équation 1 : \(\question[1]). Cette équation a une seule solution, qui est : \(\x1)=\embed{r1,5}</li> 
 <li> équation 2 : \(\question[2]). Cette équation a une seule solution, qui est : \(\x2)=\embed{r2,5}</li> 
</ul>
<div class="wims_instruction"> Si vous voulez voir un exemple, cliquer ci-dessous sur "Indication".
<p>Donner la valeur exacte de la solution ou une valeur approchée à \(10^-3) près. </p>
<p>Rédigez vos calculs sur une feuille de brouillon.</p>
</div>
}

\answer{}{\solexact[1]}{type=numeric}{option=comma,absolute}
\answer{}{\solexact[2]}{type=numeric}{option=comma,absolute}


\solution{
Voici les solutions : 
<ul>
\for{j=1 to \nmax}{
 <li> \solu de l'équation \j : \ac1 \(\sol[\j]) \ac2 </li>
}
</ul>
}

\hint{Voici un exemple :<br/>\exemple}
