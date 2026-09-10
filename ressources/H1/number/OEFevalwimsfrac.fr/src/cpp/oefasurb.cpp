target=oefasurb1 oefasurb2 oefasurb3 oefasurb4 oefasurb5
#define TITRE Fraction et valeur décimale
\langage{fr}
\author{Jean-Luc,Donadoni}
\email{jluc.donadoni@laposte.net}
\format{html}

#if defined TARGET_oefasurb1
\title{TITRE 1}

\text{ty=clickfill}
\text{size=60x40}
\integer{b=randint(2..12)}
\integer{a=randint(1..\b-1)}
\rational{z=simplify(\a/\b)}
\integer{t=0}
\integer{d=0}
\while{\t<1}{\integer{d=\d+1}
             \real{t1=\d*\z}
             \integer{t2=\d*\z}
             \if{\t1=\t2}{\integer{t=1}}}
\integer{n=\z*\d}

\text{enonc=Nous avons la fraction \(\frac{\n}{\d}).
<p>Compléter l'égalité :</p> <div class="wimscenter">\(\frac{\n}{\d}) = }
\text{rep1=\(\n \div \d)}
\text{rep2=\(\d \div \n),
\(\n \times \d),
\(\n + \d),
\(\n - \d),
\n\(,)\d
}
#endif

#if defined TARGET_oefasurb2
\title{TITRE 2}
\text{ty=clickfill}
\text{size=60x50}
\text{d=shuffle(3,4,5,6,7,8,9,10,11,12)}
\matrix{ln=wims(record 1 of src/fractions)}
\text{a=row(\d[1]-1,\ln)}
\text{a=item(2..items(\a),\a)}
\integer{n=randomitem(\a)}
\integer{d=\d[1]}

\text{enonc=Nous avons la fraction \(\frac{\n}{\d}).
<p>Compléter l'égalité : </p> <div class="wimscenter">\(\frac{\n}{\d}) = }
\text{rep1=\(\frac{1}{\d} \times \n) }
\text{rep2=\(\frac{1}{\n} \times \d),
\(\n \times \d),
\(\frac{\n}{10} \times \d),
\(\frac{1}{\d} \div \n),
\(\frac{\d}{10} \times \n)
}
#endif

#if defined TARGET_oefasurb3
\title{TITRE 3}
\text{ty=clickfill}
\text{size=120x50}
\text{f=1,2;1,4;2,4;3,4;1,5;2,5;3,5;4,5;3,6;1,8;2,8;3,8;4,8;5,8;6,8;7,8;1,10;2,10;3,10;4,10;5,10;6,10;7,10;8,10;9,10}
\integer{ch=randint(1..25)}
\text{f=row(\ch,\f)}
\real{v=\f[1]/\f[2]}
\text{enonc=Nous avons l'égalité suivante : \v \(\times) \f[2] = \f[1]
  donc <i>(Choisir la bonne égalité)</i> : <div class="wimscenter">}
\text{rep1=\(\frac{\f[1]}{\f[2]}) = \v }
\text{rep2=\(\frac{\f[2]}{\f[1]}) = \v ,
\(\frac{\v}{\f[2]}) = \f[1],
\(\frac{\v}{\f[1]}) = \f[2]
}
#endif

#if defined TARGET_oefasurb4
\title{TITRE 4}
\text{ty=correspond}
\text{size=60x60}
\text{f=1,2;1,4;2,4;3,4;1,5;2,5;3,5;4,5;3,6;1,8;2,8;3,8;4,8;5,8;6,8;7,8;1,10;2,10;3,10;4,10;5,10;6,10;7,10;8,10;9,10}
\text{ch=shuffle(25)}
\text{n=}
\text{d=}
\text{vr=}
\text{fr=}
\for{i=1 to 4}{
    \text{fa=row(\ch[\i],\f)}
    \real{v=\fa[1]/\fa[2]}
    \text{n=wims(append item \fa[1] to \n)}
    \text{d=wims(append item \fa[2] to \d)}
    \text{vr=wims(append item \v to \vr)}}

\text{enonc= Mettre en relation la fraction avec sa valeur décimale :
<div class="wimscenter">}
\text{rep1=\(\frac{\n[1]}{\d[1]}),\(\frac{\n[2]}{\d[2]}),\(\frac{\n[3]}{\d[3]}),\(\frac{\n[4]}{\d[4]})}
\text{rep2=\vr[1],\vr[2],\vr[3],\vr[4]}
#endif

#if defined TARGET_oefasurb5
\title{TITRE 5}
\text{ty=correspond}
\text{size=60x60}
\text{f=1,3;2,3;1,6;2,6;4,6;5,6;1,7;2,7;3,7;4,7;5,7;6,7;1,9;2,9;3,9;4,9;5,9;6,9;7,9;8,9}
\text{ch=shuffle(20)}
\text{n=}
\text{d=}
\text{vr=}
\text{fr=}
\for{i=1 to 4}{
    \text{fa=row(\ch[\i],\f)}
    \real{v=rint((\fa[1]/\fa[2])*100)/100}
    \text{n=wims(append item \fa[1] to \n)}
    \text{d=wims(append item \fa[2] to \d)}
    \text{vr=wims(append item \v to \vr)}}

\text{enonc= Mettre en relation la fraction avec sa valeur décimale approchée :
<div class="wimscenter">}
\text{rep1=\(\frac{\n[1]}{\d[1]}),\(\frac{\n[2]}{\d[2]}),\(\frac{\n[3]}{\d[3]}),\(\frac{\n[4]}{\d[4]})}
\text{rep2=\vr[1],\vr[2],\vr[3],\vr[4]}
#endif

\statement{
\enonc
\embed{r1,\size}
</div>}

\answer{}{\rep1;\rep2}{type=\ty}{option=shuffle}
