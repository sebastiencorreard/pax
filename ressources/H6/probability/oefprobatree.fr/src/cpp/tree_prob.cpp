target=tree1 binarytree
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#define SIZEX 800
#define SIZEY 250

\precision{100}
\text{s=2}
\text{prof=3}
#if defined TARGET_tree1
\integer{s=\confparm1= ? randint(2..3):\confparm1+1}
#endif
\text{nom=*}
#if defined TARGET_binarytree
\text{nom=\nom,A, A^c,B,B^c,B,B^c}
#endif
\integer{N=randitem(10,25,20,50)}

\integer{H=(\s^(\prof)-1)/(\s-1)-1}
\text{prob=wims(makelist 1/\s for x=1 to \s-1)}
\text{liste=slib(stat/multinomial \H,\N,[\prob])}

\text{p=wims(lines2items \liste)}
\text{p=pari(1.*[\p]/\N)}

\text{freponse=\p,wims(values x/\N for x=0 to \N)}

\text{S = slib(graph/randtree \H,\s,\prof,[\nom], middle perfect point)}

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

\text{pos_m=}
\text{border=10}

\integer{M=(\cnt_m-1)/\s}
\text{V=slib(stat/random \M, 1,\s)}
\integer{W=1+\V[1]}
\for{a=2 to \M}{
	\integer{W1=1+(\a-1)*\s +\V[\a]}
	\text{W=\W,\W1}
}
/* Reponses */
#if defined TARGET_binarytree
\text{rep=wims(makelist r x for x = 1 to \M+1)}
\text{j=1}
#elif defined TARGET_tree1
\text{rep=wims(makelist r x for x = 1 to \M)}
\text{j=0}
#endif
\text{rep = wims(nospace \rep)}

\text{reponse=}
\text{pos_m=}
\for{i=2 to \cnt_m}{
  \real{sx=\milieu[\i;1]}
  \real{sy=\milieu[\i;2]}
  \real{c=\p[\i-1]}
  \if{\i isitemof \W}{
	  \text{POS=slib(draw/convpixel \sx-0.8,\sy,SIZEX,SIZEY,\rangex,\rangey,10,pixels)}
	  \text{j=\j+1}
 	  \matrix{pos_m=\pos_m
	  \rep[\j], \POS[1] x \POS[2]}
	  \text{reponse=\reponse,\c}
  }{
    \text{u=\u
		text black,\sx-0.8,\sy+0.1,medium,\c}
	}
}
\text{reponse=wims(nonempty items \reponse)}

#if defined TARGET_binarytree
\text{evenements= A et B , A et B^c, A^c et B, A^c et B^c}
\text{choix=randint(1..4)}
\text{evenement=\evenements[\choix]}
\real{proba= \choix=1 ? \p[1]*\p[3]}
\real{proba= \choix=2 ? \p[1]*\p[4]}
\real{proba= \choix=3 ? \p[2]*\p[5]}
\real{proba= \choix=4 ? \p[2]*\p[6]}
#endif
\text{dessin=draw(SIZEX,SIZEY
\u)}
\steps{\rep}

\statement{
   \name_enonce
#if defined TARGET_binarytree
   \name_enonce1
#endif
#if defined TARGET_tree1 || defined TARGET_binarytree
   \name_enonce2:
#endif
<div class="wimscenter">
\special{imagefill \dessin,SIZEX x SIZEY,40x20
\pos_m
}
</div>
#if defined TARGET_binarytree
  <label for="reply1">\name_question \(p(\evenement)\):</label> \embed{reply 1}
#endif
}
#if defined TARGET_binarytree
\answer{\name_answer}{\proba}{type=numeric}
#endif

#define ANS(y) \
\answer{}{\reponse[y]}{type=clickfill}

\answer{}{\reponse[1];\freponse,\p}{type=clickfill}
ANS(2)
ANS(3)
ANS(4)
ANS(5)
ANS(6)
ANS(7)
ANS(8)
ANS(10)
ANS(11)
ANS(12)
ANS(13)
