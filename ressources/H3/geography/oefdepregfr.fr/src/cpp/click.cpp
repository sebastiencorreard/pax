target=clickdept clickreg clickcode clickcap clickrcap

#include "header.inc"

#if #TARGET (clickdept)
 \title{Département cliqué}
 \text{map=dept.gif}
# include "frdept.inc"
# define DEPARTEMENT 1
#endif

#if #TARGET (clickcode)
 \title{Code cliqué}
 \text{map=dept.gif}
# include "frdept.inc"
# define DEPARTEMENT 1
# define CODEONLY 1
#endif

#if #TARGET (clickcap)
 \title{Chef-lieu cliqué départements}
 \text{map=dept.gif}
# include "frdept.inc"
# define DEPARTEMENT 1
# define CAPONLY 1
#endif

#if #TARGET (clickreg)
 \title{Région cliquée}
 \text{map=region.gif}
# include "frreg.inc"
# define REGION 1
#endif

#if #TARGET (clickrcap)
 \title{Chef-lieu cliqué régions}
 \text{map=region.gif}
# include "frreg.inc"
# define REGION 1
# define CAPONLY 1
#endif

\text{depts=column(2,\data)}
\text{codes=column(1,\data)}
\text{caps=column(3,\data)}
\text{regs=column(4,\data)}
\text{rcaps=column(5,\data)}
\matrix{coords=column((6,7),\data)}
\text{clist=wims(replace internal ; by ;b,\map, in b,\map,\coords)}
\integer{n=rows(\data)}
\integer{t=random(1..\n)}
\text{this=row(\t,\data)}
\text{code=item(1,\this)}
\text{cap=item(3,\this)}
\text{rcap=item(5,\this)}
\text{x=item(6,\this)}
\text{y=item(7,\this)}

#ifdef DEPARTEMENT
 \text{depregs=départements}
 \text{dept=item(2,\this)}
#else
 \text{depregs=régions}
 \text{dept=item(4,\this)}
#endif

\statement{Voici une carte des \depregs de la France. Veuillez cliquer sur
#ifdef CODEONLY
celui dont le code est <b>\code</b>.
#else
# ifdef CAPONLY
#   ifdef DEPARTEMENT
   celui dont le chef-lieu est <b>\cap</b>.
#   else
   celle dont le chef-lieu est <b>\rcap</b>.
#   endif
# else
  <b>\dept</b>.
# endif
#endif
<div class="wimscenter">
\embed{reply 1}
</div>
}

\answer{\dept}{\imagedir/\map;b,\map,\x,\y;\clist}{type=coord}

\text{baddep=item(\result1-1,\depts)}
\text{badreg=item(\result1-1,\regs)}
\text{badcode=item(\result1-1,\codes)}

\feedback{\result1>1}{
#ifdef DEPARTEMENT
    Vous avez cliqué sur <span class="oef_indbad">\baddep (\badcode)</span> au lieu de
    <em>\dept</em> (\code).
#else
    Vous avez cliqué sur <span class="oef_indbad">\badreg</span> au lieu de
    <em>\dept</em>.
#endif
}

