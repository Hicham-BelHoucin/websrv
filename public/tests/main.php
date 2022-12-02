<?php
if(!session_id())
{
    session_start();
}
echo "Content-Type: text/html \r\n\r\n"
?>
<!DOCTYPE html>
<html lang="en">

<head>
	<title>Document</title>
</head>

<body >
	<div >
	<?php
		// Echo session variables that were set on previous page
		echo "Favorite color is " . $_SESSION["favcolor"] . ".<br>";
		echo "Favorite animal is " . $_SESSION["favanimal"] . ".";
		print_r($_SESSION);
	?>
	</div>
</body>

</html>