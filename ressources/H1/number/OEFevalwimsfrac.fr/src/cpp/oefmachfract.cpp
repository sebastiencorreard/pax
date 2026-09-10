target=oefmachfract1 oefmachfract2 oefmachfract3 oefmachfract4 oefmachfract5
#define TITRE Calculatrice et multiplication par une fraction
\langage{fr}
\author{Jean-Luc,Donadoni}
\email{jluc.donadoni@laposte.net}
\format{html}

#if defined TARGET_oefmachfract1
\title{TITRE 1}
\integer{n1=1}
\integer{d1=randint(1..9)*10+randint(1..9)}
\integer{rep=randint(1..9)*1000+randint(0..9)*100+randint(0..9)*10+randint(1..9)}
\integer{nb=\rep*\d1}
\text{nb=slib(numeration/ecriturenombre \nb)}
\text{rep=slib(numeration/ecriturenombre \rep)}
\text{enonc=}
#endif

#if defined TARGET_oefmachfract2
\title{TITRE 2}
\integer{n1=1}
\integer{d1=randint(1..9)*10+randint(1..9)}
\integer{rep=randint(1..9)*1000+randint(0..9)*100+randint(0..9)*10+randint(1..9)}
\real{rep=\rep/10^randint(1..3)}
\real{nb=\rep*\d1}
\text{nb=slib(numeration/ecriturenombre \nb)}
\text{rep=slib(numeration/ecriturenombre \rep)}
\text{nb=wims(translate . to , in \nb)}
\text{rep=wims(translate . to , in \rep)}
\text{enonc=}
#endif

#if defined TARGET_oefmachfract3
\title{TITRE 3}
\integer{n1=randint(2..99)}
\integer{d1=randint(1..9)*10+randint(1..9)}
\integer{rep=\n1*(randint(1..9)*1000+randint(0..9)*100+randint(0..9)*10+randint(1..9))}
\integer{nb=\rep*\d1/\n1}
\text{nb=slib(numeration/ecriturenombre \nb)}
\text{rep=slib(numeration/ecriturenombre \rep)}
\text{enonc=}
#endif

#if defined TARGET_oefmachfract4
\title{TITRE 4}
\integer{n1=randint(2..99)}
\integer{d1=randint(1..9)*10+randint(1..9)}
\integer{rep=\n1*(randint(1..9)*1000+randint(0..9)*100+randint(0..9)*10+randint(1..9))}
\real{rep=\rep/10^randint(1..3)}
\real{nb=\rep*\d1/\n1}
\text{nb=slib(numeration/ecriturenombre \nb)}
\text{rep=slib(numeration/ecriturenombre \rep)}
\text{nb=wims(translate . to , in \nb)}
\text{rep=wims(translate . to , in \rep)}
\text{enonc=}
#endif

#if defined TARGET_oefmachfract5
\title{TITRE 5}
\integer{n1=randint(2..98)}
\integer{d1=randint(1..9)*10+randint(1..9)}
\integer{f=\n1/\d1}
\real{g=\n1/\d1}
\if{\f=\g}{\integer{n1=\n1+1}}
\integer{nb=randint(1..9)*10000+randint(0..9)*1000+randint(0..9)*100+randint(0..9)*10+randint(1..9)}
\integer{rep=\nb*\n1/\d1*10}
\real{rep=\rep/10}
\text{rep2=}
\integer{f=\rep}
\real{g=\rep}
\if{\f=\g}{\text{rep2=,0}}
\text{nb=slib(numeration/ecriturenombre \nb)}
\text{rep=slib(numeration/ecriturenombre \rep)}
\text{nb=wims(translate . to , in \nb)}
\text{rep=wims(translate . to , in \rep)\rep2}
\text{enonc=Vous donnerez un résultat approché au dixième, en précisant le dixième.}
#endif

\statement{
Utiliser la calculatrice pour donner le résultat :
\if{\enonc!=}{<p>\enonc</p>}
<div class="wimscenter">
\nb \(\times \frac{\n1}{\d1} \) =
\embed{r1,10}
</div>
<div class="wims_instruction">Vous utiliserez la virgule comme séparateur décimal,
et vous respecterez l'espace tous les trois chiffres et éviterez les zéros inutiles.</div>
}

\answer{}{\rep}{type=raw}
