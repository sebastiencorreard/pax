target=oefconstaxe1 oefconstaxe2 oefconstaxe3 oefconstaxe4 oefconstaxe5

#include "author.inc"
\keywords{symmetry}
\precision{1000}

\text{enonc1=Faire la construction avec les instruments de géométrie sur une feuille de brouillon
et répondre à la question :}

#if defined TARGET_oefconstaxe1
# define NUM 1
\real{l1=randint(20..40)*2/10}
\real{l2=randint(25..50)*2/10}
\integer{rep=sqrt(\l2^2-\l1^2/4)*20}
\real{rep1=(\rep-1)/10}
\real{rep2=(\rep+1)/10}

\text{enonc2=<li>Tracer un triangle ABC tel que :
<div class="wimscenter">AC = \l1 cm et AB = \l2 cm.</div></li>
<li>Construire le triangle AEC, symétrique du triangle ABC par rapport à la droite (AC).</li>}

\text{enonc3=Mesurer le segment BE.}
\text{enonc4=BE}
#endif

#if defined TARGET_oefconstaxe2
# define NUM 2
\text{c=shuffle(35)}
\real{l1=(20+\c[1])*2/10}
\real{l2=(20+\c[2])*2/10}
\real{l3=(20+\c[3])*2/10}
\integer{rep=sqrt(\l2^2-((\l1^2+\l2^2-\l3^2)/(2*\l1))^2)*20}
\real{rep1=(\rep-1)/10}
\real{rep2=(\rep+1)/10}

\text{enonc2=<li>Tracer un triangle ABC tel que :
<div class="wimscenter">AC = \l1 cm&#44; AB = \l2 cm et BC = \l3 cm.</div></li>
<li>Construire le triangle AEC, symétrique du triangle ABC par rapport à la droite (AC).</li>}

\text{enonc3=Mesurer le segment BE.}
\text{enonc4=BE}
#endif

#if defined TARGET_oefconstaxe3
# define NUM 3
\real{l1=randint(25..45)}
\real{l2=randint(20..\l1-3)*2/10}
\real{l1=\l1*2/10}
\integer{d=sqrt(\l2^2+\l1^2)*10}
\integer{rep=\l1*\l2*200/\d}
\real{rep1=(\rep-1)/10}
\real{rep2=(\rep+1)/10}

\text{enonc2=<li>Tracer un rectangle EFGH tel que :
<div class="wimscenter">EF = \l1 cm et EG = \l2 cm.</div></li>
<li>Construire le rectangle HRFS, symétrique du rectangle EFGH par rapport à la droite (HF).</li>
<li>Le point R est le symétrique du point E et le point S est le symétrique du point G.</li>}

\text{enonc3=Mesurer le segment ER.}
\text{enonc4=ER}
#endif
#if defined TARGET_oefconstaxe4
# define NUM 4
\real{l1=randint(15..30)}
\real{l2=randint(10..\l1*2-5)*2/10}
\real{l1=\l1*2/10}
\integer{rep=sqrt(\l1^2-\l2^2/4)*20}
\real{rep1=(\rep-1)/10}
\real{rep2=(\rep+1)/10}

\text{enonc2=<li>Tracer un cercle de centre A et de rayon \l1 cm.</li>
<li>Tracer une corde [EF] du cercle telle que EF = \l2 cm.</li>
<li>Construire le cercle de centre S, symétrique du cercle de centre A par rapport à la droite (EF).</li>
}

\text{enonc3=Mesurer le segment AS.}
\text{enonc4=AS}
#endif
#if defined TARGET_oefconstaxe5
# define NUM 5
\real{l1=randint(30..55)}
\real{l2=randint(20..\l1-5)*2/10}
\real{l1=\l1*2/10}
\real{l=sqrt(\l2^2/4+\l1^2/4)}
\integer{rep=sqrt(\l1^2-(\l1^4/(4*\l^2)))*20}
\real{rep1=(\rep-1)/10}
\real{rep2=(\rep+1)/10}

\text{enonc2=<li>Tracer un losange ABCE tel que :
<div class="wimscenter">BE = \l1 cm et AC = \l2 cm.</div></li>
<li>Construire le losange BCRS, symétrique du losange ABCE par
rapport à la droite (BC).</li>}

\text{enonc3=Mesurer le segment ER.}
\text{enonc4=ER}
#endif
#include "lang_titles.inc"
\statement{
\enonc1
<ul>
\enonc2
<li>\enonc3</li>
</ul>
<div class="wimscenter"><label for="reply1">\enonc4 =</label>
\embed{r1,10} cm.</div>

<div class="wims_instruction">Vous utiliserez le point comme séparateur décimal.</div>
}

\answer{}{\rep1,\rep2}{type=range}
