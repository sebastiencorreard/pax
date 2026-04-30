target=choix1,choix2,choix3,choix4,choix5

#define TITRE Théorème ou réciproque
\author{Fabrice,Guerimand}
\email{fguerima@free.fr}
#if defined TARGET_choix1
# define NUM 1
#endif
#if defined TARGET_choix2
# define NUM 2
#endif
#if defined TARGET_choix3
# define NUM 3
#endif
#if defined TARGET_choix4
# define NUM 4
#endif
#if defined TARGET_choix5
# define NUM 5
#endif
\title{TITRE NUM}

\matrix{sommets=A,B,C,D,E,F,G
E,F,G,H,I,J,K
M,N,O,P,Q,R,S}
\text{sommet=randrow(\sommets)}
\text{sommet=shuffle(\sommet)}

\text{A=item(1,\sommet)}
\text{B=item(2,\sommet)}
\text{C=item(3,\sommet)}
\text{D=item(4,\sommet)}
\text{E=item(5,\sommet)}
\text{F=item(6,\sommet)}
\text{G=item(7,\sommet)}

\integer{xrange=200}
\integer{yrange=200}

\text{dessin1=segment 20,20,180,130,black
segment 20,20,50,180,black
segment 180,130,50,180,black
segment 35,100,100,75,black
text black,10,10,medium,\A
text black,190,135,medium,\B
text black,35,185,medium,\C
text black,25,100,medium,\E
text black,115,70,medium,\D}

\text{dessin2=segment 20,80,180,120,black
segment 90,30,110,170,black
segment 20,80,90,30,black
segment 180,120,110,170,black
text black,110,90,medium,\A
text black,5,70,medium,\B
text black,100,25,medium,\C
text black,95,170,medium,\E
text black,185,120,medium,\D}

#if defined TARGET_choix1
 \text{enonce=Dans cette situation, quel théorème faudrait-il utiliser pour
 démontrer que les droites \((\D \E)\) et \((\B \C)\) sont parallèles}
 \text{good=2}
 \integer{ch=randint(1..2)}
 \text{dessin=\ch=1?\dessin1:\dessin2}
 \text{list=Le théorème de Thalès,La réciproque du théorème de Thalès}
#endif

#if defined TARGET_choix2
 \text{enonce=Dans cette situation, quel théorème faudrait-il utiliser pour démontrer que
   les droites \((\D \E)\) et \((\B \C)\) ne sont  pas parallèles}
 \text{good=1}
 \integer{ch=randint(1..2)}
 \text{dessin=\ch=1?\dessin1:\dessin2}
 \text{list=Le théorème de Thalès,La réciproque du théorème de Thalès}
#endif
#if defined TARGET_choix3
 \integer{ch=randint(1..2)}
 \real{k=randitem(0.7,0.8,0.9,1.1,1.2)}
 \text{dessin=\ch=1?\dessin1:\dessin2}
 \integer{b=randint(5..19)}
 \integer{a=\b+randint(\b/3..2*\b/3)}
 \real{c=\k*\a}
 \real{d=\k*\b}
 \text{enonce=<li>\(\A \C = \a\) ; \(\A \E = \b\) ; \(\A \B = \c\) ; \(\A \D = \d\).</li>
 <li>Le but est de décider si les droites \((\D \E)\) et \((\B \C)\) sont parallèles ou non.</li>
 <li>Quel théorème faut-il utiliser asis(?)</li>}
 \text{good=2}
 \text{list=Le théorème de Thalès,La réciproque du théorème de Thalès}
#endif
#if defined TARGET_choix4
 \integer{ch=randint(1..2)}
 \text{k=shuffle(0.7,0.8,0.9,1.1,1.2)}
 \text{dessin=\ch=1?\dessin1:\dessin2}
 \integer{b=randint(5..19)}
 \integer{a=\b+randint(\b/3..2*\b/3)}
 \real{c=\k[1]*\a}
 \real{d=\k[2]*\b}
 \text{enonce=<li>\(\A \C = \a\) ; \(\A \E = \b\) ; \(\A \B = \c\) ; \(\A \D = \d\).</li><li>
  Le but est de décider si les droites \((\D \E)) et \((\B \C)) sont parallèles ou non.</li><li>
  Quel théorème faut-il utiliser asis(?)</li>}
 \text{good=1}
 \text{list=Le théorème de Thalès,La réciproque du théorème de Thalès}
#endif

#if defined TARGET_choix5
 \text{dessin=range 0,200,0,200
segment 25,25,50,200,black
segment 25,25,175,200,black
segment 25,25,200,75,black
segment 38,113,86,96,red
segment 86,96,108,49,red
segment 49,191,140,159,red
segment 140,159,183,70,red
text black,23,23,medium,\A
text black,39,195,medium,\B
text black,182,68,medium,\C
text black,27,117,medium,\D
text black,108,45,medium,\E
text black,82,110,medium,\F
text black,137,175,medium,\G}
 \integer{good=randint(1..2)}
 \integer{b=randint(4..19)}
 \integer{a=\b+randint(1/3*\b..2/3*\b)}
 \text{k=shuffle(0.7,0.8,0.9,1.1,1.2,1.3)}
 \if{\good=1}{
  \real{c=\k[1]*\a*randitem(0.9,0.8)}
  \real{d=\k[1]*\b}
  \real{e=\k[2]*\a}
  \real{f=\k[2]*\b}
 }{
  \real{c=\k[1]*\a}
  \real{d=\k[1]*\b}
  \real{e=\k[2]*\a}
  \real{f=\k[2]*\b*randitem(1.1,1.2)}
 }
 \text{enonce=<li>\(\A \C = \a\)  ;  \(\A \E = \b\) ; \(\A \B = \c\); \(\A \D = \d\) ;
  \(\A \F = \f\) ; \(\A \G = \e\).</li><li>
  Le but est de décider si les droites \((\D \E)\) et \((\B \C)\) sont parallèles ou non.</li><li>
  Quel théorème faut-il utiliser asis(?)</li>}
  \text{list=Le théorème de Thalès (ou sa contraposée),La réciproque du théorème de Thalès}
#endif

\text{Good=item(\good,\list)}
\text{figure=draw(\xrange,\yrange
\dessin)}

\statement{
#if defined TARGET_choix1 || defined TARGET_choix2
 \enonce
#else
<ul class="wims_nopuce">
\enonce
</ul>
#endif
<div class="wimscenter">
<img src="\figure" alt=""></div>
}

\choice{Réponse}{\Good}{\list}
