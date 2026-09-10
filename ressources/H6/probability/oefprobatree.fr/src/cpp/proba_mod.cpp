target= potpourri2x2
#include "lang_titles.inc"
#if defined TARGET_potpourri2x2
# define SIZEX 400
# define SIZEY 250
#else
# define SIZEX 600
# define SIZEY 250
#endif
#include "author.inc"

\precision{100}
\text{prof=3}

\text{s=2}
\text{nom=*,A, A^c,B,B^c,B,B^c}
\text{nominv=*,B, B^c,A,A^c,A,A^c}
\integer{N=randitem(10,25,20,50)}
\integer{H=(\s^(\prof)-1)/(\s-1)-1}
\text{prob=wims(makelist 1/\s for x=1 to \s-1)}
\text{liste=slib(stat/multinomial \H,\N,[\prob])}

\text{p=wims(lines2items \liste)}
\text{p=pari(1.*[\p]/\N)}
\matrix{G=1,2,3
2,4,5
3,6,7}

\text{S=slib(graph/drawtree [\G],, middle point)}
\text{u=wims(declosing \S[1])}
\text{position= \S[3]}
\text{milieu=\S[4]}
\matrix{position= wims(declosing \position)}
\matrix{milieu= wims(declosing \milieu)}
\text{G=\S[2]}
\text{G= wims(declosing \G)}
\text{cnt=rows(\G)}
\integer{cnt_m=rows(\milieu)}
/* Dessin */
\matrix{G = \G }
\text{rangex=row(1,\u)}
\text{rangex =wims(replace internal xrange by in \rangex)}
\text{rangey=row(2,\u)}
\text{rangey =wims(replace internal yrange by in \rangey)}

/* Reponses */

\text{rep=r1,r2,r3,r4,r5}

\text{rep = wims(nospace \rep)}
\text{uinv=\u}
 \for{i=2 to \cnt_m}{
 	\real{sx=\milieu[\i;1]}
 	\real{sy=\milieu[\i;2]}
 	\text{c=\p[\i-1]}
	\text{uinv=\uinv
		text black,\sx-0.8,\sy+0.1,medium,\c}
}
\real{a=\p[1]*\p[3]+\p[2]*\p[5]}
\real{b=1-\a}
\real{c=round(1000*\p[1]*\p[3]/\a)/ 1000}
\real{d=1-\c}
\real{e=round( 1000*\p[4] *\p[1]/\b)/1000}
\real{f=1-\c}
\text{reponse=\a,\b,\c,\d,\e,\f}
\text{uinv=\u}
 \for{i=2 to \cnt_m}{
 	\real{sx=\milieu[\i;1]}
 	\real{sy=\milieu[\i;2]}
 	\text{c=\p[\i-1]}
 	\text{d=\reponse[\i-1]}
	\text{uinv=\uinv
		text black,\sx-0.8,\sy+0.1,medium,\d}
	\text{u=\u
		text black,\sx-0.8,\sy+0.1,medium,\c}
}
\for{i=2 to \cnt}{
	\real{sx=\position[\i;1]}
 	\real{sy=\position[\i;2]}
 	\text{c=\nom[\i]}
 	\text{cinv=\nominv[\i]}
	\text{u=\u
	text black, \sx-0.4,\sy+0.1,medium,\c
	}
	\text{uinv=\uinv
	text black,\sx-0.4,\sy+0.1,medium,\cinv
	}
}
\text{dessininv=draw(SIZEX,SIZEY
\uinv)}
\text{dessin=draw(SIZEX,SIZEY
\u)}

\steps{\rep}
\matrix{objets=
   gâteau,x,m
   montre,s,f
   voyage,s,m
   voyage,s,m
   voyage,s,m
   personne,s,f
}
\text{N=randint(1..rows(\objets))}
\text{a=randint(1,2)}

\text{objet=\objets[\N;1]}
\text{genre=\objets[\N;3]}
\text{objets=wims(nospace \objet \objets[\N;2])}
\text{Article=\genre issametext m ? Un:Une}
\text{article=\genre issametext m ? un:une}
\text{pronom=\genre issametext m ? il:elle}
\text{pris=\genre issametext m ? pris:prise}
\text{introduction=row(\N,
   Un pâtissier a fabriqué des gâteaux.
   Un bijoutier fabrique des montres de deux types et les monte soit avec un bracelet métallique, soit avec un bracelet en cuir.
   Un voyagiste vend des voyages dont les trajets se font soit uniquement en car, soit uniquement en train dans deux directions (Nord et Sud)
   Un voyagiste vend des voyages en Europe ou hors Europe.
   Un voyagiste vend des voyages en France ou hors France.
   En région parisienne, on interroge au hasard une personne d'un groupe.)}
\matrix{Cond1=
   au chocolat,sans chocolat
   du type I,du type II
   en car,en train
   en Europe, hors Europe
   en France, hors de la France
   à Paris, hors de Paris
}

\text{cond1=\Cond1[\N;\a]}
\text{condc1=\Cond1[\N;3-\a]}
\text{texte1=row(\N,
   sont
   sont
   sont
   se passent
   se passent
   sont nées
)}

\text{texte2= row(\N,
   sont
   ont un bracelet
   sont en direction du
   se passent
   se passent à la
   travaillent)}

\text{texte3= row(\N,
  &nbsp;
   avec un bracelet
   en direction du
  &nbsp;
   à la
   travaillant)}

\text{texte4=row(\N,
 &nbsp;
 &nbsp;
 &nbsp;
 &nbsp;
 &nbsp;
   née)}
\matrix{Cond2=
   avec des fruits, sans fruits
   en cuir, métallique
   Sud, Nord
   en famille, avec des amis
   mer,montagne
   à Paris, hors de Paris
}
\text{cond2=\Cond2[\N;\a]}
\text{condc2=\Cond2[\N;3-\a]}

\real{a=\p[1]*\p[3]}
\real{b=\p[1]*\p[4]}
\real{c=\p[2]*\p[5]}
\real{d=\p[2]*\p[6]}
\real{U=round(1000*(\a+\c))/1000}
\real{V= round(1000*(\a/(\p[1]*\p[3]+\p[2]*\p[5])))/1000}

\matrix{question= \condc1,\condc2,\d
 \cond1, \condc2,\b
 \cond1, \cond2,\a
 \condc1,\cond2,\c
 }

\text{pourcent=pari([\p]*100)}
\statement{
\introduction
<ul><li>\pourcent[1] % des \objets \texte1 \cond1 ;</li>
<li>parmi les \objets qui \texte1 \cond1, \pourcent[3] % des \objets \texte2 \cond2 ;</li>
<li>parmi les \objets qui \texte1 \condc1, \pourcent[5] % des \objets \texte2 \cond2.</li>
</ul>
   On prend \article \objet au hasard. Calculer :
<ul>
\for{m=1 to 3}{
 <li><label for="reply\m">La probabilité d'avoir \article \objet \text4 \question[\m;1] et \texte3 \question[\m;2] :
 </label>\embed{reply \m}</li>}
 <li><label for="reply4">La probabilité d'avoir \article \objet \texte3 \cond2 :</label> \embed{reply4}</li>
</ul>
 \Article \objet \pris au hasard se trouve être \article \objet \texte3 \cond2.
   <label for="reply5">Calculer la probabilité qu'\pronom soit \texte4 \cond1 :</label>
<div class="wimscenter">\embed{reply5}.</div>
}

\answer{}{\question[1;3]}{type=numeric}
\answer{}{\question[2;3]}{type=numeric}
\answer{}{\question[3;3]}{type=numeric}
\answer{}{\U}{type=numeric}
\answer{}{\V}{type=numeric}

\hint{On peut par exemple commencer par construire l'arbre pondéré associé et son inversion.}
\feedback{1=1}{On note \(A\) l'événement <span class="bold">avoir un \objet \cond1</span>,
\(B\) l'événement <span class="bold">avoir un \objet \cond2</span>, \(A^c\) et \(B^c\) sont les
  événements contraires.
  Voici les deux arbres pondérés associés :
<div class="wimscenter"><img src="\dessin" alt=""> <img src="\dessininv" alt=""></div>
}
