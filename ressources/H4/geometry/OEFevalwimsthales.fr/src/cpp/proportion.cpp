target=proportion1,proportion2,proportion3,proportion4,proportion5
#define TITRE Conservation de proportions
\email{fguerima@free.fr}
\author{Fabrice,Guerimand}
#if defined TARGET_proportion1
# define NUM 1
#endif
#if defined TARGET_proportion2
# define NUM 2
#endif
#if defined TARGET_proportion3
# define NUM 3
#endif
#if defined TARGET_proportion4
# define NUM 4
#endif
#if defined TARGET_proportion5
# define NUM 5
#endif
\title{TITRE NUM}

\matrix{sommets=A,B,C,D,E,F
E,F,G,H,I,J
M,N,O,P,Q,R}
\text{sommet=randrow(\sommets)}
\text{sommet=shuffle(\sommet)}

\text{sommet=row(1,\sommets)}

\text{A=item(1,\sommet)}
\text{B=item(2,\sommet)}
\text{C=item(3,\sommet)}
\text{D=item(4,\sommet)}
\text{E=item(5,\sommet)}
\text{F=item(6,\sommet)}


\text{k=shuffle(2,3,3,4,2,4)}

#if defined TARGET_proportion1
 \integer{den=randint(3..5)}
 \integer{num=randint(1..\den-1)}
 \text{k=\k[1],\k[2],\k[3],\k[2]}
 \integer{my=-max(\k[2],\k[4])*\den-1}
 \integer{Mx=\k[3]*\den+1}
 \integer{mx=-\k[1]*\den-1}
 \integer{nby=1-\my}
 \integer{nbx=\Mx-\mx+1}
 \text{dessin=range \mx,\Mx,\my,1
parallel \mx,1,\Mx,1,0,-1,\nby,grey
parallel \mx,1,\mx,\my,1,0,\nbx,grey
triangle 0,0,-\k[1]*\den,-\k[2]*\den,\k[3]*\den,-\k[4]*\den,black
segment -\k[1]*\num,-\k[2]*\num,\k[3]*\num,-\k[4]*\num,black
text black,0,0.7,medium,\A
text black,-\k[1]*\num-0.7,-\k[2]*\num+0.7,medium,\D
text black,-\k[1]*\den,-\k[2]*\den,medium,\B
text black,\k[3]*\num+0.7,-\k[4]*\num+0.7,medium,\E
text black,\k[3]*\den,-\k[4]*\den,medium,\C}
 \text{rap=randitem(\frac{\A \D}{\A \B},\frac{\A \E}{\A \C})}
#endif

#if defined TARGET_proportion2
 \integer{den=randint(3..5)}
 \integer{num=randint(1..\den-1)}
 \text{k=\k[2]=\k[4]?\k[1],\k[2],\k[3],\k[5]}
 \integer{my=-max(\k[2],\k[4])*\den-1}
 \integer{Mx=\k[3]*\den+1}
 \integer{mx=-\k[1]*\den-1}
 \integer{nby=1-\my}
 \integer{nbx=\Mx-\mx+1}
 \text{dessin=range \mx,\Mx,\my,1
parallel \mx,1,\Mx,1,0,-1,\nby,grey
parallel \mx,1,\mx,\my,1,0,\nbx,grey
triangle 0,0,-\k[1]*\den,-\k[2]*\den,\k[3]*\den,-\k[4]*\den,black
segment -\k[1]*\num,-\k[2]*\num,\k[3]*\num,-\k[4]*\num,black
text black,0,0.7,medium,\A
text black,-\k[1]*\num-0.7,-\k[2]*\num+0.7,medium,\D
text black,-\k[1]*\den,-\k[2]*\den,medium,\B
text black,\k[3]*\num+0.7,-\k[4]*\num+0.7,medium,\E
text black,\k[3]*\den,-\k[4]*\den,medium,\C}
 \text{rap=randitem(\frac{\A \D}{\A \B},\frac{\A \E}{\A \C})}
#endif

#if defined TARGET_proportion3
 \text{den=shuffle(1,2,3,4)}
 \integer{num=\den[1]}
 \integer{den=\den[2]}
 \text{k=\k[2]=\k[4]?\k[1],\k[2],\k[3],\k[5]}
 \integer{my=-max(\k[2]*\den,\k[4]*\den)-1}
 \integer{My=max(\k[2]*\num,\k[4]*\num)+1}
 \integer{Mx=max(\k[1]*\num,\k[3]*\den)+1}
 \integer{mx=-max(\k[1]*\den,\k[3]*\num)-1}
 \integer{nby=\My-\my+1}
 \integer{nbx=\Mx-\mx+1}
 \text{dessin=range \mx,\Mx,\my,\My
parallel \mx,\My,\Mx,\My,0,-1,\nby,grey
parallel \mx,\my,\mx,\My,1,0,\nbx,grey
triangle 0,0,-\k[1]*\den,-\k[2]*\den,\k[3]*\den,-\k[4]*\den,black
triangle 0,0,\k[1]*\num,\k[2]*\num,-\k[3]*\num,\k[4]*\num,black
text black,0,-1,medium,\A
text black,\k[1]*\num,\k[2]*\num+1,medium,\D
text black,-\k[1]*\den,-\k[2]*\den,medium,\B
text black,-\k[3]*\num,\k[4]*\num+1,medium,\E
text black,\k[3]*\den,-\k[4]*\den,medium,\C}
 \text{rap=randitem(\frac{\A \D}{\A \B},\frac{\A \E}{\A \C})}
#endif

#if defined TARGET_proportion4
 \integer{den=randint(3..5)}
 \integer{num=randint(1..\den-1)}
 \text{k=2,2,shuffle(1,3)}
 \integer{my=-max(\k[2],\k[4])*\den-1}
 \integer{Mx=\k[3]*\den+1}
 \integer{mx=-\k[1]*\den-1}
 \real{vx=\k[1]/\k[2]}
 \text{dessin=range \mx,\Mx,\my,1
triangle 0,0,-\k[1]*\den,-\k[2]*\den,\k[3]*\den,-\k[4]*\den,black
segment -\k[1]*\num,-\k[2]*\num,\k[3]*\num,-\k[4]*\num,black
linewidth 2
parallel -\k[1]*\den-0.5+\vx,-\k[2]*\den+1,-\k[1]*\den+0.5+\vx,-\k[2]*\den+1,\vx,1,\k[2]*(\den-\num)-1,grey
parallel -\k[1]*\num-0.5+\vx,-\k[2]*\num+1,-\k[1]*\num+0.5+\vx,-\k[2]*\num+1,\vx,1,\k[2]*\num-1,grey
text black,0,0.7,medium,\A
text black,-\k[1]*\num-0.7,-\k[2]*\num+0.7,medium,\D
text black,-\k[1]*\den,-\k[2]*\den,medium,\B
text black,\k[3]*\num+0.7,-\k[4]*\num+0.7,medium,\E
text black,\k[3]*\den,-\k[4]*\den,medium,\C}
 \text{rap=randitem(\frac{\A \D}{\A \B},\frac{\A \E}{\A \C})}
 \text{comp=Les droites \((\E \D)\) et \((\B \C)\) sont parallèles.}
#endif

#if defined TARGET_proportion5
 \text{den=shuffle(1,2,3,4)}
 \integer{num=\den[1]}
 \integer{den=\den[2]}
 \text{k=\k[1],\k[2],\k[3],0}
 \integer{my=-max(\k[2]*\den,\k[4]*\den)-1}
 \integer{My=max(\k[2]*\num,\k[4]*\num)+1}
 \integer{Mx=max(\k[1]*\num,\k[3]*\den)+1}
 \integer{mx=-max(\k[1]*\den,\k[3]*\num)-1}
 \real{vx=(\k[1]+\k[3])/\k[2]}
 \text{dessin=range \mx,\Mx,\my,\My
triangle 0,0,-\k[1]*\den,-\k[2]*\den,\k[3]*\den,-\k[4]*\den,black
triangle 0,0,\k[1]*\num,\k[2]*\num,-\k[3]*\num,\k[4]*\num,black
linewidth 2
parallel -\k[3]*\num-0.5+\vx,1,-\k[3]*\num+0.5+\vx,1,\vx,1,\k[2]*\num-1,grey
parallel -\k[1]*\den-0.5+\vx,-\k[2]*\den+1,-\k[1]*\den+0.5+\vx,-\k[2]*\den+1,\vx,1,\k[2]*\den-1,grey
text black,0,-0.5,medium,\A
text black,\k[1]*\num,\k[2]*\num+1,medium,\D
text black,-\k[1]*\den,-\k[2]*\den,medium,\B
text black,-\k[3]*\num,\k[4]*\num+1,medium,\E
text black,\k[3]*\den,-\k[4]*\den,medium,\C}
 \text{rap=\frac{\A \E}{\A \C}}
 \text{comp=Les droites \((\E \D)\) et \((\B \C)\) sont parallèles.
 }
#endif
\text{name_hint=Les traits gris délimitent des segments de même longueur.}
\text{image=draw(300,300
\dessin)}

\statement{
<ul class="wims_nopuce">
 <li>
  En utilisant la figure ci-dessous calculer le rapport \(\rap).
 </li><li>
 \comp
  <div class="wimscenter"><img src="\image" alt=""></div>
</li></ul>
<div class="wims_instruction">
\name_hint
</div>
}

\answer{\(\rap)}{\num/\den}{type=numexp}
