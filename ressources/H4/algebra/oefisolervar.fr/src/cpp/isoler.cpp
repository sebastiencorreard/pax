target=isolerbts1 isolerbts2 isolerdroite isolervitesse isolerinit1 isolerinit2


\language{fr}
\format{html}

\text{instr=X}

#if defined TARGET_isolerbts1
  \title{Isoler 5}
  !!I/V &#61; (bh²)/6
  \author{Paul,Byache}
  \email{paul@byache.fr}
  \text{alphabet=shuffle(I,J,U,V,b,c,h)}
  \text{I=\alphabet[1]}
  \text{V=\alphabet[2]}
  \text{b=\alphabet[3]}
  \text{h=\alphabet[4]}
  \integer{n=random(2,3,4,5,6)}
    
  !!on aura une equation du type : I/V=(bh²)/6
  \text{enonce = \frac{\I}{\V} = \frac{\b \h^2}{\n}}
  \text{instr=Pour saisir "\(\sqrt{ab}\)", taper "sqrt(ab)".<br>Pour être sûr que votre réponse soit bien interprétée par le logiciel, indiquez les signes de multiplication par le caractère " * ".}
  \text{QR=randomrow(\I,(\b*\h^2*\V)/\n
  \V,(\n*\I)/(\b*\h^2)
  \b,(\n*\I)/(\V*\h^2)
  \h,sqrt((\n*\I)/(\V*\b)))}

  \text{quest=\QR[1]}
  \text{rep=\QR[2]}
#endif


#if defined TARGET_isolerbts2
  \title{Isoler 6}
  !!E deltaI / I &#61; N / S
  
  \author{Paul,Byache}
  \email{paul@byache.fr}
  \text{alphabet=shuffle(E,F,t,u,N,M,S,T)}
  \text{E=\alphabet[1]}
  \text{I=\alphabet[2]}
  \text{N=\alphabet[3]}
  \text{S=\alphabet[4]}

  !!on aura une equation du type : E delta I / I = N / S
  \text{enonce = \E \frac{\Delta \I}{\I} = \frac{\N}{\S}}

  \text{QR=randomrow(\E,(\N*\I)/(\S*delta\I) | (\N*\I)/(\S*delta \I)
  \Delta \I,(\N*\I)/(\S*\E)
  \I,(\E*delta\I*\S)/(\N) | (\E*delta \I*\S)/(\N)
  \N,(\E*delta\I*\S)/(\I) | (\E*delta \I*\S)/(\I)
  \S,(\N*\I)/(\E*delta\I) | (\N*\I)/(\E*delta \I))}
  
  \text{instr=Pour saisir "\(\Delta \I\)", taper "delta\I" <br>Pour être sûr que votre réponse soit bien interprétée par le logiciel, indiquez les signes de multiplication par le caractère " * ".}

  \text{quest=\QR[1]}
  \text{rep=\QR[2]}
#endif


#if defined TARGET_isolerdroite
  \title{Isoler 3}
  !!4x+6y-5 &#61; 0
  
  \author{Paul,Byache}
  \email{paul@byache.fr}
  \text{alphabet=x,y,a,b,u,v}
  \integer{choix=random(0,1,2)}
  \text{x=\alphabet[2*\choix+1]}
  \text{y=\alphabet[2*\choix+2]}
  \integer{a=random(1,-1)*random(1,2,3,4,5,6)}
  \integer{b=random(1,-1)*random(1,2,3,4,5,6)}
  \integer{c=random(1,-1)*random(1,2,3,4,5,6)}
    
  !!on aura une equation du type : ax+by+c=0
  \text{enonce = texmath(\a*\x+\b*\y+\c=0)}

  \text{QR=randomrow(\x,(-(\c)-(\b)*\y)/(\a)
  \y,(-(\c)-(\a)*\x)/(\b))}
  
  \text{quest=\QR[1]}
  \text{rep=\QR[2]}
#endif


#if defined TARGET_isolervitesse
  \title{Isoler 4}
  !!d &#61; vt+6
  
  \author{Paul,Byache}
  \email{paul@byache.fr}
  \text{alphabet=d,v,t,a,b,c,x,y,z}
  \integer{choix=random(0,1,2)}
  \text{d=\alphabet[3*\choix+1]}
  \text{v=\alphabet[3*\choix+2]}
  \text{t=\alphabet[3*\choix+3]}
  \integer{a=random(1,-1)*random(1,2,3,4,5,6)}
    
  !!on aura une equation du type : d=vt+a
  \text{enonce = texmath(\d=\v*\t+\a)}

  \text{QR=randomrow(\v,(\d-(\a))/\t
  \t,(\d-(\a))/\v)}
  
  \text{quest=\QR[1]}
  \text{rep=\QR[2]}
#endif

#if defined TARGET_isolerinit1
  \title{Isoler 1}
  !!formules faciles connues : U/R=I, L=2piR, E=Pt, v=d/t, F=ma
  
  \author{Groupe, MutuWIMS}
  \email{communaute.mutuwims@laposte.net}
  !! termes groupés par 2, correspondant au 1er et 2nd membre de l'égalité.
  !! les 2 premiers sont l'égalité à présenter
  !! les autres sont des couples d'égalités à obtenir
  \matrix{formules =
     U/R, I, U, R*I,  R, U/I
     L, 2*pi*R, R,L/(2*pi), R, L/(2*pi)
     E,P*t,P,E/t,t,E/P
     v,d/t,d,v*t,t,d/v
     F,m*a,m,F/a,a,F/m
  }

  \text{formule = randomrow(\formules)}
  \integer{k = items(\formule)/2-1}
  \text{enonce = texmath(\formule[1] = \formule[2])}
  \text{n = randint(1..\k)}
  \text{quest = \formule[2*\n+1]}
  \text{rep = \formule[2*\n+2]}
  \text{instr=Pour être sûr que votre réponse soit bien interprétée par le logiciel, indiquez les signes de multiplication 
  par le caractère " * ".}
  \if{pi isin \rep}{
    \text{instr=\instr <br>Tapez <b>pi</b> pour \( \pi \).}
  }

#endif

#if defined TARGET_isolerinit2
  \title{Isoler 2}
  !!formules un peu moins faciles connues : h=1/2 gt², PV=nRT, E=1/2 mv², A=(B+b)*h/2
  
  \author{Groupe, MutuWIMS}
  \email{communaute.mutuwims@laposte.net}
  !!termes groupés par 2, correspondant au 1er et 2nd membre de l'égalité.
  !!les 2 premiers sont l'égalité à présenter
  !!les autres sont des couples d'égalités à obtenir
  \matrix{formules =
   h, 1/2*g*t^2, t, sqrt(2*h/g)
   P*V,n*R*T, P, n*R*T/V, V, n*R*T/P, R,P*V/(n*T) , T,P*V/(n*R)
   E, 1/2*m*v^2, m,2*E/v^2, v,sqrt(2*E/m)
   A, (B+b)*h/2, h,2*A/(B+b), B,2*A/h-b, b, 2*A/h-B
  }

  \text{formule = randomrow(\formules)}
  \integer{k = items(\formule)/2-1}
  \text{enonce = texmath(\formule[1] = \formule[2])}
  \text{n = randint(1..\k)}
  \text{quest = \formule[2*\n+1]}
  \text{rep = \formule[2*\n+2]}
  \text{instr=Pour être sûr que votre réponse soit bien interprétée par le logiciel, indiquez les signes de multiplication par le caractère " * ".}

  \if{sqrt isin \rep}{
    \text{instr=\instr <br>Tapez <b>sqrt(a)</b> pour \( \sqrt{a} \).}
  }
#endif

\text{rep=wims(replace internal | by , in \rep)}
\text{phrase=randitem(Isoler la variable \(\quest\) dans l'équation suivante,Ecrire la variable \(\quest\) en fonction des autres variables de l'équation suivante)}
\text{ans=Réponse}
\text{solu=\quest=texmath(\rep)}

\statement{\phrase :
<div class="wimscenter">
\(\enonce\)
</div>
<div class="wims_question">
\ans : <label for="reply1">\(\quest=\)</label>\embed{r1}
</div>

\if{\instr notsametext X}{<div class=wims_instruction>\instr</div>}
}

\answer{\(\quest=\)}{\rep}{type=formal}
\solution{ \( \solu \) }
\latex{
\begin{statement}
  \phrase : \(\enonce\)
  \newline
  \ans : ................
\end{statement}
\begin{solution}
  \(\solu\)
\end{solution}}
