# SAC_Enzo_ObjectConnectes

Introduction

Notre client veut donc un système qui puisse contrôler le four à distance et avoir différentes caractéristiques souhaitées. Lorsqu’un employé veut se servir du four, il pourra grâce à un service WEB choisir le bois sélectionné, il aura ensuite les spécificités de celui-ci, le type de bois, son origine, le temps de séchage et la température min pour démarrer le séchage. 
Ensuite lorsqu’il aura sélectionné le bois et l’aura mis dans le four, il pourra actionner un bouton de démarrage et notre service WEB regardera la température actuelle du four et la température de séchage minimum, si le four se trouve dans une plage de 10% de la température qui est en Celsius alors le compte à rebours pourra commencer.
Sinon le four augmentera sa température pour atteindre la température cible. Tant que le four reste dans la plage convenue le compte à rebours décompte jusqu’au temps de séchage définie, mais si la température est trop haute ou trop basse comparé à la température cible alors le compte à rebours retombe à zéro et le système attend que le four revienne dans la plage convenue. On a doit à une marge de +/- 10% d’écart pour la température.
Enfin si le compte à rebours s’est découlé correctement alors l’employé peut retirer le bois du four car la porte se débloquera. On a 3 états de la porte qui sera afficher sur notre page WEB, verte : four prêt à l’emploi, jaune : chauffage en cours et rouge : porte barrée.
Avec ce système on aura un ESP32 qui sera utilisé, celui-ci hébergera notre service WEB, et affichera nos différentes informations. On pourra voir sa connexion au Wifi et la bonne initialisation du système. On y verra le nom du système, l’IP, le mode en cours (Ready, Waiting, Heating) et la température en cours. Tout ceci sera affiché sur un écran OLED relié à notre microprocesseur, des LEDs de couleur Rouge, Jaune et Verte seront aussi connectés à notre système, ainsi qu’un capteur de température pour capter la température actuelle.

Installation

Téléchargez le zip du projet
Avec Visual Studio, installer le plug-in 'PlatformIO', ensuite choissisez la board 'DOIT ESP32 DEVKIT V1' et sélectionner le projet dé-ziper.
Ensuite connecter votre ESP32 bien connecté avec un écran OLED connecté au GPIO SDA : 21 GPIO SCL : 22; branché en 3.3V
Aussi il faudra connecter un DHT22 sur la PIN GPIO 4 en 3.3V
Pour les leds suivez la logique suivante : GPIO12 : pin 12   Rouge, GPIO14 : pin 27   Vert et GPIO27 : pin 14   Jaune 
Enfin vous pouvez UPLOAD le programme et lancez le 'Serial Monitor'

Utilisation

Lors de la première utilisation l'ESP32 va créer un Acess Point, en créant aléatoirement un nom de réseau et un mot de passe.
Il faudra alors vous y connectez et en suite vous connectez au réseau ou l'ESP32 va opérer. Les LEDs vont clignoter 2 fois en cas de réussite.
Une adresse IP va apparaître pour accéder au service WEB il faut se connecter à cette adresse IP.
Ensuite vous pourrez sélectionner le bois et ses détails s'afficheront. En cliquant sur le bouton 'Démarrer le four' l'ESP32 passera en état 'COLD'.
Tant que la température minimum n'est pas atteinte, avec une marge de 10% d'erreur, il restera dans cette état.
En étant dans la plage de la température cible il passera en mode 'HEATING' et un compte à rebours demarrera.
Tant que la température est dans la plage le compte à rebours défilera, si il est sort alors le compte à rebours retombe à zéro.

Contact
Richard Enzo - 2132827@cegeprdl.ca - enzo.richard.pro2@gmail.com
