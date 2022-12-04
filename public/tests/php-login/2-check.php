<?php
// (A) START SESSION
if (isset($_COOKIE["PHPSESSID"]))
    ini_set('session.use_cookies', 0); # disable session cookies
session_start();
 
// (B) PROCESS LOGIN
if (isset($_POST["user"]) && !isset($_SESSION["user"])) {
  // (B1) USERS & PASSWORDS - SET YOUR OWN !
   $users = [
    "joe" => "123456",
    "jon" => "654321",
    "joy" => "987654"
  ];
 
  // (B2) CHECK & VERIFY
  if (isset($users[$_POST["user"]]) && $users[$_POST["user"]] == $_POST["password"]) {
    $_SESSION["user"] = $_POST["user"];
  }
 
  // (B3) FAILED LOGIN FLAG
  if (!isset($_SESSION["user"])) { $failed = true; }
}
 
// (C) REDIRECT TO HOME PAGE IF SIGNED IN - SET YOUR OWN !
if (isset($_SESSION["user"])) {
  header("Location: /4-dummy.php");
  exit();
}