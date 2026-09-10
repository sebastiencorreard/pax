target=oefvocparper1 oefvocparper2 oefvocparper3 oefvocparper4 oefvocparper5
\langage{fr}
\author{Jean-Luc,Donadoni}
\email{jluc.donadoni@laposte.net}
\format{html}
#define TITRE Vocabulaire parallèle perpendiculaire
#if defined TARGET_oefvocparper1
# define NUM 1
#endif
#if defined TARGET_oefvocparper2
# define NUM 2
#endif
#if defined TARGET_oefvocparper3
# define NUM 3
#endif
#if defined TARGET_oefvocparper4
# define NUM 4
#endif
#if defined TARGET_oefvocparper5
# define NUM 5
#endif
\title{TITRE NUM}

\text{nom=shuffle(A,B,C,E,F,G,R,S,T)}
#if defined TARGET_oefvocparper1 || defined TARGET_oefvocparper2
\integer{pe=randint(-80..80)}
\integer{pa=random(+,-)randint(20..80)}
#endif
#if defined TARGET_oefvocparper3
\integer{pe=randint(-50..50)}
\integer{pa=random(+,-)randint(30..60)}
\integer{ang=random(+,-)randint(10..80)}
#endif
#if defined TARGET_oefvocparper4
\integer{pe=randint(0..80)}
\integer{pa=random(+,-)randint(20..70)}
\integer{ps=randint(20..80)}
#endif
#if defined TARGET_oefvocparper5
\integer{pe=50}
\integer{pa=50}
\integer{ps=20}
#endif
\text{d1=-100,0,100,0}
\text{d2=\pe,-100,\pe,100}
\text{d3=-100,\pa,100,\pa}
#if defined TARGET_oefvocparper1 || defined TARGET_oefvocparper2
\text{dess1=draw(200,200
xrange -100,100
yrange -100,100
square \pe,10,10,red
text black,\pe-10,-5,medium,\nom[1]
text black,-95,20,medium,d1
text black,\pe+5,95,medium,d2
segment \d1,black
segment \d2,black
)}
#endif
#if defined TARGET_oefvocparper3
\text{dess1=draw(200,200
xrange -100,100
yrange -100,100
rotate \ang
segment \pe,10,\pe+10,10,red
segment \pe+10,0,\pe+10,10,red
text black,\pe-10,-5,medium,\nom[1]
text black,-75,20,medium,d1
text black,\pe+5,75,medium,d2
segment \d1,black
segment \d2,black
)}
#endif
#if defined TARGET_oefvocparper1 || defined TARGET_oefvocparper2
\text{dess2=draw(200,200
xrange -100,100
yrange -100,100
square \pe,10,10,red
square \pe,\pa,10,red
text black,\pe-10,-5,medium,\nom[1]
text black,-95,20,medium,d1
text black,\pe+5,95,medium,d2
segment \d1,black
segment \d2,black
segment \d3,black
text black,85,\pa+15,medium,d3
)}
#endif
#if defined TARGET_oefvocparper3
\text{dess2=draw(200,200
xrange -100,100
yrange -100,100
rotate \ang
segment \pe,10,\pe+10,10,red
segment \pe+10,0,\pe+10,10,red
segment \pe,\pa+10,\pe+10,\pa+10,red
segment \pe+10,\pa,\pe+10,\pa+10,red
text black,\pe-10,-5,medium,\nom[1]
text black,-75,20,medium,d1
text black,\pe+5,75,medium,d2
segment \d1,black
segment \d2,black
segment \d3,black
text black,75,\pa+15,medium,d3
)}
#endif
#if defined TARGET_oefvocparper4
\text{d4=-100+\ps,-100,-30+\ps,100}
\text{dess=draw(200,200
xrange -100,100
yrange -100,100
square \pe,10,10,red
square \pe,\pa,10,red
text black,-95,20,medium,d1
text black,\pe+5,-85,medium,d2
segment \d1,black
segment \d2,black
segment \d3,black
text black,85,\pa+15,medium,d3
segment \d4,black
text black,-120+\ps,-85,medium,d4)}

\matrix{list=d1,d2,2
d1,d4,2
d2,d3,2
d2,d4,2
d3,d4,2
d1,d3,1
d3,d1,1}
#endif
#if defined TARGET_oefvocparper5
\text{d4=-100+\ps,-100,-30+\ps,100}
\text{dess=draw(200,200
xrange -100,100
yrange -100,100
square \pe,10,10,red
square \pe,\pa,10,red
text black,-95,20,medium,d1
text black,\pe+5,-85,medium,d2
segment \d1,black
segment \d2,black
segment \d3,black
text black,85,\pa+15,medium,d3
segment \d4,black
text black,-120+\ps,-85,medium,d4
text black,\pe-10,\pa+15,medium,\nom[1]
text black,\pe-10,-5,medium,\nom[2]
text black,\ps-60,-5,medium,\nom[3]
text black,\ps-55,\pa+15,medium,\nom[4]
)}
#endif
#if defined TARGET_oefvocparper1 || defined TARGET_oefvocparper2 || defined TARGET_oefvocparper3
\text{reps=perpendiculaires,parallèles}
\text{list=d2,d3}
\text{a=randint(1..2)}
\text{fig=<img src="\dess1" alt="">,<img src="\dess2" alt="">}
\text{fig=\fig[\a]}
#endif
#if defined TARGET_oefvocparper4
\text{reps=parallèles,sécantes}
\text{a=randint(1..7)}
\text{list=row(\a,\list)}
\text{fig=<img src="\dess" alt="">}
#endif
#if defined TARGET_oefvocparper1 || defined TARGET_oefvocparper2 || defined TARGET_oefvocparper3
\text{enonc=Les deux droites d1 et \list[\a] sont}
#endif
#if defined TARGET_oefvocparper4
\text{enonc=Les deux droites \list[1] et \list[2] sont}
#endif
#if defined TARGET_oefvocparper5
\matrix{list=Les droites d2, et d3 sont ,sécantes ,et perpendiculaires ,au point,\nom[1].
La perpendiculaire, à la droite d3, passant par le point, \nom[1], est la droite d2.
Les droites d1, et d2 sont ,sécantes ,et perpendiculaires ,au point,\nom[2].
La perpendiculaire, à la droite d2, passant par le point, \nom[2], est la droite d1.
Les droites d1, et d4 sont ,sécantes, au point,\nom[3].
Les droites d3, et d4 sont ,sécantes, au point,\nom[4].
}
\text{reps=\nom[1],\nom[2],\nom[3],\nom[4],parallèles,sécantes,perpendiculaires}
\text{a=randint(1..6)}
\text{list=row(\a,\list)}
\text{fig=<img src="\dess" alt="">}
\text{enonc=Reconstituer la phrase décrivant le dessin.}
#endif
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\fig</div>
 <div class="medium_size text_col">
\enonc
#if defined TARGET_oefvocparper1 || defined TARGET_oefvocparper4
\embed{r1}.
#endif
#if defined TARGET_oefvocparper2 || defined TARGET_oefvocparper3
\embed{r1,15}.
#endif
 </div>
</div>
#if defined TARGET_oefvocparper5
\embed{r1,180x50}
#endif
}
#if defined TARGET_oefvocparper1
\answer{}{\a;\reps}{type=menu}{option=shuffle}
#endif
#if defined TARGET_oefvocparper2 || defined TARGET_oefvocparper3
\answer{}{\reps[\a]}{type=raw}{option=nocase}
#endif
#if defined TARGET_oefvocparper4
\answer{}{\list[3];\reps}{type=menu}{option=shuffle}
#endif
#if defined TARGET_oefvocparper5
\answer{}{\list;\reps}{type=clickfill}{option=shuffle}
#endif
