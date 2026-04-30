target = pointsur pointsurcart
#define TITRE Point sur la droite ?
#if defined TARGET_pointsur
\title{TITRE (eq. réduite)}
#endif

#if defined TARGET_pointsurcart
\title{TITRE (eq. cartésienne)}
#endif
\language{fr}
\range{-5..5}
\author{Thomas, Charon;Bruno, Mifsud}##Complété par Cyrille Douriez##
\email{thomas.charon@ac-lyon.fr;communaute.mutuwims@laposte.net}
\keywords{line,equations}
\computeanswer{yes}
\format{html}
\precision{10000}

\text{confparm1= items(\confparm1)=0 ? 1:\confparm1}

\integer{cas=randomitem(1,2,3,3,3)}
\integer{rep=randomitem(1,2)}
\integer{k=randint(-10..10)}
\integer{p=randint(-10..10)}
\integer{m=randint(1..10)*randomitem(-1,1)}

#if defined TARGET_pointsur
\text{tp=\p<0?\p:+\p}
\text{tx=\m=-1?-x:\m x}
\text{tx=\m=1?x}
\text{eq3=\p=0?\tx:\tx \tp}
#endif
#if defined TARGET_pointsurcart
\integer{r=randint(2..4)*randint(-1,1)}
\function{eq4=maxima(\r*\m*x-\r*y+\r*\p)}

#endif



#if defined TARGET_pointsur
\text{eq=item(\cas,x=\k,y=\p,y=\eq3)}
\text{mot=réduite}
#endif
#if defined TARGET_pointsurcart
\text{eq=item(\cas,x-\k=0,y-\p=0,\eq4=0)}
\text{mot=cartésienne}
#endif

\function{f=maxima(\m*x+\p)}

\integer{xa=item(\cas,\k,randint(-10..10),randint(-10..10))}
\integer{ya=item(\cas,randint(-10..10),\p,\m*\xa+\p)}
\integer{d=randint(1..2)*randomitem(-1,1)} %%%% petit écart au cas où la figure est affichée%%%
%%%% coord du point qui n'est pas sur la droite
\integer{xb=item(\cas,\k+\d,randint(-10..10),randint(-10..10))}
\integer{yb=item(\cas,randint(-10..10),\p+\d,\m*\xb+\p+\d)}

#if defined TARGET_pointsurcart
%%cas=1
\if{\rep=1}{
\text{xak=wims(replace internal x by \xa in maxima(x-\k))}
\text{yak=wims(replace internal y by \ya in maxima(y-\p))}
}
{\text{xak=wims(replace internal x by \xb in maxima(x-\k))}
\integer{xakn=\xb-\k}
\text{yak=wims(replace internal y by \yb in maxima(y-\p))}
\integer{yakn=\yb-\p}
}

\integer{eq4b=\r*\m*\xb-\r*\yb+\r*\p}
\text{eq4txta=\xa>0?wims(replace x by \xa in \eq4):wims(replace x by (\xa) in \eq4)}
\text{eq4txta=\ya>0?wims(replace y by \ya in \eq4txta):wims(replace y by (\ya) in \eq4txta)}
\text{eq4txtb=\xb>0?wims(replace x by \xb in \eq4):wims(replace x by (\xb) in \eq4)}
\text{eq4txtb=\yb>0?wims(replace y by \yb in \eq4txtb):wims(replace y by (\yb) in \eq4txtb)}
#endif
\text{sol=appartient ,n'appartient pas}

%%%%%%%%%%%%Image
\if{\confparm1=1}{
\text{imgtemp=xrange -100,100
yrange -100,100
hline 0,0,black
vline 0,0,black
parallel -50,-2,-50,2,100,0,2,black
parallel -2,-50,2,-50,0,100,2,black
text black , 50,-0.5,small , 50
text black , 1,50,small , 50
text black , 2,-1,small , O
linewidth 1.5
}

\if{\cas==1}{\text{plotdrt=vline \k,0,blue}}
\if{\cas==2}{\text{plotdrt=hline 0,\p,blue}}
\if{\cas==3}{\text{plotdrt=plot blue,\f}}

\text{imgpt=\rep=1?crosshairs red,\xa,\ya:crosshairs red,\xb,\yb}
\text{image=draw(90,90
\imgtemp
\imgpt
\plotdrt

)}


\text{img=<img src="\image" alt="représentation graphique" style="float:right;margin-top:-1em">}
\text{imagecorr=draw(100,100
\imgtemp
\imgpt
\plotdrt

)}
\text{imgcorr=<img src="\imagecorr" alt="représentation graphique" style="float:right;margin-left:0.5em;margin-right:0.2em;">}
}
%%%Eléments pour le corrigé%%%
\integer{yac=\rep=1?\m*\xa+\p:\m*\xb+\p}
\if{\rep=1}{
\if{\xa>0}{\text{tcx=\m=1?\xa:\m \times \xa}}{\text{tcx=\m=-1?-(\xa):\m \times (\xa)}}
}{
\if{\xb>0}{\text{tcx=\m=1?\xb:\m \times \xb}}{\text{tcx=\m=-1?-(\xb):\m \times (\xb)}}}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\statement{
<div class=wims_question>\img
On considère la droite \((d)) d'équation \mot \(\eq).
<br >
Le point \(A) \if{\rep=1}{\((\xa;\ya))}{\((\xb;\yb))} \embed{reply 1} à la droite \((d)) </div>
}
\answer{}{\rep;\sol}{type=menu}

\solution{\imgcorr

<p> Il faut vérifier si les coordonnées de \(A) \if{\rep=1}{\((\xa;\ya))}{\((\xb;\yb))} vérifient l'équation \(\eq).</p>
#if defined TARGET_pointsur
\if{\cas=1}{Ici :\(x_A=)\if{\rep=1}{\(\k)}{\(\xb \neq \k)} donc \(A) \if{\rep=1}{appartient}{n'appartient pas} à la droite \((d)). }
\if{\cas=2}{Ici : \(y_A=)\if{\rep=1}{\(\p)}{\(\yb \neq \p)} donc \(A) \if{\rep=1}{appartient}{n'appartient pas} à la droite \((d)). }

\if{\cas>2}{Pour \(x=x_A)=\if{\rep=1}{\(\xa)}{\(\xb)}, l'équation \mot de la droite donne \(y= \tcx \tp=) \if{\rep=1}{\(\ya=y_A)}{\(\yac \neq y_A)} donc \(A) \if{\rep=1}{appartient}{n'appartient pas} à la droite \((d)). }
#endif
#if defined TARGET_pointsurcart
\if{\cas=1}{Ici  pour \(x=x_A), \(\xak)\if{\rep=1}{\({}=0)}{\({=\xakn} \neq 0)} donc \(A) \if{\rep=1}{appartient}{n'appartient pas} à la droite \((d)). }
\if{\cas=2}{Ici pour \(y=y_A), \(\yak)\if{\rep=1}{\({}=0)}{\({=\yakn} \neq 0)} donc \(A) \if{\rep=1}{appartient}{n'appartient pas} à la droite \((d)). }
\if{\cas>2}{Pour \(x=x_A={})\if{\rep=1}{\(\xa)}{\(\xb)} et \(y=y_A={})\if{\rep=1}{\(\ya)}{\(\yb)}, l'équation \mot de la droite donne :
\if{\rep==1}{\(\eq4txta = 0)}{\(\eq4txtb)\({}=\eq4b \neq 0)}
 donc \(A) \if{\rep==1}{appartient}{n'appartient pas} à la droite \((d)). }
#endif

}
