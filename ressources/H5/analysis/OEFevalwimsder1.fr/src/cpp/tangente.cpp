target=tangente1 tangente2 tangente3 tangente4 tangente5
\author{Régine, Mangeard ; Maguy, Bruno}
\email{regine@mangeard.fr}
\format{html}
\precision{100}
#define TITRE Equation de tangente
#if defined TARGET_tangente1
\title{TITRE 1}
\integer{x0=randint(-5..5)}
\integer{y0=randint(-10..10)}
\integer{k=randint(-5..5)}
\text{eq=y=\y0+\k*(x-\x0)}
\statement{
   Une fonction \(f) de courbe représentative \(\mathcal{C}) est telle que
<div class="wimscenter"> \(f(\x0)=\y0) et \(f'(\x0)=\k)</div>
<p>
   Écrire une équation de la tangente \(\mathcal{T}) à \(\mathcal{C}) au point \(A) d'abscisse \x0&nbsp;:
</p>
<div class="wimscenter"><label for="reply1">\(\mathcal{T})&nbsp;:</label> \embed{reply1}</div>
}
\answer{tangente}{\eq}{type=equation}
#endif
#if defined TARGET_tangente2
\title{TITRE 2}
\text{infg=\(-\infty)}
\text{infd=\(+\infty)}
\text{empt=\(\emptyset)}
\text{ptvirg=&#59;}
\text{data1=randomrow(
1/(x+1),random(randint(-3..-2),randint(0..3)),\(\RR \setminus) &#123;-1 &#125;
sin(x),0, \(\ \RR)
cos(x),0,\(\ \RR)
)}
\text{data2=randomrow(
1/(x+1)^2,randint(0,1),\(\RR \setminus) &#123;-1 &#125;
(x+1)^2,randint(-3..3),\(\RR)
)}
\text{data3=randomrow(
(x+1)^3,randint(-2..2),\(\RR)
1/(x+1)^3,randint(0,1),\(\RR \setminus) &#123;-1 &#125;
)}
\text{datah=randomrow(
sqrt(x+1),random(0,3,8,15), &#91;-1 \ptvirg \infd &#91;
1/sqrt(x+1),random(0,3,15), &#93;-1 \ptvirg \infd &#91;
)}
\text{data=\data1;\data2;\data3;\datah}
\integer{cnt=rows(\data)}
\text{take=shuffle(\cnt)}
\text{data1=row(\take[1],\data)}
\text{f1=\data1[1]}

\integer{x0=\data1[2]}
\text{defdom=\data1[3]}
\text{v1=wims(replace internal x+1 by \plus1 in \f1)}
\text{v1=wims(replace internal x+2 by \plus2 in \v1)}
\text{v1=wims(mathsubst x=\epsilon in \v1)}
\function{f=\f1}
\function{value=\v1}
\real{y0=evalue(\f,x=\x0)}
\function{deriv=diff(\f,x)}
\real{deriv0=evalue(\deriv,x=\x0)}
\text{eq=y=\deriv0*(x-\x0)+\y0}

\statement{Soit la fonction \(f) de courbe représentative \(\mathcal{C}), définie sur \defdom par
<div class="wimscenter"> \(f(x)= \f).</div>
   Écrire une équation de la tangente \(\mathcal{T}) à \(\mathcal{C}) au point \(A) d'abscisse \x0&nbsp;:
<div class="wimscenter"><label for="reply1">\(\mathcal{T})&nbsp;:</label> \embed{reply1}</div>
}
\answer{tangente}{\eq}{type=equation}
#endif
#if defined TARGET_tangente3
\title{TITRE 3}
\integer{a=randint(1..5)*randint(1,-1)}
\integer{b=randint(-5..5)}
\integer{b2=-3*\a*\b}
\integer{c2=3*\a*(\b)^2}
\integer{d=-\a*(\b)^3}
\integer{k=randint(1..3)}
\integer{m=randint(-5..5)}
\if{\k=1}{
  \integer{nm=randint(1..5)}
  \integer{nm=\a<0?-\nm}
  \integer{n=\m+\nm}
  \text{mstep=r1}
}
\if{\k=2}{
  \integer{n=\m}
  \integer{x1=\b}
  \text{mstep=r1
r2}
}
\if{\k=3}{
  \integer{e=randint(1,4,9)}
  \integer{n=\m-\e*3*\a}
  \integer{x2=sqrt(\e)+\b}
  \integer{x1=-sqrt(\e)+\b}
  \text{mstep=r1
r2}
}
\integer{c2=\c2+\n}
\integer{tmp=\a*(\m-\n)}
\text{ft=texmath(maxima(\a*x^3+\b2*x^2+\c2*x+\d))}
\steps{\mstep}
\text{lstrep= aucun point, un point, deux points}
\statement{
  Soit la fonction \(f) définie sur \(\ \RR) par :
  <div class="wimscenter">\(f(x)=\ft).</div>

  \if{\step=1}{
    <p>
       Combien existe-t-il de points de \(\mathcal{C}) où la tangente a
       pour coefficient directeur \m?
    </p>
    <div class="wimscenter"> \embed{reply1}</div>
  }{<p>
    Il existe \lstrep[\k] de \(\mathcal{C}) où la tangente a pour coefficient directeur \m.
    </p>
    \if{\k=2}{
      <p>Indiquer l'abscisse de ce point:</p>
      <div class="wimscenter"><label for="reply2">\(x=)</label> \embed{reply2,3} </div>
    }{<p>
      Indiquer les abscisses \(x_1) et \(x_2) de ces points avec \(x_1 < x_2):
      </p>
      <div class="wimscenter"><label for="reply2">\(x_1=)</label> \embed{reply2,3} </div>
      <div class="wimscenter"><label for="reply3">\(x_2=)</label>  \embed{reply3,3} </div>
    }
  }
}

\answer{nombre de points}{\k;aucun,un,deux}{type=radio}
\answer{solution}{\x1}{type=numeric}
\answer{deuxième solution}{\x2}{type=numeric}
#endif
#if defined TARGET_tangente4
\title{TITRE 4}
\integer{b=randint(-5..5)}
\integer{a=randint(1..5)*randint(1,-1)}
\integer{c=randint(-5..5)}
\integer{m=randint(-5..5)}
\function{f=\a*x^2+\b*x+\c}
\text{tf=texmath(maxima(\f))}
\rational{xA=-\b/(2*\a)}
\rational{yA=evalue(\f,x=\xA)}
\rational{xB=(\m-\b)/(2*\a)}
\rational{yB=evalue(\f,x=\xB)}
\text{eqd=texmath(maxima(\m*x))}
\statement{
   Soit la fonction \(f) définie sur \(\ \RR) par \(f(x)=\tf) et \(\mathcal{P}) sa représentation graphique.
<p>
 Déterminer les coordonnées des points suivants&nbsp;:
</p><ol>
<li> \(A\), point en lequel \(\mathcal{P}) admet une tangente horizontale&nbsp;:
<div class="wimscenter"><label for="reply1">\(A)=</label> (\embed{reply1,3},\embed{reply2,3})</div>
</li>
<li> \(B\), point en lequel \(\mathcal{P}) admet une tangente parallèle à la droite d'équation \(y=\eqd)&nbsp;:
<div class="wimscenter"><label for="reply3">\(B)=</label> (\embed{reply3,3},\embed{reply4,3})</div>
</li></ol>

}
\answer{xA}{\xA}{type=numeric}
\answer{yA}{\yA}{type=numeric}
\answer{xB}{\xB}{type=numeric}
\answer{yB}{\yB}{type=numeric}
#endif
#if defined TARGET_tangente5
\title{TITRE 5}
\integer{k=randint(1,-1)}
\integer{a=randint(1..5)*\k}
\integer{x0=randint(1..6)}
\integer{x1=-\x0}
\integer{b=-\a*2*\x0^2}
\integer{c=randint(-5..5)}
\integer{d=randint(-5..5)}
\rational{p=\d-(\b)^2/(4*\a)}
\function{f=\a*x^4+\b*x^2+\c*x+\d}
\text{tf=texmath(maxima(\f))}
\text{eqt=y=\c*x+\p}
\statement{
   Soit la fonction \(f), de courbe représentative \(\mathcal{P}), définie sur \(\ \RR) par
<div class="wimscenter"> \(f(x)=\tf).</div>
<p>
   On cherche à déterminer l'équation d'une droite \(\mathcal{T}) de pente
\c qui soit tangente à \(\mathcal{P}) en deux points distincts.
</p>
<ol>
<li> Quelle est l'équation de \(\mathcal{T})?
<div class="wimscenter"> <label for="reply1">\(\mathcal{T})&nbsp;:</label> \embed{reply1}</div>
</li><li> Quelles sont les abscisses \(x_1) et \(x_2) avec \(x_1 < x_2) des points de tangence?
<div class="wimscenter"> <label for="reply2">\(x_1)=</label> \embed{reply2,5} </div>
<div class="wimscenter"> <label for="reply3">\(x_2)=</label> \embed{reply3,5} </div>
</li>
</ol>
}
\answer{equation}{\eqt}{type=equation}
\answer{\(x_1)}{\x1}{type=numeric}
\answer{\(x_2)}{\x0}{type=numeric}
#endif
