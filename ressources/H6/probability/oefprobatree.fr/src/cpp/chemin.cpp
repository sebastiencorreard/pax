target=chemin ensemble

#include "author.inc"
\precison{100}
#include "lang_titles.inc"
#include "lang.inc"
/*Nombre de branches possibles maximum*/
\integer{MAX=4}
\integer{MAX=\confparm1=1 ? 1}
\integer{MAX=\confparm1=2 ? 2}
\integer{MAX=\confparm1=3 ? 4}

\integer{T=randint(1..7)}
\if{\T=1}{
  \matrix{G=1,2,3
2,4,5,6
3,7,8,9}
\text{nom=*,A1,A2,B1,B2,B3,B1,B2,B3}
}
\if{\T=2}{
	\matrix{G=1,2,3
2,4,5
3,6,7,8}
	\text{nom=*,A1,A2,B1,B2,B1,B2,B3}
}
\if{\T=3}{
	\matrix{G=1,2,3
2,4,5,6
3,7,8,9,10}
	\text{nom=*,A1,A2,B1,B2,B3,B1,B2,B3,B4}
}
\if{\T=4}{
	\matrix{G=1,2,3,4
2,5,6
3,7,8
4,9,10}
	\text{nom=*,A1,A2,A3,B1,B2,B1,B2,B1,B2}
}
\if{\T=5}{
	\matrix{G=1,2,3,4
2,5,6,7
3,8,9,10
4,11,12,13}
	\text{nom=*,A1,A2,A3,B1,B2,B3,B1,B2,B3,B1,B2,B3}
}
\if{\T=6}{
	\matrix{G=1,2,3,4
2,5,6,7
3,8,9
4,10,11,12}
	\text{nom=*,A1,A2,A3,B1,B2,B3,B1,B2,B1,B2,B3}
}
\if{\T=7}{
	\matrix{G=1,2,3,4
2,5,6
3,7,8,9
4,10,11,12}
	\text{nom=*,A1,A2,A3,B1,B2,B1,B2,B3,B1,B2,B3}
}
\text{listechemin=}
\text{cnt=rows(\G)}
\for{i=2 to \cnt}{
	\text{ligne=\G[\i;2..-1]}
	\for{j in \ligne}{
	\matrix{listechemin= \listechemin
\i,\j}
}
}
\integer{N= randitem(10,20,50)}
/* Proba */
\text{p=0}
\for{i=1 to \cnt}{
	\integer{s=items(\G[\i;])-1}
	\text{prob=wims(makelist 1/\s for x = 1 to \s-1)}
	\text{p=\p,slib(stat/multinomial 1,\N, [\prob])}
}
\text{p=pari(1.*[\p]/\N)}
/*Graphe*/
\text{S=slib(graph/drawtree [\G],[[\nom],[\p]],middle point)}
\text{u=wims(declosing \S[1])}
\text{position= \S[3]}
\text{milieu=\S[4]}
\matrix{position= wims(declosing \position)}
\matrix{milieu= wims(declosing \milieu)}

/*Choix des chemins*/
\text{n=randint(1..min(\MAX,rows(\listechemin)))}
\text{HH=item(1..\n,shuffle(rows(\listechemin)))}
\text{H=\listechemin[\HH;]}
\text{h=rows(\H)}

/*Calcul des probas*/
\real{proba=0}
\for{i=1 to \h}{
	\real{proba=\proba + \p[\H[\i;1]]*\p[\H[\i;2]]}
}

/*dessin des lignes et génération des ensembles*/
\text{ensemble=}
\for{r =1 to \n}{
	\text{chemin=\H[\r;]}
	\text{ligne=\position[1;1],\position[1;2]}
	\text{ens=}
	\for{t in \chemin}{
	  \text{ligne=\ligne, \position[\t;1],\position[\t;2]}
	  \text{ens=\ens ,\nom[\t]}
	  \text{ens=wims(nonempty items \ens)}
	}
	\text{ensemble=\r = 1 ? \ens :
	\ensemble ;
	\ens}
	\text{u=\u
linewidth 2
polyline red,\ligne}
	}

\text{A=A_}
\text{B=B_}
\text{C=C_}

\text{inter=et }
\text{union= ou }
\text{ensemble=wims(nonempty items \ensemble)}
\text{ensemble1=wims(replace internal , by \inter in \ensemble)}
\text{ensemble1= wims(replace internal A by \A in \ensemble1) }
\text{ensemble1= wims(replace internal B by \B in \ensemble1) }
\text{ensemble1= wims(replace internal C by \C in \ensemble1) }
\text{ensemble1= wims(replace internal ; by , in \ensemble1) }

\text{reponse=}
\matrix{permutation=\n=1 ? }
\matrix{permutation=\n=2 ?2,1}
\matrix{permutation=\n=3 ?1,3,2
2,1,3
2,3,1
3,1,2
3,2,1}

\matrix{permutation=\n=4 ?
1,3,2,4
2,1,3,4
2,3,1,4
3,1,2,4
3,2,1,4
2,3,4,1
2,4,3,1
3,2,4,1
3,4,2,1
4,2,3,1
4,3,2,1
3,4,1,2
3,1,4,2
4,3,1,2
4,1,3,2
1,3,4,2
1,4,3,2
4,1,2,3
4,2,1,3
1,2,2,3
1,2,2,3
2,2,1,3
2,1,2,3
}
\text{ensemble2=}
\for{i=1 to \h}{
  \text{ensemble2= \i=1 ? ( \ensemble1[1] ): \ensemble2 \union ( \ensemble1[\i] )}
}

#if defined TARGET_ensemble
/* Pour compose, fausses réponses*/
\text{freponse=}

\for{i= 1 to rows( \listechemin)}{
	\text{freponse= \freponse
,\(( \nom[\listechemin[\i;1]] \inter \nom[\listechemin[\i;2]] )\)}
     \if{\i isitemof \HH}{ \text{reponse =\reponse, \i}}
     }
\text{freponse= wims(replace internal A by \A in \freponse) }
\text{freponse= wims(replace internal B by \B in \freponse) }
\text{freponse= wims(replace internal C by \C in \freponse) }
\text{freponse=wims(nonempty items \freponse)}
\text{freponse=\freponse,\(\inter\),\(\union\)}
\text{reponse=wims(nonempty items \reponse)}
\text{reponse=\freponse[\reponse]}
\text{Reponse=\reponse}
\text{nperm=rows(\permutation)}
\for{k =1 to \nperm} {
	\text{Reponse=\Reponse|\reponse[\permutation[\k;]]}
}

\text{Reponse=wims(nonempty items \Reponse)}
\text{Reponse=wims(replace internal , by ,\(\union\), in \Reponse)}
#endif

\statement{
\name_enonce
<div class="wimscenter">\draw{700,200}{\u}</div>

#if defined TARGET_chemin
  \name_question
<div class="wimscenter">\(F= \ensemble2\).</div>
#elif defined TARGET_ensemble
  <label for="reply1">\name_question</label>
   \embed{r1}
#endif
}
#if defined TARGET_chemin
\answer{\name_answer \(F\)}{\proba}{type=numeric}
#elif defined TARGET_ensemble
\answer{}{\Reponse;\freponse}{type=compose}
#endif
