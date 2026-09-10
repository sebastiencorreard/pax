#if defined TARGET_majbase
\text{name_statement1=Les nombres de l'opération suivante sont écrits dans une base \(b\) :}
\text{name_statement2=Donner l'ensemble des bases possibles avec cette seule
    indication sans chercher à trouver une solution
    (s'il y a plusieurs bases possibles, les séparer par des virgules) :}
\text{name_hint=Cherchez des majorations et des minorations de chacun des
   nombres en fonction de la base \(b\) et comparez-les. Par exemple,
   \(2\bullet\bullet\bullet\) est compris entre \(2 b^3\)
   et \(3 b^3\), \(23\bullet\bullet\) est compris entre \((2b+3)* b^2\)
   et \((2b+4)* b^2\).
   Vous pouvez utiliser les outils graphiques pour résoudre les équations
   un peu compliquées.}
#endif
#if defined TARGET_divisiontrou
\text{name_statement= La multiplication suivante, en base \(b\),
  a été partiellement effacée. Dans quelle base se passe cette
  multiplication ? Déterminer les chiffres manquants :}
\text{name_instruction=La base est inférieure à \lim. Les chiffres sont
    écrits de 0 à 9, puis avec des lettres \(A\), \(B\), ...}
\text{name_condition=est un chiffre en base}
\text{name_inbase=en base}
%%% note for translators: keep commas
\text{name_solution=une solution possible est,avec}
#endif
#if defined TARGET_division
%%% note for translators: keep commas
\text{name_statement=Effectuer la division euclidienne de,dans le système de numération de base \b.}
\text{name_by=par}
\text{name_quotient=Quotient}
\text{name_remainder=Reste}
#endif
#if defined TARGET_mental
\text{name_statement=Calculer rapidement \( \a - \b \) en base \base
  en utilisant la méthode de l'aide :}
\text{name_instruction=Tous les nombres sont écrits en base \base.}
\text{name_help1=Voici une méthode permettant de faire des additions et
  des compléments à \base plutôt que des soustractions :}
#endif
#if defined TARGET_mental10
\text{name_statement=Calculer rapidement \( \a - \b \) en utilisant la
  méthode de l'aide :}
\text{name_help1=Voici une méthode si vous préférez faire des additions et des compléments à 10 que des soustractions : }
\text{name_help5=Cette méthode est bien sûr encore valable en écriture
  dans une base \(b\) à la place de 10.}
#endif
#if defined TARGET_mental|| defined TARGET_mental10
\text{name_numbdig=Nombre de chiffres}
\text{name_of=de}
\text{name_help2=si \(p\) est le nombre de chiffres de \b, calculer}
\text{name_help3=Pour calculer \(10^p - \b\) :le chiffre des unités est le
  complément du chiffre des unités à 10, les autres sont le complément à 10
  moins 1.}
\text{name_help4=et enlever \(10^p\) n'est pas trop dur en général, si
  le \(p+1\) chiffre n'est pas un 0.}
#endif
#if defined TARGET_add
\text{name_statement=Effectuer en base \b la somme des nombres}
\text{name_and=et}
#endif
#if defined TARGET_geonum1D
\text{name_statement=Écrire la coordonnée du point dans le système de numération binaire}
#endif
#if defined TARGET_geonum1D || TARGET_geonum2D
\text{name_instruction_point=Utilisez le point comme séparateur pour les décimales.}
#endif
#if defined TARGET_mult
\text{name_statement=En quelle base la multiplication suivante est-elle valable ?}
\text{name_feedback1=Il y a une autre solution \(b = \b\) .}
\text{name_feedback2=En base, on a,La réponse est}
\text{name_feedback3=En base \(b\), tous les chiffres des nombres doivent
  être strictement inférieurs à \(b\). Ce n'est pas le cas ici avec}
#endif
#if defined TARGET_tablemult
\text{name_statement=Voici quelques multiplications tirées d'une
  table. Trouver le système de numération : donner la base \(b\) (écrite en
  base décimale). }
\text{name_condition=La base est correcte ?}
\text{name_feedback1=Un système de numération possible est}
%%% note for translators: keep commas
\text{name_feedback2=Dans la base \base que vous avez indiqué,est égal à,et non pas à}
%%% note for translators: keep commas
\text{name_feedback3=Dans un système de numération de base,les chiffres sont "inférieurs" à}
#endif
#if defined TARGET_mult || defined TARGET_tablemult
\text{name_base=Base}
#endif
#if defined TARGET_addition
\text{name_statement=Donner la table d'addition par \n dans le système de numération de base \b.}
\text{name_help=wims(record 0 of help.fr)}
#endif
#if defined TARGET_entierbase
\text{name_statement1=Combien de nombres entiers positifs ont-ils une écriture en base \base constituée de \n chiffres ?}
\text{name_statement12=Oui, il y a \sol1 nombres entiers positifs dont l'écriture en base \base est constituée de \n chiffres.}
\text{name_statement2=Dans combien de ces nombres le chiffre \ch apparaît-il une fois ?}
\text{name_answer=Réponse}
\text{name_feedback1=Attention, le nombre que vous avez donné est le cardinal de}
\text{name_feedback2=Les suites de \n chiffres commençant
 par 0 ne sont pas des nombres à \n chiffres. }
#endif
#if defined TARGET_numgeo1D
\text{name_statement=Placer le point de l'axe de coordonnée
  <b>\nombre</b> écrite dans le système de numération binaire}
#endif
#if defined TARGET_numgeo2D
\text{name_statement=Placer le point du plan dont les coordonnées
  écrites en numération binaire sont }
#endif
#if defined TARGET_borne
\text{name_list_bigsml=grand,petit}
\text{grand=item(\c,\name_list_bigsml)}
\text{name_statement=Donner le plus \grand nombre (écrit dans le système décimal) ayant \n chiffres dans le système à base \b.}
#endif
#if defined TARGET_livre
\text{name_statement=On effectue la pagination d'un livre et on compte le nombre de caractères utilisés.}
\matrix{name_matrix_question=Le livre a \page pages. Combien utilise-t-on de caractères pour numéroter les pages
On a utilisé \caractere caractères pour numéroter les pages. Combien le livre a-t-il de pages}
\text{name_characters=caractères}
\text{name_pages=pages}
\text{name_numberof=Nombre de}
#endif
#if defined TARGET_geonum2D
\text{name_statement=Donner les coordonnées du point du plan dessiné, écrites en numération binaire :}
#endif
#if defined TARGET_multiplication
\text{name_statement=Donner la table de multiplication par
  \zn dans le système de numération en base \b.}
#endif
#if defined TARGET_immatriculation
\text{name_statement1=Les nouvelles plaques d'immatriculation sont mises en circulation. Chaque véhicule immatriculé
    possède un numéro à vie. Ce numéro est constitué de sept caractères, répartis en trois blocs :}
\text{name_statement2=La numérotation des véhicules est faite de manière
    chronologique et au niveau national, de AA-001-AA à ZZ-999-ZZ, les
    numéros se succèdant de la manière suivante :}
\matrix{name_matrix_statement=Premier bloc : deux lettres
    Deuxième bloc : trois chiffres
    Troisième bloc : deux lettres
    de AA-001-AA à AA-999-AA
    puis de AA-001-AA à AA-999-AB, etc.
    puis de AA-001-BA à AA-999-BZ, etc.
    puis de AB-001-AA à AZ-999-ZZ
    puis de BA-999-AA à ZZ-999-ZZ
    }
\matrix{name_matrix_instruction1=Combien de véhicules devront être immatriculés pour atteindre le numéro \Imat ?
Quel est le nombre de véhicules immatriculés avant d'arriver au numéro \Imat ?
Quel est le nombre de véhicules immatriculés avant d'arriver au numéro \Imat ? }
\text{name_instruction2=Donner l'immatriculation du \voit2-ième véhicule.}
\text{name_instruction3=Au bout de combien d'années ce système de numération est-il épuisé si \N millions de véhicules
  sont immatriculés chaque année ?}
#endif
#if defined TARGET_nbit3
\text{name_statement=Un entier \(n\) a \N chiffres en base \b .
    Donner la plus petite base \(b\) dans laquelle il a sûrement
    moins de \M chiffres.}
\text{name_base=base}
#endif
#if defined TARGET_changbin
\text{name_statement=Donner l'écriture en base \(\b^\k\) du nombre dont l'écriture en base \(\b\) est}
\text{name_instruction1=Utiliser les <em>chiffres</em>}
\text{name_instruction2=sans laisser d'espace}
\text{name_instruction3=en les séparant par un espace}
\text{name_instruction4=Ne pas laisser d'espaces entre les chiffres}
\text{name_answer=en base}
#endif
#if defined TARGET_musique
\text{name_statement=Écrire la valeur de la succession de notes
  suivantes comme un nombre binaire fractionnaire}
\text{name_answer=Valeur du thème}
\text{name_condition=Votre réponse :}
\text{name_feedback=La valeur est}
\text{name_list_notes=noire,blanche,ronde,croche,double croche}
\text{name_help1=La notation musicale s'écrit naturellement
   dans le système binaire fractionnaire.}
\text{name_help2=Prenons une noire comme l'unité de base (1).
  La blanche vaut deux noires, la ronde vaut quatre noires,
  la croche vaut la moitié d'une noire, la double croche vaut le quart
  d'une noire.
  Seules interviennent dans les rapports précédents des puissances
  de 2. }
\text{name_help3=Pour écrire une valeur + la moitié de cette valeur,
  on fait suivre la valeur d'un point. Deux points
  signifient la valeur + sa moitié + son quart.}
\text{name_help4=On est donc dans un système binaire fractionnaire.}
\text{name_explanation=explication}
#endif
#if defined TARGET_guess
\text{name_statement=L'ordinateur a choisi un nombre entre 1 et 63.
  Vous devez le deviner. Pour vous aider, il vous indique que ce nombre
  se trouve uniquement sur les cartes marquées. Quel est ce nombre ?}
\text{name_answer=Le nombre est}
\text{name_hint=Quels nombres se trouvent sur chacune des cartes ?}
#endif

