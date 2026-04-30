target=distvalabs1 distvalabs2 distvalabs3 distvalabs4 distvalabs5
\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{100}
#define TITRE Valeur absolue et distance
%%%% on place 3 points O,B ,C,
\integer{a=random(1..10)* random(1,-1)}
\integer{b=random(1..10)* random(1,-1)}
\integer{b=\b=\a?\b+2}
\integer{c=random(1..10)*random(1,-1)}



Choix parametre rationnel ou entier
\integer{choix=random(1,2)}

\rational{d=\choix=1?random(-1,-2,2):random(-1,-2,-3,2,3)/\b}
On ne veut pas d=1
\rational{d=\d=1?2}

#if defined TARGET_distvalabs1
 \title{TITRE I}
\integer{k=random(1,2)}
\integer{b=\b<0?-1*\b}
\integer{b=(\a=\b or \a=-\b)?2*\b}
\text{intro=Traduire mathématiquement avec une valeur absolue,Choisir la phrase qui traduit l'égalité}
\text{tintro=\intro[\k]}
\text{lstquest=Sur une droite graduée&#44; la distance du point \(M\) d'abscisse \(x\) au point \(A\) d'abscisse \(\a\) vaut \(\b\),
  Sur une droite graduée&#44; la distance du point \(M\) d'abscisse \(x\) au point \(A\) d'abscisse \(-\a\) vaut \(\b\),
  Sur une droite graduée&#44; la distance du point \(M\) d'abscisse \(x\) au point \(A\) d'abscisse \(\b\) vaut \(\a\),
\(abs(x-(\a))=\b\),\(abs(x-(\b))=\a\),\(abs(x+(\a))=\b\)}

\if{\k=1}
 {
  \text{quest=\lstquest[1]}
  \text{listrep=item(4..6,\lstquest)}
 }
 {
  \text{quest=\lstquest[4]}
  \text{listrep=item(1..3,\lstquest)}
 }
\integer{goodrep=1}
\statement{
\tintro&nbsp;:
<div class="wimscenter">\quest</div>
<ul><li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
</ul>
}
\answer{traduction}{\goodrep;\listrep}{type=radio}{option=shuffle}
#endif

#if defined TARGET_distvalabs2
 \title{TITRE II}
%%%% text{image= draw(806,100)}
\text{image=xrange -13,13
  yrange -2,2
  hline 0,0,red
  parallel -12,-0.2,-12,0.2,1,0,2,blue
  parallel -10,-0.4,-10,0.4,5,0,5,blue
  parallel -9,-0.2,-9,0.2,1,0,4,blue
  parallel -4,-0.2,-4,0.2,1,0,4,blue
  parallel 1,-0.2,1,0.2,1,0,4,blue
  parallel 6,-0.2,6,0.2,1,0,4,blue
  parallel 11,-0.2,11,0.2,1,0,2,blue
  text red,-0.1,1,medium,O
  text red,\b-0.1,1,medium,B
  text red,\c-0.1,1,medium,C
  text red,-0.1,-0.75,medium,0
  text red,\b-0.1,-0.75,medium,\b
  text red,\c-0.1,-0.75,medium,\c
  segment \b,-0.2,\b,0.2,red
  segment \c,-0.2,\c,0.2,red
  }

%%%% preparation de la réponse
\text{eqb=texmath(x-(\b)),texmath(\b-x), texmath(-x+(\b)), texmath(-(\b)+x)}
\text{eqc=texmath(x-(\c)),texmath(\c-x),texmath(-(\c)+x),texmath(-x+(\c))}

\statement{Soit M le point d'abscisse \(x\) sur la droite graduée d'origine O.
<div class="wimscenter">
\draw{800,64}{\image}
</div>
  Donner l'expression de la distance de M à B puis de C à M, à l'aide d'une valeur absolue.
<div class="wimscenter"><label for="reply1">d(\(x\),\b) =</label> &#124; \embed{r1,5}&#124;<br>
<label for="reply2">d(\c,\(x\)) = </label>&#124; \embed{r2,5}&#124;<br>
</div>
 }
\answer{dxa}{\eqbt}{}
\answer{dxb}{\eqct}{}
\condition{d(x,\b) bonne réponse }{texmath(\eqbt) isitemof \eqb}
\condition{d(\c,x) bonne réponse }{texmath(\eqct) isitemof \eqc}

#endif


#if defined TARGET_distvalabs3
 \title{TITRE III}

%%%% borne pour le rayon ##
\integer{rayonmax=20}
%%%% borne pour le centre ##
\integer{centremax=10}

%%%% Choix des bornes ##
\integer{sing1=random(1..\centremax)*randint(1,-1)}
\integer{sing2=random(1..\rayonmax)}
\text{eqx=\(abs(texmath(x-(\sing1)))) = \sing2 }

\statement{
  Traduire par une distance l'équation <span class="nowrap">\eqx.</span>
<div class="wimscenter"><label for="reply1">d(\(x\),</label>\embed{reply1,3})<label for="reply2">=</label>\embed{reply2,3}</div>
}
\answer{}{\sing1}{type=numeric}
\answer{}{\sing2}{type=numeric}
#endif


#if defined TARGET_distvalabs4
 \title{TITRE IV}
\integer{c=\c<0?-1*\c}
\integer{d=abs(\b-(\a))}
\text{data=le point \(M\) d'abscisse \(x\) est à égale distance des points \(A\) d'abscisse \(\a\) et \(B\) d'abscisse \(\b\),abs(x-(\a))=abs(x-(\b)),\(M A = M B\),\(\mathrm{d}(x,\a)=\mathrm{d}(x,\b)\)
  la distance du point \(M\) d'abscisse \(x\) au point \(B\) d'abscisse \(\b\) vaut \(\c\),abs(x-(\b))=\c,\(M B = \c\),\(\mathrm{d}(x,\b)=\c\)
  la distance du point \(M\) d'abscisse \(x\) au point \(B\) d'abscisse \(\b\) est le double de la distance de \(M\) à \(A\) d'abscisse \(\a\),abs(x-(\b))=2*abs(x-(\a)),\(M B = 2  M A\),\(\mathrm{d}(x,\b)=2 \times \mathrm{d}(x,\a)\)
  le point \(M\) d'abscisse \(x\) est le milieu du segment \([AB]\),abs(x-(\a))=abs(x-(\b)),\(M A = M B\),\(\mathrm{d}(x,\a)=\mathrm{d}(x,\b)\)
  le point \(M\) d'abscisse \(x\) est le symétrique du point \(A\) d'abscisse \(\a\) par rapport au point \(B\) d'abscisse \(\b\),abs(x-(\b))=abs(\b-\a),\(M B = B A\),\(\mathrm{d}(x,\b)=\mathrm{d}(\b,\a)\),\(abs(x-(\b))=\d\)}
\text{cedata=randomrow(\data)}
\integer{nbitem=wims(itemcnt \cedata)}
\text{quest=\cedata[1]}
\text{goodrep=\cedata[2]}

\statement{
  Les points \(M,A\) et \(B\) sont trois points d'une droite graduée repérés par leurs abscisses respectives \(x,\a\) et <span class="nowrap">\(\b\).</span>
<p>
  Traduire par une égalité avec une ou des valeurs absolues que&nbsp;:
</p>
<div class="wimscenter">\quest</div>
<div class="wims_instruction"> Écrire "abs(x-2)" pour \(abs(x-2)\)</div>
<div class="wimscenter"><label for="reply1">Égalité&nbsp;:</label> \embed{reply1}</div>
}
\answer{}{\goodrep}{type=equation}

\solution{
Avec les données de l'exercice, <strong>\quest</strong> se traduit par&nbsp;:<br>
\cedata[3] <br>
\cedata[4] <br>
\(\goodrep\)
\if{\nbitem=5}{<br>\cedata[5]}
}
#endif

#if defined TARGET_distvalabs5
 \title{TITRE V}
\text{taille=40x100x100}
\text{donnees=slib(draw/repere 800,30,10,-12,12,-1,0,1,0,black,white)}

\text{tmp=row(1,\donnees)}
#coordonnéées de l'origine du repère
\integer{Ox=item(1,\tmp)}
\integer{Oy=item(2,\tmp)}

\text{tmp=row(2,\donnees)}
%%%%échelle des axes
\integer{ex=item(1,\tmp)}
\integer{ey=item(2,\tmp)}

\integer{Ox=0}
\integer{ex=1}

%%%% On prépare le dessin
\text{image=xrange -16,16
  yrange -3,3
  hline 0,0,red
  arrow 15,0,16,0,15,red
  parallel -15,-0.2,-15,0.2,1,0,5,blue
  parallel -10,-0.4,-10,0.4,5,0,5,blue
  parallel -9,-0.2,-9,0.2,1,0,4,blue
  parallel -4,-0.2,-4,0.2,1,0,4,blue
  parallel 1,-0.2,1,0.2,1,0,4,blue
  parallel 6,-0.2,6,0.2,1,0,4,blue
  parallel 11,-0.2,11,0.2,1,0,5,blue
  text red,-0.1,1.5,medium,O
}

\integer{xmin=-15}
\integer{xoffset=4}
\text{pt=A,B,C,D,E,F}
\integer{nbpt=items(\pt)}
\integer{pty=\Oy}
\text{listx=}
\text{listpt=}
\text{listquest=}
\text{listrep=}
\text{indlist=shuffle(\nbpt)}


%%%% on choisit les points et on les met sur le dessin
\for{i=1 to \nbpt/2}
{
\integer{x=random(\xmin+(\i-1)*\xoffset .. \xmin+\i*\xoffset-1)}
\integer{x2=-1*(\x)}
\integer{ptx=\Ox+\x*\ex}
\integer{ptx2=\Ox+\x2*\ex}
\text{image=\image
 text red,\ptx-0.1,1.5,medium,\pt[\indlist[\i]]
 text red,\ptx-0.1,-1,medium,\x
 segment \ptx,-0.2,\ptx,0.2,red
 text red,\ptx2-0.1,1.5,medium,\pt[\indlist[\i+\nbpt/2]]
 text red,\ptx2-0.1,-1,medium,\x2
 segment \ptx2,-0.2,\ptx2,0.2,red
}
\text{listx=wims(append item \x to \listx)}
\text{listpt=wims(append item \ptx to \listpt)}
\text{questxlist=\(texmath(abs(x-(\x)))\),\(texmath(abs((\x)-x))\),\(texmath(abs(-x+(\x)))\),\(texmath(abs(-(\x)+x))\)}
\text{questx=randomitem(\questxlist)}
\text{listquest=wims(append item \questx to \listquest)}
\text{repx=M\pt[\indlist[\i]],\pt[\indlist[\i]]M}
\text{listrep=wims(append item randomitem(\repx) to \listrep)}

\text{listx=wims(append item \x2 to \listx)}
\text{listpt=wims(append item \ptx2 to \listpt)}
\text{questxlist=\(texmath(abs(x-(\x2)))\),\(texmath(abs((\x2)-x))\),\(texmath(abs(-x+(\x2)))\),\(texmath(abs(-(\x2)+x))\)}
\text{questx=randomitem(\questxlist)}
\text{listquest=wims(append item \questx to \listquest)}
\text{repx=M\pt[\indlist[\i+\nbpt/2]],\pt[\indlist[\i+\nbpt/2]]M}
\text{listrep=wims(append item randomitem(\repx) to \listrep)}
}


\statement{
  Soit M le point d'abscisse \(x\) sur la droite graduée d'origine O.
<div class="wimscenter">
\draw{800,64}{\image}
</div>
  Associer les valeurs absolues aux distances auxquelles elle correspondent.
<div class="wimscenter">\embed{reply 1,\taille}
</div>
 }
\answer{Correspondance objet/equation}{\listrep;\listquest}{type=correspond}
#endif
