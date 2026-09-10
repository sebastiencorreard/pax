target=loi1 loi2 loi3 loi4 loi5 interunion1
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
#if defined TARGET_loi1 || defined TARGET_interunion1
# define NUM 1
# endif
#if defined TARGET_loi2
# define NUM 2
# endif
#if defined TARGET_loi3
# define NUM 3
# endif
#if defined TARGET_loi4
# define NUM 4
# endif
#if defined TARGET_loi5
# define NUM 5
# endif
\text{consig=Donner les valeurs exactes en utilisant des fractions.}
#include "lang_titles.inc"

#if defined TARGET_loi1
\integer{k1=randint(3..6)}
\integer{k2=randint(3..6)}
\integer{k2=\k1=\k2?\k2+1}
\integer{k31=randint(20..30)}
\integer{k32=randint(50,80,100)-\k31}
\integer{k41=randint(36..42)*1000}
\integer{k42=randint(200..300)}
\integer{k5=randint(20..40)}
\text{nombre=un,deux,trois,quatre,cinq,six,sept,huit,neuf,dix}
\text{data= « Survivre une heure sous un mètre de neige »,On a une chance sur \nombre[\k1] de survivre une heure sous un mètre de neige,1/\k1
  « Partir en vacances d'hiver »,Un français sur \nombre[\k2] part en vacances d'hiver,1/\k2
  « Être une femme »,Dans cette assemblée&#44; il y a \k31 femmes pour \k32 hommes,\k31/(\k31+\k32)
  « Présenter un défaut »,\k41 voitures sont sorties en l'an 2000 de la chaîne de montage de cette entreprise dont \k42 présentaient un défaut,\k42/\k41
  « Faire de l'équitation »,Dans ce club de vacances&#44; \k5 % des personnes font de l'équitation,0.\k5
}
\text{ind=shuffle(5)}
\text{ev=}
\text{ph=}
\text{rep=}
\for{i=1 to 3}{
 \text{cedata=row(\ind[\i],\data)}
 \text{ev=wims(append item \cedata[1] to \ev)}
 \text{ph=wims(append item \cedata[2] to \ph)}
 \rational{r=\cedata[3]}
 \text{rep=wims(append item \r to \rep)}
}

\statement{
Traduire, en termes de probabilité, les phrases suivantes
correspondant à l'événement \(A\) :
<div class="wims_question">
<ol>
<li>\(A\) \ev[1]<br>
 \ph[1] : <label for="reply1">\(P(A)=\)</label>\embed{reply1,7}</li>
<li>\(A\) \ev[2]<br>
 \ph[2] : <label for="reply2">\(P(A)=\)</label>\embed{reply2,7}</li>
<li>\(A\) \ev[3]<br>
 \ph[3] : <label for="reply3">\(P(A)=\)</label>\embed{reply3,7}</li>
</ol></div>
}
\answer{Phrase 1}{\rep[1]}{type=numexp}
\answer{Phrase 2}{\rep[2]}{type=numexp}
\answer{Phrase 3}{\rep[3]}{type=numexp}
#endif

#if (defined TARGET_loi2 || defined TARGET_interunion1 )
\integer{a=randint(20,25,32,40)}
\integer{bf=randint(10..\a-6)}
\integer{bg=\a-\bf}
\integer{cf=randint(5..\bf)}
\integer{cg=randint(5..\bg)}
\integer{df=\bf-\cf}
\integer{dg=\bg-\cg}
\integer{c=\cf+\cg}
\integer{d=\df+\dg}
\rational{p1=\cf/\a}
\rational{p2=\df/\a}
\rational{p3=\cg/\a}
\rational{p4=\dg/\a}
\rational{rep1=\bg/\a}
\rational{rep4=\d/\a}




\statement{<p>
Dans une classe de 1ère S de \a élèves, il y a \bf filles
et \cg des \c élèves qui apprennent l'espagnol sont des garçons.
</p>
#if defined TARGET_loi2
<div class="wims_question">
 Compléter le tableau à double entrée en nombres d'élèves.

<table class="wimscenter wimsborder">
<tr><td>&nbsp;</td><th>Filles</th><th>Garçons</th><th>Total</th></tr>
<tr><td>apprenant l'espagnol</td><td>\embed{reply1,3}</td>
<td>\embed{reply2,3}</td><th>\embed{reply3,3}</th></tr>
<tr><td>n'apprenant pas l'espagnol</td>
<td>\embed{reply4,3}</td><td>\embed{reply5,3}</td>
<th>\embed{reply6,3}</th></tr>
<tr><th>Total</th><th>\embed{reply7,3}</th><th>\embed{reply8,3}</th><th>\embed{reply9,3}</th></tr>
</table>
</div>
 On tire au hasard un élève de cette classe.
 <div class="wims_question">
 Compléter le tableau de cette loi de probabilité.
<table class="wimscenter wimsborder">
<tr><th>Elèves</th><th>Filles<br>apprenant l'espagnol</th>
<th>Filles<br>n'apprenant pas l'espagnol</th>
<th>Garçons <br>apprenant l'espagnol</th>
<th>Garçons <br>n'apprenant pas l'espagnol</th></tr>
<tr><th>Probabilité</th><td>\embed{reply10,4}</td>
<td>\embed{reply11,4}</td>
<td>\embed{reply12,4}</td>
<td>\embed{reply13,4}</td></tr>
</table>
</div>
<div class="wims_instruction">Donner les valeurs exactes des probabilités en utilisant des fractions.</div>
}
\answer{v1}{\cf}{type=numexp}{option=noreduction}
\answer{v2}{\cg}{type=numexp}{option=noreduction}
\answer{v3}{\c}{type=numexp}{option=noreduction}
\answer{v4}{\df}{type=numexp}{option=noreduction}
\answer{v5}{\dg}{type=numexp}{option=noreduction}
\answer{v6}{\d}{type=numexp}{option=noreduction}
\answer{v7}{\bf}{type=numexp}{option=noreduction}
\answer{v8}{\bg}{type=numexp}{option=noreduction}
\answer{v9}{\a}{type=numexp}{option=noreduction}
\answer{p1}{\p1}{type=numexp}{option=noreduction}
\answer{p2}{\p2}{type=numexp}{option=noreduction}
\answer{p3}{\p3}{type=numexp}{option=noreduction}
\answer{p4}{\p4}{type=numexp}{option=noreduction}
#else
<p>On a complété le tableau à double entrée en nombres d'élèves.</p>
<table class="wimscenter wimsborder">
<tr><td>&nbsp;</td><th>Filles</th><th>Garçons</th><th>Total</th></tr>
<tr><th>apprenant l'espagnol</th><td>\cf</td><td>\cg</td><td>\c</td></tr>
<tr><th>n'apprenant pas l'espagnol</th><td>\df</td><td>\dg</td><td>\d</td></tr>
<tr><th>Total</th><td>\bf</td><td>\bg</td><td>\a</td></tr>
</table>
 On tire au hasard un élève de cette classe.
<div class="wims_question">Déterminer les probabilités des événements suivants :
<ul>
<li>\(A\) « c'est un garçon » : \embed{reply1,3}</li>
<li>\(B\) « c'est une fille n'apprenant pas l'espagnol » : \embed{reply2,3}</li>
<li>\(C\) « c'est un garçon apprenant l'espagnol » : \embed{reply3,3}</li>
<li>\(D\) « c'est un élève n'apprenant pas l'espagnol » : \embed{reply4,3}</li>
</ul></div>
<div class="wims_instruction">\consig</div>
}
\answer{un garçon}{\rep1}{type=numexp}{option=noreduction}
\answer{une fille n'apprenant pas l'espagnol}{\p2}{type=numexp}{option=noreduction}
\answer{un garçon apprenant l'espagnol}{\p3}{type=numexp}{option=noreduction}
\answer{un élève n'apprenant pas l'espagnol}{\rep4}{type=numexp}{option=noreduction}
#endif

#endif

#if defined TARGET_loi5
\integer{n1=randint(1..4)}
\integer{n2=\n1+3}
\integer{v=2*\n1}
\text{val=}
\for{i=1 to 7}{
 \text{val=wims(append item \v to \val)}
 \integer{v=\v+1}
}
\text{p=1/16,1/8,3/16,1/4,3/16,1/8,1/16}
\rational{esp=0}
\rational{var=0}
\for{i=1 to 7}{
 \rational{esp=\esp+\p[\i]*\val[\i]}
 \rational{var=\var+\p[\i]*(\val[\i])^2}
}
\rational{var=\var-\esp^2}
\real{sig=sqrt(\var)}
\statement{<p>
On lance deux dés tétraèdriques dont les faces sont numérotées de \n1 à \n2, puis on calcule
la somme des numéros obtenus.
</p>
<div class="wims_question">Déterminer la loi de probabilité de cette expérience.
<table class="wimscenter wimsborder">
<tr><th>Issue</th><td>\val[1]</td><td>\val[2]</td><td>\val[3]</td><td>\val[4]</td><td>\val[5]</td><td>\val[6]</td><td>\val[7]</td><th>Total</th></tr>
<tr><th>Probabilité</th><td>\embed{reply1,3}</td><td>\embed{reply2,3}</td><td>\embed{reply3,3}</td><td>\embed{reply4,3}</td><td>\embed{reply5,3}</td><td>\embed{reply6,3}</td>
<td>\embed{reply7,3}</td><td>\embed{reply8,3}</td></tr></table>
</div><div class="wims_instruction">\consig</div>
}
\answer{p1}{\p[1]}{type=numexp}{option=noreduction}
\answer{p2}{\p[2]}{type=numexp}{option=noreduction}
\answer{p3}{\p[3]}{type=numexp}{option=noreduction}
\answer{p4}{\p[4]}{type=numexp}{option=noreduction}
\answer{p5}{\p[5]}{type=numexp}{option=noreduction}
\answer{p6}{\p[6]}{type=numexp}{option=noreduction}
\answer{p7}{\p[7]}{type=numexp}{option=noreduction}
\answer{Total}{1}{type=numeric}
#endif
#if defined TARGET_loi3
\integer{b=randint(5..10)}
\integer{c=randint(5,10,15,20)+2*\b}
\integer{a=2*\c}
\integer{t=\a+\b+\c}
\rational{p1=\a/\t}
\rational{p2=\b/\t}
\rational{p3=\c/\t}

\statement{
Le cycle d'allumage d'un feu tricolore est le suivant :<br>
Feu vert pendant \a secondes, feu orange pendant \b secondes, feu rouge pendant \c secondes
<div class="wims_question">
En admettant qu'un automobiliste arrive au hasard devant
 l'une des trois positions possibles du feu tricolore, déterminer
 la loi de probabilité de cette expérience aléatoire.

<table class="wimscenter wimsborder">
<tr><th>Feu</th><th>Vert</th><th>Orange</th><th>Rouge</th><th>Total</th></tr>
<tr><th>Probabilité</th><td>\embed{reply1,3}</td><td>\embed{reply2,3}</td>
<td>\embed{reply3,3}</td><td>\embed{reply4,3}</td></tr>
</table></div>
<div class="wims_instruction">\consig</div>
}
\answer{p(Vert)}{\p1}{type=numexp}{option=noreduction}
\answer{p(Orange)}{\p2}{type=numexp}{option=noreduction}
\answer{p(rouge)}{\p3}{type=numexp}{option=noreduction}
\answer{Total}{1}{type=numeric}
#endif

#if defined TARGET_loi4
\integer{a1=randint(5..25)}
\integer{a2=randint(25..65)}
\integer{a3=randint(35..45)}
\integer{a=\a1+\a2+\a3}
\integer{a4=randint(5..300-\a)}
\integer{a=\a+\a4}
\integer{a5=randint(2..340-\a)}
\integer{a=\a+\a5}
\integer{a6=360-\a}
\text{ang=shuffle(\a1,\a2,\a3,\a4,\a5,\a6)}
\text{angs=\ang[1],\ang[1]+\ang[2],\ang[1]+\ang[2]+\ang[3],\ang[1]+\ang[2]+\ang[3]+\ang[4],\ang[1]+\ang[2]+\ang[3]+\ang[4]+\ang[5]}
\text{color=shuffle(red,green,blue,orange,yellow,gray,pink)}
\text{dessin=
 xrange -5,5
 yrange -5,5
 circle 0,0,200,black
 segment 0,0,5,0,black
 segment 0,0,5*cos(\ang[1]*pi/180),5*sin(\ang[1]*pi/180),black
 fill 2*cos(\ang[1]*pi/360),2*sin(\ang[1]*pi/360),\color[1]
 segment 0,0,5*cos((\angs[2])*pi/180),5*sin((\angs[2])*pi/180),black
 fill 3*cos((\ang[1]+\ang[2]/2)*pi/180),3*sin((\ang[1]+\ang[2]/2)*pi/180),\color[2]
 segment 0,0,5*cos((\angs[3])*pi/180),5*sin((\angs[3])*pi/180),black
 fill 3*cos((\angs[2]+\ang[3]/2)*pi/180),3*sin((\angs[2]+\ang[3]/2)*pi/180),\color[3]
 segment 0,0,5*cos((\angs[4])*pi/180),5*sin((\angs[4])*pi/180),black
 fill 3*cos((\angs[3]+\ang[4]/2)*pi/180),3*sin((\angs[3]+\ang[4]/2)*pi/180),\color[4]
 segment 0,0,5*cos((\angs[5])*pi/180),5*sin((\angs[5])*pi/180),black
 fill 3*cos((\angs[4]+\ang[5]/2)*pi/180),3*sin((\angs[4]+\ang[5]/2)*pi/180),\color[5]
 fill 3*cos((\angs[5]+\ang[6]/2)*pi/180),3*sin((\angs[5]+\ang[6]/2)*pi/180),\color[6]
 text black,3*cos((\ang[1]/2)*pi/180),3*sin((\ang[1]/2)*pi/180),medium,A
 text black,3*cos((\ang[1]+\ang[2]/2)*pi/180),3*sin((\ang[1]+\ang[2]/2)*pi/180),medium,B
 text black,3*cos((\angs[2]+\ang[3]/2)*pi/180),3*sin((\angs[2]+\ang[3]/2)*pi/180),medium,C
 text black,3*cos((\angs[3]+\ang[4]/2)*pi/180),3*sin((\angs[3]+\ang[4]/2)*pi/180),medium,D
 text black,3*cos((\angs[4]+\ang[5]/2)*pi/180),3*sin((\angs[4]+\ang[5]/2)*pi/180),medium,E
 text black,3*cos((\angs[5]+\ang[6]/2)*pi/180),3*sin((\angs[5]+\ang[6]/2)*pi/180),medium,F
}

\text{p=\ang[1]/360,\ang[2]/360,\ang[3]/360,\ang[4]/360,\ang[5]/360,\ang[6]/360}
\statement{<div class="float_right">\draw{200,200}{\dessin}</div>
Une roue de loterie est formée de six secteurs A,B,C,D,E,F associés
 aux mesures d'angles suivantes en degrés :
<table class="wimscenter wimsborder">
<tr><th>Secteur</th><td>A</td><td>B</td><td>C</td><td>D</td><td>E</td><td>F</td></tr>
<tr><th>Angle en degré</th><td>\ang[1]</td><td>\ang[2]</td><td>\ang[3]</td><td>\ang[4]</td><td>\ang[5]</td><td>\ang[6]</td></tr>
</table>
<p>
Lorsque la roue achève sa rotation, un secteur se trouve face
au repère avec une probabilité proportionnelle à l'angle associé.</p>

<div class="wims_question clearall">
  Déterminer la loi de probabilité obtenue.

<table class="wimscenter wimsborder">
<tr><th>Secteur</th><td>A</td><td>B</td><td>C</td><td>D</td><td>E</td><td>F</td><th>Total</th></tr>
<tr><th>Probabilité</th><td>\embed{reply1,3}</td><td>\embed{reply2,3}</td><td>\embed{reply3,3}
</td><td>\embed{reply4,3}</td><td>\embed{reply5,3}</td><td>\embed{reply6,3}</td><th>\embed{reply7,3}</th></tr>
</table></div>
<div class="wims_instruction">\consig</div>
}
\answer{p(A)}{\p[1]}{type=numexp}{option=noreduction}
\answer{p(B)}{\p[2]}{type=numexp}{option=noreduction}
\answer{p(C)}{\p[3]}{type=numexp}{option=noreduction}
\answer{p(D)}{\p[4]}{type=numexp}{option=noreduction}
\answer{p(E)}{\p[5]}{type=numexp}{option=noreduction}
\answer{p(F)}{\p[6]}{type=numexp}{option=noreduction}
\answer{Total}{1}{type=numeric}

#endif
