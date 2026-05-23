#if defined TARGET_01CliquerHypotenuse
\text{hint_text1=Par définition, l'hypoténuse d'un triangle rectangle est le côté opposé à son angle droit.}
#endif

#if defined TARGET_02CliquerAdjacent || defined TARGET_03CliquerOppose || defined TARGET_04ReconTrRect1 || defined TARGET_04ReconTrRect2 || defined TARGET_05ReconTrRect3 || defined TARGET_10DeuxMesures
\text{hint_title2=Vocabulaire dans le triangle rectangle}
\text{hint_text2=
<p>Considérons un triangle ABC rectangle en A.</p>
 <ul class="euler_ul">
  <li>Considérons son angle droit <span style="color:red;font-weight:bold">\(\widehat{BAC}\)</span>.
      <br>Par définition, l'<span style="font-weight:bold">hypoténuse</span>
      du triangle rectangle ABC est le côté opposé à son angle droit&nbsp;;
      c'est le côté <span style="color:red;font-weight:bold">[BC]</span>.
  </li>
  <li>Considérons l'angle aigu <span style="color:blue;font-weight:bold">\(\widehat{ABC}\)</span>.
    <ul class="euler_ul">
      <li>Cet angle a deux côtés&nbsp;: l'un est l'<span style="font-weight:bold">hypoténuse <span style="color:red">[BC]</span></span>,
          l'autre est le <span style="font-weight:bold"> côté adjacent</span> à l'angle aigu \(\widehat{ABC}\).
      </li>
      <li> Le troisième côté du triangle est le <span style="font-weight:bold"> côté opposé</span> à l'angle aigu \(\widehat{ABC}\).
      </li>
    </ul>
  </li>
  <li>Considérons l'angle aigu <span style="color:brown;font-weight:bold">\(\widehat{ACB}\)</span>.
   <ul class="euler_ul">
     <li>Cet angle a deux côtés&nbsp;: l'un est l'<span style="font-weight:bold">hypoténuse <span style="color:red">[BC]</span></span>,
     l'autre est le <strong> côté adjacent</strong> à l'angle aigu \(\widehat{ACB}\).
     </li>
     <li> Le troisième côté du triangle est le <strong> côté opposé</strong> à l'angle aigu \(\widehat{ACB}\).
     </li>
   </ul>
  </li>
 </ul>
 <div class="spacer"></div>
}
#endif

#if defined TARGET_06AssocVocTrigo || defined TARGET_07IdentifierLigneTrigo1 || defined TARGET_08IdentifierLigneTrigo2 || defined TARGET_09DonnerLigneTrigo || defined TARGET_10DeuxMesures || defined TARGET_11LigneTrigoUniteEtape
\text{hint_title3=Trigonométrie dans le triangle rectangle}
\text{hint_text3=
<p>Soit ABC un triangle rectangle en A. Considérons l'angle aigu <span class="insecable">\(\widehat{ABC}\).</span></p>
<p>Par définition, nous avons&nbsp;:</p>
<div class="unbreakable" style="overflow-y:hidden;">
\(sin(\widehat{ABC})=\frac{\text{longueur du côté opposé à l'angle}\; \widehat{ABC}}{\text{longueur de l'hypoténuse}}\)
</div>
<div class="unbreakable" style="overflow-y:hidden;">
\(cos(\widehat{ABC})=\frac{\text{longueur du côté adjacent à l'angle}\; \widehat{ABC}}{\text{longueur de l'hypoténuse}}\)
</div>
<div class="unbreakable" style="overflow-y:hidden;">
\(tan(\widehat{ABC})=\frac{\text{longueur du côté opposé à l'angle}\; \widehat{ABC}}{\text{longueur du côté adjacent à l'angle}\; \widehat{ABC}}\)
</div>
<div class="spacer"></div>
}
#endif

#if defined TARGET_07IdentifierLigneTrigo1 || defined TARGET_08IdentifierLigneTrigo2 || defined TARGET_09DonnerLigneTrigo  || defined TARGET_10DeuxMesures || defined TARGET_11LigneTrigoUniteEtape || defined TARGET_12LigneTrigoUnite
\text{hint_title4=Les questions à se poser}

# if defined TARGET_07IdentifierLigneTrigo1 || defined TARGET_08IdentifierLigneTrigo2 || defined TARGET_09DonnerLigneTrigo  || defined TARGET_11LigneTrigoUniteEtape
\text{hint_text4=Quelles sont les deux longueurs données par l'énoncé&nbsp;?
<br>Quelle relation trigonométrique fait intervenir ces deux longueurs et l'angle étudié&nbsp;?
}
# endif

# if defined TARGET_10DeuxMesures
\text{hint_text4=Quelles sont les deux longueurs données par l'énoncé&nbsp;?
<br>Quelles relations trigonométriques font intervenir ces deux longueurs&nbsp;?
}
# endif

# if defined TARGET_12LigneTrigoUnite
\text{hint_text5=Nous connaissons les longueurs de deux côtés d'un triangle rectangle,
 et nous cherchons une mesure d'angle&nbsp;; nous utilisons dans ce cas la trigonométrie.<br>
Les questions que nous nous posons sont&nbsp;:}
\text{hint_text6=quelles sont les deux longueurs données par l'énoncé&nbsp;?}
\text{hint_text7=quelle relation trigonométrique fait intervenir les deux longueurs données par l'énoncé&nbsp;?}
# endif
#endif
