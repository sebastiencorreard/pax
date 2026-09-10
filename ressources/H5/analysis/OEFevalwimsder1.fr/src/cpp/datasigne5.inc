\integer{choix=2}
\if{\choix=1}
 {
\integer{a=randint(-2..2)}
\function{fd=(6*(x+\a)+3)/((x+\a)^2+x+\a+2.5)}
\text{dessin=
 xrange -6,6
 yrange -3,3
 parallel -6,-3,6,-3,0,1,7,gray
 parallel -6,-3,-6,3,1,0,13,gray
 arrow -6,0,6,0,10,black
 arrow 0,-3,0,3,10,black
 text black,-0.5,1,medium,1
 text black,1,-0.2,medium,1
 plot blue,\fd
}
\text{intro=Soit \(f) une fonction définie et dérivable sur \(\RR), la courbe ci-contre représente la fonction \(f'), dérivée de \(f).}
\integer{c=1-\a}
\integer{d=-2-\a}
\integer{e=randint(\c,\d)}
\rational{xext=-0.5-\a}
\text{qA=\(f'(\e)=0),2,
\(f'(\xext)=0),1}
\text{qB=\(f) admet un extremum en \xext,1,
\(f) admet un extremum en \e,2}
\text{qC=\(f) est décroissante sur [\c ;6],2,
\(f) est croissante sur [\d ;\c],2,
\(f) est croissante sur [\xext ;6],1}
\text{qD=La tangente à la courbe de \(f) au point d'abscisse \c a pour coefficient directeur 2,1,
   La tangente à la courbe de \(f) au point d'abscisse \d a pour coefficient directeur -2,1,
   La tangente à la courbe de \(f) au point d'abscisse \e a pour coefficient directeur 0,2}
\text{qE=Sur [-6;6] la courbe de \(f) admet deux tangentes horizontales,1,
   Sur [-6;6] la courbe de \(f) admet une seule tangente horizontale,2}

 }
 {
\integer{a=randint(-2..2)}
\function{f=-0.17*(x+\a)^3+0.5*(x+\a)^2+x+\a}
\text{dessin=
 xrange -6,6
 yrange -4,4
 parallel -6,-4,6,-4,0,1,9,gray
 parallel -6,-4,-6,4,1,0,13,gray
 arrow -6,0,6,0,10,black
 arrow 0,-4,0,4,10,black
 text black,-0.5,1,medium,1
 text black,1,-0.2,medium,1
 plot red,\f
}
\text{intro=La courbe ci-contre représente une fonction \(f) définie et dérivable sur \(\RR). On appelle \(f') la fonction dérivée de \(f).}
\integer{b=-\a}
\integer{c=2-\a}
\integer{d=4-\a}
\text{qA=\(f') est positive sur [\b;\c],1,
\(f') est positive sur [\c;\d],2}
\text{qB=Sur [-6;6] \(f') s'annule 3 fois,2,
   Sur [-6;6] \(f') s'annule 2 fois,1}
\text{qC=Sur [-6;6] l'équation \(f'(x)=1) a 3 solutions,2,
   Sur [-6;6] l'équation \(f'(x)=1) a 2 solutions,2,
   Sur [-6;6] l'équation \(f'(x)=1) a 1 seule solution,1}
\text{qD=Le coefficient directeur de la tangente à la courbe de \(f) au point d'abscisse \d est positif,2,
   Le coefficient directeur de la tangente à la courbe de \(f) au point d'abscisse \d est négatif,1}
\text{qE=Le coefficient directeur de la tangente à la courbe de \(f) au point d'abscisse \b est positif,1,
   Le coefficient directeur de la tangente à la courbe de \(f) au point d'abscisse \b est négatif,2}
\text{qF=Sur [\c;\d] \(f') change de sens de variation,2,
   Sur [\c;\d] \(f') ne change pas de sens de variation,1}
 }

\text{grep=}

\text{cedata=randomrow(\qA)}
\text{qAf=\cedata[1]}
\if{\cedata[2]=1}
 {
 \text{grep=wims(append item 1 to \grep)}
 }
\text{cedata=randomrow(\qB)}
\text{qBf=\cedata[1]}
\if{\cedata[2]=1}
 {
 \text{grep=wims(append item 2 to \grep)}
 }
\text{cedata=randomrow(\qC)}
\text{qCf=\cedata[1]}
\if{\cedata[2]=1}
 {
 \text{grep=wims(append item 3 to \grep)}
 }
\text{cedata=randomrow(\qD)}
\text{qDf=\cedata[1]}
\if{\cedata[2]=1}
 {
 \text{grep=wims(append item 4 to \grep)}
 }
\text{cedata=randomrow(\qE)}
\text{qEf=\cedata[1]}
\if{\cedata[2]=1}
 {
 \text{grep=wims(append item 5 to \grep)}
 }
\text{lstrep=\qAf,\qBf,\qCf,\qDf,\qEf}
\if{\choix=2}
 {
\text{cedata=randomrow(\qF)}
\text{qFf=\cedata[1]}
\if{\cedata[2]=1}
 {
 \text{grep=wims(append item 6 to \grep)}
 }
\text{lstrep=\lstrep,\qFf}
}
