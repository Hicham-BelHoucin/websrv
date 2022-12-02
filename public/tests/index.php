<?php
// Start the session
if(!session_id())
{
	session_start();
	ini_set('session.save_path', '/Users/hbel-hou/Desktop/websrv/public/tests/session');
	ini_set('session.auto_start', 'on');
}
echo "Content-Type: text/html \r\n\r\n"
?>
<!DOCTYPE html>
<html>
<body>
<?php
// Echo session variables that were set on previous page
$_SESSION["favcolor"] = "dfjjdf";
$_SESSION["favanimal"] = "dfjjddfj";
print_r($_SESSION);
?>

</body>