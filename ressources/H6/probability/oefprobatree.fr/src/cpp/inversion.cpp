target=inversion

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{100}
\integer{n=\confparm1=? 2: min(3,\confparm1+1)}

\if{\n = 2}{\matrix{G=1,2,3
2,4,5
3,6,7
}
\matrix{Ginv=\G}
\text{nom=*,A,A^c,B,B^c,B,B^c}
\text{nominv=*,B,B^c,A,A^c,A,A^c}

}

\if{\n = 3}{\matrix{G=1,2,3
2,4,5,6
3,7,8,9
}
\matrix{Ginv=1,2,3,4
2,5,6
3,7,8
4,9,10
}
\text{nom=*,A1,A2,B1,B2,B3,B1,B2,B3}
\text{nominv=*,B1,B2,B3,A1,A2,A1,A2,A1,A2}
}

\text{SIZEX=600}
\text{SIZEY=250}

\text{M=randint(1..2)}
\integer{N=randitem(10,20,50)}
\text{p=}

\text{S=\n=2 ? 2,2,2:2,3,3}
\for{s in \S}{
	\text{prob=wims(makelist 1/\s for x=1 to \s-1)}
	\text{liste=slib(stat/multinomial  1,\N,[\prob])}
	\text{liste=wims(lines2items \liste)}
	\text{p1=pari(1.*[\liste]/\N)}
	\text{p=\p,\p1}
}
\text{p=wims(nonempty items \p)}
\text{s1=\n=3 ? 2}
\text{s2=\n=3 ? 3}
\text{s1=\n=2 ? 2}
\text{s2=\n=2 ? 2}

\text{q=}
\for{i=1 to \s2}{
	\real{q1=\p[\s1+\i]*\p[1]+\p[\i+\s2+\s1]*\p[2]}
	\text{q=\q,\q1}
}
\text{q=wims(nonempty items \q)}
\for{i=1 to \s2}{
	\real{q1=round(1000*(\p[\i+\s1]*\p[1]/\q[\i]))/1000}
	\text{q=\q,\q1}
	\real{q1=1-\q1}
	\text{q=\q,\q1}
}

\text{S=slib(graph/drawtree [\G],[\nom], middle point)}
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
\text{rangex=row(1,\u)}
\text{rangex =wims(replace internal xrange by in \rangex)}
\text{rangey=row(2,\u)}
\text{rangey =wims(replace internal yrange by in \rangey)}
/* Reponses */

\text{Sinv=slib(graph/drawtree [\Ginv],[\nominv], middle point)}
\text{uinv=wims(declosing \Sinv[1])}
\text{positioninv= \Sinv[3]}
\text{milieuinv=\Sinv[4]}
\matrix{positioninv= wims(declosing \positioninv)}
\matrix{milieuinv= wims(declosing \milieuinv)}
\text{Ginv=\Sinv[2]}
\text{Ginv= wims(declosing \Ginv)}
\text{cntinv=rows(\Ginv)}
\integer{cnt_minv=rows(\milieuinv)}
/* Dessin */
\text{rangexinv=row(1,\uinv)}
\text{rangexinv =wims(replace internal xrange by in \rangexinv)}
\text{rangeyinv=row(2,\uinv)}
\text{rangeyinv =wims(replace internal yrange by in \rangeyinv)}
/* Reponses */
\text{freponse=\p,\q}
\text{reponse=\M=1 ? \q:\p}
\text{rep=\M=1 ? wims(makelist r x for x=1 to \cnt_minv-1):wims(makelist r x for x=1 to \cnt_m-1)}

\text{pos_m=}
 \for{i=2 to \cnt_m}{
 	\real{sx=\milieu[\i;1]}
 	\real{sy=\milieu[\i;2]}
 		\text{c=\p[\i-1]}
 	\if{\M=1}{
	\text{u=\u
		text black,\sx-0.8,\sy+0.1,medium,\c}
		}{
			\text{POS=slib(draw/convpixel \sx-0.8,\sy,\SIZEX,\SIZEY,\rangex,\rangey,10,pixels)}
 	 	\matrix{pos_m=\pos_m
	\rep[\i-1] , \POS[1] x \POS[2]}
		}
}

 \for{i=2 to \cnt_minv}{
 	\real{sx=\milieuinv[\i;1]}
 	\real{sy=\milieuinv[\i;2]}
 	\text{c=\q[\i-1]}
 	\if{\M=2}{
		\text{uinv=\uinv
		text black,\sx-0.8,\sy+0.1,medium,\c}
		}{
			\text{POS=slib(draw/convpixel \sx-0.8,\sy,\SIZEX,\SIZEY,\rangexinv,\rangeyinv,10,pixels)}
 	 	\matrix{pos_m=\pos_m
	\rep[\i-1] , \POS[1] x \POS[2]}
	}
}

\text{dessininv=draw(\SIZEX,\SIZEY
\uinv)}
\text{dessin=draw(\SIZEX,\SIZEY
\u)}

\steps{\rep}
\statement{
  \name_enonce:
<div class="wimscenter">
\if{\M=1}{
	<img src="\dessin" alt=""></div><div class="wimscenter">
	\special{imagefill \dessininv,\SIZEX x \SIZEY,40x20
\pos_m}
	}{
	<img src="\dessininv" alt=""></div><div class="wimscenter">
\special{imagefill \dessin,\SIZEX x \SIZEY,40x20
\pos_m}
}
</div>
}

\answer{}{\reponse[1];\freponse}{type=clickfill}
\answer{}{\reponse[2]}{type=clickfill}
\answer{}{\reponse[3]}{type=clickfill}
\answer{}{\reponse[4]}{type=clickfill}
\answer{}{\reponse[5]}{type=clickfill}
\answer{}{\reponse[6]}{type=clickfill}
\answer{}{\reponse[7]}{type=clickfill}
\answer{}{\reponse[8]}{type=clickfill}
\answer{}{\reponse[9]}{type=clickfill}
\answer{}{\reponse[10]}{type=clickfill}
\answer{}{\reponse[11]}{type=clickfill}
\answer{}{\reponse[12]}{type=clickfill}
