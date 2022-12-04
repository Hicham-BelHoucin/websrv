<?php session_start(); /* Starts the session */
    echo "Content-Type: text/html; charset=UTF-8 \r\n\r\n";
if(!isset($_SESSION['UserData']['Username'])){
        header("Location: /php-login/login.php");
        exit;
}
?>

Congratulation! You have logged into password protected page. <a href="/php-login/logout.php">Click here</a> to Logout.