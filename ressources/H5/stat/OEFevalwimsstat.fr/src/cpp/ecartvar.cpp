target=ecartvar1 ecartvar2 ecartvar3 ecartvar4 ecartvar5
#include "author.inc"
#include "lang_titles.inc"
\precision{1000}

\integer{range=random(20..100)}
\integer{xmin=randint(0..\range)}
\integer{parite=random(1,2)}
\integer{parite=2}
\integer{nbval=2*randint(3,4)+\parite}
#if defined TARGET_ecartvar1
\integer{xmin=2}
#endif
#if defined TARGET_ecartvar3
\integer{xmin=300}
\integer{nbval=14}
#endif
%% generation des effectifs
\integer{efftotal=randint(100,200,400,500)}
#include "lsteff.inc"
\text{listval=}
\integer{val=\xmin}
\text{xlistval=}
\text{lsth=}
\integer{Smin=0}
\integer{Smax=0}
\integer{var=0}
\integer{varh=0}
\text{xlistval=wims(append item \val to \xlistval)}
\for{i=1 to \nbval}{
  \integer{eff=\lsteff[\i]}
  \integer{Smin=\Smin+\eff*\val}
  \integer{var=\var+\eff*\val^2}
  \integer{largeur=random(1,2,4)}
  \integer{val = \val+\largeur*10}
#if defined TARGET_ecartvar1
  \integer{val = \xmin+\i}
#endif
#if defined TARGET_ecartvar3
  \real{varh=\varh+\eff*(\xmin+\i*5-2.5)^2}
  \integer{val = \xmin+\i*5}
  \integer{largeur=1}
#endif
  \integer{Smax=\Smax+\eff*\val}
  \text{xlistval=wims(append item \val to \xlistval)}
  \real{high=\eff / \largeur}
  \text{lsth=wims(append item \high to \lsth)}
}
\text{lstht=wims(listuniq \lsth)}
\text{lstht=wims(sort numeric list \lstht)}
\integer{nblstht=items(\lstht)}
\integer{hmax=\lstht[\nblstht]}
\rational{ig=\Smin/\efftotal}
\rational{id=\Smax/\efftotal}
\rational{moyh=(\ig+\id)/2}
\text{lstefft=wims(listuniq \lsteff)}
\text{lstefft=wims(sort numeric list \lstefft)}
\integer{nbefft=items(\lstefft)}
\integer{effmax=\lstefft[\nbefft]}
\real{moy=\Smin/\efftotal}
\rational{var=\var / \efftotal - (\moy)^2}
\rational{varh=\varh / \efftotal - (\moyh)^2}
\real{sig=sqrt(\var)}
\real{sigh=sqrt(\varh)}
\real{moy=round(\Smin*100/\efftotal)/100}
\real{moyh=round(\moyh*100)/100}
\real{varh=round(\varh*100)/100}
\real{var=round(\var*100)/100}
\real{sig=round(\sig*100)/100}
\real{sigh=round(\sigh*100)/100}
#if defined TARGET_ecartvar4
\text{table=<table class="wimscenter wimsborder">
<caption>Répartition</caption>}

\integer{nn=ceil(\nbval/10)}
\for{i=0 to \nn-1}{
  \text{table=\table <tr>}
  \for{j=1 to 10}{
    \text{a=item(\i*10+\j,\slistval)}
    \text{table=\table <td> \a </td>}
  }
  \text{table=\table </tr>}
}
\text{table=\table </table>}
#endif

\integer{xmin=\xlistval[1]}
\integer{xmax=\xlistval[\nbval+1]}

#if defined TARGET_ecartvar1
\integer{depeff=0}
\for{i=1 to \nbval}{
  \integer{depeff=abs(\xlistval[\i]-\moy)>\sig?\depeff+\lsteff[\i]}
}
\real{pctdep=round(\depeff*100/\efftotal)}
\real{cm=(\xlistval[1]+\xlistval[\nbval])/2}
\integer{rv=\cm>\moy?2:1}
\integer{rv=\cm=\moy?3}
\statement{<p>
Dans un journal, on a comptabilisé le nombre de lignes de chaque petite annonce.<br>
 On a obtenu le tableau de répartition suivant :
</p>
<table class="wimscenter wimsborder"><tr>
<th> Nombre de lignes</th>
\for{j=1 to \nbval}{
  <td>\xlistval[\j]</td>
}
</tr><tr>
<th>Nombre d'annonces</th>
\for{j=1 to \nbval}{
  <td>\lsteff[\j]</td>
}
</tr></table>
<p>
Calculer la moyenne et l'écart-type de la série, arrondis à 0.01 près.
</p>
<ul><li><label for="reply1">Moyenne =</label> \embed{reply1,5}</li>
<li><label for="reply2">Écart-type =</label> \embed{reply2,5}</li>
</ul>
<p>
Quel est le pourcentage d'annonces dont le nombre de lignes présente
 un écart avec la moyenne supérieur à l'écart-type ?<br>
<i>Arrondir à l'unité</i>
</p>
<div class="wimscenter">
<label for="reply3">Pourcentage d'annonces =</label> \embed{reply3,5} %</div>
<p>
Comment varie la moyenne si on retire une annonce de \xlistval[1] lignes
et une annonce de \xlistval[\nbval] lignes ?
</p>
<div class="wimscenter"><label for="reply4">la moyenne</label> \embed{reply4,5}</div>
}
\answer{Moyenne}{\moy}{type=numeric}
\answer{Écart-type}{\sig}{type=numeric}
\answer{pct annonce}{\pctdep}{type=numeric}
\answer{sensibilité aux valeurs extrêmes}{\rv;augmente,diminue,reste inchangée}{type=radio}
#endif
#if defined TARGET_ecartvar2
\text{image=
 xrange \xmin-15,\xmax+5
 yrange -10,\effmax+5
 arrow \xmin-5,0,\xmax+5,0,10,black
 arrow \xmin-5,-5,\xmin-5,\effmax+5,10,black
 segment \xlistval[1],0,\xlistval[1],\lsteff[1],blue
dsegment \xmin-5,\lsteff[1],\xlistval[1],\lsteff[1],orange
text black,\xlistval[1],-5,medium,\xlistval[1]
}
\integer{xoff=12}
\integer{yoff=5}
\for{i=2 to \nbval}{
 \integer{xoff=\xoff=12?7:12}
 \integer{yoff=\yoff=3?5:3}
 \text{image=\image
 segment \xlistval[\i],0,\xlistval[\i],\lsteff[\i],blue
 dsegment \xmin-5,\lsteff[\i],\xlistval[\i],\lsteff[\i],orange
 text black,\xlistval[\i],-\yoff,medium,\xlistval[\i]}
}
\real{xoff=12}
\for{i=1 to \nbefft}{
  \integer{xoff=\xoff=12?7:12}
  \text{image=\image
 text black,\xmin-\xoff,\lstefft[\i],medium,\lstefft[\i]}
}
\statement{<div class="wims_columns">
 <div class="medium_size img_col">
  \draw{400,400}{\image}
  </div>
 <div class="medium_size text_col"><p>
  Voici la représentation en bâtons d'une série statistique:
  </p>
  Calculer la moyenne et l'écart type de la série, arrondis à 0.01 près .
  <ul style="list-style-type:none">
  <li><label for="reply1">Moyenne =</label> \embed{reply1,5}</li>
  <li><label for="reply2">Écart-type =</label> \embed{reply2,5}</li>
  </ul>
  </div></div>
}
\answer{Moyenne}{\moy}{type=numeric}
\answer{Écart-type}{\sig}{type=numeric}
#endif

#if defined TARGET_ecartvar3
\real{xoff1=(\xmax-\xmin)/5}
\real{xoff=(\xmax-\xmin)/5}
\text{image=
 xrange \xmin-\xoff1,\xmax+5
 yrange -10,\hmax+5
 arrow \xmin-5,0,\xmax+5,0,10,black
 arrow \xmin-5,-5,\xmin-5,\effmax+5,10,black
 polyline blue,\xlistval[1],0,\xlistval[1],\lsth[1],\xlistval[2],\lsth[1],\xlistval[2],0
dsegment \xmin-5,\lsth[1],\xlistval[1],\lsth[1],orange
text black,\xlistval[1],-5,medium,\xlistval[1]
}
\integer{yoff=3}
\for{i=2 to \nbval}
 {
 \real{xoff=\xoff=\xoff1?\xoff1/2:\xoff1}
 \integer{yoff=\yoff=3?5:3}
 \text{image=\image
 polyline blue,\xlistval[\i],0,\xlistval[\i],\lsth[\i],\xlistval[\i+1],\lsth[\i],\xlistval[\i+1],0
 dsegment \xmin-5,\lsth[\i],\xlistval[\i],\lsth[\i],orange
 text black,\xlistval[\i],-\yoff,medium,\xlistval[\i]
 }
 }
\real{xoff=(\xmax-\xmin)/5}
\for{i=1 to \nblstht}
 {
 \real{xoff=\xoff=\xoff1?\xoff1/2:\xoff1}
 \text{image=\image
 text black,\xmin-\xoff,\lstht[\i],medium,\lstht[\i]
 }
 }
\integer{eff1=0}
\integer{eff2=0}
\integer{eff3=0}
\for{i=1 to \nbval}
 {
  \integer{eff1=abs(\xlistval[\i]+2.5-\moyh)<\sigh?\eff1+\lsteff[\i]}
  \integer{eff2=abs(\xlistval[\i]+2.5-\moyh)<2*\sigh?\eff2+\lsteff[\i]}
  \integer{eff3=abs(\xlistval[\i]+2.5-\moyh)<3*\sigh?\eff3+\lsteff[\i]}
 }
\real{pct1=round(\eff1*100/\efftotal)}
\real{pct2=round(\eff2*100/\efftotal)}
\real{pct3=round(\eff3*100/\efftotal)}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col">
  \draw{400,400}{\image}
  </div>
 <div class="medium_size text_col">
<p>
Voici une distribution de \efftotal boulons suivant leur diamètre en centième de mm:
</p>
Calculer la moyenne et l'écart-type de cette distribution
<ul style="list-style-type:none"><li>
<label for="reply1">Moyenne =</label> \embed{reply1,5}</li><li>
<label for="reply2">Écart-type =</label> \embed{reply2,5}</li>
</ul>
En faisant l'hypothèse d'une distribution uniforme dans chaque classe,
 calculer le pourcentage de données situées dans les intervalles:
 <div class="wimscenter">[m-s ;m+s],[m-2s ;m+2s] et [m-3s ;m+3s]</div>
<ul style="list-style-type:none">
  <li><label for="reply3">Pourcentage dans [m-s ;m+s]</label> : \embed{reply3,5}%</li>
<li><label for="reply4">Pourcentage dans [m-2s ;m+2s]</label> : \embed{reply4,5}%</li>
<li><label for="reply5">Pourcentage dans [m-3s ;m+3s]</label> : \embed{reply5,5}%</li>
</ul>
</div></div>
}
\answer{Moyenne}{\moyh}{type=numeric}
\answer{Écart-type}{\sigh}{type=numeric}
\answer{pct1}{\pct1}{type=numeric}
\answer{pct2}{\pct2}{type=numeric}
\answer{pct3}{\pct3}{type=numeric}
#endif

#if defined TARGET_ecartvar4
\integer{moy1=randint(9..11)}
\integer{moy2=randint(9..11)}
\integer{moy3=randint(13..15)}
\integer{nbval=36}
\text{listval1=}
\text{listval2=}
\text{listval3=}
%% moyenne et homogène
\integer{offmax=4}
\for{i=1 to \nbval/2}
  {
  \integer{off=randint(-\offmax..\offmax)}
  \integer{val1=\moy1+\off}
  \integer{val2=\moy1-\off}
  \text{listval1=wims(append item \val1,\val2 to \listval1)}
  }
\text{slistval1=shuffle(\listval1)}
%%moyenne et hétérogène
\integer{offmax=4}
\for{i=1 to \nbval/4}
  {
  \integer{off=3+randint(0..\offmax)}
  \integer{val1=\moy2+\off}
  \integer{val2=\moy2-\off}
  \text{listval2=wims(append item \val1,\val2 to \listval2)}
  }
\for{i=1 to \nbval/4}{
  \integer{off=randint(0..\offmax)}
  \integer{val1=\moy2+\off}
  \integer{val2=\moy2-\off}
  \text{listval2=wims(append item \val1,\val2 to \listval2)}
}
\text{slistval2=shuffle(\listval2)}
%% Forte et hétérogène
\for{i=1 to \nbval/4}{
  \integer{off=3+randint(0..\offmax)}
  \integer{val1=\moy3+\off}
  \integer{val1=\val1>20?20}
  \integer{val2=\moy3-\off}
  \text{listval3=wims(append item \val1,\val2 to \listval3)}
}
\for{i=1 to \nbval/4}{
  \integer{off=randint(0..\offmax)}
  \integer{val1=\moy3+\off}
  \integer{val2=\moy3-\off}
  \text{listval3=wims(append item \val1,\val2 to \listval3)}
}
\text{slistval3=shuffle(\listval3)}

\text{tab1=}

\integer{nn=ceil(\nbval/10)}
\for{i=0 to \nn-1}{
  \text{tab1=\tab1 <tr>}
  \for{j=1 to 10}{
    \text{a=item(\i*10+\j,\slistval1)}
    \text{tab1=\tab1 <td> \a </td>}
  }
  \text{tab1=\tab1 </tr>}
}
\text{tab1=\tab1 </table>}

\text{tab2=}

\integer{nn=ceil(\nbval/10)}
\for{i=0 to \nn-1}{
  \text{tab2=\tab2 <tr>}
  \for{j=1 to 10}{
    \text{a=item(\i*10+\j,\slistval2)}
    \text{tab2=\tab2 <td> \a </td>}
  }
  \text{tab2=\tab2 </tr>}
}
\text{tab2=\tab2 </table>}

\text{tab3=}

\integer{nn=ceil(\nbval/10)}
\for{i=0 to \nn-1}{\text{tab3=\tab3 <tr>}
  \for{j=1 to 10}{
    \text{a=item(\i*10+\j,\slistval3)}
    \text{tab3=\tab3 <td> \a </td>}
  }
  \text{tab3=\tab3 </tr>}
}
\text{tab3=\tab3 </table>}

%% on mélange les 3 tableaux
\text{ind=shuffle(3)}
\if{\ind[1]=1}{\text{taba=\tab1}}
\if{\ind[2]=1}{\text{tabb=\tab1}}
\if{\ind[3]=1}{\text{tabc=\tab1}}
\if{\ind[1]=2}{\text{taba=\tab2}}
\if{\ind[2]=2}{\text{tabb=\tab2}}
\if{\ind[3]=2}{\text{tabc=\tab2}}
\if{\ind[1]=3}{\text{taba=\tab3}}
\if{\ind[2]=3}{\text{tabb=\tab3}}
\if{\ind[3]=3}{\text{tabc=\tab3}}
\integer{i1=position(1,\ind)}
\integer{i2=position(2,\ind)}
\integer{i3=position(3,\ind)}
\text{lstserie=Série A, Série B, Série C}
\text{rep1=\lstserie[\i1]}
\text{rep2=\lstserie[\i2]}
\text{rep3=\lstserie[\i3]}
\text{size=50x20x1}
\statement{
  <table class="wimscenter wimsborder">
  <caption>notes de la classe A</caption>
  \taba
  <table class="wimscenter wimsborder">
  <caption>notes de la classe B</caption>
  \tabb
  <table class="wimscenter wimsborder">
  <caption>notes de la classe C</caption>
  \tabc
  Après avoir calculé la moyenne et l'écart-type des 3 séries ci-contre,
   associer à chaque commentaire la série correspondante :
  <ul>
  <li>classe moyenne et homogène : \embed{reply1,\size}</li>
  <li>classe moyenne et hétérogène : \embed{reply2,\size}</li>
  <li>classe forte et hétérogène : \embed{reply3,\size}</li>
  </ul>
}

\answer{C1}{\rep1}{type=dragfill}
\answer{C2}{\rep2}{type=dragfill}
\answer{C3}{\rep3}{type=dragfill}
#endif
#if defined TARGET_ecartvar5
\integer{a=randint(2..10)*10-1}
\real{m=randint(20..80)/10}
\real{s=randint(20..50)/10}
\integer{v=randint(5..50)}
\real{moy=(\a*\m+\v)/(\a+1)}
\real{moy=round(10*\moy)/10}
\real{var=(\s^2+\m^2)*\a/(\a+1)+\v^2/(\a+1)-\moy^2}
\real{sig=sqrt(\var)}
\real{sig=round(\sig*10)/10}
\statement{<p>
  Une série statistique a pour effectif \a.
   Sa moyenne est de \m et son écart-type est \s.
   On ajoute une valeur supplémentaire égale à \v.
  </p><p>
  Calculer la moyenne et l'écart-type de la nouvelle série (<i> arrondis à 0.1 près</i>).
  </p>
  <ul><li><label for="reply1">Moyenne =</label> \embed{reply1,4}</li>
  <li><label for="reply2">Écart-type =</label> \embed{reply2,4}</li>
  </ul>
}
\answer{Moyenne}{\moy}{type=numeric}
\answer{Écart-type}{\sig}{type=numeric}
#endif
