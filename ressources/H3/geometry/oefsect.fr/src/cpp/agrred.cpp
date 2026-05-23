target=agredlong agredaire agredvol

#include "agrred.inc"

#if defined TARGET_agredlong 
\title{Agrandissement-Réduction (longueur)}
\integer{dim=1}
\real{num2=\num1*\coef}
\matrix{enonce=\(\mathcal{C}_1) est \nom dont la hauteur mesure \num1 \unit. \(\mathcal{C}_2) est \verbe en multipliant les longueurs de \(\mathcal{C}_1) par \coef. Quelle est la hauteur de \(\mathcal{C}_2)
\(\mathcal{C}_1) est \nom. \(\mathcal{C}_2) est \verbe en multipliant les longueurs de \(\mathcal{C}_1) par \coef. La hauteur de \(\mathcal{C}_2) mesure \num2 \unit. Quelle est la longueur de la hauteur de \(\mathcal{C}_1)
\(\mathcal{C}_1) et \(\mathcal{C}_2) sont \pnom dont les dimensions sont proportionnelles. La hauteur de \(\mathcal{C}_1) mesure \num1 \unit et la hauteur de \(\mathcal{C}_2) mesure \num2 \unit. Quel est le coefficient qui permet d'obtenir les dimensions de \(\mathcal{C}_2) en fonction de celles de \(\mathcal{C}_1) }

#endif

#if defined TARGET_agredaire 
\title{Agrandissement-Réduction (aire)}
\text{unit=\(\unit ^2)}
\integer{dim=2}
\real{num2=\num1*(\coef)^2}
\matrix{enonce=\(\mathcal{C}_1) est \nom dont la base a une aire de \num1 \unit. \(\mathcal{C}_2) est \verbe en multipliant les longueurs de \(\mathcal{C}_1) par \coef. Quelle est l'aire de la base de \(\mathcal{C}_2)
\(\mathcal{C}_1) est \nom. \(\mathcal{C}_2) est \verbe en multipliant les longueurs de \(\mathcal{C}_1) par \coef. L'aire de la base de \(\mathcal{C}_2) est de \num2 \unit. Quelle est l'aire de la base de \(\mathcal{C}_1)
\(\mathcal{C}_1) et \(\mathcal{C}_2) sont \pnom dont les dimensions sont proportionnelles. L'aire de la base de \(\mathcal{C}_1) est de \num1 \unit et l'aire de la base de \(\mathcal{C}_2) est de \num2 \unit. Quel est le coefficient qui permet d'obtenir les dimensions de \(\mathcal{C}_2) en fonction de celles de \(\mathcal{C}_1) }

#endif

#if defined TARGET_agredvol 
\title{Agrandissement-Réduction (volume)}
\text{unit=\(\unit ^3)}
\integer{dim=3}
\real{num2=\num1*(\coef)^3}
\matrix{enonce=\(\mathcal{C}_1) est \nom dont le volume est de \num1 \unit. \(\mathcal{C}_2) est \verbe en multipliant les longueurs de \(\mathcal{C}_1) par \coef. Quel est le volume de \(\mathcal{C}_2)
\(\mathcal{C}_1) est \nom. \(\mathcal{C}_2) est \verbe en multipliant les longueurs de \(\mathcal{C}_1) par \coef. Le volume de \(\mathcal{C}_2) est de \num2 \unit. Quel est le volume de \(\mathcal{C}_1)
\(\mathcal{C}_1) et \(\mathcal{C}_2) sont \pnom dont les dimensions sont proportionnelles. Le volume de \(\mathcal{C}_1) est de \num1 \unit et le volume de \(\mathcal{C}_2) est de \num2 \unit. Quel est le coefficient qui permet d'obtenir les dimensions de \(\mathcal{C}_2) en fonction de celles de \(\mathcal{C}_1) }

#endif

#include "agrred2.inc"
