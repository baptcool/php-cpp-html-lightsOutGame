
<?php
require_once "./objet_tableau.php";
session_start();
     
$light = $_SESSION["light"];  

if (filter_input_array(INPUT_GET)) {  #on recupère la position de la case précédement coché
    $hauteur = htmlspecialchars(trim(filter_input(INPUT_GET, "hauteur")));
    $largeur = htmlspecialchars(trim(filter_input(INPUT_GET, "largeur")));
 
    if($hauteur <= 9 && $largeur <= 9){
         $light = new objet_tableau($hauteur,$largeur); //si la bonne taille a été saisie, on peut re-créé le tableau avec la nouvelle taille
    }else{
        $light = new objet_tableau(5,5); // si la taille est trop grande
    }
    $_SESSION["light"]= $light;
    
}
 else{ //par defaut
     
     $light = new objet_tableau($light->hauteur,$light->largeur);
     $_SESSION["light"]= $light;
     
 }


header("location: ./index.php");