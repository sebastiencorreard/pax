target=distrib_simple distrib_simple2 distrib_double distrib_double0 distrib_double2

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

#if #TARGET(distrib_simple)
 \title{Distributivité simple (1).}
 \integer{taille=10}
 \integer{nmax=2}
 \for{k=1 to \nmax} {

  //expressions de la forme : c(ax+b)
  \text{x=\vars[\k]}
  \rational{a=\data[3*(\k-1)+1]}
  \rational{b=\data[3*(\k-1)+2]}
  \rational{c=\data2[3*(\k-1)+3]}

  //dans la deuxième, une variable dans le facteur commun
  \text{c= \k=2 ? \c*\x : \c}

  \text{expr=random(\c*(\a*\x+\b),\c*(\b+\a*\x))}
  \text{sol= maxima(expand(\expr))}

  \text{exemple=<table style="text-align:center;"><tr><td>\(2*x*(4*x+5))</td></tr><tr><td>\(=2*x*4*x+2*x*5)</td></tr><tr><td>\(=8*x^2+10*x)</td></tr></table>}
  \if{\confparm1=Z}{
      \text{exemple=<table style="text-align:center;"><tr><td>\(-2*x*(4*x-5))</td></tr><tr><td>\(=-2x\times 4x-2x\times(-5))</td></tr><tr><td>\(=-8*x^2+10*x)</td></tr></table>}
  }
  \if{\confparm1=Q}{
      \text{exemple=<table style="text-align:center;"><tr><td>\(2/3*x*(4*x+1/2))</td></tr><tr><td>\(={2/3 x}\times{4x}+{2/3 x}\times{1/2})</td></tr><tr><td>\(=8/3*x^2+1/3*x)</td></tr></table>}
  }

  \text{exprs=wims(append item \expr to \exprs)}
  \text{sols=wims(append item \sol to \sols)}
 }

#endif

#if #TARGET(distrib_simple2)
 \title{Distributivité simple (2).}
 \integer{taille=30}
 \integer{nmax=2}
 \for{k=1 to \nmax} {

  //expressions de la forme : c(ax+b)+g(dx+f)
  \text{x=\vars[\k]}
  \rational{a=\data[4*(\k-1)+1]}
  \rational{b=\data[4*(\k-1)+2]}
  \rational{c=\data2[2*(\k-1)+3]}
  \rational{d=\data[4*(\k-1)+4]}
  \rational{f=\data[4*(\k-1)+5]}
  \rational{g=\data2[2*(\k-1)+6]}

  //dans la deuxième, une variable dans le facteur commun et un signe moins
  \text{c= \k=2 ? \c*\x : \c}
  \rational{g= \k=2 ? (-1)*\g : \g}

  \text{expr=random(\c*(\a*\x+\b)+\g*(\d*\x+\f),\c*(\b+\a*\x)+\g*(\d*\x+\f),\c*(\a*\x+\b)+\g*(\f+\d*\x))}
  \text{sol= maxima(expand(\expr)) }

  \text{exemple=<table style="text-align:center;"><tr><td>\(2*x*(4*x+5)-3*(x+6))</td></tr><tr><td>\(=2*x*4*x+2*x*5-3*x-3*6)</td></tr><tr><td>\(=8*x^2+10*x-3*x-18)</td></tr><tr><td>\(=8*x^2+7*x-18)</td></tr></table>}
  \if{\confparm1=Z}{
      \text{exemple=<table style="text-align:center;"><tr><td>\(-2*x*(4*x-5)-3*(x-6))</td></tr><tr><td>\(=-2x\times 4x-2x\times(-5)-3x-3\times (-6))</td></tr><tr><td>\(=-8*x^2+10*x-3*x+18)</td></tr><tr><td>\(=-8*x^2+7*x+18)</td></tr></table>}
  }
  \if{\confparm1=Q}{
      \text{exemple=<table style="text-align:center;"><tr><td>\(2/3*x*(4*x+1/2)-1/3*(x+6))</td></tr><tr><td>\(={2/3 x}\times{4x}+{2/3 x}\times{1/2}-1/3\times x-1/3 \times 6)</td></tr><tr><td>\(=8/3*x^2+1/3*x-1/3*x-2)</td></tr><tr><td>\(=8/3*x^2-2)</td></tr></table>}
  }

  \text{exprs=wims(append item \expr to \exprs)}
  \text{sols=wims(append item \sol to \sols)}
 }

#endif

#if #TARGET(distrib_double0)
 \title{Distributivité double (0).}
 \integer{taille=20}
 \integer{nmax=2}
 \for{k=1 to \nmax} {

  //expressions de la forme : (a+b)(c-d)
  \text{x=shuffle(a,b,c,d)}
  \text{a=random(-\x[1],\x[1])}
  \text{b=random(-\x[2],\x[2])}
  \text{c=random(-\x[3],\x[3])}
  \text{d=random(-\x[4],\x[4])}


  \text{expr=(\a+\b)*(\c+\d)}
  \text{sol= maxima(\a*\c+\a*\d+\b*\c+\b*\d)}

  \text{exemple=<table style="text-align:center;"><tr><td>\((a+b)(c-d))</td></tr><tr><td>\(=a\times c+a\times (-d)+b\times c+b\times (-d))</td></tr><tr><td>\(=a*c-a*d+b*c-b*d)</td></tr></table>}


  \text{exprs=wims(append item \expr to \exprs)}
  \text{sols=wims(append item \sol to \sols)}
 }

#endif

#if #TARGET(distrib_double)
 \title{Distributivité double (1).}
 \integer{taille=20}
 \integer{nmax=2}
 \for{k=1 to \nmax} {

  //expressions de la forme : (a+b)(c-d) avec c=a ou d=b ou les deux
  \text{x=shuffle(a,b,c,d)}
  \text{a=random(-\x[1],\x[1])}
  \text{b=random(-\x[2],\x[2])}
  \text{c=random(-\x[3],\x[3])}
  \text{d=random(-\x[4],\x[4])}

  \if{\k=1}{
     \text{c=random(\a,\b)}
  }
  \if{\k=2}{
     \text{c=\b}
     \text{d=\a}
  }

  \text{expr=random((\a+\b)*(\c+\d),(\c+\d)*(\a+\b))}
  \text{sol= maxima(\a*\c+\a*\d+\b*\c+\b*\d)}

  \text{exemple=<table style="text-align:center;"><tr><td>\((a+b)(a-d))</td></tr><tr><td>\(=a\times a+a\times (-d)+b\times a+b\times (-d))</td></tr><tr><td>\(=a^2-a*d+b*a-b*d)</td></tr></table>}


  \text{exprs=wims(append item \expr to \exprs)}
  \text{sols=wims(append item \sol to \sols)}
 }

#endif

#if #TARGET(distrib_double2)
 \title{Distributivité double (2).}
 \integer{taille=30}
 \integer{nmax=2}
 \for{k=1 to \nmax} {

  //expressions de la forme : (ax+b)(dx+f)
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
