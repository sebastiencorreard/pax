%%%%%%%%%%%%%%%%%%%%%%%%%%% HELP %%%%%%%%%%%%%%%%%%%%%%%%%%%
#if defined TARGET_01a || defined TARGET_02a || defined TARGET_03a || defined TARGET_04a || defined TARGET_05a
\text{aide1=
<h2>Figure</h2>
<ul>
  <li>
    <strong>Menu <em>JSXGraph</em>&nbsp;:</strong>
    <div class="wimscenter"><img  src="\imagedir/JSXGraph_help.png"  alt ="Aide JSXGraph"></div>
  </li>
  <li>
    <strong>Avec la souris&nbsp;:</strong><br>
    <ul>
      <li>Pour <strong>déplacer toute la figure</strong>&nbsp;: clic droit ou gauche maintenu dans la fenêtre <em>JSXGraph</em> tout en déplaçant le curseur de la souris.</li>
      <li>Pour <strong>déplacer l'étiquette</strong> d'un point&nbsp;: clic droit ou gauche maintenu sur l'étiquette tout en déplaçant le curseur de la souris.</li>
      <li>Pour <strong>zoomer</strong> la figure&nbsp;: touche <span class="nowrap" style="font-weight: bold;border: 1px solid grey;border-radius: 5px;background-color: lightgrey;">Maj &#x2191;</span> 
      du clavier enfoncée et roulette de la souris dans la fenêtre <em>JSXGraph</em>.</li>
    </ul>
  </li>
  <li>
    <strong>Sur smartphone et tablette&nbsp;:</strong><br>
    <ul>
      <li>Pour <strong>déplacer la figure</strong>&nbsp;: poser 2 doigts dans la fenêtre <em>JSXGraph</em> et déplacer les 2 doigts en même temps.</li>
      <li>Pour <strong>déplacer l'étiquette</strong> d'un point&nbsp;: déplacement à l'aide d'un seul doigt.</li>
      <li>Pour <strong>zoomer</strong> la figure&nbsp;: poser 2 doigts dans la fenêtre <em>JSXGraph</em> et les éloigner ou les rapprocher pour agrandir ou réduire la figure.</li>
    </ul>
  </li>
</ul>


}
#endif
#if defined TARGET_02a || defined TARGET_02b ||  defined TARGET_03a || defined TARGET_03b || defined TARGET_04a || defined TARGET_04b ||  defined TARGET_05a || defined TARGET_05b
\text{aide2=<h2>Expressions mathématiques</h2>
<ul>
<li>Dans la zone de saisie on pourra écrire un nombre écrit en chiffres ou une expression numérique.</li>
<li>Pour écrire \(\sqrt{3}\) saisir <span class="nowrap"><code>sqrt(3)</code>.</span> 
<li>Pour écrire \(3^2\) saisir <span class="nowrap"><code>3^2</code>.</span> 
<br>Attention, le caractère <code>^</code> n'apparaît qu'après avoir saisi la suite de l'expression.</li>
</ul>
}
#endif

#if defined TARGET_01a
\text{aide=\aide1
}
#endif
#if defined TARGET_02b || defined TARGET_03b ||  defined TARGET_04b ||  defined TARGET_05b 
\text{aide=\aide2}
#endif
#if defined TARGET_02a || defined TARGET_03a || defined TARGET_04a || defined TARGET_05a
\text{aide=
\aide1
\aide2
}
#endif
