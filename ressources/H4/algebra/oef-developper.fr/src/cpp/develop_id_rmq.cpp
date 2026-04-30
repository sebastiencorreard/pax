target=id_rmq0 id_rmq

\text{data=shuffle(2,3,4,5,6,7,8,9,1,1,1,1,1,1,1,1)}
\text{data2=shuffle(2,3,4,5,6,7,8,9)}
\if{\confparm1=Z}{
 \text{data=shuffle(2,3,4,5,-2,-3,-4,-5,-6,-7,-8,-9,-1,-1,-1,-1,1,1)}
 \text{data2=shuffle(2,3,4,5,-2,-3,-4,-5,-6,-7,-8,-9,-1,-1,-1,-1)}
}
\if{\confparm1=Q}{
 \text{data=shuffle(1/2,-1/3,2/3,-1/4,3/4,-1/5,2/5,-3/5,2,-3,4,-5,6,-7,8,-9,1,-1,1,-1,1,-1,1,-1)}
 \text{data2=shuffle(-1/2,1/3,-2/3,1/4,-3/4,1/5,-2/5,3/5,-2,3,-4,5,-6,7,-8,9)}
}

\text{vars=shuffle(x,x,y,z)}

\text{exprs=}
\text{sols=}


#if #TARGET(id_rmq0)
 \title{Identités remarquables (0).}
 \integer{taille=20}
 \integer{nmax=2}
 \text{has=shuffle(2,1)}
 \for{k=1 to \nmax} {

  //expressions de la forme : (a+b)² ou (a+b)(a-b)
  \text{x=shuffle(a,b,c,d)}
  \text{a=random(-\x[1],\x[1])}
  \text{b=random(-\x[2],\x[2])}

  \text{exprs2=(\a+\b)^2,(\a+\b)*(\a-\b)}
  \text{expr=\exprs2[\has[\k]]}
  \text{sol=maxima(expand(\expr))}

  \text{exemple=<table style="text-align:center;"><tr><td>\((a-b)^2)</td></tr><tr><td>\(=a^2+2\times a\times (-b)+(-b)^2)</td></tr><tr><td>\(=a^2-2*a*b+b^2)</td></tr></table>}


  \text{exprs=wims(append item \expr to \exprs)}
  \text{sols=wims(append item \sol to \sols)}
 }

#endif

#if #TARGET(id_rmq)
 \title{Identités remarquables (1).}
 \integer{taille=30}
 \integer{nmax=2}
 \text{has=shuffle(1,2,3,4,5,6,7)}

 \for{k=1 to \nmax} {

  //expressions de la forme : (ax+b)^2
  \text{x=\vars[\k]}
  \rational{a=\data[4*(\k-1)+1]}
  \rational{b=\data[4*(\k-1)+2]}

  //dans la deuxième, une variable dans le facteur commun et un signe moins
  \rational{b= \k=2 ? (-1)*\b : \b}

  \text{exprs2=(\a*\x+\b)^2,(\b+\a*\x)^2,(\b-\a*\x)^2,(\a*\x-\b)^2,(\a*\x+\b)*(\a*\x-\b),(\a*\x-\b)*(\a*\x+\b),(\b+\a*\x)*(\b-\a*\x)}
  \text{expr=\exprs2[\has[\k]]}
  \text{sol= maxima(expand(\expr)) }

  \text{exemple=<table style="text-align:center;"><tr><td>\((4*x+5)^2)</td></tr><tr><td>\(=(4*x)^2+2*4*x*5+5^2)</td></tr><tr><td>\(=16*x^2+40*x+25)</td></tr></table>}
  \if{\confparm1=Z}{
      \text{exemple=<table style="text-align:center;"><tr><td>\((-4*x-5)^2)</td></tr><tr><td>\(=(-4x)^2+2\times (-4x)\times (-5)+(-5)^2)</td></tr><tr><td>\(=16*x^2+40*x+25)</td></tr></table>}
  }
  \if{\confparm1=Q}{
      \text{exemple=<table style="text-align:center;"><tr><td>\((4*x+1/2)^2)</td></tr><tr><td>\(=(4 x)^2+2\times 4 x \times 1/2+(1/2)^2)</td></tr><tr><td>\(=16*x^2+4*x+1/4)</td></tr></table>}
  }

  \text{exprs=wims(append item \expr to \exprs)}
  \text{sols=wims(append item \sol to \sols)}
 }

#endif

#if #TARGET(id_rmq2)
 \title{Identités remarquables (2).}
 \integer{taille=30}
 \integer{nmax=2}
 \for{k=1 to \nmax} {

  //expressions de la forme : (ax+b)^2
  \text{x=\vars[\k]}
  \rational{a=\data[4*(\k-1)+1]}
  \rational{b=\data[4*(\k-1)+2]}
  \rational{d=\data[4*(\k-1)+4]}
  \rational{f=\data[4*(\k-1)+5]}

  //dans la deuxième, une variable dans le facteur commun et un signe moins
  \rational{b= \k=2 ? (-1)*\b : \b}

  \text{expr=random((\a*\x+\b)*(\d*\x+\f),(\b+\a*\x)*(\d*\x+\f),(\a*\x+\b)*(\f+\d*\x))}
  \text{sol= maxima(expand(\expr)) }

  \text{exemple=<table style="text-align:center;"><tr><td>\((4*x+5)*(x+6))</td></tr><tr><td>\(=4*x*x+4*x*6+5*x+5*6)</td></tr><tr><td>\(=4*x^2+24*x+5*x+30)</td></tr><tr><td>\(=4*x^2+29*x+30)</td></tr></table>}
  \if{\confparm1=Z}{
      \text{exemple=<table style="text-align:center;"><tr><td>\((4*x-5)*(-x+6))</td></tr><tr><td>\(=4x\times (-x)+4x\times 6-5\times (-x)-5\times 6)</td></tr><tr><td>\(=-4*x^2+24*x+5*x-30)</td></tr><tr><td>\(=-4*x^2+29*x-30)</td></tr></table>}
  }
  \if{\confparm1=Q}{
      \text{exemple=<table style="text-align:center;"><tr><td>\((4*x+1/2)*(x-1/3))</td></tr><tr><td>\(={4 x}\times{x}+{4 x}\times(-1/3)+1/2\times x+1/2 \times (-1/3))</td></tr><tr><td>\(=4*x^2-4/3*x+x/2-1/6)</td></tr><tr><td>\(=4*x^2-5/6*x-1/6)</td></tr></table>}
  }

  \text{exprs=wims(append item \expr to \exprs)}
  \text{sols=wims(append item \sol to \sols)}
 }

#endif

\statement{
Développer et réduire :
<ul>
 <li> \(\exprs[1])= \embed{r1,\taille}</li>
 <li> \(\exprs[2])= \embed{r2,\taille}</li>
</ul>
Si vous voulez voir un exemple, cliquer ci-dessous sur "Indication".
<p>Rédigez vos calculs sur une feuille de brouillon.</p>
}

\answer{}{\sols[1]}{type=algexp}
\answer{}{\sols[2]}{type=algexp}

\hint{Voici un exemple :<br>\exemple}
\solution{
Voici les expressions développées et réduites :
<ul>
 <li> \(\exprs[1]=\sols[1]) </li>
 <li> \(\exprs[2]=\sols[2]) </li>
</ul>
}
