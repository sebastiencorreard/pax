target=convertirp

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}


\text{size=20x25x}
\integer{basep=row(1,\confparm4)}
\text{S=row(3,\confparm4)}
\text{S=item(1 to \basep,\S)}

\text{p=shuffle(2,3,4,5)}
\text{nombre=}
\text{srep=}
\text{lsize=}
\for{r=1 to \confparm3}{
 \integer{n=randint(1..\basep-1)}
 \integer{N=randint(\basep^\p[\r]..\basep^(\p[\r]+1))}
 \text{n=slib(basep \N,\S)}
 \text{nombre=wims(append item \N to \nombre)}
 \text{rep=slib(char2item \n)}
 \integer{tmp=items(\rep)}
 \text{lsize=wims(append item \size\tmp to \lsize)} 
 \text{srep=wims(append line \rep to \srep)}
}

\text{ltrep=item(1 to \confparm3,r1,r2,r3,r4,r5)}
\steps{\ltrep}


#include "lang.inc"

\statement{
\txtstatement1<p>
\if{\confparm3=1}{
 \txtstatement2
}{
 \txtstatement3
}
</p>
<table class="wimscenter wimsborder">
 <tr><th>\txtbaseten</th><th>\txtbase \basep</th></tr>
 \for{k=1 to \confparm3}{<tr><td>\nombre[\k] </td><td> \embed{r\k,\lsize[\k]}</td></tr>}
</table>
}

\answer{\nombre 1 }{\srep[1;];\S}{type=clickfill}
\answer{\nombre 2 }{\srep[2;];\S}{type=clickfill}
\answer{\nombre 3 }{\srep[3;];\S}{type=clickfill}
\answer{\nombre 4 }{\srep[4;];\S}{type=clickfill}
\answer{\nombre 5}{\srep[5;];\S}{type=clickfill}
