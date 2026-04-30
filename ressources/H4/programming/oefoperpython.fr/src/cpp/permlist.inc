\integer{n=randint(20..30)}
\text{list=shuffle(\n)} 

\text{l3p=(\alea==1)?tmp=liste[1]:tmp=liste[nn[2]]}
\text{bfp=(\alea==1)?for(x=1,nn[2]-1,liste[x]=liste[x+1]):forstep(x=nn[2],2,-1,liste[x]=liste[x-1])}
\text{l4p=(\alea==1)?liste[nn[2]]=tmp:liste[1]=tmp}
\text{DD=pari(liste=[\list];
nn=matsize(liste);
\l3p;
\bfp;
\l4p;)}
text{result=pari(print(nn[2]);)}
\text{result=[pari(print(liste);)]}

\text{code=
\#Initialisation des variables#
liste=[\list]
\###
\#Permutation des variables#
\###
\###
\###
\###
\#Fin de la permutation des variables#
\#Affichage du résultat#
\Affprint
\#Fin Affichage#}

\title{Permuter une liste}
\text{prob=Permutation circulaire d'une liste}

\text{lfle=(\alea==1)?\longleftarrow:\longrightarrow}
\text{lnalgo=\(\left \|
\begin{array}{c c c}
 tmp       & \lfle & list[0] \\\
 list[0]   & \lfle & list[1] \\\
 list[1]   & \lfle & list[2] \\\
    \vdots & \lfle & \vdots \\\
 list[i-1] & \lfle & list[i] \\\
    \vdots & \lfle & \vdots \\\
 list[n]   & \lfle & tmp    
\end{array}
\right.
\)}

\text{cfle=(\alea==1)?a->i->b->e->h->f->g->c->d->a:a->d->c->g->f->h->e->b->i->a}
\text{arbre= layout="circo";
bgcolor= grey90
  a [color=black,shape=box,style=rounded,label="list[0]"];
  b [color=black,shape=box,style=rounded,label="list[n]"];
  c [color=black,shape=box,style=rounded,label="list[2]"];
  d [color=black,shape=box,style=rounded,label="list[1]"];
  e [color=black,shape=box,style=rounded,label="..."];
  f [color=black,shape=box,style=rounded,label="list[i-1]"];
  g [color=black,shape=box,style=rounded,label="..."];
  h [color=black,shape=box,style=rounded,label="list[i]"];
  i [color=black,shape=box,style=rounded,label="tmp"];
  \cfle [color=black, arrowsize=2];}
\text{test=\arbre}

\text{arbre1 =slib(draw/graphviz digraph  { \test
},png dot url)}


\text{instruction=Écrire un script qui permet de réaliser une permutation circulaire des éléments
 d'une liste en utilisant une variable tampon.
<br> La liste suivante est donnée : \(list=\left [ \list \right] \)
<br> On souhaite permuter les éléments de la liste
 \(list[i]\) de cette liste \(list\). En langage naturel, on écrit :
 \lnalgo
 <br>Cette permutation circulaire est représentée par le schéma suivant :
 \arbre1}

\text{instruction_code=instruction=[n=len(liste),n=len(liste)-1,tmp=liste[0],liste[0]=tmp,tmp=liste[1],liste[1]=tmp,for i in range(n-1):,for i in range(n-1,0,-1):,for i in range(n-1,1,-1):,for i in range(n):,for i in range(n,0,-1):,for i in range(n,1,-1):,liste[i]=liste[i+1],liste[i+1]=liste[i],liste[i]=liste[i-1],liste[i-1]=liste[i],liste[n-1]=tmp,tmp=liste[n-1],liste[n]=tmp,tmp=liste[n],&#32;&#32;]}

n=len(liste)
tmp=liste[0]
for i in range(n-1):
  liste[i]=liste[i+1]
liste[n-1]=tmp
