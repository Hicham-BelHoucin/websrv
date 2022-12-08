<?php
if (isset($_POST['prenom']) && isset($_POST['nom']))
{
    $prenom = $_POST['prenom'];
    $nom = $_POST['nom'];
    setcookie("prenom", $_POST['prenom'], time() + (10 * 365 * 24 * 60 * 60));
    setcookie("nom", $_POST['nom'],   time() + (10 * 365 * 24 * 60 * 60));
}
else
{
    $prenom = $_COOKIE['prenom'];
    $nom = $_COOKIE['nom'];
}
?>
<html>
<form action="" method="post" enctype="multipart/form-data">
    Name: <input type="text" name="prenom"><br>
    E-mail: <input type="text" name="nom"><br>
<input type="submit">
</form>
<div>Bonjour <?php echo $nom?>  <?php echo $prenom ?></div>
</html>