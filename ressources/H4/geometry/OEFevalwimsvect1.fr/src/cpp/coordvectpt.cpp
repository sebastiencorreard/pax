target=coordvecpt1 coordvecpt2 coordvecpt3 coordvecpt4 coordvecpt5
\language{fr}
\range{-5..5}
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{100}
#define TITLE Coordonnées de vecteurs / points
\integer{mid=4}
\integer{range=\mid*2}
\integer{a1=2*random(-\mid..\mid-2)+1}
\integer{b1=2*random(-\mid..\mid)}
\integer{a2=random(-\range..\range)}
\integer{b2=2*random(-\mid..\mid-2)+1}
\integer{a=random(2..\range)*random(-1,1)}
\integer{b=random(2..\range)*random(-1,1)}
\integer{xa=random(-\range..\range)}
\integer{ya=random(-\range..\range)}
\integer{xb=random(-\range..\range)}
\integer{yb=random(-\range..\range)}
\if{\xa=\xb and \ya=\yb}
 {
 \integer{xa=\xa+1}
 \integer{ya=\ya-2}
 }
#if (defined TARGET_coordvecpt2 || defined TARGET_coordvecpt5)
\rational{pente=4}
#else
\rational{pente=0}
#endif
\text{cadre=
  xrange -10,10
  yrange -10,10
  parallel -10-\pente/2,-10,-10+\pente/2,10,1,0,21,gray
  parallel -10,-10,10,-10,0,1,21,gray
}
\text{axes=
  linewidth 2
  arrow -10,0,10,0,10,black
  arrow 0-\pente/2,-10,0+\pente/2,10,10,black
  linewidth 3
  arrow 0,0,1,0,5,red
  arrow 0,0,\pente/20,1,5,red
  text red,0.2,-0.8,medium,i
  text red,-0.8,0.2,medium,j
  text red,-0.4,-0.4,medium,O
}
#if defined TARGET_coordvecpt1
 \title{TITLE I}
#endif
#if defined TARGET_coordvecpt2
 \title{TITLE II}
#endif
#if(defined TARGET_coordvecpt1 || defined TARGET_coordvecpt2)
\if{\a>0}{
   \integer{xb=random(-\range..\range-\a)}
 }{
   \integer{xb=random(-\range-(\a)..\range)}
 }
\if{\b>0}{
   \integer{yb=random(-\range..\range-\b)}
 }{
   \integer{yb=random(-\range-(\b)..\range)}
 }
 \rational{xbb=\xb+\yb*\pente/20}
 \rational{xbc=\xb+\a +(\yb+\b)*\pente/20}

 \text{cadre=\cadre
 \axes
 linewidth 5
 point \xa+\ya*\pente/20,\ya,orange
 linewidth 3
 text orange,\xa-0.5,\ya-0.5,medium,M
 arrow \xbb,\yb,\xbc,\yb+\b,10,green
 text green,\xbc-0.5,\yb+\b-0.5,medium,u
}
\text{rep=\xa,\ya}
\text{rep2=\a,\b}
\statement{
<div class="wims_columns">
<div class="medium_size">
\draw{400,400}{\cadre}
</div>
<div class="medium_size">
  On a placé sur le graphique ci-contre un point \(M) et un vecteur \(\vec{u}).
<p>
  Déterminer les coordonnées du point \(M) et du vecteur \(\vec{u}) dans le repère \((O,\vec{i},\vec{j})).
</p><ul>
  <li><label for="reply1">Coordonnées de \(M):</label> \embed{reply1,7}</li>
  <li><label for="reply2">Coordonnées de \(\vec{u}):</label> \embed{reply2,7}</li>
</ul>
</div>
</div>
<div class="wims_instruction">Séparer l'ordonnée de l'abscisse par une virgule</div>
}
\answer{Votre réponse}{\rep}{type=vector}
\answer{Votre réponse}{\rep2}{type=vector}
#endif
#if defined TARGET_coordvecpt3
 \title{TITLE III}
\integer{xa=random(-\mid..\mid)}
\integer{ya=random(-\mid..\mid)}
\integer{xb=random(\xa+1..\range)}
\integer{yb=random(\ya+1..\range)}
\integer{xc=random(-\range..\xa-1)}
\integer{yc=random(-\range..\ya-1)}
\text{pt=A,B,C}
\text{pt=shuffle(\pt)}
 \text{cadre=\cadre
 \axes
 linewidth 5
 points blue,\xa,\ya,\xb,\yb,\xc,\yc
 text blue,\xa-0.5,\ya-0.5,medium,\pt[1]
 text blue,\xb-0.5,\yb-0.5,medium,\pt[2]
 text blue,\xc-0.5,\yc-0.5,medium,\pt[3]
}
\integer{k=random(1,2)}
\if{\k=1}{
  \text{quest=\(\pt[1] \pt[2] \pt[3] D) est un parallélogramme}
  \integer{x=\xc+(\xa)-(\xb)}
  \integer{y=\yc+(\ya)-(\yb)}
  \text{rep=\x,\y}
  }
\if{\k=2}{
  \text{quest=\(\pt[1] \pt[2] D) est un triangle rectangle isocèle en \(\pt[1]\)}
  \integer{x1=\yb-(\ya)+\xa}
  \integer{y1=\xa-(\xb)+\ya}
  \integer{x2=\ya-(\yb)+\xa}
  \integer{y2=\xb-(\xa)+\ya}
 }
\statement{
<div class="wims_columns">
<div class="medium_size">
\draw{400,400}{\cadre}
</div>
<div class="medium_size">
  Dans le plan muni du repère \((O,\vec{i},\vec{j})), on a placé les points \(A\), \(B\) et \(C).
<p>
  Déterminer les coordonnées du point \(D) tel que:
</p>
<div class="wimscenter">
\quest.
</div>
<div class="wimscenter">
  <label for="reply1">Les coordonnées de \(D) sont:</label> (\embed{reply1,3};\embed{reply2,3})
</div>
</div>
</div>
}

\answer{Abscisse}{\X}{type=numeric}
\answer{Ordonnée}{\Y}{type=numeric}
\condition{Coordonnées de D}{(\k=1 and \X=\x and \Y=\y) or (\k=2 and ((\X=\x1 and \Y=\y1) or (\X=\x2 and \Y=\y2)))}
#endif
#if defined TARGET_coordvecpt4
 \title{TITLE IV}
\text{sb=\b>0?+}
\text{combi=\a \vec{u} \sb \b \vec{v}}
\integer{x=\xa*\a+\xb*\b}
\integer{y=\ya*\a+\yb*\b}
 \text{rep=\x,\y}

\statement{
  Dans une base \((\vec{i},\vec{j})) du plan, on considère les vecteurs
\(\vec{u})\(\left(\begin{array}{c} \xa \\ \ya \end{array}\right)) et
\(\vec{v})\(\left(\begin{array}{c} \xb \\ \yb \end{array}\right)).
<p>
  Calculer les coordonnées du vecteur \(\vec{w}) tel que:
</p>
<div class="wimscenter">\(\vec{w} = \combi ).
</div>
  <label for="reply1">Les coordonnées de \(\vec{w}) sont:</label> \embed{reply1,7}

<div class="wims_instruction">Séparer l'ordonnée de l'abscisse par une virgule.</div>
}

\answer{Votre réponse}{\rep}{type=vector}
#endif
#if defined TARGET_coordvecpt5
 \title{TITLE V}
\integer{xu=random(1..3)*random(1,-1)}
\integer{yu=0}
\integer{xv=0}
\integer{yv=\xu+random(1..2)}
\integer{yv=\yv=0?\xu-random(1..2)}
\integer{x=random(1..4)*random(1,-1)}
\integer{y=random(1..4)*random(1,-1)}
\integer{xw=\x*(\xu)+(\y)*(\xv)}
\integer{yw=\x*(\yu)+(\y)*(\yv)}
\if{\xw>0}{
   \integer{xa=random(-\range..\range-\xw)}
 }{
   \integer{xa=random(-\range-(\xw)..\range)}
 }
\if{\yw>0}{
   \integer{ya=random(-\range..\range-\yw)}
 }{
   \integer{ya=random(-\range-(\yw)..\range)}
 }
\text{cadre=\cadre
 linewidth 3
 arrow 0,0,\xu,\yu,10,red
 arrow 0,0,\yv*\pente/20,\yv,10,blue
 arrow \xa+\ya*\pente/20,\ya,\xa+\xw+(\ya+\yw)*\pente/20,\ya+\yw,10,green
 text red,\xu-0.5,\yu-0.5,large,u
 text blue,\xv-0.5,\yv-0.5,large,v
 text green,\xa+\xw-0.5,\ya+\yw-0.5,large,w
 }
\statement{
<div class="wims_columns">
<div class="medium_size">
\draw{400,400}{\cadre}
</div>
<div class="medium_size">
  On a placé sur le graphique ci-contre une base \((\vec{u},\vec{v})) et un vecteur
  <span class="nowrap">\(\vec{w}).</span>
<p>
  Exprimer le vecteur \(\vec{w}) en fonction des vecteurs \(\vec{u})
 et \(\vec{v}).
</p><div class="wimscenter">
\(\vec{w})= \embed{reply1,3}<label for="reply1">\(\vec{u})</label> +
  \embed{reply2,3}<label for="reply2">\(\vec{v})</label>
</div>
</div></div>
}
\answer{Première coordonnée}{\x}{type=numeric}
\answer{Deuxième coordonnée}{\y}{type=numeric}
#endif
