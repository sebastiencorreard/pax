target=approx1 approx2 approx3 approx4 approx5
\author{Régine, Mangeard ; Maguy, Bruno}
\email{regine@mangeard.fr}
\format{html}
\precision{10000}
#define TITRE Approximation affine
#if defined TARGET_approx1
\title{TITRE 1}
\integer{x0=randint(-5..5)}
\integer{y0=randint(-10..10)}
\integer{k=randint(-5..5)}
\function{f=\y0+\k*(x-\x0)}
\statement{
   Une fonction \(f) de courbe représentative \(\mathcal{C}) est telle que
<div class="wimscenter"> \(f(\x0)=\y0) et \(f'(\x0)=\k)</div>
<p>
   Quelle est l'approximation affine de \(f) en \x0?
</p>
<div class="wimscenter"><label for="reply1">\(x \mapsto)</label> \embed{reply1}</div>
}
\answer{approximation affine}{\f}{type=formal}
#endif
#if defined TARGET_approx2
\title{TITRE 2}
\integer{x0=randint(-9..9)}
\integer{y0=randint(-9..9)}
\rational{k=simplify(randint(-5..5)/randint(2,3,5))}
\text{tk=texmath(\k)}
\integer{a=randint(1..5)*randint(1,-1)}
\real{h=\a/10^2}
\real{x1=\x0+\h}
\function{f=\y0+\k*(x-\x0)}
\real{y1=evalue(\f,x=\x1)}
\statement{
   Donner une valeur approchée de \(f(\x1)) sachant que
<div class="wimscenter"> \(f(\x0)=\y0) et \(f'(\x0)=\tk).</div>
<div class="wimscenter"><label for="reply1">\(f(\x1) \simeq\)</label> \embed{reply1,5}</div>
}
\answer{valeur approchée}{\y1}{type=numeric}
#endif
#if (defined TARGET_approx3 || defined TARGET_approx4 || defined TARGET_approx5 )
\text{infg=\(-\infty)}
\text{infd=\(+\infty)}
\text{empt=\(\emptyset)}
\text{ptvirg=&#59;}

# if defined TARGET_approx3
\title{TITRE 3}
\text{data=randomrow(
1/(x+1)^2,randint(0,1),\(\RR \setminus) &#123;-1 &#125;
(x+1)^2,randint(-3..3),\(\RR)
),2}
# endif
# if defined TARGET_approx4
\title{TITRE 4}
\text{data=randomrow(
1/(x+1),random(randint(-3..-2),randint(0..3)),\(\RR \setminus) &#123;-1 &#125;
sin(x),0, \(\RR)
cos(x),0,\(\RR)
),1}
# endif
# if defined TARGET_approx5
\title{TITRE 5}
\text{data=randomrow(
sqrt(x+1),random(0,3,8,15), &#91;-1 \ptvirg \infd &#91;
1/sqrt(x+1),random(0,3,15), &#93;-1 \ptvirg \infd &#91;
),0.5}
# endif
\integer{cnt=rows(\data)}
\text{take=shuffle(\cnt)}
\text{data1=row(\take[1],\data)}
\text{f1=\data1[1]}

\integer{x0=\data1[2]}
\text{defdom=\data1[3]}
\real{epsilon=randitem(0.001,0.002,0.003,0.005,0.006,0.008,0.01,0.015,0.02,0.03,0.05)*random(1,-1)}
\real{minus=-(\epsilon)}
\real{plus1=1+\epsilon}
\real{minus1=1-\epsilon}
\real{plus2=2+\epsilon}
\real{minus2=2-\epsilon}
\text{interval=\epsilon>0?[0,\epsilon]:[\epsilon,0]}
\text{v1=wims(replace internal x+1 by \plus1 in \f1)}
\text{v1=wims(replace internal x+2 by \plus2 in \v1)}
\text{v1=wims(mathsubst x=\epsilon in \v1)}
\function{f=\f1}
\function{value=\v1}
\real{const=evalue(\f,x=\x0)}
\real{x1=\x0+(\epsilon)}
\function{deriv=diff(\f,x)}
\real{deriv0=evalue(\deriv,x=\x0)}
\real{approx=\deriv0*\epsilon +(\const)}

\statement{Soit la fonction \(f) définie sur \defdom par \(f(x)= \f).<br>
  Déterminer par approximation affine, une valeur approchée de \(f(\x1)).
<ol>
<li><label for="reply1">Donner l'expression de \(f'(x))&nbsp;:</label> \embed{reply1}</li>
<li>Puis calculer <label for="reply2">\(f'(\x0))&nbsp;:</label>\embed{reply2} et
  <label for="reply3">\(f(\x0))&nbsp;: </label>\embed{reply3}</li>
<li> En déduire
<label for="reply4">une valeur approchée de \(f(\x1))&nbsp;:</label> \embed{reply4}</li>
</ol>
}

\answer{Étape 1}{\deriv}{type=formal}
\answer{Étape 2}{\deriv0}{type=numeric}
\answer{Étape 3}{\const}{type=numeric}
\answer{Étape 4}{\approx}{type=numeric}

\hint{Une valeur approchée par approximation affine s'obtient par
<div class="wimscenter">\(f(x_0+h) \simeq f(x_0)+f'(x_0)h)</div>}
\solution{\(f(\x1) \simeq f(\x0) + f'(\x0)(\x1-(\x0)) \simeq \const + \deriv0 \times (\epsilon) \simeq \approx )}
#endif
