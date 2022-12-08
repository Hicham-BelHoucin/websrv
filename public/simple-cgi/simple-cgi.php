<?php
if (isset($_POST['prenom']))
{ ?>
    <h1 style="color: blue"> Bonjour <?php echo ($_POST['prenom'])?>   <?php echo ($_POST['nom'])?>  </h1>
<?php } ?>
<!DOCTYPE html>
<html>
<body>

<form action="" method="POST" enctype="multipart/form-data">
First-Name: <input type="text" name="prenom"><br>
Last-Name: <input type="text" name="nom"><br>
<input type="submit">
</form>

</body>
</html>