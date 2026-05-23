target=agredlong agredaire agredvol

#include "agrred.inc"

#if #TARGET (agredlong)
\title{Toename-Afname (lengte)}
\integer{dim=1}
\real{num2=\num1*\coef}
\matrix{enonce=\(\mathcal{C}_1) is \nom waarvan de hoogte  \num1 \unit is. \(\mathcal{C}_2) wordt \verbe door de afmetingen van  \(\mathcal{C}_1) met \coef te vermenigvuldigen. Wat is de hoogte van \(\mathcal{C}_2)
\(\mathcal{C}_1) is \nom. \(\mathcal{C}_2) wordt \verbe door de afmetingen van \(\mathcal{C}_1) met \coef te vermenigvuldigen. De hoogte van \(\mathcal{C}_2) is \num2 \unit. Hoe hoog is \(\mathcal{C}_1)
\(\mathcal{C}_1) en \(\mathcal{C}_2) zijn \pnom wiens afmetingen proportioneel zijn. De hoogte van \(\mathcal{C}_1) is \num1 \unit en de hoogte van \(\mathcal{C}_2) is \num2 \unit. Met welk coefficient moet men vermenigvuldigen om de afmetingen van  \(\mathcal{C}_2) vanuit die van  \(\mathcal{C}_1) te krijgen }

#endif

#if #TARGET (agredaire)
\title{Toename-Afname (oppervlak)}
\text{unit=\(\unit ^2)}
\integer{dim=2}
\real{num2=\num1*(\coef)^2}
\matrix{enonce=\(\mathcal{C}_1) is \nom wiens basis een oppervlak van \num1 \unit heeft. \(\mathcal{C}_2) wordt \verbe door de afmetingen van \(\mathcal{C}_1) met \coef te vermenigvuldigen. Wat is het oppervlak van de basis van  \(\mathcal{C}_2)
\(\mathcal{C}_1) is \nom. \(\mathcal{C}_2) wordt \verbe door de afmetingen van  \(\mathcal{C}_1) met \coef te vermenigvuldigen. Het oppervlak van de basis van \(\mathcal{C}_2) is \num2 \unit. Wat is het oppervlak van de basis van \(\mathcal{C}_1)
\(\mathcal{C}_1) en \(\mathcal{C}_2) zijn \pnom wiens afmetingen proportioneel zijn. Het oppervlak van de basis van  \(\mathcal{C}_1) is \num1 \unit en het oppervalk van de basis van  \(\mathcal{C}_2) is \num2 \unit. Met welk coefficient moet men vermenigvuldigen om de afmetingen van  \(\mathcal{C}_2) vanuit die van \(\mathcal{C}_1) te krijgen }

#endif

#if #TARGET (agredvol)
\title{Toename-Afname (volume)}
\text{unit=\(\unit ^3)}
\integer{dim=3}
\real{num2=\num1*(\coef)^3}
\matrix{enonce=\(\mathcal{C}_1) is \nom met volume  \num1 \unit. \(\mathcal{C}_2) wordt \verbe door de afmetingen van  \(\mathcal{C}_1) met \coef te vermenigvuldigen. Wat is het volume van \(\mathcal{C}_2)
\(\mathcal{C}_1) is \nom. \(\mathcal{C}_2) wordt \verbe door de afmetingen van  \(\mathcal{C}_1) met \coef te vermenigvuldigen. Het volume van \(\mathcal{C}_2) is \num2 \unit. Wat is het volume van  \(\mathcal{C}_1)
\(\mathcal{C}_1) en \(\mathcal{C}_2) zijn \pnom wiens afmetingen proportioneel zijn. Het volume van \(\mathcal{C}_1) is \num1 \unit en het volume van \(\mathcal{C}_2) is \num2 \unit. Met welk coefficient moet men vermenigvuldigen om de afmetingen van \(\mathcal{C}_2) vanuit die van \(\mathcal{C}_1) te krijgen }

#endif

#include "agrred2.inc"
