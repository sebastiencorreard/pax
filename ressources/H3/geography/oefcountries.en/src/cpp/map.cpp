target=mapeu mapas mapaf mapam mapoc mapall mapbig

#if #TARGET (mapeu)
 \title{Maps of Europe}
 \text{continent=of Europe}
# include "eu.inc"
#endif

#if #TARGET (mapas)
 \title{Maps of Asia}
 \text{continent=of Asia}
# include "as.inc"
#endif

#if #TARGET (mapaf)
 \title{Maps of Africa}
 \text{continent=of Africa}
# include "af.inc"
#endif

#if #TARGET (mapam)
 \title{Maps of America}
 \text{continent=of American continent}
# include "am.inc"
#endif

#if #TARGET (mapoc)
 \title{Maps of Oceanic}
 \text{continent=of Oceanic countries}
# include "oc.inc"
#endif

#if #TARGET (mapall) || #TARGET (mapbig)
 \text{af=Africa}
 \text{am=America}
 \text{as=Asia}
 \text{eu=Europe}
 \text{oc=Oceanic}
 \text{continent=}
 \text{continents=\af,\am,\as,\eu,\oc}
# define ALLORBIG 1
#endif

#if #TARGET (mapall)
 \title{Maps of countries}
# include "all.inc"
#endif

#if #TARGET (mapbig)
 \title{Maps of big countries}
# include "big.inc"
#endif

\language{en}
\range{-5..5}
\author{XIAO, Gang}
\email{xiao@unice.fr}
\computeanswer{no}
\format{html}
\precision{10000}

\text{row=randomrow(\data)}
\text{code=item(1,\row)}
\text{pays=item(2,\row)}
\text{names=
#include "pays.inc"
}

#ifdef ALLORBIG
 \text{cont=item(3,\row)}
#endif

\statement{
\img{scripts/data/maps/\code.jpg}{align=right hspace=50}
<p> <center>
 What is this country \continent? <p>
#ifdef ALLORBIG
 \embed{reply 1,18} <p>
 This is a country of
 \embed{choice 1}.
#else
 <br>
 \embed{reply 1,18}
#endif
</center>
}

\answer{Name of the country}{\pays;\names}{type=atext}
#ifdef ALLORBIG
\choice{Continent}{\cont}{\continents}
#endif

