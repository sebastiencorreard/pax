target=flageu flagas flagaf flagam flagoc flagall flagbig

#if #TARGET (flageu)
 \title{Flags of Europe}
# include "eu.inc"
#endif

#if #TARGET (flagas)
 \title{Flags of Asia}
# include "as.inc"
#endif

#if #TARGET (flagaf)
 \title{Flags of Africa}
# include "af.inc"
#endif

#if #TARGET (flagam)
 \title{Flags of America}
# include "am.inc"
#endif

#if #TARGET (flagoc)
 \title{Flags of Oceanic}
# include "oc.inc"
#endif

#if #TARGET (flagall)
 \title{Flags of countries}
# include "all.inc"
#endif

#if #TARGET (flagbig)
 \title{Flags of big countries}
# include "big.inc"
#endif

\language{en}
\author{XIAO, Gang}
\email{xiao@unice.fr}
\format{html}

\integer{n=rows(\data)}
\text{sh=item(1..5,shuffle(\n))}
\matrix{data=row(\sh,\data)}
\text{data=wims(translate internal | to , in \data)}
\text{flags=column(1,\data)}
\text{countries=column(2,\data)}
\text{flagb=}
\for{i=1 to 5}{
 \text{flag=item(\i,\flags)}
 \text{flag=wims(rename gifs/flags/\flag-lgflag.gif)}
 \text{flagb=wims(append item \flag to \flagb)}
}
text{flags=wims(nospace \flags)}
\text{imgleft=<center><img height=46 src=}
\text{imgright=></center>}

\text{flagb=wims(replace internal , by \imgright,\imgleft in
	\imgleft\flagb\imgright)}
\text{data=\flagb ; \countries}

\statement{Establish the correspondance between the flags and the countries:
<p><center>\embed{reply 1,50x120x150}</center>
}

\answer{The correspondance}{\data}{type=correspond}

