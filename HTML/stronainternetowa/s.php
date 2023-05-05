<?php   
    include './funkcje.php';
    switch($_POST["functionname"]){ 

        case 'funkcja': 
            pisz($_POST['arguments'][0]);
            break;      
    }   
?>