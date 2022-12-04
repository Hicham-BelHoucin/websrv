<?php
if (isset($_COOKIE['prenom']) && isset($_COOKIE['nom']))
{
    $prenom = $_COOKIE['prenom'];
    $nom = $_COOKIE['nom'];
}
else
{
    setcookie("prenom", $_POST['prenom']);
    setcookie("nom", $_POST['nom']);
    $prenom = $_POST['prenom'];
    $nom = $_POST['nom'];
}
?>


<form action="" method="post" enctype="multipart/form-data">
    Name: <input type="text" name="prenom"><br>
    E-mail: <input type="text" name="nom"><br>
<input type="submit">
</form>


<div>Bonjour <?php echo $nom?>  <?php echo $prenom ?></div>