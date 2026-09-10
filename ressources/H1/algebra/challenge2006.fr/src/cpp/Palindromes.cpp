target=Palindromes32,Palindromes43,Palindromes5,Palindromes6
#define TITRE Palindromes

\author{Fabrice,Guerimand;Joseph,Cesaro}
\email{fwguerima@free.fr}
\format{html}
\language{fr}
\observation{Il y a 4 exercices Palindromes de difficulté différente (1 le plus difficile à 4 le plus facile).}

#if defined TARGET_Palindromes32
  \title{TITRE 1}
  \integer{b=randint(1..9)}
  \integer{d=randint(1..9)}
  \integer{e=randint(1..3)}
  \integer{c=randint(\e+1..6)}
  \integer{a=\c+3}
  \integer{N2=\a\b\c}
  \integer{N1=\c\d\e}
  \integer{rep=10*(-\c+\a)+\b-\d}
#endif
#if defined TARGET_Palindromes43
  \title{TITRE 2}
  \integer{b=randint(1..9)}
  \integer{d=randint(1..9)}
  \integer{e=randint(1..3)}
  \integer{c=randint(\e+1..7)}
  \integer{a=\c+2}
  \integer{N1=\c\d\e}
  \integer{N2=\a\b\c}
  \integer{rep=10*(\a-\c)-\d+\b}
#endif
#if defined TARGET_Palindromes5
  \title{TITRE 3}
  \integer{x=randint(3..4)}
  \integer{b=randint(1..9)}
  \integer{c=randint(1..9-\x-3)}
  \integer{a=randint(\c+1..9-\x)}
  \integer{N1=\a\b\c}
  \integer{N2=\N1+\x*100}
  \integer{rep=10*\x}
#endif
#if defined TARGET_Palindromes6
  \title{TITRE 4}
  \integer{x=randint(1..2)}
  \integer{b=randint(1..9)}
  \integer{c=randint(1..9-\x-3)}
  \integer{a=randint(\c+1..9-\x)}
  \integer{N1=\a\b\c}
  \integer{N2=\N1+\x*100}
  \integer{rep=10*\x}
#endif

\integer{x1=randint(1..9)}
\integer{x2=randint(1..9)}
\statement{
  Un nombre palindrome est un nombre dont l'écriture peut se lire indifféremment
  de gauche à droite et de droite à gauche en conservant la même valeur.
<br>
  Par exemple : \x1\x2\x2\x1 est un palindrome.
<br>
Combien y-a-t-il de palindromes compris entre \(\N1) et \(\N2) ?}

\answer{Réponse}{\rep}{type=numexp}
