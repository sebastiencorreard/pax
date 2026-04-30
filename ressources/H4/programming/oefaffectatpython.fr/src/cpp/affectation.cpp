target=inst2 inst3 inst4 2inst4 2inst2 inst2a inst3a inst4a 2inst4a 2inst4b
\matrix{theme=ambiance,neat;3024-night,3024-day}
\text{list_var=a,b,c,d,f,g,h,l,m,n,o,p,q,r,s,t,u,v,x,y,z}
\text{nomvar=randitem(\list_var)}
\integer{aa=randint(3..9)}
\integer{bb=randitem(+1,-1)*randint(2..\aa-1)}
\text{enonce=Après avoir lu les instructions, déterminer la valeur finale de la variable
 \(\nomvar\).}
\text{consigne=}
\matrix{lr=r1}
\text{llpas=}

#define DEBUT Affectation avec
#define MPP en mode pas à pas
#define ADC avec des calculs
#define INST instructions
#define VAR une variable et
#define VARS deux variables et

#if defined TARGET_inst2 || defined TARGET_inst2a
#include "inst2.inc"
\title{DEBUT VAR 2 INST}
#endif

#if defined TARGET_inst3 || defined TARGET_inst3a
#include "inst3.inc"
\title{DEBUT VAR 3 INST}
#endif

#if defined TARGET_inst4 || defined TARGET_inst4a
#include "inst4.inc"
\title{DEBUT VAR 4 INST}
#endif

#if defined TARGET_2inst4 || defined TARGET_2inst4a
#include "2inst4.inc"
\title{DEBUT VARS 4 INST ADC}
#endif


#if defined TARGET_2inst2 
#include "2inst2.inc"
\title{DEBUT VARS 4 INST}
#endif

#if defined TARGET_inst2a || defined TARGET_inst3a || defined TARGET_inst4a || defined TARGET_2inst4a || defined TARGET_2inst4b
\css{<style>
.tabb {visibility:hidden;display:inline-block;min-width:70px;}
.jxgbox {display:inline-block;}
</style>}
\text{consigne=<div class="wims_instruction">Cliquer sur le bouton intitulé "Mode pas à pas"
 puis compléter le tableau.</div>}
\text{lr=wims(makelist r x for x = 1 to \nbinst+1)}
\integer{ff=\nbinst+1}
\text{llpas=1,1,1,4;2,1,2,6}
#endif

#if defined TARGET_inst2a
\title{DEBUT VAR 2 INST MPP}
#include "inst2a.inc"
#endif

#if defined TARGET_inst3a
\title{DEBUT VAR 3 INST MPP}
#include "inst3a.inc"
\text{llpas=\llpas;3,1,3,6}
#endif

#if defined TARGET_inst4a
\title{DEBUT VAR 4 INST MPP}
# include "inst4a.inc"
#endif

#if defined TARGET_2inst4a
\title{DEBUT VARS 4 INST MPP}
\text{consigne=<div class="wims_instruction">Cliquer sur le bouton intitulé "Mode pas à pas"
 puis compléter le tableau. Si la variable n'a pas de valeur affectée, mettre le mot clef <code>None</code>.</div>}
\text{lr=wims(makelist r x for x = 1 to 2*(\nbinst+1))}
\integer{fff=2*(\nbinst+1)}
\integer{ff=\fff-1}
#include "2inst4a.inc"
#endif

#if defined TARGET_2inst4b
\title{DEBUT VARS 4 INST MPP bis}
\text{consigne=<div class="wims_instruction">Cliquer sur le bouton intitulé "Mode pas à pas"
 puis compléter le tableau. Si la variable n'a pas de valeur affectée, mettre le mot clef <code>None</code>.</div>}
\integer{nbinst=4}
\text{lr=wims(makelist r x for x = 1 to 2*(\nbinst+1))}
\integer{fff=2*(\nbinst+1)}
\integer{ff=\fff-1}
#include "2inst4b.inc"
#endif

\text{prob=Affectation des variables}
\text{instruction=Instruction}
\matrix{nstep=\lr}
\nextstep{\nstep}

\language{fr}
\author{Julien, Lyotard}
\email{Julien.Lyotard@ac-dijon.fr}

\text{A=slib(coding/editor [python,[\code]],1,readonly fullscreen theme=[zenburn,neat] bystep=[\llpas])}

\statement{
<div class="encadre">
<p class="problematique">\prob</p>
<div id="boited">
<img src="\imagedir/python.png" alt="Logo de Python">
</div>
<div class="enonce">
\enonce
\consigne
<div class="question">
\A
#if defined TARGET_inst2a || defined TARGET_inst3a || defined TARGET_inst4a || defined TARGET_2inst4a || defined TARGET_2inst4b
<div class="spacer"></div>
<table class="wimsborder">
<tr><th>ligne n°</th>\for{k=1 to \nbinst}{<td><span id="td1\k">\k</span></td>}</tr>
<tr><th>Valeur de \nomvar</th>\for{jj=1 to \nbinst}{<td><span id="td2\jj" class="tabb">\embed{reply\jj,3}</span></td>}</tr>
#if defined TARGET_2inst4a || defined TARGET_2inst4b
<tr><th>Valeur de \nomvar2</th>\for{jj=1 to \nbinst}{<td><span id="td3\jj" class="tabb">\embed{reply\jj+\nbinst,3}</span></td>}</tr>
#endif
</table>
#endif
<div>La valeur finale de \(\nomvar\) est : \embed{reply\ff,4}</div>
#if defined TARGET_2inst4 || defined TARGET_2inst4a || defined TARGET_2inst2 || defined TARGET_2inst4b
<div>La valeur finale de \(\nomvar2\) est : \embed{reply\fff,4}</div>
#endif
</div>
</div>
</div>
#if defined TARGET_inst2 || defined TARGET_inst3 || defined TARGET_inst4 || defined TARGET_2inst4 || defined TARGET_2inst2
}
#endif
#if defined TARGET_inst2a || defined TARGET_inst3a || defined TARGET_inst4a || defined TARGET_2inst4a || defined TARGET_2inst4b
<script>
    var mode_pasapas = document.getElementById('bystep1');
    var i_modepasapas=1;
    function aff() {var atab=document.getElementsByClassName('tabb');
    for (var i = 0; i < atab.length; i++) {atab[i].style.visibility='visible';}}
    function test() {
        var ele=document.getElementById('td2'+i_modepasapas);
        ele.style.visibility='visible';
        ele.style.backgroundColor='white';
        ele.style.padding='0 0.2em 0 0.2em';
#if defined TARGET_2inst4a || defined TARGET_2inst4b
        var elee=document.getElementById('td3'+i_modepasapas);
        elee.style.visibility='visible';
        elee.style.backgroundColor='white';
        elee.style.padding='0 0.2em 0 0.2em';
#endif        
        document.querySelector('#td2'+i_modepasapas+' input').focus();
        i_modepasapas=i_modepasapas+1;
        if(i_modepasapas==\nbinst+1){mode_pasapas.style.visibility='hidden';};
    }
    mode_pasapas.addEventListener('click',test);
  </script>}
\feedback{1==1}{<script>window.onload = aff;
</script>}
\answer{}{\resultat1}{type=numexp}
\answer{}{\resultat2}{type=numexp}
#endif
#if defined TARGET_inst3a || defined TARGET_inst4a || defined TARGET_2inst4a || defined TARGET_2inst4b
\answer{}{\resultat3}{type=numexp}
#endif
#if defined TARGET_inst4a || defined TARGET_2inst4a || defined TARGET_2inst4b
\answer{}{\resultat4}{type=numexp}
#endif
#if defined TARGET_2inst4a || defined TARGET_2inst4b
\answer{}{\resultat5}{type=case}
\answer{}{\resultat6}{type=numexp}
\answer{}{\resultat7}{type=numexp}
\answer{}{\resultat8}{type=numexp}
#endif
\answer{}{\resultatf}{type=numexp}

#if defined TARGET_2inst4 || defined TARGET_2inst4a || defined TARGET_2inst2 || defined TARGET_2inst4b
\answer{}{\resultatff}{type=numexp}
#endif

\text{nstep=(\step=2)?}
