target=unionint
#define GGG B2 -
\title{GGG Ensembles de multiples}
\description{il s'agit de décrire trouver les éléments d'un ensemble à partir de sa description.}
\observation{Exercice sur la réunion, l'intersection et la différence de 2 ensembles.}
\keywords{set_theory}
\language{fr}
\range{-5..5}
\author{Bernadette, Perrin-Riou}
\email{bernadette.m.riou@orange.fr}
\computeanswer{no}
\format{html}
\precision{10000}
#include "common.inc"
#include "css.inc"
\integer{init=random(30..48)}
\integer{t= random(2,3,5)}
\integer{s= random(2,3,5)}
\integer{u=\s*\t}
\integer{rr=random(2,3,4,5,7)}
\integer{r= \r%\t=0 or \r%\s =0 ? 7:\rr}

\text{S=}
\integer{fin=floor(\init/\t)}
\for{i=1 to \fin}{
	\integer{tt= \i*\t}
	\text{S=\S,\tt}
}
\text{A1=}
\for{i in \S}{
	\text{tt= \i%\u=0? \i:NNN}
	\text{A1=\tt notsametext NNN ?\A1,\tt}
}
\text{A1=wims(nonempty items \A1)}
\text{B1=}
\for{i in \S}{
	\text{tt= \i%\r=0? \i:NNN}
	\text{B1=\tt notsametext NNN ? \B1,\tt}
}
\text{B1=wims(nonempty items \B1)}
\integer{v=1}
\text{A =item(\v,(\A1),(\B1))}
\text{A=wims(declosing \A)}
\text{B =item(3-\v,(\A1),(\B1))}
\text{B=wims(declosing \B)}
\text{AIB= wims(listintersect \A and \B)}
\text{AUB= wims(listunion \A and \B)}
\text{CAIB=wims(listcomplement \AIB in \S)}
\text{CAUB=wims(listcomplement \AUB in \S)}
\text{CA=wims(listcomplement \A in \S)}
\text{CB=wims(listcomplement \B in \S)}
\text{AMB=wims(listcomplement \B in \A)}
\text{BMA=wims(listcomplement \A in \B)}
\text{ADB=wims(listcomplement \AIB in \AUB)}
\text{CAUCB=wims(listunion \CA and \CB)}

#include "lang_unionint_fr.inc"
\if{\lang=it}{
#include "lang_unionint_it.inc"
}
\if{\lang=es}{
#include "lang_unionint_es.inc"
}
\matrix{matcas= \matcaslang[1;], \CAUCB
\matcaslang[2;], \AMB
\matcaslang[3;], \BMA
\matcaslang[4;], \ADB
\matcaslang[5;], \AUB
\matcaslang[6;], \AIB
\matcaslang[7;], \CAIB
\matcaslang[8;],\CAUB
}

\text{choix=randrow(\matcas)}
\text{cas=item(1,\choix)}
\integer{n=items(\choix)}
\text{sol1=item(2..-1,\choix)}
\text{sol= \n>1 ? \sol1:0}
\text{sol=wims(sort numeric item \sol)}
\statement{
<div class="color1">\instruction</div>
<div class="wims_question">\question \cas.</div>
<div class="wims_instruction">\warning</div> }
\answer{\(C\) }{\sol}{type=set}
