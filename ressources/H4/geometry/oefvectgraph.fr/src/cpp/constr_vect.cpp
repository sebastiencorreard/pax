target=comblin difference representant somme somme3

\author{Paul,Byache}
\email{paul@byache.fr}
\language{fr}
\format{html}
\computeanswer{no}

*********************titre et premiers paramètres******************
#if defined TARGET_somme
\title{Somme de 2 vecteurs.}
**ordonnées de u et v
\integer{yu=random(-3,-2,-1,1,2,3)}
\integer{yv=random(-3,-2,-1,1,2,3)}
#endif

#if defined TARGET_representant
\title{Représentant de vecteur.}
**ordonnées de u
\integer{yu=random(-3,-2,-1,1,2,3)}
#endif

#if defined TARGET_difference
\title{Différence de 2 vecteurs.}
**ordonnées de u et v
\integer{yu=random(-3,-2,-1,1,2,3)}
\integer{yv=random(-3,-2,-1,1,2,3)}
#endif

#if defined TARGET_comblin
\title{Combinaison linéaire de 2 vecteurs.}
**ordonnées de u et v
\integer{yu=random(-3,-2,-1,1,2,3)}
\integer{yv=random(-3,-2,-1,1,2,3)}
#endif

#if defined TARGET_somme3
\title{Somme de 3 vecteurs.}
**ordonnées de u et v
\integer{yu=randint(-2,2)}
\integer{yv=randint(-2,2)}
**coord origine vecteur w
\integer{xw0=randint(5,6)}
\integer{yw0=randint(-1,1)}
**coord vecteur w
\integer{xw=random(-3,-2,-1,1,2,3)}
\integer{yw=randint(-2,2)}
#endif

*****************************code commun à tous*******************

**coord origine vecteur u
\integer{xu0=randint(-4,4)}
\integer{yu0=randint(-1,1)}
**coord vecteur u
\integer{xu=random(-3,-2,-1,1,2,3)}
**coord origine vecteur v
\integer{xv0=randint(-4,4)}
**pour ne ps que les deux vecteurs soient dessinés trop l'un sur l'autre :
\integer{xv0= abs(\xv0-\xu0)<4 ? -\xv0}
\integer{yv0=randint(-1,1)}
**coord vecteur v
\integer{xv=random(-3,-2,-1,1,2,3)}

******************dessin*************************

#if defined TARGET_somme
\text{canvas_code=xrange -10,10
  yrange -4,4
  opacity 255,255
  hline 0,0,black
  vline 0,0,black
  linewidth 2
  fontfamily 18px Arial
  arrow 0,0,1,0,6,#EE0700
  latex 0.3,0,\vec{i}
  arrow 0,0,0,1,6,#EE0700
  latex -0.5,0.7,\vec{j}
  arrow \xu0,\yu0,\xu0+\xu,\yu0+\yu,10,#EE0700
  latex \xu0+\xu/2-0.3,\yu0+\yu/2,\vec{u}
  arrow \xv0,\yv0,\xv0+\xv,\yv0+\yv,10,#EE0700
  latex \xv0+\xv/2-0.3,\yv0+\yv/2,\vec{v}
  point \xu0,\yu0,black
  point \xv0,\yv0,black
  precision 10
  opacity 155,155
  linewidth 1
  grid 1,1,grey
  snaptogrid
}

#endif

#if defined TARGET_representant
\text{canvas_code=xrange -10,10
  yrange -4,4
  opacity 255,255
  hline 0,0,black
  vline 0,0,black
  linewidth 2
  fontfamily 18px Arial
  arrow 0,0,1,0,6,#EE0700
  latex 0.3,0,\vec{i}
  arrow 0,0,0,1,6,#EE0700
  latex -0.5,0.7,\vec{j}
  arrow \xu0,\yu0,\xu0+\xu,\yu0+\yu,10,#EE0700
  latex \xu0+\xu/2-0.3,\yu0+\yu/2,\vec{u}
  point \xu0,\yu0,black
  precision 10
  opacity 155,155
  linewidth 1
  grid 1,1,grey
  snaptogrid
}
#endif

#if defined TARGET_difference
\text{canvas_code=xrange -10,10
  yrange -4,4
  opacity 255,255
  hline 0,0,black
  vline 0,0,black
  linewidth 2
  fontfamily 18px Arial
  arrow 0,0,1,0,6,#EE0700
  latex 0.3,0,\vec{i}
  arrow 0,0,0,1,6,#EE0700
  latex -0.5,0.7,\vec{j}
  arrow \xu0,\yu0,\xu0+\xu,\yu0+\yu,10,#EE0700
  latex \xu0+\xu/2-0.3,\yu0+\yu/2,\vec{u}
  arrow \xv0,\yv0,\xv0+\xv,\yv0+\yv,10,#EE0700
  latex \xv0+\xv/2-0.3,\yv0+\yv/2,\vec{v}
  point \xu0,\yu0,black
  point \xv0,\yv0,black
  precision 10
  opacity 155,155
  linewidth 1
  grid 1,1,grey
  snaptogrid
}
#endif

#if defined TARGET_comblin
**coeff comb lin
\real{a=random(-2,-1,1,2)/random(1,2)}
\real{b=random(1,2,3)/random(1,2)}
\real{a=\a=1 and (\b=1 or \b=-1) ? -0.5}
\text{cl=pari(\a*u+\b*v)}
\text{cl=wims(replace internal v by \vec{v} in \cl)}
\text{cl=wims(replace internal u by \vec{u} in \cl)}
\text{cl=wims(replace internal * by in \cl)}

\text{canvas_code=xrange -10,10
  yrange -6,6
  opacity 255,255
  hline 0,0,black
  vline 0,0,black
  linewidth 2
  fontfamily 18px Arial
  arrow 0,0,1,0,6,#EE0700
  latex 0.5,0,\vec{i}
  arrow 0,0,0,1,6,#EE0700
  latex -0.3,0.7,\vec{j}
  arrow \xu0,\yu0,\xu0+\xu,\yu0+\yu,10,#EE0700
  latex \xu0+\xu/2,\yu0+\yu/2,\vec{u}
  arrow \xv0,\yv0,\xv0+\xv,\yv0+\yv,10,#EE0700
  latex \xv0+\xv/2,\yv0+\yv/2,\vec{v}
  point \xu0,\yu0,black
  point \xv0,\yv0,black
  precision 10
  opacity 155,155
  linewidth 1
  parallel -10,-6,-10,6,1,0,21,grey
  parallel -10,-6,10,-6,0,1,13,grey
  opacity 0,0
  grid 0.5,0.5,white
  opacity 255,255
  linewidth 2
  snaptogrid
}

#endif

#if defined TARGET_somme3
\text{canvas_code=xrange -10,10
  yrange -4,4
  opacity 255,255
  hline 0,0,black
  vline 0,0,black
  linewidth 2
  fontfamily 18px Arial
  arrow 0,0,1,0,6,#EE0700
  latex 0.5,0,\vec{i}
  arrow 0,0,0,1,6,#EE0700
  latex -0.3,0.7,\vec{j}
  arrow \xu0,\yu0,\xu0+\xu,\yu0+\yu,10,#EE0700
  latex \xu0+\xu/2,\yu0+\yu/2,\vec{u}
  arrow \xv0,\yv0,\xv0+\xv,\yv0+\yv,10,#EE0700
  latex \xv0+\xv/2,\yv0+\yv/2,\vec{v}
  arrow \xw0,\yw0,\xw0+\xw,\yw0+\yw,10,#EE0700
  latex \xw0+\xw/2,\yw0+\yw/2,\vec{w}
  point \xu0,\yu0,black
  point \xv0,\yv0,black
  point \xw0,\yw0,black
  precision 10
  opacity 155,155
  linewidth 1
  grid 1,1,grey
  snaptogrid
}
#endif

******************solutions**************************************
\integer{yusol= \yu>0 ? 1 : 3}

#if defined TARGET_somme
\text{taille=500x200}
\integer{yvsol= \yv>0 ? -3 : -1}
\integer{xsol= (\xu+\xv)>0 ? 2 : 8}
\integer{ysol= (\yu+\yv)>0 ? -3 : 3}
\text{sol=wims(exec canvasdraw
  size 750,300
  xrange -15,15
  yrange -6,6
  opacity 155,155
  linewidth 1
  grid 1,1,grey
  opacity 255,255
  linewidth 2
  fontfamily 18px Arial
  arrow -5,\yusol,-5+\xu,\yusol+\yu,10,#EE0700
  latex -5+\xu/2-0.3,\yusol+\yu/2,\vec{u}
  arrow -5,\yvsol,-5+\xv,\yvsol+\yv,10,#EE0700
  latex -5+\xv/2-0.3,\yvsol+\yv/2,\vec{v}
  point -5,\yusol,black
  point -5,\yvsol,black
  arrow \xsol,\ysol,\xsol+\xu,\ysol+\yu,6,blue
  arrow \xsol+\xu,\ysol+\yu,\xsol+\xu+\xv,\ysol+\yu+\yv,6,blue
  arrow \xsol,\ysol,\xsol+\xu+\xv,\ysol+\yu+\yv,10,green
  latex \xsol+(\xu+\xv)/2,\ysol+(\yu+\yv)/2,\vec{u}+\vec{v}
  )}
\text{consigne=Dessiner un représentant de la somme \(\vec{u}+\vec{v}).}
\text{consigne2=Vous pouvez dessiner autant de vecteurs que vous voulez, mais seuls les trois premiers que vous
construisez seront analysés.<br>Si \(\vec{u}+\vec{v}) est le vecteur nul, cliquez deux fois au même endroit !}
#endif

#if defined TARGET_representant
\text{taille=500x200}
\integer{xsol= (\xu)>0 ? 2 : 8}
\integer{ysol= (\yu)>0 ? -3 : 3}
\text{sol=wims(exec canvasdraw
  size 500,200
  xrange -10,10
  yrange -4,4
  opacity 155,155
  linewidth 1
  grid 1,1,grey
  opacity 255,255
  linewidth 2
  fontfamily 18px Arial
  arrow -5,\yusol,-5+\xu,\yusol+\yu,10,#EE0700
  latex -5+\xu/2-0.3,\yusol+\yu/2,\vec{u}
  point -5,\yusol,black
  arrow \xsol,\ysol,\xsol+\xu,\ysol+\yu,10,green
  point \xsol,\ysol,black
  latex \xsol+(\xu)/2,\ysol+(\yu)/2,\vec{u}
  )}
\text{consigne=Dessiner un représentant du vecteur \(\vec{u}) à un autre endroit.}
\text{consigne2=Attention : si vous dessinez plus d'un vecteur, seul le premier que vous construisez sera analysé.}
#endif

#if defined TARGET_difference
\text{taille=500x200}
\integer{yvsol= \yv>0 ? -3 : -1}
\integer{xsol= (\xu-\xv)>0 ? 2 : 8}
\integer{ysol= (\yu-\yv)>0 ? -1 : 3}
\integer{xdecal= \yv=0 ? 0 : 2}
\integer{ydecal= \xdecal=0 ? 2 : 0}
\text{sol=wims(exec canvasdraw
  size 750,300
  xrange -15,15
  yrange -6,6
  opacity 155,155
  linewidth 1
  grid 1,1,grey
  opacity 255,255
  linewidth 2
  fontfamily 18px Arial
  arrow -5,\yusol,-5+\xu,\yusol+\yu,10,#EE0700
  latex -5+\xu/2-0.3,\yusol+\yu/2,\vec{u}
  arrow -5,\yvsol,-5+\xv,\yvsol+\yv,10,#EE0700
  latex -5+\xv/2-0.3,\yvsol+\yv/2,\vec{v}
  darrow -5+\xdecal+\xv,\yvsol+\ydecal+\yv,-5+\xdecal,\yvsol+\ydecal,10,blue
  latex -5+\xdecal+\xv/2-0.3,\yvsol+\ydecal+\yv/2,-\vec{v}
  point -5,\yusol,black
  point -5,\yvsol,black
  arrow \xsol,\ysol,\xsol+\xu,\ysol+\yu,6,blue
  arrow \xsol+\xu,\ysol+\yu,\xsol+\xu-\xv,\ysol+\yu-\yv,6,blue
  arrow \xsol,\ysol,\xsol+\xu-\xv,\ysol+\yu-\yv,10,green
  latex \xsol+(\xu-\xv)/2,\ysol+(\yu-\yv)/2,\vec{u}-\vec{v}
  )}
\text{consigne=Dessiner un représentant de la différence \(\vec{u}-\vec{v}).}
\text{consigne2=Vous pouvez dessiner autant de vecteurs que vous voulez, mais seuls les trois premiers que vous
construisez seront analysés.<br>Si \(\vec{u}-\vec{v}) est le vecteur nul, cliquez deux fois au même endroit !}

#endif

#if defined TARGET_comblin
\text{taille=500x300}
\integer{yvsol= \yv>0 ? -3 : -1}
\integer{xsol= (\a*\xu+\b*\xv)>0 ? 2 : 8}
\integer{ysol= (\a*\yu+\b*\yv)>0 ? -3 : 3}
\integer{xdecalu= \yu=0 ? 0 : 2}
\integer{ydecalu= \xdecalu=0 ? 2 : 0}
\integer{xdecalv= \yv=0 ? 0 : 2}
\integer{ydecalv= \xdecalv=0 ? 2 : 0}
\text{au= \a=1 ? :
  dashed
  darrow -5+\xdecalu,\yusol+\ydecalu,-5+\xdecalu+\a*\xu,\yusol+\ydecalu+\a*\yu,10,blue
  latex -5+\xdecalu+\a*\xu/2-0.3,\yusol+\ydecalu+\a*\yu/2,\a\vec{u}
}
\text{bv= \b=1 ? :
  dashed
  darrow -5+\xdecalv,\yvsol+\ydecalv,-5+\xdecalv+\b*\xv,\yvsol+\ydecalv+\b*\yv,10,blue
  latex -5+\xdecalv+\b*\xv/2-0.3,\yvsol+\ydecalv+\b*\yv/2,\b\vec{v}
}

\text{sol=wims(exec canvasdraw
  size 750,450
  xrange -15,15
  yrange -9,9
  opacity 155,155
  linewidth 1
  grid 1,1,grey
  opacity 255,255
  linewidth 2
  fontfamily 18px Arial
  arrow -5,\yusol,-5+\xu,\yusol+\yu,10,#EE0700
  latex -5+\xu/2-0.3,\yusol+\yu/2,\vec{u}
  arrow -5,\yvsol,-5+\xv,\yvsol+\yv,10,#EE0700
  latex -5+\xv/2-0.3,\yvsol+\yv/2,\vec{v}
  point -5,\yusol,black
  point -5,\yvsol,black
  \au \bv arrow \xsol,\ysol,\xsol+\a*\xu,\ysol+\a*\yu,6,blue
  arrow \xsol+\a*\xu,\ysol+\a*\yu,\xsol+\a*\xu+\b*\xv,\ysol+\a*\yu+\b*\yv,6,blue
  arrow \xsol,\ysol,\xsol+\a*\xu+\b*\xv,\ysol+\a*\yu+\b*\yv,10,green
  latex \xsol+(\a*\xu+\b*\xv)/2,\ysol+(\a*\yu+\b*\yv)/2,\cl
  )}

\text{consigne=Dessiner un représentant de \(\cl).}
\text{consigne2=Vous pouvez dessiner autant de vecteurs que vous voulez, mais seuls les trois premiers que vous
construisez seront analysés.<br>Si \(\cl) est le vecteur nul, cliquez deux fois au même endroit !}
#endif

#if defined TARGET_somme3
\text{taille=500x200}
\integer{yvsol= \yv>0 ? -3 : -1}
\integer{xsol= (\xu+\xv+\xw)>0 ? 2 : 8}
\integer{ysol= (\yu+\yv+\yw)>0 ? -3 : 3}
\text{sol=wims(exec canvasdraw
  size 500,300
  xrange -10,10
  yrange -6,6
  opacity 155,155
  linewidth 1
  grid 1,1,grey
  opacity 255,255
  linewidth 2
  fontfamily 18px Arial
  arrow -5,\yusol,-5+\xu,\yusol+\yu,10,#EE0700
  latex -5+\xu/2-0.3,\yusol+\yu/2,\vec{u}
  arrow -5,\yvsol,-5+\xv,\yvsol+\yv,10,#EE0700
  latex -5+\xv/2-0.3,\yvsol+\yv/2,\vec{v}
  arrow 0,0,\xw,\yw,10,#EE0700
  latex \xw/2-0.3,\yw/2,\vec{w}
  point -5,\yusol,black
  point 0,0,black
  arrow \xsol,\ysol,\xsol+\xu,\ysol+\yu,6,blue
  arrow \xsol+\xu,\ysol+\yu,\xsol+\xu+\xv,\ysol+\yu+\yv,6,blue
  arrow \xsol+\xu+\xv,\ysol+\yu+\yv,\xsol+\xu+\xv+\xw,\ysol+\yu+\yv+\yw,6,blue
  arrow \xsol,\ysol,\xsol+\xu+\xv+\xw,\ysol+\yu+\yv+\yw,10,green
  latex \xsol+(\xu+\xv+\xw)/2,\ysol+(\yu+\yv+\yw)/2,\vec{u}+\vec{v}+\vec{w}
  )}
\text{consigne=Dessiner un représentant de la somme \(\vec{u}+\vec{v}+\vec{w}).}
\text{consigne2=Vous pouvez dessiner autant de vecteurs que vous voulez, mais seuls les quatre premiers que vous
construisez seront analysés.<br>Si \(\vec{u}+\vec{v}+\vec{w}) est le vecteur nul, cliquez deux fois au même endroit !}
#endif

\statement{ \consigne <div class="wimscenter">
\embed{r1,\taille
arrows
[\canvas_code]}
</div>
<div class="wims_instruction">\consigne2</div>
}
\answer{}{\rep}{type=draw}

***********************************analyse de la réponse********************

\integer{cnt=wims(itemcnt \rep)}

#if defined TARGET_somme
\text{dernier=Le représentant qu'il fallait construire en dernier est en vert.}
\condition{La somme est-elle correctement construite (en utilisant au plus 3 vecteurs) ? }{(\rep[3]-\rep[1]=\xu+\xv and \rep[4]-\rep[2]=\yu+\yv and \cnt>3)
or (\rep[7]-\rep[5]=\xu+\xv and \rep[8]-\rep[6]=\yu+\yv and \cnt>7)
or (\rep[11]-\rep[9]=\xu+\xv and \rep[12]-\rep[10]=\yu+\yv and \cnt>11) and \cnt<13}
\feedback{\cnt >12}{Attention, vous avez construit trop de vecteurs. Certains n'ont pas été analysés !}
#endif

#if defined TARGET_representant
\condition{Un vecteur égal à \(\vec{u}) mais à partir d'une origine différente est-il construit ? }{\rep[3]-\rep[1]=\xu and \rep[4]-\rep[2]=\yu and ( \rep[1] != \xu0 or \rep[2] != \yu0 )}
#endif

#if defined TARGET_difference
\text{dernier=Le représentant qu'il fallait construire en dernier est en vert.}
\condition{La différence est-elle correctement construite (en utilisant au plus 3 vecteurs) ? }{(\rep[3]-\rep[1]=\xu-\xv and \rep[4]-\rep[2]=\yu-\yv)
or (\rep[7]-\rep[5]=\xu-\xv and \rep[8]-\rep[6]=\yu-\yv)
or (\rep[11]-\rep[9]=\xu-\xv and \rep[12]-\rep[10]=\yu-\yv) and \cnt<13}
#endif

#if defined TARGET_comblin
\text{dernier=Le représentant qu'il fallait construire en dernier est en vert.}
\condition{La combinaison linéaire est-elle correctement construite (en utilisant au plus 3 vecteurs) ? }{(\rep[3]-\rep[1]=\a*\xu+\b*\xv and \rep[4]-\rep[2]=\a*\yu+\b*\yv)
or (\rep[7]-\rep[5]=\a*\xu+\b*\xv and \rep[8]-\rep[6]=\a*\yu+\b*\yv)
or (\rep[11]-\rep[9]=\a*\xu+\b*\xv and \rep[12]-\rep[10]=\a*\yu+\b*\yv) and \cnt<13}
#endif

#if defined TARGET_somme3
\text{dernier=Le représentant qu'il fallait construire en dernier est en vert.}
\condition{La somme est-elle correctement construite (en utilisant au plus 4 vecteurs) ? }{((\rep[3]-\rep[1]=\xu+\xv+\xw and \rep[4]-\rep[2]=\yu+\yv+\yw)
or (\rep[7]-\rep[5]=\xu+\xv+\xw and \rep[8]-\rep[6]=\yu+\yv+\yw)
or (\rep[11]-\rep[9]=\xu+\xv+\xw and \rep[12]-\rep[10]=\yu+\yv+\yw)
or (\rep[15]-\rep[13]=\xu+\xv+\xw and \rep[16]-\rep[14]=\yu+\yv+\yw)) and \cnt<17}
#endif


\solution{Voici ci-dessous une construction possible. \dernier <br>
\sol}
