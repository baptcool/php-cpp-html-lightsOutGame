<?php
            require_once "objet.php";
            session_start();
            if(filter_input_array(INPUT_GET)){
                $message= htmlspecialchars(trim(filter_input(INPUT_GET, 'message')));
                echo $message;
            }
             if (isset($_SESSION["utilisateur"])) { 
                 $utilisateur = $_SESSION["utilisateur"]; 
                   $utilisateur[0]->afficher();
             }
               
?>
**********************************************
<form action="serveur.php" method="POST">
              name : <input name="name" type="text" placeholder="name" required=""><br/>
              nom famille :<input name="nameFamily" type="text" placeholder="famille" required="" ><br/>
              age :<input name="age" type="number" min="3" max="99" placeholder="age" required=""><br/>
            <button type="submit">valide</button>
</form>

***********************************************

coté serveur:


if(filter_input_array(INPUT_POST)){
   
    $name = htmlspecialchars(trim(filter_input(INPUT_POST, 'name')));
    $nameFamily =htmlspecialchars(trim(filter_input(INPUT_POST, 'nameFamily')));
    $age =htmlspecialchars(trim(filter_input(INPUT_POST, 'age')));
    
    
    if(is_numeric($age) != 1 || $name  != NULL || $nameFamily  != NULL || $age != NULL ){
       require_once "objet.php";
        session_start();
        
        
        if (isset($_SESSION["utilisateur"])) {    #si il existe deja une session
             $utilisateur = $_SESSION["utilisateur"]; //on enregistre
             $tempo = new Objet($name, $nameFamily, $age);
             array_push($utilisateur,$tempo);
             $_SESSION["utilisateur"] = $utilisateur; //on enregistre 
             
             $str="ok";
             header("location:client.php?message=".urldecode($str));
             
        } else {
            $tempo = new Objet($name, $nameFamily, $age);
            $utilisateur[0]=$tempo;
           //$utilisateur[0]->afficher();
            $_SESSION["utilisateur"] = $utilisateur; //on enregistre 
            $str="ok";
            header("location:client.php?message=".urldecode($str));
        }
      
      
    }
    else{
        $str=" pas valide!";
        header("location:client.php?message=".urldecode($str));
    }
    
    
}



****************************************
objet:



class Objet {

    private $name;
    private $nameFamily;
    private $age;

    
    function __construct($name, $nameFamily,$age) {
       $this->name = $name;
       $this->nameFamily =$nameFamily;
       $this->age=$age;
    }
    

}


*****************************
autres

$base = [
    "baptiste.millot@isen.fr" => "baptiste"
    ];



 if(array_key_exists($email, $base)==true){
        if( $base[$email] == $mdp ){ 
            header("location: auth_ok.html");