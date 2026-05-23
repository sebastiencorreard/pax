target=priorite1 priorite2 priorite3 priorite4
#define TITRE Priorités opératoires
\author{Fabrice,Guerimand}
\email{fwguerima@free.fr}

\text{v=wims(values v for v=2 to 12)}
\text{v=shuffle(\v)}


#if defined TARGET_priorite1
 \title{TITRE 1}
 \integer{ch1=randint(1..2)}
 \if{\ch1=1}{
  \text{sg1=\times}
  \text{texte1=La multiplication}
}{
  \text{sg1=\div}
  \text{texte1=La division}
}
 \integer{ch2=randint(1..2)}
 \if{\ch2=1}{
  \text{sg2=+}
  \text{texte2=L'addition}
}{
  \text{sg2=-}
  \text{texte2=La soustraction}
}
 \integer{ch=randint(1..3)}
 \text{ltcalcul=\v[1] \sg1 (\v[2] \sg2 \v[3])
(\v[2] \sg2 \v[3]) \sg1 \v[1]
\v[1] \sg1 \v[2] \sg2 \v[3]}
 \text{calcul=row(\ch,\ltcalcul)}
 \text{bad=\texte2,\texte2,\texte1,Peu importe}
 \text{good=item(\ch,\bad)}
#endif

#if defined TARGET_priorite2
 \title{TITRE 2}
 \integer{ch2=randint(1..2)}
 \if{\ch2=1}{
  \text{sg2=+}
  \text{texte2=L'addition}
}{
  \text{sg2=-}
  \text{texte2=La soustraction}
}
 \integer{ch=randint(1..4)}
 \text{ltcalcul=\frac{\v[1]}{\v[2]\sg2\v[3]}
\v[1] \div(\v[2] \sg2 \v[3])
\v[1] \div \v[2] \sg2 \v[3]
\frac{\v[1]}{\v[2]} \sg2 \v[3]}
 \text{calcul=row(\ch,\ltcalcul)}
 \text{bad=\texte2,\texte2,La division,La division,Peu importe}
 \text{good=item(\ch,\bad)}
#endif

#if defined TARGET_priorite3
 \title{TITRE 3}
 \integer{ch1=randint(1..2)}
 \if{\ch1=1}{
  \text{sg1=+}
  \text{texte1=L'addition de \v[1] et \v[2]}
}{
  \text{sg1=-}
  \text{texte1=La soustraction de \v[2] à \v[1]}
}
 \integer{ch2=randint(1..2)}
 \if{\ch2=1}{
  \text{sg2=+}
  \text{texte2=L'addition de \v[2] et \v[3]}
}{
  \text{sg2=-}
  \text{texte2=La soustraction de \v[3] à \v[2]}
}
 \text{calcul=\v[1] \sg1 \v[2] \sg2 \v[3]}
 \text{bad=Peu importe,\texte1,\texte2}
 \text{good=item(\ch1,\bad)}
#endif

#if defined TARGET_priorite4
 \title{TITRE 4}
 \integer{ch1=randint(1..2)}
 \if{\ch1=1}{
  \text{sg1=\times}
  \text{texte1=La multiplication de \v[1] par \v[2]}
}{
  \text{sg1=\div}
  \text{texte1=La division de \v[1] par \v[2]}
}
 \integer{ch2=randint(1..2)}
 \if{\ch2=1}{
  \text{sg2=\times}
  \text{texte2=La multiplication de \v[2] par \v[3]}
}{
  \text{sg2=\div}
  \text{texte2=La division de \v[2] par \v[3]}
}
 \text{calcul=\v[1] \sg1 \v[2] \sg2 \v[3]}
 \text{bad=Peu importe,\texte1,\texte2}
 \text{good=item(\ch1,\bad)}
#endif


\statement{
Voici un calcul :
<div class="wimscenter">\(\calcul)</div>
Quelle opération devez-vous obligatoirement effectuer en premier ?}

\choice{}{\good}{\bad}
