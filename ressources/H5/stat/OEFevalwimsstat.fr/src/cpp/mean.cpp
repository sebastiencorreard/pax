target=mean1 mean2 mean3 mean4 mean5
#include "author.inc"
\precision{1000}
#include "lang_titles.inc"
\integer{range=random(20..100)}
\integer{xmin=random(1..5)*10}
\integer{parite=random(1,2)}
\integer{parite=2}
\integer{nbval=2*randint(3,4)+\parite}
\text{listval=}
 \integer{val=\xmin}
 \integer{efftotal=0}
 \text{xlistval=}
%% generation des effectifs
\integer{efftotal=randint(100,200,400,500)}
#include "lsteff.inc"
 \text{lsth=}
 \integer{Smin=0}
 \integer{Smax=0}
 \text{xlistval=wims(append item \val to \xlistval)}
 \for{i=1 to \nbval}
 {
  \integer{eff=\lsteff[\i]}
  \integer{Smin=\Smin+\eff*\val}
  \integer{largeur=random(1,2,4)}
  \integer{val = \val+\largeur*10}
  \integer{Smax=\Smax+\eff*\val}
  \text{xlistval=wims(append item \val to \xlistval)}
  \real{high=\eff / \largeur}
  \text{lsth=wims(append item \high to \lsth)}
 }
\text{lstht=wims(listuniq \lsth)}
\text{lstht=wims(sort numeric list \lstht)}
\integer{nblstht=items(\lstht)}
\integer{hmax=\lstht[\nblstht]}
\integer{ig=\Smin/\efftotal}
\integer{id=\Smax/\efftotal}
\integer{moyh=(\ig+\id)/2}
\real{moy=round(\Smin*10/\efftotal)/10}
\text{lstefft=wims(listuniq \lsteff)}
\text{lstefft=wims(sort numeric list \lstefft)}
\integer{nbefft=items(\lstefft)}
\integer{effmax=\lstefft[\nbefft]}



\integer{xmin=\xlistval[1]}
\integer{xmax=\xlistval[\nbval+1]}

#if defined TARGET_mean1
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
\integer{yoff=3}
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
\statement{<p>
Voici une série représentée par son diagramme en bâtons.</p>
<div class="wimscenter">\draw{400,400}{\image}</div>
Calculer la moyenne de cette série: <br><i> Arrondir à 0.1 près</i>
<div class="wimscenter"><label for="reply1">Moyenne =</label> \embed{reply1,4}</div>
}
\answer{moyenne}{\moy}{type=numeric}
#endif
#if defined TARGET_mean2
\real{xoff1=(\xmax-\xmin)/5}
\real{xoff=(\xmax-\xmin)/5}
\text{image=
 xrange \xmin-\xoff1,\xmax+10
 yrange -10,\hmax+5
 arrow \xmin-5,0,\xmax+5,0,10,black
 arrow \xmin-5,-5,\xmin-5,\effmax+5,10,black
 polyline blue,\xlistval[1],0,\xlistval[1],\lsth[1],\xlistval[2],\lsth[1],\xlistval[2],0
dsegment \xmin-5,\lsth[1],\xlistval[1],\lsth[1],orange
text black,\xlistval[1],-5,medium,\xlistval[1]
}
\integer{yoff=5}
\for{i=2 to \nbval}{
  \real{xoff=\xoff=\xoff1?\xoff1/2:\xoff1}
  \integer{yoff=\yoff=3?5:3}
  \text{image=\image
 polyline blue,\xlistval[\i],0,\xlistval[\i],\lsth[\i],\xlistval[\i+1],\lsth[\i],\xlistval[\i+1],0
 dsegment \xmin-5,\lsth[\i],\xlistval[\i],\lsth[\i],orange
 text black,\xlistval[\i],-\yoff,medium,\xlistval[\i]}
}
 \integer{yoff=\yoff=3?5:3}
 \text{image=\image
 text black,\xlistval[-1],-\yoff,medium,\xlistval[-1]
}

\real{xoff=(\xmax-\xmin)/5}
\for{i=1 to \nblstht}{
 \real{xoff=\xoff=\xoff1?\xoff1/2:\xoff1}
 \text{image=\image
 text black,\xmin-\xoff,\lstht[\i],medium,\lstht[\i]}
}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\draw{400,400}{\image}</div>
 <div class="medium_size text_col">
<p>On a relevé le montant en euros de \efftotal chèques déposés dans
  un commerce dans une journée.</p>
Soit S le montant total de l'ensemble des \efftotal chèques.<br>
 <label for="reply1">Donner le plus petit encadrement possible de S.</label>
<div class="wimscenter">\embed{reply1,3} <label for="reply2">\(\leq S \leq)</label> \embed{reply2,3}</div>
<p>
En déduire un intervalle I tel que le montant moyen des chèques appartient à I.<br>
<i>arrondir à l'unité</i>
</p>
<div class="wimscenter"> <label for="reply3">I= </label>
&#91; \embed{reply3,3} ; \embed{reply4,3} &#93; </div>
 <label for="reply5">Calculer la moyenne de la série: </label>\embed{reply5,4}<br>
<i>arrondir à l'unité</i>
<p>
  Cette moyenne représente-t-elle le centre de l'intervalle I ? \embed{reply6}
</p>
</div></div>
}
\answer{minimum de S}{\Smin}{type=numeric}
\answer{maximum de S}{\Smax}{type=numeric}
\answer{borne gauche}{\ig}{type=numeric}
\answer{borne droite}{\id}{type=numeric}
\answer{moyenne}{\moyh}{type=numeric}
\answer{centre}{1;Oui,Non}{type=radio}
#endif
#if defined TARGET_mean3
\integer{a=randint(10..20)}
\integer{b=randint(10..20)}
\real{x1=randint(80..120)/10}
\real{x2=randint(80..120)/10}
\real{rep=(\x1*\a+\x2*\b)/(\a+\b)}
\real{rep=round(\rep*10)/10}
\statement{<p>
La moyenne de mathématique au contrôle du groupe de \a élèves suivant l'option SES est de \x1,
 et celle du groupe de \b élèves suivant l'option MPI est de \x2.</p>
 Quelle est la moyenne de la classe?
<div class="wimscenter">
  <label for="reply1">Moyenne de la classe =</label> \embed{reply1}</div>
<i> Arrondir à 0.1 près</i>
}
\answer{moyenne}{\rep}{type=numeric}
#endif

#if (defined TARGET_mean4 || defined TARGET_mean5 )
\integer{a=randint(20..35)}
\real{b=randint(85..145)/10}
\integer{c=\b+randint(2..4)*randint(1,-1)}
\real{rep=(\b*\a+\c)/(\a+1)}
\real{rep=round(10*\rep)/10}
# if defined TARGET_mean4
\statement{<p>
Un professeur d'une classe de \a élèves corrige un devoir et obtient une moyenne de \b.<br>
 Un élève rend sa copie en retard et obtient pour note \c.</p>
 Quelle est la nouvelle moyenne de la classe ? <br><i>(arrondir à 0.1 près.)</i>
<div class="wimscenter"><label for="reply1">Moyenne de la classe =</label> \embed{reply1}</div>
}
\answer{moyenne}{\rep}{type=numeric}
# else
\text{verbe=\rep>\b?augmente:baisse}
\real{x=\rep>\b?\rep-\b:\b-\rep}
\real{x=round(\x*10)/10}
\integer{d=\rep>\b?(\a+1)*(\b+\x)-\a*\b:(\a+1)*(\b-\x)-\a*\b}
\statement{<p>
Un professeur d'une classe de \a élèves corrige un devoir et obtient une moyenne de \b.<br>
 Un élève rend sa copie en retard.</p>
Quelle est doit être sa note pour que la moyenne de la classe \verbe de \x ?
<br><i> arrondir à l'unité</i>
<div class="wimscenter"><label for="reply1">Note du retardataire =</label> \embed{reply1}</div>
}
\answer{moyenne}{\d}{type=numeric}
# endif
#endif
