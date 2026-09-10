target=propbary1 propbary2 cnstbary1

#include "author.inc"
#if defined TARGET_propbary1 || defined TARGET_propbary2
# define TITRE Propriétés des barycentres
#endif
#if defined TARGET_cnstbary1
# define TITRE Calcul et construction de barycentre
# define NUM
#endif
#if defined TARGET_propbary1
# define NUM 1
#endif
#if defined TARGET_propbary2
# define NUM 2
#endif

\title{TITRE NUM}
#if defined TARGET_propbary1
\matrix{V=slib(matrix/invertible 3,3)}
\matrix{u=\V[1;]}
\matrix{v=\V[2;]}
\matrix{w=\V[3;]}
\integer{a=randint(1..10)*randint(1,-1)}
\integer{b=randint(1..10)*randint(1,-1)}
\integer{d=randint(2,4,5,8,10)*randint(1,-1)}
\integer{c=\d-\a-\b}
\rational{xG=simplify((\a*\u[1]+\b*\v[1]+\c*\w[1])/\d)}
\rational{yG=simplify((\a*\u[2]+\b*\v[2]+\c*\w[2])/\d)}
\rational{zG=simplify((\a*\u[3]+\b*\v[3]+\c*\w[3])/\d)}
\integer{xD=-\u[1]-\v[1]}
\integer{yD=-\u[2]-\v[2]}
\integer{zD=-\u[3]-\v[3]}


\integer{a2=randint(1..10)*randint(1,-1)}
\integer{b2=randint(1..10)*randint(1,-1)}
\integer{c2=1-\a2-\b2}
\integer{xD=\a2*\u[1]+\b2*\v[1]+\c2*\w[1]}
\integer{yD=\a2*\u[2]+\b2*\v[2]+\c2*\w[2]}
\integer{zD=\a2*\u[3]+\b2*\v[3]+\c2*\w[3]}
\statement{
<p>
 On rapporte l'espace à un repère \((0,\vec{i},\vec{j},\vec{k})).
 On considère les points \(A(\u[1],\u[2],\u[3]),B(\v[1],\v[2],\v[3])) et \(C(\w[1],\w[2],\w[3])).<p>
 </p>
 Déterminer les réels \(\,\alpha\), \(\,\beta) et \(\,\gamma) tels que le point \(G(\xG,\yG,\zG))
 soit le barycentre de \((A,\alpha),(B,\beta),(C,\gamma)), avec \(\alpha+\beta+\gamma=\d).
<div class="wimscenter">
\(\,\alpha=)\embed{reply1,3}
\(\,\beta=)\embed{reply2,3}
\(\,\gamma=)\embed{reply3,3}
</div>
 Déterminer les réels \(a,b) et \(c) tels que le point \(D(\xD,\yD,\zD)) soit
 le barycentre de \((A,a),(B,b)) et \((C,c)) avec \(a+b+c=1).
<div class="wimscenter">
\(a=)\embed{reply4,3} &nbsp;&nbsp; \(b)\embed{reply5,3} &nbsp;&nbsp; \(c=)\embed{reply6,3}
</div>

}
\answer{\(\alpha)}{\a}{type=numeric}
\answer{\(\beta)}{\b}{type=numeric}
\answer{\(\gamma)}{\c}{type=numeric}
\answer{a}{\a2}{type=numeric}
\answer{a}{\b2}{type=numeric}
\answer{a}{\c2}{type=numeric}
#endif

#if defined TARGET_propbary2
\integer{a=randint(2..10)*randint(1,-1)}
\integer{b=randint(1..10)*randint(1,-1)}
\integer{c=randint(1..10)*randint(1,-1)}
\integer{c=\a+\b+\c=0?\c+randint(1..5)}
\integer{d=randint(2..10)*randint(1,-1)}
\integer{e=randint(1..10)*randint(1,-1)}
\integer{e=\d+\e=0?-\e}
\integer{ck=\a*(\d+\e)}
\integer{cb=\b*\d-\a*\e}
\integer{cc=\c*\d}
\statement{
<p>
Soit \(A\), \(B\) et \(C) trois points distincts. Soit
\(G) le barycentre des points pondérés \((A,\a),(B,\b)) et \((C,\c))
et \(K) le barycentre des points pondérés \((A,\d)) et \((B,\e)).
</p><p>
  Déterminer des coefficients \(\,\alpha\), \(\,\beta) et \(\,\gamma) tels que \(G\)
 soit le barycentre de \((K,\alpha),(B,\beta)) et \((C,\gamma)).
</p>
<div class="wimscenter"> <label for="reply1">\(\,\alpha=)</label> \embed{reply1,3} </div>
<div class="wimscenter"> <label for="reply1">\(\,\beta=)</label> \embed{reply2,3} </div>
<div class="wimscenter"> <label for="reply1">\(\,\gamma=)</label> \embed{reply3,3} </div>
}
\answer{\(\alpha)}{\rk}{type=numexp}
\answer{\(\beta)}{\rb}{type=numexp}
\answer{\(\gamma)}{\rc}{type=numexp}
\condition{coefficients}{\rk*\cc=\rc*\ck and \rk*\cb=\rb*\ck}
\solution{ Une solution possible est : \(\alpha=\ck) , \(\beta=\cb) et \(\gamma=\cc)}
#endif

#if defined TARGET_cnstbary1
\integer{k=randint(2..4)}
\integer{a1=randint(2,3,5,6,7)}
\integer{b1=\k*\a1}
\integer{c1=\k*(\a1-1)}
\integer{a2=randint(10000..25000)}
\integer{b2=\k*\a2}
\text{data=\a1 \pi,\b1 \pi,
\frac{\sqrt{\a1}-1}{\c1},\frac{1}{1+\sqrt{\a1}}
\a2,\b2
}
\text{cedata=randomrow(\data)}
\text{a=\cedata[1]}
\text{b=\cedata[2]}

\text{donnees=slib(draw/repere 806,64,0,-10,40,-1,3,1,1,black,grey)}

\text{tmp=row(1,\donnees)}
\\\\\\coordonnées de l'origine du repère
\integer{Ox=item(1,\tmp)}
\integer{Oy=item(2,\tmp)}

\text{tmp=row(2,\donnees)}
\\\\\\échelle des axes
\integer{ex=item(1,\tmp)}
\integer{ey=item(2,\tmp)}

\rational{fx=30*\k/(1+\k)}
\integer{fy=0}
\rational{\fxx=\Ox+\ex*\fx}
\rational{\fxxm=\fxx-0.3*\ex}
\rational{\fxxp=\fxx+0.3*\ex}
\text{image= draw(806,64
  xrange -10,40
  yrange -1,3
  hline 0,0,red
  parallel -9,-0.2,-9,0.2,1,0,50,blue
  linewidth 2
  parallel -5,-0.4,-5,0.4,10,0,5,green
  parallel -10,-0.4,-10,0.4,10,0,6,red
  text red,-0.1,1.5,medium,A
  text red,30-0.1,1.5,medium,B
  linewidth 5
  points red,0,0,30,0)
  }
\text{repimage=
  xrange -10,40
  yrange -1,3
  hline 0,0,red
  parallel -9,-0.2,-9,0.2,1,0,50,blue
  linewidth=2
  parallel -5,-0.4,-5,0.4,10,0,5,green
  parallel -10,-0.4,-10,0.4,10,0,6,red
  text red,-0.1,1.5,medium,A
  text red,30-0.1,1.5,medium,B
  linewidth 5
  points red,0,0,30,0,\fx,0
  text red,\fx-0.1,-0.5,medium,M
  }

\statement{<p>
 On a représenté ci-dessous un segment \(\lbrack A B \rbrack), de longueur non
 nulle. Placer le barycentre des points \(A) et \(B),
 affectés des coefficients \(\alpha=\a) et \(\beta=\b).
 </p>
}
\answer{}{\image;rectangle,\fxxm,0,\fxxp,64}{type=coord}
\solution{
<div class="wimscenter">
\draw{800,64}{\repimage}
</div>
}
#endif
