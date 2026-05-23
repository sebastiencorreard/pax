\text{champ=wims(record \confparm1 of src/generateur)}
\text{A=row(2,\champ)}
\text{B=row(3,\champ)}
\text{c=item(3,\A)}
\if{\B=}{
\text{a=item(1,\A)}
\text{b=item(2,\A)}
\if{\c<0}{
  \text{valeurs=wims(values \c*v,-(\c)*v for v=\a to \b)}
}{
  \text{valeurs=wims(values \c*v for v=\a to \b)}
}
}{
  \text{valeurs=\B}
  \if{\c<0}{
    \text{tmp=wims(replace internal , by ,- in \valeurs)}
    \text{valeurs=wims(listunion \valeurs and \tmp)}
  }
}
\text{valeurs=wims(listuniq \valeurs)}
\text{valeurs=shuffle(\valeurs)}
