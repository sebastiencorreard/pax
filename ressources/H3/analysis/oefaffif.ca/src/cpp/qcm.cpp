target= qcmequa,qcmfonct

\language{fr}
\range{-5..5}
\author{Guerimand Fabrice}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{10000}

\integer{a=random(-1,1)*random(2..5)}
\integer{b=random(-1,1)*random(2..3)}
\integer{b=\b=\a?6}
\integer{oa=-\a}
\integer{ob=-\b}
\text{A=\a<0?\a:+\a}
\text{B=\b<0?\b:+\b}
\text{OA=\oa<0?\oa:+\oa}
\text{OB=\ob<0?\ob:+\ob}

#if #TARGET(qcmfonct)
\title{Quelle est la fonction ?}
\text{good=\(f:x\mapsto \a x\B)}
\text{bad=\(f:x\mapsto \b x\A),\(f:x\mapsto \oa x\B),\(f:x\mapsto \oa x\OB),\(f:x\mapsto \a x\OB),\(f:x\mapsto \b x\OA)}
\text{question=Quelle est la fonction f dont la représentation graphique est ci-dessous}
\text{nom=f(x)}
#endif

#if #TARGET(qcmequa)
\title{Quelle est l'équation ?}
\text{good=\(y= \a x\B)}
\text{bad=\(y= \b x\A),\(y= \oa x\B),\(y= \oa x\OB),\(y= \a x\OB),\(y= \b x\OA)}
\text{question=Quelle est l'équation de la droite suivante}
\text{nom=y}
#endif

\function{dg=-(\a*(x)+(\b))*30+150}
\integer{pt1=evalue(\dg,x=-5)}
\integer{pt2=evalue(\dg,x=5)}
\text{dessin=wims(record 2 of src/graph.don)}
\text{dessin=\dessin
line 0,\pt1,300,\pt2,red
text black,290,150,medium,x
text black,155,2,medium,\nom}

\statement{\question ?
<center>
\draw{301,301}{\dessin}
</center>}

\choice{Réponse}{\good}{\bad}
