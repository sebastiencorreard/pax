target=chpuiss

#include "header.inc"

\title{Chiffres de puissance}

\integer{n1=randint(3..8)}
\integer{n2=randint(1..9)}
\integer{nn=\n1\n2}
\integer{n=9*(\nn-2)+(9-\n1)+(10-\n2)}

\statement{
  Quelle est la somme des chiffres de \(10^\nn - \nn) ?
}

\reply{Somme des chiffres}{\n}{type=default}

