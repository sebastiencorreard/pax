target=prime1 prime2 prime3 divpremier1 divpremier2

\text{confparm1= items(\confparm1)=0 ? random(1,2):\confparm1}
\text{confparm2= items(\confparm2)=0 ? random(8..20):\confparm2}

\author{Bruno, Mifsud}
\email{bruno.mifsud@laposte.net}

\integer{pas=\confparm2}
\integer{bsup=\confparm1=1 ? 30-\pas :100-\pas}

#if defined TARGET_prime1
\title{Reconnaitre les nombres premiers (liste ordonnée)}
#endif
#if defined TARGET_prime2
\title{Reconnaitre les nombres premiers (liste non ordonnée)}
#endif
#if defined TARGET_prime3
\title{Reconnaitre le premier nombre premier plus grand que}
#endif
#if defined TARGET_divpremier1
\title{Diviseur premier d'un entier}
#endif
#if defined TARGET_divpremier2
\title{Diviseur premier de deux entiers}
#endif
\text{defprime=<b>Définition :</b> On appelle nombre premier tout entier positif qui admet exactement deux diviseurs positifs : 1 et lui-même.
<br/>Exemple : 5 est un nombre premier
<br/>Contre exemple : 6 n'est pas un nombre premier.
Il est divisible à la fois par 1, 2, 3 et 6.
}
\help{\defprime}
#if defined TARGET_divpremier1 || defined TARGET_divpremier2

\text{name_critere=Pensez aux critères de divisibilité par 2, 3 et 5 et essayez
  de diviser XXXX par un de ces nombres premiers.}
#endif

\text{N1=randint(1..\bsup)}
#if defined TARGET_divpremier1
\text{N1=randint(6..\bsup)}
#endif
#if defined TARGET_divpremier2
\text{N1=randint(6..\bsup)}
#endif
\integer{N2=\N1+\pas-1}
\text{list=wims(makelist x for x=\N1 to \N2)}
#if defined TARGET_prime2
\text{list=shuffle(\list)}
#endif

\integer{listcnt=items(\list)}
\text{listpos=}
\for{j=1 to \listcnt}{
  \text{listpos=pari(t=\list[\j]; isprime(t))=1 ? wims(append item \j to \listpos)}
}
#if defined TARGET_divpremier1

%%%%%%%%    On en prend un au hasard qu'on multiplie par 2 ou 3 ou 5
\integer{efflistpos=items(\listpos)}
\integer{r0=random(1..\efflistpos)}
\integer{r=\listpos[\r0]}
\integer{co1=random(2,3,5)}
\integer{n1=\list[\r]*\co1}

%%%%%%%%%on reinitialise la liste des bonnes réponses
\text{listpos=\r}
#endif


#if defined TARGET_divpremier2
%%%%%%%%    On en prend un au hasard qu'on multiplie par 2 ou 3 ou 5
\integer{efflistpos=items(\listpos)}
\integer{r0=random(1..\efflistpos)}
\integer{r=\listpos[\r0]}
\integer{co1=random(2,3,5)}
\integer{n1=\list[\r]*\co1}
\integer{co2=random(2,3,5)}
\if{\co1=\co2}{
\integer{co1=2}
\integer{co2=random(3,5)}}
\integer{n1=\list[\r]*\co1}
\integer{n2=\list[\r]*\co2}

%%on reinitialise la liste des bonnes réponses
\text{listpos=\r}
#endif
#if defined TARGET_prime3
\integer{n3=random(\N1..\N2-8)}
\integer{n3p= pari(isprime(\n3))=1 ? pari(nextprime(\n3+1)): pari(nextprime(\n3))}
\text{listpos=}
\for{j=1 to \listcnt}{
  \text{listpos= \list[\j]=\n3p ? wims(append item \j to \listpos)}
}
#endif

#if defined TARGET_prime1
\text{name_instruction=Cliquez sur les nombres premiers de la liste suivante.}
#endif
#if defined TARGET_prime2
\text{name_instruction=Cliquez sur les nombres premiers de la liste suivante.}
#endif
#if defined TARGET_prime3
\text{name_instruction=Cliquer sur le premier nombre premier
  qui est strictement plus grand que \n3.}
#endif
#if defined TARGET_divpremier1
\text{name_instruction=Cliquez sur le nombre premier de la liste suivante qui divise
  le nombre \n1.}
#endif
#if defined TARGET_divpremier2
\text{name_instruction=Cliquez sur le nombre premier de la liste suivante qui divise
  le nombre \n1 et le nombre \n2.}
#endif

\statement{\name_instruction
<div class="wimscenter">
\for{k=1 to \listcnt}{\embed{r1,\k} ; }</div>
}

\answer{}{\listpos;\list}{type=mark}
\text{rep=\reply1}


#if defined TARGET_prime1 || defined TARGET_prime2 || TARGET_prime3
\if{\sc_reply1<1}{
  \text{noprime=}
  \for{j in \rep}{\text{noprime=pari(isprime(\j))=0? wims(append item \j to \noprime)}}
  \integer{noprimecnt=items(\noprime)}
}
\if{\sc_reply1<1}{
  \text{prime=}
  \for{j in \rep}{\text{prime=pari(isprime(\j))=1? wims(append item \j to \prime)}}
  \integer{primecnt=items(\prime)}
}
\feedback{1=1}{
  \if{\sc_reply1<1 and \noprimecnt>0}{<div class="feedback">
    \if{\noprimecnt>1}{Les nombres \noprime ne sont pas premiers}
      {Le nombre \noprime n'est pas premier.}</div>}
 #if defined TARGET_prime3
    \if{\sc_reply1<1 and \primecnt>0}{
    <div class="feedback">\if{\primecnt>1}{Les nombres \prime sont premiers}
      {Le nombre \prime est premier.}
      <br /> Mais seul le <b>premier</b> nombre premier était demandé.
  </div>}
#endif

}
#endif

#if defined TARGET_divpremier1 || defined TARGET_divpremier2
\text{testp=pari(isprime(\rep))}
\text{testd=\n1%\rep=0? 1:0}
# if defined TARGET_divpremier1
\text{name_critere=wims(replace internal XXXX by \n1 in \name_critere)}

\feedback{1=1}{

\if{\sc_reply1<1}{
  \if{\testp==0}{
    L'entier \rep n'est pas un nombre premier.
  }
  \if{\testd==0}{
    Le nombre entier \n1 n'est pas divisible par \rep.
  }
  Par contre,}
  {En effet}
  <div class="wimscenter"> \(\n1={\special{color=red}{\list[\r]}} \times \co1\)</div>
  et \list[\r] est premier et divise \n1.
}
# endif
# if defined TARGET_divpremier2
\text{testd2=\n2%\rep=0? 1:0}
\text{name_critere=wims(replace internal XXXX by \n1 et \n2 in \name_critere)}
\feedback{1=1}{

\if{\sc_reply1<1}{
  \if{\testp==0}{
    L'entier \rep n'est pas un nombre premier.
  }
  \if{\testd==0}{
    Le nombre entier \n1 n'est pas divisible par \rep.
  }
  \if{\testd2==0}{
    Le nombre entier \n2 n'est pas divisible par \rep.
  }
  Par contre,}
  {En effet}
  <div class="wimscenter"> \(\n1={\special{color=red}{\list[\r]}} \times \co1\)</div>
  <div class="wimscenter"> \(\n2={\special{color=red}{\list[\r]}} \times \co2\)</div>
  et \list[\r] est premier et divise à la fois \n1 et \n2.
}
# endif
\feedback{1=1}{

<p>\name_critere</p>
<div class="wims_msg info">
\if{\confparm1=1}
{Pour rappel, voici la liste des nombres premiers plus petits que 30 :
<br />2 ;  3  ; 5  ; 7  ; 11 ; 13 ; 17 ; 19 ; 23 ; 29  }
{Pour rappel, voici la liste des nombres premiers plus petits que 100 :
<br />2  ; 3  ; 5  ; 7  ; 11 ; 13 ; 17 ; 19 ; 23 ; 29
<br />31 ; 37 ; 41 ; 43 ; 47 ; 53 ; 59
<br /> 61 ; 67 ; 71  ; 73 ; 79 ; 83 ; 89 ; 97
}
}
#endif
\feedback{1=1}{
<div class="wims_msg info">
\defprime
</div>}
