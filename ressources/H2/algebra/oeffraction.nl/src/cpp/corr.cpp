target=correq3 correq4 correq5 corrinv3 corrinv4 corrinv5

#include "header.inc"
#define TIT Overeenkomst
#if #TARGET (correq3)
# define TIT2 gelijkheid
# define CNT 3
#endif
#if #TARGET (correq4)
# define TIT2 gelijkheid
# define CNT 4
#endif
#if #TARGET (correq5)
# define TIT2 gelijkheid
# define CNT 5
#endif
#if #TARGET (corrinv3)
# define TIT2 inverse
# define CNT 3
# define INVERSE 1
#endif
#if #TARGET (corrinv4)
# define TIT2 inverse
# define CNT 4
# define INVERSE 1
#endif
#if #TARGET (corrinv5)
# define TIT2 inverse
# define CNT 5
# define INVERSE 1
#endif

\title{TIT TIT2 CNT}
\integer{cnt=CNT}

\text{mulist=1,2,3,4,5,6,8,9,10,12}
#include "matrix.inc"

\text{sh=shuffle(items(\data))}
\text{choice=wims(translate internal / to , in \all[\sh[1..\cnt];1,2])}
\text{left=}
\text{right=}
\for{i=1 to \cnt}{
 \text{left=wims(append item \(\choice[\i;1]/(\choice[\i;2])) to \left)}
#ifdef INVERSE
 \text{right=wims(append item \(\choice[\i;4]/(\choice[\i;3])) to \right)}
#else
 \text{right=wims(append item \(\choice[\i;3]/(\choice[\i;4])) to \right)}
#endif
}
\text{size=50x50x50}

\statement{Geef bij iedere breuk links de breuk rechts aan die 
#ifdef INVERSE
  overeenkomt met zijn inverse. 
#else
 overeenkomt. 
#endif

<p><center>
\embed{reply 1,\size}
</center>
}

\reply{De overeenkomst}{\left;\right}{type=correspond}

