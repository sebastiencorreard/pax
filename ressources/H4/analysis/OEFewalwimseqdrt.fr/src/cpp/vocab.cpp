target=vocab1 vocab2 vocab3 vocab4 vocab5
#include "author.inc"
#define TITRE Vocabulaire et équations de droites
\keywords{line, line_equation}
#if defined TARGET_vocab1
\title{TITRE I}
\integer{a=random(1..9)*randint(1,-1)}
\integer{b=random(1..9)*randint(1,-1)}
\integer{b=\b=\a?-1*\b}
\text{data=La droite \(D\) d'équation \(texmath(y=\a* x+\b)) est la représentation graphique d'une fonction affine,1
  La droite \(D\) d'équation \(texmath(y=\a* x+\b)) est la représentation graphique d'une fonction linéaire,2
  La droite \(D\) d'équation \(texmath(y=\a* x+\b)) est la représentation graphique d'une fonction constante,2
  La droite \(D\) d'équation \(texmath(y=\a* x)) est la représentation graphique d'une fonction linéaire,1
  La droite \(D\) d'équation \(texmath(y=\a* x)) est la représentation graphique d'une fonction constante,2
  La droite \(D\) d'équation \(texmath(y=\b)) est la représentation graphique d'une fonction constante,1
  La droite \(D\) d'équation \(texmath(y=\b)) est la représentation graphique d'une fonction linéaire,2
  La droite \(D\) d'équation \(texmath(y=\b)) est parallèle à l'axe des ordonnées,2
  La droite \(D\) d'équation \(texmath(y=\b)) est parallèle à l'axe des abscisses,1
  La droite \(D\) d'équation \(texmath(x=\b)) est la représentation graphique d'une fonction affine,2
  La droite \(D\) d'équation \(texmath(x=\b)) est la représentation graphique d'une fonction linéaire,2
  La droite \(D\) d'équation \(texmath(x=\b)) est la représentation graphique d'une fonction constante,2
  La droite \(D\) d'équation \(texmath(x=\b)) n'est la représentation graphique d'aucune fonction,1}
\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}
\integer{rep=\cedata[2]}
#endif
#if defined TARGET_vocab2
\title{TITRE II}
\integer{a=random(1..9)*randint(1,-1)}
\integer{b=random(1..9)*randint(1,-1)}
\integer{b=\b=\a?-1*\b}
\text{data=La droite \(D\) d'équation \(texmath(y=\a* x+\b)) a pour coefficient directeur \a,1
  La droite \(D\) d'équation \(texmath(y=\a* x+\b)) a pour coefficient directeur \b,2
  La droite \(D\) d'équation \(texmath(y=\a* x+\b)) a pour ordonnée à l'origine \a,2
  La droite \(D\) d'équation \(texmath(y=\a* x+\b)) a pour ordonnée à l'origine \b,1
  La droite \(D\) d'équation \(texmath(x=\b)) a pour ordonnée à l'origine \b,2
  La droite \(D\) d'équation \(texmath(x=\b)) a pour coefficient directeur \b,2
  La droite \(D\) d'équation \(texmath(x=\b)) n'a ni coefficient directeur ni ordonnée à l'origine,1
  Deux droites se coupant sur l'axe des ordonnées ont même coefficent directeur,2
  Deux droites parallèles ont même coefficent directeur,1
  Deux droites parallèles ont même ordonnée à l'origine,2
}
\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}
\integer{rep=\cedata[2]}
#endif

#if defined TARGET_vocab3
\title{TITRE III}
\integer{a=random(2..9)*randint(1,-1)}
\integer{b=random(2..9)*randint(1,-1)}
\integer{b=\b=\a?-1*\b}
\text{data=La droite \(D\) d'équation \(texmath(y=\a* x+\b)) a pour vecteur directeur (1&#44;\a),1
  La droite \(D\) d'équation \(texmath(y=\a* x+\b)) a pour vecteur directeur (1&#44;\b),2
  La droite \(D\) d'équation \(texmath(y=\a* x+\b)) a pour vecteur directeur (\a&#44;1),2
  La droite \(D\) d'équation \(texmath(x=\b)) n'a pas de vecteur directeur,2
  La droite \(D\) d'équation \(texmath(x=\b)) a pour vecteur directeur (1&#44;0),2
  La droite \(D\) d'équation \(texmath(x=\b)) a pour vecteur directeur (0&#44;1),1
  La droite \(D\) d'équation \(texmath(y=\b)) n'a pas de vecteur directeur,2
  La droite \(D\) d'équation \(texmath(y=\b)) a pour vecteur directeur (1&#44;0),1
  La droite \(D\) d'équation \(texmath(y=\b)) a pour vecteur directeur (0&#44;1),2
  Deux droites se coupant sur l'axe des ordonnées ont même vecteur directeur,2
  Deux droites parallèles ont même vecteur directeur,1
}
\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}
\integer{rep=\cedata[2]}
#endif

#if defined TARGET_vocab4
\title{TITRE IV}
\integer{a=random(1..9)*randint(1,-1)}
\integer{b=random(1..9)*randint(1,-1)}
\text{data=Si P et Q sont deux points de la droite D&#44; alors le vecteur \(\overrightarrow{PQ}) est un vecteur directeur de D,1
  Si \(P(x_P&#44;y_P)) et \(Q(x_Q&#44;y_Q)) sont deux points de la droite \(D\) non parallèle à \((Oy))&#44;  alors le coefficient directeur  de \(D\) est le rapport \(\frac{y_P-y_Q}{x_P-x_Q}),1
  Si \(P(x_P&#44;y_P)) et \(Q(x_Q&#44;y_Q)) sont deux points de la droite \(D\) non parallèle à \((Oy))&#44;  alors le coefficient directeur  de \(D\) est le rapport \(\frac{y_Q-y_P}{x_P-x_Q}),2
  Si \(P(x_P&#44;y_P)) et \(Q(x_Q&#44;y_Q)) sont deux points de la droite \(D\) non parallèle à \((Oy))&#44;  alors le coefficient directeur  de \(D\) est le rapport \(\frac{x_P-x_Q}{y_P-y_Q}),2
  Si \(P(x_P&#44;y_P)) et \(Q(x_Q&#44;y_Q)) sont deux points de la droite \(D\) non parallèle à \((Oy))&#44;  alors l'ordonnée à l'origine de \(D\) est le rapport \(\frac{y_P-y_Q}{x_P-x_Q}),2
  Pour tous points \(P(x_P&#44;y_P)) et \(Q(x_Q&#44;y_Q)) de la droite \(D\) non parallèle à \((Oy))&#44;  le rapport \(\frac{y_P-y_Q}{x_P-x_Q}) est constant,1
  Si \(D\) est une droite passant par les points \(M(0&#44;\b)) et \(N(1&#44;\a))&#44; alors l'ordonnée à l'origine de \(D\) est \b,1
  Si \(D\) est une droite passant par les points \(M(0&#44;\b)) et \(N(1&#44;\a))&#44; alors l'ordonnée à l'origine de \(D\) est \a,2
}
\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}
\integer{rep=\cedata[2]}
#endif

#if defined TARGET_vocab5
\title{TITRE V}
\integer{a=random(1..9)*randint(1,-1)}
\integer{b=random(1..9)*randint(1,-1)}
#endif
#if defined TARGET_vocab5
\integer{k=randint(1,2)}
\if{\k=1}
 {\text{eq=\(texmath(y= \a*x + \b))}}
 {\text{eq=\(texmath(y= \b + \a*x ))}}
\statement{
  Déterminer le coefficient directeur et l'ordonnée à l'origine de la droite \(D\) d'équation.
<div class="wimscenter">\eq</div>
<ol>
<li>Coefficient directeur : \embed{reply1,3}</li>
<li>Ordonnée à l'origine : \embed{reply2,3}</li>
</ol>
}
\answer{ Coefficient directeur }{\a}{type=numeric}
\answer{ Ordonnée à l'origine }{\b}{type=numeric}
#else
\statement{
  Cocher la bonne réponse :
<div class="wimscenter">\quest.</div>
<div class="wimscenter">\embed{reply1}</div>
}
\answer{}{\rep;Vrai,Faux}{type=radio}
#endif
