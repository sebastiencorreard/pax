target=puiss4a puiss4b puiss6a puiss6b puiss8a puiss8b puisspa puisspb

#include "header.inc"
#define TIT Puissances

#if defined TARGET_puisspa
# define PERM 1
# define CNT Permutées
# define TYPE a
# define TT 1
#endif
#if defined TARGET_puisspb
# define PERM 1
# define CNT Permutées
# define TYPE b
# define TT 2
#endif
#if defined TARGET_puiss4a
# define CNT 4
# define TYPE a
# define TT 1
#endif
#if defined TARGET_puiss4b
# define CNT 4
# define TYPE b
# define TT 2
#endif
#if defined TARGET_puiss6a
# define CNT 6
# define TYPE a
# define TT 1
#endif
#if defined TARGET_puiss6b
# define CNT 6
# define TYPE b
# define TT 2
#endif
#if defined TARGET_puiss8a
# define CNT 8
# define TYPE a
# define TT 1
#endif
#if defined TARGET_puiss8b
# define CNT 8
# define TYPE b
# define TT 2
#endif

\title{TIT CNT - TYPE}

#ifdef PERM
 \integer{cnt=6}
 \text{sh=shuffle(2,3,5,6,7)}
 \text{perm=1,2,3;1,3,2;2,1,3;2,3,1;3,1,2;3,2,1}
 \text{list=}
 \text{ll=}
 \for{i=1 to \cnt}{
  \integer{a1=\sh[\perm[\i;1]]}
  \integer{a2=\sh[\perm[\i;2]]}
  \integer{a3=\sh[\perm[\i;3]]}
  \text{list=wims(append item \a1^(\a2^\a3) to \list)}
  \text{ll=wims(append item log(\a1)*(\a2^\a3) to \ll)}
 }
#else
 \integer{range=4}
 \integer{cnt=CNT}
 \text{sh=shuffle(\range^3)}
 \text{sh=\sh[1..20]}
 \text{list=}
 \text{ll=}
 \for{i=1 to \cnt}{
  \integer{a1=(\sh[\i])%\range+3}
  \integer{a2=(floor(\sh[\i]/\range))%\range+3}
  \integer{a3=(floor(\sh[\i]/\range^2))+2}
  \text{list=wims(append item \a1^(\a2^\a3) to \list)}
  \text{ll=wims(append item log(\a1)*(\a2^\a3) to \ll)}
 }
#endif
\text{vlist=wims(values x for x in \ll)}
\text{list=wims(makelist \(x) for x in \list)}
\text{vlsort=wims(sort numeric items \vlist)}
\text{ss=}
\for{i=1 to \cnt}{
 \integer{aa=wims(positionof item \vlsort[\i] in \vlist)}
 \text{ss=wims(append item \aa to \ss)}
}
\text{lsort=item(\ss,\list)}

#if TT == 1
 \integer{dir=random(1,2)}
 \text{name=item(\dir,grand,petit)}
 \text{r=\dir=1?\lsort[\cnt]:\lsort[1]}
 \integer{r=wims(positionof item \r in \list)}
 \statement{Cliquez sur le plus \name des nombres suivants.
  <div class="wimscenter">
  \embed{r1}
 </div>
 }
 \reply{Le plus \name}{\r;\list}{type=click}
#endif

#if TT == 2
 \text{size=55x55x\cnt}
 \statement{
  Rangez les \cnt nombres suivants selon leur ordre de grandeur,
  du plus petit au plus grand.
  <div class="wimscenter">
   \embed{r1,\size}
  </div>
 }
 \reply{L'ordre}{\lsort}{type=dragfill}
#endif



