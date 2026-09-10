target=champadd1 champadd2 champadd3 champadd4 champadd5 champmul1 champmul2 champmul3 champmul4 champmul5

\author{Fabrice, Guerimand}
\email{fwguerima@free.fr}
#define TITRE Vocabulaire du champ additif
#define TITR2 Vocabulaire du champ multiplicatif
\keywords{calculation}

#if defined TARGET_champadd1
 \title{TITRE 1}
 \integer{a=randint(1..10)}
 \integer{b=randint(11..20)}
 \text{enonce=L'expression \(\a + \b) est écrite sous la forme }
 \text{good=d'une somme}
 \text{bad=d'un produit,d'une différence,d'un quotient}
#endif

#if defined TARGET_champadd2
 \title{TITRE 2}
 \integer{a=randint(1..10)}
 \integer{b=randint(11..20)}
 \text{enonce=L'expression \(\b - \a) est écrite sous la forme }
 \text{good=d'une différence}
 \text{bad=d'un produit,d'une somme,d'un quotient}
#endif

#if defined TARGET_champadd3
 \title{TITRE 3}
 \integer{a=randint(1..10)}
 \integer{b=randint(11..20)}
 \text{enonce=Dans l'expression \(\b + \a), \b et \a sont}
 \text{good=les termes d'une somme}
 \text{bad=les termes d'un produit,les termes d'une différence,les facteurs d'un produit,les facteurs d'une somme}
#endif

#if defined TARGET_champadd4
 \title{TITRE 4}
 \text{enonce=Le résultat d'une addition est }
 \text{good=une somme}
 \text{bad=un produit,une différence,un quotient,un terme,un facteur}
#endif

#if defined TARGET_champadd5
 \title{TITRE 5}
 \text{enonce=Le résultat d'une soustraction est }
 \text{good=une différence}
 \text{bad=un produit,une somme,un quotient,un terme,un facteur}
#endif

#if defined TARGET_champmul1
 \title{TITR2 1}
 \integer{a=randint(1..10)}
 \integer{b=randint(11..20)}
 \text{enonce=L'expression \(\a \times \b) est écrite sous la forme }
 \text{good=d'un produit}
 \text{bad=d'une somme,d'une différence,d'un quotient}
#endif

#if defined TARGET_champmul2
 \title{TITR2 2}
 \integer{a=randint(1..10)}
 \integer{b=randint(11..20)}
 \text{enonce=L'expression \(\frac{\b}{\a}) est écrite sous la forme }
 \text{good=d'un quotient}
 \text{bad=d'un produit,d'une somme,d'une différence}
#endif

#if defined TARGET_champmul3
 \title{TITR2 3}
 \integer{a=randint(1..10)}
 \integer{b=randint(11..20)}
 \text{enonce=Dans l'expression \(\b \times \a), \b et \a sont}
 \text{good=les facteurs d'un produit}
 \text{bad=les termes d'une somme,les termes d'un produit,les termes d'une différence,les facteurs d'une somme}
#endif

#if defined TARGET_champmul4
 \title{TITR2 4}
 \text{enonce=Le résultat d'une multiplication est }
 \text{good=un produit}
 \text{bad=une somme,une différence,un quotient,un terme,un facteur}
#endif

#if defined TARGET_champmul5
 \title{TITR2 5}
 \text{enonce=Le résultat d'une division est }
 \text{good=un quotient}
 \text{bad=un produit,une somme,une différence,un terme,un facteur}
#endif

\statement{
Complète la phrase suivante :
<div class="wimscenter">\enonce ...</div>}

\choice{}{\good}{\bad}
