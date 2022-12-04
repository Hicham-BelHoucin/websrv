<?php 
session_id($_COOKIE["PHPSESSID"]);
session_start(); /* Starts the session */
if (!isset($_SESSION["user"])) {
    header("Location: /php-login/1-login.php");
    exit();
}
if (isset($_POST["logout"])) {
    session_destroy(); /* Destroy started session */
    unset($_SESSION);
    header("Location: /php-login/1-login.php");  /* Redirect to login page */
    exit;
}
?>
<form method="post">
    Hello there <?php
        var_dump($_SESSION['user']);
    ?>
  <input type="hidden" name="logout" value="1">
  <input type="submit" value="Sign Out">
</form>