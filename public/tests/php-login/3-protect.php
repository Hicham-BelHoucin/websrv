<?php
// (A) START SESSION
if (isset($_ENV["HTTP_Cookie"]))
    ini_set('session.use_cookies', 0); # disable session cookies
session_start();
 
// (B) LOGOUT REQUEST
if (isset($_POST["logout"])) {
  session_destroy();
  unset($_SESSION);
}
 
// (C) REDIRECT TO LOGIN PAGE IF NOT LOGGED IN
if (!isset($_SESSION["user"])) {
  header("Location: /php-login/1-login.php");
  exit();
}