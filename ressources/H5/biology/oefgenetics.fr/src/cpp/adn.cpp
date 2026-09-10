target=adnbrin1 adnbrin2 adnbrin3 adnbrin4 adnbrin5

#if defined TARGET_adnbrin1
\title{Transcription 1}
\text{instruction=En s'appuyant sur la séquence du brin ADN transcrit, écrire
  la séquence d'ARN messager après une transcription simple (sans épissage).}
#endif
#if defined TARGET_adnbrin2
\title{Transcription 2}
\text{instruction=En s'appuyant sur la séquence du brin ADN codant, écrire
  la séquence d'ARN messager après une transcription simple (sans épissage).}
#endif
#if defined TARGET_adnbrin3
\title{Traduction 1}
#endif
#if defined TARGET_adnbrin4
\title{Traduction 2 (codon START)}
\text{instruction=Cette séquence correspond au début d'un ARN messager.
  Identifiez le codon d'initiation où débute la traduction.}
\text{instruction2=Donner le début de la séquence protéique traduite.}
#endif
#if defined TARGET_adnbrin5
\title{Traduction 3 (codon STOP)}
\text{instruction=Cette séquence correspond au début d'un ARN messager.
  Identifiez le codon STOP.}
#endif
\text{sequence=wims(makelist A,T,C,G for x=1 to 5)}
\text{sequence=shuffle(\sequence)}
\text{sequence=\sequence[1..15]}
\text{sens=\confparm1=? 1: randitem(\confparm1)}

#if defined TARGET_adnbrin1 || defined TARGET_adnbrin2
# define TYPE 1
#endif
#if defined TARGET_adnbrin3 || defined TARGET_adnbrin4 || defined TARGET_adnbrin5
# define TYPE 2
#endif
#if TYPE==2
\text{N=15}
\integer{N0=3*\N}
\text{n=randitem(1,2,3,4)}  On a besoin par la suite que n<N-5
\integer{nn=randitem(3,3,3,1,2)+3*(\n-1)}
# if defined TARGET_adnbrin3
\text{instruction=En s'appuyant sur la séquence suivante et le code génétique,
  écrire la séquence de la protéine produite à partir du nucléotide \nn.}
# endif

\text{name_tableau=Tableau des codons ARN}
\text{name_help=Si un codon STOP apparait, la traduction s'arrête,
  les codons ne sont plus traduits en acides aminés.}
\text{list=Ala, Arg, Asn, Asp, Cys, Gln, Glu, Gly, His, Ile,
  Leu, Lys, Met, Phe, Pro, Prp, Ser, Thr, Trp, Tyr, Val}
\text{sequence=wims(makelist A,U,G,U for x=1 to \N)}
\text{sequence=shuffle(\sequence)}
\text{sequence=\sequence[1..\N0]}
\text{sequence=wims(nospace wims(items2words \sequence))}
\text{sequence=wims(text expand \sequence using 0111)}
\text{sequence=wims(words2items \sequence)}
\text{sequence=wims(replace internal UGA by AUA in \sequence)}
\text{sequence=wims(replace internal UAA by AGU in \sequence)}
%%% force a avoir des STOP de temps en temps au moins si le nombre de nucleotides est multiple de 3
\text{st=randitem(0,1)}
# if defined TARGET_adnbrin3
\if{\st=1}{
  \text{s=randitem(UAA,UAG,UGA)}
  \integer{ss=randint(\N-4..\N)}
  \text{sequence=wims(replace internal item number \ss by \s in \sequence)}
}
# endif
# if defined TARGET_adnbrin4
%%% force a avoir un START
\integer{ss=randint(2..4)}
\text{sequence=wims(replace internal item number \ss by AUG in \sequence)}
\text{sequence=randitem(A,U,G,T) \sequence}
%%% trouve si il n'y a pas un START avant
\text{sequencemark=wims(words2items wims(text expand wims(items2words \sequence) using 01))}

\text{sequence=wims(nospace wims(items2words \sequence))}
\text{N0=wims(charcnt \sequence)}
\text{j=1}
\text{nn=0}
\while{j <= \ss and \nn=0}{
  \text{start=wims(char 1 to 3 of wims(text compare wims(char \j to -1 of \sequence) and AUG))}
  \text{nn=\start=0? \j}
  \integer{j=\j+1}
}
# endif
# if defined TARGET_adnbrin5
%%% force a avoir un STOP
\integer{ss=randint(\N-4..\N)}
\text{STOP=UAA,UAG,UGA}
\text{stop=randitem(\STOP)}
\text{sequence=\sequence,\stop,randitem(A,U,G)}


\text{sequence=_U,A,A isin _\sequence ?
  wims(replace internal _U,A,A by G,A,G,U,U in _\sequence)}
\text{sequence=_U,A,G isin _\sequence ?
  wims(replace internal _U,A,G by G,A,G,U,U in _\sequence)}
\text{sequence=_U,G,A isin _\sequence ?
  wims(replace internal _U,G,A by G,A,G,U,U in _\sequence)}
\text{sequence=shuffle(A,A,A,G,G,G),U,\sequence}
\text{sequencemark=wims(words2items wims(text expand wims(items2words \sequence) using 01))}
\text{sequence=wims(nospace wims(items2words \sequence))}
\text{N0=wims(charcnt \sequence)}
%%% trouve si il n'y a pas un STOP avant
\integer{J=\N0-2}
\for{t=1 to 3}{
  \integer{nn=0}
  \text{st0=\STOP[\t]}
  \for{k=1 to \J}{
    \if{\nn=0}{
      \text{start=wims(char 1 to 3 of wims(text compare wims(char \k to \J+2 of \sequence) and \st0))}
      \text{nn=\start=0? \k}
    }
  }
  \text{J=\nn<\J and \nn>0? \nn}
}
\integer{nn=\J}

\text{aaa=\sequence}
# endif

#if defined TARGET_adnbrin5
\text{sequencefeed=}
\for{j=1 to \N0}{
  \text{sequencefeed=\j=\nn or \j=\nn+1 or \j=\nn+2 ?
    \sequencefeed <span class="oef_indgood">\sequencemark[\j]</span>:\sequencefeed \sequencemark[\j]}
}

# else
\text{sequence2=wims(words2items wims(text expand wims(items2words \sequence) using 01))}
\text{sequence2=\sequence2[1..\nn]}
\text{sequence2=wims(nospace wims(items2words \sequence2))}
\text{sequence2=wims(text expand \sequence2 using 0111)}
\text{sequence2=wims(words2items \sequence2)}
\integer{cnt=items(\sequence2)}
\text{rep=}
\text{stop=0}
\for{j=1 to \cnt}{
  \if{\stop=0}{
    \text{t1=\sequence2[\j]}
    \if{\j=\cnt}{
      \text{nbchar=wims(charcnt \t1)}
      \text{stop=\nbchar<3? \j}
    }
    \text{t=wims(lookup \t1 in codon2am)}
    \text{stop=\t issametext STOP ? \j}
    \text{rep=\stop=0? wims(append item \t to \rep)}
  }
}
# endif
\text{sequence=wims(items2words \sequence)}

#endif
#if TYPE==1
# if defined TARGET_adnbrin1
 \text{sequence2=wims(translate internal ATCG to UAGC in \sequence)}
# endif
# if defined TARGET_adnbrin2
 \text{sequence2=wims(translate internal ATCG to AUCG in \sequence)}
# endif
\text{sequence=wims(nospace wims(replace internal , by in \sequence))}
\text{sequence2=wims(nospace wims(replace internal , by in \sequence2))}

\text{ext=5,3}
\text{ext=shuffle(\ext)}
# if defined TARGET_adnbrin2
\if{\sens=1}{
  \text{extrep=\ext}
}{
 \text{extrep=\ext[2],\ext[1]}
 \text{sequence2=wims(text reverse \sequence2)}
}
# endif
# if defined TARGET_adnbrin1
\if{\sens=1}{
  \text{extrep=\ext[2],\ext[1]}
}{
 \text{extrep=\ext}
 \text{sequence2=wims(text reverse \sequence2)}
}
# endif
\statement{ \instruction
<div class="wimscenter">\(^{\ext[1]'}\) \sequence \(^{\ext[2]'}\)</div>
<div class="wimscenter">\(^{\extrep[1]'}\) \embed{r1, 20} \(^{\extrep[2]'}\)</div>
}
\answer{}{\sequence2}{type=case}
#endif
#if TYPE==2
\text{ext=5,3}
\text{sequence=wims(nospace \sequence)}
\text{sequencet=wims(char 1 to \nn-1 of \sequence)}
\text{sequence2=wims(char \nn to -1 of \sequence)}
\text{sequence=wims(text expand \sequence2 using 0111)}
#include "tableaucodon.inc"
# if defined TARGET_adnbrin3
\statement{
\instruction
<div class="wimscenter bold">\(^{\ext[1]'}\) \sequencet \sequence \(^{\ext[2]'}\)</div>

<div class="wimscenter">\embed{r1, 40x30x15}</div>
<div class="wims_instruction">\special{help gencode, \name_tableau}</div>
}
\answer{}{\rep;\list}{type=clickfill}
# endif
# if defined TARGET_adnbrin4
\text{rep1=wims(makelist x for x=\nn to \nn+2)}
\steps{r1
r2}
\statement{
  \if{\step=1}{
  \instruction
    <div class="wimscenter">\(^{\ext[1]'}\)
    \for{h=1 to \N0}{\embed{r1,\h}}\(^{\ext[2]'}\)
    </div>
  }
  \if{\step>=2}{
  \instruction2
    <div class="wimscenter">\(^{\ext[1]'}\) \sequencet <span class="bold">\sequence</span> \(^{\ext[2]'}\)</div>
    <div class="wimscenter">\embed{r2, 40x30x15}</div>
    <div class="wims_instruction">\special{help gencode, \name_tableau}</div>
  }
}
\answer{}{\rep1;\sequencemark}{type=mark}{option=noanalyzeprint}
\answer{}{\rep;\list}{type=clickfill}
\feedback{\sc_reply1=0}{
  <div class="wimscenter">\(^{\ext[1]'}\) \sequencet <span class="bold">\sequence</span> \(^{\ext[2]'}\)</div>
}
# endif
# if defined TARGET_adnbrin5
\text{rep1=wims(makelist x for x=\nn to \nn+2)}
\statement{
  \instruction
  <div class="wimscenter">\(^{\ext[1]'}\)
    \for{h=1 to \N0}{\embed{r1,\h}}\(^{\ext[2]'}\)
  </div>
}
\answer{}{\rep1;\sequencemark}{type=mark}{option=noanalyzeprint}
\feedback{\sc_reply1=0}{
<div class="wimscenter">\(^{\ext[1]'}\) \sequencefeed \(^{\ext[2]'}\)</div>
}
# endif
\help{
#include "gencode.inc"
}
#endif
