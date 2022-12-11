<?php
    session_start();
    if (!isset($_SESSION['luser'])) {
		echo "<html>Please Login again";
        echo "<a href='/php-login/login.php'>Click Here to Login</a>";
    }
    else {
		$now = time(); // Checking the time now when home page starts.

        if ($now > $_SESSION['expire']) {
			session_destroy();
            echo "<html> Your session has expired! <a href='/php-login/login.php'>Login here</a>";
        }
        else { //Starting this else one [else1]
?>
<html>

    Welcome
    <?php
        echo $_SESSION['luser'];
        echo "<a href='/php-login/logout.php'>Log out</a>";
    ?>
</html>
<?php
        }
    }
?>
