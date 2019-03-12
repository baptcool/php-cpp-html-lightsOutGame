<!DOCTYPE html>
<html>
    <head>
        <title>LIGHTS OUT ! GBL</title>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link rel="stylesheet" href="./css/cssPrincipal.css" type="text/css"/>
        <link rel="stylesheet" type="text/css" href="./css/style.css"/>
        <link href='https://fonts.googleapis.com/css?family=Oswald' rel='stylesheet' type='text/css'>
    </head>
    <body>
        <header>
            <form id="wrapLeft" action="zero.php" method="get">
                <input type="number" name="largeur" placeholder="Largeur" class="boutonInput" min="0" max="64">
                <input type="number" name="hauteur" placeholder="Longueur" class="boutonInput" min="0" max="64">
                <button id="boutonOK">OK</button>
            </form>
            <span id="Centerer">
                <img src="images/title.png" id="title" alt=""/>
            </span>
            <div id="wrapRight">
                <form action="zero.php" method="get">
                    <button type="submit"  class="choixBouton" id="first">Générer <br> Aléatoirement</button>
                </form>

                <form action="personalisation.php" method="get">
                    <button type="submit"   class="choixBouton" id="second">Prédéfinir le<br>tableau</button>

                </form>
            </div>
        </header>
        <div id="bravo">Bravo ! tu as réussi!</div>
        <section id="gameWrapper">
            <article id="jeu">
                <img src="images/stalone.jpg" id="imageVictoire" alt="HTML5 Icon" style="width:500px;height:500px;">
            </article>
        </section>
    </body>
</html>
